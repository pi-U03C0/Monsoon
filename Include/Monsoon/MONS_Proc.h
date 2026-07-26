#ifndef MONSOON_PROC_H
#define MONSOON_PROC_H

#include <Monsoon/Platform/Platform.h>
#include <Monsoon/MONS_Types.h>

#define MONS_PROC_WINDOW 1
#define MONSOON_PROC_LEN 1

#ifdef _WIN32
    #define MONSOON_PROC_WINDOW_NAME MONSOON_PROC_WIN32_WINDOW_NAME
#endif

extern MONS_Proc* MONS_Procs;

MONS_Proc MONS_ProcsDefine[] = {
    {MONS_PROC_WINDOW,MONSOON_PROC_WINDOW_NAME}
};

void* MONS_GetProc(uint16_t ProcType);

#endif
