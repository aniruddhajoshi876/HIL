/** @file Connection.h
 *
 * @brief
 * Header file class representing abstract base class for connections
 *
 * @details
 * Contains declarations of a class representing abstract base class for connections
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_CONNECTION_CONNECTION_H_
#define STACK_CONNECTION_CONNECTION_H_

#include "Basetypes.h"
#include "hal.h"
#include <memory>
#include "NotCopyable.h"

#define DNP3_HEADER_LEN         8
#define DNP3_DATA_CHUNK_LEN     16

/** \class CConnection Connection.h
 *  \brief Interface for connections
 *
 * Generic interface for connection classes
 */
class CConnection : NotCopyable {
public:
  CConnection() : BUFFER_SIZE(0) {
    rxLen = 0;
  }

  CConnection(int16u bufSize) : BUFFER_SIZE(bufSize)  {
    rxLen = 0;
  }

  /**
   * Check if connection obj was created succesfully
   * @brief Check if buffers are correctly initialized
   * @return Status of the buffers
   */
  virtual DNP3_STATUS_t isFunctional() = 0;

  /**
   * Initialize connection with the other side
   * @brief Initialize connection
   * @return Status of the connection
   */
  virtual DNP3_STATUS_t connect() = 0;

  /**
   * Disconnect from the other side
   * @brief Disconnect
   * @return Status of the disconnection
   */
  virtual DNP3_STATUS_t disconnect() = 0;

  /**
   * Send data through the connection
   * @brief send data
   * @param p_data - point to the data buffer
   * @param len - length of the data to be sent
   * @return Status
   */
  virtual DNP3_STATUS_t sendFrame(int8u *p_data, int16u len) = 0;

  /**
   * Receive data through the connection
   * @brief receive data
   * @param p_data - output parameter set to buffer with received data
   * @param p_len - output parameter set to length of the received data
   * @param timeout - how long to wait for incoming data
   */
  DNP3_STATUS_t receiveFrame(int8u ** p_data, int16u * p_len, int32u timeout);

  /**
   * Check if there are any incoming connections and handle them
   * @brief Handle incoming connections
   * @return empty pointer if no connections, new connection object if accepted connection
   */
  virtual std::unique_ptr<CConnection> listenForConnections() = 0;

  /**
   * Close server listening for connections
   * @brief Stop listening for connections
   * @return Status
   */
  virtual DNP3_STATUS_t stopListen() = 0;

  /**
   * Open server to listen for incoming connections
   * @brief Start listening for connections
   * @return Status
   */
  virtual DNP3_STATUS_t openServer() = 0;

  /**
   *  Specify whether DNP3 DLL confirmations are used - e.g. false for TCP, true for serial line
   *  @brief Check if confirmations are to be used
   *  @return Use confirmations flag
   */
  virtual boolean_t useConfirmed() = 0;

  /**
   * Virtual destructor base
   */
  virtual ~CConnection() {;}

protected:
  virtual DNP3_STATUS_t receive(int8u * p_data, int16u * p_len, int32u timeout) = 0;

  DNP3_STATUS_t getRefTokenStr(char * ps_res, const char *&ps_tok);

  DNP3_STATUS_t getRefTokenInt(int32u &ires, const char *&ps_tok);

  int16u decodeMsgLen(int8u *p_buf, int16u length);

  boolean_t            isServer;
  int8u              * p_rxBuf;
  int16u               rxLen;
  int8u              * p_txBuf;
  const int16u         BUFFER_SIZE;
};

#endif /* STACK_CONNECTION_CONNECTION_H_ */
