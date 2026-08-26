/*
*   File       : sg_esd_write_v1_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO691 CAN Write block.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*/

#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO602_IO691_write_s

#include "simstruc.h"

#ifndef MATLAB_MEX_FILE
#include "../common/libsg/sg_common.h"
#else
#include "mex.h"
#endif

#include "../common/libsg/sg_callback.h"
#include "../common/libsg/sg_printf.h"

#include "include/CAN_Message_Definition.h"
#include "include/CANFD_Message_Definition.h"
#include "include/IO602_IO691_SFunctionInterface.h"

using namespace sg::esd;
using namespace sg::esdSFcn;
#include <exception>

#define QTY_PARAM 1     // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_IN_PORTS 0  // Quantity of the input ports of the S-Function block.
#define QTY_OUT_PORTS 0 // Quantity of output ports of the S-Function block.
#define QTY_R_WORK 0    // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 0    // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 1    // Quantity of vectors/pointers of the data type VOID of the S-Function.

#define pINIT_VALUES ssGetSFcnParam(S, 0)

static char_T s_ErrorMsg[256]; // String for the error message of the S-Function.

static int SetAndCheckSFunctionParames(uint8_T isTunable, SimStruct *S);
static void CreateSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S);
static int CheckSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S);
static void SetSFunctionInputPortProperties(int32_T portNumber, uint32_T portWidth, uint32_T dataType, boolean_T isRequiredContiguous, boolean_T isDirectFeedThrough, uint8_T propertySelection, SimStruct *S);
static void CreateSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S);
static int CheckSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S);
static void SetSFunctionOutputPortProperties(int32_T portNumber, int32_T portWidth, uint32_T dataType, uint8_T propertySelection, SimStruct *S);

static void mdlInitializeSizes(SimStruct *S)
{
    const WriteInitValues *pInitVals = reinterpret_cast<const WriteInitValues *>(mxGetPr(pINIT_VALUES));
    const double *pInitValsAsDouble = mxGetPr(pINIT_VALUES);
    uint8_t IsBusInput = static_cast<uint8_t>(pInitValsAsDouble[7]); // BusInput is not a member of sg::esd::ChannelInitValues_T. Therefore, get BusInput by means of this cast

    DTypeId newDataTypeId = 0;

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParames(0, S))
    {
        sprintf(s_ErrorMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, s_ErrorMsg);
        return;
    }

    // Set input and output ports
    if (1 == pInitVals->Channel.messageType) // CAN-FD / CAN
    {
        CreateSFunctionInputPorts(1, S);
#ifdef MATLAB_MEX_FILE

        if (1 == pInitVals->Channel.canType)
        {
            if (1 == IsBusInput)
            {
                ssRegisterTypeFromNamedObject(S, "CAN_MESSAGE_BUS", &newDataTypeId);
            }
            else
            {
                newDataTypeId = ssRegisterDataType(S, "CAN_MESSAGE");
            }

            if (INVALID_DTYPE_ID == newDataTypeId)
                return;
            if (!ssSetDataTypeSize(S, newDataTypeId, sizeof(CANMsg)))
                return;
        }
        else if (2 == pInitVals->Channel.canType)
        {
            ssRegisterTypeFromNamedObject(S, "CAN_FD_MESSAGE_BUS", &newDataTypeId);
            if (INVALID_DTYPE_ID == newDataTypeId)
                return;
            ssSetBusInputAsStruct(S, 0, 1);
        }
        else
            return;

        SetSFunctionInputPortProperties(0, 1, newDataTypeId, 1, 1, 0, S);
        if (1 == IsBusInput)
        {
            ssSetBusInputAsStruct(S, 0, 1);
        }
#endif // MATLAB_MEX_FILE
    }
    else if (2 == pInitVals->Channel.messageType) // RAW
    {
        if (1 == pInitVals->Channel.canType)
        {
            CreateSFunctionInputPorts(4, S);
            SetSFunctionInputPortProperties(0, 1, SS_UINT32, 1, 1, 0, S); // ID
            SetSFunctionInputPortProperties(1, 1, SS_UINT8, 1, 1, 0, S);  // FF (Frame format 0 = 11 bit, 1 = 29 bit)
            SetSFunctionInputPortProperties(2, 1, SS_UINT8, 1, 1, 0, S);  // Length (0 - 8)
            SetSFunctionInputPortProperties(3, 8, SS_UINT8, 1, 1, 0, S);  // Data
        }
        else if (2 == pInitVals->Channel.canType)
        {
            CreateSFunctionInputPorts(5, S);
            SetSFunctionInputPortProperties(0, 1, SS_UINT32, 1, 1, 0, S); // ID
            SetSFunctionInputPortProperties(1, 1, SS_UINT8, 1, 1, 0, S);  // FF (Frame format 0 = 11 bit, 1 = 29 bit)
            SetSFunctionInputPortProperties(2, 1, SS_UINT8, 1, 1, 0, S);  // Length (0 - 64)
            SetSFunctionInputPortProperties(3, 1, SS_UINT8, 1, 1, 0, S);  // BRS
            SetSFunctionInputPortProperties(4, 64, SS_UINT8, 1, 1, 0, S); // Data
        }
    }

    if (1 == pInitVals->enableStatusPort) //  static_cast<uint8_t>(pInitVals[6]))
    {
        CreateSFunctionOutputPorts(1, S);
        SetSFunctionOutputPortProperties(0, 1, SS_INT8, 0, S);
    }
    else
    {
        CreateSFunctionOutputPorts(0, S);
    }

    // Set RWork vector
    ssSetNumRWork(S, QTY_R_WORK);

    // Set IWork vector
    ssSetNumIWork(S, QTY_I_WORK);

    // Set PWork vector
    ssSetNumPWork(S, QTY_P_WORK);

    // Default settings
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    // Specify the sim state compliance to be same as a built-in block
    // UNCOMMENT: ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    // Set options
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE); // see SS_OPTION in simstruct.h
}

static int SetAndCheckSFunctionParames(uint8_T isTunable, SimStruct *S)
{
    int i = 0;

    ssSetNumSFcnParams(S, QTY_PARAM);

    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        return 0;
    }

    for (i = 0; i < QTY_PARAM; i++)
    {
        ssSetSFcnParamTunable(S, i, isTunable);
    }

    return 1;
}

static void CreateSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S)
{
    // Create input ports
    if (0 == quantityOfInputs)
    {
        ssSetNumInputPorts(S, QTY_IN_PORTS);
    }
    else
    {
        ssSetNumInputPorts(S, quantityOfInputs);
    }
}

static int CheckSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S)
{
    if (0 == quantityOfInputs)
    {
        if (QTY_IN_PORTS != ssGetNumInputPorts(S))
        {
            return 0;
        }
    }
    else
    {
        if (quantityOfInputs != ssGetNumInputPorts(S))
        {
            return 0;
        }
    }

    return 1;
}

static void SetSFunctionInputPortProperties(int32_T portNumber, uint32_T portWidth, uint32_T dataType, boolean_T isRequiredContiguous,
                                            boolean_T isDirectFeedThrough, uint8_T propertySelection, SimStruct *S)
{
    if (1 == propertySelection)
    {
        ssSetInputPortWidth(S, portNumber, portWidth);
    }
    else if (2 == propertySelection)
    {
        ssSetInputPortDataType(S, portNumber, dataType);
    }
    else if (3 == propertySelection)
    {
        ssSetInputPortRequiredContiguous(S, portNumber, isRequiredContiguous);
    }
    else if (4 == propertySelection)
    {
        ssSetInputPortDirectFeedThrough(S, portNumber, isDirectFeedThrough);
    }
    else
    {
        ssSetInputPortWidth(S, portNumber, portWidth);
        ssSetInputPortDataType(S, portNumber, dataType);
        ssSetInputPortRequiredContiguous(S, portNumber, isRequiredContiguous);
        ssSetInputPortDirectFeedThrough(S, portNumber, isDirectFeedThrough);
    }
}

static void CreateSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S)
{
    // Create input ports
    if (0 == quantityOfOutputs)
    {
        ssSetNumOutputPorts(S, QTY_OUT_PORTS);
    }
    else
    {
        ssSetNumOutputPorts(S, quantityOfOutputs);
    }
}

static int CheckSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S)
{
    if (0 == quantityOfOutputs)
    {
        if (QTY_OUT_PORTS != ssGetNumOutputPorts(S))
        {
            return 0;
        }
    }
    else
    {
        if (quantityOfOutputs != ssGetNumOutputPorts(S))
        {
            return 0;
        }
    }

    return 1;
}

static void SetSFunctionOutputPortProperties(int32_T portNumber, int32_T portWidth, uint32_T dataType, uint8_T propertySelection, SimStruct *S)
{
    if (1 == propertySelection)
    {
        ssSetOutputPortWidth(S, portNumber, portWidth);
    }
    else if (2 == propertySelection)
    {
        ssSetOutputPortDataType(S, portNumber, dataType);
    }
    else
    {
        ssSetOutputPortWidth(S, portNumber, portWidth);
        ssSetOutputPortDataType(S, portNumber, dataType);
    }
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    const double *pInitVals = mxGetPr(pINIT_VALUES);

    if (pInitVals[2] == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, pInitVals[2]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

static void sg_ModelLoad(SimStruct *S) {}

static void sg_ModelStart(SimStruct *S)
{
    const WriteInitValues *pInitValues = reinterpret_cast<const WriteInitValues *>(mxGetPr(pINIT_VALUES));

    try
    {
#ifndef MATLAB_MEX_FILE
        // note if we wanted to reuse this buffer in the next run, we would need e.g. S-id to identify SFunction instance;
        // instead, we let Setup block clean this up in the end.
        sg::esdSFcn::CheckOrCreateModule(pInitValues->mid);
        void *p = sg::esdSFcn::GetBlockBufferEx(*pInitValues);
        ssSetPWorkValue(S, 0, p);
#endif
    }
    catch (const std::exception &e)
    {
        strncpy(s_ErrorMsg, e.what(), sizeof(s_ErrorMsg));
        ssSetErrorStatus(S, s_ErrorMsg);
        return;
    }
}

static void sg_ModelStep(SimStruct *S)
{
    const WriteInitValues *pInitValues = reinterpret_cast<const WriteInitValues *>(mxGetPr(pINIT_VALUES));

    try
    {
#ifndef MATLAB_MEX_FILE
        //		SG_PRINTF(DEBUG, "\nDbg - mdlOutputs of Write s-function!\n");

        int8_t state = 0;
        CanFdMessage msg = {0};
        const CANMsg *hsmsg = reinterpret_cast<const CANMsg *>(ssGetInputPortSignal(S, 0));

        int32_t msgType = (int32_t)pInitValues->Channel.messageType;
        int32_t canType = (int32_t)pInitValues->Channel.canType;

        if (1 == msgType)
        {
            if (1 == canType)
            {
                msg.ID = hsmsg->ID;
                msg.ProtocolMode = 0;
                msg.Extended = hsmsg->Extended;
                msg.Length = hsmsg->Length;
                msg.DLC = msg.Length;
                memcpy((void *)msg.Data, (const void *)hsmsg->Data, (size_t)msg.Length);
            }
            else if (2 == canType)
            {
                msg = *(const CanFdMessage *)ssGetInputPortSignal(S, 0);
                msg.ProtocolMode = 1;
            }
        }
        else if (2 == msgType) // RAW
        {
            if (1 == canType)
            {
                msg.ID = *(uint32_t *)ssGetInputPortSignal(S, 0);
                msg.ProtocolMode = 0;
                msg.Extended = *(uint8_t *)ssGetInputPortSignal(S, 1);
                msg.Length = *(uint8_t *)ssGetInputPortSignal(S, 2);
                msg.DLC = msg.Length;
                memcpy((void *)msg.Data, (void *)ssGetInputPortSignal(S, 3), (size_t)msg.Length);
            }
            else if (2 == canType)
            {
                msg.ID = *(uint32_t *)ssGetInputPortSignal(S, 0);
                msg.ProtocolMode = 1;
                msg.Extended = *(uint8_t *)ssGetInputPortSignal(S, 1);
                msg.DLC = *(uint8_t *)ssGetInputPortSignal(S, 2);
                msg.Length = sg::esdSFcn::GetMessageDataLengthByDlc(msg.DLC);
                msg.BRS = *(uint8_t *)ssGetInputPortSignal(S, 3);
                memcpy((void *)msg.Data, (void *)ssGetInputPortSignal(S, 4), (size_t)msg.Length);
            }
        }

        state = sg::esdSFcn::AddMessageToBuffer(*pInitValues, &msg, ssGetPWorkValue(S, 0));

        if (1 == (int32_t)pInitValues->enableStatusPort)
        {
            *(int8_t *)ssGetOutputPortSignal(S, 0) = state;
        }

        // release the sender semaphore - this triggers the sender thread if it waits on new messages

#endif
    }
    catch (const std::exception &e)
    {
        strncpy(s_ErrorMsg, e.what(), sizeof(s_ErrorMsg));
        ssSetErrorStatus(S, s_ErrorMsg);
        return;
    }
}

static void sg_ModelStop(SimStruct *S)
{
}

#include "../common/libsg/sg_sfcn_glue.h"
