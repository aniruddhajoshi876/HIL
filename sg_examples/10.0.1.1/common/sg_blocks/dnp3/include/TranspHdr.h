/** @file TranspHdr.h
 *
 * @brief
 * Header file class representing transport header octet
 *
 * @details
 * Contains declarations of a class representing transport header octet
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_TRANSPHDR_H_
#define STACK_INCLUDE_TRANSPHDR_H_

#include "Basetypes.h"

class CTranspHdr {
public:
  CTranspHdr();
  CTranspHdr(int8u * p_data);

  enum {
    SEQ0 = 0x01,
    SEQ1 = 0x02,
    SEQ2 = 0x04,
    SEQ3 = 0x08,
    SEQ4 = 0x10,
    SEQ5 = 0x20,
    FIR  = 0x40,
    FIN  = 0x80
  };

  /* Set/Clear functions return pointer to itself to allow one-line usage e.g. setBits(CTranspHdr::FIN)->getData() */
  /* Sets transport header to values, discards previous data */
  CTranspHdr *     setData(int8u value);
  /* Sets selected bits in the data, e.g. setBits(CTranspHdr::FIN | CTranspHdr::FIR) */
  CTranspHdr *     setBits(int8u value);
  /* Clears selected bits in the data, e.g. clearBits(CTranspHdr::FIN | CTranspHdr::FIR) */
  CTranspHdr *     clearBits(int8u value);
  /* Returns data */
  int8u            getData(void);
  /* Checks if the selected bit is set. Returns true if set, false if cleared */
  bool             checkBit(int8u bit);
  /* Returns values of multi-bit SEQ field */
  int8u            getSEQ(void);
  /* Sets value of multi-bit SEQ field */
  void             setSEQ(int8u seq);

private:
  int8u data;
};

#endif /* STACK_INCLUDE_TRANSPHDR_H_ */
