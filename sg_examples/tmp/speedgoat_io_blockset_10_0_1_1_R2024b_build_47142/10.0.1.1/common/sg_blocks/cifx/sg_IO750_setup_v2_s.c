#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO750_setup_v2_s

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
#include "ECS_api.h"
#endif
#include "sg_callback.h"

/* Defines */
#define MOD_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[0]
#define NODE_ID_ARG (uint32_T) mxGetPr(ssGetSFcnParam(S, 0))[1]
// 1
// 2
#define BUS_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 3))[0]
#define SLOT_ARG (int16_T) mxGetPr(ssGetSFcnParam(S, 3))[1]
#define VENDOR_ID (uint32_T) mxGetPr(ssGetSFcnParam(S, 4))[0]
#define PRODUCTCODE (uint32_T) mxGetPr(ssGetSFcnParam(S, 5))[0]
#define REVISION_NO (uint32_T) mxGetPr(ssGetSFcnParam(S, 6))[0]
#define SERIAL_NO (uint32_T) mxGetPr(ssGetSFcnParam(S, 7))[0]
#define BUS_STARTUP (uint8_T) mxGetPr(ssGetSFcnParam(S, 11))[0]
#define DC_SYNC (uint8_T) mxGetPr(ssGetSFcnParam(S, 12))[0]
#define PDO_CFG (ssGetSFcnParam(S, 13))
#define PDO_NAME (ssGetSFcnParam(S, 14))
#define AO_NAME (ssGetSFcnParam(S, 15))
#define TX_PDO_OFFSET (uint32_T) mxGetPr(ssGetSFcnParam(S, 16))[0]
// 17
// 18
#define SDO_CFG ssGetSFcnParam(S, 19)
#define SDO_NAME (ssGetSFcnParam(S, 20))
#define STATION_ALIAS (uint16_T) mxGetPr(ssGetSFcnParam(S, 21))[0]
#define DEVICE_IDENT (uint16_T) mxGetPr(ssGetSFcnParam(S, 22))[0]
#define RX_SYNC_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 23))[0]
#define TX_SYNC_ARG (uint8_T) mxGetPr(ssGetSFcnParam(S, 24))[0]
#define NUMBER_OF_ARGS 25

#define PDO_ID(i) ((uint32_T)(mxGetPr(PDO_CFG)[i + 0 * (int_T)mxGetM(PDO_CFG)]))
#define PDO_DT(i) ((uint8_T)(mxGetPr(PDO_CFG)[i + 1 * (int_T)mxGetM(PDO_CFG)]))
#define PDO_BITLEN(i) ((uint8_T)(mxGetPr(PDO_CFG)[i + 2 * (int_T)mxGetM(PDO_CFG)]))
#define PDO_PAD(i) ((boolean_T)(mxGetPr(PDO_CFG)[i + 3 * (int_T)mxGetM(PDO_CFG)]))
#define PDO_ECAT_DT(i) ((uint8_T)(mxGetPr(PDO_CFG)[i + 6 * (int_T)mxGetM(PDO_CFG)]))

#define SDO_INDEX(i) ((uint16_T)(mxGetPr(SDO_CFG)[i + 0 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_SUBINDEX(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 1 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_DT(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 2 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_INIVAL(i) ((real64_T)(mxGetPr(SDO_CFG)[i + 3 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_ACCESSRIGHTS(i) ((uint16_T)(mxGetPr(SDO_CFG)[i + 4 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_ACCESSMODE(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 5 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_BYTELEN(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 6 * (int_T)mxGetM(SDO_CFG)]))
#define SDO_NUMELEMENTS(i) ((uint8_T)(mxGetPr(SDO_CFG)[i + 7 * (int_T)mxGetM(SDO_CFG)]))

/* Definitions */
static char_T ErrMsg[1024];

int32_T GetCsvString(char *src, char *dest, uint32_T len)
{
    unsigned int i = 0, n = 0;

    if (strlen(src) <= 0)
    {
        return -1;
    }

    if (src[0] != ',')
    {
        return -1;
    }

    for (i = 1; i < strlen(src); i++)
    {
        if ((src[i] == '\0') || (src[i] == ','))
        {
            return n;
        }
        else
        {
            dest[n] = src[i];
            n++;
        }
    }

    return n;
}

static void mdlInitializeSizes(SimStruct *S)
{
    int_T i = 0;

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
    if (NODE_ID_ARG > 0)
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO750-32");
    }
    else
    {
        snprintf(ModuleName, sizeof(ModuleName), "IO750");
    }

    if (0 != Cifx_AddModule(MOD_ID_ARG, BUS_ARG, SLOT_ARG, &Module))
    {
        sprintf(ErrMsg, "%s, ID %s: %s", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }
    if (0 != Cifx_AddNode(NODE_ID_ARG, Module, &Node))
    {
        sprintf(ErrMsg, "%s, ID %s: %s", ModuleName, ModuleIdStr, CifxMsg);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

    if (0 != Cifx_AddChannel(sizeof(ECS_PARAM_T), Node, &Channel))
    {
        sprintf(ErrMsg, "%s, ID %s: %s", ModuleName, ModuleIdStr, CifxMsg);
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
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "sgn52ecs.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "4.8.0.0");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "sgnetX52.bin");
        snprintf(Node->FpgaFileName, sizeof(Node->FpgaFileName), "IO75X-32.bin");
        snprintf(Node->FpgaVersionName, sizeof(Node->FpgaVersionName), "IO75X-32.inf");
    }
    else
    {
        Module->Type = CIFX_MODULE_TYPE_GEN;
        Node->IrqEnabled = true;
        Node->DmaEnabled = true;
        snprintf(Node->FwFileName, sizeof(Node->FwFileName), "cifxecs2.nxf");
        snprintf(Node->FwVersionStr, sizeof(Node->FwVersionStr), "4.9.0.2");
        snprintf(Node->BtldName, sizeof(Node->BtldName), "NETX100.bin");
    }
    Node->BlockVersion = 2;
    Node->IsReInit = !sg_isFirstModelLoad();
    snprintf(Node->FwName, sizeof(Node->FwName), "EtherCAT Slave");
    snprintf(Node->ModuleIdStr, sizeof(Node->ModuleIdStr), ModuleIdStr);

    /* Set channel parameters */
    Channel->BusStartupMode = BUS_STARTUP;
    snprintf(Channel->ProtocolStr, sizeof(Channel->ProtocolStr), "ETHERCAT");
    snprintf(Channel->StationTypeStr, sizeof(Channel->StationTypeStr), "Slave");
    Channel->StationType = CIFX_STATION_TYPE_S;
    Channel->ProtocolType = CIFX_PROTOCOL_ETHERCAT;
    Channel->CfgMode = CIFX_CFG_MODE_WARM;
    Channel->NumCfgFiles = 0;

    /* Set warmstart parameters */
    {
        uint32_T i = 0;
        uint32_T PreviousPdoId = 0;
        char_T *PdoNames = NULL;
        char_T *AoNames = NULL;
        char_T *SdoNames = NULL;
        char_T *pToNextPdo = NULL;
        char_T *pToNextAo = NULL;
        char_T *pToNextSdo = NULL;
        ECS_PARAM_T *Param = (ECS_PARAM_T *)(Channel->Param);

        Param->VendorID = VENDOR_ID;
        Param->ProdCode = PRODUCTCODE;
        Param->RevisionNo = REVISION_NO;
        Param->SerialNo = SERIAL_NO;
        Param->StationAlias = STATION_ALIAS;
        Param->DeviceIdent = DEVICE_IDENT;
        Param->DcSyncMode = DC_SYNC;
        Param->RxSync = RX_SYNC_ARG;
        Param->TxSync = TX_SYNC_ARG;
        Param->NumSdo = (uint32_T)mxGetM(SDO_CFG);

        /* Read application object names, process data object names
         * and service data object names from S-function parameter */
        if (mxGetN(PDO_NAME) > 0)
        {
            PdoNames = malloc(mxGetN(PDO_NAME) + 1);
            if (PdoNames == NULL)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Out of memory");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }

            if (mxGetString(PDO_NAME, PdoNames, 1 + mxGetN(PDO_NAME)) != 0)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Unable to read block parameter");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (mxGetN(AO_NAME) > 0)
        {
            AoNames = malloc(mxGetN(AO_NAME) + 1);
            if (AoNames == NULL)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Out of memory");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }

            if (mxGetString(AO_NAME, AoNames, 1 + mxGetN(AO_NAME)) != 0)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Unable to read block parameter");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        if (mxGetN(SDO_NAME) > 0)
        {
            SdoNames = malloc(mxGetN(SDO_NAME) + 1);
            if (SdoNames == NULL)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Out of memory");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }

            if (mxGetString(SDO_NAME, SdoNames, 1 + mxGetN(SDO_NAME)) != 0)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Unable to read block parameter");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
        }

        pToNextPdo = PdoNames;
        pToNextAo = AoNames;

        /* Step through the PDO configuration parameter and create process data and application objects */
        for (i = 0; i < (int_T)mxGetM(PDO_CFG); i++)
        {
            int_T n = 0;
            uint32_T PdoId = PDO_ID(i);

            static ECS_PDO_AREA_T *Area = NULL;
            static ECS_PDO_T *Pdo = NULL;
            ECS_AO_T *Ao = NULL;

            /* Check whether to add a PDO */
            if ((i == 0) || (PreviousPdoId != PdoId) || (i == TX_PDO_OFFSET))
            {
                /* Select either RX PDO or TX PDO area */
                Area = &(Param->PdoArea[(i >= TX_PDO_OFFSET) ? ECS_PDO_TX : ECS_PDO_RX]);

                /* Add a PDO */
                if (0 != ECS_AddPdo(Area, &Pdo))
                {
                    sprintf(ErrMsg, "%s, ID %s: %s", ModuleName, ModuleIdStr, CifxMsg);
                    ssSetErrorStatus(S, ErrMsg);
                    return;
                }

                PreviousPdoId = PdoId;
            }

            /* Add an AO */
            if (0 != ECS_AddAo(Pdo, &Ao))
            {
                sprintf(ErrMsg, "%s, ID %s: %s", ModuleName, ModuleIdStr, CifxMsg);
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
            Ao->Dtype = PDO_DT(i);
            Ao->EcatDtype = PDO_ECAT_DT(i);
            Ao->BitLen = PDO_BITLEN(i);
            Ao->Padding = PDO_PAD(i);

            /* Count bits for the whole PDO area */
            Area->BitLen += Ao->BitLen;

            n = GetCsvString(pToNextPdo, Pdo->Name, sizeof(Pdo->Name) - 1);
            if (n < 0)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Error while reading block parameter");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
            else
            {
                pToNextPdo = pToNextPdo + 1 + n;
            }

            n = GetCsvString(pToNextAo, Ao->Name, sizeof(Ao->Name) - 1);
            if (n < 0)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Error while reading block parameter");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
            else
            {
                pToNextAo = pToNextAo + 1 + n;
            }
        }

        pToNextSdo = SdoNames;

        for (i = 0; i < (int_T)mxGetM(SDO_CFG); i++)
        {
            int_T n = 0;

            Param->Sdo[i].Index = SDO_INDEX(i);
            Param->Sdo[i].SubIndex = SDO_SUBINDEX(i);
            Param->Sdo[i].AccessRights = SDO_ACCESSRIGHTS(i);
            Param->Sdo[i].DataType = SDO_DT(i);
            Param->Sdo[i].InitValue = SDO_INIVAL(i);
            Param->Sdo[i].AccessMode = SDO_ACCESSMODE(i);
            Param->Sdo[i].ByteLen = SDO_BYTELEN(i);
            Param->Sdo[i].NumElements = SDO_NUMELEMENTS(i);

            n = GetCsvString(pToNextSdo, Param->Sdo[i].Name, sizeof(Param->Sdo[i].Name) - 1);
            if (n < 0)
            {
                sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, "Error while reading block parameter");
                ssSetErrorStatus(S, ErrMsg);
                return;
            }
            else
            {
                pToNextSdo = pToNextSdo + 1 + n;
            }

            Param->Sdo[i].AcyclicLot = Channel->NumAcyclicParticipants;
            Channel->NumAcyclicParticipants++;
        }

        /* Free memory of object names */
        if (PdoNames != NULL)
        {
            free(PdoNames);
        }
        if (AoNames != NULL)
        {
            free(AoNames);
        }
        if (SdoNames != NULL)
        {
            free(SdoNames);
        }
    }

    if (0 != Cifx_InitNode(Node))
    {
        sprintf(ErrMsg, "%s, ID %s: %s", Module->Name, ModuleIdStr, CifxMsg);
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
    ECS_Clear(Channel);
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
