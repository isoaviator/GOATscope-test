#pragma once
#include <map>
#include <string>

// ----------------------------------------------------------------
// Subset of the global ICAO airport database.
// Add entries freely – format is { "ICAO", "Full Name" }.
// A real deployment should load this from a CSV/JSON at runtime,
// but this inline map works great for VATSIM coverage.
// ----------------------------------------------------------------

inline void PopulateAirportNames(std::map<std::string, std::string>& db)
{
    // ── United States ────────────────────────────────────────────
    db["KATL"] = "Hartsfield-Jackson Atlanta International Airport";
    db["KLAX"] = "Los Angeles International Airport";
    db["KORD"] = "Chicago O'Hare International Airport";
    db["KDFW"] = "Dallas/Fort Worth International Airport";
    db["KDEN"] = "Denver International Airport";
    db["KJFK"] = "John F. Kennedy International Airport";
    db["KSFO"] = "San Francisco International Airport";
    db["KLAS"] = "Harry Reid International Airport";
    db["KMIA"] = "Miami International Airport";
    db["KPHX"] = "Phoenix Sky Harbor International Airport";
    db["KIAH"] = "George Bush Intercontinental Airport";
    db["KMCO"] = "Orlando International Airport";
    db["KBOS"] = "Boston Logan International Airport";
    db["KEWR"] = "Newark Liberty International Airport";
    db["KLGA"] = "LaGuardia Airport";
    db["KBWI"] = "Baltimore/Washington International Airport";
    db["KIAD"] = "Washington Dulles International Airport";
    db["KDCA"] = "Ronald Reagan Washington National Airport";
    db["KPHL"] = "Philadelphia International Airport";
    db["KCLT"] = "Charlotte Douglas International Airport";
    db["KSLC"] = "Salt Lake City International Airport";
    db["KPDX"] = "Portland International Airport";
    db["KSEA"] = "Seattle-Tacoma International Airport";
    db["KMSP"] = "Minneapolis-Saint Paul International Airport";
    db["KDTW"] = "Detroit Metropolitan Wayne County Airport";
    db["KSTL"] = "St. Louis Lambert International Airport";
    db["KMEM"] = "Memphis International Airport";
    db["KBNA"] = "Nashville International Airport";
    db["KRDU"] = "Raleigh-Durham International Airport";
    db["KCVG"] = "Cincinnati/Northern Kentucky International Airport";
    db["KCLE"] = "Cleveland Hopkins International Airport";
    db["KPIT"] = "Pittsburgh International Airport";
    db["KIND"] = "Indianapolis International Airport";
    db["KFLL"] = "Fort Lauderdale-Hollywood International Airport";
    db["KTPA"] = "Tampa International Airport";
    db["KMKE"] = "Milwaukee Mitchell International Airport";
    db["KOKC"] = "Will Rogers World Airport";
    db["KTUL"] = "Tulsa International Airport";
    db["KABQ"] = "Albuquerque International Sunport";
    db["KELP"] = "El Paso International Airport";
    db["KSAN"] = "San Diego International Airport";
    db["KSNA"] = "John Wayne Airport";
    db["KOAK"] = "Oakland International Airport";
    db["KSJC"] = "San Jose International Airport";
    db["KSMF"] = "Sacramento International Airport";
    db["KANC"] = "Ted Stevens Anchorage International Airport";
    db["PHNL"] = "Daniel K. Inouye International Airport";
    db["KMDW"] = "Chicago Midway International Airport";
    db["KHOU"] = "William P. Hobby Airport";
    db["KDAL"] = "Dallas Love Field";
    db["KAUS"] = "Austin-Bergstrom International Airport";
    db["KSAT"] = "San Antonio International Airport";
    db["KMSY"] = "Louis Armstrong New Orleans International Airport";
    db["KJAX"] = "Jacksonville International Airport";
    db["KRIC"] = "Richmond International Airport";
    db["KSRQ"] = "Sarasota Bradenton International Airport";
    db["KRSW"] = "Southwest Florida International Airport";
    db["KPBI"] = "Palm Beach International Airport";

    // ── Canada ───────────────────────────────────────────────────
    db["CYYZ"] = "Toronto Pearson International Airport";
    db["CYVR"] = "Vancouver International Airport";
    db["CYUL"] = "Montréal-Pierre Elliott Trudeau International Airport";
    db["CYYC"] = "Calgary International Airport";
    db["CYOW"] = "Ottawa Macdonald-Cartier International Airport";
    db["CYEG"] = "Edmonton International Airport";
    db["CYWG"] = "Winnipeg James Armstrong Richardson International Airport";
    db["CYQB"] = "Québec City Jean Lesage International Airport";
    db["CYHZ"] = "Halifax Stanfield International Airport";
    db["CYXE"] = "Saskatoon John G. Diefenbaker International Airport";
    db["CYQR"] = "Regina International Airport";
    db["CYJT"] = "Stephenville International Airport";
    db["CYYT"] = "St. John's International Airport";

    // ── United Kingdom ───────────────────────────────────────────
    db["EGLL"] = "London Heathrow Airport";
    db["EGKK"] = "London Gatwick Airport";
    db["EGSS"] = "London Stansted Airport";
    db["EGGW"] = "London Luton Airport";
    db["EGCC"] = "Manchester Airport";
    db["EGBB"] = "Birmingham Airport";
    db["EGPH"] = "Edinburgh Airport";
    db["EGPF"] = "Glasgow International Airport";
    db["EGNX"] = "East Midlands Airport";
    db["EGGD"] = "Bristol Airport";
    db["EGNT"] = "Newcastle International Airport";
    db["EGHI"] = "Southampton Airport";
    db["EGAA"] = "Belfast International Airport";
    db["EGAC"] = "Belfast City Airport";
    db["EGDL"] = "RAF Lyneham";
    db["EGLF"] = "Farnborough Airport";

    // ── Europe ───────────────────────────────────────────────────
    db["EDDF"] = "Frankfurt Airport";
    db["EDDM"] = "Munich Airport";
    db["EDDB"] = "Berlin Brandenburg Airport";
    db["EDDL"] = "Düsseldorf Airport";
    db["EDDH"] = "Hamburg Airport";
    db["EDDS"] = "Stuttgart Airport";
    db["EDDP"] = "Leipzig/Halle Airport";
    db["EHAM"] = "Amsterdam Schiphol Airport";
    db["EHRD"] = "Rotterdam The Hague Airport";
    db["LFPG"] = "Paris Charles de Gaulle Airport";
    db["LFPO"] = "Paris Orly Airport";
    db["LFML"] = "Marseille Provence Airport";
    db["LFLL"] = "Lyon-Saint Exupéry Airport";
    db["LFMN"] = "Nice Côte d'Azur Airport";
    db["LEMD"] = "Adolfo Suárez Madrid-Barajas Airport";
    db["LEBL"] = "Josep Tarradellas Barcelona-El Prat Airport";
    db["LEMG"] = "Málaga-Costa del Sol Airport";
    db["LEPA"] = "Palma de Mallorca Airport";
    db["LPPT"] = "Lisbon Humberto Delgado Airport";
    db["LIRF"] = "Rome Fiumicino Airport";
    db["LIML"] = "Milan Linate Airport";
    db["LIMC"] = "Milan Malpensa Airport";
    db["LIME"] = "Bergamo Orio al Serio Airport";
    db["LICJ"] = "Palermo Falcone-Borsellino Airport";
    db["LSZH"] = "Zurich Airport";
    db["LSGG"] = "Geneva Airport";
    db["LOWW"] = "Vienna International Airport";
    db["LKPR"] = "Václav Havel Airport Prague";
    db["EPWA"] = "Warsaw Chopin Airport";
    db["EPKK"] = "John Paul II International Airport Kraków-Balice";
    db["EKCH"] = "Copenhagen Airport";
    db["ESSA"] = "Stockholm Arlanda Airport";
    db["ENGM"] = "Oslo Gardermoen Airport";
    db["EFHK"] = "Helsinki-Vantaa Airport";
    db["EVRA"] = "Riga International Airport";
    db["EYKA"] = "Kaunas Airport";
    db["EYVI"] = "Vilnius Airport";
    db["EETN"] = "Lennart Meri Tallinn Airport";
    db["LBSF"] = "Sofia Airport";
    db["LRCL"] = "Cluj-Napoca International Airport";
    db["LROP"] = "Henri Coandă International Airport";
    db["LDZA"] = "Zagreb Airport";
    db["LJLJ"] = "Ljubljana Jože Pučnik Airport";
    db["LKMT"] = "Ostrava Leoš Janáček Airport";
    db["UKBB"] = "Boryspil International Airport";
    db["UKKK"] = "Kyiv Igor Sikorsky International Airport";
    db["URSS"] = "Sochi International Airport";
    db["UUEE"] = "Moscow Sheremetyevo International Airport";
    db["UUDD"] = "Moscow Domodedovo International Airport";
    db["UUWW"] = "Moscow Vnukovo International Airport";
    db["ULLI"] = "St. Petersburg Pulkovo Airport";

    // ── Middle East ──────────────────────────────────────────────
    db["OMDB"] = "Dubai International Airport";
    db["OMDW"] = "Al Maktoum International Airport";
    db["OMAA"] = "Abu Dhabi International Airport";
    db["OKBK"] = "Kuwait International Airport";
    db["OEJN"] = "King Abdulaziz International Airport";
    db["OERK"] = "King Khalid International Airport";
    db["OEDF"] = "King Fahd International Airport";
    db["OTHH"] = "Hamad International Airport";
    db["OBBI"] = "Bahrain International Airport";
    db["OOMS"] = "Muscat International Airport";
    db["LLBG"] = "Ben Gurion International Airport";
    db["OAKB"] = "Kabul International Airport";

    // ── Asia-Pacific ─────────────────────────────────────────────
    db["VHHH"] = "Hong Kong International Airport";
    db["RCTP"] = "Taiwan Taoyuan International Airport";
    db["RKSI"] = "Incheon International Airport";
    db["RJTT"] = "Tokyo Haneda Airport";
    db["RJAA"] = "Tokyo Narita International Airport";
    db["RJOO"] = "Osaka Itami Airport";
    db["RJBB"] = "Kansai International Airport";
    db["RJCC"] = "New Chitose Airport";
    db["RJFF"] = "Fukuoka Airport";
    db["ZBAA"] = "Beijing Capital International Airport";
    db["ZBAD"] = "Beijing Daxing International Airport";
    db["ZSPD"] = "Shanghai Pudong International Airport";
    db["ZSSS"] = "Shanghai Hongqiao International Airport";
    db["ZGGG"] = "Guangzhou Baiyun International Airport";
    db["ZGSZ"] = "Shenzhen Bao'an International Airport";
    db["ZPPP"] = "Kunming Changshui International Airport";
    db["ZUUU"] = "Chengdu Tianfu International Airport";
    db["ZWWW"] = "Ürümqi Diwopu International Airport";
    db["VMMC"] = "Macau International Airport";
    db["WSSS"] = "Singapore Changi Airport";
    db["WMKK"] = "Kuala Lumpur International Airport";
    db["WMKP"] = "Penang International Airport";
    db["WADD"] = "Ngurah Rai International Airport";
    db["WIII"] = "Soekarno-Hatta International Airport";
    db["RPLL"] = "Ninoy Aquino International Airport";
    db["VTBS"] = "Suvarnabhumi Airport";
    db["VTBD"] = "Don Mueang International Airport";
    db["VVTS"] = "Tan Son Nhat International Airport";
    db["VVNB"] = "Noi Bai International Airport";
    db["VDPP"] = "Phnom Penh International Airport";
    db["VLVT"] = "Wattay International Airport";
    db["VNKT"] = "Tribhuvan International Airport";
    db["VABB"] = "Chhatrapati Shivaji Maharaj International Airport";
    db["VIDP"] = "Indira Gandhi International Airport";
    db["VOMM"] = "Chennai International Airport";
    db["VOBL"] = "Kempegowda International Airport";
    db["VECC"] = "Netaji Subhas Chandra Bose International Airport";
    db["VOCI"] = "Cochin International Airport";

    // ── Africa ───────────────────────────────────────────────────
    db["FAOR"] = "O.R. Tambo International Airport";
    db["FACT"] = "Cape Town International Airport";
    db["FALA"] = "Lanseria International Airport";
    db["HECA"] = "Cairo International Airport";
    db["HAAB"] = "Addis Ababa Bole International Airport";
    db["DNMM"] = "Murtala Muhammed International Airport";
    db["DIAP"] = "Félix-Houphouët-Boigny International Airport";
    db["DTTA"] = "Tunis-Carthage International Airport";
    db["GMME"] = "Rabat-Salé Airport";
    db["GMMN"] = "Mohammed V International Airport";
    db["GMTT"] = "Tangier Ibn Battuta Airport";

    // ── Latin America ────────────────────────────────────────────
    db["SBGR"] = "São Paulo–Guarulhos International Airport";
    db["SBBR"] = "Brasília International Airport";
    db["SBGL"] = "Rio de Janeiro Galeão International Airport";
    db["SAEZ"] = "Ministro Pistarini International Airport";
    db["SKBO"] = "El Dorado International Airport";
    db["SEQM"] = "Mariscal Sucre International Airport";
    db["SPIM"] = "Jorge Chávez International Airport";
    db["SCEL"] = "Arturo Merino Benítez International Airport";
    db["MMMX"] = "Mexico City International Airport";
    db["MMGL"] = "Miguel Hidalgo y Costilla Guadalajara International Airport";
    db["MMMY"] = "General Mariano Escobedo International Airport";
    db["MHLM"] = "Ramón Villeda Morales International Airport";
    db["MPTO"] = "Tocumen International Airport";
    db["MSLP"] = "Monseñor Óscar Arnulfo Romero International Airport";
    db["MROC"] = "Juan Santamaría International Airport";
    db["MNMG"] = "Augusto C. Sandino International Airport";
    db["MGTK"] = "Mundo Maya International Airport";
    db["MGGT"] = "La Aurora International Airport";
    db["MBPV"] = "Providenciales International Airport";
    db["MKJP"] = "Norman Manley International Airport";
    db["MDPC"] = "Punta Cana International Airport";
    db["MDSD"] = "Las Américas International Airport";
    db["TNCM"] = "Princess Juliana International Airport";
    db["TBPB"] = "Grantley Adams International Airport";
    db["TTPP"] = "Piarco International Airport";
    db["SVMI"] = "Simón Bolívar International Airport";
    db["SGAS"] = "Silvio Pettirossi International Airport";
    db["SUAA"] = "Carrasco International Airport";

    // ── Australia / NZ / Pacific ─────────────────────────────────
    db["YSSY"] = "Sydney Kingsford Smith Airport";
    db["YMML"] = "Melbourne Airport";
    db["YBBN"] = "Brisbane Airport";
    db["YPPH"] = "Perth Airport";
    db["YPAD"] = "Adelaide Airport";
    db["NZAA"] = "Auckland Airport";
    db["NZWN"] = "Wellington Airport";
    db["NZCH"] = "Christchurch Airport";
    db["NFFN"] = "Nadi International Airport";
    db["NVVV"] = "Bauerfield International Airport";
}
