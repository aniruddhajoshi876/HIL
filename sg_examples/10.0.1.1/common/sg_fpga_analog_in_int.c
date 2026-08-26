// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0xc44+399-0xdd1)};
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#include <stdint.h>
#include "sg_blocks/fpga/analog/include/sg_fpga_analog_dma.h"
#include "sg_printf.h"
#define zc19a381cf7               5373952
#ifndef z5eee7ecc7d
#define z5eee7ecc7d     (0xfa9+2203-0x1843)
#endif
#define z7f33ef6623      (0xf2f+3068-0x1b28)
#define z2b24e9f2cb     (0xde5+1473-0x13a6)
typedef volatile struct{uint32_t ISR;uint32_t z2faa57e0eb;uint32_t IER;uint32_t z6759dc6668;uint32_t zdfbc31d580;uint32_t zd2888ccec8;uint32_t zea83b74a38;uint32_t z119ae482c7;uint32_t zae4666333d;uint32_t z1d07e70426;}z4f23961b4f;SG_INT_START_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x771+6776-0x21e7))+zc19a381cf7);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z5eee7ecc7d);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z5eee7ecc7d;z2b067ad6f2->zdfbc31d580=z5eee7ecc7d;z2b067ad6f2->z119ae482c7=(0x2063+1584-0x2690);}}SG_INT_STOP_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x1e1a+104-0x1e80))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x5d3+2916-0x1135))+z622b5514bc);z22dd4070f1->z93beb01ec7.zaed73eb2ad&=~(zda905d3958);z22dd4070f1->z93beb01ec7.z3d41168cf2|=z533cc0b976;z2b067ad6f2->zd2888ccec8=z5eee7ecc7d;z2b067ad6f2->z119ae482c7=z2b24e9f2cb;}SG_INT_ISR_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0xa79+4317-0x1b54))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x1584+2077-0x1d9f))+z622b5514bc);if(z22dd4070f1->z93beb01ec7.z3d41168cf2&zc0623a201e){z22dd4070f1->z93beb01ec7.z3d41168cf2=zc0623a201e;if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z5eee7ecc7d;z2b067ad6f2->zdfbc31d580=z5eee7ecc7d;}return SG_RUN_ISR;}return SG_DROP_ISR;}
