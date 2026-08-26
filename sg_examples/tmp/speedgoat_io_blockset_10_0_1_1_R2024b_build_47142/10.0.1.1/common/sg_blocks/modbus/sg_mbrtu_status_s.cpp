#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbrtu_status_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "mb_def.h"
#include "sg_common.h"

#ifndef MATLAB_MEX_FILE
#include "mbrtu.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace modbusRTU;
#endif

/* Defines */
#define INTERFACE_ID_ARG (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define SAMPLE_TIME_ARG  mxGetPr(ssGetSFcnParam(S, 1))[0]

#define NUMBER_OF_ARGS 2

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_t i = 0;
    uint32_t NumInputPorts = 0;
    uint32_t NumOutputPorts = 1;

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
    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 1);

    /* Configure the ports */
    ssSetOutputPortWidth(S, 0, 7);
    ssSetOutputPortDataType(S, 0, SS_UINT32);

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

    cInterface *Interface = NULL;

    Root.init();

    /* Add a client interface */
    ret = Root.addInterface(INTERFACE_ID_ARG, true, (cInterface **)&Interface);
    if (ret != 0) {
        sprintf(ErrMsg, "Failed to add Modbus RTU client interface %i", INTERFACE_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Interface);
}

static void sg_ModelStep(SimStruct *S)
{
    cInterface *Interface = (cInterface *)ssGetPWorkValue(S, 0);

    if (Interface != NULL) {
        uint32_T *p = (uint32_T *)ssGetOutputPortSignal(S, 0);

        *p = Interface->NumTimeouts;
        p++;
        *p = Interface->TxTotalNumBytes;
        p++;
        *p = Interface->TxTotalNumValid;
        p++;
        *p = Interface->RxTotalNumBytes;
        p++;
        *p = Interface->RxTotalNumValid;
        p++;
        *p = Interface->RxTotalNumInvalid;
        p++;
        *p = Interface->RxTotalNumIncomplete;
    }
}

static void sg_ModelStop(SimStruct *S) {}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
