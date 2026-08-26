// Copyright 2006-2026 Speedgoat GmbH

#ifndef z56a98ff248
#define z56a98ff248
#ifdef __cplusplus
extern"C"{
#endif
#include <linux/ioctl.h>
#define z1607ca63fc	(0x149b+272-0x14f8)
#define	zab9edc5120		((0x70f+1464-0xcc6)<<(0xf44+1027-0x1347))	
#define zdd01c2d3e8		((0x669+4741-0x18ed)<<(0x644+1159-0xaca))	
#define zfcd8222a4e			((0x1bc+4364-0x12c7)<<(0xa0b+2407-0x1370))	
#define zf2ec3ba480			((0x179d+39-0x17c3)<<(0xbfb+2808-0x16f0))	
#define zb1f53ea2c9		((0x1ec7+1016-0x22be)<<(0x1581+4132-0x25a1))	
typedef struct{int zc3beeea551;int ze85db7c5eb;int z76759288f1;int z235d9fbec8;int deviceId;int z886ea186cc;char z8031c16749[(0x479+5969-0x1bb6)];int zf353514e83;unsigned char z5302196e36;}TDRV002_GET_INFO_STRUCT;typedef struct{unsigned int z156e88c023;unsigned int za51aa3b36a;}TDRV002_SET_FIFO_STRUCT;enum zcac0da99dc{z77772977e7=(0x56c+6187-0x1d97),zdd6f4e25c3=(0x5ed+7744-0x242c),zdfb4ac4a4d=(0x1a99+3043-0x267a)};enum z833109362d{za75513a4df=(0x15e8+4030-0x25a6),z60fbc12760=(0x54c+2212-0xdef),z26a9b57a05=(0x296+8899-0x2557),z9f5e75bf47=(0xcbd+2072-0x14d2)};typedef struct{enum zcac0da99dc mode;enum z833109362d z21d68b8dc4;enum z833109362d zb1c43c5b50;unsigned char xon1;unsigned char xon2;unsigned char xoff1;unsigned char xoff2;unsigned char z29d40afbed;}TDRV002_SET_HANDSHAKE_STRUCT;typedef struct{unsigned char z363ee6683b;unsigned char z0c1475aa07;unsigned char z4bd438c81b;unsigned int z3598f918ae;unsigned int zc24b7ef2c3;}TDRV002_SET_BAUDRATE_STRUCT;typedef struct{unsigned char zc5afb7aa30[(0xa03+1956-0x1197)];unsigned char z3fad3d9764[(0xc95+3857-0x1b96)];unsigned char status;unsigned z6bda92b87c;}TDRV002_DRV_REG_STRUCT;
#define TDRV002_IOCQ_BIST		            _IO(z1607ca63fc, (0x909+6348-0x21d4))	
#define TDRV002_IOCT_CONF_TRANS	            _IOW(z1607ca63fc, (0x1bb6+2578-0x25c6), int)	
#define TDRV002_IOCQ_GET_SPEED	            _IOR(z1607ca63fc, (0xaf4+6159-0x2300), int)	
#define TDRV002_IOCQ_GET_INFO	            _IOR(z1607ca63fc, (0x99d+5725-0x1ff6), TDRV002_GET_INFO_STRUCT)	
#define TDRV002_IOCT_SET_FIFOTRIG           _IOW(z1607ca63fc, (0x207+7044-0x1d86), TDRV002_SET_FIFO_STRUCT)	
#define TDRV002_IOCT_SET_BAUDRATE           _IOW(z1607ca63fc, (0x1141+2267-0x1a16), TDRV002_SET_BAUDRATE_STRUCT)	
#define TDRV002_IOCT_SET_TR_DELAY	        _IOW(z1607ca63fc, (0xcb3+1833-0x13d5), int)	
#define TDRV002_IOCT_SET_HANDSHAKE          _IOW(z1607ca63fc, (0x452+3024-0x101a), TDRV002_SET_HANDSHAKE_STRUCT) 
#define TDRV002_IOCT_GET_DRV_REG            _IOR(z1607ca63fc, (0xa85+3844-0x1980), TDRV002_DRV_REG_STRUCT) 
#define TDRV002_IOCT_GET_OSCILLATOR_CLOCK   _IOR(z1607ca63fc, (0xc1d+707-0xed6), int) 
#define TDRV002_CFG_RS485_RS232     ((0x396+5320-0x185d) << (0x15f8+680-0x18a0))        
#define TDRV002_CFG_HDPLX           ((0xdaa+5473-0x230a) << (0x83d+1845-0xf71))        
#define TDRV002_CFG_RENA            ((0xa4c+3933-0x19a8) << (0x5b6+2637-0x1001))        
#define TDRV002_CFG_RTERM           ((0xa56+5216-0x1eb5) << (0x439+3452-0x11b2))        
#define TDRV002_CFG_TTERM           ((0x9ec+6791-0x2472) << (0x41d+7448-0x2131))        
#define TDRV002_CFG_SLEWLIMIT       ((0x75c+7222-0x2391) << (0x28f+7156-0x1e7e))        
#define TDRV002_CFG_SHDN            ((0x21bb+875-0x2525) << (0x7c7+1241-0xc9a))        
#define TDRV002_CFG_AUTO_RS485      ((0x51c+7073-0x20bc) << (0xecf+1772-0x15b4))        
#define TDRV002_INTF_OFF          (TDRV002_CFG_SHDN)            
#define TDRV002_INTF_RS232        ((0x31a+1504-0x8fa))                           
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
#ifdef __cplusplus
}
#endif
#endif 

