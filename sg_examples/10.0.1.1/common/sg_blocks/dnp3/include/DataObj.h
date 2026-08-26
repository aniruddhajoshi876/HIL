/** @file DataObj.h
 *
 * @brief
 * Header file class representing DNP3 data object octets
 *
 * @details
 * Contains declarations of a class representing DNP3 data object octets
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_DATAOBJ_H_
#define STACK_INCLUDE_DATAOBJ_H_

#include "Basetypes.h"
#include "Point.h"

int16u getElemSize(int8u grp, int8u var);

class CDataObj {
public:
  CDataObj();
  // TODO param constructor for interpreting
  // getters/setters
  void setPrefix(int32u pfx, int8u pfxLen);
  void setData(CData * p_dataParam, int8u grpParam, int8u varParam);
  void setGrp(int8u grpParam);
  void setVar(int8u varParam);
  CData * getData();
  int8u getGrp();
  int8u getVar();
  int16u getLength();
  void serialize(int8u * p_buffer);
  void serialize(int8u * p_buffer, int8u offset);
  static boolean_t isBPF(int8u grp, int8u var); // Binary Packed Format
private:
  int8u     prefix[4];
  int8u     prefixLen;
  CData   * p_data;
  int8u     grp;
  int8u     var;
};


#endif /* STACK_INCLUDE_DATAOBJ_H_ */
