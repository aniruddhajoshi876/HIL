#ifndef __MBRTU_SERVER_BLOCK_H
#define __MBRTU_SERVER_BLOCK_H

#include "stdint.h"
#include "sg_printf.h"
#include <cstddef>
#include <stdarg.h>

namespace modbusRTU
{

class cServerBlock
{
  private:
  public:
    uint16_t ID = 0;
    bool InitDone = false;
    uint8_t BlockType = 0;
    void *DataAddress = NULL;
    void *Node = NULL;

    uint16_t DataTable = 0;
    uint16_t DataIndex = 0;
    uint16_t DataQuantity = 0;

    int32_t assignDataAddress(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity);
    int32_t init(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity, bool ByteSwap);
    int32_t read(void *Destination);
    int32_t write(void *Source);
    int32_t terminate();
    void log(Severity l, const char *m, ...);

    void (*swapBytes)(uint16_t *) = NULL;

    cServerBlock(uint16_t ID, void *Parent);
    ~cServerBlock();
};

} // namespace modbusRTU

#endif
