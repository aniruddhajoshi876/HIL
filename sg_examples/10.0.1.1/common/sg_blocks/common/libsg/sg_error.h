// Copyright 2006-2026 Speedgoat GmbH

#ifndef zcef7aa01ef
#define zcef7aa01ef
#define SGERROR_ERROR_MSG_BUFFER_LEN    ((0xb50+715-0xd53))
#define SGERROR_OUTPUT_MSG_BUFFER_LEN   ((0x180f+3950-0x26b5))
#ifdef __cplusplus
extern"C"{
#endif
typedef struct{char errorMsg[SGERROR_ERROR_MSG_BUFFER_LEN];char outputMsg[SGERROR_OUTPUT_MSG_BUFFER_LEN];int writeIndex;}SgError;extern SgError*sgError_new(void);extern void sgError_delete(SgError*error);extern void sgError_setPreamble(SgError*error,const char*z9a1876ef4c,const char*z0af3eceea4,int moduleId);extern void sgError_setMsg(SgError*error,const char*format,...);extern void sgError_extractMsg(SgError*error,char*msg);extern const char*sgError_getMsg(SgError*error);
#ifdef __cplusplus
}
#endif
#endif  

