/** @file Outstation.h
 *
 * @brief
 * Header file for Outstation class
 *
 * @details
 * Contains definition of Outstation attributes and member functions
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */


#if !defined(_DNP3_OUTSTATION_H)
#define _DNP3_OUTSTATION_H

#include "dnp3_config.h"
#include "DeviceConfig.h"
#include "IntInd.h"
#include "TranspFunc.h"

boolean_t isEvent(int8u grp);

typedef struct {
  int16u                 osId;
  const GROUP0_VALUE_t * arrGrp0;
  const int              cntBinPts;
  const int              cntBinEvPts;
  const int              cntDBinPts;
  const int              cntDBinEvPts;
  const int              cntOutBinPts;
  const int              cntOutBinEvPts;
  const int              cntCountPts;
  const int              cntCountEvPts;
  const int              cntAnalogInPts;
  const int              cntAnalogInEvPts;
  const int              cntAnalogOutPts;
  const int              cntAnalogOutEvPts;
} OUTSTATION_CONFIG_t;

#define OS_DEFINE(n, c, t)   COutstationInst<c, t>    n;


class COutstation;

/** \class IOutstationCallback
 *  \brief Interface for outstation callback implementation
 *
 *  Outstation callbacks need to inherit from this class and implement virtual functions
 */
class IOutstationCallback {
  friend class COutstation;
  template<const OUTSTATION_CONFIG_t  &cfg, class CB> friend class COutstationInst;

public:

/*! \fn DNP3_STATUS_t handle_appInit(int8u *p_app, int16u len);
 *   This function shall be called by outstation main function to initialize the values of data points and any other
 *   structures specific for given outstation application. It could be also called in respose to INITIALIZE_APPL(16)
 *   request sent by the DNP3 master.
 *  \brief Callback function initializing outstation application.
 *  \param p_app   - pointer to the name of the application to be initialized
 *  \param len     - length of the application name
 *  \return DNP3_OK on success or error code otherwise
 */
  virtual DNP3_STATUS_t handle_appInit(int8u *p_app, int16u len) {
    UNUSEDARG(p_app);
    UNUSEDARG(len);
    LOG_info("Default callback\n");
    return DNP3_OK;
  }

/*! \fn DNP3_STATUS_t handle_appStart(int8u *p_app, int16u len);
 *   This function is called in respose to START_APPL(17) request sent by the DNP3 master. It shall take the steps necessary
 *   to run the application indicated by p_app parameter.
 *  \brief Callback function indicating start of outstation application.
 *  \param p_app   - pointer to the name of the application to be started
 *  \param len     - length of the application name
 *  \return DNP3_OK on success or error code otherwise
 */
  virtual DNP3_STATUS_t handle_appStart(int8u *p_app, int16u len) {
    UNUSEDARG(p_app);
    UNUSEDARG(len);
    LOG_info("Default callback\n");
    return DNP3_OK;
  }

/*! \fn DNP3_STATUS_t handle_appStop(int8u *p_app, int16u len);
 *   This function is called in respose to STOP_APPL(18) request sent by the DNP3 master. It shall take the steps necessary
 *   to stop the application indicated by p_app parameter.
 *  \brief Callback function indicating stop of outstation application.
 *  \param p_app   - pointer to the name of the application to be stoped
 *  \param len     - length of the application name
 *  \return DNP3_OK on success or error code otherwise
 */
  virtual DNP3_STATUS_t handle_appStop(int8u *p_app, int16u len) {
    UNUSEDARG(p_app);
    UNUSEDARG(len);
    LOG_info("Default callback\n");
    return DNP3_OK;
  }

/*! \fn DNP3_STATUS_t USER_operateBOut(int16u idx, int8u ctrlCode, int8u cnt, int32u timeOn, int32u timeOff);
 *   This function is called in respose to OPERATE(4) or DIRECT_OPERATE(5) request sent by the DNP3 master to control
 *   the value of binary output. It shall implement the control operation specific to the hardware on which outstation
 *   is running.
 *  \brief Callback function handling control operation on binary output.
 *  \param idx      - index of analag output point (group 41)
 *  \param ctrlCode - byte specyfying control operation: pulse (on/off), latch (on/off)
 *  \param cnt      - number of times the outstation shall execute the operation
 *  \param timeOn   - time in miliseconds when output is active
 *  \param timeOff  - time in miliseconds when output is non-active
 *  \return DNP3_OK on success or error code otherwise
 */
  virtual DNP3_STATUS_t handle_operateBOut(int16u idx, int8u ctrlCode, int8u cnt, int32u, int32u) {
    LOG_info("Default callback index:%d ctrl code:%d, count: %d\n", idx, ctrlCode, cnt);
    return DNP3_OK;
  }

/*! \fn DNP3_STATUS_t handle_operateAOut(int16u idx, int8u flags, double64 val);
 *   This function is called in respose to OPERATE(4) or DIRECT_OPERATE(5) request sent by the DNP3 master to control
 *   the value of analog output. It shall implement the control operation specific to the hardware on which outstation
 *   is running.
 *  \brief Callback function handling control operation on analog output.
 *  \param idx     - index of analag output point (group 41)
 *  \param flags   - parameters of the control operation
 *  \param val     - value to be set for analog output point
 *  \return DNP3_OK on success or error code otherwise
 */
  virtual DNP3_STATUS_t handle_operateAOut(int16u idx, int8u flags, double64 val) {
    LOG_info("Default callback index:%d flags:%02x, value:%f\n", idx, flags, val);
    return DNP3_OK;
  }

/*! \fn DNP3_STATUS_t handle_restart(int8u bCold);
 *   This function is called in respose to COLD_RESTART(13) or WARM_RESTART(14) request sent by the DNP3 master. It shall restart
 *   outstation device.
 *  \brief Callback function indicating restart of the outstation.
 *  \param bCold   - parameter indicating if cold (true) or warm(false) restart shall be performed.
 *  \return DNP3_OK on success or error code otherwise
 */
  virtual DNP3_STATUS_t handle_restart(int8u bCold) {
    LOG_info("Default callback - cold = %d\n", bCold);
    return DNP3_OK;
  }

protected:
  IOutstationCallback(COutstation *p_outSt) :  p_os(p_outSt) {
    p_arg = NULL;
  };

  IOutstationCallback() : p_os(nullptr) {
    p_arg = NULL;
  };

  /** Pointer to Outstation object which the callback instance belongs to */
  COutstation       *p_os;
  void              *p_arg;
};

/** \class COutstation COutstation.h
 *  \brief COutstation contains functinality of the DNP3 outstation
 *
 * This class implements functionality of DNP3 outstation. APIs defined within this class allows the application
 * to read or write values of static data points stored in arrays, which are memebers of COutstation class. It also tracks
 * active connections established by DNP3 masters and provides APIs used by command handlers when processing DNP3 requests
 * received from the master.
 *
 */
class COutstation {
friend COutstation* getInstance(int8u grp, CArray *p_grp);

public:
  static COutstation* getInstance(int16u id);
  static COutstation* getInstance(int8u grp, CArray *p_grp);
  static COutstation* getInstance(int8u grp, int16u idx, CData *p_dat);
  static void         closeConn(CTranspFunc *);
  static DNP3_STATUS_t openConn(int16u id, CTranspFunc *);

  /*! \fn COutstation(const GROUP0_VALUE_t *arrGrp0);
   *  \brief Default constructor of COutstation class
   *  \param arrGrp0 - array of group 0 values used for initialization
   *  \return none
   *  Defualt constructor initializes internal data structures. The array of values arrGrp0 is used for initialization of group 0
   *  static points.
   */
  COutstation(const OUTSTATION_CONFIG_t &cfg);

  ~COutstation();

  const OUTSTATION_CONFIG_t& GetConfig(void) { return osCfg; }

  IOutstationCallback* GetCB(void) { return p_cb; }

  /*! \fn int16u GetCount(int8u grp)
   *  \brief Returns number of elements within the group
   *  \param grp     - number of group for which element count shall be returned
   *  \retval number of elements in the array
   */
  int16u GetCount(int8u grp) {
    CArray  *p_array = GetGroup(grp);

    return (NULL == p_array) ? 0 : p_array->GetCount();
  }

  /*! \fn DNP3_STATUS_t GetIndexRange(int8u grp, int32u &idxF, int32u &idxL);
   *  \brief Returns range of point indexes for given group.
   *  \param grp     - number of group for which index range shall be returned
   *  \param idxF    - index of the first point within the group
   *  \param idxL    - index of the last point within the group
   *  \retval DNP3_OK on success,
   *           DNP3_ERR_PARAM - grp parameter is invalid
   *  Defualt constructor initializes internal data structures. The array of values arrGrp0 is used for initialization of group 0
   *  static points.
   */
  DNP3_STATUS_t GetIndexRange(int8u grp, int32u &idxF, int32u &idxL);

  /*! \fn DNP3_STATUS_t Freez(int8u grp, int16u idx, bool bClear);
   *  \brief  used by command handler to freez values of Counter (group 20) or Analog Inut (group 30)
   *  \param grp     - number of group to be frozen
   *  \param idx     - index of the point to freez or INDEX_ALL value
   *  \param bClear  - flag indicating if values of the points shal be cleared (reset) after freezing
   *  \retval DNP3_OK on success,
   *           DNP3_ERR_PARAM - grp parameter is invalid
   *           DNP3_ERR_NOT_SUPPORTED - freez operation is not supported
   */
  virtual DNP3_STATUS_t Freez(int8u grp, int16u idx, bool bClear) = 0;

  /*! \fn int16u GetIndexNext(int8u grp, int16u idx)
   *  \brief Returns index of the next element in the group
   *  \param grp     - number of group for which element count shall be returned
   *  \param idx     - index of the point
   *  \retval index of the next element in the group
   */
  int16u GetIndexNext(int8u grp, int16u idx) {
    CArray  *p_array = GetGroup(grp);

    return (NULL == p_array) ? 0 : p_array->GetNext(idx);
  }

  /*! \fn CArray* GetGroup(int8u grp);
   *  \brief returns pointer to the array holding members of the group indicated by grp parameter
   *  \param grp     - number of group to be returned
   *  \retval pointer the the CArray object representing group specified by grp
   *          NULL - grp parameter is invalid
   */
  CArray* GetGroup(int8u grp);

  /*! \fn CData* GetObject(int8u grp, int16u idx);
   *  \brief returns pointer to the point obbject indicated by group number (grp) and the index (idx)
   *  \param grp     - number of group
   *  \param idx     - index of the point to be reutrned
   *  \retval pointer the the CData object representing point from specific group / index
   *          NULL - either group number (grp) or point (idx) are ivalid
   */
  virtual CData* GetObject(int8u grp, int16u idx) = 0;

  /*! \fn int8u GetDefaultVar(int8u grp);
   *  \brief returns defult variance for give group
   *  \param grp     - number of group
   *  \retval variance number
   */
  int8u GetDefaultVar(int8u grp);

  /*! \fn template<typename T> DNP3_STATUS_t ChangeValue(int8u grp, int16u idx, const T &val, CTimeStampDNP3 *p_ts = (CTimeStampDNP3*)NULL)
   *  \brief used by application to modify value of point within a group
   *  \param grp     - number of group to be frozen
   *  \param idx     - index of the static point
   *  \param val     - new value of the static point to be set
   *  \param p_ts    - ponter to the time stamp object which should be used when generating event related to the change
   *  \retval DNP3_OK on success,
   *          DNP3_ERR_PARAM - group (grp) or point index (idx) are invalid
   *          DNP3_ERR_VALUE new value is the same as current one
   */
  template<typename T>
  DNP3_STATUS_t ChangeValue(int8u grp, int16u idx, const T &val, CTimeStampDNP3 *p_ts = (CTimeStampDNP3*)NULL) {
    CData              *p_dat;
    CPoint<T>          *p_obj;
    CGroup<CPoint<T>>  *p_grp;
    DNP3_STATUS_t   res = DNP3_ERR_PARAM;

    p_dat = (CData*)NULL;
    p_obj = (CPoint<T>*)NULL;
    if (0 == grp) {
      res = arr2XX.SetValue(idx, val);
    }
    else {
      p_grp = reinterpret_cast<CGroup<CPoint<T>>*>( GetGroup(grp) );
      if ( p_grp ) {
        p_dat = p_grp->GetObject(idx);
        if ( p_dat ) {
          // dynamic cast to verify
          p_obj = dynamic_cast< CPoint<T>* >( p_dat );
        }
        if ( p_obj ) {
          res = p_obj->ChangeValue(val);                  // change static value of the point
          if (DNP3_OK == res) {
            CLASS_t eventClass = p_obj->GetClass();
            if ((CLASS_UNKNOWN != eventClass) && (CLASS_0 != eventClass)) {
               res = generateEvent(eventClass, grp, idx, p_grp, p_ts);
            }
          }
        }
      }
    }
    return res;
  }

  /** \brief  used by application to set value of point within a group */

  /*! \fn template<typename T> DNP3_STATUS_t SetValue(int8u grp, int16u idx, const T val, CTimeStampDNP3 *p_ts = (CTimeStampDNP3*)NULL)
   *  \brief used by application to modify value of point within a group
   *  \param grp     - number of group to be frozen
   *  \param idx     - index of the static point
   *  \param val     - new value of the static point to be set
   *  \param p_ts    - ponter to the time stamp object which should be used when generating event related to the change
   *  \retval DNP3_OK on success,
   *          DNP3_ERR_PARAM - group (grp) or point index (idx) are invalid
   */
  template<typename T>
  DNP3_STATUS_t SetValue(int8u grp, int16u idx, const T val, CTimeStampDNP3 *p_ts = (CTimeStampDNP3*)NULL) {
    CData              *p_dat;
    CPoint<T>          *p_obj;
    CGroup<CPoint<T>>  *p_grp;
    DNP3_STATUS_t   res = DNP3_ERR_PARAM;

    p_dat = (CData*)NULL;
    p_obj = (CPoint<T>*)NULL;
    if (0 == grp) {
      res = arr2XX.SetValue(idx, val);
    }
    else {
      p_grp = reinterpret_cast<CGroup<CPoint<T>>*>( GetGroup(grp) );
      if ( p_grp ) {
        p_dat = p_grp->GetObject(idx);
        if ( p_dat ) {
          // dynamic cast to verify
          p_obj = dynamic_cast< CPoint<T>* >( p_dat );
        }
        if ( p_obj ) {
          CLASS_t eventClass = p_obj->GetClass();

          p_obj->SetValue(val);
          if ((NULL != p_ts) && (CLASS_UNKNOWN != eventClass) && (CLASS_0 != eventClass)) {
             res = generateEvent(eventClass, grp, idx, p_grp, p_ts);
          }
          else {
            res = DNP3_OK;
          }
        }
      }
    }
    return res;
  }

  /*! \fn template<typename T> DNP3_STATUS_t GetValue(int8u grp, int16u idx, T &val)
   *  \brief used by application to obtain the value of point within a group
   *  \param grp     - number of group
   *  \param idx     - index of the static point which value shall be returned
   *  \param val     - reference of the output argument where value of the point shall be stored
   *  \retval DNP3_OK on success,
   *          DNP3_ERR_PARAM - group (grp) or point index (idx) are invalid
   */
  template<typename T>
  DNP3_STATUS_t GetValue(int8u grp, int16u idx, T &val) {
    CData  *p_obj;
    DNP3_STATUS_t  res = DNP3_ERR_PARAM;

    if (0 == grp) {
      res = arr2XX.GetValue(idx, val);
    }
    else {
      p_obj = GetObject(grp, idx);
      if (NULL != p_obj) {
        res = p_obj->GetValue<T>(val);
      }
    }
    return res;
  }

  /*! \fn CIntInd * GetIntInd(void)
   *  \brief returns pointer to object of class CIntInd updated with current event information
   *  \retval pointer to object of class CIntInd
   */
  CIntInd * GetIntInd(void) {
    if (class1EventsCount > class1EventsCountTBC) {
      intInd.setBits(CIntInd::CLASS_1_EVENTS);
    }
    else {
      intInd.clearBits(CIntInd::CLASS_1_EVENTS);
    }
    if (class2EventsCount > class2EventsCountTBC) {
      intInd.setBits(CIntInd::CLASS_2_EVENTS);
    }
    else {
      intInd.clearBits(CIntInd::CLASS_2_EVENTS);
     }
    if (class3EventsCount > class3EventsCountTBC) {
      intInd.setBits(CIntInd::CLASS_3_EVENTS);
    }
    else {
      intInd.clearBits(CIntInd::CLASS_3_EVENTS);
    }
    return &intInd;
  }

  void ConfEvents(void) {
    class1EventsCount -= class1EventsCountTBC;
    class2EventsCount -= class2EventsCountTBC;
    class3EventsCount -= class3EventsCountTBC;
    class1EventsCountTBC = 0;
    class2EventsCountTBC = 0;
    class3EventsCountTBC = 0;
  }

  void EventTaken(CLASS_t evClass) {
    switch(evClass) {
      case CLASS_1:
        class1EventsCountTBC++;
        break;
      case CLASS_2:
        class2EventsCountTBC++;
        break;
      case CLASS_3:
        class3EventsCountTBC++;
        break;
      default:
        break;
    }
  }

  int8u GetNextGroup(int8u grp, int8u var);

  /*! \fn DNP3_STATUS_t Reset(void);
   *  \brief reinitializes COutsation object
   *  \retval DNP3_OK
   */
  DNP3_STATUS_t Reset(void);

  /*! \fn  void SetCallbackArg(void *p_x);
   *  \brief sets user defined argument within callback object used to handel events
   *  \param p_x    - pointer to anything defined by the user app; could be referneced in user defined callback functions
   *  \retval none
   */
  void SetCallbackArg(void *p_x) {
    if (nullptr != p_cb) p_cb->p_arg = p_x;
  }

#if CFG_UNSOLICITED_ENABLED
  /*! \fn void UnsolicitedEnable(int8u cmask, void *p_tr);
   *  \brief enables unsolicited messages for DNP3 master
   *  \param cmask   - mask of event classes for which unsolicited messages shall be enabled
   *  \param p_tr    - pointer to transport object representing connection with DNP3 master
   *  \retval none
   */
  int8u UnsolicitedEnable(int8u cmask, void *p_tr);

  /*! \fn void UnsolicitedDisable(int8u cmask, void *p_tr);
   *  \brief disables unsolicited messages for DNP3 master
   *  \param cmask   - mask of event classes for which unsolicited messages shall be disabled
   *  \param p_tr    - pointer to transport object representing connection with DNP3 master
   *  \retval none
   */
  int8u UnsolicitedDisable(int8u cmask, void *p_tr);

  /*! \fn DNP3_STATUS_t UnsolicitedSend(CLASS_t evClass, int8u grp, int16u idx);
   *  \brief called when event is generated to send unsolicited message to DNP3 master
   *  \param evClass - class of the static point which generated the event
   *  \param grp     - group of the generated event
   *  \param idx     - index of generated event
   *  \retval DNP3_OK on success or error code otherwise
   */
  DNP3_STATUS_t UnsolicitedSend(CLASS_t evClass, int8u grp, int16u idx);
#endif

protected:
  COutstation();

  DNP3_STATUS_t openConn(CTranspFunc *p_tf);

  static COutstation*           arrOutst[CFG_OUTSTATION_COUNT];
  static boolean_t              bInit;

  template<typename T>
  DNP3_STATUS_t generateEvent(CLASS_t evClass, int8u grp, int16u idx, CGroup<CPoint<T>> *p_grp, CTimeStampDNP3 *p_ts) {
    DNP3_STATUS_t  retVal = DNP3_OK;

    retVal = p_grp->GenerateEvent(grp, idx, p_ts);
    if (DNP3_OK == retVal) {
      switch (evClass) {
        case CLASS_1:
          class1EventsCount++;
          break;
        case CLASS_2:
          class2EventsCount++;
          break;
        case CLASS_3:
          class3EventsCount++;
          break;
        default:
          break;
      }
    }
    else if (DNP3_ERR_NOT_SUPPORTED == retVal) {
      retVal = DNP3_OK;
    }
    else {
      intInd.setBits(CIntInd::EVENT_BUFFER_OVERFLOW);
    }
    return retVal;
  }

  void setCallback(IOutstationCallback *p_cbInst) {
    p_cb = p_cbInst;
    if (nullptr != p_cb) p_cb->p_os = this;
  }

  /** Array of group 0 configuration data */
  CIntInd                       intInd;

  /** ID of the outstation which is matched against the destAddr in the incomming requests   */
  int16u                        outstId;
  /** Count of class 1 events generated by Outstation app */
  int16u                        class1EventsCount;
  /** Count of class 1 events sent to DNP3 master and awaiting confirmation */
  int16u                        class1EventsCountTBC; // To Be Confirmed
  /** Count of class 2 events generated by Outstation app */
  int16u                        class2EventsCount;
  /** Count of class 2 events sent to DNP3 master and awaiting confirmation */
  int16u                        class2EventsCountTBC; // To Be Confirmed
  /** Count of class 3 events generated by Outstation app */
  int16u                        class3EventsCount;
  /** Count of class 3 events sent to DNP3 master and awaiting confirmation */
  int16u                        class3EventsCountTBC; // To Be Confirmed

  typedef struct {
    CTranspFunc                 *p_transp;

    /** bitmask of classes (1,2,3,4) for which unsolicited messaging is enabled */
    int8u                       unsolicitedMask;
  } CONNECTION_INF_t;

  /** Array of structures holding information about connection (e.g. unsolicited mask) with DNP3 masters */
  CONNECTION_INF_t              arrConn[CFG_MAX_OS_CONNECTIONS];

  typedef struct {
    int8u          grp;
    CArray        *p_array;
  } GROUP_MAP_t;

  #define CFG_GROUP_COUNT       24
  GROUP_MAP_t                   arrGrpMap[CFG_GROUP_COUNT];

  const OUTSTATION_CONFIG_t       &osCfg;

  /** Pointer to defining callback functions */
  IOutstationCallback           *p_cb;

  /** Array of group 0 configuration data */
  C2XXArray                     arr2XX;
};


template<const OUTSTATION_CONFIG_t  &cfg, class CB>
class COutstationInst : public COutstation {
public:

  COutstationInst() : COutstation(cfg),
                arrBinPts(1,2), arrDBinPts(3,4), arrBOutPts(10, 11, 12, 13), arrCountPts(20, 22, 21, 23),
                arrAINPts(30, 32, 31, 33), arrAOUTPts(40, 42, 41, 43), arrTimePts(50, 0), arrCTOPts(51, 0), arrDelayPts(52, 0) {

    setCallback( &(this->objCB) );                // initialize pointer to callback object in parent class

    arrGrpMap[1].grp = 1;
    arrGrpMap[1].p_array = &arrBinPts;
    arrGrpMap[2].grp = 2;
    arrGrpMap[2].p_array = arrBinPts.template GetGroup<CEvent<CBinPoint>>(2);
    arrGrpMap[3].grp = 3;
    arrGrpMap[3].p_array = &arrDBinPts;
    arrGrpMap[4].grp = 4;
    arrGrpMap[4].p_array = arrDBinPts.template GetGroup<CEvent<CDBinPoint>>(4);
    // Binary output groups
    arrGrpMap[5].grp = 10;
    arrGrpMap[5].p_array = &arrBOutPts;
    arrGrpMap[6].grp = 11;
    arrGrpMap[6].p_array = arrBOutPts.template GetGroup<CEvent<CBinPoint>>(11);
    arrGrpMap[7].grp = 12;
    arrGrpMap[7].p_array = arrBOutPts.template GetGroup<CBinPoint>(12);
    arrGrpMap[8].grp = 13;
    arrGrpMap[8].p_array = arrBOutPts.template GetGroup<CEvent<CCROBPoint>>(13);
    // Counter groups
    arrGrpMap[9].grp = 20;
    arrGrpMap[9].p_array = &arrCountPts;
    arrGrpMap[10].grp = 21;
    arrGrpMap[10].p_array = arrCountPts.template GetGroup<CCountPoint>(21);
    arrGrpMap[11].grp = 22;
    arrGrpMap[11].p_array = arrCountPts.template GetGroup<CEvent<CCountPoint>>(22);
    arrGrpMap[12].grp = 23;
    arrGrpMap[12].p_array = arrCountPts.template GetGroup<CEvent<CCountPoint>>(23);
    // Analog input groups
    arrGrpMap[13].grp = 30;
    arrGrpMap[13].p_array = &arrAINPts;
    arrGrpMap[14].grp = 31;
    arrGrpMap[14].p_array = arrAINPts.template GetGroup<CAnalogPoint>(31);
    arrGrpMap[15].grp = 32;
    arrGrpMap[15].p_array = arrAINPts.template GetGroup<CEvent<CAnalogPoint>>(32);
    arrGrpMap[16].grp = 33;
    arrGrpMap[16].p_array = arrAINPts.template GetGroup<CEvent<CAnalogPoint>>(33);
    // Analog output groups
    arrGrpMap[17].grp = 40;
    arrGrpMap[17].p_array = &arrAOUTPts;
    arrGrpMap[18].grp = 41;
    arrGrpMap[18].p_array = arrAOUTPts.template GetGroup<CAnalogPoint>(41);
    arrGrpMap[19].grp = 42;
    arrGrpMap[19].p_array = arrAOUTPts.template GetGroup<CEvent<CAnalogPoint>>(42);
    arrGrpMap[20].grp = 43;
    arrGrpMap[20].p_array = arrAOUTPts.template GetGroup<CEvent<CAnalogPoint>>(43);
    arrGrpMap[21].grp = 50;
    arrGrpMap[21].p_array = &arrTimePts;
    arrGrpMap[22].grp = 51;
    arrGrpMap[22].p_array = &arrCTOPts;
    arrGrpMap[23].grp = 52;
    arrGrpMap[23].p_array = &arrDelayPts;
  }

  /*! \fn DNP3_STATUS_t Freez(int8u grp, int16u idx, bool bClear);
   *  \brief  used by command handler to freez values of Counter (group 20) or Analog Inut (group 30)
   *  \param grp     - number of group to be frozen
   *  \param idx     - index of the point to freez or INDEX_ALL value
   *  \param bClear  - flag indicating if values of the points shal be cleared (reset) after freezing
   *  \retval DNP3_OK on success,
   *           DNP3_ERR_PARAM - grp parameter is invalid
   *           DNP3_ERR_NOT_SUPPORTED - freez operation is not supported
   */
  virtual DNP3_STATUS_t Freez(int8u grp, int16u idx, bool bClear) {
  #if CFG_ENABLE_FREEZ
    DNP3_STATUS_t   res = DNP3_ERR_PARAM;

    LOG_info("freez grp:%d, index:%d  clear:%s\n", grp, idx, (bClear ? "TRUE":"FALSE"));
    if (20 == grp) {
      res = arrCountPts.Freez(false, idx, bClear);
    }
    else if (22 == grp) {
      res = arrCountPts.Freez(true, idx, bClear);
    }
    else if (30 == grp) {
      res = arrAINPts.Freez(false, idx, bClear);
    }
    else if (32 == grp) {
      res = arrAINPts.Freez(true, idx, bClear);
    }
    else {
      LOG_error("Invalid group:%d for freez operation\n", grp);
      res = DNP3_ERR_PARAM;
    }
  #else
    DNP3_STATUS_t   res = DNP3_ERR_NOT_SUPPORTED;
    LOG_error("Freez operation is not supported!\n");
  #endif
    return res;
  }

  /*! \fn CData* GetObject(int8u grp, int16u idx);
   *  \brief returns pointer to the point obbject indicated by group number (grp) and the index (idx)
   *  \param grp     - number of group
   *  \param idx     - index of the point to be reutrned
   *  \retval pointer the the CData object representing point from specific group / index
   *          NULL - either group number (grp) or point (idx) are ivalid
   */
  virtual CData* GetObject(int8u grp, int16u idx) {
    CData  *p_obj = (CData*)NULL;

    if (0 == grp) {
      p_obj = GetObject<CData>(grp, (int16u)idx);
    }
    else if (1 == grp) {
      p_obj = GetObject<CBinPoint>(grp, (int16u)idx);
    }
    else if (2 == grp) {
      p_obj = GetObject<CEvent<CBinPoint>>(grp, (int16u)idx);
    }
    else if (3 == grp) {
      p_obj = GetObject<CDBinPoint>(grp, (int16u)idx);
    }
    else if (4 == grp) {
      p_obj = GetObject<CEvent<CDBinPoint>>(grp, (int16u)idx);
    }
    else if (10 == grp) {
      p_obj = GetObject<CBinPoint>(grp, (int16u)idx);
    }
    else if (11 == grp) {
      p_obj = GetObject<CEvent<CBinPoint>>(grp, (int16u)idx);
    }
    else if (12 == grp) {
      p_obj = GetObject<CCROBPoint>(grp, (int16u)idx);
    }
    else if (13 == grp) {
      p_obj = GetObject<CEvent<CPoint<bool>>>(grp, (int16u)idx);
    }
    else if (20 == grp) {
      p_obj = GetObject<CCountPoint>(grp, (int16u)idx);
    }
    else if (21 == grp) {
      p_obj = GetObject<CCountPoint>(grp, (int16u)idx);
    }
    else if (22 == grp) {
      p_obj = GetObject<CEvent<CCountPoint>>(grp, (int16u)idx);
    }
    else if (23 == grp) {
      p_obj = GetObject<CEvent<CCountPoint>>(grp, (int16u)idx);
    }
    else if ((30 == grp) || (31 == grp)) {
      p_obj = GetObject<CAnalogPoint>(grp, (int16u)idx);
    }
    else if (32 == grp) {
      p_obj = GetObject<CEvent<CAnalogPoint>>(grp, (int16u)idx);
    }
    else if (40 == grp) {
      p_obj = GetObject<CAnalogPoint>(grp, (int16u)idx);
    }
    else if (41 == grp) {
      p_obj = GetObject<CAnalogPoint>(grp, (int16u)idx);
    }
    else if (42 == grp) {
      p_obj = GetObject<CEvent<CAnalogPoint>>(grp, (int16u)idx);
    }
    else if (43 == grp) {
      p_obj = GetObject<CEvent<CAnalogPoint>>(grp, (int16u)idx);
    }
    else if (50 == grp) {
      p_obj = GetObject<CTimePoint>(grp, (int16u)idx);
    }
    else if (51 == grp) {
      p_obj = GetObject<CCTOPoint>(grp, (int16u)idx);
    }
    else if (52 == grp) {
      p_obj = GetObject<CDelayPoint>(grp, (int16u)idx);
    }
    return p_obj;
  }

  /*! \fn template<class C> C* GetObject(int8u grp, int16u idx)
   *  \brief returns pointer to the point obbject of specific type C indicated by group number (grp) and the index (idx)
   *  \param grp     - number of group
   *  \param idx     - index of the point to be reutrned
   *  \retval pointer the the CData object representing point from specific group / index
   *          NULL - type mismatch between C anbd actual type of group (grp) elements, or group number (grp) / point (idx) are ivalid
   */
  template<class C>
  C* GetObject(int8u grp, int16u idx) {
    CData  *p_dat;
    C  *p_obj;

    if (0 == grp) {
      p_obj = dynamic_cast<C*>(arr2XX.GetObject(idx));
    }
    else {
      p_dat = arrBinPts.GetObject(grp, idx);
      if (NULL == p_dat) {
        p_dat = arrDBinPts.GetObject(grp, idx);
      }
      if (NULL == p_dat) {
        p_dat = arrBOutPts.GetObject(grp, idx);
      }
      if (NULL == p_dat) {
        p_dat = arrCountPts.GetObject(grp, idx);
      }
      if (NULL == p_dat) {
        p_dat = arrAINPts.GetObject(grp, idx);
      }
      if (NULL == p_dat) {
        p_dat = arrAOUTPts.GetObject(grp, idx);
      }
      if (NULL == p_dat) {
        p_dat = arrTimePts.GetObject(grp, idx);
      }
      if (NULL == p_dat) {
        p_dat = arrCTOPts.GetObject(grp, idx);
      }
      if (NULL == p_dat) {
        p_dat = arrDelayPts.GetObject(grp, idx);
      }
      p_obj = dynamic_cast<C*>(p_dat);
    }
    return p_obj;
  }

protected:
  /** Array of binary input points groups 1,2     */
  CPointArray<CBinPoint, cfg.cntBinPts, cfg.cntBinEvPts>                                    arrBinPts;

  /** Array of double-bit binary input points groups 3, 4 */
  CPointArray<CDBinPoint, cfg.cntDBinPts, cfg.cntDBinEvPts>                                 arrDBinPts;

  /** Array of ontrol relay output block points groups 10,11,12,13  */
  COutCmdArray<CBinPoint, CCROBPoint, cfg.cntOutBinPts, cfg.cntOutBinEvPts>                 arrBOutPts;

  /** Array of counter points groups 20,22, 21,23   */
  CPointArray<CCountPoint, cfg.cntCountPts, cfg.cntCountEvPts, cfg.cntCountPts>             arrCountPts;

  /** Array of analog input group 30,32   */
  CPointArray<CAnalogPoint, cfg.cntAnalogInPts, cfg.cntAnalogInEvPts, cfg.cntAnalogInPts>   arrAINPts;

  /** Array of analog output group 40,41,42,43   */
  COutCmdArray<CAnalogPoint, CAnalogPoint, cfg.cntAnalogOutPts, cfg.cntAnalogOutEvPts>      arrAOUTPts;

  /** Array of time point group 50   */
  CPointArray<CTimePoint, 1, 0>               arrTimePts;

  /** Array of CTO point group 51   */
  CPointArray<CCTOPoint, 1, 0>                arrCTOPts;

  /** Array of delay point group 52   */
  CPointArray<CDelayPoint, 1, 0>              arrDelayPts;

  /** Object defining callback methods */
  CB                                          objCB;
};

#endif
