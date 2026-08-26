// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x14c8+4379-0x25e1)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO112_adread_s
#include <stddef.h>
#include <stdlib.h>
#include "sg_callback_legacy.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#include "sg_printf.h"
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x32"
#define VENDORID 4277
#define DEVICEID 36950
#define SUBVENDORID 4277
#define SUBDEVICEID 13361
#define ze13f49a01f           ssGetSFcnParam(S, (0x20c+1518-0x7fa))
#define za8bff65d14              ssGetSFcnParam(S, (0x52c+4765-0x17c8))
#define z04bce731b0             ssGetSFcnParam(S, (0x823+3038-0x13ff))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x170b+2100-0x1f3c))
#define z8fd86139be               ssGetSFcnParam(S, (0x8df+2442-0x1265))
#define z19087bd486          ssGetSFcnParam(S, (0x44b+1418-0x9d0))
#define z3832b85a32           ssGetSFcnParam(S, (0xbb5+2332-0x14cb))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1e0+6493-0x1b36))
#define zdf24515981                           ((0x7fa+6269-0x206f))
#define zc2f3e0cbc0        ((0xc3a+164-0xcde))
#define z2e6483d505              ((0x563+4674-0x17a4))
#define z8caad2a8e6              ((0x13b5+4282-0x246f))
#define z5bfe7a2613            ((0xfbd+2789-0x1aa1))
#define zc5ce4cb81a              ((0x48b+1186-0x92b))
#define z0194338df7         ((0x1787+2675-0x21fa))
#define z2b17e2ee3b              ((0x143a+2813-0x1f36))
static char_T msg[(0x21f9+372-0x226d)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1e9b+129-0x1f1c));ssSetNumDiscStates(S,(0x1fc1+1847-0x26f8));if(!(boolean_T)mxGetPr(z04bce731b0)[(0x9f+6664-0x1aa7)]){ssSetNumOutputPorts(S,(0x13d4+3823-0x22c2));ssSetOutputPortWidth(S,(0x7c1+3272-0x1489),(uint32_T)mxGetPr(za9d8fb6bcf)[(0xc49+5118-0x2047)]);}else{ssSetNumOutputPorts(S,(0x1419+2443-0x1da2));ssSetOutputPortDataType(S,(0xd61+3713-0x1be2),SS_BOOLEAN);ssSetOutputPortWidth(S,(0x188a+1843-0x1fbd),(0x1877+228-0x195a));ssSetOutputPortWidth(S,(0x372+8073-0x22fa),(uint32_T)mxGetPr(za9d8fb6bcf)[(0xd3a+3526-0x1b00)]);}if(!(boolean_T)mxGetPr(za8bff65d14)[(0x1743+1808-0x1e53)]){ssSetNumInputPorts(S,(0x11f5+535-0x140c));}else{ssSetNumInputPorts(S,(0x126+4874-0x142f));ssSetInputPortDirectFeedThrough(S,(0x233+1363-0x786),(0x8c9+5538-0x1e6a));ssSetInputPortWidth(S,(0x180+816-0x4b0),(0x1e31+1994-0x25fa));ssSetInputPortDataType(S,(0x4b0+1319-0x9d7),SS_BOOLEAN);ssSetInputPortRequiredContiguous(S,(0x13f8+125-0x1475),(0xa52+1241-0xf2a));}ssSetNumSampleTimes(S,(0x1120+5276-0x25bb));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xe7f+4940-0x21cb));ssSetNumNonsampledZCs(S,(0x223a+289-0x235b));for(i=(0x1b0c+380-0x1c88);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x801+3226-0x149b));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xb42+2202-0x13dc)]==-1.0){ssSetSampleTime(S,(0x669+4611-0x186c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x8b6+2648-0x130e),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x16e1+2420-0x2055),mxGetPr(z3832b85a32)[(0xdb5+4531-0x1f68)]);ssSetOffsetTime(S,(0x52d+3820-0x1419),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;uint32_T zf91d71c6d9=(uint32_T)mxGetPr(za9d8fb6bcf)[(0xad6+4542-0x1c94)];if(mxGetN(z702a26a5e9)==(0x1260+855-0x15b6)){bus=(0x99a+6421-0x22af);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1540+3994-0x24da)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1256+4662-0x248c)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xaf2+6968-0x2629)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x22c+5572-0x17f0)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x306+5247-0x1785)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0x309+3994-0x12a1));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);ssSetIWorkValue(S,zc2f3e0cbc0,(uint32_T)zf91d71c6d9);if((uint32_T)mxGetPr(z19087bd486)[(0x577+4305-0x1648)]==(0xfd7+1628-0x1632)){switch((uint32_T)mxGetPr(z8fd86139be)[(0x213b+905-0x24c4)]){case(0xcd2+369-0xe42):ssSetRWorkValue(S,z8caad2a8e6,13107.15);ssSetRWorkValue(S,z5bfe7a2613,10.0);break;case(0x1cd8+896-0x2056):ssSetRWorkValue(S,z8caad2a8e6,26214.3);ssSetRWorkValue(S,z5bfe7a2613,5.0);break;}}else{switch((uint32_T)mxGetPr(z8fd86139be)[(0xa80+5306-0x1f3a)]){case(0x1b4+8448-0x22b3):ssSetRWorkValue(S,z8caad2a8e6,3276.8);ssSetRWorkValue(S,z5bfe7a2613,10.0);break;case(0x323+3701-0x1196):ssSetRWorkValue(S,z8caad2a8e6,6553.6);ssSetRWorkValue(S,z5bfe7a2613,5.0);break;}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint16_T zf91d71c6d9=(uint16_T)ssGetIWorkValue(S,zc2f3e0cbc0);volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint32_T z32b35fb51b=(uint32_T)mxGetPr(z19087bd486)[(0x7a8+1331-0xcdb)];real_T*y,z0754dd67cc,offset;uint32_T i;uint32_T count;uint32_T z4314ccb6ec=(0x6d3+2880-0x1213);boolean_T*z0daf90e5e1;boolean_T enabled=true;if((int)mxGetPr(za8bff65d14)[(0xe4c+1820-0x1568)]){z0daf90e5e1=(boolean_T*)ssGetInputPortSignal(S,(0x105+9550-0x2653));enabled=z0daf90e5e1[(0x790+300-0x8bc)];}if((int)mxGetPr(z04bce731b0)[(0x6d1+336-0x821)]){z0daf90e5e1=(boolean_T*)ssGetOutputPortSignal(S,(0xa0c+6552-0x23a4));z0daf90e5e1[(0xa76+7120-0x2646)]=enabled;z4314ccb6ec=(0xef+425-0x297);}y=ssGetOutputPortSignal(S,z4314ccb6ec);z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);offset=ssGetRWorkValue(S,z5bfe7a2613);if(enabled){i=(0x32d+6784-0x1dad);while(!(za42cf7dd4a[(0x1ddf+1610-0x2426)]&524288)){i++;}if(z32b35fb51b==(0x1b3+76-0x1fe)){for(i=(0x56f+3729-0x1400);i<zf91d71c6d9;i++){count=za42cf7dd4a[(0x19e0+972-0x1daa)];y[i]=(real_T)(count&262143)/z0754dd67cc-offset;}}else{count=za42cf7dd4a[(0x1265+4688-0x24b3)];if(count!=65537){SG_PRINTF(DEBUG,"\x73\x6f\x6d\x65\x74\x68\x69\x6e\x67\x20\x73\x74\x72\x61\x6e\x67\x65" "\n");}for(i=(0x478+4235-0x1503);i<(uint16_T)(zf91d71c6d9/(0xdeb+3348-0x1afd));i++){count=za42cf7dd4a[(0x2001+956-0x23bb)];y[(0x579+102-0x5df)+i*(0x4a9+7019-0x2012)]=(real_T)(count&65535)/z0754dd67cc-offset;y[(0x37a+3136-0xfb9)+i*(0x16b9+3373-0x23e4)]=(real_T)((count&4294901760)>>(0x7e8+4108-0x17e4))/z0754dd67cc-offset;}}}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   

