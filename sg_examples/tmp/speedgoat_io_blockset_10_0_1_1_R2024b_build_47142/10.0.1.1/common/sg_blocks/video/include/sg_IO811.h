// Copyright 2006-2026 Speedgoat GmbH

#ifndef z2c472b93f0
#define z2c472b93f0
#include "tmwtypes.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"      
#endif
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x38\x31\x31\x20\x2d\x20\x42\x69\x74\x46\x6c\x6f\x77\x20\x4e\x45\x4f\x4e"
#define VENDORID (0x17e2+2869-0x118a)
#define DEVICEID 16384
#define SUBVENDORID 65535
#define SUBDEVICEID 65535
#define zcaa377ea6b (0x57d+591-0x7c7)
#define z55c6db6058 (0xde7+1589-0x140c)
typedef struct z25068cbdae{volatile uint32_t zba9dbe1e8e;volatile uint32_t zc10e8d2264;uint32_t z4498a0a185;uintptr_t z8510194de9;uintptr_t z5521bbf801;uintptr_t z154c53ff1b;uint32_t zd4c7c48ff9[(0x12ab+4259-0x234a)];uint32_t dx;uint32_t dy;uint32_t zcf45350c67;uint32_t zfd17019b34;uint32_t z386f6b05d5;}zbbbd9b49d7;int32_t sg_BFRegisterBoard(int32_t bus,int32_t slot,int32_t za0d38ae598,sg_PCIDevice*zeccbadd9b3);void sg_BFUNRegisterBoard(int32_t z4498a0a185);int sg_BFSetupDMA(int32_t z4498a0a185,uint32_t z5bf31f911a,uint32_t zebbc86307e,uint32_t z918cc35b03,uint32_t*zd4c7c48ff9,const double*zde83594af4,const double*z1da7c58fd5,uint32_t z18f3c93482);void sg_BFWriteNeonConfig(int32_t z4498a0a185,const double*zde83594af4);void sg_BFWriteMuxFPGA(int32_t z4498a0a185,const double*data,uint32_t size);char*sg_BFError(uint32_t z2f7faf6c48);void sg_BFResetAndStart(uint32_t z4498a0a185,uint32_t z6c90e5e407);void sg_BFStop(uint32_t z4498a0a185);uint32_t sg_BFCurrentCount(uint32_t z4498a0a185);uint32_t z568682afe1(uint32_t z4498a0a185);uint32_t sg_BFIntAck(uint32_t z4498a0a185);void sg_BFIntEnable(uint32_t z4498a0a185);void sg_BFIntDisable(uint32_t z4498a0a185);uint32_t sg_BFIntAny(uint32_t z4498a0a185);void sg_BFSWTrig(uint32_t z4498a0a185,uint32_t val);void sg_BFCurrentStatus(uint32_t z4498a0a185,uint32_t*z8a40480618,uint32_t*z66666679bc,uint32_t*z386f6b05d5,uint32_t*za404d4eee4);void sg_BFSerialInit(uint32_t z4498a0a185,uint32_t z36648ef580,uint32_t zf12d8b9b7a,uint32_t z1cb8f73998,uint32_t baud);void sg_BFSerialWrite(uint32_t z4498a0a185,char*data,uint32_t echo);int32_t z009ab226a1(uint32_t z4498a0a185);
#define zff55967a3b 7340032
struct zd2657f94dc{volatile uint8_t data;volatile uint8_t zc75aeee1f2[(0x251d+100-0x257a)];volatile uint8_t ier;volatile uint8_t zaabf29d721[(0x1286+4179-0x22d2)];volatile uint8_t za0ca912916;volatile uint8_t zaa4d6a6365[(0x6df+881-0xa49)];volatile uint8_t lcr;volatile uint8_t zf86f989b22[(0x1882+1556-0x1e8f)];volatile uint8_t mcr;volatile uint8_t z99eaad57f1[(0x195a+337-0x1aa4)];volatile uint8_t lsr;volatile uint8_t z20394a3057[(0x1855+2948-0x23d2)];volatile uint8_t msr;volatile uint8_t zbbe8bf5658[(0x527+6508-0x1e8c)];volatile uint8_t z0b1916a654;};
#define IIRREASON  (0x107a+437-0x1220)  
#define IIR64      (0x456+2435-0xdb9)  
#define IIRFEBL    (0x11e2+2887-0x1c69)  
#define IIRXOFF    (0x17fb+2164-0x205f)  
#define IIRHWFLOW  (0x808+806-0xb0e)  
#define FCREBL     (0x59c+3502-0x1349)  
#define FCRRCLR    (0x1692+831-0x19cf)  
#define FCRTCLR    (0x485+5088-0x1861)  
#define FCRDMA     (0xcb2+6730-0x26f4)  
#define FCR64      (0x1675+1712-0x1d05)  
#define FCRONE     (0x919+4265-0x19c2)  
#define FCRQUARTER (0x65f+4279-0x16d6)  
#define FCRHALF    (0x33d+6623-0x1c9c)  
#define FCRFULL    (0x52a+8666-0x2644)  
#define LCR5BIT    (0x7b5+3822-0x16a3)  
#define LCR6BIT    (0x1bd8+23-0x1bee)
#define LCR7BIT    (0xd91+5485-0x22fc)
#define LCR8BIT    (0x112a+3486-0x1ec5)  
#define LCRSTOP    (0x219d+477-0x2376)  
#define LCRPARITY  (0x349+5394-0x1853)  
#define LCREVEN    (0x27f+2509-0xc3c)  
#define LCRSTICK   (0x4d9+7752-0x2301)  
#define LCRBREAK   (0x390+8122-0x230a)  
#define LCRDLAB    (0x837+957-0xb74)  
#define LSRDR      (0x13db+654-0x1668)  
#define LSRTEMT    (0x325+2222-0xb93)  
#endif 

