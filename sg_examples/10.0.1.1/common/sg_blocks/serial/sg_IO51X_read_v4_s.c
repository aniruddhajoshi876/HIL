// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x115d+5430-0x2691)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO51X_read_v4_s
#include    "sg_io51X.h"
#include "sg_callback.h"
#ifndef     MATLAB_MEX_FILE
#include    "sg_target.h"
#include    "sg_printf.h"
#include    "sg_module_types.h"
#ifdef __QNX__
#include    <sys/neutrino.h>
#endif 
#endif
#define ze13f49a01f           ssGetSFcnParam(S,(0x2058+208-0x2128))
#define z702a26a5e9                ssGetSFcnParam(S,(0x16b3+3175-0x2319))
#define z3832b85a32           ssGetSFcnParam(S,(0xd2a+4786-0x1fda))
#define za9d8fb6bcf             ssGetSFcnParam(S,(0xb26+6466-0x2465))
#define z8b97cfc998            ssGetSFcnParam(S,(0x10d0+406-0x1262))
#define z43434943e0             ssGetSFcnParam(S,(0x197b+3016-0x253e))
#define zdf24515981          ((0x3d1+283-0x4e6))
#define z2e6483d505              ((0x114d+3109-0x1d72))
#define zc5ce4cb81a              ((0x10ec+2950-0x1c72))
#define z2b17e2ee3b              ((0x6d2+3870-0x15f0))
static char msg[(0x2a4+8644-0x2368)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1d18+2261-0x25ed));ssSetNumDiscStates(S,(0x176d+466-0x193f));ssSetNumOutputPorts(S,(0xe38+5779-0x24c9));ssSetOutputPortDataType(S,(0x8f5+1573-0xf1a),SS_UINT32);ssSetOutputPortWidth(S,(0x1b21+952-0x1ed9),(0x84f+6599-0x2215));ssSetOutputPortDataType(S,(0x1d5c+541-0x1f78),SS_UINT8);ssSetOutputPortWidth(S,(0xea5+4424-0x1fec),(int)mxGetPr(z8b97cfc998)[(0xb54+392-0xcdc)]);ssSetNumInputPorts(S,(0x1d9f+181-0x1e54));ssSetNumSampleTimes(S,(0x632+2265-0xf0a));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x18ec+236-0x19d8));ssSetNumNonsampledZCs(S,(0x170b+2815-0x220a));for(i=(0x15+3494-0xdbb);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x86d+4148-0x18a1));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1f7b+1884-0x26d7)]==-1.0){ssSetSampleTime(S,(0x1819+1906-0x1f8b),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1c3b+1744-0x230b),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xdf0+5815-0x24a7),mxGetPr(z3832b85a32)[(0x1994+433-0x1b45)]);ssSetOffsetTime(S,(0x829+2237-0x10e6),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int ch,za0d38ae598;uint32_t z52754d10b7;volatile uint8_t*z3283caa368;z4d30c8ca6d*z9efda8cb66=NULL;ch=(int)mxGetPr(za9d8fb6bcf)[(0x124b+2164-0x1abf)]-(0x836+6324-0x20e9);za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0xe39+4876-0x2145)];z9efda8cb66=(z4d30c8ca6d*)sg_module_get_custom_data((int)mxGetPr(z43434943e0)[(0x10b3+554-0x12dd)],za0d38ae598);if(z9efda8cb66==NULL){sprintf(msg,"\x49\x4f\x25\x64\x20\x73\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64" "\n",(int)mxGetPr(z43434943e0)[(0xca2+2520-0x167a)]);ssSetErrorStatus(S,msg);return;}z3283caa368=(volatile uint8_t*)z9efda8cb66->z5fcf9921e0;if(z9efda8cb66->z9c3f63b18d==false){ssSetErrorStatus(S,"\x54\x68\x72\x65\x61\x64\x20\x69\x73\x20\x6e\x6f\x74\x20\x72\x75\x6e\x6e\x69\x6e\x67");return;}z9efda8cb66->z6cbb5714e1[ch].buffer=calloc((int)mxGetPr(z8b97cfc998)[(0x27+3844-0xf2b)],sizeof(uint8_t));z9efda8cb66->z6cbb5714e1[ch].z102e76cb71=z9efda8cb66->z6cbb5714e1[ch].buffer+(int)mxGetPr(z8b97cfc998)[(0x7b7+4227-0x183a)]-(0x58f+5231-0x19fd);z9efda8cb66->z6cbb5714e1[ch].z7b5c8c9301=(0x1afc+1079-0x1f33);z9efda8cb66->z6cbb5714e1[ch].head=z9efda8cb66->z6cbb5714e1[ch].buffer;z9efda8cb66->z6cbb5714e1[ch].tail=z9efda8cb66->z6cbb5714e1[ch].buffer;z9efda8cb66->z9331cd8a61++;SG_PRINTF(DEBUG,"\x42\x75\x66\x66\x65\x72\x20\x25\x70\x2c\x20\x4d\x75\x74\x65\x78\x20\x25\x70" "\n",z9efda8cb66->z6cbb5714e1[ch].buffer,z9efda8cb66->mutex);SG_PRINTF(DEBUG,"\x42\x75\x66\x66\x65\x72\x20\x65\x6e\x64\x20\x25\x70" "\n",z9efda8cb66->z6cbb5714e1[ch].z102e76cb71);z10de5338a4(z9efda8cb66->z5fcf9921e0,ch)=(0x25b+1255-0x740);sg_wait_s(0.1);z3283caa368[z0ad99d441b+(ch+(0xd7+5160-0x14fe))*z4253d7befd]=(0xa6f+5380-0x1f2b);sg_wait_s(0.1);z3283caa368[z0d97bf448f+(ch+(0x1889+2135-0x20df))*z4253d7befd]=(0xc49+998-0xf4f);z3283caa368[zd51c1c41d2+(ch+(0x1720+3229-0x23bc))*z4253d7befd]=(0x1072+5316-0x2526);z3283caa368[z740cd938fc+(ch+(0x1d7+1515-0x7c1))*z4253d7befd]=(0x28+4949-0x136d);z3283caa368[z2a002e110d+(ch+(0xf47+4922-0x2280))*z4253d7befd]=(0x1375+1131-0x1761);z3283caa368[z5267f6fa1c+(ch+(0x49b+2640-0xeea))*z4253d7befd]=(0x675+2672-0x1005);z52754d10b7=ze457f812cb(z9efda8cb66->z5fcf9921e0);z52754d10b7|=(0xb+2832-0xb17)<<((0x18b8+1557-0x1ec9)*ch);z52754d10b7|=(0x15b8+3016-0x2178)<<((0x15f4+3626-0x241a)*ch);ze457f812cb(z9efda8cb66->z5fcf9921e0)=z52754d10b7;SG_PRINTF(DEBUG,"\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74\x20\x64\x6f\x6e\x65" "\n");
#endif 
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE          
z4d30c8ca6d*z9efda8cb66=NULL;uint8_t*zf68649b2d6;uint32_t*zc553d38c2f,z7b5c8c9301;int i;int ch=(int)mxGetPr(za9d8fb6bcf)[(0x171+6465-0x1ab2)]-(0x1e79+241-0x1f69);int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x53c+4151-0x1573)];zc553d38c2f=(uint32_t*)ssGetOutputPortSignal(S,(0xf6d+3466-0x1cf7));zf68649b2d6=(uint8_t*)ssGetOutputPortSignal(S,(0x1353+2608-0x1d82));z9efda8cb66=(z4d30c8ca6d*)sg_module_get_custom_data((int)mxGetPr(z43434943e0)[(0x8bc+2739-0x136f)],za0d38ae598);if(z9efda8cb66==NULL){sprintf(msg,"\x49\x4f\x25\x64\x20\x73\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64" "\n",(int)mxGetPr(z43434943e0)[(0x11d1+1200-0x1681)]);ssSetErrorStatus(S,msg);return;}sg_lockMutex(z9efda8cb66->mutex);z7b5c8c9301=z9efda8cb66->z6cbb5714e1[ch].z7b5c8c9301;if(z7b5c8c9301>(uint32_t)mxGetPr(z8b97cfc998)[(0x59a+859-0x8f5)]){sg_unlockMutex(z9efda8cb66->mutex);sprintf(msg,"\x52\x78\x20\x46\x49\x46\x4f\x20\x6f\x76\x65\x72\x66\x6c\x6f\x77\x20\x63\x68\x20\x25\x64" "\n",ch+(0xebd+4070-0x1ea2));ssSetErrorStatus(S,msg);return;}if(z7b5c8c9301>(0xa5+3355-0xdc0)){for(i=(0x411+4601-0x160a);i<z7b5c8c9301;i++){zf68649b2d6[i]=*(z9efda8cb66->z6cbb5714e1[ch].tail);if(z9efda8cb66->z6cbb5714e1[ch].tail==z9efda8cb66->z6cbb5714e1[ch].z102e76cb71){z9efda8cb66->z6cbb5714e1[ch].tail=z9efda8cb66->z6cbb5714e1[ch].buffer;}else{z9efda8cb66->z6cbb5714e1[ch].tail++;}}z9efda8cb66->z6cbb5714e1[ch].z7b5c8c9301-=z7b5c8c9301;zc553d38c2f[(0xd40+1473-0x1301)]=z7b5c8c9301;}else{zc553d38c2f[(0x1416+4124-0x2432)]=(0x733+4075-0x171e);}sg_unlockMutex(z9efda8cb66->mutex);
#endif
}static void sg_ModelStop(SimStruct*S){}
#include "../common/libsg/sg_sfcn_glue.h"   

