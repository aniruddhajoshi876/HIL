#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO644_transceiver_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* Defines */
#define MOD_ID_ARG      (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG     (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define MESSAGE_ID_ARG  (uint32_T) mxGetScalar(ssGetSFcnParam(S, 1))
#define INIT_VALUE_ARG  ssGetSFcnParam(S, 2)
#define OP_ARG          (uint32_T) mxGetScalar(ssGetSFcnParam(S, 3))
#define EXTENDED_ARG    (boolean_T) mxGetScalar(ssGetSFcnParam(S, 4))
#define SAMPLE_TIME_ARG ssGetSFcnParam(S, 5)

#define RECEIVE_OP_ARG (OP_ARG == 1)
#define SEND_OP_ARG    (OP_ARG == 2)

#define NUM_ARGS 6

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;
    uint32_T PortIndex = 0;
    uint32_T NumInputPorts = 0;
    uint32_T NumOutputPorts = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUM_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUM_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Configure ports */
    if (SEND_OP_ARG) {
        NumInputPorts++;
        if (EXTENDED_ARG) {
            NumInputPorts++;
            NumInputPorts++;
        }
    }
    if (RECEIVE_OP_ARG) {
        NumOutputPorts++;
        if (EXTENDED_ARG) {
            NumOutputPorts++;
            NumOutputPorts++;
        }
    }

    /* Configure input ports */
    if (!ssSetNumInputPorts(S, NumInputPorts))
        return;

    if (SEND_OP_ARG) {
        ssSetInputPortDataType(S, PortIndex, DYNAMICALLY_TYPED);
        ssSetInputPortWidth(S, PortIndex, DYNAMICALLY_SIZED);
        ssSetInputPortRequiredContiguous(S, PortIndex, 1);
        ssSetInputPortDirectFeedThrough(S, PortIndex, 1);
        PortIndex++;
        if (EXTENDED_ARG) {
            ssSetInputPortDataType(S, PortIndex, SS_BOOLEAN);
            ssSetInputPortWidth(S, PortIndex, 1);
            ssSetInputPortRequiredContiguous(S, PortIndex, 1);
            ssSetInputPortDirectFeedThrough(S, PortIndex, 1);
            PortIndex++;
            ssSetInputPortDataType(S, PortIndex, SS_UINT32);
            ssSetInputPortWidth(S, PortIndex, 1);
            ssSetInputPortRequiredContiguous(S, PortIndex, 1);
            ssSetInputPortDirectFeedThrough(S, PortIndex, 1);
            PortIndex++;
        }
    }

    /* Configure output ports */
    if (!ssSetNumOutputPorts(S, NumOutputPorts))
        return;

    PortIndex = 0;

    if (RECEIVE_OP_ARG) {
        ssSetOutputPortDataType(S, PortIndex, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
        ssSetOutputPortWidth(S, PortIndex, mxGetNumberOfElements(INIT_VALUE_ARG));
        PortIndex++;
        if (EXTENDED_ARG) {
            ssSetOutputPortDataType(S, PortIndex, SS_UINT32);
            ssSetOutputPortWidth(S, PortIndex, 1);
            PortIndex++;
            ssSetOutputPortDataType(S, PortIndex, SS_UINT32);
            ssSetOutputPortWidth(S, PortIndex, 1);
            PortIndex++;
        }
    }

    /* Set options */
    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLE_TIME_ARG)[0] == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLE_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct *S)
{
    ssSetNumRunTimeParams(S, 1);
    ssRegDlgParamAsRunTimeParam(S, 2, 0, "InitValue",
                                ssGetDTypeIdFromMxArray(ssGetSFcnParam(S, 2)));
}

#define MDL_SET_INPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_INPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    ssSetInputPortDimensionInfo(S, portIndex, dimsInfo);
}
#endif /* MDL_SET_INPUT_PORT_DIMENSION_INFO */

#define MDL_SET_INPUT_PORT_DATA_TYPE
#if defined(MDL_SET_INPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDataType(SimStruct *S, int_T port, DTypeId id)
{
    ssSetInputPortDataType(S, port, id);
}
#endif /* MDL_SET_INPUT_PORT_DATA_TYPE */

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    ssSetOutputPortDimensionInfo(S, portIndex, dimsInfo);
}
#endif /* MDL_SET_OUTPUT_PORT_DIMENSION_INFO */

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
#if defined(MDL_SET_OUTPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDataType(SimStruct *S, int_T port, DTypeId id)
{

    ssSetOutputPortDataType(S, port, id);
}
#endif /* MDL_SET_OUTPUT_PORT_DATA_TYPE */

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
#if defined(MDL_SET_DEFAULT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
    ssSetErrorStatus(S, "Cannot inherit port data types\n");
    return;
}
#endif /* MDL_SET_DEFAULT_PORT_DIMENSION_INFO */

static void mdlStart(SimStruct *S) {}
static void mdlOutputs(SimStruct *S, int_T tid) {}
static void mdlTerminate(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{
    int32_T Dummy = 0;
    uint32_T ModuleId = MOD_ID_ARG;
    uint32_T NodeId = NODE_ID_ARG;
    uint32_T MessageId = MESSAGE_ID_ARG;
    uint32_T Operation = OP_ARG;
    boolean_T Extended = EXTENDED_ARG;

    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Channel", ssGetNumPWork(S))) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosBlockIdx", &Dummy, SS_INT32)) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosModuleIdx", &Dummy, SS_INT32)) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosMessageIdx", &Dummy, SS_INT32)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(
            S, 5, SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "MessageId", &MessageId, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "Operation", &Operation, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended, DTINFO(SS_BOOLEAN, COMPLEX_NO))) {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h" // Code generation glue
