#include "Window.h"

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
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));

        EndPaint(hWnd, &ps);
    }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
    : m_hInstance(GetModuleHandle(nullptr))
{
    const wchar_t* CLASS_NAME = L"Tutorial Window Class";

    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIconW(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_MINIMIZE | WS_SYSMENU;

    int width = 640;
    int height = 480;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false); // change to true to see what happens

    m_hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Tutorial Window",
        style,
        rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
        NULL,
        NULL,
        m_hInstance,
        NULL
    );

    ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
    const wchar_t* CLASS_NAME = L"Tutorial Window Class";

    UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return false;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
     
    return true;
}
