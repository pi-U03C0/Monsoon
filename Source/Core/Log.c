#include <Monsoon/Monsoon.h>

#include <stdarg.h>
#include <stdio.h>
#include <vadefs.h>

void MONS_Log(char* FunctionName,char* Message,uint64_t Code,int Severity,...)
{
  if (!(__Monsoon -> state.LogLevel >= Severity)) return;

  if (!Message)
  {
    MONS_WriteStdOutput("MONS_Log: Message was NULL FunctionName=");
    MONS_WriteStdOutput(FunctionName);
    MONS_WriteStdOutput("\n");

    return;
  }

  va_list args;
  va_list backup_args;

  va_start(args, Severity);
  va_copy(backup_args,args);

  char* buffer = GetMemory(1024);
  if (!buffer)
  {
    MONS_WriteStdOutput("MONS_LOG: malloc err\n");
    va_end(args);
    va_end(backup_args);
    return;
  }

  int prefix = snprintf(buffer,1024,"[%s]: ",MONS_SeverityToString(Severity,True));
  int message_len = vsnprintf(buffer+prefix,1024-prefix,Message,backup_args);
  snprintf(buffer+prefix+message_len,1024-prefix-message_len," [\033[34m%s\033[0m],[%020llu]",FunctionName,Code);

  va_end(args);
  va_end(backup_args);

  MONS_WriteStdOutput(buffer);
  MONS_WriteStdOutput("\n");

  RemoveMemory(buffer);
}

char* MONS_SeverityToString(char Severity,MSBool Colour)
{
  if (Colour)
  {
    switch (Severity)
    {
      case MONSOON_LOG_ERROR:return "\033[91mERROR\033[0m";
      case MONSOON_LOG_CRITICAL:return "\033[91mCRITICAL\033[0m";
      case MONSOON_LOG_FATAL:return "\033[91mFATAL\033[0m";
      case MONSOON_LOG_INFO:return "\033[94mINFO\033[0m";
      case MONSOON_LOG_SUCCESS:return "\033[92mSUCCESS\033[0m";
      case MONSOON_LOG_WARNING:return "\033[93mWARNING\033[0m";
      case MONSOON_LOG_DEBUG:return "\033[93mDEBUG\033[0m";
      default:return "?";
    }
  }
  else if (Colour == 2)
  {
    return NULL;
  }
  else
  {
    switch (Severity)
    {
      case MONSOON_LOG_ERROR:return "ERROR";
      case MONSOON_LOG_CRITICAL:return "CRITICAL";
      case MONSOON_LOG_FATAL:return "FATAL";
      case MONSOON_LOG_INFO:return "INFO";
      case MONSOON_LOG_SUCCESS:return "SUCCESS";
      case MONSOON_LOG_WARNING:return "WARNING";
      case MONSOON_LOG_DEBUG:return "DEBUG";
      default:return "?";
    }
  }
}
