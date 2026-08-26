#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbtcp_client_setup_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "mb_def.h"

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#ifndef MATLAB_MEX_FILE
#include "mbtcp.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace modbusTCP;
#endif

/* Defines */
#define CLIENT_ID_ARG   (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
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

static void sg_ModelLoad(SimStruct *S) { Root.init(); }

static void sg_ModelStart(SimStruct *S)
{
    int32_t ret = 0;
    cClientNode *Node = NULL;

    /* Add a client node */
    ret = Root.addNode(CLIENT_ID_ARG, true, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus client node %i!", ret, CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the node */
    ret = Node->init(IP_ADDR_ARG, 0);
    if (ret != 0) {
        if (ret == MB_ERROR_LICENSE) {
            sprintf(ErrMsg, "Error: not enough licenses for Modbus TCP Client!\nPlease contact "
                    "Speedgoat Support at:\nsupport@speedgoat.com");
            ssSetErrorStatus(S, ErrMsg);
            return;
        } else {
            sprintf(ErrMsg, "Error %i while initializing client node %i!", ret, CLIENT_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    ssSetPWorkValue(S, 0, Node);
}

static void sg_ModelStep(SimStruct *S)
{
    if (Root.Stop) {
        ssSetStopRequested(S, 1);
    }
    {
        static bool FirstStep = true;
        static uint64_t StartDelayTimer = 0;
        if (FirstStep) {
            StartDelayTimer = getTime();
            FirstStep = false;
        }
        if ((getTime() - StartDelayTimer) > 1000) {
            Root.Run = true;
        }
    }
}

static void sg_ModelStop(SimStruct *S)
{
    Root.Run = false;
}

static void sg_ModelExit(SimStruct *S)
{
    Root.terminate();
}
#endif

#include "sg_sfcn_glue.h" // Code generation glue
