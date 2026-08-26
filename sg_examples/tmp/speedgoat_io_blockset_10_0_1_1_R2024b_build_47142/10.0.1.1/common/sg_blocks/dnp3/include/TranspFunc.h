/** @file TranspFunc.h
 *
 * @brief
 * Header file class representing DNP3 transport function handler
 *
 * @details
 * Contains declarations of a class representing DNP3 transport function handler
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_TRANSPFUNC_H_
#define STACK_INCLUDE_TRANSPFUNC_H_

#include "Basetypes.h"
#include "DLLPrimary.h"
#include "Command.h"
#include "NotCopyable.h"
#include "IRespHandler.h"

#define TF_SEG_LENGTH     250 /* 1 octet header and 1 to 249 data */
#define TF_DATA_LENGTH    249
#define TF_SEQ_MAX        64

class CTranspFunc : NotCopyable {
public:

  enum RCV_STATE_T {
    STATE_IDLE,
    STATE_ASSEMBLY,
    STATE_WAIT_SEC_REPLY,
    STATE_WAIT_KEY_STATUS,
    STATE_WAIT_KEY_CHG_ACK
  };

  CTranspFunc(CDLLPrimary * p_pri, IRespHandler * p_hdlr);
  ~CTranspFunc();

  /* Splits the Application Layer fragment to segments and sends them. Called by Application Layer */
  DNP3_STATUS_t sendFrame(int8u * p_buf, int16u fragLen);
  /* Assembles segments from Data Link Layer to construct one fragment and calls Application Layer handler. Called by Data Link Layer */
  DNP3_STATUS_t receiveFrame(int8u * p_buf, int8u fragLen, int16u dstAddr);

  DNP3_STATUS_t handleUnsolicited(int8u * p_pdu, int16u pduLen);

  int16u getOutstAddr(void) { return outstAddr; }
  int8u* getTxBuf(int16u len);
  int8u  getState(void) { return rcvState; }

protected:
  virtual DNP3_STATUS_t checkRxASDU(int8u*, int16u) { return DNP3_OK; }
  virtual DNP3_STATUS_t checkTxASDU(int8u*, int16u*) { return DNP3_OK; }

  int8u calcSegs(int16u fragLen);
  int8u calcSegLen(int16u fragLen);
  boolean_t isNextSeq(int8u seq);
  void appendToBuffer(int8u * p_buf, int8u dataLen);

  int8u               txSeqNr;
  int8u               rxSeqNr;
  int8u *             p_rxBuf;
  int16u              rxBufLen;
  int8u *             p_txBuf;
  RCV_STATE_T         rcvState;
  CDLLPrimary *       p_primary;
  IRespHandler *      p_handler;
  int16u              outstAddr;      // received from upper layer, needed in application layer
};

#endif /* STACK_INCLUDE_TRANSPFUNC_H_ */
