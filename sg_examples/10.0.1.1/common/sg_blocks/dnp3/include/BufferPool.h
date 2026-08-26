/** @file BufferPool.h
 *
 * @brief
 * Header file class representing buffer pool
 *
 * @details
 * Contains declarations of a class implementing buffer pool
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_UTILS_BUFFERPOOL_H_
#define STACK_UTILS_BUFFERPOOL_H_

#include "Basetypes.h"

template<int16u poolSize, int32u bufSize>
class CBufferPool {
public:
  CBufferPool() {
    for (int16u idx = 0; idx < poolSize; idx++) {
      used[idx] = false;
    }
  }

  int8u * getBuffer() {
    int8u * p_res = nullptr;
    for (int16u idx = 0; idx < poolSize; idx++) {
      if (used[idx] == false) {
        p_res = buffers[idx];
        used[idx] = true;
        break;
      }
    }
    return p_res;
  }
  void returnBuffer(int8u * p_buf) {
    for (int16u idx = 0; idx < poolSize; idx++) {
      if (p_buf == buffers[idx]) {
        used[idx] = false;
        break;
      }
    }
  }
private:
  int8u buffers[poolSize][bufSize];
  boolean_t used[poolSize];
};

// TODO move to some config

#define BUFFER_CNT                               CFG_MAX_CONNECTIONS
#define TCP_RX_BUFFER_SIZE                       32768
#define TCP_TX_BUFFER_SIZE                       4096
#define SERIAL_RX_BUFFER_SIZE                    32768
#define SERIAL_TX_BUFFER_SIZE                    4096
#define SEC_RX_BUFFER_SIZE                       256
#define SEC_TX_BUFFER_SIZE                       256
#define PRI_TX_BUFFER_SIZE                       300 // TODO calculate more precisely
#define TF_TX_BUFFER_SIZE                        250
#define TF_RX_BUFFER_SIZE                        2049
#define AL_TX_BUFFER_SIZE                        900
#define AL_RX_BUFFER_SIZE                        2048

// TODO move to master?
#define MASTER_REQ_BUFFER_CNT                    10
#define MASTER_REQ_BUFFER_SIZE                   64 // enough??

typedef CBufferPool<BUFFER_CNT, TCP_RX_BUFFER_SIZE>                   TCP_RX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, TCP_TX_BUFFER_SIZE>                   TCP_TX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, SERIAL_RX_BUFFER_SIZE>                SERIAL_RX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, SERIAL_TX_BUFFER_SIZE>                SERIAL_TX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, SEC_RX_BUFFER_SIZE>                   SEC_RX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, SEC_TX_BUFFER_SIZE>                   SEC_TX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, PRI_TX_BUFFER_SIZE>                   PRI_TX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, TF_TX_BUFFER_SIZE>                    TF_TX_BUFFER_POOL_t;
typedef CBufferPool<BUFFER_CNT, TF_RX_BUFFER_SIZE>                    TF_RX_BUFFER_POOL_t;
typedef CBufferPool<MASTER_REQ_BUFFER_CNT, MASTER_REQ_BUFFER_SIZE>    MASTER_REQ_BUFFER_POOL_t;


#endif /* STACK_UTILS_BUFFERPOOL_H_ */
