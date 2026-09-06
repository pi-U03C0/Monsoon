#include <shlwapi.h>
#define INCLUDE_STD
#include <Monsoon/Monsoon.h>
#include <Monsoon/SystemHeaders.h>

LRESULT CALLBACK MONS_Win32_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
        {
          MONS_Event Event = {
            .Type = MONSOON_EVENT_WINDOW_CLOSE,
            .Prarms = NULL,
          };

          MONS_PushWindowEvent((MONS_Window*)GetWindowLongPtr(hwnd,GWLP_USERDATA),&Event);
          return 0;
        };

        case (WM_SIZE):
        {
          MONS_WindowPrarmSize* Prames = GetMemory(sizeof(MONS_WindowPrarmSize));
          if (!Prames)
          {
              Error_Memory();
              return 0;
          }

          Prames -> Width = LOWORD(lParam);
          Prames -> Height = HIWORD(lParam);
          Prames -> How = MONS_Win32_WindowReSizeToStd(wParam);

          MONS_Event Event = {
              .Type = MONSOON_EVENT_WINDOW_CHANGE_SIZE,
              .Prarms = Prames
          };

          MONS_Window* Window = (MONS_Window*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
          Window -> WindowArea -> Width = Prames -> Width;
          Window -> WindowArea -> Height = Prames -> Height;

          MONS_PushWindowEvent(Window, &Event);
          return 0;
        }

        case (WM_MOVE):
        {
          MONS_WindowPrarmPosition* Prames = GetMemory(sizeof(MONS_WindowPrarmPosition));
          if (!Prames)
          {
            Error_Memory();
            return 0;
          }

          Prames -> X = (int)(short)LOWORD(lParam);
          Prames -> Y = (int)(short)HIWORD(lParam);

          MONS_Event Event = {
              .Type = MONSOON_EVENT_WINDOW_MOVE,
              .Prarms = Prames
          };

          MONS_Window* Window = (MONS_Window*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
          Window -> WindowArea -> X = Prames -> X;
          Window -> WindowArea -> Y = Prames -> Y;

          MONS_PushWindowEvent(Window, &Event);
          return 0;
        }

        case (WM_SETFOCUS):
        {
          MONS_Event Event = {
              .Type = MONSOON_EVENT_WINDOW_FOCUS,
              .Prarms = NULL
          };

          MONS_PushWindowEvent((MONS_Window*)GetWindowLongPtr(hwnd,GWLP_USERDATA), &Event);
          return 0;
        }

        case WM_KILLFOCUS:
        {
          MONS_Event Event = {
              .Type = MONSOON_EVENT_WINDOW_LOST_FOCUS,
              .Prarms = NULL
          };

          MONS_PushWindowEvent((MONS_Window*)GetWindowLongPtr(hwnd,GWLP_USERDATA), &Event);
          return 0;
        }

        case (WM_KEYUP):
        {
           MONS_WindowPrarmKey* Prarms = GetMemory(sizeof(MONS_WindowPrarmKey));
           Prarms -> Key = (uint32_t)wParam;
           Prarms -> Repeat = (uint16_t)LOWORD(lParam);
           Prarms -> ScanCode = (uint8_t)((lParam >> 16) & 0xFF);
           Prarms -> IsExtended = (lParam & (1ULL << 24)) != 0;
           Prarms -> IsRepeat = (lParam & (1ULL << 30)) != 0;

           MONS_Event Event = {
              .Type = MONSOON_EVENT_KEY_UP,
              .Prarms = Prarms
           };

           LOG("Win32 Window Proc KeyUP: Key=%d(%c)",MONSOON_LOG_HIGHT_DEBUG,255,Prarms -> Key,Prarms -> Key);
           MONS_PushWindowEvent((MONS_Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA), &Event);
           return 0;
        }

        case (WM_KEYDOWN):
        {
           MONS_WindowPrarmKey* Prarms = GetMemory(sizeof(MONS_WindowPrarmKey));
           Prarms -> Key = (uint32_t)wParam;
           Prarms -> Repeat = (uint16_t)LOWORD(lParam);
           Prarms -> ScanCode = (uint8_t)((lParam >> 16) & 0xFF);
           Prarms -> IsExtended = (lParam & (1ULL << 24)) != 0;
           Prarms -> IsRepeat = (lParam & (1ULL << 30)) != 0;

           MONS_Event Event = {
              .Type = MONSOON_EVENT_KEY_DOWN,
              .Prarms = Prarms
           };

           LOG("Win32 Window Proc KeyDown: Key=%d(%c)",MONSOON_LOG_HIGHT_DEBUG,255,Prarms -> Key,Prarms -> Key);
           MONS_PushWindowEvent((MONS_Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA), &Event);
           return 0;
        }

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

  if (!RegisterClass(&window_class))
  {
    LOG("Unable to Register Class,Win32 ErrorCode = %d",MONSOON_LOG_ERROR,2,GetLastError());
    RemoveMemory(window_class_name);
    return NULL;
  }

  HANDLE WindowHandle = CreateWindowEx(
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

  RemoveMemory(window_class_name);
  if (!WindowHandle)
  {
    return NULL;
  }
  return WindowHandle;
}

MSBool MONS_Win32_CloseWindow(HANDLE Window)
{
  if (!Window && (!IsWindow(Window)))
  {
    LOG("The Window Handle was InValid",MONSOON_LOG_ERROR,MONSOON_LOG_INVALID);
    return False;
  }

  return DestroyWindow(Window);
}

MSBool MONS_Win32_WindowPollEvent(HANDLE Window)
{
  if (!Window && (!IsWindow(Window)))
  {
    LOG("The Window Handle was InValid",MONSOON_LOG_ERROR,MONSOON_LOG_INVALID);;
    return False;
  }

  MSG msg;
  if (PeekMessage(&msg,Window,0,0,True))
  {
    TranslateMessage(&msg);
    return DispatchMessage(&msg);
  }
  return False;
}

void* MONS_Win32_GetWindowDrawSurface(HANDLE Window)
{
  if (!Window)
  {
    LOG("Window was NULL",MONSOON_LOG_ERROR,1);
    return False;
  }

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

uint8_t MONS_Win32_WindowReSizeToStd(uint8_t How)
{
  switch (How)
  {
    case (SIZE_RESTORED):
    {
      return MONS_WINDOW_RESIZE;
    }
    case (SIZE_MINIMIZED):
    {
       return MONS_WINDOW_MINIMIZED;
    }
    case (SIZE_MAXIMIZED):
    {
      return MONS_WINDOW_MAXIMIZED;
    }
    default:return False;
  }
}
