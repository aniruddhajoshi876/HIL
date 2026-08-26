/** @file RngFld.h
 *
 * @brief
 * Header file class representing range field octets
 *
 * @details
 * Contains declarations of a class representing range field octets
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */


#ifndef STACK_INCLUDE_RNGFLD_H_
#define STACK_INCLUDE_RNGFLD_H_


#include "Basetypes.h"
#include "QualFld.h"

class CRngFld {
public:
  CRngFld();
  CRngFld(int8u * p_data, RNG_SPEC_t rngSpec_);

  /* TODO add get/set methods  with proper handling of data member*/

  /* Returns length of the range field */
  int16u getLength();
  /* Gets start and stop indexes based on range specifier code */
  void getRange(int32u* p_startIdx, int32u* p_stopIdx);
  /* Sets the data of all members based on the input buffer */
  void setData(int8u * p_data, RNG_SPEC_t rngSpec_);
  /* TODO */
  void setIndexes(int8u idxStart, int8u idxStop);
  void setIndexes(int16u idxStart, int16u idxStop);
  void setIndexes(int32u idxStart, int32u idxStop);
  void setCount(int8u count);
  void setCount(int16u count);
  void setCount(int32u count);
  /* Copies contained data to the buffer */
  void serialize(int8u * p_buffer);
private:
  RNG_SPEC_t    rngSpec;
  int8u         data[8];
  int16u        length;
};



#endif /* STACK_INCLUDE_RNGFLD_H_ */
