#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_zmi4104_vmestatus_s

#include 	<stddef.h>
#include 	<stdlib.h>

#include 	"simstruc.h" 

#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>

#include    "xpcimports.h"
#include    "sg_vme_zmi4104.h"

#endif

/* Input Arguments */

#define NUMBER_OF_ARGS          (2)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define SAMPLETIME_ARG          ssGetSFcnParam(S,1)

#define NO_I_WORKS              (1)
#define NODE_IO_ADDR_I_WORKS    (0)

#define NO_R_WORKS              (0)

#define NO_P_WORKS              (0)

char msg[256];
 
/* Initialize Sizes ******************************************************/
static void mdlInitializeSizes(SimStruct *S)
{
    char msg[256];
    int32_T i;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
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

    
    
    ssSetNumInputPorts(S, 0);
    
    ssSetNumOutputPorts(S, 1);
    
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_UINT8);
        
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
    xpcPCIDevice pciinfo;
    
    BAR1TYPE * nodeio_bar;
    
    // Check PCI slot
    if ((int_T)mxGetPr(SLOT_ARG)[0]<0) 
    {
        xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, XPC_NO_BUS_SLOT, XPC_NO_BUS_SLOT, &pciinfo);
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
        
        xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, bus, slot, &pciinfo);
    }
    
    // Physical / Virtual BAR addresses assignment 
    pciinfo.VirtAddress[1] = (uint32_T*)xpcReserveMemoryRegion((uint32_T*)pciinfo.BaseAddress[1],
                                                                pciinfo.Length[1], 
                                                                XPC_RT_PG_USERREADWRITE);
    
    nodeio_bar = (BAR1TYPE*) (pciinfo.VirtAddress[1] & 0xFFFFFFF0);                 // BAR1 (CSR)
    
    ssSetIWorkValue(S, NODE_IO_ADDR_I_WORKS, (int_T)nodeio_bar);
        
#endif
}

/* mdlOutput *************************************************************/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    
    BAR1TYPE * nodeio_bar;
    uint8_T *ptOutPort = ssGetOutputPortSignal(S, 0);      // Status Register 0
        

    nodeio_bar = (BAR1TYPE*) ssGetIWorkValue(S, NODE_IO_ADDR_I_WORKS);       
    
    ptOutPort[0] = VmeBusStatus(S, nodeio_bar);
    
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


