// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0xf51+2438-0x18d5)};
#include <stdint.h>
#include "sg_blocks/fpga/analog/include/sg_fpga_analog_dma.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#define zc19a381cf7               5373952
#define z2ffacf2c38    (0x534+3934-0x148a)
#define z7f33ef6623      (0x17d+4836-0x145e)
#define z2b24e9f2cb     (0x10e1+646-0x1367)
typedef volatile struct{uint32_t ISR;uint32_t z2faa57e0eb;uint32_t IER;uint32_t z6759dc6668;uint32_t zdfbc31d580;uint32_t zd2888ccec8;uint32_t zea83b74a38;uint32_t z119ae482c7;uint32_t zae4666333d;uint32_t z1d07e70426;}z4f23961b4f;SG_INT_START_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x400+2167-0xc75))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z2ffacf2c38);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z2ffacf2c38;z2b067ad6f2->zdfbc31d580=z2ffacf2c38;z2b067ad6f2->z119ae482c7=(0x12f7+1685-0x1989);}}SG_INT_STOP_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x5f0+8302-0x265c))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x1b5d+1419-0x20e6))+z622b5514bc);z22dd4070f1->z6bce6d1437.zaed73eb2ad&=~(zda905d3958);z22dd4070f1->z6bce6d1437.z3d41168cf2|=z533cc0b976;z2b067ad6f2->zd2888ccec8=z2ffacf2c38;z2b067ad6f2->z119ae482c7=z2b24e9f2cb;}SG_INT_ISR_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0xf65+495-0x1152))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x274+7701-0x2087))+z622b5514bc);if(z22dd4070f1->z6bce6d1437.z3d41168cf2&zc0623a201e){z22dd4070f1->z6bce6d1437.z3d41168cf2=zc0623a201e;if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z2ffacf2c38;z2b067ad6f2->zdfbc31d580=z2ffacf2c38;}return SG_RUN_ISR;}return SG_DROP_ISR;}
