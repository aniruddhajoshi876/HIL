// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x1247+5195-0x2690)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_crank_decoder_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include 	<stdint.h>
#include    <stdbool.h>
#include 	"simstruc.h" 
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
typedef enum{CHANNEL,ze344b15ab1,z6c561dc4d0,z9664ce1e38,z378bbbb5c0,zb6f6b332b9,z75dacb6973,z3143ab366a,zdac06097ed,zc386cafb7d,zb29d1d12c8,z8ffaaecdf5,zc900c56a8e,z1e15bc65ce,zd46cec07f1,ID,z88c63e0ba1,zdf24515981}zad377ef63a;
#define za9d8fb6bcf                        ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32                      ssGetSFcnParam(S, ze344b15ab1)
#define z7cd927ffe6                    ssGetSFcnParam(S, z6c561dc4d0) 
#define z399d208005            ssGetSFcnParam(S, z9664ce1e38) 
#define z95955aace8       ssGetSFcnParam(S, z378bbbb5c0) 
#define zdecf152cfe               ssGetSFcnParam(S, zb6f6b332b9) 
#define z0c9862abe7                 ssGetSFcnParam(S, z75dacb6973) 
#define z7cfa1d1990                      ssGetSFcnParam(S, z3143ab366a) 
#define z062ce87455             ssGetSFcnParam(S, zdac06097ed) 
#define z5bcc09d807            ssGetSFcnParam(S, zc386cafb7d) 
#define z35662a74b0                     ssGetSFcnParam(S, zb29d1d12c8) 
#define z5bf87896c2                  ssGetSFcnParam(S, z8ffaaecdf5) 
#define z8b15f1d2e8     ssGetSFcnParam(S, zc900c56a8e) 
#define zf267dbb0f0                     ssGetSFcnParam(S, z1e15bc65ce) 
#define zba7ad8dfa4                     ssGetSFcnParam(S, zd46cec07f1) 
#define z58f464b4bb                             ssGetSFcnParam(S, ID) 
#define za08eaecce0                      ssGetSFcnParam(S, z88c63e0ba1) 
#define z2e6483d505                         (0xef+7484-0x1e2b)
#define zc5ce4cb81a                         (0x1+9938-0x26d3)
#define z2b17e2ee3b                         (0x12d0+409-0x1468)
#define z0194338df7                    (0x1d26+329-0x1e6f)
#define z5bbcf8be2c                       (0xa2d+1503-0x100b)
static char msg[(0x496+520-0x59e)];typedef volatile struct{uint32_t version;uint32_t enable;uint32_t z58a8cb195b;uint32_t z230b1088f7[(0x39f+5934-0x1aad)];uint32_t z2ed09dc5c9[(0xdb+1757-0x798)];uint32_t z425a04401c[(0x2fb+3679-0x113a)];uint32_t z6fd270185b[(0x1043+2658-0x1a85)];uint32_t zd1cf58679f[(0x7f8+4193-0x1839)];uint32_t zcac75465c8[(0xda1+2125-0x15ce)];uint32_t z001486e71e[(0x7af+1988-0xf53)];uint32_t zde1716aa7f[(0xb3c+4249-0x1bb5)];uint32_t z5a010db02d[(0x1baa+2602-0x25b4)];uint32_t z9629f6fbd3[(0x16f1+846-0x1a1f)];uint32_t z28500d2aa2[(0x51f+7633-0x22d0)];uint32_t z592af79c90[(0x95b+3056-0x152b)];uint32_t z105955ee26;}z477f8d8ba4;static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xb3b+997-0xf20));ssSetNumDiscStates(S,(0x156b+435-0x171e));ssSetNumInputPorts(S,(0x259+2920-0xdc1));za0df33019b=(0xa77+5102-0x1e65);if(mxGetPr(z35662a74b0)[(0x22b+7795-0x209e)]){za0df33019b++;}if(mxGetPr(z5bf87896c2)[(0xf4f+5094-0x2335)]){za0df33019b++;}if(mxGetPr(z8b15f1d2e8)[(0x1530+1085-0x196d)]){za0df33019b++;}if(mxGetPr(zf267dbb0f0)[(0x1c7+7826-0x2059)]){za0df33019b++;}if(mxGetPr(zba7ad8dfa4)[(0x19c+2729-0xc45)]){za0df33019b++;}ssSetNumOutputPorts(S,za0df33019b);for(i=(0x24b3+445-0x2670);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));}ssSetNumSampleTimes(S,(0x99f+4669-0x1bdb));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa82+5149-0x1e9f));ssSetNumNonsampledZCs(S,(0xbbb+5686-0x21f1));for(i=(0x560+3571-0x1353);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x604+2468-0xfa8));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xecb+1768-0x15b3)]==-1.0){ssSetSampleTime(S,(0x1583+2378-0x1ecd),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x688+6662-0x208e),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x49b+6227-0x1cee),mxGetPr(z3832b85a32)[(0x1110+1085-0x154d)]);ssSetOffsetTime(S,(0x1783+904-0x1b0b),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z477f8d8ba4*z4a127fc0e7;void*bar2ptr;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x8b4+6172-0x20d0)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x1691+3165-0x22ee);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,CRANK_DECODER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x43\x72\x61\x6e\x6b\x20\x44\x65\x63\x6f\x64\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x71+3345-0xd82)],SG_FPGA_IO3XX_BAR2);z4a127fc0e7=(z477f8d8ba4*)((uintptr_t)bar2ptr+(uintptr_t)zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z4a127fc0e7);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z4a127fc0e7->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x43\x72\x61\x6e\x6b\x20\x44\x65\x63\x6f\x64\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif  
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t channel,enable,z13f5011671;double z230b1088f7,z64198f8f6d;double z7dab6f6958;z477f8d8ba4*z4a127fc0e7;z4a127fc0e7=(z477f8d8ba4*)(ssGetPWorkValue(S,z0194338df7));z7dab6f6958=(double)mxGetPr(za08eaecce0)[(0x6c1+2242-0xf83)];for(i=(0x115a+2402-0x1abc);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xd00+3552-0x1adf);z230b1088f7=(double)mxGetPr(z7cd927ffe6)[i];z64198f8f6d=(double)180.0/z230b1088f7;z4a127fc0e7->z230b1088f7[channel]=(uint32_t)z230b1088f7;z4a127fc0e7->z2ed09dc5c9[channel]=(uint32_t)mxGetPr(z399d208005)[i];z4a127fc0e7->z425a04401c[channel]=(uint32_t)((double)mxGetPr(zdecf152cfe)[i]/z64198f8f6d);z4a127fc0e7->z6fd270185b[channel]=(uint32_t)((double)mxGetPr(z0c9862abe7)[i]/z64198f8f6d);z4a127fc0e7->zd1cf58679f[channel]=(uint32_t)((double)mxGetPr(z7cfa1d1990)[i]/z64198f8f6d);z4a127fc0e7->zcac75465c8[channel]=(uint32_t)((double)mxGetPr(z062ce87455)[i]*z7dab6f6958);z4a127fc0e7->z001486e71e[channel]=(uint32_t)((double)mxGetPr(z5bcc09d807)[i]*z7dab6f6958);}z13f5011671=(0xf38+1639-0x159f);if(mxGetPr(z95955aace8)[(0x17e1+308-0x1915)]){for(i=(0xddb+1754-0x14b5);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xad3+4123-0x1aed);z13f5011671|=((0x968+727-0xc3e)<<channel);}}z4a127fc0e7->z105955ee26|=z13f5011671;enable=(0x1691+4112-0x26a1);for(i=(0x156+2815-0xc55);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xc72+750-0xf5f);enable|=((0x191c+1585-0x1f4c)<<channel);}z4a127fc0e7->enable|=enable;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z34a675f13b,zb871a780a7;double*round,*zf7ef2b3012,*zdfb7e3faaa,*zb1812b1e1e,*zc4ac91c294;double z7dab6f6958;double zd64a812a16[(0xf20+3159-0x1b76)],z31033a83bc[(0xfda+5369-0x24d2)];z477f8d8ba4*z4a127fc0e7;z4a127fc0e7=(z477f8d8ba4*)(ssGetPWorkValue(S,z0194338df7));z7dab6f6958=(double)mxGetPr(za08eaecce0)[(0x1bf2+2121-0x243b)];zb871a780a7=(0x1d1+269-0x2de);for(i=(0x988+6389-0x227d);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1a04+3157-0x2658);zb871a780a7|=((0x1b87+1826-0x22a8)<<channel);}z4a127fc0e7->z58a8cb195b=zb871a780a7;z4a127fc0e7->z58a8cb195b=(0x1382+1749-0x1a57);z34a675f13b=(0x381+6728-0x1dc9);if(mxGetPr(z35662a74b0)[(0x1384+3648-0x21c4)]){round=(double*)ssGetOutputPortSignal(S,z34a675f13b);z34a675f13b++;for(i=(0x1ed+1409-0x76e);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x418+2293-0xd0c);round[i]=(double)z4a127fc0e7->zde1716aa7f[channel];}}if(mxGetPr(z5bf87896c2)[(0x8b8+858-0xc12)]){zf7ef2b3012=(double*)ssGetOutputPortSignal(S,z34a675f13b);z34a675f13b++;for(i=(0x882+6590-0x2240);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xcc0+5635-0x22c2);zd64a812a16[(0x1260+4136-0x2288)]=(double)z4a127fc0e7->zde1716aa7f[channel];zf7ef2b3012[i]=((double)z4a127fc0e7->z5a010db02d[channel])*180.0/((double)mxGetPr(z7cd927ffe6)[i]);if(zd64a812a16[(0xd6a+3778-0x1c2c)]==(0x3e1+4941-0x172c)){zf7ef2b3012[i]=zf7ef2b3012[i]+(0x12e6+3343-0x1e8d);}}}if(mxGetPr(z8b15f1d2e8)[(0x1975+301-0x1aa2)]){zb1812b1e1e=(double*)ssGetOutputPortSignal(S,z34a675f13b);z34a675f13b++;for(i=(0x8db+5429-0x1e10);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x706+292-0x829);zd64a812a16[(0x518+5035-0x18c3)]=(double)z4a127fc0e7->zde1716aa7f[channel];z31033a83bc[(0x355+6474-0x1c9f)]=((double)z4a127fc0e7->z5a010db02d[channel])*180.0/((double)mxGetPr(z7cd927ffe6)[i]);if(zd64a812a16[(0x1bb9+507-0x1db4)]==(0x6e1+6027-0x1e6a)){z31033a83bc[(0x22d+1960-0x9d5)]=z31033a83bc[(0x7b8+7728-0x25e8)]+(0x6db+7347-0x2226);}zb1812b1e1e[i]=z31033a83bc[(0x629+8269-0x2676)]+(double)z4a127fc0e7->z28500d2aa2[channel]/(double)z4a127fc0e7->z9629f6fbd3[channel]*180.0/((double)mxGetPr(z7cd927ffe6)[i]);}}if(mxGetPr(zf267dbb0f0)[(0x1b24+612-0x1d88)]){zdfb7e3faaa=(double*)ssGetOutputPortSignal(S,z34a675f13b);z34a675f13b++;for(i=(0xc23+2577-0x1634);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x2539+180-0x25ec);zdfb7e3faaa[i]=60.0*1.0/(2.0*((double)mxGetPr(z7cd927ffe6)[i]))*z7dab6f6958/((double)z4a127fc0e7->z9629f6fbd3[channel]);}}if(mxGetPr(zba7ad8dfa4)[(0x4b2+773-0x7b7)]){zc4ac91c294=(double*)ssGetOutputPortSignal(S,z34a675f13b);z34a675f13b++;for(i=(0x1197+4132-0x21bb);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xe41+586-0x108a);zc4ac91c294[i]=(double)z4a127fc0e7->z592af79c90[channel];}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE  
z477f8d8ba4*z4a127fc0e7;z4a127fc0e7=(z477f8d8ba4*)(ssGetPWorkValue(S,z0194338df7));z4a127fc0e7->enable=(0xca4+5820-0x2360);
#endif
}
#include "sg_sfcn_glue.h"   

