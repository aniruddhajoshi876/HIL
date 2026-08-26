#ifndef __MBS_API_H
#define __MBS_API_H

#include "stdint.h"
#include "sg_common.h"

#define MBS_AREA_COIL			1
#define MBS_AREA_DISCRETE		2
#define MBS_AREA_HOLDING		3
#define MBS_AREA_INPUT			4

typedef struct t_MBS_PARAM
{
	bool EnaMapFC1FC3;    // Enable mapping for FC1 and FC3
	bool EnaDHCP;         // Enable DHCP
	bool EnaBootP;        // Enalbe BootP
	uint8_t ProtMode;       // Protocol mode
	uint32_t SysFlgs;       // System flags
	uint32_t WdgTime;       // Watchdog time
	uint32_t OpenSrvSokt;   // Number of sockets to open
	uint32_t  DataSwap;     // Swap Data or not
	uint32_t  AnsTimeout; // Internal Timeout
	uint32_t  OmbOpenTime;  // Time to close Socket
	uint32_t  SndTimeout;   // Parameter for TCP-Task
	uint32_t  ConTimeout;   // Parameter for TCP-Task
	uint32_t  CloseTimeout; // Parameter for TCP-Task
	char IPAdr[16];
	char Netmask[16];
	char Gateway[16];

} MBS_PARAM_T;

int32_t MBS_MsgModeIndicationHandling(CIFX_CHANNEL_T *Channel);
void MBS_BlkInFC1andFC2(CIFX_CHANNEL_T *Channel, uint8_t type, uint32_t startAdr, uint32_t qty, uint8_t *pDataIn);
void MBS_BlkInFC3andFC4(CIFX_CHANNEL_T *Channel, uint8_t type, uint32_t startAdr, uint32_t qty, uint16_t *pDataIn);
void MBS_BlkOutFC1andFC2(CIFX_CHANNEL_T *Channel, uint8_t type, uint32_t startAdr, uint32_t qty, uint8_t *pDataOut);
void MBS_BlkOutFC3andFC4(CIFX_CHANNEL_T *Channel, uint8_t type, uint32_t startAdr, uint32_t qty, uint16_t *pDataOut);

uint32_t MBS_WriteBit(CIFX_CHANNEL_T* Channel, uint8_t Area, uint32_t Offset, uint32_t Quantity, uint8_t* Source);
uint32_t MBS_ReadBit(CIFX_CHANNEL_T* Channel, uint8_t Area, uint32_t Offset, uint32_t Quantity, uint8_t* Destination);
uint32_t MBS_WriteWord(CIFX_CHANNEL_T* Channel, uint8_t Area, uint32_t Offset, uint32_t Quantity, uint16_t* Source);
uint32_t MBS_ReadWord(CIFX_CHANNEL_T* Channel, uint8_t Area, uint32_t Offset, uint32_t Quantity, uint16_t* Destination);

#endif