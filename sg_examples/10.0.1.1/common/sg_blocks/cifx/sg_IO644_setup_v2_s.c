#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO644_setup_v2_s

/* Includes */
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

/* Defines */
#define MOD_ID_ARG           (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG          (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[1]
#define BUS_ARG				  (int16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SLOT_ARG			  (int16_T)mxGetPr(ssGetSFcnParam(S, 1))[1] 
#define CO_NODE_ID_ARG		 (uint32_T)mxGetScalar(ssGetSFcnParam(S, 2))
#define BAUD_RATE_ARG       (uint32_T)mxGetScalar(ssGetSFcnParam(S, 3))
#define VENDOR_ID_ARG       (uint32_T)mxGetScalar(ssGetSFcnParam(S, 4))
#define PRODUCT_CODE_ARG    (uint32_T)mxGetScalar(ssGetSFcnParam(S, 5))
#define REV_NUMBER_ARG      (uint32_T)mxGetScalar(ssGetSFcnParam(S, 6))
#define HB_PRODUCER_ARG           (uint16_T)mxGetScalar(ssGetSFcnParam(S, 7))
#define HB_CONSUMER_ARG           ssGetSFcnParam(S, 8)
#define GUARD_TIME_ARG           (uint16_T)mxGetScalar(ssGetSFcnParam(S, 9))
#define LIFE_TIME_FACTOR_ARG           (uint8_T)mxGetScalar(ssGetSFcnParam(S, 10))
#define DEVICE_TYPE_ARG       (uint32_T)mxGetScalar(ssGetSFcnParam(S, 11))

#define NUMBER_OF_ARGS											12

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

    /* Set all parameters to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    if (!ssSetNumInputPorts(S, 0)) 
        return;
    if (!ssSetNumOutputPorts(S, 0)) 
        return;

    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);

    /* SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME prevents the block from being eliminated by the 
     * Simulink Coder in case the model parameter option is INLINED or input and output ports 
     * are not connected */
    ssSetOptions(S, SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME | SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP); 
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
	ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
	ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

/* mdlSetWorkWidths */
#define MDL_SET_WORK_WIDTHS
void mdlSetWorkWidths(SimStruct* S)
{
    if (!mxIsEmpty(HB_CONSUMER_ARG))
    {
        ssSetNumRunTimeParams(S, 1);
        ssRegDlgParamAsRunTimeParam(S, 8, 0, "HBC_P", ssGetDTypeIdFromMxArray(HB_CONSUMER_ARG));
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
    int16_T Bus = BUS_ARG;
    int16_T Slot = SLOT_ARG;
    uint32_T CoNodeId = CO_NODE_ID_ARG;
    uint32_T BaudRate = BAUD_RATE_ARG;
    uint32_T VendorId = VENDOR_ID_ARG;
    uint32_T ProductCode = PRODUCT_CODE_ARG;
    uint32_T RevNum = REV_NUMBER_ARG;
    uint16_T HbProducer = HB_PRODUCER_ARG;
    uint16_T GuardTime = GUARD_TIME_ARG;
    uint8_T LifeTimeFactor = LIFE_TIME_FACTOR_ARG;
    uint32_T DeviceType = DEVICE_TYPE_ARG;

    /* Set work vectors */
    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Channel", ssGetNumPWork(S))) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosBlockIdx", &Dummy, SS_UINT32)) {
        return;
    }

    if (!ssWriteRTWScalarParam(S, "CosModuleIdx", &Dummy, SS_INT32)) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 13,
        SSWRITE_VALUE_DTYPE_NUM, "ModuleId", &ModuleId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "NodeId", &NodeId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Bus", &Bus, DTINFO(SS_INT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Slot", &Slot, DTINFO(SS_INT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "CoNodeId", &CoNodeId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "BaudRate", &BaudRate, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "VendorId", &VendorId, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ProductCode", &ProductCode, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "RevNum", &RevNum, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "HbProducer", &HbProducer, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "GuardTime", &GuardTime, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "LifeTimeFactor", &LifeTimeFactor, DTINFO(SS_UINT8, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "DeviceType", &DeviceType, DTINFO(SS_UINT32, COMPLEX_NO)
    )) {
        return;
    }
}
#endif

#include "sg_sfcn_glue.h"   
