#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO750_sdo_read_s

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
#define PORT_TYPE_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
// 2
#define SAMPLETIME_ARG ssGetSFcnParam(S, 3)
#define SDO_CFG ssGetSFcnParam(S, 4)
#define DATA_LEN_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define NUMBER_OF_ARGS 6

#define SDO_INDEX(i) ((uint16_T)(mxGetPr(SDO_CFG)[i + 0 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_SUBINDEX(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 1 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_DT(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 2 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_INIVAL(i) ((real64_T)(mxGetPr(SDO_CFG)[i + 3 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_ACCESSRIGHTS(i) ((uint16_T)(mxGetPr(SDO_CFG)[i + 4 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_ACCESSMODE(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 5 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_BYTELEN(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 6 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_NUMELEMENTS(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 7 * (int_T)mxGetM(SDO_CFG)]))

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
    if (!ssSetNumInputPorts(S, 0))
        return;

    /* Output ports */
    for (i = 0; i < mxGetM(SDO_CFG); i++)
    {
        if ((SDO_ACCESSMODE(i) == 1) || (SDO_ACCESSMODE(i) == 3))
        {
            if (SDO_SUBINDEX(i) != 0 || (SDO_NUMELEMENTS(i) == 0))
            {
                NumPorts++;
            }
        }
    }
    if (!ssSetNumOutputPorts(S, NumPorts))
        return;

    for (i = 0; i < mxGetM(SDO_CFG); i++)
    {
        if ((SDO_ACCESSMODE(i) == 1) || (SDO_ACCESSMODE(i) == 3))
        {
            if (SDO_SUBINDEX(i) != 0 || (SDO_NUMELEMENTS(i) == 0))
            {
                ssSetOutputPortWidth(S, n, 1);
                ssSetOutputPortDataType(S, n, (int32_T)SDO_DT(i));
                n++;
            }
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
    CIFX_CHANNEL_T *Channel = (CIFX_CHANNEL_T *)ssGetPWorkValue(S, 0);
    ECS_PARAM_T *Param = NULL;
    uint32_T i = 0, p = 0;

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
        Param = (ECS_PARAM_T *)(Channel->Param);

        /* Check whether SDO configurations match */
        if (mxGetM(SDO_CFG) != Param->NumSdo)
        {
            ssSetErrorStatus(S, "SDO configurations of Setup block and Read/Write block do not match\n");
            return;
        }
        for (i = 0; i < Param->NumSdo; i++)
        {
            if (SDO_BYTELEN(i) != Param->Sdo[i].ByteLen)
            {
                ssSetErrorStatus(S, "SDO configurations of Setup block and Read/Write block do not match\n");
                return;
            }
        }

        ssSetPWorkValue(S, 0, Channel);
    }

    Param = (ECS_PARAM_T *)(Channel->Param);

    /* Check if index is in range */
    for (i = 0; i < Param->NumSdo; i++)
    {
        ECS_SDO_T *Sdo = &Param->Sdo[i];

        /* SDO must not be a root object with sub objects */
        if ((Sdo->SubIndex != 0) ||
            (Sdo->NumElements == 0))
        {
            /* Read direction */
            if ((Sdo->AccessMode == 1) || (Sdo->AccessMode == 3))
            {
                if (p < (uint32_T)ssGetNumOutputPorts(S))
                {
                    void *Port = (void *)ssGetOutputPortSignal(S, p);

                    memcpy(Port, (void *)Sdo->ReadValue, Sdo->ByteLen);

                    Sdo->RxHostFlags++;

                    p++;
                }
            }
        }
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
