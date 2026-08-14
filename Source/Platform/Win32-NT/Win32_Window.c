#define INCLUDE_STD
#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

LRESULT CALLBACK MONS_Win32_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE: {
          MONS_Event event = {
            .Type = MONSOON_EVENT_WINDOW_CLOSE,
            .Prarms = NULL,
          };

          MONS_PushWindowEvent((MONS_Window*)GetWindowLongPtrA(hwnd,GWLP_USERDATA),&event);
          return 0;
        };

        case WM_DESTROY:
        {
          PostQuitMessage(0);
          return 0;
        }

        default:
        {
          return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
}

uint32_t MONS_Win32_ActToMode(char act)
{
  switch (act)
  {
    case MONS_SHOW_WINDOW:return SW_SHOWNORMAL;
    default:return -1;
  }
}

HANDLE MONS_Win32_CreateWindow(char* Title,MONS_Rect* rect,void* WinProc)
{
  if (!WinProc)
  {
    LOG("WinProc was NULL",MONSOON_LOG_ERROR,1);
    return NULL;
  }

  char* window_class_name = GetMemory(256);
  if (!window_class_name)
  {
    Error_Memory();
    return NULL;
  }

  snprintf(window_class_name, 256, "Monsoon Win32 Window: %d",__Monsoon -> state.WindowCount);;

  WNDCLASS window_class = {0};
  window_class.lpszClassName = window_class_name;
  window_class.lpfnWndProc = WinProc;
  window_class.style = CS_OWNDC;

  if (!RegisterClassA(&window_class))
  {
    LOG("Unable to Register Class,Win32 ErrorCode = %d",MONSOON_LOG_ERROR,2,GetLastError());
    RemoveMemory(window_class_name);
    return NULL;
  }
  RemoveMemory(window_class_name);

  HANDLE WindowHandle = CreateWindowExA(
    0,
    window_class.lpszClassName,
    Title,
    WS_OVERLAPPEDWINDOW,
    rect -> X,
    rect -> Y,
    rect -> Width,
    rect -> Height,
    NULL,
    NULL,
    NULL,
    NULL
  );

  if (!WindowHandle)
  {
    return NULL;
  }
  return WindowHandle;
}

MSBool MONS_Win32_CloseWindow(HANDLE Window)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_ERROR,1);
    return False;
  }

  return DestroyWindow(Window);
}

MSBool MONS_Win32_WindowPollEvent(HANDLE Window)
{
  MSG msg;
  if (PeekMessage(&msg,NULL,0,0,True))
  {
    TranslateMessage(&msg);
    return DispatchMessage(&msg);
  }
  return False;
}

void* MONS_Win32_GetWindowDrawSurface(HANDLE Window)
{
  return GetDC(Window);
}

MSBool MONS_Win32_SetPixelFormat(HDC WindowDC)
{
    PIXELFORMATDESCRIPTOR pfd = {0};

    pfd.nSize = sizeof(pfd);

    pfd.nVersion = 1;

    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

    pfd.iPixelType = PFD_TYPE_RGBA;

    pfd.cColorBits = 24;
    pfd.cAlphaBits = 8;

    pfd.cDepthBits = 24;

    pfd.cStencilBits = 8;

    pfd.iLayerType = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat( WindowDC, &pfd);
    if (!format) return False;
    SetPixelFormat(WindowDC, format, &pfd);

  return True;
}
