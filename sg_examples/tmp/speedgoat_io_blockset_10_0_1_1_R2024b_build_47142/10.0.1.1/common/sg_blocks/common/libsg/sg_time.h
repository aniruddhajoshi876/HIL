#ifndef SG_TIME_H
#define SG_TIME_H

#ifdef __cplusplus
extern "C" 
{
#endif

#if defined( __QNX__) || defined(__linux__)

typedef struct DateTime_tag
{
    int year;
    int month;
    int dom; // day of month
    int doy; // day of year
    int hour;
    int min;
    int sec;
    double subsec; 
    int ns;
    int inSync; // 1: System in sync
}DateTime_T;

typedef struct DateStr_tag
{
    char wd[4];  // week day
    char month[4];
    char dom[4];  // day of month
    char hhmmss[9];
    char tz[4];
    char year[4];
}DateStr_T;

int sg_getTargetTime(char* targetTime);
double sg_getTargetTimeNum();
double sg_getSecondsSinceStart(void);

// Add leap day for leap years:
#define IS_LEAP(y) ((((y) % 4 == 0) && ((y) % 100 != 0)) || ((y) % 400 == 0))

#define DAYS_UNTIL_YEAR_LENGTH 3001

#endif

#ifdef __cplusplus
}
#endif

#endif // #ifndef SG_TIME_H
