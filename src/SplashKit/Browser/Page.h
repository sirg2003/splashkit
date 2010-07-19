#pragma once
#include <sstream>
#include <vector>
#include <Windows.h>
#include <JavaScriptCore/JavaScript.h>

using namespace std;

class Page
{
public:
    Page(void);
    ~Page(void);
    string Render();
    vector<JSStaticFunction> GetScripts() { return _scripts; }

protected:
    virtual void RenderMainContent(std::ostream *html);
    void AddScript(LPCSTR name, JSObjectCallAsFunctionCallback callback);

private:
    vector<JSStaticFunction> _scripts;
    void RenderInternal(std::ostream *html);
};
