/** @file MasterImpl.h
 *
 * @brief
 * Header file for Master class implementation
 *
 * @details
 * Contains definition of Master attributes and member functions
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_MASTER_H_
#define STACK_INCLUDE_MASTER_H_

#include "IMasterCallback.h"
#include "BufferPool.h"
#include "FrameCreator.h"
#include "MasterRespHandler.h"
#include "DNPClient.h"
#include "SQueue.h"

#define CTRL_REQ_CNT              8
#define CTRL_REQ_SIZE            (1 + 2 + CROB_SIZE)

enum M_REQ_TYPE_T{
  REQ_AUTHORIZATION        = 0,
  REQ_DELAY_MEASURE,
  REQ_TIME_RECORD,
  REQ_TIME_WRITE,
  REQ_COMMON
};

/** \brief CMasterImpl contains functionality of the DNP3 master  */
class CMasterImpl {
public:
  struct MASTER_REQ_T {
    int8u    * p_buf;
    int8u      seq;
    int16u     len;
    int8u      uid;
    int8u      retryCnt;
    boolean_t  expectResponse;
    M_REQ_TYPE_T reqType;
  };

  /* CONFIGURATION */
  CMasterImpl(IMasterCallback * p_cb = nullptr);
  CMasterImpl(DNPClientConfig& conf, IMasterCallback * p_cb = nullptr);
  ~CMasterImpl();

  DNP3_STATUS_t setConnAndRun(std::unique_ptr<CConnection> p_conn, int16u maddr = DEF_CLI_MAS_ADDR);

  /* INTEGRITY POLL */
  DNP3_STATUS_t integrityPoll();

  /* READ */
  DNP3_STATUS_t readAll(int8u grp, int8u var);
  DNP3_STATUS_t readRange(int8u grp, int8u var, int16u idxStart, int16u idxStop);
  DNP3_STATUS_t readClasses(int8u classes);

  /* WRITE */
  DNP3_STATUS_t clearDeviceRestart();
  DNP3_STATUS_t writeTime(int8u var);

  /* TIME SYNC */
  DNP3_STATUS_t syncTime(boolean_t isSerial = false);
  DNP3_STATUS_t recordCurrentTime();
  DNP3_STATUS_t delayMeasurement();

#if CFG_CTRL_ENABLED

  /* CONTROL */
  DNP3_STATUS_t selectAndOperateCROB(int16u index, CROB_REQUEST_t &crob);
  DNP3_STATUS_t directOperateCROB(int16u index, CROB_REQUEST_t &crob, boolean_t noResp);
  DNP3_STATUS_t directOperateCROB(int16u index, int8u * crob, boolean_t isSelect = false);
  DNP3_STATUS_t selectAndOperateAOB(int16u index, int8u var, AOB_REQUEST_t &aob);
  DNP3_STATUS_t directOperateAOB(int16u index, int8u var, AOB_REQUEST_t &aob, boolean_t noResp);
  DNP3_STATUS_t directOperateAOB(int8u var, int16u index, int8u * p_aob, int8u aobLen, boolean_t isSelect = false);

#endif /* CFG_CTRL_ENABLED */

  /* FREEZE */
  DNP3_STATUS_t freezeAll(int8u grp, boolean_t clear, boolean_t noResp);
  DNP3_STATUS_t freezeRange(int8u grp, int16u idxStart, int16u idxStop, boolean_t clear, boolean_t noResp);
  DNP3_STATUS_t freezeAllAtTime(int8u grp, int64u time, int32u interval, boolean_t noResp);
  DNP3_STATUS_t freezeRangeAtTime(int8u grp, int16u idxStart, int16u idxStop, int64u time, int32u interval, boolean_t noResp);

  /* RESTART */
  DNP3_STATUS_t coldRestart();
  DNP3_STATUS_t warmRestart();

  /* APPLICATION */
  DNP3_STATUS_t initializeApplicationAll();
  DNP3_STATUS_t startApplicationAll();
  DNP3_STATUS_t stopApplicationAll();

  /* UNSOLICITED */
  DNP3_STATUS_t enableUnsolicited(int8u classes);
  DNP3_STATUS_t disableUnsolicited(int8u classes);

  /* OTHER */
  DNP3_STATUS_t assignClassAll(int8u grp, CLASS_t newClass);
  DNP3_STATUS_t assignClassRange(int8u grp, int16u idxStart, int16u idxStop, CLASS_t newClass);

  /* AUTHENTICATION */
  DNP3_STATUS_t setUser(int16u uid);

  /* INTERFACE */
  MASTER_REQ_T * getRequest();
  void ackRequest(MASTER_REQ_T * p_req);
  IMasterCallback * getCb();
  boolean_t getSelected();
  void setSelected(boolean_t val);
  void ctrlComplete(CFrameCreator fcr, int8u grp, int8u var, int16u len, boolean_t bResp);
  boolean_t verifyCtrlResp(CFrameInterpreter& fi, int8u pfxLen, int16u len);
  void stopClient();
  boolean_t isClientEnabled();

private:
  void sendConfirmation();
  int16u fillCROB(int16u idx, CROB_REQUEST_t &crob);
  int16u fillHeader(CFrameCreator &fcr, int8u grp, int8u var, OBJECT_PREFX_t pfx, RNG_SPEC_t rng,
                    int16u idxStart, int16u idxStop);
  DNP3_STATUS_t sendFrame(CFrameCreator &fcr, boolean_t bResp, int8u rtxCnt = 0, M_REQ_TYPE_T reqType = REQ_COMMON);
  int8u * getBuffer();
  // TODO read/write/select/operate/freeze

  IMasterCallback * p_callback;
  CMasterRespHandler respHandler;
  CDNPClient client;
  int8u nextSEQ;

  MASTER_REQ_BUFFER_POOL_t masterReqBuffers;
  CSQueue<MASTER_REQ_T, 10> requestQueue; // TODO size the same as buffers count

  int8u      userId;
  int8u      arrCtrlReq[CTRL_REQ_CNT * CTRL_REQ_SIZE];
  int16u     offRd;
  int16u     offWr;
  boolean_t  selected;
  HAL_ATOMIC_BOOL runClient;
};

#endif /* STACK_INCLUDE_MASTER_H_ */
