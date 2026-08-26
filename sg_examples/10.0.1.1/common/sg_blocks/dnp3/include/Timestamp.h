/** @file Timestamp.h 
 *
 * @brief
 * Header file with definition of timestamp class
 *
 * @details
 * TBD
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */

#ifndef _DNP3_TIMESTAMP_H
#define _DNP3_TIMESTAMP_H

#include "dnp3_config.h"
#include "Basetypes.h"
#include "hal_time.h"

class CTimeStampDNP3 : public CTimeStamp {
public:
  CTimeStampDNP3() : m_mstick(0), m_shift(0) {
    Reset();
  }

  int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off);
  int64u  Get(void);
  void Set(int64u);
  void Reset(void);

  bool operator==(const CTimeStampDNP3& rhs);
  bool operator<(const CTimeStampDNP3& rhs);
protected:
  int32u    m_mstick;                 // value of local milisecond timer since start of application
  int16u    m_shift;                  // adjustment of miliseconds

};

#endif
