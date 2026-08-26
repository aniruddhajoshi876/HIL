// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x9b7+1895-0x111c)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_fpga_vrs_sf_3
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include  "sg_printf.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
typedef enum{zfaa050b79d,CHANNEL,ze344b15ab1,z1c6d416fde,z88c63e0ba1,z731cbedf5e,z878b4ea0cf,z1d53a15f7b,zab4b0248d6,zdf24515981}z1ebbfc0a89;
#define ze13f49a01f         ssGetSFcnParam(S, zfaa050b79d)
#define za9d8fb6bcf           ssGetSFcnParam(S, CHANNEL)
#define z3832b85a32         ssGetSFcnParam(S, ze344b15ab1)
#define z38f57ee110     ssGetSFcnParam(S, z1c6d416fde)
#define za08eaecce0         ssGetSFcnParam(S, z88c63e0ba1    )
#define zd68f0d3534          ssGetSFcnParam(S, z731cbedf5e     )
#define z0760155ccd       ssGetSFcnParam(S, z878b4ea0cf  )
#define zb5a56d8a40  ssGetSFcnParam(S, z1d53a15f7b)
#define zb8a484fa5c   ssGetSFcnParam(S, zab4b0248d6)
#define z2e6483d505            ((0x9f3+660-0xc85))
#define zc5ce4cb81a            ((0x93f+3314-0x1630))
#define z2b17e2ee3b            ((0x13a3+3457-0x2123))
#define z0194338df7       ((0xa6a+6916-0x256e))
#define zd002430c33     ((0x1624+2634-0x206e))
#define z977c717d5d     ((0x8d9+4893-0x1bf5))
#define z25ffcbf791     ((0x569+6122-0x1d53))
#define z5bbcf8be2c          (0x6c9+2972-0x1262)
#define z4099fa3dcd          (32767/(0xb42+1554-0x114a))
#define zae4028a32c            4294967296 
#define z62917fff17            32768 
#define z2352836e59            16384 
typedef struct{uint32_t version;uint32_t zce6988b072;uint32_t enable;uint32_t z0a1f578afb;uint32_t z124cafb731;uint32_t z5a5725572d[(0xf45+3051-0x1b25)];uint32_t z4a29242ba3[(0x1072+1148-0x14ce)];uint32_t z8e28bead35[(0x584+5145-0x197d)];uint32_t step[(0x378+8109-0x2305)];uint32_t z0754dd67cc[(0x5a3+4519-0x172a)];uint32_t zb640018cea[(0x205a+846-0x2388)];uint32_t z9e1ca6238a[(0x72+4083-0x1045)];uint32_t z35e0b1bf97[(0x5a8+331-0x6d3)];uint32_t z7b2bfa7236[(0x1d33+570-0x1f4d)];uint32_t zfb17dcf6d2[(0x249+14-0x237)];uint32_t z4250da54be[(0xb46+2053-0x132b)];uint32_t position[(0x512+4494-0x1680)];}z4af5f5a9d9;static char_T msg[(0x56a+5811-0x1b1d)];static void mdlInitializeSizes(SimStruct*S){uint32_t i,z4d71223f46,zbb09957843;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xa75+1325-0xfa2));ssSetNumDiscStates(S,(0x1bb+32-0x1db));z4d71223f46=(0x567+3569-0x1358);if((uint32_t)mxGetPr(zb5a56d8a40)[(0x2222+113-0x2293)]){z4d71223f46=(0x259b+78-0x25e7);}else{z4d71223f46=(0x1f7a+861-0x22d4);}ssSetNumInputPorts(S,z4d71223f46);for(i=(0x1073+5129-0x247c);i<z4d71223f46;i++){ssSetInputPortWidth(S,i,(uint32_T)mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,i,(0x70+840-0x3b7));ssSetInputPortRequiredContiguous(S,i,(0x142+3796-0x1015));ssSetInputPortDataType(S,i,(0xd33+4332-0x1e1f));}if((uint32_t)mxGetPr(zb8a484fa5c)[(0x1dd+5487-0x174c)]){zbb09957843=(0x34a+9046-0x269f);ssSetNumOutputPorts(S,zbb09957843);ssSetOutputPortWidth(S,(0x52f+579-0x772),(uint32_T)mxGetN(za9d8fb6bcf));}else{zbb09957843=(0x465+7295-0x20e4);ssSetNumOutputPorts(S,zbb09957843);}ssSetNumSampleTimes(S,(0x14a7+635-0x1721));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x238d+43-0x23b8));ssSetNumNonsampledZCs(S,(0x207+5988-0x196b));for(i=(0x43a+2417-0xdab);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xfd9+4641-0x21fa));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1dc4+1091-0x2207)]==-1.0){ssSetSampleTime(S,(0xd38+220-0xe14),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xc21+2690-0x16a3),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1e9+6008-0x1961),mxGetPr(z3832b85a32)[(0x743+7147-0x232e)]);ssSetOffsetTime(S,(0x650+1808-0xd60),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z4af5f5a9d9*z77f880f88c;void*bar2ptr;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xbd+7705-0x1ed6)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x2120+287-0x223f);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,VRS_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x56\x52\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x107b+4034-0x203d)],SG_FPGA_IO3XX_BAR2);z77f880f88c=(z4af5f5a9d9*)((uintptr_t)bar2ptr+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z77f880f88c);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z77f880f88c->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x56\x52\x53\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t z0a1f578afb;real_T z3525a674aa,z996b4b3c19,z87a9298581;uint32_t zfc610e35a5;uint32_t zce6988b072;uint32_t z03cd415bce,zcf6f309a0a;uint32_t z183c848830;uint32_t i;uint32_t channel;volatile z4af5f5a9d9*z77f880f88c;z77f880f88c=(z4af5f5a9d9*)(ssGetPWorkValue(S,z0194338df7));z3525a674aa=(real_T)mxGetPr(za08eaecce0)[(0x1cd1+2605-0x26fe)];z996b4b3c19=(real_T)mxGetPr(zd68f0d3534)[(0x1fa3+823-0x22da)];z0a1f578afb=(uint32_t)(z3525a674aa/z996b4b3c19);z77f880f88c->z0a1f578afb=z0a1f578afb;z87a9298581=(real_T)mxGetPr(z0760155ccd)[(0x5ac+5992-0x1d14)];ssSetRWorkValue(S,z25ffcbf791,z87a9298581);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x911+4056-0x18e9)]-(0x209+7424-0x1f08);zce6988b072=z77f880f88c->zce6988b072;zce6988b072|=((0x1576+3078-0x217b)<<channel);z77f880f88c->zce6988b072=zce6988b072;for(i=(0xf22+5683-0x2555);i<z2352836e59;i++){z77f880f88c->z4a29242ba3[channel]=i;zfc610e35a5=(uint32_t)((int32_t)mxGetPr(z38f57ee110)[i]);z77f880f88c->z8e28bead35[channel]=zfc610e35a5;}zce6988b072=z77f880f88c->zce6988b072;zce6988b072&=~((0x1cc6+1484-0x2291)<<channel);z77f880f88c->zce6988b072=zce6988b072;z03cd415bce=(uint32_t)mxGetPr(zb8a484fa5c)[(0x285+6402-0x1b87)];ssSetIWorkValue(S,zd002430c33,z03cd415bce);zcf6f309a0a=(uint32_t)mxGetPr(zb5a56d8a40)[(0x1f63+485-0x2148)];ssSetIWorkValue(S,z977c717d5d,zcf6f309a0a);z183c848830=z77f880f88c->z124cafb731;z183c848830|=(zcf6f309a0a<<channel);z77f880f88c->z124cafb731=z183c848830;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t channel;real_T*zc7305bcef3,*z0754dd67cc,*zb640018cea;real_T z3525a674aa,z87a9298581;real_T zf8a793f028,z3269ea9aaa;real_T*out;uint32_t enable;uint32_t z40a5b4a9e6;volatile z4af5f5a9d9*z77f880f88c;z77f880f88c=(z4af5f5a9d9*)(ssGetPWorkValue(S,z0194338df7));channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0xfc4+935-0x136b)]-(0x1a94+800-0x1db3);enable=z77f880f88c->enable;enable|=((0xb22+6126-0x230f)<<channel);z77f880f88c->enable=enable;z3525a674aa=(real_T)mxGetPr(za08eaecce0)[(0x1723+2900-0x2277)];z40a5b4a9e6=(0x441+1205-0x8f6);if((uint32_t)ssGetIWorkValue(S,z977c717d5d)==(0xaf6+3616-0x1916)){zc7305bcef3=(real_T*)ssGetInputPortSignal(S,z40a5b4a9e6);z77f880f88c->step[channel]=(uint32_t)(zc7305bcef3[(0x7b1+4243-0x1844)]*zae4028a32c/z3525a674aa/(0x2d4+2897-0xe23)/(0x563+2905-0x1080));z40a5b4a9e6++;}z87a9298581=(real_T)ssGetRWorkValue(S,z25ffcbf791);z0754dd67cc=(real_T*)ssGetInputPortSignal(S,z40a5b4a9e6);zf8a793f028=z0754dd67cc[(0x729+2536-0x1111)]*z87a9298581/(0x1f5d+1053-0x2378);if(zf8a793f028>(0x151+4712-0x12b9)){zf8a793f028=(0x83c+1566-0xd5a);}else if(zf8a793f028<-(0x1372+1219-0x1735)){zf8a793f028=-(0x60f+882-0x881);}z77f880f88c->z0754dd67cc[channel]=(uint32_t)(zf8a793f028*z62917fff17);z40a5b4a9e6++;zb640018cea=(real_T*)ssGetInputPortSignal(S,z40a5b4a9e6);z3269ea9aaa=zb640018cea[(0x8a7+4446-0x1a05)]*z87a9298581;if(z3269ea9aaa>(0x207+387-0x389)){z3269ea9aaa=(0xebd+3296-0x1b9c);}else if(z3269ea9aaa<-(0xd92+5495-0x2308)){z3269ea9aaa=-(0xe37+3061-0x1a2b);}z77f880f88c->zb640018cea[channel]=(uint32_t)(z3269ea9aaa*z62917fff17);if((uint32_t)ssGetIWorkValue(S,zd002430c33)){out=(real_T*)ssGetOutputPortSignal(S,(0xa78+2390-0x13ce));out[(0x67d+5707-0x1cc8)]=(real_T)z77f880f88c->position[channel]/zae4028a32c*(0x744+5714-0x1ac6);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z4af5f5a9d9*z77f880f88c;z77f880f88c=(z4af5f5a9d9*)(ssGetPWorkValue(S,z0194338df7));z77f880f88c->enable=(uint32_t)((0x33b+8162-0x231d));
#endif
}
#include "sg_sfcn_glue.h"   

