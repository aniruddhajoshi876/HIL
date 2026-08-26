#ifndef __TRDP_H
#define __TRDP_H

#include "trdp_root.h"

namespace ns_sg_trdp
{
    /* Global MB root node */
    extern cRoot Root;
    extern uint64_t getMicroCounter(void);
}

extern ns_sg_trdp::cRoot *SgTrdp;

#endif
