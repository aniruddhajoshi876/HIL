#include "stdint.h"
#include "cifxapi.h"


#define PNS_MAX_NUM_SUBMODULES   95      // PNSIF_API.h
#define PNS_NAME_OF_STATION_LEN  127     // PNSIF_spec.h
#define PNS_SUBMODULE_INFO_LEN   7
#define PNS_MAX_RECORD_LEN  1500
#define PNS_MAX_NUM_RECORDS 4096
#define PNS_MAX_STR_LEN 256

#define PNS_ERROR_RECORD_READ           0xDE800000
#define PNS_ERROR_RECORD_WRITE          0xDF800000

#define PNS_ERROR_RECORD_INDEX          0x0000B000
#define PNS_ERROR_RECORD_LENGTH         0x0000B100
#define PNS_ERROR_RECORD_SLOT           0x0000B200
#define PNS_ERROR_RECORD_API            0x0000B400

typedef struct t_PNS_RECORD
{
    uint32_t Api;
    uint16_t Slot;
    uint16_t SubSlot;
    uint16_t Index;
    uint32_t MaxDataLen;
    uint32_t DataLen;
    uint32_t Status;
    uint32_t StatusOld;
    uint8_t Data[PNS_MAX_RECORD_LEN];
} PNS_RECORD_T;

typedef struct t_PNS_SUBMODULE_INFO
{
	uint32_t pnApi;
	uint16_t pnSlot;
	uint16_t pnSubSlot;
	uint32_t pnMod;
	uint32_t pnSubMod;
	uint32_t InLen;
	uint32_t OutLen;

} PNS_SUBMODULE_INFO_T;

typedef struct t_PNS_PARAM
{
	char NameOfStation[PNS_MAX_STR_LEN];
	uint32_t NumPnSubModules;
	uint32_t VendorId;
	uint32_t DeviceId;
    char DeviceType[PNS_MAX_STR_LEN];
    char OrderId[PNS_MAX_STR_LEN];
    char SerialNumber[PNS_MAX_STR_LEN];
    uint16_t HwRev;
    uint8_t SwRevPrefix;
    uint16_t SwRev[3];
	uint32_t ObjId;
	uint32_t InputLength;
	uint32_t OutputLength;
    uint32_t NumRecords;
    bool RecordSuccess;
    bool OptionalIdent;
	PNS_SUBMODULE_INFO_T pnSubModules[PNS_MAX_NUM_SUBMODULES];
    PNS_RECORD_T *Records[PNS_MAX_NUM_RECORDS];

} PNS_PARAM_T;

#ifdef __cplusplus
extern "C" {
#endif

int32_t PNS_HandleIndication(CIFX_CHANNEL_T *Channel);
int32_t PNS_AddRecord_v1(CIFX_CHANNEL_T *Channel, PNS_RECORD_T **Record);
int32_t PNS_AddRecord_v2(CIFX_CHANNEL_T* Channel,
    PNS_RECORD_T** Record,
    uint16_t Api,
    uint16_t Slot,
    uint16_t SubSlot,
    uint16_t Index,
    uint32_t Len);
int32_t PNS_RemoveRecords(CIFX_CHANNEL_T *Channel);
int32_t PNS_UpdateRecord(PNS_RECORD_T* Record, 
    void* DataInPort, 
    bool* EnablePort, 
    uint32_t* LenInPort, 
    void* DataOutPort, 
    uint32_t* StatusPort, 
    uint32_t* LenOutPort);
uint32_t PNS_FindRecord(CIFX_CHANNEL_T* Channel, uint32_t Api, uint32_t Slot, uint32_t SubSlot, uint32_t Index, uint32_t* Pos);
int32_t PNS_AcyclicHandler(CIFX_CHANNEL_T* Channel);

#ifdef __cplusplus
}
#endif