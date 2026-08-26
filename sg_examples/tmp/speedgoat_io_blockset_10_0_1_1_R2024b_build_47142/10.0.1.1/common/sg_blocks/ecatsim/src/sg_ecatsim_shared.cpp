#include "simstruc.h"


uint32_T getDataTypeLength(uint32_T DataType)
{
    switch (DataType) {
    case SS_DOUBLE:
        return 8;
    case SS_SINGLE:
        return 4;
    case SS_UINT32:
        return 4;
    case SS_INT32:
        return 4;
    case SS_UINT16:
        return 2;
    case SS_INT16:
        return 2;
    case SS_UINT8:
        return 1;
    case SS_INT8:
        return 1;
    default:
        return 0;
    }
    return 0;
}
