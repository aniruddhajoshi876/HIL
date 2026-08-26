#ifndef __CIFXAPI_H
#define __CIFXAPI_H

#include "sg_common.h" // bool
#include "stdint.h"

#if defined(_MSC_VER) && _MSC_VER < 1900
#ifndef snprintf
#define snprintf _snprintf
#endif
#endif

#define CIFX_MAX_NUM_MODULES  128
#define CIFX_MAX_NUM_NODES    32
#define CIFX_MAX_NUM_CHANNELS 1
#define CIFX_MAX_NUM_CFGFILES 2

#define CIFX_DPM_IO_DATA_SIZE 5760

#define CIFX_MAX_PATH_LEN    256
#define CIFX_DEFAULT_STR_LEN 32

#define CIFX_MODULE_TYPE_GEN      0x01
#define CIFX_MODULE_TYPE_TEWS     0x10
#define CIFX_MODULE_TYPE_TEWS_ETH 0x11
#define CIFX_MODULE_TYPE_TEWS_PB  0x12

#define CIFX_STATION_TYPE_M 1 // Master
#define CIFX_STATION_TYPE_S 2 // Slave

#define CIFX_PROTOCOL_PROFIBUS   0x01
#define CIFX_PROTOCOL_ETHERCAT   0x11
#define CIFX_PROTOCOL_PROFINET   0x12
#define CIFX_PROTOCOL_MODBUS     0x13
#define CIFX_PROTOCOL_ETHERNETIP 0x14
#define CIFX_PROTOCOL_POWERLINK  0x15
#define CIFX_PROTOCOL_CANOPEN    0x16

#define CIFX_CFG_MODE_FILE 1
#define CIFX_CFG_MODE_WARM 2

#define BUS_STARTUP_AUTO 1
#define BUS_STARTUP_APP  2

#define CIFX_MAX_ERR_LEN 512

/* MAC address length */
#define CIFX_MAC_ADR_LEN 6

extern char CifxMsg[256];

/*
 *   Enumeration for all available status of the acyclic communication.
 */
typedef enum t_CIFX_ACY_STATE {
    AcsNotUsed = 0,     /**< Process is not used, not active */
    AcsGetFbSpecData,   /**< Get fieldbus specific data. */
    AcsRdyToOp,         /**< Process is ready to operate, configuration is finished. */
    AcsAwaitPkt,        /**< Process is awaiting a response message */
    AcsAddObjToObjDict, /**< Process is in the configuration status */
    AcsAwaitObjDictPkt, /**< Process is awaiting a response message from the object dictionary
                           (EtherCAT, POWERLINK) */
    AcsAddObjToDict,    /**< Process is adding acyclic objects to the object dictionary (EtherCAT,
                           POWERLINK) */
    AcsModbusProcessIndication // A Modbus TCP indication was received and is no processed.

} CIFX_ACY_STATE;

/*
 *   Structure for the general PCI data.
 */
typedef struct t_CIFX_PCI {
    uint8_t HdrType;              // Header type of the PCI module
    uint8_t IntLn;                // Interrupt line
    int16_t Bus;                  // Bus number of the PCI module
    int16_t Slot;                 // Slot number of the PCI module
    int16_t Fcn;                  // Function code for the PCI module
    uint16_t DevID;               // Device ID
    uint16_t SubDevID;            // Sub device ID of the PCI device.
    uint16_t VenID;               // Vendor ID of the PCI devcie.
    uint16_t SubVenID;            // Sub vendor ID of the PCI device.
    uint32_t sizeBAR0;            // Length of the DPM start of the corresponding sub-module
    uint32_t sizeBAR2;            // Length of the CONFIG space of the corresponding sub-module
    volatile uint32_t PhyAdrBAR0; // Physical address of the BAR0
    volatile uint32_t PhyAdrBAR2; // Physical address of the BAR2

    sg_PCIDevice pPciInfo;

} CIFX_PCI_T;

typedef struct t_cfgfile {
    char Name[CIFX_DEFAULT_STR_LEN];
    char Path[CIFX_MAX_PATH_LEN];

} CIFX_CFGFILE_T;

typedef struct t_cifxchannel {
    bool IsInit;
    uint8_t BusStartupMode;
    char ProtocolStr[128];
    char StationTypeStr[CIFX_DEFAULT_STR_LEN]; // Master, Slave
    uint8_t StationType;
    uint8_t ProtocolType;
    uint8_t NumCfgFiles;
    uint8_t CfgMode; // File, Warmstart
    uint32_t CntPdoIn;
    bool IndicationHandlingEnabled; // Status flag if the acyclic option 'Register Application' is
                                    // done. Default = false
    void (*AcyclicHandler)(void *);
    CIFX_ACY_STATE AcyState; // Status of the acyclic communication.
    uint32_t AcyclicBaton;
    uint32_t NumAcyclicParticipants;

    CIFX_CFGFILE_T CfgFiles[CIFX_MAX_NUM_CFGFILES];

    void *Param;  // Protocol specific parameter
    void *Custom; // Protocol specific data extensions
    void *Node;

    void *DpmChannel;

    uint8_t RxData[5760];
    uint8_t TxData[5760];
    uint32_t RxLen;
    uint32_t TxLen;
    uint32_t RxHostFlags;
    uint32_t RxDevFlags;
    uint32_t TxHostFlags;
    uint32_t TxDevFlags;

} CIFX_CHANNEL_T;

typedef struct t_cifxnode {
    bool IsInit;
    bool IsReInit;
    bool IrqEnabled;
    bool DmaEnabled;
    bool IrqGo;
    uint8_t BlockVersion;
    uint8_t FirstNode;
    uint32_t ID;
    uint32_t Idx;
    uint8_t NumChannels;
    uint32_t SN;
    uint8_t IrqEventMask;
    uint32_t CntIntr;

    char Drive[CIFX_DEFAULT_STR_LEN];
    char ModuleIdStr[CIFX_DEFAULT_STR_LEN];

    char FwFileName[CIFX_DEFAULT_STR_LEN];
    char FwPath[CIFX_MAX_PATH_LEN];
    uint8_t FwVersion[4];
    char FwVersionStr[CIFX_DEFAULT_STR_LEN];
    char FwName[CIFX_MAX_PATH_LEN];

    char BtldName[CIFX_DEFAULT_STR_LEN];
    char BtldPath[CIFX_MAX_PATH_LEN];

    char FpgaFileName[CIFX_DEFAULT_STR_LEN];
    char FpgaFilePath[CIFX_MAX_PATH_LEN];

    char FpgaVersionName[CIFX_DEFAULT_STR_LEN];
    char FpgaVersionPath[CIFX_MAX_PATH_LEN];

    uint8_t MAC[CIFX_MAC_ADR_LEN]; // MAC addres of the sub-module

    CIFX_CHANNEL_T *Channels[CIFX_MAX_NUM_CHANNELS];
    void *Module;
    void *DpmDevice;
    void *DMA;
    uintptr_t PhysicalDMA;

} CIFX_NODE_T;

typedef struct t_cifxmodule {
    // bool IsFPGAUpd;				// Status flag if an update on the FPGA was
    // performed bool IsInitDone;              // Status flag if module init is done bool IrqEnable;
    // // Module has been configured to be an interrupt source uint32_t ID;                    // ID
    // of the module uint32_t Idx;                   // Index of the module uint32_t QtySubMods; //
    // Quantity of sub-modules uint32_t SN;                    // SG Serial number of the TEWS PCI
    // device uint32_t HelpTempTimeVal; Cifx_PCIDevType Type;           // Type of the PCI card
    // (Hilscher or TEWS) Cifx_PCIObj PCI;                // PCI data of the module Cifx_SubModObj
    // *pSubMods;       // Pointer to the sub-module array Cifx_TEWSAsmBAR2 TEWSAcsBAR2;    //
    // Configuration area of the TEWS card, mapped to BAR2 of the PCI module

    uint32_t irqcnt;
    uint64_t tick;
    uint64_t oldtick;
    uint64_t tickdiff[10000];

    uint32_t ID;
    uint32_t Idx;
    uint32_t NumNodes;
    uint32_t Baton;
    int16_t PciBus;
    int16_t PciSlot;
    uint32_t SN;
    uint8_t Type;
    bool IrqEnabled;
    char Name[CIFX_DEFAULT_STR_LEN];
    bool IsInit;
    // Cifx_PCIObj PCI;
    CIFX_NODE_T *Nodes[CIFX_MAX_NUM_NODES];
    CIFX_PCI_T PCI;
    void *Registers; // Cifx_TEWSAsmBAR2
    void *Bar0;

    void *CifxThread;

} CIFX_MODULE_T;

#ifdef __cplusplus
extern "C" {
#endif

int Cifx_IntrPreFcn(uint32_t BaseAddress, uint16_t InterruptLine);
void Cifx_IntrStartFcn(uint32_t BaseAddress, uint16_t InterruptLine);
void Cifx_IntrStopFcn(uint32_t BaseAddress, uint16_t InterruptLine);
void Cifx_CreateModuleIdStr(uint32_t ModuleID, uint32_t NodeID, char *s, int len);
int32_t Cifx_AddModule(uint32_t ModuleId, int16_t PciBus, int16_t PciSlot, CIFX_MODULE_T **Module);
int32_t Cifx_AddNode(uint32_t NodeId, CIFX_MODULE_T *Module, CIFX_NODE_T **Node);
int32_t Cifx_AddChannel(uint32_t ParamLen, CIFX_NODE_T *Node, CIFX_CHANNEL_T **Channel);
int32_t Cifx_InitNode(CIFX_NODE_T *Node);
int32_t Cifx_FindNode(uint32_t ModuleID, uint8_t NodeID, CIFX_NODE_T **Node);
int32_t Cifx_StartCom(CIFX_CHANNEL_T *Channel, uint32_t Timeout);
int32_t Cifx_StopCom(CIFX_CHANNEL_T *Channel, uint32_t Timeout);
int32_t Cifx_RecDataExt(CIFX_CHANNEL_T *Channel, uint32_t dataLen, void *pData);
bool Cifx_SndDataExt(CIFX_CHANNEL_T *Channel, uint32_t dataLen, void *pData);
int32_t Cifx_RegisterApplication(CIFX_CHANNEL_T *Channel);
int32_t Cifx_UnRegisterApplication(CIFX_CHANNEL_T *Channel);
int32_t Cifx_GetFPGATemp(CIFX_MODULE_T *Module, uint8_t *pPort);
int32_t Cifx_GetBoardTemp(CIFX_MODULE_T *Module, uint8_t *pPort);
int32_t Cifx_SetNWStat(CIFX_CHANNEL_T *Channel, uint32_t *b);
int32_t Cifx_GetNWStat(CIFX_CHANNEL_T *Channel, uint32_t *b);
int32_t Cifx_FreeChannel(CIFX_CHANNEL_T *Channel);
int32_t Cifx_CheckChannel(CIFX_CHANNEL_T *Channel);
int32_t Cifx_RegisterApplicationDontWait(CIFX_CHANNEL_T *Channel);
int32_t Cifx_ConditionalStartCom(CIFX_CHANNEL_T *Channel);
int32_t Cifx_ConditionalStopCom(CIFX_CHANNEL_T *Channel);
void Cifx_StartBackground(void);
void Cifx_StopBackground(void);
int32_t Cifx_GetRxData(CIFX_CHANNEL_T *Channel, uint32_t DataLen, void *Data);
int32_t Cifx_SetTxData(CIFX_CHANNEL_T *Channel, uint32_t DataLen, void *Data);
int32_t Cifx_ProcessRxData(CIFX_CHANNEL_T *Channel);
int32_t Cifx_ProcessTxData(CIFX_CHANNEL_T *Channel);
int32_t Cifx_ProcessIoData(CIFX_CHANNEL_T *Channel);


#ifdef __cplusplus
}
#endif

#endif