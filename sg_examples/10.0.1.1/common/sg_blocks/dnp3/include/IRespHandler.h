/** @file IRespHandler.h
 *
 * @brief
 * Header file class representing an interface for response handler implementation
 *
 * @details
 * Contains declarations of a class representing an interface for master callback implemenation
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_IRESPHANDLER_H_
#define STACK_INCLUDE_IRESPHANDLER_H_

#include "Basetypes.h"

class CTranspFunc;

class IRespHandler {
public:
  virtual DNP3_STATUS_t handleReq(int8u *p_pdu, int16u pduLen, CTranspFunc * p_tf) = 0;
  virtual DNP3_STATUS_t handleEvents(void) { return DNP3_OK; }
  virtual ~IRespHandler() { }
};

#endif /* STACK_INCLUDE_IRESPHANDLER_H_ */
