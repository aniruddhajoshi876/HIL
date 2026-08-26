#ifndef __DNP3_CLIENTSTATION_H
#define __DNP3_CLIENTSTATION_H

#include "stdint.h"
#include <map>
#include "dnp3_station.h"
#include "dnp3_connection.h"

namespace dnp3
{
    class cClientStation : public cStation
    {

    private:

        /* List of connection */
        std::map<uint16_t, dnp3::cConnection*> Connections;

    public:   

        uint32_t LocalIpAddr;

        void log(Severity l, const char* m, ...);

        bool isRemoteRegistered(uint16_t);
        int32_t addConnection(uint16_t, cConnection**);
        int32_t getConnection(uint16_t, cConnection**);
        int32_t getStationStatus(uint8_t* Status, uint16_t NumStations);

        int32_t init(uint32_t IpAddr);
        int32_t start();
        int32_t process();
        int32_t terminate();

        cClientStation(uint16_t ID) : cStation(ID) {};
        ~cClientStation();  

    };

}

#endif
