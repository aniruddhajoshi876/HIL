#ifndef __DNP3_STATION_H
#define __DNP3_STATION_H

#include "stdint.h"

namespace dnp3
{
class cStation
{
    private:

    public:

        uint16_t ID;
        void* Parent;

        bool IsFaulty = false;
        uint32_t State = 0;

        virtual int32_t start() = 0;
        virtual int32_t process() = 0;
        virtual int32_t terminate() = 0;

        cStation(uint16_t ID);
        virtual ~cStation() = 0;
};

}

#endif

