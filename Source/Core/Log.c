#include <Monsoon/Monsoon.h>

#include <stdarg.h>
#include <stdio.h>
#include <vadefs.h>

void MONS_Log(char* FunctionName,char* Message,uint64_t Code,int Severity,...)
{
  va_list args;
  va_list backup_args;

  int bufferLen = 0;

  va_start(args, Severity);
  va_copy(backup_args,args);

  bufferLen += snprintf(NULL,0,"[%s],[%s],[%020llu]: ",FunctionName,MONS_SeverityToString(Severity),Code);

  bufferLen += vsnprintf(NULL,0,Message,args);

  char* buffer = malloc(bufferLen+1);
  if (!buffer)
  {
    printf("Error: MONS_Log malloc err");
    va_end(args);
    va_end(backup_args);
    return;
  }

  int prefix = snprintf(buffer, bufferLen+1, "[%s],[%020llu]: ",MONS_SeverityToString(Severity),Code);
  vsnprintf(buffer+prefix,bufferLen,Message,backup_args);

  va_end(args);
  va_end(backup_args);

  MONS_WriteStdOutput(buffer);

  free(buffer);
}
