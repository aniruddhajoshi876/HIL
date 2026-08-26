/*
*   File       : sg_IO61X_write_LIN_s.cpp
*   Description: (obsolete) This file includes all functions of the Simulik S-Function for the IO611 write module for LIN protocol.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$

*/

#pragma region S-Function Default Defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO61X_write_LIN_s

#pragma endregion <-- Default Defines -->

#include "./include/IO61X_sfunc_help.h"
#include "./include/LIN_Message_Definition.h"

#pragma region Define - S-Function Parameters

#define QTY_PARAM 7         // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // v
#define QTY_P_WORK 0        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

// Setup
#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]       // Module ID
#define pSAMPLE_TIME ssGetSFcnParam(S, 1)       // Sample time of the block.

// LIN
#define LIN_MSG_TYPE (uint8_T)mxGetPr(ssGetSFcnParam(S, 2))[0]      // LIN message type.
#define LIN_QTY_MSG (uint32_T)mxGetPr(ssGetSFcnParam(S, 3))[0]      // Quantity of LIN messages to send.

// Hidden
#define pPROTL ssGetSFcnParam(S, 4)     // Name of the protocol.
#define PT_IDX (uint8_T)mxGetPr(ssGetSFcnParam(S, 5))[0]        // Port number selection for LIN.
#define LIN_IS_SLV (boolean_T)mxGetPr(ssGetSFcnParam(S, 6))[0]      // Status flag if it is a master or slave write block

#pragma endregion <-- Mask Parameters -->

#pragma region Globals - Static Values

static char_T ErrMsg[256];      // String for the error message of the S-Function.

#pragma endregion <-- Static Values -->


#pragma region S-Function - Initialization

/*
    Set all properties of the S-Function block (e.g. parameters, input ports, output ports and so on).
*/


static void mdlInitializeSizes(SimStruct *S)
{
    int8_T dataTypeInOut = 0;
    int_T status = 0;
    DTypeId objectIDLIN = 0;

    #ifdef MATLAB_MEX_FILE

    // Register and check user defined data type for LIN message
    objectIDLIN = ssRegisterDataType(S, "LIN_MESSAGE");

    if (INVALID_DTYPE_ID == objectIDLIN)
    {
        return;
    }

    status = ssSetDataTypeSize(S, objectIDLIN, sizeof(LINMsg));

    if (0 == status)
    {
        return;
    }

    #endif // MATLAB_MEX_FILE

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParams(0, S, QTY_PARAM))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Set input and output ports
    CreateSFunctionOutputPorts(0, S);

    if (1 == LIN_MSG_TYPE)
    {
        uint32_T i = 0;

        CreateSFunctionInputPorts(LIN_QTY_MSG, S);

        for (i = 0; i < LIN_QTY_MSG; i++)
        {
            SetSFunctionInputPortProperties(i, 1, objectIDLIN, 1, 1, 0, S);
        }
    }
    else
    {
        CreateSFunctionInputPorts(4, S);
        SetSFunctionInputPortProperties(0, LIN_QTY_MSG, SS_UINT8, 1, 1, 0, S);      // Protected ID
        SetSFunctionInputPortProperties(1, LIN_QTY_MSG, SS_UINT8, 1, 1, 0, S);      // Checksum
        SetSFunctionInputPortProperties(2, LIN_QTY_MSG, SS_UINT8, 1, 1, 0, S);      // Data length
        SetSFunctionInputPortProperties(3, LIN_QTY_MSG * 8, SS_UINT8, 1, 1, 0, S);  // Data (max. 8 byte)
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
    Set the sample times of the S-Function block.
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
*   Check if driver is initialized and get corresponding module index from driver strucutre.
*/
static void sg_ModelStart(SimStruct* S)
{
    #ifndef MATLAB_MEX_FILE
    {
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

        if (!IO61X_CheckIsModuleStatusReady(modIdx, ErrMsg))
        {
            printf("\n");
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        IO6X_SetLinMessageQuantity(modIdx, PT_IDX, LIN_QTY_MSG);
    }

    #endif
}

/*
    Send LIN or RAW message which are available on the input ports.
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    #ifndef MATLAB_MEX_FILE

    uint32_T modIdx = (uint32_T)ssGetIWorkValue(S, 0);
    uint32_T statusCode = 0;
    uint32_T i = 0;
    LINMsg *pMsg = NULL;

    IO61X_SetLinBuffer(modIdx, PT_IDX, true, LIN_IS_SLV);

    if (1 == LIN_MSG_TYPE)
    {
        for (i = 0; i < LIN_QTY_MSG; i++)
        {
            pMsg = (LINMsg*)ssGetInputPortSignal(S, i);
            pMsg->IDOnly = 0;
            statusCode = IO61X_SendLinMessage(modIdx, PT_IDX, (LINMsg*)ssGetInputPortSignal(S, i));
        }
    }
    else
    {
        uint8_T *pID = (uint8_T*)ssGetInputPortSignal(S, 0);
        uint8_T *pChecksum = (uint8_T*)ssGetInputPortSignal(S, 1);
        uint8_T *pLen = (uint8_T*)ssGetInputPortSignal(S, 2);
        uint8_T *pData = (uint8_T*)ssGetInputPortSignal(S, 3);
        uint8_T idOnly = 0;

        for (i = 0; i < LIN_QTY_MSG; i++)
        {
            if (!IO61X_CheckLinDlcAndChecksum(modIdx, PT_IDX, pLen[i], pChecksum[i], ErrMsg))
            {
                ssSetErrorStatus(S, ErrMsg);
                return;
            }

            statusCode = IO61X_SendLinRawMessage(modIdx, PT_IDX, &pID[i], &idOnly, &pChecksum[i], &pLen[i], pData);
            pData += 8;
        }

        IO61X_SetLinBuffer(modIdx, PT_IDX, false, LIN_IS_SLV);
    }

    #endif
}

/*
    Not used.
*/
static void sg_ModelStop(SimStruct *S)
{
    #ifndef MATLAB_MEX_FILE
    #endif 
}

#pragma endregion <-- mdlStart, mdlOutput, mdlTerminate -->

/*
    Prepare code for TLC file and assign S-Function parameters to TLC file.mdlWRT(SimStruct *S)
*/
static void mdlWRT(SimStruct *S)
{
}


#include "../common/libsg/sg_sfcn_glue.h"
