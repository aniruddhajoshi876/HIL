#ifndef __MQTT_CLIENT_CONNECTION_H
#define __MQTT_CLIENT_CONNECTION_H

#include <limits.h>
#include <netinet/in.h>
#include <stdint.h>
#include <wchar.h>
#include <list>

#include <mqtt_base.h>
#include <mqtt_client_transceiver.h>

namespace mqtt
{
class cClientConnection : public cBase
{
    private:

    public:

		uint16_t ID = 0;
    
        uint32_t IpAddr = 0;
        uint16_t TcpPort = 0;
        char IpAddrStr[INET_ADDRSTRLEN + 1] = {0};
        char Url[USHRT_MAX + 1] = {0};
        char Username[USHRT_MAX+1] = {0};
        char Password[USHRT_MAX+1] = {0};

        bool UserAuth = false;
        bool IsCom = false;
        uint32_t SessionState = 0;
        uint32_t SecureChannelState = 0;
        uint32_t ConnectStatus = 0;

        bool ResponsePending = false;

        uint32_t RequestID = 0;
        uint32_t ConnectTimer = 0;
        bool ConnectTimerActive = false;

        void *OpenClient = NULL;
        void *OpenConfig = NULL;

        void *PahoClient = NULL;

        void *Station = NULL;


        std::list<cClientTransceiver*> Transceivers;

        int32_t init(uint32_t IpAddr, uint16_t TcpPort, bool UserAuth, char *Username, char *Password);
        int32_t start();
        int32_t process();
        int32_t terminate();

        int32_t addTransceiver(cClientTransceiver **Transceiver);

        cClientConnection(uint16_t ID);
        ~cClientConnection();
};

    
}

#endif
