#pragma once
#include <Windows.h>
#include <WebKit/WebKit.h>
#include <WebKit/WebKitCOMAPI.h>
#include <JavaScriptCore/JavaScript.h>
#include <commctrl.h>
#include <commdlg.h>
#include <objbase.h>
#include <shlwapi.h>
#include <wininet.h>
#include "../Resources/Resource.h"
#include <atlbase.h>
#include <string>
#include "IWindow.h"
#include "ApplicationRuntime.h"
#include "../Browser/Page.h"

class MainWindow : IWindow
{
private:
    HINSTANCE _hInstance;
    HWND _hMainWnd;
    long _DefEditProc;
    IWebView* _webView;
    HWND _viewWindow;
    bool _isShown;

protected:
    virtual bool HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
    MainWindow(ApplicationRuntime * instance);
    ~MainWindow(void);

    void Navigate(Page *page);
    void Navigate(string *str);
    void Navigate(LPCSTR str);
    void Navigate(LPCSTR str, vector<JSStaticFunction>* functions);

    void Show();
};

