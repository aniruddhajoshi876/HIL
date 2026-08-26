// Copyright 2006-2026 Speedgoat GmbH

#ifndef zb5aa6f5350
#define zb5aa6f5350
#include "a2b/error.h"
#include "sg_common.h"
#include "sg_fpga_io3xx_scatter_gather_dma.h"
#include "sg_fpga_xilinx_i2c.h"
#define z5be3a76df2 zc01ee289fd
typedef struct{void*z83975a4e48[z5be3a76df2];void*mutex[z5be3a76df2];uint8_t*zf83fca9966[z5be3a76df2];void*z6349a10312[z5be3a76df2];io3xx_sgdma_Handle*z5e68a99d52;io3xx_sgdma_Handle*z9cde62bda9;uintptr_t zdda8f94a2e;bool zd820dfbf1a[z5be3a76df2];uint32_t*zfeadb8e3a1[z5be3a76df2][(0xce5+4125-0x1ce2)];uint32_t zfac69d27f5;}z231f74460b;typedef struct{uint32_t za8ffe2a98e;int8_t z7c97567ae4;uint8_t z9b567360ec;uint8_t z1c1135cc6f;bool z7ddb5c3240;}zf2ee4b9caa;typedef struct{int16_t z1a62be8d17;uint8_t direction;uint8_t zc64bd29281;uint8_t level;bool z4cddfc20fe;}z3fcb489ba4;
#ifdef __cplusplus
extern"C"{
#endif
int a2b_SetupNode(z231f74460b*z465222e7c0,uint8_t zbb80d581a0,bool ze54b6c2c7a);int a2b_MonitorNetwork(void*z83975a4e48,uint8_t zbb80d581a0);int a2b_SetupStop(void*z83975a4e48);int a2b_StatusStep(void*z83975a4e48,zf2ee4b9caa*status);int a2b_IsGPIOEnabled(void*z83975a4e48,z3fcb489ba4*z50d14bfd8f);int a2b_GPIOStep(void*z83975a4e48,z3fcb489ba4*z50d14bfd8f);int a2b_i2cRemoteWriteRead(void*z83975a4e48,int8_t z7c97567ae4,uint8_t addr,uint8_t zdf3aa6a19a,uint8_t*regAddr,uint8_t nBytes,uint8_t*buffer);int a2b_i2cRemoteWrite(void*z83975a4e48,int8_t z7c97567ae4,uint8_t addr,uint8_t nBytes,uint8_t*buffer);int a2b_spiRemoteWriteRead(void*z83975a4e48,uint8_t zbd1db1b50c,uint8_t nBytes,uint8_t*buffer);int a2b_spiRemoteWrite(void*z83975a4e48,uint8_t nBytes,uint8_t*buffer);
#ifdef __cplusplus
}
#endif
#endif

