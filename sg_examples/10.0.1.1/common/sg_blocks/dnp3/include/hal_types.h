/** @file hal_types.h 
 *
 * @brief
 * Declarations of basic data types
 *
 * @details
 * This file contains the definition of basic types used in the library implementation
 *
 * @copyright
 * Copyright 2020-2099 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */
 
#include "sg_printf.h"
#include "sg_common.h"

#ifndef _HAL_TYPES_H
#define _HAL_TYPES_H

#define UNUSEDARG(a)        (void)(a)

/** Logging macrodefinitions */
#define LOG_LEVEL_ERR     0x0001
#define LOG_LEVEL_INFO    0x0002
#define LOG_LEVEL_DBG     0x0004
#define LOG_LEVEL_ALL     (LOG_LEVEL_ERR|LOG_LEVEL_INFO|LOG_LEVEL_DBG)

#define LOG_LEVEL_VAR(n)  static unsigned short _dbgFlag = n;

#define DNP3_PRINTF_ERROR(...) sg_printf(sg_error, __VA_ARGS__) 
#define DNP3_PRINTF_INFO(...) sg_printf(sg_info, __VA_ARGS__) 
#define DNP3_PRINTF_DEBUG(...) sg_printf(sg_debug, __VA_ARGS__) 

/** Macro definitions for logging debug information */
#define LOG_error(f, ...)   if (LOG_LEVEL_ERR & _dbgFlag) DNP3_PRINTF_ERROR("[%s:%s:%d] " f, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

/** Macro definitions for logging debug information */
#define LOG_info(f, ...)    if (LOG_LEVEL_INFO & _dbgFlag) DNP3_PRINTF_DEBUG("[%s:%s:%d] " f, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

#define LOG_enter(f, ...)   if (LOG_LEVEL_DBG & _dbgFlag) DNP3_PRINTF_DEBUG("[%s:%s:%d] " f, __FILE__, __func__, __LINE__, ##__VA_ARGS__);

/** Definition of the BOOLEAN type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef bool                 boolean_t;

/** Definition of the INT8 type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef signed char          int8;

/** Definition of the INT16 type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef signed short int     int16;

/** Definition of the INT32 type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef signed int           int32;

/** Definition of the INT64 type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef signed long long int int64;

/** Definition of the INT8Utype defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef unsigned char        int8u;

/** Definition of the INT16U type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef unsigned short int   int16u;

/* INT24U */
//typedef unsigned int       int24u;

/** Definition of the INT32U type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef unsigned int         int32u;

/** Definition of the FLOAT32 type defined in IEC 61850-7-2 chapter 6.1.1 pp 23 */
typedef float                float32;

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL         ((void*)0)
#endif
#endif

typedef enum {
  HAL_OKEY                              = 0,
  HAL_ERR_GEN,
  HAL_ERR_INIT,
  HAL_ERR_PARAM,
  HAL_ERR_NOTFOUND,
  HAL_ERR_PTR,
  HAL_ERR_IO,
  HAL_ERR_TIMEOUT,
  HAL_ERR_FILE,
  HAL_ERR_VERIFY,
  HAL_ERR_TCP_CLOSING,
  HAL_TCP_EOF,
  HAL_NO_DATA,
  HAL_FILE_MORE_DATA,
  HAL_ERR_NVM_CRC,
  HAL_ERR_NVM_INDEX,
  HAL_ERR_NVM_SIZE,
  HAL_ERR_FULL                      /*!< no space in the buffer or array error */
} HAL_STATUS_t;

#endif
