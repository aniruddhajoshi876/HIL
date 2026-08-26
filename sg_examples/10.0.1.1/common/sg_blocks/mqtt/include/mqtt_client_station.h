#ifndef __MQTT_CLIENT_STATION_H
#define __MQTT_CLIENT_STATION_H

#include <mqtt_client_connection.h>
#include <mqtt_station.h>
#include <stdint.h>
#include <map>

namespace mqtt
{
class cClientStation : public cStation
{
    private:

    public:
    
        uint32_t IpAddr = 0;
        uint32_t localIp = 0;
        uint16_t TcpPort = 0;
        char ClientIdentifier[USHRT_MAX + 1] = {0};

        /* List of connections */
        std::map<uint16_t, cClientConnection*> Connections;

        int32_t init(char *ClientIdentifier, uint32_t IpAddr, uint16_t TcpPort);
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
