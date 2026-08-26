// Copyright 2006-2026 Speedgoat GmbH

#ifndef z02a5cc859c
#define z02a5cc859c
#ifdef __cplusplus
extern"C"{
#endif
#include "sg_io623_flexray_type.h"
#include <stdlib.h>
enum z52c9b912eb{z2e11a86afc=(0x950+7591-0x26f6),z80fa3fc24e=(0x5db+7286-0x224f),z2f65385f15=(0x62b+998-0xa0e)};enum z9cdbfae8ee{z40117edf52,z85776ccfc7,z5b2c4b330a,z6c1555506c,zd5d28c1603,z0094aff6d5,z71312cee6c,z61565a53df,z0cf33d227f,z06586ff471,z9cacb68f15,zec3709d24c,z788d4e96bf,zc2593316a1,z0f1732f1a0};typedef struct{int frameId;int channels;int ignoreNullFrames;}Io623_UnpackFilter;typedef struct{int numPorts;void**addrs;int*types;}Io623_OutputPortAssignment;extern void io623_unpackFrame(Io623_UnpackFilter*filter,Io623_FlexrayFrame*z41711266a5,int z1bfcb41b43,Io623_OutputPortAssignment*z17f3ceba5d);
#ifdef __cplusplus
}
#endif
#endif  

