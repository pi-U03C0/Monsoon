#include <Monsoon/Monsoon.h>

MONS_Proc* MONS_Procs = NULL;

MONS_Proc MONS_ProcsDefine[] = {
    {MONS_PROC_WINDOW,MONSOON_PROC_WINDOW_NAME}
};

void* MONS_GetProc(uint16_t ProcType)
{
  for (uint16_t i = 0 ; MONS_Procs[i].Type ; i++)
  {
    if (MONS_Procs[i].Type == ProcType)
    {
      return MONS_Procs[i].Proc;
    }
  }
  return NULL;
}
