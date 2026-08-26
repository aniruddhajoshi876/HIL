#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO812_readAllPosAndTimeSync_s

#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdbool.h>
#include    <math.h>

#include 	"simstruc.h" 


#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>

#include    "sg_common.h"
#include    "sg_vme_IO812.h"
#include "sg_callback_legacy.h"

#endif

/* Input Arguments */
#define NUMBER_OF_ARGS          (18)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define SAMPLETIME_ARG          ssGetSFcnParam(S,1)
#define ACTAXIS1                ssGetSFcnParam(S,2)
#define ACTAXIS2                ssGetSFcnParam(S,3)
#define ACTAXIS3                ssGetSFcnParam(S,4)
#define ACTAXIS4                ssGetSFcnParam(S,5)
#define ACTAXIS5                ssGetSFcnParam(S,6)
#define ACTAXIS6                ssGetSFcnParam(S,7)
#define ACTAXIS7                ssGetSFcnParam(S,8)
#define ACTAXIS8                ssGetSFcnParam(S,9)
#define ACTTIME1                ssGetSFcnParam(S,10)
#define ACTTIME2                ssGetSFcnParam(S,11)
#define ACTTIME3                ssGetSFcnParam(S,12)
#define ACTTIME4                ssGetSFcnParam(S,13)
#define ACTTIME5                ssGetSFcnParam(S,14)
#define ACTTIME6                ssGetSFcnParam(S,15)
#define ACTTIME7                ssGetSFcnParam(S,16)
#define ACTTIME8                ssGetSFcnParam(S,17)

#define NO_I_WORKS              (8)

#define NO_R_WORKS              (0)

#define NO_P_WORKS              (0)

char msg[256];
 
/* Initialize Sizes ******************************************************/
static void mdlInitializeSizes(SimStruct *S)
{
    char msg[256];
    uint8_T i, cnt;
  
    uint8_T act_axis1      = (uint8_T)mxGetPr(ACTAXIS1)[0];
    uint8_T act_axis2      = (uint8_T)mxGetPr(ACTAXIS2)[0];
    uint8_T act_axis3      = (uint8_T)mxGetPr(ACTAXIS3)[0];
    uint8_T act_axis4      = (uint8_T)mxGetPr(ACTAXIS4)[0];
    uint8_T act_axis5      = (uint8_T)mxGetPr(ACTAXIS5)[0];
    uint8_T act_axis6      = (uint8_T)mxGetPr(ACTAXIS6)[0];
    uint8_T act_axis7      = (uint8_T)mxGetPr(ACTAXIS7)[0];
    uint8_T act_axis8      = (uint8_T)mxGetPr(ACTAXIS8)[0];
    uint8_T act_time1      = (uint8_T)mxGetPr(ACTTIME1)[0];
    uint8_T act_time2      = (uint8_T)mxGetPr(ACTTIME2)[0];
    uint8_T act_time3      = (uint8_T)mxGetPr(ACTTIME3)[0];
    uint8_T act_time4      = (uint8_T)mxGetPr(ACTTIME4)[0];
    uint8_T act_time5      = (uint8_T)mxGetPr(ACTTIME5)[0];
    uint8_T act_time6      = (uint8_T)mxGetPr(ACTTIME6)[0];
    uint8_T act_time7      = (uint8_T)mxGetPr(ACTTIME7)[0];
    uint8_T act_time8      = (uint8_T)mxGetPr(ACTTIME8)[0];

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n", NUMBER_OF_ARGS);
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
        ssSetSFcnParamTunable(S,i,0);  /* None of the parameters are tunable */
    }

    ssSetNumInputPorts(S, 1);
    
    for (i = 0 ; i < 1 ; i++)
    {
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous( S, i, 1 );
        ssSetInputPortWidth(S, i, 1); 
        ssSetInputPortDataType(S, i, SS_UINT16);
    }
    
	cnt = act_axis1 + act_axis2 + act_axis3 + act_axis4 + act_axis5 + act_axis6 + act_axis7 + act_axis8 + act_time1 + act_time2 + act_time3 + act_time4 + act_time5 + act_time6 + act_time7 + act_time8;
    ssSetNumOutputPorts(S, cnt); 
       
	for (i = 0; i < cnt; i++)
    {         
        ssSetOutputPortWidth(S, i, 1);
        ssSetOutputPortDataType(S, i, SS_DOUBLE);
    }
     
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);
    
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

/* Initialize Sample Times ***********************************************/
static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLETIME_ARG)[0]==-1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLETIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

/* mdlStart **************************************************************/
#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
   
    volatile uint32_T *bar2;
    uintptr_t bar2ptr;

    sg_PCIDevice pciinfo;
 
    // Check PCI slot
    if ((int_T)mxGetPr(SLOT_ARG)[0]<0) 
    {
   if (sg_findPciDevice(&pciinfo, DEVNAME, VENDORID, DEVICEID, SUBVENDORID,
                SUBDEVICEID, 1, 0, -1))        {
            ssSetErrorStatus(S, pSgErrorStr);
            return;
        }
    } 
    else 
    {
        uint16_T bus, slot;

        if (mxGetN(SLOT_ARG) == 1) 
        {
            bus = 0;
            slot = (uint16_T)mxGetPr(SLOT_ARG)[0];
        } 
        else 
        {
            bus = (uint16_T)mxGetPr(SLOT_ARG)[0];
            slot = (uint16_T)mxGetPr(SLOT_ARG)[1];
        }
        
    if (sg_findPciDevice(&pciinfo, DEVNAME, VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, 1, bus, slot))
        {
            ssSetErrorStatus(S, pSgErrorStr);
            return;
        }
    }
    
    // Physical / Virtual BAR addresses assignment     
    bar2ptr = (uintptr_t)sg_mapMemory(&pciinfo, 2);
    bar2 = (volatile uint32_T*) ((uintptr_t)bar2ptr);    // BAR2 PCI MEM Space     

	ssSetIWorkValue(S, 0, (int_T)&bar2[VME_REMOTE_ZMI_BOARD1_AXIS1]);
	ssSetIWorkValue(S, 1, (int_T)&bar2[VME_REMOTE_ZMI_BOARD1_AXIS2]);
	ssSetIWorkValue(S, 2, (int_T)&bar2[VME_REMOTE_ZMI_BOARD1_AXIS3]);
	ssSetIWorkValue(S, 3, (int_T)&bar2[VME_REMOTE_ZMI_BOARD1_AXIS4]);
	ssSetIWorkValue(S, 4, (int_T)&bar2[VME_REMOTE_ZMI_BOARD2_AXIS1]);
	ssSetIWorkValue(S, 5, (int_T)&bar2[VME_REMOTE_ZMI_BOARD2_AXIS2]);
	ssSetIWorkValue(S, 6, (int_T)&bar2[VME_REMOTE_ZMI_BOARD2_AXIS3]);
	ssSetIWorkValue(S, 7, (int_T)&bar2[VME_REMOTE_ZMI_BOARD2_AXIS4]);
  
#endif
}

/* mdlOutput *************************************************************/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    uint8_T act_axis1      = (uint8_T)mxGetPr(ACTAXIS1)[0];
    uint8_T act_axis2      = (uint8_T)mxGetPr(ACTAXIS2)[0];
    uint8_T act_axis3      = (uint8_T)mxGetPr(ACTAXIS3)[0];
    uint8_T act_axis4      = (uint8_T)mxGetPr(ACTAXIS4)[0];
    uint8_T act_axis5      = (uint8_T)mxGetPr(ACTAXIS5)[0];
    uint8_T act_axis6      = (uint8_T)mxGetPr(ACTAXIS6)[0];
    uint8_T act_axis7      = (uint8_T)mxGetPr(ACTAXIS7)[0];
    uint8_T act_axis8      = (uint8_T)mxGetPr(ACTAXIS8)[0];
    uint8_T act_time1      = (uint8_T)mxGetPr(ACTTIME1)[0];
    uint8_T act_time2      = (uint8_T)mxGetPr(ACTTIME2)[0];
    uint8_T act_time3      = (uint8_T)mxGetPr(ACTTIME3)[0];
    uint8_T act_time4      = (uint8_T)mxGetPr(ACTTIME4)[0];
    uint8_T act_time5      = (uint8_T)mxGetPr(ACTTIME5)[0];
    uint8_T act_time6      = (uint8_T)mxGetPr(ACTTIME6)[0];
    uint8_T act_time7      = (uint8_T)mxGetPr(ACTTIME7)[0];
    uint8_T act_time8      = (uint8_T)mxGetPr(ACTTIME8)[0];
    
    uint8_T nPort = 0;
              
    uint16_T *ptInputPort_Enable = ssGetInputPortSignal(S, 0);
	
	if ( ptInputPort_Enable[0] >= 1 )
	{			 
		uint32_T lsbs[8];
		uint16_T exts[8];
		ZMI4104TYPE * baseAddresses[8];
		int i;
		int nPort = 0;
		real_T time;
		
		for (i = 0; i < 8; i++)
		{
			baseAddresses[i] = (ZMI4104TYPE *) ssGetIWorkValue(S, i);
		}
		
		// ZMI Konfiguration in VmeZmiAxisSyncInit Funktion
    /* Timing SCLK0 und Out Enable in Control Register 16 nur von Board 1, Achse 3*/
//    zmiWrite16(baseAddresses[0], ZMI_VME_CONTROL_REGISTER_16, 0x3C00); /*3c00 FineTiming 1.Karte Kanal 1 und 2*/
//    zmiWrite16(baseAddresses[2], ZMI_VME_CONTROL_REGISTER_16, 0x3E00); /*0x200 OutEnable + 3c00 FineTiming 1.Karte Kanal 3 und 4*/
//    zmiWrite16(baseAddresses[4], ZMI_VME_CONTROL_REGISTER_16, 0x3C00); /*3c00 FineTiming 2.Karte Kanal 1 und 2*/
//    zmiWrite16(baseAddresses[6], ZMI_VME_CONTROL_REGISTER_16, 0x3C00); /*3c00 FineTiming 2.Karte Kanal 3 und 4*/
    
    /* External Sample (SCLK0) in SCLK Command Register nur von Achse 3 auf 1 setzen*/
    zmiWrite16(baseAddresses[2], ZMI_VME_SCLK_COMMAND_REGISTER, 0x1);
		
    /*Positionsregister auslesen*/			
		for (i = 0; i < 8; i++)
		{
			VmeZmiReadPositionComponents(baseAddresses[i], &lsbs[i], &exts[i]);
		}
		
		if (act_axis1)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[0], lsbs[0]);			
			nPort++;
		}
    if (act_axis2)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[1], lsbs[1]);
			nPort++;
		}
    if (act_axis3)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[2], lsbs[2]);
			nPort++;
		}
    if (act_axis4)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[3], lsbs[3]);
			nPort++;
		}
    if (act_axis5)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[4], lsbs[4]);
			nPort++;
		}
    if (act_axis6)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[5], lsbs[5]);
			nPort++;
		}
    if (act_axis7)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[6], lsbs[6]);
			nPort++;
		}
    if (act_axis8)
		{
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = GetRealValue(exts[7], lsbs[7]);
			nPort++;
		}
		
		if (act_time1)
		{
			VmeZmiReadTime(baseAddresses[0], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time; 			
			nPort++;
		}
    if (act_time2)
		{
			VmeZmiReadTime(baseAddresses[1], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time;
			nPort++;
		}
    if (act_time3)
		{
			VmeZmiReadTime(baseAddresses[2], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time;
			nPort++;
		}
    if (act_time4)
		{
			VmeZmiReadTime(baseAddresses[3], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time;
			nPort++;
		}
    if (act_time5)
		{
			VmeZmiReadTime(baseAddresses[4], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time;
			nPort++;
		}
    if (act_time6)
		{
			VmeZmiReadTime(baseAddresses[5], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time;
			nPort++;
		}
    if (act_time7)
		{
			VmeZmiReadTime(baseAddresses[6], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time;
			nPort++;
		}
    if (act_time8)
		{
			VmeZmiReadTime(baseAddresses[7], &time);
			*((real_T*)ssGetOutputPortSignal(S, nPort)) = time;
			nPort++;
		}
	}
#endif
}

/* mdlTerminate **********************************************************/
static void mdlTerminate(SimStruct *S)
{   
#ifndef MATLAB_MEX_FILE
      
#endif    
}

#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif


