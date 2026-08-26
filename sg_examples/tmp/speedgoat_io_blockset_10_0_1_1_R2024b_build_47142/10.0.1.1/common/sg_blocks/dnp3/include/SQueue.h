/** @file SQueue.h
 *
 * @brief
 * Header file class representing static size queue
 *
 * @details
 * Contains declarations of a class implementing static size queue
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_UTILS_SQUEUE_H_
#define STACK_UTILS_SQUEUE_H_

#include "Basetypes.h"
#include "hal.h"

/* As this is static size queue Type must be default-constructible */
template<typename T>
class CTypeQueue {
public:
    int16u getSize() { return size; }

    // TODO return copy
    T * pop() {
      T * p_elem = nullptr;

      HAL_SemTake(&mutex);
      if (length > 0) {
        p_elem = &(p_arr[idxT]);
        if (idxT == (size - 1)) {
          idxT = 0;
        }
        else {
          idxT++;
        }
        length--;
      }
      HAL_SemGive(&mutex);
      return p_elem;
    }

    T * popLast() {
      T * p_elem = nullptr;

      HAL_SemTake(&mutex);
      if (length > 0) {
        if (idxH == 0) {
          idxH = size - 1;
        }
        else {
          idxH--;
        }
        length--;
        p_elem = &(p_arr[idxH]);
      }
      HAL_SemGive(&mutex);
      return p_elem;
    }

    T* peek() {
      T * p_elem = nullptr;

      HAL_SemTake(&mutex);
      if (length > 0) {
        p_elem = &(p_arr[idxT]);
      }
      HAL_SemGive(&mutex);
      return p_elem;
    }

    T* peekLast() {
      T * p_elem = nullptr;

      HAL_SemTake(&mutex);
      if (length > 0) {
        if (idxH == 0) {
          p_elem = &(p_arr[size - 1]);
        }
        else {
          p_elem = &(p_arr[idxH - 1]);
        }
      }
      HAL_SemGive(&mutex);
      return p_elem;
    }

    /* Important: uses operator= to copy elements */
    // TODO pass reference
    DNP3_STATUS_t push(T * p_elem) {
      DNP3_STATUS_t   retVal = DNP3_OK;

      HAL_SemTake(&mutex);
      if (length < size) {
        p_arr[idxH] = *p_elem;
        if (idxH == (size - 1)) {
          idxH = 0;
        }
        else {
          idxH++;
        }
        length++;
      }
      else {
        retVal = DNP3_ERR_FULL;
      }
      HAL_SemGive(&mutex);
      return retVal;
    }

    T* next(boolean_t bHead = true, boolean_t bBlock = false) {
      T   *p_next = nullptr;

      HAL_SemTake(&mutex);
      if (length < size) {
        if ( bHead ) {
          // new element will be added to the back of the queue
          p_next = &(p_arr[idxH]);
          if (idxH == (size - 1)) {
            idxH = 0;
          }
          else {
            idxH++;
          }
        }
        else {
          // new element will be added to the front of the queue
          if (idxT == 0) {
            idxT = (size - 1);
          }
          else {
            idxT--;
          }
          p_next = &(p_arr[idxT]);
        }
        length++;
        if ( !bBlock ) HAL_SemGive(&mutex);         // element of the queu
      }
      else {
        HAL_SemGive(&mutex);
      }
      return p_next;
    }

    void release(void) {
      HAL_SemGive(&mutex);
    }

    int16u getLength() {
      return length;
    }

    bool isEmpty() {
      return length == 0;
    }

    bool isFull() {
      return length == size;
    }

protected:
    CTypeQueue() : size(0), length(0) {
      idxH = idxT = 0;
      p_arr = nullptr;
      HAL_SemCreate(&mutex, HAL_SEM_BINARY, 1);
    }

    CTypeQueue(int16u s, T *p_buf) : size(s), length(0) {
      idxH = idxT = 0;
      p_arr = p_buf;
      HAL_SemCreate(&mutex, HAL_SEM_BINARY, 1);
    }

    const int16u    size;

    T              *p_arr;
    int16u          length;
    int16u          idxH;
    int16u          idxT;
    HAL_SEM_T       mutex;
};

template<typename T, int16u S>
class CSQueue : public CTypeQueue<T> {
public:
    CSQueue() : CTypeQueue<T>(S, arrData) {};

protected:
    T         arrData[S];
};

#endif /* STACK_UTILS_SQUEUE_H_ */
