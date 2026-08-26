#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_send_s_v3

#include "sg_io682_v3.h"

#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "../arinc429/lib/sg_IO682/include/cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

enum SendParamNumbers
{
    PAR_MODULE_ID,
    PAR_CHANNEL,        // Between 1 and 16
    PAR_SAMPLE_TIME,
    PAR_NUMBER_OF_ARGS
};

struct SendParams
{
    int moduleId;
    int channel;
    double sampleTime;
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
    P_WORK_PARAMS,
    P_WORK_ERROR,
    LENGTH_P_WORK_VEC
};

static int checkTxChannelNumber(const SendParams *params, SgError *err);
static void setErrorStatus(SimStruct *S, SgError *err, int moduleId);
static SendParams *newSendParams(SimStruct *S);
static void deleteSendParams(SendParams *params);
static void debugPrintParams(const SendParams *params);

static void mdlInitializeSizes(SimStruct *S)
{
    SgMaskInit_SetupSettingsArgs args;
    args.numberOfParams       = PAR_NUMBER_OF_ARGS;
    args.integerWorkVecLength = LENGTH_I_WORK_VEC;
    args.realWorkVecLength    = LENGTH_R_WORK_VEC;
    args.pointerWorkVecLength = LENGTH_P_WORK_VEC;

    if (sgMaskInit_initSizesForRegularBlock(S, &args))
    {
        static char initErrorMsg[128];
        sprintf(initErrorMsg,
            "In IO682, Send block, ID %d: Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", sgParam_getInt(S, PAR_MODULE_ID), PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, initErrorMsg);
        return;
    }

    sgMaskInit_setNoOutputPorts(S);

    // sgMaskInit_setOutputPorts(S, numOutputPorts, outputPortWidth);

    ssSetNumInputPorts(S, 1);
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
}

#ifdef MATLAB_MEX_FILE
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct *S, int port, const DimsInfo_T *info)
{
    if (!ssSetInputPortDimensionInfo(S, port, info))
    {
        return;
    }
}
#endif

static void mdlInitializeSampleTimes(SimStruct *S)
{
    double sampleTime = sgParam_getDouble(S, PAR_SAMPLE_TIME);
    sgMaskInit_initSampleTimesForRegularBlock(S, sampleTime);
}

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    SendParams *params = newSendParams(S);
    SgError *error = sgError_new();

    if (sg_isModelInit())
    {
        debugPrintParams(params);
    }

    // arx30init downloads the slave processor at model download time. In addition, all of the per
    // channel initializations are done in arx30init.

    if (checkTxChannelNumber(params, error))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }

    ssSetPWorkValue(S, P_WORK_PARAMS, params);
    ssSetPWorkValue(S, P_WORK_ERROR, error);
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    SendParams *params = static_cast<SendParams*>(ssGetPWorkValue(S, P_WORK_PARAMS));
    SgError *error = static_cast<SgError*>(ssGetPWorkValue(S, P_WORK_ERROR));

    int numMessages = *ssGetInputPortDimensions(S, 0);
    Io682_ArincMsg_t **signalPtrs = (Io682_ArincMsg_t **)ssGetInputPortSignalPtrs(S, 0);

    // Note that the input signals are assumed to be Io682_ArincMsg_t values masquerading as doubles
    // with the data payload in the "word" member.

    short result;
    short boardId = params->moduleId - 1;
    short channel = params->channel - 1;
    for (int i = 0; i < numMessages; i++)
    {
        result = arx30_putword(boardId, channel, signalPtrs[i]->word);

        if (result != ARS_NORMAL)
        {
            sgError_setMsg(error, "Transmit error %d on board %d chan %d: %s\n", result, boardId,
                channel, arx30_get_error(result));
            setErrorStatus(S, error, params->moduleId);
            return;
        }
    }
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    SendParams *params = static_cast<SendParams*>(ssGetPWorkValue(S, P_WORK_PARAMS));
    SgError *error = static_cast<SgError*>(ssGetPWorkValue(S, P_WORK_ERROR));

    sgError_delete(error);
    deleteSendParams(params);
#endif
}

#ifndef MATLAB_MEX_FILE

static int checkTxChannelNumber(const SendParams *params, SgError *err)
{
    int boardId = params->moduleId - 1;
    int channel = params->channel - 1;

    if ((channel < 0) || (channel >= arx30_num_xchans(boardId)))
    {
        sgError_setMsg(err, "Channel %d is not available on this I/O module", params->channel);
        return -1;
    }
    return 0;
}

static void setErrorStatus(SimStruct *S, SgError *err, int moduleId)
{
    sgError_setPreamble(err, "IO682", "Send", moduleId);
    ssSetErrorStatus(S, sgError_getMsg(err));
}

static SendParams *newSendParams(SimStruct *S)
{
    SendParams *params = new SendParams;

    params->moduleId   = sgParam_getInt(S, PAR_MODULE_ID);
    params->channel    = sgParam_getInt(S, PAR_CHANNEL);
    params->sampleTime = sgParam_getDouble(S, PAR_SAMPLE_TIME);

    return params;
}

static void deleteSendParams(SendParams *params)
{
    delete params;
}

static void debugPrintParams(const SendParams *params)
{
    SG_PARAM_PRINT_INT(params, moduleId);
    SG_PARAM_PRINT_INT(params, channel);
    SG_PARAM_PRINT_DOUBLE(params, sampleTime);
}

#endif  // MATLAB_MEX_FILE

#include "sg_sfcn_glue.h"   // Code generation glue
