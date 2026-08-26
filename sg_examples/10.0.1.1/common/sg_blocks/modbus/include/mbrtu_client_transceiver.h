#ifndef __MBRTU_CLIENT_TRANSCEIVER_H
#define __MBRTU_CLIENT_TRANSCEIVER_H

#include "mb_def.h"
#include "mbrtu_interface.h"
#include "stdint.h"
#include <cstdint>
#include <list>
#include <map>

namespace modbusRTU
{
class cClientTransceiver
{
  private:
  public:
    bool InitDone = false;
    uint16_t ID;

    uint8_t NodeID = 0;
    uint8_t FunctionCode = 0;
    uint16_t Index = 0;
    uint16_t Quantity = 0;
    uint8_t ByteCount = 0;

    uint8_t ErrorCode = 0;
    uint8_t ExceptionCode = 0;

    bool EnaSend = true;
    bool WantsToSend = false;
    bool WaitingOnResponse = false;
    bool EnableUpdateOnChange = false;
    uint8_t UpdateHappened = 0;
    uint32_t RequestTimer = 0;
    uint32_t ResponseTimer = 0;
    uint32_t PollingInterval = 0;
    uint32_t NumBytes = 0;

    void *DataAddress = NULL;

    uint8_t TxBuffer[MB_RTU_MAX_MESSAGE_LEN] = {0};

    void (*swapBytes)(uint16_t *) = NULL;

    int32_t init(uint8_t FunctionCode, uint16_t UnitID, bool EnaSend, uint32_t PollingInterval,
                 uint16_t Index, uint16_t Quantity, bool UpdateOnChange, bool ByteSwap);
    int32_t process(bool AllowedToSend);
    int32_t terminate();

    void log(Severity l, const char *m, ...);

    int32_t sendRequest();
    int32_t sendRequest01();
    int32_t sendRequest02();
    int32_t sendRequest03();
    int32_t sendRequest04();
    int32_t sendRequest05();
    int32_t sendRequest06();
    int32_t sendRequest15();
    int32_t sendRequest16();

    int32_t handleResponse(MB_RESPONSE_T *Response);
    int32_t handleResponse01(MB_RESPONSE_01_T *Response);
    int32_t handleResponse02(MB_RESPONSE_02_T *Response);
    int32_t handleResponse03(MB_RESPONSE_03_T *Response);
    int32_t handleResponse04(MB_RESPONSE_04_T *Response);
    int32_t handleResponse05(MB_RESPONSE_05_T *Response);
    int32_t handleResponse06(MB_RESPONSE_06_T *Response);
    int32_t handleResponse15(MB_RESPONSE_15_T *Response);
    int32_t handleResponse16(MB_RESPONSE_16_T *Response);
    int32_t handleError(MB_RESPONSE_ERROR_T *Response);

    int32_t transceive(void *BlockPort);
    int32_t sendMessage(uint8_t *Message, uint32_t Length);

    void *Connection;

    cClientTransceiver(uint16_t ID, void *Parent);
    ~cClientTransceiver();
};

} // namespace modbusRTU

#endif
