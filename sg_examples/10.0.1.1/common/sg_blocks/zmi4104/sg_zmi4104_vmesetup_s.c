#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_zmi4104_vmesetup_s

#include 	<stddef.h>
#include 	<stdlib.h>

#include 	"simstruc.h" 

#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>

#include    "xpcimports.h"
#include    "sg_vme_zmi4104.c"

#endif

/* Input Arguments */

#define NUMBER_OF_ARGS          (7)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define SAMPLETIME_ARG          ssGetSFcnParam(S,1)
#define MODULES_ARG             ssGetSFcnParam(S,2)
#define Z1_ADDRSW1_ARG          ssGetSFcnParam(S,3)
#define Z1_ADDRSW2_ARG          ssGetSFcnParam(S,4)
#define Z2_ADDRSW1_ARG          ssGetSFcnParam(S,5)
#define Z2_ADDRSW2_ARG          ssGetSFcnParam(S,6)

#define NO_I_WORKS              (3)
#define BASE_ADDR1_I_IND        (0)
#define BASE_ADDR2_I_IND        (1)
#define BASE_ADDR3_I_IND        (2)

#define NO_R_WORKS              (0)

#define NO_P_WORKS              (0)

char msg[256];
 
/* Initialize Sizes ******************************************************/
static void mdlInitializeSizes(SimStruct *S)
{
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
        /* None of the parameters are tunable */
        ssSetSFcnParamTunable(S,i,0);  
    }

    ssSetNumInputPorts(S, 0);
    
    ssSetNumOutputPorts(S, (int_T)mxGetPr(MODULES_ARG)[0]);
    for (i = 0 ; i < (int_T)mxGetPr(MODULES_ARG)[0] ; i++)
    {         
        ssSetOutputPortWidth(S, i, 4);
        ssSetOutputPortDataType(S, i, SS_UINT32);
    } 
    
        
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);
    
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
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
    volatile uint32_T * mappingreg_bar;
    volatile uint32_T *remotemem_bar;
    volatile uint32_T *ptAxis1, *ptAxis2, *ptAxis3, *ptAxis4;
    
    uint32_T *ptOutputPort1;
    uint32_T *ptOutputPort2;

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
    
    nodeio_bar = (BAR1TYPE*) (pciinfo.VirtAddress[1] & 0xFFFFFFF0);                 // BAR1 (CSR)
    mappingreg_bar = (volatile uint32_T*) (pciinfo.VirtAddress[2] & 0xFFFFFFF0);    // BAR2 (Mapping registers)
    remotemem_bar = (volatile uint32_T*) (pciinfo.VirtAddress[3] & 0xFFFFFFF0);     // BAR3 (Remote Memory Window)

    ssSetIWorkValue(S, BASE_ADDR1_I_IND, (int_T)nodeio_bar);
    ssSetIWorkValue(S, BASE_ADDR2_I_IND, (int_T)mappingreg_bar);
    ssSetIWorkValue(S, BASE_ADDR3_I_IND, (int_T)remotemem_bar);
    
//     xpcShowPCIDeviceInfo(&pciinfo);    
    
    if (xpcIsModelInit() == 0)
    {
        VmeBusInit(S, nodeio_bar, msg); // VME bus initialization
        xpcBusyWait(2);
        if (VmeBusInit(S, nodeio_bar, msg) > 0)
        {
            printf("%s: initialization failed\n", DEVNAME);
        }
        else
        {
            printf("%s: VME bus access done\n", DEVNAME);
        }
        
        if (VmeBusStatus(S, nodeio_bar) > 0)
        {
            printf("%s: VME bus not connected\n", DEVNAME);
            sprintf(msg,"%s: VME bus not connected\n", DEVNAME);
            ssSetErrorStatus(S,msg);
            return;
        }
        
        /* Map board 1*/
        VmeZmiMapping(1, mappingreg_bar,
                      (int_T)mxGetPr(Z1_ADDRSW1_ARG)[0],
                      (int_T)mxGetPr(Z1_ADDRSW2_ARG)[0]);
        
        if ((int_T)mxGetPr(MODULES_ARG)[0] == 2)
        {
            /* Map board 2*/
            VmeZmiMapping(2, mappingreg_bar,
                          (int_T)mxGetPr(Z2_ADDRSW1_ARG)[0],
                          (int_T)mxGetPr(Z2_ADDRSW2_ARG)[0]);
        }
               
        #ifdef SG_DEBUG
        {
//             uint8_T i; 
            printf("Remote memory [0x00] = 0x%08x \n", remotemem_bar[0x00]);

//             for (i = 0x00 ; i <= 0x0C00; i++)   // use 0x1800 for 16-bit based
//             {
//                 if (remotemem_bar[i] == 0xb0a19001)
//                     printf("found  at %i (0x%x) \n", i,i);
// 
//                 // Answers must be: 0x0000, 0x0800, 0x1000, 0x1800 (16-bit based)
//                 // Answers must be: 0x0000, 0x0400, 0x0800, 0x0C00 (32-bit based)
//             }
        }
        #endif

        /* One board only ************************************************/
        if ((int_T)mxGetPr(MODULES_ARG)[0] == 1)
        {
            /*Board 1*/
            ptAxis1 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS1];
            ptAxis2 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS2];
            ptAxis3 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS3];
            ptAxis4 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS4];
            
            #ifdef SG_DEBUG
            printf("Remote Memory address ptAxis1: 0x%x \n",ptAxis1);
            printf("Remote Memory address ptAxis2: 0x%x \n",ptAxis2);
            printf("Remote Memory address ptAxis3: 0x%x \n",ptAxis3);
            printf("Remote Memory address ptAxis4: 0x%x \n",ptAxis4);
            
            printf("Remote Memory address ptAxis1[0x00]: 0x%x \n",ptAxis1[0x00]);   // Answers 0xB******* | 0x00000001, e.g. 0xB0A19001
            printf("Remote Memory address ptAxis2[0x00]: 0x%x \n",ptAxis2[0x00]);   // Answers 0xB******* | 0x00000001
            printf("Remote Memory address ptAxis3[0x00]: 0x%x \n",ptAxis3[0x00]);   // Answers 0xB******* | 0x00000001
            printf("Remote Memory address ptAxis4[0x00]: 0x%x \n",ptAxis4[0x00]);   // Answers 0xB******* | 0x00000001
            #endif
                    
            ptOutputPort1 = ssGetOutputPortSignal(S, 0);

            ptOutputPort1[0] = (uint32_T)ptAxis1;
            ptOutputPort1[1] = (uint32_T)ptAxis2;
            ptOutputPort1[2] = (uint32_T)ptAxis3;
            ptOutputPort1[3] = (uint32_T)ptAxis4;
        }
        
        /* Two boards ****************************************************/
        else if ((int_T)mxGetPr(MODULES_ARG)[0] == 2)
        {
            /* Board 1 */
            ptAxis1 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS1];
            ptAxis2 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS2];
            ptAxis3 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS3];
            ptAxis4 = &remotemem_bar[VME_REMOTE_ZMI_BOARD1_AXIS4];
            
            ptOutputPort1 = ssGetOutputPortSignal(S, 0);

            ptOutputPort1[0] = (uint32_T)ptAxis1;
            ptOutputPort1[1] = (uint32_T)ptAxis2;
            ptOutputPort1[2] = (uint32_T)ptAxis3;
            ptOutputPort1[3] = (uint32_T)ptAxis4;

            /* Board 2*/
            ptAxis1 = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS1];
            ptAxis2 = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS2];
            ptAxis3 = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS3];
            ptAxis4 = &remotemem_bar[VME_REMOTE_ZMI_BOARD2_AXIS4];
            
            ptOutputPort2 = ssGetOutputPortSignal(S, 1);

            ptOutputPort2[0] = (uint32_T)ptAxis1;
            ptOutputPort2[1] = (uint32_T)ptAxis2;
            ptOutputPort2[2] = (uint32_T)ptAxis3;
            ptOutputPort2[3] = (uint32_T)ptAxis4;
        }
        
    }
        
#endif
}

/* mdlOutput *************************************************************/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    
    
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


