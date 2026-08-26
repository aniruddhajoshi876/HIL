#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO750_receive_v2_s

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
#define PDO_CFG ssGetSFcnParam(S, 4)
#define DATA_LEN_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define NUMBER_OF_ARGS 6

#define PDO_DT(i) (mxGetPr(PDO_CFG)[i + 1 * (int_T)mxGetM(PDO_CFG)])
#define PDO_BITLEN(i) (mxGetPr(PDO_CFG)[i + 2 * (int_T)mxGetM(PDO_CFG)])
#define PDO_PAD(i) (mxGetPr(PDO_CFG)[i + 3 * (int_T)mxGetM(PDO_CFG)])
#define PDO_BYTEOFFSET(i) (mxGetPr(PDO_CFG)[i + 4 * (int_T)mxGetM(PDO_CFG)])
#define PDO_BITOFFSET(i) (mxGetPr(PDO_CFG)[i + 5 * (int_T)mxGetM(PDO_CFG)])
#define PDO_ECAT_DT(i) (mxGetPr(PDO_CFG)[i + 6 * (int_T)mxGetM(PDO_CFG)])

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

    /* Input ports */
    if (!ssSetNumInputPorts(S, 0))
        return;

    /* Output ports */
    if (mxGetM(PDO_CFG) <= 0)
    {
        if (!ssSetNumOutputPorts(S, 0))
            return;
    }
    else
    {
        if (PORT_TYPE_ARG == 1) // 1 output port with byte array
        {
            if (!ssSetNumOutputPorts(S, 1))
                return;
            ssSetOutputPortWidth(S, 0, DATA_LEN_ARG);
            ssSetOutputPortDataType(S, 0, SS_UINT8);
        }
        else if (PORT_TYPE_ARG == 2) // one output port for each variable
        {
            int_T n = 0;
            for (i = 0; i < mxGetM(PDO_CFG); i++) // Skip padding bytes
            {
                if (!(boolean_T)PDO_PAD(i))
                {
                    n++;
                }
            }

            if (!ssSetNumOutputPorts(S, n))
                return;

            n = 0;
            for (i = 0; i < mxGetM(PDO_CFG); i++)
            {
                if (!(boolean_T)PDO_PAD(i))
                {
                    ssSetOutputPortWidth(S, n, 1);
                    ssSetOutputPortDataType(S, n, (int32_T)PDO_DT(i));
                    n++;
                }
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

    if (mxGetM(PDO_CFG) > 0) // If no variables have been defined
    {
        if (PORT_TYPE_ARG == 1) // If one port with byte array
        {
            Cifx_RecDataExt(Channel, DATA_LEN_ARG, (void *)ssGetOutputPortSignal(S, 0));
        }
        else // If one port for each signal
        {
            uint8_T data[5760] = {0};

            if (Cifx_RecDataExt(Channel, DATA_LEN_ARG, (void *)data))
            {
                uint32_T i = 0;
                uint32_T n = 0;

                for (i = 0; i < mxGetM(PDO_CFG); i++) // Do for each PDO variable
                {
                    if (!(boolean_T)PDO_PAD(i)) // Skip padding variables
                    {
                        if (PDO_DT(i) == SS_BOOLEAN) // If boolean
                        {
                            boolean_T *p = (boolean_T *)ssGetOutputPortSignal(S, n);
                            *p = (data[(uint32_T)PDO_BYTEOFFSET(i)] & ((uint8_T)0x01 << (uint8_T)PDO_BITOFFSET(i))) > 0;
                        }
                        else // If non boolean
                        {
                            void *p = (void *)ssGetOutputPortSignal(S, n);
                            memcpy(p, &data[(uint32_T)PDO_BYTEOFFSET(i)], (uint32_T)PDO_BITLEN(i) / 8);
                        }
                        n++;
                    }
                }
            }
        }
    }

    ECS_AcyclicHandler(Channel);
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
