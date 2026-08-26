#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_opcua_client_connection_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "opcua_def.h"
#include "opcua.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace opcua;
#endif

/* Defines */
#define CLIENT_ID_ARG          	(uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CONNECTION_ID_ARG       (uint16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define IP_ADDR_ARG          	                  ssGetSFcnParam(S, 2)
#define TCP_PORT_ARG          	(uint16_T)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define SAMPLE_TIME_ARG         		  mxGetPr(ssGetSFcnParam(S, 4))[0]
#define SECURITY_POLICY_ARG		 (uint8_T)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define MSG_SECURITY_MODE_ARG	 (uint8_T)mxGetPr(ssGetSFcnParam(S, 6))[0]
#define USER_TOKEN_POLICY_ARG	 (uint8_T)mxGetPr(ssGetSFcnParam(S, 7))[0]
#define USERNAME_ARG			                  ssGetSFcnParam(S, 8)
#define PASSWORD_ARG			                  ssGetSFcnParam(S, 9)
#define CERTIFICATE_ARG			                 ssGetSFcnParam(S, 10)
#define PRIVATE_KEY_ARG							 ssGetSFcnParam(S, 11)
#define APP_URI_ARG			                     ssGetSFcnParam(S, 12)
#define NUMBER_OF_ARGS											   13

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

    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 3);
    ssSetOutputPortDataType(S, 0, SS_UINT32);

    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumDWork(S, 0);

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP); 
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
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

    uint16_T ClientId = CLIENT_ID_ARG;
    uint16_T ConnectionId = CONNECTION_ID_ARG;
    char_T *IpAddr = mxArrayToString(IP_ADDR_ARG);
    uint16_T TcpPort = TCP_PORT_ARG;
    uint32_T UBID = 0;
    uint8_T SecurityPolicy = SECURITY_POLICY_ARG;
    uint8_T MessageSecurityMode = MSG_SECURITY_MODE_ARG;
    uint8_T UserTokenPolicy = USER_TOKEN_POLICY_ARG;
    char_T *Username = mxArrayToString(USERNAME_ARG);
    char_T *Password = mxArrayToString(PASSWORD_ARG);
    char_T *Certificate = mxArrayToString(CERTIFICATE_ARG);
    char_T *PrivateKey = mxArrayToString(PRIVATE_KEY_ARG);
    char_T *AppUri = mxArrayToString(APP_URI_ARG);

    if (!ssWriteRTWScalarParam(S, "UBID", &UBID, SS_UINT32)) {
        return;
    }

    if (!ssWriteRTWWorkVect(S, "PWork", 1, "Instance", ssGetNumPWork(S))) {
        return;
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 12,
        SSWRITE_VALUE_DTYPE_NUM, "ClientID", &ClientId, DTINFO(SS_UINT16, COMPLEX_NO),
		SSWRITE_VALUE_DTYPE_NUM, "ConnectionID", &ConnectionId, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_QSTR, "IpAddr", IpAddr,
        SSWRITE_VALUE_DTYPE_NUM, "TcpPort", &TcpPort, DTINFO(SS_UINT16, COMPLEX_NO),
		SSWRITE_VALUE_DTYPE_NUM, "SecurityPolicy", &SecurityPolicy, DTINFO(SS_UINT8, COMPLEX_NO),
		SSWRITE_VALUE_DTYPE_NUM, "MessageSecurityMode", &MessageSecurityMode, DTINFO(SS_UINT8, COMPLEX_NO),
		SSWRITE_VALUE_DTYPE_NUM, "UserTokenPolicy", &UserTokenPolicy, DTINFO(SS_UINT8, COMPLEX_NO),
		SSWRITE_VALUE_STR , "Username", Username,
		SSWRITE_VALUE_STR , "Password", Password,
		SSWRITE_VALUE_STR , "Certificate", Certificate,
		SSWRITE_VALUE_STR , "PrivateKey", PrivateKey,
		SSWRITE_VALUE_STR , "AppUri", AppUri
    )) {
        return;
    }

    mxFree(IpAddr);
    mxFree(Username);
    mxFree(Password);
    mxFree(Certificate);
    mxFree(PrivateKey);
    mxFree(AppUri);
}
#endif /* MDL_RTW */

#include "sg_sfcn_glue.h"   // Code generation glue
