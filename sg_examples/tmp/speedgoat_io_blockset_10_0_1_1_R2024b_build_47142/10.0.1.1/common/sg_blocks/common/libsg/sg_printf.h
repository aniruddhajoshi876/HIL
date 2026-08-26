#ifndef SG_PRINTF_H
#define SG_PRINTF_H

#ifdef __cplusplus
extern "C" 
{
#endif

//Enabled severities
#define SG_INFO_PRINT
#define SG_WARNING_PRINT
#define SG_ERROR_PRINT

#ifdef MATLAB_MEX_FILE //*** MEX file *********************************************
	#define SG_PRINTF(SEVERITY, ...) SG_PRINTF_##SEVERITY(__VA_ARGS__)
    #ifdef SG_TRACE_PRINT
		#define SG_PRINTF_TRACE(...) 	printf(__VA_ARGS__)
	#else
		#define SG_PRINTF_TRACE(...)    while(0)
	#endif
    
	#ifdef SG_DEBUG_PRINT
		#define SG_PRINTF_DEBUG(...) 	printf(__VA_ARGS__)
	#else
		#define SG_PRINTF_DEBUG(...)    while(0)
	#endif

	#ifdef SG_INFO_PRINT
		#define SG_PRINTF_INFO(...)	    printf(__VA_ARGS__)
	#else
		#define SG_PRINTF_INFO(...)     while(0)
	#endif

	#ifdef SG_WARNING_PRINT
		#define SG_PRINTF_WARNING(...)  printf(__VA_ARGS__)
	#else
		#define SG_PRINTF_WARNING(...)  while(0)
	#endif

	#ifdef SG_ERROR_PRINT
		#define SG_PRINTF_ERROR(...)    printf(__VA_ARGS__)
	#else
		#define SG_PRINTF_ERROR(...)    while(0)
	#endif	
#else //*** QNX *******************************************************************
    enum Severity
    {
        sg_trace,
        sg_debug,
        sg_info,
        sg_warning,
        sg_error
    };
    #define SG_PRINTF(SEVERITY, ...) SG_PRINTF_##SEVERITY(__VA_ARGS__)
    #ifdef SG_TRACE_PRINT
        #define SG_PRINTF_TRACE(...) sg_printf(sg_trace, __VA_ARGS__)
    #else
        #define SG_PRINTF_TRACE(...) do { } while(0)
    #endif
    
    #ifdef SG_DEBUG_PRINT
        #define SG_PRINTF_DEBUG(...) sg_printf(sg_debug, __VA_ARGS__)
    #else
        #define SG_PRINTF_DEBUG(...) do { } while(0)
    #endif

    #ifdef SG_INFO_PRINT
        #define SG_PRINTF_INFO(...) sg_printf(sg_info, __VA_ARGS__)
    #else
        #define SG_PRINTF_INFO(...) do { } while(0)
    #endif

    #ifdef SG_WARNING_PRINT
        #define SG_PRINTF_WARNING(...) sg_printf(sg_warning, __VA_ARGS__)
    #else
        #define SG_PRINTF_WARNING(...) do { } while(0)
    #endif

    #ifdef SG_ERROR_PRINT
        #define SG_PRINTF_ERROR(...) sg_printf(sg_error, __VA_ARGS__)
    #else
        #define SG_PRINTF_ERROR(...) do { } while(0)
    #endif
    
    #define SG_PRINTF_MAX_LENGTH     512

    void sg_printf(enum Severity severity, const char* msg, ...);
	  
    //Log stuff
    void sg_log(enum Severity severity, const char* msg);
    
    //On standalone applications, sg_printf becomes a normal printf.
    //printf's with severity debug or trace are not printed by default.
    //To change this:
    void sg_printf_set_severity(enum Severity severity);

#endif // MATLAB_MEX_FILE

#ifdef __cplusplus
}
#endif

#endif // SG_PRINTF_H
