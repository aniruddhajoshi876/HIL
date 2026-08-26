/** @file DataSet.h 
 *
 * @brief
 * Header file DaatSet functionality
 *
 * @details
 * Contains definition of classe(s) which implement DNP3 data sets
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */

typedef struct _DATA_SET_ELEM_t {
  int8u              groupId;
  int16u             index;
} DATA_SET_ELEM_t;

typedef struct _GROUP_2_DESCR_t {
  int8u              grp;
  int8u              descr;
} GROUP_2_DESCR_t;

static const GROUP_2_DESCR_t arrGroup2Descr[] = {
  {1, 0},
  {2, 0},
  {3, 0},
  {4, 0},
  {10, 0},
  {11, 0},
  {12, 0},
  {13, 0},
  {20, 0},
  {21, 0},
  {22, 0},
  {23, 0},
  {30, 0},
  {31, 0},
  {32, 0},
  {33, 0},
  {34, 0},
  {40, 0},
  {41, 0},
  {42, 0},
  {43, 0}
}; 
 
template<int S>
class CDataSet : public CData {
public:
  CDataSet(int32u id) : dsId(id) {
    timeStamp.Reset();
  }

  void SetElems(DATA_SET_ELEM_t *p_elem) {
    for (int16u i = 0; i < S; i++) {
      arrElem[idx] = *p_elem++;
    }
    timeStamp.Reset();
  }

  void SetElem(int8u idx, int8u grp, int16u idxPt) {
    if (S > idx) {
      arrElem[idx].groupId = grp;
      arrElem[idx].index = idxPt;      
    }
    timeStamp.Reset();
  }

  virtual int16u Encode(int8u *p_buf, int8u grp, int8u var, int8u off) = 0;
  
protected:
  int32u                        dsId;
  CTimeStamp                    timeStamp;
  DATA_SET_ELEM_t               arrElem[S];
};
