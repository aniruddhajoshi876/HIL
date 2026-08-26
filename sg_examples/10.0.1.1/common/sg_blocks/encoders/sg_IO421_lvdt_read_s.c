// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL  (0xaa3+6749-0x24fe)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO421_lvdt_read_s
#define zd6a3cd0da0 "\x49\x4f\x34\x32\x31\x2d\x31"
#define zbb2ebcc7de "\x4c\x56\x44\x54\x2f\x52\x56\x44\x54\x20\x6d\x65\x61\x73\x75\x72\x65\x6d\x65\x6e\x74"
#define zdd9aa31c07 30354
#define z95835284b8 (0x226d+1053-0x10de)
#define z5674e18e88 (0x1354+696-0x1608)
#define z20f97d736d 19522 
#define z24077972a0   19544 
#define z403d45b116 za42cf7dd4a[(0x138+121-0x1b1)]    
#define z6265bf51f4 "\x6c\x76\x5f\x72\x5f\x72\x65\x67\x2e\x63\x73\x76"
#define z88ca2e8e70   "\x6c\x76\x5f\x72\x5f\x72\x75\x6e\x2e\x63\x73\x76"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include    "sg_callback.h"
#include    "sg_printf.h"
#define za9d8fb6bcf         ssGetSFcnParam(S, (0x277+7462-0x1f9d))
#define z86992bd6b1         ssGetSFcnParam(S, (0x1030+1179-0x14ca)) 
#define z8759454a33          ssGetSFcnParam(S, (0x12a5+414-0x1441))
#define zf1b17602bb         ssGetSFcnParam(S, (0xc98+2578-0x16a7))
#define z6851db3a5b        ssGetSFcnParam(S, (0x14b0+2348-0x1dd8))
#define z3832b85a32       ssGetSFcnParam(S, (0x11bf+2488-0x1b72))
#define z702a26a5e9            ssGetSFcnParam(S, (0xe32+2629-0x1871))  
#define ze13f49a01f       ssGetSFcnParam(S, (0x1460+303-0x1588)) 
#define zdf24515981                       ((0x1530+15-0x1537))
#define z2e6483d505              ((0x859+3100-0x1475))
#define zc5ce4cb81a              ((0xc22+2289-0x1513))
#define z2b17e2ee3b              ((0x3cb+6331-0x1c86))
#define zf23a276386            (0x11d7+2163-0x1a4a)  
#define zab0c6777d2            (0x9c6+614-0xc28)  
#define zb8d9e18b93              (0x502+5278-0x1960)  
#define z5803b14552          (0x60b+2177-0xe3c)  
#define zb0321f33ec     (0xa2f+4839-0x1cba)  
#define zf84b99a6c8        (0x1878+2080-0x2038)  
#define z39759ebfce         (0x7ea+2252-0x1052)  
#define z9a7bdb2094            (0x1f60+1208-0x23b0)  
#define z4deb0e2a33          (0x1fb1+1945-0x26da)  
#define zd4732228ac       (0xc98+23-0xc37)  
#define z7bb0b12fdf   (0x5f5+1112-0x9ad)  
#define z4a4fb1dbf0   (0xc2b+2036-0x137b)  
#define zb182222425       (0x48c+6398-0x1cca)  
#define z26f11002ec   (0x1272+3428-0x1f06)  
#define ze01cb9b83c           (0x11d8+4654-0x2306)  
#define z615b449cad           (0xaea+6634-0x23c4)  
#define zb20fe15b56             (0x1c0f+1572-0x20f3)  
#define z5603507732             (0x2cd+9652-0x26b1)  
#define zbaedcecb33             (0x1afb+2219-0x21d2)  
#define zdd9d7c18a2      (0x1121+3813-0x1e22)  
#define ze36fd17bd0      (0x178c+3104-0x21c4)  
#define zd8e996cc5e      (0x9c8+7012-0x2340)  
#define z38b9d91ae0        (0x23d+9504-0x255d)  
#define z79cfc785ef        (0xee6+6252-0x254e)  
#define z395b1a96f8        (0xe4a+6282-0x24cc)  
#define z011f6e6b8b        (0x6b0+5468-0x1a00)  
#define zcddf3f512f      (0xc95+5537-0x1c36)  
#define z71763e75f8      (0x955+3688-0x11ad)  
#define zf5aa914738   (0x12d3+5678-0x22e1)  
#define zf064710957        (0x10ef+5541-0x2054)  
#define zed77e50b70        (0x1cb2+1897-0x1dd7)  
#define z8849a8e340       (0x19e6+483-0x1581)  
#define z2dd3682034        (0xcf8+5552-0x1c5c)  
#define z125464d13e        (0x167a+1669-0x16af)  
#define z807210a558             (0x76b+5089-0x14f8)  
#define z512181a8d5          (0xaa1+2925-0xfb6)  
#define z6bb464116c       (0x98d+9073-0x26a2)  
#define z3605c57398       (0xdf9+5586-0x1d0b)  
#define z5b3ae3dec0             (0x18e6+2676-0x1c5a)  
#define z14104ee594      (0x1346+672-0xe7e)  
#define z8389a0694a      (0x1f9c+288-0x1950)  
#define zfd273e051e         (0x1244+4685-0x1d21)  
#define z4267492038        (0x1df0+3420-0x23d8)  
#define z88e2416cde              (0x2583+1387-0x2376)  
#define zf4a8506aca          (0xfaf+4693-0x1a44)  
#define za340fd67b9       (0xabb+4141-0x1324)  
#define z4927a023af          (0x10b5+1743-0xfbc)  
#define z3a3c1415c9         (0x1087+1670-0xf41)  
#define z2f17ac91c1    (0xe49+2918-0x11df)  
#define zb4af4b5018(slot,ch)             za42cf7dd4a[((((slot-(0x1d2+2085-0x9f6)) * (0x26e6+223-0x1fc5) + zf23a276386            + (ch-(0x1e39+550-0x205e)) * (0x1da+3799-0x10a9))/(0x1152+2399-0x1aaf)))]
#define ze5668a942c(slot,ch)             za42cf7dd4a[((((slot-(0x10d+7415-0x1e03)) * (0xcdd+5631-0x1adc) + zab0c6777d2            + (ch-(0x186f+1679-0x1efd)) * (0x474+5049-0x1825))/(0x11e3+621-0x144e)))]
#define zd139276cb7(slot,ch)               za42cf7dd4a[((((slot-(0x4c7+333-0x613)) * (0x20f0+529-0x1b01) + zb8d9e18b93              + (ch-(0x1ed3+2017-0x26b3)) * (0x1d23+876-0x208b))/(0x1135+5003-0x24be)))]
#define z1c46a1fd49(slot)              za42cf7dd4a[((((slot-(0x2364+852-0x26b7)) * (0x17c9+5030-0x236f) + z5803b14552                      )/(0x1042+4430-0x218e)))]
#define zd342ccc2ba(slot)         za42cf7dd4a[((((slot-(0x966+5686-0x1f9b)) * (0x157c+6334-0x263a) + zb0321f33ec                 )/(0x21b1+276-0x22c3)))]
#define zad49f46bf6(slot)            za42cf7dd4a[((((slot-(0xbe5+6280-0x246c)) * 2048 + zf84b99a6c8                    )/(0x7ca+1465-0xd81)))]
#define zd608c0fe24(slot)             za42cf7dd4a[((((slot-(0xac1+2236-0x137c)) * (0x1fbf+3688-0x2627) + z39759ebfce                     )/(0x11e7+1416-0x176d)))]
#define z03315844fb(slot)                za42cf7dd4a[((((slot-(0x1127+3573-0x1f1b)) * (0x13ff+4969-0x1f68) + z9a7bdb2094                        )/(0x15d2+3171-0x2233)))]
#define z9e37f3f192(slot)              za42cf7dd4a[((((slot-(0x1448+2428-0x1dc3)) * (0x243f+2626-0x2681) + z4deb0e2a33                      )/(0x588+3085-0x1193)))]
#define z56becc4131(slot)           za42cf7dd4a[((((slot-(0x1391+2637-0x1ddd)) * (0x130c+3776-0x19cc) + zd4732228ac                   )/(0x1b4d+310-0x1c81)))]
#define z853692a017(slot,ch)    za42cf7dd4a[((((slot-(0x25a8+290-0x26c9)) * (0xce6+5616-0x1ad6) + z7bb0b12fdf   + (ch-(0x1b13+84-0x1b66)) * (0x913+672-0xbab))/(0xa8f+3322-0x1787)))] 
#define zbbd5933507(slot,ch)    za42cf7dd4a[((((slot-(0x6b8+2237-0xf74)) * (0x89b+2905-0xbf4) + z4a4fb1dbf0   + (ch-(0xa75+6097-0x2245)) * (0x1d87+1872-0x24cf))/(0x293+3524-0x1055)))] 
#define zf23e326281(slot,ch)        za42cf7dd4a[((((slot-(0x3d6+4171-0x1420)) * (0x26e2+1399-0x2459) + zb182222425       + (ch-(0x15a+3227-0xdf4)) * (0x1322+2325-0x1c33))/(0x849+1275-0xd42)))] 
#define z03fc80adb6(slot,ch)    za42cf7dd4a[((((slot-(0xf27+2603-0x1951)) * (0x15ea+4197-0x1e4f) + z26f11002ec   + (ch-(0x168d+297-0x17b5)) * (0x18d6+31-0x18f1))/(0xe41+4337-0x1f30)))] 
#define zcd6aa986d5(slot,ch)            za42cf7dd4a[((((slot-(0x959+6923-0x2463)) * (0x1795+5210-0x23ef) + ze01cb9b83c           + (ch-(0x1c5+245-0x2b9)) * (0x3ec+3200-0x1068))/(0x2e7+8173-0x22d2)))]
#define zeecf280bb9(slot,ch)            za42cf7dd4a[((((slot-(0x5d8+4634-0x17f1)) * (0xb25+8868-0x25c9) + z615b449cad           + (ch-(0x1a20+2533-0x2404)) * (0xd75+6493-0x26ce))/(0x28f+6483-0x1be0)))]
#define zb18daf3aee(slot,ch)              za42cf7dd4a[((((slot-(0x55a+1422-0xae7)) * (0xb75+19-0x388) + zb20fe15b56             + (ch-(0x642+207-0x710)) * (0x1bfb+1510-0x21dd))/(0x46a+1608-0xab0)))]
#define z64aac58d70(slot)                 za42cf7dd4a[((((slot-(0x20b8+1003-0x24a2)) * (0x964+3101-0xd81) + z5603507732                         )/(0xbba+3776-0x1a78)))]
#define z8eeedcb2d8(slot)                 za42cf7dd4a[((((slot-(0x19c7+3228-0x2662)) * (0x1d21+2891-0x206c) + zbaedcecb33                         )/(0xb1b+826-0xe53)))]
#define z21c03bb35c(slot)          za42cf7dd4a[((((slot-(0x1695+2775-0x216b)) * (0x1344+6632-0x252c) + zdd9d7c18a2                  )/(0x1c4+1727-0x881)))]
#define z561661b03d(slot)          za42cf7dd4a[((((slot-(0x751+3092-0x1364)) * (0x21e7+2357-0x231c) + ze36fd17bd0                  )/(0xef5+1232-0x13c3)))]
#define z2646826950(slot)          za42cf7dd4a[((((slot-(0x42a+2137-0xc82)) * (0x132d+729-0xe06) + zd8e996cc5e                  )/(0xb89+6103-0x235e)))]
#define z9b3fb52a28(slot)            za42cf7dd4a[((((slot-(0x664+7838-0x2501)) * (0x9ad+3072-0xdad) + z38b9d91ae0                    )/(0x1ed2+1556-0x24e4)))]
#define z0c25523114(slot)            za42cf7dd4a[((((slot-(0xd9+5293-0x1585)) * (0xb11+8082-0x22a3) + z79cfc785ef                    )/(0x69c+4829-0x1977)))]
#define zbf1ecb42c3(slot)            za42cf7dd4a[((((slot-(0x8a+7694-0x1e97)) * (0x151b+4409-0x1e54) + z395b1a96f8                    )/(0xd6f+4120-0x1d85)))]
#define z2c88181def(slot)            za42cf7dd4a[((((slot-(0x16d+4087-0x1163)) * (0x17db+4949-0x2330) + z011f6e6b8b                    )/(0x559+4897-0x1878)))]
#define z6ec5eee58a(slot,ch)       za42cf7dd4a[((((slot-(0xeab+2081-0x16cb)) * (0x24df+1228-0x21ab) + zcddf3f512f      + (ch-(0xde4+6204-0x261f)) * (0x6aa+7711-0x24c5))/(0xa97+3603-0x18a8)))]
#define ze99021c8a7(slot,ch)       za42cf7dd4a[((((slot-(0x90d+6679-0x2323)) * (0x14c6+4404-0x1dfa) + z71763e75f8      + (ch-(0x10da+2759-0x1ba0)) * (0xbf1+5442-0x212f))/(0x619+4997-0x199c)))]
#define z049eb433ff(slot,ch)    za42cf7dd4a[((((slot-(0x367+3837-0x1263)) * (0x1180+4401-0x1ab1) + zf5aa914738   + (ch-(0x380+4838-0x1665)) * (0x19f0+641-0x1c6d))/(0x411+2009-0xbe8)))]
#define z5004a8b482(slot,ch)         za42cf7dd4a[((((slot-(0x1817+862-0x1b74)) * (0x948+9599-0x26c7) + zf064710957        + (ch-(0x33a+2376-0xc81)) *(0x1db+832-0x4fb))/(0xa00+1175-0xe95)))]
#define z3d189a1a42(slot,ch)         za42cf7dd4a[((((slot-(0x11d1+3836-0x20cc)) * (0x97d+3559-0xf64) + zed77e50b70        + (ch-(0x1517+3708-0x2392)) *(0x10dc+3766-0x1f72))/(0xdc9+1545-0x13d0)))]
#define z859529f28d(slot,ch)        za42cf7dd4a[((((slot-(0x82d+7560-0x25b4)) * (0x91c+2115-0x95f) + z8849a8e340       + (ch-(0x615+2288-0xf04)) *(0x1048+788-0x133c))/(0x1cb+1535-0x7c8)))]
#define z9b05f0457d(slot,ch)         za42cf7dd4a[((((slot-(0x50f+191-0x5cd)) * (0x18e4+252-0x11e0) + z2dd3682034        + (ch-(0xc1d+4059-0x1bf7)) *(0x688+7148-0x2254))/(0x1cb5+1032-0x20bb)))]
#define zace9039268(slot,ch)         za42cf7dd4a[((((slot-(0xf0f+666-0x11a8)) * (0x197d+2570-0x1b87) + z125464d13e        + (ch-(0xe02+6396-0x26fd)) *(0x7d9+2323-0x10cc))/(0x26d+8818-0x24dd)))]
#define zb17be837d3(slot,ch)              za42cf7dd4a[((((slot-(0x74c+8029-0x26a8)) * (0x11d2+4322-0x1ab4) + z807210a558             + (ch-(0x1e59+2048-0x2658)) *(0x297+7269-0x1edc))/(0x21f+6418-0x1b2f)))]
#define z20b82e916e(slot,ch)           za42cf7dd4a[((((slot-(0x1383+934-0x1728)) * (0x1af5+1275-0x17f0) + z512181a8d5          + (ch-(0x9eb+6230-0x2240)) *(0x14c3+4008-0x244b))/(0x10fc+2800-0x1bea)))]
#define z2224f069d9(slot,ch)        za42cf7dd4a[((((slot-(0x582+1071-0x9b0)) * (0x14b5+5962-0x23ff) + z6bb464116c       + (ch-(0x14b9+3245-0x2165)) *(0x8f7+122-0x951))/(0x26f+6844-0x1d29)))]
#define zb4d1c01725(slot)           za42cf7dd4a[((((slot-(0xc37+2993-0x17e7)) * (0xae4+7540-0x2058) + z3605c57398                   )/(0x18a4+992-0x1c82)))]
#define z8b1762799d(slot)                 za42cf7dd4a[((((slot-(0x8c6+3211-0x1550)) * (0xffd+7288-0x2475) + z5b3ae3dec0                         )/(0x146a+888-0x17e0)))]
#define z123838a02a(slot)          za42cf7dd4a[((((slot-(0x513+5806-0x1bc0)) * (0x1ee7+169-0x1790) + z14104ee594                  )/(0xc46+1214-0x1102)))]
#define z8c808de8ef(slot)          za42cf7dd4a[((((slot-(0x152a+3632-0x2359)) * (0x1472+3650-0x1ab4) + z8389a0694a                  )/(0xcf3+4907-0x201c)))]
#define z87b9f369b2(slot)             za42cf7dd4a[((((slot-(0xa48+4815-0x1d16)) * (0x1afc+2122-0x1b46) + zfd273e051e                     )/(0xda9+6498-0x2709)))]
#define z6efd834b2a(slot)            za42cf7dd4a[((((slot-(0xc8a+3574-0x1a7f)) * (0x1cef+2742-0x1fa5) + z4267492038                    )/(0x10c+645-0x38f)))]
#define zfaa050b79d(slot)                  za42cf7dd4a[((((slot-(0x9c9+7112-0x2590)) * (0x1a9d+2731-0x1d48) + z88e2416cde                          )/(0x59b+3473-0x132a)))]
#define zb27b482aa2(slot)              za42cf7dd4a[((((slot-(0x1063+620-0x12ce)) * (0x1a21+4685-0x246e) + zf4a8506aca                      )/(0x11c4+5078-0x2598)))]
#define z2a95cb8008(slot)           za42cf7dd4a[((((slot-(0x6e0+5137-0x1af0)) * (0x1fd0+686-0x1a7e) + za340fd67b9                   )/(0x922+1836-0x104c)))]
#define zc19b85bb75(slot)              za42cf7dd4a[((((slot-(0x7ef+7337-0x2497)) * (0x1855+5324-0x2521) + z4927a023af                      )/(0xd92+3293-0x1a6d)))]
#define z5324236a2f(slot)             za42cf7dd4a[((((slot-(0xc3c+4863-0x1f3a)) * (0xeff+7427-0x2402) + z3a3c1415c9                     )/(0xbbf+4462-0x1d2b)))]
#define z50fbb35dbc(slot)        za42cf7dd4a[((((slot-(0xd04+5632-0x2303)) * (0x233d+2650-0x2597) + z2f17ac91c1                )/(0x708+4810-0x19d0)))]
#define z359c1d60c8()         za42cf7dd4a[((12288 / (0x1c4c+2536-0x2632)))] 
#define z9976d74502()       za42cf7dd4a[((12292 / (0xd7+9019-0x2410)))] 
#define z828a61b0f6()           za42cf7dd4a[((12296 / (0xbad+2392-0x1503)))] 
#define z8482c363f2()       za42cf7dd4a[((12300 / (0x1b2+466-0x382)))] 
#define zf9143fcdba()          za42cf7dd4a[((12344 / (0x2230+1034-0x2638)))] 
#define z32992c1e7b()    za42cf7dd4a[((12304 / (0x1f36+563-0x2167)))] 
#define zaa6d1f788a()   za42cf7dd4a[((12308 / (0x2cc+5315-0x178d)))] 
#define z626f7f443b()         za42cf7dd4a[((12312 / (0xa6c+6320-0x231a)))] 
#define za30f12f23b()      za42cf7dd4a[((12316 / (0x10a5+2895-0x1bf2)))] 
#define z55743775eb()          za42cf7dd4a[((12320 / (0x1ee8+1462-0x249c)))] 
#define z7a4d487411()      za42cf7dd4a[((12336 / (0x1a0+2290-0xa90)))] 
#define PLATFORM()            za42cf7dd4a[((12340 / (0x1e62+1217-0x2321)))] 
#define z5955864021()          za42cf7dd4a[((12348 / (0x1058+4439-0x21ad)))] 
#define z3c7df23547()        za42cf7dd4a[((12352 / (0x1189+336-0x12d7)))] 
#define z56991a8f1b()       za42cf7dd4a[((12360 / (0x14a7+3456-0x2225)))] 
#define zcf6bd1672d()       za42cf7dd4a[((12364 / (0xc74+2041-0x146b)))] 
#define zbc3942a92b()      za42cf7dd4a[((12368 / (0xd91+1872-0x14df)))] 
#define za6326d7613()      za42cf7dd4a[((12372 / (0xd52+1566-0x136e)))] 
#define z4dac1e9744()          za42cf7dd4a[((12376 / (0x1337+4902-0x265b)))] 
#define z658fbafc18()          za42cf7dd4a[((12380 / (0x225+9309-0x2680)))] 
#define z8a60033168()      za42cf7dd4a[((12384 / (0x91c+814-0xc48)))] 
#define z4baeb7dc8b()     za42cf7dd4a[((12388 / (0x1adb+1743-0x21a8)))] 
#define za8c8ee5776()      za42cf7dd4a[((12392 / (0x2367+662-0x25fb)))] 
#define z224a619e1e()       za42cf7dd4a[((12396 / (0x207+3033-0xdde)))] 
#define zd630e1c4f5()  za42cf7dd4a[((12400 / (0x1a5a+804-0x1d7c)))] 
#define ze64cf9894f()    za42cf7dd4a[((13312 / (0x1f7+444-0x3b1)))] 
#define zf8460e53e1(x) ((sizeof(x)/sizeof(x[(0xfd7+4424-0x211f)])))
static char*z387e3a68e7(int zf0aadfa29e){static char*z6579388d80[]={"\x50\x4f\x53\x5f\x44\x41\x54\x41\x5f\x4c\x4f","\x50\x4f\x53\x5f\x44\x41\x54\x41\x5f\x48\x49","\x42\x41\x4e\x44\x57\x49\x44\x54\x48","\x42\x41\x4e\x44\x57\x49\x44\x54\x48\x5f\x53\x45\x4c","\x4c\x44\x5f\x41\x43\x54\x49\x56\x45\x5f\x43\x48\x41\x4e\x4e\x45\x4c\x53","\x4c\x56\x44\x54\x5f\x54\x52\x41\x43\x4b\x5f\x48\x4f\x4c\x44","\x54\x45\x53\x54\x5f\x44\x32\x5f\x56\x45\x52\x49\x46\x59","\x54\x45\x53\x54\x5f\x45\x4e\x41\x42\x4c\x45","\x54\x45\x53\x54\x5f\x50\x4f\x53\x49\x54\x49\x4f\x4e","\x54\x57\x4f\x5f\x4f\x52\x5f\x46\x4f\x55\x52\x5f\x57\x49\x52\x45","\x52\x45\x46\x5f\x46\x52\x45\x51\x5f\x4d\x45\x41\x53\x55\x52\x45\x44\x5f\x4c\x4f","\x52\x45\x46\x5f\x46\x52\x45\x51\x5f\x4d\x45\x41\x53\x55\x52\x45\x44\x5f\x48\x49","\x53\x49\x47\x5f\x56\x4c\x4c\x5f\x4d\x45\x41\x53\x55\x52\x45\x44","\x52\x45\x46\x5f\x56\x4f\x4c\x54\x41\x47\x45\x5f\x4d\x45\x41\x53\x55\x52\x45\x44","\x53\x49\x47\x5f\x4c\x4f\x53\x53\x5f\x54\x48\x52","\x52\x45\x46\x5f\x4c\x4f\x53\x53\x5f\x54\x48\x52","\x4c\x56\x44\x54\x5f\x53\x43\x41\x4c\x45","\x53\x49\x47\x5f\x53\x54\x41\x54\x55\x53","\x52\x45\x46\x5f\x53\x54\x41\x54\x55\x53","\x53\x49\x47\x5f\x53\x54\x41\x54\x55\x53\x5f\x49\x4e\x54\x5f\x45\x4e","\x52\x45\x46\x5f\x53\x54\x41\x54\x55\x53\x5f\x49\x4e\x54\x5f\x45\x4e","\x42\x49\x54\x5f\x53\x54\x41\x54\x55\x53\x5f\x49\x4e\x54\x5f\x45\x4e","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x46\x52\x45\x51\x5f\x4c\x4f","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x46\x52\x45\x51\x5f\x48\x49","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x56\x4f\x4c\x54\x5f\x4c\x4f","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x56\x4f\x4c\x54\x5f\x48\x49","\x44\x41\x54\x41\x5f\x42\x55\x46\x5f\x46\x49\x46\x4f\x5f\x56\x41\x4c","\x44\x41\x54\x41\x5f\x42\x55\x46\x5f\x46\x49\x46\x4f\x5f\x43\x4e\x54","\x44\x41\x54\x41\x5f\x42\x55\x46\x5f\x46\x49\x46\x4f\x5f\x53\x54\x41\x54\x55\x53","\x44\x41\x54\x41\x5f\x42\x55\x46\x5f\x48\x49\x5f\x54\x48\x52","\x44\x41\x54\x41\x5f\x42\x55\x46\x5f\x4c\x4f\x5f\x54\x48\x52","\x42\x55\x46\x5f\x44\x45\x4c\x41\x59\x5f\x53\x41\x4d\x50\x4c\x45","\x42\x55\x46\x5f\x4e\x55\x4d\x5f\x53\x41\x4d\x50\x4c\x45\x53","\x42\x55\x46\x5f\x53\x41\x4d\x50\x4c\x45\x5f\x52\x41\x54\x45","\x43\x4c\x45\x41\x52\x5f\x46\x49\x46\x4f","\x42\x55\x46\x5f\x44\x41\x54\x41\x5f\x54\x59\x50\x45","\x42\x55\x46\x5f\x54\x52\x49\x47\x47\x45\x52\x5f\x4d\x4f\x44\x45","\x53\x4f\x46\x54\x57\x41\x52\x45\x5f\x54\x52\x49\x47\x47\x45\x52","\x42\x49\x54\x5f\x53\x54\x41\x54\x55\x53","\x4d\x4f\x44\x55\x4c\x45\x5f\x44\x45\x53\x49\x47\x4e\x5f\x56\x45\x52","\x4d\x4f\x44\x55\x4c\x45\x5f\x44\x45\x53\x49\x47\x4e\x5f\x52\x45\x56","\x4d\x4f\x44\x55\x4c\x45\x5f\x44\x53\x50\x5f\x52\x45\x56","\x4d\x4f\x44\x55\x4c\x45\x5f\x46\x50\x47\x41\x5f\x52\x45\x56","\x4d\x4f\x44\x55\x4c\x45\x5f\x49\x44","\x56\x45\x43\x54\x5f\x42\x49\x54\x5f\x46\x41\x49\x4c","\x56\x45\x43\x54\x5f\x53\x49\x47\x4e\x41\x4c\x5f\x4c\x4f\x53\x53","\x56\x45\x43\x54\x5f\x52\x45\x46\x5f\x4c\x4f\x53\x53","\x56\x45\x43\x54\x5f\x4c\x4f\x43\x4b\x5f\x4c\x4f\x53\x53","\x56\x45\x43\x54\x5f\x50\x4f\x53\x49\x54\x49\x4f\x4e\x5f\x44\x45\x4c\x54\x41"};static char*ze6bbffa862="\x49\x4c\x4c\x45\x47\x41\x4c\x20\x52\x45\x47\x49\x53\x54\x45\x52\x20\x49\x4e\x44\x45\x58";if(zf0aadfa29e<(0xfb2+817-0x12e3)||zf0aadfa29e>=zf8460e53e1(z6579388d80)){SG_PRINTF(INFO,"\x25\x73\x20\x45\x52\x52\x4f\x52\x20\x69\x6e\x20\x67\x65\x74\x52\x65\x67\x54\x79\x70\x65\x3a\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x69\x52\x65\x67\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x3a\x20\x69\x52\x65\x67\x20\x3d\x20\x25\x69\x2c\x20\x6d\x61\x78\x20\x3d\x20\x25\x69\x2e" "\n",zd6a3cd0da0,zf0aadfa29e,zf8460e53e1(z6579388d80));return ze6bbffa862;}return z6579388d80[zf0aadfa29e];}static int z18572e0c5a(int zf0aadfa29e){static const int z6a2cfde11b[]={(0x6c4+8251-0x26fd),(0x17f5+2453-0x2188),(0x917+4856-0x1c0e),(0x43d+7389-0x211a),(0xb84+6408-0x248c),(0xd66+2950-0x18ec),(0x110+6538-0x1a9a),(0x1588+2479-0x1f37),(0xf33+171-0xfde),(0xc55+1185-0x10f6),(0xd0c+4225-0x1d8b),(0x114c+602-0x13a4),(0xe33+1895-0x1599),(0x2d0+2602-0xcf9),(0x1f04+1249-0x23e4),(0x968+4644-0x1b8b),(0xc6b+199-0xd31),
(0x1eba+300-0x1fe6),(0x603+7194-0x221d),(0x2210+679-0x24b7),(0x1907+817-0x1c38),(0xbeb+3565-0x19d8),(0x1206+474-0x13e0),(0x1011+5748-0x2685),(0xc92+4123-0x1cad),(0x272+885-0x5e7),(0x17ac+755-0x1a9e),(0x1379+3383-0x20af),(0x212+6379-0x1afc),(0x289+7618-0x2043),(0xc04+838-0xf42),(0xd36+4999-0x20b5),(0x30f+8495-0x2436),(0x540+817-0x869),(0xbc3+2952-0x1743),(0xbc2+3970-0x1b3c),(0xa8c+2810-0x157e),(0x8dd+2949-0x1462),(0x8e8+2680-0x1360),(0x1c50+2010-0x242a),(0xb49+2352-0x1479),(0x1218+192-0x12d8),(0x7cd+1441-0xd6e),(0xb3a+2365-0x1477),(0x32d+2442-0xcb7),(0x71d+6458-0x2057),(0xbb4+2825-0x16bd),(0x2da+4401-0x140b),(0x6d0+1050-0xaea)};if(zf0aadfa29e<(0x1fc1+229-0x20a6)||zf0aadfa29e>=zf8460e53e1(z6a2cfde11b)){SG_PRINTF(INFO,"\x25\x73\x20\x45\x52\x52\x4f\x52\x20\x69\x6e\x20\x67\x65\x74\x52\x65\x67\x54\x79\x70\x65\x3a\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x69\x52\x65\x67\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x3a\x20\x69\x52\x65\x67\x20\x3d\x20\x25\x69\x2c\x20\x6d\x61\x78\x20\x3d\x20\x25\x69\x2e" "\n",zd6a3cd0da0,zf0aadfa29e,zf8460e53e1(z6a2cfde11b));return-(0x4cd+3883-0x13f7);}return z6a2cfde11b[zf0aadfa29e];}static int zd15c590fb6(int zb3bcd8e2ee){int i;static const int z786beb0eba[]={(0x3d+6303-0x18dc),(0x16a7+2162-0x1f15),(0x4b6+5675-0x1aa1),(0xc81+6791-0x26b8),(0x17e8+496-0x197c),(0x18d3+1132-0x1cdf),(0x4e6+2229-0xd37),(0x704+3788-0x1568),(0x116+859-0x401),(0xdd6+2347-0x1689),(0x5a9+6030-0x1c97),(0x746+5881-0x1d9b),(0x6c7+4074-0x15f1),(0x224a+861-0x24d7),(0x1b99+289-0x1bba),(0x842+8110-0x26e0),(0xbbb+3196-0x16f7),(0x98a+2617-0x11f3),(0x439+7701-0x207a),(0x1326+3635-0x1f75),(0xadc+6111-0x20d3),(0xee0+1321-0x121d),(0x178f+2879-0x20ce),(0x629+4143-0x1454),(0x238f+689-0x2438),(0xb16+5015-0x1ca1),(0x1d4f+1263-0x1c3e),(0xddf+2758-0x1295),(0x1497+1945-0x1610),(0x731+7450-0x1e0b),1604,(0x1f3f+1312-0x1e17),(0xd1a+6694-0x20f4),(0x943+7821-0x2180),(0x14b9+5061-0x222a),(0x1607+5113-0x23a8),(0x158b+3559-0x1d16),(0x103b+4997-0x1d00),(0x1191+1665-0x1112),(0x19bf+2250-0x1b21),(0x1f66+1987-0x1fbd),(0x8b0+8019-0x2093),(0x261b+160-0x1f47),(0x142f+2988-0x1863),1984,(0xc26+7822-0x22f0),(0xe7b+4963-0x1a16),(0x17f5+195-0x10ec),(0x10da+5852-0x1fe6)};for(i=(0xc90+6646-0x2686);i<zf8460e53e1(z786beb0eba);i++){if(z786beb0eba[i]==zb3bcd8e2ee)return i;}return-(0xc93+1721-0x134b);}static char msg[(0x35c+3680-0x10bc)];static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x16f8+1389-0x1c65));ssSetNumDiscStates(S,(0xa9a+1397-0x100f));ssSetNumInputPorts(S,(0x186d+2710-0x2303));ssSetNumOutputPorts(S,mxGetN(za9d8fb6bcf));for(i=(0x164a+3531-0x2415);i<mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x5ed+4586-0x17d6));ssSetOutputPortDataType(S,i,SS_DOUBLE);}ssSetNumSampleTimes(S,(0x366+1255-0x84c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x45b+8112-0x240b));ssSetNumNonsampledZCs(S,(0x290+6516-0x1c04));for(i=(0x54b+2295-0xe42);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xa0+6443-0x19cb));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x968+167-0xa0f)]==-1.0){ssSetSampleTime(S,(0x1cc5+655-0x1f54),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xc6+259-0x1c9),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x2d7+8114-0x2289),mxGetPr(z3832b85a32)[(0x1f85+1750-0x265b)]);ssSetOffsetTime(S,(0x1049+4773-0x22ee),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zc3b39a639a;uint16_t pci_bus=(0x7d4+6762-0x223e),pci_slot=(0x63a+6270-0x1eb8);volatile uint16_t*za42cf7dd4a;uint16_t z0879a25298;uint32_t i,channel,z615725805d;int slot=(int)mxGetPr(z86992bd6b1)[(0x1b97+2343-0x24be)];const uint32_t ze3584cafff=(uint32_t)mxGetN(za9d8fb6bcf);int ch;uint32_t moduleId=(uint32_t)mxGetPr(ze13f49a01f)[(0x82d+3022-0x13fb)];sg_mod_info*mod_info;mod_info=sg_module_get_single(z64e93986da,moduleId);if(mod_info==NULL){mod_info=sg_module_register(z64e93986da,moduleId);if((int)mxGetPr(z702a26a5e9)[(0x25c+920-0x5f4)]<(0x1b3b+2997-0x26f0)){if(sg_findPciDevice(&zc3b39a639a,zd6a3cd0da0,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{if(mxGetN(z702a26a5e9)==(0x7e6+3238-0x148b)){pci_bus=(0xb74+2491-0x152f);pci_slot=(uint16_t)mxGetPr(z702a26a5e9)[(0x16b3+3922-0x2605)];}else{pci_bus=(uint16_t)mxGetPr(z702a26a5e9)[(0xa77+1093-0xebc)];pci_slot=(uint16_t)mxGetPr(z702a26a5e9)[(0x103b+35-0x105d)];}if(sg_findPciDevice(&zc3b39a639a,zd6a3cd0da0,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,pci_bus,pci_slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}za42cf7dd4a=(volatile uint16_t*)sg_mapMemory(&zc3b39a639a,(0x2f0+6975-0x1e2f));mod_info->custom_data=(void*)za42cf7dd4a;}else{SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x25\x73\x20\x6d\x6f\x64\x75\x6c\x65" "\n",zd6a3cd0da0);za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(z64e93986da,(uint32_t)mxGetPr(ze13f49a01f)[(0xd8b+5838-0x2459)]);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x31\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n");return;}}if(slot<(0xd65+3683-0x1bc7)||slot>z5674e18e88){sprintf(msg,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x73\x75\x62\x73\x6c\x6f\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}if(ze3584cafff<(0x1252+477-0x142e)||ze3584cafff>z5674e18e88){sprintf(msg,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}for(i=(0x182+5362-0x1674);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];if(ch<(0xfeb+3120-0x1c1a)||ch>z5674e18e88){sprintf(msg,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}}i=(0x6b9+2943-0x1238);while((z626f7f443b()!=43605)&&(i<(0x15e7+801-0x18d6))){i++;sg_wait_s(0.001);}if(i>=(0x44c+4297-0x14e3)){sprintf(msg,"\n" "\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x43\x61\x6e\x27\x74\x20\x61\x63\x63\x65\x73\x73\x20\x74\x6f\x20\x6d\x6f\x64\x75\x6c\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}z0879a25298=zfaa050b79d(slot);if((z0879a25298<z20f97d736d)||(z0879a25298>z24077972a0)){sprintf(msg,"\x25\x73\x20\x5b\x25\x64\x2f\x25\x64\x5d\x3a\x20\x57\x72\x6f\x6e\x67\x20\x70\x6c\x75\x67\x2d\x69\x6e\x20\x27\x25\x63\x25\x63\x27\x20\x69\x6e\x20\x73\x6c\x6f\x74\x20\x25\x69\x2e",zd6a3cd0da0,pci_bus,pci_slot,(char)(z0879a25298>>(0x13d8+4133-0x23f5)),(char)z0879a25298,slot);ssSetErrorStatus(S,msg);return;}for(i=(0x1f0b+739-0x21ee);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];if(mxGetN(zf1b17602bb)>(0x310+4427-0x145a)){z0879a25298=(uint16_t)(mxGetPr(zf1b17602bb)[i]*(0x11a+1790-0x80e)*0.9);}else{z0879a25298=(uint16_t)(mxGetPr(zf1b17602bb)[(0x1af2+517-0x1cf7)]*(0x595+707-0x84e)*0.9);}zcd6aa986d5(slot,ch)=z0879a25298;z403d45b116;}for(i=(0x2aa+6039-0x1a41)
;i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];if(mxGetN(z6851db3a5b)>(0x1572+95-0x15d0)){z0879a25298=(uint16_t)(mxGetPr(z6851db3a5b)[i]*(0x235+455-0x3f2)*0.9);}else{z0879a25298=(uint16_t)(mxGetPr(z6851db3a5b)[(0x22b+8071-0x21b2)]*(0x1e1+8095-0x2176)*0.9);}zeecf280bb9(slot,ch)=z0879a25298;z403d45b116;}z1c46a1fd49(slot)=(0x69a+3033-0x1264);for(i=(0x170c+3894-0x2642);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];zd139276cb7(slot,ch)=(0x330+3173-0xf6b);z403d45b116;zd139276cb7(slot,ch)=(0x9d5+7116-0x2579);z403d45b116;}z0879a25298=(0xb5f+1734-0x1225);for(i=(0x192b+1808-0x203b);i<ze3584cafff;i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xb2a+3216-0x17b9);z615725805d=(mxGetN(z8759454a33)>(0x129a+1635-0x18fc))?(uint32_t)mxGetPr(z8759454a33)[i]:(uint32_t)mxGetPr(z8759454a33)[(0x16c6+929-0x1a67)];z615725805d=(z615725805d==(0x16a1+3501-0x244e))?(0xc47+6544-0x25d5):(0x1495+1463-0x1a4b);z0879a25298|=(z615725805d<<((0x17a9+2683-0x2222)*channel));}z56becc4131(slot)=z0879a25298;for(i=(0x5d1+3772-0x148d);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];zb18daf3aee(slot,ch)=65535;z403d45b116;}z0879a25298=(0x146+6239-0x19a5);for(i=(0x6b1+3823-0x15a0);i<ze3584cafff;i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1515+4099-0x2517);z0879a25298|=((0x225+8013-0x2171)<<channel);}zd342ccc2ba(slot)=z0879a25298;z03315844fb(slot)=(0x12af+2586-0x1cc5);zd608c0fe24(slot)=(0x91a+6921-0x2423);for(i=(0x12c6+3532-0x2092);zd608c0fe24(slot)!=(0x197+6754-0x1ba4);i++){if(i>(0x12b7+2387-0x1ba6)){sprintf(msg,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x54\x65\x73\x74\x20\x44\x32\x20\x66\x61\x69\x6c\x65\x64\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}sg_wait_s(0.01);}SG_PRINTF(INFO,"\x25\x73\x20\x53\x6c\x6f\x74\x20\x25\x69\x3a\x20\x25\x73\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x65\x64\x2e" "\n",zd6a3cd0da0,slot,zbb2ebcc7de);
#ifdef zf9506af2d6
{FILE*ze0541857aa=fopen(z6265bf51f4,"\x77\x2b");int ze4f87e9bf4=(0x23a+9013-0x256f),zf0aadfa29e,ze93aba4ce7,zd0072007fc=(0x156+6242-0x19b8),z26dbd73a5e,z6a2cfde11b;sg_wait_s((0xf8+4766-0x1395));SG_PRINTF(DEBUG,"\x43\x72\x65\x61\x74\x69\x6e\x67\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x64\x75\x6d\x70\x20\x66\x69\x6c\x65\x2e\x2e\x2e\x20");zd0072007fc=(slot-(0x1d75+1270-0x226a))*(0x1396+2059-0x13a1);fprintf(ze0541857aa,"\x41\x64\x64\x72\x2c\x56\x61\x6c\x48\x65\x78\x2c\x56\x61\x6c\x44\x65\x63\x2c\x52\x65\x67\x4e\x61\x6d\x65\x2c\x43\x48\x20" "\n");while(ze4f87e9bf4<(0xf35+2339-0x1058)){zf0aadfa29e=zd15c590fb6(ze4f87e9bf4);if(zf0aadfa29e<(0xe31+4913-0x2162)){ze4f87e9bf4+=(0x2f2+7839-0x218d);}else{z6a2cfde11b=z18572e0c5a(zf0aadfa29e);if(z6a2cfde11b==(0xd72+166-0xe18)){ze93aba4ce7=(zd0072007fc+ze4f87e9bf4)/(0x4e1+2322-0xdf1);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x30\x78\x25\x30\x34\x78\x2c\x25\x35\x69\x2c\x25\x73\x2c" "\n",ze93aba4ce7*(0x1f8b+316-0x20c5),za42cf7dd4a[ze93aba4ce7],za42cf7dd4a[ze93aba4ce7],z387e3a68e7(zf0aadfa29e));ze4f87e9bf4+=(0x173f+1086-0x1b79);}else{for(ch=(0x301+5878-0x19f7);ch<z5674e18e88;ch++){for(z26dbd73a5e=(0x1671+3832-0x2569);z26dbd73a5e<z6a2cfde11b;z26dbd73a5e++){ze93aba4ce7=(zd0072007fc+ze4f87e9bf4)/(0x164b+4105-0x2652);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x30\x78\x25\x30\x34\x78\x2c\x25\x35\x69\x2c\x25\x73\x2c\x25\x69" "\n",ze93aba4ce7*(0x618+3745-0x14b7),za42cf7dd4a[ze93aba4ce7],za42cf7dd4a[ze93aba4ce7],z387e3a68e7(zf0aadfa29e+z26dbd73a5e),ch+(0x1857+3275-0x2521));ze4f87e9bf4+=(0x12ac+59-0x12e3);}}}}}fprintf(ze0541857aa,"\x49\x4f\x34\x32\x31\x20\x4d\x6f\x74\x68\x65\x72\x62\x6f\x61\x72\x64\x20\x49\x6e\x66\x6f\x2c\x2c\x2c\x2c" "\n");fprintf(ze0541857aa,"\x50\x61\x72\x74\x20\x4e\x75\x6d\x62\x65\x72\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z359c1d60c8(),z359c1d60c8());fprintf(ze0541857aa,"\x53\x65\x72\x69\x61\x6c\x20\x4e\x75\x6d\x62\x65\x72\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z9976d74502(),z9976d74502());fprintf(ze0541857aa,"\x44\x61\x74\x65\x20\x43\x6f\x64\x65\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z828a61b0f6(),z828a61b0f6());fprintf(ze0541857aa,"\x50\x43\x42\x20\x52\x65\x76\x20\x4c\x65\x76\x65\x6c\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z8482c363f2(),z8482c363f2());fprintf(ze0541857aa,"\x50\x72\x6f\x63\x65\x73\x73\x6f\x72\x20\x52\x65\x76\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z32992c1e7b(),z32992c1e7b());fprintf(ze0541857aa,"\x50\x43\x49\x20\x46\x50\x47\x41\x20\x52\x65\x76\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",zaa6d1f788a(),zaa6d1f788a());fprintf(ze0541857aa,"\x44\x65\x73\x69\x67\x6e\x20\x56\x65\x72\x73\x69\x6f\x6e\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z7a4d487411(),z7a4d487411());fprintf(ze0541857aa,"\x50\x6c\x61\x74\x66\x6f\x72\x6d\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",PLATFORM(),PLATFORM());fprintf(ze0541857aa,"\x4d\x6f\x64\x65\x6c\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",zf9143fcdba(),zf9143fcdba());fprintf(ze0541857aa,"\x47\x65\x6e\x65\x72\x61\x74\x69\x6f\x6e\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z5955864021(),z5955864021());fprintf(ze0541857aa,"\x53\x70\x65\x63\x69\x61\x6c\x20\x53\x70\x65\x63\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z3c7df23547(),z3c7df23547());fprintf(ze0541857aa,"\n\n" "\x41\x6c\x6c\x20\x72\x65\x67\x69\x73\x74\x65\x72\x73\x20\x28\x72\x65\x67\x61\x72\x64\x6c\x65\x73\x73\x20\x69\x66\x20\x64\x6f\x63\x75\x6d\x65\x6e\x74\x65\x64\x20\x6f\x72\x20\x6e\x6f\x74\x29\x2c\x2c\x2c\x2c" "\n");fprintf(ze0541857aa,"\x41\x64\x64\x72\x2c\x56\x61\x6c\x28\x48\x45\x58\x29\x2c\x56\x61\x6c\x28\x64\x65\x63\x29\x2c\x2c" "\n");ze4f87e9bf4=(0x319+736-0x5f9);while(ze4f87e9bf4<2048){ze93aba4ce7=(zd0072007fc+ze4f87e9bf4)/(0x15c0+833-0x18ff);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x30\x78\x25\x30\x34\x78\x2c\x25\x35\x69\x2c\x2c" "\n",ze93aba4ce7*(0x113+8667-0x22ec),za42cf7dd4a[
ze93aba4ce7],za42cf7dd4a[ze93aba4ce7]);ze4f87e9bf4+=(0x68+8513-0x21a5);}fclose(ze0541857aa);SG_PRINTF(DEBUG,"\x64\x6f\x6e\x65\x2e" "\n");}
#endif
#ifdef z536fbb5294
{FILE*ze0541857aa=fopen(z88ca2e8e70,"\x77\x2b");for(i=(0xf5c+5788-0x25f8);i<ze3584cafff;i++){fprintf(ze0541857aa,"\x43\x48\x2c\x50\x6f\x73\x69\x74\x69\x6f\x6e\x2c\x64\x65\x63\x50\x2c");fprintf(ze0541857aa,"\x52\x65\x66\x46\x72\x65\x71\x2c\x64\x65\x63\x45\x46\x2c");fprintf(ze0541857aa,"\x52\x65\x66\x56\x6f\x6c\x74\x2c\x64\x65\x63\x45\x56\x2c");fprintf(ze0541857aa,"\x53\x69\x67\x56\x6f\x6c\x74\x2c\x64\x65\x63\x53\x56\x2c");}fprintf(ze0541857aa,"\n");fclose(ze0541857aa);}
#endif
#endif
}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint16_t*za42cf7dd4a;uint32_t i,ze3584cafff,ch;double*y;int16_t z9add8982f5;int slot=(int)mxGetPr(z86992bd6b1)[(0xd9c+2705-0x182d)];
#ifdef z536fbb5294
uint32_t z615725805d;uint16_t z0879a25298;double r;FILE*ze0541857aa=fopen(z88ca2e8e70,"\x61");
#endif
za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(z64e93986da,(uint32_t)mxGetPr(ze13f49a01f)[(0x1c0+7895-0x2097)]);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x31\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}ze3584cafff=(uint32_t)mxGetN(za9d8fb6bcf);for(i=(0x1d1a+1946-0x24b4);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];y=ssGetOutputPortRealSignal(S,i);z9add8982f5=(int16_t)ze5668a942c(slot,ch);y[(0x28+8032-0x1f88)]=((double)z9add8982f5)/((0x108+4252-0x11a3)<<(0xde6+4805-0x209c));
#ifdef z536fbb5294
fprintf(ze0541857aa,"\x25\x69\x2c\x30\x78\x25\x30\x34\x78\x2c\x25\x31\x2e\x36\x66\x2c",ch,(int16_t)z9add8982f5,y[(0x15e3+838-0x1929)]);z615725805d=(z853692a017(slot,ch)&65535)+((zbbd5933507(slot,ch)<<(0x4b9+5618-0x1a9b))&4294901760);r=(double)z615725805d/(0x122d+3246-0x1e77);fprintf(ze0541857aa,"\x30\x78\x25\x30\x38\x78\x2c\x25\x34\x2e\x31\x66\x2c",z615725805d,r);z0879a25298=z03fc80adb6(slot,ch);r=(double)z0879a25298/(0x156f+361-0x1674);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x25\x32\x2e\x32\x66\x2c",z0879a25298,r);z0879a25298=zf23e326281(slot,ch);r=(double)z0879a25298/(0x124d+4349-0x22e6);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x25\x32\x2e\x32\x66\x2c",z0879a25298,r);
#endif
}
#ifdef z536fbb5294
fprintf(ze0541857aa,"\n");fclose(ze0541857aa);
#endif
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelExit(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t moduleId=(uint32_t)mxGetPr(ze13f49a01f)[(0x96+9730-0x2698)];sg_module_unregister(z64e93986da,moduleId);SG_PRINTF(DEBUG,"\x49\x4f\x34\x32\x31\x2d\x31\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n");
#endif
}
#include "sg_sfcn_glue.h"   

