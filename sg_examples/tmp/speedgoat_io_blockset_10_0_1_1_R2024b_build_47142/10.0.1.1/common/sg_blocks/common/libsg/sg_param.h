// Copyright 2006-2026 Speedgoat GmbH

#ifndef z3683ba5d5e
#define z3683ba5d5e
#define RTW_GENERATED_S_FUNCTION
#include "simstruc.h"
#ifdef __cplusplus
extern"C"{
#endif
#include "sg_printf.h"
typedef struct{int*val;int len;}SgParam_IntVec;typedef struct{bool*val;int len;}SgParam_BoolVec;typedef struct{double*val;int len;}SgParam_DoubleVec;typedef struct{char*val;int len;}SgParam_CharVec;
#define SG_PARAM_PRINT_INT(zd30357c8a1, field)                                            \
    do {                                                                            \
        SG_PRINTF(DEBUG, #field "\x3a\x20\x25\x64" "\n", (zd30357c8a1)->field);                          \
    } while ((0x1+4563-0x11d4))
#define SG_PARAM_PRINT_BOOL(zd30357c8a1, field)                                           \
    do {                                                                            \
        SG_PRINTF(DEBUG, #field "\x3a\x20\x25\x73" "\n", ((zd30357c8a1)->field) ? "\x74\x72\x75\x65" : "\x66\x61\x6c\x73\x65");     \
    } while ((0x882+7380-0x2556))
#define SG_PARAM_PRINT_DOUBLE(zd30357c8a1, field)                                         \
    do {                                                                            \
        SG_PRINTF(DEBUG, #field "\x3a\x20\x25\x66" "\n", (zd30357c8a1)->field);                          \
    } while ((0x1dd1+773-0x20d6))
#define SG_PARAM_PRINT_CHAR(zd30357c8a1, field)                                           \
    do {                                                                            \
        SG_PRINTF(DEBUG, #field "\x3a\x20\x25\x63" "\n", (zd30357c8a1)->field);                          \
    } while ((0x705+2945-0x1286))
#define SG_PARAM_PRINT_INT_VEC(zd30357c8a1, field)                                        \
    do {                                                                            \
        int i;                                                                      \
        char buffer[(0xb10+6697-0x2139)];                                                          \
        size_t z8a7e6753de = (0x14d1+3935-0x2430);                                                             \
        z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, #field "\x3a\x20\x5b");          \
        for (i = (0x191f+1154-0x1da1); i < (zd30357c8a1)->field->len && z8a7e6753de < sizeof(buffer) - (0x5fd+2725-0x1093); i++)      \
        {                                                                           \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x25\x64",               \
                (zd30357c8a1)->field->val[i]);                                            \
            if ((i + (0x90+9021-0x23cc)) != (zd30357c8a1)->field->len)                                     \
            {                                                                       \
                z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x2c\x20");          \
            }                                                                       \
        }                                                                           \
        if (z8a7e6753de < sizeof(buffer) - (0x1cc+4671-0x1409)) {                                             \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x5d" "\n");             \
        } else {                                                                    \
            buffer[sizeof(buffer) - (0x5ea+5784-0x1c7f)] = ((char)(0x71+1914-0x78e));                                       \
            buffer[sizeof(buffer) - (0xdf7+5523-0x2388)] = '\n';                                      \
            buffer[sizeof(buffer) - (0xfb0+5965-0x26fc)] = '\0';                                      \
        }                                                                           \
        SG_PRINTF(DEBUG, "\x25\x73", buffer);                                             \
    } while ((0x109+9068-0x2475))
#define SG_PARAM_PRINT_BOOL_VEC(zd30357c8a1, field)                                       \
    do {                                                                            \
        int i;                                                                      \
        char buffer[(0x1169+4713-0x1fd2)];                                                          \
        size_t z8a7e6753de = (0xc49+2480-0x15f9);                                                             \
        z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, #field "\x3a\x20\x5b");          \
        for (i = (0x349+3139-0xf8c); i < (zd30357c8a1)->field->len && z8a7e6753de < sizeof(buffer) - (0xa4a+5713-0x2091); i++)      \
        {                                                                           \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x25\x73",               \
                ((zd30357c8a1)->field->val[i]) ? "\x74\x72\x75\x65" : "\x66\x61\x6c\x73\x65");                       \
            if ((i + (0x8b0+576-0xaef)) != (zd30357c8a1)->field->len)                                     \
            {                                                                       \
                z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x2c\x20");          \
            }                                                                       \
        }                                                                           \
        if (z8a7e6753de < sizeof(buffer) - (0x268+1307-0x781)) {                                             \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x5d" "\n");             \
        } else {                                                                    \
            buffer[sizeof(buffer) - (0x9f2+3079-0x15f6)] = ((char)(0x9c3+5734-0x1fcc));                                       \
            buffer[sizeof(buffer) - (0x416+1881-0xb6d)] = '\n';                                      \
            buffer[sizeof(buffer) - (0x597+113-0x607)] = '\0';                                      \
        }                                                                           \
        SG_PRINTF(DEBUG, "\x25\x73", buffer);                                             \
    } while ((0xab2+4153-0x1aeb))
#define SG_PARAM_PRINT_DOUBLE_VEC(zd30357c8a1, field)                                     \
    do {                                                                            \
        int i;                                                                      \
        char buffer[(0x66a+8184-0x2262)];                                                          \
        size_t z8a7e6753de = (0x1ceb+1701-0x2390);                                                             \
        z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, #field "\x3a\x20\x5b");          \
        for (i = (0x1008+2875-0x1b43); i < (zd30357c8a1)->field->len && z8a7e6753de < sizeof(buffer) - (0x77c+3234-0x1405); i++)      \
        {                                                                           \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x25\x66",               \
                (zd30357c8a1)->field->val[i]);                                            \
            if ((i + (0x18a1+779-0x1bab)) != (zd30357c8a1)->field->len)                                     \
            {                                                                       \
                z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x2c\x20");          \
            }                                                                       \
        }                                                                           \
        if (z8a7e6753de < sizeof(buffer) - (0x796+7202-0x23b6)) {                                             \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x5d" "\n");             \
        } else {                                                                    \
            buffer[sizeof(buffer) - (0x1034+3297-0x1d12)] = ((char)(0x5e8+5827-0x1c4e));                                       \
            buffer[sizeof(buffer) - (0x1fc0+1841-0x26ef)] = '\n';                                      \
            buffer[sizeof(buffer) - (0x86a+2709-0x12fe)] = '\0';                                      \
        }                                                                           \
        SG_PRINTF(DEBUG, "\x25\x73", buffer);                                             \
    } while ((0xa52+4113-0x1a63))
#define SG_PARAM_PRINT_CHAR_VEC(zd30357c8a1, field)                                       \
    do {                                                                            \
        int i;                                                                      \
        char buffer[(0x14e7+1506-0x16c9)];                                                          \
        size_t z8a7e6753de = (0x340+1592-0x978);                                                             \
        z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, #field "\x3a\x20" "\"");         \
        for (i = (0xd44+4961-0x20a5); i < (zd30357c8a1)->field->len && z8a7e6753de < sizeof(buffer) - (0x13cb+3875-0x22ea); i++)       \
        {                                                                           \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\x25\x63",               \
                (zd30357c8a1)->field->val[i]);                                            \
        }                                                                           \
        if (z8a7e6753de < sizeof(buffer) - (0x7a7+1215-0xc64)) {                                             \
            z8a7e6753de += snprintf(buffer + z8a7e6753de, sizeof(buffer) - z8a7e6753de, "\"\n");            \
        } else {                                                                    \
            buffer[sizeof(buffer) - (0x743+786-0xa52)] = ((char)(0x1309+4413-0x2424));                                       \
            buffer[sizeof(buffer) - (0x9f1+2384-0x133f)] = '\n';                                      \
            buffer[sizeof(buffer) - (0xd23+3807-0x1c01)] = '\0';                                      \
        }                                                                           \
        SG_PRINTF(DEBUG, "\x25\x73", buffer);                                             \
    } while ((0xcf8+6161-0x2509))
extern int sgParam_getInt(SimStruct*S,int id);extern bool sgParam_getBool(SimStruct*S,int id);extern double sgParam_getDouble(SimStruct*S,int id);extern char sgParam_getChar(SimStruct*S,int id);extern SgParam_IntVec*sgParam_newIntVec(SimStruct*S,int id);extern void sgParam_deleteIntVec(SgParam_IntVec*ze71522182c);extern SgParam_BoolVec*sgParam_newBoolVec(SimStruct*S,int id);extern void sgParam_deleteBoolVec(SgParam_BoolVec*ze71522182c);extern SgParam_DoubleVec*sgParam_newDoubleVec(SimStruct*S,int id);extern void sgParam_deleteDoubleVec(SgParam_DoubleVec*ze71522182c);extern SgParam_CharVec*sgParam_newCharVec(SimStruct*S,int id);extern void sgParam_deleteCharVec(SgParam_CharVec*ze71522182c);
#ifdef __cplusplus
}
#endif
#endif  

