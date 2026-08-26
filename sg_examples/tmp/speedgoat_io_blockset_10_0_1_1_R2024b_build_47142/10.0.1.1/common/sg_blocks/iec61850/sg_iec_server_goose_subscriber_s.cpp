#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_iec_server_goose_subscriber_s

/* Includes */
#include "simstruc.h"
#include <tmwtypes.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#include "goose_receiver.h"
#include "goose_subscriber.h"
#include "iec_def.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#ifndef MATLAB_MEX_FILE
#include "iec.h"
#include "iec_def.h"
#include "iec_goose_root.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace iec61850;
#endif

/* Defines */

#define SERVER_ID_ARG     (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define MAC_ADDRESS_ARG   (uint64_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define ETHERNET_PORT_ARG ssGetSFcnParam(S, 2)
#define APP_ID_ARG        (uint16_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define DATA_TYPE_ARG     (uint8_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define DATA_LENGTH_ARG   (uint16_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define GO_CB_REF_ARG     ssGetSFcnParam(S, 6)
#define SAMPLE_TIME_ARG   mxGetPr(ssGetSFcnParam(S, 7))[0]
#define NUMBER_OF_ARGS    8

#define SINGLE_QUANTITY 1
#define MAX_STRING_SIZE 255

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
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, DATA_LENGTH_ARG);
    ssSetOutputPortDataType(S, 0, DATA_TYPE_ARG);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 1);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

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

static void sg_ModelLoad(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    /* Initialize GOOSE */
    GooseRoot.init();

#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    int32_t ret = 0;
    cGooseSNode *Node = NULL;

    /* Add a node */
    ret = GooseRoot.addNode(GooseRoot.NodeIDs, false, (cNodeGoose **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "GOOSE | Failed to add subscriber node %i\n", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Get EthInterfaceLabel Parameter */
    char_T *EthInterfaceLabel;
    EthInterfaceLabel = (char_T *)malloc(mxGetN(ETHERNET_PORT_ARG) + 1);
    if (EthInterfaceLabel == NULL) {
        ssSetErrorStatus(S, "GOOSE | Not enough memory");
        return;
    }
    if (mxGetString(ETHERNET_PORT_ARG, EthInterfaceLabel, 1 + mxGetN(ETHERNET_PORT_ARG)) != 0) {
        ssSetErrorStatus(S, "GOOSE | Failed to read EthInterfaceLabel parameter");
        return;
    }

    /* Search translation file for eth label and retrieve eth name */
    std::string EthInterfaceName = getEthInterfaceNameFromLabel(std::string(EthInterfaceLabel));
    if (EthInterfaceName.empty()) {
        sprintf(ErrMsg, "GOOSE | Ethernet interface label %s is invalid\n", EthInterfaceLabel);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Reserve memory for reading the strings */
    std::vector<std::string> stReadVect;

    /* Get GoCbRef Parameter */
    char_T *GoCbRef = NULL;
    GoCbRef = (char_T *)malloc(mxGetN(GO_CB_REF_ARG) + 1);
    if (GoCbRef == NULL) {
        ssSetErrorStatus(S, "GOOSE | Not enough memory");
        return;
    }
    if (mxGetString(GO_CB_REF_ARG, GoCbRef, 1 + mxGetN(GO_CB_REF_ARG)) != 0) {
        ssSetErrorStatus(S, "GOOSE | Failed to read GoCbRef parameter");
        return;
    }
    stReadVect.push_back(GoCbRef);
    free(GoCbRef);

    /* Initialize the node */
    ret = Node->init(ssGetOutputPortDataType(S, 0), 0, ssGetOutputPortWidth(S, 0), MAC_ADDRESS_ARG,
                     EthInterfaceName, std::string(EthInterfaceLabel), APP_ID_ARG, stReadVect);
    if (ret != 0) {
        sprintf(ErrMsg, "GOOSE | Failed to initialize subscriber node %i\n", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (EthInterfaceLabel != NULL) {
        free(EthInterfaceLabel);
    }

    ssSetPWorkValue(S, 0, Node);
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    cGooseSNode *Node = (cGooseSNode *)ssGetPWorkValue(S, 0);

    /* Receive data and output */
    int8_t *OutPort = (int8_t *)ssGetOutputPortSignal(S, 0);
    memcpy(OutPort, Node->DataOut, Node->DataLength);

    /* Start background thread */
    {
        static bool FirstStep = true;
        static uint64_t StartDelayTimer = 0;
        if (FirstStep) {
            StartDelayTimer = getMilliCounter();
            FirstStep = false;
        }
        if ((getMilliCounter() - StartDelayTimer) > 100) {
            GooseRoot.launch();
        }
    }

    /* Stop model execution if required */
    if (GooseRoot.IsFaulty == true) {

        sprintf(ErrMsg, "GOOSE | Runtime error\n");
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
    GooseRoot.stop();
#endif
}

#include "sg_sfcn_glue.h" // Code generation glue
