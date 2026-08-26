/*
*   File       : sg_IO61X_status_LIN_s.cpp
*   Description: (obsolete9 This file includes all functions of the Simulik S-Function for the IO611 status module for LIN protocol.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*
*/

#pragma region S-Function Default Defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO61X_status_LIN_s

#pragma endregion <-- Default Defines -->

#include "./include/IO61X_sfunc_help.h"


#pragma region Define - S-Function Parameters

#define QTY_PARAM 10        // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 0        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

// Setup
#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]       // Module ID
#define pSAMPLE_TIME ssGetSFcnParam(S, 1)                       // Sample time of the block.

// Status
#define ENA_OP_MODE (boolean_T)mxGetPr(ssGetSFcnParam(S, 2))[0]             // Enalbe status port for the operating mode of LIN.
#define ENA_BDR (boolean_T)mxGetPr(ssGetSFcnParam(S, 3))[0]                 // Enalbe the status port for LIN baudrate.
#define ENA_BUSLOAD (boolean_T)mxGetPr(ssGetSFcnParam(S, 4))[0]             // Enalbe the status port for LIN bus load.
#define ENA_DATA_OVERRUN (boolean_T)mxGetPr(ssGetSFcnParam(S, 5))[0]        // Enalbe status port for LIN data overrun occured.
#define ENA_INIT_ACT (boolean_T)mxGetPr(ssGetSFcnParam(S, 6))[0]            // Enalbe status port for is LIN initialization active.

// Hidden
#define pPROTL ssGetSFcnParam(S, 7)     // Name of the protocol.
#define QTY_STAT_BLK (uint8_T)mxGetPr(ssGetSFcnParam(S, 8))[0]      // Quantity of available status blocks in the model.
#define PT_IDX (uint8_T)mxGetPr(ssGetSFcnParam(S, 9))[0]            // Port number.

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
    uint8_T i;
    uint8_T outputPortCounter = 0;

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParams(0, S, QTY_PARAM))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Set input and output ports
    CreateSFunctionInputPorts(0, S);

    outputPortCounter += (ENA_OP_MODE == 1) ? 1 : 0;
    outputPortCounter += (ENA_BDR == 1) ? 1 : 0;
    outputPortCounter += (ENA_BUSLOAD == 1) ? 1 : 0;
    outputPortCounter += (ENA_DATA_OVERRUN == 1) ? 1 : 0;
    outputPortCounter += (ENA_INIT_ACT == 1) ? 1 : 0;
    CreateSFunctionOutputPorts(outputPortCounter, S);

    for (i = 0; i < outputPortCounter; i++)
    {
        SetSFunctionOutputPortProperties(i, 1, SS_UINT32, 0, S);
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

        // Activate status handling
        IO61X_ActivateStatus(modIdx, PT_IDX, ErrMsg);
    }

    #endif
}

/*
*   Read the input ports and set the output ports of the S-Functions. This function is invoked cyclical (realtime process).

*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    #ifndef MATLAB_MEX_FILE

    uint8_T outputPortCounter = 0;
    uint32_T modIdx = (uint32_T)ssGetIWorkValue(S, 0);

    if (ENA_OP_MODE)
    {
        IO61X_LINGetStatusOpMode(modIdx, PT_IDX, (void*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_BDR)
    {
        IO61X_LINGetStatusBdr(modIdx, PT_IDX, (void*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_BUSLOAD)
    {
        IO61X_LINGetStatusBusLoad(modIdx, PT_IDX, (void*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_DATA_OVERRUN)
    {
        IO61X_LINGetStatusDataOvrn(modIdx, PT_IDX, (void*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    if (ENA_INIT_ACT)
    {
        IO61X_LINGetStatusInitAct(modIdx, PT_IDX, (void*)ssGetOutputPortSignal(S, outputPortCounter));
        outputPortCounter++;
    }

    #endif
}

/*
*   Clean up the S-Function block befor termination.
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
