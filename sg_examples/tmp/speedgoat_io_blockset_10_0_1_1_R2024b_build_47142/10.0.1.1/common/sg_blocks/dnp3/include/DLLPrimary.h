/** @file DLLPrimary.h
 *
 * @brief
 * Header file class representing DNP3 Data Link Layer primary station
 *
 * @details
 * Contains declarations of a class representing DNP3 Data Link Layer primary station
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLPRIMARY_H_
#define STACK_FRAME_DLL_DLLPRIMARY_H_

#include "Basetypes.h"
#include "DLLFrameInterpreter.h"
#include "NotCopyable.h"

#include "IMasterCallback.h"

typedef enum {
  SecUnResetIdle,
  SecResetIdle,
  ResetLinkWait1,
  ResetLinkWait2,
  URLinkStatusWait,
  TestWait,
  CfmdDataWait,
  RLinkStatusWait
} PSTATE_t; /* ref DNP3 9.3.1.2 */

class CDLLHandler;

class CDLLPrimary : NotCopyable {
friend class CDLLHandler;
public:
  CDLLPrimary(CDLLHandler * p_handlerParam, int8u retries);

  DNP3_STATUS_t handleResponse(CDLLFrameInterpreter& fi);
  DNP3_STATUS_t handleTimeout();
  DNP3_STATUS_t sendData(int8u * p_data, int8u dataLen);
  DNP3_STATUS_t keepAlive();

  DNP3_STATUS_t resetLink();
  DNP3_STATUS_t testLink();

  boolean_t getIsMaster();
  boolean_t getExpectResp();
  void setMasterCB(IMasterCallback *p_cb) { p_masterCB = p_cb; }

  ~CDLLPrimary();

private:
  DNP3_STATUS_t sendRequest(CDLLCtrl::DLL_FUN_t funCode, int8u * p_data = nullptr, int8u dataLen = 0);
  DNP3_STATUS_t sendConfData(int8u * p_data, int8u dataLen);
  DNP3_STATUS_t sendUnconfData(int8u * p_data, int8u dataLen);
  DNP3_STATUS_t resendRequest();

  boolean_t secStationIsReset; /* ref DNP3 9.2.8.1 */
  PSTATE_t state; /* ref DNP3 9.2.8.1 */
  boolean_t NFCB; /* ref DNP3 9.2.8.1 */
  int8u                retryCount;
  int8u                maxRetries;
  int8u                nolinkCnt;
  CDLLHandler        * p_handler;
  IMasterCallback    * p_masterCB;
  int8u              * p_txBuf;
  boolean_t            expectResp;
  int16u               retrFrameLen;
};

#endif /* STACK_FRAME_DLL_DLLPRIMARY_H_ */
