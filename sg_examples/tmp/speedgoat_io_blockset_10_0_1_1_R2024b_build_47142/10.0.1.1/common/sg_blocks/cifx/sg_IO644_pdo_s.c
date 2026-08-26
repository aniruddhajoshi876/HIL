#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO644_pdo_s

/* Includes */
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* Defines */
#define MOD_ID_ARG              (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG          (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[1]
#define PDO_TYPE_ARG               (uint8_T)mxGetScalar(ssGetSFcnParam(S, 1))
#define PDO_ID_ARG            (uint16_T)mxGetScalar(ssGetSFcnParam(S, 2))
#define COB_ID_ARG            (uint32_T)mxGetScalar(ssGetSFcnParam(S, 3))
#define MAP_ARG            ssGetSFcnParam(S, 4)
#define TRANS_TYPE_ARG                            (uint8_T)mxGetScalar(ssGetSFcnParam(S, 5))
#define TRANS_RATE_ARG            (uint8_T)mxGetScalar(ssGetSFcnParam(S, 6))
#define INHIBIT_TIME            (uint16_T)mxGetScalar(ssGetSFcnParam(S, 7))
#define EVENT_TIMER            (uint32_T)mxGetScalar(ssGetSFcnParam(S, 8))
#define SYNC_START_ARG                           (uint8_T)mxGetScalar(ssGetSFcnParam(S, 9))
#define NUMBER_OF_ARGS                                              10

/* Definitions */
static char_T ErrMsg[512];

/* mdlInitializeSizes */
static void mdlInitializeSizes(SimStruct* S)
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

    /* Set all parameters to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    if (!ssSetNumOutputPorts(S, 0)) return;
    if (!ssSetNumInputPorts(S, 0)) return;

    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

/* mdlInitializeSampleTimes */
static void mdlInitializeSampleTimes(SimStruct* S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

/* mdlSetWorkWidths */
#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct* S)
{
    if (!mxIsEmpty(MAP_ARG))
    {
        ssSetNumRunTimeParams(S, 1);
        ssRegDlgParamAsRunTimeParam(S, 4, 0, "Map_P", ssGetDTypeIdFromMxArray(MAP_ARG));
    }
}

static void mdlStart(SimStruct* S) {}
static void mdlOutputs(SimStruct* S, int_T tid) {}
static void mdlTerminate(SimStruct* S) {}

/* mdlRTW */
#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct* S) {
    
    uint32_T Dummy = 0;
    uint32_T ModuleId = MOD_ID_ARG;
    uint32_T NodeId = NODE_ID_ARG;
    uint8_T PdoType = PDO_TYPE_ARG;
    uint16_T PdoId = PDO_ID_ARG;
    uint32_T CobId = COB_ID_ARG;
    uint8_T TransType = TRANS_TYPE_ARG;
    uint8_T TransRate = TRANS_RATE_ARG;
    uint16_T InhibitTime = INHIBIT_TIME;
    uint16_T EventTimer = EVENT_TIMER;
    uint8_T SyncStart = SYNC_START_ARG;
    
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

    if (!ssWriteRTWScalarParam(S, "CosPdoIdx", &Dummy, SS_INT32)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 10,
        SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "PdoType", &PdoType, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "PdoId", &PdoId, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "CobId", &CobId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "TransType", &TransType, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "TransRate", &TransRate, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "InhibitTime", &InhibitTime, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "EventTimer", &EventTimer, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "SyncStart", &SyncStart, DTINFO(SS_UINT8, COMPLEX_NO)
    )) {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h"   
