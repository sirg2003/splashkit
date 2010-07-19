#pragma once
#include <Windows.h>

class IWindow
{
public: 
    IWindow(void);
    ~IWindow(void);
    virtual bool HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

