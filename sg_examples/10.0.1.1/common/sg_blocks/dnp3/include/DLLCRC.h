/** @file DLLCRC.h
 *
 * @brief
 * Header file class calculating DNP3 CRC octets
 *
 * @details
 * Contains declarations of a class calculating DNP3 CRC octets
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_FRAME_DLL_DLLCRC_H_
#define STACK_FRAME_DLL_DLLCRC_H_

#include "Basetypes.h"

class CDLLCRC {
public:
  CDLLCRC();
  CDLLCRC(int8u * p_data);

  void            setData(int8u * p_data);
  void            setData(int16u dataParam);
  int16u          getData();
  void            serialize(int8u * p_buffer);
  static int16u   calculateCRC(int8u * p_data, int8u len);
private:
  static void     calcCRC4Byte(int8u byte, int16u * p_crc);
  int16u          data; /* LSB first */
};

#endif /* STACK_FRAME_DLL_DLLCRC_H_ */
