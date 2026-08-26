#ifndef __OPCUA_CLIENT_STATION_H
#define __OPCUA_CLIENT_STATION_H

#include <opcua_client_connection.h>
#include <opcua_station.h>
#include <stdint.h>
#include <map>

namespace opcua
{
class cClientStation : public cStation
{
    private:

    public:
    
        uint32_t IpAddr = 0;
        uint16_t TcpPort = 0;

        /* List of connections */
        std::map<uint16_t, cClientConnection*> Connections;

        int32_t init(uint32_t IpAddr, uint16_t TcpPort);
        int32_t start();
        int32_t process();
        int32_t terminate();

		bool isConnection(uint16_t ID);
		int32_t addConnection(uint16_t ID, cClientConnection** Connection);
		int32_t getConnection(uint16_t, cClientConnection**);


        cClientStation(uint16_t ID);
        ~cClientStation();
};

}

#endif
