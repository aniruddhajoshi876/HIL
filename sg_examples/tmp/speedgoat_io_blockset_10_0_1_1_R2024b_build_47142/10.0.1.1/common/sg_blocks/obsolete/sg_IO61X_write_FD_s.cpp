/*
*   File       : sg_IO61X_write_FD_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO613 write module for CAN protocol.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*
*/

#pragma region S-Function Default Defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO61X_write_FD_s

#pragma endregion <-- Default Defines -->

#include "include/IO61X_sfunc_help.h"

#pragma region Define - S-Function Parameters

#define QTY_PARAM 7         // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 1        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]           // Module ID
#define pSAMPLE_TIME ssGetSFcnParam(S, 1)                           // Sample time of the block.
#define CAN_MSG_TYPE (uint8_T)mxGetPr(ssGetSFcnParam(S, 2))[0]      // Message type selection for CAN.
#define ENA_STAT_PT (boolean_T)mxGetPr(ssGetSFcnParam(S, 3))[0]     // Enable status output port.

// Hidden
#define pPROTL ssGetSFcnParam(S, 4)                                 // Protocol string
#define PT_IDX (uint8_T)mxGetPr(ssGetSFcnParam(S, 5))[0]            // Port index.
#define IS_FD_MOD (boolean_T)mxGetPr(ssGetSFcnParam(S, 6))[0]       // Status flag if current module a CAN-FD module (=true) or not (=false)

#pragma endregion <-- Mask Parameters -->

#pragma region Globals - Static Values

static char_T ErrMsg[256];      // String for the error message of the S-Function.

#pragma endregion <-- Static Values -->

#pragma region S-Function - Initialization

/*
*   Set all properties of the S-Function block (parameters, input ports, output ports and so on).
*/
static void mdlInitializeSizes(SimStruct *S)
{
    DTypeId newDataTypeId = 0;

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParams(0, S, QTY_PARAM))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Set input and output ports
    if (1 == CAN_MSG_TYPE)
    {
        // Register and check user defined data type for CAN message
        ssRegisterTypeFromNamedObject(S, "CAN_FD_MESSAGE_BUS", &newDataTypeId);

        if (INVALID_DTYPE_ID == newDataTypeId)
        {
            ssSetErrorStatus(S,"CAN_FD_MESSAGE_BUS object not found\n");
            return;
        }
        CreateSFunctionInputPorts(1, S);
        SetSFunctionInputPortProperties(0, 1, newDataTypeId, 1, 1, 0, S);
		ssSetBusInputAsStruct(S, 0, 1);
    }
    else
    {
        CreateSFunctionInputPorts(5, S);
        SetSFunctionInputPortProperties(0, 1, SS_UINT32, 1, 1, 0, S);   // ID
        SetSFunctionInputPortProperties(1, 1, SS_UINT32, 1, 1, 0, S);   // EFF (Frame format 0 = 11 bit, 1 = 29 bit)
        SetSFunctionInputPortProperties(2, 1, SS_UINT32, 1, 1, 0, S);   // DLC
        SetSFunctionInputPortProperties(3, 1, SS_UINT32, 1, 1, 0, S);   // BRS
        SetSFunctionInputPortProperties(4, 64, SS_UINT8, 1, 1, 0, S);    // Data
    }

    // Set status output port
    if (ENA_STAT_PT)
    {
        CreateSFunctionOutputPorts(1, S);
        SetSFunctionOutputPortProperties(0, 1, SS_UINT32, 0, S);
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
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);     // see SS_OPTION in simstruct.h
}


/*
*   Set the sample times of the S-Function block.

*/
static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(pSAMPLE_TIME)[0] == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(pSAMPLE_TIME)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

#pragma endregion <-- Initialization -->

#pragma region S-Function - mdlStart, mdlOutput, mdlTerminate

static void sg_ModelLoad(SimStruct* S) {  }


/*
*   Check if dirver is initialized, get the corresponding module index in the driver struct.
*/
static void sg_ModelStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    uint32_T modIdx = 0;
    char_T protl[10] = {0};
    void *pBuffer = NULL;

    // Get protocol string
    mxGetString(pPROTL, protl, 7);

    // Check driver initialization
    if (!IO61X_CheckIsDriverInitialized(MOD_ID, protl, ErrMsg))
    {
        CleanupOnError(0, MOD_ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Check and set module index
    if (!IO61X_GetModuleIndex(MOD_ID, protl, &modIdx, ErrMsg))
    {
        CleanupOnError(0, MOD_ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetIWorkValue(S, 0, modIdx);


    if (!IO61X_CreatePort(modIdx, PT_IDX, IS_FD_MOD, 2, 0, ErrMsg))
    {
        CleanupOnError(0, MOD_ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (!IO61X_GetBlockBuffer_spin(modIdx, PT_IDX, 1, 0, &pBuffer, ErrMsg))
    {
        CleanupOnError(0, MOD_ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetPWorkValue(S, 0, pBuffer);


#endif
}

/*
*   Get CAN message as real or RAW message by input port(s), write it into the send queue and send message.
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE

    uint8_T *pHelp;
    uint32_T *pStatusPort;
    uint32_T modIdx = (uint32_T)ssGetIWorkValue(S, 0);
    int32_T statusCode = 0;
    CanFdMessage msg = {0};

    if (!IO61X_CheckIsModuleStatusReady(modIdx, ErrMsg))
    {
        CleanupOnError(0, MOD_ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (1 == CAN_MSG_TYPE)
    {
        statusCode = IO61X_UpdateBuffer(modIdx, PT_IDX, ssGetPWorkValue(S, 0), (void*)ssGetInputPortSignal(S, 0), ErrMsg);
        if (statusCode < 0) {
            CleanupOnError(0, MOD_ID, ErrMsg);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
        IO61X_ReleaseWriteSempahore(modIdx);
    }
    else
    {
        int realDlc;
        msg.ID = *(int32_T*)ssGetInputPortSignal(S, 0);
        msg.Extended = *(uint8_T*)ssGetInputPortSignal(S, 1);
        msg.DLC = *(uint8_T*)ssGetInputPortSignal(S, 2);
        msg.BRS = *(uint8_T*)ssGetInputPortSignal(S, 3);
        msg.ProtocolMode = 1;
        pHelp = (uint8_T*)ssGetInputPortSignal(S, 4);
        realDlc = IO61X_CanFdCheckAndGetBaudrate(modIdx, PT_IDX, msg.DLC, ErrMsg);

        ////g_log.dbg(" realDlc: %i", realDlc);

        if (-1 == realDlc)
        {
            CleanupOnError(0, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        msg.Length = (uint8_T)realDlc;
        memcpy(msg.Data, pHelp, msg.Length);
        statusCode = IO61X_UpdateBuffer(modIdx, PT_IDX, ssGetPWorkValue(S, 0), (void*)&msg, ErrMsg);
        if (statusCode < 0) {
            CleanupOnError(0, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
        IO61X_ReleaseWriteSempahore(modIdx);
    }


    if (ENA_STAT_PT)
    {
        pStatusPort = (uint32_T*)ssGetOutputPortSignal(S, 0);

        pStatusPort[0] = (uint32_T)statusCode;
    }

#endif
}

/*
*   Not used.
*/
static void sg_ModelStop(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    // not used
#endif 
}

#pragma endregion <-- mdlStart, mdlOutput, mdlTerminate -->


/*
*   Prepare code for TLC file and assign S-Function parameters to TLC file.mdlWRT(SimStruct *S)
*/
static void mdlWRT(SimStruct *S)
{
    // not used
}


#include "../common/libsg/sg_sfcn_glue.h"
