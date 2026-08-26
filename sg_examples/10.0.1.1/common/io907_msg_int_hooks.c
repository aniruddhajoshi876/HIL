// Copyright 2006-2026 Speedgoat GmbH

#define z96fdfde5a1 
#include "sg_blocks/sharedmemory/include/sg_IO907.h"
#include "sg_blocks/common/libsg/sg_common.h"
static const int SG_INT_BARS[]={(0x975+2881-0x14b6),(0x5eb+4664-0x1821)};
#define SG_INT_PREFIX IO907_MSG
static int z73f20c1e99(sg_PCIDevice*zeccbadd9b3,uint32_t moduleId,int bus,int slot);
#define SG_INT_CUSTOM_FIND_PCI_FUNCTION z73f20c1e99
#include "sg_interrupt_config.h"
static int z73f20c1e99(sg_PCIDevice*zeccbadd9b3,uint32_t moduleId,int bus,int slot){if(sg_findPciDevice(zeccbadd9b3,DEVNAME,z066317d01e,DEVICEID,SUBVENDORID,SUBDEVICEID,moduleId,bus,slot)!=(0xdbc+6054-0x2562)){if(sg_findPciDevice(zeccbadd9b3,DEVNAME,z1058005ab1,DEVICEID,SUBVENDORID,SUBDEVICEID,moduleId,bus,slot)!=(0xfa4+4780-0x2250)){SG_PRINTF(ERROR,"\x25\x73" "\n",pSgErrorStr);return-(0x1122+275-0x1234);}}return(0xa84+706-0xd46);}
#define z62d4e261fe
#include "sg_io907_io908_int.c"
