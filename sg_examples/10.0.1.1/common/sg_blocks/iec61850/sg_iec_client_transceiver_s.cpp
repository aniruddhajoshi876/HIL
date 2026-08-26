#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_iec_client_transceiver_s

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
#include "iec_client_node.h"
#include "sg_common.h"
#include "sg_printf.h"
// #include <gulliver.h>
#endif

#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace iec61850;
#endif

/* Defines */

#define CLIENT_ID_ARG      (uint16_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define CONNECTION_ID_ARG  (uint16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define POLL_INTERVALL_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define READ_ITEMS_ARG     ssGetSFcnParam(S, 3)
#define WRITE_ITEMS_ARG    ssGetSFcnParam(S, 4)
#define READ_LENGTH_ARG    (uint16_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define WRITE_LENGTH_ARG   (uint16_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define PORT_TYPE_ARG      (uint8_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define CONTROL_ITEMS_ARG  ssGetSFcnParam(S, 8)
#define CONTROL_LENGTH_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define CONTROL_MODE_ARG   (boolean_T) mxGetPr(ssGetSFcnParam(S, 10))[0]
#define CONTROL_TEST_ARG   (boolean_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define SAMPLE_TIME_ARG    mxGetPr(ssGetSFcnParam(S, 12))[0]
#define NUMBER_OF_ARGS     13

#define SINGLE_QUANTITY 1
#define MAX_STRING_SIZE 255
#define TYPE            (PORT_TYPE_ARG - 1)

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct *S) // @suppress("Unused static function")
{
    //	printf("mdlInitializeSizes");
    uint32_T i = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < 0; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    if (CONTROL_MODE_ARG) {
        ssSetNumInputPorts(S, (CONTROL_LENGTH_ARG * 2)); // @suppress("Statement has no effect")
        for (i = 0; i < (CONTROL_LENGTH_ARG * 2);
             i++) { // Add double amount of port for the enable ports

            ssSetInputPortWidth(S, i, SINGLE_QUANTITY);
            ssSetInputPortDataType(S, i, SS_BOOLEAN);
            ssSetInputPortRequiredContiguous(S, i, 1);
            ssSetInputPortDirectFeedThrough(S, i, 1);
        }
    } else {
        ssSetNumInputPorts(S, WRITE_LENGTH_ARG); // @suppress("Statement has no effect")
        for (i = 0; i < WRITE_LENGTH_ARG; i++) {
            if (TYPE == 9 || TYPE == 11) { // If we want to input string
                ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
                ssSetInputPortDataType(S, 0, SS_UINT8);
                break;
            } else if (TYPE == 10) { // Bit String
                ssSetInputPortWidth(S, i, 1);
                ssSetInputPortDataType(S, i, SS_UINT32);
            } else {
                ssSetInputPortWidth(S, i, 1);
                ssSetInputPortDataType(S, i, TYPE);
            }

            ssSetInputPortRequiredContiguous(S, i, 1);
            ssSetInputPortDirectFeedThrough(S, i, 1);
        }
        ssSetNumOutputPorts(S, READ_LENGTH_ARG); // @suppress("Statement has no effect")
        for (i = 0; i < READ_LENGTH_ARG; i++) {
            if (TYPE == 9 || TYPE == 11) { // If we want to output string
                ssSetOutputPortWidth(S, 0, MAX_STRING_SIZE);
                ssSetOutputPortDataType(S, 0, SS_UINT8);
                break;
            } else if (TYPE == 10) { // Bit String
                ssSetOutputPortWidth(S, i, 1);
                ssSetOutputPortDataType(S, i, SS_UINT32);
            } else {
                ssSetOutputPortDataType(S, i, TYPE);
                ssSetOutputPortWidth(S, i, 1);
            }
        }
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

/* Do this unknown and extremely dark magic, to set dynamic port sizes */
#ifdef MATLAB_MEX_FILE
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct *S, int port, const DimsInfo_T *dimsInfo)
{
    if (!ssSetInputPortDimensionInfo(S, port, dimsInfo)) {
        return;
    }
}

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
static void mdlSetOutputPortDimensionInfo(SimStruct *S, int port, const DimsInfo_T *dimsInfo)
{
    if (!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) {
        return;
    }
}
#endif // MATLAB_MEX_FILE

static void mdlInitializeSampleTimes(SimStruct *S) // @suppress("Unused static function")
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

static void sg_ModelLoad(SimStruct *S) {}
static void sg_ModelStart(SimStruct *S) // @suppress("Unused static function")
{
#ifndef MATLAB_MEX_FILE

    uint32_t i = 0;
    int32_t ret = 0;
    cClientTransceiver *Transceiver = NULL;
    cClientNode *Node = NULL;
    cClientConnection *Connection = NULL;

    SG_PRINTF_DEBUG("MDL_START in Transceiver\n");

    /* Add a client node */
    ret = Root.addNode(CLIENT_ID_ARG, true, (cNode **)&Node);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to add client node %i", CLIENT_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a client connection to the node */
    ret = Node->addConnection(CONNECTION_ID_ARG, (cClientConnection **)&Connection);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to add client connection %i", CONNECTION_ID_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Add a transceiver  to the connection */
    ret = Connection->addTransceiver((cClientTransceiver **)&Transceiver);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to add transceiver");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Propagate the data items */
    if (CONTROL_MODE_ARG) {
        if (mxGetN(CONTROL_ITEMS_ARG) > 0) {

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
                ret = Transceiver->addDataItem(MMS_DATAITEM_TYPE_CONTROL, i, TYPE,
                                               iec61850::getDataTypeLength(TYPE), ItemPath);
                if (ret != 0) {
                    sprintf(ErrMsg, "MMS | Failed to add control items");
                    ssSetErrorStatus(S, ErrMsg);
                    return;
                }
            }
        }
    } else {

        if (mxGetN(READ_ITEMS_ARG) > 0) {

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
                ret = Transceiver->addDataItem(MMS_DATAITEM_TYPE_READ, i, TYPE,
                                               iec61850::getDataTypeLength(TYPE), ItemPath);
                if (ret != 0) {
                    sprintf(ErrMsg, "MMS | Failed to add data items");
                    ssSetErrorStatus(S, ErrMsg);
                    return;
                }
            }
        }

        if (mxGetN(WRITE_ITEMS_ARG) > 0) {

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
                ret = Transceiver->addDataItem(MMS_DATAITEM_TYPE_WRITE, i, TYPE,
                                               iec61850::getDataTypeLength(TYPE),
                                               (char *)ItemPath.c_str());
                if (ret != 0) {
                    sprintf(ErrMsg, "MMS | Failed to add data items");
                    ssSetErrorStatus(S, ErrMsg);
                    return;
                }
            }
        }
    }

    /* Initialize the transceiver */
    ret = Transceiver->init(POLL_INTERVALL_ARG, READ_LENGTH_ARG, WRITE_LENGTH_ARG,
                            CONTROL_LENGTH_ARG, CONTROL_MODE_ARG, CONTROL_TEST_ARG, TYPE);
    if (ret != 0) {
        sprintf(ErrMsg, "MMS | Failed to initialize client transceiver");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, Transceiver);
#endif
}

static void sg_ModelStep(SimStruct *S) // @suppress("Unused static function")
{
#ifndef MATLAB_MEX_FILE

    cClientTransceiver *Transceiver = (cClientTransceiver *)ssGetPWorkValue(S, 0);

    if (CONTROL_MODE_ARG) {
        for (int i = 0; i < CONTROL_LENGTH_ARG; i++) {
            bool *Operate = (bool *)ssGetInputPortSignal(S, 2 * i);
            void *Data = (void *)ssGetInputPortSignal(S, 2 * i + 1);
            Transceiver->updateControlItem(i, *Operate, Data);
        }
    } else {
        for (int i = 0; i < READ_LENGTH_ARG; i++) {
            void *Data = (void *)ssGetOutputPortSignal(S, i);
            Transceiver->updateReadItem(i, true, Data);
        }
        for (int i = 0; i < WRITE_LENGTH_ARG; i++) {
            void *Data = (void *)ssGetInputPortSignal(S, i);
            Transceiver->updateWriteItem(i, true, Data);
        }
    }

#endif
}

static void sg_ModelStop(SimStruct *S) // @suppress("Unused static function")
{
#ifndef MATLAB_MEX_FILE
#endif
}

#include "sg_sfcn_glue.h" // Code generation glue
