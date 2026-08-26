#ifndef __MBTCP_CLIENT_NODE_H
#define __MBTCP_CLIENT_NODE_H

#include "stdint.h"
#include "mb_def.h"
#include "mbtcp_node.h"
#include "mbtcp_client_connection.h"

namespace modbusTCP
{
class cClientNode : public cNode
{
    private:

    public:
    
        bool Stop = false;

        uint32_t LocalIpAddr = 0;
        uint16_t LocalTcpPort = 0;

        uint32_t NumBlocks = 0;

        uint16_t NumConnection = 0;

        std::map <uint16_t, cClientConnection*> Connections;

        void log(Severity l, const char *m, ...);
        int32_t addConnection(uint16_t ConnectionID, cClientConnection **Connection);
        int32_t getConnection(uint16_t ConnectionID, cClientConnection** Connection);
        int32_t getFirstConnection(cClientConnection** Connection);
        bool isConnection(uint16_t ConnectionID);

        int32_t process();
        int32_t terminate();
        int32_t init(uint32_t LocalIpAddr, uint16_t LocalTcpPort);

        cClientNode(uint16_t ID) : cNode(ID) {};
        ~cClientNode();
};

} // namespace modbusTCP

#endif
