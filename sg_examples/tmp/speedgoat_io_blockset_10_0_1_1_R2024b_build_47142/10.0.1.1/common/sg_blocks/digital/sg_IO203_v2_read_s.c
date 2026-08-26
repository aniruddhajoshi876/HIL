// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x119+8348-0x21b3)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO203_v2_read_s
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdbool.h>
#include "sg_io203_v2.h"
#include 	"simstruc.h" 
#ifndef MATLAB_MEX_FILE
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#else
#include "mex.h"
#endif
#include "sg_callback.h"
#define zdf24515981          ((0x10d2+3027-0x1c9e))
#define zf22006b8b3            ssGetSFcnParam(S,(0xe5d+4387-0x1f80))
#define z7945f7753b        ssGetSFcnParam(S,(0x4a4+606-0x701))
#define z10e6897daf          ssGetSFcnParam(S,(0x798+5996-0x1f02))
#define z3832b85a32           ssGetSFcnParam(S,(0x18a1+1836-0x1fca))
#define ze13f49a01f       	ssGetSFcnParam(S,(0x2d7+8048-0x2243))
#define z702a26a5e9                ssGetSFcnParam(S,(0x139f+2070-0x1bb0))
#define z4848d060ef           ssGetSFcnParam(S,(0x2c1+7896-0x2193))
#define z2e6483d505              ((0x2b6+722-0x588))
#define zc5ce4cb81a              ((0xd8+7304-0x1d60))
#define z2b17e2ee3b              ((0x171b+3342-0x2429))
#define THRESHOLD               0.5
static char_T msg[(0x183+769-0x384)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;uint8_t z23caebc4cc=(0xb8c+5762-0x220e);uint8_t ze97179dd68=(0x2bd+3262-0xf7b);uint8_t z336107e3a8=(0x17dc+2566-0x21e2);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1b10+2471-0x24b7));ssSetNumDiscStates(S,(0x10b+4536-0x12c3));z23caebc4cc=mxGetPr(z7945f7753b)[(0x224b+113-0x22bc)];ze97179dd68=(uint8_t)mxGetPr(z4848d060ef)[(0x16f0+1772-0x1ddc)];z336107e3a8=(uint8_t)mxGetPr(zf22006b8b3)[(0x8c4+1990-0x108a)];if(!ssSetNumInputPorts(S,(0xed6+1620-0x152a)))return;switch(z336107e3a8){case(0x1e4b+748-0x2136):if(!ssSetNumOutputPorts(S,(0x155c+1344-0x1a9b)))return;ssSetOutputPortWidth(S,(0xb99+5649-0x21aa),(0xb28+422-0xc8e));switch(ze97179dd68){case(0x15fa+12-0x1605):ssSetOutputPortDataType(S,(0xcb3+4967-0x201a),SS_DOUBLE);break;case(0x1237+1185-0x16d6):ssSetOutputPortDataType(S,(0x1501+852-0x1855),SS_BOOLEAN);break;}break;case(0x208f+2-0x208f):if(!ssSetNumOutputPorts(S,z23caebc4cc))return;for(i=(0x509+4742-0x178f);i<z23caebc4cc;i++){ssSetOutputPortWidth(S,i,(0x2293+268-0x239e));switch(ze97179dd68){case(0x19d8+1526-0x1fcd):ssSetOutputPortDataType(S,i,SS_DOUBLE);break;case(0x294+7126-0x1e68):ssSetOutputPortDataType(S,i,SS_BOOLEAN);break;}}break;default:if(!ssSetNumOutputPorts(S,(0xc0a+6535-0x2591)))return;break;}ssSetNumSampleTimes(S,(0x1334+2091-0x1b5e));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1143+2308-0x1a47));ssSetNumNonsampledZCs(S,(0x342+5447-0x1889));for(i=(0x7d5+371-0x948);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x6b0+6521-0x2029));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x988+7239-0x25cf)]==-1.0){ssSetSampleTime(S,(0xe14+1721-0x14cd),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x17b3+3133-0x23f0),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1a48+2-0x1a4a),mxGetPr(z3832b85a32)[(0x15ff+4278-0x26b5)]);ssSetOffsetTime(S,(0x1bf6+1963-0x23a1),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t i=(0x138f+2746-0x1e49);uint8_t za0d38ae598;uint8_t zb220d7e807=mxGetPr(z7945f7753b)[(0x803+5382-0x1d09)];uint8_t z7da5ab49fa;boolean_T*z006366feb6;real_T*z208fc19091;uint32_t z8a4697fda3;uint32_t z859211b704;z6ba2595435*zae10e3f17f=NULL;za0d38ae598=((uint32_t)mxGetPr(ze13f49a01f)[(0x61c+7391-0x22fb)]);uint8_t z336107e3a8=(uint8_t)mxGetPr(zf22006b8b3)[(0x14+8248-0x204c)];uint8_t ze97179dd68=(uint8_t)mxGetPr(z4848d060ef)[(0x1715+2965-0x22aa)];zae10e3f17f=(z6ba2595435*)sg_module_get_custom_data(SG_MODULE_TYPE_IO203,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z8a4697fda3=zae10e3f17f->z2ffeecda2b[(0xc95+4149-0x1cc2)/(0x8f5+7602-0x26a3)];z859211b704=zae10e3f17f->z2ffeecda2b[(0x1ba3+304-0x1cc7)/(0x1023+2247-0x18e6)];switch(z336107e3a8){case(0xa78+4960-0x1dd7):switch(ze97179dd68){case(0x109d+3493-0x1e41):z208fc19091=(real_T*)ssGetOutputPortSignal(S,(0xfe6+3106-0x1c08));for(i=(0x43f+7721-0x2268);i<(0x1311+133-0x1376);i++){z208fc19091[i]=(real_T)((z8a4697fda3>>i)&(0x1093+289-0x11b3));z208fc19091[i+(0xf5f+4751-0x21ce)]=(real_T)((z859211b704>>i)&(0x1aa3+1398-0x2018));}break;case(0xe5a+767-0x1157):z006366feb6=(boolean_T*)ssGetOutputPortSignal(S,(0x1125+4674-0x2367));for(i=(0x152a+3580-0x2326);i<(0x892+7051-0x23fd);i++){z006366feb6[i]=(boolean_T)((z8a4697fda3>>i)&(0x141+5922-0x1862));z006366feb6[i+(0x669+8324-0x26cd)]=(boolean_T)((z859211b704>>i)&(0x49+1584-0x678));}break;}break;case(0x491+746-0x779):for(i=(0x6eb+5861-0x1dd0);i<zb220d7e807;i++){z7da5ab49fa=mxGetPr(z10e6897daf)[i];switch(ze97179dd68){case(0x1b7+2621-0xbf3):z208fc19091=(real_T*)ssGetOutputPortSignal(S,i);if((0x1fa8+485-0x218c)<=z7da5ab49fa&&z7da5ab49fa<=(0x11d7+713-0x1480)){z208fc19091[(0xd14+5807-0x23c3)]=(real_T)((z8a4697fda3>>(z7da5ab49fa-(0x407+555-0x631)))&(0x19d3+524-0x1bde));}else if((0xa8a+1822-0x1187)<=z7da5ab49fa&&z7da5ab49fa<=(0x1d51+1400-0x2289)){z208fc19091[(0x2539+367-0x26a8)]=(real_T)((z859211b704>>(z7da5ab49fa-(0xa10+5581-0x1fbc)))&(0x95d+5280-0x1dfc));}break;case(0xd7f+5328-0x224d):z006366feb6=(boolean_T*)ssGetOutputPortSignal(S,i);if((0x201+1037-0x60d)<=z7da5ab49fa&&z7da5ab49fa<=(0x8dd+3458-0x163f)){z006366feb6[(0x358+5831-0x1a1f)]=(boolean_T)((z8a4697fda3>>(z7da5ab49fa-(0x6c5+4688-0x1914)))&(0x2a6+2285-0xb92));}else if((0x2673+90-0x26ac)<=z7da5ab49fa&&z7da5ab49fa<=(0x4b8+4163-0x14bb)){z006366feb6[(0x6d6+4490-0x1860)]=(boolean_T)((z859211b704>>(z7da5ab49fa-(0x1e72+582-0x2097)))&(0xdfd+5456-0x234c));}break;}}break;}}static void sg_ModelStop(SimStruct*S){}
#endif  
#include "sg_sfcn_glue.h"   

