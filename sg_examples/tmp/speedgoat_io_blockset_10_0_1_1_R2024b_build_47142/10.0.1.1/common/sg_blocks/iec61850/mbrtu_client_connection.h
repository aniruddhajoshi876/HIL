#ifndef __MBRTU_CLIENT_CONNECTION_H
#define __MBRTU_CLIENT_CONNECTION_H

#include "../common/mb_def.h"
#include "stdint.h"
#include <iostream>
#include "mbrtu_transceiver.h"
#include <string>
#include <vector>

namespace modbusRTU
{
    class cClientConnection
    {
    private:

    public:

    uint16_t Transaction_ID = 0;

    void* Interface;
    bool IsInit = false;
    bool IsConnected = false;
    bool WantsToConnect = false;
    bool AlwaysReconnect = true;
    const bool IsClient = true;
    bool Next_TRX = false;
    bool pending = false;

    bool Stop = false;
    uint16_t ConnectionID = 0;
    uint16_t TransceiverIDs = 1;
    uint16_t NumTransceivers = 0;

    uint32_t IpAddr = 0;
    uint16_t TcpPort = 0;
    uint32_t RemIpAddr = 0;
    uint16_t RemTcpPort = 0;
    uint32_t ResponseTimeout = 0;
    uint32_t ResponseIntervall = 0;
    uint32_t Timeout = 0;

    uint32_t NumBlocks = 0;

    std::list<MB_SEND_FRAME_T> SendQueue;

    int ClientSocket = -1;
    int RemoteSocket = -1;

    bool IsCom = false;
    bool IsSwap = false;

    std::map <uint16_t, cClientTransceiver*> Transceivers;

    int32_t addTransceiver(cClientTransceiver **Transceiver);
    int32_t getTransceiver(uint16_t TransceiverID, cClientTransceiver** Transceiver);
    int32_t getFirstTransceiver(cClientTransceiver** Transceiver);
    bool isTransceiver(uint16_t TransceiverID);

    int32_t removeRemote(cClientConnection *Connection);
    void (*swap)(uint16_t*) = NULL;

    int32_t process();
    int32_t init(uint32_t RemoteIpAddr, uint16_t RemoteTcpPort, bool Swap, bool NeverDisconnect);
    int32_t listenSocket();
    inline void buildRequestHeader(MB_REQUEST_T *RequestADU, uint8_t FunctionCode, uint16_t UnitID);
    int32_t requestConnection();
    int32_t trx_send(const uint16_t TransceiverID, uint8_t FunctionCode, uint16_t UnitID, uint16_t Address, uint16_t Quantity, void* Value);
    int32_t trx_receive(const uint16_t TransceiverID, void* Value, cClientTransceiver* Transceiver, std::map<uint16_t, cClientTransceiver*>::iterator iterB);

    uint32_t pendingConnection(uint32_t flag, uint32_t* Timeout);
    int32_t removeConnection();
    uint32_t getTime(void);

    bool getConnectionStatus(void);
    bool getConnectRequest(void);

    cClientConnection(uint16_t connectionID);
        ~cClientConnection();
    int32_t reopenConnection(void);

    bool buildReq01(MB_REQUEST_01_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t Quantity, uint16_t *PduLen);
    bool buildReq02(MB_REQUEST_02_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t Quantity, uint16_t *PduLen);
    bool buildReq03(MB_REQUEST_03_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t Quantity, uint16_t *PduLen);
    bool buildReq04(MB_REQUEST_04_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t Quantity, uint16_t *PduLen);
    bool buildReq05(MB_REQUEST_05_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t *PduLen, void *Value);
    bool buildReq06(MB_REQUEST_06_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t *PduLen, void *Value);
    bool buildReq15(MB_REQUEST_15_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t Quantity, uint16_t *PduLen, void *Value);
    bool buildReq16(MB_REQUEST_16_T *RequestPDU, MB_REQUEST_T *RequestADU, uint8_t FunctionCode,
                    uint16_t Address, uint16_t Quantity, uint16_t *PduLen, void *Value);
};

} // namespace modbusRTU

#endif
