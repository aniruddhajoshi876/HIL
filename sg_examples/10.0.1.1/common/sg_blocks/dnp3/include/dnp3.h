#ifndef __DNP3_H
#define __DNP3_H

#include "dnp3_root.h"

namespace dnp3
{
    /* Global DNP3 root node */
    extern cRoot Root;

    void ModelExitCb(void*);
    std::string convertIpToString(uint32_t i);
    uint64_t getTime(void);

}

#endif
