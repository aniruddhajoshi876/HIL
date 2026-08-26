// Copyright 2006-2026 Speedgoat GmbH

#include "sg_blocks/common/libsg/IoModuleRegistry.h"
#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/common/libsg/sg_printf.h"
#include "sg_blocks/flexray/include/Io623Module.h"
const int SG_INT_BARS[]={(0x560+7734-0x2396)};
#define SG_INT_PREFIX IO623
#include "sg_interrupt_config.h"
#define z7e0c29398b              (0x97d+1726-0xf27)
#define ze691d453eb      4294901768
#define z827f3836f1  536870912
#define zc8d247f2a8  2097152
#define zd55ff6d54a  1073741824
#define z93a5e8cfc3  33554432
#define za343d3927c  (0x1c9+4708-0x142b)
#define z64a49b4952  (0x1351+4857-0x224a)
#define z6174083c2d  (0x75f+4717-0x19c8)
#define z66d2a24860  (0x1c3+1381-0x6e8)
static uint32_t z138adb96a5(uintptr_t regAddr){return*(uint32_t*)regAddr;}static void za6976b665e(uintptr_t regAddr,uint32_t value){*(uint32_t*)regAddr=value;}SG_INT_START_FUNC{if(!sg_isModelInit()){sg::zd43ee5c691*zae10e3f17f=static_cast<sg::zd43ee5c691*>(sg::IoModuleRegistry::find(SG_INT_GET_PCIINFO));if(zae10e3f17f==nullptr){SG_PRINTF(ERROR,"\x49\x4f\x36\x32\x33\x3a\x20\x43\x61\x6e\x6e\x6f\x74\x20\x66\x69\x6e\x64\x20\x49\x2f\x4f\x20\x6d\x6f\x64\x75\x6c\x65\x20\x74\x6f\x20\x73\x74\x61\x72\x74\x20\x69\x6e\x74\x65\x72\x72\x75\x70\x74" "\n");return;}zae10e3f17f->za111a7b5f6();}}SG_INT_ISR_FUNC{uintptr_t z2079a0087c=SG_INT_MAPPED_BAR((0x1316+1708-0x19c2))+z7e0c29398b;uint32_t zad3c165c4a=z138adb96a5(z2079a0087c);if(zad3c165c4a==4294967295){return SG_DROP_ISR;}if(!(zad3c165c4a&ze691d453eb)){return SG_DROP_ISR;}if(zad3c165c4a&z827f3836f1){za6976b665e(z2079a0087c,zad3c165c4a|za343d3927c);return SG_RUN_ISR;}if(zad3c165c4a&zc8d247f2a8){za6976b665e(z2079a0087c,zad3c165c4a|z64a49b4952);return SG_RUN_ISR;}if(zad3c165c4a&zd55ff6d54a){za6976b665e(z2079a0087c,zad3c165c4a|z6174083c2d);return SG_RUN_ISR;}if(zad3c165c4a&z93a5e8cfc3){za6976b665e(z2079a0087c,zad3c165c4a|z66d2a24860);return SG_RUN_ISR;}return SG_DROP_ISR;}SG_INT_STOP_FUNC{if(!sg_isModelInit()){sg::zd43ee5c691*zae10e3f17f=static_cast<sg::zd43ee5c691*>(sg::IoModuleRegistry::find(SG_INT_GET_PCIINFO));if(zae10e3f17f==nullptr){SG_PRINTF(ERROR,"\x49\x4f\x36\x32\x33\x3a\x20\x43\x61\x6e\x6e\x6f\x74\x20\x66\x69\x6e\x64\x20\x49\x2f\x4f\x20\x6d\x6f\x64\x75\x6c\x65\x20\x74\x6f\x20\x73\x74\x6f\x70\x20\x69\x6e\x74\x65\x72\x72\x75\x70\x74" "\n");return;}zae10e3f17f->z866a22b76f();}}
