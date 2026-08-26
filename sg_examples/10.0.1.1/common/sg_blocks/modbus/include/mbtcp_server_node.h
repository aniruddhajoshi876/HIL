#ifndef __MBTCP_SERVER_NODE_H
#define __MBTCP_SERVER_NODE_H

#include "stdint.h"
#include "mb_def.h"
#include "mbtcp_server_remote.h"
#include "mbtcp_unit.h"
#include "mbtcp_server_fi.h"

namespace modbusTCP
{
class cServerNode : public cNode
{
    private:

    public:
    
        bool Stop = false;

        uint32_t IpAddr = 0;
        uint16_t TcpPort = 502;
        uint32_t KeepAlive = 0;

        uint32_t NumBlocks = 0;

        int ServerSocket = -1;

        bool IsSwap = false;
        uint16_t NumRemote = 0;
        uint32_t ResponseDelay = 0;

        std::map <uint16_t, cUnit*> Units;
        std::map <uint16_t, cServerRemote*> Remotes;

        /* Vector of fault insertion blocks */
        std::vector<cServerFi *> Fis;

        int32_t addFi(cServerFi **Fi);
        int32_t runFis(uint32_t IpAddr, uint32_t Port, bool *Accepted);
        int32_t runFis(MB_REQUEST_T *RequestADU, MB_SEND_FRAME_T *TxFrame, bool *DoSend);

        int32_t addUnit(uint8_t ID, cUnit **Unit);
        int32_t getUnit(uint8_t ID, bool Redirect255, cUnit** Unit);
        int32_t getFirstUnit(cUnit** Unit);
        bool isUnit(uint8_t ID);

        void log(Severity l, const char *m, ...);
        int32_t addRemote(cServerRemote **Remote);
        int32_t removeRemote(cServerRemote *Remote);
        int32_t removeRemoteAll();

        int32_t process();
        int32_t terminate();
        int32_t init(uint32_t LocalIpAddr, uint16_t LocalTcpPort, uint32_t KeepAlive, bool Swap, uint32_t ResponseDelay);
        int32_t listenSocket();
        int32_t acceptRemote();

        int32_t getDataAddress(uint8_t ID, uint16_t DataTable, uint16_t DataIndex, uint16_t DataQuantity, void **Address);

        cServerNode(uint16_t ID) : cNode(ID) {};
        ~cServerNode();
};
} //namespace modbusTCP

#endif
