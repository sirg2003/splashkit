#pragma once
#include <Windows.h>

class ApplicationConfiguration
{
private:
    bool _isInViewSourceMode;

public:
    ApplicationConfiguration(LPCSTR configurationFile);
    ~ApplicationConfiguration(void);

    void setIsInViewSourceMode(bool value) { _isInViewSourceMode = value; }
    bool isInViewSourceMode() { return _isInViewSourceMode; }
};
