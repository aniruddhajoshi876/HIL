#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_dnp3_client_setup_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "dnp3.h"
#include "dnp3_api.h"
#include "dnp3_root.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace dnp3;
#endif

/* Defines */
#define NETWORK_ID_ARG          (uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CLIENT_ID_ARG          (uint16_T)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define IP_ADDR_ARG          (uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define KEEP_ALIVE_ARG          (uint32_T)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define RX_TIMEOUT_ARG            (uint32_T)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define DL_RETRIES_ARG              (uint8_T)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define SERVER_CFG_ARG						  ssGetSFcnParam(S, 6)
#define SAMPLE_TIME_ARG         mxGetPr(ssGetSFcnParam(S, 7))[0]
#define NUMBER_OF_ARGS											8

#define SERVER_ID(i)	((uint32_T)(mxGetPr(SERVER_CFG_ARG)[i + 0 * (int_T)mxGetM(SERVER_CFG_ARG)]))
#define SERVER_IP(i)		((uint32_T)(mxGetPr(SERVER_CFG_ARG)[i + 1 * (int_T)mxGetM(SERVER_CFG_ARG)]))
#define SERVER_PORT(i)		((uint32_T)(mxGetPr(SERVER_CFG_ARG)[i + 2 * (int_T)mxGetM(SERVER_CFG_ARG)]))

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
    for (i = 0; i < 0; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetNumInputPorts(S, 0);

    if (mxGetM(SERVER_CFG_ARG) > 0)
    {
        ssSetNumOutputPorts(S, 1);
        ssSetOutputPortWidth(S, 0, (int_T)mxGetM(SERVER_CFG_ARG));
        ssSetOutputPortDataType(S, 0, SS_UINT8);
    } else
    {
        ssSetNumOutputPorts(S, 0);
    }

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
    if (SAMPLE_TIME_ARG == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else
    {
        ssSetSampleTime(S, 0, SAMPLE_TIME_ARG);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

static void sg_ModelLoad(SimStruct *S) {
#ifndef MATLAB_MEX_FILE

    Root.init();

#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    int32_t ret = 0;
    uint32_T i = 0;
    cClientStation *Station = NULL;

    /* Add a station to the network */
    ret = Root.addStation(CLIENT_ID_ARG, true, (cStation **)&Station);
    if (ret != 0)
    {
        sprintf(ErrMsg, "DNP3 | Failed to add station %i", CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the station */
    ret = Station->init(IP_ADDR_ARG);
    if (ret != 0)
    {
        sprintf(ErrMsg, "Failed to initialize station %i", CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* For each server in table */
    for (i = 0; i < mxGetM(SERVER_CFG_ARG); i++)
    {
        cConnection *Connection = NULL;

        /* Add a connection to the station */
        ret = Station->addConnection(SERVER_ID(i), (cConnection **)&Connection);
        if (ret != 0)
        {
            sprintf(ErrMsg, "DNP3 | Failed to add connection %i to station %i", SERVER_ID(i), CLIENT_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        Connection->KeepAlive = KEEP_ALIVE_ARG;
        Connection->RxTimeout = RX_TIMEOUT_ARG;

        /* Initialize the connection */
        ret = Connection->init(Station->LocalIpAddr, 0, SERVER_IP(i), SERVER_PORT(i));
        if (ret != 0)
        {
            sprintf(ErrMsg, "DNP3 | Failed to initialize connection %i of station %i", SERVER_ID(i), CLIENT_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    ssSetPWorkValue(S, 0, Station);

#endif

}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    cClientStation *Station = (cClientStation *)ssGetPWorkValue(S, 0);

    static bool FirstStep = true;
    static uint64_t StartDelayTimer = 0;
    if (FirstStep)
    {
        StartDelayTimer = dnp3::getTime();
        FirstStep = false;
    }
    if ((dnp3::getTime() - StartDelayTimer) > 1000)
    {
        dnp3::Root.launch();
    }

    if (mxGetM(SERVER_CFG_ARG) > 0)
    {
        Station->getStationStatus((uint8_T *)ssGetOutputPortSignal(S, 0), (uint16_T)ssGetOutputPortWidth(S, 0));
    }

#endif
}

static void sg_ModelStop(SimStruct *S)
{
}

static void sg_ModelExit(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    Root.stop();
#endif
}

#include "sg_sfcn_glue.h"   // Code generation glue
