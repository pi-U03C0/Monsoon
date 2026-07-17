#define __FILE_NUMBER__ 1
#define __PROJECT_PART__ -1

#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

#include <stdio.h>

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
            // Window has been created.
            return 0;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int main(int argc, char** argv)
{
  if (!MONSInit())
  {
     printf("MONSInit filed\n");
     return 1;
  }

  MONS_Rect window_corrd = {100,200,300,300};

  MONS_Window* Window = MONS_CreateWindow("test", &window_corrd,WindowProc);
  if (!Window)
  {
    LOG("Window was NULL", MONSOON_LOG_FATAL, 1);
    goto exit;
  }
  MONS_ShoWindow(Window,MONS_SHOW_WINDOW);;

  MSG msg;
  while (GetMessageA(&msg, NULL , 0,0))
  {
     TranslateMessage(&msg);
     DispatchMessageA(&msg);
  }

  MONS_CloseWindow(Window);

  MONSTerminate();

exit:
  return 0;
}
