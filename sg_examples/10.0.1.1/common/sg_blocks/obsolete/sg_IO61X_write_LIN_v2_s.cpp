/*
*   File       : sg_IO61X_write_LIN_v2_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO611 write module for LIN protocol.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*/

#pragma region S-Function Default Defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO61X_write_LIN_v2_s

#pragma endregion <-- Default Defines -->

#include "include/IO61X_sfunc_help.h"
#include "include/LIN_Message_Definition.h"


#pragma region Define - S-Function Parameters

#define QTY_PARAM 12        // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_OUT_PORTS 0     // Quantity of output ports of the S-Function block.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 1        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

// Configuration
#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]       // Module ID of the IO61X module
#define pSAMPLE_TIME ssGetSFcnParam(S, 1)                       // Sample time of the block
#define LIN_MSG_TYPE (uint8_T)mxGetPr(ssGetSFcnParam(S, 2))[0]  // Selected message type (1= LIN, 2= RAW)

// LIN
#define PROT_ID (uint8_T)mxGetPr(ssGetSFcnParam(S, 3))[0]   // Protected Identifier of the LIN message
#define DLC (uint8_T)mxGetPr(ssGetSFcnParam(S, 4))[0]       // Data Length Code of the LIN message
#define pDEFAULT_DATA ssGetSFcnParam(S, 5)                  // Default message data
#define INPUT_ENABLE_RESPONSE (uint8_T)mxGetPr(ssGetSFcnParam(S,6))[0]   // activate input port for enabling/disabling the slave response for this msg ID

// Hidden
#define pPROTL ssGetSFcnParam(S, 7)                                     // Name of the protocol.
#define PT_IDX (uint8_T)mxGetPr(ssGetSFcnParam(S, 8))[0]                // Port Index
#define LIN_IS_SLV (boolean_T)mxGetPr(ssGetSFcnParam(S, 9))[0]          // Status flag if it is a master or slave write block
#define IS_ENHCD_CHCKSUM (boolean_T)mxGetPr(ssGetSFcnParam(S, 10))[0]    // Status flag if message is using enhanced checksum (=true) or not (=false)
#define QTY_LIN_BLOCKS (uint8_T)mxGetPr(ssGetSFcnParam(S, 11))[0]       // Quantity of LIN message blocks. Not used.

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

    // Check parameters
    if (NULL == mxGetPr(ssGetSFcnParam(S, 4)))
    {
        sprintf(ErrMsg, "Block mask parameter \"DLC\" is not valid!");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParams(0, S, QTY_PARAM))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Set input and output ports
    CreateSFunctionOutputPorts(QTY_OUT_PORTS, S);
    int qty_in_ports = 1;
    if (INPUT_ENABLE_RESPONSE)
        qty_in_ports++;
    CreateSFunctionInputPorts(qty_in_ports, S);

    if (1 == LIN_MSG_TYPE)
    {
        sprintf(ErrMsg, "Message type 'LIN' is not supported yet!!!");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
    else
    {
        SetSFunctionInputPortProperties(0, DLC, SS_UINT8, 1, 1, 0, S);      // Data

        // new input parameter: enable send response
        if (INPUT_ENABLE_RESPONSE)
            SetSFunctionInputPortProperties(1, 1, SS_UINT8, 1, 1, 0, S);
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
    Check if driver is initialized and get corresponding module index from driver structure.
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

    if (!IO61X_CheckIsModuleStatusReady(modIdx, ErrMsg))
    {
        CleanupOnError(0, MOD_ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    {
        void *pBuffer = NULL;

        if (!IO61X_CreatePort(modIdx, PT_IDX, 0, 3, LIN_IS_SLV, ErrMsg))
        {
            CleanupOnError(0, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        if (!IO61X_GetBlockBuffer_spin(modIdx, PT_IDX, 1, PROT_ID, &pBuffer, ErrMsg))
        {
            CleanupOnError(0, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
        ssSetPWorkValue(S, 0, pBuffer);

        uint8_t isIdOnly = (0 == LIN_IS_SLV) ? 1 : 0;
        IO61X_LinUpdateRwwbBuffer(modIdx, PT_IDX, LIN_IS_SLV, PROT_ID, isIdOnly, DLC, IS_ENHCD_CHCKSUM);
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

    if (1 == LIN_MSG_TYPE)
    {
        CleanupOnError(0, MOD_ID);
        sprintf(ErrMsg, "Message type 'LIN' is not supported yet!!!");
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
    else
    {
        LINMsg2 m = {0};
        m.msg.ProtID = PROT_ID;
        m.msg.EnhcdCksm = IS_ENHCD_CHCKSUM;
        m.msg.Len = DLC;
        m.msg.IDOnly = 0;
        if (INPUT_ENABLE_RESPONSE)
            m.senderOfResponse = *(uint8_T*)ssGetInputPortSignal(S, 1);
        else
            m.senderOfResponse = 1;
        memcpy(m.msg.Data, (void*)ssGetInputPortSignal(S, 0), DLC);
        if (IO61X_UpdateBuffer(modIdx, PT_IDX, ssGetPWorkValue(S, 0), (void*)&m, ErrMsg) < 0) {
            CleanupOnError(0, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
        IO61X_ReleaseWriteSempahore(modIdx);
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
