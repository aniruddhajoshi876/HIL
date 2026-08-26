#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO751_record_write_s

/* Includes */
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* Defines */
#define MOD_ID_ARG       (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG      (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define DEVICE_INDEX_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define API_ARG          (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define SLOT_ARG         (uint16_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define SUBSLOT_ARG      (uint16_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define RECORD_INDEX_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define EXTENDED_ARG     (boolean_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define SAMPLE_TIME_ARG  ssGetSFcnParam(S, 7)
#define TIMEOUT_ARG      (uint32_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define NUMBER_OF_ARGS   9

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Wrong number of input arguments passed.\n%d arguments are expected\n",
                NUMBER_OF_ARGS);

        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Input ports */
    if (EXTENDED_ARG) {
        if (!ssSetNumInputPorts(S, 3))
            return;
    } else {
        if (!ssSetNumInputPorts(S, 2))
            return;
    }

    /* 1. DATA input port */
    ssSetInputPortDataType(S, 0, DYNAMICALLY_TYPED);
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    /* 2. ENABLE input port */
    ssSetInputPortDataType(S, 1, SS_BOOLEAN);
    ssSetInputPortWidth(S, 1, 1);
    ssSetInputPortRequiredContiguous(S, 1, 1);
    ssSetInputPortDirectFeedThrough(S, 1, 1);

    /* 3. DATA LENGTH input port */
    if (EXTENDED_ARG) {
        ssSetInputPortDataType(S, 2, SS_UINT32);
        ssSetInputPortWidth(S, 2, 1);
        ssSetInputPortRequiredContiguous(S, 2, 1);
        ssSetInputPortDirectFeedThrough(S, 2, 1);
    }

    /* Output ports */
    if (EXTENDED_ARG) {
        if (!ssSetNumOutputPorts(S, 2))
            return;

        /* 1. STATUS output port */
        ssSetOutputPortDataType(S, 0, SS_UINT32);
        ssSetOutputPortWidth(S, 0, 1);

        /* 2. ERROR output port */
        ssSetOutputPortDataType(S, 1, SS_UINT32);
        ssSetOutputPortWidth(S, 1, 1);
    } else {
        if (!ssSetNumOutputPorts(S, 0))
            return;
    }

    /* Options */
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 2);

    ssSetNumDWork(S, 2);
    /* Error string DWORK */
    ssSetDWorkName(S, 0, "ErrMsg");
    ssSetDWorkDataType(S, 0, SS_UINT8);
    ssSetDWorkWidth(S, 0, 256);
    /* DWORK for remembering the ENABLE input port value */
    ssSetDWorkName(S, 1, "EnablePort");
    ssSetDWorkWidth(S, 1, 1);
    ssSetDWorkDataType(S, 1, SS_BOOLEAN);

    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

/*
 *   Set the sample times of the S-Function block.
 */
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
#endif /* MDL_SET_INPUT_PORT_DIMENSION_INFO */

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
#if defined(MDL_SET_OUTPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDataType(SimStruct *S, int_T port, DTypeId id)
{
    ssSetOutputPortDataType(S, port, id);
}
#endif /* MDL_SET_INPUT_PORT_DATA_TYPE */

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
#if defined(MDL_SET_DEFAULT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
    ssSetErrorStatus(S, "Cannot inherit port data types\n");
    return;
}
#endif /* MDL_SET_DEFAULT_PORT_DIMENSION_INFO */

#define MDL_START
static void mdlStart(SimStruct *S) {}
static void mdlOutputs(SimStruct *S, int_T tid) {}
static void mdlTerminate(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{
    uint32_T ModuleId = MOD_ID_ARG;
    uint32_T NodeId = NODE_ID_ARG;
    uint16_T DeviceIndex = DEVICE_INDEX_ARG;
    uint32_T Api = API_ARG;
    uint16_T Slot = SLOT_ARG;
    uint16_T SubSlot = SUBSLOT_ARG;
    uint16_T RecordIndex = RECORD_INDEX_ARG;
    boolean_T Extended = EXTENDED_ARG;
    uint32_T Timeout = TIMEOUT_ARG;

    /* Set work vectors */
    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 2, "Channel", 1, "RecordHandle", 1)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(
            S, 9, SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "DeviceIndex", &DeviceIndex, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "Api", &Api, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "Slot", &Slot, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "SubSlot", &SubSlot, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "RecordIndex", &RecordIndex, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended, DTINFO(SS_BOOLEAN, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "Timeout", &Timeout, DTINFO(SS_UINT32, COMPLEX_NO))) {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h"
