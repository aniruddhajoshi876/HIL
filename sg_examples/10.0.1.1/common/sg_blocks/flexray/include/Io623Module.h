// Copyright 2006-2026 Speedgoat GmbH

#ifndef z75061d5674
#define z75061d5674
#ifdef MATLAB_MEX_FILE
struct sg_PCIDevice{};
#else
#include "sg_common.h"
#endif
#include "IoModule.h"
#include "sg_error.h"
#include "sg_param.h"
#undef WIN32
#undef z6cadf57691
#include "fcBaseTypes.h"
#include "sg_io623_param.h"
#include "sg_io623_flexray_type.h"
namespace sg{class zd43ee5c691:public IoModule{public:static const int z0b03e1bc6a=(0x6bb+2256-0xf87);z13d0aa5fbb z3e96791c0d;zb40709057e zdf8f47045e;z6d51461349 za0f6ca2e0c;zb3f32e0583 z6b11e07878;zd43ee5c691(int moduleId);~zd43ee5c691();int init(const SgParam_IntVec*z8ff1e003d4);int zfdda11441c();int z13e569b276();int zed4044b959(int cc,const SgParam_CharVec*z4bbe48c546);int za3b9e36c6f(SgParam_BoolVec*zdc7a2ff6e0);int za111a7b5f6();int z866a22b76f();int z6160b72eba(Io623_FlexrayFrame**z7160ccfcc8,int z000d0f5ef7);int zf96e9b1966(int cc,int zacf2715ec1,uint16_t*zd06f8de607,int z8ac130b21e);bool zc8c1fb94ca(int cc,int zacf2715ec1);const char*z3af791a73f(const char*z0af3eceea4);void z798a78318b(const char*format,...);private:int z0730514d6a(const SgParam_IntVec*z8ff1e003d4,sg_PCIDevice*ze296e0333d);void z26ad7bbe0c(z699429c0b5 z6f13d0cde5,const char*message);void zcef515fb65(z0cbef0396c*pInfo);void z8c89985e46(z1cf8bd8373*z3e5a142b74);void z39cdda211d(z3f538c55d9*za4166e20e4);void zdbd66c2faf(const char*str,const z458e0b78f7&za59b933f2f);void za491117f8b(z22edab0133*z79c65f2150,Io623_FlexrayFrame**z7160ccfcc8,int z000d0f5ef7);bool zc8d5a4fe97[z0b03e1bc6a];int z9ef0b19be2;z463a167308 z47e2687eb2;SgError*z4b4c5cbd5b;};}
#endif  

