#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_iec_server_readwrite_s

/* Includes */
#include "simstruc.h"
#include <tmwtypes.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#include "iec_def.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#ifndef MATLAB_MEX_FILE
#include "iec.h"
#include "iec_server_node.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace iec61850;
#endif

/* Defines */
#define SERVER_ID_ARG      (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define READ_ITEMS_ARG     ssGetSFcnParam(S, 1)
#define WRITE_ITEMS_ARG    ssGetSFcnParam(S, 2)
#define TIME_ITEMS_ARG     ssGetSFcnParam(S, 3)
#define CONTROL_ITEMS_ARG  ssGetSFcnParam(S, 4)
#define READ_LENGTH_ARG    (uint16_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define WRITE_LENGTH_ARG   (uint16_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define TIME_LENGTH_ARG    (uint16_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define CONTROL_LENGTH_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define PORT_TYPE_ARG      ((uint8_T)mxGetPr(ssGetSFcnParam(S, 9))[0] - 1)
#define SAMPLE_TIME_ARG    mxGetPr(ssGetSFcnParam(S, 10))[0]
#define NUMBER_OF_ARGS     11

#define SINGLE_QUANTITY 1

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

    /* Set all parameters to non-tunable */
    for (i = 0; i < 0; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetNumInputPorts(S, WRITE_LENGTH_ARG); // @suppress("Statement has no effect")
    for (i = 0; i < WRITE_LENGTH_ARG; i++) {
        ssSetInputPortWidth(S, i, 1);
        ssSetInputPortDataType(S, i, PORT_TYPE_ARG);
        ssSetInputPortRequiredContiguous(S, i, 1);
        ssSetInputPortDirectFeedThrough(S, i, 1);
    }

    ssSetNumOutputPorts(S, READ_LENGTH_ARG); // @suppress("Statement has no effect")
    for (i = 0; i < READ_LENGTH_ARG; i++) {
        ssSetOutputPortWidth(S, i, 1);
        ssSetOutputPortDataType(S, i, PORT_TYPE_ARG);
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

static void sg_ModelLoad(SimStruct *S) {}
static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    uint32_t i = 0;
    int32_t ret = 0;
    cServerReadWrite *ReadWrite = NULL;
    cServerNode *Node = NULL;

    /* Add the server node */
    ret = Root.addNode(SERVER_ID_ARG, false, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to add server node %i", SERVER_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add the block to the server */
    ret = Node->addReadWrite((cServerReadWrite **)&ReadWrite);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to add server block");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* new read */
    if (mxGetN(READ_ITEMS_ARG) > 0) { // Check if read ports are set

        std::vector<std::string> ItemPaths;

        /* Allocate memory for the data item paths string */
        char_T *PathList = (char_T *)malloc(mxGetN(READ_ITEMS_ARG) + 1);
        if (PathList == NULL) {
            sprintf(ErrMsg, "MMS | Out of memory");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Copy the string from the block parameter */
        if ((mxGetString(READ_ITEMS_ARG, PathList, 1 + mxGetN(READ_ITEMS_ARG)) != 0)) {
            sprintf(ErrMsg, "MMS | Failed to get data item path");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Extract the data item paths */
        ItemPaths = iec61850::extractDataItemPaths(PathList);
        if (ItemPaths.size() != READ_LENGTH_ARG) {
            sprintf(ErrMsg, "MMS | Failed to get data item path (%i!=%i)", int(ItemPaths.size()),
                    READ_LENGTH_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* No longer needed */
        free(PathList);

        /* Register the data items */
        for (i = 0; i < ItemPaths.size(); i++) {
            std::string ItemPath = ItemPaths[i];

            ReadWrite->stReadVect.push_back(
                ReadWrite->remFcConstraint(ItemPath, ReadWrite->fcReadVect));
        }

        for (std::vector<std::string>::iterator rit = ReadWrite->stReadVect.begin();
             rit != ReadWrite->stReadVect.end(); rit++) {
            rit->replace(rit->find("/"), 1, "$");
            while (rit->find(".") != std::string::npos) {
                rit->replace(rit->find("."), 1, "$");
            }
        }
    }

    /* new write */
    if (mxGetN(WRITE_ITEMS_ARG) > 0) { // Check if write ports are set

        std::vector<std::string> ItemPaths;

        /* Allocate memory for the data item paths string */
        char_T *PathList = (char_T *)malloc(mxGetN(WRITE_ITEMS_ARG) + 1);
        if (PathList == NULL) {
            sprintf(ErrMsg, "MMS | Out of memory");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Copy the string from the block parameter */
        if ((mxGetString(WRITE_ITEMS_ARG, PathList, 1 + mxGetN(WRITE_ITEMS_ARG)) != 0)) {
            sprintf(ErrMsg, "MMS | Failed to get data item path");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Extract the data item paths */
        ItemPaths = iec61850::extractDataItemPaths(PathList);
        if (ItemPaths.size() != WRITE_LENGTH_ARG) {
            sprintf(ErrMsg, "MMS | Failed to get data item path (%i!=%i)", int(ItemPaths.size()),
                    WRITE_LENGTH_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* No longer needed */
        free(PathList);

        /* Register the data items */
        for (i = 0; i < ItemPaths.size(); i++) {
            std::string ItemPath = ItemPaths[i];

            ReadWrite->stWriteVect.push_back(
                ReadWrite->remFcConstraint(ItemPath, ReadWrite->fcWriteVect));
        }

        for (std::vector<std::string>::iterator rit = ReadWrite->stWriteVect.begin();
             rit != ReadWrite->stWriteVect.end(); rit++) {
            rit->replace(rit->find("/"), 1, "$");
            while (rit->find(".") != std::string::npos) {
                rit->replace(rit->find("."), 1, "$");
            }
        }
    }

    /* new time */
    if (mxGetN(TIME_ITEMS_ARG) > 0) { // Check if time ports are set

        std::vector<std::string> ItemPaths;

        /* Allocate memory for the data item paths string */
        char_T *PathList = (char_T *)malloc(mxGetN(TIME_ITEMS_ARG) + 1);
        if (PathList == NULL) {
            sprintf(ErrMsg, "MMS | Out of memory");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Copy the string from the block parameter */
        if ((mxGetString(TIME_ITEMS_ARG, PathList, 1 + mxGetN(TIME_ITEMS_ARG)) != 0)) {
            sprintf(ErrMsg, "MMS | Failed to get data item path");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Extract the data item paths */
        ItemPaths = iec61850::extractDataItemPaths(PathList);
        if (ItemPaths.size() != TIME_LENGTH_ARG) {
            sprintf(ErrMsg, "MMS | Failed to get data item path (%i!=%i)", int(ItemPaths.size()),
                    TIME_LENGTH_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* No longer needed */
        free(PathList);

        /* Register the data items */
        for (i = 0; i < ItemPaths.size(); i++) {
            std::string ItemPath = ItemPaths[i];

            ReadWrite->stTimeVect.push_back(
                ReadWrite->remFcConstraint(ItemPath, ReadWrite->fcTimeVect));
        }

        for (std::vector<std::string>::iterator rit = ReadWrite->stTimeVect.begin();
             rit != ReadWrite->stTimeVect.end(); rit++) {
            rit->replace(rit->find("/"), 1, "$");
            while (rit->find(".") != std::string::npos) {
                rit->replace(rit->find("."), 1, "$");
            }
        }
    }

    /* new control */
    if (mxGetN(CONTROL_ITEMS_ARG) > 0) { // Check if control ports are set

        std::vector<std::string> ItemPaths;

        /* Allocate memory for the data item paths string */
        char_T *PathList = (char_T *)malloc(mxGetN(CONTROL_ITEMS_ARG) + 1);
        if (PathList == NULL) {
            sprintf(ErrMsg, "MMS | Out of memory");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Copy the string from the block parameter */
        if ((mxGetString(CONTROL_ITEMS_ARG, PathList, 1 + mxGetN(CONTROL_ITEMS_ARG)) != 0)) {
            sprintf(ErrMsg, "MMS | Failed to get data item path");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Extract the data item paths */
        ItemPaths = iec61850::extractDataItemPaths(PathList);
        if (ItemPaths.size() != CONTROL_LENGTH_ARG) {
            sprintf(ErrMsg, "MMS | Failed to get data item path (%i!=%i)", int(ItemPaths.size()),
                    CONTROL_LENGTH_ARG);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* No longer needed */
        free(PathList);

        /* Register the data items */
        for (i = 0; i < ItemPaths.size(); i++) {
            std::string ItemPath = ItemPaths[i];

            ReadWrite->stControlVect.push_back(
                ReadWrite->remFcConstraint(ItemPath, ReadWrite->fcControlVect));
        }

        for (std::vector<std::string>::iterator rit = ReadWrite->stControlVect.begin();
             rit != ReadWrite->stControlVect.end(); rit++) {
            rit->replace(rit->find("/"), 1, "$");
            while (rit->find(".") != std::string::npos) {
                rit->replace(rit->find("."), 1, "$");
            }
        }
    }

    /* Initialize the ReadWrite */
    ret = ReadWrite->init(READ_LENGTH_ARG, WRITE_LENGTH_ARG, TIME_LENGTH_ARG, CONTROL_LENGTH_ARG,
                          PORT_TYPE_ARG);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to initialize server block");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, ReadWrite);

#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    cServerReadWrite *ReadWrite = (cServerReadWrite *)ssGetPWorkValue(S, 0);

    // SG_PRINTF_ERROR("%i %i\n", WRITE_LENGTH_ARG, READ_LENGTH_ARG);

    for (int i = 0; i < WRITE_LENGTH_ARG; i++) {
        void *p = (void *)ssGetInputPortSignal(S, i);
        ReadWrite->processInputPort(i, p);
    }
    for (int i = 0; i < READ_LENGTH_ARG; i++) {
        void *p = (void *)ssGetOutputPortSignal(S, i);
        ReadWrite->updateOutputPort(i, p);
    }

#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
#endif
}

#include "sg_sfcn_glue.h" // Code generation glue
