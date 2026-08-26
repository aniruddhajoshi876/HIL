#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_receive_s_v4

#include "sg_io682_v4.h"

#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

enum ReceiveParamNumbers
{
    PAR_MODULE_ID,
    PAR_CHANNEL,        // Between 1 and 16
    PAR_MAX_MESSAGES,   // > 0
    PAR_SAMPLE_TIME,
    PAR_EN_TIME_TAGS,
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
typedef struct sg_IO682_receive_block_T
{
    CEI_INT32 *dataBuffer;
    CEI_INT32 *timeBuffer;
} sg_IO682_receive_block_t;
#endif

static void mdlInitializeSizes(SimStruct *S)
{
    int maxWords = sgParam_getInt(S, PAR_MAX_MESSAGES);

    if (maxWords < 1)
    {
        ssSetErrorStatus(S, "Receive block max words < 1");
        return;
    }

    SgMaskInit_SetupSettingsArgs args;
    args.numberOfParams       = PAR_NUMBER_OF_ARGS;
    args.integerWorkVecLength = LENGTH_I_WORK_VEC;
    args.realWorkVecLength    = LENGTH_R_WORK_VEC;
    args.pointerWorkVecLength = LENGTH_P_WORK_VEC;

    if (sgMaskInit_initSizesForRegularBlock(S, &args))
    {
        sprintf(msg,
            "In IO682, Receive block, ID %d: Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", sgParam_getInt(S, PAR_MODULE_ID), PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }

    sgMaskInit_setNoInputPorts(S);

    if (sgParam_getInt(S, PAR_EN_TIME_TAGS))
    {
        //TimeTags
        ssSetNumOutputPorts(S, 3);
        ssSetOutputPortWidth(S, 2, maxWords);
        ssSetOutputPortDataType(S, 2, SS_UINT32);
    }
    else
    {
        ssSetNumOutputPorts(S, 2);
    }
    //Cnt
    ssSetOutputPortWidth(S, 0, 1);
    ssSetOutputPortDataType(S, 0, SS_UINT32);
    //Data
    ssSetOutputPortWidth(S, 1, maxWords);
    ssSetOutputPortDataType(S, 1, SS_UINT32);
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
	CEI_INT32 *dataBuffer, *timeBuffer;
	int boardId = sgParam_getInt(S, PAR_MODULE_ID) - 1;
    int channel = sgParam_getInt(S, PAR_CHANNEL) - 1;
    int maxMessages = sgParam_getInt(S, PAR_MAX_MESSAGES);
    sg_mod_info *mod_info = nullptr;
    sg_block_info *block_info = nullptr;
    sg_IO682_receive_block_t *pIO682_receive;

    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, boardId+1);
    if (mod_info == nullptr)
    {
        sprintf(msg, "IO682 receive: Module not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO682_RECEIVE, (uintptr_t)S);
    if (block_info == nullptr)
    {
        sprintf(msg, "IO682 receive: Block not registered\n");
        ssSetErrorStatus(S, msg);
        return;
    }

    // arx30init downloads the slave processor at model download time. In addition, all of the per
    // channel initializations are done in arx30init.

    if ((channel < 0) || (channel >= arx30_num_rchans(boardId)))
    {
        sprintf(msg, "Channel %d is not available on this I/O module", sgParam_getInt(S, PAR_CHANNEL));
        ssSetErrorStatus(S, msg);
        return;
    }
	
	CEI_INT16 val;
	arx30_get_device_config(boardId,channel,ARU_RX_FIFO_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d FIFO Cnt %d\n",channel+1,val);
	arx30_get_device_config(boardId,channel,ARU_RX_MSG_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d Msg Cnt %d\n",channel+1,val);
	
	dataBuffer = (CEI_INT32*)malloc((maxMessages)*sizeof(CEI_INT32));
	timeBuffer = (CEI_INT32*)malloc((maxMessages)*sizeof(CEI_INT32));

    //Setup block registry
    pIO682_receive = (sg_IO682_receive_block_t*)calloc(1, sizeof(sg_IO682_receive_block_t));
    
    pIO682_receive->dataBuffer = dataBuffer;
    pIO682_receive->timeBuffer = timeBuffer;
    
    block_info->custom_data = pIO682_receive;
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    int boardId = sgParam_getInt(S, PAR_MODULE_ID) - 1;
    int channel = sgParam_getInt(S, PAR_CHANNEL) - 1;
    CEI_INT32 numNewMessages = 0;
    int maxMessages = sgParam_getInt(S, PAR_MAX_MESSAGES);
    uint32_t *cnt = (uint32_t*)ssGetOutputPortSignal(S, 0);
    uint32_t *data = (uint32_t*)ssGetOutputPortSignal(S, 1);
    uint32_t *time;
    if (sgParam_getInt(S, PAR_EN_TIME_TAGS))
    {
        time = (uint32_t*)ssGetOutputPortSignal(S, 2);
    }

    sg_mod_info *mod_info = nullptr;
    sg_block_info *block_info = nullptr;
    sg_IO682_receive_block_t *pIO682_receive;
    
    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, sgParam_getInt(S, PAR_MODULE_ID));
    if (mod_info == nullptr)
    {
        sprintf(msg, "IO682 receive: Failed to retrieve module from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO682_RECEIVE, (uintptr_t)S);
    if (block_info == nullptr)
    {
        sprintf(msg, "IO682 receive: Failed to retrieve block from registry in ModelStep\n");
        ssSetErrorStatus(S, msg);
        return;
    }
    
    pIO682_receive = (sg_IO682_receive_block_t*)block_info->custom_data;
    CEI_INT32 *pword = pIO682_receive->dataBuffer;
    CEI_INT32 *ptime = pIO682_receive->timeBuffer;

    int status = arx30_getblock(boardId, // (input)  board to reference (0 to 127)
        channel,                         // (input)  recvr channel to use (0 to 31)
        maxMessages,   			         // (input)  number of messages to retrieve
        0,                               // (input)  unused parameter (legacy support)
        &numNewMessages,                 // (output) number of messages retrieved
        pword,                 			 // (output) location to store data
        ptime                  			 // (output) location to store timetags
        );

    if (status == ARS_GOTDATA)	// include ARS_BAD_MESSAGE?
    {

        cnt[0] = numNewMessages;

        for (int i = 0; i < numNewMessages; i++)
        {
            data[i] = pword[i];
            if (sgParam_getInt(S, PAR_EN_TIME_TAGS))
            {
                time[i] = ptime[i];
            }
        }
    }
    else
    {
		cnt[0] = 0;
		
		if (status == ARS_BAD_MESSAGE)
		{
			SG_PRINTF(WARNING,"BAD_MESSAGE: Rx Msg Cnt %d\n",numNewMessages);
		}
		else
		{
			SG_PRINTF(TRACE,"Rx status %d\n",status);
		}
    }
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
	int boardId = sgParam_getInt(S, PAR_MODULE_ID) - 1;
    int channel = sgParam_getInt(S, PAR_CHANNEL) - 1;
	CEI_INT32 status, msgCount;
	CEI_INT16 val;

    sg_mod_info *mod_info = nullptr;
    sg_block_info *block_info = nullptr;
    sg_IO682_receive_block_t *pIO682_receive;

    //Retrieve data from module registry
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, sgParam_getInt(S, PAR_MODULE_ID));
    if (mod_info == nullptr)
    {
        sprintf(msg, "IO682 receive: Failed to retrieve module from registry in ModelStop\n");
        SG_PRINTF(WARNING, "%s", msg);
        return;
    }
    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO682_RECEIVE, (uintptr_t)S);
    if (block_info == nullptr)
    {
        sprintf(msg, "IO682 receive: Failed to retrieve block from registry in ModelStop\n");
        SG_PRINTF(WARNING, "%s", msg);
        return;
    }
    else
    {
        pIO682_receive = (sg_IO682_receive_block_t*)block_info->custom_data;
        free(pIO682_receive->dataBuffer);
        free(pIO682_receive->timeBuffer);
        free(pIO682_receive);
        sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO682_RECEIVE, (uintptr_t)S);
    }

	SG_PRINTF(DEBUG,"mdlTerminate\n");
	arx30_get_device_config(boardId,channel,ARU_RX_FIFO_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d FIFO Cnt %d\n",channel+1,val);
	arx30_get_device_config(boardId,channel,ARU_RX_MSG_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d Msg Cnt %d\n",channel+1,val);
	arx30_get_rx_channel_status(boardId,channel,&status,&msgCount);
	SG_PRINTF(DEBUG,"Rx Ch %d Status %X\n",channel+1,status);	//msgCount is the same as FIFO cnt
	
#endif
}


#include "sg_sfcn_glue.h"   // Code generation glue
