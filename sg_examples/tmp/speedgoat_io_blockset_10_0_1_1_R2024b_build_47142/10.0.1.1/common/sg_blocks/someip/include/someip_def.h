#ifndef __SOMIEIP_DEF_H
#define __SOMIEIP_DEF_H

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

#define SOMIEIP_STATION_TYPE_UNDEF  0
#define SOMIEIP_STATION_TYPE_CLIENT 1
#define SOMIEIP_STATION_TYPE_SERVER 2

#define SOMIEIP_STR_LEN 1024

namespace sg_ns_someip
{
} // namespace sg_ns_someip

#pragma pack(pop)

#endif
