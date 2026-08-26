// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x6fc+1187-0xb9d)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO51X_write_v4_s
#include    "sg_io51X.h"
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S,(0x4eb+1084-0x927))
#define z702a26a5e9                ssGetSFcnParam(S,(0x1df5+1447-0x239b))
#define z3832b85a32           ssGetSFcnParam(S,(0x112f+1224-0x15f5))
#define ze6ed1ec117              ssGetSFcnParam(S,(0x1b98+2757-0x265a))
#define zaa6d563b18             ssGetSFcnParam(S,(0xbb9+6357-0x248a))
#define z43434943e0             ssGetSFcnParam(S,(0x9c1+3305-0x16a5))
#define zdf24515981          ((0x994+6070-0x2144))
#define z2e6483d505              ((0x809+7011-0x236c))
#define zc5ce4cb81a              ((0x1615+2992-0x21c5))
#define z2b17e2ee3b              ((0xefb+2399-0x185a))
static char msg[(0x803+7836-0x259f)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x7a8+1278-0xca6));ssSetNumDiscStates(S,(0x1b2+9450-0x269c));ssSetNumOutputPorts(S,(0x1378+860-0x16d4));ssSetNumInputPorts(S,(0x223d+672-0x24db));ssSetInputPortDataType(S,(0x3da+4589-0x15c7),SS_UINT32);ssSetInputPortWidth(S,(0xeb4+529-0x10c5),(0x12ec+517-0x14f0));ssSetInputPortDirectFeedThrough(S,(0x171a+3151-0x2369),(0x531+3066-0x112a));ssSetInputPortRequiredContiguous(S,(0xbe9+4107-0x1bf4),(0x417+6687-0x1e35));ssSetInputPortDataType(S,(0x1940+3149-0x258c),SS_UINT8);ssSetInputPortWidth(S,(0x1f4+5621-0x17e8),(int)mxGetPr(zaa6d563b18)[(0x2db+5070-0x16a9)]);ssSetInputPortDirectFeedThrough(S,(0x1077+4178-0x20c8),(0x646+351-0x7a4));ssSetInputPortRequiredContiguous(S,(0x286+3321-0xf7e),(0x1fe0+616-0x2247));ssSetNumSampleTimes(S,(0x1456+1484-0x1a21));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x95+2679-0xb0c));ssSetNumNonsampledZCs(S,(0x40b+8094-0x23a9));for(i=(0x892+2710-0x1328);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xdd2+2655-0x1831));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xa24+5571-0x1fe7)]==-1.0){ssSetSampleTime(S,(0x211b+1274-0x2615),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x933+1211-0xdee),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x101+6844-0x1bbd),mxGetPr(z3832b85a32)[(0x1353+4950-0x26a9)]);ssSetOffsetTime(S,(0xcb1+3031-0x1888),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE 
z4d30c8ca6d*z9efda8cb66=NULL;uint32_t za0d38ae598=(uint32_t)mxGetPr(ze13f49a01f)[(0xe92+4629-0x20a7)];int i,ch;uint32_t*z7b5c8c9301=(uint32_t*)ssGetInputPortSignal(S,(0x165+8856-0x23fd));uint8_t*data=(uint8_t*)ssGetInputPortSignal(S,(0xceb+3179-0x1955));uint32_t size;size=z7b5c8c9301[(0xfc7+3720-0x1e4f)];ch=(uint32_T)mxGetPr(ze6ed1ec117)[(0xd8+351-0x237)];z9efda8cb66=(z4d30c8ca6d*)sg_module_get_custom_data((int)mxGetPr(z43434943e0)[(0x7b5+6894-0x22a3)],za0d38ae598);if(z9efda8cb66==NULL){sprintf(msg,"\x49\x4f\x25\x64\x20\x57\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64" "\n",(int)mxGetPr(z43434943e0)[(0x1a6+185-0x25f)]);ssSetErrorStatus(S,msg);return;}volatile uint8_t*z3283caa368=(volatile uint8_t*)z9efda8cb66->z5fcf9921e0;if(size>(0x1086+2609-0x1ab7)){if(size>(int)mxGetPr(zaa6d563b18)[(0x2d5+5220-0x1739)]){ssSetErrorStatus(S,"\x54\x78\x20\x46\x49\x46\x4f\x20\x6f\x76\x65\x72\x66\x6c\x6f\x77" "\n");return;}z3283caa368[ze00d244ebe+ch*z4253d7befd]=(uint8_t)((0x83f+1049-0xb59)&(size>>(0x1530+403-0x16c3)*(0x1754+2891-0x2297)));z3283caa368[z92b8525715+ch*z4253d7befd]=(uint8_t)((0x2217+1399-0x268f)&(size>>(0x410+3854-0x131d)*(0x705+3980-0x1689)));z3283caa368[z0ad99d441b+ch*z4253d7befd]|=(uint8_t)((0x214a+788-0x2450)<<((0x90f+3073-0x1505)-(0x18+9430-0x24e6)));for(i=(0x9d6+4980-0x1d4a);i<size;i++){z2eecedfa7e(z9efda8cb66->z5fcf9921e0,ch-(0x230+4689-0x1480))=data[i];}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE   
#endif
}
#include "../common/libsg/sg_sfcn_glue.h"   

