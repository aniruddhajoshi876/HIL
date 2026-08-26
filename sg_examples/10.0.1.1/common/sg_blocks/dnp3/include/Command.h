/** @file Command.h 
 *
 * @brief
 * Header file command handling functionality
 *
 * @details
 * Contains definition of classe(s) which implement DNP3 command handlers:
 *   read, write, freez, start, stop, enable/disable unsolicited
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */

#if !defined(_DNP3_COMMAND_H_)
#define _DNP3_COMMAND_H_

#include "dnp3_config.h"
#include "Basetypes.h"
#include "SQueue.h"
#include "hal.h"
#include "NotCopyable.h"
#include "IRespHandler.h"

#define INVALID_SEQ                  0xFF

#define APP_CONTROL_BYTE_OFFSET      11

typedef enum {
  DNP3_CMD_CONFIRM                 = 0x00,
  DNP3_CMD_READ                    = 0x01,
  DNP3_CMD_WRITE                   = 0x02,
  DNP3_CMD_SELECT                  = 0x03,
  DNP3_CMD_OPER                    = 0x04,
  DNP3_CMD_DIRECT_OPER             = 0x05,
  DNP3_CMD_DIRECT_OPER_NR          = 0x06,
  DNP3_CMD_IMMED_FREEZ             = 0x07,
  DNP3_CMD_IMMED_FREEZ_NR          = 0x08,
  DNP3_CMD_FREEZ_CLEAR             = 0x09,
  DNP3_CMD_FREEZ_CLEAR_NR          = 0x0A,
  DNP3_CMD_FREEZE_AT_TIME          = 0x0B,
  DNP3_CMD_FREEZE_AT_TIME_NR       = 0x0C,
  DNP3_CMD_COLD_RESTART            = 0x0D,
  DNP3_CMD_WARM_RESTART            = 0x0E,
  DNP3_CMD_INITIALIZE_DATA         = 0x0F,
  DNP3_CMD_INITIALIZE_APPL         = 0x10,
  DNP3_CMD_START_APPL              = 0x11,
  DNP3_CMD_STOP_APPL               = 0x12,
  DNP3_CMD_SAVE_CONFIG             = 0x13,
  DNP3_CMD_ENABLE_UNSOLICITED      = 0x14,
  DNP3_CMD_DISABLE_UNSOLICITED     = 0x15,
  DNP3_CMD_ASSIGN_CLASS            = 0x16,
  DNP3_CMD_DELAY_MEASUREMENT       = 0x17,
  DNP3_CMD_RECORD_CURRENT_TIME     = 0x18,
  DNP3_CMD_OPEN_FILE               = 0x19,
  DNP3_CMD_CLOSE_FILE              = 0x1A,
  DNP3_CMD_DELETE_FILE             = 0x1B,
  DNP3_CMD_GET_FILE_INFO           = 0x1C,
  DNP3_CMD_AUTH_FILE               = 0x1D,
  DNP3_CMD_ABORT_FILE              = 0x1E,
  DNP3_CMD_ACTIVATE_CONFIG         = 0x1F,
  DNP3_CMD_AUTH_REQUEST            = 0x20,
  DNP3_CMD_AUTH_ERROR              = 0x21,
  DNP3_CMD_RESPONSE                = 0x81,
  DNP3_CMD_UNSOLICITED_RESPONSE    = 0x82,
  DNP3_CMD_AUTH_RESPONSE           = 0x83,
  DNP3_CMD_NONE                    = 0xFF
} COMMAND_ID_t;

class CFrameCreator;
class CFrameInterpreter;
#include "FrameInterpreter.h"
#include "FrameCreator.h"
class CTranspFunc;
class COutstation;
class CArray;

typedef struct _REQ_INFO_t {
  CTranspFunc    *p_transp;                      // connection with master
  int8u          seq;
  COMMAND_ID_t   cmd;
  int8u          grp;
  int8u          var;
  CQualFld       qualFld;
  CRngFld        rngFld;
  int32u         objCnt;
  int8u         *data;
  int16u         dataLen;
  int8u          grpLast = 0;
  int16u         idxLast = 0;
} REQ_INFO_t;

typedef struct _EV_CONF_t {
  int16u         timId;
  int8u          grp;
  int8u          ptrIdx;
  int8u          txCnt;
  int8u          seq;
  int8u          flags;
  COMMAND_ID_t   cmd;
} EV_CONF_t;

typedef enum {
  CMD_STATE_IDLE               = 0,
  CMD_STATE_BUSY,
  CMD_STATE_WAIT_CONF,
  CMD_STATE_SEL
} COMMAND_STATE_t;

int8u*  getWrBuf(int16u &len);
void printHex(const int8u *p_out, int l);

class DNP3CommandHdlr : public IRespHandler, public NotCopyable {
public:
  DNP3CommandHdlr() : state(CMD_STATE_IDLE) {
    seqReq = seqResp = INVALID_SEQ;
    init();
  }
  virtual DNP3_STATUS_t handleReq(int8u *p_pdu, int16u pduLen, CTranspFunc * p_tf);
  virtual DNP3_STATUS_t handleCmd(REQ_INFO_t *p_req, CFrameCreator &fcr);
  DNP3_STATUS_t handleReqQueue(CTypeQueue<REQ_INFO_t> &qReq, int8u mask);
  
  virtual ~DNP3CommandHdlr() {};

protected:

  typedef enum {
    ALLCALL_DONT_CONFIRM,
    ALLCALL_SHALL_CONFIRM,
    ALLCALL_OPTIONAL_CONFIRM,
    ALLCALL_NONE
  } ALL_STATION_ADDR_t;

  DNP3_STATUS_t  init(void);
  DNP3_STATUS_t  handleConf(int8u seqNo);
  DNP3_STATUS_t  handleApp(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleAssignClass(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleRead(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleWrite(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleFreez(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleFreezTime(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleRestart(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleRecordCurTime(REQ_INFO_t * p_req, CFrameCreator * p_creator);
#if CFG_UNSOLICITED_ENABLED
  DNP3_STATUS_t  handleUnsolicited(REQ_INFO_t * p_req, CFrameCreator * p_creator);
#endif
  virtual DNP3_STATUS_t  handleControl(REQ_INFO_t * p_req, CFrameCreator * p_creator);
  virtual DNP3_STATUS_t  decodeCtrlReq(CFrameInterpreter*, int8u, REQ_INFO_t*) { return DNP3_OK; }

  DNP3_STATUS_t  decodeGenericReq(CFrameInterpreter *p_fi, CObjHdr *p_objHdr, REQ_INFO_t *p_req);
  DNP3_STATUS_t  decodeAssignClass(CFrameInterpreter *p_fi, CObjHdr *&p_objHdr, REQ_INFO_t *p_req);
  DNP3_STATUS_t  decodeFreezTime(CFrameInterpreter *p_fi, CObjHdr *&p_objHdr, REQ_INFO_t *p_req);
  DNP3_STATUS_t  decodeWriteReq(REQ_INFO_t *p_reqInf, CObjHdr * p_objHdr, CFrameInterpreter * p_fi);

  DNP3_STATUS_t calcRange(REQ_INFO_t* request, int32u& idxStart, int32u& idxStop, int32u& objCnt);
  DNP3_STATUS_t calcRange(int8u grp, CQualFld* p_qual, CRngFld *p_rng, int32u& idxStart, int32u& idxStop, int32u& objCnt);

  void handleASMR(int16u addr);

  COMMAND_STATE_t                      state;
  CSQueue<REQ_INFO_t, CFG_REQ_CNT>        qRequest;                   // queue of pending requests
  CSQueue<REQ_INFO_t, CFG_RD_REQ_CNT>     qRequestRd;                 // queue of pending read requests
  CSQueue<REQ_INFO_t, CFG_EV_REQ_CNT>     qRequestEv;                 // queue of pending event requests
  CSQueue<REQ_INFO_t, CFG_UNSOL_REQ_CNT>  qRequestUnsol;              // queue of pending unsolicited
  EV_CONF_t                            arrToBeConfirmed[CFG_REQ_CNT]; // array of events awaiting confirmation
  COutstation                         *p_os;                          // pointer to the Outstation instance
  int8u                                seqReq;                        // sequence number of the last request
  int8u                                seqResp;                       // sequence number of the last response
  int8u                                seqUnsol;                      // sequence number of the unsolicited message
  boolean_t                            moreFollows;
  boolean_t                            reqInProg;
  boolean_t                            allStMsgRcvd;                  // All Stations Message Received
  ALL_STATION_ADDR_t                   asmrType;                      // All Stations Message Received address type
  HAL_SEM_T                            mutex;
};

#if CFG_CTRL_ENABLED

#define CTRL_EVENT_CNT           16
typedef struct {
  CArray        *p_grp;
  int8u          grp;
  int8u          idx;
} CTRL_EVENT_t;

/** \brief Implements control model functionality (select, operate, direct operate, direct operate no ack) */
class DNP3ControlHdlr : public DNP3CommandHdlr {
public:
  DNP3ControlHdlr() : timIdCtrl(HAL_TIMER_INV), rdCtrEv(0), wrCtrEv(0) {};

  void  reset(void);

protected:
  static HAL_TIMER_FUNCTION(controlTimerHndl);

  virtual DNP3_STATUS_t  handleEvents(void);
  virtual DNP3_STATUS_t  handleControl(REQ_INFO_t * request, CFrameCreator * p_creator);
  virtual DNP3_STATUS_t  decodeCtrlReq(CFrameInterpreter *p_fi, int8u prefixLen, REQ_INFO_t *p_req);
  DNP3_STATUS_t  handleSelect(REQ_INFO_t * request, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleOper(REQ_INFO_t * request, CFrameCreator * p_creator);
  DNP3_STATUS_t  handleDirectOper(REQ_INFO_t * request, CFrameCreator * p_creator);

  int16u           timIdCtrl;
  int8u            arrCtrlData[256];
  CTRL_EVENT_t     arrCtrlEv[CTRL_EVENT_CNT];
  int8u            rdCtrEv;
  int8u            wrCtrEv;
};
#endif

#endif /* STACK_INCLUDE_COMMAND_H_ */
