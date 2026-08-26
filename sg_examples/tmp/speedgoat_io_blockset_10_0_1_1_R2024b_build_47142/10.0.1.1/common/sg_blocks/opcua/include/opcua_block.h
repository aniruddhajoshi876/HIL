#ifndef __OPCUA_BLOCK_H
#define __OPCUA_BLOCK_H

#include <opcua_base.h>
#include <stdint.h>
#include <wchar.h>

namespace opcua
{

class cBlock : public cBase
{
    private:
    public:

        uint8_t BlockType = 0;

        void *Station = NULL;
        void *Connection = NULL;

        uint32_t HostFlagsTx = 0;
        uint32_t HostFlagsRx = 0;
        uint32_t DevFlagsTx = 0;
        uint32_t DevFlagsRx = 0;

        cBlock() {};
        virtual ~cBlock() {};
};

}

#endif
