#ifndef __IEC_NODE_H
#define __IEC_NODE_H

#include "stdint.h"

namespace iec61850
{
class cNode
{
    private:

    public:

        uint16_t ID;
        void* Root;

        virtual int32_t start(void) = 0;
        virtual int32_t process(void) = 0;
        virtual int32_t terminate(void) = 0;

        cNode(uint16_t ID);
        virtual ~cNode() = 0;
};

}

#endif

