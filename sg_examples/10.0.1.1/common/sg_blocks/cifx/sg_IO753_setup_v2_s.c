#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO753_setup_v2_s

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
#include "MBM_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[1]
#define BUS_START_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define IPADDR_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define NETMASK_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define GATEWAY_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define BOOTP_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define DHCP_ARG (boolean_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define CMD_DELAY_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define DATA_SWAP_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define CMD_CONFIG_ARG ssGetSFcnParam(S, 10)
#define CMD_CONFIG_CRC_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define NUMBER_OF_ARGS 12

#define CMD_IPADDR(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 0 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_UNIT(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 1 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_CODE(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 2 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_ADDR(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 3 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_QTY(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 4 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_TIME(i) ((int32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 5 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_OFFSET(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 6 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_LEN(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 7 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_RW(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 8 * (int_T)mxGetM(CMD_CONFIG_ARG)]))
#define CMD_DT(i) ((uint32_T)(mxGetPr(CMD_CONFIG_ARG)[i + 9 * (int_T)mxGetM(CMD_CONFIG_ARG)]))

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i = 0;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!", NUMBER_OF_ARGS);
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
    ssSetNumPWork(S, 1);
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
    char_T ModuleIdStr[CIFX_DEFAULT_STR_LEN] = {0};
    char_T ModuleName[CIFX_DEFAULT_STR_LEN] = {0};

    /* Assemble the module ID string and module name */
    Cifx_CreateModuleIdStr(MOD_ID_ARG, NODE_ID_ARG, ModuleIdStr, sizeof(ModuleIdStr));
    snprintf(ModuleName, sizeof(ModuleName), "IO753");

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

    if (0 != Cifx_AddChannel(sizeof(MBM_PARAM_T), Node, &Channel))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    /* Set module parameters */
    snprintf(Module->Name, sizeof(Module->Name), ModuleName);
    Module->Type = CIFX_MODULE_TYPE_GEN;

    /* Set node parameters */
    Node->IrqEnabled = false;
    Node->DmaEnabled = true;
    snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxomb3.nxf");
    snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "3.0.0.3");
    snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    Node->BlockVersion = 2;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "Open Modbus/TCP");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = BUS_START_ARG;
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "ModbusTCP");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Client");
    Channel->StationType = CIFX_STATION_TYPE_M;
    Channel->ProtocolType = CIFX_PROTOCOL_MODBUS;
    Channel->CfgMode = CIFX_CFG_MODE_WARM;
    Channel->NumCfgFiles = 0;

    /* Set warmstart parameters */
    {
        uint32_T i = 0;
        MBM_PARAM_T *Param = (MBM_PARAM_T *)(Channel->Param);

        Param->IPaddr = IPADDR_ARG;
        Param->Netmask = NETMASK_ARG;
        Param->Gateway = GATEWAY_ARG;
        Param->DHCP = DHCP_ARG;
        Param->BootP = BOOTP_ARG;
        Param->CmdDelay = CMD_DELAY_ARG;
        Param->Swap = DATA_SWAP_ARG;
        Param->CmdCRC = CMD_CONFIG_CRC_ARG;

        for (i = 0; i < mxGetM(CMD_CONFIG_ARG); i++)
        {
            if (i >= MBM_MAX_NUM_CMD)
            {
                break;
            }

            Param->Cmd[i].Ipaddr = CMD_IPADDR(i);
            Param->Cmd[i].Unit = CMD_UNIT(i);
            Param->Cmd[i].Code = CMD_CODE(i);
            Param->Cmd[i].Addr = CMD_ADDR(i);
            Param->Cmd[i].Qty = CMD_QTY(i);
            Param->Cmd[i].Time = CMD_TIME(i);
            Param->Cmd[i].Offset = CMD_OFFSET(i);
            Param->Cmd[i].Len = CMD_LEN(i);
            Param->Cmd[i].Rw = CMD_RW(i);

            /* Calculate the total number of input and output bytes */
            /* Calculate the position of the last byte in the DPM input area */
            if (CMD_RW(i) == MBM_DIRECTION_READ)
            {
                Param->DiagOffset = CMD_OFFSET(i) + CMD_LEN(i);
                // Param->ReadLen += CMD_LEN(i);
                Param->ReadLen = Param->DiagOffset + sizeof(MBM_DIAG_T);

                /* Must be 4-byte-aligned */
                Param->DiagOffset = (Param->DiagOffset + 3) & (~3);
            }
            else
            {
                Param->WriteLen += CMD_LEN(i);
            }

            Param->NumOfCommands++;
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

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];

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

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node))
    {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];

    Cifx_ConditionalStopCom(Channel);
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
