/** @file QualFld.h
 *
 * @brief
 * Header file class representing qualifier field octet
 *
 * @details
 * Contains declarations of a class representing qualifier field octet
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_QUALFLD_H_
#define STACK_INCLUDE_QUALFLD_H_

#include "Basetypes.h"

// TODO move into the class ??

typedef enum {
  OBJPFX_NONE       = 0x00, /* No index prefix */
  OBJPFX_IDX_8B     = 0x01, /* 1-octet index prefix */
  OBJPFX_IDX_16B    = 0x02, /* 2-octet index prefix */
  OBJPFX_IDX_32B    = 0x03, /* 4-octet index prefix */
  OBJPFX_SIZE_8B    = 0x04, /* 1-octet object size prefix */
  OBJPFX_SIZE_16B   = 0x05, /* 2-octet object size prefix */
  OBJPFX_SIZE_32B   = 0x06, /* 4-octet object size prefix */
  OBJPFX_RES        = 0x07  /* Reserved */
} OBJECT_PREFX_t;

typedef enum {
  RNG_IDX_8B        = 0x00, /* 1-octet start and stop indexes */
  RNG_IDX_16B       = 0x01, /* 2-octet start and stop indexes */
  RNG_IDX_32B       = 0x02, /* 4-octet start and stop indexes */
  RNG_VA_8B         = 0x03, /* 1-octet start and stop virtual addresses */
  RNG_VA_16B        = 0x04, /* 2-octet start and stop virtual addresses */
  RNG_VA_32B        = 0x05, /* 4-octet start and stop virtual addresses */
  RNG_NONE          = 0x06, /* No range field is used. This implies all values */
  RNG_CNT_8B        = 0x07, /* 1-octet count of objects */
  RNG_CNT_16B       = 0x08, /* 2-octet count of objects */
  RNG_CNT_32B       = 0x09, /* 4-octet count of objects */
  RNG_RES0          = 0x0A, /* Reserved */
  RNG_VFQ           = 0x0B, /* Variable format qualifier, 1 octet count of objects */
  RNG_RES1          = 0x0C, /* Reserved */
  RNG_RES2          = 0x0D, /* Reserved */
  RNG_RES3          = 0x0E, /* Reserved */
  RNG_RES4          = 0x0F, /* Reserved */
} RNG_SPEC_t;

class CQualFld {
public:
  CQualFld();
  CQualFld(OBJECT_PREFX_t, RNG_SPEC_t);

  /* Returns object prefix */
  OBJECT_PREFX_t getObjPfx();
  /* Return range specifier code */
  RNG_SPEC_t getRngSpecCode();
  /* Sets object prefix*/
  CQualFld * setObjPrfx(OBJECT_PREFX_t pfx);
  /* Sets range specifier */
  CQualFld * setRngSpecCode(RNG_SPEC_t rng);
  /* Sets QualFld to value, discards previous data */
  CQualFld* setData(int8u value);
  /* Returns data */
  int8u getData();
  /* Sets the data of all members based on the input buffer */
  void setData(int8u * p_data);

private:
  int8u data;
};

#endif /* STACK_INCLUDE_QUALFLD_H_ */
