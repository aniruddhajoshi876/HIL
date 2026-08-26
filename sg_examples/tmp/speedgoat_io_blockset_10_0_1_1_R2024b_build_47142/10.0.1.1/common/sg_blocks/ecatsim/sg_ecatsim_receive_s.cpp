#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_ecatsim_receive_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "ecatsim_public.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace sg_ns_ecatsim;
#endif

/* Defines */
#define SLAVE_ADDRESS_ARG (uint32_T) mxGetScalar(ssGetSFcnParam(S, 0))
#define DATA_TYPE_ARG(i)  (uint32_T(mxGetPr(ssGetSFcnParam(S, 1))[i]))
#define WIDTH_ARG(i)      (uint32_T(mxGetPr(ssGetSFcnParam(S, 2))[i]))
#define OFFSET_ARG(i)     (uint32_T(mxGetPr(ssGetSFcnParam(S, 3))[i]))
#define SAMPLE_TIME_ARG   ssGetSFcnParam(S, 4)
#define IF_ID_ARG         (uint32_T) mxGetScalar(ssGetSFcnParam(S, 5))
#define NUM_ARGS          6

#define NUM_OUTPUT_PORTS (int_T) mxGetN(ssGetSFcnParam(S, 1))

/* Definitions */
static char_T ErrMsg[1024];
uint32_T getDataTypeLength(uint32_T DataType);

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUM_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUM_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUM_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Configure input ports */
    if (!ssSetNumInputPorts(S, 0))
        return;

    /* Configure output ports */
    if (!ssSetNumOutputPorts(S, NUM_OUTPUT_PORTS))
        return;

    for (i = 0; i < NUM_OUTPUT_PORTS; i++) {
        ssSetOutputPortDataType(S, i, DATA_TYPE_ARG(i));
        ssSetOutputPortWidth(S, i, WIDTH_ARG(i));
    }

    /* Set options */
    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLE_TIME_ARG)[0] == -1.0) {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    } else {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLE_TIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S) {}

static void sg_ModelStart(SimStruct *S)
{
    int32_t ret = 0;
    cNetwork *Network = NULL;
    cTransceiver *Transceiver = NULL;

    SgEcatSim->init();

    /* Add a network */
    ret = SgEcatSim->addNetwork(IF_ID_ARG, &Network);
    if (ret != 0) {
        sprintf(ErrMsg, "EC | Failed to add network %i", IF_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a transceiver */
    ret = Network->addTransceiver(&Transceiver);
    if (ret != 0) {
        sprintf(ErrMsg, "EC | Failed to add transceiver");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the transceiver */
    ret = Transceiver->init();
    if (ret != 0) {
        sprintf(ErrMsg, "EC | Failed to initialize transceiver");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Transceiver);
}

static void sg_ModelStep(SimStruct *S)
{
    cTransceiver *Transceiver = (cTransceiver *)ssGetPWorkValue(S, 0);

    /* For each output port */
    for (uint32_T i = 0; i < NUM_OUTPUT_PORTS; i++) {

        Transceiver->read((uint8_t *)ssGetOutputPortSignal(S, i),
                          getDataTypeLength(DATA_TYPE_ARG(i)), WIDTH_ARG(i), OFFSET_ARG(i),
                          DATA_TYPE_ARG(i) == SS_BOOLEAN);
    }
}

static void sg_ModelStop(SimStruct *S) {}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
