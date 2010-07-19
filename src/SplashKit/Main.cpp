#include <Windows.h>
#include "Host/ApplicationRuntime.h"
#include "Host/ApplicationConfiguration.h"
#include "Host/MainWindow.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    auto configuration = new ApplicationConfiguration("D:\\Code\\SplashKit\\src\\bin\\Debug\\SplashKit.ini");

    auto runtime = new ApplicationRuntime(hInstance);
    auto main = new MainWindow(runtime, configuration);
    main->Show();
    main->Navigate(new Page());

    return runtime->Run();
}
