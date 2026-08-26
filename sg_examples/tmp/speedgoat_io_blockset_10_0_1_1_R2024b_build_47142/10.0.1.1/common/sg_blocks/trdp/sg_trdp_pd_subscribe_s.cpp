#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_trdp_pd_subscribe_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "fixedpoint.c"
#include "fixedpoint.h"
#include "mex.h"
#endif

#include "trdp_def.h"

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"

#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace ns_sg_trdp;
#endif

/* Defines */
#define STATION_ID_ARG      (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
// 1
#define COM_ID_ARG          (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define DEST_IP_ADDR_ARG    (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define TIMEOUT_ARG         (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define PULL_ARG            (boolean_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define SRC_IP_ADDR_ARG     (uint32_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define INIT_VALUE_ARG  ssGetSFcnParam(S, 7)
#define EXTENDED_ARG    (boolean_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define SAMPLE_TIME_ARG mxGetPr(ssGetSFcnParam(S, 9))[0]
#define NUMBER_OF_ARGS  10

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Set and check parameters */
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

    /* Check whether init value is specified */
    if (mxIsEmpty(INIT_VALUE_ARG)) {
        sprintf(ErrMsg, "Init Value parameter must not be empty");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Input ports */
    if (PULL_ARG) {
        if (!ssSetNumInputPorts(S, 1))
            return;
    } else {
        if (!ssSetNumInputPorts(S, 0))
            return;
    }

    if (PULL_ARG)
    {
        /* 1. PULL input port */
        ssSetInputPortDataType(S, 0, SS_BOOLEAN);
        ssSetInputPortWidth(S, 0, 1);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
    }

    /* Output ports */
    if (EXTENDED_ARG) {
        if (!ssSetNumOutputPorts(S, 3))
            return;
    } else {
        if (!ssSetNumOutputPorts(S, 1))
            return;
    }

    /* 1. DATA output port */
    /* DATA output port derives type and dimensions from the init value parameter */
    ssSetOutputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
    ssSetOutputPortWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));

    if (EXTENDED_ARG) {

        /* 2. STATUS output port */
        ssSetOutputPortDataType(S, 1, SS_UINT32);
        ssSetOutputPortWidth(S, 1, 1);

        /* 3. DATA LENGTH output port */
        ssSetOutputPortDataType(S, 2, SS_UINT32);
        ssSetOutputPortWidth(S, 2, 1);
    }

    /* DWork Vectors */
    ssSetNumDWork(S, 1);
    ssSetDWorkName(S, 0, "Buffer");
    ssSetDWorkDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
    ssSetDWorkWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));

    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetModelReferenceSampleTimeInheritanceRule(S, USE_DEFAULT_FOR_DISCRETE_INHERITANCE);

    if (SAMPLE_TIME_ARG == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else {
        ssSetSampleTime(S, 0, SAMPLE_TIME_ARG);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct *S)
{
    ssSetNumRunTimeParams(S, 1);
    ssRegDlgParamAsRunTimeParam(S, 7, 0, "InitValue",
                                ssGetDTypeIdFromMxArray(ssGetSFcnParam(S, 7)));
}

static void sg_ModelLoad(SimStruct *S) {}
static void sg_ModelStart(SimStruct *S) {}
static void sg_ModelStep(SimStruct *S) {}
static void sg_ModelStop(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{

    int32_T i = 0;
    uint16_T StationId = STATION_ID_ARG;
    uint32_T ComId = COM_ID_ARG;
    uint32_T DestIpAddr = DEST_IP_ADDR_ARG;
    uint32_T SrcIpAddr = SRC_IP_ADDR_ARG;
    uint32_T Timeout = TIMEOUT_ARG;
    bool Pull = PULL_ARG;
    bool Extended = EXTENDED_ARG;

    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Instance", ssGetNumPWork(S))) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(
        S, 7, SSWRITE_VALUE_DTYPE_NUM, "StationId", &StationId, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ComId", &ComId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "DestIpAddr", &DestIpAddr, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "SrcIpAddr", &SrcIpAddr, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Timeout", &Timeout, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Pull", &Pull, DTINFO(SS_BOOLEAN, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended, DTINFO(SS_BOOLEAN, COMPLEX_NO))) {
        return;
    }
}

#endif /* MDL_RTW */

#include "sg_sfcn_glue.h" // Code generation glue
