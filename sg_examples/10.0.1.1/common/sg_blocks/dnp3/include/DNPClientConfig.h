/** @file DNPClientConfig.h
 *
 * @brief
 * Header file class representing DNP3 client configuration
 *
 * @details
 * Contains declarations of a class representing DNP3 client configuration
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_MASTER_DNPCLIENTCONFIG_H_
#define STACK_MASTER_DNPCLIENTCONFIG_H_

#include "Basetypes.h"

#define DEF_CLI_OUT_ADDR 102
#define DEF_CLI_MAS_ADDR 101
#define DEF_CLI_RX_TIMEOUT 400
#define DEF_CLI_DLL_RETRIES 3

struct DNPClientConfig {
  DNPClientConfig() {
    outstationAddress = DEF_CLI_OUT_ADDR;
    masterAddress = DEF_CLI_MAS_ADDR;
    keepAliveTimeout = CFG_CLI_KEEP_ALIVE;
    rxTimeout = DEF_CLI_RX_TIMEOUT;
    dllRetries = DEF_CLI_DLL_RETRIES;
  }
  int16u outstationAddress;
  int16u masterAddress;
  int32u keepAliveTimeout;
  int32u rxTimeout;
  int8u dllRetries;

  static DNPClientConfig Default() {
    return DNPClientConfig();
  }
};



#endif /* STACK_MASTER_DNPCLIENTCONFIG_H_ */
