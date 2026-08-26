/*
*   File       : sg_IO612_setup_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO612 setup module.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*

*/

#pragma region Default S-Function defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO612_setup_s

#pragma endregion <-- Default S-Function defines -->

#include "include/IO61X_sfunc_help.h"

#pragma region Define - S-Function Parameters

#define QTY_PARAM 31        // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_IN_PORTS 0      // Quantity of the input ports of the S-Function block.
#define QTY_OUT_PORTS 0     // Quantity of output ports of the S-Function block.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 0        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

// Setup tab
#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]       // Module ID of the IO612 module.
#define pDR_LTR ssGetSFcnParam(S, 1)                            // String for the driver letter on the target system.
#define pPCI_SLOT ssGetSFcnParam(S, 2)                          // PCI bus number of the IO612 module.
#define PT_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 3))[0]          // Configure port 1 as: 1 = Disabled, 2 = CAN (HS).
#define PT_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 4))[0]          // Configure port 2 as: 1 = Disabled, 2 = CAN (HS).
#define PT_3 (uint8_T)mxGetPr(ssGetSFcnParam(S, 5))[0]          // Configure port 3 as: 1 = Disabled, 2 = CAN (HS)
#define PT_4 (uint8_T)mxGetPr(ssGetSFcnParam(S, 6))[0]          // Configure port 4 as: 1 = Disabled, 2 = CAN (HSS).

// CAN port 1
#define CAN_OP_MODE_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 7))[0]             // Number of the physical bus selection, 1 = highspeed.
#define CAN_BDR_BRP_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 8))[0]             // User defined baudrate value BRP for port 1.
#define CAN_BDR_SJW_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 8))[1]             // User defined baudrate value SJW for port 1.
#define CAN_BDR_TSEG1_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 8))[2]           // User defined baudrate value TSET1 for port 1.
#define CAN_BDR_TSEG2_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 8))[3]           // User defined baudrate value TSET2 for port 1.
#define CAN_STD_ACC_MASK_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 9))[0]       // Standard accetance mask 1 value for port 1.
#define CAN_STD_ACC_CODE_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 9))[1]       // Standard accetance code 1 value for port 1.
#define CAN_EXT_ACC_MASK_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 10))[0]      // Extended accetance mask 1 value for port 1.
#define CAN_EXT_ACC_CODE_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 10))[1]      // Extended accetance code 1 value for port 1.

// CAN port 2
#define CAN_OP_MODE_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 11))[0]            // Number of the physical bus selection, 1 = highspeed, 0 = lowspeed for port 2.
#define CAN_BDR_BRP_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 12))[0]            // User defined baudrate value BRP for port 2.
#define CAN_BDR_SJW_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 12))[1]            // User defined baudrate value SJW for port 2.
#define CAN_BDR_TSEG1_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 12))[2]          // User defined baudrate value TSET1 for port 2.
#define CAN_BDR_TSEG2_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 12))[3]          // User defined baudrate value TSET2 for port 2.
#define CAN_STD_ACC_MASK_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 13))[0]      // Standard accetance mask 1 value for port 2.
#define CAN_STD_ACC_CODE_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 13))[1]      // Standard accetance code 1 value for port 2.
#define CAN_EXT_ACC_MASK_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 14))[0]      // Extended accetance mask 1 value for port 2.
#define CAN_EXT_ACC_CODE_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 14))[1]      // Extended accetance code 1 value for port 2.

// CAN 3
#define CAN_OP_MODE_3 (uint8_T)mxGetPr(ssGetSFcnParam(S, 15))[0]            // Number of the physical bus selection, 1 = highspeed for port 3.
#define CAN_BDR_BRP_3 (uint8_T)mxGetPr(ssGetSFcnParam(S, 16))[0]            // User defined baudrate value BRP for port 3.
#define CAN_BDR_SJW_3 (uint8_T)mxGetPr(ssGetSFcnParam(S, 16))[1]            // User defined baudrate value SJW for port 3.
#define CAN_BDR_TSEG1_3 (uint8_T)mxGetPr(ssGetSFcnParam(S, 16))[2]          // User defined baudrate value TSET1 for port 3.
#define CAN_BDR_TSEG2_3 (uint8_T)mxGetPr(ssGetSFcnParam(S, 16))[3]          // User defined baudrate value TSET2 for port 3.
#define CAN_STD_ACC_MASK_3 (uint32_T)mxGetPr(ssGetSFcnParam(S, 17))[0]      // Standard accetance mask 1 value for port 3.
#define CAN_STD_ACC_CODE_3 (uint32_T)mxGetPr(ssGetSFcnParam(S, 17))[1]      // Standard accetance code 1 value for port 3.
#define CAN_EXT_ACC_MASK_3 (uint32_T)mxGetPr(ssGetSFcnParam(S, 18))[0]      // Extended accetance mask 1 value for port 3.
#define CAN_EXT_ACC_CODE_3 (uint32_T)mxGetPr(ssGetSFcnParam(S, 18))[1]      // Extended accetance code 1 value for port 3.

// CAN 4
#define CAN_OP_MODE_4 (uint8_T)mxGetPr(ssGetSFcnParam(S, 19))[0]            // Number of the physical bus selection, 1 = highspeed for port 4.
#define CAN_BDR_BRP_4 (uint8_T)mxGetPr(ssGetSFcnParam(S, 20))[0]            // User defined baudrate value BRP for port 4.
#define CAN_BDR_SJW_4 (uint8_T)mxGetPr(ssGetSFcnParam(S, 20))[1]            // User defined baudrate value SJW for port 4.
#define CAN_BDR_TSEG1_4 (uint8_T)mxGetPr(ssGetSFcnParam(S, 20))[2]          // User defined baudrate value TSET1 for port 4.
#define CAN_BDR_TSEG2_4 (uint8_T)mxGetPr(ssGetSFcnParam(S, 20))[3]          // User defined baudrate value TSET2 for port 4.
#define CAN_STD_ACC_MASK_4 (uint32_T)mxGetPr(ssGetSFcnParam(S, 21))[0]      // Standard accetance mask 1 value for port 4.
#define CAN_STD_ACC_CODE_4 (uint32_T)mxGetPr(ssGetSFcnParam(S, 21))[1]      // Standard accetance code 1 value for port 4.
#define CAN_EXT_ACC_MASK_4 (uint32_T)mxGetPr(ssGetSFcnParam(S, 22))[0]      // Extended accetance mask 1 value for port 4.
#define CAN_EXT_ACC_CODE_4 (uint32_T)mxGetPr(ssGetSFcnParam(S, 22))[1]      // Extended accetance code 1 value for port 4.

// Init/Termination structs
#define pCAN_INIT_STRUCT ssGetSFcnParam(S, 23)      // Pointer to the initialization structure
#define pCAN_TERM_STRUCT ssGetSFcnParam(S, 24)      // Pointer to the termination structure

// Hidden parameters
#define pPROTL ssGetSFcnParam(S, 25)                                // Name of the protocol.
#define QTY_MOD (uint32_T)mxGetPr(ssGetSFcnParam(S, 26))[0]         // Quantitay of available IO613 SETUP blocks in the Simulink model.
#define pCH_NO ssGetSFcnParam(S, 27)                                // Array for the channle number of the port.
#define pPT_TYPES ssGetSFcnParam(S, 28)                             // Array for the port types of the module
#define pPROTL_HELP_IDX ssGetSFcnParam(S, 29)                       // Array of the portocol index that's the index of the port within the protocol group (e.g.: CAN 1 = 0, CAN 2 = 1, LIN 1 = 0, LIN 2 = 1)
#define IS_FD_MOD (bool)(mxGetPr(ssGetSFcnParam(S, 30))[0] ? true:false)     // Status flag if current module a CAN-FD module (=true) or not (=false)

#pragma endregion <-- Mask Parameters -->

#pragma region Globals - Static

const int sg_module_type = SG_MODULE_TYPE_IO612;

static char_T ErrMsg[256];      // String for the error message of the S-Function.

#pragma endregion <-- Static -->



#pragma region S-Function Initialization

/*
*   Set all properties of the S-Function block (e.g. parameters, input ports, output ports and so on).
*/
static void mdlInitializeSizes(SimStruct *S)
{
    // Set and check parameters
    if (0 == SetAndCheckSFunctionParams(0, S, QTY_PARAM))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    // Set input and output ports
    CreateSFunctionInputPorts(QTY_IN_PORTS, S);
    CreateSFunctionOutputPorts(QTY_OUT_PORTS, S);

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
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);     // see SS_OPTION in simstruct.h
}


/*
*   Set the sample times of the S-Function block.
*/
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

#pragma endregion <-- S-Function Initialization -->

#pragma region S-Function Start, Output, Terminate

static void mdlStart_(SimStruct* S, bool isInit);
static void sg_ModelLoad(SimStruct *S)
{
    mdlStart_(S, true);
}
static void sg_ModelStart(SimStruct* S) { mdlStart_(S, false); }

/*
    This function can be used to set the start options of the S-Function block.
*/
static void mdlStart_(SimStruct* S, bool isInit)
{
#ifndef MATLAB_MEX_FILE

    uint32_T modIdx = 0;
    char_T protl[10] = {0};
    sg_mod_list mod_data;

    // Get protocol string
    mxGetString(pPROTL, protl, 7);

    if (0 == sg_module_get(&mod_data, sg_module_type, MOD_ID))
        sg_module_register(sg_module_type, MOD_ID);

    if (isInit)
    {
        SG_PRINTF(DEBUG, "sg_ModelStart begin init phase\n");

        if (IO61X_CheckIsDriverInitialized(MOD_ID, protl, ErrMsg)) {
            if (IO61X_GetModuleIndex(MOD_ID, protl, &modIdx, ErrMsg))
                // another Setup block has initialized this same module
                return;
        }

        int16_T bus = 0;
        int16_T slot = 0;
        char_T drLtr[10] = {0};

        IO61X_TargetDefaults();

        // Get driver letter and PCI values
        mxGetString(pDR_LTR, drLtr, 7);

        if (1 == mxGetN(pPCI_SLOT))
        {
            slot = (int16_T)mxGetPr(pPCI_SLOT)[0];
            bus = (-1 == slot) ? -1 : 0;
        }
        else
        {
            bus = (int16_T)mxGetPr(pPCI_SLOT)[0];
            slot = (int16_T)mxGetPr(pPCI_SLOT)[1];
        }

        // Print module information
        if (!IO61X_PrintModuleInfo(MOD_ID, bus, slot, protl))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            ssSetErrorStatus(S, "Protocol is not supported");
            return;
        }

        // Create driver structure
        if (!IO61X_CreateDriverModuleList(QTY_MOD, drLtr, ErrMsg))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        // Init model
        if (!IO61X_InitializeModule(MOD_ID, (uint8_T)mxGetN(pCH_NO), protl, bus, slot, &modIdx, ErrMsg))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        // g_log.dbg(" modIdx: %i", modIdx);

        ssSetIWorkValue(S, 0, modIdx);

        // Initialize controller CAN port 1
        if (PT_1 > 1)
        {
            uint8_t ptIdx = 0;

            if (!IO61X_InitializeCanController(modIdx, ptIdx, 0, (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx]
                                               , CAN_OP_MODE_1, CAN_BDR_BRP_1, CAN_BDR_SJW_1, CAN_BDR_TSEG1_1
                                               , CAN_BDR_TSEG2_1, 0, 0, 0, 0, 0, 0, CAN_STD_ACC_MASK_1, CAN_STD_ACC_CODE_1, CAN_EXT_ACC_MASK_1
                                               , CAN_EXT_ACC_CODE_1, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Initialize controller CAN port 2
        if (PT_2 > 1)
        {
            uint8_t ptIdx = 1;

            if (!IO61X_InitializeCanController(modIdx, ptIdx, 0, (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx]
                                               , CAN_OP_MODE_2, CAN_BDR_BRP_2, CAN_BDR_SJW_2, CAN_BDR_TSEG1_2
                                               , CAN_BDR_TSEG2_2, 0, 0, 0, 0, 0, 0, CAN_STD_ACC_MASK_2, CAN_STD_ACC_CODE_2, CAN_EXT_ACC_MASK_2
                                               , CAN_EXT_ACC_CODE_2, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Initialize controller CAN port 3
        if (PT_3 > 1)
        {
            uint8_t ptIdx = 2;

            if (!IO61X_InitializeCanController(modIdx, ptIdx, 0, (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx]
                                               , CAN_OP_MODE_3, CAN_BDR_BRP_3, CAN_BDR_SJW_3, CAN_BDR_TSEG1_3
                                               , CAN_BDR_TSEG2_3, 0, 0, 0, 0, 0, 0, CAN_STD_ACC_MASK_3, CAN_STD_ACC_CODE_3, CAN_EXT_ACC_MASK_3
                                               , CAN_EXT_ACC_CODE_3, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Initialize controller CAN port 4
        if (PT_4 > 1)
        {
            uint8_t ptIdx = 3;

            if (!IO61X_InitializeCanController(modIdx, ptIdx, 0, (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx]
                                               , CAN_OP_MODE_4, CAN_BDR_BRP_4, CAN_BDR_SJW_4, CAN_BDR_TSEG1_4
                                               , CAN_BDR_TSEG2_4, 0, 0, 0, 0, 0, 0, CAN_STD_ACC_MASK_4, CAN_STD_ACC_CODE_4, CAN_EXT_ACC_MASK_4
                                               , CAN_EXT_ACC_CODE_4, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (!IO61X_SetModuleStatusStartPorts(modIdx, ErrMsg))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }
    else
    {
        /*  First check that module was properly initialized when application was loaded onto target (branch 1 == isInit)) */
        uint8_t idxOk = IO61X_GetModuleIndex(MOD_ID, protl, &modIdx, ErrMsg);
        if (!idxOk || !IO61X_GetModuleStatusInitialized(modIdx))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "module type=%d id=%d was not initialized!\n", sg_module_type, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
        ssSetIWorkValue(S, 0, modIdx);

        if (1 == IO61X_CheckIsModuleStatusReady(modIdx, ErrMsg))
        {
            return; // some other setup block instance already started the controller.
        }
        // Start controller CAN port 1
        if (PT_1 > 1)
        {
            if (!IO61X_StartCanController(modIdx, 0, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Start controller CAN port 2
        if (PT_2 > 1)
        {
            if (!IO61X_StartCanController(modIdx, 1, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Start controller CAN port 3
        if (PT_3 > 1)
        {
            if (!IO61X_StartCanController(modIdx, 2, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Start controller CAN port 4
        if (PT_4 > 1)
        {
            if (!IO61X_StartCanController(modIdx, 3, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (!IO61X_SetModuleStatusReady(modIdx, ErrMsg))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        // Send initialization structure for CAN
        if ((PT_1 > 1) || (PT_2 > 1) || (PT_3 > 1) || (PT_4 > 1))
        {
            if (!SendInitTermStructure(modIdx, IS_FD_MOD, mxGetPr(pCAN_INIT_STRUCT))) {
                printf("\n");
                sg_module_unregister(sg_module_type, MOD_ID);
                sprintf(ErrMsg, "SG %s: Module %i, send CAN initialization message(s) failed.", protl, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }
    }

#endif
}

/*
    Not used
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE

#endif
}


/*
    Send termination structures, stop all enabled port controllers and cleanup the complete driver sturcture.
*/
static void sg_ModelStop(SimStruct* S)
{
#ifndef MATLAB_MEX_FILE

    uint32_T modIdx = ssGetIWorkValue(S, 0);
    char_T protl[10] = { 0 };
    // Get protocol string
    mxGetString(pPROTL, protl, 7);
	
    sg_mod_list mod_data;
    if (sg_module_get(&mod_data, sg_module_type, MOD_ID) > 0)
		sg_module_unregister(sg_module_type, MOD_ID);

    // Check if another Setup block instance was already called for this block. (relevant in referenced model systems)
    if (0 == IO61X_CheckIsModuleStatusReady(modIdx, ErrMsg))
    {
        return; // some other setup block instance already stopped the controller.
    }

    // Send termination messages for CAN
    if ((PT_1 > 1) || (PT_2 > 1) || (PT_3 > 1) || (PT_4 > 1))
    {
        if (!SendInitTermStructure(modIdx, IS_FD_MOD, mxGetPr(pCAN_TERM_STRUCT))) {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, send CAN termination message(s) failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    // Stop controller CAN port 1
    if (PT_1 > 1)
    {
        if (!IO61X_StopCanController(modIdx, 0))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, stop CAN controller failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    // Stop controller CAN port 2 and/or LIN port 1
    if (PT_2 > 1)
    {
        if (!IO61X_StopCanController(modIdx, 1))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, stop CAN controller failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    // Stop controller CAN port 3
    if (PT_3 > 1)
    {
        if (!IO61X_StopCanController(modIdx, 2))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, stop CAN controller failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    // Stop controller CAN port 4
    if (PT_4 > 1)
    {
        if (!IO61X_StopCanController(modIdx, 3))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, stop CAN controller failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    IO61X_SetModuleStatusStartPorts(modIdx, ErrMsg);

    IO61X_ClearPortBuffer(modIdx);

#endif 
}

#pragma endregion <-- S-Function Start, Output, Terminate -->


/*
    Not used
*/
static void mdlWRT(SimStruct *S)
{
}


#include "../common/libsg/sg_sfcn_glue.h"
