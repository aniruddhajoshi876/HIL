#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mqtt_client_connection_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "mqtt.h"
#include "mqtt_def.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace mqtt;
#endif

/* Defines */
#define STATION_ID_ARG    (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CONNECTION_ID_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define IP_ADDR_ARG       (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define TCP_PORT_ARG      (uint16_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define SAMPLE_TIME_ARG   mxGetPr(ssGetSFcnParam(S, 4))[0]
#define USER_AUTH_ARG     (boolean_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define USERNAME_ARG      ssGetSFcnParam(S, 6)
#define PASSWORD_ARG      ssGetSFcnParam(S, 7)
#define NUMBER_OF_ARGS    8

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

    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_BOOLEAN);

    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
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

static void sg_ModelLoad(SimStruct *S) {}
static void sg_ModelStart(SimStruct *S) {}
static void sg_ModelStep(SimStruct *S) {}
static void sg_ModelStop(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct *S)
{

    uint16_T StationId = STATION_ID_ARG;
    uint16_T ConnectionId = CONNECTION_ID_ARG;
    uint32_T IpAddr = IP_ADDR_ARG;
    uint16_T TcpPort = TCP_PORT_ARG;
    uint32_T UBID = 0;
    boolean_T UserAuth = USER_AUTH_ARG;
    char_T *Username = mxArrayToString(USERNAME_ARG);
    char_T *Password = mxArrayToString(PASSWORD_ARG);

    if (!ssWriteRTWScalarParam(S, "UBID", &UBID, SS_UINT32)) {
        return;
    }

    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Instance", ssGetNumPWork(S))) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(
            S, 7, SSWRITE_VALUE_DTYPE_NUM, "StationId", &StationId, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "ConnectionId", &ConnectionId, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "IpAddr", &IpAddr, DTINFO(SS_UINT32, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "TcpPort", &TcpPort, DTINFO(SS_UINT16, COMPLEX_NO),
            SSWRITE_VALUE_DTYPE_NUM, "UserAuth", &UserAuth, DTINFO(SS_BOOLEAN, COMPLEX_NO),
            SSWRITE_VALUE_STR, "Username", Username, SSWRITE_VALUE_STR, "Password", Password)) {
        return;
    }

    mxFree(Username);
    mxFree(Password);
}
#endif /* MDL_RTW */

#include "sg_sfcn_glue.h" // Code generation glue
