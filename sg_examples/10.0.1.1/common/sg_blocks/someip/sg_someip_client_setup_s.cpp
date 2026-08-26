#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_someip_client_setup_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "someip_def.h"

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "someip_api.h"
#include "someip_client_station_api.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace sg_ns_someip;
#endif

/* Defines */
#define STATION_ID_ARG  (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define IP_ADDR_ARG     (uint32_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SAMPLE_TIME_ARG mxGetPr(ssGetSFcnParam(S, 2))[0]
#define NUMBER_OF_ARGS  3

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
    for (i = 0; i < 0; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 0);

    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 1);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (SAMPLE_TIME_ARG == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else {
        ssSetSampleTime(S, 0, SAMPLE_TIME_ARG);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S) {}

static void sg_ModelStart(SimStruct *S)
{
    int32_t ret = 0;
    cClientStationApi *Station = NULL;

    SgSomeIp->init();

    /* Add a station */
    ret = SgSomeIp->addStation(STATION_ID_ARG, SOMIEIP_STATION_TYPE_CLIENT, (void **)&Station);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding SOME IP station %i!", ret, STATION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the station */
    ret = Station->init(IP_ADDR_ARG, 0);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while initializing client station %i!", ret, STATION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Station);
}

static void sg_ModelStep(SimStruct *S) { SgSomeIp->start(); }

static void sg_ModelStop(SimStruct *S) { SgSomeIp->stop(); }
#endif

#include "sg_sfcn_glue.h" // Code generation glue
