#ifndef __TRDP_DEF_H
#define __TRDP_DEF_H

#include <stdint.h>

#pragma pack(push, 1)

#ifndef MATLAB_MEX_FILE

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif

#define TRDP_BLOCK_TYPE_UNDEF           0x00000000
#define TRDP_BLOCK_TYPE_PD_SUBSCRIBE    0x00000004
#define TRDP_BLOCK_TYPE_PD_PUBLISH      0x00000005
#define TRDP_BLOCK_TYPE_MD_LISTEN       0x00000006
#define TRDP_BLOCK_TYPE_MD_REQUEST      0x00000007

namespace ns_sg_trdp
{

}

#pragma pack(pop)

#endif
