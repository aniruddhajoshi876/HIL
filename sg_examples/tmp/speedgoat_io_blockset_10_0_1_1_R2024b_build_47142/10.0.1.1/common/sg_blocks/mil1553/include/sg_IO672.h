#ifndef SG_IO672_H
#define SG_IO672_H

#include <stddef.h> 
#include <stdlib.h> 
#include <stdint.h>

#include "simstruc.h" 

#ifdef  MATLAB_MEX_FILE
    #include "mex.h"
#else
    #include "busapi.h"
#endif

#define VENDOR_ID         0x13c6   // Condor Engineering
#define DEVICE_ID         0x1553   // QPCI-1553

#define MAX_CHANNEL       (4)

#define SG_BLOCK_TYPE_IO672_INIT        6721
#define SG_BLOCK_TYPE_IO672_RTINIT      6722
#define SG_BLOCK_TYPE_IO672_BCSEND      6723
#define SG_BLOCK_TYPE_IO672_BM          6724
#define SG_BLOCK_TYPE_IO672_RTSEND      6725
#define SG_BLOCK_TYPE_IO672_RTRECEIVE   6726

#ifndef  MATLAB_MEX_FILE
    typedef struct sg_IO672_block_T
    {
        BT_UINT cardnum;
        API_BC_MBUF *bc_msg;
        API_BM_MBUF *bm_msg;
    } sg_IO672_block_t;
#endif

#endif
