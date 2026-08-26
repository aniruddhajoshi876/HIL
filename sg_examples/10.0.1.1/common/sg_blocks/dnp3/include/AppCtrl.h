/** @file AppCtrl.h
 *
 * @brief
 * Header file class representing application control octet
 *
 * @details
 * Contains declarations of a class representing application control octet
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_APPCTRL_H_
#define STACK_INCLUDE_APPCTRL_H_

#include "Basetypes.h"


class CAppCtrl {
public:
  CAppCtrl();
  CAppCtrl(int8u * p_data);
  
  static const int8u  SEQ = 0x0F;
  static const int8u  UNS = 0x10;
  static const int8u  CON = 0x20;
  static const int8u  FIN = 0x40;
  static const int8u  FIR = 0x80;

  /* Set/Clear functions return pointer to itself to allow one-line usage e.g. setBits(AppCtrl::FIN)->getData() */
  /* Sets ACO to values, discards previous data */
  CAppCtrl *     setData(int8u value);
  /* Sets selected bits in the data, e.g. setBits(AppCtrl::FIN | AppCtrl::FIR) */
  CAppCtrl *     setBits(int8u value);
  /* Clears selected bits in the data, e.g. clearBits(AppCtrl::FIN | AppCtrl::FIR) */
  CAppCtrl *     clearBits(int8u value);
  /* Returns data */
  int8u          getData(void);
  /* Checks if the selected bit is set. Returns true if set, false if cleared */
  boolean_t      checkBit(int8u bit);
  /* Returns values of multi-bit SEQ field */
  int8u          getSEQ(void);
  /* Sets value of multi-bit SEQ field */
  void           setSEQ(int8u seq);

private:
  int8u data;
};

#endif /* STACK_INCLUDE_APPCTRL_H_ */
