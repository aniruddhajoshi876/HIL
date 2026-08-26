/*
*   See    : Corresponding Code-File: IO61X_iConcurrentExecution.cpp
*   Version: $Revison$
*   Author : $Author$
*   Date   : $Date$
*/

#ifndef __IO61X_I_CONCURRENT_EXECUTIO_H__
#define __IO61X_I_CONCURRENT_EXECUTIO_H__


#include "CAN_Message_Definition.h"
#include "CANFD_Message_Definition.h"
#include "LIN_Message_Definition.h"

//uint8_t IO61X_CheckTargetFileSystem(const char *pProtl, const char *pDrLtr, char *pErrMsg);

void IO61X_TargetDefaults(); // initialize target-dependent globals.
uint8_t IO61X_CreateDriverModuleList(uint32_t qtyMods, const char *pDrLtr, char *pErrMsg);

uint8_t IO61X_PrintModuleInfo(uint32_t modID, int16_t bus, int16_t slot, const char *pProtl);
uint8_t IO61X_InitializeModule(uint32_t modID, uint8_t ptQty, const char *pProtl, int16_t PCIBus, int16_t PCISlot, uint32_t *pModIdx, char *pErrMsg);
uint8_t IO61X_SetModuleStatusStartPorts(uint32_t modIdx, char *pErrMsg);
uint8_t IO61X_SetModuleStatusReady(uint32_t modIdx, char *pErrMsg);
uint8_t IO61X_SetModuleStatusNotReady(uint32_t modIdx);
int     IO61X_GetModuleStatusInitialized(uint32_t modIdx);
uint8_t IO61X_CheckIsModuleStatusReady(uint32_t modIdx, char *pErrMsg);
uint8_t IO61X_GetModuleIndex(uint32_t modID, const char *pProtl, uint32_t *pModIdx, char *pErrMsg);

uint8_t IO61X_CheckIsDriverInitialized(uint32_t modID, const char *pProtl, char *pErrMsg);

int IO61X_CanFdCheckAndGetBaudrate(uint32_t modIdx, uint8_t ptIdx, uint32_t dlc, char *pErrMsg);


uint8_t IO61X_StartCanController(uint32_t modIdx, uint8_t ptIdx, char *pErrMsg);
uint8_t IO61X_StopCanController(uint32_t modIdx, uint8_t ptIdx);

uint8_t IO61X_StartLinController(uint32_t modIdx, uint8_t ptIdx, char *pErrMsg);
uint8_t IO61X_StopLinController(uint32_t modIdx, uint8_t ptIdx);

uint8_t IO61X_SendCanMessage(uint32_t modIdx, uint8_t ptIdx, uint8_t isFD, const CANMsg *pMsg);

uint8_t IO61X_ReceiveCanMessage(uint32_t modIdx, uint8_t ptIdx, uint8_t isFD, CANMsg *pMsg);
uint8_t IO61X_ReceiveCanRawMessage(uint32_t modIdx, uint8_t ptIdx, uint8_t isFD, uint32_t* pID, uint32_t* pFF, uint32_t* pLen, double* pTimeStamp, void *pData);
uint8_t IO61X_ReceiveCanAndCanRawMessage(uint32_t modIdx, uint8_t ptIdx, uint8_t isFD, CANMsg *pMsg, uint32_t* pID, uint32_t* pFF, uint32_t* pLen, double* pTimeStamp, void *pData);


uint8_t IO61X_SendCanFdMessage(uint32_t modIdx, uint8_t ptIdx, const void *pMsg);
uint8_t IO61X_SendCanFdRawMessage(uint32_t modIdx, uint8_t ptIdx, const uint32_t *pID, const uint32_t *pFF, const uint32_t *pDLC, const uint32_t *pBrs,
                                  const uint8_t *pData);
uint8_t IO61X_ReceiveCanFdMessage(uint32_t modIdx, uint8_t ptIdx, void *pMsg);
uint8_t IO61X_ReceiveCanFdMessageRaw(uint32_t modIdx, uint8_t ptIdx, uint32_t* pID, uint32_t* pFF, uint32_t* pDLC,
    uint32_t* pBrs, double* pTimeStamp, void *pData);
uint8_t IO61X_ReceiveCanFdAndCanFdRawMessage(uint32_t modIdx, uint8_t ptIdx, void *pMsg, uint32_t* pID, 
    uint32_t* pFF, uint32_t* pDLC, uint32_t* pBrs, double* pTimeStamp, void *pData);


uint8_t IO61X_InitializeCanController(uint32_t modIdx, uint8_t ptIdx, uint8_t isProtlFD, uint8_t protlHelpIdx
                                      , uint8_t opMode, uint16_t brp, uint16_t sjw, uint16_t tseg1, uint16_t tseg2, uint16_t brpDataFD, uint16_t sjwDataFD
                                      , uint16_t tseg1DataFD, uint16_t tseg2DataFD, double spFD, uint16_t bdrFD, uint32_t stdAccMask, uint32_t stdAccCode
                                      , uint32_t extAccMask, uint32_t extAccCode, char *pErrMsg);

uint8_t IO61X_InitializeLincotroller(uint32_t modIdx, uint8_t ptIdx, uint8_t opMode, uint32_t bdr, uint8_t ptChNo, uint8_t protlIdx, uint8_t ptType
                                     , char *pErrMsg);

// obsolete
void IO6X_SetLinMessageQuantity(uint32_t modIdx, uint8_t ptIdx, uint32_t qtyMsg);
// obsolete
void IO61X_SetLinBuffer(uint32_t modIdx, uint8_t ptIdx, uint8_t isStart, uint8_t isSlv);
// obsolete
uint8_t IO61X_SendLinMessage(uint32_t modIdx, uint8_t ptIdx, const LINMsg *pMsg);
// obsolete
uint8_t IO61X_SendLinRawMessage(uint32_t modIdx, uint8_t ptIdx, const uint8_t *pID, const uint8_t *pIDOnly, const uint8_t *pChkSum
                                , const uint8_t *pLen, const uint8_t *pData);
// obsolete
uint8_t IO61X_CheckLinDlcAndChecksum(uint32_t modIdx, uint8_t ptIdx, uint8_t dlc, uint8_t chkSum, char *pErrMsg);
// obsolete
void IO61X_SetLinMessageFilter(uint32_t modIdx, uint8_t ptIdx, const uint8_t *pID, const uint8_t *pIDOnly, const uint8_t *pChkSum, const uint8_t *pLen);
// obsolete
uint8_t IO61X_ReceiveLinMessage(uint32_t modIdx, uint8_t ptIdx);
// obsolete
uint8_t IO61X_GetLinMessageById(uint32_t modIdx, uint8_t ptIdx, uint8_t slvID, LINMsg *pMsg);
// obsolete
uint8_t IO61X_GetLinRawMessageById(uint32_t modIdx, uint8_t ptIdx, uint8_t slvID, uint32_t *pID, uint32_t *pType, uint32_t *pChkSum, uint32_t *pLen
                                   , uint32_t *pPosDataOvrn, uint32_t *pTimStamp, uint8_t *pData);


#pragma region Forward-Declaration - CAN

uint8_t IO61X_CreatePort(uint32_t modIdx, uint8_t portIdx, uint8_t isFdModule, uint8_t portType, uint8_t opMode,
                         char *pErrMsg);
void IO61X_ClearPortBuffer(uint32_t modIdx);
uint8_t IO61X_GetBlockBuffer_spin(uint32_t modIdx, uint8_t portIdx, uint8_t isSender, uint32_t msgId, void **ppBuffer
                                  , char *pErrMsg);
void IO61X_ReleaseWriteSempahore(uint32_t modIdx);

/* 
pBuffer must point to the buffer registered for the calling S-Function block.
pMsg contains CAN, CANFd, or LIN msg.
returns codes: 
    -1 error, pErrMsg contains error message
     0  no message sent
     1  msg was copied to send buffer*/
int8_t IO61X_UpdateBuffer(uint32_t modIdx, uint8_t portIdx, void *pBuffer, void *pMsg, char* pErrMsg);

void IO61X_LinUpdateRwwbBuffer(uint32_t modIdx, uint8_t portIdx, uint8_t isSlave, uint8_t protId, uint8_t isIdOnly,
                                    uint8_t dlc, uint8_t isEnhcdChksum);
uint8_t IO61X_LinRecMsg_spin(uint32_t modIdx, uint8_t portIdx, double ts, int id);
uint8_t IO61X_GetReceivedMessageLin(uint32_t modIdx, uint32_t portIdx, uint8_t protID, int *pUpdateState,
                                          uint32_t *pMsgType, uint32_t *pDataOverrun, uint32_t *pTimeStamp, uint8_t *pData);

#pragma endregion



#pragma region Forward-Declaration - Status Handling

uint8_t IO61X_ActivateStatus(uint32_t modIdx, uint8_t ptIdx, char *pErrMsg);
void IO61X_GetStatusOperatingModeByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetStatusExtendedOperatingModeByStatusBlock(uint32_t moduleIndex, uint8_t portNumber, uint32_t*pStatusOutputPort);
void IO61X_GetStatusBusLoadByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANStatusTimingModeByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANFDStatusTimingModeByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANStatusBaudRatePrescalerByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANFDStatusBaudRatePrescalerByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANStatusBitTimeSegment1ByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANFDStatusBitTimeSegment1ByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANStatusBitTimeSegment2ByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANFDStatusBitTimeSegment2ByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetCANStatusSynchronisationJumpWidthByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetCANFDStatusSynchronisationJumpWidthByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetCANStatusTransceiverDelayOffsetByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t*pStatusOutputPort);
void IO61X_GetStatusTransmissionPendingByStatusBlock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetStatusDataOverrunByStatusblock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetStatusErrorWarningByStatusblock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetStatusBusOffByStatusblock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetStatusInitModeByStatusblock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetStatusBusCouplingErrorByStatusblock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetStatusPrioTransmissionPendingByStatusblock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);
void IO61X_GetStatusBusRecoveryCounterByStatusblock(uint32_t modIdx, uint8_t ptIdx, uint32_t* pStatusOutputPort);

void IO61X_ActivateStatusThread(uint32_t modIdx, uint8_t ptIdx, uint32_t busRecoInPt, uint32_t busRecoType);

void IO61X_LINGetStatusOpMode(uint32_t modIdx, uint8_t ptIdx, void *pStatusOutputPort);
void IO61X_LINGetStatusBdr(uint32_t modIdx, uint8_t ptIdx, void *pStatusOutputPort);
void IO61X_LINGetStatusBusLoad(uint32_t modIdx, uint8_t ptIdx, void *pStatusOutputPort);
void IO61X_LINGetStatusDataOvrn(uint32_t modIdx, uint8_t ptIdx, void *pStatusOutputPort);
void IO61X_LINGetStatusInitAct(uint32_t modIdx, uint8_t ptIdx, void *pStatusOutputPort);

#pragma endregion

/*
    Send CAN initialization/termination structure.
*/
bool SendInitTermStructure(uint32_t modIdx, bool isFdMod, const double* itstruct);

/* 
 Handle error situation.
 use sg_module_type=0 if not known.
*/
void CleanupOnError(int sg_module_type, int modId);
inline void CleanupOnError(int sg_module_type, int modId, const char* errmsg) { errmsg;  CleanupOnError(sg_module_type, modId); }

#endif // !__IO61X_I_CONCURRENT_EXECUTIO_H__
