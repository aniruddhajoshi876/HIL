#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO644_netstate_v2_s

/* Includes */
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "matrix.h"
#include "mex.h"
#endif

/* Defines */
#define MOD_ID_ARG      (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG     (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define STATE_CTRL_ARG  (boolean_T) mxGetScalar(ssGetSFcnParam(S, 1))
#define STATE_IND_ARG   (boolean_T) mxGetScalar(ssGetSFcnParam(S, 2))
#define EXT_DIAG_ARG    (boolean_T) mxGetScalar(ssGetSFcnParam(S, 3))
#define MONITORING_ARG  (boolean_T) mxGetScalar(ssGetSFcnParam(S, 4))
#define SAMPLE_TIME_ARG ssGetSFcnParam(S, 5)
#define NUMBER_OF_ARGS  6

/* Definitions */
static char_T ErrMsg[1024];

/* mdlInitializeSizes */
static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;
    uint32_T NumInPorts = 0;
    uint32_T NumOutPorts = 1;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    if (STATE_CTRL_ARG != 0)
        NumInPorts += 1;
    if (STATE_IND_ARG != 0)
        NumOutPorts += 1;
    if (EXT_DIAG_ARG != 0)
        NumOutPorts += 1;
    if (MONITORING_ARG != 0)
        NumOutPorts += 1;

    if (!ssSetNumInputPorts(S, NumInPorts))
        return;
    if (!ssSetNumOutputPorts(S, NumOutPorts))
        return;

    if (STATE_CTRL_ARG) {
        ssSetInputPortWidth(S, 0, 1);
        ssSetInputPortDataType(S, 0, SS_UINT32);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
    }

    i = 0;
    ssSetOutputPortWidth(S, i, 1);
    ssSetOutputPortDataType(S, i, SS_UINT32);
    i++;

    if (STATE_IND_ARG) {
        ssSetOutputPortWidth(S, i, 1);
        ssSetOutputPortDataType(S, i, SS_UINT32);
        i++;
    }

    if (EXT_DIAG_ARG) {
        ssSetOutputPortWidth(S, i, 13);
        ssSetOutputPortDataType(S, i, SS_UINT32);
        i++;
    }

    if (MONITORING_ARG) {
        ssSetOutputPortWidth(S, i, 128);
        ssSetOutputPortDataType(S, i, SS_UINT32);
    }

    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

/* mdlInitializeSampleTimes */
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

static void mdlStart(SimStruct *S) {}
static void mdlOutputs(SimStruct *S, int_T tid) {}
static void mdlTerminate(SimStruct *S) {}

/* mdlRTW */
#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{

    uint32_T ModuleId = MOD_ID_ARG;
    uint32_T NodeId = NODE_ID_ARG;
    boolean_T StateCtrl = STATE_CTRL_ARG;
    boolean_T StateInd = STATE_IND_ARG;
    boolean_T ExtDiag = EXT_DIAG_ARG;
    boolean_T Monitoring = MONITORING_ARG;

    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Channel", ssGetNumPWork(S))) {
        return;
    }

    // if (!ssWriteRTWScalarParam(S, "CosBlockIdx", &Dummy, SS_INT32)) {
    //     return;
    // }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(
            S, 6, SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "StateCtrl", &StateCtrl, DTINFO(SS_BOOLEAN, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "StateInd", &StateInd, DTINFO(SS_BOOLEAN, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "ExtDiag", &ExtDiag, DTINFO(SS_BOOLEAN, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "Monitoring", &Monitoring, DTINFO(SS_BOOLEAN, COMPLEX_NO))) {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h"
