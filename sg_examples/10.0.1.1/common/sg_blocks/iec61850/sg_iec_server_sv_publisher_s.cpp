#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_iec_server_sv_publisher_s

/* Includes */
#include "simstruc.h"
#include <tmwtypes.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#include "iec_def.h"
#include "sv_publisher.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#ifndef MATLAB_MEX_FILE
#include "iec.h"
#include "iec_def.h"
#include "iec_sv_publisher.h"
#include "iec_sv_root.h"
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
#define VLAN_ID_ARG       (uint16_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define VLAN_PRIORITY_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define DATA_TYPE_ARG     (uint8_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define ASDU_NAME_ARG     ssGetSFcnParam(S, 7)
#define POLLING_TIME_ARG  (uint64_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define ENA_TIMESTAMP_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define SAMPLE_TIME_ARG   mxGetPr(ssGetSFcnParam(S, 10))[0]
#define NUMBER_OF_ARGS    11

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

    /* DATA input port */
    ssSetNumInputPorts(S, 1);
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDataType(S, 0, DATA_TYPE_ARG);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    ssSetNumOutputPorts(S, 0);
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

#ifdef MATLAB_MEX_FILE
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct *S, int port, const DimsInfo_T *dimsInfo)
{
    if (!ssSetInputPortDimensionInfo(S, port, dimsInfo)) {
        return;
    }
}
#endif // MATLAB_MEX_FILE

static void mdlInitializeSampleTimes(SimStruct *S)
{
    //	printf("mdlInitializeSampleTimes");
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

    /* Initialize AV */
    SVRoot.init();

#endif
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    int32_t ret = 0;
    cSVPNode *Node = NULL;

    /* Add a client node */
    ret = SVRoot.addNode(SVRoot.NodeIDs, true, (cNodeSV **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "SV | Failed to add publisher node %i\n", SERVER_ID_ARG);
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

    char_T *ASDU_Name;
    ASDU_Name = (char_T *)malloc(mxGetN(ASDU_NAME_ARG) + 1);
    if (ASDU_Name == NULL) {
        ssSetErrorStatus(S, "SV | Not enough memory");
        return;
    }
    if (mxGetString(ASDU_NAME_ARG, ASDU_Name, 1 + mxGetN(ASDU_NAME_ARG)) != 0) {
        ssSetErrorStatus(S, "SV | Failed to read ASDU_Name parameter");
        return;
    }

    /* Initialize the node */
    ret = Node->init(POLLING_TIME_ARG, ssGetInputPortDataType(S, 0), ENA_TIMESTAMP_ARG, 0,
                     ssGetInputPortWidth(S, 0), MAC_ADDRESS_ARG, EthInterfaceName,
                     std::string(ASDU_Name), EthInterfaceLabel, APP_ID_ARG, VLAN_ID_ARG,
                     VLAN_PRIORITY_ARG);
    if (ret != 0) {
        sprintf(ErrMsg, "SV | Failed to initialize publisher node %i\n", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (EthInterfaceLabel != NULL) {
        free(EthInterfaceLabel);
    }

    if (ASDU_Name != NULL) {
        free(ASDU_Name);
    }

    ssSetPWorkValue(S, 0, Node);
#endif
}

static void sg_ModelStep(SimStruct *S) // @suppress("Unused static function")
{
#ifndef MATLAB_MEX_FILE

    cSVPNode *Node = (cSVPNode *)ssGetPWorkValue(S, 0);

    /* Input and send data */
    int8_t *InPort = (int8_t *)ssGetInputPortSignal(S, 0);
    memcpy(Node->DataIn, InPort, Node->DataLength);

    /* Start background thread */
    {
        static bool FirstStep = true;
        static uint64_t StartDelayTimer = 0;
        if (FirstStep) {
            StartDelayTimer = getMilliCounter();
            FirstStep = false;
        }
        if ((getMilliCounter() - StartDelayTimer) > 100) {
            SVRoot.launch();
        }
    }

    /* Stop model execution if required */
    if (SVRoot.IsFaulty == true) {

        sprintf(ErrMsg, "SV | Runtime error\n");
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
    SVRoot.stop();
#endif
}

#include "sg_sfcn_glue.h" // Code generation glue
