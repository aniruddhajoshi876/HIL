#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mbrtu_server_setup_s

/* Includes */
#include <stdint.h>

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "mb_def.h"
#include "mbrtu.h"

#include <fcntl.h>
#include <termios.h>
#endif

// sg_callback.h converts traditional level 2 S-function interface to Speedgoat stage 3 interface
// (see https://speedgoat.atlassian.net/wiki/spaces/PnS/pages/144113665)
#define SG_EARLY_INIT // Causes sg_ModelLoad() to be called upon tg.load for R2024a and later
#define SG_HAS_MDL_EXIT
#include "sg_callback.h"

#ifndef MATLAB_MEX_FILE
using namespace modbusRTU;
#endif

/* Defines */
#define MODULE_TYPE_ARG    (uint16_t)mxGetPr(ssGetSFcnParam(S, 0))[0] // <-- Serial Interface
#define MODULE_ID_ARG      (uint16_t)mxGetPr(ssGetSFcnParam(S, 1))[0]
#define CHANNEL_ARG        (uint8_t)mxGetPr(ssGetSFcnParam(S, 2))[0]
#define INTERFACE_ID_ARG   (uint16_t)mxGetPr(ssGetSFcnParam(S, 3))[0] // <-- Modbus
#define NODE_ID_ARG        ssGetSFcnParam(S, 4)
#define TABLE_DIM_ARG      ssGetSFcnParam(S, 5)
#define RESPONSE_DELAY_ARG (uint32_t)mxGetPr(ssGetSFcnParam(S, 6))[0]
#define SWAP_ARG           (bool)mxGetPr(ssGetSFcnParam(S, 7))[0]
#define SAMPLE_TIME_ARG    mxGetPr(ssGetSFcnParam(S, 8))[0]
#define NUMBER_OF_ARGS     9

#define NUM_COIL_ARG(i) ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 0 * mxGetM(TABLE_DIM_ARG)]))
#define NUM_DISCRETE_ARG(i)                                                                        \
    ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 1 * mxGetM(TABLE_DIM_ARG)]))
#define NUM_HOLDING_ARG(i)                                                                         \
    ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 2 * mxGetM(TABLE_DIM_ARG)]))
#define NUM_INPUT_ARG(i) ((uint16_t)(mxGetPr(TABLE_DIM_ARG)[i + 3 * mxGetM(TABLE_DIM_ARG)]))

/* Definitions */
static char_T ErrMsg[256];

static void mdlInitializeSizes(SimStruct* S)
{
    uint32_t i = 0;

    /* Set and check parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set all parameters to non-tunable */
    for (i = 0; i < NUMBER_OF_ARGS; i++) {
        ssSetSFcnParamTunable(S, i, 0);
    }

    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 0);

    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE /* Do not place ASAP flag -> We need data from the serial blocks first! | SS_OPTION_PLACE_ASAP */);
}

static void mdlInitializeSampleTimes(SimStruct* S)
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

static void sg_ModelLoad(SimStruct *S)
{
    int32_t ret = 0;
    uint8_t Channel = 0;
    cServerInterface *Interface = NULL;
    char SerialDeviceName[MAX_LENGTH_SERIAL_DEVICE_NAME] = {0};
    sg_mod_info *ModuleInfo = NULL;
    void *ModuleData = NULL;
    MB_SERIAL_INFO_T SerialInfo = {0};

    // Board Type (0 = IO503, 1 = IO504, 2 = IO505, 3 = IO581, 4 = Onboard Serial)
    uint32_t BoardType = MODULE_TYPE_ARG - 1;
    int ModuleID = MODULE_ID_ARG;
    if (INTERFACE_TYPE[BoardType] == SG_ONBOARD_SERIAL_UART) {
        ModuleID = 1;
    }

    /* Find the serial module in the module registry */
    ModuleInfo = (sg_mod_info *)sg_module_get_single(INTERFACE_TYPE[BoardType], ModuleID);
    if (!ModuleInfo) {
        sprintf(ErrMsg, "MBRTU | Failed to find serial module %i", ModuleID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Retrieve custom data from of the serial module */
    ModuleData = (void *)ModuleInfo->custom_data;
    if (!ModuleData) {
        sprintf(ErrMsg, "MBRTU | Failed to retrieve custom data of serial module %i", ModuleID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (INTERFACE_TYPE[BoardType] == SG_ONBOARD_SERIAL_UART) {
        Channel = CHANNEL_ARG;
    } else {
        Channel = (CHANNEL_ARG - 1);
    }

    if (INTERFACE_TYPE[BoardType] == SG_ONBOARD_SERIAL_UART) {

        OnBoardSerial_Device_t *Onboard_ModuleData = (OnBoardSerial_Device_t *)ModuleData;

        SerialInfo.enabled = Onboard_ModuleData->enabled[Channel];

    } else {

        Io5xx_Device_t *IO5xx_ModuleData = (Io5xx_Device_t *)ModuleData;

#if defined(__QNX__)
        SerialInfo.SerialIndex = IO5xx_ModuleData->devNumber + Channel;
#elif defined(__linux__)
        SerialInfo.SerialIndex = IO5xx_ModuleData->ttyNumberList[Channel];
#endif
        SerialInfo.enabled = IO5xx_ModuleData->enabled[Channel];
    }

    /* Check if channel is enabled */
    if (!SerialInfo.enabled) {
        sprintf(ErrMsg, "MBRTU | Channel %d is not enabled", CHANNEL_ARG);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (INTERFACE_TYPE[BoardType] == SG_ONBOARD_SERIAL_UART) {

        /* Open the serial driver */
        SerialInfo.fd = sg_serial_device_open(Channel);
        if (SerialInfo.fd == -1) {
            sprintf(ErrMsg, "MBRTU | Failed to open %s", SerialDeviceName);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Flush bytes in the device's input buffer */
        sg_serial_device_flush(Channel, FlushOnly);

    } else {

        /* Create device name from index */
        memset(SerialDeviceName, 0, sizeof(SerialDeviceName));
#if defined(__QNX__)
        sprintf(SerialDeviceName, "/dev/ser%d", SerialInfo.SerialIndex);
#elif defined(__linux__)
        sprintf(SerialDeviceName, "/dev/ttySTDRV002_%d", SerialInfo.SerialIndex);
#endif

        /* Open the serial driver */
        SerialInfo.fd = open(SerialDeviceName, O_RDWR | O_NONBLOCK);
        if (SerialInfo.fd == -1) {
            sprintf(ErrMsg, "MBRTU | Failed to open %s", SerialDeviceName);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Flush bytes in the device's input buffer */
        if (tcflush(SerialInfo.fd, TCIFLUSH) != 0) {
            sprintf(ErrMsg, "MBRTU | Failed to flush %s", SerialDeviceName);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

    }

    /* Init the Modbus root structure */
    Root.init();

    /* Add a server interface */
    ret = Root.addInterface(INTERFACE_ID_ARG, false, (cInterface **)&Interface);
    if (ret != 0) {
        sprintf(ErrMsg, "MBRTU | Failed to add server interface");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Initialize the interface */
    ret = Interface->init(MODULE_TYPE_ARG, MODULE_ID_ARG, CHANNEL_ARG, RESPONSE_DELAY_ARG, SWAP_ARG,
                          SerialInfo);
    if (ret != 0) {
        sprintf(ErrMsg, "MBRTU | Failed to initialize server interface");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* For each node */
    for (uint32_t i = 0; i < mxGetN(NODE_ID_ARG); i++) {
        cNode *Node = NULL;

        uint8_t NodeID = (uint8_t)mxGetPr(NODE_ID_ARG)[i];

        /* Add a remote station relation to the master module */
        ret = Interface->addNode(NodeID, (cNode **)&Node);
        if (ret != 0) {
            sprintf(ErrMsg, "MBRTU | Failed to add server node");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        /* Initialize node */
        ret = Node->init(NUM_COIL_ARG(i), NUM_DISCRETE_ARG(i), NUM_HOLDING_ARG(i), NUM_INPUT_ARG(i),
                         false);
        if (ret != 0) {
            sprintf(ErrMsg, "MBRTU | Failed to initialize server node");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }
}

static void sg_ModelStart(SimStruct* S) {}

static void sg_ModelStep(SimStruct* S)
{
    {
        static bool FirstStep = true;
        static uint64_t StartDelayTimer = 0;
        if (FirstStep) {
            StartDelayTimer = getTime();
            FirstStep = false;
        }
        if ((getTime() - StartDelayTimer) > 100) {
            Root.start();
        }
    }
}

static void sg_ModelStop(SimStruct* S)
{
}

static void sg_ModelExit(SimStruct* S)
{
    Root.stop();
}
#endif

#include "sg_sfcn_glue.h" // Code generation glue
