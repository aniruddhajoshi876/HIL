/** @file DLLSecondary.h
 *
 * @brief
 * Header file class representing DNP3 Data Link Layer secondary station
 *
 * @details
 * Contains declarations of a class representing DNP3 Data Link Layer secondary station
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLSECONDARY_H_
#define STACK_FRAME_DLL_DLLSECONDARY_H_

#include "Basetypes.h"
#include "DLLFrameInterpreter.h"
#include "TranspFunc.h"
#include "NotCopyable.h"

class CDLLHandler;

class CDLLSecondary : NotCopyable {
  friend class CDLLHandler;
public:
  CDLLSecondary(CDLLHandler * p_handlerParam, CTranspFunc * p_tf);

  DNP3_STATUS_t handleRequest(CDLLFrameInterpreter& fi);

  ~CDLLSecondary();
private:
  typedef enum {
    UnReset,
    Idle
  } SSTATE_t; /* ref DNP3 9.3.2.2 */

  DNP3_STATUS_t sendResponse(CDLLCtrl::DLL_FUN_t funCode);
  DNP3_STATUS_t passToTF(CDLLFrameInterpreter& fi);

  boolean_t linkIsReset; /* ref DNP3 9.2.8.2 */
  SSTATE_t state; /* ref DNP3 9.2.8.2 */
  boolean_t EFCB; /* ref DNP3 9.2.8.2 */
  CDLLHandler * p_handler;
  CTranspFunc * p_transpFunc;
  int8u * p_rxBuf;
  int8u * p_txBuf;

};

#endif /* STACK_FRAME_DLL_DLLSECONDARY_H_ */
