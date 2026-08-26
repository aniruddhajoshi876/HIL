#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO644_setup_s

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
#include "COS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[1]
#define BUS_START_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 2))[0]
#define CO_NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define NUMBER_OF_ARGS 4

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
    char_T ModuleIdStr[CIFX_DEFAULT_STR_LEN] = {0};
    char_T ModuleName[CIFX_DEFAULT_STR_LEN] = {0};

    /* Assemble the module ID string and module name */
    Cifx_CreateModuleIdStr(MOD_ID_ARG, NODE_ID_ARG, ModuleIdStr, sizeof(ModuleIdStr));
    snprintf(ModuleName, sizeof(ModuleName), "IO644");

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

    if (0 != Cifx_AddChannel(sizeof(COS_PARAM_T), Node, &Channel))
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
    snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxcos.nxf");
    snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "3.7.0.2");
    snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    Node->BlockVersion = 1;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "CANopen Slave");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = BUS_START_ARG;
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "CANopen");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Slave");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_CANOPEN;
    Channel->CfgMode = CIFX_CFG_MODE_WARM;
    Channel->NumCfgFiles = 0;

    /* Set warmstart parameters */
    {
        COS_PARAM_T *Param = (COS_PARAM_T *)(Channel->Param);

        Param->CoNodeId = CO_NODE_ID_ARG;
    }

    /* Initialize hardware */
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