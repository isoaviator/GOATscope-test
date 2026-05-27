#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES
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
              "GOATscope",
              "1.0.0",
              "GOATscope Dev",
              "Free to use on VATSIM")
{
    LoadAirportDatabase();
    RegisterTagItemType("GOATscope Info", TAG_ITEM_GOATSCOPE);
    RegisterTagItemFunction("Open GOATscope Popup", FUNC_OPEN_POPUP);
    DisplayUserMessage("GOATscope", "System",
        "GOATscope v1.0.0 loaded. Click a tag item to open flight info.",
        true, true, false, false, false);
}

GOATscopePlugin::~GOATscopePlugin() {}

void GOATscopePlugin::LoadAirportDatabase()
{
    PopulateAirportNames(m_airportNames);
}

std::string GOATscopePlugin::GetAirportName(const std::string& icao) const
{
    auto it = m_airportNames.find(icao);
    if (it != m_airportNames.end())
        return it->second;
    return "(Unknown Airport)";
}

void GOATscopePlugin::OnGetTagItem(
    EuroScopePlugIn::CFlightPlan   FlightPlan,
    EuroScopePlugIn::CRadarTarget  RadarTarget,
    int    ItemCode,
    int    TagData,
    char   sItemString[16],
    int*   pColorCode,
    COLORREF* pRGB,
    double* pFontSize)
{
    if (ItemCode != TAG_ITEM_GOATSCOPE)
        return;
    strncpy_s(sItemString, 16, "[GOAT]", _TRUNCATE);
    *pColorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
    *pRGB = RGB(255, 215, 0);
}

void GOATscopePlugin::OnFunctionCall(
    int         functionId,
    const char* itemString,
    POINT       pt,
    RECT        area)
{
    if (functionId != FUNC_OPEN_POPUP)
        return;
    EuroScopePlugIn::CFlightPlan fp = FlightPlanSelectASEL();
    if (!fp.IsValid())
    {
        DisplayUserMessage("GOATscope", "Error",
            "No flight plan selected. Click a strip first.",
            true, true, false, false, false);
        return;
    }
    ShowFlightInfoPopup(fp, pt);
}

bool GOATscopePlugin::CheckICAOSemicircular(int altitudeFt,
