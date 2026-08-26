#ifndef __SG_FPGA_SETUP_UTIL_H__
#define __SG_FPGA_SETUP_UTIL_H__
// #include <stdio.h>
#include <stdint.h>
#include "sg_hdlc_api.h"

// #include "simstruc.h"

#ifndef MATLAB_MEX_FILE
#include "sg_fpga_io3xx_util.h"
#endif

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************
 * IO3xx_2x - State Machine (no ipcore)
 *****************************************************************************/
// structures
typedef struct
{
  volatile uint32_t enable; // enable io3xx_21
  volatile uint32_t update; // update port configuration
  volatile uint32_t dir; // DIO direction
  volatile uint32_t vio; // DIO voltage
  volatile uint32_t pull; // pull-resistor
  volatile uint32_t i2c_enable; // enable 3x customer I2C lines
  volatile uint32_t rxDataExpander1; // readback data from i2c port configuration
  volatile uint32_t rxDataExpander2; // readback data from i2c port configuration
  volatile uint32_t rxDataExpander3; // readback data from i2c port configuration
  volatile uint32_t rxDataExpander4; // readback data from i2c port configuration
  volatile uint32_t test1; // test 1 of io3xx_21_wrapper
  volatile uint32_t test2; // test 2 of io3xx_21_wrapper
  volatile uint32_t spare_registers[4];
  volatile uint32_t reg_clear;
  volatile uint32_t reg_write_enb;
  volatile uint32_t reg_address;
  volatile uint32_t reg_data_wr;
  volatile uint32_t slave_id;
  volatile uint32_t start_transfer;
  volatile uint32_t frame_size;
  volatile uint32_t ntx_rx;
  volatile uint32_t reg_data_rd;
  volatile uint32_t eot;
  volatile uint32_t global_enable;
  volatile uint32_t control_register;
}io3xx_2x;

#define IO3xx_PULL_BASE         (0x4000) // FPGA Core base address
typedef struct
{
  volatile uint32_t enable; // enable pull resistor (if disabled = floating)
  volatile uint32_t pull; // pull-resistor
  volatile uint32_t test1; // test 1 of io31x_pull_wrapper
  volatile uint32_t test2; // test 2 of io31x_pull_wrapper
  volatile uint32_t term_enb;
}io3xx_pull;

/*****************************************************************************
 * function prototypes
 *****************************************************************************/
//IO3xx-21
void IO3xx_21_update(char *devname, uint32_t module_identifier, uint32_t pull, uint32_t dir, uint32_t vio, uint32_t p14Position);
uint32_t IO3xx_21_update2(char *devname, uint32_t module_identifier, uint32_t pull, uint32_t dir, uint32_t vio, uint32_t p14Position);
uint32_t IO3xx_21_terminate(char *devname, uint32_t module_identifier, uint32_t vio, uint32_t p14Position);

//IO3xx-22
void IO3xx_22_update(char *devname, uint32_t module_identifier, uint32_t pull, uint32_t dir, uint32_t vio, uint32_t p14Position);
uint32_t IO3xx_22_update2(char *devname, uint32_t module_identifier, uint32_t pull, uint32_t dir, uint32_t vio, uint32_t p14Position);
uint32_t IO3xx_22_terminate(char *devname, uint32_t module_identifier, uint32_t vio, uint32_t p14Position);

// IO3xx-24
uint32_t IO3xx_24_update(char *devname, uint32_t module_identifier, uint32_t pull, uint32_t dir, uint32_t vio, uint32_t rearDiffSettings, uint32_t p14Position);
uint32_t IO3xx_24_update2(char *devname, uint32_t module_identifier, uint32_t pull, uint32_t dir, uint32_t vio, uint32_t rearDiffSettings, uint32_t p14Position);
uint32_t IO3xx_24_terminate(uint32_t module_identifier, uint32_t p14Position);

// IO3xx-40
uint32_t IO3xx_40_update(char *devname, uint32_t module_identifier, uint32_t p14Position);

// IO3xx-41
uint32_t IO3xx_41_update(char *devname, uint32_t module_identifier, uint32_t p14Position);

// IO3xx-120
uint32_t IO3xx_120_update(char *devname, uint32_t module_identifier, uint32_t p14Position);

// i2c functions for the legacy -24 wrapper
uint32_t IO3xx_24_i2c_legacy_read(volatile io3xx_2x* ptrio3xx_24, uint32_t deviceID, uint32_t frameSize, uint32_t readAddr, uint8_t *rdData);
uint32_t IO3xx_24_i2c_legacy_write(volatile io3xx_2x* ptrio3xx_24, uint32_t deviceID, uint32_t frameSize, uint8_t txData[]);

// function to check if the right i/o extension is connected
uint32_t sg_fpga_io3xx_check_rear_io(char *devname, uint32_t module_identifier, uint32_t p14Position, uint32_t rearIO);
bool sg_looks_like_string(const uint8_t *buf, uint32_t len);
// ip core addresses
#define IO3xx_P14_I2C_ADDR          0x00590000
#define IO3xx_P14_I2C_OFFSET        0x00010000

#ifdef __cplusplus
}
#endif


#endif
