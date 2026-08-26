/** @file IMasterCallback.h
 *
 * @brief
 * Header file class representing an interface for master callback implementation
 *
 * @details
 * Contains declarations of a class representing an interface for master callback implementation
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_MASTER_IMASTERCALLBACK_H_
#define STACK_MASTER_IMASTERCALLBACK_H_

#include "Point.h"
#include "ObjHdr.h"

typedef enum {
  DNP3_CONN_ON            = 1,
  DNP3_CONN_LOST,
  DNP3_LINK_LOST,
  DNP3_LINK_RESP,
  DNP3_REQ_NORESP
} DNP3_NOTIF_t;

/** \class IMasterCallback IMasterCallback.h
 *  \brief Interface for master callback implementation
 *
 *  Master callbacks need to inherit from this class and implement virtual functions
 */
class IMasterCallback {
public:
  /* POINTS */

  /**
   * This function is called when value of type binary point is received
   * @brief Handle CBinPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CBinPoint& point) = 0;

  /**
   * This function is called when value of type double binary point is received
   * @brief Handle CDBinPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CDBinPoint& point) = 0;

  /**
   * This function is called when value of type counter point is received
   * @brief Handle CCountPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CCountPoint& point) = 0;

  /**
   * This function is called when value of type counter point is received
   * @brief Handle CCountPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CStatsPoint& point) = 0;

  /**
   * This function is called when value of type frozen counter point is received
   * @brief Handle CFrozenCountPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CFrozenCountPoint& point) = 0;

  /**
   * This function is called when value of type analog point is received
   * @brief Handle CAnalogPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CAnalogPoint& point) = 0;

  /**
   * This function is called when value of type frozen analog point is received
   * @brief Handle CFrozenAnalogPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CFrozenAnalogPoint& point) = 0;

  /**
   * This function is called when value of type time point (group 50) is received
   * @brief Handle CTimePoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CTimePoint& point) = 0;

  /**
   * This function is called when value of type delay (group 52) is received
   * @brief Handle CDelayPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CDelayPoint& point) = 0;

  /**
   * This function is called when value of type time CTO (group 51) is received
   * @brief Handle CCTOPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param point - reference to the point object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CCTOPoint& point) = 0;

  /* EVENTS */

  /**
   * This function is called when event with point of type binary point is received
   * @brief Handle event with CBinPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param event - reference to the event object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CBinPoint>& event, boolean_t bUnsol) = 0;

  /**
   * This function is called when event with point of type double binary point is received
   * @brief Handle event with CDBinPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param event - reference to the event object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CDBinPoint>& event, boolean_t bUnsol) = 0;

  /**
   * This function is called when event with point of type counter point is received
   * @brief Handle event with CCountPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param event - reference to the event object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CCountPoint>& event, boolean_t bUnsol) = 0;

  /**
   * This function is called when event with point of type analog point is received
   * @brief Handle event with CAnalogPoint type
   * @param p_header - pointer to header object accompanying the point in response from outstation
   * @param index - point index
   * @param event - reference to the event object
   */
  virtual void handle(const CObjHdr * p_header, int16u index, CEvent<CAnalogPoint>& event, boolean_t bUnsol) = 0;

  /**
     * This function is called when response to operate by CROB response is received
     * @brief Handle CROB response
     * @param p_header - pointer to header object accompanying the point in response from outstation
     * @param status - status byte received
     * @param matchReq - indicates if the response matches the request
     * @param isSelect - indicates if this is a response for select or operate
     */
  virtual void operateStatusCROB(const CObjHdr * p_header, int8u status, boolean_t matchReq, boolean_t isSelect) = 0;

  /**
       * This function is called when response to operate by AOB response is received
       * @brief Handle AOB response
       * @param p_header - pointer to header object accompanying the point in response from outstation
       * @param status - status byte received
       * @param matchReq - indicates if the response matches the request
       * @param isSelect - indicates if this is a response for select or operate
       */
  virtual void operateStatusAOB(const CObjHdr * p_header, int8u status, boolean_t matchReq, boolean_t isSelect) = 0;

  virtual void notify(DNP3_NOTIF_t errCode, const char* ps_msg = NULL) {
    if (nullptr != ps_msg) {
      LOG_error("CODE: %d - %s\n", errCode, ps_msg);
    }
    else {
      LOG_error("CODE  %d\n", errCode);
    }
  }

  /**
   * Virtual destructor base
   */
  virtual ~IMasterCallback() { }
};

#endif /* STACK_MASTER_IMASTERCALLBACK_H_ */
