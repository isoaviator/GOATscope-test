#include "GOATscope.h"
#include "AirportDB.h"
#include <cmath>
#include <sstream>
#include <iomanip>

// ----------------------------------------------------------------
// EuroScope plugin entry point – called by ES on DLL load
// ----------------------------------------------------------------
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

// ----------------------------------------------------------------
// Constructor / Destructor
// ----------------------------------------------------------------
GOATscopePlugin::GOATscopePlugin()
    : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
              "GOATscope",
              "1.0.0",
              "GOATscope Dev",
              "Free to use on VATSIM")
{
    LoadAirportDatabase();

    // Register our custom tag item
    RegisterTagItemType("GOATscope Info", TAG_ITEM_GOATSCOPE);
    RegisterTagItemFunction("Open GOATscope Popup", FUNC_OPEN_POPUP);

    DisplayUserMessage("GOATscope", "System",
        "GOATscope v1.0.0 loaded. Click a tag item to open flight info.",
        true, true, false, false, false);
}

GOATscopePlugin::~GOATscopePlugin() {}

// ----------------------------------------------------------------
// Load airport database
// ----------------------------------------------------------------
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

// ----------------------------------------------------------------
// Tag item – shows a small "GOAT" indicator in the radar label
// ----------------------------------------------------------------
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

    // Show a tiny clickable marker in the tag
    strncpy_s(sItemString, 16, "[GOAT]", _TRUNCATE);
    *pColorCode = EuroScopePlugIn::TAG_COLOR_RGB_DEFINED;
    *pRGB = RGB(255, 215, 0); // Gold colour – because we're the GOATs
}

// ----------------------------------------------------------------
// Function call – fired when user clicks the tag item
// ----------------------------------------------------------------
void GOATscopePlugin::OnFunctionCall(
    int         functionId,
    const char* itemString,
    POINT       pt,
    RECT        area)
{
    if (functionId != FUNC_OPEN_POPUP)
        return;

    // Find the selected flight plan
    EuroScopePlugIn::CFlightPlan fp =
        FlightPlanSelectASEL(); // returns controller's ASEL (selected) FP

    if (!fp.IsValid())
    {
        DisplayUserMessage("GOATscope", "Error",
            "No flight plan selected. Click a strip first.",
            true, true, false, false, false);
        return;
    }

    ShowFlightInfoPopup(fp, pt);
}

// ----------------------------------------------------------------
// Altitude rule: ICAO Semicircular Rule
//   Eastbound (0°–179° magnetic): odd thousands  (FL090, FL110 …)
//   Westbound (180°–359° magnetic): even thousands (FL100, FL120 …)
// ----------------------------------------------------------------
bool GOATscopePlugin::CheckICAOSemicircular(int altitudeFt,
                                             double magneticTrackDeg,
                                             std::string& ruleResult) const
{
    int thousands = altitudeFt / 1000;
    bool isOdd    = (thousands % 2) != 0;
    bool eastbound = (magneticTrackDeg >= 0.0 && magneticTrackDeg < 180.0);

    bool correct = eastbound ? isOdd : !isOdd;

    std::ostringstream oss;
    oss << "ICAO Semicircular: "
        << (eastbound ? "Eastbound" : "Westbound")
        << " → expects " << (eastbound ? "ODD" : "EVEN") << " thousands. "
        << "Filed FL" << std::setfill('0') << std::setw(3) << (altitudeFt / 100)
        << " → " << (correct ? "✔ CORRECT" : "✘ INCORRECT");
    ruleResult = oss.str();
    return correct;
}

// ----------------------------------------------------------------
// Altitude rule: FAA Hemispheric Rule (VFR & IFR)
//   Eastbound (0°–179° magnetic):
//     IFR: odd thousands  (3000, 5000, 7000 …)
//     VFR: odd thousands + 500 (3500, 5500 …)
//   Westbound (180°–359° magnetic):
//     IFR: even thousands (4000, 6000, 8000 …)
//     VFR: even thousands + 500 (4500, 6500 …)
// ----------------------------------------------------------------
bool GOATscopePlugin::CheckFAAHemispheric(int altitudeFt,
                                           double magneticTrackDeg,
                                           std::string& ruleResult) const
{
    bool eastbound = (magneticTrackDeg >= 0.0 && magneticTrackDeg < 180.0);
    int  thousands = altitudeFt / 1000;
    int  remainder = altitudeFt % 1000;
    bool isOdd     = (thousands % 2) != 0;

    // IFR check (no +500 offset)
    bool ifrCorrect = eastbound ? (isOdd && remainder == 0)
                                : (!isOdd && remainder == 0);

    std::ostringstream oss;
    oss << "FAA Hemispheric: "
        << (eastbound ? "Eastbound" : "Westbound")
        << " → IFR expects " << (eastbound ? "ODD" : "EVEN") << " thousands. "
        << "Filed " << altitudeFt << " ft → "
        << (ifrCorrect ? "✔ CORRECT" : "✘ INCORRECT");
    ruleResult = oss.str();
    return ifrCorrect;
}

// ----------------------------------------------------------------
// Rough magnetic track between two airports using their
// EuroScope-provided lat/lon (great-circle initial bearing)
// ----------------------------------------------------------------
double GOATscopePlugin::GetMagneticTrack(const std::string& depICAO,
                                          const std::string& arrICAO) const
{
    // Fetch airport positions from the ES sector file
    EuroScopePlugIn::CSectorElement dep =
        SectorFileElementSelectFirst(EuroScopePlugIn::SECTOR_ELEMENT_AIRPORT);

    double depLat = 0, depLon = 0, arrLat = 0, arrLon = 0;
    bool   foundDep = false, foundArr = false;

    while (dep.IsValid())
    {
        std::string name = dep.GetName();
        if (name == depICAO && !foundDep)
        {
            dep.GetPosition(&EuroScopePlugIn::CPosition(), 0);
            // Use the position directly
            EuroScopePlugIn::CPosition pos = dep.GetPosition(nullptr, 0);
            depLat = pos.m_Latitude;
            depLon = pos.m_Longitude;
            foundDep = true;
        }
        if (name == arrICAO && !foundArr)
        {
            EuroScopePlugIn::CPosition pos = dep.GetPosition(nullptr, 0);
            arrLat = pos.m_Latitude;
            arrLon = pos.m_Longitude;
            foundArr = true;
        }
        if (foundDep && foundArr) break;
        dep = SectorFileElementSelectNext(dep, EuroScopePlugIn::SECTOR_ELEMENT_AIRPORT);
    }

    if (!foundDep || !foundArr)
        return 0.0; // can't determine – default to eastbound

    // Great-circle initial bearing
    const double DEG2RAD = M_PI / 180.0;
    const double RAD2DEG = 180.0 / M_PI;

    double lat1 = depLat * DEG2RAD;
    double lat2 = arrLat * DEG2RAD;
    double dLon = (arrLon - depLon) * DEG2RAD;

    double y = std::sin(dLon) * std::cos(lat2);
    double x = std::cos(lat1) * std::sin(lat2)
             - std::sin(lat1) * std::cos(lat2) * std::cos(dLon);

    double bearing = std::atan2(y, x) * RAD2DEG;
    bearing = std::fmod(bearing + 360.0, 360.0); // normalize to 0–360

    // Note: this is a TRUE bearing; for proper magnetic we'd need a
    // variation lookup. For VATSIM purposes true ≈ magnetic is acceptable,
    // but you can add a WMM variation table here for precision.
    return bearing;
}

// ----------------------------------------------------------------
// Build the pop-up info string and display it via ES message box
// ----------------------------------------------------------------
void GOATscopePlugin::ShowFlightInfoPopup(
    EuroScopePlugIn::CFlightPlan& fp,
    POINT screenPt)
{
    // ── Gather flight plan data ──────────────────────────────────
    std::string callsign  = fp.GetCallsign();
    std::string depICAO   = fp.GetFlightPlanData().GetOrigin();
    std::string arrICAO   = fp.GetFlightPlanData().GetDestination();
    std::string altStr    = fp.GetFlightPlanData().GetFinalAltitude();
    std::string acType    = fp.GetFlightPlanData().GetAircraftFPType();
    std::string route     = fp.GetFlightPlanData().GetRoute();
    std::string flightRules = fp.GetFlightPlanData().GetPlanType(); // I / V / Y / Z

    // Parse altitude (can be FL090 or 9000)
    int altitudeFt = 0;
    if (!altStr.empty())
    {
        if (altStr[0] == 'F' || altStr[0] == 'f') // "FL090" style
            altitudeFt = std::stoi(altStr.substr(2)) * 100;
        else
            altitudeFt = std::stoi(altStr);
    }

    // ── Airport names ────────────────────────────────────────────
    std::string depName = GetAirportName(depICAO);
    std::string arrName = GetAirportName(arrICAO);

    // ── Magnetic track & altitude checks ─────────────────────────
    double track = GetMagneticTrack(depICAO, arrICAO);
    std::string icaoResult, faaResult;
    bool icaoOk = CheckICAOSemicircular(altitudeFt, track, icaoResult);
    bool faaOk  = CheckFAAHemispheric  (altitudeFt, track, faaResult);

    // ── Build display string ──────────────────────────────────────
    std::ostringstream msg;
    msg << "╔══════════════════════════════════════════╗\n";
    msg << "  GOATscope – " << callsign << "\n";
    msg << "╠══════════════════════════════════════════╣\n";
    msg << "  A/C Type : " << acType                           << "\n";
    msg << "  Rules    : " << flightRules                      << "\n";
    msg << "  DEP      : " << depICAO << " – " << depName      << "\n";
    msg << "  ARR      : " << arrICAO << " – " << arrName      << "\n";
    msg << "  Altitude : " << altStr
        << " (" << altitudeFt << " ft)"                        << "\n";
    msg << "  Track    : " << std::fixed << std::setprecision(1)
        << track << "° (true)"                                 << "\n";
    msg << "──────────────────────────────────────────\n";
    msg << "  " << icaoResult                                  << "\n";
    msg << "  " << faaResult                                   << "\n";
    msg << "╚══════════════════════════════════════════╝";

    // Display in the EuroScope message area (top-right chat)
    DisplayUserMessage(
        "GOATscope",           // channel name
        callsign.c_str(),      // sender label
        msg.str().c_str(),     // message body
        true,   // show in message area
        true,   // flash taskbar
        false,  // sound
        false,  // override
        false   // private
    );
}
