#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbrtu_client_send_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "mb_def.h"

#ifndef MATLAB_MEX_FILE
#include "mbrtu.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace modbusRTU;
#endif

/* Defines */
#define INTERFACE_ID_ARG   (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define REMOTE_NODE_ID_ARG (uint8_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define FUNC_CODE_ARG      (uint16_t)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define INDEX_ARG          (uint16_t)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define QUANTITY_ARG       (uint16_t)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define POLL_INTERVALL_ARG (uint32_t)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define ENABLE_SEND_ARG    (bool)mxGetPr(ssGetSFcnParam(S, 6))[0]
// obsolete 7
#define SAMPLE_TIME_ARG    mxGetPr(ssGetSFcnParam(S, 8))[0]
#define BYTE_SWAP_ARG      (bool)mxGetPr(ssGetSFcnParam(S, 9))[0]
#define NUMBER_OF_ARGS     10

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_t i = 0;
    uint32_t NumInputPorts = 1;
    uint32_t NumOutputPorts = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
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
    case MB_FC_WRITE_COIL:
        ssSetInputPortWidth(S, 0, 1);
        ssSetInputPortDataType(S, 0, SS_BOOLEAN);
        break;
    case MB_FC_WRITE_HOLDING_REG:
        ssSetInputPortWidth(S, 0, 1);
        ssSetInputPortDataType(S, 0, SS_UINT16);
        break;
    case MB_FC_WRITE_COILS:
        ssSetInputPortWidth(S, 0, QUANTITY_ARG);
        ssSetInputPortDataType(S, 0, SS_BOOLEAN);
        break;
    case MB_FC_WRITE_HOLDING_REGS:
        ssSetInputPortWidth(S, 0, QUANTITY_ARG);
        ssSetInputPortDataType(S, 0, SS_UINT16);
        break;
    default:
        return;
    }

    ssSetInputPortRequiredContiguous(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

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

    cClientInterface *Interface = NULL;
    cClientConnection *Connection = NULL;
    cClientTransceiver *Transceiver = NULL;

    Root.init();

    /* Add a client interface */
    ret = Root.addInterface(INTERFACE_ID_ARG, true, (cInterface **)&Interface);
    if (ret != 0) {
        sprintf(ErrMsg, "Failed to add Modbus RTU client interface %i", INTERFACE_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a connection to the interface */
    ret = Interface->addConnection(REMOTE_NODE_ID_ARG, (cClientConnection **)&Connection);
    if (ret != 0) {
        sprintf(ErrMsg, "Failed to add Modbus RTU client connection %i", REMOTE_NODE_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a transceiver to the connection */
    ret = Connection->addTransceiver((cClientTransceiver **)&Transceiver);
    if (ret != 0) {
        sprintf(ErrMsg, "Failed to add Modbus RTU client transceiver");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize Transceiver */

    ret = Transceiver->init(FUNC_CODE_ARG, REMOTE_NODE_ID_ARG, ENABLE_SEND_ARG, POLL_INTERVALL_ARG,
                            INDEX_ARG, QUANTITY_ARG, 0, BYTE_SWAP_ARG);

    ssSetPWorkValue(S, 0, Transceiver);
}

static void sg_ModelStep(SimStruct *S)
{
    cClientTransceiver *Transceiver = (cClientTransceiver *)ssGetPWorkValue(S, 0);

    /* Check if we want to send a request */
    if (Transceiver->EnaSend) {
        /* Read the input to check if user wants to send to server */
        bool *InPort = (bool *)ssGetInputPortSignal(S, 1);
        if (*InPort > 0)
        {
            Transceiver->WantsToSend = true;
        }
    } else {
        Transceiver->WantsToSend = true;
    }

    /* Transfer data from the input port to the protocol stack */
    Transceiver->transceive((void*)ssGetInputPortSignal(S, 0));
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
