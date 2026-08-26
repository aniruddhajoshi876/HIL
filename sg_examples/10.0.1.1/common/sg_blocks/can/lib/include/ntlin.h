// Copyright 2006-2026 Speedgoat GmbH

#pragma once
#ifndef _NTLIN_H_
#define _NTLIN_H_
#include <ntcan.h>
#ifdef __cplusplus
extern"C"{
#endif
#define z91329e620b                  (0x3cb+6229-0x1b21)
#define z45d82a8ee0(id)                    ((id) & (0x187+2641-0xb99))
#define z3c0158b0e3                       (0x7d0+1834-0xeba)
#define z07c11dc7ab       (0x1043+2071-0x185a)
#define z98e07f4d2d    (0x1c11+630-0x1e86)
#define zeee65801fd  (0x6b2+664-0x948)
#define NTLIN_IOCTL_SET_BAUDRATE       (0x8a8+6423-0x21be)
#define NTLIN_IOCTL_GET_BAUDRATE       (0x213f+1365-0x2692)
#define NTLIN_IOCTL_GET_SERIAL         NTCAN_IOCTL_GET_SERIAL
#define NTLIN_IOCTL_GET_TIMESTAMP_FREQ NTCAN_IOCTL_GET_TIMESTAMP_FREQ
#define NTLIN_IOCTL_GET_TIMESTAMP      NTCAN_IOCTL_GET_TIMESTAMP
#define NTLIN_IOCTL_SET_TIMEOUT        NTCAN_IOCTL_SET_RX_TIMEOUT
#define NTLIN_IOCTL_MASTER_SEL         NTCAN_IOCTL_LIN_MASTER_SEL
#define NTLIN_SUCCESS NTCAN_SUCCESS
#define NTLIN_INVALID_PARAMETER NTCAN_INVALID_PARAMETER
#define NTLIN_INVALID_HANDLE NTCAN_INVALID_HANDLE
#define NTLIN_NOT_SUPPORTED NTCAN_NOT_SUPPORTED
#define NTLIN_TIMEOUT NTCAN_RX_TIMEOUT
#define NTLIN_CONTR_BUSY NTCAN_CONTR_BUSY
#define NTLIN_HANDLE NTCAN_HANDLE
#define NTLIN_RESULT NTCAN_RESULT
#define NTLIN_NO_HANDLE NTCAN_NO_HANDLE
#define LIN_TX_ONCE (0x59c+8476-0x26b7)  
EXPORT NTLIN_RESULT CALLTYPE linOpen(int net,uint32_t flags,int32_t zfd0b590b9d,NTLIN_HANDLE*handle);EXPORT NTLIN_RESULT CALLTYPE linClose(NTLIN_HANDLE handle);EXPORT NTLIN_RESULT CALLTYPE linIoctl(NTLIN_HANDLE handle,uint32_t cmd,void*arg);EXPORT NTLIN_RESULT CALLTYPE linMasterTxHeader(NTLIN_HANDLE handle,int32_t id);EXPORT NTLIN_RESULT CALLTYPE linSlaveRxTake(NTLIN_HANDLE handle,int32_t id,int32_t*z88244e4151,void*data,uint64_t*timestamp);EXPORT NTLIN_RESULT CALLTYPE linSlaveTxCreate(NTLIN_HANDLE handle,int32_t id,uint32_t flags);EXPORT NTLIN_RESULT CALLTYPE linSlaveTxUpdate(NTLIN_HANDLE handle,int32_t id,int32_t len,void*data);EXPORT NTLIN_RESULT CALLTYPE linSlaveTxDestroy(NTLIN_HANDLE handle,int32_t id);EXPORT NTLIN_RESULT CALLTYPE linWait(NTLIN_HANDLE handle,int32_t*id,int32_t*len,void*data,uint64_t*timeStamp);EXPORT NTLIN_RESULT CALLTYPE linIdAdd(NTLIN_HANDLE handle,int32_t id,uint32_t type);EXPORT NTLIN_RESULT CALLTYPE linIdDelete(NTLIN_HANDLE handle,int32_t id,uint32_t type);
#ifdef __cplusplus
}
#endif
#endif 

