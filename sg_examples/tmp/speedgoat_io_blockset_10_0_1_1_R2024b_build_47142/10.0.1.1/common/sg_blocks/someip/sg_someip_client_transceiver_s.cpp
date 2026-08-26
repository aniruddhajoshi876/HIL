#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_someip_client_transceiver_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "someip_def.h"

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_printf.h"
#include "someip_api.h"
#include "someip_client_station_api.h"
#include "someip_client_transceiver_api.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace sg_ns_someip;
#endif

/* Defines */
#define STATION_ID_ARG     (uint32_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define SERVICE_ID_ARG     (uint16_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define INSTANCE_ID_ARG    (uint16_t)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define METHOD_ID_ARG      (uint16_t)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define EVENT_ID_ARG       (uint16_t)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define EVENT_GROUP_ID_ARG (uint16_t)mxGetPr(ssGetSFcnParam(S, 5))[0]
#define DATA_LEN_ARG       (uint32_t)mxGetPr(ssGetSFcnParam(S, 6))[0]
#define ENABLE_SEND_ARG    (bool)mxGetPr(ssGetSFcnParam(S, 7))[0]
#define UPDATE_CHANGE_ARG  (bool)mxGetPr(ssGetSFcnParam(S, 8))[0]
#define SAMPLE_TIME_ARG    mxGetPr(ssGetSFcnParam(S, 9))[0]
#define NUMBER_OF_ARGS     10

#define OUTPORT_CONNECTED   (DATA_LEN_ARG > 0 ? true : false)
#define OUTPORT_DATA_LENGTH (DATA_LEN_ARG)
#define INPORT_CONNECTED    (ssGetInputPortConnected(S, 0))
#define INPORT_DATA_LENGTH  (ssGetInputPortWidth(S, 0))

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (uint32_T i = 0; i < NUMBER_OF_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Input ports */
    ssSetNumInputPorts(S, 1);
    ssSetInputPortDataType(S, 0, SS_UINT8);
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    /* Output ports */
    if (OUTPORT_CONNECTED) {
        ssSetNumOutputPorts(S, 1);
        ssSetOutputPortWidth(S, 0, DATA_LEN_ARG);
        ssSetOutputPortDataType(S, 0, SS_UINT8);
    } else {
        ssSetNumOutputPorts(S, 0);
    }

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

#define MDL_SET_INPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_INPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    ssSetInputPortDimensionInfo(S, portIndex, dimsInfo);
}
#endif /* MDL_SET_INPUT_PORT_DIMENSION_INFO */

#define MDL_SET_INPUT_PORT_DATA_TYPE
#if defined(MDL_SET_INPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetInputPortDataType(SimStruct *S, int_T port, DTypeId id)
{
    ssSetInputPortDataType(S, port, id);
}
#endif /* MDL_SET_INPUT_PORT_DATA_TYPE */

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDimensionInfo(SimStruct *S, int portIndex, const DimsInfo_T *dimsInfo)
{
    ssSetOutputPortDimensionInfo(S, portIndex, dimsInfo);
}
#endif /* MDL_SET_OUTPUT_PORT_DIMENSION_INFO */

#define MDL_SET_OUTPUT_PORT_DATA_TYPE
#if defined(MDL_SET_OUTPUT_PORT_DATA_TYPE) && defined(MATLAB_MEX_FILE)
static void mdlSetOutputPortDataType(SimStruct *S, int_T port, DTypeId id)
{
    ssSetOutputPortDataType(S, port, id);
}
#endif /* MDL_SET_OUTPUT_PORT_DATA_TYPE */

#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
#if defined(MDL_SET_DEFAULT_PORT_DIMENSION_INFO) && defined(MATLAB_MEX_FILE)
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
    ssSetInputPortWidth(S, 0, 1);
    // ssSetErrorStatus(S, "Cannot inherit port dimensions\n");
    return;
}
#endif /* MDL_SET_DEFAULT_PORT_DIMENSION_INFO */

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S) {}

static void sg_ModelStart(SimStruct *S)
{
    int32_t ret = 0;
    cClientStationApi *Station = NULL;
    cClientTransceiverApi *Transceiver = NULL;

    /* Add a station */
    ret = SgSomeIp->addStation(STATION_ID_ARG, SOMIEIP_STATION_TYPE_CLIENT, (void **)&Station);
    if (ret != 0) {
        sprintf(ErrMsg, "SOME IP | Failed to add client %i", STATION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a transceiver to the station */
    ret = Station->addTransceiver((cClientTransceiverApi **)&Transceiver);
    if (ret != 0) {
        sprintf(ErrMsg, "SOME IP | Failed to add transceiver to client %i", STATION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the transceiver */
    ret = Transceiver->init(SERVICE_ID_ARG, INSTANCE_ID_ARG, METHOD_ID_ARG, EVENT_ID_ARG,
                            EVENT_GROUP_ID_ARG, OUTPORT_CONNECTED, OUTPORT_DATA_LENGTH,
                            INPORT_CONNECTED, INPORT_DATA_LENGTH);
    if (ret != 0) {
        sprintf(ErrMsg, "SOME IP | Failed to initialize transceiver of client %i\n",
                STATION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Transceiver);
}

static void sg_ModelStep(SimStruct *S)
{
    void *InPort = NULL;
    void *OutPort = NULL;
    cClientTransceiverApi *Transceiver = (cClientTransceiverApi *)ssGetPWorkValue(S, 0);

    /* Check if input port is connected and process it */
    if (INPORT_CONNECTED) {
        InPort = (void *)ssGetInputPortSignal(S, 0);
    }
    Transceiver->processInport(InPort);

    /* Check if block has an output port and process it */
    if (OUTPORT_CONNECTED) {
        OutPort = (void *)ssGetOutputPortSignal(S, 0);
    }
    Transceiver->processOutport(OutPort);
}

static void sg_ModelStop(SimStruct *S) {}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
