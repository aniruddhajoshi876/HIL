#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO812_initaxissync_s

#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdbool.h>

#include 	"simstruc.h" 


#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef     MATLAB_MEX_FILE
#include    <windows.h>

#include    "sg_common.h"
#include    "sg_vme_IO812.h"
#include "sg_callback_legacy.h"

#endif

/* Input Arguments */

#define NUMBER_OF_ARGS          (11)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define SAMPLETIME_ARG          ssGetSFcnParam(S,1)
#define BOARD_NUMBER            ssGetSFcnParam(S,2)
#define AX1_FILTERKP_ARG        ssGetSFcnParam(S,3)
#define AX1_FILTERKV_ARG        ssGetSFcnParam(S,4)
#define AX2_FILTERKP_ARG        ssGetSFcnParam(S,5)
#define AX2_FILTERKV_ARG        ssGetSFcnParam(S,6)
#define AX3_FILTERKP_ARG        ssGetSFcnParam(S,7)
#define AX3_FILTERKV_ARG        ssGetSFcnParam(S,8)
#define AX4_FILTERKP_ARG        ssGetSFcnParam(S,9)
#define AX4_FILTERKV_ARG        ssGetSFcnParam(S,10)


#define NO_I_WORKS              (0)

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

    
    
    ssSetNumInputPorts(S, 5);
    
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous( S, 0, 1 );
    ssSetInputPortWidth(S, 0, 4);   // because of the 4 registers (4 axes)
    ssSetInputPortDataType(S, 0, SS_UINT32);
    
    for (i = 1 ; i < 5 ; i++) // 4x reset port (1x for each axis)
    {
        ssSetInputPortDirectFeedThrough(S, i, 1);
        ssSetInputPortRequiredContiguous( S, i, 1 );
        ssSetInputPortWidth(S, i, 1);
        ssSetInputPortDataType(S, i, SS_DOUBLE);
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

    int8_T kp_id, kv_id;
    int8_T board_number;
    
    const uint32_T *ptInputPort1 = ssGetInputPortSignal(S, 0);
    
    const real_T *ptInputPort2_Rst1 = ssGetInputPortSignal(S, 1);
    const real_T *ptInputPort3_Rst2 = ssGetInputPortSignal(S, 2);
    const real_T *ptInputPort4_Rst3 = ssGetInputPortSignal(S, 3);
    const real_T *ptInputPort5_Rst4 = ssGetInputPortSignal(S, 4);

    volatile uint32_T *ptAxis1, *ptAxis2, *ptAxis3, *ptAxis4;
    
    board_number = (int32_T)mxGetPr(BOARD_NUMBER)[0];
                        
    if (sg_isModelInit() == 0)
    {               
        ptAxis1 = (uint32_T*) ptInputPort1[0];
        ptAxis2 = (uint32_T*) ptInputPort1[1];
        ptAxis3 = (uint32_T*) ptInputPort1[2];
        ptAxis4 = (uint32_T*) ptInputPort1[3];
             
        /* EEPROM Test ***************************************************/
        printf("EEPROM read test (value should be 50): %i \n",VmeZmiEepromRead(ptAxis3, 1));   
        
        /* Initializations **********************************/
        
        if (ptInputPort2_Rst1[0] >= 1)     // Axis 1
        {
            //VmeZmiWaitingAxis(S, ptAxis1, 1, msg);
            
            VmeZmiAxisSyncInit(ptAxis1, 1, board_number);

            kp_id = (int8_T)mxGetPr(AX1_FILTERKP_ARG)[0];
            kv_id = (int8_T)mxGetPr(AX1_FILTERKV_ARG)[0];

            VmeZmiSetFilter(ptAxis1, kp_id-1, kv_id-1); 

            VmeZmiReset(ptAxis1);
            printf("Reset Axis 1\n");
        }
        if (ptInputPort3_Rst2[0] >= 1)
        {
            //VmeZmiWaitingAxis(S, ptAxis2, 2, msg);
            
            VmeZmiAxisSyncInit(ptAxis2, 2, board_number);

            kp_id = (int8_T)mxGetPr(AX2_FILTERKP_ARG)[0];
            kv_id = (int8_T)mxGetPr(AX2_FILTERKV_ARG)[0];

            VmeZmiSetFilter(ptAxis2, kp_id-1, kv_id-1);

            VmeZmiReset(ptAxis2);
            printf("Reset Axis 2\n");
        }
        if (ptInputPort4_Rst3[0] >= 1)
        {
            // VmeZmiWaitingAxis(S, ptAxis3, 3, msg);
            
            VmeZmiAxisSyncInit(ptAxis3, 3, board_number);

            kp_id = (int8_T)mxGetPr(AX3_FILTERKP_ARG)[0];
            kv_id = (int8_T)mxGetPr(AX3_FILTERKV_ARG)[0];

            VmeZmiSetFilter(ptAxis3, kp_id-1, kv_id-1);

            VmeZmiReset(ptAxis3);
            printf("Reset Axis 3\n");
        }
        if (ptInputPort5_Rst4[0] >= 1)
        {
            //VmeZmiWaitingAxis(S, ptAxis4, 4, msg);
            
            VmeZmiAxisSyncInit(ptAxis4, 4, board_number);
            kp_id = (int8_T)mxGetPr(AX4_FILTERKP_ARG)[0];
            kv_id = (int8_T)mxGetPr(AX4_FILTERKV_ARG)[0];

            VmeZmiSetFilter(ptAxis4, kp_id-1, kv_id-1);

            VmeZmiReset(ptAxis4);
            printf("Reset Axis 4\n");
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


