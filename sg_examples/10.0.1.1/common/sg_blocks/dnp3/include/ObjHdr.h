/** @file ObjHdr.h
 *
 * @brief
 * Header file class representing DNP3 object header octets
 *
 * @details
 * Contains declarations of a class representing DNP3 object header octets
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_OBJHDR_H_
#define STACK_INCLUDE_OBJHDR_H_

#include "Basetypes.h"
#include "QualFld.h"
#include "RngFld.h"

class CObjHdr {
public:
  CObjHdr();
  CObjHdr(int8u * p_data);

  /* Returns group */
  int8u       getGrp(void) const;
  /* Sets group */
  void        setGrp(int8u grpParam);
  /* Returns variation */
  int8u       getVar(void) const;
  /* Sets variation */
  void        setVar(int8u varParam);
  /* Returns a pointer to the qualifier field object */
  CQualFld *  getQualFld(void);
  /* Returns a pointer to the range field object */
  CRngFld *   getRngFld(void);
  /* Return length of this Object Header */
  int16u      getLength(void);
  /* Sets the data of all members based on the input buffer */
  void        setData(int8u * p_data);
  /* Copies contained data to the buffer */
  void        serialize(int8u * p_buffer);

private:
  int8u      grp; /* Group */
  int8u      var; /* Variation */
  CQualFld   qualFld; /* Qualifier fields */
  CRngFld    rngFld; /* Range fields */
  int16u     length; /* Object Header length */
};



#endif /* STACK_INCLUDE_OBJHDR_H_ */
