

#include "Monsoon/MONS_Console.h"
#include <Monsoon/Monsoon.h>

#include <stdarg.h>
#include <stdio.h>
#include <vadefs.h>

void MONS_Log(char* FunctionName,char* Message,uint64_t Code,int Severity,...)
{
  va_list args;
  va_list backup_args;

  va_start(args, Severity);
  va_copy(backup_args,args);

  char* buffer = malloc(1024);
  if (!buffer)
  {
    MONS_WriteStdOutput("Error: MONS_Log malloc err");
    va_end(args);
    va_end(backup_args);
    return;
  }

  int prefix = snprintf(buffer,1024,"[%s],[\033[34m%s\033[0m],[%020llu]: ",MONS_SeverityToString(Severity,True),FunctionName,Code);
  vsnprintf(buffer+prefix,1024-prefix,Message,backup_args);

  va_end(args);
  va_end(backup_args);

  MONS_WriteStdOutput(buffer);
  MONS_WriteStdOutput("\n");

  free(buffer);
}
