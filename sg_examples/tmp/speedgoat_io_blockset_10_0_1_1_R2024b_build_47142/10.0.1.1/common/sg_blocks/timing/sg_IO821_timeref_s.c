#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO821_timeref_s

/** TODO:

Initial Host Time includes the Time Zone offset: setting a value of datenum(2015,07,04,10,30,00) will set the module time to 04-Jul-2015 8:30:00

docnotes
The board is capable of using multiple time zone and DST settings for  different references and outputs. This is not (yet) implemented in this driver.

*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifdef 	 MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "IO821.h"
#endif

#define SG_HAS_MDL_EXIT //Causes sg_ModelExit() to be called upon process exit
#define SG_EARLY_INIT   //Causes sg_ModelLoad() to be called upon tg.load for R2024a and later
#include "sg_callback.h"
#include "sg_printf.h"


/* Debug Settings */
#define DEBUG_PRINTF
//#define DEBUG_PRINT_FUNCTION_CALLS

/* Board constants */
#define DEVNAME "Speedgoat IO821"
#define VENDORID 0x1ad7
#define DEVICEID 0x8000
#define SUBVENDORID 0x1ad7
//#define SUBDEVICEID 0x7400  //PMC: 0x7400, PCIe: 0x8000


/* Input Arguments (copy from Block Parameters in lib context menu):
parPciSlot, parModuleId, parPeriodicIntEnable, parNanoPeriod, parPeriodicIntAlign, parShowActiveRef, parShowSyncState, parShowHoldoverState, parShowAlarmState, parShowTime, parTimeOffset, parInitialTime, parRefEnable_1, parRefPrio_1, parRefTime_1, parRef1PPS_1, parRefEnable_2, parRefPrio_2, parRefTime_2, parRef1PPS_2, parRefEnable_3, parRefPrio_3, parRefTime_3, parRef1PPS_3, parRefEnable_4, parRefPrio_4, parRefTime_4, parRef1PPS_4, parRefEnable_5, parRefPrio_5, parRefTime_5, parRef1PPS_5, parRefEnable_6, parRefPrio_6, parRefTime_6, parRef1PPS_6
*/




//#define REF_TABLE_ENABLE_ARG(x) mxGetPr(parRefEnable_#x_ARG)[0]

#define SLOT_ARG                    ssGetSFcnParam(S,  0) // parPciSlot
#define parModuleId_ARG             ssGetSFcnParam(S,  1) // parModuleId
#define parPeriodicIntEnable_ARG    ssGetSFcnParam(S,  2) // parPeriodicIntEnable
//
#define parIntDutyCycle_ARG         ssGetSFcnParam(S,  3) // parIntDutyCycle
//
#define parNanoPeriod_ARG           ssGetSFcnParam(S,  4) // parNanoPeriod
#define parPeriodicIntAlign_ARG     ssGetSFcnParam(S,  5) // parPeriodicIntAlign
#define parShowActiveRef_ARG        ssGetSFcnParam(S,  6) // parShowActiveRef
#define parShowSyncState_ARG        ssGetSFcnParam(S,  7) // parShowSyncState
#define parShowHoldoverState_ARG    ssGetSFcnParam(S,  8) // parShowHoldoverState
#define parShowAlarmState_ARG       ssGetSFcnParam(S,  9) // parShowAlarmState
#define parShowTime_ARG             ssGetSFcnParam(S, 10) // parShowTime
//
#define parLeadTime1_ARG            ssGetSFcnParam(S, 11) // parTimeFormat
#define parLeadTime2_ARG            ssGetSFcnParam(S, 12) // parTimeFormat
#define parTimeFormat_ARG           ssGetSFcnParam(S, 13) // parTimeFormat
#define par0EdgeDetection_ARG       ssGetSFcnParam(S, 14) // par0EdgeDetect
#define par0SignalEdge_ARG          ssGetSFcnParam(S, 15) // rising or falling edge?
#define par1EdgeDetection_ARG       ssGetSFcnParam(S, 16) // par1EdgeDetect
#define par1SignalEdge_ARG          ssGetSFcnParam(S, 17) // rising or falling edge?
#define parEdgeDetectionFormat_ARG  ssGetSFcnParam(S, 18) // parEdgeDetectTimeFormat
//
#define parHWTrig1Enable_ARG        ssGetSFcnParam(S, 19) // parHWTrig1Enable
#define parHWTrig1SignalEdge_ARG    ssGetSFcnParam(S, 20) // parHWTrig1SignalEdge
#define parHWTrig1LeadTime_ARG      ssGetSFcnParam(S, 21) // parHWTrig1LeadTIme


#define parHWTrig2Enable_ARG        ssGetSFcnParam(S, 22) // parHWTrig2Enable
#define parHWTrig2SignalEdge_ARG    ssGetSFcnParam(S, 23) // parHWTrig2SignalEdge
#define parHWTrig2LeadTime_ARG      ssGetSFcnParam(S, 24) // parHWTrig2LeadTime

//
#define parIRIGenable_ARG           ssGetSFcnParam(S, 25) // parIRIGenable
#define parIRIGexpression_ARG       ssGetSFcnParam(S, 26) // parIRIGexpression
#define parCFconfig_ARG             ssGetSFcnParam(S, 27) // parCFconfig

//
#define parTimeOffset_ARG           ssGetSFcnParam(S, 28) // parTimeOffset
#define parInitialTime_ARG          ssGetSFcnParam(S, 29) // parInitialTime
#define parRefEnable_1_ARG          ssGetSFcnParam(S, 30) // parRefEnable_1
#define parRefPrio_1_ARG            ssGetSFcnParam(S, 31) // parRefPrio_1
#define parRefTime_1_ARG            ssGetSFcnParam(S, 32) // parRefTime_1
#define parRef1PPS_1_ARG            ssGetSFcnParam(S, 33) // parRef1PPS_1
#define parRefEnable_2_ARG          ssGetSFcnParam(S, 34) // parRefEnable_2
#define parRefPrio_2_ARG            ssGetSFcnParam(S, 35) // parRefPrio_2
#define parRefTime_2_ARG            ssGetSFcnParam(S, 36) // parRefTime_2
#define parRef1PPS_2_ARG            ssGetSFcnParam(S, 37) // parRef1PPS_2
#define parRefEnable_3_ARG          ssGetSFcnParam(S, 38) // parRefEnable_3
#define parRefPrio_3_ARG            ssGetSFcnParam(S, 39) // parRefPrio_3
#define parRefTime_3_ARG            ssGetSFcnParam(S, 40) // parRefTime_3
#define parRef1PPS_3_ARG            ssGetSFcnParam(S, 41) // parRef1PPS_3
#define parRefEnable_4_ARG          ssGetSFcnParam(S, 42) // parRefEnable_4
#define parRefPrio_4_ARG            ssGetSFcnParam(S, 43) // parRefPrio_4
#define parRefTime_4_ARG            ssGetSFcnParam(S, 44) // parRefTime_4
#define parRef1PPS_4_ARG            ssGetSFcnParam(S, 45) // parRef1PPS_4
#define parRefEnable_5_ARG          ssGetSFcnParam(S, 46) // parRefEnable_5
#define parRefPrio_5_ARG            ssGetSFcnParam(S, 47) // parRefPrio_5
#define parRefTime_5_ARG            ssGetSFcnParam(S, 48) // parRefTime_5
#define parRef1PPS_5_ARG            ssGetSFcnParam(S, 49) // parRef1PPS_5
#define parRefEnable_6_ARG          ssGetSFcnParam(S, 50) // parRefEnable_6
#define parRefPrio_6_ARG            ssGetSFcnParam(S, 51) // parRefPrio_6
#define parRefTime_6_ARG            ssGetSFcnParam(S, 52) // parRefTime_6
#define parRef1PPS_6_ARG            ssGetSFcnParam(S, 53) // parRef1PPS_6
#define NUMBER_OF_ARGS                               (54)



/* Integer Work Vectors */
#define NO_I_WORKS              (0)

/* Real Work Vectors */
#define NO_R_WORKS              (0)

/* Pointer Work Vectors */
#define NO_P_WORKS              (0)



#ifndef MATLAB_MEX_FILE
static IO821_data_T IO821_Data;
static IO821_config_T IO821_Config;
static int erroneousOutputFlag = 1;



static void updateOutputPorts(SimStruct *S)
{
    int iPort = 0;
    bool* pOutPortBool;
    real_T* pOutPortReal;
    int* pOutPortInt;

    if(IO821_Config.showActiveRef)
    { 
        pOutPortInt = ssGetOutputPortSignal(S, iPort++);
       *pOutPortInt = IO821_Data.ActiveRef;
    }
    if(IO821_Config.showSyncState)
    {
            /*if(((IO821_Data.datenum - IO821_Config.InitialTime) < -1) || ((IO821_Data.datenum - IO821_Config.InitialTime) > 0.00002) && erroneousOutputFlag == 1) //Does not work when using IRIG as source
            {
            //SG_PRINTF(INFO, "Erroneous Datenum Output!\n");
            pOutPortBool = ssGetOutputPortSignal(S, iPort++);
            *pOutPortBool = 0;
            }
            else*/
            {
            erroneousOutputFlag = 0;
            //SG_PRINTF(INFO, "Correct Datenum Output!\n"); 
            pOutPortBool = ssGetOutputPortSignal(S, iPort++);
            *pOutPortBool = IO821_Data.SyncState;  
            }
    }
    if(IO821_Config.showHoldoverState)
    {
       pOutPortBool = ssGetOutputPortSignal(S, iPort++);
       *pOutPortBool = IO821_Data.HoldoverState;
    }  
    if(IO821_Config.showAlarmState)
    {
       pOutPortBool = ssGetOutputPortSignal(S, iPort++);
       *pOutPortBool = IO821_Data.AlarmState;
    }     
    if(IO821_Config.showTime)
    {
        if(IO821_Config.moduleTimeFormat == 1) //datenum output
        {
            pOutPortReal = ssGetOutputPortSignal(S, iPort++);
            *pOutPortReal = IO821_Data.datenum;
            pOutPortReal = ssGetOutputPortSignal(S, iPort++);
            *pOutPortReal = IO821_Data.subsec;
        }
        else //array output
        {
            pOutPortReal = ssGetOutputPortSignal(S, iPort++);
            memcpy(pOutPortReal,IO821_Data.moduleTime.ymdhmsArray,(6*sizeof(real_T)));
            pOutPortReal = ssGetOutputPortSignal(S, iPort++);
            *pOutPortReal = IO821_Data.moduleTime.uSecOfYear;
            //SG_PRINTF(INFO, "IO821_Data.moduleTime.uSecOfYear sent to outport! %f\n", (float)IO821_Data.moduleTime.uSecOfYear);
        }
        
    }
    if(IO821_Config.edgeDetectTimeFormat == 1) //datenum output
    {
        if(IO821_Config.gpi0EdgeDetectActive)
        {
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                *pOutPortReal = IO821_Data.gpi0Time.datenum;
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                *pOutPortReal = IO821_Data.gpi0Time.subsec;
        }
        if(IO821_Config.gpi1EdgeDetectActive)
        {
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                *pOutPortReal = IO821_Data.gpi1Time.datenum;
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                *pOutPortReal = IO821_Data.gpi1Time.subsec;
        }
    }
    else // array output
    {
        if(IO821_Config.gpi0EdgeDetectActive)
        {
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                memcpy(pOutPortReal,IO821_Data.gpi0Time.ymdhmsArray,(6*sizeof(real_T)));
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                *pOutPortReal = IO821_Data.gpi0Time.uSecOfYear;
        }
        if(IO821_Config.gpi1EdgeDetectActive)
        {
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                memcpy(pOutPortReal,IO821_Data.gpi1Time.ymdhmsArray,(6*sizeof(real_T)));
                pOutPortReal = ssGetOutputPortSignal(S, iPort++);
                *pOutPortReal = IO821_Data.gpi1Time.uSecOfYear;
        }
    }
               
}
#endif

static char msg[256];
int skipFirstExecution = 1;

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_t i;
    uint32_t ports;
    uint32_t iPort;
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n",NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for( i = 0 ; i < NUMBER_OF_ARGS ; i++ )
    {
        /* None of the parameters are tunable */
        ssSetSFcnParamTunable(S,i,0);
    }

    // count input ports
    ssSetNumInputPorts(S, 0);

    // count output ports
    ports = 0;
    if (mxGetPr(parShowActiveRef_ARG)[0])     { ports++; }
    if (mxGetPr(parShowSyncState_ARG)[0])     { ports++; }
    if (mxGetPr(parShowHoldoverState_ARG)[0]) { ports++; }
    if (mxGetPr(parShowAlarmState_ARG)[0])    { ports++; }
    if (mxGetPr(parShowTime_ARG)[0]) { ports++; ports++; } // 2 ports
    if (mxGetPr(par0EdgeDetection_ARG)[0]) { ports++; ports++; } // 2 ports
    if (mxGetPr(par1EdgeDetection_ARG)[0]) { ports++; ports++; } // 2 ports
    ssSetNumOutputPorts(S, ports);

    // configure output ports
    // for(iPort = 0; iPort < ports; iPort++)
    // {
    //     ssSetOutputPortWidth(S, iPort, 1);
    // }
    iPort = 0;
    if (mxGetPr(parShowActiveRef_ARG)[0])
    {
        ssSetOutputPortWidth(S, iPort, 1);
        ssSetOutputPortDataType(S,iPort,SS_UINT8);
        iPort++;
    }
    if (mxGetPr(parShowSyncState_ARG)[0])
    {
        ssSetOutputPortWidth(S, iPort, 1);
        ssSetOutputPortDataType(S,iPort,SS_BOOLEAN);
        iPort++;
    }
    if (mxGetPr(parShowHoldoverState_ARG)[0])
    {
        ssSetOutputPortWidth(S, iPort, 1);
        ssSetOutputPortDataType(S,iPort,SS_BOOLEAN);
        iPort++;
    }
    if (mxGetPr(parShowAlarmState_ARG)[0])
    {
        ssSetOutputPortWidth(S, iPort, 1);
        ssSetOutputPortDataType(S,iPort,SS_BOOLEAN);
        iPort++;
    }
    if (mxGetPr(parShowTime_ARG)[0])
    {
        if(1 == (uint8_t)mxGetPr(parTimeFormat_ARG)[0]) // datenum format
        {
            //Time datenum output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
            //Time subsec output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
        }
        else
        {
            //Time array output
            ssSetOutputPortWidth(S, iPort, 6);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
            //Time usec of year output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
        }
    }
    if(1 == (uint8_t)mxGetPr(parEdgeDetectionFormat_ARG)[0]) // datenum format
    {
        if (mxGetPr(par0EdgeDetection_ARG)[0])
        {
            //Time datenum output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
            //Time subsec output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
        }
        if (mxGetPr(par1EdgeDetection_ARG)[0])
        {
            //Time datenum output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
            //Time subsec output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
        }
    }
    else // array output
    {
        if (mxGetPr(par0EdgeDetection_ARG)[0])
        {
            //Time array output
            ssSetOutputPortWidth(S, iPort, 6);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
            //Time usec of year output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
        }
        if (mxGetPr(par1EdgeDetection_ARG)[0])
        {
            //Time array output
            ssSetOutputPortWidth(S, iPort, 6);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
            //Time usec of year output
            ssSetOutputPortWidth(S, iPort, 1);
            ssSetOutputPortDataType(S,iPort,SS_DOUBLE);
            iPort++;
        }
    }
    


    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);/* ASAP only in Setup block */
 }

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

static void sg_ModelLoad(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    sg_PCIDevice pciInfo;
    void* bar;
    int rc = 0;
    int bus, slot;
	int moduleId = 1;	//Only one IO821 per rttm is supported
    sg_mod_info *mod_info;
	
	// ------ redirect stdout to file -------------------
    /*FILE *log;
    char logFilePath[128];
    
    if(sg_getModelBaseDir(logFilePath, 128))
	{
		ssSetErrorStatus(S, pSgErrorStr);
		return;
	}
    strcat(logFilePath, "/stdoutLog.txt");
	SG_PRINTF(INFO, "Model Dir: %s\n", logFilePath);
    log = freopen(logFilePath, "a", stdout);*/
    // ---------------------------------------------------
    
    // Find card
    #ifndef DRY_RUN
    if ((int)mxGetPr(SLOT_ARG)[0]<0)
    {
        if (sg_findPciDevice(&pciInfo, DEVNAME, VENDORID, DEVICEID, SG_NO_SUB, SG_NO_SUB,
                                moduleId, SG_NO_BUS_SLOT, SG_NO_BUS_SLOT))
        {
            sprintf(msg,"%s: board not present", DEVNAME);
            ssSetErrorStatus(S,msg);
            return;
        }
    }
    else
    {
        if (mxGetN(SLOT_ARG) == 1)
        {
            bus = 0;
            slot = (int)mxGetPr(SLOT_ARG)[0];
        }
        else
        {
            bus = (int)mxGetPr(SLOT_ARG)[0];
            slot = (int)mxGetPr(SLOT_ARG)[1];
        }
        if (sg_findPciDevice(&pciInfo, DEVNAME, VENDORID, DEVICEID, SG_NO_SUB, SG_NO_SUB,
                                moduleId, bus, slot))
        {
            sprintf(msg,"%s (bus %d, slot %d): board not present",DEVNAME, bus, slot );
            ssSetErrorStatus(S,msg);
            return;
        }
    }
    bus  = pciInfo.bus;
    slot = pciInfo.slot;
    
    //sg_showPciDevice(&pciInfo);
	
	#else // DRY_RUN
    pciInfo.bus = 0;
    pciInfo.slot = 0;
    #endif
	
    bar = sg_mapMemory(&pciInfo, 0); // map Bar0

    //sg_showPciDevice(&pciInfo);

    // Check if another block has already registered for the same module
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO821, (uint32_t) moduleId);
    if (mod_info == NULL)
    {
        mod_info = sg_module_register(SG_MODULE_TYPE_IO821, (uint32_t)moduleId);
        mod_info->custom_data = bar;
    }
    else
    {
        //Module already registered
        SG_PRINTF(DEBUG,"Do not register %s module\n", DEVNAME);
        return;
    }

    //SG_PRINTF(INFO, "&IO821_Data = 0x%08X &IO821_Config = 0x%08X\n", &IO821_Data, &IO821_Config);
    SG_PRINTF(INFO, "%s: Initializing ...\n",DEVNAME);
    IO821_Config.PeriodicIntEnable      = (int)mxGetPr(parPeriodicIntEnable_ARG)[0];
    IO821_Config.NanoPeriod             = (int)mxGetPr(parNanoPeriod_ARG)[0];
    IO821_Config.PeriodicIntAlign       = (int)mxGetPr(parPeriodicIntAlign_ARG)[0];
    IO821_Config.showActiveRef          = (int)mxGetPr(parShowActiveRef_ARG)[0];
    IO821_Config.showSyncState          = (int)mxGetPr(parShowSyncState_ARG)[0];
    IO821_Config.showHoldoverState      = (int)mxGetPr(parShowHoldoverState_ARG)[0];
    IO821_Config.showAlarmState         = (int)mxGetPr(parShowAlarmState_ARG)[0];
    IO821_Config.showTime               = (int)mxGetPr(parShowTime_ARG)[0];
    IO821_Config.TimeOffset             = (int)mxGetPr(parTimeOffset_ARG)[0];  
    IO821_Config.TimeOffset             = IO821_Config.TimeOffset - 13; // compensate for popup list in mask: '-12'=1, '-11'=2 .. '+12'=25
    IO821_Config.TimeOffset             = IO821_Config.TimeOffset *3600; // must be set in seconds
    IO821_Config.InitialTime            = mxGetPr(parInitialTime_ARG)[0];
    IO821_Config.RefTab[0].enabled      = (uint8_t)mxGetPr(parRefEnable_1_ARG)[0];
    IO821_Config.RefTab[0].prio         = (uint8_t)mxGetPr(  parRefPrio_1_ARG)[0];
    IO821_Config.RefTab[0].time         = (uint8_t)mxGetPr(  parRefTime_1_ARG)[0];
    IO821_Config.RefTab[0].pps          = (uint8_t)mxGetPr(  parRef1PPS_1_ARG)[0];
    IO821_Config.RefTab[1].enabled      = (uint8_t)mxGetPr(parRefEnable_2_ARG)[0];
    IO821_Config.RefTab[1].prio         = (uint8_t)mxGetPr(  parRefPrio_2_ARG)[0];
    IO821_Config.RefTab[1].time         = (uint8_t)mxGetPr(  parRefTime_2_ARG)[0];
    IO821_Config.RefTab[1].pps          = (uint8_t)mxGetPr(  parRef1PPS_2_ARG)[0];
    IO821_Config.RefTab[2].enabled      = (uint8_t)mxGetPr(parRefEnable_3_ARG)[0];
    IO821_Config.RefTab[2].prio         = (uint8_t)mxGetPr(  parRefPrio_3_ARG)[0];
    IO821_Config.RefTab[2].time         = (uint8_t)mxGetPr(  parRefTime_3_ARG)[0];
    IO821_Config.RefTab[2].pps          = (uint8_t)mxGetPr(  parRef1PPS_3_ARG)[0];
    IO821_Config.RefTab[3].enabled      = (uint8_t)mxGetPr(parRefEnable_4_ARG)[0];
    IO821_Config.RefTab[3].prio         = (uint8_t)mxGetPr(  parRefPrio_4_ARG)[0];
    IO821_Config.RefTab[3].time         = (uint8_t)mxGetPr(  parRefTime_4_ARG)[0];
    IO821_Config.RefTab[3].pps          = (uint8_t)mxGetPr(  parRef1PPS_4_ARG)[0];
    IO821_Config.RefTab[4].enabled      = (uint8_t)mxGetPr(parRefEnable_5_ARG)[0];
    IO821_Config.RefTab[4].prio         = (uint8_t)mxGetPr(  parRefPrio_5_ARG)[0];
    IO821_Config.RefTab[4].time         = (uint8_t)mxGetPr(  parRefTime_5_ARG)[0];
    IO821_Config.RefTab[4].pps          = (uint8_t)mxGetPr(  parRef1PPS_5_ARG)[0];
    IO821_Config.RefTab[5].enabled      = (uint8_t)mxGetPr(parRefEnable_6_ARG)[0];
    IO821_Config.RefTab[5].prio         = (uint8_t)mxGetPr(  parRefPrio_6_ARG)[0];
    IO821_Config.RefTab[5].time         = (uint8_t)mxGetPr(  parRefTime_6_ARG)[0];
    IO821_Config.RefTab[5].pps          = (uint8_t)mxGetPr(  parRef1PPS_6_ARG)[0];
    IO821_Config.rt_entries             = NUM_REF_TAB_ENTRIES;
    //new in v2:
    IO821_Config.moduleTimeFormat       = (uint8_t)mxGetPr(parTimeFormat_ARG)[0];//1-datenum; 2-array
    IO821_Config.gpi0EdgeDetectActive   = (uint8_t)mxGetPr(par0EdgeDetection_ARG)[0];//0-inactive; 1-active
    IO821_Config.gpi0SignalEdgeFormat   = (uint8_t)mxGetPr(par0SignalEdge_ARG)[0];//1-rising edge; 2-falling edge
    IO821_Config.gpi1EdgeDetectActive   = (uint8_t)mxGetPr(par1EdgeDetection_ARG)[0];//0-inactive; 1-active
    IO821_Config.gpi1SignalEdgeFormat   = (uint8_t)mxGetPr(par1SignalEdge_ARG)[0];//1-rising edge; 2-falling edge
    IO821_Config.edgeDetectTimeFormat   = (uint8_t)mxGetPr(parEdgeDetectionFormat_ARG)[0];//1-datenum; 2-array
    IO821_Config.dt1                    = (int)mxGetPr(parLeadTime1_ARG)[0];//Lead Time until output enable
    IO821_Config.dt2                    = (int)mxGetPr(parLeadTime2_ARG)[0];//Lead Time until output activation
    IO821_Config.dutyCycle              = (uint8_t)mxGetPr(parIntDutyCycle_ARG)[0];//Periodic Int duty cycle
    IO821_Config.irigEnable             = (int)mxGetPr(parIRIGenable_ARG)[0];
    IO821_Config.irigExpression         = (int)mxGetPr(parIRIGexpression_ARG)[0];
    IO821_Config.irigCfConfig           = (int)mxGetPr(parCFconfig_ARG)[0];
        
    IO821_Config.hwTrig1Enable          = (int)mxGetPr(parHWTrig1Enable_ARG)[0];      //HW Trigger 1 enabled
    IO821_Config.hwTrig1LeadTime        = (uint64_t)mxGetPr(parHWTrig1LeadTime_ARG)[0];    //HW Trigger 1 Lead Time
    IO821_Config.hwTrig1SignalEdge      = (int)mxGetPr(parHWTrig1SignalEdge_ARG)[0];  //HW Trigger 1 Signal Edge
    IO821_Config.hwTrig2Enable          = (int)mxGetPr(parHWTrig2Enable_ARG)[0];      //HW Trigger 2 enabled
    IO821_Config.hwTrig2LeadTime        = (uint64_t)mxGetPr(parHWTrig2LeadTime_ARG)[0];    //HW Trigger 2 Lead Time
    IO821_Config.hwTrig2SignalEdge      = (int)mxGetPr(parHWTrig2SignalEdge_ARG)[0];  //HW Trigger 2 Signal Edge

    //when building with the makefile, the following function call causes the target machine to freeze. Investigate! :)
    // for(int i=0; i<6; i++)
    // {
    //     SG_PRINTF(INFO, "init IO821_Config\n");
    //     SG_PRINTF(INFO, "IO821_Data.moduleTime.ymdhmsArray[%d] : %d\n",i, (int)IO821_Data.moduleTime.ymdhmsArray[i]);
    // 

    rc = IO821_mdlStart_init(bar, &IO821_Data, &IO821_Config);
    if(rc != 0)
    {
        SG_PRINTF(INFO, "failed\n");
        sprintf(msg,"%s (bus %d, slot %d): Init returned %i",DEVNAME, bus, slot, rc);
        ssSetErrorStatus(S,msg);
        return;
    }

    SG_PRINTF(INFO, " ok\n");

    // SG_PRINTF(INFO, "New params values in source file:\n");
    //SG_PRINTF(INFO, "IO821_Config.hwTrig1Enable: %d\n",IO821_Config.hwTrig1Enable);
    //SG_PRINTF(INFO, "IO821_Config.hwTrig1LeadTime: %lu\n",IO821_Config.hwTrig1LeadTime);
    // SG_PRINTF(INFO, "IO821_Config.hwTrig1SignalEdge: %d\n",IO821_Config.hwTrig1SignalEdge);
    
    //SG_PRINTF(INFO, "IO821_Config.hwTrig2Enable: %d\n",IO821_Config.hwTrig2Enable);
    //SG_PRINTF(INFO, "IO821_Config.hwTrig2LeadTime: %lu\n",IO821_Config.hwTrig2LeadTime);
    // SG_PRINTF(INFO, "IO821_Config.hwTrig2SignalEdge: %d\n",IO821_Config.hwTrig2SignalEdge);
    // // SG_PRINTF(INFO, "IO821_Config.gpi0EdgeDetectActive: %d\n",IO821_Config.gpi0EdgeDetectActive);
    // SG_PRINTF(INFO, "IO821_Config.gpi0SignalEdgeFormat: %d\n",IO821_Config.gpi0SignalEdgeFormat);
    // SG_PRINTF(INFO, "IO821_Config.gpi1EdgeDetectActive: %d\n",IO821_Config.gpi1EdgeDetectActive);
    // SG_PRINTF(INFO, "IO821_Config.gpi1SignalEdgeFormat: %d\n",IO821_Config.gpi1SignalEdgeFormat);
    // SG_PRINTF(INFO, "IO821_Config.edgeDetectTimeFormat: %d\n",IO821_Config.edgeDetectTimeFormat);
    // SG_PRINTF(INFO, "IO821_Config.dt1: %d\n",IO821_Config.dt1);
    // SG_PRINTF(INFO, "IO821_Config.dt2: %d\n",IO821_Config.dt2);
    //SG_PRINTF(INFO, "IO821_Config.NanoPeriod: %d\n",IO821_Config.NanoPeriod);
        
#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    void* bar;
    sg_PCIDevice pciInfo;
    int bus, slot;
    int moduleId = 1;	//Only one IO821 per rttm is supported
    
    // Find card
    #ifndef DRY_RUN
    if ((int)mxGetPr(SLOT_ARG)[0]<0)
    {
        if (sg_findPciDevice(&pciInfo, DEVNAME, VENDORID, DEVICEID, SG_NO_SUB, SG_NO_SUB,
                                moduleId, SG_NO_BUS_SLOT, SG_NO_BUS_SLOT))
        {
            sprintf(msg,"%s: board not present", DEVNAME);
            ssSetErrorStatus(S,msg);
            return;
        }
    }
    else
    {
        if (mxGetN(SLOT_ARG) == 1)
        {
            bus = 0;
            slot = (int)mxGetPr(SLOT_ARG)[0];
        }
        else
        {
            bus = (int)mxGetPr(SLOT_ARG)[0];
            slot = (int)mxGetPr(SLOT_ARG)[1];
        }
        if (sg_findPciDevice(&pciInfo, DEVNAME, VENDORID, DEVICEID, SG_NO_SUB, SG_NO_SUB,
                                moduleId, bus, slot))
        {
            sprintf(msg,"%s (bus %d, slot %d): board not present",DEVNAME, bus, slot );
            ssSetErrorStatus(S,msg);
            return;
        }
    }
    bus  = pciInfo.bus;
    slot = pciInfo.slot;
    
    //sg_showPciDevice(&pciInfo);
	
	#else // DRY_RUN
    pciInfo.bus = 0;
    pciInfo.slot = 0;
    #endif
	
    //Retrieve data from module registry
    bar = sg_module_get_custom_data(SG_MODULE_TYPE_IO821, (uint32_t)moduleId);
    if (bar == NULL)
    {
        ssSetErrorStatus(S, "Timeref: Failed to retrieve module from registry in ModelStart\n");
        return;
    }
    
    // for(int i=0; i<6; i++)
    // {
    //     SG_PRINTF(INFO, "mdlStart_start IO821_Data\n");
    //     SG_PRINTF(INFO, "IO821_Data.moduleTime.ymdhmsArray[%d] : %d\n",i, (int)IO821_Data.moduleTime.ymdhmsArray[i]);
    // }

    updateOutputPorts(S);
        
    IO821_mdlStart_start(bar);
    skipFirstExecution = 1;
    
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    void* bar;
    uint32_t moduleId = 1;	//Only one IO821 per rttm is supported

    //Retrieve data from module registry
    bar = sg_module_get_custom_data(SG_MODULE_TYPE_IO821, moduleId);
    if (bar == NULL)
    {
        ssSetErrorStatus(S, "Timeref: Failed to retrieve module from registry in ModelStep\n");
        return;
    }
    
    if(skipFirstExecution)
    {   
        skipFirstExecution = 0;
        return;
    }
        // for(int i=0; i<6; i++)
        // {
        //     SG_PRINTF(INFO, "IO821_Data.moduleTime.ymdhmsArray[%d] : %d\n",i, (int)IO821_Data.moduleTime.ymdhmsArray[i]);
        // }
        // SG_PRINTF(INFO, "IO821_Data.moduleTime.usec: %f\n", IO821_Data.moduleTime.uSecOfYear);
    IO821_mdlOutputs(bar);
    updateOutputPorts(S);

#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    void* bar;
    uint32_t moduleId = 1;	//Only one IO821 per rttm is supported

    //Retrieve data from module registry
    bar = sg_module_get_custom_data(SG_MODULE_TYPE_IO821, moduleId);
    if (bar == NULL)
    {
        ssSetErrorStatus(S, "Timeref: Failed to retrieve module from registry in ModelStop\n");
        return;
    }

    IO821_mdlTerminate_end(bar);
    erroneousOutputFlag = 1;
    memset(IO821_Data.gpi0Time.ymdhmsArray, 0, sizeof(IO821_Data.gpi0Time.ymdhmsArray));
    IO821_Data.gpi0Time.uSecOfYear = 0;
    memset(IO821_Data.gpi1Time.ymdhmsArray, 0, sizeof(IO821_Data.gpi1Time.ymdhmsArray));
    IO821_Data.gpi1Time.uSecOfYear = 0;

    IO821_Data.gpi0Time.datenum = 0;
    IO821_Data.gpi0Time.subsec = 0;
    IO821_Data.gpi1Time.datenum = 0;
    IO821_Data.gpi1Time.subsec = 0;

    updateOutputPorts(S);

#endif
}

static void sg_ModelExit(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    uint32_t moduleId = 1;	//Only one IO821 per rttm is supported

    sg_module_unregister(SG_MODULE_TYPE_IO821, moduleId);

#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue



