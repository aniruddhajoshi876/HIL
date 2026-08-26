#ifndef __MBTCP_H
#define __MBTCP_H

#include "mbtcp_root.h"

namespace modbusTCP
{
/* Global MB root node */
extern cRoot Root;
uint64_t getTime(void);
void swapTCP_None(uint16_t *Value);
void swapTCP_16(uint16_t *Value);
void outputMessageDump(uint8_t *Message, uint32_t Length);

} // namespace modbusTCP

#endif
