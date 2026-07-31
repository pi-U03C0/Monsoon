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

void MONS_InitProcDefine()
{
  uint16_t NextIndex = 0;
  #ifdef MONSOON_PLATFORM_NT
     MONS_ProcsDefine[NextIndex].Proc = MONSOON_PROC_WINDOW_NAME;
     MONS_ProcsDefine[NextIndex].Type = MONS_PROC_WINDOW;
  #endif
}
