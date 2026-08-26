/*
*   File       : sg_IO611_setup_s.c
*   Description: This file includes all functions of the Simulik S-Function for the IO611 setup module.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$

*/

#pragma region S-Function Default Defines

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO611_setup_s

#pragma endregion <-- Default Defines -->

#pragma region Includes

#include "include/IO61X_sfunc_help.h"

#pragma endregion 

#pragma region Define - S-Function Parameters

#define QTY_PARAM 30        // Quantity of the S-Function block parameters which are used in this S-Function code file.
#define QTY_IN_PORTS 0      // Quantity of the input ports of the S-Function block.
#define QTY_OUT_PORTS 0     // Quantity of output ports of the S-Function block.
#define QTY_R_WORK 0        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
#define QTY_I_WORK 1        // Quantity of vectors/pointers of the data type INT of the S-Function.
#define QTY_P_WORK 0        // Quantity of vectors/pointers of the data type VOID of the S-Function.

#pragma endregion <-- S-Function Parameters -->

#pragma region Define - Mask Parameters

// Tab: Module Setup
#define MOD_ID (uint32_T)mxGetPr(ssGetSFcnParam(S, 0))[0]       // Module ID of the IO611 module.
#define pDR_LTR ssGetSFcnParam(S, 1)                            // String for the driver letter on the target system.
#define pPCI_SLOT ssGetSFcnParam(S, 2)                          // PCI bus number of the IO611 module.
#define PT_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 3))[0]          // Configure port 1 as: 1 = Disabled, 2 = CAN (HS), 3 = CAN-FD.
#define PT_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 4))[0]          // Configure port 2 as: 1 = Disabled, 2 = CAN (HS), 3 = CAN-FD.
#define PT_3 (uint8_T)mxGetPr(ssGetSFcnParam(S, 5))[0]          // Configure port 1 as: 1 = Disabled, 2 = CAN (HS/LS), 3 = CAN-FD.
#define PT_4 (uint8_T)mxGetPr(ssGetSFcnParam(S, 6))[0]          // Configure port 2 as: 1 = Disabled, 2 = CAN (HS/LS), 3 = CAN-FD.

// CAN port 1
#define CAN_OP_MODE_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 7))[0]                 // Number of the physical bus selection, 1 = highspeed, 0 = lowspeed for port 1.
#define CAN_BDR_BRP_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 8))[0]                // User defined baudrate value BRP for port 1 (CAN)
#define CAN_BDR_SJW_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 8))[1]                // User defined baudrate value SJW for port 1 (CAN)
#define CAN_BDR_TSEG1_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 8))[2]              // User defined baudrate value TSET1 for port 1 (CAN)
#define CAN_BDR_TSEG2_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 8))[3]              // User defined baudrate value TSET2 for port 1 (CAN)
#define CANFD_BDR_DATA_BRP_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 9))[0]         // User defined baudrate value BRP for port 1 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_SJW_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 9))[1]         // User defined baudrate value SJW for port 1 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_TSEG1_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 9))[2]       // User defined baudrate value TSEG1 for port 1 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_TSEG2_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 9))[3]       // User defined baudrate value TSEG2 for port 1 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_SP_1 (real64_T)mxGetPr(ssGetSFcnParam(S, 9))[4]          // User defined baudrate value Sample Point for port 1 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_BDR_1 (uint16_T)mxGetPr(ssGetSFcnParam(S, 9))[5]         // User defined baudrate value baudrate in kBit/s for port 1 (CAN-FD/Data phase).
#define CAN_STD_ACC_MASK_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 10))[0]          // Standard accetance mask 1 value for port 1 (CAN)
#define CAN_STD_ACC_CODE_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 10))[1]          // Standard accetance code 1 value for port 1 (CAN)
#define CAN_EXT_ACC_MASK_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 11))[0]          // Extended accetance mask 1 value for port 1 (CAN)
#define CAN_EXT_ACC_CODE_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 11))[1]          // Extended accetance code 1 value for port 1 (CAN)

// CAN port 2
#define CAN_OP_MODE_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 12))[0]                // Number of the physical bus selection, 1 = highspeed, 0 = lowspeed for port 2.
#define CAN_BDR_BRP_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 13))[0]               // User defined baudrate value BRP for port 2 (CAN)
#define CAN_BDR_SJW_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 13))[1]               // User defined baudrate value SJW for port 2 (CAN)
#define CAN_BDR_TSEG1_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 13))[2]             // User defined baudrate value TSET1 for port 2 (CAN)
#define CAN_BDR_TSEG2_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 13))[3]             // User defined baudrate value TSET2 for port 2 (CAN)
#define CANFD_BDR_DATA_BRP_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 14))[0]        // User defined baudrate value BRP for port 2 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_SJW_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 14))[1]        // User defined baudrate value SJW for port 2 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_TSEG1_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 14))[2]      // User defined baudrate value TSEG1 for port 2 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_TSEG2_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 14))[3]      // User defined baudrate value TSEG2 for port 2 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_SP_2 (real64_T)mxGetPr(ssGetSFcnParam(S, 14))[4]         // User defined baudrate value Sample Point for port 2 (CAN-FD/Data phase).
#define CANFD_BDR_DATA_BDR_2 (uint16_T)mxGetPr(ssGetSFcnParam(S, 14))[5]        // User defined baudrate value baudrate in kBit/s for port 2 (CAN-FD/Data phase).
#define CAN_STD_ACC_MASK_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 15))[0]          // Standard accetance mask 1 value for port 2 (cAN)
#define CAN_STD_ACC_CODE_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 15))[1]          // Standard accetance code 1 value for port 2 (CAN)
#define CAN_EXT_ACC_MASK_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 16))[0]          // Extended accetance mask 1 value for port 2 (CAN)
#define CAN_EXT_ACC_CODE_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 16))[1]          // Extended accetance code 1 value for port 2 (CAN)

// Init/term struct
#define pCAN_INIT_STRUCT ssGetSFcnParam(S, 17)      // Pointer to the initialization structures (CAN)
#define pCAN_TERM_STRUCT ssGetSFcnParam(S, 18)      // Pointer to the termination structures (CAN)

// LIN port 1
#define LIN_OP_MODE_1 (uint8_T)mxGetPr(ssGetSFcnParam(S, 19))[0]        // Operation mode for the LIN port 1 (master or slave)
#define LIN_BDR_1 (uint32_T)mxGetPr(ssGetSFcnParam(S, 20))[0]           // Baudrate of the LIN port 1.

// LIN port 2
#define LIN_OP_MODE_2 (uint8_T)mxGetPr(ssGetSFcnParam(S, 21))[0]        // Operation mode for the LIN port 2(master or slave)
#define LIN_BDR_2 (uint32_T)mxGetPr(ssGetSFcnParam(S, 22))[0]           // Baudrate of the LIN port 2.

// Hidden
#define pPROTL ssGetSFcnParam(S, 23)                                // Name of the protocol.
#define QTY_MOD (uint32_T)mxGetPr(ssGetSFcnParam(S, 24))[0]         // Quantity of available IO611 SETUP blocks in the Simulink model.
#define pCH_NO ssGetSFcnParam(S, 25)                                // Array of available channel numbers ( [ 1 2 3 4 ] on IO611 )
#define pPT_TYPES ssGetSFcnParam(S, 26)                             // Array for the port types of the module
#define pIS_PROTL_FD ssGetSFcnParam(S, 27)                          // Array for the port protocol
#define pPROTL_HELP_IDX ssGetSFcnParam(S, 28)                       // Array of the portocol index that's the index of the port within the protocol group (e.g.: CAN 1 = 0, CAN 2 = 1, LIN 1 = 0, LIN 2 = 1)
#define IS_FD_MOD (bool)(mxGetPr(ssGetSFcnParam(S, 29))[0] ? true:false)     // Status flag if current module a CAN-FD module (=true) or not (=false)

#pragma endregion <-- Mask Parameters -->

#pragma region Globals - Static Values

const int sg_module_type = SG_MODULE_TYPE_IO611;

static char_T ErrMsg[256];      // String for the error message of the S-Function.

#pragma endregion <-- Static Values -->


#pragma region S-Function - Initialization

/*
    Set all properties of the S-Function block (e.g. parameters, input ports, output ports and so on).
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

#pragma endregion <-- Initialization -->


#pragma region S-Function - mdlStart, mdlOutput, mdlTerminate

static void mdlStart_(SimStruct* S, bool isInit);

static void sg_ModelLoad(SimStruct *S)
{
    mdlStart_(S, true);
}

static void sg_ModelStart(SimStruct* S) { mdlStart_(S, false); }

/*
    Initialize enabled module ports, start the corresponding port controller and send initialization structures.
*/
static void mdlStart_(SimStruct *S, bool isInit)
{
#ifndef MATLAB_MEX_FILE

    uint32_T modIdx = 5;
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
            CleanupOnError(sg_module_type, MOD_ID, "Protocol is not supported");
            ssSetErrorStatus(S, "Protocol is not supported");
            return;
        }

        // Create driver structure
        if (!IO61X_CreateDriverModuleList(QTY_MOD, drLtr, ErrMsg))
        {
            CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        // Init model
        if (!IO61X_InitializeModule(MOD_ID, (uint8_T)mxGetN(pCH_NO), protl, bus, slot, &modIdx, ErrMsg))
        {
            CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
        ssSetIWorkValue(S, 0, modIdx);

        // Initialization of CAN/CAN-FD controller
        if (PT_1 > 1)
        {
            uint8_t ptIdx = 0;

            if (!IO61X_InitializeCanController(modIdx, ptIdx, (uint8_T)mxGetPr(pIS_PROTL_FD)[ptIdx]
                                               , (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx], CAN_OP_MODE_1
                                               , CAN_BDR_BRP_1, CAN_BDR_SJW_1, CAN_BDR_TSEG1_1, CAN_BDR_TSEG2_1, CANFD_BDR_DATA_BRP_1
                                               , CANFD_BDR_DATA_SJW_1, CANFD_BDR_DATA_TSEG1_1, CANFD_BDR_DATA_TSEG2_1, CANFD_BDR_DATA_SP_1
                                               , CANFD_BDR_DATA_BDR_1, CAN_STD_ACC_MASK_1, CAN_STD_ACC_CODE_1, CAN_EXT_ACC_MASK_1
                                               , CAN_EXT_ACC_CODE_1, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (PT_2 > 1)
        {
            uint8_t ptIdx = 1;

            if (!IO61X_InitializeCanController(modIdx, ptIdx, (boolean_T)mxGetPr(pIS_PROTL_FD)[ptIdx]
                                               , (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx],  CAN_OP_MODE_2
                                               , CAN_BDR_BRP_2, CAN_BDR_SJW_2, CAN_BDR_TSEG1_2, CAN_BDR_TSEG2_2, CANFD_BDR_DATA_BRP_2
                                               , CANFD_BDR_DATA_SJW_2, CANFD_BDR_DATA_TSEG1_2, CANFD_BDR_DATA_TSEG2_2, CANFD_BDR_DATA_SP_2
                                               , CANFD_BDR_DATA_BDR_2, CAN_STD_ACC_MASK_2, CAN_STD_ACC_CODE_2, CAN_EXT_ACC_MASK_2
                                               , CAN_EXT_ACC_CODE_2, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Initialization of LIN controller
        if (PT_3 > 1)
        {
            uint8_t ptIdx = 2;

            if (!IO61X_InitializeLincotroller(modIdx, ptIdx, LIN_OP_MODE_1, LIN_BDR_1, (uint8_T)mxGetPr(pCH_NO)[ptIdx]
                                              , (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx], (uint8_T)mxGetPr(pPT_TYPES)[ptIdx], ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (PT_4 > 1)
        {
            uint8_t ptIdx = 3;

            if (!IO61X_InitializeLincotroller(modIdx, ptIdx, LIN_OP_MODE_2, LIN_BDR_2, (uint8_T)mxGetPr(pCH_NO)[ptIdx]
                                              , (uint8_T)mxGetPr(pPROTL_HELP_IDX)[ptIdx], (uint8_T)mxGetPr(pPT_TYPES)[ptIdx], ErrMsg))
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
		SG_PRINTF(DEBUG, "sg_ModelStart begin start phase\n");
		
        /*  First check that module was properly initialized when application was loaded onto target (branch 1 == isInit)) */
        uint8_t idxOk = IO61X_GetModuleIndex(MOD_ID, protl, &modIdx, ErrMsg);

        // SG_PRINTF(DEBUG, "!idxOk: %i \t !IO61X_GetModuleStatusInitialized(modIdx): %i \n", !idxOk, !IO61X_GetModuleStatusInitialized(modIdx));

        if (!idxOk || !IO61X_GetModuleStatusInitialized(modIdx))
        {
            sprintf(ErrMsg, "module type=%d id=%d was not initialized!\n", sg_module_type, MOD_ID);
            CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
        ssSetIWorkValue(S, 0, modIdx);

        if (1 == IO61X_CheckIsModuleStatusReady(modIdx, ErrMsg))
        {
            return; // some other setup block instance already started the controller.
        }

        // Start CAN controller
        if (PT_1 > 1)
        {
            if (!IO61X_StartCanController(modIdx, 0, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (PT_2 > 1)
        {
            if (!IO61X_StartCanController(modIdx, 1, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        // Start LIN controller
        if (PT_3 > 1)
        {
            if (!IO61X_StartLinController(modIdx, 2, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (PT_4 > 1)
        {
            if (!IO61X_StartLinController(modIdx, 3, ErrMsg))
            {
                CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (!IO61X_SetModuleStatusReady(modIdx, ErrMsg))
        {
            CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        // Send initialization structure for CAN
        if ((PT_1 > 1) || (PT_2 > 1))
        {
            if (!SendInitTermStructure(modIdx, IS_FD_MOD, mxGetPr(pCAN_INIT_STRUCT))) {
                sprintf(ErrMsg, "SG %s: Module %i, send CAN initialization message(s) failed.", protl, MOD_ID);
                CleanupOnError(sg_module_type, MOD_ID, ErrMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }
    }

#endif
}

/*
    Not used.
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
    // not used
#endif
}



/*
    Send termination structures, stop all enabled port controllers and cleanup the complete driver structure.
*/
static void sg_ModelStop(SimStruct *S)
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

    // Send termination messages for CAN and CAN-FD
    if ((PT_1 > 1) || (PT_2 > 1))
    {
        if (!SendInitTermStructure(modIdx, IS_FD_MOD, mxGetPr(pCAN_TERM_STRUCT))) {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, send CAN termination message(s) failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    // Stop CAN controller
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

    // Stop LIN controller
    if (PT_3 > 1)
    {
        if (!IO61X_StopLinController(modIdx, 2))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, stop LIN controller failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }

    if (PT_4 > 1)
    {
        if (!IO61X_StopLinController(modIdx, 3))
        {
            CleanupOnError(sg_module_type, MOD_ID);
            sprintf(ErrMsg, "SG %s: Module %i, stop LIN controller failed.", protl, MOD_ID);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }
    }


    IO61X_SetModuleStatusStartPorts(modIdx, ErrMsg);

    IO61X_ClearPortBuffer(modIdx);

#endif 
}

#pragma endregion <-- mdlStart, mdlOutput, mdlTerminate -->

/*
    Prepare code for TLC file and assign S-Function parameters to TLC file.mdlWRT(SimStruct *S)
*/
static void mdlWRT(SimStruct *S)
{
    // not used
}

#include "../common/libsg/sg_sfcn_glue.h"

