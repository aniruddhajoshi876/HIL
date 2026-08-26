#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_zmi4104_writereg_v2_s

#include 	<stddef.h>
#include 	<stdlib.h>

#include 	"simstruc.h" 

#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef     MATLAB_MEX_FILE
#include    <windows.h>

#include    "xpcimports.h"
#include    "sg_vme_zmi4104.h"

#endif

/* Input Arguments */

#define NUMBER_OF_ARGS          (2)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define SAMPLETIME_ARG          ssGetSFcnParam(S,1)
//#define ZMI4104ID_ARG           ssGetSFcnParam(S,2)
//#define AXIS_ARG                ssGetSFcnParam(S,3)
//#define PCIACCESS_ARG           ssGetSFcnParam(S,4)

#define INPORT_ENABLE           (0)
#define INPORT_ZMIID            (1)
#define INPORT_AXIS             (2)
#define INPORT_PCIACCESS        (3)
#define INPORT_OFFSET           (4)
#define INPORT_VALUE            (5)

#define NO_I_WORKS              (1)
#define REMOTE_ADDR_I_IND       (0)

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

    ssSetNumInputPorts(S, 6);
    
    for (i = 0 ; i < 6 ; i++)
    {
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous( S, i, 1 );
        ssSetInputPortWidth(S, i, 1); 
        
        ssSetInputPortDataType(S, i, SS_UINT32);
    }
    
    ssSetNumOutputPorts(S, 0);
        
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
    
    volatile ZMI4104TYPE *remotemem_bar;
     
    
    // Check PCI slot
    if ((int_T)mxGetPr(SLOT_ARG)[0]<0) 
    {
        if (xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, XPC_NO_BUS_SLOT, XPC_NO_BUS_SLOT, &pciinfo)) 
        {
            sprintf(msg,"%s: board not present", DEVNAME);
            ssSetErrorStatus(S,msg);
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
        
        if (xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, bus, slot, &pciinfo)) 
        {
            sprintf(msg,"%s (bus %d, slot %d): board not present",DEVNAME, bus, slot );
            ssSetErrorStatus(S,msg);
            return;
        }
    }
    
    // Physical / Virtual BAR addresses assignment 
    pciinfo.VirtAddress[1] = (uint32_T*)xpcReserveMemoryRegion((uint32_T*)pciinfo.BaseAddress[1],
                                                                pciinfo.Length[1], 
                                                                XPC_RT_PG_USERREADWRITE);
    
    pciinfo.VirtAddress[2] = (uint32_T*)xpcReserveMemoryRegion((uint32_T*)pciinfo.BaseAddress[2],
                                                                pciinfo.Length[1], 
                                                                XPC_RT_PG_USERREADWRITE);
    
    pciinfo.VirtAddress[3] = (uint32_T*)xpcReserveMemoryRegion((uint32_T*)pciinfo.BaseAddress[3],
                                                                pciinfo.Length[1], 
                                                                XPC_RT_PG_USERREADWRITE);

    remotemem_bar = (volatile uint32_T*) (pciinfo.VirtAddress[3] & 0xFFFFFFF0);     // BAR3 (Remote Memory Window)
    
    ssSetIWorkValue(S, REMOTE_ADDR_I_IND, remotemem_bar);
//     xpcShowPCIDeviceInfo(&pciinfo);   

     
#endif
}

/* mdlOutput *************************************************************/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    
    uint32_T *ptInputPort_Enable = ssGetInputPortSignal(S, INPORT_ENABLE);
    uint32_T *ptInputPort_Offset = ssGetInputPortSignal(S, INPORT_OFFSET);
    uint32_T *ptInputPort_Write = ssGetInputPortSignal(S, INPORT_VALUE);
    uint32_T *ptInputPort_PciAccess = ssGetInputPortSignal(S, INPORT_PCIACCESS);
    uint32_T *ptInputPort_ZmiId= ssGetInputPortSignal(S, INPORT_ZMIID);
    uint32_T *ptInputPort_Axis = ssGetInputPortSignal(S, INPORT_AXIS);
    
    volatile uint32_T *remotemem_bar = (uint32_T *) ssGetIWorkValue(S, REMOTE_ADDR_I_IND);
    ZMI4104TYPE *ptZmiRegs;
    
    if (ptInputPort_ZmiId[0] == 1)
    {
        switch  (ptInputPort_Axis[0])
        {
            case 1: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS1];
                    break;
            case 2: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS2];
                    break;
            case 3: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS3];
                    break;
            case 4: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS4];
                    break;
        }
    }
    else if (ptInputPort_ZmiId[0] == 2)
    {
        switch  (ptInputPort_Axis[0])
        {
            case 1: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS1];
                    break;
            case 2: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS2];
                    break;
            case 3: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS3];
                    break;
            case 4: ptZmiRegs = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS4];
                    break;
        }
    }

    if ( ptInputPort_Enable[0] >= 1 )
    {
        if (ptInputPort_PciAccess[0] == 0) // 16-bit write
            zmiWrite16(ptZmiRegs, ptInputPort_Offset[0], ptInputPort_Write[0]);
        
        else if (ptInputPort_PciAccess[0] == 1) // 32-bit write
            zmiWrite32(ptZmiRegs, ptInputPort_Offset[0], ptInputPort_Write[0]);
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


