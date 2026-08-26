#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO642_setup_v2_s

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
#include "PBS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[1]
// 2
#define BUSSTARTUP (int)mxGetPr(ssGetSFcnParam(S, 3))[0]
#define WATCHDOGTIME (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define IOSTATUS (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define IDENTNUMBER (uint16_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define BUSADDRESS (uint8_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define BAUDRATE (int)mxGetPr(ssGetSFcnParam(S, 8))[0]
#define DPV1ENABLE (int)mxGetPr(ssGetSFcnParam(S, 9))[0]
#define SYNCSUPPORTED (int)mxGetPr(ssGetSFcnParam(S, 10))[0]
#define FREEZESUPPORTED (int)mxGetPr(ssGetSFcnParam(S, 11))[0]
#define FAILSAFESUPPORTED (int)mxGetPr(ssGetSFcnParam(S, 12))[0]
#define ALARMSAP50 (int)mxGetPr(ssGetSFcnParam(S, 13))[0]
#define IODATASWAP (int)mxGetPr(ssGetSFcnParam(S, 14))[0]
#define ADDRESSCHANGE (int)mxGetPr(ssGetSFcnParam(S, 15))[0]
#define ALARM_MODE_NO_SEQ (int)mxGetPr(ssGetSFcnParam(S, 16))[0]
#define IOCONFIG (int)mxGetPr(ssGetSFcnParam(S, 17))[0]
#define IODATA ssGetSFcnParam(S, 18)
#define NUMBER_OF_ARGS (19)

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i;

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
    PBS_PARAM_T *Param = NULL;
    char_T ModuleIdStr[CIFX_DEFAULT_STR_LEN] = {0};
    char_T ModuleName[CIFX_DEFAULT_STR_LEN] = {0};

    /* Assemble the module ID string and module name */
    Cifx_CreateModuleIdStr(MOD_ID_ARG, NODE_ID_ARG, ModuleIdStr, sizeof(ModuleIdStr));
    if (NODE_ID_ARG > 0)
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO642-32");
    }
    else
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO642");
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

    if (0 != Cifx_AddChannel(sizeof(PBS_PARAM_T), Node, &Channel))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    Param = (PBS_PARAM_T *)(Channel->Param);

    /* Set module parameters */
    snprintf(Module->Name, sizeof(Module->Name), ModuleName);

    /* Set node parameters */
    if (NODE_ID_ARG > 0)
    {
        Module->Type = CIFX_MODULE_TYPE_TEWS_PB;
        Node->IrqEnabled = false;
        Node->DmaEnabled = false;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "sgn52dps.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "2.11.1.0");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "sgnetX52.bin");
        snprintf(Node->FpgaFileName, sizeof(Node->FpgaFileName), "IO642-32.bin");
        snprintf(Node->FpgaVersionName, sizeof(Node->FpgaVersionName), "IO642-32.inf");
    }
    else
    {
        Module->Type = CIFX_MODULE_TYPE_GEN;
        Node->IrqEnabled = false;
        Node->DmaEnabled = true;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxdps.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "2.11.1.0");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    }
    Node->BlockVersion = 2;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "PROFIBUS DP Slave");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = BUSSTARTUP;
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "Profibus");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Slave");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_PROFIBUS;
    Channel->CfgMode = CIFX_CFG_MODE_WARM;
    Channel->NumCfgFiles = 0;

    /* Set warmstart parameters */
    Param->IOStat = IOSTATUS;
    Param->WdgTime = WATCHDOGTIME;
    Param->IdentNo = IDENTNUMBER;
    Param->BusAdr = BUSADDRESS;
    Param->CfgLen = (uint8_T)mxGetN(IODATA);
    Param->Res[0] = ALARM_MODE_NO_SEQ; // Alarm sequence mode is enabled by 0
    Param->Res[1] = 0;
    Param->enaDPV1 = DPV1ENABLE;
    Param->IsSyncSup = SYNCSUPPORTED;
    Param->IsFreezeSup = FREEZESUPPORTED;
    Param->IsFailSaveSup = FAILSAFESUPPORTED;
    Param->enaAlarmSAP50Deact = (ALARMSAP50 == 0);
    Param->enaIODataSwap = IODATASWAP;
    Param->enaAutoCfg = IOCONFIG;
    Param->enaAdrCngNotAlwd = (ADDRESSCHANGE == 0);
    Param->Bdr = BAUDRATE;

    for (i = 0; i < Param->CfgLen; i++)
    {
        Param->CfgData[i] = (uint8_T)mxGetPr(IODATA)[i];
    }

    if (0 != Cifx_InitNode(Node))
    {
        sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (Channel->BusStartupMode != BUS_STARTUP_APP)
    {
        /* If "start bus automatically" is selected,
            then the start bit has already been set,
            but we need to do some indication handling ahead of time
            in order to properly respond to the connection requests from the master*/
        if (sg_isFirstModelLoad())
        {
            uint32_T counter = 0;

            /* Register at the stack in order to receive indications about connection requests from master */
            if (0 != Cifx_RegisterApplication(Channel))
            {
                sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }

            /* Handle connection requests and get connected */
            while (counter < 20)
            {
                if (Param->firstConnectionAttempt)
                {
                    break;
                }
                PBS_HandleIndication(Channel);
                counter++;
                sg_wait_s(0.01);
            }

            /* Unsubscribe from the stack.
             * If the remote master reboots while no indication handling is executed on the slave side,
             * the stack will go down */
            if (0 != Cifx_UnRegisterApplication(Channel))
            {
                sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, Node->ModuleIdStr, CifxMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }
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

    Cifx_UnRegisterApplication(Channel);
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
