#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO755_receive_s

/* Includes */
#include <stddef.h>
#include <stdlib.h>

#include <stdbool.h>
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define SAMPLETIME_ARG ssGetSFcnParam(S, 1)
#define INADDRESS_ARG ssGetSFcnParam(S, 2)
#define DATA_LEN_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define PORT_TYPE_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define NUMBER_OF_ARGS (5)

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

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

    /* Ports */
    if (!ssSetNumInputPorts(S, 0))
        return;

    if (PORT_TYPE_ARG == 1)
    {
        if (!ssSetNumOutputPorts(S, DATA_LEN_ARG))
            return;

        for (i = 0; i < DATA_LEN_ARG; i++)
        {
            ssSetOutputPortWidth(S, i, 1);
            ssSetOutputPortDataType(S, i, SS_UINT8);
        }
    }
    else if (PORT_TYPE_ARG == 2)
    {
        if (!ssSetNumOutputPorts(S, 1))
            return;

        ssSetOutputPortWidth(S, 0, DATA_LEN_ARG);
        ssSetOutputPortDataType(S, 0, SS_UINT8);
    }

    /* Options */
    ssSetNumPWork(S, 1);
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
}

static void sg_ModelStep(SimStruct *S)
{
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];

    if (PORT_TYPE_ARG == 1)
    {
        uint8_T data[5760] = {0};

        if (Cifx_RecDataExt(Channel, DATA_LEN_ARG, (void *)data))
        {
            uint8_t *pOutPort = NULL;
            uint32_T i;

            for (i = 0; i < DATA_LEN_ARG; i++)
            {
                pOutPort = (uint8_T *)ssGetOutputPortSignal(S, i);
                pOutPort[0] = data[i];
            }
        }
    }
    else
    {
        Cifx_RecDataExt(Channel, DATA_LEN_ARG, (void *)ssGetOutputPortSignal(S, 0));
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
