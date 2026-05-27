#pragma once
#include "EuroScopePlugIn.h"
#include <string>
#include <map>

// ----------------------------------------------------------------
// GOATscope – EuroScope Plugin
// Shows full airport names and IFR altitude rule checks
// in a pop-up window when you click a flight strip.
// ----------------------------------------------------------------

class GOATscopePlugin : public EuroScopePlugIn::CPlugIn
{
public:
    GOATscopePlugin();
    virtual ~GOATscopePlugin();

    // Called when a controller opens the tag menu / double-clicks a flight
    virtual void OnFunctionCall(int functionId,
                                const char* itemString,
                                POINT pt,
                                RECT area) override;

    // Register the custom tag item so it appears in ES tag settings
    virtual void OnGetTagItem(EuroScopePlugIn::CFlightPlan FlightPlan,
                              EuroScopePlugIn::CRadarTarget RadarTarget,
                              int ItemCode,
                              int TagData,
                              char sItemString[16],
                              int* pColorCode,
                              COLORREF* pRGB,
                              double* pFontSize) override;

private:
    // Airport ICAO -> full name lookup
    std::map<std::string, std::string> m_airportNames;

    void LoadAirportDatabase();
    std::string GetAirportName(const std::string& icao) const;

    // Altitude rule checkers
    // Returns true if the altitude is correct for the given magnetic track
    bool CheckICAOSemicircular(int altitudeFt, double magneticTrackDeg,
                               std::string& ruleResult) const;
    bool CheckFAAHemispheric(int altitudeFt, double magneticTrackDeg,
                             std::string& ruleResult) const;

    // Build and show the info pop-up for a flight plan
    void ShowFlightInfoPopup(EuroScopePlugIn::CFlightPlan& fp, POINT screenPt);

    // Helpers
    double GetMagneticTrack(const std::string& depICAO,
                            const std::string& arrICAO) const;

    // Tag item & function IDs
    static const int TAG_ITEM_GOATSCOPE   = 900;
    static const int FUNC_OPEN_POPUP      = 901;
};
