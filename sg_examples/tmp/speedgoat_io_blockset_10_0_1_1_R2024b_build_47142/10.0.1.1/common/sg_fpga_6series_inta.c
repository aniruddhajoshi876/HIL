// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x381+4222-0x13fd)};
#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#include "sg_interrupt_config.h"
#include <stdint.h>
typedef struct{uint32_t zab46142f2e;uint32_t clear;uint32_t event;}za276549eb0;SG_INT_START_FUNC{volatile za276549eb0*z79f5963ede;SG_INT_ENABLE_FPGA_6SERIES_INTA_FIX();z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0x1a08+1301-0x1f1b))+INTA_BASE);z79f5963ede->zab46142f2e=z79f5963ede->zab46142f2e|(0x565+4386-0x1686);return;}SG_INT_STOP_FUNC{volatile za276549eb0*z79f5963ede;z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0x109d+4162-0x20dd))+INTA_BASE);z79f5963ede->zab46142f2e=(0x219+747-0x504);z79f5963ede->clear=(0x302+936-0x6a9);z79f5963ede->clear=(0x1aef+2665-0x2558);return;}SG_INT_ISR_FUNC{
#ifdef __linux__
if(!SG_INT_IS_POLLING){if(SG_INT_OVERLOAD_CHECK){SG_INT_OVERLOAD_CHECK_CLEAR;return SG_DROP_ISR;}return SG_RUN_ISR;}
#endif
volatile za276549eb0*z79f5963ede;z79f5963ede=(za276549eb0*)((uintptr_t)SG_INT_MAPPED_BAR((0x1f3d+698-0x21f5))+INTA_BASE);if(!(uintptr_t)SG_INT_MAPPED_BAR((0x12d1+3019-0x1e9a)))return SG_DROP_ISR;if(z79f5963ede->event!=(0x401+4133-0x1426)){z79f5963ede->clear=(0x6d9+3663-0x1527);z79f5963ede->clear=(0x18e4+1419-0x1e6f);return SG_RUN_ISR;}else{return SG_DROP_ISR;}}
