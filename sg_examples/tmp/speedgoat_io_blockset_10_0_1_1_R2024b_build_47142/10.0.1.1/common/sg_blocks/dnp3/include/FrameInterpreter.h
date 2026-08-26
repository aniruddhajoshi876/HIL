/** @file FrameInterpreter.h
 *
 * @brief
 * Header file incoming frame interpreting functionality
 *
 * @details
 * Contains declarations of class(es) which interpret incoming DNP3 frames
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_FRAMEINTERPRETER_H_
#define STACK_INCLUDE_FRAMEINTERPRETER_H_

#include "Basetypes.h"
#include "Command.h"
#include "AppCtrl.h"
#include "IntInd.h"
#include "ObjHdr.h"

class CFrameInterpreter {
public:
  CFrameInterpreter(int8u *p_data, int16u pduLen, boolean_t masterParam = false);

  CAppCtrl *    getAppCtrl();
  COMMAND_ID_t  getFuncCode();
  CIntInd *     getIntInd();
  /* Resets object header iteration to the beginning */
  void          resetObjHdr();
  /* Returns pointer to next object header, nullptr if no more headers */
  CObjHdr *     getNextObjHdr();
  /* Returns pointer to the data object after previously extracted object header */
  int8u *       getDataObjPtr();
  /* Sets pointer to next object header. Used when there are data objects after headers */
  void          setNextObjHdr(int8u * p_NOHParam);
  /* Logs the frame */
  void          log();
protected:
  int16u        pduLen;
  CAppCtrl      appCtrl;
  COMMAND_ID_t  funcCode;
  CObjHdr       objHdr;
  int16u        parsedOHLen; /* Sum of lengths of Object Headers before the next one */
  int8u *       p_FOH; // points to first object header (if exists)
  int8u *       p_NOH; // points to next object header (if exists)
  boolean_t     isMaster;
  CIntInd       intInd;
};

#endif /* STACK_INCLUDE_FRAMEINTERPRETER_H_ */
