//===========================================================================
//
// NAME:    pdl_if.h
//
// DESCRIPTION:
//
//          PowerDAQ QNX driver firmware interface definition
//
// AUTHOR:  Alex Ivchenko
//
// DATE:    12-APR-2000
//
// REV:     0.8
//
// R DATE:  
//
// HISTORY:
//
//      Rev 0.8,     12-MAR-2000,     Initial version.
//
//
//---------------------------------------------------------------------------
//      Copyright (C) 2000 United Electronic Industries, Inc.
//      All rights reserved.
//---------------------------------------------------------------------------

#ifndef __PDL_IF_H__
#define __PDL_IF_H__

#define FW_MAXSEGSIZE 2048

typedef struct {
    DWORD dwMemType;
    DWORD dwMemAdrs;
    DWORD dwMemSize;
    DWORD dwMemData[FW_MAXSEGSIZE];
    } FW_MEMSEGMENT;

void pd_main();

// Start dealing with boards
extern int pd_find_devices(void);

// Cleanup boards after use
extern int pd_clean_devices(void);

// Get board capabilities
extern int pd_get_adapter_info(int board, Adapter_Info* pAdInfo)
;

// Interface between xPC Target and UEI
int pd_xpc_assign_device( int subDeviceId,
                          unsigned long address,
                          unsigned short interruptLine);
// pdl_fwi.c
extern u32 pd_dsp_get_status(int board);
extern u32 pd_dsp_get_flags(int board);
extern void pd_dsp_set_flags(int board, u32 new_flags);
extern void pd_dsp_command(int board, int command);
extern void pd_dsp_cmd_no_ret(int board, u16 command);
extern void pd_dsp_write(int board, u32 data);
extern u32 pd_dsp_read(int board);
extern u32 pd_dsp_cmd_ret_ack(int board, u16 wCmd);
extern u32 pd_dsp_cmd_ret_value(int board, u16 wCmd);
extern u32 pd_dsp_read_ack(int board);
extern u32 pd_dsp_write_ack(int board, u32 dwValue);
extern u32 pd_dsp_cmd_write_ack(int board, u16 wCmd, u32 dwValue);
extern u32 pd_dsp_int_status(int board);
extern u32 pd_dsp_acknowledge_interrupt(int board);
extern int pd_dsp_startup(int board);
extern void  pd_init_calibration(int board);
extern int pd_reset_dsp(int board);
extern int pd_download_firmware_bootstrap(int board);
extern int pd_reset_board(int board);
extern int pd_download_firmware(int board);
extern int pd_echo_test(int board);
extern u32 pd_dsp_reg_read( int board, u32 offset );
extern u32 pd_dsp_reg_write( int board, u32 offset, u32 value );

// pdl_ain.c
extern int pd_ain_set_config(int, u32, u32, u32);
extern int pd_ain_set_cv_clock(int board, u32 clock_divisor);
extern int pd_ain_set_cl_clock(int board, u32 clock_divisor);
extern int pd_ain_set_channel_list(int board, u32 num_entries, u32 list[]);
extern int pd_ain_set_events (int board, u32 dwEvents);
extern int pd_ain_get_status(int board, u32* status);
extern int pd_ain_sw_start_trigger(int board);
extern int pd_ain_sw_stop_trigger(int board);
extern int pd_ain_set_enable_conversion(int board, int enable);
extern int pd_ain_get_value(int board, u16* value);
extern int pd_ain_set_ssh_gain(int board, u32 dwCfg);
extern int pd_ain_get_samples(int board, int max_samples, uint16_t buffer[]);
extern int pd_ain_reset(int board);
extern int pd_ain_sw_cl_start(int board);
extern int pd_ain_sw_cv_start(int board);
extern int pd_ain_reset_cl(int board);
extern int pd_ain_clear_data(int board);
extern int pd_ain_flush_fifo(int board);
extern int pd_ain_get_xfer_samples(int board, int samples, uint16_t* buffer);
extern int pd_ain_set_xfer_size(int board, u32 size);
extern int pd_ain_set_busmaster_list(int board, unsigned long *list);

// pdl_aio.c
extern int pd_register_daq_buffer(int board, u32 ScanSize, u32 FrameSize, u32 NumFrames,
                           uint16_t* databuf, int bWrap, int bRecycle);
extern int pd_unregister_daq_buffer(int board);                           
extern int pd_clear_daq_buffer(int board, int subsystem);
extern int pd_ain_async_init(int board, PTAinAsyncCfg pAInCfg);
extern int pd_ain_async_term(int board);
extern int pd_ain_async_start(int board);
extern int pd_ain_async_stop(int board);
extern int pd_ain_get_scans(int board, PTScan_Info pScanInfo);
extern int pd_get_buf_status(int board, int subsystem, PTBuf_Info pDaqBuf);

// pdl_ao.c
extern int pd_aout_set_config(int board, u32 config, u32 posttrig);
extern int pd_aout_set_cv_clk(int board, u32 dwClkDiv);
extern int pd_aout_set_events(int board, u32 dwEvents);
extern int pd_aout_get_status(int board, u32* dwStatus);
extern int pd_aout_set_enable_conversion(int board, u32 dwEnable);
extern int pd_aout_sw_start_trigger(int board);
extern int pd_aout_sw_stop_trigger(int board);
extern int pd_aout_sw_cv_start(int board);
extern int pd_aout_clear_data(int board);
extern int pd_aout_reset(int board);
extern int pd_aout_put_value(int board, u32 dwValue);
extern int pd_aout_put_block(int board, u32 dwNumValues, u32* pdwBuf, u32* pdwCount);
extern int pd_aout_dmaSet(int board, u32 offset, u32 count, u32 source);
extern int _PdAO96SetUpdateChannel(int board, u16 wChannel, u16 Mode);
       
int pd_aout_write_scan(
   int board,
   const char *buffer,
   int count);  // function for write() from aout
   
// pdl_dio.c
extern int pd_din_set_config(int board, u32 config);
extern int pd_din_set_event(int board, u32 events);
extern int pd_din_clear_events(int board, u32 events);
extern int pd_din_read_inputs(int board, u32 *pdwValue);
extern int pd_din_clear_data(int board);
extern int pd_din_reset(int board);
extern int pd_din_status(int board, u32 *pdwValue);
extern int pd_dout_write_outputs(int board, uint32_t val);
extern int pd_dio256_write_output(int board, uint32_t cmd, uint32_t val);
extern int pd_dio256_read_input(int board, uint32_t cmd, uint32_t* val);

extern int pd_din_read(int board, char* buffer, int count);
extern int pd_dout_write(int board, const char* buffer, int count);

// pdl_uct.c
extern int pd_uct_set_config(int board, u32 config);
extern int pd_uct_set_event(int board, u32 events);
extern int pd_uct_clear_event(int board, u32 events);
extern int pd_uct_get_status(int board, u32* status);
extern int pd_uct_write(int board, u32 value);
extern int pd_uct_read(int board, u32 config, u32* value);
extern int pd_uct_set_sw_gate(int board, u32 gate_level);
extern int pd_uct_sw_strobe(int board);
extern int pd_uct_reset(int board);

// pdl_event.c
extern int pd_enable_events(int board, PTEvents pEvents);
extern int pd_disable_events(int board, PTEvents pEvents);
extern int pd_set_user_events(int board, u32 subsystem, u32 events);
extern int pd_clear_user_events(int board, u32 subsystem, u32 events);
extern int pd_get_user_events(int board, u32 subsystem, u32* events);
extern int pd_immediate_update(int board);
extern void pd_debug_show_events (TEvents *Event, char* msg);

// pdl_brd.c
extern int pd_adapter_enable_interrupt(int board, u32 val);
extern int pd_adapter_acknowledge_interrupt(int board);
extern int pd_adapter_get_board_status(int board, PTEvents pEvent);
extern int pd_adapter_set_board_event1(int board, u32 dwEvents);
extern int pd_adapter_set_board_event2(int board, u32 dwEvents);
extern int pd_adapter_eeprom_read(int board, u32 dwMaxSize, uint16_t *pwReadBuf);
extern int pd_adapter_eeprom_write(int board, u32 dwBufSize, u16* pwWriteBuf);
extern int pd_cal_dac_write(int board, u32 dwCalDACValue);
extern int pd_adapter_test_interrupt(int board);

// pdl_int.c
extern void pd_stop_and_disable_ain(int board);
extern void pd_process_pd_ain_get_samples(int board, int bFHFState);
extern void pd_process_driver_events(int board, PTEvents pEvents);
extern int pd_notify_user_events(int board, PTEvents pNewFwEvents);
extern void pd_process_events(int board);

// pdl_init.c
extern void  pd_init_pd_board(int board);

// pd2_dao.c
extern int _PdDIOEnableOutput(int board, u32 dwRegMask);
extern int _PdDIORead(int board, u32 dwRegister, u32 *pdwValue);
extern int _PdDIOWrite(int board, u32 dwRegister, u32 dwValue);

#endif // _PDL_IF_H
