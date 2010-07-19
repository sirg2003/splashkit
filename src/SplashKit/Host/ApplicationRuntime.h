#include <Windows.h>
#include <vector>
#include "IWindow.h"

#pragma once



class ApplicationRuntime
{
public:
    HINSTANCE Instance;

    // Lifetime
    ApplicationRuntime(HINSTANCE instance);
    ~ApplicationRuntime();

    // Methods
    template <class T> T* CreateNewWindow() 
    {
        auto window = new T(_hInstance);
        _windows.push_back(*window);
        return window;
    }

    int Run();

    static LRESULT CALLBACK ApplicationRuntime::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

