// Copyright 2006-2026 Speedgoat GmbH
static const int SG_INT_BARS[]={(0x93c+6231-0x2193),(0x98a+5887-0x2087)};
#include <stdint.h>
#include "sg_blocks/fpga/analog/include/sg_fpga_analog_dma.h"
#include "sg_blocks/fpga/setup/include/sg_fpga_io3xx_util.h"
#include "sg_blocks/fpga/analog/include/sg_AnalogOutputCm_IO334.h"
#include "sg_printf.h"
#ifdef SG_AXI_DEVICE_NAME
#include "sg_interrupt_config_axi.h"
#else
#include "sg_interrupt_config.h"
#endif
#define zc19a381cf7               5373952
#define zc72cf764c2      (0x55d+4387-0x1620)
#define z72b0fd0e17 (0x372+2351-0xc51)
#define z9aa61b27a6 (0x11c4+3231-0x1e62)
#define z2ffacf2c38    (0x1c19+2614-0x2647)
#define z7f33ef6623      (0x20c+2303-0xb08)
#define z2b24e9f2cb     (0x197b+1851-0x20b6)
typedef volatile struct{uint32_t ISR;uint32_t z2faa57e0eb;uint32_t IER;uint32_t z6759dc6668;uint32_t zdfbc31d580;uint32_t zd2888ccec8;uint32_t zea83b74a38;uint32_t z119ae482c7;uint32_t zae4666333d;uint32_t z1d07e70426;}z4f23961b4f;SG_INT_START_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x9e0+2159-0x124d))+zc19a381cf7);volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0x1422+1682-0x1ab4))+zc72cf764c2);volatile uint32_t*zc1156e3f7d=(uint32_t*)(SG_INT_MAPPED_BAR((0x197+4135-0x11be))+z72b0fd0e17);SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(z2ffacf2c38);if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z2ffacf2c38;z2b067ad6f2->zdfbc31d580=z2ffacf2c38;z2b067ad6f2->z119ae482c7=(0x1343+1661-0x19bd);}*z65093051d7=(0x1721+1147-0x1b9b);*zc1156e3f7d=z9aa61b27a6;}SG_INT_STOP_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x68d+7753-0x24d4))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x15a8+3533-0x2373))+z622b5514bc);volatile uint32_t*z65093051d7=(uint32_t*)(SG_INT_MAPPED_BAR((0x106a+2290-0x195c))+zc72cf764c2);z22dd4070f1->z6bce6d1437.zaed73eb2ad&=~(zda905d3958);z22dd4070f1->z6bce6d1437.z3d41168cf2|=z533cc0b976;z2b067ad6f2->zd2888ccec8=z2ffacf2c38;z2b067ad6f2->z119ae482c7=z2b24e9f2cb;*z65093051d7=(0x12ec+732-0x15c8);}SG_INT_ISR_FUNC{z4f23961b4f*z2b067ad6f2=(z4f23961b4f*)(SG_INT_MAPPED_BAR((0x7da+3667-0x162b))+zc19a381cf7);z9258e0f85a*z22dd4070f1=(z9258e0f85a*)(SG_INT_MAPPED_BAR((0x66a+3080-0x1270))+z622b5514bc);
#ifdef z775b53dc8d
z0a61963b8c*z2bb2be4242=(z0a61963b8c*)(SG_INT_MAPPED_BAR((0xb60+1557-0x1173))+z94686bc670);
#else
z0a61963b8c*z2bb2be4242=(z0a61963b8c*)(SG_INT_MAPPED_BAR((0x46f+99-0x4d0))+z2420abdd0e);
#endif
if(z2bb2be4242->z58bed3c2d9){z22dd4070f1->z6bce6d1437.z3d41168cf2=zc0623a201e;if(!(SG_INT_IS_POLLING)){z2b067ad6f2->z6759dc6668=z2ffacf2c38;z2b067ad6f2->zdfbc31d580=z2ffacf2c38;}return SG_RUN_ISR;}return SG_DROP_ISR;}
