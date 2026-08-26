#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO753_receive_v2_s

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
#define CMD_CONFIG_ARG ssGetSFcnParam(S, 2)
#define CMD_CONFIG_CRC_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define NUMBER_OF_ARGS 4

#define CMD_IPADDR(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 0 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_UNIT(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 1 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_CODE(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 2 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_ADDR(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 3 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_QTY(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 4 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_TIME(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 5 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_OFFSET(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 6 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_LEN(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 7 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_RW(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 8 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_DT(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 9 * (int_T)mxGetM(CMD_CONFIG_ARG)]))

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
    if (!ssSetNumInputPorts(S, 0))
        return;

    /* Output ports */
    if (mxGetM(CMD_CONFIG_ARG) <= 0)
    {
        if (!ssSetNumOutputPorts(S, 0))
            return;
    }
    else
    {
        int_T n = 0;
        for (i = 0; i < mxGetM(CMD_CONFIG_ARG); i++)
        {

            /* Create port only for send/write commands */
            if (CMD_RW(i) == 0)
            {
                n++;
            }
        }

        if (!ssSetNumOutputPorts(S, n))
            return;

        n = 0;
        for (i = 0; i < mxGetM(CMD_CONFIG_ARG); i++)
        {
            if (CMD_RW(i) == 0)
            {
                ssSetOutputPortWidth(S, n, (int32_T)CMD_QTY(i));
                ssSetOutputPortDataType(S, n, (int32_T)CMD_DT(i));
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
    uint8_T data[CIFX_DPM_IO_DATA_SIZE] = {0};
    uint32_T i = 0; // command index
    uint32_T p = 0; // block input/output port index
    uint32_T n = 0; // port array element index

    CIFX_CHANNEL_T *Channel = (CIFX_CHANNEL_T *)ssGetPWorkValue(S, 0);
    MBM_PARAM_T *Param = NULL;

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
        Param = (MBM_PARAM_T *)(Channel->Param);

        /* Check whether command configurations match */
        if (CMD_CONFIG_CRC_ARG != Param->CmdCRC)
        {
            ssSetErrorStatus(S, "Command configuration of Setup block and Receive block do not match");
            return;
        }

        ssSetPWorkValue(S, 0, Channel);
    }

    Param = (MBM_PARAM_T *)(Channel->Param);

    /* Copy data from DPM */
    Cifx_RecDataExt(Channel, Param->ReadLen, (void *)data);

    /* For each command */
    for (i = 0; i < mxGetM(CMD_CONFIG_ARG); i++)
    {
        /* Only if send/write */
        if (CMD_RW(i) == MBM_DIRECTION_READ)
        {
            /* Coils / discretes */
            if (CMD_DT(i) == SS_BOOLEAN)
            {
                /* For each array element */
                for (n = 0; n < CMD_QTY(i); n++)
                {
                    boolean_T *Val = (boolean_T *)ssGetOutputPortSignal(S, p) + n;
                    uint32_T ByteOffset = CMD_OFFSET(i) + (uint32_T)(n / 8);
                    uint32_T BitOffset = (uint32_T)(n % 8);

                    *Val = ((data[ByteOffset] >> BitOffset) & 0x01);
                }
            }
            /* Registers */
            else
            {
                void *port = (void *)ssGetOutputPortSignal(S, p);
                memcpy(port, &data[CMD_OFFSET(i)], CMD_QTY(i) * sizeof(uint16_T));
            }
            p++;
        }
    }

    /* Get diag information */
    memcpy(&Param->Diag, &data[Param->DiagOffset], sizeof(MBM_DIAG_T));
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
