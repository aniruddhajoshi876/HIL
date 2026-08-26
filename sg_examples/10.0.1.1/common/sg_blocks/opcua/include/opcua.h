#ifndef __OPCUA_H
#define __OPCUA_H

#include <opcua_root.h>

namespace opcua
{
    /* Global MB root node */
    extern cRoot Root;

    void ModelExitCb(void*);
    uint64_t getTime(void);
}

#endif
