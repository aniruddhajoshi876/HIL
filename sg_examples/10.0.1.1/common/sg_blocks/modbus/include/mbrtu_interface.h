#ifndef __MBRTU_INTERFACE_H
#define __MBRTU_INTERFACE_H

#include "stdint.h"
#include <map>

#include "mb_def.h"

namespace modbusRTU
{
class cInterface
{
    private:

    public:
 
    MB_SERIAL_INFO_T SerialInfo;

    uint8_t RxBuffer[MB_RTU_MAX_BUF_SIZE] = {0};
    uint8_t TxBuffer[MB_RTU_MAX_BUF_SIZE] = {0};

    uint32_t RxBufPos = 0;
    uint32_t RxBufEnd = 0;
    uint32_t TxBufLen = 0;

    uint32_t NumTimeouts = 0;
    uint32_t RxTotalNumBytes = 0;
    uint32_t RxTotalNumIncomplete = 0;
    uint32_t RxTotalNumInvalid = 0;
    uint32_t RxTotalNumValid = 0;
    uint32_t TxTotalNumBytes = 0;
    uint32_t TxTotalNumValid = 0;

    void *Root;

    bool Stop = false;
    bool InitDone = false;
    bool ExtRespPending = true;
    uint16_t ID;
    uint8_t State = 0;
    
    void log(Severity l, const char *m, ...);
    int32_t sendBuffer();
    virtual int32_t process() = 0;
    virtual int32_t terminate() = 0;

    cInterface(uint16_t ID);
    virtual ~cInterface() = 0;
};

}

#endif

