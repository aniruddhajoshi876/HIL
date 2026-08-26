/** @file DLLFrameInterpreter.h
 *
 * @brief
 * Header file incoming Data Link Layer frame interpreting functionality
 *
 * @details
 * Contains declarations of class(es) which interpret incoming DNP3
 * Data Link Layer frames
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLFRAMEINTERPRETER_H_
#define STACK_FRAME_DLL_DLLFRAMEINTERPRETER_H_

#include "Basetypes.h"
#include "DLLHdr.h"

class CDLLFrameInterpreter {
public:
  CDLLFrameInterpreter(int8u * p_data);

  CDLLHdr * getHdr();
  int16u getOffset();
  DNP3_STATUS_t validate();
  /* Len is out parameter, set to length of user data block (0-16). CRC is optional out, contains pointer to UD crc */
  int8u * getNextUD(int8u * p_len, int8u ** pp_crc = nullptr);
  int8u getUDLen();
private:
  CDLLHdr hdr;
  int16u parsedUDLen; /* Parsed user data length */
  int8u * p_FUD; /* Pointer to first user data */
  int8u * p_NUD; /* Pointer to next user data */
  int8u udLen; /* User data length */
};

#endif /* STACK_FRAME_DLL_DLLFRAMEINTERPRETER_H_ */
