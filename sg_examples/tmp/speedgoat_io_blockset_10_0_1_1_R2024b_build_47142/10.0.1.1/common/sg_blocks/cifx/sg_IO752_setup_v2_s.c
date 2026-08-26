#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO752_setup_v2_s

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
#define DRIVE_ARG                     ssGetSFcnParam(S, 1)
#define CONFIG_MODE (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define OP_MODE (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 4))[1]
// 5
#define BUS_STARTUP_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define NAME_OF_STATION_ARG ssGetSFcnParam(S, 8)
#define VENDOR_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define DEVICE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 10))[0]
#define OBJ_ID_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define PN_MOD_CFG_ARG ssGetSFcnParam(S, 12)
#define PN_RECORD_CFG_ARG ssGetSFcnParam(S, 13)
#define PN_RECORD_DEFAULTS_ARG ssGetSFcnParam(S, 14)
#define PN_RECORD_SUCCESS_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 15))[0]
#define NUMBER_OF_ARGS 16

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
    int_T i = 0, n = 0;
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
        Module->Type = CIFX_MODULE_TYPE_GEN;
        Node->IrqEnabled = true;
        Node->DmaEnabled = true;
        if (CONFIG_MODE == CIFX_CFG_MODE_FILE)
        {
            snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxpns5.nxf");   // default DDP state = active
        }
        else
        {
            snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxpns4.nxf");   // default DDP state = inactive
        }
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "4.8.0.5");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    }
    Node->BlockVersion = 2;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "PROFINET IO Device");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = BUS_STARTUP_ARG;
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "PROFINET");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Device");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_PROFINET;
    Channel->CfgMode = CONFIG_MODE;
    if (CONFIG_MODE != CIFX_CFG_MODE_FILE)
    {
        Channel->NumCfgFiles = 0;
    }
    else
    {
        Channel->NumCfgFiles = 2;
        snprintf(Channel->CfgFiles[0].Name, sizeof(Channel->CfgFiles[0].Name), "CONFIG.NXD");
        snprintf(Channel->CfgFiles[1].Name, sizeof(Channel->CfgFiles[1].Name), "NWID.NXD");
    }

    /* Set warmstart parameters */
    if (CONFIG_MODE == CIFX_CFG_MODE_WARM)
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

        if (mxGetN(NAME_OF_STATION_ARG) >= PNS_NAME_OF_STATION_LEN)
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
        mxGetString(NAME_OF_STATION_ARG, Param->NameOfStation, mxGetN(NAME_OF_STATION_ARG) + 1);

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
        }

        for (i = 0; i < (int_T)mxGetM(PN_RECORD_CFG_ARG); i++)
        {
            PNS_RECORD_T *Record = NULL;
            uint32_T j = 0;

            if (0 != PNS_AddRecord_v2(
                         Channel,
                         &Record,
                         (uint32_T)mxGetPr(PN_RECORD_CFG_ARG)[i + 0 * (int_T)mxGetM(PN_RECORD_CFG_ARG)],
                         (uint32_T)mxGetPr(PN_RECORD_CFG_ARG)[i + 1 * (int_T)mxGetM(PN_RECORD_CFG_ARG)],
                         (uint32_T)mxGetPr(PN_RECORD_CFG_ARG)[i + 2 * (int_T)mxGetM(PN_RECORD_CFG_ARG)],
                         (uint32_T)mxGetPr(PN_RECORD_CFG_ARG)[i + 3 * (int_T)mxGetM(PN_RECORD_CFG_ARG)],
                         (uint32_T)mxGetPr(PN_RECORD_CFG_ARG)[i + 5 * (int_T)mxGetM(PN_RECORD_CFG_ARG)]))
            {
                sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, ModuleIdStr, CifxMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }

            // printf("my %i %i %X %i\n", Record->Slot, Record->SubSlot, Record->Index, Record->MaxDataLen);
            for (j = 0; j < Record->MaxDataLen; j++)
            {
                Record->Data[j] = (uint8_T)mxGetPr(PN_RECORD_DEFAULTS_ARG)[n];
                // printf("%X", Record->Data[j]);
                n++;
            }
            // printf("\n");
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

    Cifx_UnRegisterApplication(Channel);
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
