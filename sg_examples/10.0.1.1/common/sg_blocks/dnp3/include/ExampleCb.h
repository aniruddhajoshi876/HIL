/** @file ExampleCb.h
 *
 * @brief
 * Header file class representing an example implementation of master callback interface
 *
 * @details
 * Contains declarations of a class representing example implementation of master callback interface
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_MASTER_EXAMPLECB_H_
#define STACK_MASTER_EXAMPLECB_H_

#include "IMasterCallback.h"

class CExampleCb : public IMasterCallback {
public:
  virtual void handle(const CObjHdr * p_header, int16u index, CCountPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CFrozenCountPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CCTOPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CCountPoint>& event, boolean_t bUnsol = false) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CBinPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CDBinPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CTimePoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CDelayPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CDBinPoint>& event, boolean_t bUnsol = false) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CAnalogPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CFrozenAnalogPoint& point) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CBinPoint>& event, boolean_t bUnsol = false) override;
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CAnalogPoint>& event, boolean_t bUnsol = false) override;
  virtual void operateStatusCROB(const CObjHdr * p_header, int8u status, boolean_t matchReq, boolean_t isSelect) override;
  virtual void operateStatusAOB(const CObjHdr * p_header, int8u status, boolean_t matchReq, boolean_t isSelect) override;
  virtual void notify(DNP3_NOTIF_t errCode, const char* ps_msg);
};

#endif /* STACK_MASTER_EXAMPLECB_H_ */
