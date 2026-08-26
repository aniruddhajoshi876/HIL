/** @file ConnectionTCP.h
 *
 * @brief
 * Header file class representing TCP connection
 *
 * @details
 * Contains declarations of a class representing TCP connection
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_CONNECTION_CONNECTIONTCP_H_
#define STACK_CONNECTION_CONNECTIONTCP_H_

#include "Connection.h"

class CConnectionTCP : public CConnection {
public:
  /**
   * Creates an object used for TCP connection
   * @brief Create TCP connection object
   * @param isServerParam - specifies if connection is to be used as a server (for outstation) or client (for master)
   * @param ipParam - IP address
   * @portParam - TCP port
   */
  //CConnectionTCP(boolean_t isServerParam = false, int32u ipParam = 0, int16u portParam = 20000);

    CConnectionTCP(boolean_t isServerParam, int32u localIpParam = 0, int16u localPortParam = 20000,
        int32u remoteIpParam = 0, int16u remotePortParam = 20000);

  /**
   * Check if connection obj was created succesfully
   * @brief Check if buffers are correctly initialized
   * @return Status of the buffers
   */
  virtual DNP3_STATUS_t isFunctional() override;

  /**
   * Initialize connection with the other side
   * @brief Initialize connection
   * @return Status of the connection
   */
  virtual DNP3_STATUS_t connect() override;

  /**
   * Disconnect from the other side
   * @brief Disconnect
   * @return Status of the disconnection
   */
  virtual DNP3_STATUS_t disconnect() override;

  /**
   * Send data through the connection
   * @brief send data
   * @param p_data - point to the data buffer
   * @param len - length of the data to be sent
   * @return Status
   */
  virtual DNP3_STATUS_t sendFrame(int8u *p_data, int16u len) override;

  /**
   * Check if there are any incoming connections and handle them
   * @brief Handle incoming connections
   * @return empty pointer if no connections, new connection object if accepted connection
   */
  virtual std::unique_ptr<CConnection> listenForConnections() override;

  /**
   * Close server listening for connections
   * @brief Stop listening for connections
   * @return Status
   */
  virtual DNP3_STATUS_t stopListen() override;

  /**
   * Open server to listen for incoming connections
   * @brief Start listening for connections
   * @return Status
   */
  virtual DNP3_STATUS_t openServer() override;

  /**
   *  Specify whether DNP3 DLL confirmations are used - e.g. false for TCP, true for serial line
   *  @brief Check if confirmations are to be used
   *  @return Use confirmations flag
   */
  virtual boolean_t useConfirmed() override;

  /**
   * Destructor
   */
  virtual ~CConnectionTCP();

protected:
  virtual DNP3_STATUS_t receive(int8u * p_data, int16u * p_len, int32u timeout) override;

  CConnectionTCP(HAL_TCPCHAN_T ch, boolean_t isServerParam = false);

  HAL_TCPCHAN_T        channel;
  int16u localPort;
  int32u localIp;
  int16u remotePort;
  int32u remoteIp;
};

#endif /* STACK_CONNECTION_CONNECTIONTCP_H_ */
