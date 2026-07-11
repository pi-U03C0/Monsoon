#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>
#include <string.h>

int MONS_WriteStdOutput(char* Message)
{
  #ifdef _WIN32
  static HANDLE hConsole = NULL;
  LPDWORD WriteLen = 0;

  if (!hConsole) hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  WriteFile(
    hConsole,
    Message,
    strlen(Message),
    WriteLen,
    NULL
  );

  return *WriteLen;
  #endif
}

int MONS_WriteStdError(char* Message)
{
  #ifdef _WIN32
  static HANDLE hConsole = NULL;
  LPDWORD WriteLen = 0;

  if (!hConsole) hConsole = GetStdHandle(STD_ERROR_HANDLE);

  WriteFile(
    hConsole,
    Message,
    strlen(Message),
    WriteLen,
    NULL
  );

  return *WriteLen;
  #endif
}

int MONS_WriteStdInput(char* Message)
{
  #ifdef _WIN32
  static HANDLE hConsole = NULL;
  LPDWORD WriteLen = 0;

  if (!hConsole) hConsole = GetStdHandle(STD_INPUT_HANDLE);

  WriteFile(
    hConsole,
    Message,
    strlen(Message),
    WriteLen,
    NULL
  );

  return *WriteLen;
  #endif
}

MSBool MONS_StdInputIsConsole()
{
  HANDLE cHandle = GetStdHandle(STD_INPUT_HANDLE);

  switch (GetFileType(cHandle))
  {
    case FILE_TYPE_CHAR:return True;
    default:return False;
  }

  return 0;
}
