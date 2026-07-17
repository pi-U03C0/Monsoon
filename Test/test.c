#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ 1

#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

#include <stdio.h>

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE: return 0;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int main(int argc, char** argv)
{
  if (!MONSInit())
  {
     printf("MONSInit filed\n");
     return 1;
  }

  if (!MONS_FileExists("ls.txt")) MONS_Win32_MakeFile("ls.txt");

  MONS_File* FileHandle = MONS_OpenFile("ls.txt", MONSOON_FILE_READ);

  char* buffer = GetMemory(FileHandle -> FileSize);

  MONS_ReadFile(FileHandle,buffer,FileHandle -> FileSize);
  buffer[FileHandle -> FileSize] = 0;

  printf("%s", buffer);

  RemoveMemory(buffer);
  MONS_CloseFile(FileHandle);
  MONSTerminate();

  return 0;
}
