#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_ecatsim_object_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* Defines */
#define IF_ID_ARG         (uint32_T) mxGetScalar(ssGetSFcnParam(S, 0))
#define SLAVE_ADDRESS_ARG (uint32_T) mxGetScalar(ssGetSFcnParam(S, 1))
#define INDEX_ARG         (uint32_T) mxGetScalar(ssGetSFcnParam(S, 2))
#define SUBINDEX_ARG      (uint32_T) mxGetScalar(ssGetSFcnParam(S, 3))
#define INIT_VALUE_ARG    ssGetSFcnParam(S, 4)
#define READ_OP_ARG       (boolean_T) mxGetScalar(ssGetSFcnParam(S, 5))
#define WRITE_OP_ARG      (boolean_T) mxGetScalar(ssGetSFcnParam(S, 6))
#define EXTENDED_ARG      (boolean_T) mxGetScalar(ssGetSFcnParam(S, 7))
#define SAMPLE_TIME_ARG   ssGetSFcnParam(S, 8)

#define NUM_ARGS 9

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
    if (WRITE_OP_ARG) {
        NumInputPorts++;
        if (EXTENDED_ARG) {
            NumInputPorts++;
            NumInputPorts++;
        }
    }
    if (READ_OP_ARG) {
        NumOutputPorts++;
        if (EXTENDED_ARG) {
            NumOutputPorts++;
            NumOutputPorts++;
        }
    }

    /* Configure input ports */
    if (!ssSetNumInputPorts(S, NumInputPorts))
        return;

    if (WRITE_OP_ARG) {
        ssSetInputPortDataType(S, PortIndex, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
        ssSetInputPortWidth(S, PortIndex, mxGetNumberOfElements(INIT_VALUE_ARG));
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

    if (READ_OP_ARG) {
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
    ssRegDlgParamAsRunTimeParam(S, 4, 0, "InitValue",
                                ssGetDTypeIdFromMxArray(ssGetSFcnParam(S, 4)));
}

static void mdlStart(SimStruct *S) {}
static void mdlOutputs(SimStruct *S, int_T tid) {}
static void mdlTerminate(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{
    uint32_T InterfaceId = IF_ID_ARG;
    uint32_T SlaveAddress = SLAVE_ADDRESS_ARG;
    uint32_T ObjIndex = INDEX_ARG;
    uint32_T ObjSubIndex = SUBINDEX_ARG;
    boolean_T ReadOp = READ_OP_ARG;
    boolean_T WriteOp = WRITE_OP_ARG;
    boolean_T Extended = EXTENDED_ARG;

    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Object", 1)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(
            S, 7, SSWRITE_VALUE_DTYPE_NUM, "InterfaceId", &InterfaceId,
            DTINFO(SS_UINT32, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "SlaveAddress", &SlaveAddress,
            DTINFO(SS_UINT32, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "ObjIndex", &ObjIndex,
            DTINFO(SS_UINT32, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "ObjSubIndex", &ObjSubIndex,
            DTINFO(SS_UINT32, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "ReadOp", &ReadOp,
            DTINFO(SS_BOOLEAN, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "WriteOp", &WriteOp,
            DTINFO(SS_BOOLEAN, COMPLEX_NO), SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended,
            DTINFO(SS_BOOLEAN, COMPLEX_NO))) {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h" // Code generation glue
