// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x86d+2850-0x138d)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spi_sf_2
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
enum{zf80bd68bc8,ID,CHANNEL,ze344b15ab1,PCI_SLOT,z053e27f1a6,zfe3589821b,z13e3aff50f,z79c39f7a01,ze993564d8d,zec4978d7a5,z7ffc0e38b1,z9546341a16,z9468c4df6f,zdd6aeaaf6a,zb520353196,z7cffc2ae28,zdf24515981};
#define z533b11d03f           ssGetSFcnParam(S, zf80bd68bc8           )
#define z58f464b4bb                  ssGetSFcnParam(S, ID                  )
#define za9d8fb6bcf             ssGetSFcnParam(S, CHANNEL             )
#define z3832b85a32           ssGetSFcnParam(S, ze344b15ab1           )
#define ze7b39f8507            ssGetSFcnParam(S, PCI_SLOT            )
#define z8536354e66                ssGetSFcnParam(S, z053e27f1a6                )
#define z444df23a13           ssGetSFcnParam(S, zfe3589821b           )
#define z86af52d74e                ssGetSFcnParam(S, z13e3aff50f                )
#define z31fb671cb8                ssGetSFcnParam(S, z79c39f7a01                )
#define z2534ed2570     ssGetSFcnParam(S, ze993564d8d     )
#define z8a8fd515c5         ssGetSFcnParam(S, zec4978d7a5         )
#define z78c7242543          ssGetSFcnParam(S, z7ffc0e38b1          )
#define z8f58b8666c  ssGetSFcnParam(S, z9546341a16  )
#define z14ff49484e          ssGetSFcnParam(S, z9468c4df6f          )
#define z4fb8efe4cd           ssGetSFcnParam(S, zdd6aeaaf6a           )
#define z9b4ef96a45   ssGetSFcnParam(S, zb520353196   )
#define ze60bb5a28b      ssGetSFcnParam(S, z7cffc2ae28      )
#define z2e6483d505            (0xde4+3821-0x1cd1)
#define zc5ce4cb81a            (0x1ae1+2345-0x240a)
#define z2b17e2ee3b            (0x171+925-0x50d)
#define z93d7dbe681       (0x26b+8355-0x230e)
#define z5bbcf8be2c          (0x123f+1603-0x1880)
#define z9a3f261491              851968
static char msg[(0x116b+4534-0x2221)];struct z8e4b47c7a2{uint32_t z48d0bb18f6[(0x3b5+439-0x54c)];uint32_t z00d55f3f09[(0x820+2581-0x1215)];uint32_t z29b8f4aa12[(0x12a3+3427-0x1fe6)];uint32_t z12f528bf35[(0x35b+3553-0x111c)];uint32_t z38c71b4bf1[(0xf85+4538-0x211f)];uint32_t z5ba6171f0d[(0x740+2976-0x12c0)];uint32_t zc9a3e36bdf[(0xe2f+2381-0x175c)];uint32_t z40bf21df8f[(0xf40+3197-0x1b9d)];uint32_t z2e87e7e5d4[(0xa61+1065-0xe6a)];uint32_t zcb493c8a03[(0xa6b+71-0xa92)];uint32_t z045c082819[(0x1f26+1279-0x2405)];uint32_t ze2bbd49d5d[(0x71+2971-0xbec)];uint32_t zf1dc9838ef[(0x37+6883-0x1afa)];uint32_t z7885bab821[(0x7fa+3721-0x1663)];uint32_t version;uint32_t zf64b65d5a7;uint32_t z184c2a9653;uint32_t z46c2b7bc26;uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t z1b0476e135;uint32_t z90bc4b3324;uint32_t zfea0a3d037;uint32_t z83d556b26d;};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x82a+4389-0x194f));ssSetNumDiscStates(S,(0x737+3481-0x14d0));ssSetNumInputPorts(S,(0x1944+1723-0x1fff));ssSetNumOutputPorts(S,(0x96b+3286-0x1641));ssSetNumSampleTimes(S,(0x11ab+2568-0x1bb2));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xe0d+259-0xf10));ssSetNumNonsampledZCs(S,(0x522+98-0x584));for(i=(0x1c4d+387-0x1dd0);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4e1+2069-0xcf6));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x8c4+147-0x957)]==-1.0){ssSetSampleTime(S,(0xbe1+3376-0x1911),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1f2a+1860-0x266e),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x407+5344-0x18e7),mxGetPr(z3832b85a32)[(0x860+1869-0xfad)]);ssSetOffsetTime(S,(0x156b+2950-0x20f1),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile struct z8e4b47c7a2*zb9f7147b6c;uint32_t za43d9fed9a,z43c341facf,z97287efa46,zeeeba54a90;uint32_t i,channel,zbea4a89f24,zdc0d676974,zf64b65d5a7,z46c2b7bc26,z0939f56295,z90bc4b3324;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0xe9d+3650-0x1cdf)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0xd47+3099-0x1962)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0x565+1011-0x957)){bus=(0x6b4+5211-0x1b0f);slot=(int_T)mxGetPr(ze7b39f8507)[(0x5e2+307-0x715)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0x220c+1078-0x2642)];slot=(int_T)mxGetPr(ze7b39f8507)[(0xfda+2002-0x17ab)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x430+512-0x630)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}zb9f7147b6c=(volatile struct z8e4b47c7a2*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xec1+1149-0x133e)],SG_FPGA_IO3XX_BAR2)+z9a3f261491);ssSetPWorkValue(S,z93d7dbe681,(void*)zb9f7147b6c);if(!sg_isModelInit()){za43d9fed9a=((zb9f7147b6c->version&3221225472)>>(0xa4d+6209-0x2270));z43c341facf=((zb9f7147b6c->version&1072693248)>>(0x1bb3+2390-0x2503));z97287efa46=((zb9f7147b6c->version&1047552)>>(0x1a40+1902-0x21a4));zeeeba54a90=(zb9f7147b6c->version&(0x1afb+1817-0x1e15));if(za43d9fed9a==(0xbf4+5534-0x2190)&&z43c341facf==z9a3f261491&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x20\x53\x50\x49\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x2e\x25\x64\x20\x73\x74\x61\x72\x74\x65\x64\x2e" "\n",moduleId.devname,z97287efa46,zeeeba54a90);}else{sprintf(msg,"\x25\x73\x20\x57\x72\x6f\x6e\x67\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x50\x49\x20\x4d\x6f\x64\x75\x6c\x65\x2e" "\n" "\x20\x75\x6e\x69\x71\x75\x65\x49\x64\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x61\x6a\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x69\x6e\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x73\x74\x61\x74\x75\x73\x3a\x20\x30\x78\x25\x78" "\n",moduleId.devname,z43c341facf,z97287efa46,zeeeba54a90,za43d9fed9a);ssSetErrorStatus(S,msg);}zdc0d676974=(0x1af+9502-0x26cd);zbea4a89f24=(0x694+8214-0x26aa);z46c2b7bc26=(0x87f+4847-0x1b6e);zf64b65d5a7=(0x19b5+1512-0x1f9d);z0939f56295=(0x1a09+582-0x1c4f);z90bc4b3324=(0x1cc+8336-0x225c);for(i=(0x1060+2367-0x199f);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x167b+1330-0x1bac);if((uint32_t)mxGetPr(z8536354e66)[(0x556+6756-0x1fba)]==(0x1a74+2773-0x2548)){zf64b65d5a7|=((0x1d2+1378-0x733)<<channel);zb9f7147b6c->z12f528bf35[channel]=(uint32_t)mxGetPr(z8a8fd515c5)[i];zb9f7147b6c->z38c71b4bf1[channel]=(uint32_t)mxGetPr(z78c7242543)[i];zb9f7147b6c->zc9a3e36bdf[channel]=(uint32_t)mxGetPr(z14ff49484e)[i];zb9f7147b6c->z40bf21df8f[channel]=(uint32_t)mxGetPr(z4fb8efe4cd)[i];zb9f7147b6c->z5ba6171f0d[channel]=(uint32_t)mxGetPr(z8f58b8666c)[i];zb9f7147b6c->z7885bab821[channel]=(uint32_t)mxGetPr(z9b4ef96a45)[i];}else{if((uint32_t)mxGetPr(ze60bb5a28b)[(0x7d0+5177-0x1c09)]){z90bc4b3324|=((0x85d+5082-0x1c36)<<channel);}}if((uint32_t)mxGetPr(z444df23a13)[(0x215f+135-0x21e6)]==(0x964+7419-0x265e)){z0939f56295|=((0x164f+3244-0x22fa)<<channel);}else{z46c2b7bc26|=((0x6bb+2803-0x11ad)<<channel);zb9f7147b6c->z29b8f4aa12[channel]=(uint32_t)mxGetPr(z2534ed2570)[i];}zb9f7147b6c->z2e87e7e5d4[channel]=(0x252+9079-0x25c1);zdc0d676974=(uint32_t)mxGetPr(z86af52d74e)[i]<<channel;zbea4a89f24=(uint32_t)mxGetPr(z31fb671cb8)[i]<<channel;}zb9f7147b6c->zdc0d676974|=zdc0d676974;zb9f7147b6c->zbea4a89f24|=zbea4a89f24;zb9f7147b6c->z90bc4b3324|=z90bc4b3324;zb9f7147b6c->zfea0a3d037|=z0939f56295;zb9f7147b6c->zf64b65d5a7|=zf64b65d5a7;zb9f7147b6c->z46c2b7bc26|=z46c2b7bc26;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

