#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbrtu_server_read_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "mb_def.h"

#ifndef MATLAB_MEX_FILE
#include "mbrtu.h"
#include "mbrtu_server_block.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace modbusRTU;
#endif

/* Defines */
#define INTERFACE_ID_ARG (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG      (uint8_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define TABLE_ARG        (uint16_t)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define INDEX_ARG        (uint16_t)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define QUANTITY_ARG     (uint16_t)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define SAMPLE_TIME_ARG  mxGetPr(ssGetSFcnParam(S, 5))[0]
#define BYTE_SWAP_ARG    (bool)mxGetPr(ssGetSFcnParam(S, 6))[0]
#define NUMBER_OF_ARGS   7

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

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

    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 1);

    switch (TABLE_ARG) {
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
    default:
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

    cServerInterface *Interface = NULL;
    cServerBlock *Block = NULL;
    cNode *Node = NULL;

    Root.init();

    /* Add a server interface */
    ret = Root.addInterface(INTERFACE_ID_ARG, false, (cInterface **)&Interface);
    if (ret != 0) {
        sprintf(ErrMsg, "MBRTU | Failed to initialize server interface");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a node to the interface */
    ret = Interface->addNode(NODE_ID_ARG, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "MBRTU | Failed to initialize server node");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a block to the node */
    ret = Node->addBlock(0, (cServerBlock **)&Block);
    if (ret != 0) {
        sprintf(ErrMsg, "MBRTU | Failed to initialize server read block");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Block);
}

static void sg_ModelStep(SimStruct *S)
{
    int32_t ret = 0;
    cServerBlock *Block = (cServerBlock *)ssGetPWorkValue(S, 0);

    /* Check if the block is initialized */
    if (!Block->InitDone) {
        /* Initialize the block */
        ret = Block->init(TABLE_ARG, INDEX_ARG, QUANTITY_ARG, BYTE_SWAP_ARG);
        if (ret != 0) {
            sprintf(ErrMsg, "MBRTU | Failed to initialize server read block");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    } else {
        /* Read data and output */
        void *Port = (void *)ssGetOutputPortSignal(S, 0);
        Block->read(Port);
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
