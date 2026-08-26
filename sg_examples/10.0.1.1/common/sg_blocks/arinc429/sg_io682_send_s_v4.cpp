#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io682_send_s_v4

#include "sg_io682_v4.h"
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "cdev_api.h"
#endif

#include "sg_callback.h"
#include "sg_mask_init.h"

enum SendParamNumbers
{
    PAR_MODULE_ID,
    PAR_CHANNEL,        // Between 1 and 16
    PAR_SAMPLE_TIME,
    PAR_TX_CTRL,
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
            "In IO682, Send block, ID %d: Wrong number of input arguments passed.\n"
            "%d arguments are expected.\n", sgParam_getInt(S, PAR_MODULE_ID), PAR_NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }

    sgMaskInit_setNoOutputPorts(S);

    if(sgParam_getInt(S, PAR_TX_CTRL) == 1)
    {
        ssSetNumInputPorts(S, 2);
        ssSetInputPortWidth(S, 1, DYNAMICALLY_SIZED);
        ssSetInputPortDataType(S, 1, SS_UINT32);
        ssSetInputPortDirectFeedThrough(S, 1, 1);
        ssSetInputPortRequiredContiguous(S, 1, 1);
    }
    else
    {
        ssSetNumInputPorts(S, 1);
    }
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDataType(S, 0, SS_UINT32);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);
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
#ifndef MATLAB_MEX_FILE
    

#endif
}

static void sg_ModelStart(SimStruct* S)
{
#ifndef MATLAB_MEX_FILE
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    uint32_t *txCtrlOld;

    // Check if module is already registered
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, sgParam_getInt(S, PAR_MODULE_ID));
    if (mod_info == NULL)
    {
        ssSetErrorStatus(S, "IO682 Send: Module not registered\n");
        return;
    }

    block_info = sg_block_register_with_uid(mod_info, SG_BLOCK_TYPE_IO682_SEND, (uintptr_t)S);
    
    if (block_info == NULL)
    {
        ssSetErrorStatus(S, "IO682 Send: Block not registered\n");
        return;
    }

    //input port size check
    if(sgParam_getInt(S, PAR_TX_CTRL) == 1)
    {
        if (ssGetInputPortWidth(S, 0) != ssGetInputPortWidth(S, 1))
        {
            ssSetErrorStatus(S, "Tx Control input size does not match Msg input size\n");
            return;
        }
    }

    txCtrlOld = (uint32_t*)malloc(ssGetInputPortWidth(S, 0) * sizeof(uint32_t));    //Get size of Msg input as txCtrlOld is used even if txCtrl is not enabled
    //Init to 1
    for (int i = 0; i < ssGetInputPortWidth(S, 0); i++)
    {
        txCtrlOld[i] = 1;
    }
    block_info->custom_data = txCtrlOld;

    
    // arx30init downloads the slave processor at model download time. In addition, all of the per
    // channel initializations are done in arx30init.

    int boardId = sgParam_getInt(S, PAR_MODULE_ID) - 1;
    int channel = sgParam_getInt(S, PAR_CHANNEL) - 1;

    if ((channel < 0) || (channel >= arx30_num_xchans(boardId)))
    {
        sprintf(msg, "Channel %d is not available on this I/O module", channel+1);
        ssSetErrorStatus(S, msg);
        return;
    }

#endif
}

static void sg_ModelStep(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    int numMessages = ssGetInputPortWidth(S, 0);
    uint32_t *data = (uint32_t *)ssGetInputPortSignal(S, 0);
    uint32_t *txCtrl, *txCtrlOld;
    short result;
    short boardId = sgParam_getInt(S, PAR_MODULE_ID) - 1;
    short channel = sgParam_getInt(S, PAR_CHANNEL) - 1;
    sg_mod_info *mod_info;
    sg_block_info *block_info;

    // Check if module is already registered
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, sgParam_getInt(S, PAR_MODULE_ID));
    if (mod_info == NULL)
    {
        ssSetErrorStatus(S, "IO682 Send: Module not registered\n");
        return;
    }

    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO682_SEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        ssSetErrorStatus(S, "IO682 Send: Failed to retrieve block from registry in ModelStep\n");
        return;
    }

    txCtrlOld = (uint32_t *)block_info->custom_data;

    if(sgParam_getInt(S, PAR_TX_CTRL) == 1)
    {
        txCtrl = (uint32_t *)ssGetInputPortSignal(S, 1);
    }
    else
    {
        txCtrl = txCtrlOld; //Always send all messages
    }
    
    for (int i = 0; i < numMessages; i++)
    {
        if (txCtrl[i] != 0)
        {
            if (txCtrlOld[i] >= txCtrl[i])  //Use >= in case of change during runtime to a lower value
            {
                result = arx30_putword(boardId, channel, data[i]);  //check putblock, faster?
                //SG_PRINTF(INFO, "Data[%d]: 0x%X\n", i, data[i]);

                if (result != ARS_NORMAL)
                {
                    sprintf(msg, "Transmit error %d on board %d chan %d: %s\n", result, boardId,
                        channel, arx30_get_error(result));
                    ssSetErrorStatus(S, msg);
                    return;
                }

                txCtrlOld[i] = 1;   //reset when msg is transmitted
            }
            else
            {
                ++txCtrlOld[i];
            }
        }
    }
#endif
}

static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    sg_mod_info *mod_info;
    sg_block_info *block_info;
    uint32_t *txCtrlOld;

    // Check if module is already registered
    mod_info = sg_module_get_single(SG_MODULE_TYPE_IO682, sgParam_getInt(S, PAR_MODULE_ID));
    if (mod_info == NULL)
    {
        SG_PRINTF(WARNING, "IO682 Send: Module not registered\n");
        return;
    }

    block_info = sg_block_get_by_uid(mod_info, SG_BLOCK_TYPE_IO682_SEND, (uintptr_t)S);
    if (block_info == NULL)
    {
        SG_PRINTF(WARNING, "IO682 Send: Failed to retrieve block from registry in ModelStop\n");
        return;
    }
    else
    {
        txCtrlOld = (uint32_t *)block_info->custom_data;
        free(txCtrlOld);
        sg_block_unregister(mod_info, SG_BLOCK_TYPE_IO682_SEND, (uintptr_t)S);
    }
#endif
}


#include "sg_sfcn_glue.h"   // Code generation glue
