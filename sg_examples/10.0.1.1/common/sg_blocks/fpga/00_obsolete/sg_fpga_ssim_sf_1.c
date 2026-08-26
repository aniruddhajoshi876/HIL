// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x1d10+1125-0x2173)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_ssim_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include        "sg_callback_legacy.h"
#include        "sg_printf.h"
#endif
#define zdf24515981        ((0x1aea+293-0x1c04))
#define z533b11d03f         ssGetSFcnParam(S,  (0xed3+2030-0x16c1)) 
#define ze13f49a01f         ssGetSFcnParam(S,  (0x652+1575-0xc78))
#define za9d8fb6bcf           ssGetSFcnParam(S,  (0x1226+4131-0x2247)) 
#define zf5ee62a4ad      ssGetSFcnParam(S,  (0x1c20+2503-0x25e4))
#define z3a4907dee5          ssGetSFcnParam(S,  (0x36d+1386-0x8d3))
#define z3832b85a32         ssGetSFcnParam(S,  (0x42+7506-0x1d8f))
#define z702a26a5e9              ssGetSFcnParam(S,  (0x8d6+7663-0x26bf))
#define z3e94973266                ssGetSFcnParam(S,  (0x3c0+6772-0x1e2d))
#define z2624d402ab                ssGetSFcnParam(S,  (0x125a+4673-0x2493))
#define z0422d86ad2					  ssGetSFcnParam(S,  (0x184a+3559-0x2628))
#define z596b77cbe5					  ssGetSFcnParam(S, (0x1c+7709-0x1e2f))
#define z2e6483d505            ((0x109a+1943-0x1831))
#define zc5ce4cb81a            ((0xee4+778-0x11ee))
#define z2b17e2ee3b            ((0xa3f+5845-0x2113))
#define z93d7dbe681       ((0x31d+7980-0x2249))
#define z9a3f261491              (245760)
static char_T msg[(0x68b+2490-0xf45)];typedef struct{uint32_t z15923ef3d9[(0x3d3+7407-0x20a2)];uint32_t z28e9d9261f[(0xdeb+4350-0x1ec9)];uint32_t z42ad4eacaf[(0x85c+4018-0x17ee)];uint32_t zfe18d134a8[(0x325+8358-0x23ab)];uint32_t z86bb419998[(0x15a7+180-0x163b)];uint32_t z08fefe38a9[(0xccf+6736-0x26ff)];uint32_t zb15396a870[(0x3cd+3607-0x11c4)];uint32_t zdd951fbe16[(0x858+4991-0x1bb7)];uint32_t z64fc736a62[(0xa1+4527-0x1230)];uint32_t zaf2186d9ec[(0x11b+5393-0x160c)];uint32_t z8c1a8bbff3[(0x1df+980-0x593)];uint32_t zdc1eed0ad0[(0xc85+2944-0x17e5)];uint32_t start;uint32_t test1;uint32_t test2;}z69e58993ac;void z22c44e4cdd(uint32_t*z407efd0741,uint32_t*zbcc3fe600b,uint32_t z15923ef3d9,uint32_t za746b13f73){uint32_t mask;uint32_t offset;uint32_t i;uint32_t zb534899b45,count;mask=(0x7c4+7482-0x24fe);offset=(0x1d3d+2145-0x259e);count=(0x3a1+1638-0xa07);for(i=(0x175+1521-0x766);i<z15923ef3d9;i++){mask|=((0x5ba+7036-0x2135)<<i);}for(i=(0x1725+2966-0x22bb);i<za746b13f73;i++){zb534899b45=z407efd0741[count];if(offset+z15923ef3d9<(0xb95+2830-0x1683)){zbcc3fe600b[i]=(zb534899b45>>offset)&mask;offset+=z15923ef3d9;}else if(offset+z15923ef3d9==(0xe79+6321-0x270a)){zbcc3fe600b[i]=(zb534899b45>>offset)&mask;offset=(0x3d6+7177-0x1fdf);count++;}else{zbcc3fe600b[i]=(zb534899b45>>offset)&mask;count++;zb534899b45=z407efd0741[count];zbcc3fe600b[i]|=(zb534899b45<<((0x1618+2839-0x210f)-offset));zbcc3fe600b[i]&=mask;offset=z15923ef3d9-((0x15f7+955-0x1992)-offset);}}}static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x733+3819-0x161e));ssSetNumDiscStates(S,(0x163d+1140-0x1ab1));zbc7ebd0e53=(uint32_t)mxGetN(za9d8fb6bcf);ssSetNumOutputPorts(S,zbc7ebd0e53);for(i=(0x56b+223-0x64a);i<zbc7ebd0e53;i++){ssSetOutputPortDataType(S,i,SS_UINT32);ssSetOutputPortWidth(S,i,(0x311+7003-0x1e6b));}ssSetNumSampleTimes(S,(0xf35+2918-0x1a9a));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xe2d+3685-0x1c92));ssSetNumNonsampledZCs(S,(0x68+2023-0x84f));for(i=(0x204+853-0x559);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x9a5+4871-0x1cac));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1770+3438-0x24de)]==-1.0){ssSetSampleTime(S,(0x8c2+3886-0x17f0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1590+3874-0x24b2),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x6da+66-0x71c),mxGetPr(z3832b85a32)[(0x1126+656-0x13b6)]);ssSetOffsetTime(S,(0x8a2+1512-0xe8a),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t i,channel;volatile z69e58993ac*zb9f7147b6c;sg_fpga_io3xxModuleIdT moduleId;uint32_t boardType,test=(0x443+1661-0xac0),test1=(0x182+2800-0xc72),x=(0x312+4230-0x1398);volatile uint32_t error=(0x3d0+8789-0x2625);uint32_t zcd308d01c9=(0x583+8405-0x2658),zc3f3fb8321=(0xf26+2108-0x1762);void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x225+6638-0x1c13)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x16b+7826-0x1ffd)){sprintf(msg,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0xf78+2235-0x1832)){bus=(0x2b2+3916-0x11fe);slot=(int_T)mxGetPr(z702a26a5e9)[(0x16b0+820-0x19e4)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1d0d+2457-0x26a6)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xfc2+55-0xff8)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x781+5152-0x1ba1)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1107+5130-0x2511)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);zb9f7147b6c=(z69e58993ac*)((uintptr_t)bar2ptr+z9a3f261491);if(!sg_isModelInit()){for(i=(0xc35+3133-0x1872);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x5f9+2596-0x101c);zcd308d01c9|=((0x70+3634-0xea1)<<channel);zb9f7147b6c->z15923ef3d9[channel]=(uint32_t)mxGetPr(z3a4907dee5)[i];zb9f7147b6c->z28e9d9261f[channel]=(uint32_t)mxGetPr(zf5ee62a4ad)[i];zb9f7147b6c->zdc1eed0ad0[channel]=(uint32_t)mxGetPr(z3e94973266)[i];zb9f7147b6c->z8c1a8bbff3[channel]=(uint32_t)mxGetPr(z2624d402ab)[i];}zc3f3fb8321=zb9f7147b6c->start;zb9f7147b6c->start=zc3f3fb8321|zcd308d01c9;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);uint32_t i,z26dbd73a5e=(0x8f+9578-0x25f9),channel,binary,zf67c59be22;volatile z69e58993ac*zb9f7147b6c;uint32_t*out,z69a8079db8,za892a705b5=(0xc0a+1066-0x1034),x;uint32_t z407efd0741[(0xdb9+1997-0x157e)],zbcc3fe600b[(0x864+1145-0xcbd)];zb9f7147b6c=(z69e58993ac*)(base+z9a3f261491);for(i=(0x1c98+2109-0x24d5);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xadb+3056-0x16ca);z69a8079db8=(uint32_t)mxGetPr(z3a4907dee5)[i]/(0x1ee7+484-0x20ab);if(((uint32_t)mxGetPr(z3a4907dee5)[i]%(0x1629+4182-0x265f))!=(0x13e7+2341-0x1d0c)){z69a8079db8=z69a8079db8+(0x1e9+9060-0x254c);}z407efd0741[(0xcf6+2667-0x1761)]=(0x15db+1514-0x1bc5);z407efd0741[(0x115b+4861-0x2457)]=(0x1171+3287-0x1e48);z407efd0741[(0x3d+6603-0x1a06)]=(0xec0+1689-0x1559);z407efd0741[(0x13d5+3902-0x2310)]=(0x12b+8119-0x20e2);z407efd0741[(0xbb6+6532-0x2536)]=(0x1f90+1594-0x25ca);z407efd0741[(0x450+3958-0x13c1)]=(0x10ff+720-0x13cf);z407efd0741[(0x14d7+3974-0x2457)]=(0x74d+2083-0xf70);z407efd0741[(0x84a+6350-0x2111)]=(0x10e6+4115-0x20f9);if(z69a8079db8>=(0x21e8+958-0x25a5)){if((uint32_t)mxGetPr(z0422d86ad2)[(0xb1+5036-0x145d)]==(0x104c+711-0x1312)){z407efd0741[(0xc4c+5828-0x2310)]=zb9f7147b6c->z42ad4eacaf[channel];za892a705b5=z407efd0741[(0x1322+1276-0x181e)];z407efd0741[(0x1124+4514-0x22c6)]=(0x1de7+364-0x1f53);for(x=(0xfb2+1321-0x14db);x<(uint32_t)mxGetPr(z3a4907dee5)[i];x++){if(x!=(0x7e2+2733-0x128f)){za892a705b5=za892a705b5>>(0x25d0+220-0x26ab);z407efd0741[(0x12ec+3842-0x21ee)]=z407efd0741[(0xdf6+3305-0x1adf)]<<(0x804+5589-0x1dd8);}z407efd0741[(0x2f5+6979-0x1e38)]=z407efd0741[(0x11dd+1825-0x18fe)]|(za892a705b5&(0x8c4+2539-0x12ae));}}else if((uint32_t)mxGetPr(z596b77cbe5)[(0x1ef+3131-0xe2a)]==(0x125c+2076-0x1a76)){binary=(0xa10+4920-0x1d48);z407efd0741[(0x11c0+3981-0x214d)]=zb9f7147b6c->z42ad4eacaf[channel];zf67c59be22=z407efd0741[(0xb6c+5994-0x22d6)];z407efd0741[(0x152d+2525-0x1f0a)]=(0x11c5+890-0x153f);binary=binary|(zf67c59be22&2147483648);for(x=(0x6ed+5091-0x1acf);x<(0xb90+5562-0x212a);x++){binary=binary|((((zf67c59be22<<x)^(binary<<(x-(0x1300+329-0x1448))))&16777216)>>x);}z407efd0741[(0x118+750-0x406)]=binary;}else{z407efd0741[(0x9f9+6859-0x24c4)]=zb9f7147b6c->z42ad4eacaf[channel];}}if(z69a8079db8>=(0x1401+1185-0x18a0)){z407efd0741[(0xa56+1586-0x1087)]=zb9f7147b6c->zfe18d134a8[channel];}if(z69a8079db8>=(0x4e2+6776-0x1f57)){z407efd0741[(0x9a6+7186-0x25b6)]=zb9f7147b6c->z86bb419998[channel];}if(z69a8079db8>=(0x1d8+901-0x559)){z407efd0741[(0xbf7+3035-0x17cf)]=zb9f7147b6c->z08fefe38a9[channel];}if(z69a8079db8>=(0x97+8568-0x220a)){z407efd0741[(0x1384+2756-0x1e44)]=zb9f7147b6c->zb15396a870[channel];}if(z69a8079db8>=(0x1dd6+660-0x2064)){z407efd0741[(0x14ef+2481-0x1e9b)]=zb9f7147b6c->zdd951fbe16[channel];}if(z69a8079db8>=(0x177+4166-0x11b6)){z407efd0741[(0x1812+2670-0x227a)]=zb9f7147b6c->z64fc736a62[channel];}if(z69a8079db8>=(0xd39+6184-0x2559)){z407efd0741[(0x49+1358-0x590)]=zb9f7147b6c->zaf2186d9ec[channel];}z69a8079db8=(uint32_t)mxGetPr(z3a4907dee5)[i]/(0x1a8a+2207-0x2309);if(((uint32_t)mxGetPr(z3a4907dee5)[i]%(0x8bb+904-0xc23))!=(0x326+4355-0x1429)){z69a8079db8=z69a8079db8+(0x585+3933-0x14e1);}z22c44e4cdd(z407efd0741,zbcc3fe600b,(0x968+57-0x981),z69a8079db8);out=(uint32_t*)ssGetOutputPortSignal(S,i);for(z26dbd73a5e=(0x3d2+5229-0x183f);z26dbd73a5e<z69a8079db8;z26dbd73a5e++){out[z26dbd73a5e]=zbcc3fe600b[z26dbd73a5e];}}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile z69e58993ac*zb9f7147b6c;zb9f7147b6c=(z69e58993ac*)(base+z9a3f261491);zb9f7147b6c->start=(uint32_t)(0x295+7747-0x20d8);
#endif
}
#include "sg_sfcn_glue.h"   

