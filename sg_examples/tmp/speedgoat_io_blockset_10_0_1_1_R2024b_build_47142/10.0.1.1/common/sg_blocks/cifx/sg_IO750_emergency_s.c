#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO750_emergency_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#include "ECS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define SAMPLETIME_ARG ssGetSFcnParam(S, 1)
#define NUMBER_OF_ARGS 2

/* Definitions */
static char_T ErrMsg[1024]; 

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;
    uint32_T n = 0;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg,
                "Wrong number of input arguments passed.\n%d arguments are expected\n",
                NUMBER_OF_ARGS);

        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Input ports */
    if (!ssSetNumInputPorts(S, 4))
        return;

    ssSetInputPortWidth(S, n, 1);
    ssSetInputPortDataType(S, n, SS_BOOLEAN);
    ssSetInputPortRequiredContiguous(S, n, 1);
    ssSetInputPortDirectFeedThrough(S, n, 1);
    n++;
    ssSetInputPortWidth(S, n, 1);
    ssSetInputPortDataType(S, n, SS_UINT16);
    ssSetInputPortRequiredContiguous(S, n, 1);
    ssSetInputPortDirectFeedThrough(S, n, 1);
    n++;
    ssSetInputPortWidth(S, n, 1);
    ssSetInputPortDataType(S, n, SS_UINT8);
    ssSetInputPortRequiredContiguous(S, n, 1);
    ssSetInputPortDirectFeedThrough(S, n, 1);
    n++;
    ssSetInputPortWidth(S, n, 5);
    ssSetInputPortDataType(S, n, SS_UINT8);
    ssSetInputPortRequiredContiguous(S, n, 1);
    ssSetInputPortDirectFeedThrough(S, n, 1);

    /* Output ports */
    if (!ssSetNumOutputPorts(S, 0))
        return;

    /* Options */
    ssSetNumPWork(S, 2);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLETIME_ARG)[0] == -1.0)
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

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
    ssSetPWorkValue(S, 0, NULL);
    ssSetPWorkValue(S, 1, NULL);
}

static void sg_ModelStep(SimStruct *S)
{
    CIFX_CHANNEL_T *Channel = (CIFX_CHANNEL_T *)ssGetPWorkValue(S, 0);
    ECS_EMERGENCY_T *Emergency = (ECS_EMERGENCY_T *)ssGetPWorkValue(S, 1);

    boolean_T *Enable = (boolean_T *)ssGetInputPortSignal(S, 0);
    uint16_T *ErrorCode = (uint16_T *)ssGetInputPortSignal(S, 1);
    uint8_T *ErrorRegister = (uint8_T *)ssGetInputPortSignal(S, 2);
    uint8_T *Data = (uint8_T *)ssGetInputPortSignal(S, 3);

    /* Find corresponding node structure in global driver array */
    if (Channel == NULL)
    {
        CIFX_NODE_T *Node = NULL;

        if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
        {
            ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
            return;
        }

        Channel = Node->Channels[0];

        /* Add a new emergency node to the channel */
        ECS_AddEmergency(Channel, &Emergency);

        ssSetPWorkValue(S, 0, Channel);
        ssSetPWorkValue(S, 1, Emergency);
    }

    /* Update the emergency node */
    ECS_UpdateEmergency(Channel, Emergency, *Enable, 0, *ErrorCode, *ErrorRegister, Data);
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
