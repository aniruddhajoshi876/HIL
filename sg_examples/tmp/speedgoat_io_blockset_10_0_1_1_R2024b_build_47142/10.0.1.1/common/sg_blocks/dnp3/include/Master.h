/** @file Master.h
 *
 * @brief
 * Header file for Master class API
 *
 * @details
 * Contains API of DNP3 Master
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_MASTER_MASTER_H_
#define STACK_MASTER_MASTER_H_

#include "IMasterCallback.h"
#include "DNPClient.h"
#include "MasterImpl.h"

/** \brief CMaster contains API of the DNP3 master  */
class CMaster {
public:
  /* CONFIGURATION */

  /** Creates master object used to communicate with outstation
   * @brief Create master object
   * @param p_cb - pointer to callback implementation that shall be called when receiving outstation responses
   * @retval None
  */
  CMaster(IMasterCallback * p_cb = nullptr);

  /** Creates configured master object used to communicate with outstation
   * @brief Create configured master object
   * @param config - DNP client configuration
   * @param p_cb - pointer to callback implementation that shall be called when receiving outstation responses
   * @retval None
  */
  CMaster(DNPClientConfig config, IMasterCallback * p_cb = nullptr);

  /** This function assigns the connection object to master and initializes it
   * @brief Set connection object and start master
   * @param p_conn - pointer to connection object
   * @param maddr  - link layer address of the master
   * @retval Status
  */
  DNP3_STATUS_t setConnAndRun(std::unique_ptr<CConnection> p_conn, int16u maddr = DEF_CLI_MAS_ADDR);

  /* INTEGRITY POLL */

  /** Sends integrity poll to outstation (read classes 0, 1, 2, 3)
   * @brief Perform integrity poll
   * @retval Status
  */
  DNP3_STATUS_t integrityPoll();

  /* READ */

  /** Send read request for all objects of specified group and variation
   * @brief Read all objects
   * @param grp - group
   * @param var - variation
   * @retval Status
  */
  DNP3_STATUS_t readAll(int8u grp, int8u var);

  /** Send read request for range of objects from idxStart to idxStop
   * @brief Read range of objects
   * @param grp - group
   * @param var - variation
   * @param idxStart - start index
   * @param idxStop - stop index
   * @retval Status
  */
  DNP3_STATUS_t readRange(int8u grp, int8u var, int16u idxStart, int16u idxStop);

  /** Send read request for objects with specified classes
   * @brief Read objects by classes
   * @param classes - OR mask of CLASS_T objets
   * @retval Status
  */
  DNP3_STATUS_t readClasses(int8u classes);

  /* WRITE */

  /** Send write request to clear Device Restart Internal Indication bit
   * @brief Clear Device Restart bit
   * @retval Status
  */
  DNP3_STATUS_t clearDeviceRestart();

  /** Send write request with current time to set outstation time
   * @brief Set outstation time - current master HAL time is used
   * @param var - variation type 1/3
   * @retval Status
  */
  DNP3_STATUS_t writeTime(int8u var);

  /** Send delay measure and write time request to set outstation time for serial connection
   *  Send record current time and write time request to set outstation time for LAN connection
   * @brief Update time on outstation - master HAL time is used, and me
   * @param isSerial - true for serial connection
   * @retval Status
  */
  DNP3_STATUS_t syncTime(boolean_t isSerial = false);

#if CFG_CTRL_ENABLED

  /* CONTROL */

  /** Send requests to operate a point with select procedure CROB
   * @brief Operate a point with select CROB
   * @param index - index of the binary point to be operated
   * @param crob - CROB object specifying desired operation
   * @retval Status
  */
  DNP3_STATUS_t selectAndOperateCROB(int16u index, CROB_REQUEST_t &crob);

  /** Send direct operate request on a binary point using CROB
   * @brief Operate a binary point directly using CROB object
   * @param index - index of the binary point to be operated
   * @param crob - CROB object specifying desired operation
   * @param noResp - no response flag
   * @retval Status
  */
  DNP3_STATUS_t directOperateCROB(int16u index, CROB_REQUEST_t &crob, boolean_t noResp);

  /** Send requests to operate a point with select procedure AOB
   * @brief Operate a point with select AOB
   * @param index - index of the analog point to be operated
   * @param var - AOB variation
   * @param aob - value in union matching variation
   * @retval Status
  */
  DNP3_STATUS_t selectAndOperateAOB(int16u index, int8u var, AOB_REQUEST_t &aob);

  /** Send direct operate request on an analog point using AOB
   * @brief Operate a binary point directly using AOB object
   * @param index - index of the analog point to be operated
   * @param var - AOB variation
   * @param aob - value in union matching variation
   * @param noResp - no response flag
   * @retval Status
  */
  DNP3_STATUS_t directOperateAOB(int16u index, int8u var, AOB_REQUEST_t &aob, boolean_t noResp);

#endif /* CFG_CTRL_ENABLED */

  /* FREEZE */

  /** Send freeze request for all points of the group
   * @brief Freeze all points
   * @param grp - group
   * @param clear - clear flag
   * @param noResp - no response flag
   * @retval Status
  */
  DNP3_STATUS_t freezeAll(int8u grp, boolean_t clear, boolean_t noResp);

  /** Send freeze request for a range of points
   * @brief Freeze a range of points
   * @param grp - group
   * @param idxStart - start index
   * @param idxStop - stop index
   * @param clear - clear flag
   * @param noResp - no response flag
   * @retval Status
  */
  DNP3_STATUS_t freezeRange(int8u grp, int16u idxStart, int16u idxStop, boolean_t clear, boolean_t noResp);

  /** Send freeze request for all points of the group
   * @brief Freeze all points
   * @param grp - group
   * @param time - 48-bit time in miliseconds since January 1, 1970
   * @param interval - periodic interval in miliseconds
   * @param noResp - no response flag
   * @retval Status
  */
  DNP3_STATUS_t freezeAllAtTime(int8u grp, int64u time, int32u interval, boolean_t noResp);

  /** Send freeze request for a range of points
   * @brief Freeze a range of points
   * @param grp - group
   * @param idxStart - start index
   * @param idxStop - stop index
   * @param noResp - no response flag
   * @retval Status
  */
  DNP3_STATUS_t freezeRangeAtTime(int8u grp, int16u idxStart, int16u idxStop, int64u time, int32u interval, boolean_t noResp);

  /* RESTART */

  /** Send cold restart request to the outstation
   * @brief Cold restart an outstation
   * @retval Status
  */
  DNP3_STATUS_t coldRestart();

  /** Send warm restart request to the outstation
   * @brief Warm restart an outstation
   * @retval Status
  */
  DNP3_STATUS_t warmRestart();

  /* APPLICATION */

  /** Send a request to initalize all applications in an outstation
   * @brief Initialize all applications
   * @retval Status
  */
  DNP3_STATUS_t initializeApplicationAll();

  /** Send a request to start all applications in an outstation
   * @brief Start all applications
   * @retval Status
  */
  DNP3_STATUS_t startApplicationAll();

  /** Send a request to stop all applications in an outstation
   * @brief Stop all applications
   * @retval Status
  */
  DNP3_STATUS_t stopApplicationAll();

  /* UNSOLICITED */

  /** Send a request to enable unsolicited messages from outstation
   * @brief Enable unsolicited messages
   * @param classes - OR mask of CLASS_T objets
   * @retval Status
  */
  DNP3_STATUS_t enableUnsolicited(int8u classes);

  /** Send a request to disable unsolicited messages from outstation
   * @brief Disable unsolicited messages
   * @param classes - OR mask of CLASS_T objets
   * @retval Status
  */
  DNP3_STATUS_t disableUnsolicited(int8u classes);

  /* OTHER */

  /** Send a request to assign class to all points at outstation
   * @brief Assign class to all points
   * @param grp - group to assign class to
   * @param newClass - class to be assigned
   * @retval Status
  */
  DNP3_STATUS_t assignClassAll(int8u grp, CLASS_t newClass);

  /** Send a request to assign class to a range of points at outstation
   * @brief Assign class to a range of points
   * @param grp - group to assign class to
   * @param idxStart - start index
   * @param idxStop - stop index
   * @param newClass - class to be assigned
   * @retval Status
  */
  DNP3_STATUS_t assignClassRange(int8u grp, int16u idxStart, int16u idxStop, CLASS_t newClass);

  /** Assign user to the current session
   * @brief Assign class to a range of points
   * @param uid - ID of the user (1 - default)
   * @retval DNP3_OK or error code
  */
  DNP3_STATUS_t setUser(int16u uid);

  /** Stop client and disconnect from the outstation
   * @brief Disconnect/Stop client
   * @retval Status
  */
  DNP3_STATUS_t stopClient();

  ~CMaster();

private:
  CMasterImpl * masterImpl;

  /** Send record current time request to outstation
   * @brief Record current time
   * @retval Status
  */
  DNP3_STATUS_t recordCurrentTime();

  /** Send delay measure request to outstation
   * @brief Measure delay
   * @retval Status
  */
  DNP3_STATUS_t delayMeasurement();
};

#endif /* STACK_MASTER_MASTER_H_ */
