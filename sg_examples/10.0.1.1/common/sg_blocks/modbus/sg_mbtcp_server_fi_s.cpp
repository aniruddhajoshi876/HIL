#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbtcp_server_fi_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "mb_def.h"

#ifndef MATLAB_MEX_FILE
#include "mbtcp.h"
#include "mbtcp_server_fi.h"
#include "mbtcp_server_fi_rule.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace modbusTCP;
#endif

/* Defines */
#define SERVER_ID_ARG           (uint16_T)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define SAMPLE_TIME_ARG         mxGetPr(ssGetSFcnParam(S, 1))[0]
#define MODE_ARG                (uint32_T)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define SHOW_ENABLE_PORT_ARG    (boolean_T)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define SHOW_VALUE_PORT_ARG     (boolean_T)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define RULES_ARG               ssGetSFcnParam(S, 5)

#define NUMBER_OF_ARGS          6

#define NUM_RULES               (uint32_T)mxGetM(RULES_ARG)
#define INVALID_RULES           (mxGetPr(RULES_ARG) == NULL ? true : false)

#define PEER_ACTION(i)          ((uint32_T)(mxGetPr(RULES_ARG)[i + 0 * (int_T)mxGetM(RULES_ARG)]))

#define PEER_IPADDR_FIRST(i)    ((real64_T)(mxGetPr(RULES_ARG)[i + 1 * (int_T)mxGetM(RULES_ARG)]))
#define PEER_IPADDR_LAST(i)     ((real64_T)(mxGetPr(RULES_ARG)[i + 2 * (int_T)mxGetM(RULES_ARG)]))
#define PEER_PORT_FIRST(i)      ((real64_T)(mxGetPr(RULES_ARG)[i + 3 * (int_T)mxGetM(RULES_ARG)]))
#define PEER_PORT_LAST(i)       ((real64_T)(mxGetPr(RULES_ARG)[i + 4 * (int_T)mxGetM(RULES_ARG)]))

#define MSG_MODIFIER(i)      ((real64_T)(mxGetPr(RULES_ARG)[i + 1 * (int_T)mxGetM(RULES_ARG)]))
#define MSG_UNIT_FIRST(i)       ((real64_T)(mxGetPr(RULES_ARG)[i + 2 * (int_T)mxGetM(RULES_ARG)]))
#define MSG_UNIT_LAST(i)        ((real64_T)(mxGetPr(RULES_ARG)[i + 3 * (int_T)mxGetM(RULES_ARG)]))
#define MSG_FC_FIRST(i)         ((real64_T)(mxGetPr(RULES_ARG)[i + 4 * (int_T)mxGetM(RULES_ARG)]))
#define MSG_FC_LAST(i)          ((real64_T)(mxGetPr(RULES_ARG)[i + 5 * (int_T)mxGetM(RULES_ARG)]))
#define MSG_INDEX_FIRST(i)      ((real64_T)(mxGetPr(RULES_ARG)[i + 6 * (int_T)mxGetM(RULES_ARG)]))
#define MSG_INDEX_LAST(i)       ((real64_T)(mxGetPr(RULES_ARG)[i + 7 * (int_T)mxGetM(RULES_ARG)]))

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;
    uint32_T NumInputPorts = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Check the pointer/address of all parameters and set them to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++) {
        if (mxGetPr(ssGetSFcnParam(S, i)) != NULL) {
            ssSetSFcnParamTunable(S, i, 0);
        }
    }

    /* Configure the input ports */
    if (!INVALID_RULES) {
        if (NUM_RULES > 0) {
            if (SHOW_ENABLE_PORT_ARG) {
                NumInputPorts++;
            }
            if ((SHOW_VALUE_PORT_ARG) && (MODE_ARG == MB_FI_MODE_MSG)) {
                NumInputPorts++;
            }
        }
    }

    if (!ssSetNumInputPorts(S, NumInputPorts))
        return;

    if (ssGetNumInputPorts(S) > 0) {
        i = 0;
        if (SHOW_ENABLE_PORT_ARG) {
            ssSetInputPortDataType(S, i, SS_BOOLEAN);
            ssSetInputPortWidth(S, i, NUM_RULES);
            ssSetInputPortRequiredContiguous(S, i, 1);
            ssSetInputPortDirectFeedThrough(S, i, 1);
            i++;
        }
        if ((SHOW_VALUE_PORT_ARG) && (MODE_ARG == MB_FI_MODE_MSG)) {
            ssSetInputPortDataType(S, i, SS_DOUBLE);
            ssSetInputPortWidth(S, i, NUM_RULES);
            ssSetInputPortRequiredContiguous(S, i, 1);
            ssSetInputPortDirectFeedThrough(S, i, 1);
            i++;
        }
    }

    /* Configure the output ports */
    if (!ssSetNumOutputPorts(S, 0))
        return;

    /* Options */
    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
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
    cServerNode *Node = NULL;
    cServerFi *Fi = NULL;

    /* Add a server node */
    ret = Root.addNode(SERVER_ID_ARG, false, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus server node %i!", ret, SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a fault insertion block to the node */
    ret = Node->addFi((cServerFi **)&Fi);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding fault insertion block to server node %i!", ret,
                SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Init the fault insertion block */
    ret = Fi->init(MODE_ARG, SHOW_ENABLE_PORT_ARG, SHOW_VALUE_PORT_ARG);
    if (ret != 0) {
        sprintf(ErrMsg, "Failed to initialize fault insertion block %i!", Fi->ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add rules */
    if (!INVALID_RULES) {
        for (uint32_t i = 0; i < NUM_RULES; i++) {

            cServerFiRule *Rule = NULL;

            /* Add a rule to the fault insertion block */
            ret = Fi->addRule((cServerFiRule **)&Rule);
            if (ret != 0) {
                sprintf(ErrMsg, "Failed to add rule to fault insertion %i!", Fi->ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }

            /* Init the rule */
            if (MODE_ARG == MB_FI_MODE_PEER) {
                ret = Rule->init(PEER_ACTION(i),
                                 PEER_IPADDR_FIRST(i), PEER_IPADDR_LAST(i),
                                 PEER_PORT_FIRST(i), PEER_PORT_LAST(i));
            } else {
                ret = Rule->init(PEER_ACTION(i),
                                 MSG_UNIT_FIRST(i), MSG_UNIT_LAST(i),
                                 MSG_FC_FIRST(i), MSG_FC_LAST(i),
                                 MSG_INDEX_FIRST(i), MSG_INDEX_LAST(i),
                                 MSG_MODIFIER(i));
            }
            if (ret != 0) {
                sprintf(ErrMsg, "Failed to initialize fault insertion rule %i!", Rule->ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }
    }

    ssSetPWorkValue(S, 0, Fi);
}

static void sg_ModelStep(SimStruct *S)
{
    int32_t i = 0;
    cServerFi *Fi = (cServerFi *)ssGetPWorkValue(S, 0);
    boolean_T *EnablePort = NULL;
    real64_T *ValuePort = NULL;

    /* Do nothing if no ports */
    if (ssGetNumInputPorts(S) == 0) {
        return;
    }

    /* Get pointers to ports */
    if (SHOW_ENABLE_PORT_ARG) {
        EnablePort = (boolean_T *)ssGetInputPortSignalPtrs(S, i);
        i++;
    }
    if ((SHOW_VALUE_PORT_ARG) && (MODE_ARG == MB_FI_MODE_MSG)) {
        ValuePort = (real64_T *)ssGetInputPortSignalPtrs(S, i);
        i++;
    }

    i = 0;
    /* For each rule */
    for (cServerFiRule *&Rule : Fi->Rules) {

        /* Get pointer to corresponding port elements */
        if (SHOW_ENABLE_PORT_ARG) {
            EnablePort = &EnablePort[i];
        }
        if ((SHOW_VALUE_PORT_ARG) && (MODE_ARG == MB_FI_MODE_MSG)) {
            ValuePort = &ValuePort[i];
        }

        /* Update the rule */
        Rule->update((bool*)EnablePort, ValuePort);
        i++;
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
