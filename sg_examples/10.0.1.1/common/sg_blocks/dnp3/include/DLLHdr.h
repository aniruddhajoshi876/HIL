/** @file DLLHdr.h
 *
 * @brief
 * Header file class representing DNP3 Data Link Layer header octets
 *
 * @details
 * Contains declarations of a class representing DNP3 Data Link Layer header octets
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLHDR_H_
#define STACK_FRAME_DLL_DLLHDR_H_

#include "Basetypes.h"
#include "DLLCtrl.h"
#include "DLLCRC.h"

#define DLL_HDR_LEN 10
#define DLL_CRC_LEN 2
#define DLL_HDR_LEN_DIFF 5
#define DLL_UD_BLK_LEN 16

class CDLLHdr {
public:
  CDLLHdr();
  CDLLHdr(int8u * p_data);

  int8u *     getStart();
  int8u       getLength();
  CDLLCtrl *  getControl();
  int16u      getDstAddr();
  int16u      getSrcAddr();
  CDLLCRC *   getCRC();

  /* No setStart on purpose */
  void        setLength(int8u lenParam);
  void        setDstAddr(int16u dstParam);
  void        setSrcAddr(int16u srcParam);

  void        setData(int8u * p_data);
  void        serialize(int8u * p_buffer);
private:
  int8u       start[2];
  int8u       length; /* Value of length field, not length of header (always 10)! */
  CDLLCtrl    control;
  int16u      dstAddr;
  int16u      srcAddr;
  CDLLCRC     crc;

};

#endif /* STACK_FRAME_DLL_DLLHDR_H_ */
