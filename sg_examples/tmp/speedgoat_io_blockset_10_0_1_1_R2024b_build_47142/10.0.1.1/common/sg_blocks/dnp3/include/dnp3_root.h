#ifndef __DNP3_ROOT_H
#define __DNP3_ROOT_H

#include <map>
#include "dnp3_station.h"
#include "dnp3_clientstation.h"
#include "dnp3_serverstation.h"

namespace dnp3
{
    class cRoot
    {
    private:

        std::map<uint16_t, dnp3::cStation*> Stations;

        void* MainThread;

    public:

        bool IsFaulty = false;
        uint32_t State = 0;

        void log(Severity l, const char* m, ...);

        bool isStation(uint16_t ID);
        int32_t addStation(uint16_t ID, boolean_t IsClient, cStation** Station);
        int32_t getStation(uint16_t, cStation**);
        int32_t getFirstStation(cStation** Station);

        int32_t init();
        void launch();
        int32_t start();
        int32_t process();
        void stop();
        int32_t terminate();

        cRoot();
        ~cRoot();

    };

}

#endif