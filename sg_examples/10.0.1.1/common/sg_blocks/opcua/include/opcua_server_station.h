#ifndef __OPCUA_SERVER_STATION_H
#define __OPCUA_SERVER_STATION_H

#include <opcua_server_node.h>
#include <opcua_station.h>
#include <stddef.h>
#include <stdint.h>
#include <list>

namespace opcua
{
typedef struct EndpointProps_t
{
	uint32_t IsActive;
	uint32_t SecurityMode;
} OPCUA_ENDPOINT_PROPS_T;

class cServerStation : public cStation
{
    private:

    public:
    
        uint32_t IpAddr = 0;
        uint16_t TcpPort = 0;
        uint32_t KeepAlive = 0;
        uint32_t NumNodes = 0;
        uint32_t NumConnections = 0;

        OPCUA_ENDPOINT_PROPS_T *Endpoints;
        uint8_t UserTokenPolicy;
        uint32_t NumUsers;
        uint32_t NumSpaces;
        char Username[OPCUA_STR_LEN+1] = {0};
        char Password[OPCUA_STR_LEN+1] = {0};
        void *Logins = NULL;
        char Certificate[OPCUA_STR_LEN+1] = {0};
        char PrivateKey[OPCUA_STR_LEN+1] = {0};
        char TrustList[OPCUA_STR_LEN+1] = {0};
        char AppUri[OPCUA_STR_LEN+1] = {0};

        bool IsCom = false;
        bool IsSwap = false;

        void *OpenServer = NULL;
        void *Logger = NULL;

        /* List of UA nodes */
        std::list<cServerNode*> Nodes;

        int32_t init(uint32_t IpAddr, uint16_t TcpPort, uint32_t KeepAlive, bool Swap, OPCUA_ENDPOINT_PROPS_T *Endpoints,
        		uint8_t UserTokenPolicy, uint32_t NumUsers, char **Usernames, char **Passwords, char *Certificate, char *PrivateKey, char *TrustList, char *AppUri, uint32_t NumSpaces);
        int32_t start();
        int32_t process();
        int32_t terminate();

        int32_t addNode(cServerNode **Node);
        uint32_t getNumConnections();

        cServerStation(uint16_t ID);
        ~cServerStation();
};


    
}

#endif
