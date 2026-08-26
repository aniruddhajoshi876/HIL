// Copyright 2006-2026 Speedgoat GmbH

#include "sg_blocks/common/libsg/sg_common.h"
static const int SG_INT_BARS[]={(0x101d+1288-0x1525)};
#define SG_INT_PREFIX IO901_IO902
#include "sg_interrupt_config.h"
SG_INT_ISR_FUNC{volatile uint32_t*z52d81e7135;uint32_t zeb54954966;int z44b16090d2=SG_DROP_ISR;z52d81e7135=(volatile uint32_t*)SG_INT_MAPPED_BAR((0x1247+3379-0x1f7a));zeb54954966=z52d81e7135[(0x1196+4551-0x235a)];while(zeb54954966&(0x351+3348-0xf66)){z44b16090d2=SG_RUN_ISR;z52d81e7135[(0x1a67+617-0x1ccd)]=zeb54954966;zeb54954966=z52d81e7135[(0x1201+4768-0x249e)];}return z44b16090d2;}SG_INT_START_FUNC{volatile uint32_t*z52d81e7135;z52d81e7135=(volatile uint32_t*)SG_INT_MAPPED_BAR((0x420+6480-0x1d70));z52d81e7135[(0xd7c+601-0xfd2)]=524288;return;}SG_INT_STOP_FUNC{volatile uint32_t*z52d81e7135;z52d81e7135=(volatile uint32_t*)SG_INT_MAPPED_BAR((0x992+3009-0x1553));z52d81e7135[(0x48+4451-0x11a8)]=(0x1970+837-0x1cb5);return;}
