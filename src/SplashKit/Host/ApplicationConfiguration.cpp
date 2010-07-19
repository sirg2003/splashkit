#include "ApplicationConfiguration.h"
#include <SimpleIni.h>

ApplicationConfiguration::ApplicationConfiguration(LPCSTR configurationFile)
{
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile(configurationFile);
    
    _isInViewSourceMode = ini.GetBoolValue("Debug", "ViewSource", false, false);
}

ApplicationConfiguration::~ApplicationConfiguration(void)
{
}
