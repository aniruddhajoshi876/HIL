// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0xc4+8574-0x2242),(0x1bb5+1224-0x207b)};
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#include <stdint.h>
#include "sg_blocks/fpga/analog/include/sg_fpga_analog_dma.h"
#include "sg_printf.h"
#define zc19a381cf7               5373952
#define zc72cf764c2      (0x36a+6989-0x1e57)
#define z72b0fd0e17 (0xe1+5908-0x17a5)
#define z9aa61b27a6 (0x942+1-0x942)
#define z5eee7ecc7d     (0x378+3901-0x12b1)
#define z7f33ef6623      (0x2073+996-0x2454)
#define z2b24e9f2cb     (0x78a+947-0xb3d)
typedef volatile struct{uint32_t ISR;uint32_t z2faa57e0eb;uint32_t IER;uint32_t z6759dc6668;uint32_t zdfbc31d580;uint32_t zd2888ccec8;uint32_t zea83b74a38;uint32_t z119ae482c7;uint32_t zae4666333d;uint32_t z1d07e70426;}z4f23961b4f;SG_INT_START_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0xd19+6129-0x2508))+zc19a381cf7);volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0x120c+2253-0x1ad9))+zc72cf764c2);volatile uint32_t*zc1156e3f7d=(uint32_t*)(SG_INT_MAPPED_BAR((0x15f+889-0x4d8))+z72b0fd0e17);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z5eee7ecc7d);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z5eee7ecc7d;z2b067ad6f2->zdfbc31d580=z5eee7ecc7d;z2b067ad6f2->z119ae482c7=(0x204a+206-0x2115);}*z65093051d7=(0x1ea+6634-0x1bd3);*zc1156e3f7d=z9aa61b27a6;}SG_INT_STOP_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x7d3+3300-0x14b5))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x3a6+8566-0x251a))+z622b5514bc);volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0xa77+25-0xa90))+zc72cf764c2);*z65093051d7=(0x6dc+1699-0xd7f);z22dd4070f1->z93beb01ec7.zaed73eb2ad&=~(zda905d3958);z22dd4070f1->z93beb01ec7.z3d41168cf2|=z533cc0b976;z2b067ad6f2->zd2888ccec8=z5eee7ecc7d;z2b067ad6f2->z119ae482c7=z2b24e9f2cb;}SG_INT_ISR_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x473+8796-0x26cd))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0xde9+1913-0x1560))+z622b5514bc);if(z22dd4070f1->z93beb01ec7.z3d41168cf2&zc0623a201e){z22dd4070f1->z93beb01ec7.z3d41168cf2=zc0623a201e;if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z5eee7ecc7d;z2b067ad6f2->zdfbc31d580=z5eee7ecc7d;}return SG_RUN_ISR;}return SG_DROP_ISR;}
