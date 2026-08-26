// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x8fb+3137-0x153a)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO106_adread_s
#include <stddef.h>
#include <stdlib.h>
#include "sg_IO106.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_printf.h"
#include "sg_common.h"
#include "sg_module_types.h"
#include "sg_module_registry.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0xf87+552-0x11af))
#define za8bff65d14              ssGetSFcnParam(S, (0x6b2+5328-0x1b81))
#define z04bce731b0             ssGetSFcnParam(S, (0x1954+1681-0x1fe3))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x288+4480-0x1405))
#define z8fd86139be               ssGetSFcnParam(S, (0x48b+2214-0xd2d))
#define z8e37b80355            ssGetSFcnParam(S, (0x72+5222-0x14d3))
#define z3832b85a32           ssGetSFcnParam(S, (0x5d4+1868-0xd1a))
#define z702a26a5e9                ssGetSFcnParam(S, (0xb8+9406-0x256f))
#define zdf24515981          ((0x99c+4204-0x1a00))
#define z2e6483d505              ((0x37c+78-0x3ca))
#define zc5ce4cb81a              ((0x6b1+3245-0x135e))
#define z2b17e2ee3b              ((0x6eb+4836-0x19cf))
static char_T msg[(0x1009+5426-0x243b)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xd71+5888-0x2471));ssSetNumDiscStates(S,(0x13c8+1621-0x1a1d));if(!(boolean_T)mxGetPr(z04bce731b0)[(0x2462+311-0x2599)]){if(!ssSetNumOutputPorts(S,(0x163+8556-0x22ce)))return;switch((uint32_T)mxGetPr(z8e37b80355)[(0x1484+1115-0x18df)]){case(0x158d+283-0x16a7):ssSetOutputPortWidth(S,(0xef8+3514-0x1cb2),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x1098+3393-0x1dd9)]);break;case(0x1412+930-0x17b2):ssSetOutputPortWidth(S,(0x9ad+1448-0xf55),(uint32_T)mxGetPr(za9d8fb6bcf)[(0xa06+1885-0x1163)]-(0x21d7+130-0x2258));break;case(0x475+3012-0x1036):ssSetOutputPortWidth(S,(0x3bd+4887-0x16d4),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x1e2+4713-0x144b)]);break;}}else{if(!ssSetNumOutputPorts(S,(0x942+715-0xc0b)))return;ssSetOutputPortDataType(S,(0xb6+31-0xd5),SS_BOOLEAN);ssSetOutputPortWidth(S,(0xcdb+5670-0x2301),(0xdd4+3194-0x1a4d));switch((uint32_T)mxGetPr(z8e37b80355)[(0xe39+4464-0x1fa9)]){case(0x360+4251-0x13fa):ssSetOutputPortWidth(S,(0x1601+3983-0x258f),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x1cc5+886-0x203b)]);break;case(0x8fd+4271-0x19aa):ssSetOutputPortWidth(S,(0xdcb+4590-0x1fb8),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x42b+8831-0x26aa)]-(0xafb+7132-0x26d6));break;case(0x1792+3042-0x2371):ssSetOutputPortWidth(S,(0x1995+365-0x1b01),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x1f72+1358-0x24c0)]);break;}}if(!(boolean_T)mxGetPr(za8bff65d14)[(0x1fd6+798-0x22f4)]){if(!ssSetNumInputPorts(S,(0xc04+114-0xc76)))return;}else{if(!ssSetNumInputPorts(S,(0xe72+2918-0x19d7)))return;ssSetInputPortDirectFeedThrough(S,(0x16bd+1047-0x1ad4),(0x172b+3390-0x2468));ssSetInputPortWidth(S,(0x10dd+439-0x1294),(0x22c+5418-0x1755));ssSetInputPortDataType(S,(0xc82+1224-0x114a),SS_BOOLEAN);ssSetInputPortRequiredContiguous(S,(0xcd9+1050-0x10f3),(0x8a7+169-0x94f));}ssSetNumSampleTimes(S,(0xc1b+314-0xd54));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xf91+4891-0x22ac));ssSetNumNonsampledZCs(S,(0xbd8+1407-0x1157));for(i=(0x9c4+1683-0x1057);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x148a+1315-0x19ad));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x15c8+4222-0x2646)]==-1.0){ssSetSampleTime(S,(0xe37+4214-0x1ead),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x980+3601-0x1791),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x111+7383-0x1de8),mxGetPr(z3832b85a32)[(0xc09+2173-0x1486)]);ssSetOffsetTime(S,(0x536+3739-0x13d1),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T zf91d71c6d9=(uint32_T)mxGetPr(za9d8fb6bcf)[(0x36d+6567-0x1d14)];uint32_T z8b9d33e44f=(uint32_T)mxGetPr(z8e37b80355)[(0x1584+2935-0x20fb)];uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x314+1858-0xa56)]);real_T*y;uint32_T i;uint32_T count;uint32_T z4314ccb6ec=(0x14f2+3637-0x2327);boolean_T*z0daf90e5e1;boolean_T enabled=true;z6077dd317b*zae10e3f17f=(z6077dd317b*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x41\x44\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}if((int)mxGetPr(za8bff65d14)[(0xd83+6267-0x25fe)]){z0daf90e5e1=(boolean_T*)ssGetInputPortSignal(S,(0x1277+4646-0x249d));enabled=z0daf90e5e1[(0xf80+3328-0x1c80)];}if((int)mxGetPr(z04bce731b0)[(0xc20+2359-0x1557)]){z0daf90e5e1=(boolean_T*)ssGetOutputPortSignal(S,(0xf95+905-0x131e));z0daf90e5e1[(0x778+7827-0x260b)]=enabled;z4314ccb6ec=(0x14cc+2181-0x1d50);}y=ssGetOutputPortSignal(S,z4314ccb6ec);if(enabled){i=(0x411+1788-0xb0d);while(!(zae10e3f17f->z3fad3d9764->z8727c368fa&((0x1922+3438-0x268f)<<z452dd4baee))){i++;}count=zae10e3f17f->z3fad3d9764->z690d720321;for(i=(0xbf3+4088-0x1beb);i<(uint16_T)(zf91d71c6d9/(0x276+1508-0x858));i++){count=zae10e3f17f->z3fad3d9764->z690d720321;if(z8b9d33e44f==(0x10e9+2665-0x1b50)){if(i==(0x350+6027-0x1adb)){y[(0x9a7+2233-0x125f)+i*(0x19+5529-0x15b0)-(0x1eb9+1489-0x2489)]=2.0*((real_T)((count&4294901760)>>(0x258+1743-0x917))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);}else{y[(0x858+1613-0xea5)+i*(0x1821+681-0x1ac8)-(0x123f+1799-0x1945)]=2.0*((real_T)(count&65535)/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);y[(0x502+3357-0x121e)+i*(0xff2+4386-0x2112)-(0x46d+3362-0x118e)]=2.0*((real_T)((count&4294901760)>>(0x531+5471-0x1a80))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);}}else{if(z8b9d33e44f==(0x995+6387-0x2285)){y[(0x4fc+980-0x8d0)+i*(0x328+8980-0x263a)]=2.0*((real_T)(count&65535)/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);y[(0x1543+287-0x1661)+i*(0x3f4+5810-0x1aa4)]=2.0*((real_T)((count&4294901760)>>(0xc01+5500-0x216d))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a);}else{y[(0x67a+7009-0x21db)+i*(0x547+1292-0xa51)]=(real_T)(count&65535)/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a;y[(0x2b6+1446-0x85b)+i*(0xced+1226-0x11b5)]=(real_T)((count&4294901760)>>(0x12dc+1470-0x188a))/zae10e3f17f->z409f51ac11-zae10e3f17f->za59ce6481a;}}}zae10e3f17f->z3fad3d9764->z8727c368fa|=((0x1213+2254-0x1ae0)<<z62c191e480);;}}static void sg_ModelStop(SimStruct*S){}
#endif
#include "sg_sfcn_glue.h"   

