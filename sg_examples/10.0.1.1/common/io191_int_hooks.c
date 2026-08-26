// Copyright 2006-2026 Speedgoat GmbH

#include "sg_blocks/analog/include/sg_io191.h"
#include "sg_blocks/common/libsg/sg_common.h"
const int SG_INT_BARS[]={(0x1131+1684-0x17c5),(0xf2b+5543-0x24d0)};
#define SG_INT_PREFIX IO191
#include "sg_interrupt_config.h"
SG_INT_START_FUNC{zeb49e172d5*z8bf047e7b6;z5419123aee*z286a95e879;uint32_t zea9d5c3d22;z8bf047e7b6=(zeb49e172d5*)SG_INT_MAPPED_BAR((0x1015+3774-0x1ed3));z286a95e879=(z5419123aee*)SG_INT_MAPPED_BAR((0x211+550-0x435));zea9d5c3d22=z286a95e879->z495adeb12a;z286a95e879->z495adeb12a=zea9d5c3d22|((0xa20+3947-0x198a)<<z55588371ab)|((0x1576+3162-0x21cf)<<z357fbf486a);z286a95e879->zfb4e23ffe8=z9cdfc90584|z42315c4b7d;z8bf047e7b6->z1969cde68e=(0xd75+3822-0x1c5f);}SG_INT_ISR_FUNC{z5419123aee*z286a95e879=(z5419123aee*)SG_INT_MAPPED_BAR((0xc0a+1512-0x11f0));if(z286a95e879->zfb4e23ffe8&z2f8d87c79b){z286a95e879->zfb4e23ffe8=z9cdfc90584;return SG_RUN_ISR;}return SG_DROP_ISR;}SG_INT_STOP_FUNC{z5419123aee*z286a95e879=(z5419123aee*)SG_INT_MAPPED_BAR((0x980+4745-0x1c07));z286a95e879->zfb4e23ffe8=z9cdfc90584;}
