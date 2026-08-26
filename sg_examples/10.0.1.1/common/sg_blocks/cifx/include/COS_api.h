#ifndef __COS_API_H
#define __COS_API_H

/* Includes */
#include "stdint.h"

/* Defines */
#define CO_PDO_LEN           8
#define CO_MAX_HB_CONSUMER   64
#define CO_MAX_MONITOR_ITEMS 128

typedef struct t_COS_OBJECT {

    uint16_t Index;
    uint8_t SubIndex;
    uint16_t AccessRights;
    uint8_t ObjectType;
    uint16_t DataType;
    uint32_t DataLen;
    uint32_t NumElements;
    uint32_t Status;
    bool ReadOp;
    bool WriteOp;
    bool Extended;
    bool IsMain;
    void *Data;

} COS_OBJECT_T;

typedef struct t_COS_PDO {
    uint8_t PdoType;
    uint16_t PdoId;
    uint32_t CobId;
    uint8_t TransType;
    uint8_t TransRate;
    uint16_t InhibitTime;
    uint16_t EventTimer;
    uint8_t SyncStart;
    uint32_t DataLen;

    uint8_t NumObjects;
    COS_OBJECT_T *Objects[CO_PDO_LEN];

    uint32_t Map[CO_PDO_LEN][2];
    uint32_t DpmOffset[CO_PDO_LEN];

} COS_PDO_T;

typedef struct t_COS_MESSAGE {
    uint32_t TxHostFlags;
    uint32_t TxDevFlags;
    uint32_t RxHostFlags;
    uint32_t RxDevFlags;
    uint32_t MessageID;
    uint32_t Length;
    uint32_t MaxLength;
    uint8_t Data[8];

} COS_MESSAGE_T;

typedef struct t_COS_DIAG {
    uint32_t Flags;
    uint32_t BusOffEventCnt;
    uint32_t ErrorPassiveEventCnt;
    uint32_t RxOverflowCnt;
    uint32_t TxOverflowCnt;
    uint32_t ErrorCnt;
    uint32_t TimeoutCnt;
    uint32_t IndLostCnt;
    uint32_t DiagInfoCnt;
    uint32_t LastDiagEntry;
    uint32_t AddDetail[3];

} COS_EXTDIAG_T;

typedef struct t_COS_STATUS {
    uint32_t NodeState;
    uint32_t NodeStateCtrl;
    uint32_t NodeStateCtrlOld;
    uint32_t NodeStateCmd;
    COS_EXTDIAG_T ExtDiag;
    uint32_t Monitoring[CO_MAX_MONITOR_ITEMS];

} COS_STATUS_T;

typedef struct t_COS_HBC {
    uint16_t Time;
    uint8_t CanNodeId;
    uint8_t reserved;

} COS_HBC_T;

typedef struct t_COS_PARAM {
    bool AppRegReq;
    bool AppRegCnf;
    bool ComStartReq;
    bool ComStartCnf;
    bool StateChangeReq;
    bool StateChangeCnf;
    bool ErrorIsActive;

    uint32_t NumErrors;

    uint32_t CoNodeId;
    uint32_t BaudRate;
    uint32_t DeviceType;
    uint32_t VendorId;
    uint32_t ProductCode;
    uint32_t RevNum;

    uint16_t HbProducer;
    uint8_t NumHbConsumer;
    COS_HBC_T HbConsumer[CO_MAX_HB_CONSUMER];
    uint16_t GuardTime;
    uint16_t LifeTimeFactor;
    
    uint32_t NumObjects;
    uint16_t NumRxPdos;
    uint16_t NumTxPdos;
    uint32_t NumRxMessages;
    uint32_t NumTxMessages;
    uint32_t RxLen;
    uint32_t TxLen;

    uint32_t InternalState;

    COS_STATUS_T Status;

    COS_OBJECT_T **Objects;
    COS_PDO_T **RxPdos;
    COS_PDO_T **TxPdos;
    COS_MESSAGE_T **RxMessages;
    COS_MESSAGE_T **TxMessages;

} COS_PARAM_T;

#ifdef __cplusplus
extern "C" {
#endif

int32_t COS_AcyclicHandler(CIFX_CHANNEL_T *Channel);
int32_t COS_UpdateRxPdos(CIFX_CHANNEL_T *Channel);
int32_t COS_UpdateTxPdos(CIFX_CHANNEL_T *Channel);
int32_t COS_UpdateState(CIFX_CHANNEL_T *Channel, bool ExtDiag);
int32_t COS_Shutdown(CIFX_CHANNEL_T *Channel);
int32_t COS_MapObjects(COS_PARAM_T* Param, uint32_t* TotalLength, COS_PDO_T** Pdos, uint32_t NumPdos);
int32_t COS_SortObjects(COS_PARAM_T* Param);

#ifdef __cplusplus
}
#endif

#endif