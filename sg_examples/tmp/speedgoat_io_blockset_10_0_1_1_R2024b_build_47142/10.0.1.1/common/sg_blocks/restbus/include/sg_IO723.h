// Copyright 2006-2026 Speedgoat GmbH

#ifndef z04f82fd026
#define z04f82fd026
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <vector>
#include "sg_printf.h"
#define z9fe96ce105(x)          (mxGetPr(ssGetSFcnParam(S, x)))
#define z09263dafad(x)  (mxGetN(ssGetSFcnParam(S, x)))
#define z4c1a02abaf(x)     (mxGetM(ssGetSFcnParam(S, x)))
#define z3b623ddf8f(x, str, strlen)	(mxGetString(ssGetSFcnParam(S, x), str, strlen))
#define z8444fc96d2(x) (((x>>(0x209a+378-0x21fc))&(0x1953+3502-0x2602)) | ((x>>(0x195f+1145-0x1dd0))&65280) | ((x<<(0xae2+6375-0x23c1))&16711680) | ((x<<(0x14c0+1052-0x18c4))&4278190080))
#define z0056adfa94(x) (((x>>(0x203c+1029-0x2439))&(0x894+5437-0x1cd2)) | ((x<<(0x272+3382-0xfa0))&65280))
#define z9c1b598942	(0x750+6105-0x1f21)
#define z0396f94aa6      (0xb13+5649-0x211a)
#define zca7c2667f8    (0xb5c+3287-0x1831)
#define z3ca17416ff	(0xbe4+6148-0x23de)
#define z74a503429b       61530
#define z0668c72bd4         42255
#define z010e24146f   (0x25aa+1773-0x1a14)
#define zb99fcf4436   (0x2320+3003-0x1d58)
#define z1eacc82045  (0x805+8118-0x2238)
#define z461054cda9     (0x155a+1386-0x1a84)
#define zd4230e46bf	(0x1ba+4184-0x1192)
#define zed54b34401 65535
#define zedda59d72a         (0x1a31+1490-0x2002)
#define zd5b24154de  (0xc06+2140-0x1460)
#define zeeae56ded9          (0x206+3847-0x110a)
#define zf658685572    (0x16b6+2481-0x1fff)
#define z96df86a33f    7231
#define ze4108889ae   (0x258b+6197-0x2180)
#define zc9230c8786 7233
#ifndef MATLAB_MEX_FILE
typedef struct{uint16_t z9ebc1fd836;uint16_t z3a4df7af09;uint8_t z4cda2e35cc;uint8_t z79f20abf52;uint8_t z3a3e70d2a1;uint8_t Reserved;}__attribute__((packed))zb0840740f6;namespace zb1f6d57e30{struct Write{std::vector<uint8_t>*buffer;std::vector<uint8_t>::iterator z839a645366;double z809e708716;unsigned int z00ea66086b;unsigned int z2a6d53438e;};struct z71cbdc214f{std::vector<uint8_t>*buffer;std::vector<uint8_t>::iterator z8d50b21bf3;std::vector<uint8_t>::iterator z41222ce7e5;int state;bool z2d32058a83;};struct Module{unsigned int zd67953f34b;void*z87bf9389a8;void*z9224f86eb0;void*zd2c01b1c10;void*z9c06b80e43;void*z910c9655d9;void*z3bd6bc72fd;void*za98d59ab97;struct Write write;struct z71cbdc214f z6c358729c7;};int init(sg_mod_info*z00018d0b83);int close(sg_mod_info*z00018d0b83);int za483c9dbea(sg_mod_info*z00018d0b83,int z8f91d310f6);int z69099f6d66(zb1f6d57e30::Module*module,uint8_t*data,uint32_t nBytes);int z5e73087f46(zb1f6d57e30::Module*module,uint8_t*zb673a38fb9,uint32_t z8f2b959532,uint8_t*z8c5a65813f,uint32_t zcb5ea036be);int z10de4af24f(zb1f6d57e30::Module*module,uint8_t*data,uint32_t nBytes,uint8_t z6f95ebc3e6,uint8_t z8618aa9f53,uint8_t zd67953f34b);extern std::string errorMsg;const uint32_t z4301cb1b61=134405;const uint32_t ze3a5c318a7=((0x9f5+6920-0x24fc)<<(0x1423+4526-0x25c1))+(0x845+321-0x3aa);const uint32_t zf96b46ef14=((0x71b+5454-0x1c68)<<(0x147b+1550-0x1a79))+(0x3c5+2922-0xe51);namespace write{int z73378f8306(sg_mod_info*z00018d0b83,unsigned int size);int z0c63221d0a(sg_mod_info*z00018d0b83,double sampleTime);int z9a65ea9434(sg_mod_info*z00018d0b83,uint8_t*data,unsigned int size,double sampleTime);}namespace z6c358729c7{int z73378f8306(sg_mod_info*z00018d0b83,unsigned int size);int z9a65ea9434(sg_mod_info*z00018d0b83,uint8_t*data,unsigned int size);int z03c4b94c3c(sg_mod_info*z00018d0b83,bool z2d32058a83);}namespace zd4b08e63b3{typedef enum z1a8b0e4d04{z8bdd465cc5=(0xc73+1293-0x117f),z861ad05738,DATA,zce5073f4e3,ERROR,zb272d6b9e0,}z1a8b0e4d04;const uint32_t z7ce9ebe2aa=131141;const uint32_t z4fd0bc1413=131151;const uint32_t z9eb81cda51=183552;int init(void*handle,int direction);int read(void*handle,std::vector<uint8_t>*data,uint16_t*z3941d6406e);int write(void*handle,std::vector<uint8_t>*data,uint16_t z3941d6406e);}}
#endif  
#endif  

