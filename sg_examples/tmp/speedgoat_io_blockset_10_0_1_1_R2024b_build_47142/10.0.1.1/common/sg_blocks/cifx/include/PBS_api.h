#ifndef __EIS_API_H
#define __EIS_API_H

#include "stdint.h"
#include "sg_common.h"

/*
*   Length of the alarm sequence mode array
*/
#define IO642_WARM_PARAM_SEQ_MODE_NO_LEN 2

/*
*   Standard length for the IO642 configuration data array
*/
#define IO642_WARM_PARAM_CONFIG_DATA_LEN 244

typedef struct t_PBS_PARAM
{
	bool enaDPV1;
	bool IsSyncSup;
	bool IsFreezeSup;
	bool IsFailSaveSup;
	bool enaAlarmSAP50Deact;
	bool enaIODataSwap;
	bool enaAutoCfg;
	bool enaAdrCngNotAlwd;
    bool firstConnectionAttempt;
	uint8_t Bdr;
	uint8_t CfgLen;
	uint8_t Res[IO642_WARM_PARAM_SEQ_MODE_NO_LEN];
	uint8_t CfgData[IO642_WARM_PARAM_CONFIG_DATA_LEN];
	uint16_t IdentNo;
	uint32_t IOStat;
	uint32_t WdgTime;
	uint8_t BusAdr;

} PBS_PARAM_T;

int32_t PBS_HandleIndication(CIFX_CHANNEL_T *Channel);
int32_t PBS_HandleIndication_RT(CIFX_CHANNEL_T *Channel);

#endif