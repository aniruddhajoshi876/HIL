/** @file FrameCreator.h
 *
 * @brief
 * Header file outgoing frame creating functionality
 *
 * @details
 * Contains declarations of class(es) which prepare outgoing DNP3 frames
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_FRAMECREATOR_H_
#define STACK_INCLUDE_FRAMECREATOR_H_

#include "Basetypes.h"
#include "Command.h"
#include "AppCtrl.h"
#include "IntInd.h"
#include "ObjHdr.h"
#include "DataObj.h"

class CFrameCreator {
public:
  CFrameCreator(int8u *p_data, int16u bufLen, boolean_t masterParam = false, int8u doff = 1);

  CAppCtrl *    getAppCtrl(void);
  COMMAND_ID_t  getFuncCode(void);
  CIntInd *     getIntInd(void);

  DNP3_STATUS_t addObjHdr(CObjHdr& objHdrParam, boolean_t bReset = false);
  DNP3_STATUS_t updateObjHdr(CObjHdr& objHdrParam);

  DNP3_STATUS_t addDataObj(CDataObj& dataObjParam, int16u hdrLen);

  void          setBuffer(int8u *p_buf, int16u len);

  void          setFuncCode(COMMAND_ID_t cmd);

  void          setData(int8u grp, int8u var, int8u qual, CRngFld &rng, int8u *p_data, int16u dataLen);

  /* Logs the frame */
  void          log(void);
  /* Serializes all the objects, prepares the buffer to be sent */
  int8u *       serialize(void);
  /* Returns the length of the frame */
  int16u        getLength(void);
  void          setLength(int16u);

protected:
  int8u*        p_buffer;
  int16u        frameLen;
  int16u        bufferCapacity;
  CAppCtrl      appCtrl;
  COMMAND_ID_t  funcCode;
  CIntInd       intInd;
  int8u *       p_loh;                      // last added object header (if exists)
  int8u *       p_next;
  int8u         offset;
  int8u         dataOff;                    // offset of the APDU in the buffer
  int16u        lastBPFLen;
  boolean_t     isMaster;
};



#endif /* STACK_INCLUDE_FRAMECREATOR_H_ */
