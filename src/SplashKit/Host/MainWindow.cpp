#include "MainWindow.h"
#include "ApplicationRuntime.h"

MainWindow::MainWindow(ApplicationRuntime *runtime, ApplicationConfiguration *configuration)
{
    _isShown = false;
    _hInstance = runtime->Instance;
    _configuration = configuration;
    runtime->Enlist(this);
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::Show() 
{
    if (_isShown) 
        return;
    
    _isShown = true;

    MSG msg;
    INITCOMMONCONTROLSEX initCtrlEx;
    initCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
    initCtrlEx.dwICC  = 0x00004000;
    InitCommonControlsEx(&initCtrlEx);

    WNDCLASS wndclass ;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = ApplicationRuntime::WndProc;
    wndclass.cbClsExtra = 0 ;
    wndclass.cbWndExtra = 0 ;
    wndclass.hInstance = _hInstance;
    wndclass.hIcon = LoadIcon (_hInstance, MAKEINTRESOURCE(IDI_FALLBACKICON)) ;
    wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1) ;
    wndclass.lpszMenuName = "AppMenu";
    wndclass.lpszClassName = "Bootstrapper";
    RegisterClass (&wndclass) ;

    _hMainWnd = CreateWindow ("Bootstrapper", "Welcome to Immedic",
       WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
       CW_USEDEFAULT, CW_USEDEFAULT,
       CW_USEDEFAULT, CW_USEDEFAULT,
       NULL, NULL, _hInstance, NULL) ;

    ShowWindow(_hMainWnd, SW_MAXIMIZE);
    UpdateWindow(_hMainWnd);
    
    OleInitialize(NULL);

    HRESULT hr = WebKitCreateInstance(CLSID_WebView, 0, IID_IWebView, (void**)&_webView);
    if (FAILED(hr))
        throw "Could not create webkit";

    hr = _webView->setHostWindow((OLE_HANDLE) _hMainWnd);
    if (FAILED(hr))
        throw "Could not initialize webkit in main window";

    RECT clientRect;
    GetClientRect(_hMainWnd, &clientRect);
    hr = _webView->initWithFrame(clientRect, 0, 0);
    if (FAILED(hr))
        throw "Could not initialize frame";

    IWebPreferences *prefs = NULL;
    if (!FAILED(_webView->preferences(&prefs)))
    {
        prefs->setJavaScriptEnabled(TRUE);
        prefs->setFontSmoothing(FontSmoothingTypeWindows);
        prefs->setPrivateBrowsingEnabled(TRUE);
        prefs->setAutosaves(FALSE);
        prefs->setMinimumFontSize(5);
    }

    Navigate("");

    IWebViewPrivate* viewExt;
    _webView->QueryInterface(IID_IWebViewPrivate, (void**)&viewExt);

    if (_configuration->isInViewSourceMode())
    {
        viewExt->setInViewSourceMode(TRUE);
    }

    hr = viewExt->viewWindow((OLE_HANDLE*) &_viewWindow);
    viewExt->Release();
    if (FAILED(hr) || !_viewWindow)
        throw "Unable to set view window";
    
    RECT rcClient;
    GetClientRect(_hMainWnd, &rcClient);
    MoveWindow(_viewWindow, 0, 0, rcClient.right, rcClient.bottom, TRUE);

    ShowWindow(_viewWindow, SW_MAXIMIZE);
    UpdateWindow(_viewWindow);
    SetForegroundWindow(_hMainWnd);					
	SetFocus(_hMainWnd);		
}

bool MainWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_SIZE:
            if (!_webView)
                break;

            RECT rcClient;
            GetClientRect(_hMainWnd, &rcClient);
            MoveWindow(_viewWindow, 0, 0, rcClient.right, rcClient.bottom, TRUE);
            return TRUE;
    }
    return FALSE;
}

void MainWindow::Navigate(Page *page)
{
    auto str = page->Render();
    Navigate(str.c_str());
}

void MainWindow::Navigate(string *str)
{
    Navigate(str->c_str());
}

static void myclass_init_cb(JSContextRef ctx, JSObjectRef object)
{
}

static void myclass_finalize_cb(JSObjectRef object)
{
}

static JSValueRef myclass_mymethod(JSContextRef context, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
    JSStringRef string = JSStringCreateWithUTF8CString("JS goes here");
    return JSValueMakeString(context, string);
}

static void AddJSClasses(JSGlobalContextRef context, vector<JSStaticFunction>* functions)
{
    //JSStaticFunction f = { NULL, NULL, 0 };
    //functions->push_back(f);

    JSClassDefinition class_def =
    {
        0,
        kJSClassAttributeNone,
        "TestClass",
        NULL,

        NULL,
        NULL,

        myclass_init_cb,
        myclass_finalize_cb,

        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    };

    //class_def.staticFunctions = (const JSStaticFunction*)&functions[0];

    JSClassRef classDef = JSClassCreate(&class_def);
    JSObjectRef classObj = JSObjectMake(context, classDef, context);
    JSObjectRef globalObj = JSContextGetGlobalObject(context);
    JSStringRef str = JSStringCreateWithUTF8CString("host");
    JSObjectSetProperty(context, globalObj, str, classObj, kJSPropertyAttributeNone, NULL);
}

void MainWindow::Navigate(LPCSTR str)
{
    IWebFrame* frame;
    _webView->mainFrame(&frame);
    const CComBSTR bstr(str);

    //AddJSClasses(frame->globalContext(), NULL);
    frame->loadHTMLString(bstr, 0);
    frame->Release();
}
