/** @file DNPClient.h
 *
 * @brief
 * Header file class representing DNP3 client
 *
 * @details
 * Contains declarations of a class representing DNP3 client in master
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_DNPCLIENT_H_
#define STACK_INCLUDE_DNPCLIENT_H_

#include "Connection.h"
#include "Basetypes.h"
#include "DNPClientConfig.h"
#include "MasterRespHandler.h"
#include <memory>

class CMasterImpl;

class CDNPClient {
public:
  CDNPClient();
  CDNPClient(DNPClientConfig conf);

  ~CDNPClient() {
    close();
  }

  DNP3_STATUS_t init(std::unique_ptr<CConnection> conn, int16u maddr = DEF_CLI_MAS_ADDR);
  void close();

  static HAL_THREAD_FUNCTION(cliThread);

  void setRespHandler(CMasterRespHandler * p_rH) {
    p_respHandler = p_rH;
  }

  void setMaster(CMasterImpl * p_m) {
    p_master = p_m;
  }

private:
  struct ThreadParams {
    ThreadParams(std::unique_ptr<CConnection> p_c, CDNPClient * p_cli);
    std::unique_ptr<CConnection> p_conn;
    CDNPClient                 * p_client;
  };
  HAL_ATOMIC_BOOL        handleOK;
  HAL_THREAD_HANDLE_T    handle;
  DNPClientConfig        config;
  CMasterImpl          * p_master;
  CMasterRespHandler   * p_respHandler;
};

#endif /* STACK_INCLUDE_DNPCLIENT_H_ */
