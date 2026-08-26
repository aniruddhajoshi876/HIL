/** @file MasterRespHandler.h
 *
 * @brief
 * Header file for master response handler class
 *
 * @details
 * Contains definition of master response handler attributes and member functions
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_MASTERRESPHANDLER_H_
#define STACK_INCLUDE_MASTERRESPHANDLER_H_

#include "Basetypes.h"
#include "TranspFunc.h"
#include "IRespHandler.h"

class CMasterImpl;

class CMasterRespHandler : public IRespHandler {
public:
  CMasterRespHandler(CMasterImpl * p_masterParam);
  virtual DNP3_STATUS_t handleReq(int8u *p_pdu, int16u pduLen, CTranspFunc * p_tf) override;

  virtual ~CMasterRespHandler() {}

protected:
  DNP3_STATUS_t handleResp(CFrameInterpreter& fi, boolean_t * p_conf);
  DNP3_STATUS_t handleUnsolResp(CFrameInterpreter& fi);
  DNP3_STATUS_t handleAuthResp(CFrameInterpreter& fi);

private:
  DNP3_STATUS_t checkSEQ(CAppCtrl *p_appCtrl);

  CMasterImpl * p_master;
  int8u         nextSeq;
};

#endif /* STACK_INCLUDE_MASTERRESPHANDLER_H_ */
