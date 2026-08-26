#ifndef __MBRTU_CLIENT_CONNECTION_H
#define __MBRTU_CLIENT_CONNECTION_H

#include "mb_def.h"
#include "mbrtu_client_transceiver.h"
#include "stdint.h"
#include <cstdint>

namespace modbusRTU
{
class cClientConnection
{
  private:
    bool InitDone = false;

    uint16_t Baton = 0;

    std::vector<cClientTransceiver *> Transceivers;
    void log(Severity l, const char *m, ...);
    
    void passBaton();

  public:
    uint8_t ID = 0;
    void *Interface;

    int32_t init();
    int32_t terminate();
    int32_t process(bool AllowedToSend);
    int32_t addTransceiver(cClientTransceiver **Transceiver);
    int32_t handleResponse(MB_RESPONSE_T *Response);

    bool isWaiting();
    void stopWaiting();

    cClientConnection(uint8_t ID, void *Parent);
    ~cClientConnection();
};

} // namespace modbusRTU

#endif
