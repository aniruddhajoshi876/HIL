#ifndef __MQTT_H
#define __MQTT_H

#include <mqtt_root.h>

namespace mqtt
{
    /* Global MB root node */
    extern cRoot Root;

    void ModelExitCb(void*);
    uint64_t getTime(void);
}

#endif
