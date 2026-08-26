#ifndef __ECATSIM_PUBLIC_H
#define __ECATSIM_PUBLIC_H

#include "ecatsim_root.h"
#include <stdint.h>

#pragma pack(push, 1)

namespace sg_ns_ecatsim
{
/* Global MB root node */
extern cRoot Root;
extern cRoot *SgEcatSim;
uint64_t getMilliCounter(void);
} // namespace sg_ns_ecatsim

#pragma pack(pop)

#endif
