// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1bc5+2140-0x241f)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO112_ad_s
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
#endif
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x32"
#define VENDORID (0x12dd+1733-0x8ed)
#define DEVICEID 36950
#define SUBVENDORID (0x1a49+3358-0x16b2)
#define SUBDEVICEID 13361
#define ze13f49a01f           ssGetSFcnParam(S, (0x22d+303-0x35c))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x15d4+1868-0x1d1f))
#define z8fd86139be               ssGetSFcnParam(S, (0x10a3+1830-0x17c7))
#define z19087bd486          ssGetSFcnParam(S, (0x21e1+107-0x2249))
#define z3832b85a32           ssGetSFcnParam(S, (0x25b+3725-0x10e4))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1254+5159-0x2676))
#define zdf24515981                           ((0xde5+4866-0x20e1))
#define zc2f3e0cbc0        ((0x1067+130-0x10e9))
#define z2e6483d505              ((0xa17+5424-0x1f46))
#define z8caad2a8e6              ((0xb28+2670-0x1596))
#define z5bfe7a2613            ((0x453+7477-0x2187))
#define zc5ce4cb81a              ((0x82c+467-0x9fd))
#define z0194338df7         ((0x50c+4988-0x1888))
#define z2b17e2ee3b              ((0xc9b+4425-0x1de3))
static char_T msg[(0x1ad3+3247-0x2682)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x7+7276-0x1c73));ssSetNumDiscStates(S,(0x230b+908-0x2697));ssSetNumInputPorts(S,(0x1aa4+441-0x1c5d));ssSetNumOutputPorts(S,(0x1b95+1077-0x1fc9));ssSetOutputPortWidth(S,(0x1a34+732-0x1d10),(uint32_T)mxGetPr(za9d8fb6bcf)[(0x3a3+7935-0x22a2)]);ssSetNumSampleTimes(S,(0x848+3851-0x1752));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x262+4676-0x14a6));ssSetNumNonsampledZCs(S,(0xf86+4255-0x2025));for(i=(0xdd6+109-0xe43);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x140+475-0x31b));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x10c8+3499-0x1e73)]==-1.0){ssSetSampleTime(S,(0x1cc4+23-0x1cdb),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1e22+204-0x1eee),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xa17+1186-0xeb9),mxGetPr(z3832b85a32)[(0xc2+632-0x33a)]);ssSetOffsetTime(S,(0x1d6f+2315-0x267a),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;uint32_T zf91d71c6d9=(uint32_T)mxGetPr(za9d8fb6bcf)[(0x12dd+4252-0x2379)];if(mxGetN(z702a26a5e9)==(0x607+126-0x684)){bus=(0xa4+8941-0x2391);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1aa0+1179-0x1f3b)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xef0+5017-0x2289)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x11ba+4409-0x22f2)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x1128+4159-0x2167)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x289+2968-0xe21)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0xdac+3148-0x19f6));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);ssSetIWorkValue(S,zc2f3e0cbc0,(uint32_T)zf91d71c6d9);if((uint32_T)mxGetPr(z19087bd486)[(0x388+5500-0x1904)]==(0x464+8210-0x2475)){switch((uint32_T)mxGetPr(z8fd86139be)[(0x6ec+7319-0x2383)]){case(0xa1f+4612-0x1c22):ssSetRWorkValue(S,z8caad2a8e6,13107.15);ssSetRWorkValue(S,z5bfe7a2613,10.0);break;case(0x1eec+1050-0x2304):ssSetRWorkValue(S,z8caad2a8e6,26214.3);ssSetRWorkValue(S,z5bfe7a2613,5.0);break;}}else{switch((uint32_T)mxGetPr(z8fd86139be)[(0x3a1+1427-0x934)]){case(0x66f+2979-0x1211):ssSetRWorkValue(S,z8caad2a8e6,3276.8);ssSetRWorkValue(S,z5bfe7a2613,10.0);break;case(0xf06+1003-0x12ef):ssSetRWorkValue(S,z8caad2a8e6,6553.6);ssSetRWorkValue(S,z5bfe7a2613,5.0);break;}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint16_T zf91d71c6d9=(uint16_T)ssGetIWorkValue(S,zc2f3e0cbc0);volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint32_T z32b35fb51b=(uint32_T)mxGetPr(z19087bd486)[(0x58b+6073-0x1d44)];real_T*y,z0754dd67cc,offset;uint32_T i;uint32_T count;za42cf7dd4a[(0x106+4993-0x1487)]=za42cf7dd4a[(0xcb+7915-0x1fb6)]|(0x2061+2783-0x1b40);y=ssGetOutputPortSignal(S,(0x72a+2053-0xf2f));z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);offset=ssGetRWorkValue(S,z5bfe7a2613);i=(0x308+1222-0x7ce);while(!(za42cf7dd4a[(0x722+5068-0x1aeb)]&524288)){i++;}if(z32b35fb51b==(0x252+2340-0xb75)){for(i=(0x3e7+1537-0x9e8);i<zf91d71c6d9;i++){count=za42cf7dd4a[(0x1293+2500-0x1c55)];y[i]=(real_T)(count&262143)/z0754dd67cc-offset;}}else{count=za42cf7dd4a[(0x7ba+467-0x98b)];if(count!=65537){SG_PRINTF(DEBUG,"\x73\x6f\x6d\x65\x74\x68\x69\x6e\x67\x20\x73\x74\x72\x61\x6e\x67\x65" "\n");}for(i=(0x1918+940-0x1cc4);i<(uint16_T)(zf91d71c6d9/(0xa81+7044-0x2603));i++){count=za42cf7dd4a[(0x1d01+97-0x1d60)];y[(0x18c4+183-0x197b)+i*(0x2dc+5168-0x170a)]=(real_T)(count&65535)/z0754dd67cc-offset;y[(0x1c74+618-0x1edd)+i*(0x63d+5209-0x1a94)]=(real_T)((count&4294901760)>>(0x22b+1437-0x7b8))/z0754dd67cc-offset;}}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   

