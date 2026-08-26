
#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO754_message_v2_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#include "MBS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define SAMPLETIME_ARG ssGetSFcnParam(S, 1)
#define pBlkFcn ssGetSFcnParam(S, 2)
#define pSTART_ADR ssGetSFcnParam(S, 3)
#define pQTY ssGetSFcnParam(S, 4)
#define pMAIN_PROTOCOL ssGetSFcnParam(S, 5)
#define pSUB_PROTOCOL ssGetSFcnParam(S, 6)
#define INIT_VAL_ARG ssGetSFcnParam(S, 7)
#define NUMBER_OF_ARGS 8

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;
    uint32_T DataQty = 0;
    uint32_T DataType = 0;
    uint32_T NumInPorts = 0;
    uint32_T NumOutPorts = 0;

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
    DataQty = (uint32_T)mxGetPr(pQTY)[0];

    switch ((uint8_T)mxGetPr(pBlkFcn)[0])
    {
    case 1: // Set Coils
    case 3: // Set inputs
        NumInPorts = 1;
        NumOutPorts = 0;
        DataType = SS_BOOLEAN;
        break;
    case 2: // Read Coils
    case 4: // Read inputs
        NumInPorts = 0;
        NumOutPorts = 1;
        DataType = SS_BOOLEAN;
        break;
    case 5: // Set holding
    case 7: // Set inReg
        NumInPorts = 1;
        NumOutPorts = 0;
        DataType = SS_UINT16;
        break;
    case 6: // Read Holding
    case 8: // Read inReg
        NumInPorts = 0;
        NumOutPorts = 1;
        DataType = SS_UINT16;
        break;
    case 10: // Msg-Mode
        NumInPorts = 0;
        NumOutPorts = 0;
        break;
    default:
        break;
    }

    if (!ssSetNumInputPorts(S, NumInPorts))
        return;
    if (!ssSetNumOutputPorts(S, NumOutPorts))
        return;

    switch ((uint8_T)mxGetPr(pBlkFcn)[0])
    {
    case 1: // Set Coils
    case 3: // Set inputs
    case 5: // Set holding
    case 7: // Set inReg
        ssSetInputPortWidth(S, 0, DataQty);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDataType(S, 0, DataType);
        break;
    case 2: // Read Coils
    case 4: // Read inputs
    case 6: // Read Holding
    case 8: // Read inReg
        ssSetOutputPortWidth(S, 0, DataQty);
        ssSetOutputPortDataType(S, 0, DataType);
        break;
    default:
        break;
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
    MBS_PARAM_T *Param = NULL;
    uint8_T fun = (uint8_T)mxGetPr(pBlkFcn)[0];
    uint32_T addr = (uint32_T)mxGetPr(pSTART_ADR)[0];
    uint32_T qty = (uint32_T)mxGetPr(pQTY)[0];

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

        Param = (MBS_PARAM_T *)(Channel->Param);
        if (Param->ProtMode == 1) // IO-Mode
        {
            return;
        }

        /* Initialize modbus data areas */
        if (mxGetN(INIT_VAL_ARG) > 0)
        {
            uint32_T i = 0;

            switch (fun)
            {
            case 2: // Read coils
            {
                uint8_T InitValues[65536] = {0};
                for (i = 0; i < qty; i++)
                {
                    InitValues[i] = (uint8_T)mxGetPr(INIT_VAL_ARG)[i];
                }
                MBS_WriteBit(Channel, MBS_AREA_COIL, addr, qty, InitValues);
                break;
            }
            case 6: // Read holding register
            {
                uint16_T InitValues[65536] = {0};
                for (i = 0; i < qty; i++)
                {
                    InitValues[i] = (uint16_T)mxGetPr(INIT_VAL_ARG)[i];
                }
                MBS_WriteWord(Channel, MBS_AREA_HOLDING, addr, qty, InitValues);
                break;
            }
            }
        }
    }

    Param = (MBS_PARAM_T *)(Channel->Param);
    if (Param->ProtMode == 1) // IO-Mode
    {
        return;
    }

    switch (fun)
    {
    case 1: // Set coils
        MBS_WriteBit(Channel, MBS_AREA_COIL, addr, qty, (uint8_T *)ssGetInputPortSignal(S, 0));
        break;
    case 2: // Read coils
        MBS_ReadBit(Channel, MBS_AREA_COIL, addr, qty, (uint8_T *)ssGetOutputPortSignal(S, 0));
        break;
    case 3: // Set discrete inputs
        MBS_WriteBit(Channel, MBS_AREA_DISCRETE, addr, qty, (uint8_T *)ssGetInputPortSignal(S, 0));
        break;
    case 4: // Read discrete inputs
        MBS_ReadBit(Channel, MBS_AREA_DISCRETE, addr, qty, (uint8_T *)ssGetOutputPortSignal(S, 0));
        break;
    case 5: // Set holding register
        MBS_WriteWord(Channel, MBS_AREA_HOLDING, addr, qty, (uint16_T *)ssGetInputPortSignal(S, 0));
        break;
    case 6: // Read holding register
        MBS_ReadWord(Channel, MBS_AREA_HOLDING, addr, qty, (uint16_T *)ssGetOutputPortSignal(S, 0));
        break;
    case 7: // Set input register
        MBS_WriteWord(Channel, MBS_AREA_INPUT, addr, qty, (uint16_T *)ssGetInputPortSignal(S, 0));
        break;
    case 8: // Read input register
        MBS_ReadWord(Channel, MBS_AREA_INPUT, addr, qty, (uint16_T *)ssGetOutputPortSignal(S, 0));
        break;
    }

    MBS_MsgModeIndicationHandling(Channel);
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
