/*
*   See    : Corresponding C-File: sg_IO601_fcn.c
*   Version: $Revison$
*   Author : $Author$
*   Date   : $Date$
*/

#ifndef __SG_IO601_FCN_H__
#define __SG_IO601_FCN_H__

#pragma region Include - Standard Header Files

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma endregion

#pragma region Inlcude - Simulink Header Files

#include "rtwtypes.h"
#include "sg_common.h"

#pragma endregion

#pragma region Include - Driver Header Files

#include "sg_IO601_datatypes.h"


#pragma endregion


#pragma region Define - General Driver Values

#define DEVNAME "Speedgoat IO601"
#define QUANTITY_IO_MODULES 10      // Max quantity of I/O modules.
#define VERSION_LENGTH 7            // Number of characters of the module version.
#define TIMEOUT_FOR_SEND_PACKET 100 // Timeout in ms after the communication will be aborted.
#define BLK_BUF_SZ 2                // Size of the block buffer for CAN and LIN read and write blocks

#pragma endregion

#pragma region Define - PCI-Device Values

#define VENDORID               (0x10b5)
#define DEVICEID               (0x9030)
#define SUBVENDORID            (0x10b5)
#define SUBDEVICEID            (0x2977)

#pragma endregion

#pragma region Define - DPRAM Command Codes

/* Command 0x5, 0x9 0xA are not supported since firmware V4.03 */
#define BLOCKING_CMD                (0)
#define NON_BLOCKING_CMD            (1)
#define CMD_ID                      (0x1)
#define CMD_VERSION                 (0x2)
#define CMD_TEST                    (0x3)
#define CMD_INIT_CAN                (0x4)
#define CMD_START_CAN               (0x6)
#define CMD_STOP_CAN                (0x7)
#define CMD_RESET_CAN               (0x8)
#define CMD_CONFIG_RX_QUEUE         (0x0B)
#define CMD_GET_BOARD_INFO          (0xC)
#define CMD_START_TIMER             (0xD)
#define CMD_STOP_TIMER              (0xE)
#define CMD_SET_ACC_MASK            (0xF)
#define CMD_GET_LIN_STAT            (0x29)
#define CMD_START_LIN               (0x2A)
#define CMD_STOP_LIN                (0x2B)
#define CMD_RESET_LIN               (0x2C)
#define CMD_INIT_LIN                (0x2D)
#define CMD_UPDATE_RES_BUFFER_LIN   (0x2E)

#pragma endregion

#pragma region Define - General IXXAT Values

#define BCI_POLL_MODE (0x0)
#define BCI_LATENCY_MODE (0x1)
#define BCI_THROUGHPUT_MODE (0x2)
#define LIN_k_CLASSIC (0)                       // calculate classic checksum for LIN 1.3 and earlier
#define LIN_k_ENHANCED (1)                      // calculate enhanced checksum for LIN 2.0 and newer (except for id 60 and 61)
#define FIFO_READ (0)
#define FIFO_WRITE (1)
#define OFFSET_SEMAPHORES_START_ADDRESS 0x2000  // Address offset for the semaphores area with the DPRAM start address as base address.
#define OFFSET_CAN_STATUS_BUFFER 0xFF0          // Address offset for the CAN status buffer in the DPRAM with the DPRAM start address as base address.
#define QUANTITY_OF_CAN_PORTS 2                 // Quantity of available CAN ports on the IXAAT board.
#define LENGTH_SEMAPHORE_NAME 100               // Length of the semaphore name (quantity of characters).

#pragma endregion


#pragma region Enum - CAN

/*
    Status of the CAN port.
*/
typedef enum CANPortStatus_E
{
    CpsStopped = 0, // CAN port is stopped
    CpsRunning,     // CAN port is running
    CpsRecovering   // CAN port is in bus-recovering status

} CANPortStatus;

/*
    Bus-recovering status of the CAN port.
*/
typedef enum CANRecoveryStatus_E
{
    CrsStop = 0,                // Bus-recovery: stop CAN port
    CrsInitialization,          // Bus-recovery: initilize CAN port
    CrsSetAcceptanceMask,       // Bus-recovery: set acceptance mask
    CrsConfigurationRxQueue,    // Bus-recovery: configure the Rx queue
    CrsStart                    // Bus-recovery: start CAN port

} CANRecoveryStatus;

/*
    Status of the CAN communication.
*/
typedef enum CANCommunicationStatus_E
{
    CcsStopCommunication = 0,   // Stop CAN communication
    CcsStartCommunication,      // Start CAN communication
    CcsCommunicationIsRunning   // CAN communication is running

} CANCommunicationStatus;

#pragma endregion

#pragma region Enum - LIN

/*
    That enum defines the values for the different global block functionalities.

*/
typedef enum IO601_BlockType_E
{
    BtNotDef = 0,       // Block type: not defined
    BtSender,           // Block type: sender
    BtReceiver,         // Block type: receiver
    BtSndRec,           // Block type: sender and receiver
    BtGlbSender = 4,    // Block type: global sender
    BtGlbReceiver = 8   // Block type: global receiver

} IO601_BlockType;

#pragma endregion


#pragma region Struct - CAN

/*
    Data structure for the CAN status available in the DPRAM at address 0xFF0 (Status Buffer0).
*/
typedef struct CANStatusBufferDPRAM_T
{
    uint16_T Status0;       // Status bits of the CAN 0 (Port 1)
    uint16_T BusLoad0;      // Bus load in percent of the CAN 0 (Port 1)
    uint16_T Status1;       // Status bits of the CAN 1 (Port 2)
    uint16_T BusLoad1;      // Bus load in percent of the CAN 1 (Port 2)
    uint16_T CPULoad;       // CPU load of the CAN board
    uint16_T LiveCounter;   // Live counter, shows if the firmware is running or not

} CANStatusBufferDPRAM;

/*
    All data and information for the CAN communication.
*/
typedef struct CANCommunicationData_T
{
    uint8_T ReadCounter;            // Counter for the current message index in the receie queue
    uint8_T WriteCounter;           // Counter for the current message index in the send queue
    CANCommunicationStatus Status;  // Current communication status of the CAN port

} CANCommunicationData;



/*
*   Structure for the global CAN sender of the IO601 module.
*/
typedef struct IO601_CANGlbSnd_T
{
    time_T LastTs;      // last sample time
    uint32_T QtySndBlk; // quantity of available write blocks in the model
    uint32_T AryIdx;    // Index for the next element, only for creation of array needed
    uint32_T *pQueueAddr;   // array of addresses for the single queue pointers

} IO601_CANGlbSnd;

/*
*   Concurrent execution struct
*/
typedef struct IO601_ConCurExeCAN_T
{
    void *pGlbSnd;         // Global sender for CAN

} IO601_ConCurExeCAN;


/*
    Includes all data and information about a CAN port.
*/
typedef struct CANPortData_T
{
    uint8_T IsEnabled;                  // Shows if CAN port is active (=TRUE) or not (=FALSE)
    uint8_T IsBackgroundTaskForRecoveryEnabled;
    uint8_T IsInitializationDone;       // Shows if CAN port is initilized (=TRUE) or not (=FALSE)
    uint8_T TimingRegisterBRP;
    uint8_T TimingRegisterSJW;
    uint8_T TimingRegisterTSEG1;
    uint8_T TimingRegisterTSEG2;
    uint8_T Mode;
    uint16_T BusRecoveryCounter;        // Counter for the number of times how often the bus has benn recovered
    uint32_T StartAutoBusRecovery;
    uint32_T StandardAcceptanceMask[2];
    uint32_T StandardAcceptanceCode[2];
    uint32_T ExtendedAcceptanceMask[2];
    uint32_T ExtendedAcceptanceCode[2];
    CANPortStatus Status;               // Current status of the CAN port
    CANRecoveryStatus RecoveryStatus;   // Current status of the recovery process
    CANCommunicationData Communication; // CAN communication data and information
    IO601_ConCurExeCAN ConCurExe;

} CANPortData;

/*
    All data of the CAN bus.
*/
typedef struct CANData_T
{
    uint8_T Test;
    CANStatusBufferDPRAM *pStatus;               // Current status of the CAN bus (DPRAM status buffer0 address: 0xFF0)
    CANPortData CANPort[2];

} CANData;

/*
*   Message buffer for each CAN write block.
*/
typedef struct IO601_CANWrtBlkBuf_T
{
    boolean_T isUpdated;
    canMsg Msg;           // Message buffer of the send block

} IO601_CANWrtBlkBuf;

/*
*   Structure for the CAN message queue for each CAN port.
*/
typedef struct IO601_CANPortSndQueue_T
{
    boolean_T IsUpdated;        // Status flag if queue index is updated or not
    uint8_T WrtIdx;             // Write index for the next message of the Simulink block
    uint8_T RdIdx;              // Read index for the message read by the global sender
    IO601_CANWrtBlkBuf BufMsg[3];

} IO601_CANPortSndQueue;


#pragma endregion

#pragma region Struct - Background Task

/*
    Structure for the BackgroundTask handling.
*/
typedef struct BackgroundTaskData_T
{
    void* pBusStatusSemaphore;         // Semaphore for the bus status
    void* pCANRecoveryThread[2];       // CAN recovery thread
    t_semaphores *pSemaphoreStatus;     // Semaphores status of CAN and LIN


} BackgroundTaskData;


typedef struct Mytest_T
{
    unsigned char DoRun;
    unsigned char DoLock;
    unsigned char IsLinSlave;
    unsigned char IsReaderWaiting[3];
    unsigned char RtnCanSndState[3];
    unsigned int Idx;
    unsigned int PortIndex;
    unsigned int FifoIdx;
    unsigned int FifoIdxLin;
    void* pSnderThr;
    void* pSnderSem;
    void* pSndRecMutex[3];
    ////char Logging[20000][40];
    unsigned int Cnt;
    unsigned int CountReaderWait[3];
    unsigned int CountThreadBreak;
    unsigned int WriterExe;
    unsigned int ReaderExe;
    unsigned int HelpCounter;

} Mytest;


#pragma endregion

#pragma region Struct - LIN

/* 
    LIN message is the datatype as used by IXXAT
    bId          -> identifier
    bModel       -> classic or enhanced checksum
    bCheckSum    -> checksum
    bSendData    -> 0: send header only, 1: send full frame
    bLength      -> valid data count of bDataByte field
    bDummy       -> padding byte
    bDataByte[8] -> data
*/
typedef struct BCI_t_LIN_MSG_Tag
{
    uint8_T bId;
    uint8_T bModel;
    uint8_T bCheckSum;
    uint8_T bSendData;
    uint8_T bLength;
    uint8_T bDummy;
    uint8_T bDataByte[8];
}BCI_t_LIN_MSG_T;

typedef struct LINQueueEntry_Tag
{
    uint8_T status;
    uint8_T count;
    uint8_T timeStamp[4];
    uint8_T type;
    uint8_T information;
    BCI_t_LIN_MSG_T sMsg;
}LINQueueEntry_T;

/*
*   That structure defines the message object in the global LIN message buffer.

*/
typedef struct IO601_LINMsgBuf_T
{
    boolean_T EnaToSend;        // Status flag if the message must be sent (=1) or not (=0)
    boolean_T isSndData;        // Status flag if sent message includes data (=1) or not (=0)
    boolean_T IsEnhcdChksum;    // Status flag which checksum should be used default (=0) or enhanced (=1)
    uint8_T ConsNo;             // Consecutiv number of the LIN message
    uint8_T FullProtID;         // Full protected ID = protected ID + the even and odd parity bits
    uint8_T Chksum;             // Checksum of the LIN message
    uint8_T DLC;                // Data length code (length of the message data)
    uint8_T MsgType;            // Message type of the received LIN message
    uint8_T MsgInfo;            // Information of the received LIN message
    uint8_T Data[8];            // Data field for the LIN message
    uint16_T ErrCode;           // LIN message error code
    uint32_T Tstp;              // Timestamp of the received message
    int32_T UpdState;           // Update state of the LIN message: 1 = updated, 0 = not updated, -1 = error
    real_T SampelTime;          // Sample time of the LIN message block
    IO601_BlockType BlkType;

} IO601_LINMsgBuf;

/*
*   Message buffer for each LIN write block.
*/
typedef struct IO601_LINBlkBufMsg_T
{
    uint8_T isUpdated;
    uint8_T ProtID;
    uint8_T FullProtID;
    uint8_T IsEnhcdChksum;
    uint8_T Chksum;
    uint8_T isSndData;
    uint8_T DLC;
    uint8_T Type;
    uint8_T Info;
    uint8_T Data[8];
    uint16_T ErrCode;
    uint32_T Tstp;
    int32_T UpdState;

} IO601_LINBlkBufMsg;

/*
*   Structure for the CAN message queue for each CAN port.
*/
typedef struct IO601_LINPortQueue_T
{
    boolean_T IsSender; // is block global sender
    boolean_T IsReceiver; // is block global receiver
    uint8_T WrtIdx;     // Write index for the next block msg (updated by block or glbReceiver)
    uint8_T RdIdx;      // Read index for the message read by the global sender or block
    uint16_T ErrCode;
    time_T Ts;      // Sample time of the block
    IO601_LINBlkBufMsg BufMsg[BLK_BUF_SZ];

} IO601_LINPortQueue;



/*
*   Structure for the global LIN sender of the IO601 module.
*/
typedef struct IO601_LINGlbSndRec_T
{
    uint8_T BlockQty;                   // quantity of blocks with the fastest sample time
    time_T FastestTs;                   // fastest sample time
    IO601_LINPortQueue* QueueAry[64];   // array for the addresses of the single block buffers

} IO601_LINGlbSndRec;

/*
*   Concurrent execution struct
*/
typedef struct IO601_ConCurExeLIN_T
{
    ////IO601_LINGlbSndRec GlbSnd;         // Global sender for LIN
    ////IO601_LINGlbSndRec GlbRec;         // Global Receiver for LIN
    ////void *pHandler;                 // Pointer to the concurrent execution hanlder (C++ code)

    void *pGlbSnd;
    void *pGlbRec;

} IO601_ConCurExeLIN;


/*
*   Structure includes all LIN information.

*/
typedef struct LINData_T
{
    boolean_T IsMaster;             // Status flag if device is master (=1) or slave (=0)
    uint8_T ConsNoLIN;              // Consecutive number for LIN
    uint8_T NextMsgIdx;             // Index of the last message which was sent
    uint8_T ReadIndex;              // Index of the read position of the LIN receive queue
    uint8_T WriteIndex;             // Index of the write position of the LIN send queue
    uint8_T ErrIdx;
    uint8_T ErrIdxRd;
    uint16_T ErrCodes[64];          // Array for the received error codes
    IO601_LINMsgBuf LINMsgBuf[64];  // Pointer to the LIN message buffer
    IO601_ConCurExeLIN ConCurExe;
} LINData;


/*
*   Structure for the LIN status

*/
typedef struct LINStatus_T
{
    uint8_T Role;       // LIN role, 0: Slave, 1: Master
    uint8_T Busload;    // LIN bus load in [%]
    uint16_T Bitrate;   // Bitrate set during the configuration
    uint32_T Status;    // LIN status, 0: OK, 1: Data overrun, 16: Controller in init mode

} LINStatus;
#pragma endregion

#pragma region Struct - Driver

/*
    Global driver structure

*/
typedef struct sg_IO601_Module_Tag
{
    int16_T SlotNumber;                     // Number of the PCI slot of the I/O module
    int16_T BusNumber;                      // Number of the PCI bus of the I/O module
    uint32_T ModuleID;                      // Device number of the I/O module
    uint32_T ModuleIndex;                   // Index of the I/O moudle (PCI card
    CANData CAN;                            // CAN infromation
    LINData LIN;                            // LIN information
    BackgroundTaskData BackgroundTask;      // Sempahore for bus recovery
    volatile uint32_T *pIOAddress0;         // Pointer to the virtual PCI addres with the index 0
    volatile uint8_T *pIOAddress2;          // Pointer to the virtual PCI addres with the index 2
    volatile BCICOMMAND *pCommandPacket;    // A pointer to the command buffer of the I/O module, the structure represent the communication packet
    Mytest *pGlbSnd;
    CANPortStatus PortStatus[3];             // Port status

} sg_IO601_Module_T;

#pragma endregion


#pragma region Globals - External

extern sg_IO601_Module_T *sg_IO601_pModule;
extern uint32_T sg_IO601_ModuleCounter;

#pragma endregion


#pragma region Forward-Declarations - Static

static uint32_T ToIntel(uint32_T id, uint32_T nBits);

#pragma endregion

#pragma region Forward-Declarations - General

void SetGeneralStartValuesBySetupBlock(uint32_T moduleIndex);
void ClearAllBoardBuffers(uint32_T moduleIndex);
void ClearPCToMCBuffers(uint32_T moduleIndex, uint8_T CANPort);
void ClearMCToPCBuffers(uint32_T moduleIndex, uint8_T CANPort);
void AnalyseMCToPCBuffers(uint32_T moduleIndex, uint8_T CANPort); // for debugging only
void CleanupAll(uint32_T moduleIndex);
void CleanupAllOnError(uint32_T moduleIndex);
void ResetBoard(uint32_T moduleIndex);
void InterruptMicrocontroller(uint32_T moduleIndex);
void SetOutputPortValue(uint32_T moduleIndex, uint8_T CANPort, uint32_T valueIndex, uint16_T *pOutputPortCAN0);
void SetDefaultValues(uint32_T moduleIndex);
void RestartFirmware(volatile uint32_T *ioaddress0, volatile BCICOMMAND *bci, uint8_T blocking);
void UpdateLinTxBufDpramEntry(uintptr_t base, uint8_T entry, volatile BCI_t_LIN_MSG msg);

boolean_T IO601_SetGlbSndRec(uint32_T modIdx);

uint8_T CheckDriver();
// DELETE_: uint8_T SetDefaultValuesBySetupBlock(uint32_T moduleIndex);
uint8_T SetDefaultValuesBySetupBlock(uint32_T moduleIndex, boolean_T isSetupBlk);
uint8_T SetStartValuesStatusBlock(uint32_T moduleIndex);
uint8_T GetPCIDeviceInformation(uint32_T moduleIndex, int16_T busNumber, int16_T slotNumber);
uint8_T InitializationBoard(uint32_T moduleIndex);
uint8_T ReadApplicationIdentifyingInformation(uint32_T moduleIndex);
uint8_T ReadoutVersionNumber(int32_T moduleIndex);
uint8_T TestBoard(uint32_T moduleIndex);
uint8_T ConfigureReceivingQueue(uint32_T moduleIndex, uint8_T CANPort, uint8_T receiveMode);
uint8_T CreateBusStatusSemaphore(uint32_T moduleIndex);
uint8_T IsBusOff(uint32_T moduleIndex, uint8_T port);
uint8_T ReadFIFO(uint32_T moduleIndex, uintptr_t queueEntryAddress, canMsg *message, uint32_T* tsOut);
uint8_T CreateID(uint8_T id);

uint32_T WriteFIFO(uintptr_t queueEntryAddress, canMsg message);
uint32_T ToMotorola(uint32_T id, uint32_T nBits);

void IO601_SleepMilliseconds(real_T milliseconds);

#pragma endregion

#pragma region Forward-Declaration - CAN

void SetBusSpecificValues(uint32_T moduleIndex, uint8_T CANPort,
                          uint8_T busTimingRegisterBRP, uint8_T busTimingRegisterSJW, uint8_T busTimingRegisterTSEG1, uint8_T busTimingRegisterTSEG2, uint8_T mode,
                          uint32_T acceptanceMask1, uint32_T acceptanceCode1, uint32_T acceptanceMask2, uint32_T acceptanceCode2,
                          uint32_T extAcceptanceMask1, uint32_T extAcceptanceCode1, uint32_T extAcceptanceMask2, uint32_T extAcceptanceCode2);
void IncrementCANQueueEntryPosition(uint8_T readWrite, uint32_T moduleIndex, uint32_T port);
//void ReadCANMessage(uint32_T moduleIndex, uint8_T CANPort, uint8_T *pIsCANMessageAvailable, canMsg *pCANMessageOutputPort);
void ReadCANAndRAWMessage(uint32_T moduleIndex, uint8_T CANPort, uint8_T *pIsCANMessageAvailable, canMsg *pCANMessageOutputPort,
                          uint8_T *pData, uint32_T *pIdentifier, uint32_T *pLength, uint32_T *pIdentifierType, uint32_T *pTimestamp);
void ReadRawMessage(uint32_T moduleIndex, uint8_T CANPort, boolean_T *pIsRAWMessageAvailable, uint8_T *pData, uint32_T *pIdentifier, uint32_T *pLength,
                    uint32_T *pIdentifierType, uint32_T *pTimestamp);

uint8_T SetStandardAcceptanceMask(uint32_T moduleIndex, uint8_T CANPort, uint8_T maskNumber, uint8_T mode, uint32_T acceptanceMask,
                                  uint32_T acceptanceCode);
uint8_T InitializeCANPort(uint32_T moduleIndex, uint8_T CANPort);
uint8_T StartCANPort(uint32_T moduleIndex, uint8_T CANPort);
uint8_T StopCANPort(uint32_T moduleIndex, uint8_T CANPort);
uint8_T PrepareCANQueueEntry(canMsg message, volatile CAN_QUEUEENTRY *pQueue);

int32_T SendCANMessage(uint32_T moduleIndex, uint8_T CANPort, canMsg *pCANMessageInputPort);
int32_T SendRAWMessage(uint32_T moduleIndex, uint8_T CANPort, uint8_T *pRAWDataInputPort, uint32_T *pRAWIdentifierInputPort, uint32_T *pRAWLengthInputPort, uint32_T *pRAWIdentifierTypeInputPort);

uintptr_t GetCANQueueBaseAddress(uint32_T moduleIndex, uint32_T port, uint8_T fifo);
uintptr_t GetCANQueueEntryAddress(uint32_T moduleIndex, uint32_T port, uint8_T fifo);

#pragma endregion

#pragma region Forward-Declaration - LIN

void IO601_SetMsgData(uint8_T modIdx, uint8_T protID, uint8_T *pData);
void IO601_LINGetMsgState(uint32_T modIdx, uint8_T protID, int32_T *pMsgState);
void IO601_LINGetMsgInfo(uint32_T modIdx, uint8_T protID, int32_T *pInfo);
void IO601_LINGetMsgError(uint32_T modIdx, uint8_T protID, int32_T *pErr);
void IO601_LINGetMsgTstp(uint32_T modIdx, uint8_T protID, uint32_T *pTstp);
void IO601_LINGetMsgData(uint32_T modIdx, uint8_T protID, uint8_T *pData);

boolean_T IO601_LINAddMsgToBuf(uint32_T modIdx, uint8_T protID, uint8_T blkType, boolean_T enaToSnd, boolean_T isSndData, boolean_T isChkSumV2x, uint8_T dlc,
                               real_T sampleTime, uint8_T qtyMsg, uint8_T *pDefMsgData);
boolean_T IO601_LINWrtMsgToSndQueue(uint32_T modIdx, uint8_T protID);
boolean_T IO601_LINRdMsgFromRecQueue(uint32_T modIdx, uint8_T protID);
boolean_T IO601_LINSlvWrtMsgToQueue(uint32_T modIdx, uint8_T protID);
boolean_T IO601_LINChkStateSema(uint32_T modIdx, boolean_T isSemaLock);

uint8_T ResetLIN(uint32_T moduleIndex);
uint8_T InitializeLIN(uint32_T moduleIndex, uint8_T role, uint16_T baudrate);
uint8_T StartLIN(uint32_T moduleIndex);
uint8_T StopLIN(uint32_T moduleIndex);

void IO601_LINStatusRole(uint32_T modIdx, uint32_T *pRole);
void IO601_LINStatusBusload(uint32_T modIdx, uint32_T *pBusload);
void IO601_LINStatusBitrate(uint32_T modIdx, uint32_T *pBitrate);
void IO601_LINStatusStatus(uint32_T modIdx, uint32_T *pStatus);
void LINCleanupMsgBuffer(uint32_T modIDx);

BCI_t_LIN_MSG EncodeLINMessage(uint8_T id, uint8_T length, uint8_T enhancedChecksum, uint8_T* data);


#pragma endregion

#pragma region Forward-Declaration - CAN Concurrent Execution

int32_T IO601_CANSendMessage(uint32_T moduleIndex, uint8_T CANPort, canMsg *pCANMessageInputPort);

////boolean_T IO601_CANSetConCurExeHdl(uint32_T modIdx);
////boolean_T IO601_SetSndQueueArray(uint32_T modIdx, uint8_T ptIdx, uint32_T qtySndBlocks);
////boolean_T IO601_CANSetPortQueue(uint32_T modIdx, uint8_T ptIdx, void **ppQueue);
////boolean_T IO601_CANGlbSender(uint32_T modIdx, uint8_T ptIdx, int id, time_T ts);
////boolean_T IO601_CANSetMsgToBuffer(uint32_T modIdx, void *pQueue, canMsg *pMsg);

#pragma endregion

#pragma region Forward-Declaration - LIN Concurrent Execution

unsigned char IO601_LINLockUnlockBuffer1(uint32_T modIdx, boolean_T enaLock);
unsigned char IO601_LINLockUnlockBuffer2(uint32_T modIdx, boolean_T enaLock);
void IO601_WrtMsgToRwwb(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg);
void IO601_LINCopyRwwb(uint32_T modIdx);
unsigned char IO601_LINMaSend(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg);

void IO601_WrtMsgToRwwb2(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg);



void IO601_WrtMsgToRwwb_22(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg);



////boolean_T IO601_LINSetConCurExeHdl(uint32_T modIdx);
////boolean_T IO601_LINSetPortQueue(uint32_T modIdx, uint8_T protID, boolean_T isEnhcdChkSum, uint8_T dlc, boolean_T isSndData, boolean_T isSender, time_T ts, void **ppQueue);
////boolean_T IO601_LINSetMsgToBuffer(uint32_T modIdx, void *pQueue, uint8_T *pData, double ts, uint8_T protID);
////boolean_T IO601_LINGlbSender(uint32_T modIdx, uint8_T protID, time_T ts);
////boolean_T IO601_LINGlbReceiver(uint32_T modIdx, uint8_T protID, time_T ts);
////void IO601_LINGetReadIdx(uint32_T modIdx, uint8_T protID, uint8_T *pIdx, void *pQueue, double ts);
////void IO601_LINGetMsgFromBufferUpdState(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pState);
////void IO601_LINGetMsgFromBufferMsgInfo(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pInfo);
////void IO601_LINGetMsgFromBufferMsgErrCode(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pErrCode);
////void IO601_LINGetMsgFromBufferTstp(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pTstp);
////void IO601_LINGetMsgFromBuffer(uint32_T modIdx, uint8_T rdIdx, void *pQueue, uint8_T *pData, double ts);
////boolean_T IO601_LINGlbSlvReceiver(uint32_T modIdx, uint8_T protID, time_T ts);
////boolean_T IO601_LINGlbUpdaterSlv(uint32_T modIdx, uint8_T protID, time_T ts);

#pragma endregion

#endif // !__SG_IO601_FCN_H__
