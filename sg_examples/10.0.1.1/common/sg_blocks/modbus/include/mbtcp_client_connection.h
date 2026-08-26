#ifndef __MBTCP_CLIENT_CONNECTION_H
#define __MBTCP_CLIENT_CONNECTION_H

#include "mb_def.h"
#include "mbtcp_client_transceiver.h"
#include "stdint.h"
#include <iostream>
#include <string>
#include <vector>

#define MBTCP_CONNECTION_STATUS_CLOSED  0
#define MBTCP_CONNECTION_STATUS_OPENING 1
#define MBTCP_CONNECTION_STATUS_OPENED  2

#define MBTCP_CONNECTION_TIMEOUT 2000 // ms
#define MBTCP_RESPONSE_TIMEOUT   5000 // ms

namespace modbusTCP
{
class cClientConnection
{
  private:
  public:
    void *Node;
    bool InitDone = false;
    bool WantsToConnect = false;
    bool AlwaysReconnect = true;
    bool Stop = false;
    bool ResponsePending = false;
    uint16_t ID = 0;
    uint16_t TransceiverIDs = 1;
    uint16_t NumTransceivers = 0;
    uint32_t RemIpAddr = 0;
    uint16_t RemTcpPort = 0;
    uint32_t PollingInterval = 0;
    uint32_t Status = 0;
    uint32_t NumBlocks = 0;
    uint64_t ConnectTime = 0;
    uint64_t SendTime = 0;
    uint16_t Baton = 1;
    bool Concurrence = true;
    int ClientSocket = -1;
    bool IsSwap = false;

    std::map<uint16_t, cClientTransceiver *> Transceivers;

    void log(Severity l, const char *m, ...);
    int32_t addTransceiver(cClientTransceiver **Transceiver);
    int32_t getTransceiver(uint16_t TransceiverID, cClientTransceiver **Transceiver);
    bool isTransceiver(uint16_t TransceiverID);
    void (*swap)(uint16_t *) = NULL;
    int32_t process();
    int32_t terminate();
    int32_t init(uint32_t RemoteIpAddr, uint16_t RemoteTcpPort, bool Swap, bool NeverDisconnect,
                 bool Concurrence);
    int32_t openConnection();
    int32_t sendRequest(cClientTransceiver *Transceiver);
    int32_t receiveResponse();
    int32_t exchangeData();
    int32_t proveConnection();
    int32_t closeConnection();

    bool getConnectionStatus(void);

    cClientConnection(uint16_t connectionID);
    ~cClientConnection();

    bool buildReq01(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
    bool buildReq02(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
    bool buildReq03(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
    bool buildReq04(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
    bool buildReq05(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
    bool buildReq06(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
    bool buildReq15(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
    bool buildReq16(cClientTransceiver *Transceiver, MB_REQUEST_T *RequestADU, uint16_t *PduLen);
};

} // namespace modbusTCP

#endif
