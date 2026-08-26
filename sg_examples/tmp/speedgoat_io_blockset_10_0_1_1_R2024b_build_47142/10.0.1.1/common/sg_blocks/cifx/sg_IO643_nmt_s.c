#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO643_nmt_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#include "COM_api.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define CO_NODE_ID_ARG ssGetSFcnParam(S, 1)
#define SAMPLE_TIME_ARG ssGetSFcnParam(S, 2)

#define NUMBER_OF_ARGS 3

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

    /* Output ports */
    if (!ssSetNumOutputPorts(S, 0))
        return;

    /* Input ports */
    if (!ssSetNumInputPorts(S, 1))
        return;
    ssSetInputPortWidth(S, 0, mxGetN(CO_NODE_ID_ARG));
    ssSetInputPortDataType(S, 0, SS_UINT32);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

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
    int32_t i = 0;
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;
    COM_PARAM_T *Param = NULL;
    
    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];
    Param = (COM_PARAM_T *)(Channel->Param);

    Param->Nmt.NumNodes = mxGetN(CO_NODE_ID_ARG);
    for (i = 0; i < Param->Nmt.NumNodes; i++)
    {
        Param->Nmt.Nodes[i] = (uint32_t)mxGetPr(CO_NODE_ID_ARG)[i];
    }

    Cifx_ConditionalStartCom(Channel);
    ssSetPWorkValue(S, 0, NULL);
}

static void sg_ModelStep(SimStruct *S)
{
    int32_t i = 0;
    CIFX_CHANNEL_T *Channel = (CIFX_CHANNEL_T *)ssGetPWorkValue(S, 0);
    COM_PARAM_T *Param = NULL;
    uint32_T *u = (uint32_T*)ssGetInputPortSignal(S,0);

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

    Param = (COM_PARAM_T *)(Channel->Param);

    for (i = 0; i < Param->Nmt.NumNodes; i++)
    {
        if (Param->Nmt.Triggers[i] == 0)
        {
            if (u[i] != Param->Nmt.States[i])
            {
                Param->Nmt.States[i] = u[i];
                Param->Nmt.Triggers[i] = 1;
            }
        }
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
