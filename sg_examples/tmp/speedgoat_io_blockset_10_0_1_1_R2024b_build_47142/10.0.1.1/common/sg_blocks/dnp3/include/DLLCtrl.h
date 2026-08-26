/** @file DLLCtrl.h
 *
 * @brief
 * Header file class representing DNP3 Data Link Layer control octet
 *
 * @details
 * Contains declarations of a class representing DNP3 Data Link Layer control octet
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLCTRL_H_
#define STACK_FRAME_DLL_DLLCTRL_H_

#include "Basetypes.h"



class CDLLCtrl {
public:
  CDLLCtrl();
  CDLLCtrl(int8u value);

  enum {
    FUNC0 = 0x01,
    FUNC1 = 0x02,
    FUNC2 = 0x04,
    FUNC3 = 0x08,
    FCV   = 0x10,
    DFC   = 0x10,
    FCB   = 0x20,
    PRM   = 0x40,
    DIR   = 0x80
  };

  typedef enum {
    /* Primary to secondary */
    RESET_LINK_STATES = 0x00,
    TEST_LINK_STATES  = 0x02,
    CONF_USER_DATA    = 0x03,
    UNCONF_USER_DATA  = 0x04,
    REQ_LINK_STATUS   = 0x09,
    /* Secondary to primary */
    ACK               = 0x00,
    NACK              = 0x01,
    LINK_STATUS       = 0x0B,
    NOT_SUPPORTED     = 0x0F
  } DLL_FUN_t;

  // TODO doc
  CDLLCtrl *    setData(int8u value);
  CDLLCtrl *    setBits(int8u value);
  CDLLCtrl *    clearBits(int8u value);
  int8u         getData();
  boolean_t     checkBit(int8u bit);
  DLL_FUN_t     getFun();
  void          setFun(DLL_FUN_t fun);

private:
  int8u data;
};

#endif /* STACK_FRAME_DLL_DLLCTRL_H_ */
