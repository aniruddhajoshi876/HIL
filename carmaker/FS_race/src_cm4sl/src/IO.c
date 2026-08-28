/*
******************************************************************************
**  CarMaker - Version 12.0.1
**  Vehicle Dynamics Simulation Toolkit
**
**  Copyright (C)   IPG Automotive GmbH
**                  Bannwaldallee 60             Phone  +49.721.98520.0
**                  76185 Karlsruhe              Fax    +49.721.98520.99
**                  Germany                      WWW    www.ipg-automotive.com
******************************************************************************
**
** Connection to I/O hardware of the CarMaker/HIL test stand
**
** Connected test rig: ???
**
******************************************************************************
**
** Functions
** ---------
**
** - iGetCal ()
** - CalIn ()
** - CalInF ()
** - CalOut ()
** - CalOutF ()
** - LimitInt ()
** - IO_Init_First ()
** - IO_Init_Finalize ()
** - IO_Init ()
** - IO_Param_Get ()
** - IO_BeginCycle ()
** - IO_In ()
** - IO_Out ()
** - IO_Cleanup ()
**
******************************************************************************
*/

#include <Global.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <CarMaker.h>
#include <pcanio.h>
#include <E2E.h>

#if defined(XENO)
#include <mio.h>
#endif /* defined(XENO) */
#include <ioconf.h>
#if defined(CM_HIL)
#include <FailSafeTester.h>
#endif /* defined(CM_HIL) */

#include "IOVec.h"


/*** I/O vector */
tIOVec IO;


/*** CarMaker CAN interface */

#define MFE_PCAN_DEVICE		pcan_usb
/* Probed at init: CarMaker's PCANIO channel numbering vs PCANBasic's
** PCAN_USBBUS1 handle is not documented, so try the plausible values
** and keep whichever the driver accepts. */
static int MFE_PCAN_CHANNEL = 1;
static const int MFE_PCAN_CHANNEL_CANDIDATES[] = { 0, 1, 0x51 };
#define MFE_PCAN_BITRATE	1000000
#define MFE_PCAN_RX_MAX	16

double MFE_CAN_InverterTorqueSetpointNm[4];
unsigned char MFE_CAN_InverterReady[4];

/* CarMaker vehicle-physics truth sent to the Speedgoat on channel 1 as the
** 0x503-0x506 frames (see VC_HIL/docs/carmaker_imu_truth_source_plan.md).
** Written by TorqueVect.mdl through the MFE_CAN.Physics.* dictionary
** quantities; sampled here in IO_Out(). Vehicle/Fr1 frame, SI units -- the
** Speedgoat applies the sensor mounting transform, not this side. */
double MFE_CAN_PhysicsAcceleration[3];
double MFE_CAN_PhysicsAngularRate[3];
double MFE_CAN_PhysicsVelocity[3];
double MFE_CAN_PhysicsEuler[3];

/* Aggregates of the four per-inverter values above, maintained here rather
** than as extra Simulink blocks so the vehicle model keeps a single scalar
** demand and a single gate, exactly as the superseded XCP path provided.
*/
double MFE_CAN_TorqueRequestTotalNm;
unsigned char MFE_CAN_DriveActive;

static int MFE_PCAN_Initialized;
static unsigned char MFE_PCAN_AliveCounter;
static unsigned char MFE_PCAN_PhysicsGroupCounter;
static int MFE_PCAN_Ready;


/*** I/O configuration */

/* int IO_None; DON'T - Variable is predefined by CarMaker! */
int IO_CAN_IF;
int IO_FlexRay;

static struct tIOConfig IOConfiguration[] = {
/* This table should contain one line for each IO_xyz-flag in IOVec.h */
/*  { <Flagvar>,	<Name for -io>,	<Description for -help> },     */
    { &IO_None,		"none",		"No I/O" }, /* Always keep this first line! */
    { &IO_CAN_IF,	"can",		"CAN communication" },
    { &IO_FlexRay,	"flexray",	"FlexRay communication" },
    { NULL, NULL, NULL } /* End of table */
};



/**** Additional useful functions *********************************************/


/*
** iGetCal()
**
** Read calibration parameters.
*/

void
iGetCal (tInfos *Inf, const char *key, tCal *cal, int optional)
{
    cal->Min       =  1e37f;
    cal->Max       = -1e37f;
    cal->LimitLow  =  1e37f;
    cal->LimitHigh = -1e37f;
    cal->Factor    =  1.0f;
    cal->Offset    =  0.0f;
    cal->Rezip     =  0;

    const char *item = iGetStrOpt(Inf, key, NULL);
    if (item != NULL) {
	int n = sscanf(item, "%g %g %g %g %d",
		       &cal->LimitLow, &cal->LimitHigh,
		       &cal->Factor,   &cal->Offset, &cal->Rezip);
	if (n != 5)
	    LogErrF(EC_Init, "Invalid calibration parameter entry '%s'", key);
    } else {
	if (!optional) {
	    LogErrF(EC_Init, "Missing calibration parameter entry '%s'", key);
	    return;
	}
	cal->LimitLow  = -1e37f;
	cal->LimitHigh =  1e37f;
    }

    cal->Min = cal->LimitHigh;
    cal->Max = cal->LimitLow;
}


/*
** CalInF() / CalIn()
**
** Analog input -> calibration infos -> physical quantity
** Converts an I/O value (e.g. the voltage from an analog input module) to
** the corresponding physical value, delimited by LimitLow and LimitHigh.
*/

float
CalInF (tCal *cal, float Value)
{
    float Result = (Value - cal->Offset) * cal->Factor;

    if (cal->Rezip)
	Result = 1.0f / Result;

    if      (Result < cal->Min)  cal->Min = Result;
    else if (Result > cal->Max)  cal->Max = Result;

    if      (Result < cal->LimitLow)   Result = cal->LimitLow;
    else if (Result > cal->LimitHigh)  Result = cal->LimitHigh;

    return Result;
}

float
CalIn (tCal *cal, int Value)
{
    return CalInF(cal, (float) Value);
}


/*
** CalOutF() / CalOut()
**
** Physical quantity -> calibration infos -> analog output
** The physical value is delimited by LimitLow and LimitHigh and then converted
** to the corresponding I/O value (e.g. voltage for an analog output module).
*/

float
CalOutF (tCal *cal, float Value)
{
    if      (Value < cal->Min) cal->Min = Value;
    else if (Value > cal->Max) cal->Max = Value;

    if      (Value < cal->LimitLow)  Value = cal->LimitLow;
    else if (Value > cal->LimitHigh) Value = cal->LimitHigh;

    if (cal->Rezip) {
	return 1.0f / (Value*cal->Factor) + cal->Offset;
    } else {
	return Value/cal->Factor + cal->Offset;
    }
}

int
CalOut (tCal *cal, float Value)
{
    return (int)CalOutF(cal, Value);
}


int
LimitInt (float fValue, int Min, int Max)
{
    int Value = (int)fValue;
    if      (Value < Min) return Min;
    else if (Value > Max) return Max;
    return   Value;
}



/*****************************************************************************/


/*
** IO_Init_First ()
**
** First, low level initialization of the IO module
**
** Call:
** - one times at start of program
** - no realtime conditions
*/

int
IO_Init_First (void)
{
    memset(&IO,  0, sizeof(IO));

    IO_SetConfigurations(IOConfiguration);

    return 0;
}



/*
** IO_Init ()
**
** initialization
** - i/o hardware
** - add variables to data dictionary
**
** call:
** - single call at program start
*/

int
IO_Init (void)
{
    char status_text[256] = { 0 };
    unsigned int status;

    Log("I/O Configuration: %s\n", IO_ListNames(NULL, 1));

#if defined(XENO)
    if (IOConf_Init() < 0)
            return -1;
#endif /* defined(XENO) */

    /* PCAN link. Deliberately initialised BEFORE the IO_None early return:
    ** this adapter is not a CarMaker MIO module, so it must not depend on
    ** CarMaker's -io hardware mode, which is "none" for a normal CM4SL run.
    ** Failures are logged and leave MFE_PCAN_Ready clear rather than aborting
    ** init, so the bench still runs with no adapter attached.
    */
    MFE_PCAN_Ready = 1;
    if (PCANIO_Init() != 0) {
	LogErrF(EC_Init, "PCANIO_Init failed - CAN disabled, CarMaker continues");
	MFE_PCAN_Ready = 0;
    }

    {
	int ci, ok = 0;
	for (ci = 0; ci < (int)(sizeof MFE_PCAN_CHANNEL_CANDIDATES
			       / sizeof MFE_PCAN_CHANNEL_CANDIDATES[0]); ci++) {
	    int cand = MFE_PCAN_CHANNEL_CANDIDATES[ci];
	    if (PCANIO_SetCommParam(MFE_PCAN_DEVICE, cand,
				    MFE_PCAN_BITRATE, 0, NULL, NULL) == 0) {
		MFE_PCAN_CHANNEL = cand;
		ok = 1;
		Log("PCAN-USB FD: channel index %d accepted by PCANIO\n", cand);
		break;
	    }
	    Log("PCAN-USB FD: channel index %d rejected, trying next\n", cand);
	}
	if (!ok) {
	LogErrF(EC_Init, "PCAN-USB FD channel %d: 1 Mbit/s classic-CAN setup failed",
		MFE_PCAN_CHANNEL);
	PCANIO_Terminate();
	MFE_PCAN_Ready = 0;
	}
    }

    status = PCANIO_GetStatus(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL, status_text);
    if (status != 0) {
	LogErrF(EC_Init, "PCAN-USB FD channel %d status 0x%x: %s",
		MFE_PCAN_CHANNEL, status, status_text);
	PCANIO_CloseComm(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL);
	PCANIO_Terminate();
	MFE_PCAN_Ready = 0;
    }
    if (MFE_PCAN_Ready)
	Log("PCAN-USB FD: CAN link ready on channel %d\n", MFE_PCAN_CHANNEL);

    /* hardware configuration "none" */
    if (IO_None)
	return 0;
#if defined(CM_HIL)
    int nErrors = Log_nError;

    /*** MIO initialization */
    if (MIO_Init(NULL) < 0) {
	LogErrF(EC_General, "MIO initialization failed. I/O disabled (1)");
	IO_SelectNone();
	return -1;
    }
    MIO_SetAppState(0.0, MIO_SimState_AppInit);
    // MIO_ModuleShow();

    /* check for MIO errors */
    if (nErrors != Log_nError) {
	LogErrF(EC_General, "MIO initization failed. I/O disabled (2)");
	IO_SelectNone();
	return -1;
    }
#endif /* defined(CM_HIL) */

#if defined(XENO)
    /*** FailSafeTester */
    FST_ConfigureCAN();
#endif /* defined(XENO) */


    MFE_PCAN_Initialized = 1;
    Log("PCAN-USB FD channel %d initialized: 1 Mbit/s classic CAN (%s)\n",
	MFE_PCAN_CHANNEL, status_text);

    return 0;
}


/*
** IO_Init_Finalize ()
**
** last (deferred) I/O initialization step
**
** call:
** - single call at program start in CarMaker_FinishStartup()
*/

int
IO_Init_Finalize (void)
{

    return 0;
}


/*
** IO_Param_Get ()
**
** Get i/o configuration parameters
** - calibration
** - constant values
** - ids
*/

int
IO_Param_Get (tInfos *inf)
{
    unsigned nError = GetInfoErrorCount ();
#if defined(CM_HIL)
    /* ignition off */
    SetKl15 (0);
#if defined(XENO)
    IOConf_Param_Get();
#endif /* defined(XENO) */
#endif /* defined(CM_HIL) */

    if (IO_None)
    	return 0;

    return nError != GetInfoErrorCount() ? -1 : 0;
}


void
IO_BeginCycle (void)
{
#if defined(CM_HIL)
    MIO_SetAppState(TimeGlobal, (tMIO_SimState)SimCore_State2MIO_SimState(SimCore.State));
#endif /* defined(CM_HIL) */
}


/*
** IO_In ()
**
** reading signals from hardware / ECU
**
** CycleNo: simulation cycle counter, incremented every loop/millisecond
**
** call:
** - in the main loop
** - first function call in main loop, after waiting for next loop
** - just before User_In()
** - pay attention to realtime condition
*/

void
IO_In (unsigned CycleNo)
{
    int i;
    int raw;
    CAN_Msg Msg;

#if defined(CM_HIL)
    IO.DeltaT = SimCore.DeltaT;
    IO.T      = TimeGlobal;
#if defined(XENO)
    IOConf_In(CycleNo);
#endif /* defined(XENO) */
    if (IO_None)
	return;

    /*** FailSafeTester messages */
    if (FST_IsActive()) {
#if defined(XENO)
	while (MIO_M51_Recv(FST_CAN_Slot, FST_CAN_Ch, &Msg) == 0)
	    FST_MsgIn (CycleNo, &Msg);
#endif /* defined(XENO) */
    }
#endif /* defined(CM_HIL) */

    for (i=0; i<MFE_PCAN_RX_MAX; i++) {
	if (PCANIO_Recv(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL, &Msg) != 0)
	    break;

	if (Msg.FrameFmt != 0 || Msg.RTR != 0 || Msg.FrameLen != 8)
	    continue;

	if (Msg.MsgId == 0x501) {
	    raw = (int)Msg.Data[0] | ((int)Msg.Data[1] << 8);
	    if (raw & 0x8000)
		raw -= 0x10000;
	    MFE_CAN_InverterTorqueSetpointNm[0] = raw / 32.0;

	    raw = (int)Msg.Data[2] | ((int)Msg.Data[3] << 8);
	    if (raw & 0x8000)
		raw -= 0x10000;
	    MFE_CAN_InverterTorqueSetpointNm[1] = raw / 32.0;

	    raw = (int)Msg.Data[4] | ((int)Msg.Data[5] << 8);
	    if (raw & 0x8000)
		raw -= 0x10000;
	    MFE_CAN_InverterTorqueSetpointNm[2] = raw / 32.0;

	    raw = (int)Msg.Data[6] | ((int)Msg.Data[7] << 8);
	    if (raw & 0x8000)
		raw -= 0x10000;
	    MFE_CAN_InverterTorqueSetpointNm[3] = raw / 32.0;

	    MFE_CAN_TorqueRequestTotalNm =
		MFE_CAN_InverterTorqueSetpointNm[0]
		+ MFE_CAN_InverterTorqueSetpointNm[1]
		+ MFE_CAN_InverterTorqueSetpointNm[2]
		+ MFE_CAN_InverterTorqueSetpointNm[3];
	} else if (Msg.MsgId == 0x502) {
	    if ((Msg.Data[0] & 0xf0) != 0 || Msg.Data[1] != 0 ||
		Msg.Data[2] != 0 || Msg.Data[3] != 0 || Msg.Data[4] != 0 ||
		Msg.Data[5] != 0 || Msg.Data[6] != 0 || Msg.Data[7] != 0)
		continue;

	    MFE_CAN_InverterReady[0] = Msg.Data[0] & 0x01;
	    MFE_CAN_InverterReady[1] = (Msg.Data[0] >> 1) & 0x01;
	    MFE_CAN_InverterReady[2] = (Msg.Data[0] >> 2) & 0x01;
	    MFE_CAN_InverterReady[3] = (Msg.Data[0] >> 3) & 0x01;

	    /* Provisional, deliberately permissive: any single inverter
	    ** reporting ready is enough to gate the vehicle model. Requiring
	    ** all four was judged too strict for bring-up. Revisit before the
	    ** bench is trusted under load, since this admits a partially
	    ** ready drive chain.
	    */
	    MFE_CAN_DriveActive = (unsigned char)
		(MFE_CAN_InverterReady[0] || MFE_CAN_InverterReady[1]
		 || MFE_CAN_InverterReady[2] || MFE_CAN_InverterReady[3]);
	}
    }

}



/* Round-and-saturate a physical value to a signed 16-bit count. */
static short
MFE_PhysicsRoundSaturate (double value, double scale)
{
    double counts = value / scale;
    if (counts >  32767.0) counts =  32767.0;
    if (counts < -32768.0) counts = -32768.0;
    return (short)(counts >= 0.0 ? counts + 0.5 : counts - 0.5);
}

/* Pack and send one physics frame (0x503-0x506): three little-endian int16
** at bytes 0/2/4, the shared group counter at byte 6, and CRC-8/SAE-J1850
** over bytes 0-6 at byte 7 -- the same helper the 0x500 frame uses. */
static void
MFE_SendPhysicsFrame (unsigned id, const double value[3], double scale,
		      unsigned char counter)
{
    CAN_Msg Msg;
    int i;

    memset(&Msg, 0, sizeof(Msg));
    Msg.MsgId    = id;
    Msg.FrameFmt = 0;
    Msg.RTR      = 0;
    Msg.FrameLen = 8;
    for (i = 0; i < 3; i++) {
	unsigned short raw =
	    (unsigned short)MFE_PhysicsRoundSaturate(value[i], scale);
	Msg.Data[2*i]   = raw & 0xff;
	Msg.Data[2*i+1] = (raw >> 8) & 0xff;
    }
    Msg.Data[6] = counter;
    Msg.Data[7] = GetCRC_J1850_User(Msg.Data, 7, 0xff, 0xff);

    if (PCANIO_Send(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL, &Msg) != 0)
	LogErrF(EC_General,
		"PCAN-USB FD channel %d: physics CAN 0x%03x send failed",
		MFE_PCAN_CHANNEL, id);
}


/*
** IO_Out ()
**
** writing signals to hardware / ECU
**
** CycleNo: simulation cycle counter, incremented every loop/millisecond
**
** call:
** - in the main loop
** - last function call in main loop
** - just after User_Out()
** - pay attention to realtime condition
*/

void
IO_Out (unsigned CycleNo)
{
    CAN_Msg Msg;
    int throttle;
    int brake;

#if defined(XENO)
    IOConf_Out(CycleNo);
#endif /* defined(XENO) */
    if (IO_None)
	return;
#if defined(CM_HIL)
    /*** Messages to the FailSafeTester */
    FST_MsgOut(CycleNo);
#endif /* defined(CM_HIL) */

    if (!MFE_PCAN_Ready || CycleNo % 10 != 0)
	return;

    throttle = LimitInt((float)(DrivMan.Gas * 10000.0 + 0.5), 0, 10000);
    brake    = LimitInt((float)(DrivMan.Brake * 10000.0 + 0.5), 0, 10000);

    memset(&Msg, 0, sizeof(Msg));
    Msg.MsgId    = 0x500;
    Msg.FrameFmt = 0;
    Msg.RTR      = 0;
    Msg.FrameLen = 8;
    Msg.Data[0]  = throttle & 0xff;
    Msg.Data[1]  = (throttle >> 8) & 0xff;
    Msg.Data[2]  = brake & 0xff;
    Msg.Data[3]  = (brake >> 8) & 0xff;
    Msg.Data[4]  = 0x01 | ((MFE_PCAN_AliveCounter & 0x0f) << 1);
    MFE_PCAN_AliveCounter = (MFE_PCAN_AliveCounter + 1) & 0x0f;
    Msg.Data[5] = GetCRC_J1850_User(Msg.Data, 5, 0xff, 0xff);

    if (PCANIO_Send(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL, &Msg) != 0)
	LogErrF(EC_General, "PCAN-USB FD channel %d: CAN send failed",
		MFE_PCAN_CHANNEL);

    /* Vehicle-physics group: four consecutive frames on the same 10-ms cycle
    ** sharing one modulo-256 counter, sent right after 0x500. Scales match
    ** carmaker/config/MFE26_Inverter_CarMaker.dbc; the values are decoded by
    ** the Speedgoat, never by CarMaker. */
    MFE_SendPhysicsFrame(0x503, MFE_CAN_PhysicsAcceleration, 0.01,
			 MFE_PCAN_PhysicsGroupCounter);
    MFE_SendPhysicsFrame(0x504, MFE_CAN_PhysicsAngularRate,  0.002,
			 MFE_PCAN_PhysicsGroupCounter);
    MFE_SendPhysicsFrame(0x505, MFE_CAN_PhysicsVelocity,     0.01,
			 MFE_PCAN_PhysicsGroupCounter);
    MFE_SendPhysicsFrame(0x506, MFE_CAN_PhysicsEuler,        0.0001,
			 MFE_PCAN_PhysicsGroupCounter);
    MFE_PCAN_PhysicsGroupCounter++;

}



/*
** IO_Cleanup ()
**
** Uninits all MIO hardware:
** - puts M-Modules into reset state
** - frees unneeded memory
*/

void
IO_Cleanup (void)
{
    if (IO_None)
	goto EndReturn;

#if defined(XENO)
    IOConf_Cleanup();
#endif
#if defined(CM_HIL)
    MIO_SetAppState(TimeGlobal, MIO_SimState_AppExit);
    MIO_ResetModules();
    MIO_DeleteAll();
#endif /* defined(CM_HIL) */

    if (MFE_PCAN_Initialized) {
	PCANIO_CloseComm(MFE_PCAN_DEVICE, MFE_PCAN_CHANNEL);
	PCANIO_Terminate();
	MFE_PCAN_Initialized = 0;
    }

  EndReturn:
    return;
}
