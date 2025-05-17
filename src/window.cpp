#include <window.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


Window::Window()
    : m_hInstance(GetModuleHandle(nullptr))
{
    const wchar_t* CLASS_NAME = L"Windows Class";

    WNDCLASS wndClass = {};
    wndClass.lpszClassName =  CLASS_NAME;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc; //foo

    RegisterClass(&wndClass);

    DWORD stile = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    int width = 640;
    int height = 480;
    RECT rect; 
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, stile, false);

    m_hWnd = CreateWindowEx(
        0, 
        CLASS_NAME,
        L"Title",
        stile,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL, // menus
        NULL,
        m_hInstance,
        NULL
    );

    ShowWindow(m_hWnd, SW_SHOW);
} 

Window::~Window()
    
{
    const wchar_t* CLASS_NAME = L"Windows Class";
    UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::proccesMessages()
{
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message = WM_QUIT) 
            return false;
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}
