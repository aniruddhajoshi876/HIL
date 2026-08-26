// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0x1671+143-0x16fe)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_damodule7_sf_a1
#include  <stddef.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <stdbool.h>
#include  "simstruc.h"
#ifdef    MATLAB_MEX_FILE
#include  "mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#endif
#define zdf24515981        ((0x19c+1264-0x681))
#define z533b11d03f         ssGetSFcnParam(S, (0x1b61+256-0x1c61)) 
#define z58f464b4bb                ssGetSFcnParam(S, (0x572+4810-0x183b))
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x112b+742-0x140f)) 
#define z9ad049935d        ssGetSFcnParam(S, (0x9a2+6895-0x248e))
#define z59bb2f4bac        ssGetSFcnParam(S, (0x6d5+3620-0x14f5))
#define z962f28f429        ssGetSFcnParam(S, (0x121+4704-0x137c))
#define zad03d924d8              ssGetSFcnParam(S, (0x1277+4000-0x2211)) 
#define z159ecbe81e           ssGetSFcnParam(S, (0x233c+418-0x24d7)) 
#define z04f0a23313          ssGetSFcnParam(S, (0x65b+3965-0x15d0)) 
#define z3832b85a32         ssGetSFcnParam(S, (0xb58+5963-0x229a))
#define z702a26a5e9              ssGetSFcnParam(S, (0x148+1829-0x863))
#define z2e6483d505              ((0x1866+3054-0x2454))
#define zc5ce4cb81a              ((0x3b3+8789-0x2608))
#define z2b17e2ee3b              ((0xa84+5650-0x2095))
#define z0194338df7         ((0xaac+696-0xd64))
#define zde0f6a0b5c              (655360)
#define zd055b77bdc                         ((0x47f+1181-0x91b))
#define z59a7b09cad                       ((0x44f+7679-0x224c))
#define z893a26ca15                ((0x173d+234-0x1824))
#define zaa2f1194f3                    ((0x14e8+4058-0x24be))
#define zde225cb98f    ((0x97b+4594-0x1b68))
#define zd784dd3efd  ((0xcf8+2448-0x1682))
#define z5674e18e88                      ((0x3ec+5857-0x1abd))
static char msg[(0x149d+1382-0x1903)];struct z6e54179dbd{uint32_t zd7f607991c[(0x1866+1839-0x1f85)];uint32_t z64c973e715[(0x19ba+522-0x1bb4)];uint32_t z3a9c5f054e[(0x104d+2458-0x19d7)];uint32_t enable;uint32_t z6a621e2ebc;uint32_t zfc0eea4f31;uint32_t za87b7c2ad3;uint32_t version;uint32_t revision;};static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1bea+2187-0x2475));ssSetNumDiscStates(S,(0x242+8857-0x24db));za0df33019b=(0xf73+767-0x1272);for(i=(0x3c+3072-0xc3c);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){if((uint32_t)mxGetPr(z9ad049935d)[i]==(0x1b77+186-0x1c31)){za0df33019b++;}}ssSetNumInputPorts(S,za0df33019b);for(i=(0x2f2+3878-0x1218);i<za0df33019b;i++){ssSetInputPortWidth(S,i,(0x1ed4+914-0x2265));ssSetInputPortDirectFeedThrough(S,i,(0x1f1c+737-0x21fc));ssSetInputPortRequiredContiguous(S,i,(0x197+838-0x4dc));}ssSetNumOutputPorts(S,(0x175+3774-0x1033));ssSetNumSampleTimes(S,(0xdd0+4647-0x1ff6));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1e79+2143-0x26d8));ssSetNumNonsampledZCs(S,(0xb72+4843-0x1e5d));for(i=(0x166c+3808-0x254c);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1b23+3014-0x26e9));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1050+281-0x1169)]==-1.0){ssSetSampleTime(S,(0xc43+2752-0x1703),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x272+9195-0x265d),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x426+8648-0x25ee),mxGetPr(z3832b85a32)[(0x1dd8+771-0x20db)]);ssSetOffsetTime(S,(0x1917+2632-0x235f),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t z6a621e2ebc;uint32_t boardType,channel,enable;sg_fpga_io3xxModuleIdT moduleId;volatile struct z6e54179dbd*zf1756dff08;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x192+3712-0x1012)];if(sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x591+5089-0x1972)){sprintf(msg,"\x49\x4f\x33\x78\x78\x20\x61\x6e\x61\x6c\x6f\x67\x20\x6f\x75\x74\x70\x75\x74\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);return;}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x67+5649-0x1678)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xe5a+1077-0x128f)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z0194338df7,bar2ptr);zf1756dff08=(volatile struct z6e54179dbd*)((uintptr_t)bar2ptr+zde0f6a0b5c);if(!sg_isModelInit()){z6a621e2ebc=(0x432+1425-0x9c3);enable=(0x651+685-0x8fe);for(i=(0x155+6856-0x1c1d);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x7f4+2617-0x122c);enable|=((0xb74+5610-0x215d)<<channel);if((uint32_t)mxGetPr(z9ad049935d)[i]==(0x6a8+5471-0x1c06)){z6a621e2ebc|=((0x207b+711-0x2341)<<channel);}else{z6a621e2ebc&=~((0x228d+845-0x25d9)<<channel);}zf1756dff08->z3a9c5f054e[channel]=(uint32_t)mxGetPr(z59bb2f4bac)[i]-(0x83f+939-0xbe9);zf1756dff08->z64c973e715[channel]=(uint32_t)mxGetPr(z962f28f429)[i]-(0x114a+450-0x130b);}zf1756dff08->zfc0eea4f31=(uint32_t)mxGetPr(zad03d924d8)[(0x22f+5728-0x188f)]-(0xaf4+2572-0x14ff);zf1756dff08->z6a621e2ebc=z6a621e2ebc;zf1756dff08->enable=enable;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,update,z0add1d1c25;volatile struct z6e54179dbd*zf1756dff08;double*in;uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint16_t count=(0x148+4708-0x13ac);double z7de4111e09;zf1756dff08=(volatile struct z6e54179dbd*)(base+zde0f6a0b5c);update=(0x93b+1103-0xd8a);z0add1d1c25=(0x1a6+2469-0xb4b);for(i=(0x4bd+4635-0x16d8);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){if((uint32_t)mxGetPr(z9ad049935d)[i]==(0x8fa+4925-0x1c37)){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1907+892-0x1c82);update|=((0x2147+417-0x22e7)<<channel);in=(double*)ssGetInputPortSignal(S,z0add1d1c25);z7de4111e09=in[(0x147d+2932-0x1ff1)];if((uint32_t)mxGetPr(zad03d924d8)[(0x10d8+4136-0x2100)]==zaa2f1194f3){z7de4111e09+=10.0;count=(uint16_t)((int16_t)((z7de4111e09/20.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0xbf4+941-0xfa1)]==z59a7b09cad){z7de4111e09+=0.0;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x1856+3134-0x2494)]==zde225cb98f){z7de4111e09+=2.5;count=(uint16_t)((int16_t)((z7de4111e09/5.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0xf5+6737-0x1b46)]==zd055b77bdc){z7de4111e09+=0.0;count=(uint16_t)((int16_t)((z7de4111e09/5.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x9d8+254-0xad6)]==z893a26ca15){z7de4111e09+=5.0;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x10fd+5243-0x2578)]==zd784dd3efd){z7de4111e09+=2.5;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}zf1756dff08->zd7f607991c[channel]=count;z0add1d1c25++;}}if(update>(0x218a+1201-0x263b)){zf1756dff08->za87b7c2ad3=update;zf1756dff08->za87b7c2ad3=(0x4e2+5965-0x1c2f);}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,update,channel;uint16_t count=(0x7d4+396-0x960);double z7de4111e09=(0x1bc8+974-0x1f96),zc6fde417de[(0x1d19+612-0x1f6d)];volatile struct z6e54179dbd*zf1756dff08;uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z0194338df7);zf1756dff08=(volatile struct z6e54179dbd*)(base+zde0f6a0b5c);if(sg_isModelInit()){zf1756dff08->z6a621e2ebc=(0x62a+2511-0xff9);sg_wait_s(0.00001);for(i=(0x31b+8342-0x23b1);i<z5674e18e88;i++){zc6fde417de[i]=0.0;}for(i=(0x444+269-0x551);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x262+5000-0x15e9);zc6fde417de[channel]=(double)mxGetPr(z159ecbe81e)[i];}for(channel=(0x1f57+1390-0x24c5);channel<z5674e18e88;channel++){z7de4111e09=zc6fde417de[channel];if((uint32_t)mxGetPr(zad03d924d8)[(0x25b+4143-0x128a)]==zaa2f1194f3){z7de4111e09+=10.0;count=(uint16_t)((int16_t)((z7de4111e09/20.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x5fd+2948-0x1181)]==z59a7b09cad){z7de4111e09+=0.0;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0xc63+3784-0x1b2b)]==zde225cb98f){z7de4111e09+=2.5;count=(uint16_t)((int16_t)((z7de4111e09/5.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x1898+222-0x1976)]==zd055b77bdc){z7de4111e09+=0.0;count=(uint16_t)((int16_t)((z7de4111e09/5.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x10ab+2964-0x1c3f)]==z893a26ca15){z7de4111e09+=5.0;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x4e8+8302-0x2556)]==zd784dd3efd){z7de4111e09+=2.5;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}zf1756dff08->zd7f607991c[channel]=count;}update=65535;zf1756dff08->zfc0eea4f31=(uint32_t)mxGetPr(zad03d924d8)[(0xa7b+5235-0x1eee)]-(0xb89+6947-0x26ab);zf1756dff08->enable=update;zf1756dff08->za87b7c2ad3=update;zf1756dff08->za87b7c2ad3=(0x173a+416-0x18da);sg_wait_s(0.00001);}else{zf1756dff08->z6a621e2ebc=(0x64f+7975-0x2576);sg_wait_s(0.00001);update=(0x1957+3423-0x26b6);for(i=(0x1294+4382-0x23b2);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){if((uint32_t)mxGetPr(z04f0a23313)[i]){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x11c4+918-0x1559);update|=((0xfcb+2513-0x199b)<<channel);z7de4111e09=(double)mxGetPr(z159ecbe81e)[i];if((uint32_t)mxGetPr(zad03d924d8)[(0xf8+7196-0x1d14)]==zaa2f1194f3){z7de4111e09+=10.0;count=(uint16_t)((int16_t)((z7de4111e09/20.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x1a52+73-0x1a9b)]==z59a7b09cad){z7de4111e09+=0.0;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x756+5358-0x1c44)]==zde225cb98f){z7de4111e09+=2.5;count=(uint16_t)((int16_t)((z7de4111e09/5.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x9df+3768-0x1897)]==zd055b77bdc){z7de4111e09+=0.0;count=(uint16_t)((int16_t)((z7de4111e09/5.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0xb23+3296-0x1803)]==z893a26ca15){z7de4111e09+=5.0;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}else if((uint32_t)mxGetPr(zad03d924d8)[(0x759+6600-0x2121)]==zd784dd3efd){z7de4111e09+=2.5;count=(uint16_t)((int16_t)((z7de4111e09/10.0)*65535.0));}zf1756dff08->zd7f607991c[channel]=count;}}zf1756dff08->za87b7c2ad3=update;zf1756dff08->za87b7c2ad3=(0x278+2481-0xc29);sg_wait_s(0.00001);SG_PRINTF(DEBUG,"\x76\x65\x72\x73\x69\x6f\x6e\x3a\x20\x25\x64" "\n",zf1756dff08->version);SG_PRINTF(DEBUG,"\x72\x65\x76\x69\x73\x69\x6f\x6e\x3a\x20\x25\x64" "\n",zf1756dff08->revision);}
#endif
}
#include "sg_sfcn_glue.h"   

