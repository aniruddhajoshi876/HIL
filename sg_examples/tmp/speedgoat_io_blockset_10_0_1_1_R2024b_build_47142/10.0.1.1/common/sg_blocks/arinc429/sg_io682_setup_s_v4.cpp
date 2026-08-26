#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_setup_s_v4

#define SG_HAS_MDL_EXIT //Causes sg_ModelExit() to be called upon process exit
#define SG_EARLY_INIT   //Causes sg_ModelLoad() to be called upon tg.load for R2024a and later

#include "sg_io682_v4.h"

#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

#define IO682_2_2   1
#define IO682_4_4   2
#define IO682_8_8   3
#define IO682_16_16 4

enum SetupParamNumbers
{
    PAR_MODULE_ID,
    PAR_DEVICE_VARIANT,
    PAR_PCI_SLOT,
    PAR_DEVICE_ID,
    PAR_SCHEDULED_MESSAGES,
    PAR_CH_IN_CONFIG,
	PAR_CH_OUT_CONFIG,
    PAR_NUMBER_OF_ARGS
};

struct SetupParams
{
    int moduleId;       // Is between 1 and 16
    SgParam_IntVec *pciSlot;
    int deviceId;       // 0x430, 0x530, 0x830, or 0x821
};

enum IntegerWorkVector
{
    LENGTH_I_WORK_VEC
};

enum RealWorkVector
{
    LENGTH_R_WORK_VEC
};

enum PointerWorkVector
{
    LENGTH_P_WORK_VEC
};

static int checkParams(SetupParams *params, SgError *err);
static void setErrorStatus(SimStruct *S, SgError *err, int moduleId);
static SetupParams *newSetupParams(SimStruct *S);
static void deleteSetupParams(SetupParams *params);
static void debugPrintParams(const SetupParams *params);

static void mdlInitializeSizes(SimStruct *S)
{
    SgMaskInit_SetupSettingsArgs args;
    args.numberOfParams       = PAR_NUMBER_OF_ARGS;
    args.integerWorkVecLength = LENGTH_I_WORK_VEC;
    args.realWorkVecLength    = LENGTH_R_WORK_VEC;
    args.pointerWorkVecLength = LENGTH_P_WORK_VEC;

    if (sgMaskInit_initSizesForSetupBlock(S, &args))
    {
        static char initErrorMsg[128];
        sprintf(initErrorMsg,
            "In IO682, Setup block, ID %d: Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", sgParam_getInt(S, PAR_MODULE_ID), PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, initErrorMsg);
        return;
    }
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    sgMaskInit_initSampleTimesForSetupBlock(S);
}

static void sg_ModelLoad(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    SetupParams *params = newSetupParams(S);
    SgError *error = sgError_new();
    sg_mod_info *mod_info;

    debugPrintParams(params);

    if (checkParams(params, error))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }

    // Check if another block has already registered for the same module
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, (uint32_t)params->moduleId);
    if (mod_info == NULL)
    {
        mod_info = sg_module_register(SG_MODULE_TYPE_IO682, (uint32_t)params->moduleId);
    }
    else
    {
        SG_PRINTF(DEBUG,"IO682 Setup: Do not register module\n");
        return;
    }

    int boardId = params->moduleId - 1;
    if (io682_configPciAddresses(params->deviceId, params->pciSlot, params->moduleId, boardId,
            error))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }
    if (io682_initArincApi(boardId, error))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }

    //Check board variant
    CEI_INT16 nRxCh = 0;
    CEI_INT16 nTxCh = 0;
    switch (sgParam_getInt(S, PAR_DEVICE_VARIANT))
    {
        case IO682_2_2: nRxCh = 2; nTxCh = 2; break;
        case IO682_4_4: nRxCh = 4; nTxCh = 4; break;
        case IO682_8_8: nRxCh = 8; nTxCh = 8; break;
        //case IO682_16_1: nRxCh = 16; nTxCh = 1; break;    //Old version
        case IO682_16_16: nRxCh = 16; nTxCh = 16; break;
        //case IO682_8_8_4_4: nRxCh = 8; nTxCh = 8; break;    //Additionally 4 digital I/O lines, not supported anymore
        default: ssSetErrorStatus(S, "Unknown Board Variant\n"); return;
    }
    if ((nRxCh != arx30_num_rchans(boardId)) || (nTxCh != arx30_num_xchans(boardId)))
    {
        static char msg[256];
        sprintf(msg, "Selected board variant does not match. Num RX channels: %d, num TX channels: %d\n",arx30_num_rchans(boardId),arx30_num_xchans(boardId));
        ssSetErrorStatus(S, msg);
        return;
    }

    // This needs to be set before initializing the API (aka loading the slave processor).
    // However, we don't do this and it still works.
    if (io682_setConcurrencyMode(boardId, error))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }
    if ((mxGetM(ssGetSFcnParam(S,PAR_SCHEDULED_MESSAGES)) != 0) &&
        (mxGetN(ssGetSFcnParam(S,PAR_SCHEDULED_MESSAGES)) == 5))
    {
        if (io682_configScheduler(S, params->moduleId, error, ssGetSFcnParam(S, PAR_SCHEDULED_MESSAGES)))
        {
            setErrorStatus(S, error, params->moduleId);
            return;
        }
    }
    if (io682_configChannels(S, params->moduleId, error,ssGetSFcnParam(S, PAR_CH_IN_CONFIG),ssGetSFcnParam(S, PAR_CH_OUT_CONFIG)))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }

    SG_PRINTF(INFO, "Speedgoat IO682, ID: %d, Initialization OK\n", params->moduleId);

    sgError_delete(error);
    deleteSetupParams(params);
#endif
}

static void sg_ModelStart(SimStruct* S)
{
    SetupParams *params = newSetupParams(S);
    SgError *error = sgError_new();
    int boardId = params->moduleId - 1;

    if (io682_startDriver(boardId, error))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }

    sgError_delete(error);
    deleteSetupParams(params);
}

static void sg_ModelStep(SimStruct *S)
{
}

static void sg_ModelStop(SimStruct *S)
{
}

static void sg_ModelExit(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    int boardId = sgParam_getInt(S, PAR_MODULE_ID) - 1;
    char error[128];

    int result = arx30_reset(boardId);
    if (result != ARS_NORMAL)
    {
        sprintf(error, "Failed to reset I/O module: %s", arx30_get_error(result));
        SG_PRINTF(WARNING, "%s", error);
        return;
    }

    sg_module_unregister(SG_MODULE_TYPE_IO682, (uint32_t)sgParam_getInt(S, PAR_MODULE_ID));
#endif
}

#ifndef MATLAB_MEX_FILE

static int checkParams(SetupParams *params, SgError *err)
{
    if ((params->moduleId < 1) || (params->moduleId > MAX_BOARDS))
    {
        sgError_setMsg(err, "Invalid module ID: %d", params->moduleId);
        return -1;
    }

    switch (params->deviceId)
    {
        case 0x430:     // CEI-430
        case 0x430A:    // CEI-430A
        case 0x530:     // CEI-530
        case 0x830:     // CEI-830
        case 0x831:     // CEI-830RX
        case 0x830A:    // RCEI-830A
            break;
        default:
            sgError_setMsg(err, "Unsupported device ID 0x%X", params->deviceId);
            return -1;
    }
    return 0;
}

static void setErrorStatus(SimStruct *S, SgError *err, int moduleId)
{
    sgError_setPreamble(err, "IO682", "Setup", moduleId);
    ssSetErrorStatus(S, sgError_getMsg(err));
}

static SetupParams *newSetupParams(SimStruct *S)
{
    SetupParams *params = new SetupParams;

    params->moduleId          = sgParam_getInt(S, PAR_MODULE_ID);
    params->pciSlot           = sgParam_newIntVec(S, PAR_PCI_SLOT);
    params->deviceId          = sgParam_getInt(S, PAR_DEVICE_ID);

    return params;
}

static void deleteSetupParams(SetupParams *params)
{
    sgParam_deleteIntVec(params->pciSlot);

    delete params;
}

static void debugPrintParams(const SetupParams *params)
{
    SG_PARAM_PRINT_INT(params, moduleId);
    SG_PARAM_PRINT_INT_VEC(params, pciSlot);
    SG_PARAM_PRINT_INT(params, timeSource);
    SG_PARAM_PRINT_INT(params, deviceId);
    SG_PARAM_PRINT_INT(params, timerRate);
}

#endif  // MATLAB_MEX_FILE

#include "sg_sfcn_glue.h"   // Code generation glue
