#ifndef __IEC_GOOSE_NODE_H
#define __IEC_GOOSE_NODE_H

#include "stdint.h"
#include <iostream>
#include <cstring>

namespace iec61850
{
class cNodeGoose
{
    private:

    public:

        uint16_t ID;
        void* GooseRoot;

        bool IsFaulty = false;
        uint32_t State = 0;

        virtual int32_t start() = 0;
        virtual int32_t process() = 0;
        virtual int32_t terminate() = 0;
        char* findGooseEthernetLabel(const char* EthTranslateFile, const char* EthLabel);

        cNodeGoose(uint16_t ID);
        virtual ~cNodeGoose() = 0;
};

}

#endif

