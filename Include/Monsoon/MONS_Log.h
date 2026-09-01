#ifndef MONSOON_LOG_H
#define MONSOON_LOG_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/MONS_Error.h>

#define MONSOON_LOG_UNIGNORE 11
#define MONSOON_LOG_LOW_DEBUG 10
#define MONSOON_LOG_MID_DEBUG 9
#define MONSOON_LOG_HIGHT_DEBUG 8
#define MONSOON_LOG_DEBUG 7
#define MONSOON_LOG_INFO 6
#define MONSOON_LOG_SUCCESS 5
#define MONSOON_LOG_WARNING 4
#define MONSOON_LOG_ERROR 3
#define MONSOON_LOG_CRITICAL 2
#define MONSOON_LOG_FATAL 1
#define MONSOON_LOG_NONE 0

#define MONSOON_LOG_OS_ERROR 40
#define MONSOON_LOG_UNABLE_TO_ALLOC_MEMORY 100
#define MONSOON_LOG_EMPTY 300
#define MONSOON_LOG_WAS_NULL 301
#define MONSOON_LOG_WAS_FULL 302
#define MONSOON_LOG_UNABLE_GET 303
#define MONSOON_LOG_UNKNOWN 304
#define MONSOON_LOG_FREE 305
#define MONSOON_LOG_INIT 306
#define MONSOON_LOG_UNABLE_DO 307
#define MONSOON_LOG_TOO_LONG 308

#ifndef MONSOON_NO_LOG
   #define LOG(Message,Severity,ErrorReason,...)\
      MONS_Log(__FUNCTION__,Message,Make_Code(ErrorReason),Severity, ##__VA_ARGS__)
#else
     #define LOG(Message,Severity,ErrorReason,...)
#endif

#ifndef MONSOON_LOG_DEFAULT
#define  MONSOON_LOG_DEFAULT 10
#endif

#ifndef MONSOON_LOG_LEVEL
  #define MONSOON_LOG_LEVEL MONSOON_LOG_DEFAULT
#endif

void MONS_Log(char* FunctionName,char* Message,uint64_t Code,int Severity,...);

char* MONS_SeverityToString(char Severity,MSBool Colour);

#endif
