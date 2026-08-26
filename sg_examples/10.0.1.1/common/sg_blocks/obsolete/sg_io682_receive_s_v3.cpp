#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_receive_s_v3

#include "sg_io682_v3.h"

#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "../arinc429/lib/sg_IO682/include/cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

enum ReceiveParamNumbers
{
    PAR_MODULE_ID,
    PAR_CHANNEL,        // Between 1 and 16
    PAR_MIN_MESSAGES,   // <= MAX_MESSAGES
    PAR_MAX_MESSAGES,   // > 0
    PAR_SAMPLE_TIME,
    PAR_NUMBER_OF_ARGS
};

struct ReceiveParams
{
    int moduleId;
    int channel;
    int minMessages;
    int maxMessages;
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
	P_WORK_DATA_BUFFER,
	P_WORK_TIME_BUFFER,
    LENGTH_P_WORK_VEC
};

static int checkRxChannelNumber(const ReceiveParams *params, SgError *err);
static void setErrorStatus(SimStruct *S, SgError *err, int moduleId);
static ReceiveParams *newReceiveParams(SimStruct *S);
static void deleteReceiveParams(ReceiveParams *params);
static void debugPrintParams(const ReceiveParams *params);

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
        static char initErrorMsg[128];
        sprintf(initErrorMsg,
            "In IO682, Receive block, ID %d: Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", sgParam_getInt(S, PAR_MODULE_ID), PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, initErrorMsg);
        return;
    }

    sgMaskInit_setNoInputPorts(S);

    // Word count goes in 0-th element
    sgMaskInit_setOutputPorts(S, 1, maxWords + 1);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    double sampleTime = sgParam_getDouble(S, PAR_SAMPLE_TIME);
    sgMaskInit_initSampleTimesForRegularBlock(S, sampleTime);
}

static void sg_ModelLoad(SimStruct *S)
{
}

static void sg_ModelStart(SimStruct* S)
{
#ifndef MATLAB_MEX_FILE
    ReceiveParams *params = newReceiveParams(S);
    SgError *error = sgError_new();
	CEI_INT32 *dataBuffer, *timeBuffer;
	int boardId = params->moduleId - 1;
    int channel = params->channel - 1;

    if (sg_isModelInit())
    {
        debugPrintParams(params);
    }

    // arx30init downloads the slave processor at model download time. In addition, all of the per
    // channel initializations are done in arx30init.

    if (checkRxChannelNumber(params, error))
    {
        setErrorStatus(S, error, params->moduleId);
        return;
    }
	
	CEI_INT16 val;
	arx30_get_device_config(boardId,channel,ARU_RX_FIFO_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d FIFO Cnt %d\n",channel+1,val);
	arx30_get_device_config(boardId,channel,ARU_RX_MSG_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d Msg Cnt %d\n",channel+1,val);
	
	dataBuffer = (CEI_INT32*)malloc((params->maxMessages)*sizeof(CEI_INT32));
	timeBuffer = (CEI_INT32*)malloc((params->maxMessages)*sizeof(CEI_INT32));

    ssSetPWorkValue(S, P_WORK_PARAMS, params);
	ssSetPWorkValue(S, P_WORK_DATA_BUFFER, dataBuffer);
	ssSetPWorkValue(S, P_WORK_TIME_BUFFER, timeBuffer);
    sgError_delete(error);
#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    ReceiveParams *params = static_cast<ReceiveParams*>(ssGetPWorkValue(S, P_WORK_PARAMS));
    int boardId = params->moduleId - 1;
    int channel = params->channel - 1;
	CEI_INT32 *pword = (CEI_INT32 *)ssGetPWorkValue(S, P_WORK_DATA_BUFFER);
	CEI_INT32 *ptime = (CEI_INT32 *)ssGetPWorkValue(S, P_WORK_TIME_BUFFER);
	Io682_ArincMsg_t *arincOut = (Io682_ArincMsg_t *)ssGetOutputPortSignal(S, 0);
	real_T *realOut = (real_T *)arincOut;
    CEI_INT32 numNewMessages = 0;

    // Count is output in normal double format in element 0 of the output port. Data are output in
    // elements 1 to maxWords in Io682_ArincMsg_t format.

    // Word and time tag data are buffered in separate IWorks. When the buffer contains at least
    // minWords words, the data and time tags are packaged into Io682_ArincMsg_t structures and put
    // out on the output port.
    int status = arx30_getblock(boardId, // (input)  board to reference (0 to 127)
        channel,                         // (input)  recvr channel to use (0 to 31)
        params->maxMessages,   			 // (input)  number of messages to retrieve
        0,                               // (input)  unused parameter (legacy support)
        &numNewMessages,                 // (output) number of messages retrieved
        pword,                 			 // (output) location to store data
        ptime                  			 // (output) location to store timetags
        );

    if (status == ARS_GOTDATA)	// include ARS_BAD_MESSAGE?
    {
        if (numNewMessages < params->minMessages)
        {
            realOut[0] = 0;
			if (numNewMessages < 0)
			{
				SG_PRINTF(TRACE, "Rx Cnt negative\n");
			}
        }
        else
        {
            realOut[0] = (real_T)numNewMessages;

			for (int i = 0; i < numNewMessages; i++)
			{
				arincOut[i+1].word = pword[i];
				arincOut[i+1].time = ptime[i];
			}
        }
    }
    else
    {
		realOut[0] = 0;
		
		if (status == ARS_BAD_MESSAGE)
		{
			SG_PRINTF(DEBUG,"BAD_MESSAGE: Rx Msg Cnt %d\n",numNewMessages);
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
    ReceiveParams *params = static_cast<ReceiveParams*>(ssGetPWorkValue(S, P_WORK_PARAMS));
	int boardId = params->moduleId - 1;
    int channel = params->channel - 1;
	CEI_INT32 status, msgCount;
	CEI_INT16 val;

	SG_PRINTF(DEBUG,"mdlTerminate\n");
	arx30_get_device_config(boardId,channel,ARU_RX_FIFO_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d FIFO Cnt %d\n",channel+1,val);
	arx30_get_device_config(boardId,channel,ARU_RX_MSG_COUNT,&val);
	SG_PRINTF(DEBUG,"Rx Ch %d Msg Cnt %d\n",channel+1,val);
	arx30_get_rx_channel_status(boardId,channel,&status,&msgCount);
	SG_PRINTF(DEBUG,"Rx Ch %d Status %X\n",channel+1,status);	//msgCount is the same as FIFO cnt
	
    deleteReceiveParams(params);
#endif
}

#ifndef MATLAB_MEX_FILE

static int checkRxChannelNumber(const ReceiveParams *params, SgError *err)
{
    int boardId = params->moduleId - 1;
    int channel = params->channel - 1;

    if ((channel < 0) || (channel >= arx30_num_rchans(boardId)))
    {
        sgError_setMsg(err, "Channel %d is not available on this I/O module", params->channel);
        return -1;
    }
    return 0;
}

static void setErrorStatus(SimStruct *S, SgError *err, int moduleId)
{
    sgError_setPreamble(err, "IO682", "Receive", moduleId);
    ssSetErrorStatus(S, sgError_getMsg(err));
}

static ReceiveParams *newReceiveParams(SimStruct *S)
{
    ReceiveParams *params = new ReceiveParams;

    params->moduleId    = sgParam_getInt(S, PAR_MODULE_ID);
    params->channel     = sgParam_getInt(S, PAR_CHANNEL);
    params->minMessages = sgParam_getInt(S, PAR_MIN_MESSAGES);
    params->maxMessages = sgParam_getInt(S, PAR_MAX_MESSAGES);
    params->sampleTime  = sgParam_getDouble(S, PAR_SAMPLE_TIME);

    return params;
}

static void deleteReceiveParams(ReceiveParams *params)
{
    delete params;
}

static void debugPrintParams(const ReceiveParams *params)
{
    SG_PARAM_PRINT_INT(params, moduleId);
    SG_PARAM_PRINT_INT(params, channel);
    SG_PARAM_PRINT_INT(params, minMessages);
    SG_PARAM_PRINT_INT(params, maxMessages);
    SG_PARAM_PRINT_DOUBLE(params, sampleTime);
}

#endif  // MATLAB_MEX_FILE

#include "sg_sfcn_glue.h"   // Code generation glue
