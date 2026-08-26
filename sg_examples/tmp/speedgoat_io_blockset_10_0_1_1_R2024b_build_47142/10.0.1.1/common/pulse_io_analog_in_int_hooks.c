// Copyright 2006-2026 Speedgoat GmbH

#define SG_INT_PREFIX   Pulse_IO_ANALOG_IN
#define SG_AXI_DEVICE_NAME "\x66\x70\x67\x61\x5f\x66\x61\x62\x72\x69\x63\x5f\x33"
static const int SG_INT_BARS[]={(0xeb+1637-0x74e)};
#include "sg_interrupt_config_axi.h"
#include <stdint.h>
#include "sg_blocks/fpga/analog/include/sg_fpga_analog_dma.h"
#include "sg_printf.h"
SG_INT_START_FUNC{}SG_INT_STOP_FUNC{z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0xd4a+6297-0x25e1))+z622b5514bc);z22dd4070f1->z93beb01ec7.zaed73eb2ad&=~(zda905d3958);z22dd4070f1->z93beb01ec7.z3d41168cf2|=z533cc0b976;}SG_INT_ISR_FUNC{z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x65b+8133-0x261e))+z622b5514bc);if(z22dd4070f1->z93beb01ec7.z3d41168cf2&zc0623a201e){z22dd4070f1->z93beb01ec7.z3d41168cf2=zc0623a201e;return SG_RUN_ISR;}return SG_DROP_ISR;}
