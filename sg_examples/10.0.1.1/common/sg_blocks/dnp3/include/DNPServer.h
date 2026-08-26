/** @file DNPServer.h
 *
 * @brief
 * Header file class representing DNP3 server
 *
 * @details
 * Contains declarations of a class representing DNP3 server in outstation
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_DNPSERVER_H_
#define STACK_INCLUDE_DNPSERVER_H_

#include "Basetypes.h"
#include "DLLHandler.h"
#include "hal.h"
#include "DNPServerConfig.h"
#include <memory>

class CDNPServer {
public:
  CDNPServer();
  CDNPServer(DNPServerConfig conf);

  DNP3_STATUS_t init(std::unique_ptr<CConnection> p_conn);

  static HAL_THREAD_FUNCTION(connThread);
  static HAL_THREAD_FUNCTION(srvThread);

  static boolean_t run;

private:
  struct ThreadParams {
    ThreadParams(std::unique_ptr<CConnection> p_c, DNPServerConfig * p_conf) {
      p_conn = std::move(p_c);
      p_config = p_conf;
    }
    std::unique_ptr<CConnection> p_conn;
    DNPServerConfig * p_config;
  };

  
  static int16u activeConnections;
  DNPServerConfig config;
};

#endif /* STACK_INCLUDE_DNPSERVER_H_ */
