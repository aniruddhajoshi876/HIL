#include "hal_types.h"

#if !defined(_HAL_TIME_H)
#define _HAL_TIME_H

/** 
 * @brief Structure defining the time stamp format used my the SNTP protocol
*/
struct TIME_STAMP_T {
  int32u seconds;                                /*!< Seconds relative to 0h on 1 January 1900 */ 
  int32u secFraction;                            /*!< The fraction part, in RFC 4330 not specified and ordinarily set to 0 */
};

class CTimeStamp
{

public:
  /* Class default constructor */
  CTimeStamp();

  CTimeStamp(const CTimeStamp&);

  /* Class parametrised constructor */
  CTimeStamp(int32u secEpoch, int32u fractOfsec);

  /* Class destructor */
  virtual ~CTimeStamp();

  /* Comparison operator */
  bool operator==(const CTimeStamp &ts);

  /* Assignment operator */
  virtual CTimeStamp& operator=(const CTimeStamp &ts);

  /* This method is used to set the time */
  virtual void SetTime(int32u epchSec, int32u microSec, boolean_t);

  /* This method is used to obtain the second since epoch time stamp attribute */
  int32u GetSecondSinceEpoch(void) const;

  /* This method is used to obtain the fraction of second time stamp attribute */
  int32u GetFractionOfSecond(void) const;

  /* This method is prints time in a GeneralizedTime format */
  void PrintGenTime(int8u *p_buf);

protected:
  /** The interval in seconds continuously counted from the epoch 1970-01-01 00:00:00 UTC */
  int32u secondSinceEpoch;

  /** Fraction of a second when the value of the Time Stamp has been determined */
  int32u fractionOfSecond;
};

/* This function is used to obtain a Time Stamp containing current system time */
void HAL_GetTime(CTimeStamp&);

/* This function is used to obtain a time stamp structure containing current system time */
void HAL_GetTime(struct TIME_STAMP_T *p_time);

/* Returns 6 bytes - 4 store milliseconds since beginning of the day and 2 store days since 01st Jan 1984 */
void HAL_GetTimeOfDay(int8u tmBuf[]);

/* This function is used to correct the system time */
HAL_STATUS_t HAL_CorrectSystemTime(int32 offset);

#endif
