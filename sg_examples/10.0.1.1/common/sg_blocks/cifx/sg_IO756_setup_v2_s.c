#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO756_setup_v2_s

/* Includes */
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#define SG_EARLY_INIT
#define SG_HAS_MDL_EXIT

#ifndef MATLAB_MEX_FILE
#include "EIS_api.h"
#include "cifx_common.h"
#include "cifxapi.h"
#include "sg_common.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG   (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG     (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
#define PCI_BUS_ARG     (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[0]
#define PCI_SLOT_ARG    (int16_T) mxGetPr(ssGetSFcnParam(S, 1))[1]
#define CONFIG_MODE_ARG ((uint8_T)mxGetPr(ssGetSFcnParam(S, 2))[0] - 1)
// 3 unused

#define IP_ADDRESS_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define NETMASK_ARG    (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define GATEWAY_ARG    (uint32_T) mxGetPr(ssGetSFcnParam(S, 6))[0]

#define VENDOR_ID_ARG    (uint16_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define PRODUCT_TYPE_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 8))[0]
#define PRODUCT_CODE_ARG (uint16_T) mxGetPr(ssGetSFcnParam(S, 9))[0]
#define MAJOR_REV_ARG    (uint8_T) mxGetPr(ssGetSFcnParam(S, 10))[0]
#define MINOR_REV_ARG    (uint8_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define DEVICE_NAME_ARG  ssGetSFcnParam(S, 12)

#define INPUT_ID_ARG     (uint32_T) mxGetPr(ssGetSFcnParam(S, 13))[0]
#define INPUT_LEN_ARG    (uint32_T) mxGetPr(ssGetSFcnParam(S, 14))[0]
#define INPUT_FORMAT_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 15))[0]

#define OUTPUT_ID_ARG     (uint32_T) mxGetPr(ssGetSFcnParam(S, 16))[0]
#define OUTPUT_LEN_ARG    (uint32_T) mxGetPr(ssGetSFcnParam(S, 17))[0]
#define OUTPUT_FORMAT_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 18))[0]

#define ASSEMBLIES_ARG  ssGetSFcnParam(S, 19)
#define CONNECTIONS_ARG ssGetSFcnParam(S, 20)

#define NUMBER_OF_ARGS (21)

/* Convenient access to m x n matrices which are stored as vectors */
#define ASSEMBLY_ID_ARG(i) (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 0 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_LEN_ARG(i)                                                                        \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 1 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_OFFSET_ARG(i)                                                                     \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 2 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_TYPE_ARG(i)                                                                       \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 3 * (int_T)mxGetM(ASSEMBLIES_ARG)]
#define ASSEMBLY_FORMAT_ARG(i)                                                                     \
    (uint32_T) mxGetPr(ASSEMBLIES_ARG)[i + 4 * (int_T)mxGetM(ASSEMBLIES_ARG)]

#define CONNECTION_INPUT_ID_ARG(i)                                                                 \
    (uint32_T) mxGetPr(CONNECTIONS_ARG)[i + 0 * (int_T)mxGetM(CONNECTIONS_ARG)]
#define CONNECTION_OUTPUT_ID_ARG(i)                                                                \
    (uint32_T) mxGetPr(CONNECTIONS_ARG)[i + 1 * (int_T)mxGetM(CONNECTIONS_ARG)]
#define CONNECTION_CONFIG_ID_ARG(i)                                                                \
    (uint32_T) mxGetPr(CONNECTIONS_ARG)[i + 2 * (int_T)mxGetM(CONNECTIONS_ARG)]
#define CONNECTION_TYPE_ARG(i)                                                                     \
    (uint8_T) mxGetPr(CONNECTIONS_ARG)[i + 3 * (int_T)mxGetM(CONNECTIONS_ARG)]

#define NUM_ASSEMBLIES  (int_T) mxGetM(ASSEMBLIES_ARG)
#define NUM_CONNECTIONS (int_T) mxGetM(CONNECTIONS_ARG)

/* Definitions */
static char_T ErrMsg[1024];

static void mdlInitializeSizes(SimStruct *S)
{
    uint32_T i;

    /* Parameters */
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        sprintf(ErrMsg, "Wrong number of input arguments passed.\n%d arguments are expected\n",
                NUMBER_OF_ARGS);

        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    for (i = 0; i < NUMBER_OF_ARGS; i++) {
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
    EIS_PARAM_2_T *Param = NULL;
    char_T ModuleIdStr[CIFX_DEFAULT_STR_LEN] = {0};
    char_T ModuleName[CIFX_DEFAULT_STR_LEN] = {0};
    uint32_T i = 0;

    /* Assemble the module ID string and module name */
    Cifx_CreateModuleIdStr(MOD_ID_ARG, NODE_ID_ARG, ModuleIdStr, sizeof(ModuleIdStr));
    if (NODE_ID_ARG > 0) {
        snprintf(ModuleName, sizeof(ModuleName), "IO756-32");
    } else {
        snprintf(ModuleName, sizeof(ModuleName), "IO756");
    }

    if (0 != Cifx_AddModule(MOD_ID_ARG, PCI_BUS_ARG, PCI_SLOT_ARG, &Module)) {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
    if (0 != Cifx_AddNode(NODE_ID_ARG, Module, &Node)) {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (0 != Cifx_AddChannel(sizeof(EIS_PARAM_2_T), Node, &Channel)) {
        sprintf(ErrMsg, "%s, ID %s: %s!", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    Param = (EIS_PARAM_2_T *)(Channel->Param);

    /* Set module parameters */
    snprintf(Module->Name, sizeof(Module->Name), ModuleName);

    /* Set node parameters */
    if (NODE_ID_ARG > 0) {
        Module->Type = CIFX_MODULE_TYPE_TEWS_ETH;
        Node->IrqEnabled = false;
        Node->DmaEnabled = false;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "nx52eis2.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "3.8.0.7");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "sgnetX52.bin");
        snprintf(Node->FpgaFileName, sizeof(Node->FpgaFileName), "IO75X-32.bin");
        snprintf(Node->FpgaVersionName, sizeof(Node->FpgaVersionName), "IO75X-32.inf");
    } else {
        Module->Type = CIFX_MODULE_TYPE_GEN;
        Node->IrqEnabled = false;
        Node->DmaEnabled = true;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxeis2.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "3.8.0.7");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    }

    Node->BlockVersion = 2;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "EtherNet/IP Adapter");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = BUS_STARTUP_APP;
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "EthernetIP");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Adapter");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_ETHERNETIP;
    Channel->CfgMode = CIFX_CFG_MODE_WARM;

    /* Set parameters */
    Param->ConfigMode = CONFIG_MODE_ARG;
    Param->IpAddress = IP_ADDRESS_ARG;
    Param->Netmask = NETMASK_ARG;
    Param->Gateway = GATEWAY_ARG;
    Param->VendorID = VENDOR_ID_ARG;
    Param->ProductType = PRODUCT_TYPE_ARG;
    Param->ProductCode = PRODUCT_CODE_ARG;
    Param->MinorRev = MINOR_REV_ARG;
    Param->MajorRev = MAJOR_REV_ARG;
    mxGetString(DEVICE_NAME_ARG, Param->DeviceName, mxGetN(DEVICE_NAME_ARG) + 1);

    if (CONFIG_MODE_ARG == EIS_CONFIG_MODE_SIMPLE) {

        /* Simple configuration mode */

        Param->InputAssemblyID = INPUT_ID_ARG;
        Param->InputAssemblyLen = INPUT_LEN_ARG;
        Param->InputAssemblyFormat = INPUT_FORMAT_ARG;

        Param->OutputAssemblyID = OUTPUT_ID_ARG;
        Param->OutputAssemblyLen = OUTPUT_LEN_ARG;
        Param->OutputAssemblyFormat = OUTPUT_FORMAT_ARG;

    } else {

        /* Extended configuration mode */

        Param->NumAssemblies = NUM_ASSEMBLIES;
        Param->NumConnections = NUM_CONNECTIONS;

        /* For each assembly */
        for (i = 0; i < NUM_ASSEMBLIES; i++) {

            Param->Assemblies[i].ID = ASSEMBLY_ID_ARG(i);
            Param->Assemblies[i].Length = ASSEMBLY_LEN_ARG(i);
            Param->Assemblies[i].Offset = ASSEMBLY_OFFSET_ARG(i);
            Param->Assemblies[i].Format = ASSEMBLY_FORMAT_ARG(i);
            Param->Assemblies[i].Type = ASSEMBLY_TYPE_ARG(i);
            if (Param->Assemblies[i].Type == EIS_ASSEMBLY_TYPE_CONFIG) {
                if (Param->Assemblies[i].Length > 0) {
                    Param->Assemblies[i].Data = malloc(Param->Assemblies[i].Length);
                    if (Param->Assemblies[i].Data == NULL) {
                        sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, ModuleIdStr,
                                "Out of memory\n");
                        ssSetErrorStatus(S, ErrMsg);
                        return;
                    }
                    memset(Param->Assemblies[i].Data, 0, Param->Assemblies[i].Length);
                }
            }
        }

        /* For each connection */
        for (i = 0; i < NUM_CONNECTIONS; i++) {

            Param->Connections[i].InputID = CONNECTION_INPUT_ID_ARG(i);
            Param->Connections[i].OutputID = CONNECTION_OUTPUT_ID_ARG(i);
            Param->Connections[i].ConfigID = CONNECTION_CONFIG_ID_ARG(i);
            Param->Connections[i].Type = CONNECTION_TYPE_ARG(i);
        }
    }

    /* Initialize background structures and configure the I/O module */
    if (0 != Cifx_InitNode(Node)) {
        sprintf(ErrMsg, "%s, ID %s: %s!", Module->Name, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
}

static void sg_ModelStart(SimStruct *S)
{
    CIFX_NODE_T *Node = NULL;
    CIFX_CHANNEL_T *Channel = NULL;
    EIS_PARAM_2_T *Param = NULL;

    if (0 != Cifx_FindNode(MOD_ID_ARG, NODE_ID_ARG, &Node)) {
        ssSetErrorStatus(S, "Cannot attach to Speedgaot IO module");
        return;
    }

    Channel = Node->Channels[0];
    Param = (EIS_PARAM_2_T *)(Channel->Param);

    /* Start network communication */
    if (Param->ConfigMode == EIS_CONFIG_MODE_SIMPLE) {
        Cifx_ConditionalStartCom(Channel);
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
