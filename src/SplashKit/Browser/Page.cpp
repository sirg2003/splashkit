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
    *html << "Hello from SplashKit, hosted in WebKit!" << endl;
    *html << "</html>" << endl;
}
