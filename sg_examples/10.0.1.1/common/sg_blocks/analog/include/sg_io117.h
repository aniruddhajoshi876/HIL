// Copyright 2006-2026 Speedgoat GmbH

#ifndef zeff4b68404
#define zeff4b68404
#include <stdbool.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#include "sg_io117_regs.h"
#include "sg_module_types.h"
#define VENDORID            (4277)    
#define DEVICEID            (36944)    
#define SUBVENDORID         ((0x1dc1+37-0x94e))    
#define SUBDEVICEID         ((0x14d1+1035-0x16e7))    
#define z12ba1d7c25          z4fce072d86
#define z3c60d664da             ((0xb8f+4159-0x1bcd) << (0x6e7+2528-0x10b7))
#define z5bb9de888d        (2.0)
#define z4c57271386        (4.0)
#define zeabc85c320        (10.0)
#define z26599dec66       (20.0)
#define z907277d41e                  ((0x5ec+8894-0x24c2))
#define z6c753d4c85      ((0x7cb+1310-0xce5))
#define zbaf1ba92a3       ((0xa6c+3525-0x182f))
typedef volatile struct{struct{uint16_T offset;uint16_T z0754dd67cc;}range[(0x7fd+3936-0x1759)];}z303722bdba;enum z0fd8370698{z13b8d8b319=(0x303+924-0x69f),z136e68ca28=(0xe28+882-0x1199),zd018d8a155=(0x707+7421-0x2402),z5f1c3799fe=(0xabd+3534-0x1888)};
#define zbb6f9b10be                 (zd1e3aa71a8)
#define z9dd1a3523f                 (z9ffc8c2207)
#define z16682623a4                 (zcb65900374)
#define z26e2f0437a                 (zeef8da9b67)
#define INTSTAT                 (z4bf9bffe41)
#define z0f84dc1304                 (z5730266831)
#define z844522657d                 (z1c8c2e3477)
#define z7bb8b3ca7f                (z4db306e6c7)
#define z6afa08d5b0              (zda69083382)
#define zd0125fe357              (ze25cc5b687)
#define z45a57f835e            (65535)
#define z1a15806673    (65535)
#define zd195659c5a         ((0xa47+5029-0x1dec) << z63986d6821)
#define zb06efd54c6          ((0x1df+4930-0x1520) << z63986d6821)
#define z50cb4fc509        ((0x350+3520-0x1110) << z7ee49eb82c)
#define zf0fa1ef62e         ((0xab5+1792-0x11b4) << z7ee49eb82c)
#define z8195ce9c43       ((0x16d+4909-0x149a) << zfb4827d105)
#define zdc7d6985da        ((0xcc5+3870-0x1be2) << zfb4827d105)
#define z3444e45f50        ((0x616+318-0x754) << zbd8ec55d05)
#define z0f62c35fe0         ((0x5af+7453-0x22cb) << zbd8ec55d05)
#define zb87101ff03         ((0xed3+64-0xf11) << zbd8ec55d05)
#define z1405af43a1         ((0x1921+855-0x1c75) << zbd8ec55d05)
#define zd4a970e546      ((0x796+3355-0x14b1) << z9145784c9d)
#define z30d53c4326    ((0xd7b+4351-0x1e79) << z9145784c9d)
enum zebeb91fde3{z87164073f6=(0xc85+4491-0x1e0f),z8d4dae8c2f=(0xeca+3712-0x1d48)};enum z793efb7437{zda0ee7773f=(0x2098+1348-0x25db),z4c74353c5c=(0x86+2791-0xb6b),z145192872a=(0x118f+4030-0x214a),z95fa3f12fe=(0x954+2217-0x11f9),};typedef struct{char_T*name;int16_T z3e62eb5d94;int16_T z98900a22db;int16_T z1eb2960903;int16_T z347d4b4111;int_T z250a7ada11;}zecb3eab63e;typedef struct{real_T z0754dd67cc;real_T offset;}z399695fa0f;typedef struct{zecb3eab63e z16d24d51ac;int_T zc3ac25f204;int_T z0c3eef007f;uint16_T zc9139a10cc;z303722bdba*z7b281664ab;uint16_T*z4648a2f958;real_T*z32b35fb51b;z399695fa0f*ze47081d006;}zecc5e49691;extern int_T z99cea3a645(zecb3eab63e*z16d24d51ac);extern int_T zce62d99bb5(const mxArray*zf6a6b39f7e,zecc5e49691*zae10e3f17f);
#ifndef MATLAB_MEX_FILE
extern int_T z36e54bd995(const mxArray*z3375477fdb,const zecb3eab63e*z16d24d51ac,int_T zc3ac25f204,sg_PCIDevice*zeccbadd9b3);
#endif
extern uint16_T zc41552c420(zecc5e49691*zae10e3f17f,uint16_T z3568804f6b);extern void z9d01a45f9b(zecc5e49691*zae10e3f17f,uint16_T z3568804f6b,uint16_T value);extern void z8a88f80f5a(zecc5e49691*zae10e3f17f,uint16_T z3568804f6b,uint16_T mask,uint16_T za074cf20c9);extern int_T z8da825d0cb(int_T idx,const mxArray*zace6cd920f,const mxArray*zb2b0a17c8b,const mxArray*z880ddf7a59,uint16_T*zde83594af4);extern int_T ze11fe6fe03(int_T ze00583cac9,real_T*z434f62ee93);extern void za497aa1018(zecc5e49691*zae10e3f17f,z399695fa0f*ze47081d006);extern int_T ze144210bfc(zecc5e49691*zae10e3f17f);extern int_T za5d3a63025(zecc5e49691*zae10e3f17f);extern int_T z2f30a295d4(zecc5e49691*zae10e3f17f,uint16_T z3568804f6b,uint16_T mask,int_T za4536720f6);
#endif  

