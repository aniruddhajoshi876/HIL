// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x526+1423-0xab3)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spi_write_fifo_sf_2
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef  MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_callback_legacy.h"
#endif
#include "sg_printf.h"
enum{zf80bd68bc8,ID,CHANNEL,ze344b15ab1,PCI_SLOT,zdf24515981};
#define z533b11d03f           ssGetSFcnParam(S, zf80bd68bc8           )
#define z58f464b4bb                  ssGetSFcnParam(S, ID                  )
#define za9d8fb6bcf             ssGetSFcnParam(S, CHANNEL             )
#define z3832b85a32           ssGetSFcnParam(S, ze344b15ab1           )
#define ze7b39f8507            ssGetSFcnParam(S, PCI_SLOT            )
#define z2e6483d505            (0xa7+5413-0x15cc)
#define zc5ce4cb81a            (0xfc2+3519-0x1d81)
#define z2b17e2ee3b            (0x12fc+2962-0x1e8d)
#define z93d7dbe681       (0x4e1+2325-0xdf6)
#define z5bbcf8be2c          (0x204+9437-0x26df)
#define z9a3f261491              851968
static char msg[(0x5ca+8440-0x25c2)];struct z8e4b47c7a2{uint32_t z48d0bb18f6[(0x477+6331-0x1d12)];uint32_t z00d55f3f09[(0xa61+1491-0x1014)];uint32_t z29b8f4aa12[(0x191f+3148-0x254b)];uint32_t z12f528bf35[(0x13c6+3017-0x1f6f)];uint32_t z38c71b4bf1[(0x144f+2750-0x1eed)];uint32_t z5ba6171f0d[(0xffa+4550-0x21a0)];uint32_t zc9a3e36bdf[(0xd95+4243-0x1e08)];uint32_t z40bf21df8f[(0xbf1+3262-0x188f)];uint32_t z2e87e7e5d4[(0x18c2+2074-0x20bc)];uint32_t zcb493c8a03[(0x151d+394-0x1687)];uint32_t z045c082819[(0x1273+2621-0x1c90)];uint32_t ze2bbd49d5d[(0x579+2937-0x10d2)];uint32_t zf1dc9838ef[(0x28+6608-0x19d8)];uint32_t z7885bab821[(0xcd0+1586-0x12e2)];uint32_t version;uint32_t zf64b65d5a7;uint32_t z184c2a9653;uint32_t z46c2b7bc26;uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t z1b0476e135;uint32_t z90bc4b3324;uint32_t zfea0a3d037;uint32_t z83d556b26d;};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x12db+2670-0x1d49));ssSetNumDiscStates(S,(0xcbd+1511-0x12a4));ssSetNumInputPorts(S,(0x13f0+4574-0x25cc));ssSetInputPortWidth(S,(0x13b4+4194-0x2416),(0xf46+1272-0x143d));ssSetInputPortDataType(S,(0x1714+3065-0x230d),SS_UINT8);ssSetInputPortDirectFeedThrough(S,(0x68+9089-0x23e9),(0x1baf+2273-0x248f));ssSetInputPortRequiredContiguous(S,(0x5a4+1431-0xb3b),(0x700+7294-0x237d));ssSetInputPortWidth(S,(0x164b+1725-0x1d07),(0xfd9+3012-0x1a9e));ssSetInputPortDataType(S,(0x1284+3073-0x1e84),SS_UINT8);ssSetInputPortDirectFeedThrough(S,(0xe7a+6170-0x2693),(0x1235+4610-0x2436));ssSetInputPortRequiredContiguous(S,(0x11d0+2411-0x1b3a),(0x14c+6587-0x1b06));ssSetNumOutputPorts(S,(0x331+1350-0x877));ssSetNumSampleTimes(S,(0x9e6+3661-0x1832));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x33c+2014-0xb1a));ssSetNumNonsampledZCs(S,(0x33c+4006-0x12e2));for(i=(0x36d+2769-0xe3e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x3bc+2419-0xd2f));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x47d+3804-0x1359)]==-1.0){ssSetSampleTime(S,(0x961+6269-0x21de),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x9a2+4489-0x1b2b),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x326+6813-0x1dc3),mxGetPr(z3832b85a32)[(0x49b+5904-0x1bab)]);ssSetOffsetTime(S,(0x546+7989-0x247b),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile struct z8e4b47c7a2*zb9f7147b6c;uint32_t za43d9fed9a,z43c341facf,z97287efa46,zeeeba54a90;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x1cca+1093-0x210f)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x766+231-0x84d)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0x1049+3201-0x1cc9)){bus=(0x145f+2477-0x1e0c);slot=(int_T)mxGetPr(ze7b39f8507)[(0x1028+4557-0x21f5)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0xcb1+4513-0x1e52)];slot=(int_T)mxGetPr(ze7b39f8507)[(0xf3f+320-0x107e)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1987+1498-0x1f61)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}zb9f7147b6c=(volatile struct z8e4b47c7a2*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x3e6+1954-0xb88)],SG_FPGA_IO3XX_BAR2)+z9a3f261491);ssSetPWorkValue(S,z93d7dbe681,(void*)zb9f7147b6c);if(!sg_isModelInit()){za43d9fed9a=((zb9f7147b6c->version&3221225472)>>(0x1935+1199-0x1dc6));z43c341facf=((zb9f7147b6c->version&1072693248)>>(0xd09+906-0x108d));z97287efa46=((zb9f7147b6c->version&1047552)>>(0x3d9+5998-0x1b3d));zeeeba54a90=(zb9f7147b6c->version&(0xa2f+2287-0xf1f));if(za43d9fed9a==(0x107c+5158-0x24a0)&&z43c341facf==z9a3f261491&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x20\x53\x50\x49\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x2e\x25\x64\x20\x73\x74\x61\x72\x74\x65\x64\x2e" "\n",moduleId.devname,z97287efa46,zeeeba54a90);}else{sprintf(msg,"\x25\x73\x20\x57\x72\x6f\x6e\x67\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x50\x49\x20\x4d\x6f\x64\x75\x6c\x65\x2e" "\n" "\x20\x75\x6e\x69\x71\x75\x65\x49\x64\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x61\x6a\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x69\x6e\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x73\x74\x61\x74\x75\x73\x3a\x20\x30\x78\x25\x78" "\n",moduleId.devname,z43c341facf,z97287efa46,zeeeba54a90,za43d9fed9a);ssSetErrorStatus(S,msg);}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile struct z8e4b47c7a2*zb9f7147b6c;uint8_t*zb425515a78,*za8727e5143;uint8_t i;uint32_t channel;zb9f7147b6c=(volatile struct z8e4b47c7a2*)ssGetPWorkValue(S,z93d7dbe681);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x54+426-0x1fe)]-(0x320+2601-0xd48);za8727e5143=(uint8_t*)ssGetInputPortSignal(S,(0x1ca6+1011-0x2099));zb425515a78=(uint8_t*)ssGetInputPortSignal(S,(0x568+816-0x897));if(za8727e5143[(0x133b+2510-0x1d09)]>(0xe12+1911-0x1589)){while(zb9f7147b6c->zf1dc9838ef[channel]!=(0x1fdc+256-0x20dc));for(i=(0xbbc+4016-0x1b6c);i<za8727e5143[(0x43c+7802-0x22b6)];i++){zb9f7147b6c->z48d0bb18f6[channel]=zb425515a78[i];zb9f7147b6c->z184c2a9653=(0x224+5927-0x194a)<<channel;zb9f7147b6c->z184c2a9653=(0x11fb+537-0x1414);}zb9f7147b6c->z29b8f4aa12[channel]=za8727e5143[(0x1c86+255-0x1d85)];zb9f7147b6c->z46c2b7bc26|=((0x936+43-0x960)<<channel);zb9f7147b6c->z46c2b7bc26&=~((0xf70+3629-0x1d9c)<<channel);}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

