#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO756_setup_s

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
#include "EIS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[1]
#define SAMPLETIME_ARG ssGetSFcnParam(S, 2)
// 3
#define OP_MODE (uint8_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define CONFIG_MODE (uint8_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define INPUT_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define OUTPUT_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define DHCP_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define BOOTP_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define IPADRR_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 10))[0]
#define IPADDRESS (uint32_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define NETMASK (uint32_T) mxGetPr(ssGetSFcnParam(S, 12))[0]
#define GATEWAY (uint32_T) mxGetPr(ssGetSFcnParam(S, 13))[0]
#define WATCHDOGTIME (uint32_T) mxGetPr(ssGetSFcnParam(S, 14))[0]
#define VENDID (uint16_T) mxGetPr(ssGetSFcnParam(S, 15))[0]
#define PRODUCTTYPE (uint16_T) mxGetPr(ssGetSFcnParam(S, 16))[0]
#define PRODUCTCODE (uint16_T) mxGetPr(ssGetSFcnParam(S, 17))[0]
#define MAJORREV (uint8_T) mxGetPr(ssGetSFcnParam(S, 18))[0]
#define MINORREV (uint8_T) mxGetPr(ssGetSFcnParam(S, 19))[0]
#define pDEVICENAME ssGetSFcnParam(S, 20)
#define SYSTEMFLAGS (uint32_T) mxGetPr(ssGetSFcnParam(S, 21))[0]
#define NETMASK_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 22))[0]
#define GATEWAY_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 23))[0]
#define PORT1_NEG_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 24))[0]
#define PORT1_DUPLEX_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 25))[0]
#define PORT1_SPEED_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 26))[0]
#define PORT2_OWN_SETTINGS (uint8_T) mxGetPr(ssGetSFcnParam(S, 27))[0]
#define PORT2_NEG_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 28))[0]
#define PORT2_DUPLEX_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 29))[0]
#define PORT2_SPEED_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 30))[0]
#define SERIALNUMBER (uint32_T) mxGetPr(ssGetSFcnParam(S, 31))[0]
#define INPUTASSINSTANCE (uint32_T) mxGetPr(ssGetSFcnParam(S, 32))[0]
#define INPUTASSFLAGS_3 (uint8_T) mxGetPr(ssGetSFcnParam(S, 33))[0]
#define INPUTASSFLAGS_6 (uint8_T) mxGetPr(ssGetSFcnParam(S, 34))[0]
#define INPUTASSFLAGS_7 (uint8_T) mxGetPr(ssGetSFcnParam(S, 35))[0]
#define OUTPUTASSINSTANCE (uint32_T) mxGetPr(ssGetSFcnParam(S, 36))[0]
#define OUTPUTASSFLAGS_3 (uint8_T) mxGetPr(ssGetSFcnParam(S, 37))[0]
#define OUTPUTASSFLAGS_6 (uint8_T) mxGetPr(ssGetSFcnParam(S, 38))[0]
#define OUTPUTASSFLAGS_7 (uint8_T) mxGetPr(ssGetSFcnParam(S, 39))[0]
#define QOSFLAGS (uint32_T) mxGetPr(ssGetSFcnParam(S, 40))[0]
#define TAG802_EN (uint8_T) mxGetPr(ssGetSFcnParam(S, 41))[0]
#define DSCP_URGENT (uint8_T) mxGetPr(ssGetSFcnParam(S, 42))[0]
#define DSCP_SCHEDULED (uint8_T) mxGetPr(ssGetSFcnParam(S, 43))[0]
#define DSCP_HIGH (uint8_T) mxGetPr(ssGetSFcnParam(S, 44))[0]
#define DSCP_LOW (uint8_T) mxGetPr(ssGetSFcnParam(S, 45))[0]
#define DSCP_EXPLICIT (uint8_T) mxGetPr(ssGetSFcnParam(S, 46))[0]
#define NAMESERVER (uint32_T) mxGetPr(ssGetSFcnParam(S, 47))[0]
#define NAMESERVER_2 (uint32_T) mxGetPr(ssGetSFcnParam(S, 48))[0]
#define DOMAINNAME ssGetSFcnParam(S, 49)
#define HOSTNAME ssGetSFcnParam(S, 50)
#define SELECTACD (uint8_T) mxGetPr(ssGetSFcnParam(S, 51))[0]
#define QUICKCONNECTFLAGS (uint8_T) mxGetPr(ssGetSFcnParam(S, 52))[0]
#define NUMBER_OF_ARGS (54)

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
    EIS_PARAM_T *Param = NULL;
    char_T ModuleIdStr[CIFX_DEFAULT_STR_LEN] = {0};
    char_T ModuleName[CIFX_DEFAULT_STR_LEN] = {0};

    /* Assemble the module ID string and module name */
    Cifx_CreateModuleIdStr(MOD_ID_ARG, NODE_ID_ARG, ModuleIdStr, sizeof(ModuleIdStr));
    if (NODE_ID_ARG > 0)
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO756-32");
    }
    else
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO756");
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

    if (0 != Cifx_AddChannel(sizeof(EIS_PARAM_T), Node, &Channel))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    Param = (EIS_PARAM_T *)(Channel->Param);

    /* Set module parameters */
    snprintf(Module->Name, sizeof(Module->Name), ModuleName);

    /* Set node parameters */
    if (NODE_ID_ARG > 0)
    {
        Module->Type = CIFX_MODULE_TYPE_TEWS_ETH;
        Node->IrqEnabled = false;
        Node->DmaEnabled = false;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "sgn52eis.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "3.3.0.14");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "sgnetX52.bin");
        snprintf(Node->FpgaFileName, sizeof(Node->FpgaFileName), "IO75X-32.bin");
        snprintf(Node->FpgaVersionName, sizeof(Node->FpgaVersionName), "IO75X-32.inf");
    }
    else
    {
        Module->Type = CIFX_MODULE_TYPE_GEN;
        Node->IrqEnabled = false;
        Node->DmaEnabled = true;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxeis.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "3.8.0.2");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    }
    Node->BlockVersion = 1;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "EtherNet/IP Adapter");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = 0; // Automatic
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "EthernetIP");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Adapter");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_ETHERNETIP;
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
        Param->sysFlgs = SYSTEMFLAGS;
        Param->wdgTime = WATCHDOGTIME;
        Param->inLen = INPUT_ARG;
        Param->outLen = OUTPUT_ARG;
        Param->IPadr = IPADDRESS;
        Param->netMask = NETMASK;
        Param->gateway = GATEWAY;
        Param->venID = VENDID;
        Param->prodType = PRODUCTTYPE;
        Param->prodCode = PRODUCTCODE;
        Param->serNo = SERIALNUMBER;
        Param->minRev = MINORREV;
        Param->majRev = MAJORREV;
        Param->inputAssInst = INPUTASSINSTANCE;
        Param->outputAssInst = OUTPUTASSINSTANCE;
        Param->nameSrv = NAMESERVER;
        Param->nameSrv2 = NAMESERVER_2;
        Param->selAcd = SELECTACD;
        Param->enaIPadr = IPADRR_EN;
        Param->enaNetMask = NETMASK_EN;
        Param->enaGateway = GATEWAY_EN;
        Param->enaBootP = BOOTP_EN;
        Param->enaDHCP = DHCP_EN;
        Param->enaPort1Neg = PORT1_NEG_EN;
        Param->enaPort1Dplx = PORT1_DUPLEX_EN;
        Param->enaPort1Speed = PORT1_SPEED_EN;
        Param->enaPort2OwnSet = PORT2_OWN_SETTINGS;
        Param->enaPort2Neg = PORT2_NEG_EN;
        Param->enaPort2Dplx = PORT2_DUPLEX_EN;
        Param->enaPort2Speed = PORT2_SPEED_EN;
        Param->inAssFlg3 = INPUTASSFLAGS_3;
        Param->inAssFlg6 = INPUTASSFLAGS_6;
        Param->inAssFlg7 = INPUTASSFLAGS_7;
        Param->outAssFlg3 = OUTPUTASSFLAGS_3;
        Param->outAssFlg6 = OUTPUTASSFLAGS_6;
        Param->outAssFlg7 = OUTPUTASSFLAGS_7;
        Param->QoSFlg = QOSFLAGS;
        Param->enaTag802 = TAG802_EN;
        Param->urgentDSCP = DSCP_URGENT;
        Param->scheduleDSCP = DSCP_SCHEDULED;
        Param->highDSCP = DSCP_HIGH;
        Param->lowDSCP = DSCP_LOW;
        Param->explicitDSCP = DSCP_EXPLICIT;
        Param->qckCon = QUICKCONNECTFLAGS;
        mxGetString(pDEVICENAME, Param->DevName, mxGetN(pDEVICENAME) + 1);
        mxGetString(DOMAINNAME, Param->Domain, mxGetN(DOMAINNAME) + 1);
        mxGetString(HOSTNAME, Param->Hostname, mxGetN(HOSTNAME) + 1);
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
