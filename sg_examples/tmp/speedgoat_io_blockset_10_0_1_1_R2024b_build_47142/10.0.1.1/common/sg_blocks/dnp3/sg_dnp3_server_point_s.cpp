#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_dnp3_server_point_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "dnp3.h"
#include "dnp3_api.h"
#include "dnp3_root.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace dnp3;
#endif

/* Defines */
#define NETWORK_ID_ARG      (uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define SERVER_ID_ARG   (uint16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define CMD_PROPS_ARG                         ssGetSFcnParam(S, 2)
#define GROUP_ARG           (uint16_T)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define VARIATION_ARG       (uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[1]
#define FCNCODE_ARG         (uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[2]
#define INDEX_ARG           (uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[3]
#define QTY_ARG             (uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[4]
#define PORT_PROPS_ARG                        ssGetSFcnParam(S, 3)
#define SAMPLE_TIME_ARG               mxGetPr(ssGetSFcnParam(S, 4))[0]
#define NUMBER_OF_ARGS											5

#define PORT_TYPE_ARG(i)	        ((uint32_T)(mxGetPr(PORT_PROPS_ARG)[i + 0 * (int_T)mxGetM(PORT_PROPS_ARG)]))
#define PORT_STYPE_ARG(i)	        ((uint32_T)(mxGetPr(PORT_PROPS_ARG)[i + 1 * (int_T)mxGetM(PORT_PROPS_ARG)]))
#define PORT_DTYPE_ARG(i)	        ((uint32_T)(mxGetPr(PORT_PROPS_ARG)[i + 2 * (int_T)mxGetM(PORT_PROPS_ARG)]))
#define PORT_NUM_BYTES_ARG(i)		((uint32_T)(mxGetPr(PORT_PROPS_ARG)[i + 3 * (int_T)mxGetM(PORT_PROPS_ARG)]))
#define PORT_NUM_BITS_ARG(i)		((uint32_T)(mxGetPr(PORT_PROPS_ARG)[i + 4 * (int_T)mxGetM(PORT_PROPS_ARG)]))
#define PORT_QTY_ARG(i)     		((uint32_T)(mxGetPr(PORT_PROPS_ARG)[i + 5 * (int_T)mxGetM(PORT_PROPS_ARG)]))
#define PORT_IDX_ARG(i)     		((uint32_T)(mxGetPr(PORT_PROPS_ARG)[i + 6 * (int_T)mxGetM(PORT_PROPS_ARG)]))

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct* S)
{
    uint32_T i = 0;
    uint32_T NumInputPorts = 0;
    uint32_T NumOutputPorts = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < 0; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Count input and output ports */
    for (i = 0; i < mxGetM(PORT_PROPS_ARG); i++)
    {
        switch (PORT_TYPE_ARG(i))
        {
        case 1:
            NumInputPorts++;
            break;
        case 2:
            NumOutputPorts++;
            break;
        default:
            sprintf(ErrMsg, "Unexpected error in port configuration");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    ssSetNumInputPorts(S, NumInputPorts);
    ssSetNumOutputPorts(S, NumOutputPorts);

    NumInputPorts = 0;
    NumOutputPorts = 0;

    for (i = 0; i < mxGetM(PORT_PROPS_ARG); i++)
    {
        switch (PORT_TYPE_ARG(i))
        {
        case 1:
            ssSetInputPortWidth(S, NumInputPorts, PORT_QTY_ARG(i));
            ssSetInputPortDataType(S, NumInputPorts, PORT_DTYPE_ARG(i));
            ssSetInputPortRequiredContiguous(S, NumInputPorts, 1);
            ssSetInputPortDirectFeedThrough(S, NumInputPorts, 1);
            NumInputPorts++;
            break;
        case 2:
            ssSetOutputPortWidth(S, NumOutputPorts, PORT_QTY_ARG(i));
            ssSetOutputPortDataType(S, NumOutputPorts, PORT_DTYPE_ARG(i));
            NumOutputPorts++;
            break;
        }
    }
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 1);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

static void mdlInitializeSampleTimes(SimStruct* S)
{
    if (SAMPLE_TIME_ARG == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else
    {
        ssSetSampleTime(S, 0, SAMPLE_TIME_ARG);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

static void sg_ModelLoad(SimStruct* S) {}

static void sg_ModelStart(SimStruct* S)
{
#ifndef MATLAB_MEX_FILE

    int32_t ret = 0;
    dnp3::SERVER_BLOCK_T* Block = NULL;
    cServerStation* Station = NULL;

    /* Add a server station */
    ret = Root.addStation(SERVER_ID_ARG, true, (cStation**)&Station);
    if (ret != 0)
    {
        sprintf(ErrMsg, "DNP3 | Failed to add station %i", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add present Simulink block to the server station */
    if (0 != Station->addBlock(&Block))
    {
        sprintf(ErrMsg, "DNP3 | Failed to a add block to station %i", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    Block->Type = DNP3_BLOCK_TYPE_POINT;
    Block->Group = GROUP_ARG;
    Block->Variation = VARIATION_ARG;
    Block->FcnCode = FCNCODE_ARG;
    Block->PointIdx = INDEX_ARG;
    Block->PointQty = QTY_ARG;

    /* Search for the value port and take over data type information */
    for (int i = 0; i < (int_T)mxGetM(PORT_PROPS_ARG); i++)
    {
        if (PORT_STYPE_ARG(i) == DNP3_PORT_TYPE_VALUE)
        {
            Block->DataType = PORT_DTYPE_ARG(i);
            Block->NumBytes = PORT_NUM_BYTES_ARG(i);
            Block->NumBits = PORT_NUM_BITS_ARG(i);
            break;
        }
    }

    ssSetPWorkValue(S, 0, Block);

#endif

}

static void sg_ModelStep(SimStruct* S)
{
#ifndef MATLAB_MEX_FILE

    uint32_T i = 0;
    dnp3::SERVER_BLOCK_T* Block = (dnp3::SERVER_BLOCK_T*)ssGetPWorkValue(S, 0);

    if ((Block->Group == 12) || (Block->Group == 41))
    {
        uint32_t DevFlags = Block->DevFlagsRx;

        if (DevFlags != Block->HostFlagsRx)
        {
            /* For each port */
            for (i = 0; i < (uint32_T)mxGetM(PORT_PROPS_ARG); i++)
            {
                void* Port = (void*)ssGetOutputPortSignal(S, PORT_IDX_ARG(i));
                DNP3_DATA_1201_T* Value = (DNP3_DATA_1201_T*)&Block->Value;

                switch (PORT_STYPE_ARG(i))
                {
                case (DNP3_PORT_TYPE_NEWDATA):
                {
                    memcpy(Port, (void*)Block->NewData, PORT_NUM_BYTES_ARG(i) * PORT_QTY_ARG(i));
                    break;
                }
                case (DNP3_PORT_TYPE_VALUE):
                {
                    memcpy(Port, (void*)&Value->ControlCode, PORT_NUM_BYTES_ARG(i) * PORT_QTY_ARG(i));
                    break;
                }
                case (DNP3_PORT_TYPE_COUNT):
                {
                    memcpy(Port, (void*)&Value->Count, PORT_NUM_BYTES_ARG(i) * PORT_QTY_ARG(i));
                    break;
                }
                case (DNP3_PORT_TYPE_TON):
                {
                    memcpy(Port, (void*)&Value->TimeOn, PORT_NUM_BYTES_ARG(i) * PORT_QTY_ARG(i));
                    break;
                }
                case (DNP3_PORT_TYPE_TOFF):
                {
                    memcpy(Port, (void*)&Value->TimeOff, PORT_NUM_BYTES_ARG(i) * PORT_QTY_ARG(i));
                    break;
                }
                }
            }

            Block->HostFlagsRx = DevFlags;
        }
    } else
    {
        boolean_T* Enable = (boolean_T*)ssGetInputPortSignal(S, 0);

        if (*Enable)
        {
            /* For each port */
            for (i = 1; i < (uint32_T)mxGetM(PORT_PROPS_ARG); i++)
            {
                switch (PORT_STYPE_ARG(i))
                {
                case (DNP3_PORT_TYPE_VALUE):
                {
                    uint8_T* Port = (uint8_T*)ssGetInputPortSignal(S, PORT_IDX_ARG(i));

                    memcpy((void*)Block->Value, Port, PORT_NUM_BYTES_ARG(i) * PORT_QTY_ARG(i));
                }
                }
            }
            Block->HostFlagsTx++;
        }
    }

#endif
}

static void sg_ModelStop(SimStruct* S)
{
}

#include "sg_sfcn_glue.h"   // Code generation glue
