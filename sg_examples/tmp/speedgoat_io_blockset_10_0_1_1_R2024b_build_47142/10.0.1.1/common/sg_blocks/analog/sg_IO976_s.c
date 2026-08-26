// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x1746+514-0x1946)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO976_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
static uint8_T zd1bfbc8c7d(uint_T za42cf7dd4a,uint16_T offset);static void z92599de534(uint_T za42cf7dd4a,uint16_T offset,uint8_T value);static uint8_T z3f4f2bc778(uint_T za42cf7dd4a,uint8_T command);
#endif
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x39\x37\x36"
#define VENDORID    (0x1d43+1226-0xf06)
#define DEVICEID    (0x1cdc+418-0x1e4a)
#define SUBVENDORID 4871
#define SUBDEVICEID (0x13c3+4344-0x2487)
#define z19087bd486      ssGetSFcnParam(S, (0x196+1075-0x5c9))
#define z2aed0ca77e         ssGetSFcnParam(S, (0x12a2+3094-0x1eb7))
#define zaa1519bc30       ssGetSFcnParam(S, (0x6ff+5028-0x1aa1))
#define zcbf96201c4          ssGetSFcnParam(S, (0x1f57+1734-0x261a))
#define zda964b0978            ssGetSFcnParam(S, (0x1537+2699-0x1fbe))
#define z4c720a5fa5          ssGetSFcnParam(S, (0x2021+995-0x23ff))
#define zb4d9dc68c2             ssGetSFcnParam(S, (0x1b8+504-0x3aa))
#define z3832b85a32       ssGetSFcnParam(S, (0x370+5698-0x19ab))
#define z702a26a5e9            ssGetSFcnParam(S, (0x1c7f+2016-0x2457))
#define zdf24515981                       ((0x679+838-0x9b6))
#define z824efc2f8d       ((0xbad+5067-0x1f78))
#define z2e6483d505          ((0x383+8033-0x22e4))
#define zc5ce4cb81a          ((0x1b60+1908-0x22d4))
#define z0194338df7     ((0x1eb6+428-0x2062))
#define z2b17e2ee3b          ((0x18+7024-0x1b87))
static char_T msg[(0x11e0+4613-0x22e5)];static void mdlInitializeSizes(SimStruct*S){uint_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1be9+2135-0x2440));ssSetNumDiscStates(S,(0xdc+2184-0x964));if((int_T)mxGetPr(zb4d9dc68c2)[(0xebc+291-0xfdf)]){if(!ssSetNumOutputPorts(S,(int_T)mxGetPr(zaa1519bc30)[(0x1a85+1564-0x20a1)]+(0xb25+1112-0xf7c))){return;}}else{if(!ssSetNumOutputPorts(S,(int_T)mxGetPr(zaa1519bc30)[(0x65d+6499-0x1fc0)])){return;}}for(i=(0xa26+4519-0x1bcd);i<(uint_T)ssGetNumOutputPorts(S);i++){ssSetOutputPortWidth(S,i,(0xbba+906-0xf43));}if(!ssSetNumInputPorts(S,(0x147d+4114-0x248f))){return;}ssSetNumSampleTimes(S,(0xb34+690-0xde5));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1b1d+756-0x1e11));ssSetNumNonsampledZCs(S,(0x1298+4981-0x260d));for(i=(0x16eb+1171-0x1b7e);i<zdf24515981;i++){ssSetSFcnParamNotTunable(S,i);}ssSetSimStateCompliance(S,HAS_NO_SIM_STATE);ssSetOptions(S,SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME|SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x1d23+2188-0x25af),mxGetPr(z3832b85a32)[z824efc2f8d]);ssSetOffsetTime(S,(0x232b+363-0x2496),0.0);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uintptr_t za42cf7dd4a;int_T i,z2fd2497308;uint8_T z131c770cd5;if(mxGetN(z702a26a5e9)==(0x3e6+5208-0x183d)){bus=(0xf2+5102-0x14e0);slot=(int_T)mxGetPr(z702a26a5e9)[(0xaec+198-0xbb2)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xc2b+4403-0x1d5e)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x2e4+6945-0x1e04)];}za0d38ae598=(0x178+3798-0x104d);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0xfa6+3580-0x1da2)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0xeaa+1546-0x14b2));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);if(sg_isModelInit()){sg_inpB(za42cf7dd4a+(0x1324+790-0x1636));sg_wait_s(1.0);z2fd2497308=((int_T)mxGetPr(z2aed0ca77e)[(0x957+7476-0x268b)]<<(0xcb7+4582-0x1e9b))|((int_T)mxGetPr(z19087bd486)[(0x7ec+7535-0x255b)]-(0x647+7865-0x24ff));z131c770cd5=(0x18f0+980-0x1cc4);while(z131c770cd5!=(0x159c+2404-0x1e80)){z92599de534(za42cf7dd4a,(uint16_T)(0x3f8+6317-0x19a5),(uint8_T)z2fd2497308);z131c770cd5=z3f4f2bc778(za42cf7dd4a,(0xb75+2770-0x15c7));}SG_PRINTF(INFO,"\x25\x73\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x69\x6e\x67\x20\x66\x6f\x72\x20\x63\x68\x61\x6e\x6e\x65\x6c\x73\x20\x31\x2d\x25\x64" "\n",DEVNAME,(int_T)mxGetPr(zaa1519bc30)[(0x184d+2952-0x23d5)]);for(i=(0x33b+8912-0x260b);i<(int_T)mxGetPr(zaa1519bc30)[(0x1eff+1744-0x25cf)];i++){z2fd2497308=((int_T)mxGetPr(zcbf96201c4)[i]-(0x90+5765-0x1714))|(((int_T)mxGetPr(zda964b0978)[i]-(0xb0+2280-0x997))<<(0x1868+3177-0x24ce))|(((int_T)mxGetPr(z4c720a5fa5)[i]-(0x1312+2865-0x1e42))<<(0x15e6+4359-0x26e8));z92599de534(za42cf7dd4a,(uint16_T)((0x19d1+638-0x193f)+i),(uint8_T)z2fd2497308);}z131c770cd5=z3f4f2bc778(za42cf7dd4a,(0x11eb+580-0x13ae));z131c770cd5=z3f4f2bc778(za42cf7dd4a,(0x177f+626-0x1931));}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a;uint32_T zf91d71c6d9;uint_T base;uint_T i,z812c65ff2f;real_T*y;real32_T z5f2110a0b6;uint8_T z131c770cd5;za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);zf91d71c6d9=(uint_T)mxGetPr(zaa1519bc30)[(0x10b+9568-0x266b)];for(z812c65ff2f=(0x148f+34-0x14b1);z812c65ff2f<zf91d71c6d9;z812c65ff2f++){uint8_T*z3b640b204b=(uchar_T*)&z5f2110a0b6;z131c770cd5=z3f4f2bc778(za42cf7dd4a,(uint8_T)((0x1230+3716-0x2024)|z812c65ff2f));y=ssGetOutputPortSignal(S,z812c65ff2f);base=(0x784+7622-0x222a)+(0x1662+1231-0x1b2d)*z812c65ff2f;for(i=base;i<(base+(0xfa8+5488-0x2514));i++,z3b640b204b++){*z3b640b204b=zd1bfbc8c7d(za42cf7dd4a,(uint16_T)i);}y[(0x353+7795-0x21c6)]=(double)z5f2110a0b6;}if((int_T)mxGetPr(zb4d9dc68c2)[(0x1994+87-0x19eb)]){uint8_T*z3b640b204b=(uchar_T*)&z5f2110a0b6;y=ssGetOutputPortSignal(S,(int_T)mxGetPr(zaa1519bc30)[(0x60b+1159-0xa92)]);base=(0x14c7+4983-0x24de);for(i=base;i<(base+(0xbd6+567-0xe09));i++,z3b640b204b++){*z3b640b204b=zd1bfbc8c7d(za42cf7dd4a,(uint16_T)i);}y[(0x1209+3615-0x2028)]=(double)z5f2110a0b6;}
#endif
}static void mdlTerminate(SimStruct*S){}
#ifndef MATLAB_MEX_FILE
static uint8_T zd1bfbc8c7d(uint_T za42cf7dd4a,uint16_T offset){sg_outpB(za42cf7dd4a+(0xcdd+3082-0x18e7),offset&(0x17c3+3219-0x2357));sg_outpB(za42cf7dd4a+(0x114b+1573-0x176f),(offset>>(0x157+1793-0x850))&(0x1bb+3338-0xdc6));return(uint8_T)sg_inpB(za42cf7dd4a+(0x1ed8+1892-0x263a));}static void z92599de534(uint_T za42cf7dd4a,uint16_T offset,uint8_T value){sg_outpB(za42cf7dd4a+(0x14d6+1367-0x1a2d),offset&(0x1145+5225-0x24af));sg_outpB(za42cf7dd4a+(0xd42+1979-0x14fc),(offset>>(0x504+118-0x572))&(0xcb5+3659-0x1a01));sg_outpB(za42cf7dd4a+(0x53b+5916-0x1c55),value);}static uint8_T z3f4f2bc778(uint_T za42cf7dd4a,uint8_T command){sg_outpB(za42cf7dd4a+(0xfaa+754-0x129c),(0x925+2172-0xda3)&(0xa42+4619-0x1b4e));sg_outpB(za42cf7dd4a+(0xf64+3124-0x1b97),((0x1401+846-0x1351)>>(0x13ca+3718-0x2248))&(0xd7a+2272-0x155b));while(!(sg_inpB(za42cf7dd4a+(0xb0c+4680-0x1d51))&(0x54f+779-0x81a)));sg_outpB(za42cf7dd4a+(0x1a5d+1786-0x2155),command);while(sg_inpB(za42cf7dd4a+(0x9ca+3127-0x15fe))&(0x1cf3+69-0x1cb8));sg_outpB(za42cf7dd4a+(0x1063+5128-0x246b),(0x6e8+4015-0x1298)&(0x1942+3586-0x2645));sg_outpB(za42cf7dd4a+(0x48c+3842-0x138d),((0xa34+198-0x6fb)>>(0x184b+1509-0x1e28))&(0x1c6+8920-0x239f));return(uint8_T)sg_inpB(za42cf7dd4a+(0x3b2+4496-0x1540));}
#endif
#include "sg_sfcn_glue.h"   

