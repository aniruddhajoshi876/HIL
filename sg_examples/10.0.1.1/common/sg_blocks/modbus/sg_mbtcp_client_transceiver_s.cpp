#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbtcp_client_transceiver_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

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
#define CLIENT_ID_ARG      (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CONNECTION_ID_ARG  (uint16_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define REMOTE_UNIT_ID_ARG (uint8_t)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define FUNC_CODE_ARG      (uint16_t)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define INDEX_ARG          (uint16_t)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define QUANTITY_ARG       (uint16_t)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define POLL_INTERVALL_ARG (uint32_t)mxGetPr(ssGetSFcnParam(S, 6))[0]
#define ENABLE_SEND_ARG    (bool)mxGetPr(ssGetSFcnParam(S, 7))[0]
#define UPDATE_CHANGE_ARG  (bool)mxGetPr(ssGetSFcnParam(S, 8))[0]
#define SAMPLE_TIME_ARG    mxGetPr(ssGetSFcnParam(S, 9))[0]
#define NUMBER_OF_ARGS     10

#define SINGLE_QUANTITY 1

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    //	printf("mdlInitializeSizes");
    uint32_T i = 0;
    uint32_T NumInputPorts = 0;
    uint32_T NumOutputPorts = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Check the pointer/address of all parameters and set them to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++) {
        if (mxGetPr(ssGetSFcnParam(S, i)) == NULL)
            return;
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Set the number of ports */
    if (FUNC_CODE_ARG > MB_TABLE_TYPE_INPUT) {
        NumInputPorts = 1;
    } else {
        NumOutputPorts = 1;
    }

    if (ENABLE_SEND_ARG) {
        NumInputPorts++;
    }

    ssSetNumInputPorts(S, NumInputPorts);
    ssSetNumOutputPorts(S, NumOutputPorts);

    /* Configure the ports */
    if (ENABLE_SEND_ARG) {
        ssSetInputPortWidth(S, NumInputPorts - 1, 1);
        ssSetInputPortDataType(S, NumInputPorts - 1, SS_BOOLEAN);
        ssSetInputPortRequiredContiguous(S, NumInputPorts - 1, 1);
        ssSetInputPortDirectFeedThrough(S, NumInputPorts - 1, 1);
    }

    switch (FUNC_CODE_ARG) {
    case MB_TABLE_TYPE_COIL:
    case MB_TABLE_TYPE_DISCRETE:
        ssSetOutputPortWidth(S, 0, QUANTITY_ARG);
        ssSetOutputPortDataType(S, 0, SS_BOOLEAN);
        break;
    case MB_TABLE_TYPE_HOLDING:
    case MB_TABLE_TYPE_INPUT:
        ssSetOutputPortWidth(S, 0, QUANTITY_ARG);
        ssSetOutputPortDataType(S, 0, SS_UINT16);
        break;
    case MB_TABLE_TYPE_COIL_W:
    case MB_TABLE_TYPE_REGISTER_W:
        ssSetInputPortWidth(S, 0, SINGLE_QUANTITY);
        ssSetInputPortDataType(S, 0, SS_UINT16);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
        break;
    case MB_TABLE_TYPE_MULTI_COILS_W:
        ssSetInputPortWidth(S, 0, QUANTITY_ARG);
        ssSetInputPortDataType(S, 0, SS_BOOLEAN);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
        break;
    case MB_TABLE_TYPE_MULTI_REGISTERS_W:
        ssSetInputPortWidth(S, 0, QUANTITY_ARG);
        ssSetInputPortDataType(S, 0, SS_UINT16);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
        break;
    default:
        sprintf(ErrMsg,
                "Error: unsupported or wrong function code in transceiver mask (FC%d | "
                "CONN:%d).\nCheck usage notes in the knowledge center "
                "on:\nhttps://www.speedgoat.com/help/slrt/page/io_main/"
                "refentry_mbtcp_client_transceiver \n",
                FUNC_CODE_ARG, CONNECTION_ID_ARG);
        break;
    }

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
    //	printf("mdlInitializeSampleTimes");
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
    cClientNode *Node = NULL;
    cClientConnection *Connection = NULL;
    cClientTransceiver *Transceiver = NULL;

    /* Add a client node */
    ret = Root.addNode(CLIENT_ID_ARG, true, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus node %i!", ret, CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a client connection to the node */
    ret = Node->addConnection(CONNECTION_ID_ARG, (cClientConnection **)&Connection);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus client connection %i!", ret,
                CONNECTION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a transceiver  to the connection */
    ret = Connection->addTransceiver((cClientTransceiver **)&Transceiver);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus transceiver %i to client connection %i!", ret,
                Connection->TransceiverIDs, CONNECTION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize transceiver */
    if (FUNC_CODE_ARG == MB_TABLE_TYPE_COIL_W || FUNC_CODE_ARG == MB_TABLE_TYPE_REGISTER_W) {
        ret = Transceiver->init(FUNC_CODE_ARG, REMOTE_UNIT_ID_ARG, ENABLE_SEND_ARG,
                                POLL_INTERVALL_ARG, INDEX_ARG, SINGLE_QUANTITY, UPDATE_CHANGE_ARG);
    } else {
        ret = Transceiver->init(FUNC_CODE_ARG, REMOTE_UNIT_ID_ARG, ENABLE_SEND_ARG,
                                POLL_INTERVALL_ARG, INDEX_ARG, QUANTITY_ARG, UPDATE_CHANGE_ARG);
    }

    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while initializing modbus client transceiver block!\n", ret);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Transceiver);
}

static void sg_ModelStep(SimStruct *S)
{
    cClientTransceiver *Transceiver = (cClientTransceiver *)ssGetPWorkValue(S, 0);

    /* Always send requests if triggered operation is disabled */
    if ((Transceiver->EnaSend == 0) && (Transceiver->EnableUpdateOnChange == 0)) {
        Transceiver->RequestTrigger++;
    }

    if (Transceiver->EnaSend) {
        bool *InPort = NULL;
        /* Read the input to check if user wants to send a request to the server */
        if (Transceiver->FunctionCode > MB_TABLE_TYPE_INPUT) {
            InPort = (bool *)ssGetInputPortSignal(S, 1);
        } else {
            InPort = (bool *)ssGetInputPortSignal(S, 0);
        }
        if (*InPort != 0) {
            Transceiver->RequestTrigger++;
        }
    }

    switch (FUNC_CODE_ARG) {
        /* Read FCs: */
    case MB_TABLE_TYPE_COIL:     // FC1
    case MB_TABLE_TYPE_DISCRETE: // FC2
    {
        /* Receive data and output */
        uint8_t *OutPort = (uint8_t *)ssGetOutputPortSignal(S, 0);
        memcpy(OutPort, Transceiver->DataAddress, Transceiver->Quantity * sizeof(uint8_t));
        break;
    }
    case MB_TABLE_TYPE_HOLDING: // FC3
    case MB_TABLE_TYPE_INPUT:   // FC4
    {
        /* Receive data and output */
        uint16_t *OutPort = (uint16_t *)ssGetOutputPortSignal(S, 0);
        memcpy(OutPort, Transceiver->DataAddress, Transceiver->Quantity * sizeof(uint16_t));
        break;
    }
    /* Write FCs: */
    case MB_TABLE_TYPE_COIL_W:     // FC5
    case MB_TABLE_TYPE_REGISTER_W: // FC6
    {
        /* Input and send data */
        uint16_t *InPort = (uint16_t *)ssGetInputPortSignal(S, 0);
        if (Transceiver->EnableUpdateOnChange)
            if (memcmp(Transceiver->DataAddress, InPort, SINGLE_QUANTITY * sizeof(uint16_t)))
                Transceiver->RequestTrigger++;
        memcpy(Transceiver->DataAddress, InPort, SINGLE_QUANTITY * sizeof(uint16_t));
        break;
    }
    case MB_TABLE_TYPE_MULTI_COILS_W:     // FC15
    case MB_TABLE_TYPE_MULTI_REGISTERS_W: // FC16
    {
        /* Input and send data */
        uint16_t *InPort = (uint16_t *)ssGetInputPortSignal(S, 0);
        if (Transceiver->EnableUpdateOnChange)
            if (memcmp(Transceiver->DataAddress, InPort, Transceiver->Quantity * sizeof(uint16_t)))
                Transceiver->RequestTrigger++;
        memcpy(Transceiver->DataAddress, InPort, Transceiver->Quantity * sizeof(uint16_t));
        break;
    }
    default:
        SG_PRINTF_DEBUG("Error: unsupported or wrong function code used. Check usage notes "
                        "on:\nwww.speedgoat.com/help/slrt/page/io_main/refentry_mbtcp_usage_notes");
        break;
    }

    if (Root.Stop) {
        ssSetStopRequested(S, 1);
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
