/** @file DLLHandler.h
 *
 * @brief
 * Header file class representing DNP3 Data Link Layer handler
 *
 * @details
 * Contains declarations of a class representing DNP3 Data Link Layer handler
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLHANDLER_H_
#define STACK_FRAME_DLL_DLLHANDLER_H_

#include "Basetypes.h"
#include "DLLPrimary.h"
#include "DLLSecondary.h"
#include "Connection.h"
#include "TranspFunc.h"
#include "NotCopyable.h"
#include "MasterImpl.h"

#if CFG_SECURE_AUTH
#include "SecTranspFunc.h"
#define CFG_TRANSP_FUNC                     CSTranspFunc
#else
#define CFG_TRANSP_FUNC                     CTranspFunc
#endif

enum TIME_SYNC_STATE_T{
  TIME_DELAY_MEASURE        = 0,
  TIME_RECORD,
  TIME_WRITE,
};

class CDLLHandler : NotCopyable {
public:
  CDLLHandler(CConnection * p_connParam, int16u locAddr, int32u KATimeout, int32u rxTimeout, int8u retries, boolean_t isMasterParam, IRespHandler * p_handler);

  // called by app thread
  DNP3_STATUS_t sendFrame(int8u * p_data, int16u len);
  // called by server thread in outstation or app thread in master
  DNP3_STATUS_t receiveFrame(int8u * p_data, int16u len);

  DNP3_STATUS_t handleTimeout();

  DNP3_STATUS_t sendKA();

  /* Master specific */
  boolean_t isReady();
  DNP3_STATUS_t process();
  DNP3_STATUS_t handleReq(CMasterImpl::MASTER_REQ_T * p_req);
  void stopReqTimer();
  void setReqTimeout();

  CConnection * getConn();
  int16u getLocalAddr();
  int32u getKATime();
  void setKATime(int32u t);

  void setRemoteAddr(int16u addr);
  int16u getRemoteAddr();
  boolean_t getIsMaster();
  void setMasterCB(IMasterCallback *p_cb) { primary.setMasterCB(p_cb); }
  CTranspFunc * getTF();

  ~CDLLHandler();
private:
  /* Check if the address is one of DNP3 all station addresses */
  boolean_t isBcast(int16u addr);
  DNP3_STATUS_t handleReqRetries();
  void handleTimeSyncReq(CMasterImpl::MASTER_REQ_T * p_req);

  /* Do not change the order of primary, transpFunc, secondary!*/
  CDLLPrimary       primary;
  CFG_TRANSP_FUNC   transpFunc;
  CDLLSecondary     secondary;
  CConnection     * p_conn;
  int16u            localAddr;
  int16u            remoteAddr;
  int32u            keepAliveTimeout;
  volatile boolean_t keepAliveFlag;
  int16u             keepAliveTimerID;
  HAL_SEM_T          mutex;

  /* Master specific */
  boolean_t          isMaster;
  CMasterImpl::MASTER_REQ_T * p_mReq;
  int32u             reqTimeout;
  int8u              reqSeq;
  boolean_t          reqTimeExceeded;
  int16u             reqTimerID;
  CTimeStamp         currTime;
  CTimeStamp         delayMeasureTime;
  TIME_SYNC_STATE_T  timeSyncState;
  boolean_t          isFirstReq;
};

#endif /* STACK_FRAME_DLL_DLLHANDLER_H_ */
