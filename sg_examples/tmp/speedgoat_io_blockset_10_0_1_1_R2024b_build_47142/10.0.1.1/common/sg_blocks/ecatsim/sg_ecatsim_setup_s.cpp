#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_ecatsim_setup_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#ifndef MATLAB_MEX_FILE
#include "ecatsim_public.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace sg_ns_ecatsim;
#endif

/* Defines */
#define IF_ID_ARG        (uint32_T) mxGetScalar(ssGetSFcnParam(S, 0))
#define FIRST_DEVICE_ARG (int32_T) mxGetScalar(ssGetSFcnParam(S, 1))
#define NUM_ARGS          2

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    int_T i = 0;

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

    /* No input and no output ports */
    if (!ssSetNumInputPorts(S, 0))
        return;
    if (!ssSetNumOutputPorts(S, 0))
        return;

    /* Default settings */
    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);

    /* Set options */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S) {

    int32_t ret = 0;
    cNetwork *Network = NULL;

    /* Initialize */
    SgEcatSim->init();

    /* Add a network */
    ret = SgEcatSim->addNetwork(IF_ID_ARG, &Network);
    if (ret != 0) {
        sprintf(ErrMsg, "EC | Failed to add network %i", IF_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the network */
    ret = Network->init(FIRST_DEVICE_ARG);

    if (ret != 0) {
        sprintf(ErrMsg, "EC | Failed to initialize network %i", IF_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
}

static void sg_ModelStart(SimStruct *S)
{
    int32_t ret = 0;
    cNetwork *Network = NULL;

    /* Get the network */
    ret = SgEcatSim->getNetwork(IF_ID_ARG, &Network);
    if (ret != 0) {
        sprintf(ErrMsg, "EC | Failed to get network %i", IF_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Network);
}

static void sg_ModelStep(SimStruct *S)
{
    cNetwork *Network = (cNetwork *)ssGetPWorkValue(S, 0);

    /* Start background thread */
    {
        static bool FirstStep = true;
        static uint64_t StartDelayTimer = 0;
        if (FirstStep)
        {
            StartDelayTimer = getMilliCounter();
            FirstStep = false;
        }
        if ((getMilliCounter() - StartDelayTimer) > 100)
        {
            SgEcatSim->run();
        }
    }

    /* Stop model execution if required */
    if (SgEcatSim->IsFaulty == true) {
        sprintf(ErrMsg, "EC | Runtime error");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
}

static void sg_ModelStop(SimStruct *S) {}
static void sg_ModelExit(SimStruct *S) { SgEcatSim->stop(); }

#endif

#include "sg_sfcn_glue.h" // Code generation glue
