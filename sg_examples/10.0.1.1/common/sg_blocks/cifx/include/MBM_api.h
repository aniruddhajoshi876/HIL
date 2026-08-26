#ifndef __MBS_API_H
#define __MBS_API_H

#include "stdint.h"
#include "sg_common.h"

#define MBM_MAX_NUM_SERVER			16
#define MBM_MAX_NUM_CMD				256
#define MBM_DIRECTION_READ			0
#define MBM_DIRECTION_WRITE			1

typedef struct t_MBM_DIAG
{
    uint8_t ConfigSlaves[16];
    uint8_t ActiveSlaves[16];
    uint8_t DiagSlaves[16];
    uint8_t CommandDiag[32];

} MBM_DIAG_T;

typedef struct t_MBM_CMD
{
	uint32_t	Ipaddr;
	uint32_t	Unit;
	uint32_t	Code;
	uint32_t	Addr;
	uint32_t	Qty;
	int32_t	    Time;
	uint32_t	Offset;
	uint32_t	Len;
    uint32_t    Rw;
} MBM_CMD_T;


typedef struct t_MBM_PARAM
{
	bool DHCP;
	bool BootP;
	uint32_t IPaddr;
	uint32_t Netmask;
	uint32_t Gateway;
	uint32_t CmdDelay;
	uint32_t Swap;
	uint32_t CmdCRC;
	uint32_t NumOfCommands;
    uint32_t ReadLen;
    uint32_t WriteLen;
    uint32_t DiagOffset;

    MBM_DIAG_T Diag;

	MBM_CMD_T Cmd[MBM_MAX_NUM_CMD];

} MBM_PARAM_T;

#endif