#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_update_scheduled_messages_s_v4

#include "sg_io682_v4.h"

#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

enum ScheduleParamNumbers
{
    PAR_MODULE_ID,
    PAR_MESSAGE_INDEX,
    PAR_SAMPLE_TIME,
    PAR_EN_RATE,
    PAR_NUMBER_OF_ARGS
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

static char msg[256];

#ifndef MATLAB_MEX_FILE
typedef struct sg_IO682_sched_msg_block_T
{
    AR_SCHEDULED_MSG_ENTRY_TYPE *schedEntry;
    SgParam_IntVec *pMessageIndex;
} sg_IO682_sched_msg_block_t;
#endif

static void mdlInitializeSizes(SimStruct *S)
{
    SgMaskInit_SetupSettingsArgs args;
    args.numberOfParams       = PAR_NUMBER_OF_ARGS;
    args.integerWorkVecLength = LENGTH_I_WORK_VEC;
    args.realWorkVecLength    = LENGTH_R_WORK_VEC;
    args.pointerWorkVecLength = LENGTH_P_WORK_VEC;

    if (sgMaskInit_initSizesForRegularBlock(S, &args))
    {
        sprintf(msg,
            "In IO682, Update Scheduled Messages block, ID %d: Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", sgParam_getInt(S, PAR_MODULE_ID), PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }

    sgMaskInit_setNoOutputPorts(S);

    int portWidth = static_cast<int>(mxGetNumberOfElements(ssGetSFcnParam(S, PAR_MESSAGE_INDEX)));

    if (sgParam_getInt(S, PAR_EN_RATE))
    {
        ssSetNumInputPorts(S, 2);

        ssSetInputPortWidth(S, 1, portWidth);
        ssSetInputPortDataType(S, 1, SS_DOUBLE);
        ssSetInputPortDirectFeedThrough(S, 1, 1);
        ssSetInputPortRequiredContiguous(S, 1, 1);
    }
    else
    {
        ssSetNumInputPorts(S, 1);
    }

    ssSetInputPortWidth(S, 0, portWidth);
    ssSetInputPortDataType(S, 0, SS_UINT32);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    double sampleTime = sgParam_getDouble(S, PAR_SAMPLE_TIME);
    sgMaskInit_initSampleTimesForRegularBlock(S, sampleTime);
}

static void sg_ModelLoad(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    

#endif
}

static void sg_ModelStart(SimStruct* S)
{
#ifndef MATLAB_MEX_FILE

    int boardId = sgParam_getInt(S, PAR_MODULE_ID) - 1;
    SgParam_IntVec *pMessageIndex = sgParam_newIntVec(S, PAR_MESSAGE_INDEX);
    int numEntries = pMessageIndex->len;
    AR_SCHEDULED_MSG_ENTRY_TYPE *schedEntry = new AR_SCHEDULED_MSG_ENTRY_TYPE[numEntries];
    sg_mod_info *mod_info = nullptr;
    sg_block_info *block_info = nullptr;
    sg_IO682_sched_msg_block_t *pIO682_schedMsgBlock;

    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, boardId+1);
    if (mod_info == nullptr)
    {
        sprintf(msg, "IO682 scheduled messages: Module not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO682_SCHED_MSG, (uintptr_t)S);
    if (block_info == nullptr)
    {
        sprintf(msg, "IO682 scheduled messages: Block not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }

    for (int i = 0; i < numEntries; ++i)
    {
        int messageIndex = pMessageIndex->val[i] - 1;
        int status = arx30_read_scheduled_msg_block(boardId, messageIndex, 1, &schedEntry[i]);
        if (status != ARS_NORMAL)
        {
            ssSetErrorStatus(S, "Could not read all scheduled messages.");
            return;
        }
        // The API function does not save the board field and the messageIndex always starts at
        // zero. So we have to fix this.
        schedEntry[i].board = boardId;
        schedEntry[i].messageIndex = messageIndex;
    }

    //Setup block registry
    pIO682_schedMsgBlock = (sg_IO682_sched_msg_block_t*)calloc(1, sizeof(sg_IO682_sched_msg_block_t));
    
    pIO682_schedMsgBlock->schedEntry = schedEntry;
    pIO682_schedMsgBlock->pMessageIndex = pMessageIndex;
    
    block_info->custom_data = pIO682_schedMsgBlock;
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    uint32_t *newMessageRaw = (uint32_t *)ssGetInputPortSignal(S, 0);

    sg_mod_info *mod_info = nullptr;
    sg_block_info *block_info = nullptr;
    sg_IO682_sched_msg_block_t *pIO682_schedMsgBlock;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, sgParam_getInt(S, PAR_MODULE_ID));
    if (mod_info == nullptr)
    {
        sprintf(msg, "IO682 scheduled messages: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO682_SCHED_MSG, (uintptr_t)S);
    if (block_info == nullptr)
    {
        sprintf(msg, "IO682 scheduled messages: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    pIO682_schedMsgBlock = (sg_IO682_sched_msg_block_t*)block_info->custom_data;
    AR_SCHEDULED_MSG_ENTRY_TYPE *currentEntries = pIO682_schedMsgBlock->schedEntry;
    SgParam_IntVec *pMessageIndex = pIO682_schedMsgBlock->pMessageIndex;

    for (int i = 0; i < pMessageIndex->len; ++i)
    {
        uint32_t newMessage = newMessageRaw[i];
        int newRate = 0;

        if (sgParam_getInt(S, PAR_EN_RATE))
        {
            double *newRateRaw = (double *)ssGetInputPortSignal(S, 1);
            newRate = (int)newRateRaw[i];
        }
        else
        {
            newRate = currentEntries[i].rate;
        }

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
    sg_mod_info *mod_info = nullptr;
    sg_block_info *block_info = nullptr;
    sg_IO682_sched_msg_block_t *pIO682_schedMsgBlock;

    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, sgParam_getInt(S, PAR_MODULE_ID));
    if (mod_info == nullptr)
    {
        sprintf(msg, "IO682 scheduled messages: Failed to retrieve module from registry in ModelStop\n");
        SG_PRINTF(WARNING, "%s", msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO682_SCHED_MSG, (uintptr_t)S);
    if (block_info == nullptr)
    {
        sprintf(msg, "IO682 scheduled messages: Failed to retrieve block from registry in ModelStop\n");
        SG_PRINTF(WARNING, "%s", msg);
        return;
    }
    else
    {
        pIO682_schedMsgBlock = (sg_IO682_sched_msg_block_t*)block_info->custom_data;
        AR_SCHEDULED_MSG_ENTRY_TYPE *schedEntry = pIO682_schedMsgBlock->schedEntry;
        delete[] schedEntry;
        SgParam_IntVec *pMessageIndex = pIO682_schedMsgBlock->pMessageIndex;
        sgParam_deleteIntVec(pMessageIndex);
        free(pIO682_schedMsgBlock);
        sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO682_SCHED_MSG, (uintptr_t)S);
    }

#endif
}


#include "sg_sfcn_glue.h"   // Code generation glue
