#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO752_setup_v3_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "cifxapi.h"
#include "cifx_common.h"
#include "PNS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[1]
#define BUS_START_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define STATION_NAME_ARG ssGetSFcnParam(S, 3)
#define VENDOR_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define DEVICE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define OBJ_ID_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define PN_MOD_CFG_ARG ssGetSFcnParam(S, 7)
#define PN_RECORD_SUCCESS_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define PN_SYS_RED_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define OPTIONAL_IDENT_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 10))[0]
#define DEVICE_TYPE_ARG ssGetSFcnParam(S, 11)
#define ORDER_ID_ARG ssGetSFcnParam(S, 12)
#define HW_REV_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 13))[0]
#define SW_REV_PREFIX_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 14))[0]
#define SW_REV_ARG ssGetSFcnParam(S, 15)
#define SERIAL_NUMBER_ARG ssGetSFcnParam(S, 16)
#define NUMBER_OF_ARGS 17

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg,
                "Wrong number of input arguments passed.\n%d arguments are expected\n",
                NUMBER_OF_ARGS);

        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++)
    {
        ssSetSFcnParamTunable(S, i, 0);
    }

    /* Ports */
    if (!ssSetNumInputPorts(S, 0))
        return;
    if (!ssSetNumOutputPorts(S, 0))
        return;

    /* Options */
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
}

#ifndef MATLAB_MEX_FILE

static void sg_ModelLoad(SimStruct *S)
{
    int_T i = 0;
    CIFX_MODULE_T *Module = NULL;
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;
    PNS_PARAM_T *Param = NULL;
    char_T ModuleIdStr[CIFX_DEFAULT_STR_LEN] = {0};
    char_T ModuleName[CIFX_DEFAULT_STR_LEN] = {0};

    /* Assemble the module ID string and module name */
    Cifx_CreateModuleIdStr(MOD_ID_ARG, NODE_ID_ARG, ModuleIdStr, sizeof(ModuleIdStr));
    if (NODE_ID_ARG > 0)
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO752-32");
    }
    else
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO752");
    }

    if (0 != Cifx_AddModule(MOD_ID_ARG, BUS_ARG, SLOT_ARG, &Module))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
    if (0 != Cifx_AddNode(NODE_ID_ARG, Module, &Node))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (0 != Cifx_AddChannel(sizeof(PNS_PARAM_T), Node, &Channel))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set module parameters */
    snprintf(Module->Name, sizeof(Module->Name), ModuleName);

    /* Set node parameters */
    if (NODE_ID_ARG > 0)
    {
        Module->Type = CIFX_MODULE_TYPE_TEWS_ETH;
        Node->IrqEnabled = false;
        Node->DmaEnabled = false;

        // snprintf(Node->FwFileName, sizeof(Node->FwFileName), "nx52pns2.nxf");
        // snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "4.6.0.3");

        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "nx52pns1.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "4.4.0.0");

        snprintf(Node->BtldName, sizeof(Node->BtldName), "sgnetX52.bin");
        snprintf(Node->FpgaFileName, sizeof(Node->FpgaFileName), "IO75X-32.bin");
        snprintf(Node->FpgaVersionName, sizeof(Node->FpgaVersionName), "IO75X-32.inf");
    }
    else
    {
        if (PN_SYS_RED_ARG)
        {
            snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxprs4.nxf");
        }
        else
        {
            snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxpns4.nxf");   // default DDP state = inactive
        }
        Module->Type = CIFX_MODULE_TYPE_GEN;
        Node->IrqEnabled = true;
        Node->DmaEnabled = true;
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "4.8.0.5");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    }
    Node->BlockVersion = 3;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "PROFINET IO Device");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = BUS_START_ARG;
    ;
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "PROFINET");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Device");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_PROFINET;

    Channel->CfgMode = CIFX_CFG_MODE_WARM;
    Channel->NumCfgFiles = 0;

    {
        Param = (PNS_PARAM_T *)(Channel->Param);

        if (mxGetN(PN_MOD_CFG_ARG) != PNS_SUBMODULE_INFO_LEN)
        {
            sprintf(ErrMsg, "%s, ID %s: Profinet slot / module configuration has to be a Mx%i matrix!", ModuleName, ModuleIdStr, PNS_SUBMODULE_INFO_LEN);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        if (mxGetM(PN_MOD_CFG_ARG) > PNS_MAX_NUM_SUBMODULES)
        {
            sprintf(ErrMsg, "%s, ID %s: Profinet slot/module configuration exceeds the maximum number of Profinet submodules!", ModuleName, ModuleIdStr);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        if (mxGetN(STATION_NAME_ARG) >= PNS_NAME_OF_STATION_LEN)
        {
            sprintf(ErrMsg, "%s, ID %s: Name of station too long!", ModuleName, ModuleIdStr);
            ssSetErrorStatus(S, ErrMsg);
            return;
        }

        Param->NumPnSubModules = (int_T)mxGetM(PN_MOD_CFG_ARG);
        Param->VendorId = VENDOR_ID_ARG;
        Param->DeviceId = DEVICE_ID_ARG;
        Param->ObjId = OBJ_ID_ARG;
        Param->RecordSuccess = PN_RECORD_SUCCESS_ARG;
        Param->OptionalIdent = OPTIONAL_IDENT_ARG;
        mxGetString(STATION_NAME_ARG, Param->NameOfStation, mxGetN(STATION_NAME_ARG) + 1);

        if (OPTIONAL_IDENT_ARG)
        {
            Param->HwRev = HW_REV_ARG;
            Param->SwRevPrefix = SW_REV_PREFIX_ARG;
            Param->SwRev[0] = (uint16_T)mxGetPr(SW_REV_ARG)[0];
            Param->SwRev[1] = (uint16_T)mxGetPr(SW_REV_ARG)[1];
            Param->SwRev[2] = (uint16_T)mxGetPr(SW_REV_ARG)[2];
            
            mxGetString(DEVICE_TYPE_ARG, Param->DeviceType, mxGetN(DEVICE_TYPE_ARG) + 1);
            mxGetString(ORDER_ID_ARG, Param->OrderId, mxGetN(ORDER_ID_ARG) + 1);
            mxGetString(SERIAL_NUMBER_ARG, Param->SerialNumber, mxGetN(SERIAL_NUMBER_ARG) + 1);
        }

        // SG_PRINTF_ERROR("%s %X %X %X %i\n", Param->NameOfStation, Param->VendorId, Param->DeviceId, Param->ObjId, Node->Channels[0]->BusStartupMode);

        for (i = 0; i < (int_T)mxGetM(PN_MOD_CFG_ARG); i++)
        {
            Param->pnSubModules[i].pnApi = (uint32_T)mxGetPr(PN_MOD_CFG_ARG)[i + 0 * (int_T)mxGetM(PN_MOD_CFG_ARG)]; // mxGetM: Number of rows in array
            Param->pnSubModules[i].pnSlot = (uint16_T)mxGetPr(PN_MOD_CFG_ARG)[i + 1 * (int_T)mxGetM(PN_MOD_CFG_ARG)];
            Param->pnSubModules[i].pnSubSlot = (uint16_T)mxGetPr(PN_MOD_CFG_ARG)[i + 2 * (int_T)mxGetM(PN_MOD_CFG_ARG)];
            Param->pnSubModules[i].pnMod = (uint32_T)mxGetPr(PN_MOD_CFG_ARG)[i + 3 * (int_T)mxGetM(PN_MOD_CFG_ARG)];
            Param->pnSubModules[i].pnSubMod = (uint32_T)mxGetPr(PN_MOD_CFG_ARG)[i + 4 * (int_T)mxGetM(PN_MOD_CFG_ARG)];
            Param->pnSubModules[i].InLen = (uint32_T)mxGetPr(PN_MOD_CFG_ARG)[i + 5 * (int_T)mxGetM(PN_MOD_CFG_ARG)];
            Param->pnSubModules[i].OutLen = (uint32_T)mxGetPr(PN_MOD_CFG_ARG)[i + 6 * (int_T)mxGetM(PN_MOD_CFG_ARG)];

            Param->InputLength += Param->pnSubModules[i].InLen;
            Param->OutputLength += Param->pnSubModules[i].OutLen;

            /*SG_PRINTF_ERROR("%i %i %i %X %X %i %i\n",
                            Param->pnSubModules[i].pnApi,
                            Param->pnSubModules[i].pnSlot,
                            Param->pnSubModules[i].pnSubSlot,
                            Param->pnSubModules[i].pnMod,
                            Param->pnSubModules[i].pnSubMod,
                            Param->pnSubModules[i].InLen,
                            Param->pnSubModules[i].OutLen);*/
        }
    }

    if (0 != Cifx_InitNode(Node))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
}

static void sg_ModelStart(SimStruct *S)
{
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;
    PNS_PARAM_T *Param = NULL;

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }
    Channel = Node->Channels[0];
    Param = (PNS_PARAM_T *)Channel->Param;

    /* Do only start the communication here, if we do not have any records defined in the model */
    if (Param->NumRecords == 0) {
        /* Start network communication */
        if (Channel->BusStartupMode == BUS_STARTUP_APP) {
            Cifx_StartCom(Channel, 0);
        }
    }
}

static void sg_ModelStep(SimStruct *S)
{
    Cifx_StartBackground();
}

static void sg_ModelStop(SimStruct *S)
{
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];

    /* We need to check the mailbox once before unregistering */
    PNS_AcyclicHandler(Channel);

    /* Unsubscribe because application is not able to handle indications any longer */
    Cifx_UnRegisterApplication(Channel);

    /* Stop the network communication */
    Cifx_ConditionalStopCom(Channel);

    PNS_RemoveRecords(Channel);
}

static void sg_ModelExit(SimStruct *S)
{
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];

    Cifx_FreeChannel(Channel);
}

#endif

#include "sg_sfcn_glue.h"
