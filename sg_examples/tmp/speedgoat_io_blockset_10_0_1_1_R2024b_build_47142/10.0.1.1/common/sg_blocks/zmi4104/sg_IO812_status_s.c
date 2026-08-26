#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO812_status_s

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
#include    "sg_vme_io812.h"
#include "sg_callback_legacy.h"

#endif

/* Input Arguments */

#define NUMBER_OF_ARGS          (4)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define SAMPLETIME_ARG          ssGetSFcnParam(S,1)
#define ZMI4104ID_ARG           ssGetSFcnParam(S,2)
#define AXIS_ARG                ssGetSFcnParam(S,3)

#define NO_I_WORKS              (1)
#define AXIS_ADDR_I_IND         (0)

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
    
    ssSetNumInputPorts(S, 0);
    
    ssSetNumOutputPorts(S, 1); 
    ssSetOutputPortWidth(S, 0, 20); // 20 errors
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
    sg_PCIDevice pciinfo;
    
 

   

    
    if (sg_isModelInit() == 0)
    {
    
    volatile uint32_T *bar2;
    uintptr_t bar2ptr;
    volatile uint32_T *ptAxis1, *ptAxis2, *ptAxis3, *ptAxis4;
    
    // Check PCI slot
    if ((int_T)mxGetPr(SLOT_ARG)[0]<0) 
    {
        if(sg_findPciDevice(&pciinfo, DEVNAME, VENDORID, DEVICEID, SUBVENDORID,
                SUBDEVICEID, 1, 0, -1))
        {
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
 
    bar2 = (volatile uint32_T*) ((uintptr_t)bar2ptr);                   // BAR2 PCI MEM Space    
    

    
    if ((uint_T)mxGetPr(ZMI4104ID_ARG)[0] == 1)
    {
        ptAxis1 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS1];
        ptAxis2 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS2];
        ptAxis3 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS3];
        ptAxis4 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS4];
    }
    else if ((uint_T)mxGetPr(ZMI4104ID_ARG)[0] == 2)
    {
        ptAxis1 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS1];
        ptAxis2 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS2];
        ptAxis3 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS3];
        ptAxis4 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS4];
    }
        
            dbv_printf("Remote Memory address ptAxis1: 0x%x \n",ptAxis1);
            dbv_printf("Remote Memory address ptAxis2: 0x%x \n",ptAxis2);
            dbv_printf("Remote Memory address ptAxis3: 0x%x \n",ptAxis3);
            dbv_printf("Remote Memory address ptAxis4: 0x%x \n",ptAxis4);
            
            
           
            dbv_printf("Remote Memory address ptAxis1[0x00]: 0x%x \n",ptAxis1[0x00]);   // Answers 0xB******* | 0x00000001, e.g. 0xB0A19001s
            dbv_printf("Remote Memory address ptAxis2[0x00]: 0x%x \n",ptAxis2[0x00]);   // Answers 0xB******* | 0x00000001   ,ptAxis2[0x20]
            dbv_printf("Remote Memory address ptAxis3[0x00]: 0x%x \n",ptAxis3[0x00]);   // Answers 0xB******* | 0x00000001
            dbv_printf("Remote Memory address ptAxis4[0x00]: 0x%x \n",ptAxis4[0x00]);   // Answers 0xB******* | 0x00000001


   

    switch  ( (uint_T)mxGetPr(AXIS_ARG)[0] )
    {
        case 1: ssSetIWorkValue(S, AXIS_ADDR_I_IND, (int_T)ptAxis1);
                break;
                
        case 2: ssSetIWorkValue(S, AXIS_ADDR_I_IND, (int_T)ptAxis2);
                break;
                
        case 3: ssSetIWorkValue(S, AXIS_ADDR_I_IND, (int_T)ptAxis3);
                break;
                
        case 4: ssSetIWorkValue(S, AXIS_ADDR_I_IND, (int_T)ptAxis4);
                break;
    }
    }
        
#endif
}

/* mdlOutput *************************************************************/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    
    uint8_T *ptOutPort_Error = ssGetOutputPortSignal(S, 0);
    uint8_T i;
    uint32_T status_reg = 0x0000;
    uint32_T status_reg_inv = 0x0000;
   
    ZMI4104TYPE *ptZmiRegs;

    ptZmiRegs = (ZMI4104TYPE *) ssGetIWorkValue(S, AXIS_ADDR_I_IND);       
   
	
    dbv_printf("status: before zmiRead32 0x%x\n", ptZmiRegs);	
    status_reg = zmiRead32(ptZmiRegs, ZMI_VME_ERROR_STATUS0); // & (~0xFFF00000);
	dbv_printf("status: after zmiRead32\n");
    dbv_printf("status_reg = 0x%x \n", status_reg);
   

  
     status_reg_inv =  status_reg; //(status_reg << 16) | (status_reg >> 16);    

    for (i = 0; i < 20 ; i++)
    {
        ptOutPort_Error[i] = (status_reg_inv >> i) & 1;
    }
    
    /* Scope 1 (signal 1-10)
     * 'Power Error: %1.0f,Write Error: %1.0f,Reference Signal Missing: %1.0f,Reference PLL Error: %1.0f,Reset Complete: %1.0f,Reset Failure: %1.0f,FPGA Sync Error: %1.0f,OverTempError: %1.0f,Measure Signal Missing: %1.0f,Measure Signal Saturated: %1.0f'
     *
     * Scope 2 (signal 11-20)
     * 'SSI Max Limit: %1.0f,Measure Signal Dropout: %1.0f,Measure Signal Glitch: %1.0f,Acceleration Error: %1.0f,Phase Noise Error: %1.0f,CEC Error: %1.0f,Velocity Error: %1.0f,User Velocity Error: %1.0f,37-bit Position Overflow: %1.0f,VME 32 bit Position Overflow: %1.0f'
    */
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


