#ifndef __MBTCP_SERVER_REMOTE_H
#define __MBTCP_SERVER_REMOTE_H

#include "stdint.h"
#include <map>
#include <list>
#include "mb_def.h"
#include "mbtcp_node.h"
#include "mbtcp_unit.h"

namespace modbusTCP
{
class cServerRemote
{
    private:

    public:

    int RemoteSocket = -1;
    uint32_t ResponseDelay = 0;

    uint16_t ID = 0;
    bool InitDone = false;

    uint32_t IpAddr = 0;
    uint16_t TcpPort = 502;

    void *Node;

    std::list<MB_SEND_FRAME_T> SendQueue;

    void log(Severity l, const char *m, ...);
    int32_t process();
    int32_t init(int RemoteSocket, uint32_t IpAddr, uint16_t TcpPort, bool Swap, uint32_t ResponseDelay);
    int32_t terminate();

    int32_t getDataAddress(uint8_t ID, uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity, void **Address);
    void (*swap)(uint16_t *) = NULL;

    int32_t handleRequest(uint8_t *Load, uint32_t LoadLength);
    int32_t handleRequest01(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);
    int32_t handleRequest02(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);
    int32_t handleRequest03(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);
    int32_t handleRequest04(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);
    int32_t handleRequest05(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);
    int32_t handleRequest06(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);
    int32_t handleRequest15(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);
    int32_t handleRequest16(MB_REQUEST_T *RequestADU, MB_RESPONSE_T *ResponseADU);

    cServerRemote(uint16_t ID);
    ~cServerRemote();
};

} // namespace modbusTCP

#endif
