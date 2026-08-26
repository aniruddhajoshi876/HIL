// Copyright 2006-2026 Speedgoat GmbH

#ifndef z9ebf004802
#define z9ebf004802
#ifdef __cplusplus
extern"C"{
#endif
#ifndef MATLAB_MEX_FILE
#include <sg_common.h>
#endif
#include <stdint.h>
#include <stdlib.h>
#define I2C_ERROR_OK                            (0x157a+726-0x1850)
#define I2C_WRITE_ERROR                         (0x1138+3470-0x1ec5)
#define I2C_SWITCH_ERROR                        (0x21af+242-0x229f)
#define I2C_READ_ERROR                          (0x1447+482-0x1626)
#define I2C_READ_MOD_SET_ERROR                  (0xf61+3289-0x1c36)
#define I2C_READ_MOD_CLEAR_ERROR                (0x10a0+3371-0x1dc6)
#define I2C_INIT_ERROR                          (0x1061+4340-0x214f)
#define I2C_NACK_ERROR                          (0x229d+991-0x2675)
#define I2C_BUSY_ERROR                          (0x13f0+3806-0x22c6)
#define I2C_CLOCKSYNTH_ERROR                    (0x162+2984-0xd00)
#define I2C_UNSUPPORTED_PLUGIN_ERROR            (0x1932+2327-0x223e)
#define I2C_INVALID_PLUGIN_ERROR                (0x35+3799-0xf00)
#define I2C_MISC_ERROR                          (0x414+8307-0x247a)
#define I2C_EEPROM_EMPTY                        (0x8d1+6936-0x23db)
#define z95b7e35eb1            (0x8a3+5116-0x1c90)
#define z336aceb1fd    (0x4ed+41-0x506)
#define ze3ba9178f1       (0x330+92-0x37b)
#define za048d754b2    (0x129d+1790-0x1989)
#define zedb3d6cb6d     (0x3ff+7120-0x1fbc)
#define z7766e4505a  (0x112+2157-0x96b)
#define zf5e4406a2b        (0x171+3709-0xfd9)
int sg_fpga_xilinx_i2c_read(volatile uint8_t*z455eee9a52,uint8_t z8a3d174aca,uint32_t zbd1db1b50c,uint8_t*zbf8309dca9,uint8_t*z3bc76317df,uint8_t z4fc4944394);int sg_fpga_xilinx_i2c_write(volatile uint8_t*z455eee9a52,uint8_t z8a3d174aca,uint32_t zbd1db1b50c,uint8_t*z4e469c7080,uint8_t z3bc76317df,uint8_t z4fc4944394);int z25269bb2cc(volatile uint8_t*z051252bdce,uint8_t z8a3d174aca);int zf0dac267ed(volatile uint8_t*z051252bdce,uint8_t z8a3d174aca);int z231effb428(volatile uint8_t*z051252bdce,uint8_t z8a3d174aca,uint8_t z206bf6e97d,uint16_t z64f2484018,uint8_t z8e453d1b74[(0xcf7+4432-0x1e43)]);int z6722645aad(volatile uint8_t*z051252bdce,uint8_t z8a3d174aca,uint16_t z64f2484018,uint8_t z8e453d1b74[(0xd26+1811-0x1435)]);int z42cee0b003(volatile uint8_t*z051252bdce,uint8_t z8a3d174aca,uint8_t*z668f576053,size_t za89d75a28c);uint32_t sg_fpga_ioexpander_write(volatile uint8_t*z455eee9a52,uint8_t z8a3d174aca,uint8_t regAddr,uint8_t data);uint32_t sg_fpga_ioexpander_read(volatile uint8_t*z455eee9a52,uint8_t z8a3d174aca,uint8_t regAddr,uint8_t*data);uint32_t sg_fpga_ioexpander_modify(volatile uint8_t*z455eee9a52,uint8_t z8a3d174aca,uint8_t regAddr,uint8_t zb7de202b51,uint8_t zab7134293b);typedef volatile struct{uint32_t zaa91623895[(0x12d2+2715-0x1d4d)];uint32_t z392f7ebdb2[(0xfcd+1223-0x1474)];uint32_t zf0a639368c[(0xa5f+4329-0x1b28)];uint32_t za13318b168[(0xefc+3116-0x1b08)];uint32_t z661cc29292[(0x3c3+3969-0x1324)];uint32_t z4873d4bf9a[(0x34+6800-0x1aa4)];uint32_t z8e433fc0c3[(0x513+8129-0x24b4)];uint32_t z56ecbe425d[(0x15dd+1988-0x1d81)];uint32_t z2e87e7e5d4[(0xa1f+4075-0x19ea)];uint32_t za60cf20d07[(0x16f2+2-0x16d4)];uint32_t z0987820d8d[(0xbec+3708-0x1a48)];uint32_t status[(0x17ea+1037-0x1bd7)];uint32_t zf5ed9573ba;uint32_t z96e36096f7;uint32_t z1b77f28618;uint32_t zb8b34ce88c;uint32_t zcc7606196b;uint32_t zd898b4c474;uint32_t z196fe21208;uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t z0b57c4d159;uint32_t z7be6e454ad;uint32_t version;uint32_t dummy[(0x4fd+408-0x421)];}za9364ae680;typedef struct{za9364ae680*z49e84088fc;uint8_t channel;}z1c6f8acc75;void zac1f61435f(volatile uint8_t*z455eee9a52);int z0797415d21(z1c6f8acc75*z429253d188,uint16_t zbd1db1b50c,uint8_t*zbf8309dca9,uint8_t z3bc76317df);int zcdec1a814b(z1c6f8acc75*z429253d188,uint16_t zbd1db1b50c,uint8_t*z4e469c7080,uint8_t z3bc76317df);
#ifdef __cplusplus
}
#endif
#endif      

