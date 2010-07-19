#include "Page.h"

using namespace std;

Page::Page(void)
{
}

Page::~Page(void)
{
}

string Page::Render() 
{
    std::stringstream strm;
    RenderInternal(&strm);
    return strm.str();
}

void Page::RenderInternal(std::ostream* html)
{
    *html << "<html>" << endl;
    RenderMainContent(html);
    *html << "</html>" << endl;
}

void Page::RenderMainContent(std::ostream* html)
{
    *html << "Hello from SplashKit!" << endl;
}

void Page::AddScript(LPCSTR name, JSObjectCallAsFunctionCallback callback)
{
    JSStaticFunction f = { "mymethod", callback, kJSPropertyAttributeReadOnly };
    _scripts.push_back(f);
}