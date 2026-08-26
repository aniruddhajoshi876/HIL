// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL    (0x5da+4719-0x1847)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME     sg_fpga_pc_sf_1
#include  <stddef.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <stdbool.h>
#include  "simstruc.h"
#ifdef    MATLAB_MEX_FILE
#include  "mex.h"
#endif
#ifndef   MATLAB_MEX_FILE
#include  "sg_common.h"
#include  "sg_fpga_io3xx_util.h"
#include  "sg_printf.h"
#endif
#include  "sg_callback.h"
typedef enum{zfaa050b79d,ze344b15ab1,CHANNEL,zca57a609ce,zf33f443f94,z0209802352,z2ec6a0fe4b,zc5ab9c6dd5,zcf96485402,zd0c1f0310a,z24bd2ab9fe,z564c37ed72,z0d949c5665,z0084a4c290,zfca77790f8,zac8c0ff69b,zd36b1349d1,zdf24515981}z6bdd4f4292;
#define ze13f49a01f               ssGetSFcnParam(S, zfaa050b79d            )
#define z3832b85a32               ssGetSFcnParam(S, ze344b15ab1            )
#define za9d8fb6bcf                 ssGetSFcnParam(S, CHANNEL              )
#define zf7b1b30194             ssGetSFcnParam(S, zca57a609ce          )
#define z98052cd582          ssGetSFcnParam(S, zf33f443f94       )
#define z341cc063c7         ssGetSFcnParam(S, z0209802352      )
#define zea3152aacd        ssGetSFcnParam(S, z2ec6a0fe4b     )
#define zded4055429              ssGetSFcnParam(S, zc5ab9c6dd5           )
#define z48c3f71229                  ssGetSFcnParam(S, zcf96485402               )
#define z3cf19bc9cb         ssGetSFcnParam(S, zd0c1f0310a      )
#define ze60f29c132           ssGetSFcnParam(S, z24bd2ab9fe        )
#define z740c5a0791          ssGetSFcnParam(S, z564c37ed72       )
#define zab70a367c8      ssGetSFcnParam(S, z0d949c5665   )
#define z8f32a49296              ssGetSFcnParam(S, z0084a4c290           )
#define z52d058809b             ssGetSFcnParam(S, zfca77790f8          )
#define z19b9dfa260          ssGetSFcnParam(S, zac8c0ff69b       )
#define z1120e7330e                ssGetSFcnParam(S, zd36b1349d1             )
enum zbb1f615c1d{z3250bb2679};enum z93bcf30780{z8a85396f5b};enum zb06a9f15ae{z00deac365e,z54fb9b273c,z9cbfedf63b};
#define z5bbcf8be2c          (0x710+3325-0x140c)
static char msg[(0x8c6+5860-0x1eaa)];
#define zc4e765037f                (0xc8+1775-0x7b7)  
#define z29fa06a461            (0xc66+5907-0x2371)  
#define z35a53925da               (0x9a4+686-0xc48)  
#define z0b78372df4                (0x183d+1270-0x1d27)  
#define zb16a26c623            (0x1da8+1353-0x22e4)  
#define z8d51c5daa7               (0x7cd+307-0x8f2)  
#define z4a4809de33                    (0x7bd+2214-0x1053)  
#define zd9b77b668a               (0x13e2+1798-0x1ad7)  
#define zb76caa6e24                 (0xee3+4751-0x2172)  
#define z8d77ccebac              (0x68f+7178-0x2298)  
typedef volatile struct{uint32_t z4ecb2ff0e5[(0x277+5424-0x1787)];uint32_t z1121ccbac0[(0x15dc+2115-0x1dff)];uint32_t version;}z3cf7429d62;static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x764+926-0xb02));ssSetNumDiscStates(S,(0x1870+77-0x18bd));za0df33019b=(0x6aa+5374-0x1ba8);if((uint32_t)mxGetPr(z740c5a0791)[(0xc5c+1860-0x13a0)]){za0df33019b++;}if((uint32_t)mxGetPr(zab70a367c8)[(0x8ea+6443-0x2215)]){za0df33019b++;}ssSetNumInputPorts(S,za0df33019b);za0df33019b=(0xcc9+1150-0x1147);if((uint32_t)mxGetPr(z740c5a0791)[(0x67c+5718-0x1cd2)]){ssSetInputPortDataType(S,za0df33019b,SS_BOOLEAN);ssSetInputPortWidth(S,za0df33019b,(0x10a5+3125-0x1cd9));ssSetInputPortDirectFeedThrough(S,za0df33019b,(0x292+6280-0x1b19));ssSetInputPortRequiredContiguous(S,za0df33019b,(0x1fc+3268-0xebf));za0df33019b++;}if((uint32_t)mxGetPr(zab70a367c8)[(0x1452+3478-0x21e8)]){ssSetInputPortDataType(S,za0df33019b,SS_BOOLEAN);ssSetInputPortWidth(S,za0df33019b,mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,za0df33019b,(0x20cc+1520-0x26bb));ssSetInputPortRequiredContiguous(S,za0df33019b,(0x19e0+335-0x1b2e));za0df33019b++;}za0df33019b=(0xf99+448-0x1159);if((uint32_t)mxGetPr(z8f32a49296)[(0xdd4+2483-0x1787)]){za0df33019b++;}if((uint32_t)mxGetPr(z52d058809b)[(0xbd6+786-0xee8)]){za0df33019b++;}ssSetNumOutputPorts(S,za0df33019b);za0df33019b=(0x6cc+7001-0x2225);if((uint32_t)mxGetPr(z8f32a49296)[(0x1099+3790-0x1f67)]){ssSetOutputPortWidth(S,za0df33019b,mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,za0df33019b,SS_BOOLEAN);za0df33019b++;}if((uint32_t)mxGetPr(z52d058809b)[(0xfa3+1069-0x13d0)]){ssSetOutputPortWidth(S,za0df33019b,mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,za0df33019b,SS_INT32);za0df33019b++;}ssSetNumSampleTimes(S,(0x1bd3+466-0x1da4));ssSetNumRWork(S,z8a85396f5b);ssSetNumIWork(S,z3250bb2679);ssSetNumPWork(S,z9cbfedf63b);ssSetNumModes(S,(0xd3a+3284-0x1a0e));ssSetNumNonsampledZCs(S,(0x532+8072-0x24ba));for(i=(0x494+7778-0x22f6);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x16f7+3108-0x231b));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1009+2047-0x1808)]==-1.0){ssSetSampleTime(S,(0x1394+4790-0x264a),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x102f+539-0x124a),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x112+2494-0xad0),mxGetPr(z3832b85a32)[(0x1ed3+257-0x1fd4)]);ssSetOffsetTime(S,(0x3aa+986-0x784),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z3cf7429d62*z5239b7d633;pulsecounterState_t*z0f93139b4e;z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0xb86+3083-0x1791)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x11a7+1482-0x1771)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0xad4+901-0xe59);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,PULSECOUNTER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x50\x75\x6c\x73\x65\x63\x6f\x75\x6e\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z5239b7d633=(z3cf7429d62*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z00deac365e,(void*)z5239b7d633);io3xxGetPointerPulsecounterStateSgLib((int)mxGetPr(ze13f49a01f)[(0x8ed+5853-0x1fca)],&z0f93139b4e);ssSetPWorkValue(S,z54fb9b273c,(void*)z0f93139b4e);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z5239b7d633->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x50\x75\x6c\x73\x65\x63\x6f\x75\x6e\x74\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,z812c65ff2f;uint32_t channel,zf1a60f345d,z7554ac54ce,zf70773edfa,z3d8ff8d335;bool zdadf03c865,zea3d6fb5e6,z6ea885c9a7,z402f7615e0,zc5bdde1c97;z3cf7429d62*z5239b7d633=(z3cf7429d62*)ssGetPWorkValue(S,z00deac365e);pulsecounterState_t*z0f93139b4e=(pulsecounterState_t*)ssGetPWorkValue(S,z54fb9b273c);for(i=(0x11e7+4776-0x248f);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x17f3+1464-0x1daa);zdadf03c865=(0x18+3748-0xebc);zea3d6fb5e6=(0x695+3474-0x1427);z6ea885c9a7=(0x221+9216-0x2621);zc5bdde1c97=(0xe55+5217-0x22b6);z402f7615e0=(0x5d+1107-0x4b0);if((uint32_t)mxGetPr(zf7b1b30194)[(0xf82+2146-0x17e4)]==(0x44f+4296-0x1516)){if((uint32_t)mxGetPr(ze60f29c132)[(0x1520+2153-0x1d89)]==(0x22c3+248-0x23ba)){zdadf03c865=(0x19af+1594-0x1fe8);}if((uint32_t)mxGetPr(ze60f29c132)[(0xf4f+1821-0x166c)]==(0x16f0+1125-0x1b53)){zea3d6fb5e6=(0x1a83+3118-0x26b0);}if((uint32_t)mxGetPr(ze60f29c132)[(0x7e6+1919-0xf65)]==(0xaa4+6963-0x25d4)){z6ea885c9a7=(0x11f8+2778-0x1cd1);}if(!(uint32_t)mxGetPr(zab70a367c8)[(0x243+8316-0x22bf)]){if((uint32_t)mxGetPr(z48c3f71229)[(0x10c0+700-0x137c)]==(0xe3+5600-0x16c1)){zc5bdde1c97=(0xd63+5513-0x22eb);}else if((uint32_t)mxGetPr(zded4055429)[(0x170c+886-0x1a82)]==(0x291+890-0x60a)){z402f7615e0=(0x2287+875-0x25f1);}}}if((uint32_t)mxGetPr(zf7b1b30194)[(0xf8f+5693-0x25cc)]==(0x63d+2645-0x1090)){for(z812c65ff2f=(0xd99+1028-0x119d);z812c65ff2f<mxGetN(z98052cd582);z812c65ff2f++){zf1a60f345d=(uint32_t)mxGetPr(z98052cd582)[z812c65ff2f]-(0x630+5232-0x1a9f);if(channel==zf1a60f345d){zdadf03c865=(0x18a1+2594-0x22c2);}}for(z812c65ff2f=(0x12e8+469-0x14bd);z812c65ff2f<mxGetN(z341cc063c7);z812c65ff2f++){z7554ac54ce=(uint32_t)mxGetPr(z341cc063c7)[z812c65ff2f]-(0x5d5+6126-0x1dc2);if(channel==z7554ac54ce){zea3d6fb5e6=(0x1f5+4060-0x11d0);}}for(z812c65ff2f=(0x13c+3402-0xe86);z812c65ff2f<mxGetN(zea3152aacd);z812c65ff2f++){zf70773edfa=(uint32_t)mxGetPr(zea3152aacd)[z812c65ff2f]-(0x201+8105-0x21a9);if(channel==zf70773edfa){z6ea885c9a7=(0xec+9417-0x25b4);}}if(!(uint32_t)mxGetPr(zab70a367c8)[(0xc57+4999-0x1fde)]){for(z812c65ff2f=(0xc65+5870-0x2353);z812c65ff2f<mxGetN(z3cf19bc9cb);z812c65ff2f++){z3d8ff8d335=(uint32_t)mxGetPr(z3cf19bc9cb)[z812c65ff2f]-(0x5b5+3332-0x12b8);if(channel==z3d8ff8d335){z402f7615e0=(0x5f4+7241-0x223c);}}}}z0f93139b4e->operationReg[channel]=(uint32_t)(mxGetPr(z1120e7330e)[(0x731+2064-0xf41)]*mxGetPr(z19b9dfa260)[(0x113f+4896-0x245f)])<<zc4e765037f;if(zdadf03c865){z0f93139b4e->operationReg[channel]|=(0x158a+696-0x1841)<<z29fa06a461;}if(zea3d6fb5e6){z0f93139b4e->operationReg[channel]|=(0xb5+7266-0x1d15)<<z29fa06a461;}if(z6ea885c9a7){z0f93139b4e->operationReg[channel]|=(0x15d9+3841-0x24d7)<<z29fa06a461;}if(!(uint32_t)mxGetPr(zab70a367c8)[(0x1162+2789-0x1c47)]){if(zc5bdde1c97){z0f93139b4e->operationReg[channel]|=((0x1015+5295-0x24c3)<<zb16a26c623);}else if(z402f7615e0){z0f93139b4e->operationReg[channel]|=((0x131f+2240-0x1bde)<<z0b78372df4);}}z0f93139b4e->operationReg[channel]|=((0xe32+1079-0x1268)<<z4a4809de33);z5239b7d633->z4ecb2ff0e5[channel]=z0f93139b4e->operationReg[channel];}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t*zcd01d4071d;bool*reset,*direction,*zf989bd09ee;uint32_t channel,i,z0add1d1c25,z9605869eec=(0xbf4+4975-0x1f63);z3cf7429d62*z5239b7d633=(z3cf7429d62*)ssGetPWorkValue(S,z00deac365e);pulsecounterState_t*z0f93139b4e=(pulsecounterState_t*)ssGetPWorkValue(S,z54fb9b273c);z0add1d1c25=(0x326+7718-0x214c);reset=NULL;direction=NULL;if((uint32_t)mxGetPr(z740c5a0791)[(0xb77+3703-0x19ee)]){reset=(bool*)ssGetInputPortSignal(S,z0add1d1c25);z0add1d1c25++;}if((uint32_t)mxGetPr(zab70a367c8)[(0x124b+3213-0x1ed8)]){direction=(bool*)ssGetInputPortSignal(S,z0add1d1c25);z0add1d1c25++;}z0add1d1c25=(0x1551+1236-0x1a25);zf989bd09ee=NULL;zcd01d4071d=NULL;if((uint32_t)mxGetPr(z8f32a49296)[(0x1221+2317-0x1b2e)]){zf989bd09ee=(bool*)ssGetOutputPortSignal(S,z0add1d1c25);z0add1d1c25++;}if((uint32_t)mxGetPr(z52d058809b)[(0x1392+4307-0x2465)]){zcd01d4071d=(int32_t*)ssGetOutputPortSignal(S,z0add1d1c25);z0add1d1c25++;}for(i=(0x247f+361-0x25e8);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1d93+1379-0x22f5);if((uint32_t)mxGetPr(z740c5a0791)[(0x142a+819-0x175d)]){if(reset[(0x1487+3659-0x22d2)]){z0f93139b4e->operationReg[channel]|=((0xc43+3642-0x1a7c)<<z4a4809de33);}else{z0f93139b4e->operationReg[channel]&=~((0x24b4+505-0x26ac)<<z4a4809de33);}}else{z0f93139b4e->operationReg[channel]&=~((0xe8b+2760-0x1952)<<z4a4809de33);}if((uint32_t)mxGetPr(zab70a367c8)[(0x17fb+2832-0x230b)]){if(direction[i]){z0f93139b4e->operationReg[channel]|=((0x9d2+7398-0x26b7)<<z0b78372df4);}else{z0f93139b4e->operationReg[channel]&=~((0x21d9+311-0x230f)<<z0b78372df4);}}z5239b7d633->z4ecb2ff0e5[channel]=z0f93139b4e->operationReg[channel];z9605869eec=z5239b7d633->z1121ccbac0[channel];if((uint32_t)mxGetPr(z8f32a49296)[(0x700+3709-0x157d)]){zf989bd09ee[i]=(bool)(z9605869eec&(0x1526+384-0x16a5));}if((uint32_t)mxGetPr(z52d058809b)[(0x1062+2711-0x1af9)]){zcd01d4071d[i]=(int32_t)z9605869eec>>z8d77ccebac;}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

