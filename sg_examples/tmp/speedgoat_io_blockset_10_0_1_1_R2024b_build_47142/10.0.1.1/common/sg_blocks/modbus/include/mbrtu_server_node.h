#ifndef __MBRTU_NODE_H
#define __MBRTU_NODE_H

#include "mb_def.h"
#include "mbrtu_interface.h"
#include "mbrtu_server_block.h"
#include "sg_printf.h"
#include "stdint.h"
#include <list>
#include <vector>

namespace modbusRTU
{
class cNode
{
  private:
  public:
    bool InitDone = false;

    uint16_t ID = 0;

    std::vector<cServerBlock *> Blocks;

    uint8_t *Coils = NULL;
    uint8_t *DiscreteInputs = NULL;
    uint16_t *HoldingRegisters = NULL;
    uint16_t *InputRegisters = NULL;

    uint16_t NumCoils = 0;
    uint16_t NumDiscreteInputs = 0;
    uint16_t NumHoldingRegisters = 0;
    uint16_t NumInputRegisters = 0;

    uint8_t TxBuffer[MB_RTU_MAX_MESSAGE_LEN] = {0};

    void log(Severity l, const char *m, ...);
    int32_t init(uint16_t NumCoil, uint16_t NumDiscrete, uint16_t NumHolding, uint16_t NumInput,
                 bool ByteSwap);
    int32_t terminate();
    int32_t addBlock(uint8_t BlockType, cServerBlock **Block);
    int32_t getDataAddress(uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity,
                           void **Address);
    int32_t process();
    int32_t sendMessage(uint8_t *Message, uint32_t Length);
    int32_t sendErrorMessage(uint8_t FunctionCode, uint8_t ErrorCode, uint8_t ExceptionCode);

    int32_t handleRequest(MB_REQUEST_T *Request);
    int32_t handleRequest01(MB_REQUEST_01_T *Request);
    int32_t handleRequest02(MB_REQUEST_02_T *Request);
    int32_t handleRequest03(MB_REQUEST_03_T *Request);
    int32_t handleRequest04(MB_REQUEST_04_T *Request);
    int32_t handleRequest05(MB_REQUEST_05_T *Request);
    int32_t handleRequest06(MB_REQUEST_06_T *Request);
    int32_t handleRequest15(MB_REQUEST_15_T *Request);
    int32_t handleRequest16(MB_REQUEST_16_T *Request);

    void *Interface;

    cNode(uint16_t ID);
    ~cNode();
};

} // namespace modbusRTU

#endif
