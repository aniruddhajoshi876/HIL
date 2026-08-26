#ifndef __MQTT_TRANSCEIVER_H
#define __MQTT_TRANSCEIVER_H

#include <mqtt_base.h>
#include <stdint.h>
#include <wchar.h>

namespace mqtt
{

class cTransceiver : public cBase
{
    private:
    public:

        uint8_t Type = 0;

        void *Station = NULL;
        void *Connection = NULL;

        uint32_t HostFlagsTx = 0;
        uint32_t HostFlagsRx = 0;
        uint32_t DevFlagsTx = 0;
        uint32_t DevFlagsRx = 0;

        cTransceiver() {};
        virtual ~cTransceiver() {};
};

}

#endif
