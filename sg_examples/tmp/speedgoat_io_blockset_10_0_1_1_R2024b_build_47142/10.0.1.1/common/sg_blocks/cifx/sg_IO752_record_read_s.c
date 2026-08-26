#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO752_record_read_s

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
#define SAMPLETIME_ARG ssGetSFcnParam(S, 1)
#define RECORD_CFG ssGetSFcnParam(S, 2)
#define NUMBER_OF_ARGS 3

#define RECORD_ACCESSMODE(i) ((uint8_T)(mxGetPr(RECORD_CFG)[i + 4 * (int_T)mxGetM(RECORD_CFG)]))
#define RECORD_BYTELEN(i) ((uint32_T)(mxGetPr(RECORD_CFG)[i + 5 * (int_T)mxGetM(RECORD_CFG)]))

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0, n = 0;
    uint32_T NumPorts = 0;

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

    /* Inputs ports */
    if (!ssSetNumInputPorts(S, 0))
        return;

    /* Output ports */
    for (i = 0; i < mxGetM(RECORD_CFG); i++)
    {
        if ((RECORD_ACCESSMODE(i) == 1) || (RECORD_ACCESSMODE(i) == 3))
        {
            NumPorts++;
        }
    }
    if (!ssSetNumOutputPorts(S, NumPorts))
        return;

    for (i = 0; i < mxGetM(RECORD_CFG); i++)
    {
        if ((RECORD_ACCESSMODE(i) == 1) || (RECORD_ACCESSMODE(i) == 3))
        {
            ssSetOutputPortWidth(S, n, RECORD_BYTELEN(i));
            ssSetOutputPortDataType(S, n, SS_UINT8);
            n++;
        }
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
    uint32_t i = 0, p = 0;
    CIFX_CHANNEL_T *Channel = (CIFX_CHANNEL_T *)ssGetPWorkValue(S, 0);
    PNS_PARAM_T *Param = NULL;

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
        Param = (PNS_PARAM_T *)(Channel->Param);

        /* Check whether RECORD configurations match */
        if (mxGetM(RECORD_CFG) != Param->NumRecords)
        {
            ssSetErrorStatus(S, "RECORD configurations of Setup block and Read block do not match\n");
            return;
        }
        for (i = 0; i < Param->NumRecords; i++)
        {
            if (RECORD_BYTELEN(i) != (Param->Records[i])->MaxDataLen)
            {
                ssSetErrorStatus(S, "RECORD configurations of Setup block and Read block do not match\n");
                return;
            }
        }

        ssSetPWorkValue(S, 0, Channel);
    }

    Param = (PNS_PARAM_T *)(Channel->Param);

    /* For each RECORD */
    for (i = 0; i < mxGetM(RECORD_CFG); i++)
    {

        /* Read direction only */
        if ((RECORD_ACCESSMODE(i) == 1) || (RECORD_ACCESSMODE(i) == 3))
        {
            memcpy((void *)ssGetOutputPortSignal(S, p),
                   (void *)(Param->Records[i])->Data,
                   (Param->Records[i])->MaxDataLen);
            p++;
        }
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
