#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO753_netstate_v2_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#include "MBM_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define SAMPLE_TIME_ARG ssGetSFcnParam(S, 1)
#define SET_STATUS_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define NUM_SERVERS_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define NUM_COMMANDS_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define NUMBER_OF_ARGS 5

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Input ports */
    if (SET_STATUS_ARG)
    {
        if (!ssSetNumInputPorts(S, 1))
            return;
        ssSetInputPortWidth(S, 0, 1);
        ssSetInputPortDataType(S, 0, SS_BOOLEAN);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
    }
    else
    {
        if (!ssSetNumInputPorts(S, 0))
            return;
    }

    /* Output ports */
    if (!ssSetNumOutputPorts(S, 5))
        return;

    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_BOOLEAN);

    ssSetOutputPortWidth(S, 1, NUM_SERVERS_ARG > 0 ? NUM_SERVERS_ARG : 1);
    ssSetOutputPortDataType(S, 1, SS_BOOLEAN);

    ssSetOutputPortWidth(S, 2, NUM_SERVERS_ARG > 0 ? NUM_SERVERS_ARG : 1);
    ssSetOutputPortDataType(S, 2, SS_BOOLEAN);

    ssSetOutputPortWidth(S, 3, NUM_SERVERS_ARG > 0 ? NUM_SERVERS_ARG : 1);
    ssSetOutputPortDataType(S, 3, SS_BOOLEAN);

    ssSetOutputPortWidth(S, 4, NUM_COMMANDS_ARG > 0 ? NUM_COMMANDS_ARG : 1);
    ssSetOutputPortDataType(S, 4, SS_BOOLEAN);

    /* Options */
    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLE_TIME_ARG)[0] == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLE_TIME_ARG)[0]);
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
}

static void sg_ModelStep(SimStruct *S)
{
    CIFX_CHANNEL_T *Channel = (CIFX_CHANNEL_T *)ssGetPWorkValue(S, 0);
    MBM_PARAM_T *Param = NULL;
    MBM_DIAG_T *Diag = NULL;
    uint32_T i = 0;

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
        ssSetPWorkValue(S, 0, Channel);
    }

    /* Set network status */
    if (SET_STATUS_ARG)
    {
        uint32_T b = (*((boolean_T *)ssGetInputPortSignal(S, 0)) == false) ? 0 : 1;
        Cifx_SetNWStat(Channel, &b);
    }

    /* Get network status */
    {
        uint32_T b = 0;
        Cifx_GetNWStat(Channel, &b);
        *((boolean_T *)ssGetOutputPortSignal(S, 0)) = (b == false) ? 0 : 1;
    }

    Param = (MBM_PARAM_T *)(Channel->Param);
    Diag = &Param->Diag;

    /* Get server and command stati */
    for (i = 0; i < NUM_SERVERS_ARG; i++)
    {
        boolean_T *Out = NULL;
        uint32_T ByteOffset = (uint32_T)(i / 8);
        uint32_T BitOffset = (uint32_T)(i % 8);

        Out = (boolean_T *)ssGetOutputPortSignal(S, 1) + i;
        *Out = ((Diag->ConfigSlaves[ByteOffset] >> BitOffset) & 0x01);

        Out = (boolean_T *)ssGetOutputPortSignal(S, 2) + i;
        *Out = ((Diag->ActiveSlaves[ByteOffset] >> BitOffset) & 0x01);

        Out = (boolean_T *)ssGetOutputPortSignal(S, 3) + i;
        *Out = ((Diag->DiagSlaves[ByteOffset] >> BitOffset) & 0x01);
    }

    for (i = 0; i < NUM_COMMANDS_ARG; i++)
    {
        boolean_T *Out = (boolean_T *)ssGetOutputPortSignal(S, 4) + i;
        uint32_T ByteOffset = (uint32_T)(i / 8);
        uint32_T BitOffset = (uint32_T)(i % 8);

        *Out = ((Diag->CommandDiag[ByteOffset] >> BitOffset) & 0x01);
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
