#ifndef __PLS_API_H
#define __PLS_API_H

#include "stdint.h"
#include "sg_common.h"

typedef struct t_PLS_PARAM
{
	bool DisaPDOMappingVerChk;
	bool EnaDelAppObjs;
	bool EnaCfgDefObjs;
	bool DisaHostTrigOutputDataXchg;
	bool DisaHostTrigInputDataXchg;
	uint8_t NodeId;
	uint8_t BusStart;
	uint8_t IOState;
	uint16_t ProcessDataInputSize;
	uint16_t ProcessDataOutputSize;
	uint32_t WdgTime;
	uint32_t VenId;
	uint32_t ProdCode;
	uint32_t RevNo;
	uint32_t SN;
	char DNSNodeName[33];
	char Gateway[16];

} PLS_PARAM_T;

#endif