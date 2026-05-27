#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "GOATscope.h"
#include "AirportDB.h"

GOATscopePlugin* g_pPlugin = nullptr;

void __declspec(dllexport) EuroScopePlugInInit(EuroScopePlugIn::CPlugIn** ppPlugin)
{
    *ppPlugin = g_pPlugin = new GOATscopePlugin();
}

void __declspec(dllexport) EuroScopePlugInExit()
{
    delete g_pPlugin;
    g_pPlugin = nullptr;
}

GOATscopePlugin::GOATscopePlugin()
    : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
              "GOATscope", "1.0.0", "GOATscope Dev", "Free to use on VATSIM")
{
    LoadAirportDatabase();
    RegisterTagItemType("GOATscope Info", TAG_ITEM_GOATSCOPE);
    RegisterTagItemFunction("Open GOATscope Popup", FUNC_OPEN_POPUP);
    DisplayUserMessage("GOAT
