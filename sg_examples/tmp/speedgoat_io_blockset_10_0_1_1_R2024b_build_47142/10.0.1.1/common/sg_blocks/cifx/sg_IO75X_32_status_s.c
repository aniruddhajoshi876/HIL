#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO75X_32_status_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define SAMPLETIME_ARG ssGetSFcnParam(S, 1)
#define ENA_FPGA_TEMP (boolean_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define ENA_BOARD_TEMP (boolean_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define NUMBER_OF_ARGS 4

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint8_T i;
    uint8_T portCnt = 0;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg,
                "Wrong number of input arguments passed.\n%d arguments are expected\n",
                NUMBER_OF_ARGS);

        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    portCnt += (ENA_FPGA_TEMP) ? 1 : 0;
    portCnt += (ENA_BOARD_TEMP) ? 1 : 0;

    if (!ssSetNumOutputPorts(S, portCnt))
        return;

    for (i = 0; i < portCnt; i++)
    {
        ssSetOutputPortWidth(S, i, 1);
        ssSetOutputPortDataType(S, i, SS_UINT8);
    }

    ssSetNumPWork(S, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLETIME_ARG)[0] == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLETIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
    ssSetPWorkValue(S, 0, NULL);
}

static void sg_ModelStep(SimStruct *S)
{
    uint8_t portCnt = 0;
    CIFX_MODULE_T *Module = (CIFX_MODULE_T *)ssGetPWorkValue(S, 0);

    if (Module == NULL)
    {
        uint32_T i = 0;
        CIFX_NODE_T *Node = NULL;

        /* Attach to the first node configured */
        for (i = 0; i < CIFX_MAX_NUM_NODES; i++)
        {
            if (0 == Cifx_FindNode(MOD_ID_ARG, i+1, &Node))
            {
                Module = Node->Module;
                break;
            }
        }

        if (Module == NULL)
        {
            ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
            return;
        }
        
        ssSetPWorkValue(S, 0, Module);
    }

    if (ENA_FPGA_TEMP)
    {
        Cifx_GetFPGATemp(Module, (uint8_T *)ssGetOutputPortSignal(S, portCnt));
        portCnt += 1;
    }

    if (ENA_BOARD_TEMP)
    {
        Cifx_GetBoardTemp(Module, (uint8_T *)ssGetOutputPortSignal(S, portCnt));
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h"
