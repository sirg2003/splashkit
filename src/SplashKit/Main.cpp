#include <Windows.h>
#include "Host/ApplicationRuntime.h"
#include "Host/MainWindow.h"
#include <SimpleIni.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    auto runtime = new ApplicationRuntime(hInstance);
    auto main = new MainWindow(runtime);
    main->Show();
    main->Navigate(new Page());

    return runtime->Run();
}
