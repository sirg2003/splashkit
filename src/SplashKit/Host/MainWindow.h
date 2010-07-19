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
#include "ApplicationConfiguration.h"
#include "../Browser/Page.h"

class MainWindow : public IWindow
{
private:
    HINSTANCE _hInstance;
    HWND _hMainWnd;
    long _DefEditProc;
    IWebView* _webView;
    HWND _viewWindow;
    bool _isShown;
    ApplicationConfiguration *_configuration;

protected:

public:
    MainWindow(ApplicationRuntime *instance, ApplicationConfiguration *configuration);
    ~MainWindow(void);

    void Navigate(Page *page);
    void Navigate(string *str);
    void Navigate(LPCSTR str);
    
    virtual bool HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    
    void Show();
};

