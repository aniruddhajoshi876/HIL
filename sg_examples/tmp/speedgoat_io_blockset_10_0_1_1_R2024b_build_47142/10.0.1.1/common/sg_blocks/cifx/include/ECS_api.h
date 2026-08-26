#ifndef __ECS_API_H
#define __ECS_API_H

#include "stdint.h"
#include "sg_common.h"

#define ECS_OBJ_NAME_LEN		200		// Found 200 in Hilscher spec but there is no header defining this value
#define ECS_MAX_NUM_PDO			254
#define ECS_MAX_NUM_AO_IN_PDO	200
#define ECS_MAX_NUM_AO			1024
#define ECS_NUM_PDO_PROPS		4
#define ECS_MAX_NUM_SDO         (4*1024)
#define ECS_MAX_NUM_EMERGENCY   128

#define ECS_PDO_RX		0		// OUT
#define ECS_PDO_TX		1		// IN

typedef struct t_ECS_AO
{
	uint8_t Dtype;
    uint8_t EcatDtype;
	uint8_t BitLen;
	bool Padding;
	char Name[ECS_OBJ_NAME_LEN];

} ECS_AO_T;

typedef struct t_ECS_PDO_2
{
	uint8_t NumAo;
	char Name[ECS_OBJ_NAME_LEN];
	ECS_AO_T* Ao[ECS_MAX_NUM_AO_IN_PDO];

} ECS_PDO_T;

typedef struct t_ECS_AREA
{
	uint8_t NumPdo;
	uint8_t SyncManagerId;
	uint16_t SyncManagerIdx;
	uint16_t PdoIdx;
	uint16_t AoIdx;
	uint16_t AccessFlags;
	uint16_t AccessRights;
	uint32_t BitLen;
	
	char Name[ECS_OBJ_NAME_LEN];
	ECS_PDO_T* Pdo[ECS_MAX_NUM_PDO];

} ECS_PDO_AREA_T;

typedef struct t_ECS_SDO
{
    uint16_t Index;
    uint8_t SubIndex;
    uint16_t AccessRights;
    uint8_t DataType;
    uint8_t AccessMode;
    uint8_t NumElements;
    uint8_t ByteLen;
    bool DoWrite;
    double InitValue;
    uint8_t ReadValue[8];
    uint8_t WriteValue[8];
    uint32_t AcyclicLot;
    uint32_t TxHostFlags;
    uint32_t TxDevFlags;
    uint32_t RxHostFlags;
    uint32_t RxDevFlags;
    bool Operation;
    char Name[ECS_OBJ_NAME_LEN];

} ECS_SDO_T;

typedef struct t_ECS_EMERGENCY
{
    uint16_t Priority;
    uint16_t ErrorCode;
    uint8_t ErrorRegister;
    uint8_t Data[5];

    uint32_t AcyclicLot;

    uint32_t TxHostFlags;
    uint32_t TxDevFlags;

} ECS_EMERGENCY_T;

typedef struct t_ECS_PARAM
{
	uint32_t VendorID;      // Vendor ID of the module
	uint32_t ProdCode;      // Product code of the module
	uint32_t RevisionNo;    // Revision number of the module
	uint32_t SerialNo;      // Serial number of the module
	uint16_t StationAlias;	// the so-called Configured Station Address Alias
	uint16_t DeviceIdent;	// device identification value
	uint32_t InputDataSz;   // Only used by v1 blocks. Process Data Input Size
	uint32_t OutputDataSz;  // Only used by v1 blocks. Process Data Output Size
	bool DcSyncMode;
    uint8_t RxSync;
    uint8_t TxSync;
    uint32_t NumSdo;    
    uint32_t NumEmergencies;
    ECS_SDO_T Sdo[ECS_MAX_NUM_SDO];
    ECS_EMERGENCY_T Emergencies[ECS_MAX_NUM_EMERGENCY];

	ECS_PDO_AREA_T PdoArea[2];
	
} ECS_PARAM_T;

int32_t ECS_AcyclicHandler(CIFX_CHANNEL_T *Channel);
int32_t ECS_AddPdo(ECS_PDO_AREA_T* Area, ECS_PDO_T** Pdo);
int32_t ECS_AddAo(ECS_PDO_T* Pdo, ECS_AO_T** Ao);
int32_t ECS_Clear(CIFX_CHANNEL_T* Channel);
int32_t ECS_UpdateEmergency(CIFX_CHANNEL_T* Channel,
    ECS_EMERGENCY_T* Emergency,
    bool Enable,
    uint16_t Priority,
    uint16_t ErrorCode,
    uint8_t ErrorRegister,
    uint8_t* Data);
int32_t ECS_AddEmergency(CIFX_CHANNEL_T* Channel, ECS_EMERGENCY_T** Emergency);

#endif