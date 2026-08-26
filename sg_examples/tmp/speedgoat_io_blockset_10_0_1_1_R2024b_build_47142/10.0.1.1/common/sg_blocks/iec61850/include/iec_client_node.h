#ifndef __IEC_CLIENT_NODE_H
#define __IEC_CLIENT_NODE_H

#include "sg_printf.h"
#include "stdint.h"
#include "iec_def.h"
#include "iec_node.h"
#include "iec_client_connection.h"

namespace iec61850
{
class cClientNode : public cNode
{
    private:

    public:
    
        bool IsFaulty = false;
        uint32_t State = 0;

        uint32_t LocalIpAddr = 0;
        uint16_t LocalTcpPort = 0;

        /***/
        unsigned int memory = 0;
        /***/

        uint32_t NumBlocks = 0;

        bool IsCom = false;
        uint16_t NumConnection = 0;

        std::map <uint8_t, cClientConnection*> Connections;

        void log(Severity l, const char *m, ...);

        int32_t addConnection(uint8_t ConnectionID, cClientConnection **Connection);
        int32_t getConnection(uint8_t ConnectionID, cClientConnection** Connection);
        bool isConnection(uint8_t ConnectionID);


        int32_t process();
        int32_t init(uint32_t LocalIpAddr, uint16_t LocalTcpPort);
        int32_t start();

        int32_t terminate(void);
        cClientNode(uint16_t ID) : cNode(ID) {};
        ~cClientNode();
};

    
}

#endif
