// Copyright 2006-2026 Speedgoat GmbH

#define SG_INT_PREFIX   Pulse_IO_ANALOG_OUT
#define SG_AXI_DEVICE_NAME "\x66\x70\x67\x61\x5f\x66\x61\x62\x72\x69\x63\x5f\x34"
static const int SG_INT_BARS[]={(0x193+9145-0x254a)};
#include <stdint.h>
#include "sg_blocks/fpga/analog/include/sg_fpga_analog_dma.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#include "sg_blocks/fpga/analog/include/sg_AnalogOutputCm_IO334.h"
#include "sg_printf.h"
#include "sg_interrupt_config_axi.h"
SG_INT_START_FUNC{}SG_INT_STOP_FUNC{z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x1aa1+1699-0x2142))+z622b5514bc);z22dd4070f1->z6bce6d1437.zaed73eb2ad&=~(zda905d3958);z22dd4070f1->z6bce6d1437.z3d41168cf2|=z533cc0b976;}SG_INT_ISR_FUNC{z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x1365+4645-0x2588))+z622b5514bc);z0a61963b8c*z2bb2be4242=(z0a61963b8c*)(SG_INT_MAPPED_BAR((0x453+97-0x4b2))+z2420abdd0e);if(z2bb2be4242->z58bed3c2d9){z22dd4070f1->z6bce6d1437.z3d41168cf2=zc0623a201e;return SG_RUN_ISR;}return SG_DROP_ISR;}
