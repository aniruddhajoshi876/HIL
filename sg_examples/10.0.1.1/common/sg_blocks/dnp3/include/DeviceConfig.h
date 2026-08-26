/** @file DeviceConfig.h 
 *
 * @brief
 * Header file for control block base class
 *
 * @details
 * Contains definition of device attributes, points, arrays
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */
 
#include "dnp3_config.h"
#include "Point.h"

typedef CPointArray<CTimePoint, 1, 0>                                      CTimePointArr;
typedef CPointArray<CCTOPoint, 1, 0>                                       CCTOPointArr;
typedef CPointArray<CDelayPoint, 1, 0>                                     CDelayPointArr;
