/*
*   File       : sg_esd_write_v1_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO691 CAN Write block.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*/

#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO602_IO691_read_s

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

#include <exception>

#define QTY_PARAM 1     // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_IN_PORTS 0  // Quantity of the input ports of the S-Function block.
#define QTY_OUT_PORTS 0 // Quantity of output ports of the S-Function block.
#define QTY_R_WORK 0    // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 0    // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 1    // Quantity of vectors/pointers of the data type VOID of the S-Function.

#define pINIT_VALUES ssGetSFcnParam(S, 0)

#define OUTPORT_CANMSG (void *)ssGetOutputPortSignal(S, 1)
#define OUTPORT_STATUS *(uint8_t *)ssGetOutputPortSignal(S, 0)

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
    const double *pInitVals = mxGetPr(pINIT_VALUES);
    DTypeId newDataTypeId = 0;

#ifdef MATLAB_MEX_FILE
    if (2 != static_cast<uint8_t>(pInitVals[4]))
    {
        if (1 == static_cast<uint8_t>(pInitVals[5]))
        {
            if (1 == static_cast<uint8_t>(pInitVals[6])) // BusOutput
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
        else if (2 == static_cast<uint8_t>(pInitVals[5]))
        {
            ssRegisterTypeFromNamedObject(S, "CAN_FD_MESSAGE_BUS", &newDataTypeId);
            if (INVALID_DTYPE_ID == newDataTypeId)
                return;
        }
        else
            ;
    }
#endif // MATLAB_MEX_FILE

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParames(0, S))
    {
        sprintf(s_ErrorMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, s_ErrorMsg);
        return;
    }

    // Set input and output ports
    if (1 == static_cast<uint8_t>(pInitVals[4])) // CAN-FD / CAN
    {
        CreateSFunctionOutputPorts(2, S);
        SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);
        SetSFunctionOutputPortProperties(1, 1, newDataTypeId, 0, S);
        if (1 == static_cast<uint8_t>(pInitVals[6])) // BusOutput
        {
            ssSetBusOutputAsStruct(S, 1, 1);
                (S, 1, (void *)"CAN_MESSAGE_BUS");
        }
        if (2 == static_cast<uint8_t>(pInitVals[5]))
        {
            ssSetBusOutputAsStruct(S, 1, 1);
        }
    }
    else if (2 == static_cast<uint8_t>(pInitVals[4])) // RAW
    {
        if (1 == static_cast<uint8_t>(pInitVals[5]))
        {
            CreateSFunctionOutputPorts(6, S);
            SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);
            SetSFunctionOutputPortProperties(1, 1, SS_UINT32, 0, S); // ID
            SetSFunctionOutputPortProperties(2, 1, SS_UINT8, 0, S);  // FF (Frame format 0 = 11 bit, 1 = 29 bit)
            SetSFunctionOutputPortProperties(3, 1, SS_UINT8, 0, S);  // Length (0 - 8)
            SetSFunctionOutputPortProperties(4, 1, SS_DOUBLE, 0, S); // Timestamp
            SetSFunctionOutputPortProperties(5, 8, SS_UINT8, 0, S);  // Data
        }
        else if (2 == static_cast<uint8_t>(pInitVals[5]))
        {
            CreateSFunctionOutputPorts(7, S);
            SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);
            SetSFunctionOutputPortProperties(1, 1, SS_UINT32, 0, S); // ID
            SetSFunctionOutputPortProperties(2, 1, SS_UINT8, 0, S);  // FF (Frame format 0 = 11 bit, 1 = 29 bit)
            SetSFunctionOutputPortProperties(3, 1, SS_UINT8, 0, S);  // Length (0 - 64)
            SetSFunctionOutputPortProperties(4, 1, SS_DOUBLE, 0, S); // Timestamp
            SetSFunctionOutputPortProperties(5, 1, SS_UINT8, 0, S);  // BRS
            SetSFunctionOutputPortProperties(6, 64, SS_UINT8, 0, S); // Data
        }
    }
    else if (3 == static_cast<uint8_t>(pInitVals[4])) // RAW + CAN
    {
        if (1 == static_cast<uint8_t>(pInitVals[5]))
        {
            CreateSFunctionOutputPorts(7, S);
            SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);
            SetSFunctionOutputPortProperties(1, 1, newDataTypeId, 0, S);
            if (1 == static_cast<uint8_t>(pInitVals[6])) // BusOutput
            {
                ssSetBusOutputAsStruct(S, 1, 1);
                ssSetBusOutputObjectName(S, 1, (void *)"CAN_MESSAGE_BUS");
            }
            // ssSetBusOutputAsStruct(S, 1, 1);
            SetSFunctionOutputPortProperties(2, 1, SS_UINT32, 0, S); // ID
            SetSFunctionOutputPortProperties(3, 1, SS_UINT8, 0, S);  // FF (Frame format 0 = 11 bit, 1 = 29 bit)
            SetSFunctionOutputPortProperties(4, 1, SS_UINT8, 0, S);  // Length (0 - 8)
            SetSFunctionOutputPortProperties(5, 1, SS_DOUBLE, 0, S); // Timestamp
            SetSFunctionOutputPortProperties(6, 8, SS_UINT8, 0, S);  // Data
        }
        else if (2 == static_cast<uint8_t>(pInitVals[5]))
        {
            CreateSFunctionOutputPorts(8, S);
            SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);
            SetSFunctionOutputPortProperties(1, 1, newDataTypeId, 0, S);
            ssSetBusOutputAsStruct(S, 1, 1);
            SetSFunctionOutputPortProperties(2, 1, SS_UINT32, 0, S); // ID
            SetSFunctionOutputPortProperties(3, 1, SS_UINT8, 0, S);  // FF (Frame format 0 = 11 bit, 1 = 29 bit)
            SetSFunctionOutputPortProperties(4, 1, SS_UINT8, 0, S);  // Length (0 - 64)
            SetSFunctionOutputPortProperties(5, 1, SS_DOUBLE, 0, S); // Timestamp
            SetSFunctionOutputPortProperties(6, 1, SS_UINT8, 0, S);  // BRS
            SetSFunctionOutputPortProperties(7, 64, SS_UINT8, 0, S); // Data
        }
    }

    CreateSFunctionInputPorts(0, S);

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
    const ReadInitValues *pInitValues = reinterpret_cast<const ReadInitValues *>(mxGetPr(pINIT_VALUES));

    try
    {
#ifndef MATLAB_MEX_FILE
        sg::esdSFcn::CheckOrCreateModule(pInitValues->mid);
        sg::esdSFcn::setModuleHasRead(*pInitValues);
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
    const ReadInitValues *pInitValues = reinterpret_cast<const ReadInitValues *>(mxGetPr(pINIT_VALUES));
    try
    {
#ifndef MATLAB_MEX_FILE
        CanFdMessage msg = {0};
        CANMsg *hsmsg = (CANMsg *)ssGetOutputPortSignal(S, 1);
        *(bool *)ssGetOutputPortSignal(S, 0) = sg::esdSFcn::ReadCanMessage(*pInitValues, &msg);

        if (1 == pInitValues->Channel.messageType) // CAN
        {
            if (1 == pInitValues->Channel.canType)
            {
                hsmsg->ID = msg.ID;
                hsmsg->Extended = msg.Extended;
                hsmsg->Length = msg.Length;
                hsmsg->Timestamp = msg.Timestamp;
                memcpy((void *)hsmsg->Data, (const void *)msg.Data, (size_t)msg.Length);
            }
            else if (2 == pInitValues->Channel.canType)
                memcpy((void *)ssGetOutputPortSignal(S, 1), (const void *)&msg, (size_t)((uint8_t)sizeof(CanFdMessage) + (uint8_t)msg.Length) - (uint8_t)64);
            else
                ;
        }
        else if (2 == pInitValues->Channel.messageType) // RAW
        {
            if (1 == pInitValues->Channel.canType)
            {
                *(uint32_t *)ssGetOutputPortSignal(S, 1) = msg.ID;
                *(uint8_t *)ssGetOutputPortSignal(S, 2) = msg.Extended;
                *(uint8_t *)ssGetOutputPortSignal(S, 3) = msg.Length;
                *(double *)ssGetOutputPortSignal(S, 4) = msg.Timestamp;
                memcpy((void *)ssGetOutputPortSignal(S, 5), (const void *)msg.Data, (size_t)msg.Length);
            }
            else if (2 == pInitValues->Channel.canType)
            {
                *(uint32_t *)ssGetOutputPortSignal(S, 1) = msg.ID;
                *(uint8_t *)ssGetOutputPortSignal(S, 2) = msg.Extended;
                *(uint8_t *)ssGetOutputPortSignal(S, 3) = sg::esdSFcn::GetMessageDlcByDataLength(msg.Length);
                *(double *)ssGetOutputPortSignal(S, 4) = msg.Timestamp;
                *(uint8_t *)ssGetOutputPortSignal(S, 5) = msg.BRS;
                memcpy((void *)ssGetOutputPortSignal(S, 6), (const void *)msg.Data, (size_t)msg.Length);
            }
        }
        else if (3 == pInitValues->Channel.messageType) // CAN + RAW
        {
            if (1 == pInitValues->Channel.canType)
            {
                hsmsg->ID = msg.ID;
                hsmsg->Extended = msg.Extended;
                hsmsg->Length = msg.Length;
                hsmsg->Timestamp = msg.Timestamp;
                memcpy((void *)hsmsg->Data, (const void *)msg.Data, (size_t)msg.Length);
                *(uint32_t *)ssGetOutputPortSignal(S, 2) = msg.ID;
                *(uint8_t *)ssGetOutputPortSignal(S, 3) = msg.Extended;
                *(uint8_t *)ssGetOutputPortSignal(S, 4) = msg.Length;
                *(double *)ssGetOutputPortSignal(S, 5) = msg.Timestamp;
                memcpy((void *)ssGetOutputPortSignal(S, 6), (const void *)msg.Data, (size_t)msg.Length);
            }
            else if (2 == pInitValues->Channel.canType)
            {
                *(CanFdMessage *)ssGetOutputPortSignal(S, 1) = msg;
                *(uint32_t *)ssGetOutputPortSignal(S, 2) = msg.ID;
                *(uint8_t *)ssGetOutputPortSignal(S, 3) = msg.Extended;
                *(uint8_t *)ssGetOutputPortSignal(S, 4) = sg::esdSFcn::GetMessageDlcByDataLength(msg.Length);
                *(double *)ssGetOutputPortSignal(S, 5) = msg.Timestamp;
                *(uint8_t *)ssGetOutputPortSignal(S, 6) = msg.BRS;
                memcpy((void *)ssGetOutputPortSignal(S, 7), (const void *)msg.Data, (size_t)msg.Length);
            }
        }
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
#ifndef MATLAB_MEX_FILE

#endif
}

#include "../common/libsg/sg_sfcn_glue.h"
