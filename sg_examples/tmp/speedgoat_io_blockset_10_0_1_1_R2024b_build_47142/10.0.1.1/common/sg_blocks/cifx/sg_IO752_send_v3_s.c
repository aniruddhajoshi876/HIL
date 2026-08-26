#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO752_send_v3_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#include "PNS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define SAMPLE_TIME_ARG ssGetSFcnParam(S, 1)
#define PORT_CONFIG_ARG ssGetSFcnParam(S, 2)
#define NUM_BYTES_ARG ((uint32_T)mxGetPr(ssGetSFcnParam(S, 3))[0])
#define NUMBER_OF_ARGS 4

#define PORT_TYPE_ARG(i) ((int_T)(mxGetPr(PORT_CONFIG_ARG)[i + 0 * (int_T)mxGetM(PORT_CONFIG_ARG)]))
#define PORT_LENGTH_ARG(i) ((int_T)(mxGetPr(PORT_CONFIG_ARG)[i + 1 * (int_T)mxGetM(PORT_CONFIG_ARG)]))
#define PORT_NUMBYTES_ARG(i) ((int_T)(mxGetPr(PORT_CONFIG_ARG)[i + 2 * (int_T)mxGetM(PORT_CONFIG_ARG)]))

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

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

    /* Ports */
    if (!ssSetNumOutputPorts(S, 0))
        return;
    if (!ssSetNumInputPorts(S, mxGetM(PORT_CONFIG_ARG)))
        return;

    for (i = 0; i < mxGetM(PORT_CONFIG_ARG); i++)
    {

        ssSetInputPortWidth(S, i, (int_T)PORT_LENGTH_ARG(i));
        ssSetInputPortDataType(S, i, (int_T)PORT_TYPE_ARG(i));
        ssSetInputPortRequiredContiguous(S, i, 1);
        ssSetInputPortDirectFeedThrough(S, i, 1);
    }

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

    /* Copy the data to the output ports */
    if (NUM_BYTES_ARG > 0)
    {
        uint8_T Data[5760] = {0};
        uint32_T Offset = 0;
        void *Port = NULL;

        uint32_T i;

        for (i = 0; i < ssGetNumInputPorts(S); i++)
        {
            Port = (void *)ssGetInputPortSignal(S, i);
            memcpy(&Data[Offset], Port, PORT_NUMBYTES_ARG(i));
            Offset += PORT_NUMBYTES_ARG(i);
        }

        Cifx_SndDataExt(Channel, NUM_BYTES_ARG, (void *)Data);
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
