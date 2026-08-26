#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbtcp_server_setup_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#include "mb_def.h"

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
#define SERVER_ID_ARG      (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define IP_ADDR_ARG        (uint32_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define TCP_PORT_ARG       (uint16_t)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define KEEP_ALIVE_ARG     (uint32_t)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define UNIT_ID_ARG        ssGetSFcnParam(S, 4)
#define TABLE_DIM_ARG      ssGetSFcnParam(S, 5)
#define SAMPLE_TIME_ARG    mxGetPr(ssGetSFcnParam(S, 6))[0]
#define SWAP_ARG           (bool)mxGetPr(ssGetSFcnParam(S, 7))[0]
#define RESPONSE_DELAY_ARG (uint32_t)mxGetPr(ssGetSFcnParam(S, 8))[0]
#define NUMBER_OF_ARGS     9

#define NUM_COIL_ARG(i) ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 0 * (int32_t)mxGetM(TABLE_DIM_ARG)]))
#define NUM_DISCRETE_ARG(i)                                                                        \
    ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 1 * (int32_t)mxGetM(TABLE_DIM_ARG)]))
#define NUM_HOLDING_ARG(i)                                                                         \
    ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 2 * (int32_t)mxGetM(TABLE_DIM_ARG)]))
#define NUM_INPUT_ARG(i)                                                                           \
    ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 3 * (int32_t)mxGetM(TABLE_DIM_ARG)]))

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
    ssSetOutputPortDataType(S, 0, SS_UINT16);

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
    uint32_t i = 0;
    cServerNode *Node = NULL;

    /* Add a server node */
    ret = Root.addNode(SERVER_ID_ARG, false, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus server node %i!", ret, SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the node */
    ret = Node->init(IP_ADDR_ARG, TCP_PORT_ARG, KEEP_ALIVE_ARG, SWAP_ARG, RESPONSE_DELAY_ARG);
    if (ret != 0) {
        if (ret == MB_ERROR_LICENSE) {
            sprintf(ErrMsg, "Error: not enough licenses for Modbus TCP Server!\nPlease contact "
                    "Speedgoat Support at:\nsupport@speedgoat.com");
            ssSetErrorStatus(S, ErrMsg);
            return;
        } else {
            sprintf(ErrMsg, "Error %i while initializing server node %i!", ret, SERVER_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    /* For each unit */
    for (i = 0; i < mxGetN(UNIT_ID_ARG); i++) {
        cUnit *Unit = NULL;

        /* Add a remote station relation to the master module */
        ret = Node->addUnit((uint8_t)mxGetPr(UNIT_ID_ARG)[i], (cUnit **)&Unit);
        if (ret != 0) {
            sprintf(ErrMsg, "Error %i while adding Modbus unit %i to server node %i!", ret,
                    (uint8_t)mxGetPr(UNIT_ID_ARG)[i], SERVER_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Initialize unit */
        ret =
            Unit->init(NUM_COIL_ARG(i), NUM_DISCRETE_ARG(i), NUM_HOLDING_ARG(i), NUM_INPUT_ARG(i));
        if (ret != 0) {
            sprintf(ErrMsg, "Error %i while initializing Modbus unit %i!", ret,
                    (uint16_t)mxGetPr(UNIT_ID_ARG)[i]);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    ssSetPWorkValue(S, 0, Node);
}

static void sg_ModelStep(SimStruct *S)
{
    uint16_t *Out = (uint16_T *)ssGetOutputPortSignal(S, 0);
    cServerNode *Node = (cServerNode *)ssGetPWorkValue(S, 0);

    if (Node->Stop) {
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

    *Out = Node->NumRemote;
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
