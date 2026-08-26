/** @file DLLFrameCreator.h
 *
 * @brief
 * Header file outgoing Data Link Layer frame creating functionality
 *
 * @details
 * Contains declarations of class(es) which prepare outgoing DNP3 Data Link Layer frames
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLFRAMECREATOR_H_
#define STACK_FRAME_DLL_DLLFRAMECREATOR_H_

#include "Basetypes.h"
#include "DLLHdr.h"

class CDLLFrameCreator {
public:
  CDLLFrameCreator(int8u * p_data, int16u bufLen);

  CDLLHdr *     getHdr();
  void          addUD(int8u * p_data, int8u len);
  int8u *       serialize();
  int16u        getLength();
private:
  int8u *       p_buffer;
  int16u        frameLen;
  int8u         hdrLen; /* Length field of header! */
  int16u        bufferCapacity;
  CDLLHdr       hdr;
  int8u *       p_next;
};


#endif /* STACK_FRAME_DLL_DLLFRAMECREATOR_H_ */
