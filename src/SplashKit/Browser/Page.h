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

private:
    void RenderInternal(std::ostream *html);
};
