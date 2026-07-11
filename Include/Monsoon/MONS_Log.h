#ifndef MONSOON_LOG_H
#define MONSOON_LOG_H

#include <Monsoon/MONS_Types.h>
#include <Monsoon/MONS_Error.h>

#define MONSOON_LOG_DEBUG 7
#define MONSOON_LOG_SUCCESS 6
#define MONSOON_LOG_INFO 5
#define MONSOON_LOG_WARNING 4
#define MONSOON_LOG_ERROR 3
#define MONSOON_LOG_CRITICAL 2
#define MONSOON_LOG_FATAL 1
#define MONSOON_LOG_NONE 0

#if MONSON_LOG_LEVEL >= MONSOON_LOG_FATAL
#endif

#define LOG(Message,Severity,ErrorReason,...)\
     MONS_Log(__FUNCTION__,Message,Make_Code(ErrorReason),Severity,__VA_ARGS__)

void MONS_Log(char* FunctionName,char* Message,uint64_t Code,int Severity,...);

#endif
