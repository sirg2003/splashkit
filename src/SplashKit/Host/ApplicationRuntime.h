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

    void Enlist(IWindow *window);

    // Methods
    int Run();

    static LRESULT CALLBACK ApplicationRuntime::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

