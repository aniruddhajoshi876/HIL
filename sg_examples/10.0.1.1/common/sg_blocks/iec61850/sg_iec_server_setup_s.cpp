#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_iec_server_setup_s

/* Includes */
#include "simstruc.h"
#include <tmwtypes.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#include <sstream>
#include <string>
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#include "iec_def.h"

#ifndef MATLAB_MEX_FILE
#include "iec.h"
#include "iec_server_node.h"
#include "sg_common.h"
#include "sg_printf.h"
#include <array>
#include <sstream>
#include <string>
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace iec61850;
#endif

using namespace std;
/* Defines */
#define SERVER_ID_ARG     (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define IP_ADDR_ARG       (uint32_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define TCP_PORT_ARG      (uint16_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define ENABLER_ARG       ssGetSFcnParam(S, 3)
#define AUTHENTICATE_ARG  (boolean_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define KEEP_ALIVE_ARG    (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define ACCESS_POLICY_ARG ssGetSFcnParam(S, 6)
#define SAMPLE_TIME_ARG   mxGetPr(ssGetSFcnParam(S, 7))[0]
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
    for (i = 0; i < 0; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetNumInputPorts(S, 0);

    ssSetNumOutputPorts(S, 0);
    //    ssSetOutputPortWidth(S, 0, 1);
    //    ssSetOutputPortDataType(S, 0, SS_INT32);

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

static void sg_ModelLoad(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    Root.init();
#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    int32_t ret = 0;
    cServerNode *Node = NULL;

    /* Add a server node */
    ret = Root.addNode(SERVER_ID_ARG, false, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to add server node %i\n", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // std::string stringr = "";
    // if (AUTHENTICATE_ARG) {
    //     char_T *Interface;
    //     Interface = (char_T *)malloc(mxGetN(ENABLER_ARG) + 1);
    //     if (mxGetString(ENABLER_ARG, Interface, 1 + mxGetN(ENABLER_ARG)) != 0) {
    //         sprintf(ErrMsg, "Unable to read authentication parameter");
    //         ssSetErrorStatus(S, ErrMsg);
    //         return;
    //     }
    //     std::stringstream ssr(Interface);
    //     while (getline(ssr, stringr, '\n')) {
    //         SG_PRINTF_INFO("MMS Server(%d) inputed password: '%s'\n", Node->ID,
    //         stringr.c_str());
    //     }
    // }

    std::array<int, 19> AccessPolicy = {1};
    // for (int i = 0; i < (int)mxGetN(ACCESS_POLICY_ARG); i++) {
    //     AccessPolicy[i] = (uint8_T)mxGetPr(ACCESS_POLICY_ARG)[i];
    //     SG_PRINTF_DEBUG("AccessPolicy %d\n", AccessPolicy[i]);
    // }

    /* Initialize the node */
    ret =
        Node->init(IP_ADDR_ARG, TCP_PORT_ARG, KEEP_ALIVE_ARG, AUTHENTICATE_ARG, NULL, AccessPolicy);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to initialize server node %i\n", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Node);
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    /* Start background thread */
    {
        static bool FirstStep = true;
        static uint64_t StartDelayTimer = 0;
        if (FirstStep) {
            StartDelayTimer = getMilliCounter();
            FirstStep = false;
        }
        if ((getMilliCounter() - StartDelayTimer) > 100) {
            Root.launch();
        }
    }

    /* Stop model execution if required */
    if (Root.IsFaulty == true) {

        sprintf(ErrMsg, "MMS | Runtime error\n");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif
}

static void sg_ModelExit(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    Root.stop();

#endif
}
#include "sg_sfcn_glue.h" // Code generation glue
