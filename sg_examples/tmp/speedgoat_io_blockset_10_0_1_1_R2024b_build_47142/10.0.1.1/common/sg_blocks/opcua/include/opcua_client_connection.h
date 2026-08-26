#ifndef __OPCUA_CLIENT_CONNECTION_H
#define __OPCUA_CLIENT_CONNECTION_H

#include <limits.h>
#include <netinet/in.h>
#include <opcua_client_transceiver.h>
#include <stdint.h>
#include <wchar.h>
#include <list>

namespace opcua
{
class cClientConnection : public cBase
{
    private:

    public:

		uint16_t ID = 0;
    
        char IpAddr[OPCUA_STR_LEN+1] = {0};
        uint16_t TcpPort = 0;
        char Url[USHRT_MAX + 1] = {0};

        uint8_t SecurityPolicy;
        uint8_t MessageSecurityMode;
        uint8_t UserTokenPolicy;
        char Username[OPCUA_STR_LEN+1] = {0};
        char Password[OPCUA_STR_LEN+1] = {0};
        char Certificate[OPCUA_STR_LEN+1] = {0};
        char PrivateKey[OPCUA_STR_LEN+1] = {0};
        char AppUri[OPCUA_STR_LEN+1] = {0};

        bool IsCom = false;
        uint32_t SessionState = 0;
        uint32_t SecureChannelState = 0;
        uint32_t ConnectStatus = 0;

        uint32_t RequestID = 0;
        uint64_t ConnectTimer = 0;
        bool DoReconnect = false;
        bool DoDisconnect = false;
        bool IsReconnected = false;

        void *OpenClient = NULL;
        void *OpenConfig = NULL;

        void *Logger = NULL;

        void *Station = NULL;


        std::list<cClientTransceiver*> Transceivers;

        int32_t init(char *IpAddr, uint16_t TcpPort, uint8_t SecurityPolicy, uint8_t MessageSecurityMode,
					uint8_t UserTokenPolicy, char *Username, char *Password, char *Certificate, char *PrivateKey, char *AppUri);
        int32_t start();
        int32_t process();
        int32_t terminate();

        int32_t addTransceiver(cClientTransceiver **Transceiver);

        cClientConnection(uint16_t ID);
        ~cClientConnection();
};

    
}

#endif
