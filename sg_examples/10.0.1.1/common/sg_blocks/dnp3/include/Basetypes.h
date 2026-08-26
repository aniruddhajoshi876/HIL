/** @file Basetypes.h 
 *
 * @brief
 * Header file for control block base class
 *
 * @details
 * Contains definition of device attributes, points, arrays
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */
 
#if !defined(_DNP3_BASE_TYPES_H)
#define _DNP3_BASE_TYPES_H

typedef bool                 boolean_t;
typedef short int            int16;
typedef signed int           int32;
typedef unsigned char        int8u;
typedef unsigned short int   int16u;
typedef unsigned int         int32u;
typedef unsigned long long   int64u;
typedef float                float32;
typedef double               double64;
typedef char*                VSTRING_t;

#include "dnp3_config.h"

typedef enum {
  DNP3_OK       = 0,
  DNP3_MORE_DATA,
  DNP3_ERR_STATE,
  DNP3_ERR_VALUE,
  DNP3_ERR_PARAM,
  DNP3_ERR_FULL,
  DNP3_ERR_IO,
  DNP3_ERR_NOT_SUPPORTED,
  DNP3_ERR_NOT_FOUND,
  DNP3_ERR_OBJ_UNKN,
  DNP3_ERR_FUNC_CODE,
  DNP3_ERR_MEM,
  DNP3_EOF,
  DNP3_NO_DATA
} DNP3_STATUS_t;

typedef enum {
  CLASS_0        = 0x01,
  CLASS_1        = 0x02,
  CLASS_2        = 0x04,
  CLASS_3        = 0x08,
  CLASS_UNKNOWN  = 0x10
} CLASS_t;

typedef enum {
  TYPE_BOOL        = 0,
  TYPE_INT8U,
  TYPE_INT16,
  TYPE_INT16U,
  TYPE_INT32,
  TYPE_INT32U,
  TYPE_FLOAT32,
  TYPE_VSTRING,
  TYPE_NONE,
} DATA_TYPE_t;

typedef struct _GROUP0_VALUE_t{
  DATA_TYPE_t           dt;
  union {
    int8u               vi8u;
    int16               vi16;
    int32               vi32;
    float32             vf32;
    const char*         vstr;
  } v;
} GROUP0_VALUE_t;

#define INDEX_INVALID              0xFFFF
#define INDEX_ALL                  0xFFFF

#define GROUP0_ELEM_BOOL(n)        { TYPE_BOOL,    {.vi8u = (n)} }
#define GROUP0_ELEM_INT8U(n)       { TYPE_INT8U,   {.vi8u = (n)} }
#define GROUP0_ELEM_INT16(n)       { TYPE_INT16,   {.vi16 = (n)} }
#define GROUP0_ELEM_INT32(n)       { TYPE_INT32,   {.vi32 = (n)} }
#define GROUP0_ELEM_FLOAT32(n)     { TYPE_FLOAT32, {.vf32 = (n)} }
#define GROUP0_ELEM_VSTR(n)        { TYPE_VSTRING, {.vstr = (n)} }
#define GROUP0_END                 { TYPE_NONE,    {.vstr = (char*)NULL} }

#if CFG_CTRL_ENABLED
/** Size of control relay output block */
#define CROB_SIZE                      11

/** Control operation error codes      */
#define CTRL_OPER_ERR_INDEX            4

/** Indexes of the fields within CROB  */
#define CROB_OFF_CTRL                  0
#define CROB_OFF_COUNT                 1
#define CROB_OFF_TIMEON                2
#define CROB_OFF_TIMEOFF               6
#define CROB_OFF_STATUS                10

typedef enum {
  CTRL_BOUT_NULL                     = 0,
  CTRL_BOUT_PULSE_ON,
  CTRL_BOUT_PULSE_OFF,
  CTRL_BOUT_LATCH_ON,
  CTRL_BOUT_LATCH_OFF,
} CTRL_BIN_OUT_t;

typedef enum {
  TCC_NUL        = 0,
  TCC_CLOSE      = 1,
  TCC_TRIP       = 2,
  TCC_RESERVED   = 3
} TCC_t;

typedef struct {
  CTRL_BIN_OUT_t opType;
  boolean_t clearField;
  TCC_t tcc;
  int8u count;
  int32u onTime;
  int32u offTime;
} CROB_REQUEST_t;

typedef union {
  int32 val_int32;
  int16 val_int16;
  float32 val_float32;
  double64 val_double64;
} AOB_REQUEST_t;

#endif

#endif   //_DNP3_BASE_TYPES_H
