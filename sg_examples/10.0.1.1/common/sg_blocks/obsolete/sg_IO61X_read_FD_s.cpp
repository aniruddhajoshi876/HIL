/*
*   File       : sg_IO61X_read_FD_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO613 read module for CAN protocol.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*
*/

#pragma region S-Function Default Defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO61X_read_FD_s

#pragma endregion <-- Default Defines -->

#include "include/IO61X_sfunc_help.h"

#pragma region Define - S-Function Parameters

#define QTY_PARAM 6         // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_IN_PORTS 0      // Quantity of the input ports of the S-Function block.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 0        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]           // Module ID
#define pSAMPLE_TIME ssGetSFcnParam(S, 1)                           // Sample time of the block.
#define CAN_MSG_TYPE (uint8_T)mxGetPr(ssGetSFcnParam(S, 2))[0]      // Message type selection for CAN.

// Hidden
#define pPROTL ssGetSFcnParam(S, 3)                                 // Protocol string
#define PT_IDX (uint8_T)mxGetPr(ssGetSFcnParam(S, 4))[0]            // Port number selection for CAN and CAN-FD.
#define IS_FD_MOD (boolean_T)mxGetPr(ssGetSFcnParam(S, 5))[0]       // Status flag if current module a CAN-FD module (=true) or not (=false)

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

    if ((1 == CAN_MSG_TYPE) || (3 == CAN_MSG_TYPE))
    {
        // Register and check user defined data type for CAN message
        ssRegisterTypeFromNamedObject(S, "CAN_FD_MESSAGE_BUS", &newDataTypeId);

        if (INVALID_DTYPE_ID == newDataTypeId)
        {
            ssSetErrorStatus(S,"CAN_FD_MESSAGE_BUS object not found\n");
            return;
        }
    }
    
    // Set input and output ports
    CreateSFunctionInputPorts(QTY_IN_PORTS, S);

    if (1 == CAN_MSG_TYPE)
    {
        CreateSFunctionOutputPorts(2, S);
        SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);
        SetSFunctionOutputPortProperties(1, 1, newDataTypeId, 0, S);
		ssSetBusOutputAsStruct(S, 1, 1);
		ssSetBusOutputObjectName(S, 1, (void *)"CAN_FD_MESSAGE_BUS");
    }
    else if (2 == CAN_MSG_TYPE)
    {
        CreateSFunctionOutputPorts(7, S);
        SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);   // Data present
        SetSFunctionOutputPortProperties(1, 1, SS_UINT32, 0, S);    // ID
        SetSFunctionOutputPortProperties(2, 1, SS_UINT32, 0, S);    // FF (Frame format, 0 = 11 bit, 1 = 29 bit)
        SetSFunctionOutputPortProperties(3, 1, SS_UINT32, 0, S);    // DLC
        SetSFunctionOutputPortProperties(4, 1, SS_UINT32, 0, S);    // BRS
        SetSFunctionOutputPortProperties(5, 1, SS_DOUBLE, 0, S);    // Timestamp
        SetSFunctionOutputPortProperties(6, 64, SS_UINT8, 0, S);     // Data
    }
    else
    {
        CreateSFunctionOutputPorts(8, S);
        SetSFunctionOutputPortProperties(0, 1, SS_BOOLEAN, 0, S);   // Data present
        SetSFunctionOutputPortProperties(1, 1, newDataTypeId, 0, S);  // CAN message
		ssSetBusOutputAsStruct(S, 1, 1);
		ssSetBusOutputObjectName(S, 1, (void *)"CAN_FD_MESSAGE_BUS");
        SetSFunctionOutputPortProperties(2, 1, SS_UINT32, 0, S);    // ID
        SetSFunctionOutputPortProperties(3, 1, SS_UINT32, 0, S);    // FF (Frame format, 0 = 11 bit, 1 = 29 bit)
        SetSFunctionOutputPortProperties(4, 1, SS_UINT32, 0, S);    // DLC
        SetSFunctionOutputPortProperties(5, 1, SS_UINT32, 0, S);    // BRS
        SetSFunctionOutputPortProperties(6, 1, SS_DOUBLE, 0, S);    // Timestamp
        SetSFunctionOutputPortProperties(7, 64, SS_UINT8, 0, S);     // Data
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
*   Check driver initialization and get corresponding module index in the driver structure.
*/
static void sg_ModelStart(SimStruct *S)
{
    #ifndef MATLAB_MEX_FILE

    uint32_T modIdx = 0;
    char_T protl[10] = {0};

    // Get protocol string
    mxGetString(pPROTL, protl, 7);

    // Check driver initialization
    if (!IO61X_CheckIsDriverInitialized(MOD_ID, protl, ErrMsg))
    {
        printf("\n");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Check and set module index
    if (!IO61X_GetModuleIndex(MOD_ID, protl, &modIdx, ErrMsg))
    {
        printf("\n");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    ssSetIWorkValue(S, 0, modIdx);

    #endif
}

/*
*   Readout message from receive queue and forward the data as CAN or RAW message to the output port(s).
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    #ifndef MATLAB_MEX_FILE

    uint32_T modIdx = (uint32_T)ssGetIWorkValue(S, 0);
    uint32_T statusCode = 0;

    if (!IO61X_CheckIsModuleStatusReady(modIdx, ErrMsg))
    {
        CleanupOnError(0, MOD_ID, ErrMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (1 == CAN_MSG_TYPE)
    {
        *((boolean_T*)ssGetOutputPortSignal(S, 0)) = IO61X_ReceiveCanFdMessage(modIdx, PT_IDX, (void*)ssGetOutputPortSignal(S, 1));
    }
    else if (2 == CAN_MSG_TYPE)
    {
        *(boolean_T*)ssGetOutputPortSignal(S, 0) = IO61X_ReceiveCanFdMessageRaw(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, 1)
                                                                                , (uint32_t*)ssGetOutputPortSignal(S, 2)
                                                                                , (uint32_t*)ssGetOutputPortSignal(S, 3)
                                                                                ,(uint32_t*)ssGetOutputPortSignal(S, 4)
                                                                                , (double*)ssGetOutputPortSignal(S, 5)
                                                                                , (void*)ssGetOutputPortSignal(S, 6));
    }
    else
    {
        *(boolean_T*)ssGetOutputPortSignal(S, 0) = IO61X_ReceiveCanFdAndCanFdRawMessage(modIdx, PT_IDX, (void*)ssGetOutputPortSignal(S, 1)
                                                                                        , (uint32_t*)ssGetOutputPortSignal(S, 2)
                                                                                        , (uint32_t*)ssGetOutputPortSignal(S, 3)
                                                                                        , (uint32_t*)ssGetOutputPortSignal(S, 4)
                                                                                        , (uint32_t*)ssGetOutputPortSignal(S, 5)
                                                                                        , (double*)ssGetOutputPortSignal(S, 6)
                                                                                        , (void*)ssGetOutputPortSignal(S, 7));
    }

    #endif
}

/*
*   Not used.
*/
static void sg_ModelStop(SimStruct *S)
{
    #ifndef MATLAB_MEX_FILE
    #endif 
}

#pragma endregion <-- mdlStart, mdlOutput, mdlTerminate -->


/*
*   Prepare code for TLC file and assign S-Function parameters to TLC file.mdlWRT(SimStruct *S)
*/
static void mdlWRT(SimStruct *S)
{
}


#include "../common/libsg/sg_sfcn_glue.h"
