#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_mqtt_client_subscribe_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#include "fixedpoint.h"
#include "fixedpoint.c"
#endif

#include "mqtt_def.h"

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"

#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace mqtt;
#endif

/* Defines */
#define CLIENT_ID_ARG       (uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CONNECTION_ID_ARG   (uint16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define TOPIC_ARG                             ssGetSFcnParam(S, 2)
#define QOS_ARG			     (uint8_T)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define INIT_VALUE_ARG                        ssGetSFcnParam(S, 4)
#define EXTENDED_ARG       (boolean_T)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define SAMPLE_TIME_ARG               mxGetPr(ssGetSFcnParam(S, 6))[0]
#define NUMBER_OF_ARGS                                          7

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Set and check parameters */
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

    /* Check whether init value is specified */
    if (mxIsEmpty(INIT_VALUE_ARG))
    {
        sprintf(ErrMsg, "Init Value parameter must not be empty");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Input ports */
    if (!ssSetNumInputPorts(S, 0)) return;

    /* Output ports */
    if (EXTENDED_ARG)
    {
		if (!ssSetNumOutputPorts(S, 3)) return;
    }
    else
    {
    	if (!ssSetNumOutputPorts(S, 1)) return;
    }

    /* 1. DATA output port */
	/* DATA output port derives type and dimensions from the init value parameter */
	ssSetOutputPortDataType(S, 0, ssGetDTypeIdFromMxArray(INIT_VALUE_ARG));
	ssSetOutputPortWidth(S, 0, mxGetNumberOfElements(INIT_VALUE_ARG));

    if (EXTENDED_ARG)
    {

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

    if (SAMPLE_TIME_ARG == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, SAMPLE_TIME_ARG);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

static void sg_ModelLoad(SimStruct *S) {}
static void sg_ModelStart(SimStruct *S) {}
static void sg_ModelStep(SimStruct *S) {}
static void sg_ModelStop(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct * S) {

    int32_T i = 0;
    uint16_T ConnectionId = CONNECTION_ID_ARG;
    uint16_T ClientId = CLIENT_ID_ARG;
    char *Topic = mxArrayToString(TOPIC_ARG);
    uint8_T QoS = QOS_ARG;
    bool Extended = EXTENDED_ARG;

    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Instance", ssGetNumPWork(S))) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 6,
        SSWRITE_VALUE_DTYPE_NUM, "ClientId", &ClientId, DTINFO(SS_UINT16, COMPLEX_NO),
		SSWRITE_VALUE_DTYPE_NUM, "ConnectionId", &ConnectionId, DTINFO(SS_UINT16, COMPLEX_NO),
		SSWRITE_VALUE_QSTR, "Topic", Topic,
		SSWRITE_VALUE_DTYPE_NUM, "QoS", &QoS, DTINFO(SS_UINT8, COMPLEX_NO),
		SSWRITE_VALUE_DTYPE_NUM, "Extended", &Extended, DTINFO(SS_BOOLEAN, COMPLEX_NO),
		SSWRITE_VALUE_DTYPE_VECT, "InitValue", mxGetPr(INIT_VALUE_ARG), mxGetNumberOfElements(INIT_VALUE_ARG), DTINFO(ssGetDTypeIdFromMxArray(INIT_VALUE_ARG), COMPLEX_NO)
    )) {
        return;
    }

    mxFree(Topic);
}

#endif /* MDL_RTW */

#include "sg_sfcn_glue.h"   // Code generation glue
