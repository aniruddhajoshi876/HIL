/** @file hal.h
 *
 * @brief
 * IEC61850 platform abstraction (aka driver) for cygwin
 *
 * @details
 * This file contains the declaration of cygwin specific functions and variables to access communication, thread and timers.
 *
 * @copyright
 * Copyright 2014-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */

#if !defined(_HAL__INCLUDED_)
#define _HAL__INCLUDED_

#include "hal_types.h"
#include "hal_time.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <semaphore.h>

/* C++11 atomics */
#include <atomic>
typedef std::atomic<bool>       HAL_ATOMIC_BOOL;

#if DNP3_LIB_BUILD
#include "DNP3_conf.h"
#endif

#define HAL_INVCHAN             -1
#define ETH_P_VLAN              0x8100
#define MAC_ADDR_LEN            6
#define MAX_FRAME_LEN           1527

#define HAL_THREAD_INV          NULL

#define HAL_TIMER_INV           0xffff
#define HAL_TIMER_SINGLE        0
#define HAL_TIMER_PERIODIC      1
#define HAL_TIMER_FLAG_CLR      1

#define HAL_SEM_BINARY          0
#define HAL_SEM_COUNT           1
#define HAL_SEM_INV             -1

#define HAL_THREAD_PRIO_TIMER   80

/** Defines the maximum number of files that can be supported at once */
#define HAL_MAX_OPENED_FILES    10
#define HAL_INVALID_FID         0xFFFFFF

#define FALSE                   false
#define TRUE                    true

#define HAL_SNPRINTF            snprintf

#define HAL_TIMER_FUNCTION(f)   void f(void *p_arg)
#define HAL_TIMER_ARG(a,t)      ((t)(a))

#define HAL_THREAD_FUNCTION(f)  void* f(void *p_arg)
#define HAL_THREAD_RETURN(x)    HAL_ThreadReturn(x)

#define HAL_memcpy(d,s,l)       memcpy((d), (s), (l))

/* public data types
---------------------------------------------------------------------------*/
typedef int                    HAL_COMCHAN_T;
typedef int                    HAL_UDPCHAN_T;
typedef int                    HAL_TCPCHAN_T;
typedef pthread_t              HAL_THREAD_HANDLE_T;
typedef pthread_t              HAL_THREAD_ID_T;
typedef sem_t                  HAL_SEM_T;
typedef int                    HAL_UART_T;

typedef void* (*fptr_THREAD_FUNC)(void*);
typedef void (*fptr_TIMER_CB)(void*);

void HAL_Delay(int32u miliSec);

int32u HAL_SysTick(void);
uint64_t HAL_MicroSecondCount(void);
double HAL_MilliSecondCount(void);

/* This function is used to initialize the HAL system layer */
HAL_STATUS_t HAL_Init();

/* This function is used to close the HAL layer */
void HAL_Close(void);

/* initializes memory allocator */
HAL_STATUS_t HAL_memInit(void);

/* Allocates memory buffer of the size requested by the user */
int8u* HAL_memGet(int16u len);

/* Releases memory buffer allocated with HAL_memGet */
void HAL_memRelease(void *p_buf);

/* This function is used to configure the system IP */
HAL_STATUS_t HAL_IpConfig(int32u ip, int32u nm, int32u gw);

/* This function is used to verify if IP configuration of the device is consistent with the one of the IEC61850 server */
HAL_STATUS_t HAL_CheckNetConf(int32u ip, int32u nm, int32u gw);

/* This function is used to configure domain name server */
HAL_STATUS_t HAL_DnsInit(int32u dnsAddr);

/* This function is used to configure NTP server */
HAL_STATUS_t HAL_NtpInit(int32u ntpAddr, const char *ps_hname);

/* This function reads the MAC address of the given interface */
HAL_STATUS_t HAL_GetMacAddr(const char* ifName, unsigned char* pMacAddr);

/* This function reads the IP address of the given interface */
HAL_STATUS_t HAL_GetIpAddr(const char* ifName, int32u* p_ipAddr);

#if (CFG_ENABLE_GOOSE == 1) || (CFG_ENABLE_SV == 1)
/* This function is used to open a transmission channel */
HAL_COMCHAN_T HAL_OpenRTChannel(const char *ifName, int16u ethType);

/* This function is used to close a transmission channel */
HAL_STATUS_t HAL_CloseRTChannel(HAL_COMCHAN_T c);

/* This function is used to send an Ethernet frame */
HAL_STATUS_t HAL_SendFrame(HAL_COMCHAN_T c, int8u *p_data, int16u dataLen);

/* This function is used to receive Ethernet frames */
HAL_STATUS_t HAL_ReceiveFrame(HAL_COMCHAN_T c, int8u *p_data, int32u *p_dataLen);
#else
#define HAL_OpenRTChannel(ifName, ethType)        HAL_INVCHAN
#define HAL_CloseRTChannel(c)                     HAL_OKEY
#define HAL_SendFrame(c, p_d, l)                  HAL_OKEY
#define HAL_ReceiveFrame(c, p_d, p_l)             HAL_OKEY
#endif

/* Low level functions to access threads */
/* This function is used to create a thread */
HAL_STATUS_t HAL_CreateThread(int16 priority, fptr_THREAD_FUNC p_ThreadFunc, void *p_arg, HAL_THREAD_HANDLE_T *p_ThreadHandle);

/* This function is used to delete a thread */
void HAL_DeleteThread(HAL_THREAD_HANDLE_T *p_ThreadHandle);

HAL_THREAD_ID_T HAL_GetThreadId();

void HAL_Yield(void);

void* HAL_ThreadReturn(void* p_retVal);

/* This function lists available interface */
HAL_STATUS_t HAL_SelectEthIf(const char *p_netIf = NULL);

/* Functions to access timers */
/* This function is used to create a timer with a millisecond resolution */
int16u HAL_SetTimer(int8u type, int32 period, fptr_TIMER_CB p_TimerFunc, void *p_arg); //time in ms

/* This function is used to create a timer with a nanosecond resolution */
//TODOjm int16u HAL_SetTimer(int8u type, int64 period, fptr_TIMER_CB p_TimerFunc, void *p_arg); //time in ns

/* This function is used to cancel a running timer */
HAL_STATUS_t HAL_CancelTimer(int16u timerId);

/* Functions to access semaphores */
/* This function is used to create a semaphore */
HAL_STATUS_t HAL_SemCreate(HAL_SEM_T *p_sem, int8u type, int8u init_val);

/* This function is used to obtain the semaphore */
HAL_STATUS_t HAL_SemTake(HAL_SEM_T *p_sem);

/* This function is used to release the semaphore */
HAL_STATUS_t HAL_SemGive(HAL_SEM_T *p_sem);

/* This function is used delete a semaphore */
HAL_STATUS_t HAL_SemDelete(HAL_SEM_T *p_sem);

#if CFG_ENABLE_UDP
/* UDP HAL functions - used only for  time synchronization */

/* UDP HAL functions */
/* This function is used to open an UDP communication channel */
HAL_UDPCHAN_T HAL_OpenUDPChannel(int32u srcAddress, int16u port);

/*This function is used to close an UDP communication channel*/
HAL_STATUS_t HAL_CloseUDPChannel(HAL_UDPCHAN_T c);

/* This function is used to send an UDP frame */
HAL_STATUS_t HAL_SendUDPFrame(HAL_UDPCHAN_T c, int8u *p_data, int16u dataLen, int32u dstAddress, int16u port);

/* This function is used to receive an UDP frame */
HAL_STATUS_t HAL_ReceiveUDPFrame(HAL_UDPCHAN_T c, int8u *p_data, int32u *p_dataLen, int32u maxLen,
                                 int32u *p_ip, int16u *p_port);

/* This function is used to enable transmission of multicast UDP packets */
HAL_STATUS_t HAL_udpEnableMcast(HAL_UDPCHAN_T c, int32u srcAddress, int8u ttl);
HAL_STATUS_t HAL_udpJoinMcast(HAL_UDPCHAN_T ch, int32u srcAddr, int32u dstAddr);
#endif

/* TCP HAL functions */
/* This function is used to open a TCP connection server */
HAL_TCPCHAN_T HAL_openTCPServer(int16u portNum, int32u ipAddr = 0);

/* This function is used to close a TCP connection server */
HAL_STATUS_t HAL_closeTCPServer(HAL_TCPCHAN_T chServ);

/* This function is used to close a TCP client connection */
HAL_STATUS_t HAL_closeTCPChannel(HAL_TCPCHAN_T ch);

/* This function is used to obtain a TCP client connection */
HAL_TCPCHAN_T HAL_waitForConnection(HAL_TCPCHAN_T chServ);

/* This function is used to obtain a TCP client connection */
//HAL_TCPCHAN_T HAL_tcpCconnect(int32u ipAddr, int16u portNum);
HAL_TCPCHAN_T HAL_tcpCconnect(int32u localIpAddr, int16u localPort, int32u remoteIpAddr, int16u remotePort);

/* This function is used to receive data through a TCP client connection */
HAL_STATUS_t HAL_readTCPData(HAL_TCPCHAN_T ch, int8u *p_data, int16u *p_dataLen, int32u timeOut = 200);

/* This function is used to send data through a TCP client connection */
HAL_STATUS_t HAL_sendTCPData(HAL_TCPCHAN_T ch, int8u *p_data, int16u dataLen);

/* Configures UART interace */
HAL_STATUS_t HAL_uartConfig(const char* ps_uart, int32u baudRate, int8u wordLen, 
                            int8u parity, int8u stopBits, HAL_UART_T *p_uid);

/* Writes dlen bytes to serial interace */
HAL_STATUS_t HAL_uartSend(HAL_UART_T uartId, const int8u *p_data, int16u dlen);

/* Reads data from serial interface */
HAL_STATUS_t HAL_uartRead(HAL_UART_T uartId, int8u *p_data, int16u *p_dlen);

/* File access functions */
/* Function used to open a file */
HAL_STATUS_t HAL_FileOpen(const char *p_fileName, int32u pos, int32u * const p_fileID);

/* Function used to create a file */
HAL_STATUS_t HAL_FileCreate(const char *p_fileName, int32u * const p_fileID);

/* Function used to copy a file */
HAL_STATUS_t HAL_FileCopy(const char *p_fileSrc, const char *p_fileDst);

/* Function used to close a file */
HAL_STATUS_t HAL_FileClose(int32u fileID);

/* Function used to read data from file */
HAL_STATUS_t HAL_FileRead(int32u fileID, int8u *p_dst, int32u len, int32u * const p_count);

/* Function used to write data to file */
HAL_STATUS_t HAL_FileWrite(int32u fileID, const void *p_src, int32u len);

/* Function used to delete a file */
HAL_STATUS_t HAL_FileDelete(const char *p_fileName);

HAL_STATUS_t HAL_FileGetSize(int32u fileID, int32u *pFileLen);

HAL_STATUS_t HAL_FileSetPos(int32u fileID, int32u pos);

/* Function used to obtain file attributes */
HAL_STATUS_t HAL_GetFileAtrubutes(const char *p_fileName, int32u * const p_size, CTimeStamp * const p_lastMod);

/* Function used to open a file directory */
HAL_STATUS_t HAL_OpenDir(const char *p_dirName);

/* Function used to read file names from a directory */
int32u HAL_ReadDir(char *p_fileName);

/* Function used to close a file directory */
HAL_STATUS_t HAL_CloseDir(void);

/* Function used to construct a path to access files */
void HAL_CreateFullPath(char* p_fullPath, const char *p_filename);

char HAL_getChar(void);

void HAL_assert(const char *psFunc, const char *psMsg);

// Added by abeck Speedgoat
void* HAL_timerThrd(void*);

#endif /* _HAL__INCLUDED_ */
