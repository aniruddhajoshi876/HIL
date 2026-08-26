#ifndef __IEC_SV_NODE_H
#define __IEC_SV_NODE_H

#include "stdint.h"
#include <iostream>
#include <cstring>

namespace iec61850
{
class cNodeSV
{
    private:

    public:

		bool running = false;

        uint16_t ID;
        void* SVRoot;

        bool IsFaulty = false;
        uint32_t State = 0;

        virtual int32_t start() = 0;
        virtual int32_t process() = 0;
        virtual int32_t terminate() = 0;
        char* findSVEthernetLabel(const char* EthTranslateFile, const char* EthLabel);

        cNodeSV(uint16_t ID);
        virtual ~cNodeSV() = 0;
};

}

#endif

