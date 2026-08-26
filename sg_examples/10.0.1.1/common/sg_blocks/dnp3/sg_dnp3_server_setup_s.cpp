#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_dnp3_server_setup_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#endif

#include "sg_callback.h"

/* Defines */
#define NETWORK_ID_ARG          (uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define SERVER_ID_ARG       (uint16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define IP_ADDR_ARG             (uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define TCP_PORT_ARG            (uint16_T)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define NUM_DEV_ATTR_ARG        (uint32_T)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define DEV_ATTR_TYPES_ARG                        ssGetSFcnParam(S, 5)
#define DEV_ATTR_VALUES_ARG                       ssGetSFcnParam(S, 6)
#define POINT_CFG_ARG                             ssGetSFcnParam(S, 7)  
#define DEADBAND_ARG            (real32_T)mxGetPr(ssGetSFcnParam(S, 8))[0]
#define NUMBER_OF_ARGS											    9

/* Definitions */
static char_T ErrMsg[256];
char_T* DWorkName = "ErrMsg";

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
    ssSetNumOutputPorts(S, 0);

    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);

    ssSetNumDWork(S, 1);
    ssSetDWorkName(S, 0, DWorkName);
    ssSetDWorkDataType(S, 0, SS_UINT8);
    ssSetDWorkWidth(S, 0, 256);

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP); 
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
	ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
	ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

static void sg_ModelLoad(SimStruct *S) {}
static void sg_ModelStart(SimStruct *S) {}
static void sg_ModelStep(SimStruct *S) {}
static void sg_ModelStop(SimStruct *S) {}

#define MDL_RTW
#if defined(MDL_RTW) && (defined(MATLAB_MEX_FILE) || defined(NRT))
static void mdlRTW(SimStruct * S) {

    int32_T i = 0;
    uint16_T NetworkId = NETWORK_ID_ARG;
    uint16_T ServerId = SERVER_ID_ARG;
    uint32_T IpAddr = IP_ADDR_ARG;
    uint16_T TcpPort = TCP_PORT_ARG;
    uint32_T NumDevAttr = NUM_DEV_ATTR_ARG;
    real32_T Deadband = DEADBAND_ARG;
    uint32_T PointConfig[12] = { 0 };

    char_T* DevAttrTypes = mxArrayToString(DEV_ATTR_TYPES_ARG);
    char_T* DevAttrValues = mxArrayToString(DEV_ATTR_VALUES_ARG);

    if (!ssWriteRTWScalarParam(S, "NumDevAttr", &NumDevAttr, SS_UINT32)) {
        return;
    }

    if (NumDevAttr > 0)
    {
        if (!ssWriteRTWStrVectParam(S, "DevAttrTypes", DevAttrTypes, NumDevAttr)) {
            return;
        }

        if (!ssWriteRTWStrVectParam(S, "DevAttrValues", DevAttrValues, NumDevAttr)) {
            return;
        }
    }

    for (i = 0; i < 12; i++)
    {
        PointConfig[i] = (uint32_T)mxGetPr(POINT_CFG_ARG)[i];
    }

    /* Set parameters */
    if (!ssWriteRTWParamSettings(S, 6,
        SSWRITE_VALUE_DTYPE_NUM, "NetworkID", &NetworkId, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "ServerID", &ServerId, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "IpAddr", &IpAddr, DTINFO(SS_UINT32, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "TcpPort", &TcpPort, DTINFO(SS_UINT16, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_NUM, "Deadband", &Deadband, DTINFO(SS_SINGLE, COMPLEX_NO),
        SSWRITE_VALUE_DTYPE_VECT, "PointConfig", &PointConfig, 12, DTINFO(SS_UINT32, COMPLEX_NO)
    )) {
        return;
    }
}
#endif /* MDL_RTW */

#include "sg_sfcn_glue.h"   // Code generation glue
