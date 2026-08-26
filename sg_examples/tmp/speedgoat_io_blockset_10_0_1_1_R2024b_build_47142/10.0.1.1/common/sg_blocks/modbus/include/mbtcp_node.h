#ifndef __MBTCP_NODE_H
#define __MBTCP_NODE_H

#include "stdint.h"
#include <map>

namespace modbusTCP
{
class cNode
{
    private:



    public:

        uint16_t ID;
        void* Root;

        uint8_t State = 0;
        bool InitDone = false;

        virtual int32_t process() = 0;
        virtual int32_t terminate() = 0;

        cNode(uint16_t ID);
        virtual ~cNode() = 0;
};

}

#endif

