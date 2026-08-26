#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO754_setup_v2_s

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
#include "MBS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
// 1
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 2))[1]
#define CFG_MODE (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define OP_MODE (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define BUS_STARUP (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define DATA_SWAP (uint32_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define MAP_FC1_AND_FC3 (uint32_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define PROVIDER_SERVER_CONNECTIONS (uint32_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define CLIENT_CONNECTION_WATCHDOT_TIME (uint32_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define RESPONSE_TIMEOUT (uint32_T) mxGetPr(ssGetSFcnParam(S, 10))[0]
#define SEND_ACKNOWLEDGEMENT_TIMEOUT (uint32_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define CONNECTION_ACKNOWLEDGEMENT_TIMEOUT (uint32_T) mxGetPr(ssGetSFcnParam(S, 12))[0]
#define CLOSE_ACKNOWLEDGEMENT_TIMEOUT (uint32_T) mxGetPr(ssGetSFcnParam(S, 13))[0]
#define pIP_ADDRESS ssGetSFcnParam(S, 14)
#define pNETMASK ssGetSFcnParam(S, 15)
#define pGATEWAY ssGetSFcnParam(S, 16)
#define BOOT_P (boolean_T) mxGetPr(ssGetSFcnParam(S, 17))[0]
#define DHCP (boolean_T) mxGetPr(ssGetSFcnParam(S, 18))[0]
// 19
// 20
// 21
// 22
// 23
// 24
// 25
// 26
// 27
// 28
// 29
// 30
// 31
// 32
// 33
#define NUMBER_OF_ARGS 34

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
    CIFX_MODULE_T *Module = NULL;
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;
    MBS_PARAM_T *Param = NULL;
    char_T ModuleIdStr[CIFX_DEFAULT_STR_LEN] = {0};
    char_T ModuleName[CIFX_DEFAULT_STR_LEN] = {0};

    /* Assemble the module ID string and module name */
    Cifx_CreateModuleIdStr(MOD_ID_ARG, NODE_ID_ARG, ModuleIdStr, sizeof(ModuleIdStr));
    if (NODE_ID_ARG > 0)
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO754-32");
    }
    else
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO754");
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

    if (0 != Cifx_AddChannel(sizeof(MBS_PARAM_T), Node, &Channel))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    Param = (MBS_PARAM_T *)(Channel->Param);

    /* Set module parameters */
    snprintf(Module->Name, sizeof(Module->Name), ModuleName);

    /* Set node parameters */
    if (NODE_ID_ARG > 0)
    {
        Module->Type = CIFX_MODULE_TYPE_TEWS_ETH;
        Node->IrqEnabled = false;
        Node->DmaEnabled = false;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "sgn52omb.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "2.6.0.5");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "sgnetX52.bin");
        snprintf(Node->FpgaFileName, sizeof(Node->FpgaFileName), "IO75X-32.bin");
        snprintf(Node->FpgaVersionName, sizeof(Node->FpgaVersionName), "IO75X-32.inf");
    }
    else
    {
        Module->Type = CIFX_MODULE_TYPE_GEN;
        Node->IrqEnabled = false;
        Node->DmaEnabled = true;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxomb3.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "3.0.0.3");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    }
    Node->BlockVersion = 2;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "Open Modbus/TCP");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = (BUS_STARUP != 1);
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "ModbusTCP");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Server");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_MODBUS;
    Channel->CfgMode = CFG_MODE;
    if (CFG_MODE != CIFX_CFG_MODE_FILE)
    {
        Channel->NumCfgFiles = 0;
    }
    else
    {
        Channel->NumCfgFiles = 1;
        snprintf(Channel->CfgFiles[0].Name, sizeof(Channel->CfgFiles[0].Name), "INIBATCH.NXD");
    }

    /* Set warmstart parameters */
    if (CFG_MODE == CIFX_CFG_MODE_WARM)
    {
        // Set structure: default values
        Param->SysFlgs = BUS_STARUP;
        Param->WdgTime = 0; // TODO
        Param->EnaMapFC1FC3 = MAP_FC1_AND_FC3;

        // Set structure: config values
        Param->OpenSrvSokt = PROVIDER_SERVER_CONNECTIONS;
        Param->DataSwap = DATA_SWAP;
        Param->AnsTimeout = RESPONSE_TIMEOUT;
        Param->OmbOpenTime = CLIENT_CONNECTION_WATCHDOT_TIME;
        Param->SndTimeout = SEND_ACKNOWLEDGEMENT_TIMEOUT;
        Param->ConTimeout = CONNECTION_ACKNOWLEDGEMENT_TIMEOUT;
        Param->CloseTimeout = CLOSE_ACKNOWLEDGEMENT_TIMEOUT;
        Param->ProtMode = OP_MODE;
        Param->EnaDHCP = DHCP;
        Param->EnaBootP = BOOT_P;
        mxGetString(pIP_ADDRESS, Param->IPAdr, mxGetN(pIP_ADDRESS) + 1);
        mxGetString(pNETMASK, Param->Netmask, mxGetN(pNETMASK) + 1);
        mxGetString(pGATEWAY, Param->Gateway, mxGetN(pGATEWAY) + 1);
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
    CIFX_MODULE_T *Module = NULL;

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];
    Module = (CIFX_MODULE_T *)Node->Module;

    if (CFG_MODE == CIFX_CFG_MODE_WARM) // Warmstart
    {
        if (OP_MODE > 1) // MsgMode
        {
            if (0 != Cifx_RegisterApplication(Channel))
            {
                sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, Node->ModuleIdStr, CifxMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }
    }
    Cifx_ConditionalStartCom(Channel);
}

static void sg_ModelStep(SimStruct *S)
{
    Cifx_StartBackground();
}

static void sg_ModelStop(SimStruct *S)
{
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;
    CIFX_MODULE_T *Module = NULL;

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];
    Module = (CIFX_MODULE_T *)Node->Module;

    Cifx_ConditionalStopCom(Channel);

    if (CFG_MODE == CIFX_CFG_MODE_WARM) // Warmstart
    {
        if (OP_MODE > 1) // MsgMode
        {
            if (0 != Cifx_UnRegisterApplication(Channel))
            {
                sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, Node->ModuleIdStr, CifxMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }
    }
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
