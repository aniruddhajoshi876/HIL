/** @file dnp3_config.h
 *
 * @brief
 * Header file with definition of basic types (points, arrays, events).
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

#ifndef _DNP3_POINT_H
#define _DNP3_POINT_H

#include "dnp3_config.h"
#include "Basetypes.h"
#include "Timestamp.h"
#include "platform.h"
#include "dnp3_endian.h"

extern int8u evOverflowCount;

class CArray;
void notify(CLASS_t evClass, int8u grp, int16u idx, CArray *p_group);

/** \class CData Point.h
 *  \brief CData is a base abstract class for static point and event data
 *
 * This class specifies a set of abstract APIs for setting and reading value of static data point or event obejct
 */
class CData {
public:

  /*! \fn template<class T> DNP3_STATUS_t GetValue(T &val)
   *  \brief Template function for reading value of static data point, generic implementation returns error and specialized
   *         implementations call appropiate virtual function
   *  \param val     - reference to the variable receiving value of dtaa point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type
   */
  template<typename T>
  DNP3_STATUS_t GetValue(T &);

  /*! \fn template<class T> DNP3_STATUS_t SetValue(T &val)
   *  \brief Template function for setting value of static data point, generic implementation returns error and specialized
   *         implementations call appropiate virtual function
   *  \param val     - reference to the variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type
   */
  template<typename T>
  DNP3_STATUS_t SetValue(const T &);

  /*! \fn virtual DNP3_STATUS_t SetValue(int8u, int8u *&p_data, int8u grp = 0, int8u var = 0, int16u idx = 0)
   *  \brief Virtual function for setting value of static data point, based on the content of the message received froim DNP3 master.
   *         Base implmentation calls 'defaultError' and returns DNP3_ERR_PARAM. Specialized implementations must be provided
   *         in deriuved classes.
   *  \param p_data   - pointer to the buffer with the message from DNP3 master
   *  \param grp      - group number
   *  \param var      - variation indicating encoding of the value in the message
   *  \param idx      - index of the static point which value shall be set
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetValue(int8u, int8u *&, int8u grp = 0, int8u var = 0, int16u idx = 0) {
    UNUSEDARG(grp);
    UNUSEDARG(var);
    UNUSEDARG(idx);
    return defaultError("Invalid call");
  }

  /*! \fn virtual DNP3_STATUS_t GetBool(bool &val)
   *  \brief Virtual function for reading boolean value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetBool(bool &) { return defaultError("Invalid call"); }

  /*! \fn virtual DNP3_STATUS_t GetInt8u(int8u &val)
   *  \brief Virtual function for reading unsigned 8 bit intiger value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetInt8u(int8u &) { return defaultError("Invalid call"); }

  /*! \fn virtual DNP3_STATUS_t GetInt16(int16 &val)
   *  \brief Virtual function for reading 16 bit intiger value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetInt16(int16&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t GetInt16u(int16u &val)
   *  \brief Virtual function for reading unsigned 16 bit intiger value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetInt16u(int16u&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t GetInt32(int32 &val)
   *  \brief Virtual function for reading 32 bit intiger value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetInt32(int32&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t GetInt32u(int32u &val)
   *  \brief Virtual function for reading unsigned 32 bit intiger value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetInt32u(int32u&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t GetFloat32(float32 &val)
   *  \brief Virtual function for reading 32 bit float value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetFloat32(float32&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t GetDouble64(double64 &val)
   *  \brief Virtual function for reading 64 bit float value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t GetDouble64(double64&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetBool(const bool &val)
   *  \brief Virtual function for setting boolean value. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetBool(const bool&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetInt8u(const int8u &val)
   *  \brief Virtual function for setting unsigned 8 bit integer. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetInt8u(const int8u&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetInt16(const int16 &val)
   *  \brief Virtual function for setting 16 bit integer. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetInt16(const int16&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetInt16u(const int16u &val)
   *  \brief Virtual function for setting unsigned 16 bit integer. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetInt16u(const int16u&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetInt32(const int32 &val)
   *  \brief Virtual function for setting 32 bit integer. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetInt32(const int32&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetInt32u(const int32u &val)
   *  \brief Virtual function for setting unsigned 32 bit integer. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetInt32u(const int32u&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetFloat32(const float32 &val)
   *  \brief Virtual function for setting 32 bit floatting-point number. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetFloat32(const float32&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetDouble64(const double64 &val)
   *  \brief Virtual function for setting 64 bit floatting-point number. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetDouble64(const double64&) { return defaultError("Invalid call\n"); }

  /*! \fn virtual DNP3_STATUS_t SetString(const char* ps_val)
   *  \brief Virtual function for setting string. Base implmentation calls 'defaultError'
   *         and returns DNP3_ERR_PARAM. Specialized implementations must be provided in deriuved classes.
   *  \param ps_val     - new value to be set for data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetString(const char*) { return defaultError("Invalid call\n"); }

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Pure virtual function for encoding value of point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indication how the value shall be encoded
   *  \param off      - offset within the bufffer used when encoding some types/variations (e.g. binary packed).
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off) = 0;

  virtual int16u GetIndex(void) { return 0; }

  /*! \fn virtual ~CData()
   *  \brief Virtual destructor of CData class - does nothing.
   */
  virtual ~CData() {};

protected:

  /*! \fn DNP3_STATUS_t defaultError(const char * psErrMsg)
   *  \brief Default error handler, logs error message by calling LOG_error
   *  \param psErrMsg - error message to be logged
   *  \retval DNP3_ERR_PARAM
   */
  DNP3_STATUS_t defaultError(const char * psErrMsg) {
    LOG_error("%s", psErrMsg);
    return DNP3_ERR_PARAM;
  }
};

/** \class CClassedData Point.h
 *  \brief Implements representation of data point class interface: storage and get/set API.
 *
 */
class CClassedData {
public:
  /*! \fn CClassedData()
   *  \brief Default constructor initializes class to CLASS_1
   */
  CClassedData() : dataClass(CLASS_1) {}

  /*! \fn CLASS_t GetClass()
   *  \brief Returns class of data point
   *  \retval value of the class
   */
  CLASS_t GetClass(void) { return dataClass; }

  /*! \fn void SetClass(CLASS_t cl)
   *  \brief Assignes value of the class
   *  \param cl   - new value of the class to be assigned
   *  \retval none
   */
  void SetClass(CLASS_t cl) { dataClass = cl; }

protected:
  /** Storage of event class */
  CLASS_t                       dataClass;
};

/** \class CTimestampedData Point.h
 *  \brief Implements representation time stamp.
 *
 */
class CTimestampedData {
public:
  /*! \fn GetTimestamp(void)
   *  \brief Returns time stampl object
   *  \retval time stamp object
   */
  CTimeStampDNP3 GetTimestamp(void) { return ts; }

  /*! \fn void SetTimestamp(CTimeStampDNP3& tsParam)
   *  \brief Assigns new bvalue of the timestamp
   *  \param tsParam   - new value of the time stamp
   *  \retval none
   */
  void SetTimestamp(CTimeStampDNP3& tsParam) { ts = tsParam; }

protected:
  /** Object storing time stamp value */
  CTimeStampDNP3                ts;
};

/** \class CPoint Point.h
 *  \brief CPoint is a base template class for DNP3 static points of different types
 *
 * This class implements methods for changing value of the static point.
 */
template<class T>
class CPoint : public CData, public CClassedData {
public:
  /*! \fn CPoint()
   *  \brief Default constructor
   */
  CPoint() {};

  /*! \fn CPoint(const T &v)
   *  \brief Constructor initializing value of the point to the specific value
   */
  CPoint(const T &v) : data(v) {};

  /*! \fn ~CPoint()
   *  \brief CPoint destructor.
   */
  ~CPoint() {};


  /*! \fn virtual CPoint& operator=(CPoint &p)
   *  \brief CPoint assignment operator
   *  \param p   - reference to the CPoint object which value shall be assigned
   *  \retval self reference of the point
   */
  virtual CPoint& operator=(CPoint &p) {
    data = p.data;
    return *this;
  }
   /*! \fn void GetValue(CTimeStampDNP3 &val)
   *  \brief Returns value of time stamp
   *  \param val      - reference of the output variable where data value is stored
   *  \retval none
   */
  void GetValue(T &val) { val = data; }

  /*! \fn virtual DNP3_STATUS_t ChangeValue(const T &val)
   *  \brief Checks if new value passed in val argument is different from current
   *         one and if so updates the value of static point
   *  \param val   - reference of the new value
   *  \return DNP3_OK on success
              DNP3_ERR_PARAM in case current value is the same as the new one
  */
  virtual DNP3_STATUS_t ChangeValue(const T &val) {
    DNP3_STATUS_t  res = DNP3_ERR_PARAM;

    if ( !(data == val) ) {
      //Update value of the point
      data = val;
      res = DNP3_OK;
    }
    return res;
  }

  /*! \fn void SetValue(const T &val)
   *  \brief Assigns new value of static point
   *  \param val   - reference of the new value
   *  \return none
  */
  void SetValue(const T &val);

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer used when encoding some types/variations (e.g. binary packed).
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off);

protected:
  /** Member variable storing value of the point */
  T        data;
};

/** \class CBinPoint Point.h
 *  \brief CBinPoint is a class representing binary point.
 *
 * This class implements methods for binary static point access.
 */
class CBinPoint : public CPoint<int8u> {
public:
  /*! \fn CBinPoint()
   *  \brief Default constructor
   */
  CBinPoint() {};

  /*! \fn CBinPoint(const int8u &v)
   *  \param v      - vaue ot be assigned to the binary data point
   *  \brief Constructor initializing value of the binary point to specific value
   */
  CBinPoint(const int8u &v) : CPoint<int8u>(v) {};

  CBinPoint(int8u grp, int8u var, int8u * p_data, int8u offset = 0);
  CBinPoint(int8u grp, int8u var, int8u * p_data, CTimeStampDNP3 * p_ts);

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of binary point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off);

  /*! \fn virtual DNP3_STATUS_t SetValue(int8u, int8u *&p_data, int8u grp = 0, int8u var = 0, int16u idx = 0)
   *  \brief Function setting value of static data point, based on the content of the message received froim DNP3 master.
   *         It is used by command handler module when control operation is performed by DNP3 master
   *  \param p_data   - pointer to the buffer with the message from DNP3 master
   *  \param grp      - group number
   *  \param var      - variation indicating encoding of the value in the message
   *  \param idx      - index of the static point which value shall be set
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetValue(int8u, int8u *&, int8u grp = 0, int8u var = 0, int16u idx = 0);

  virtual DNP3_STATUS_t ChangeValue(const int8u &val);

  /*! \fn virtual DNP3_STATUS_t GetBool(bool &)
   *  \brief Virtual function for reading boolean value of binary point.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetBool(bool &val) { val = (0 != (0xC0 & data)); return DNP3_OK; }

  int8u GetFlags(void) { return (0x3F & data); }

protected:
  /*! \fn virtual DNP3_STATUS_t SetBool(const bool &)
   *  \brief Assignes new boolean value to binary static point`.
   *  \param val     - new value to be set for data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetBool(const bool &val) { data = val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt16(const int16 &)
   *  \brief Assignes 16 bit integer to binary static point by setting it to false when value is 0 and true otherwise
   *  \param val     - integer value to be assigned to binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt16(const int16 &val) { data = (val != 0); return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt16u(const int16u &)
   *  \brief Assignes unsigned 16 bit integer to binary static point by setting it to false when value is 0 and true otherwise
   *  \param val     - integer value to be assigned to binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt16u(const int16u &val) { data = (val != 0); return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt32(const int32 &val)
   *  \brief Assignes 32 bit integer to binary static point by setting it to false when value is 0 and true otherwise
   *  \param val     - integer value to be assigned to binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt32(const int32 &val) { data = (val != 0); return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt32u(const int32u &val)
   *  \brief Assignes unsigned 32 bit integer to binary static point by setting it to false when value is 0 and true otherwise
   *  \param val     - integer value to be assigned to binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt32u(const int32u &val) { data = (val != 0); return DNP3_OK; }
};

/** \class CDBinPoint Point.h
 *  \brief CDBinPoint is a class representing dual binary point.
 *
 * This class implements methods for dual binary static point access.
 */
class CDBinPoint : public CPoint<int8u> {
public:
  /*! \fn CDBinPoint()
   *  \brief Default constructor
   */
  CDBinPoint() {};

  /*! \fn CDBinPoint(const int8u &v)
   *  \param v      - value to be assigned to the binary data point
   *  \brief Constructor initializing value of the binary point to specific value
   */
  CDBinPoint(const int8u &v) : CPoint<int8u>(v) {};
  CDBinPoint(int8u grp, int8u var, int8u * p_data, int8u offset = 0);
  CDBinPoint(int8u grp, int8u var, int8u * p_data, CTimeStampDNP3 * p_ts);

  virtual DNP3_STATUS_t ChangeValue(const int8u &val);

  int8u GetFlags(void) { return (0x3F & data); }

  /*! \fn virtual DNP3_STATUS_t GetInt8u(int8u &val)
   *  \brief Virtual function for reading value of binary point as 8 bit integer.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetInt8u(int8u &val) { val = data; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt8u(const int8u &val)
   *  \brief Assignes unsigned 8 bit integer to double binary static point
   *  \param val     - integer value to be assigned to double binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt8u(const int8u &val) { data = val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt16(const int16 &val)
   *  \brief Assignes 16 bit integer to double binary static point
   *  \param val     - integer value to be assigned to double binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt16(const int16 &val) { data = (int8u)val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt16u(const int16u &val)
   *  \brief Assignes unsigned 16 bit integer to double binary static point
   *  \param val     - integer value to be assigned to double binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt16u(const int16u &val) { data = (int8u)val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt32(const int32 &val)
   *  \brief Assignes 32 bit integer to double binary static point
   *  \param val     - integer value to be assigned to double binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt32(const int32 &val) { data = (int8u)val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt32u(const int32u &val)
   *  \brief Assignes unsigned 32 bit integer to double binary static point
   *  \param val     - integer value to be assigned to double binary data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt32u(const int32u &val) { data = (int8u)val; return DNP3_OK; }

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of binary point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off);
};

/** \class CCROBPoint Point.h
 *  \brief CCROBPoint represents control relay output block point.
 *
 * This class implements control relay output block (CROB) point functionality.
 */
class CCROBPoint : public CPoint<int8u> {
public:
  /*! \fn CCROBPoint()
   *  \brief Default constructor
   */
  CCROBPoint() {};

  /*! \fn CCROBPoint(const int8u &v)
   *  \param v      - value to be assigned to the CROB point
   *  \brief Constructor initializing value of the CROB point to specific value
   */
  CCROBPoint(const int8u &v) : CPoint<int8u>(v) {};

  /*! \fn virtual DNP3_STATUS_t GetInt8u(int8u &val)
   *  \brief Virtual function for reading value of CROB point as 8 bit integer.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetInt8u(int8u &val) { val = data; return DNP3_OK; }

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of CROB point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off);

  /*! \fn virtual DNP3_STATUS_t SetValue(int8u, int8u *&p_data, int8u grp = 0, int8u var = 0, int16u idx = 0)
   *  \brief Function setting value of CROB point, based on the content of the message received froim DNP3 master.
   *         It is used by command handler module when control operation is performed by DNP3 master
   *  \param p_data   - pointer to the buffer with the message from DNP3 master
   *  \param grp      - group number
   *  \param var      - variation indicating encoding of the value in the message
   *  \param idx      - index of the static point which value shall be set
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetValue(int8u, int8u *&, int8u grp = 0, int8u var = 0, int16u idx = 0);

protected:
  /** Time on parameter of the control operation */
  int32u        onTime;
  /** Time off parameter of the control operation */
  int32u        offTime;
  /** numer of cycles binary control shall be executed */
  int8u         count;
  /** status of the control operation */
  int8u         status;
};

class CCountPoint : public CPoint<int32u> {
public:
  /*! \fn CCountPoint()
   *  \brief Default constructor
   */
  CCountPoint() = default;
  CCountPoint(int8u grp, int8u var, int8u * p_data);
  CCountPoint(int8u grp, int8u var, int8u * p_data, CTimeStampDNP3 * p_ts);

  int8u GetFlags(void) { return flags; }

  /*! \fn virtual DNP3_STATUS_t GetInt32(int32 &val)
   *  \brief Virtual function for reading value of counting point as 32 bit integer.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetInt32(int32 &val) { val = data; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t GetInt32u(int32u &val)
   *  \brief Virtual function for reading value of counting point as 32 bit unsigned integer.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetInt32u(int32u &val) { val = data; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt16(const int16 &val)
   *  \brief Assignes 16 bit integer to counting static point
   *  \param val     - integer value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt16(const int16 &val) { data = val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt16u(const int16u &val)
   *  \brief Assignes unsigned 16 bit integer to counting static point
   *  \param val     - integer value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt16u(const int16u &val) { data = val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt32(const int32 &val)
   *  \brief Assignes  32 bit integer to counting static point
   *  \param val     - integer value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt32(const int32 &val) { data = val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt32u(const int32u &val)
   *  \brief Assignes unsigned 32 bit integer to counting static point
   *  \param val     - integer value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt32u(const int32u &val) { data = val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetFloat32(const float32 &val)
   *  \brief Assignes unsigned 32 bit floating-point value to counting static point by casting it to 32 bit unsigned integer
   *  \param val     - floating-point value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetFloat32(const float32 &val) { data = (int32u)val; return DNP3_OK; }

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of CROB point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off);

  /*! \fn virtual void Incr(void)
   *  \brief Increments value of counting point.
   *  \retval none
   */
  virtual void Incr(void) { (this->data)++; }

protected:
  int8u   step;
  int8u   flags;
};

class CStatsPoint : public CPoint<int32u> {
public:
public:
  /*! \fn CCountPoint()
   *  \brief Default constructor
   */
  CStatsPoint() = default;
  CStatsPoint(int8u grp, int8u var, int8u * p_data);

  void Incr(void) { data++; }
  DNP3_STATUS_t GetVal(int32u &val) { val = data; return DNP3_OK; }
  void SetVal(int32u iv) { data = iv; }

  int16u Encode(int8u *p_buf, int8u grp, int8u var, int16u aid);

protected:
  int8u   flags;
};

/** \class CAnalogPoint Point.h
 *  \brief CAnalogPoint is a class representing analog point.
 *
 * This class implements methods for analo static point access.
 */
class CAnalogPoint : public CPoint<double64> {
public:
  /*! \fn CAnalogPoint()
   *  \brief Default constructor
   */
  CAnalogPoint();
  CAnalogPoint(int8u grp, int8u var, int8u * p_data);
  CAnalogPoint(int8u grp, int8u var, int8u * p_data, CTimeStampDNP3 * p_ts);

  int8u GetFlags(void) { return flags; }

  /*! \fn virtual DNP3_STATUS_t GetInt16(int16 &val)
   *  \brief Virtual function for reading value of analog point as 16 bit integer.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetInt16(int16 &val) { val = (int16)data; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t GetInt32(int32 &val)
   *  \brief Virtual function for reading value of counting point as 32 bit integer.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetInt32(int32 &val) { val = (int32)data; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t GetFloat32(float32 &val)
   *  \brief Virtual function for reading value of counting point as 32 bit floating-point number.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetFloat32(float32 &val) { val = (float32)data; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t GetDouble64(double64 &val)
   *  \brief Virtual function for reading value of counting point as 64 bit floating-point number.
   *  \param val     - reference to the output variable receiving value of data point
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetDouble64(double64 &val) { val = data; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt16(const int16 &val)
   *  \brief Assignes 16 bit integer to analog static point
   *  \param val     - integer value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt16(const int16 &val) { data = (double64)val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetInt32(const int32 &val)
   *  \brief Assignes 32 bit integer to analog static point
   *  \param val     - integer value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetInt32(const int32 &val) { data = (double64)val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetFloat32(const float32 &val)
   *  \brief Assignes 32 bit floating-point number to analog static point
   *  \param val     - floating-point value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetFloat32(const float32 &val) { data = (double64)val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetDouble64(double64 &val)
   *  \brief Assignes 64 bit floating-point number to analog static point
   *  \param val     - floating-point value to be assigned
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t SetDouble64(const double64 &val) { data = val; return DNP3_OK; }

  /*! \fn virtual DNP3_STATUS_t SetValue(int8u, int8u *&p_data, int8u grp = 0, int8u var = 0, int16u idx = 0)
   *  \brief Function setting value of CROB point, based on the content of the message received froim DNP3 master.
   *         It is used by command handler module when control operation is performed by DNP3 master
   *  \param p_data   - pointer to the buffer with the message from DNP3 master
   *  \param grp      - group number
   *  \param var      - variation indicating encoding of the value in the message
   *  \param idx      - index of the static point which value shall be set
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM - function is not supported for given type of static point
   */
  virtual DNP3_STATUS_t SetValue(int8u, int8u *&, int8u grp = 0, int8u var = 0, int16u idx = 0);

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of analog point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off);

  /*! \fn virtual DNP3_STATUS_t ChangeValue(const ChangeValue &val)
   *  \brief Checks if new value passed in val argument is different from current
   *         one and if so updates the value of static point
   *  \param val   - reference of the new value
   *  \return DNP3_OK on success
              DNP3_ERR_PARAM in case current value is the same as the new one
  */
  virtual DNP3_STATUS_t ChangeValue(const double64 &val);

  void SetDeadband(float32);

protected:
  /** Last point value used for generation of events */
  double64   lastVal;
  /** Value of deadband for generation of events */
  float32    dbVal;
  /** Flags: online, restart, communication lost, remote forced, local forced, over range */
  int8u      flags;
  /** Status of the last assignment (control) operation */
  int8u      status;
};

/** \class CTimePoint Point.h
 *  \brief CTimePoint is a class representing time point.
 *
 * This class implements methods for time point access.
 */
class CTimePoint : public CPoint<CTimeStampDNP3> {
public:
  /*! \fn CTimePoint()
   *  \brief Default constructor
   */
  CTimePoint() {
    data.Reset();
    interval = 0;
  }

  /*! \fn CTimePoint(int8u grp, int8u var, int8u * p_data)
   *  \brief Parametrized constructor
   *  \param grp      - group number
   *  \param var      - variation indicating encoding of the value in the buffer
   *  \param p_data   - pointer to the buffer with timestamp value
   */
  CTimePoint(int8u grp, int8u var, int8u * p_data);

  /*! \fn int64u GetEpochMilisec(void)
   *  \brief Returns time elapsed since epoch
   *  \retval number of miliseconds since epoch
   */
  int64u GetEpochMilisec(void) { return data.Get(); }

  /*! \fn void SetInterval(int32u intvl)
   *  \brief Sets interval attribute of DNP3 time stamp
   *  \param intvl      - value of interval in miliseconds
   *  \retval none
   */
  void SetInterval(int32u intvl) { interval = intvl; }

  /*! \fn void RecordTime(void)
   *  \brief Updates the last recorded time-stamp with current time
   *  \retval none
   */
  void RecordTime(void) { lastRecorded.Reset(); }

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of time&data point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off) override {
    int16u len = 0;
    // todo move to cpp
    if (grp == 50) {
      if (var == 0 || var == 1) {
        data.Reset();
        len = data.Encode(p_buf, grp, var, off);
      }
      else if (var == 2) {
        data.Reset();
        len = data.Encode(p_buf, grp, var, off);
        p_buf +=len;
        DNP_HTON32(p_buf, interval);
        len += 4;
      }
      else if (var == 3) {
        len = lastRecorded.Encode(p_buf, grp, var, off);
      }
      else {
        len = 0;
      }
    }
    return len;
  }

protected:
  /** Interval for restarting cyclci timer */
  int32u                        interval;
  /** value of last recorded timestamp */
  CTimeStampDNP3                lastRecorded;
};

/** \class CCTOPoint Point.h
 *  \brief CCTOPoint is a class representing CTO point.
 *
 * This class implements methods for CTO point access.
 */

class CCTOPoint : public CPoint<CTimeStampDNP3> {
public:
  /*! \fn CCTOPoint()
   *  \brief Default constructor
   */
  CCTOPoint() : synchronized(false) {}

  /*! \fn CCTOPoint(int8u grp, int8u var, int8u * p_data)
   *  \brief Parametrized constructor
   *  \param grp      - group number
   *  \param var      - variation indicating encoding of the value in the buffer
   *  \param p_data   - pointer to the buffer with timestamp value
   */
  CCTOPoint(int8u grp, int8u var, int8u * p_data);

  /*! \fn boolean_t GetSynchronized(void)
   *  \brief Returns value of synchronized attribute
   *  \retval value of synchronized (true or false)
   */
  boolean_t GetSynchronized(void) { return synchronized; }

  /*! \fn void SetSynchronized(boolean_t sync)
   *  \brief Sets value of synchronized attribute
   *  \param sync      - value of synchronized
   *  \retval none
   */
  void SetSynchronized(boolean_t sync) { synchronized = sync; }

protected:

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of time&data point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off) override {
    int16u len = 0;
    data.Reset();
    len = data.Encode(p_buf, grp, var, off);
    return len;
  }

  boolean_t                     synchronized;
};

/** \class CDelayPoint Point.h
 *  \brief CDelayPoint is a class representing delay point.
 *
 * This class implements methods for delay point access.
 */
class CDelayPoint : public CPoint<int32u> {
public:
  /*! \fn CDelayPoint()
   *  \brief Default constructor
   */
  CDelayPoint() = default;

  /*! \fn CDelayPoint(int8u grp, int8u var, int8u * p_data)
   *  \brief Parametrized constructor
   *  \param grp      - group number
   *  \param var      - variation indicating encoding of the value in the buffer
   *  \param p_data   - pointer to the buffer with timestamp value
   */
  CDelayPoint(int8u grp, int8u var, int8u * p_data);

  /*! \fn virtual DNP3_STATUS_t SetInt32u(const int32u& val)
   *  \brief Sets value of delay
   *  \param val      - value of delay
   *  \retval none
   */
  virtual DNP3_STATUS_t SetInt32u(const int32u& val) override {
    data =  val;
    return DNP3_OK;
  }

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of time&data point specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off) override {
    int16u  len = 2;
    int16u  sec;

    UNUSEDARG(grp);
    UNUSEDARG(var);
    UNUSEDARG(off);
    if (1 == var) {
      // return delay in seconds
      sec = (data / 1000);
      DNP_HTON16(p_buf, sec);
    }
    else {
      // return delay in miliseconds
      DNP_HTON16(p_buf, data);
    }
    return len;
  }
};

/** \class CEvent Point.h
 *  \brief CEvent is a class representing events generated by changes of the value of static pooints.
 *
 * This class implements methods for generation and retrieval of events.
 */
template<class T>
class CEvent : public CData, public CClassedData, public CTimestampedData {
public:
  /*! \fn CEvent()
   *  \brief Default constructor
   */
  CEvent() = default;
  CEvent(int8u grp, int8u var, int8u * p_data, int16u idxParam) : val(grp, var, p_data, &ts), idx(idxParam) {;}

  /*! \fn virtual void SetValue(int16u ptIdx, T &ptVal, CTimeStampDNP3 *p_ts, CLASS_t evClass)
   *  \brief Updates event object after changing value of a static point
   *  \param ptIdx    - index of the static point which value has changed
   *  \param ptVal    - new value of a static point
   *  \param p_ts     - pointer to a timestamp object
   *  \param evClass  - class of the point which changed the value
   *  \retval none
   */
  virtual void SetValue(int16u ptIdx, T &ptVal, CTimeStampDNP3 *p_ts, CLASS_t evClass) {
    val = ptVal;
    if ( p_ts ) {
      ts = *p_ts;
    }
    else {
      ts.Reset();
    }
    idx = ptIdx;
    dataClass = evClass;
  }

  /*! \fn virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off)
   *  \brief Virtual function for encoding value of event specified by group and variation in the buffer which
   *         will be sent to DNP3 master
   *  \param p_buf    - pointer to the buffer where the encoded value of the point shall be stored
   *  \param grp      - group number
   *  \param var      - variation indicating how the value shall be encoded
   *  \param off      - offset within the bufffer indicating which bit shall be set when vatiation (var) is 1
   *  \retval number of bytes stored in the output buffer
   */
  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off) {
    CData  *p_dat;
    int16u  retLen = 0;

    p_dat = dynamic_cast<CData*>(&val);
    if ( p_dat ) {
      retLen = p_dat->Encode(&(p_buf[0]), grp, var, off);
      retLen += ts.Encode(&(p_buf[retLen]), grp, var, off);
    }
    return retLen;
  }

  /*! \fn T& getPoint(void)
   *  \brief Returns value of static point associated with the event
   *  \retval Refernece to static point object
   */
  T& getPoint(void) {
    return val;
  }

  virtual int16u GetIndex(void) {
    return idx;
  }

protected:
  T              val;
  int16u         idx;
};

/** \class CArray Point.h
 *  \brief CArray is a base class for array of static points and events.
 *
 * This class implements abstract methods for accessing array elements
 */
class CArray {
public:
  /*! \fn CArray()
   *  \brief Default constructor
   *  \param s      - size of array
   */
  CArray(int16u s) : size(s), idxStart(0), idxLast(0), defVar(1) {}

  /*! \fn CData&  operator[](const int16u idx)
   *  \brief Index operator for accessing array members
   *  \param idx      - index of array element
   *  \retval Reference of array element
   */
  CData&       operator[](const int16u);

  /*! \fn virtual int16u GetCount(void)
   *  \brief Returns number of elements in the array
   *  \retval number of elements in the array
   */
  virtual int16u GetCount(void) { return size; }

  /*! \fn virtual int16u GetNext(int16u idx)
   *  \brief Returns index of the next element in the array or INDEX_INVALID
   *  \retval index of the next element in the array
   */
  virtual int16u GetNext(int16u idx) { return ((idx + 1) < size) ? (idx + 1) : INDEX_INVALID; }

  /*! \fn virtual DNP3_STATUS_t GetFirstIdx(int32u &idx)
   *  \brief Returns index of array first element
   *  \param idx      - output parameter receiving index of array first element
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetFirstIdx(int32u &idx) {
    idx = idxStart;
    return DNP3_OK;
  }

  /*! \fn virtual DNP3_STATUS_t GetLastIdx(int32u &idx)
   *  \brief Returns index of array last element
   *  \param idx      - output parameter receiving index of array last element
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetLastIdx(int32u &idx) {
    idx = (size - 1);
    return DNP3_OK;
  }

  int8u GetDefaultVar(void) {
    return defVar;
  }

  void SetDefaultVar(int8u var) {
    defVar = var;
  }

  /*! \fn virtual void RemoveAll(void)
   *  \brief Removes all array elements by setting index of first and last element to 0
   *  \retval none
   */
  virtual void RemoveAll(void) {
    idxStart = idxLast = 0;
  }

  /*! \fn virtual void RemoveFirst(int16u cnt)
   *  \brief Removes first cnt elements
   *  \param cnt      -  number of array elements to remove
   *  \retval none
   */
  virtual void RemoveFirst(int16u cnt) {
    // remove first cnt elements
    while ((0 < cnt) && (idxStart != idxLast)) {
      idxStart = (idxStart + 1) % size;
      cnt--;
    }
  }

  /*! \fn virtual DNP3_STATUS_t RemoveIdx(int16u idx)
   *  \brief Base virtual function for removing specific array element
   *  \param idx      -  index of the lement to be removed from the array
   *  \retval DNP3_ERR_PARAM
   */
  virtual DNP3_STATUS_t RemoveIdx(int16u idx) {
    UNUSEDARG(idx);
    return DNP3_ERR_PARAM;
  }

  /*! \fn ~CArray()
   *  \brief CArray destructor
   */
  virtual ~CArray() {};

protected:

  /*! \fn boolean_t  isValidIdx(int16u idx)
   *  \brief Checks if index passed as a parameter is within the range
   *  \param idx   -  index to verify
   *  \retval true  - index is valid
   *          false - index is out of range
   */
  boolean_t  isValidIdx(int16u idx) {
    if (idx < size) {
      if ((idxStart < idxLast) && (idxStart <= idx) && (idx < idxLast)) {
        return true;
      }
      else if ((idxLast < idxStart) && ((idxStart <= idx) || (idx < idxLast))) {
        return true;
      }
    }
    return false;
  }

  /** Size of the array                      */
  const int16u   size;
  /** Index of first element in the array    */
  int16u         idxStart;
  /** Index of last element in the array     */
  int16u         idxLast;
  /** Defualt variance - used fro generation of unsilicited responces  */
  int8u          defVar;
};

/** \class CGroup Point.h
 *  \brief CGroup is a template class representing concept of DNP3 groups.
 *
 * This class implements functions for accessing points within the group and generating events related to
 * change of the vaoue by static point.
 */
template<class T>
class CGroup : public CArray {
public:
  /*! \fn CGroup(int16u s, int8u grp)
   *  \brief Class constructor
   *  \param s      - size of the group
   *  \param grp    - group id
   */
  CGroup(int16u s, int8u grp) : CArray(s), p_elems((T*)NULL), groupId(grp) {
    elemSize = 0;
  }

  /*! \fn CGroup<T>* GetGroup(int8u grp)
   *  \brief Returns self pointer (this) if group id passed as parameter matches the id of the pobject
   *  \param grp    - group id to be returned
   *  \retval 'this' pointer if grp is the same as group
   *          NULL otherwise
   */
  CGroup<T>* GetGroup(int8u grp) { return (groupId == grp) ? this : (CGroup<T>*)NULL; }

  /*! \fn virtual boolean_t isEvent(void)
   *  \brief Virtual function returning tur if CGroup object represents event group.
   *  \retval False is returned by default implementation.
   */
  virtual boolean_t isEvent(void) { return false; }

  /*! \fn virtual boolean_t isEvent(void)
   *  \brief Virtual function returning tur if CGroup object represents event group.
   *  \retval False is returned by default implementation.
   */
  T* GetObject(int16u idx) { return (idx < size) ? (T*)(((int8u*)p_elems) + (idx * elemSize)) : (T*)NULL; }

  /*! \fn template<typename X> DNP3_STATUS_t ChangePointVal(int16u idx, const X &val, CTimeStampDNP3 *p_ts)
   *  \brief Changes value of the point and generates event the new value different from the current one
   *  \param idx    - index of the static point which changed value
   *  \param val    - new value of the static point
   *  \param p_ts   - pointer to the time-stamp object
   *  \retval DNP3_OK if value of the static point was actually changed
   *          DNP3_ERR_PARAM - new value of the sattic point is the same as the current one
   */
  template<typename X>
  DNP3_STATUS_t ChangePointVal(int16u idx, const X &val, CTimeStampDNP3 *p_ts) {
    DNP3_STATUS_t res = DNP3_ERR_PARAM;

    if (size > idx) {
      CPoint<X>   *p_pt = dynamic_cast<CPoint<X>*>(&p_elems[idx]);
      if (NULL != p_pt) {
        res = p_pt->ChangeValue(val);                  // change static value of the point
        if (DNP3_OK == res) {
          // call virtual update to complete value change  e.g. by generating the event
          GenerateEvent(groupId, idx, p_ts);
        }
      }
      else {
        LOG_error("Failed to change point value - type mismatch\n");
      }
    }
    return res;
  }

  /*! \fn virtual DNP3_STATUS_t GenerateEvent(int8u grp, int16u idx, CTimeStampDNP3 * p_ts)
   *  \brief Virtual function for generating events related to the change of static points.
   *  \param grp    - id of the group which point was changed
   *  \param idx    - index of the static point which changed value
   *  \param p_ts   - pointer to the time-stamp object
   *  \retval DNP3_ERR_PARAM
   */
  virtual DNP3_STATUS_t GenerateEvent(int8u, int16u, CTimeStampDNP3 *) { return DNP3_ERR_PARAM; }

protected:

  /** pointer to the array of elements of the group */
  T        *p_elems;
  /** Identifier of the group                       */
  int8u     groupId;
  /** Size of single lement of the group            */
  int16u    elemSize;
};

/** \class CEventArrayElem Point.h
 *  \brief CEventArrayElem is a template class representing elements of event groups.
 *
 * This class implements functions for accessing events within the event group.
 */
template<class T>
class CEventArrayElem {
public:
  /*! \fn CEventArrayElem()
   *  \brief Default constructor
   */
  CEventArrayElem() : valid(false), prevIdx(INDEX_INVALID), nextIdx(INDEX_INVALID) {}

  /*! \fn T * getElement(void)
   *  \brief Returns pointer to the event element
   *  \retval Pointer to object of CEvent class
   */
  T * getElement(void) { return &element; }

  /*! \fn T * getElement(void)
   *  \brief Returns status of given element of the event group
   *  \retval True if this event elment is valid
              false - givent object does not represent valid element
   */
  boolean_t getValid(void) { return valid; }

  /*! \fn int8u getPrevIdx(void)
   *  \brief Returns index of previous element within event group
   *  \retval index of previus element
   */
  int16u getPrevIdx(void) { return prevIdx; }

  /*! \fn int8u getNextIdx(void)
   *  \brief Returns index of next element within event group
   *  \retval index of next element
   */
  int16u getNextIdx(void) { return nextIdx; }

  /*! \fn void setElement(T& elem)
   *  \brief Assigns CEvent obejct value
   *  \param elem      - reference of the CEvent object
   *  \retval none
   */
  void setElement(T& elem) { element = elem; }

  /*! \fn void setValid(boolean_t v)
   *  \brief Updates validity of given element
   *  \param v      - true / false
   *  \retval none
   */
  void setValid(boolean_t v) { valid = v; }

  /*! \fn void setPrevIdx(int16u pIdx)
   *  \brief Updates value of previus index
   *  \param pIdx      - index of the previus element within the event group
   *  \retval none
   */
  void setPrevIdx(int16u pIdx) { prevIdx = pIdx; }

  /*! \fn void setNextIdx(int16u nIdx)
   *  \brief Updates value of previus index
   *  \param nIdx      - index of the next element within the event group
   *  \retval none
   */
  void setNextIdx(int16u nIdx) { nextIdx = nIdx; }

private:
  /** Object of CEvent class spacialized with the type depending on the static point generating given events */
  T           element;
  /** Flag determining if this is object representing valid event  */
  boolean_t   valid;
  /** Index of the previuos element within the event group         */
  int16u      prevIdx;
  /** Index of the next element within the event group             */
  int16u      nextIdx;
};

/** \class CEventArray Point.h
 *  \brief CEventArray is class implementing event group functionality
 *
 * This class implements functionality related to event groups: removal of events,
 * creation of new events, access of event within the group.
 *
 */
template<class T, unsigned short S>
class CEventArray : public CGroup<CEvent<T>> {
public:
  using ELEM_T = CEventArrayElem<CEvent<T>>;

  /*! \fn CEventArray()
   *  \brief Class constructor
   *  \param grp      - id of the event group
   */
  CEventArray(int8u grp) : CGroup<CEvent<T>>(S, grp) {
    this->p_elems = arrElems[0].getElement();
    this->elemSize = sizeof(CEvent<T>);
    this->causedOverflow = false;
    this->curLen = 0;
    this->RemoveAll();
  }

  /*! \fn virtual CEventArray& operator=(CEventArray &arr_ev)
   *  \brief Virtual asignment operator
   *  \param arr_ev      - reference of the CEventArray object which elements shall be copied to this
   *  \retval reference of this*
   */
  virtual CEventArray& operator=(CEventArray &arr_ev) {
    CEvent<T>  *p_elem;

    p_elem = dynamic_cast<CEvent<T>*>(arr_ev.p_elems);
    if ((NULL != p_elem) && (S == this->size)) {
      for (int16 i = 0; i < this->size; i++) {
        arrElems[i] = arr_ev.arrElems[i];
      }
    }
    return *this;
  }

  /*! \fn virtual void RemoveAll(void)
   *  \brief Removes all event elements from the group
   *  \retval none
   */
  virtual void RemoveAll(void) {
    this->idxStart = this->idxLast = 0;
    curLen = 0;
    for (int16u i = 0; i < this->size; i++) {
      arrElems[i].setValid(false);
      arrElems[i].setNextIdx(INDEX_INVALID);
      arrElems[i].setPrevIdx(INDEX_INVALID);
    }
  }

  /*! \fn virtual void RemoveFirst(int16u cnt)
   *  \brief Removes first cnt event elements from the group
   *  \retval none
   */
  virtual void RemoveFirst(int16u cnt) override {
    CArray::RemoveFirst(cnt);
    if (cnt > 0 && causedOverflow) {
      causedOverflow = false;
      evOverflowCount--;
    }
  }

  /*! \fn virtual int16u GetCount(void)
   *  \brief Returns number of elements in the array
   *  \retval number of elements in the array
   */
  virtual int16u GetCount(void) { return curLen; }

  /*! \fn virtual int16u GetNext(int16u idx)
   *  \brief Returns index of the next element in the array or the same value in case idx is the last one
   *  \retval index of the next element in the array
   */
  virtual int16u GetNext(int16u idx) {
    int16u   n = 0;

    while (n < curLen) {
      if (this->size > idx) idx = arrElems[idx].getNextIdx();
      if (this->size <= idx) break;
      if ( arrElems[idx].getValid() ) return idx;
      n++;
    }
    return INDEX_INVALID;
  }

  /*! \fn virtual DNP3_STATUS_t GetLastIdx(int32u &idx)
   *  \brief Returns index of array last element
   *  \param idx      - output parameter receiving index of array last element
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t GetLastIdx(int32u &idx) {
    idx = this->idxLast;
    return DNP3_OK;
  }

  /*! \fn virtual boolean_t isEvent(void)
   *  \brief SPecialization of the virtual function for CEventArray claa, by definition always returns true.
   *  \retval true
   */
  virtual boolean_t isEvent(void) { return true; }

  /*! \fn virtual void SetValue(int16u idx, T &val, CTimeStampDNP3 *p_ts, CLASS_t evClass)
   *  \brief Updates event object after changing value of a static point
   *  \param idx      - index of the static point which value has changed
   *  \param val      - new value of a static point
   *  \param p_ts     - pointer to a timestamp object
   *  \param evClass  - class of the point which changed the value
   *  \retval none
   */
  DNP3_STATUS_t SetValue(int16u idx, T &val, CTimeStampDNP3 *p_ts, CLASS_t evClass) {
    DNP3_STATUS_t res = DNP3_OK;
    boolean_t overflow = false;
    int16u toInsert = getNext(&overflow);
    arrElems[toInsert].getElement()->SetValue(idx, val, p_ts, evClass);
    arrElems[toInsert].setValid(true);
    arrElems[toInsert].setPrevIdx(this->idxLast);
    if (INDEX_INVALID != this->idxLast) {
      arrElems[this->idxLast].setNextIdx(toInsert);
    }
    this->idxLast = toInsert;

#if CFG_UNSOLICITED_ENABLED
    notify(evClass, this->groupId, toInsert, this);
#endif
    if (overflow) {
      res = DNP3_ERR_FULL;
      if (!causedOverflow) evOverflowCount++;
      causedOverflow = true;
    }
    else {
      if (0 == curLen) this->idxStart = toInsert;
      curLen++;
    }
    return res;
  }

  /*! \fn virtual DNP3_STATUS_t RemoveIdx(int16u idx)
   *  \brief Removes element specified by its index (idx) from event group
   *  \param idx      - index of event element to be removed
   *  \retval DNP3_OK
   */
  virtual DNP3_STATUS_t RemoveIdx(int16u idx) { // TODO order-like idx
    ELEM_T * p_elem = GetElemEvent(idx);
    if (p_elem != nullptr) {
      p_elem->setValid(false);
      int16u prevPtrIdx, nextPtrIdx;
      prevPtrIdx = p_elem->getPrevIdx();
      nextPtrIdx = p_elem->getNextIdx();
      if (prevPtrIdx != INDEX_INVALID) {
        arrElems[prevPtrIdx].setNextIdx(nextPtrIdx);
      }
      if (nextPtrIdx != INDEX_INVALID) {
        arrElems[nextPtrIdx].setPrevIdx(prevPtrIdx);
      }
      if (idx == this->idxLast) {
        this->idxLast = prevPtrIdx;
      }
      if (idx == this->idxStart) {
        if (nextPtrIdx != INDEX_INVALID) {
          this->idxStart = nextPtrIdx;
        }
        else {
          this->idxStart = 0;
        }
      }
      curLen--;
    }
    return DNP3_OK;
  }

  /*! \fn CEvent<T>* GetElem(int16u idx)
   *  \brief Returns pointer to event elment spcified by it index (idx) or NULL if idx is invalid
   *  \param idx      - index of event element to be returned
   *  \retval Pointer to event element (object of CEventArrayElem class) corresponding to index idx.
   *          NULL if index idx is invalid
   */
  CEvent<T>* GetElem(int16u idx) { // TODO different index! order-like idx
    ELEM_T * p_elem = GetElemEvent(idx);
    if (p_elem != nullptr) {
      return p_elem->getElement();
    }
    else {
      return nullptr;
    }
    //return ( CArray::isValidIdx(idx) ) ? &(arrElems[idx]) : (CEvent<T>*)NULL;
  }

protected:

  /*! \fn int16u   getNext(boolean_t * p_overflow)
   *  \brief Returns of the next element within the event group
   *  \param p_overflow      - output parameter receiving overfflow status
   *  \retval Index of next available element within the event group.
   */
  int16u   getNext(boolean_t * p_overflow) {
    static  int8u   dbgFull = 0;
    int16u  i;

    if (curLen == this->size) {
      if (0 == dbgFull) LOG_info("Event buffer full -> dropping one element\n");
      dbgFull = 1;
      *p_overflow = true;
      i = this->idxStart;
      this->idxStart = arrElems[i].getNextIdx();
      arrElems[this->idxStart].setPrevIdx(INDEX_INVALID);
      return i;
    }
    if (1 == dbgFull) LOG_info("Event buffer available\n");
    dbgFull = 0;
    for (i = 0; i < this->size; i++) {
      if (arrElems[i].getValid() == false) {
        return i;
      }
    }
    LOG_error("Invalid event buffer state\n");
    return this->idxLast;
  }

  /*! \fn ELEM_T* GetElemEvent(int16u idx)
   *  \brief Returns pointer to the CEventArrayElem object corresponding the the index idx
   *  \param idx      - index of the group element to be returned
   *  \retval Pointer to the CEventArrayElem object ior NULL if valid element was not found
   */
  ELEM_T* GetElemEvent(int16u idx) { // TODO different index! order-like idx

    if (this->size > idx) {
      if ( arrElems[idx].getValid() ) return (&arrElems[idx]);
    }
    return nullptr;
  }

  /** Array of event group element onbects of class CEventArrayElem */
  ELEM_T                        arrElems[S];
  /** Flag specyfying ststus of overflow condition                  */
  boolean_t                     causedOverflow;
  /** Number of generated events                                    */
  int16u                        curLen;
};

template<class T>
class CFrozenPoint : public T, public CTimestampedData {
public:
  CFrozenPoint() {};

  CFrozenPoint(int8u, int8u, int8u *);

  void assign(T &src) {
    T  *p_pt;

    p_pt = dynamic_cast<T*>(this);
    *p_pt = src;
    ts.Reset();
  }

  int16u Encode(int8u *p_buf, int8u grp, int8u var) {
    return ts.Encode(p_buf, grp, var, 0);
  }

  T* ptr(void) {
    return dynamic_cast<T*>(this);
  }
};

typedef CFrozenPoint<CCountPoint>            CFrozenCountPoint;
typedef CFrozenPoint<CAnalogPoint>           CFrozenAnalogPoint;


/** \class CPointArray Point.h
 *  \brief CPointArray is class implementing static point group functionality
 *
 * This template class implements functionality of static point groups and related freez groups and eventy groups
 * Single object of CPointArray might represent up to 4 DNP3 groups:
 *  - static point, associated events, frozen points and frozen events
 */
/** Array of points of given type T (e.g. CCountPoint<int16u>, CBinPoint, CAnalogPoint<float32>, CAnalogPoint<int32> ) */
template<class C, unsigned short S, unsigned short N, unsigned short SF = 0, unsigned short NF = 0>
class CPointArray : public CGroup<C> {
public:

  /*! \fn CPointArray(int8u grp1, int8u grp2, int8u grp3 = 0, int8u grp4 = 0)
   *  \brief Class constructor
   *  \param grp1      - id of the 'base' static point group
   *  \param grp2      - id of the event group associated with static point group grp1
   *  \param grp3      - id of the frozen group associated with static point group grp1
   *  \param grp4      - id of the frozen event group
   */
  CPointArray(int8u grp1, int8u grp2, int8u grp3 = 0, int8u grp4 = 0) : CGroup<C>(S, grp1), arrEvents(grp2)
#if CFG_ENABLE_FREEZ
                                                                       , arrEventsFreez(grp4)
#endif
  {
    this->p_elems = &(arrElems[0]);
    this->elemSize = sizeof(C);

    arrGrpIds[0] = grp1;
    arrGrpIds[1] = grp2;
    arrGrpIds[2] = grp3;
    arrGrpIds[3] = grp4;
  }

  /*! \fn template<class E> CGroup<E>* GetGroup(int8u grp)
   *  \brief Returns pointer to the CGroup<E> object corresponding to given group id (grp)
   *  \param grp      - id of the group to be returned
   *  \retval Pointer to the group object CGroup<E> object or NULL if not found
   */
  template<class E>
  CGroup<E>* GetGroup(int8u grp) {
    CGroup<E>  *p_grp = (CGroup<E>*)NULL;

    if (grp == arrGrpIds[0]) {
      p_grp = dynamic_cast<CGroup<E>*>(this);
    }
    else if (grp == arrGrpIds[1]) {
      p_grp = dynamic_cast<CGroup<E>*>(&arrEvents);
    }
#if CFG_ENABLE_FREEZ

    else if (grp == arrGrpIds[2]) {
      p_grp = dynamic_cast<CGroup<E>*>(this);
    }
    else if (grp == arrGrpIds[3]) {
      p_grp = dynamic_cast<CGroup<E>*>(&arrEventsFreez);
    }
#endif
    return p_grp;
  }

  /*! \fn CData* GetObject(int8u grp, int16u idx)
   *  \brief Returns pointer to the CData object corresponding to requested point/group
   *  \param grp      - id of the group to be returned
   *  \param idx      - index of the point within the group
   *  \retval Pointer to the top level object representing requested point
   */
  CData* GetObject(int8u grp, int16u idx) {
    CData        *p_dat = NULL;
    const int16u  cntEv = N;       // template parameter N is not used below because it generates compiler warnings
    const int16u  cntFPt = SF;     // template parameter SF is not used below because it generates compiler warnings
    const int16u  cntFEv = NF;     // template parameter NF is not used below because it generates compiler warnings

    if ((grp == arrGrpIds[0]) && (idx < S)) {
      p_dat = &(arrElems[idx]);
    }
    else if ((grp == arrGrpIds[1]) && (idx < cntEv)) {
      p_dat = arrEvents.GetElem(idx);
    }
#if CFG_ENABLE_FREEZ
    else if ((grp == arrGrpIds[2]) && (idx < cntFPt)) {
      p_dat = arrElemsFreez[idx].ptr();
    }
    else if ((grp == arrGrpIds[3]) && (idx < cntFEv)) {
      p_dat = arrEventsFreez.GetElem(idx);
    }
#endif
    return p_dat;
  }

  /*! \fn virtual DNP3_STATUS_t GetFirstIdx(int32u &idx)
   *  \brief Returns index of the first element within the group
   *  \param idx      - input/output parameter, on input its value is the id of fthe group, adn on output index of first available object within the group
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM if requested group was not found
   */
  virtual DNP3_STATUS_t GetFirstIdx(int32u &idx) {
    int32u   grp = idx;                // on input idx contains number of the group
    DNP3_STATUS_t  res = DNP3_ERR_PARAM;

    if (grp == arrGrpIds[0])  {
      // for static point array first element has always index 0
      idx = 0;
      res = DNP3_OK;
    }
    else if (grp == arrGrpIds[1])  {
      res = arrEvents.GetFirstIdx(idx);
    }
#if CFG_ENABLE_FREEZ
    else if (grp == arrGrpIds[2])  {
      idx = 0;
      res = DNP3_OK;
    }
    else if (grp == arrGrpIds[3])  {
      res = arrEventsFreez.GetFirstIdx(idx);
    }
#endif
    return res;
  }

  /*! \fn template<typename T> DNP3_STATUS_t SetPValue(int16u idx, const T &val)
   *  \brief Updates value of specific static point within the group. This function does not generate associated event even if
   *         value of static data point was changed
   *  \param idx      - index of static data point within the group grp1
   *  \param val      - value to be set for static data point
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM if requested element was not found or type mismatch occured
   */
  template<typename T>
  DNP3_STATUS_t SetPValue(int16u idx, const T &val) {
    DNP3_STATUS_t res = DNP3_ERR_PARAM;

    if (S > idx) {
      CPoint<T>   *p_pt = dynamic_cast<CPoint<T>*>(&arrElems[idx]);
      if (NULL != p_pt) {
        res = p_pt->SetValue(val);
      }
      else {
        LOG_error("Failed to update point value - type mismatch\n");
      }
    }
    return res;
  }

  /*! \fn DNP3_STATUS_t Freez(bool bEvents, int16u idx, bool bClear)
   *  \brief Updates value of specific static point within the group. This function does not generate associated event even if
   *         value of static data point was changed
   *  \param bEvents  - flag indicating if static point group shall be frozen (false) or events group (true)
   *  \param idx      - index of specific element to be frozen or INDEX_ALL to freez all emements within the group
   *  \param bClear   - flag indicating if after freezing valuse of static point group shall be reset
   *  \retval DNP3_OK on success
   *          DNP3_ERR_PARAM if requested element was not found
   */
  DNP3_STATUS_t Freez(bool bEvents, int16u idx, bool bClear) {
    DNP3_STATUS_t  res = DNP3_OK;

#if CFG_ENABLE_FREEZ
    if ( bEvents ) {
      if (N == NF) {
        *((CEventArray<C, N>*)&arrEventsFreez) = arrEvents;
      }
      else {
        LOG_error("Freez event buffer size inconsistent with events array %d != %d\n", N, NF);
        res = DNP3_ERR_PARAM;
      }
    }
    else if (INDEX_ALL != idx) {
      if (idx < S) {
        arrElemsFreez[idx].assign(arrElems[idx]);
        if ( bClear ) arrElems[idx].ChangeValue(0);
      }
      else {
        LOG_error("Point index out of range %d >= %d\n", idx, S);
        res = DNP3_ERR_PARAM;
      }
    }
    else if (S <= SF) {
      for (int16u i = 0; i < S; i++) {
        arrElemsFreez[i].assign(arrElems[i]);
        if ( bClear ) arrElems[i].ChangeValue(0);
      }
    }
    else {
      LOG_error("Freez buffer size inconsistent with element array %d > %d\n", S, SF);
      res = DNP3_ERR_PARAM;
    }
#else
  res = DNP3_ERR_NOT_SUPPORTED;
#endif
    return res;
  }

protected:

  /*! \fn virtual DNP3_STATUS_t GenerateEvent(int8u grp, int16u idx, CTimeStampDNP3 *p_ts)
   *  \brief Generates event associated with the update of static data point at index idx
   *  \param grp    - id of the group which point was changed
   *  \param idx      - index of static data point whihc generated the event
   *  \param p_ts     - pointer to time-stamp object related to the time when change was generated
   *  \retval DNP3_OK on success
   *          DNP3_ERR_FULL no space to generate new event
   */
  virtual DNP3_STATUS_t GenerateEvent(int8u grp, int16u idx, CTimeStampDNP3 *p_ts) override {
    (void)grp;
    return (0 < N) ? arrEvents.SetValue(idx, (arrElems[idx]), p_ts, arrElems[idx].GetClass()) : DNP3_ERR_NOT_SUPPORTED;
  }

  /** Array of group identifiers for elements, frozen elements, events and frozen events */
  int8u                    arrGrpIds[4];

  /** Array of static data points; group id: arrGrpIds[0] */
  C                        arrElems[S];
  /**  Array of events associated with array of static data points; group id: arrGrpIds[1] */
  CEventArray<C, N>        arrEvents;
#if CFG_ENABLE_FREEZ
  /** Array of frozen static data points; group id: arrGrpIds[2] */
  CFrozenPoint<C>          arrElemsFreez[SF];
  /** Array of frozen events; group id: arrGrpIds[3] */
  CEventArray<C, NF>       arrEventsFreez;
#endif
};


template<class PT, class CMD, unsigned short S, unsigned short N>
class COutCmdArray : public CPointArray<PT, S, N, 0, 0> {
public:
  COutCmdArray(int8u grp1, int8u grp2, int8u grp3 = 0, int8u grp4 = 0) : CPointArray<PT, S, N, 0, 0>(grp1, grp2, grp3, grp4),
                                                                            arrCmdEvents(grp4)  {
  }

  DNP3_STATUS_t GenerateEvent(int8u grp, int16u idx, CTimeStampDNP3 *p_ts) {
    CLASS_t        cl;
    DNP3_STATUS_t  res = DNP3_ERR_NOT_SUPPORTED;

    if (0 < N) {
      if (grp == this->arrGrpIds[0]) {
        cl = this->arrElems[idx].GetClass();
        res = this->arrEvents.SetValue(idx, (this->arrElems[idx]), p_ts, cl);
      }
      else {
        cl = this->arrOutCmds[idx].GetClass();
        res = arrCmdEvents.SetValue(idx, (arrOutCmds[idx]), p_ts, cl);
      }
    }
    return res;
  }

  template<class E>
  CGroup<E>* GetGroup(int8u grp) {
    CGroup<E>  *p_grp = (CGroup<E>*)NULL;

    if (grp == this->arrGrpIds[0]) {
      p_grp = dynamic_cast<CGroup<E>*>(this);                   // group 10/40 - Bin/Analog Output
    }
    else if (grp == this->arrGrpIds[1]) {
      p_grp = dynamic_cast<CGroup<E>*>(&(this->arrEvents));     // group 11/42 - Bin/Analog Output events
    }
    else if (grp == this->arrGrpIds[2]) {
      p_grp = dynamic_cast<CGroup<E>*>(this);                   // group 12/41 - Bin/Analog Output Command
    }
    else if (grp == this->arrGrpIds[3]) {
      p_grp = dynamic_cast<CGroup<E>*>(&(this->arrCmdEvents));  // group 13/43 - Bin/Analog Output Command Event
    }
    return p_grp;
  }

  CData* GetObject(int8u grp, int16u idx) {
    CData  *p_dat = NULL;

    if ((grp == this->arrGrpIds[0]) && (idx < S)) {
      p_dat = &(this->arrElems[idx]);
    }
    if ((grp == this->arrGrpIds[1]) && (idx < N)) {
      p_dat = this->arrEvents.GetElem(idx);
    }
    else if ((grp == this->arrGrpIds[2]) && (idx < S)) {
      p_dat = &(this->arrOutCmds[idx]);
    }
    else if ((grp == this->arrGrpIds[3]) && (idx < N)) {
      p_dat = this->arrCmdEvents.GetElem(idx);
    }
    return p_dat;
  }

  virtual DNP3_STATUS_t GetFirstIdx(int32u &idx) {
    int32u   grp = idx;                // on input idx contains number of the group
    DNP3_STATUS_t  res = DNP3_ERR_PARAM;

    if ((grp == this->arrGrpIds[0]) || (grp == this->arrGrpIds[2])) {
      // for static point array first element has always index 0
      idx = 0;
      res = DNP3_OK;
    }
    else if (grp == this->arrGrpIds[1])  {
      res = this->arrEvents.GetFirstIdx(idx);
    }
    else if (grp == this->arrGrpIds[3])  {
      res = this->arrCmdEvents.GetFirstIdx(idx);
    }
    return res;
  }

protected:
  CMD                       arrOutCmds[S];
  CEventArray<CMD, N>       arrCmdEvents;
};


/** Array of DNP objects defined by group 0, Variations 211-255s  */
class C2XXArray : public CArray {
public:
  C2XXArray(const GROUP0_VALUE_t *arrGrp0);

  virtual int16u GetCount(void) { return (idxLast + 1); }

  virtual DNP3_STATUS_t GetLastIdx(int32u &idx) {
    idx = idxLast;
    return DNP3_OK;
  }

  CData* GetObject(int16u idx) {

#if CFG_GROUP0_MAX_ELEM
    if (idx >= CFG_GROUP0_MAX_ELEM) {
#else
    {
#endif
      LOG_error("Group:0 index out of range: %d\n", idx);
      return (CData*)NULL;
    }
    return arr2XX[idx];
  }

  template<typename T>
  DNP3_STATUS_t SetValue(int16u idx, const T &val) {
    DNP3_STATUS_t res = DNP3_ERR_PARAM;

    if ((idx < 211) || (idx > (210 + CFG_GROUP0_MAX_ELEM))) {
      LOG_error("Index out of range: %d\n", idx);
    }
    else if (idxLast <= (idx - 211)) {
      LOG_error("Index out of range: %d > %d(configured)\n", idx, (210 + idxLast));
    }
    else {
      arr2XX[idx - 211]->SetValue<T>(val);
      res = DNP3_OK;
    }
    return res;
  }

  template<typename T>
  DNP3_STATUS_t GetValue(int16u idx, T &val) {
    DNP3_STATUS_t res = DNP3_ERR_PARAM;

    if ((idx < 211) || (idx > (210 + CFG_GROUP0_MAX_ELEM))) {
      LOG_error("Index out of range: %d\n", idx);
    }
    else if (idxLast <= (idx - 211)) {
      LOG_error("Index out of range: %d > %d(configured)\n", idx, (210 + idxLast));
    }
    else {
      arr2XX[idx - 211]->GetValue<T>(val);
      res = DNP3_OK;
    }
    return res;
  }

  // TODO Destructor

protected:

  CData*         arr2XX[CFG_GROUP0_MAX_ELEM];
};

#endif  // _DNP3_POINT_H
