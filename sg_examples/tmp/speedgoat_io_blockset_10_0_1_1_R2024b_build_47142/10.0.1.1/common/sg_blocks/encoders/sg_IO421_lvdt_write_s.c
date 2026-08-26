// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL  (0x1c3+7866-0x207b)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME   sg_IO421_lvdt_write_s
#define zd6a3cd0da0 "\x49\x4f\x34\x32\x31\x2d\x33"
#define zbb2ebcc7de "\x4c\x56\x44\x54\x2f\x52\x56\x44\x54\x20\x73\x69\x6d\x75\x6c\x61\x74\x69\x6f\x6e"
#define zdd9aa31c07 30354
#define z95835284b8 5548
#define z5674e18e88 (0x850+7471-0x257c)
#define z20f97d736d 13616 
#define z24077972a0   13657 
#define z403d45b116 za42cf7dd4a[(0x189b+3529-0x2664)]    
char*zb2e46356dc[]={"\x6c\x76\x57\x31\x5f\x72\x65\x67\x2e\x63\x73\x76","\x6c\x76\x57\x32\x5f\x72\x65\x67\x2e\x63\x73\x76","\x6c\x76\x57\x33\x5f\x72\x65\x67\x2e\x63\x73\x76"};
#define z6265bf51f4(slot) ((slot > (0x12a9+108-0x1315) && slot <= (0xc79+31-0xc95))? zb2e46356dc[slot-(0x2247+442-0x2400)] : "\x6c\x76\x57\x30\x5f\x72\x65\x67\x2e\x63\x73\x76")
char*z935f3ca1be[]={"\x6c\x76\x57\x31\x5f\x72\x75\x6e\x2e\x63\x73\x76","\x6c\x76\x57\x32\x5f\x72\x75\x6e\x2e\x63\x73\x76","\x6c\x76\x57\x33\x5f\x72\x75\x6e\x2e\x63\x73\x76"};
#define z88ca2e8e70(slot) ((slot > (0x2af+4001-0x1250) && slot <= (0xb75+3835-0x1a6d))? z935f3ca1be[slot-(0x19b7+1578-0x1fe0)] : "\x6c\x76\x57\x30\x5f\x72\x75\x6e\x2e\x63\x73\x76")
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
#define za9d8fb6bcf         ssGetSFcnParam(S, (0x122c+1566-0x184a))
#define z86992bd6b1         ssGetSFcnParam(S, (0x484+1143-0x8fa)) 
#define za80bdf5015    ssGetSFcnParam(S, (0xaf7+2307-0x13f8))
#define z1e1f908411   ssGetSFcnParam(S, (0x10a4+5050-0x245b))
#define z8d12cdfdee  ssGetSFcnParam(S, (0x468+4191-0x14c3))
#define z8f32a49296      ssGetSFcnParam(S, (0xab7+4508-0x1c4e))
#define zb377f6022b      ssGetSFcnParam(S, (0x1c79+2216-0x251b)) 
#define zf8013dab26      ssGetSFcnParam(S, (0x1011+1667-0x168d)) 
#define z3832b85a32       ssGetSFcnParam(S, (0x1f+3192-0xc8f))
#define z702a26a5e9            ssGetSFcnParam(S, (0x83f+5516-0x1dc2))  
#define z8759454a33          ssGetSFcnParam(S, (0x150d+3192-0x217b))
#define za6700577df     ssGetSFcnParam(S, (0xb9b+3731-0x1a23))
#define ze13f49a01f       ssGetSFcnParam(S, (0x1318+3520-0x20cc)) 
#define z38c9710147           ssGetSFcnParam(S, (0x1bb0+2001-0x2374))
#define z29a89d39e1     ssGetSFcnParam(S, (0x2270+907-0x25ed))
#define za2b6976fb4            ssGetSFcnParam(S, (0x23a5+644-0x261a))
#define zfad63a3095   ssGetSFcnParam(S, (0x1281+1955-0x1a14))
#define zdf24515981                       ((0x68+7-0x5e))
#define z2e6483d505              ((0x6c1+1622-0xd17))
#define zc5ce4cb81a              ((0x1e6c+631-0x20e3))
#define z2b17e2ee3b              ((0x622+7462-0x2348))
#define z7b38f83bd1          (0.0000000004656612873077390) 
#define zbfc4533cdf          (0x384+8615-0x252b)
#define zb8a1925ea5          (0x46f+4304-0x153b)
#define zf4c5100d43                (0x1730+1119-0x1b2b)
#define z24d2077e41                (0x761+906-0xa7b)
#define z9397e33cfc         (0xbdb+4409-0x1c94)
#define zcc582153b5         (0xa48+795-0xcd7)
#define z6d6e9ed697              (0xbfb+5092-0x1f47)
#define z1f0c94ecb1           (0xeda+2548-0x181e)
#define zc65b855664          (0x1e90+1429-0x22e5)
#define zcfbe33b057          (0xa95+5756-0x1fcd)
#define zcd19517108          (0x519+7080-0x1f61)
#define z8c697ada59          (0x759+833-0x936)
#define z9cf20097f1               (0x6ba+3006-0x10f8)
#define zce5113ce4f            (0x1585+1280-0x18fd)
#define zc183461c60           (0x17da+26-0x1668)
#define zed7ea714de          (0x1add+379-0x1ac0)
#define z466dbbe867       (0x14b8+2370-0x1c3a)
#define z8f47f3e584      (0xce9+1247-0x1000)
#define z25dfabfe74            (0x324+4229-0x11dd)
#define z66b0d5d3d0  (0xfac+3528-0x1ba4)
#define zaee4991894            (0xd2f+5981-0x22a4)
#define z92d0957603             (0x1149+4291-0x1f0c)
#define zedbface724             (0x5b6+4985-0x162b)
#define ze05e8ee79a              (0x1326+1598-0x1634)
#define z90831a2dad              (0x884+656-0x7e0)
#define z49d560bbc1              (0x81c+5917-0x1c01)
#define z2a0014d53f              (0x2666+11-0x2335)
#define zd2acabce83       (0x1772+3984-0x2002)
#define z758b2ec5f1       (0x981+7231-0x1ebc)
#define z0c48fe4b0b       (0x1005+3129-0x1536)
#define z4477927181       (0xc77+7401-0x2254)
#define zfa21d94b65   (0xeaf+4554-0x1969)
#define zf0a367e7e1     (0x20b3+251-0x1a46)
#define z8389a0694a         (0x101d+5769-0x1f3a)
#define zfd273e051e            1904
#define z4267492038           1908
#define z88e2416cde                 (0x1791+1707-0x16c4)
#define zc914265871       (0xc08+3236-0x10ec)
#define z70dd27add9       (0x1096+5765-0x1f57)
#define zb621d959d7       (0xc51+8101-0x242e)
#define z66af29e714   (0xabc+6114-0x1ad2)
#define zfc4acf0407(slot, ch)     za42cf7dd4a[((((slot-(0x776+7851-0x2620)) * (0xba9+3329-0x10aa) + zbfc4533cdf         + (ch-(0xcff+4497-0x1e8f)) * (0x297+6134-0x1a85))/(0xff5+4033-0x1fb4)))] 
#define zc70a18cdaf(slot, ch)     za42cf7dd4a[((((slot-(0x949+441-0xb01)) * (0xcd2+623-0x741) + zb8a1925ea5         + (ch-(0x1069+3766-0x1f1e)) * (0x610+1590-0xc3e))/(0x225+1714-0x8d5)))] 
#define z067bea3bcc(slot, ch)           za42cf7dd4a[((((slot-(0x2196+1314-0x26b7)) * (0xdd3+7579-0x236e) + zf4c5100d43               + (ch-(0x1b45+1961-0x22ed)) * (0x60c+310-0x73e))/(0x1735+251-0x182e)))] 
#define zb6956f14e9(slot, ch)           za42cf7dd4a[((((slot-(0x20e1+572-0x231c)) * 2048 + z24d2077e41               + (ch-(0x14b7+2628-0x1efa)) * (0x164d+893-0x19c6))/(0x1b2c+2914-0x268c)))] 
#define ze247702196(slot, ch)    za42cf7dd4a[((((slot-(0x733+2565-0x1137)) * (0xbdd+5717-0x1a32) + z9397e33cfc        + (ch-(0xc1c+3375-0x194a)) * (0x79d+7615-0x2558))/(0x11a9+4818-0x2479)))] 
#define z3424914fe5(slot, ch)    za42cf7dd4a[((((slot-(0xac8+4890-0x1de1)) * (0x1bd9+151-0x1470) + zcc582153b5        + (ch-(0x16c+6268-0x19e7)) * (0x355+5137-0x1762))/(0x17d0+2479-0x217d)))] 
#define z1bacb6e848(slot, ch)         za42cf7dd4a[((((slot-(0xcb8+4198-0x1d1d)) * (0x95c+8239-0x218b) + z6d6e9ed697             + (ch-(0x15a+764-0x455)) * (0x4aa+5728-0x1b06))/(0x1772+1328-0x1ca0)))] 
#define z734b0c83c9(slot)          za42cf7dd4a[((((slot-(0xeb3+2455-0x1849)) * (0xbc4+195-0x487) + z1f0c94ecb1                      )/(0x154+2236-0xa0e)))] 
#define z52c4b0bc02(slot, ch)     za42cf7dd4a[((((slot-(0x93+5492-0x1606)) * (0x18e8+203-0x11b3) + zc65b855664         + (ch-(0x1a6b+256-0x1b6a)) * (0x173f+2052-0x1f3b))/(0x76+2319-0x983)))] 
#define z7c7cd37cc9(slot, ch)     za42cf7dd4a[((((slot-(0x609+1292-0xb14)) * (0xb41+4183-0x1398) + zcfbe33b057         + (ch-(0xd0+9159-0x2496)) * (0xc38+2900-0x1784))/(0x6b+8853-0x22fe)))] 
#define zac4e78fba4(slot, ch)     za42cf7dd4a[((((slot-(0xe14+3547-0x1bee)) * (0xbf9+4573-0x15d6) + zcd19517108         + (ch-(0x255+599-0x4ab)) * (0x10a3+4749-0x2328))/(0x20d+9364-0x269f)))] 
#define z9e5260b14a(slot, ch)     za42cf7dd4a[((((slot-(0x16eb+2780-0x21c6)) * (0x1209+7301-0x268e) + z8c697ada59         + (ch-(0x2b8+5018-0x1651)) * (0x1349+1338-0x187b))/(0x18b4+1196-0x1d5e)))] 
#define zb745c1fe63(slot)              za42cf7dd4a[((((slot-(0x1d91+1458-0x2342)) * (0x85f+6071-0x1816) + z9cf20097f1                          )/(0x2046+521-0x224d)))] 
#define z4652155efa(slot)           za42cf7dd4a[((((slot-(0x2396+173-0x2442)) * (0x1dcd+3092-0x21e1) + zce5113ce4f                       )/(0x1d82+2203-0x261b)))] 
#define z40963198cc(slot)          za42cf7dd4a[((((slot-(0xdf3+2347-0x171d)) * (0x16ea+2413-0x1857) + zc183461c60                      )/(0x315+5186-0x1755)))] 
#define zcb2e5e84bc(slot)         za42cf7dd4a[((((slot-(0x1912+1440-0x1eb1)) * (0x90a+7842-0x1fac) + zed7ea714de                     )/(0x1821+920-0x1bb7)))] 
#define zbcdb5af90b(slot)      za42cf7dd4a[((((slot-(0x1698+3845-0x259c)) * (0x1426+6134-0x241c) + z466dbbe867                  )/(0x1bd9+1956-0x237b)))] 
#define zb05ee0e2ad(slot)     za42cf7dd4a[((((slot-(0x637+6713-0x206f)) * (0x1b22+573-0x155f) + z8f47f3e584                 )/(0x1544+2198-0x1dd8)))] 
#define z2e184ac1a4(slot)           za42cf7dd4a[((((slot-(0xc02+3380-0x1935)) * (0x1262+6204-0x229e) + z25dfabfe74                       )/(0x3d3+8640-0x2591)))] 
#define z291e24836a(slot) za42cf7dd4a[((((slot-(0x563+4-0x566)) * (0x1aa9+2507-0x1c74) + z66b0d5d3d0             )/(0x1007+4069-0x1fea)))] 
#define z2530e27808(slot, ch)       za42cf7dd4a[((((slot-(0xd4c+1910-0x14c1)) * (0x1340+2232-0x13f8) + zaee4991894           + (ch-(0xe8d+1412-0x1410)) * (0x20d6+701-0x238f))/(0xd2a+4463-0x1e97)))] 
#define z5c6ee6084b(slot, ch)        za42cf7dd4a[((((slot-(0xc8f+188-0xd4a)) * (0x1ae4+766-0x15e2) + z92d0957603            + (ch-(0x4bd+6465-0x1dfd)) * (0x17e5+2856-0x2305))/(0x237+7088-0x1de5)))] 
#define z405cc92672(slot, ch)        za42cf7dd4a[((((slot-(0x120+2677-0xb94)) * (0x16e4+5195-0x232f) + zedbface724            + (ch-(0x257+8608-0x23f6)) * (0xddd+2975-0x1974))/(0x1224+3802-0x20fc)))] 
#define z8976fea6f2(slot)             za42cf7dd4a[((((slot-(0x12a0+4189-0x22fc)) * (0x14f4+5561-0x22ad) + ze05e8ee79a                         )/(0x1476+4426-0x25be)))] 
#define zdce34940cd(slot)             za42cf7dd4a[((((slot-(0x1bea+738-0x1ecb)) * (0x1448+231-0xd2f) + z90831a2dad                         )/(0x7b0+6781-0x222b)))] 
#define zc6ade572cd(slot)             za42cf7dd4a[((((slot-(0x15e3+3285-0x22b7)) * (0x1159+5965-0x20a6) + z49d560bbc1                         )/(0x4f2+1257-0x9d9)))] 
#define z9c95a64e48(slot)             za42cf7dd4a[((((slot-(0x230+1144-0x6a7)) * (0x123f+4268-0x1aeb) + z2a0014d53f                         )/(0x17cc+3160-0x2422)))] 
#define z6ffda891be(slot)      za42cf7dd4a[((((slot-(0x1157+5183-0x2595)) * (0xc4c+4514-0x15ee) + zd2acabce83                  )/(0x1a80+252-0x1b7a)))] 
#define z2217f6677b(slot)      za42cf7dd4a[((((slot-(0x962+5719-0x1fb8)) * (0xacf+4006-0x1275) + z758b2ec5f1                  )/(0x1eb+2583-0xc00)))] 
#define zac8e51e974(slot)      za42cf7dd4a[((((slot-(0x1400+4213-0x2474)) * (0xf9f+4453-0x1904) + z0c48fe4b0b                  )/(0x2eb+644-0x56d)))] 
#define z296e2ef904(slot)      za42cf7dd4a[((((slot-(0x2126+1277-0x2622)) * (0x1349+149-0xbde) + z4477927181                  )/(0xad7+4042-0x1a9f)))] 
#define z514783e0ed(slot)  za42cf7dd4a[((((slot-(0x499+3819-0x1383)) * (0xaf2+5916-0x1a0e) + zfa21d94b65              )/(0x397+8713-0x259e)))] 
#define zdd4afc037d(slot)    za42cf7dd4a[((((slot-(0x871+6424-0x2188)) * (0x1e46+1316-0x1b6a) + zf0a367e7e1                )/(0xc13+3373-0x193e)))] 
#define z8c808de8ef(slot)        za42cf7dd4a[((((slot-(0x56+9194-0x243f)) * (0x19c8+609-0x1429) + z8389a0694a                    )/(0x89a+2431-0x1217)))] 
#define z87b9f369b2(slot)           za42cf7dd4a[((((slot-(0x1407+3963-0x2381)) * (0xbb8+3490-0x115a) + zfd273e051e                       )/(0x620+3882-0x1548)))] 
#define z6efd834b2a(slot)          za42cf7dd4a[((((slot-(0x784+5259-0x1c0e)) * (0xbe3+3152-0x1033) + z4267492038                      )/(0x1650+2330-0x1f68)))] 
#define zfaa050b79d(slot)                za42cf7dd4a[((((slot-(0x1d08+1733-0x23cc)) * (0x14bd+2157-0x152a) + z88e2416cde                            )/(0x417+5792-0x1ab5)))] 
#define zaabdadca94(slot)      za42cf7dd4a[((((slot-(0x857+1960-0xffe)) * (0x12ed+5998-0x225b) + zc914265871                  )/(0xd4+270-0x1e0)))] 
#define z7c641cef3a(slot)      za42cf7dd4a[((((slot-(0x1af6+2130-0x2347)) * (0x1ee0+398-0x186e) + z70dd27add9                  )/(0x1d65+1770-0x244d)))] 
#define z85bffa8bae(slot)      za42cf7dd4a[((((slot-(0x554+2673-0xfc4)) * (0x256d+1123-0x21d0) + zb621d959d7                  )/(0x1535+3393-0x2274)))] 
#define za764c436aa(slot)  za42cf7dd4a[((((slot-(0x69+7287-0x1cdf)) * (0xecd+1550-0xcdb) + z66af29e714              )/(0x1d65+139-0x1dee)))] 
#define z359c1d60c8()         za42cf7dd4a[((12288 / (0x16cb+3250-0x237b)))] 
#define z9976d74502()       za42cf7dd4a[((12292 / (0x167+3198-0xde3)))] 
#define z828a61b0f6()           za42cf7dd4a[((12296 / (0x16a3+2006-0x1e77)))] 
#define z8482c363f2()       za42cf7dd4a[((12300 / (0x1d2d+1099-0x2176)))] 
#define zf9143fcdba()          za42cf7dd4a[((12344 / (0x4a8+4205-0x1513)))] 
#define z32992c1e7b()    za42cf7dd4a[((12304 / (0x8cc+51-0x8fd)))] 
#define zaa6d1f788a()   za42cf7dd4a[((12308 / (0x68f+131-0x710)))] 
#define z626f7f443b()         za42cf7dd4a[((12312 / (0x1206+3372-0x1f30)))] 
#define za30f12f23b()      za42cf7dd4a[((12316 / (0x1a44+3156-0x2696)))] 
#define z55743775eb()          za42cf7dd4a[((12320 / (0x96f+1440-0xf0d)))] 
#define z7a4d487411()      za42cf7dd4a[((12336 / (0xd99+3305-0x1a80)))] 
#define PLATFORM()            za42cf7dd4a[((12340 / (0x150d+4102-0x2511)))] 
#define z5955864021()          za42cf7dd4a[((12348 / (0x8a0+2258-0x1170)))] 
#define z3c7df23547()        za42cf7dd4a[((12352 / (0x1f9+4359-0x12fe)))] 
#define z56991a8f1b()       za42cf7dd4a[((12360 / (0x117c+1135-0x15e9)))] 
#define zcf6bd1672d()       za42cf7dd4a[((12364 / (0x1d0a+1458-0x22ba)))] 
#define zbc3942a92b()      za42cf7dd4a[((12368 / (0x2b7+9040-0x2605)))] 
#define za6326d7613()      za42cf7dd4a[((12372 / (0x153d+2285-0x1e28)))] 
#define z4dac1e9744()          za42cf7dd4a[((12376 / (0x445+7634-0x2215)))] 
#define z658fbafc18()          za42cf7dd4a[((12380 / (0x1644+2632-0x208a)))] 
#define z8a60033168()      za42cf7dd4a[((12384 / (0x244+2125-0xa8f)))] 
#define z4baeb7dc8b()     za42cf7dd4a[((12388 / (0xd59+5811-0x240a)))] 
#define za8c8ee5776()      za42cf7dd4a[((12392 / (0x1335+182-0x13e9)))] 
#define z224a619e1e()       za42cf7dd4a[((12396 / (0x987+4994-0x1d07)))] 
#define zd630e1c4f5()  za42cf7dd4a[((12400 / (0x586+1825-0xca5)))] 
#define ze64cf9894f()    za42cf7dd4a[((13312 / (0x2077+1214-0x2533)))] 
#define zf8460e53e1(x) ((sizeof(x)/sizeof(x[(0x22cc+926-0x266a)])))
static char*z387e3a68e7(int zf0aadfa29e){static char*z6579388d80[]={"\x57\x52\x41\x50\x5f\x4c\x56\x44\x54\x5f\x50\x4f\x53\x5f\x4c\x4f","\x57\x52\x41\x50\x5f\x4c\x56\x44\x54\x5f\x50\x4f\x53\x5f\x48\x49","\x57\x52\x41\x50\x5f\x45\x58\x43\x5f\x56","\x57\x52\x41\x50\x5f\x53\x49\x47\x5f\x56","\x57\x52\x41\x50\x5f\x53\x49\x47\x5f\x4c\x4f\x53\x53\x5f\x54\x48\x52","\x57\x52\x41\x50\x5f\x45\x58\x43\x5f\x4c\x4f\x53\x53\x5f\x54\x48\x52","\x43\x48\x5f\x46\x52\x45\x51\x55\x45\x4e\x43\x59","\x53\x54\x41\x54\x55\x53\x5f\x53\x49\x47\x5f\x4c\x4f\x53\x53","\x44\x4c\x56\x5f\x53\x45\x54\x5f\x45\x58\x43\x5f\x56\x5f\x4c\x4f","\x44\x4c\x56\x5f\x53\x45\x54\x5f\x45\x58\x43\x5f\x56\x5f\x48\x49","\x44\x4c\x56\x5f\x53\x45\x54\x5f\x53\x49\x47\x5f\x56\x5f\x4c\x4f","\x44\x4c\x56\x5f\x53\x45\x54\x5f\x53\x49\x47\x5f\x56\x5f\x48\x49","\x44\x4c\x56\x5f\x54\x45\x53\x54\x5f\x45\x4e","\x44\x32\x5f\x54\x45\x53\x54\x5f\x56\x45\x52\x49\x46\x59","\x44\x4c\x56\x5f\x4f\x55\x54\x50\x55\x54\x5f\x4d\x4f\x44\x45","\x44\x4c\x56\x5f\x32\x57\x5f\x34\x57\x5f\x53\x45\x4c\x45\x43\x54","\x44\x4c\x56\x5f\x4d\x4f\x44\x55\x4c\x45\x5f\x50\x4f\x57\x45\x52\x5f\x45\x4e","\x44\x4c\x56\x5f\x41\x43\x54\x49\x56\x45\x5f\x43\x48\x5f\x53\x45\x4c\x45\x43\x54","\x44\x4c\x56\x5f\x45\x58\x43\x5f\x53\x54\x41\x54\x55\x53","\x44\x4c\x56\x5f\x50\x48\x5f\x4c\x4f\x43\x4b\x5f\x53\x54\x41\x54\x55\x53\x5f\x43\x48\x31\x5f\x32","\x44\x4c\x56\x5f\x53\x45\x54\x5f\x50\x48\x5f\x4f\x46\x46","\x44\x4c\x56\x5f\x57\x52\x5f\x50\x4f\x53\x5f\x4c\x4f","\x44\x4c\x56\x5f\x57\x52\x5f\x50\x4f\x53\x5f\x48\x49","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x56\x5f\x4c\x4f","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x56\x5f\x48\x49","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x46\x5f\x4c\x4f","\x4f\x53\x43\x5f\x53\x45\x54\x5f\x46\x5f\x48\x49","\x44\x4c\x56\x5f\x53\x54\x41\x54\x55\x53\x5f\x42\x49\x54\x5f\x54\x45\x53\x54","\x44\x4c\x56\x5f\x52\x45\x46\x5f\x4c\x4f\x53\x53\x5f\x49\x4e\x54\x5f\x45\x4e","\x44\x4c\x56\x5f\x53\x49\x47\x5f\x4c\x4f\x53\x53\x5f\x49\x4e\x54\x5f\x45\x4e","\x44\x4c\x56\x5f\x42\x49\x54\x5f\x46\x41\x49\x4c\x5f\x49\x4e\x54\x5f\x45\x4e","\x44\x4c\x56\x5f\x50\x48\x5f\x4c\x4f\x43\x4b\x5f\x4c\x4f\x53\x53\x5f\x49\x4e\x54\x5f\x45\x4e","\x4d\x4f\x44\x55\x4c\x45\x5f\x44\x45\x53\x49\x47\x4e\x5f\x56\x45\x52\x53\x49\x4f\x4e","\x4d\x4f\x44\x55\x4c\x45\x5f\x44\x45\x53\x49\x47\x4e\x5f\x52\x45\x56","\x4d\x4f\x44\x55\x4c\x45\x5f\x44\x53\x50\x5f\x52\x45\x56","\x4d\x4f\x44\x55\x4c\x45\x5f\x46\x50\x47\x41\x5f\x52\x45\x56","\x4d\x4f\x44\x55\x4c\x45\x5f\x49\x44","\x56\x45\x43\x54\x4f\x52\x5f\x49\x4e\x54\x5f\x42\x49\x54\x5f\x46\x41\x49\x4c","\x56\x45\x43\x54\x4f\x52\x5f\x49\x4e\x54\x5f\x52\x45\x46\x5f\x4c\x4f\x53\x53","\x56\x45\x43\x54\x4f\x52\x5f\x49\x4e\x54\x5f\x53\x49\x47\x5f\x4c\x4f\x53\x53","\x56\x45\x43\x54\x4f\x52\x5f\x49\x4e\x54\x5f\x50\x48\x5f\x4c\x4f\x43\x4b\x5f\x4c\x4f\x53\x53"};static char*ze6bbffa862="\x49\x4c\x4c\x45\x47\x41\x4c\x20\x52\x45\x47\x49\x53\x54\x45\x52\x20\x49\x4e\x44\x45\x58";if(zf0aadfa29e<(0x192b+2251-0x21f6)||zf0aadfa29e>=zf8460e53e1(z6579388d80)){SG_PRINTF(INFO,"\x25\x73\x20\x45\x52\x52\x4f\x52\x20\x69\x6e\x20\x67\x65\x74\x52\x65\x67\x54\x79\x70\x65\x3a\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x69\x52\x65\x67\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x3a\x20\x69\x52\x65\x67\x20\x3d\x20\x25\x69\x2c\x20\x6d\x61\x78\x20\x3d\x20\x25\x69\x2e" "\n",zd6a3cd0da0,zf0aadfa29e,zf8460e53e1(z6579388d80));return ze6bbffa862;}return z6579388d80[zf0aadfa29e];}static int z18572e0c5a(int zf0aadfa29e){static const int z6a2cfde11b[]={(0x58a+828-0x8c4),(0x1a4b+298-0x1b73),(0x1383+4499-0x2515),(0xf9f+2016-0x177e),(0x188f+798-0x1bac),(0xa73+4997-0x1df7),(0x36+1415-0x5bc),(0x1062+3483-0x1dfd),(0xe2c+6126-0x2618),(0xc6f+4429-0x1dba),(0x144+1681-0x7d3),(0xff5+1186-0x1495),(0x68b+1666-0xd0d),(0x247+4449-0x13a8),(0x605+3662-0x1453),(0x1286+2017-0x1a67),(0x1531+4448-0x2691),(0x159c+97-0x15fd),(0x936+4675-0x1b79),(0x72+6670-0x1a80),(0x9d5+3944-0x193c),(0x173a+1432-0x1cd0),(0x1aa5+2140-0x22ff),(0x968+6431-0x2287),(0x109c+3109-0x1cc1),(0x12b7+4670-0x24f5),(0x15bd+2625-0x1ffe),(0x1b24+852-0x1e78),(0xfb1+5559-0x2568),(0x10ed+5256-0x2575),
(0xa85+3284-0x1759),(0x173f+3819-0x262a),(0x1bfd+1981-0x23ba),(0x1ccc+2520-0x26a4),(0x11a7+4301-0x2274),(0x135+8730-0x234f),(0x265+1372-0x7c1),(0x1d3c+1205-0x21f1),(0xf1f+5882-0x2619),(0x256f+167-0x2616),(0xe27+3220-0x1abb)};if(zf0aadfa29e<(0x432+355-0x595)||zf0aadfa29e>=zf8460e53e1(z6a2cfde11b)){SG_PRINTF(INFO,"\x25\x73\x20\x45\x52\x52\x4f\x52\x20\x69\x6e\x20\x67\x65\x74\x52\x65\x67\x54\x79\x70\x65\x3a\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x69\x52\x65\x67\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x3a\x20\x69\x52\x65\x67\x20\x3d\x20\x25\x69\x2c\x20\x6d\x61\x78\x20\x3d\x20\x25\x69\x2e" "\n",zd6a3cd0da0,zf0aadfa29e,zf8460e53e1(z6a2cfde11b));return-(0xa0c+3988-0x199f);}return z6a2cfde11b[zf0aadfa29e];}static int zd15c590fb6(int zb3bcd8e2ee){int i;static const int z786beb0eba[]={(0x71c+4679-0x1963),(0xc3d+23-0xc50),(0x102+4407-0x11d5),(0x1e7+212-0x24b),(0x1470+4119-0x2407),(0x940+611-0xb17),(0x490+4280-0x14b0),(0x165b+3342-0x22b9),(0x20c1+1470-0x253f),(0x13f0+662-0x1542),(0x9dd+5139-0x1c90),(0x7b3+1755-0xd2a),(0x16d3+220-0x162f),(0x20e3+44-0x1f87),(0x1641+2138-0x1d0f),(0x929+5229-0x1bfe),(0xa15+5981-0x1fb2),(0xc43+4624-0x1c8b),(0xc4c+1219-0xf43),(0xa4d+6936-0x2395),(0x1098+2719-0x194f),(0x1e97+1862-0x22dd),(0x7dc+2164-0xd4c),(0x1aca+814-0x1ac8),(0x188b+1998-0x1d25),(0x470+5886-0x1836),(0xee6+500-0xd9e),(0xdc9+4292-0x178d),(0x1d03+847-0x194e),(0x1345+4595-0x1e30),(0xcbb+4596-0x17a3),(0x14a8+5883-0x2493),(0x23d6+782-0x1f7c),(0xe25+3930-0x1613),(0x2314+1598-0x21e2),(0xc84+1608-0xb58),(0x260c+1392-0x2404),(0x224c+1654-0x2102),(0x1f74+1347-0x1cf3),(0x260c+2050-0x2646),(0x1446+4347-0x1d75)};for(i=(0x2d2+8209-0x22e3);i<zf8460e53e1(z786beb0eba);i++){if(z786beb0eba[i]==zb3bcd8e2ee)return i;}return-(0x2145+1437-0x26e1);}static char msg[(0x1a73+242-0x1a65)];typedef struct{uint16_t z9f0f81f54c;uint16_t z4dcd279748;uint16_t z5e8ece4cca;uint16_t z8b90547431;uint16_t z681f9bef2b;}z85a1c7964f;static void mdlInitializeSizes(SimStruct*S){uint32_t i,z094c0030e8,ze602c7676c;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x650+766-0x94e));ssSetNumDiscStates(S,(0x1408+1772-0x1af4));ze602c7676c=mxGetN(za9d8fb6bcf);if((int)mxGetPr(z29a89d39e1)[(0x907+6614-0x22dd)]){ze602c7676c++;}if((int)mxGetPr(za2b6976fb4)[(0x277+408-0x40f)]){ze602c7676c++;}if((int)mxGetPr(zfad63a3095)[(0x1c86+644-0x1f0a)]){ze602c7676c++;}ssSetNumInputPorts(S,ze602c7676c);for(i=(0xfbb+4215-0x2032);i<ze602c7676c;i++){if(i<mxGetN(za9d8fb6bcf)){ssSetInputPortWidth(S,i,(0xd0f+186-0xdc8));}else{ssSetInputPortWidth(S,i,mxGetN(za9d8fb6bcf));}ssSetInputPortDataType(S,i,SS_DOUBLE);ssSetInputPortDirectFeedThrough(S,i,(0x1f5+3791-0x10c3));ssSetInputPortRequiredContiguous(S,i,(0x6f3+7676-0x24ee));}z094c0030e8=(0x1f5b+1206-0x2411);if((uint32_t)mxGetPr(za80bdf5015)[(0x651+4692-0x18a5)]){z094c0030e8++;}if((uint32_t)mxGetPr(z1e1f908411)[(0x1d8+6911-0x1cd7)]){z094c0030e8++;}if((uint32_t)mxGetPr(z8d12cdfdee)[(0x6c+375-0x1e3)]){z094c0030e8++;}if((uint32_t)mxGetPr(z8f32a49296)[(0x2359+261-0x245e)]){z094c0030e8++;}ssSetNumOutputPorts(S,z094c0030e8);for(i=(0x15c0+4279-0x2677);i<z094c0030e8;i++){if((uint32_t)mxGetPr(z8f32a49296)[(0x1fc+2809-0xcf5)]&&i==z094c0030e8-(0x2a4+1059-0x6c6)){ssSetOutputPortWidth(S,i,(0xd97+2877-0x18d0));ssSetOutputPortDataType(S,i,SS_DOUBLE);}else{ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,i,SS_DOUBLE);}}ssSetNumSampleTimes(S,(0xb71+2667-0x15db));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x980+6402-0x2282));ssSetNumNonsampledZCs(S,(0x3c4+239-0x4b3));for(i=(0x5fb+1998-0xdc9);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x129c+673-0x153d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static 
void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xd1b+6331-0x25d6)]==-1.0){ssSetSampleTime(S,(0xbbf+1785-0x12b8),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x10f4+4660-0x2328),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xb73+1045-0xf88),mxGetPr(z3832b85a32)[(0xc7c+2871-0x17b3)]);ssSetOffsetTime(S,(0x2c0+5570-0x1882),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zc3b39a639a;uint16_t pci_bus=(0xab5+6010-0x222f),pci_slot=(0x1646+3704-0x24be);volatile uint16_t*za42cf7dd4a;uint16_t z0879a25298;uint32_t i,zcd308d01c9,ch,val,z615725805d;int slot=(int)mxGetPr(z86992bd6b1)[(0x9d0+5977-0x2129)];const uint32_t ze3584cafff=(uint32_t)mxGetN(za9d8fb6bcf);uint32_t moduleId=(uint32_t)mxGetPr(ze13f49a01f)[(0xf3f+3237-0x1be4)];sg_mod_info*mod_info;mod_info=sg_module_get_single(zda9c9e4441,moduleId);if(mod_info==NULL){mod_info=sg_module_register(zda9c9e4441,moduleId);if((int)mxGetPr(z702a26a5e9)[(0x1a9b+1564-0x20b7)]<(0x1ecd+331-0x2018)){if(sg_findPciDevice(&zc3b39a639a,zd6a3cd0da0,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{if(mxGetN(z702a26a5e9)==(0x1862+388-0x19e5)){pci_bus=(0x24da+447-0x2699);pci_slot=(uint16_t)mxGetPr(z702a26a5e9)[(0xbd2+1274-0x10cc)];}else{pci_bus=(uint16_t)mxGetPr(z702a26a5e9)[(0x57f+2071-0xd96)];pci_slot=(uint16_t)mxGetPr(z702a26a5e9)[(0x87b+4620-0x1a86)];}if(sg_findPciDevice(&zc3b39a639a,zd6a3cd0da0,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,pci_bus,pci_slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}za42cf7dd4a=(volatile uint16_t*)sg_mapMemory(&zc3b39a639a,(0x672+7458-0x2394));mod_info->custom_data=(void*)za42cf7dd4a;}else{SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x25\x73\x20\x6d\x6f\x64\x75\x6c\x65" "\n",zd6a3cd0da0);za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(zda9c9e4441,moduleId);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x33\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n");return;}}if(slot<(0x1e0+1918-0x95d)||slot>z5674e18e88){sprintf(msg,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x73\x75\x62\x73\x6c\x6f\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}if(ze3584cafff<(0x816+4611-0x1a18)||ze3584cafff>z5674e18e88){sprintf(msg,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}for(i=(0x1bc+7571-0x1f4f);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];if(ch<(0x3d6+1309-0x8f2)||ch>z5674e18e88){sprintf(msg,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x20\x6f\x75\x74\x20\x6f\x66\x20\x72\x61\x6e\x67\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}}i=(0x10fc+1549-0x1709);while((z626f7f443b()!=43605)&&(i<(0x6d0+2983-0x1245))){i++;sg_wait_s(0.001);}if(i>=(0x12a5+4980-0x25e7)){sprintf(msg,"\n" "\x25\x73\x20\x28\x62\x75\x73\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x20\x25\x64\x29\x3a\x20\x43\x61\x6e\x27\x74\x20\x61\x63\x63\x65\x73\x73\x20\x74\x6f\x20\x6d\x6f\x64\x75\x6c\x65\x2e",zd6a3cd0da0,pci_bus,pci_slot);ssSetErrorStatus(S,msg);return;}zb745c1fe63(slot)=(0x1d31+2121-0x257a);z0879a25298=zfaa050b79d(slot);if((z0879a25298<z20f97d736d)||(z0879a25298>z24077972a0)){sprintf(msg,"\x25\x73\x20\x5b\x25\x64\x2f\x25\x64\x5d\x3a\x20\x57\x72\x6f\x6e\x67\x20\x70\x6c\x75\x67\x2d\x69\x6e\x20\x27\x25\x63\x25\x63\x27\x20\x69\x6e\x20\x73\x6c\x6f\x74\x20\x25\x69\x2e",zd6a3cd0da0,pci_bus,pci_slot,(char)(z0879a25298>>(0x2420+98-0x247a)),(char)z0879a25298,slot);ssSetErrorStatus(S,msg);return;}zbcdb5af90b(slot)=(0x1861+1878-0x1fb7);zcd308d01c9=(0x1844+2185-0x20cd);for(i=(0x2626+146-0x26b8);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];zcd308d01c9|=((0xc5b+6152-0x2462)<<(ch-(0x204f+1496-0x2626)));}zb05ee0e2ad(slot)=zcd308d01c9;SG_PRINTF(DEBUG,"\x61\x63\x74\x69\x76\x65\x43\x68\x61\x6e\x6e\x65\x6c\x73\x3a\x20\x25\x64\x20\x28\x25\x64\x29" "\n",
zb05ee0e2ad(slot),zcd308d01c9);for(i=(0x4bb+4977-0x182c);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];z5c6ee6084b(slot,ch)=(0x1856+2808-0x234e);z403d45b116;z405cc92672(slot,ch)=(0x6c6+6467-0x2009);z403d45b116;}z0879a25298=(0xc59+5832-0x2321);for(i=(0x8e3+5121-0x1ce4);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];z615725805d=(mxGetN(z8759454a33)>(0x388+5376-0x1887))?(uint32_t)mxGetPr(z8759454a33)[i]:(uint32_t)mxGetPr(z8759454a33)[(0x3ab+2518-0xd81)];z615725805d=(z615725805d==(0x7f+3902-0xfbd))?(0x3f6+8603-0x258f):(0x2059+1018-0x2452);z0879a25298|=(z615725805d<<((0x4cc+4516-0x166e)*(ch-(0xd55+4355-0x1e57))));}zcb2e5e84bc(slot)=z0879a25298;z0879a25298=(0x608+7146-0x21f2);for(i=(0x9e8+2207-0x1287);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];if(mxGetPr(za6700577df)[i]==(0xcca+1182-0x1167)){z0879a25298|=((0x21+2831-0xb2f)<<(ch-(0x52d+2458-0xec6)));}}z40963198cc(slot)=z0879a25298;for(i=(0xae0+6154-0x22ea);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];val=(uint32_t)(mxGetPr(zf8013dab26)[i]*(0x1926+915-0x1c55));zac4e78fba4(slot,ch)=val&65535;z403d45b116;z9e5260b14a(slot,ch)=(val>>(0x213+6399-0x1b02))&65535;val=(uint32_t)(mxGetPr(zf8013dab26)[i]*(0x1113+5556-0x2663)*0.9);ze247702196(slot,ch)=val;}for(i=(0x17a6+1818-0x1ec0);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];val=(uint32_t)(mxGetPr(zb377f6022b)[i]*(0x546+2201-0xd7b));z52c4b0bc02(slot,ch)=val&65535;z403d45b116;z7c7cd37cc9(slot,ch)=(val>>(0xe81+4491-0x1ffc))&65535;val=(uint32_t)(mxGetPr(zb377f6022b)[i]*(0xe80+1396-0x1390)*0.9);z3424914fe5(slot,ch)=val;}for(i=(0xddb+6252-0x2647);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];if(mxGetPr(z38c9710147)[i]<(0x13a+5991-0x18a1)){z0879a25298=(uint16_t)(mxGetPr(z38c9710147)[i]*(0x270+8797-0x24c3))-(0xe7b+3584-0x1c7a);}else{z0879a25298=(uint16_t)(mxGetPr(z38c9710147)[i]*(0x191d+3277-0x25e0));}z2530e27808(slot,ch)=z0879a25298;z403d45b116;SG_PRINTF(DEBUG,"\x50\x68\x61\x73\x65\x20\x6f\x66\x66\x73\x65\x74\x20\x72\x65\x67\x20\x3d\x20\x25\x58" "\n",z2530e27808(slot,ch));}z0879a25298=(0x1b+3351-0xd32);for(i=(0x1d6d+2178-0x25ef);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];z0879a25298|=((0x36a+2117-0xbae)<<(ch+(0x3a1+1209-0x857)));}zbcdb5af90b(slot)=z0879a25298;SG_PRINTF(DEBUG,"\x70\x6f\x77\x65\x72\x45\x6e\x61\x62\x6c\x65\x3a\x20\x25\x30\x34\x78\x20\x28\x25\x64\x29" "\n",z0879a25298,z0879a25298);z067bea3bcc(slot,ch)=(0xb4d+3667-0x19a0);z5c6ee6084b(slot,ch)=(0x553+8004-0x2497);z403d45b116;z405cc92672(slot,ch)=(0x1418+1798-0x1b1e);SG_PRINTF(INFO,"\x25\x73\x20\x53\x6c\x6f\x74\x20\x25\x69\x3a\x20\x25\x73\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x65\x64\x2e" "\n",zd6a3cd0da0,slot,zbb2ebcc7de);
#ifdef zf9506af2d6
{FILE*ze0541857aa=fopen(z6265bf51f4(slot),"\x77\x2b");int ze4f87e9bf4=(0x1084+782-0x1392),zf0aadfa29e,ze93aba4ce7,zd0072007fc=(0x1f84+1192-0x242c),z26dbd73a5e,z6a2cfde11b;sg_wait_s((0x17b7+1430-0x1d4c));SG_PRINTF(DEBUG,"\x43\x72\x65\x61\x74\x69\x6e\x67\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x64\x75\x6d\x70\x20\x66\x69\x6c\x65\x2e\x2e\x2e\x20");zd0072007fc=(slot-(0x122a+532-0x143d))*(0x100c+1370-0xd66);fprintf(ze0541857aa,"\x41\x64\x64\x72\x2c\x56\x61\x6c\x48\x65\x78\x2c\x56\x61\x6c\x44\x65\x63\x2c\x52\x65\x67\x4e\x61\x6d\x65\x2c\x43\x48\x20" "\n");while(ze4f87e9bf4<(0x13cb+3542-0x19a1)){zf0aadfa29e=zd15c590fb6(ze4f87e9bf4);if(zf0aadfa29e<(0x4ec+4062-0x14ca)){ze4f87e9bf4+=(0xdad+101-0xe0e);}else{z6a2cfde11b=z18572e0c5a(zf0aadfa29e);if(z6a2cfde11b==(0xd0d+2511-0x16dc)){ze93aba4ce7=(zd0072007fc+ze4f87e9bf4)/(0x1275+3133-0x1eb0);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x30\x78\x25\x30\x34\x78\x2c\x25\x35\x69\x2c\x25\x73\x2c" "\n",ze93aba4ce7*(0xb1d+3679-0x197a),za42cf7dd4a[ze93aba4ce7],za42cf7dd4a[ze93aba4ce7],z387e3a68e7(zf0aadfa29e));ze4f87e9bf4+=(0x6fa+8096-0x2696);}else{for(ch=(0x428+8178-0x241a);ch<z5674e18e88;ch++){for(z26dbd73a5e=(0xa33+6451-0x2366);z26dbd73a5e<z6a2cfde11b;z26dbd73a5e++){ze93aba4ce7=(zd0072007fc+ze4f87e9bf4)/(0x3e6+54-0x41a);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x30\x78\x25\x30\x34\x78\x2c\x25\x35\x69\x2c\x25\x73\x2c\x25\x69" "\n",ze93aba4ce7*(0x87c+3041-0x145b),za42cf7dd4a[ze93aba4ce7],za42cf7dd4a[ze93aba4ce7],z387e3a68e7(zf0aadfa29e+z26dbd73a5e),ch+(0xcf+941-0x47b));ze4f87e9bf4+=(0x16a7+262-0x17a9);}}}}}fprintf(ze0541857aa,"\x49\x4f\x34\x32\x31\x20\x4d\x6f\x74\x68\x65\x72\x62\x6f\x61\x72\x64\x20\x49\x6e\x66\x6f\x2c\x2c\x2c\x2c" "\n");fprintf(ze0541857aa,"\x50\x61\x72\x74\x20\x4e\x75\x6d\x62\x65\x72\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z359c1d60c8(),z359c1d60c8());fprintf(ze0541857aa,"\x53\x65\x72\x69\x61\x6c\x20\x4e\x75\x6d\x62\x65\x72\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z9976d74502(),z9976d74502());fprintf(ze0541857aa,"\x44\x61\x74\x65\x20\x43\x6f\x64\x65\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z828a61b0f6(),z828a61b0f6());fprintf(ze0541857aa,"\x50\x43\x42\x20\x52\x65\x76\x20\x4c\x65\x76\x65\x6c\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z8482c363f2(),z8482c363f2());fprintf(ze0541857aa,"\x50\x72\x6f\x63\x65\x73\x73\x6f\x72\x20\x52\x65\x76\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z32992c1e7b(),z32992c1e7b());fprintf(ze0541857aa,"\x50\x43\x49\x20\x46\x50\x47\x41\x20\x52\x65\x76\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",zaa6d1f788a(),zaa6d1f788a());fprintf(ze0541857aa,"\x44\x65\x73\x69\x67\x6e\x20\x56\x65\x72\x73\x69\x6f\x6e\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z7a4d487411(),z7a4d487411());fprintf(ze0541857aa,"\x50\x6c\x61\x74\x66\x6f\x72\x6d\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",PLATFORM(),PLATFORM());fprintf(ze0541857aa,"\x4d\x6f\x64\x65\x6c\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",zf9143fcdba(),zf9143fcdba());fprintf(ze0541857aa,"\x47\x65\x6e\x65\x72\x61\x74\x69\x6f\x6e\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z5955864021(),z5955864021());fprintf(ze0541857aa,"\x53\x70\x65\x63\x69\x61\x6c\x20\x53\x70\x65\x63\x3a\x2c\x2c\x30\x78\x25\x30\x34\x78\x2c\x28\x25\x69\x29\x2c" "\n",z3c7df23547(),z3c7df23547());fprintf(ze0541857aa,"\n\n" "\x41\x6c\x6c\x20\x72\x65\x67\x69\x73\x74\x65\x72\x73\x20\x28\x72\x65\x67\x61\x72\x64\x6c\x65\x73\x73\x20\x69\x66\x20\x64\x6f\x63\x75\x6d\x65\x6e\x74\x65\x64\x20\x6f\x72\x20\x6e\x6f\x74\x29\x2c\x2c\x2c\x2c" "\n");fprintf(ze0541857aa,"\x41\x64\x64\x72\x2c\x56\x61\x6c\x28\x48\x45\x58\x29\x2c\x56\x61\x6c\x28\x64\x65\x63\x29\x2c\x2c" "\n");ze4f87e9bf4=(0x1d64+662-0x1ffa);while(ze4f87e9bf4<(0xd96+2667-0x1001)){ze93aba4ce7=(zd0072007fc+ze4f87e9bf4)/(0xc5+7467-0x1dee);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x30\x78\x25\x30\x34\x78\x2c\x25\x35\x69\x2c\x2c" "\n",ze93aba4ce7*(0x129f+274-0x13af),
za42cf7dd4a[ze93aba4ce7],za42cf7dd4a[ze93aba4ce7]);ze4f87e9bf4+=(0x102+7349-0x1db3);}fclose(ze0541857aa);SG_PRINTF(DEBUG,"\x64\x6f\x6e\x65\x2e" "\n");}
#endif
#ifdef z536fbb5294
{FILE*ze0541857aa=fopen(z88ca2e8e70(slot),"\x77\x2b");for(i=(0x1059+2-0x105b);i<ze3584cafff;i++){fprintf(ze0541857aa,"\x43\x48\x2c\x57\x72\x69\x74\x65\x50\x6f\x73\x2c\x64\x65\x63\x50\x2c");fprintf(ze0541857aa,"\x57\x72\x61\x70\x50\x6f\x73\x2c\x64\x65\x63\x57\x50\x2c");fprintf(ze0541857aa,"\x57\x52\x41\x50\x5f\x45\x58\x43\x5f\x56\x2c\x64\x65\x63\x45\x56\x2c");fprintf(ze0541857aa,"\x43\x48\x5f\x46\x52\x45\x51\x55\x45\x4e\x43\x59\x2c\x64\x65\x63\x45\x46\x2c");}fprintf(ze0541857aa,"\x53\x69\x67\x4c\x6f\x73\x74\x2c\x45\x78\x63\x2c\x42\x49\x54\x2c\x50\x68\x4c\x63\x6b\x2c");fprintf(ze0541857aa,"\n");fclose(ze0541857aa);}
#endif
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint16_t*za42cf7dd4a;int slot=(int)mxGetPr(z86992bd6b1)[(0x18b5+3211-0x2540)];za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(zda9c9e4441,(uint32_t)mxGetPr(ze13f49a01f)[(0x1296+5141-0x26ab)]);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x33\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n");return;}zb745c1fe63(slot)=(0xf7b+3183-0x1be6);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint16_t*za42cf7dd4a;uint16_t slot;int32_t zaa494cfbb4[z5674e18e88];uint32_t z095c8f6c33;uint16_t z56ba3f487b,zc0b69ca6fa;uint32_t i,ch,z094c0030e8,ze3584cafff,ze602c7676c;uint32_t val,z02aa46c143,za42d574ba5;double*in,*out;double position,ze4506f6b8c[z5674e18e88];z85a1c7964f status;uint16_t z0879a25298;
#ifdef z536fbb5294
FILE*ze0541857aa;
#endif
za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(zda9c9e4441,(uint32_t)mxGetPr(ze13f49a01f)[(0xe2f+1431-0x13c6)]);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x33\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}slot=(uint32_t)mxGetPr(z86992bd6b1)[(0x9d9+3935-0x1938)];ze3584cafff=(uint32_t)mxGetN(za9d8fb6bcf);
#ifdef z536fbb5294
ze0541857aa=fopen(z88ca2e8e70(slot),"\x61");if(ze0541857aa<(0x8c6+7339-0x2571)){SG_PRINTF(INFO,"\x45\x52\x52\x4f\x52\x3a\x20\x63\x61\x6e\x27\x74\x20\x6f\x70\x65\x6e\x20\x66\x69\x6c\x65" "\n");return;}
#endif
#ifdef z536fbb5294
if((uint32_t)mxGetPr(z8f32a49296)[(0x25f+7011-0x1dc2)])
#endif
{status.z9f0f81f54c=z734b0c83c9(slot);status.z4dcd279748=z2e184ac1a4(slot);status.z5e8ece4cca=z6ffda891be(slot);status.z8b90547431=z291e24836a(slot);}for(i=(0x843+101-0x8a8);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];in=(double*)ssGetInputPortSignal(S,i);position=in[(0x23d3+321-0x2514)];
#if (0x377+9106-0x2709) 
if(position>=1.0-z7b38f83bd1){z095c8f6c33=2147483647;}else{if(position<-1.0){z095c8f6c33=2147483648;}else{z095c8f6c33=(int32_t)(position/z7b38f83bd1);}}
#else 
if(position>0.995){position=0.995;}else{if(position<-0.995){position=-0.995;}}z095c8f6c33=(int32_t)(position/z7b38f83bd1);
#endif
SG_PRINTF(DEBUG,"\x70\x25\x69\x3d\x25\x35\x69\x20",ch,z095c8f6c33);z56ba3f487b=(uint16_t)(z095c8f6c33&65535);zc0b69ca6fa=(uint16_t)((z095c8f6c33>>(0x1190+5515-0x270b))&65535);z405cc92672(slot,ch)=zc0b69ca6fa;z5c6ee6084b(slot,ch)=z56ba3f487b;zaa494cfbb4[ch-(0x302+1481-0x8ca)]=(uint16_t)zc70a18cdaf(slot,ch);zaa494cfbb4[ch-(0xbe6+2435-0x1568)]=zaa494cfbb4[ch-(0x142b+3306-0x2114)]<<(0xc18+5088-0x1fe8);zaa494cfbb4[ch-(0x1a8+3363-0xeca)]|=(uint16_t)zfc4acf0407(slot,ch);ze4506f6b8c[ch-(0x5f0+5778-0x1c81)]=(double)zaa494cfbb4[ch-(0xd88+631-0xffe)]*z7b38f83bd1;
#ifdef z536fbb5294
fprintf(ze0541857aa,"\x25\x69\x2c\x30\x78\x25\x30\x38\x78\x2c\x25\x31\x2e\x36\x66\x2c",ch,z095c8f6c33,in[(0xb+5235-0x147e)]);fprintf(ze0541857aa,"\x30\x78\x25\x30\x38\x78\x2c\x25\x31\x2e\x36\x66\x2c",zaa494cfbb4[ch-(0x86b+1491-0xe3d)],ze4506f6b8c[ch-(0x92f+7213-0x255b)]);z0879a25298=z067bea3bcc(slot,ch);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x25\x32\x2e\x32\x66\x2c",z0879a25298,((double)z0879a25298)/(0xf99+4300-0x2001));z0879a25298=z1bacb6e848(slot,ch);fprintf(ze0541857aa,"\x30\x78\x25\x30\x34\x78\x2c\x25\x35\x2e\x32\x66\x2c",z0879a25298,((double)z0879a25298));
#endif
}ze602c7676c=ze3584cafff;if((int)mxGetPr(z29a89d39e1)[(0x367+2340-0xc8b)]){in=(double*)ssGetInputPortSignal(S,ze602c7676c);for(i=(0x1879+255-0x1978);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];val=(uint32_t)(in[i]*(0x1b0c+2159-0x2317));z02aa46c143=val&65535;za42d574ba5=(val>>(0x25f+1346-0x791))&65535;z7c7cd37cc9(slot,ch)=za42d574ba5;z52c4b0bc02(slot,ch)=z02aa46c143;val=(uint32_t)(in[i]*(0x1ecf+1193-0x2314)*0.9);z3424914fe5(slot,ch)=val;}ze602c7676c++;}if((int)mxGetPr(za2b6976fb4)[(0x20d+8502-0x2343)]){in=(double*)ssGetInputPortSignal(S,ze602c7676c);for(i=(0x6cc+2802-0x11be);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];val=(uint32_t)(in[i]*(0x430+4553-0x1595));z02aa46c143=val&65535;za42d574ba5=(val>>(0x952+1190-0xde8))&65535;z9e5260b14a(slot,ch)=za42d574ba5;zac4e78fba4(slot,ch)=z02aa46c143;val=(uint32_t)(in[i]*(0x9ff+974-0xd69)*0.9);ze247702196(slot,ch)=val;}ze602c7676c++;}if((int)mxGetPr(zfad63a3095)[(0xeac+3707-0x1d27)]){in=(double*)ssGetInputPortSignal(S,ze602c7676c);for(i=(0xd6b+1884-0x14c7);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];if(in[i]<(0x1abc+1620-0x2110)){z0879a25298=(uint16_t)(in[i]*(0x53b+4319-0x1610))-(0xc7a+6686-0x2697);}else{z0879a25298=(uint16_t)(in[i]*(0x1444+4751-0x26c9));}z2530e27808(slot,ch)=z0879a25298;z403d45b116;}ze602c7676c++;}
#ifdef z536fbb5294
fprintf(ze0541857aa,"\x25\x69\x2c\x25\x69\x2c\x25\x69\x2c\x25\x69\x2c",status.z9f0f81f54c,status.z4dcd279748,status.z5e8ece4cca,status.z8b90547431);
#endif
SG_PRINTF(DEBUG,"\n");z094c0030e8=(0x103b+3130-0x1c75);if((uint32_t)mxGetPr(za80bdf5015)[(0x13bd+4517-0x2562)]){out=(double*)ssGetOutputPortSignal(S,z094c0030e8);for(i=(0xe9c+951-0x1253);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];out[i]=ze4506f6b8c[ch-(0x1923+1967-0x20d1)];}z094c0030e8++;}if((uint32_t)mxGetPr(z1e1f908411)[(0x180+8298-0x21ea)]){out=(double*)ssGetOutputPortSignal(S,z094c0030e8);for(i=(0x29a+5500-0x1816);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];out[i]=z1bacb6e848(slot,ch);}z094c0030e8++;}if((uint32_t)mxGetPr(z8d12cdfdee)[(0xae1+6316-0x238d)]){out=(double*)ssGetOutputPortSignal(S,z094c0030e8);for(i=(0x697+8034-0x25f9);i<ze3584cafff;i++){ch=(uint32_t)mxGetPr(za9d8fb6bcf)[i];out[i]=z067bea3bcc(slot,ch)/100.0;}z094c0030e8++;}if((uint32_t)mxGetPr(z8f32a49296)[(0xf6+9278-0x2534)]){out=(double*)ssGetOutputPortSignal(S,z094c0030e8);out[(0x12d9+4081-0x22ca)]=status.z9f0f81f54c;out[(0x675+6624-0x2054)]=status.z4dcd279748;out[(0x12b6+4086-0x22aa)]=status.z5e8ece4cca;out[(0x3ef+463-0x5bb)]=status.z8b90547431;z094c0030e8++;}
#ifdef z536fbb5294
fprintf(ze0541857aa,"\n");fclose(ze0541857aa);
#endif
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint16_t*za42cf7dd4a;uint16_t slot;slot=(uint32_t)mxGetPr(z86992bd6b1)[(0x8fb+4395-0x1a26)];za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(zda9c9e4441,(uint32_t)mxGetPr(ze13f49a01f)[(0xe53+3510-0x1c09)]);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x33\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n");return;}zb745c1fe63(slot)=(0x1c9c+2253-0x2569);
#endif
}static void sg_ModelExit(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t moduleId=(uint32_t)mxGetPr(ze13f49a01f)[(0x6b+2697-0xaf4)];sg_module_unregister(zda9c9e4441,moduleId);SG_PRINTF(DEBUG,"\x49\x4f\x34\x32\x31\x2d\x33\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n");
#endif
}
#include "sg_sfcn_glue.h"   

