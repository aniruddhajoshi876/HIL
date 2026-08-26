/*
*   File       : sg_IO61X_status_s.c
*   Description: This file includes all functions of the Simulik S-Function CAN status block for the IO611, IO612, IO613 and IO614 protocol.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*
*/

#pragma region S-Function Default Defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO61X_status_s

#pragma endregion <-- Default Defines -->

#include "include/IO61X_sfunc_help.h"

#pragma region Define - S-Function Parameters

#define QTY_PARAM 30        // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 0        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

// Setup tab
#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]           // Module ID
#define pSAMPLE_TIME ssGetSFcnParam(S, 1)                           // Sample time of the block.
#define BUS_RECO_CAN (uint8_T)mxGetPr(ssGetSFcnParam(S, 2))[0]      // Modus selection for CAN bus recovery 0:Off/1:Auto/2:Manual

// General controller status
#define ENA_AVG_BUS_LOAD (boolean_T)mxGetPr(ssGetSFcnParam(S, 3))[0]        // Average bus load (0 = disabled, 1 = enabled).

// CAN controller status
#define ENA_OP_MODE (boolean_T)mxGetPr(ssGetSFcnParam(S, 4))[0]             // CAN operation mode (0 = disabled, 1 = enabled).
#define ENA_TIMING_MODE (boolean_T)mxGetPr(ssGetSFcnParam(S, 5))[0]         // Timing mode (0 = disabled, 1 = enabled).
#define ENA_BPS (boolean_T)mxGetPr(ssGetSFcnParam(S, 6))[0]                 // Prescaler [BPS] (0 = disabled, 1 = enabled).
#define ENA_TSEG1 (boolean_T)mxGetPr(ssGetSFcnParam(S, 7))[0]               // Time segment 1 [TSEG1] (0 = disabled, 1 = enabled).
#define ENA_TSEG2 (boolean_T)mxGetPr(ssGetSFcnParam(S, 8))[0]               // Time segment 2 [TSEG2] (0 = disabled, 1 = enabled).
#define ENA_SJW (boolean_T)mxGetPr(ssGetSFcnParam(S, 9))[0]                 // Synchronisation jump width [SJW] (0 = disabled, 1 = enabled).
#define ENA_TRX_DELAY_COMP (boolean_T)mxGetPr(ssGetSFcnParam(S, 10))[0]     // Tranceiver delay compenstaion offset (0 = disabled, 1 = enabled).

// CAN-FD controller status
#define ENA_EXT_OP_MODE (boolean_T)mxGetPr(ssGetSFcnParam(S, 11))[0]            // CAN extended operation mode (0 = disabled, 1 = enabled).
#define ENA_TIMING_MODE_FD (boolean_T)mxGetPr(ssGetSFcnParam(S, 12))[0]         // Timing mode for FD (0 = disabled, 1 = enabled).
#define ENA_BPS_FD (boolean_T)mxGetPr(ssGetSFcnParam(S, 13))[0]                 // Prescaler [BPS] for FD (0 = disabled, 1 = enabled).
#define ENA_TSEG1_FD (boolean_T)mxGetPr(ssGetSFcnParam(S, 14))[0]               // Time segment 1 [TSEG1] for FD (0 = disabled, 1 = enabled).
#define ENA_TSEG2_FD (boolean_T)mxGetPr(ssGetSFcnParam(S, 15))[0]               // Time segment 2 [TSEG2] for FD (0 = disabled, 1 = enabled).
#define ENA_SJW_FD (boolean_T)mxGetPr(ssGetSFcnParam(S, 16))[0]                 // Synchronisation jump width [SJW] for FD (0 = disabled, 1 = enabled).
#define ENA_TRX_DELAY_COMP_FD (boolean_T)mxGetPr(ssGetSFcnParam(S, 17))[0]      // Tranceiver delay compenstaion offset for FD (0 = disabled, 1 = enabled).

// General port status
#define ENA_TX_PENDING (boolean_T)mxGetPr(ssGetSFcnParam(S, 18))[0]                 // Transmission pending (0 = disabled, 1 = enabled).
#define ENA_DATA_OVERRUN (boolean_T)mxGetPr(ssGetSFcnParam(S, 19))[0]               // Data overrun occured (0 = disabled, 1 = enabled).
#define ENA_ERR_WARN_LIMIT (boolean_T)mxGetPr(ssGetSFcnParam(S, 20))[0]             // Error warn limit is exceed.
#define ENA_BUS_RECO_STATE (boolean_T)mxGetPr(ssGetSFcnParam(S, 21))[0]             // Bus off status (0 = disabled, 1 = enabled).
#define ENA_INIT_MODE_ACT (boolean_T)mxGetPr(ssGetSFcnParam(S, 22))[0]              // Initialization mode active (0 = disabled, 1 = enabled).
#define ENA_BUS_COUPLING_ERR (boolean_T)mxGetPr(ssGetSFcnParam(S, 23))[0]           // Bus coupling error (0 = disabled, 1 = enabled).
#define ENA_HIGH_PRIO_TX_PENDING (boolean_T)mxGetPr(ssGetSFcnParam(S, 24))[0]       // Higth prio transmission pending (0 = disabled, 1 = enabled).
#define ENA_BUS_RECO_CNT (boolean_T)mxGetPr(ssGetSFcnParam(S, 25))[0]               // Higth prio transmission pending (0 = disabled, 1 = enabled).

// Hidden
#define pPROTL ssGetSFcnParam(S, 26)                                // Protocol string
#define QTY_STAT_BLK (uint8_T)mxGetPr(ssGetSFcnParam(S, 27))[0]     // Quantity of available status blocks in the model.
#define PT_IDX (uint8_T)mxGetPr(ssGetSFcnParam(S, 28))[0]           // Port index.
#define IS_FD_MOD (boolean_T)mxGetPr(ssGetSFcnParam(S, 29))[0]      // Status flag if current module a CAN-FD module (=true) or not (=false)

#pragma endregion <-- Mask Parameters -->

#pragma region Globals - Static Values

static char_T ErrMsg[256];      // String for the error message of the S-Function.

#pragma endregion <-- Static Values -->


#pragma region S-Function - Initialization

/*
*   Set all properties of the S-Function block (e.g. parameters, input ports, output ports and so on).
*/
static void mdlInitializeSizes(SimStruct *S)
{
    uint8_T outputPortCounter = 0;
    uint8_T i = 0;

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParams(0, S, QTY_PARAM))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Set input and output ports
    outputPortCounter += (ENA_AVG_BUS_LOAD == 1) ? 1 : 0;
    outputPortCounter += (ENA_OP_MODE == 1) ? 1 : 0;
    outputPortCounter += (ENA_TIMING_MODE == 1) ? 1 : 0;
    outputPortCounter += (ENA_BPS == 1) ? 1 : 0;
    outputPortCounter += (ENA_TSEG1 == 1) ? 1 : 0;
    outputPortCounter += (ENA_TSEG2 == 1) ? 1 : 0;
    outputPortCounter += (ENA_SJW == 1) ? 1 : 0;
    outputPortCounter += (ENA_TRX_DELAY_COMP == 1) ? 1 : 0;

    if (IS_FD_MOD)
    {
        outputPortCounter += (ENA_EXT_OP_MODE == 1) ? 1 : 0;
        outputPortCounter += (ENA_TIMING_MODE_FD == 1) ? 1 : 0;
        outputPortCounter += (ENA_BPS_FD == 1) ? 1 : 0;
        outputPortCounter += (ENA_TSEG1_FD == 1) ? 1 : 0;
        outputPortCounter += (ENA_TSEG2_FD == 1) ? 1 : 0;
        outputPortCounter += (ENA_SJW_FD == 1) ? 1 : 0;
        outputPortCounter += (ENA_TRX_DELAY_COMP_FD == 1) ? 1 : 0;
    }

    outputPortCounter += (ENA_TX_PENDING == 1) ? 1 : 0;
    outputPortCounter += (ENA_DATA_OVERRUN == 1) ? 1 : 0;
    outputPortCounter += (ENA_ERR_WARN_LIMIT == 1) ? 1 : 0;
    outputPortCounter += (ENA_BUS_RECO_STATE == 1) ? 1 : 0;
    outputPortCounter += (ENA_INIT_MODE_ACT == 1) ? 1 : 0;
    outputPortCounter += (ENA_BUS_COUPLING_ERR == 1) ? 1 : 0;

    if (IS_FD_MOD)
    {
        outputPortCounter += (ENA_HIGH_PRIO_TX_PENDING == 1) ? 1 : 0;
    }
    
    outputPortCounter += (ENA_BUS_RECO_CNT == 1) ? 1 : 0;
    CreateSFunctionOutputPorts(outputPortCounter, S);

    for (i = 0; i < outputPortCounter; i++)
    {
        SetSFunctionOutputPortProperties(i, 1, SS_UINT32, 0, S);
    }

    if (3 == BUS_RECO_CAN)
    {
        CreateSFunctionInputPorts(1, S);
        SetSFunctionInputPortProperties(0, 1, SS_UINT32, 1, 1, 0, S);
    }
    else
    {
        CreateSFunctionInputPorts(0, S);
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
*   Check driver initialization and get module index of the corresponding block in the driver structure.
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

    // Activate bus status
    if (!IO61X_ActivateStatus(modIdx, PT_IDX, ErrMsg))
    {
        CleanupOnError(0, MOD_ID);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    #endif
}

/*
*   Readout the status register for the corresponding port of the module, 
forward the data to the output ports and activate bus recovery process.
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    #ifndef MATLAB_MEX_FILE

    uint32_T inputPort = (3 == BUS_RECO_CAN) ? *(uint32_T*)ssGetInputPortSignal(S, 0) : 0;
    uint32_T modIdx = (uint32_T)ssGetIWorkValue(S, 0);
    uint32_T outputPortCounter = 0;

    if (ENA_AVG_BUS_LOAD)
    {
        IO61X_GetStatusBusLoadByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_OP_MODE)
    {
        IO61X_GetStatusOperatingModeByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_TIMING_MODE)
    {
        IO61X_GetCANStatusTimingModeByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_BPS)
    {
        IO61X_GetCANStatusBaudRatePrescalerByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_TSEG1)
    {
        IO61X_GetCANStatusBitTimeSegment1ByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_TSEG2)
    {
        IO61X_GetCANStatusBitTimeSegment2ByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_SJW)
    {
        IO61X_GetCANStatusSynchronisationJumpWidthByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_TRX_DELAY_COMP)
    {
        IO61X_GetCANStatusTransceiverDelayOffsetByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (IS_FD_MOD)
    {
        if (ENA_EXT_OP_MODE)
        {
            IO61X_GetStatusExtendedOperatingModeByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }

        if (ENA_TIMING_MODE_FD)
        {
            IO61X_GetCANFDStatusTimingModeByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }

        if (ENA_BPS_FD)
        {
            IO61X_GetCANFDStatusBaudRatePrescalerByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }

        if (ENA_TSEG1_FD)
        {
            IO61X_GetCANFDStatusBitTimeSegment1ByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }

        if (ENA_TSEG2_FD)
        {
            IO61X_GetCANFDStatusBitTimeSegment2ByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }

        if (ENA_SJW_FD)
        {
            IO61X_GetCANFDStatusSynchronisationJumpWidthByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }

        if (ENA_TRX_DELAY_COMP_FD)
        {
            IO61X_GetCANStatusTransceiverDelayOffsetByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }
    }

    if (ENA_TX_PENDING)
    {
        IO61X_GetStatusTransmissionPendingByStatusBlock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_DATA_OVERRUN)
    {
        IO61X_GetStatusDataOverrunByStatusblock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_ERR_WARN_LIMIT)
    {
        IO61X_GetStatusErrorWarningByStatusblock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_BUS_RECO_STATE)
    {
        IO61X_GetStatusBusOffByStatusblock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_INIT_MODE_ACT)
    {
        IO61X_GetStatusInitModeByStatusblock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_BUS_COUPLING_ERR)
    {
        IO61X_GetStatusBusCouplingErrorByStatusblock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (IS_FD_MOD)
    {
        if (ENA_HIGH_PRIO_TX_PENDING)
        {
            IO61X_GetStatusPrioTransmissionPendingByStatusblock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
            outputPortCounter++;
        }
    }

    if (ENA_BUS_RECO_CNT)
    {
        IO61X_GetStatusBusRecoveryCounterByStatusblock(modIdx, PT_IDX, (uint32_t*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    IO61X_ActivateStatusThread(modIdx, PT_IDX, inputPort, BUS_RECO_CAN);

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
