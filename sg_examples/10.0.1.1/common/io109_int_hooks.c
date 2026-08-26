// Copyright 2006-2026 Speedgoat GmbH

#include "sg_blocks/analog/include/sg_io109.h"
#include "sg_blocks/common/libsg/sg_common.h"
static const int SG_INT_BARS[]={(0x1b45+3015-0x270c),(0x46d+6224-0x1cbb)};
#define SG_INT_PREFIX IO109
#include "sg_interrupt_config.h"
SG_INT_START_FUNC{z78d1de5155*zeb24a60218=(z78d1de5155*)(SG_INT_MAPPED_BAR((0x5e6+2753-0x10a7))+(0x6b2+1681-0xcc3));z667d71068c*z92fa982354=(z667d71068c*)(SG_INT_MAPPED_BAR((0x105c+3067-0x1c57))+(0x877+983-0xbe6));ze1d8c6d4f5*z3fad3d9764=(ze1d8c6d4f5*)SG_INT_MAPPED_BAR((0x938+6556-0x22d2));uint32_T zb76599274b=z92fa982354->zb76599274b&4294967040;z92fa982354->zb76599274b=zb76599274b|((0xcb2+6581-0x2666)<<z3c87fa7ea1)|((0xca5+6596-0x2668)<<z445a635dd2);SG_INT_ENABLE_PLX_FIX(&z92fa982354->zb76599274b,z92fa982354->zb76599274b);z3fad3d9764->z449880baed&=~z55f98f7516;while(!(z3fad3d9764->z14bc320aa4&z2056146c0d)){}zeb24a60218->z1def6086f7=(0x7d8+5763-0x1e50);}SG_INT_ISR_FUNC{z78d1de5155*zeb24a60218=(z78d1de5155*)(SG_INT_MAPPED_BAR((0x15c+4253-0x11f9))+(0xdb2+18-0xd44));if(zeb24a60218->z1def6086f7&(0x18bc+3248-0x255c)){zeb24a60218->z1def6086f7=(0x1ad+3058-0xd94);return SG_RUN_ISR;}return SG_DROP_ISR;}SG_INT_STOP_FUNC{z78d1de5155*zeb24a60218=(z78d1de5155*)(SG_INT_MAPPED_BAR((0x1539+2626-0x1f7b))+(0x96c+5695-0x1f2b));ze1d8c6d4f5*z3fad3d9764=(ze1d8c6d4f5*)SG_INT_MAPPED_BAR((0xac3+277-0xbd6));zeb24a60218->z1def6086f7=(0x6ec+7998-0x261e);z3fad3d9764->z449880baed=z3fad3d9764->z449880baed|z55f98f7516;}
