#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_update_scheduled_messages_s_v3

#include "sg_io682_v3.h"

#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "../arinc429/lib/sg_IO682/include/cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

enum ScheduleParamNumbers
{
    PAR_MODULE_ID,
    PAR_MESSAGE_INDEX,
    PAR_SAMPLE_TIME,
    PAR_NUMBER_OF_ARGS
};

struct ScheduleParams
{
    int moduleId;
    SgParam_IntVec *messageIndex;
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
    P_WORK_PREV_MSGS,
    P_WORK_PARAMS,
    LENGTH_P_WORK_VEC
};

static int loadPreviousMessages(SimStruct *S, ScheduleParams *params, SgError *err);
static void setErrorStatus(SimStruct *S, SgError *err, int moduleId);
static ScheduleParams *newScheduleParams(SimStruct *S);
static void deleteScheduleParams(ScheduleParams *params);
static void debugPrintParams(const ScheduleParams *params);

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
            "In IO682, Update Scheduled Messages block, ID %d: Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", sgParam_getInt(S, PAR_MODULE_ID), PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, initErrorMsg);
        return;
    }

    sgMaskInit_setNoOutputPorts(S);

    int portWidth = static_cast<int>(mxGetNumberOfElements(ssGetSFcnParam(S, PAR_MESSAGE_INDEX)));
    ssSetNumInputPorts(S, 2);

    ssSetInputPortWidth(S, 0, portWidth);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

    ssSetInputPortWidth(S, 1, portWidth);
    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortRequiredContiguous(S, 1, 1);
}

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
    ScheduleParams *params = newScheduleParams(S);
    SgError *error = sgError_new();

    if (sg_isModelInit())
    {
        debugPrintParams(params);
    }
    else
    {
        if (loadPreviousMessages(S, params, error))
        {
            setErrorStatus(S, error, params->moduleId);
            return;
        }
    }

    ssSetPWorkValue(S, P_WORK_PARAMS, params);
    sgError_delete(error);
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    ScheduleParams *params = static_cast<ScheduleParams*>(ssGetPWorkValue(S, P_WORK_PARAMS));
    AR_SCHEDULED_MSG_ENTRY_TYPE *currentEntries =
        static_cast<AR_SCHEDULED_MSG_ENTRY_TYPE*>(ssGetPWorkValue(S, P_WORK_PREV_MSGS));

    Io682_ArincMsg_t *newMessageRaw = (Io682_ArincMsg_t *)ssGetInputPortSignal(S, 0);
    double *newRateRaw = (double *)ssGetInputPortSignal(S, 1);

    for (int i = 0; i < params->messageIndex->len; ++i)
    {
        uint32_t newMessage = newMessageRaw[i].word;
        int newRate = (int)newRateRaw[i];

        bool hasChanged = (newMessage != currentEntries[i].data ||
                          (newRate != currentEntries[i].rate));
        if (hasChanged)
        {
            currentEntries[i].data = newMessage;
            currentEntries[i].rate = newRate;

            arx30_modify_msg((CEI_INT16)currentEntries[i].board,
                (CEI_INT16)currentEntries[i].channel, (CEI_INT16)currentEntries[i].messageIndex,
                (CEI_INT16)currentEntries[i].rate, currentEntries[i].data);
        }
    }
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    ScheduleParams *params = static_cast<ScheduleParams*>(ssGetPWorkValue(S, P_WORK_PARAMS));
    deleteScheduleParams(params);

    if (!sg_isModelInit())
    {
        AR_SCHEDULED_MSG_ENTRY_TYPE *schedEntry =
            static_cast<AR_SCHEDULED_MSG_ENTRY_TYPE*>(ssGetPWorkValue(S, P_WORK_PREV_MSGS));
        delete[] schedEntry;
    }
#endif
}

#ifndef MATLAB_MEX_FILE

static int loadPreviousMessages(SimStruct *S, ScheduleParams *params, SgError *err)
{
    int boardId = params->moduleId - 1;
    int numEntries = params->messageIndex->len;
    AR_SCHEDULED_MSG_ENTRY_TYPE *schedEntry = new AR_SCHEDULED_MSG_ENTRY_TYPE[numEntries];

    for (int i = 0; i < numEntries; ++i)
    {
        int messageIndex = params->messageIndex->val[i] - 1;
        int status = arx30_read_scheduled_msg_block(boardId, messageIndex, 1, &schedEntry[i]);
        if (status != ARS_NORMAL)
        {
            sgError_setMsg(err, "Could not read all scheduled messages.");
            return -1;
        }
        // The API function does not save the board field and the messageIndex always starts at
        // zero. So we have to fix this.
        schedEntry[i].board = boardId;
        schedEntry[i].messageIndex = messageIndex;
    }

    ssSetPWorkValue(S, P_WORK_PREV_MSGS, schedEntry);
    return 0;
}

static void setErrorStatus(SimStruct *S, SgError *err, int moduleId)
{
    sgError_setPreamble(err, "IO682", "Update scheduled messages", moduleId);
    ssSetErrorStatus(S, sgError_getMsg(err));
}

static ScheduleParams *newScheduleParams(SimStruct *S)
{
    ScheduleParams *params = new ScheduleParams;

    params->moduleId     = sgParam_getInt(S, PAR_MODULE_ID);
    params->messageIndex = sgParam_newIntVec(S, PAR_MESSAGE_INDEX);
    params->sampleTime   = sgParam_getDouble(S, PAR_SAMPLE_TIME);

    return params;
}

static void deleteScheduleParams(ScheduleParams *params)
{
    sgParam_deleteIntVec(params->messageIndex);
    delete params;
}

static void debugPrintParams(const ScheduleParams *params)
{
    SG_PARAM_PRINT_INT(params, moduleId);
    SG_PARAM_PRINT_INT_VEC(params, messageIndex);
    SG_PARAM_PRINT_DOUBLE(params, sampleTime);
}

#endif  // MATLAB_MEX_FILE

#include "sg_sfcn_glue.h"   // Code generation glue
