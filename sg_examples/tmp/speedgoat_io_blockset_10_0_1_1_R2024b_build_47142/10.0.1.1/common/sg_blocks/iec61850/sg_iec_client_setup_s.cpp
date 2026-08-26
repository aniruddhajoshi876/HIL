#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_iec_client_setup_s

/* Includes */
#include "simstruc.h"
#include <tmwtypes.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#include "iec_def.h"

#ifndef MATLAB_MEX_FILE
#include "iec.h"
#include "iec_client_node.h"
#include "iec_def.h"
#include "iec_root.h"
#include "sg_common.h"
#include "sg_printf.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
// #include <WS2tcpip.h>
#include <IoModuleRegistry.h>
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace iec61850;
#endif

/* Defines */
#define CLIENT_ID_ARG   (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define LOC_IP_ADDR_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SAMPLE_TIME_ARG mxGetPr(ssGetSFcnParam(S, 2))[0]
#define NUMBER_OF_ARGS  3

#define LOC_TCP_PORT_ARG INADDR_ANY

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < 0; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetNumInputPorts(S, 0);
    //	ssSetInputPortWidth(S, 0, 1);
    //	ssSetInputPortDataType(S, 0, SS_UINT8);
    //	ssSetInputPortRequiredContiguous(S, 0, 1);
    //	ssSetInputPortDirectFeedThrough(S, 0, 1);

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
    cClientNode *Node = NULL;

    /* Add a client node */
    ret = Root.addNode(CLIENT_ID_ARG, true, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to add server node %i\n", CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the node */
    ret = Node->init((uint32_t)LOC_IP_ADDR_ARG, LOC_TCP_PORT_ARG);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to initialize client node %i\n", CLIENT_ID_ARG);
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
