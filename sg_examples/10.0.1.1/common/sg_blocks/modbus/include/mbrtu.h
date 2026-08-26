#ifndef __MBRTU_H
#define __MBRTU_H

#include "mb_license.h"
#include "mbrtu_root.h"

namespace modbusRTU
{
    /* Global MB root interface */
    extern cRoot Root;
    extern bool IsTrial;

    uint32_t getTime(void);
    void swapNone(uint16_t *Value);
    void swap16(uint16_t *Value);
    uint16_t calculate16CRC(uint32_t Length, uint8_t *Data);
    void outputMessageDump(uint8_t *Message, uint32_t Length);

    int32_t extractRequest(cInterface *Interface, uint8_t *Data, uint32_t DataLen);
    int32_t extractResponse(cInterface *Interface, uint8_t *Data, uint32_t DataLen);
}

#endif
