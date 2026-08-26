/** @file IntInd.h
 *
 * @brief
 * Header file class representing internal indications octets
 *
 * @details
 * Contains declarations of a class representing internal indications octets
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_INTIND_H_
#define STACK_INCLUDE_INTIND_H_

#include "Basetypes.h"

class CIntInd {
public:
  CIntInd();
  CIntInd(int8u * p_data);

  enum {
    ALL_STATIONS               = 0x0001,
    CLASS_1_EVENTS             = 0x0002,
    CLASS_2_EVENTS             = 0x0004,
    CLASS_3_EVENTS             = 0x0008,
    NEED_TIME                  = 0x0010,
    LOCAL_CONTROL              = 0x0020,
    DEVICE_TROUBLE             = 0x0040,
    DEVICE_RESTART             = 0x0080,
    NO_FUNC_CODE_SUPPORT       = 0x0100,
    OBJECT_UNKNOWN             = 0x0200,
    PARAMETER_ERROR            = 0x0400,
    EVENT_BUFFER_OVERFLOW      = 0x0800,
    ALREADY_EXECUTING          = 0x1000,
    CONFIG_CORRUPT             = 0x2000,
    RESERVED_2                 = 0x4000,
    RESERVED_1                 = 0x8000
  };

  /* Set/Clear functions return pointer to itself to allow one-line usage e.g. setBits(CIntInd::NEED_TIME)->getData() */
  /* Sets IntInd to value, discards previous data */
  CIntInd *     setData(int16u value);
  /* Sets IntInd to value extracted from the buffer, discards previous data */
  CIntInd *     setData(int8u * p_data);
  /* Sets selected bits in the data, e.g. setBits(CIntInd::NEED_TIME | CIntInd::CLASS_1_EVENTS) */
  CIntInd *     setBits(int16u value);
  /* Clears selected bits in the data, e.g. clearBits(CIntInd::NEED_TIME | CIntInd::CLASS_1_EVENTS) */
  CIntInd *     clearBits(int16u value);
  /* Returns data */
  int16u        getData(void);
  /* Checks if the selected bit is set. Returns true if set, false if cleared */
  bool          checkBit(int16u bit);
  /* Copies contained data to the buffer */
  void          serialize(int8u * p_buffer);
private:
  int16u data;
};



#endif /* STACK_INCLUDE_INTIND_H_ */
