#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbtcp_server_write_s

/* Includes */
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "mb_def.h"

#ifndef MATLAB_MEX_FILE
#include "mbtcp.h"
#include "mbtcp_server_block.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace modbusTCP;
#endif

/* Defines */
#define SERVER_ID_ARG   (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0]
#define UNIT_ID_ARG     (uint8_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define TABLE_ARG       (uint16_t)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define INDEX_ARG       (uint16_t)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define QUANTITY_ARG    (uint16_t)mxGetPr(ssGetSFcnParam(S, 4))[0]
#define SAMPLE_TIME_ARG mxGetPr(ssGetSFcnParam(S, 5))[0]
#define NUMBER_OF_ARGS  6

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

    ssSetNumOutputPorts(S, 0);
    ssSetNumInputPorts(S, 1);

    switch (TABLE_ARG) {
    case MB_TABLE_TYPE_COIL:
    case MB_TABLE_TYPE_DISCRETE:
        ssSetInputPortWidth(S, 0, QUANTITY_ARG);
        ssSetInputPortDataType(S, 0, SS_BOOLEAN);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
        break;
    case MB_TABLE_TYPE_HOLDING:
    case MB_TABLE_TYPE_INPUT:
        ssSetInputPortWidth(S, 0, QUANTITY_ARG);
        ssSetInputPortDataType(S, 0, SS_UINT16);
        ssSetInputPortRequiredContiguous(S, 0, 1);
        ssSetInputPortDirectFeedThrough(S, 0, 1);
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
    cServerBlock *Block = NULL;
    cServerNode *Node = NULL;
    cUnit *Unit = NULL;

    /* Add a server node */
    ret = Root.addNode(SERVER_ID_ARG, false, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus server node %i!", ret, SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a unit to the node */
    ret = Node->addUnit(UNIT_ID_ARG, (cUnit **)&Unit);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding Modbus unit %i to server node %i!", ret, UNIT_ID_ARG,
                SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a block to the unit */
    ret = Unit->addBlock(MB_BLOCK_TYPE_SERVER_READ, (cServerBlock **)&Block);
    if (ret != 0) {
        sprintf(ErrMsg, "Error %i while adding a block to unit %i!", ret, UNIT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Block);
}

static void sg_ModelStep(SimStruct *S)
{
    int32_t ret = 0;
    cServerBlock *Block = (cServerBlock *)ssGetPWorkValue(S, 0);

    if (!Block->InitDone) {
        /* Initialize the block */
        ret = Block->init(TABLE_ARG, INDEX_ARG, QUANTITY_ARG);

        if (ret != 0) {
            sprintf(ErrMsg, "Error %i while initializing modbus server(%d) unit(%d) write block!",
                    ret, SERVER_ID_ARG, UNIT_ID_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    } else {
        /* Read data and output */
        void *Port = (void *)ssGetInputPortSignal(S, 0);
        Block->write(Port);
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#endif

#include "sg_sfcn_glue.h" // Code generation glue
