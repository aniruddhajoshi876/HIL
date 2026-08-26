//  
/*
Adapted from condor1553init.c
Supports only the QPM-1553 (PMC) variant

 I/O module  Channels	Single/Multi-function
----------------------------------------------
 IO672-1-SF     1              single
 IO672-1-MF     1              multi
 IO672-2-SF     2              single
 IO672-2-MF     2              multi
 IO672-4-SF     4              single
 IO672-4-MF     4              multi

 */

// This block is for per-channel initialization for a bus controller

#define S_FUNCTION_LEVEL  2
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO672_setup_s

#include "sg_IO672.h"

#include "sg_callback.h"

#define NUM_ARGS           0

#define NUM_I_WORKS       (0)
#define NUM_R_WORKS       (0)

static char msg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    int i;

    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(msg, "%d input args expected, %d passed", 
            NUM_ARGS, ssGetSFcnParamsCount(S));
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if( !ssSetNumInputPorts(S, 0) ) return;

    if( !ssSetNumOutputPorts(S, 0) ) return;
    
    ssSetSimStateCompliance(S, HAS_NO_SIM_STATE);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, NUM_R_WORKS);
    ssSetNumIWork(S, NUM_I_WORKS);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUM_ARGS; i++)
        ssSetSFcnParamTunable(S, i, 0);

    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE );

}
 
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
}

#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct *S)
{

}

static void sg_ModelStart(SimStruct *S)
{

}

static void sg_ModelStep(SimStruct *S)
{

}

static void sg_ModelStop(SimStruct *S)
{

}
#endif

#include "sg_sfcn_glue.h"   // Code generation glue
