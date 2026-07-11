#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

#include <stdio.h>

LRESULT CALLBACK WindowProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY) PostQuitMessage(0);

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int main(int argc, char** argv)
{
  if (!MONSInit())
  {
     printf("MONSInit filed\n");
     return 1;
  }

  MONS_Window* Window = MONS_CreateWindow("test", &((MONS_Rect){100,200,300,300}),WindowProc);

  MONSTerminate();

  return 0;
}
