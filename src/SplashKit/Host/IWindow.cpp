#include "IWindow.h"


IWindow::IWindow(void)
{   
}


IWindow::~IWindow(void)
{
}

bool IWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}
