#ifndef _LWINDOW
#define _LWINDOW

#include<Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
    Window();
    ~Window();
    
    Window(const Window&) = delete;
    Window& operator = (const Window&) = delete;

    bool proccesMessages();
private:
    HINSTANCE m_hInstance;
    HWND m_hWnd;
};

#endif