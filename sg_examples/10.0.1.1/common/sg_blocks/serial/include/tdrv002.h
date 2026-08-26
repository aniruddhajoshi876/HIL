// Copyright 2006-2026 Speedgoat GmbH

#ifndef z8437310dac
#define z8437310dac
#include <devctl.h>
enum zcac0da99dc{z77772977e7=(0x1bff+2481-0x25b0),zdd6f4e25c3=(0x105+3412-0xe58),zdfb4ac4a4d=(0x20eb+988-0x24c5)};enum z833109362d{za75513a4df=(0x964+4314-0x1a3e),z60fbc12760=(0x80d+6351-0x20db),z26a9b57a05=(0x16a3+2232-0x1f59),z9f5e75bf47=(0x77f+7749-0x25c1)};typedef struct{unsigned char zded683570b;unsigned char z444f9cdc72;}trigger_level_t;typedef struct{enum zcac0da99dc mode;enum z833109362d z21d68b8dc4;enum z833109362d zb1c43c5b50;unsigned char xon1;unsigned char xon2;unsigned char xoff1;unsigned char xoff2;unsigned char z29d40afbed;}handshake_control_t;typedef struct{unsigned char z363ee6683b;unsigned char z0c1475aa07;unsigned char z4bd438c81b;unsigned int z3598f918ae;}baudrate_config_t;typedef struct{short z0a49f10467;short z4ac69f170a;}sw_fifo_size_t;typedef struct{unsigned char zc5afb7aa30[(0x2bc+755-0x59f)];unsigned char z3fad3d9764[(0x236+5281-0x16c7)];unsigned char status;unsigned z6bda92b87c;}drv_info_regs_t;
#define TDRV002_DCMD_SET_TRANSC     __DIOT(_DCMD_CHR, (0x1280+5472-0x26fb), unsigned char)     
#define TDRV002_DCMD_SET_TURNAROUND_DELAY   __DIOT(_DCMD_CHR, (0x1e3c+425-0x1eff), unsigned char)      
#define TDRV002_DCMD_SET_HYSTERESIS         __DIOT(_DCMD_CHR, (0x832+2514-0x111d), unsigned char)      
#define TDRV002_DCMD_SET_TRIGGER_LEVELS     __DIOT(_DCMD_CHR, (0x808+3405-0x146d), trigger_level_t)     
#define TDRV002_DCMD_SET_HANDSHAKE_CONTROL  __DIOT(_DCMD_CHR, (0x1b5f+1401-0x1fef), handshake_control_t) 
#define TDRV002_DCMD_SET_BAUDRATE           __DIOT(_DCMD_CHR, (0x4d3+1578-0xa13), baudrate_config_t)   
#define TDRV002_DCMD_SET_FIFO_BUFFERS       __DIOT(_DCMD_CHR, (0x1429+3308-0x202a), sw_fifo_size_t)      
#define TDRV002_DCMD_SET_LOOPBACK           __DIOT(_DCMD_CHR, (0xeb7+1551-0x13da), unsigned char)       
#define TDRV002_DCMD_GET_INFO_REGISTERS     __DIOF(_DCMD_CHR, (0x7b5+5474-0x1c2a), drv_info_regs_t)     
#define zbce1728e2d   __DIOF(_DCMD_CHR, (0xea0+3908-0x1cf5), unsigned int)        
#define TDRV002_CFG_RS485_RS232     ((0xbba+3644-0x19f5) << (0x3f6+3611-0x1211))        
#define TDRV002_CFG_HDPLX           ((0x6ed+486-0x8d2) << (0xf75+534-0x118a))        
#define TDRV002_CFG_RENA            ((0xa67+6739-0x24b9) << (0xfa9+1741-0x1674))        
#define TDRV002_CFG_RTERM           ((0x558+2406-0xebd) << (0x1154+3049-0x1d3a))        
#define TDRV002_CFG_TTERM           ((0x3f0+6384-0x1cdf) << (0xe42+1956-0x15e2))        
#define TDRV002_CFG_SLEWLIMIT       ((0x993+7465-0x26bb) << (0x5d7+6130-0x1dc4))        
#define TDRV002_CFG_SHDN            ((0x1cbb+1303-0x21d1) << (0x4c2+8158-0x249a))        
#define TDRV002_CFG_AUTO_RS485      ((0x19cb+2881-0x250b) << (0x1f87+1682-0x2612))        
#define TDRV002_INTF_OFF          (TDRV002_CFG_SHDN)            
#define TDRV002_INTF_RS232        ((0x6c7+4139-0x16f2))                           
#define TDRV002_INTF_RS422        (TDRV002_CFG_RS485_RS232 |    \
                                   TDRV002_CFG_RTERM)           
#define TDRV002_INTF_RS485FDM     (TDRV002_CFG_RS485_RS232 |    \
                                   TDRV002_CFG_RTERM       |    \
                                   TDRV002_CFG_TTERM)           
#define TDRV002_INTF_RS485FDS     (TDRV002_CFG_RS485_RS232 |    \
                                   TDRV002_CFG_RTERM       |    \
                                   TDRV002_CFG_TTERM       |    \
                                   TDRV002_CFG_AUTO_RS485)      
#define TDRV002_INTF_RS485HD      (TDRV002_CFG_RS485_RS232 |    \
                                   TDRV002_CFG_HDPLX       |    \
                                   TDRV002_CFG_RENA        |    \
                                   TDRV002_CFG_TTERM       |    \
                                   TDRV002_CFG_AUTO_RS485)      
#endif  

