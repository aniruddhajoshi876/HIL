/** @file DNPServerConfig.h
 *
 * @brief
 * Header file class representing DNP3 server configuration
 *
 * @details
 * Contains declarations of a class representing DNP3 server configuration
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_OUTSTATION_DNPSERVERCONFIG_H_
#define STACK_OUTSTATION_DNPSERVERCONFIG_H_

#include "Basetypes.h"

#define DEF_SRV_OUT_ADDR 102 // TODO move to config
#define DEF_SRV_KEEP_ALIVE_TIMEOUT 2000
#define DEF_SRV_RX_TIMEOUT 400
#define DEF_SRV_DLL_RETRIES 3

struct DNPServerConfig {
  DNPServerConfig() {
    outstationAddress = DEF_SRV_OUT_ADDR;
    keepAliveTimeout = DEF_SRV_KEEP_ALIVE_TIMEOUT;
    rxTimeout = DEF_SRV_RX_TIMEOUT;
    dllRetries = DEF_SRV_DLL_RETRIES;
  }
  int16u outstationAddress;
  int32u keepAliveTimeout;
  int32u rxTimeout;
  int8u dllRetries;

  static DNPServerConfig Default() {
    return DNPServerConfig();
  }
};

#endif /* STACK_OUTSTATION_DNPSERVERCONFIG_H_ */
