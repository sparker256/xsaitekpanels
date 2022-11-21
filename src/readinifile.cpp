// ****** readinifile.cpp **********
// ****  William R. Good  ********

#include "XPLMPlugin.h"
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMCamera.h"
#include "XPLMPlanes.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMMenus.h"

#include "saitekpanels.h"
#include "inireader.h"
#include <vector>

#include <iostream>
#include <fstream>
//#include <string>
#include <string.h>

string convert_Mac_Path(string in_path) {

    //char seperator_number_buffer[255] = {0};

    std::size_t len = in_path.length();
    std::size_t pos = in_path.find(":");

    in_path.erase(in_path.begin() + 0, in_path.end() - (len - pos));

    int count = 0;
    for (int i = 0; i < in_path.size(); i++)
        if (in_path[i] == ':') count++;
    // sprintf(seperator_number_buffer, "Xsaitekpanels: How many path seperators are in the path = %d\n", count);
    // XPLMDebugString(seperator_number_buffer);

    size_t found;
    int n = count;

    while (n > 0) {
        found = in_path.find(":");
        in_path.replace(found, 1, "/");
        --n;
    }

    std::size_t pos2 = in_path.find("/Aircraft");
    std::string tmp_in_path = in_path.substr(pos2);
    tmp_in_path.insert(0, ".");
    in_path = tmp_in_path;

    return in_path;
}

// ***** Configuration File Process ******
std::vector<char> ini_save_path_name;

void process_read_ini_file()

{

    char* iniDefaultPluginPath;
    //const char *defaultConfigFileName;

    iniDefaultPluginPath = "./Resources/plugins/Xsaitekpanels/xsaitekpanels.ini";
    //defaultConfigFileName = "xsaitekpanels.ini";
    string version;

    /* set defaults */

        // switch panel defaults

    // switches
    magoffswitchenable = 1;
    magrightswitchenable = 1;
    magleftswitchenable = 1;
    magbothswitchenable = 1;
    magstartswitchenable = 1;
    batmasterswitchenable = 1;
    altmasterswitchenable = 1;
    avionicsmasterswitchenable = 1;
    fuelpumpswitchenable = 1;
    deiceswitchenable = 1;
    pitotheatswitchenable = 1;
    landinggearknobupenable = 1;
    landinggearknobdnenable = 1;
    cowlflapsenable = 1;
    panellightswitchenable = 1;
    beaconlightswitchenable = 1;
    navlightswitchenable = 1;
    strobelightswitchenable = 1;
    taxilightswitchenable = 1;
    landinglightswitchenable = 1;
    gearledenable = 1;

    bataltinverse = 0;
    starterswitchenable = 0;

    // radio panel defaults
    radspeed = 1;
    numadf = 1;
    metricpressenable = 0;
    channelspacing833enable = 0;
    dmedistspeedenable = 0;

    rad1uprcom1switchremap = 0, rad1uprcom1actstbybtnremap = 0;
    rad1lwrcom1switchremap = 0, rad1lwrcom1actstbybtnremap = 0;
    rad1uprcom2switchremap = 0, rad1uprcom2actstbybtnremap = 0;
    rad1lwrcom2switchremap = 0, rad1lwrcom2actstbybtnremap = 0;
    rad1uprnav1switchremap = 0, rad1uprnav1actstbybtnremap = 0;
    rad1lwrnav1switchremap = 0, rad1lwrnav1actstbybtnremap = 0;
    rad1uprnav2switchremap = 0, rad1uprnav2actstbybtnremap = 0;
    rad1lwrnav2switchremap = 0, rad1lwrnav2actstbybtnremap = 0;
    rad1upradfswitchremap = 0, rad1upradfactstbybtnremap = 0;
    rad1lwradfswitchremap = 0, rad1lwradfactstbybtnremap = 0;
    rad1uprdmeswitchremap = 0, rad1uprdmeactstbybtnremap = 0;
    rad1lwrdmeswitchremap = 0, rad1lwrdmeactstbybtnremap = 0;


    rad2uprcom1switchremap = 0, rad2uprcom1actstbybtnremap = 0;
    rad2lwrcom1switchremap = 0, rad2lwrcom1actstbybtnremap = 0;
    rad2uprcom2switchremap = 0, rad2uprcom2actstbybtnremap = 0;
    rad2lwrcom2switchremap = 0, rad2lwrcom2actstbybtnremap = 0;
    rad2uprnav1switchremap = 0, rad2uprnav1actstbybtnremap = 0;
    rad2lwrnav1switchremap = 0, rad2lwrnav1actstbybtnremap = 0;
    rad2uprnav2switchremap = 0, rad2uprnav2actstbybtnremap = 0;
    rad2lwrnav2switchremap = 0, rad2lwrnav2actstbybtnremap = 0;
    rad2upradfswitchremap = 0, rad2upradfactstbybtnremap = 0;
    rad2lwradfswitchremap = 0, rad2lwradfactstbybtnremap = 0;
    rad2uprdmeswitchremap = 0, rad2uprdmeactstbybtnremap = 0;
    rad2lwrdmeswitchremap = 0, rad2lwrdmeactstbybtnremap = 0;


    rad3uprcom1switchremap = 0, rad3uprcom1actstbybtnremap = 0;
    rad3lwrcom1switchremap = 0, rad3lwrcom1actstbybtnremap = 0;
    rad3uprcom2switchremap = 0, rad3uprcom2actstbybtnremap = 0;
    rad3lwrcom2switchremap = 0, rad3lwrcom2actstbybtnremap = 0;
    rad3uprnav1switchremap = 0, rad3uprnav1actstbybtnremap = 0;
    rad3lwrnav1switchremap = 0, rad3lwrnav1actstbybtnremap = 0;
    rad3uprnav2switchremap = 0, rad3uprnav2actstbybtnremap = 0;
    rad3lwrnav2switchremap = 0, rad3lwrnav2actstbybtnremap = 0;
    rad3upradfswitchremap = 0, rad3upradfactstbybtnremap = 0;
    rad3lwradfswitchremap = 0, rad3lwradfactstbybtnremap = 0;
    rad3uprdmeswitchremap = 0, rad3uprdmeactstbybtnremap = 0;
    rad3lwrdmeswitchremap = 0, rad3lwrdmeactstbybtnremap = 0;

    log_enable = 0;

    dissableSwitchPanelInVR = 0;
    dissableRadioPanelInVR = 0;
    dissableMultiPanelInVR = 0;

    // multi panel defaults
    trimspeed = 1;
    multispeed = 3;
    multiaccelthreshold = 40;
    iasismachremap = 0;
    iasismachvalue = 1;

    altswitchremap = 0;
    vsswitchremap = 0;
    iasswitchremap = 0;
    hdgswitchremap = 0;
    crsswitchremap = 0;

    autothrottleswitchenable = 0;
    autothrottleswitcharmedvalue = 0;

    dynamicTrimWheel = 1;
    dynamicTrimAccelerationPoint = 0.3;
    dynamicTrimMinVal = 1;
    dynamicTrimMaxVal = 6;

    trimupremap = 0;
    trimdnremap = 0;

    flapsupremap = 0;
    flapsdnremap = 0;

    lightdatareferencetype = 0;

    apbuttonremap = 0;
    hdgbuttonremap = 0;
    navbuttonremap = 0;
    iasbuttonremap = 0;
    altbuttonremap = 0;
    vsbuttonremap = 0;
    aprbuttonremap = 0;
    revbuttonremap = 0;

    //char *configPath;

    cleanupIniReader();

    char xpsacfname[512];
    char xpsacfpath[512];
    XPLMGetNthAircraftModel(0, xpsacfname, xpsacfpath);

    char	radtestbuf1[256];

    //XPLMDebugString("\nXsaitekpanels: Raw Current aircraft path is \n");
    //XPLMDebugString(xpsacfpath);
    //XPLMDebugString("\n");

    if (strlen(xpsacfpath) == 0) {
        XPLMDebugString("\nXsaitekpanels: Error strlen(xpsacfpath) == 0 \n");
        return;
    }

    std::string xpsini_path_name = xpsacfpath;
    std::size_t pos = xpsini_path_name.find(xpsacfname);
    xpsini_path_name = xpsini_path_name.substr(0, pos);

    std::string xpsini_aircraft_name = xpsacfname;
    std::size_t pos1 = xpsini_aircraft_name.find(".acf");
    xpsini_aircraft_name = xpsini_aircraft_name.substr(0, pos1);

#if APL && __MACH__
    std::string mac_converted_path = convert_Mac_Path(xpsini_path_name);
    XPLMDebugString("\nXsaitekpanels: mac_converted_path is \n");
    XPLMDebugString(mac_converted_path.c_str());
    XPLMDebugString("\n");
    //mac_converted_path = "./Aircraft/General Aviation/KingAir C90B/";
    xpsini_path_name = mac_converted_path;
#endif

    std::string xpsini_path_name1 = xpsini_path_name;

    xpsini_path_name1.append("xsaitekpanels.ini");

    xpsini_path_name.append(xpsini_aircraft_name);

    xpsini_path_name.append("_xsaitekpanels.ini");

    int found_file = 0;

    std::vector<char> parse_ini_path_name(xpsini_path_name.size() + 1);
    std::copy(xpsini_path_name.begin(), xpsini_path_name.end(), parse_ini_path_name.begin());

    std::ifstream ifile(&parse_ini_path_name[0]);
    if (ifile) {
        XPLMDebugString("\nXsaitekpanels: Found xsaitekpanels.ini in the current aircraft path and it is\n");
        XPLMDebugString(&parse_ini_path_name[0]);
        XPLMDebugString("\n");

        ini_save_path_name = parse_ini_path_name;

        parseIniFile(&parse_ini_path_name[0]);
        found_file = 1;

    }
    else if (!ifile) {
        std::vector<char> parse_ini_path_name1(xpsini_path_name1.size() + 1);
        std::copy(xpsini_path_name1.begin(), xpsini_path_name1.end(), parse_ini_path_name1.begin());

        std::ifstream ifile1(&parse_ini_path_name1[0]);
        if (ifile1) {
            XPLMDebugString("\nXsaitekpanels: Found xsaitekpanels.ini in the current aircraft path and it is\n");
            XPLMDebugString(&parse_ini_path_name1[0]);
            XPLMDebugString("\n");

            ini_save_path_name = parse_ini_path_name1;

            parseIniFile(&parse_ini_path_name1[0]);
            found_file = 1;

        }
        if (found_file == 0) {
            XPLMDebugString("\nXsaitekpanels: Did not find xsaitekpanels.ini in the current aircraft path\n");
        }

        std::ifstream ifile2(iniDefaultPluginPath);
        if (ifile2) {
            if (found_file == 0) {

                XPLMDebugString("\nXsaitekpanels: Found xsaitekpanels.ini in the Xsaitekpanels plugin path and it is\n");
                XPLMDebugString(iniDefaultPluginPath);
                XPLMDebugString("\n");

                ini_save_path_name = parse_ini_path_name;

                parseIniFile(iniDefaultPluginPath);
            }
        }
        else {
            XPLMDebugString("\nXsaitekpanels: Error xsaitekpanels.ini not found in plugin path\n");
            return;
        }

    }

    // get xsaitekpanels.ini version
    version = getOptionToString("Version");
    XPLMDebugString("\nXsaitekpanels: xsaitekpanels.ini is version   ");
    XPLMDebugString(version.c_str());
    XPLMDebugString("\n");

    // Do we want to enable data reference editor?
    readOptionAsInt("Data Reference Editor enable", &dre_enable);

    // Do we want to display the plane icao on screen?
    readOptionAsInt("Display Plane ICAO On Screen Enable", &icao_enable);

    // Do we want debug loging enabled
    readOptionAsInt("Add Debug Entries To Log Enable", &log_enable);

    // Do we want disable switch panel in virtual reality
    readOptionAsInt("Dissable Switch Panel In VR", &dissableSwitchPanelInVR);

    // Do we want disable switch panel in virtual reality
    readOptionAsInt("Dissable Radio Panel In VR", &dissableRadioPanelInVR);

    // Do we want disable switch panel in virtual reality
    readOptionAsInt("Dissable Multi Panel In VR", &dissableMultiPanelInVR);

    sprintf(buf, "Xsaitekpanels: dre_enable = %d  icao_enable = %d  log_enable = %d dissableSwitchPanelInVR = %d dissableRadioPanelInVR = %d dissableMultiPanelInVR = %d\n", dre_enable, icao_enable, log_enable, dissableSwitchPanelInVR, dissableRadioPanelInVR, dissableMultiPanelInVR);
    XPLMDebugString(buf);

    // bat alt normal alt bat cessna
    readOptionAsInt("Bat Alt inverse", &bataltinverse, true);

    // Starter Switch Old/New Style
    readOptionAsInt("Starter Old New", &starterswitchenable, true);

    // mag off switch disable - enable - remap
    readOptionAsInt("Mag Off Switch enable", &magoffswitchenable, true);

    if (magoffswitchenable == 2) {
        mag_off_switch_on = getOptionToString("mag_off_switch_on_cmd");
        mag_off_switch_off = getOptionToString("mag_off_switch_off_cmd");
        MagOffSwitchOnCmd = XPLMFindCommand(mag_off_switch_on.c_str());
        MagOffSwitchOffCmd = XPLMFindCommand(mag_off_switch_off.c_str());

        mag_off2_switch_on = getOptionToString("mag_off2_switch_on_cmd");
        mag_off2_switch_off = getOptionToString("mag_off2_switch_off_cmd");
        MagOff2SwitchOnCmd = XPLMFindCommand(mag_off2_switch_on.c_str());
        MagOff2SwitchOffCmd = XPLMFindCommand(mag_off2_switch_off.c_str());

        mag_off3_switch_on = getOptionToString("mag_off3_switch_on_cmd");
        mag_off3_switch_off = getOptionToString("mag_off3_switch_off_cmd");
        MagOff3SwitchOnCmd = XPLMFindCommand(mag_off3_switch_on.c_str());
        MagOff3SwitchOffCmd = XPLMFindCommand(mag_off3_switch_off.c_str());

        mag_off4_switch_on = getOptionToString("mag_off4_switch_on_cmd");
        mag_off4_switch_off = getOptionToString("mag_off4_switch_off_cmd");
        MagOff4SwitchOnCmd = XPLMFindCommand(mag_off4_switch_on.c_str());
        MagOff4SwitchOffCmd = XPLMFindCommand(mag_off4_switch_off.c_str());

        mag_off5_switch_on = getOptionToString("mag_off5_switch_on_cmd");
        mag_off5_switch_off = getOptionToString("mag_off5_switch_off_cmd");
        MagOff5SwitchOnCmd = XPLMFindCommand(mag_off5_switch_on.c_str());
        MagOff5SwitchOffCmd = XPLMFindCommand(mag_off5_switch_off.c_str());

        mag_off6_switch_on = getOptionToString("mag_off6_switch_on_cmd");
        mag_off6_switch_off = getOptionToString("mag_off6_switch_off_cmd");
        MagOff6SwitchOnCmd = XPLMFindCommand(mag_off6_switch_on.c_str());
        MagOff6SwitchOffCmd = XPLMFindCommand(mag_off6_switch_off.c_str());

        mag_off7_switch_on = getOptionToString("mag_off7_switch_on_cmd");
        mag_off7_switch_off = getOptionToString("mag_off7_switch_off_cmd");
        MagOff7SwitchOnCmd = XPLMFindCommand(mag_off7_switch_on.c_str());
        MagOff7SwitchOffCmd = XPLMFindCommand(mag_off7_switch_off.c_str());

        mag_off8_switch_on = getOptionToString("mag_off8_switch_on_cmd");
        mag_off8_switch_off = getOptionToString("mag_off8_switch_off_cmd");
        MagOff8SwitchOnCmd = XPLMFindCommand(mag_off8_switch_on.c_str());
        MagOff8SwitchOffCmd = XPLMFindCommand(mag_off8_switch_off.c_str());

    }

    if ((magoffswitchenable == 3) || (magoffswitchenable == 4)) {
        mag_off_switch_data = getOptionToString("mag_off_switch_data");
        MagOffSwitchData = XPLMFindDataRef(mag_off_switch_data.c_str());
        mag_off_switch_data_on_value = getOptionToInt("mag_off_switch_data_on_value");
        mag_off_switch_data_off_value = getOptionToInt("mag_off_switch_data_off_value");

        mag_off2_switch_data = getOptionToString("mag_off2_switch_data");
        MagOff2SwitchData = XPLMFindDataRef(mag_off2_switch_data.c_str());
        mag_off2_switch_data_on_value = getOptionToInt("mag_off2_switch_data_on_value");
        mag_off2_switch_data_off_value = getOptionToInt("mag_off2_switch_data_off_value");

        mag_off3_switch_data = getOptionToString("mag_off3_switch_data");
        MagOff3SwitchData = XPLMFindDataRef(mag_off3_switch_data.c_str());
        mag_off3_switch_data_on_value = getOptionToInt("mag_off3_switch_data_on_value");
        mag_off3_switch_data_off_value = getOptionToInt("mag_off3_switch_data_off_value");

        mag_off4_switch_data = getOptionToString("mag_off4_switch_data");
        MagOff4SwitchData = XPLMFindDataRef(mag_off4_switch_data.c_str());
        mag_off4_switch_data_on_value = getOptionToInt("mag_off4_switch_data_on_value");
        mag_off4_switch_data_off_value = getOptionToInt("mag_off4_switch_data_off_value");

        mag_off5_switch_data = getOptionToString("mag_off5_switch_data");
        MagOff5SwitchData = XPLMFindDataRef(mag_off5_switch_data.c_str());
        mag_off5_switch_data_on_value = getOptionToInt("mag_off5_switch_data_on_value");
        mag_off5_switch_data_off_value = getOptionToInt("mag_off5_switch_data_off_value");

        mag_off6_switch_data = getOptionToString("mag_off6_switch_data");
        MagOff6SwitchData = XPLMFindDataRef(mag_off6_switch_data.c_str());
        mag_off6_switch_data_on_value = getOptionToInt("mag_off6_switch_data_on_value");
        mag_off6_switch_data_off_value = getOptionToInt("mag_off6_switch_data_off_value");

        mag_off7_switch_data = getOptionToString("mag_off7_switch_data");
        MagOff7SwitchData = XPLMFindDataRef(mag_off7_switch_data.c_str());
        mag_off7_switch_data_on_value = getOptionToInt("mag_off7_switch_data_on_value");
        mag_off7_switch_data_off_value = getOptionToInt("mag_off7_switch_data_off_value");

        mag_off8_switch_data = getOptionToString("mag_off8_switch_data");
        MagOff8SwitchData = XPLMFindDataRef(mag_off8_switch_data.c_str());
        mag_off8_switch_data_on_value = getOptionToInt("mag_off8_switch_data_on_value");
        mag_off8_switch_data_off_value = getOptionToInt("mag_off8_switch_data_off_value");

        mag_off9_switch_data = getOptionToString("mag_off9_switch_data");
        MagOff9SwitchData = XPLMFindDataRef(mag_off9_switch_data.c_str());
        mag_off9_switch_data_on_value = getOptionToInt("mag_off9_switch_data_on_value");
        mag_off9_switch_data_off_value = getOptionToInt("mag_off9_switch_data_off_value");

        mag_off10_switch_data = getOptionToString("mag_off10_switch_data");
        MagOff10SwitchData = XPLMFindDataRef(mag_off10_switch_data.c_str());
        mag_off10_switch_data_on_value = getOptionToInt("mag_off10_switch_data_on_value");
        mag_off10_switch_data_off_value = getOptionToInt("mag_off10_switch_data_off_value");

    }


    // mag right switch disable - enable - remap
    readOptionAsInt("Mag Right Switch enable", &magrightswitchenable, true);

    if (magrightswitchenable == 2) {
        mag_right_switch_on = getOptionToString("mag_right_switch_on_cmd");
        mag_right_switch_off = getOptionToString("mag_right_switch_off_cmd");
        MagRightSwitchOnCmd = XPLMFindCommand(mag_right_switch_on.c_str());
        MagRightSwitchOffCmd = XPLMFindCommand(mag_right_switch_off.c_str());

        mag_right2_switch_on = getOptionToString("mag_right2_switch_on_cmd");
        mag_right2_switch_off = getOptionToString("mag_right2_switch_off_cmd");
        MagRight2SwitchOnCmd = XPLMFindCommand(mag_right2_switch_on.c_str());
        MagRight2SwitchOffCmd = XPLMFindCommand(mag_right2_switch_off.c_str());

        mag_right3_switch_on = getOptionToString("mag_right3_switch_on_cmd");
        mag_right3_switch_off = getOptionToString("mag_right3_switch_off_cmd");
        MagRight3SwitchOnCmd = XPLMFindCommand(mag_right3_switch_on.c_str());
        MagRight3SwitchOffCmd = XPLMFindCommand(mag_right3_switch_off.c_str());

        mag_right4_switch_on = getOptionToString("mag_right4_switch_on_cmd");
        mag_right4_switch_off = getOptionToString("mag_right4_switch_off_cmd");
        MagRight4SwitchOnCmd = XPLMFindCommand(mag_right4_switch_on.c_str());
        MagRight4SwitchOffCmd = XPLMFindCommand(mag_right4_switch_off.c_str());

        mag_right5_switch_on = getOptionToString("mag_right5_switch_on_cmd");
        mag_right5_switch_off = getOptionToString("mag_right5_switch_off_cmd");
        MagRight5SwitchOnCmd = XPLMFindCommand(mag_right5_switch_on.c_str());
        MagRight5SwitchOffCmd = XPLMFindCommand(mag_right5_switch_off.c_str());

        mag_right6_switch_on = getOptionToString("mag_right6_switch_on_cmd");
        mag_right6_switch_off = getOptionToString("mag_right6_switch_off_cmd");
        MagRight6SwitchOnCmd = XPLMFindCommand(mag_right6_switch_on.c_str());
        MagRight6SwitchOffCmd = XPLMFindCommand(mag_right6_switch_off.c_str());

        mag_right7_switch_on = getOptionToString("mag_right7_switch_on_cmd");
        mag_right7_switch_off = getOptionToString("mag_right7_switch_off_cmd");
        MagRight7SwitchOnCmd = XPLMFindCommand(mag_right7_switch_on.c_str());
        MagRight7SwitchOffCmd = XPLMFindCommand(mag_right7_switch_off.c_str());

        mag_right8_switch_on = getOptionToString("mag_right8_switch_on_cmd");
        mag_right8_switch_off = getOptionToString("mag_right8_switch_off_cmd");
        MagRight8SwitchOnCmd = XPLMFindCommand(mag_right8_switch_on.c_str());
        MagRight8SwitchOffCmd = XPLMFindCommand(mag_right8_switch_off.c_str());

    }

    if ((magrightswitchenable == 3) || (magrightswitchenable == 4)) {
        mag_right_switch_data = getOptionToString("mag_right_switch_data");
        MagRightSwitchData = XPLMFindDataRef(mag_right_switch_data.c_str());
        mag_right_switch_data_on_value = getOptionToInt("mag_right_switch_data_on_value");
        mag_right_switch_data_off_value = getOptionToInt("mag_right_switch_data_off_value");

        mag_right2_switch_data = getOptionToString("mag_right2_switch_data");
        MagRight2SwitchData = XPLMFindDataRef(mag_right2_switch_data.c_str());
        mag_right2_switch_data_on_value = getOptionToInt("mag_right2_switch_data_on_value");
        mag_right2_switch_data_off_value = getOptionToInt("mag_right2_switch_data_off_value");

        mag_right3_switch_data = getOptionToString("mag_right3_switch_data");
        MagRight3SwitchData = XPLMFindDataRef(mag_right3_switch_data.c_str());
        mag_right3_switch_data_on_value = getOptionToInt("mag_right3_switch_data_on_value");
        mag_right3_switch_data_off_value = getOptionToInt("mag_right3_switch_data_off_value");

        mag_right4_switch_data = getOptionToString("mag_right4_switch_data");
        MagRight4SwitchData = XPLMFindDataRef(mag_right4_switch_data.c_str());
        mag_right4_switch_data_on_value = getOptionToInt("mag_right4_switch_data_on_value");
        mag_right4_switch_data_off_value = getOptionToInt("mag_right4_switch_data_off_value");

        mag_right5_switch_data = getOptionToString("mag_right5_switch_data");
        MagRight5SwitchData = XPLMFindDataRef(mag_right5_switch_data.c_str());
        mag_right5_switch_data_on_value = getOptionToInt("mag_right5_switch_data_on_value");
        mag_right5_switch_data_off_value = getOptionToInt("mag_right5_switch_data_off_value");

        mag_right6_switch_data = getOptionToString("mag_right6_switch_data");
        MagRight6SwitchData = XPLMFindDataRef(mag_right6_switch_data.c_str());
        mag_right6_switch_data_on_value = getOptionToInt("mag_right6_switch_data_on_value");
        mag_right6_switch_data_off_value = getOptionToInt("mag_right6_switch_data_off_value");

        mag_right7_switch_data = getOptionToString("mag_right7_switch_data");
        MagRight7SwitchData = XPLMFindDataRef(mag_right7_switch_data.c_str());
        mag_right7_switch_data_on_value = getOptionToInt("mag_right7_switch_data_on_value");
        mag_right7_switch_data_off_value = getOptionToInt("mag_right7_switch_data_off_value");

        mag_right8_switch_data = getOptionToString("mag_right8_switch_data");
        MagRight8SwitchData = XPLMFindDataRef(mag_right8_switch_data.c_str());
        mag_right8_switch_data_on_value = getOptionToInt("mag_right8_switch_data_on_value");
        mag_right8_switch_data_off_value = getOptionToInt("mag_right8_switch_data_off_value");

        mag_right9_switch_data = getOptionToString("mag_right9_switch_data");
        MagRight9SwitchData = XPLMFindDataRef(mag_right9_switch_data.c_str());
        mag_right9_switch_data_on_value = getOptionToInt("mag_right9_switch_data_on_value");
        mag_right9_switch_data_off_value = getOptionToInt("mag_right9_switch_data_off_value");

        mag_right10_switch_data = getOptionToString("mag_right10_switch_data");
        MagRight10SwitchData = XPLMFindDataRef(mag_right10_switch_data.c_str());
        mag_right10_switch_data_on_value = getOptionToInt("mag_right10_switch_data_on_value");
        mag_right10_switch_data_off_value = getOptionToInt("mag_right10_switch_data_off_value");

    }

    // mag left switch disable - enable - remap
    readOptionAsInt("Mag Left Switch enable", &magleftswitchenable, true);

    if (magleftswitchenable == 2) {
        mag_left_switch_on = getOptionToString("mag_left_switch_on_cmd");
        mag_left_switch_off = getOptionToString("mag_left_switch_off_cmd");
        MagLeftSwitchOnCmd = XPLMFindCommand(mag_left_switch_on.c_str());
        MagLeftSwitchOffCmd = XPLMFindCommand(mag_left_switch_off.c_str());

        mag_left2_switch_on = getOptionToString("mag_left2_switch_on_cmd");
        mag_left2_switch_off = getOptionToString("mag_left2_switch_off_cmd");
        MagLeft2SwitchOnCmd = XPLMFindCommand(mag_left2_switch_on.c_str());
        MagLeft2SwitchOffCmd = XPLMFindCommand(mag_left2_switch_off.c_str());

        mag_left3_switch_on = getOptionToString("mag_left3_switch_on_cmd");
        mag_left3_switch_off = getOptionToString("mag_left3_switch_off_cmd");
        MagLeft3SwitchOnCmd = XPLMFindCommand(mag_left3_switch_on.c_str());
        MagLeft3SwitchOffCmd = XPLMFindCommand(mag_left3_switch_off.c_str());

        mag_left4_switch_on = getOptionToString("mag_left4_switch_on_cmd");
        mag_left4_switch_off = getOptionToString("mag_left4_switch_off_cmd");
        MagLeft4SwitchOnCmd = XPLMFindCommand(mag_left4_switch_on.c_str());
        MagLeft4SwitchOffCmd = XPLMFindCommand(mag_left4_switch_off.c_str());

        mag_left5_switch_on = getOptionToString("mag_left5_switch_on_cmd");
        mag_left5_switch_off = getOptionToString("mag_left5_switch_off_cmd");
        MagLeft5SwitchOnCmd = XPLMFindCommand(mag_left5_switch_on.c_str());
        MagLeft5SwitchOffCmd = XPLMFindCommand(mag_left5_switch_off.c_str());

        mag_left6_switch_on = getOptionToString("mag_left6_switch_on_cmd");
        mag_left6_switch_off = getOptionToString("mag_left6_switch_off_cmd");
        MagLeft6SwitchOnCmd = XPLMFindCommand(mag_left6_switch_on.c_str());
        MagLeft6SwitchOffCmd = XPLMFindCommand(mag_left6_switch_off.c_str());

        mag_left7_switch_on = getOptionToString("mag_left7_switch_on_cmd");
        mag_left7_switch_off = getOptionToString("mag_left7_switch_off_cmd");
        MagLeft7SwitchOnCmd = XPLMFindCommand(mag_left7_switch_on.c_str());
        MagLeft7SwitchOffCmd = XPLMFindCommand(mag_left7_switch_off.c_str());

        mag_left8_switch_on = getOptionToString("mag_left8_switch_on_cmd");
        mag_left8_switch_off = getOptionToString("mag_left8_switch_off_cmd");
        MagLeft8SwitchOnCmd = XPLMFindCommand(mag_left8_switch_on.c_str());
        MagLeft8SwitchOffCmd = XPLMFindCommand(mag_left8_switch_off.c_str());

    }

    if ((magleftswitchenable == 3) || (magleftswitchenable == 4)) {
        mag_left_switch_data = getOptionToString("mag_left_switch_data");
        MagLeftSwitchData = XPLMFindDataRef(mag_left_switch_data.c_str());
        mag_left_switch_data_on_value = getOptionToInt("mag_left_switch_data_on_value");
        mag_left_switch_data_off_value = getOptionToInt("mag_left_switch_data_off_value");

        mag_left2_switch_data = getOptionToString("mag_left2_switch_data");
        MagLeft2SwitchData = XPLMFindDataRef(mag_left2_switch_data.c_str());
        mag_left2_switch_data_on_value = getOptionToInt("mag_left2_switch_data_on_value");
        mag_left2_switch_data_off_value = getOptionToInt("mag_left2_switch_data_off_value");

        mag_left3_switch_data = getOptionToString("mag_left3_switch_data");
        MagLeft3SwitchData = XPLMFindDataRef(mag_left3_switch_data.c_str());
        mag_left3_switch_data_on_value = getOptionToInt("mag_left3_switch_data_on_value");
        mag_left3_switch_data_off_value = getOptionToInt("mag_left3_switch_data_off_value");

        mag_left4_switch_data = getOptionToString("mag_left4_switch_data");
        MagLeft4SwitchData = XPLMFindDataRef(mag_left4_switch_data.c_str());
        mag_left4_switch_data_on_value = getOptionToInt("mag_left4_switch_data_on_value");
        mag_left4_switch_data_off_value = getOptionToInt("mag_left4_switch_data_off_value");

        mag_left5_switch_data = getOptionToString("mag_left5_switch_data");
        MagLeft5SwitchData = XPLMFindDataRef(mag_left5_switch_data.c_str());
        mag_left5_switch_data_on_value = getOptionToInt("mag_left5_switch_data_on_value");
        mag_left5_switch_data_off_value = getOptionToInt("mag_left5_switch_data_off_value");

        mag_left6_switch_data = getOptionToString("mag_left6_switch_data");
        MagLeft6SwitchData = XPLMFindDataRef(mag_left6_switch_data.c_str());
        mag_left6_switch_data_on_value = getOptionToInt("mag_left6_switch_data_on_value");
        mag_left6_switch_data_off_value = getOptionToInt("mag_left6_switch_data_off_value");

        mag_left7_switch_data = getOptionToString("mag_left7_switch_data");
        MagLeft7SwitchData = XPLMFindDataRef(mag_left7_switch_data.c_str());
        mag_left7_switch_data_on_value = getOptionToInt("mag_left7_switch_data_on_value");
        mag_left7_switch_data_off_value = getOptionToInt("mag_left7_switch_data_off_value");

        mag_left8_switch_data = getOptionToString("mag_left8_switch_data");
        MagLeft8SwitchData = XPLMFindDataRef(mag_left8_switch_data.c_str());
        mag_left8_switch_data_on_value = getOptionToInt("mag_left8_switch_data_on_value");
        mag_left8_switch_data_off_value = getOptionToInt("mag_left8_switch_data_off_value");

        mag_left9_switch_data = getOptionToString("mag_left9_switch_data");
        MagLeft9SwitchData = XPLMFindDataRef(mag_left9_switch_data.c_str());
        mag_left9_switch_data_on_value = getOptionToInt("mag_left9_switch_data_on_value");
        mag_left9_switch_data_off_value = getOptionToInt("mag_left9_switch_data_off_value");

        mag_left10_switch_data = getOptionToString("mag_left10_switch_data");
        MagLeft10SwitchData = XPLMFindDataRef(mag_left10_switch_data.c_str());
        mag_left10_switch_data_on_value = getOptionToInt("mag_left10_switch_data_on_value");
        mag_left10_switch_data_off_value = getOptionToInt("mag_left10_switch_data_off_value");

    }



    // mag both switch disable - enable - remap
    readOptionAsInt("Mag Both Switch enable", &magbothswitchenable, true);

    if (magbothswitchenable == 2) {
        mag_both_switch_on = getOptionToString("mag_both_switch_on_cmd");
        mag_both_switch_off = getOptionToString("mag_both_switch_off_cmd");
        MagBothSwitchOnCmd = XPLMFindCommand(mag_both_switch_on.c_str());
        MagBothSwitchOffCmd = XPLMFindCommand(mag_both_switch_off.c_str());

        mag_both2_switch_on = getOptionToString("mag_both2_switch_on_cmd");
        mag_both2_switch_off = getOptionToString("mag_both2_switch_off_cmd");
        MagBoth2SwitchOnCmd = XPLMFindCommand(mag_both2_switch_on.c_str());
        MagBoth2SwitchOffCmd = XPLMFindCommand(mag_both2_switch_off.c_str());

        mag_both3_switch_on = getOptionToString("mag_both3_switch_on_cmd");
        mag_both3_switch_off = getOptionToString("mag_both3_switch_off_cmd");
        MagBoth3SwitchOnCmd = XPLMFindCommand(mag_both3_switch_on.c_str());
        MagBoth3SwitchOffCmd = XPLMFindCommand(mag_both3_switch_off.c_str());

        mag_both4_switch_on = getOptionToString("mag_both4_switch_on_cmd");
        mag_both4_switch_off = getOptionToString("mag_both4_switch_off_cmd");
        MagBoth4SwitchOnCmd = XPLMFindCommand(mag_both4_switch_on.c_str());
        MagBoth4SwitchOffCmd = XPLMFindCommand(mag_both4_switch_off.c_str());

        mag_both5_switch_on = getOptionToString("mag_both5_switch_on_cmd");
        mag_both5_switch_off = getOptionToString("mag_both5_switch_off_cmd");
        MagBoth5SwitchOnCmd = XPLMFindCommand(mag_both5_switch_on.c_str());
        MagBoth5SwitchOffCmd = XPLMFindCommand(mag_both5_switch_off.c_str());

        mag_both6_switch_on = getOptionToString("mag_both6_switch_on_cmd");
        mag_both6_switch_off = getOptionToString("mag_both6_switch_off_cmd");
        MagBoth6SwitchOnCmd = XPLMFindCommand(mag_both6_switch_on.c_str());
        MagBoth6SwitchOffCmd = XPLMFindCommand(mag_both6_switch_off.c_str());

        mag_both7_switch_on = getOptionToString("mag_both7_switch_on_cmd");
        mag_both7_switch_off = getOptionToString("mag_both7_switch_off_cmd");
        MagBoth7SwitchOnCmd = XPLMFindCommand(mag_both7_switch_on.c_str());
        MagBoth7SwitchOffCmd = XPLMFindCommand(mag_both7_switch_off.c_str());

        mag_both8_switch_on = getOptionToString("mag_both8_switch_on_cmd");
        mag_both8_switch_off = getOptionToString("mag_both8_switch_off_cmd");
        MagBoth8SwitchOnCmd = XPLMFindCommand(mag_both8_switch_on.c_str());
        MagBoth8SwitchOffCmd = XPLMFindCommand(mag_both8_switch_off.c_str());

    }

    if ((magbothswitchenable == 3) || (magbothswitchenable == 4)) {
        mag_both_switch_data = getOptionToString("mag_both_switch_data");
        MagBothSwitchData = XPLMFindDataRef(mag_both_switch_data.c_str());
        mag_both_switch_data_on_value = getOptionToInt("mag_both_switch_data_on_value");
        mag_both_switch_data_off_value = getOptionToInt("mag_both_switch_data_off_value");

        mag_both2_switch_data = getOptionToString("mag_both2_switch_data");
        MagBoth2SwitchData = XPLMFindDataRef(mag_both2_switch_data.c_str());
        mag_both2_switch_data_on_value = getOptionToInt("mag_both2_switch_data_on_value");
        mag_both2_switch_data_off_value = getOptionToInt("mag_both2_switch_data_off_value");

        mag_both3_switch_data = getOptionToString("mag_both3_switch_data");
        MagBoth3SwitchData = XPLMFindDataRef(mag_both3_switch_data.c_str());
        mag_both3_switch_data_on_value = getOptionToInt("mag_both3_switch_data_on_value");
        mag_both3_switch_data_off_value = getOptionToInt("mag_both3_switch_data_off_value");

        mag_both4_switch_data = getOptionToString("mag_both4_switch_data");
        MagBoth4SwitchData = XPLMFindDataRef(mag_both4_switch_data.c_str());
        mag_both4_switch_data_on_value = getOptionToInt("mag_both4_switch_data_on_value");
        mag_both4_switch_data_off_value = getOptionToInt("mag_both4_switch_data_off_value");

        mag_both5_switch_data = getOptionToString("mag_both5_switch_data");
        MagBoth5SwitchData = XPLMFindDataRef(mag_both5_switch_data.c_str());
        mag_both5_switch_data_on_value = getOptionToInt("mag_both5_switch_data_on_value");
        mag_both5_switch_data_off_value = getOptionToInt("mag_both5_switch_data_off_value");

        mag_both6_switch_data = getOptionToString("mag_both6_switch_data");
        MagBoth6SwitchData = XPLMFindDataRef(mag_both6_switch_data.c_str());
        mag_both6_switch_data_on_value = getOptionToInt("mag_both6_switch_data_on_value");
        mag_both6_switch_data_off_value = getOptionToInt("mag_both6_switch_data_off_value");

        mag_both7_switch_data = getOptionToString("mag_both7_switch_data");
        MagBoth7SwitchData = XPLMFindDataRef(mag_both7_switch_data.c_str());
        mag_both7_switch_data_on_value = getOptionToInt("mag_both7_switch_data_on_value");
        mag_both7_switch_data_off_value = getOptionToInt("mag_both7_switch_data_off_value");

        mag_both8_switch_data = getOptionToString("mag_both8_switch_data");
        MagBoth8SwitchData = XPLMFindDataRef(mag_both8_switch_data.c_str());
        mag_both8_switch_data_on_value = getOptionToInt("mag_both8_switch_data_on_value");
        mag_both8_switch_data_off_value = getOptionToInt("mag_both8_switch_data_off_value");

        mag_both9_switch_data = getOptionToString("mag_both9_switch_data");
        MagBoth9SwitchData = XPLMFindDataRef(mag_both9_switch_data.c_str());
        mag_both9_switch_data_on_value = getOptionToInt("mag_both9_switch_data_on_value");
        mag_both9_switch_data_off_value = getOptionToInt("mag_both9_switch_data_off_value");

        mag_both10_switch_data = getOptionToString("mag_both10_switch_data");
        MagBoth10SwitchData = XPLMFindDataRef(mag_both10_switch_data.c_str());
        mag_both10_switch_data_on_value = getOptionToInt("mag_both10_switch_data_on_value");
        mag_both10_switch_data_off_value = getOptionToInt("mag_both10_switch_data_off_value");

    }


    // mag start switch disable - enable - remap
    readOptionAsInt("Mag Start Switch enable", &magstartswitchenable, true);

    if (magstartswitchenable == 2) {
        mag_start_switch_on = getOptionToString("mag_start_switch_on_cmd");
        mag_start_switch_off = getOptionToString("mag_start_switch_off_cmd");
        MagStartSwitchOnCmd = XPLMFindCommand(mag_start_switch_on.c_str());
        MagStartSwitchOffCmd = XPLMFindCommand(mag_start_switch_off.c_str());

        mag_start2_switch_on = getOptionToString("mag_start2_switch_on_cmd");
        mag_start2_switch_off = getOptionToString("mag_start2_switch_off_cmd");
        MagStart2SwitchOnCmd = XPLMFindCommand(mag_start2_switch_on.c_str());
        MagStart2SwitchOffCmd = XPLMFindCommand(mag_start2_switch_off.c_str());

        mag_start3_switch_on = getOptionToString("mag_start3_switch_on_cmd");
        mag_start3_switch_off = getOptionToString("mag_start3_switch_off_cmd");
        MagStart3SwitchOnCmd = XPLMFindCommand(mag_start3_switch_on.c_str());
        MagStart3SwitchOffCmd = XPLMFindCommand(mag_start3_switch_off.c_str());

        mag_start4_switch_on = getOptionToString("mag_start4_switch_on_cmd");
        mag_start4_switch_off = getOptionToString("mag_start4_switch_off_cmd");
        MagStart4SwitchOnCmd = XPLMFindCommand(mag_start4_switch_on.c_str());
        MagStart4SwitchOffCmd = XPLMFindCommand(mag_start4_switch_off.c_str());

        mag_start5_switch_on = getOptionToString("mag_start5_switch_on_cmd");
        mag_start5_switch_off = getOptionToString("mag_start5_switch_off_cmd");
        MagStart5SwitchOnCmd = XPLMFindCommand(mag_start5_switch_on.c_str());
        MagStart5SwitchOffCmd = XPLMFindCommand(mag_start5_switch_off.c_str());

        mag_start6_switch_on = getOptionToString("mag_start6_switch_on_cmd");
        mag_start6_switch_off = getOptionToString("mag_start6_switch_off_cmd");
        MagStart6SwitchOnCmd = XPLMFindCommand(mag_start6_switch_on.c_str());
        MagStart6SwitchOffCmd = XPLMFindCommand(mag_start6_switch_off.c_str());

        mag_start7_switch_on = getOptionToString("mag_start7_switch_on_cmd");
        mag_start7_switch_off = getOptionToString("mag_start7_switch_off_cmd");
        MagStart7SwitchOnCmd = XPLMFindCommand(mag_start7_switch_on.c_str());
        MagStart7SwitchOffCmd = XPLMFindCommand(mag_start7_switch_off.c_str());

        mag_start8_switch_on = getOptionToString("mag_start8_switch_on_cmd");
        mag_start8_switch_off = getOptionToString("mag_start8_switch_off_cmd");
        MagStart8SwitchOnCmd = XPLMFindCommand(mag_start8_switch_on.c_str());
        MagStart8SwitchOffCmd = XPLMFindCommand(mag_start8_switch_off.c_str());

    }

    if ((magstartswitchenable == 3) || (magstartswitchenable == 4)) {
        mag_start_switch_data = getOptionToString("mag_start_switch_data");
        MagStartSwitchData = XPLMFindDataRef(mag_start_switch_data.c_str());
        mag_start_switch_data_on_value = getOptionToInt("mag_start_switch_data_on_value");
        mag_start_switch_data_off_value = getOptionToInt("mag_start_switch_data_off_value");

        mag_start_switch_left_data = getOptionToString("mag_start_switch_left_data");
        MagStartSwitchLeftData = XPLMFindDataRef(mag_start_switch_left_data.c_str());
        mag_start_switch_left_data_on_value = getOptionToInt("mag_start_switch_left_data_on_value");
        mag_start_switch_left_data_off_value = getOptionToInt("mag_start_switch_left_data_off_value");

        mag_start2_switch_data = getOptionToString("mag_start2_switch_data");
        MagStart2SwitchData = XPLMFindDataRef(mag_start2_switch_data.c_str());
        mag_start2_switch_data_on_value = getOptionToInt("mag_start2_switch_data_on_value");
        mag_start2_switch_data_off_value = getOptionToInt("mag_start2_switch_data_off_value");

        mag_start2_switch_left_data = getOptionToString("mag_start2_switch_left_data");
        MagStart2SwitchLeftData = XPLMFindDataRef(mag_start2_switch_left_data.c_str());
        mag_start2_switch_left_data_on_value = getOptionToInt("mag_start2_switch_left_data_on_value");
        mag_start2_switch_left_data_off_value = getOptionToInt("mag_start2_switch_left_data_off_value");

        mag_start3_switch_data = getOptionToString("mag_start3_switch_data");
        MagStart3SwitchData = XPLMFindDataRef(mag_start3_switch_data.c_str());
        mag_start3_switch_data_on_value = getOptionToInt("mag_start3_switch_data_on_value");
        mag_start3_switch_data_off_value = getOptionToInt("mag_start3_switch_data_off_value");

        mag_start3_switch_left_data = getOptionToString("mag_start3_switch_left_data");
        MagStart3SwitchLeftData = XPLMFindDataRef(mag_start3_switch_left_data.c_str());
        mag_start3_switch_left_data_on_value = getOptionToInt("mag_start3_switch_left_data_on_value");
        mag_start3_switch_left_data_off_value = getOptionToInt("mag_start3_switch_left_data_off_value");

        mag_start4_switch_data = getOptionToString("mag_start4_switch_data");
        MagStart4SwitchData = XPLMFindDataRef(mag_start4_switch_data.c_str());
        mag_start4_switch_data_on_value = getOptionToInt("mag_start4_switch_data_on_value");
        mag_start4_switch_data_off_value = getOptionToInt("mag_start4_switch_data_off_value");

        mag_start4_switch_left_data = getOptionToString("mag_start4_switch_left_data");
        MagStart4SwitchLeftData = XPLMFindDataRef(mag_start4_switch_left_data.c_str());
        mag_start4_switch_left_data_on_value = getOptionToInt("mag_start4_switch_left_data_on_value");
        mag_start4_switch_left_data_off_value = getOptionToInt("mag_start4_switch_left_data_off_value");

        mag_start5_switch_data = getOptionToString("mag_start5_switch_data");
        MagStart5SwitchData = XPLMFindDataRef(mag_start5_switch_data.c_str());
        mag_start5_switch_data_on_value = getOptionToInt("mag_start5_switch_data_on_value");
        mag_start5_switch_data_off_value = getOptionToInt("mag_start5_switch_data_off_value");

        mag_start5_switch_left_data = getOptionToString("mag_start5_switch_left_data");
        MagStart5SwitchLeftData = XPLMFindDataRef(mag_start5_switch_left_data.c_str());
        mag_start5_switch_left_data_on_value = getOptionToInt("mag_start5_switch_left_data_on_value");
        mag_start5_switch_left_data_off_value = getOptionToInt("mag_start5_switch_left_data_off_value");

        mag_start6_switch_data = getOptionToString("mag_start6_switch_data");
        MagStart6SwitchData = XPLMFindDataRef(mag_start6_switch_data.c_str());
        mag_start6_switch_data_on_value = getOptionToInt("mag_start6_switch_data_on_value");
        mag_start6_switch_data_off_value = getOptionToInt("mag_start6_switch_data_off_value");

        mag_start6_switch_left_data = getOptionToString("mag_start6_switch_left_data");
        MagStart6SwitchLeftData = XPLMFindDataRef(mag_start6_switch_left_data.c_str());
        mag_start6_switch_left_data_on_value = getOptionToInt("mag_start6_switch_left_data_on_value");
        mag_start6_switch_left_data_off_value = getOptionToInt("mag_start6_switch_left_data_off_value");

        mag_start7_switch_data = getOptionToString("mag_start7_switch_data");
        MagStart7SwitchData = XPLMFindDataRef(mag_start7_switch_data.c_str());
        mag_start7_switch_data_on_value = getOptionToInt("mag_start7_switch_data_on_value");
        mag_start7_switch_data_off_value = getOptionToInt("mag_start7_switch_data_off_value");

        mag_start7_switch_left_data = getOptionToString("mag_start7_switch_left_data");
        MagStart7SwitchLeftData = XPLMFindDataRef(mag_start7_switch_left_data.c_str());
        mag_start7_switch_left_data_on_value = getOptionToInt("mag_start7_switch_left_data_on_value");
        mag_start7_switch_left_data_off_value = getOptionToInt("mag_start7_switch_left_data_off_value");

        mag_start8_switch_data = getOptionToString("mag_start8_switch_data");
        MagStart8SwitchData = XPLMFindDataRef(mag_start8_switch_data.c_str());
        mag_start8_switch_data_on_value = getOptionToInt("mag_start8_switch_data_on_value");
        mag_start8_switch_data_off_value = getOptionToInt("mag_start8_switch_data_off_value");

        mag_start8_switch_left_data = getOptionToString("mag_start8_switch_left_data");
        MagStart8SwitchLeftData = XPLMFindDataRef(mag_start8_switch_left_data.c_str());
        mag_start8_switch_left_data_on_value = getOptionToInt("mag_start8_switch_left_data_on_value");
        mag_start8_switch_left_data_off_value = getOptionToInt("mag_start8_switch_left_data_off_value");

        mag_start9_switch_data = getOptionToString("mag_start9_switch_data");
        MagStart9SwitchData = XPLMFindDataRef(mag_start9_switch_data.c_str());
        mag_start9_switch_data_on_value = getOptionToInt("mag_start9_switch_data_on_value");
        mag_start9_switch_data_off_value = getOptionToInt("mag_start9_switch_data_off_value");

        mag_start9_switch_left_data = getOptionToString("mag_start9_switch_left_data");
        MagStart9SwitchLeftData = XPLMFindDataRef(mag_start9_switch_left_data.c_str());
        mag_start9_switch_left_data_on_value = getOptionToInt("mag_start9_switch_left_data_on_value");
        mag_start9_switch_left_data_off_value = getOptionToInt("mag_start9_switch_left_data_off_value");

        mag_start10_switch_data = getOptionToString("mag_start10_switch_data");
        MagStart10SwitchData = XPLMFindDataRef(mag_start10_switch_data.c_str());
        mag_start10_switch_data_on_value = getOptionToInt("mag_start10_switch_data_on_value");
        mag_start10_switch_data_off_value = getOptionToInt("mag_start10_switch_data_off_value");

        mag_start10_switch_left_data = getOptionToString("mag_start10_switch_left_data");
        MagStart10SwitchLeftData = XPLMFindDataRef(mag_start10_switch_left_data.c_str());
        mag_start10_switch_left_data_on_value = getOptionToInt("mag_start10_switch_left_data_on_value");
        mag_start10_switch_left_data_off_value = getOptionToInt("mag_start10_switch_left_data_off_value");

    }

    // bat master switch disable - enable - remap
    readOptionAsInt("Bat Master Switch enable", &batmasterswitchenable, true);

    if (batmasterswitchenable == 2) {
        bat_master_switch_on = getOptionToString("bat_master_switch_on_cmd");
        bat_master_switch_off = getOptionToString("bat_master_switch_off_cmd");
        BatMasterSwitchOnCmd = XPLMFindCommand(bat_master_switch_on.c_str());
        BatMasterSwitchOffCmd = XPLMFindCommand(bat_master_switch_off.c_str());

        bat2_master_switch_on = getOptionToString("bat2_master_switch_on_cmd");
        bat2_master_switch_off = getOptionToString("bat2_master_switch_off_cmd");
        BatMaster2SwitchOnCmd = XPLMFindCommand(bat2_master_switch_on.c_str());
        BatMaster2SwitchOffCmd = XPLMFindCommand(bat2_master_switch_off.c_str());

        bat3_master_switch_on = getOptionToString("bat3_master_switch_on_cmd");
        bat3_master_switch_off = getOptionToString("bat3_master_switch_off_cmd");
        BatMaster3SwitchOnCmd = XPLMFindCommand(bat3_master_switch_on.c_str());
        BatMaster3SwitchOffCmd = XPLMFindCommand(bat3_master_switch_off.c_str());

        bat4_master_switch_on = getOptionToString("bat4_master_switch_on_cmd");
        bat4_master_switch_off = getOptionToString("bat4_master_switch_off_cmd");
        BatMaster4SwitchOnCmd = XPLMFindCommand(bat4_master_switch_on.c_str());
        BatMaster4SwitchOffCmd = XPLMFindCommand(bat4_master_switch_off.c_str());

        bat5_master_switch_on = getOptionToString("bat5_master_switch_on_cmd");
        bat5_master_switch_off = getOptionToString("bat5_master_switch_off_cmd");
        BatMaster5SwitchOnCmd = XPLMFindCommand(bat5_master_switch_on.c_str());
        BatMaster5SwitchOffCmd = XPLMFindCommand(bat5_master_switch_off.c_str());

        bat6_master_switch_on = getOptionToString("bat6_master_switch_on_cmd");
        bat6_master_switch_off = getOptionToString("bat6_master_switch_off_cmd");
        BatMaster6SwitchOnCmd = XPLMFindCommand(bat6_master_switch_on.c_str());
        BatMaster6SwitchOffCmd = XPLMFindCommand(bat6_master_switch_off.c_str());

        bat7_master_switch_on = getOptionToString("bat7_master_switch_on_cmd");
        bat7_master_switch_off = getOptionToString("bat7_master_switch_off_cmd");
        BatMaster7SwitchOnCmd = XPLMFindCommand(bat7_master_switch_on.c_str());
        BatMaster7SwitchOffCmd = XPLMFindCommand(bat7_master_switch_off.c_str());

        bat8_master_switch_on = getOptionToString("bat8_master_switch_on_cmd");
        bat8_master_switch_off = getOptionToString("bat8_master_switch_off_cmd");
        BatMaster8SwitchOnCmd = XPLMFindCommand(bat8_master_switch_on.c_str());
        BatMaster8SwitchOffCmd = XPLMFindCommand(bat8_master_switch_off.c_str());

    }

    if ((batmasterswitchenable == 3) || (batmasterswitchenable == 4)) {
        bat_master_switch_data = getOptionToString("bat_master_switch_data");
        BatMasterSwitchData = XPLMFindDataRef(bat_master_switch_data.c_str());
        bat_master_switch_data_on_value = getOptionToInt("bat_master_switch_data_on_value");
        bat_master_switch_data_off_value = getOptionToInt("bat_master_switch_data_off_value");

        bat2_master_switch_data = getOptionToString("bat2_master_switch_data");
        Bat2MasterSwitchData = XPLMFindDataRef(bat2_master_switch_data.c_str());
        bat2_master_switch_data_on_value = getOptionToInt("bat2_master_switch_data_on_value");
        bat2_master_switch_data_off_value = getOptionToInt("bat2_master_switch_data_off_value");

        bat3_master_switch_data = getOptionToString("bat3_master_switch_data");
        Bat3MasterSwitchData = XPLMFindDataRef(bat3_master_switch_data.c_str());
        bat3_master_switch_data_on_value = getOptionToInt("bat3_master_switch_data_on_value");
        bat3_master_switch_data_off_value = getOptionToInt("bat3_master_switch_data_off_value");

        bat4_master_switch_data = getOptionToString("bat4_master_switch_data");
        Bat4MasterSwitchData = XPLMFindDataRef(bat4_master_switch_data.c_str());
        bat4_master_switch_data_on_value = getOptionToInt("bat4_master_switch_data_on_value");
        bat4_master_switch_data_off_value = getOptionToInt("bat4_master_switch_data_off_value");

        bat5_master_switch_data = getOptionToString("bat5_master_switch_data");
        Bat5MasterSwitchData = XPLMFindDataRef(bat5_master_switch_data.c_str());
        bat5_master_switch_data_on_value = getOptionToInt("bat5_master_switch_data_on_value");
        bat5_master_switch_data_off_value = getOptionToInt("bat5_master_switch_data_off_value");

        bat6_master_switch_data = getOptionToString("bat6_master_switch_data");
        Bat6MasterSwitchData = XPLMFindDataRef(bat6_master_switch_data.c_str());
        bat6_master_switch_data_on_value = getOptionToInt("bat6_master_switch_data_on_value");
        bat6_master_switch_data_off_value = getOptionToInt("bat6_master_switch_data_off_value");

        bat7_master_switch_data = getOptionToString("bat7_master_switch_data");
        Bat7MasterSwitchData = XPLMFindDataRef(bat7_master_switch_data.c_str());
        bat7_master_switch_data_on_value = getOptionToInt("bat7_master_switch_data_on_value");
        bat7_master_switch_data_off_value = getOptionToInt("bat7_master_switch_data_off_value");

        bat8_master_switch_data = getOptionToString("bat8_master_switch_data");
        Bat8MasterSwitchData = XPLMFindDataRef(bat8_master_switch_data.c_str());
        bat8_master_switch_data_on_value = getOptionToInt("bat8_master_switch_data_on_value");
        bat8_master_switch_data_off_value = getOptionToInt("bat8_master_switch_data_off_value");

    }


    // alt master switch disable - enable - remap
    readOptionAsInt("Alt Master Switch enable", &altmasterswitchenable, true);

    if (altmasterswitchenable == 2) {
        alt_master_switch_on = getOptionToString("alt_master_switch_on_cmd");
        alt_master_switch_off = getOptionToString("alt_master_switch_off_cmd");
        AltMasterSwitchOnCmd = XPLMFindCommand(alt_master_switch_on.c_str());
        AltMasterSwitchOffCmd = XPLMFindCommand(alt_master_switch_off.c_str());

        alt2_master_switch_on = getOptionToString("alt2_master_switch_on_cmd");
        alt2_master_switch_off = getOptionToString("alt2_master_switch_off_cmd");
        AltMaster2SwitchOnCmd = XPLMFindCommand(alt2_master_switch_on.c_str());
        AltMaster2SwitchOffCmd = XPLMFindCommand(alt2_master_switch_off.c_str());

        alt3_master_switch_on = getOptionToString("alt3_master_switch_on_cmd");
        alt3_master_switch_off = getOptionToString("alt3_master_switch_off_cmd");
        AltMaster3SwitchOnCmd = XPLMFindCommand(alt3_master_switch_on.c_str());
        AltMaster3SwitchOffCmd = XPLMFindCommand(alt3_master_switch_off.c_str());

        alt4_master_switch_on = getOptionToString("alt4_master_switch_on_cmd");
        alt4_master_switch_off = getOptionToString("alt4_master_switch_off_cmd");
        AltMaster4SwitchOnCmd = XPLMFindCommand(alt4_master_switch_on.c_str());
        AltMaster4SwitchOffCmd = XPLMFindCommand(alt4_master_switch_off.c_str());

        alt5_master_switch_on = getOptionToString("alt5_master_switch_on_cmd");
        alt5_master_switch_off = getOptionToString("alt5_master_switch_off_cmd");
        AltMaster5SwitchOnCmd = XPLMFindCommand(alt5_master_switch_on.c_str());
        AltMaster5SwitchOffCmd = XPLMFindCommand(alt5_master_switch_off.c_str());

        alt6_master_switch_on = getOptionToString("alt6_master_switch_on_cmd");
        alt6_master_switch_off = getOptionToString("alt6_master_switch_off_cmd");
        AltMaster6SwitchOnCmd = XPLMFindCommand(alt6_master_switch_on.c_str());
        AltMaster6SwitchOffCmd = XPLMFindCommand(alt6_master_switch_off.c_str());

        alt7_master_switch_on = getOptionToString("alt7_master_switch_on_cmd");
        alt7_master_switch_off = getOptionToString("alt7_master_switch_off_cmd");
        AltMaster7SwitchOnCmd = XPLMFindCommand(alt7_master_switch_on.c_str());
        AltMaster7SwitchOffCmd = XPLMFindCommand(alt7_master_switch_off.c_str());

        alt8_master_switch_on = getOptionToString("alt8_master_switch_on_cmd");
        alt8_master_switch_off = getOptionToString("alt8_master_switch_off_cmd");
        AltMaster8SwitchOnCmd = XPLMFindCommand(alt8_master_switch_on.c_str());
        AltMaster8SwitchOffCmd = XPLMFindCommand(alt8_master_switch_off.c_str());

    }

    if ((altmasterswitchenable == 3) || (altmasterswitchenable == 4)) {
        alt_master_switch_data = getOptionToString("alt_master_switch_data");
        AltMasterSwitchData = XPLMFindDataRef(alt_master_switch_data.c_str());
        alt_master_switch_data_on_value = getOptionToInt("alt_master_switch_data_on_value");
        alt_master_switch_data_off_value = getOptionToInt("alt_master_switch_data_off_value");

        alt2_master_switch_data = getOptionToString("alt2_master_switch_data");
        Alt2MasterSwitchData = XPLMFindDataRef(alt2_master_switch_data.c_str());
        alt2_master_switch_data_on_value = getOptionToInt("alt2_master_switch_data_on_value");
        alt2_master_switch_data_off_value = getOptionToInt("alt2_master_switch_data_off_value");

        alt3_master_switch_data = getOptionToString("alt3_master_switch_data");
        Alt3MasterSwitchData = XPLMFindDataRef(alt3_master_switch_data.c_str());
        alt3_master_switch_data_on_value = getOptionToInt("alt3_master_switch_data_on_value");
        alt3_master_switch_data_off_value = getOptionToInt("alt3_master_switch_data_off_value");

        alt4_master_switch_data = getOptionToString("alt4_master_switch_data");
        Alt4MasterSwitchData = XPLMFindDataRef(alt4_master_switch_data.c_str());
        alt4_master_switch_data_on_value = getOptionToInt("alt4_master_switch_data_on_value");
        alt4_master_switch_data_off_value = getOptionToInt("alt4_master_switch_data_off_value");

        alt5_master_switch_data = getOptionToString("alt5_master_switch_data");
        Alt5MasterSwitchData = XPLMFindDataRef(alt5_master_switch_data.c_str());
        alt5_master_switch_data_on_value = getOptionToInt("alt5_master_switch_data_on_value");
        alt5_master_switch_data_off_value = getOptionToInt("alt5_master_switch_data_off_value");

        alt6_master_switch_data = getOptionToString("alt6_master_switch_data");
        Alt6MasterSwitchData = XPLMFindDataRef(alt6_master_switch_data.c_str());
        alt6_master_switch_data_on_value = getOptionToInt("alt6_master_switch_data_on_value");
        alt6_master_switch_data_off_value = getOptionToInt("alt6_master_switch_data_off_value");

        alt7_master_switch_data = getOptionToString("alt7_master_switch_data");
        Alt7MasterSwitchData = XPLMFindDataRef(alt7_master_switch_data.c_str());
        alt7_master_switch_data_on_value = getOptionToInt("alt7_master_switch_data_on_value");
        alt7_master_switch_data_off_value = getOptionToInt("alt7_master_switch_data_off_value");

        alt8_master_switch_data = getOptionToString("alt8_master_switch_data");
        Alt8MasterSwitchData = XPLMFindDataRef(alt8_master_switch_data.c_str());
        alt8_master_switch_data_on_value = getOptionToInt("alt8_master_switch_data_on_value");
        alt8_master_switch_data_off_value = getOptionToInt("alt8_master_switch_data_off_value");
    }

    // avionics master switch disable - enable - remap
    readOptionAsInt("Avionics master Switch enable", &avionicsmasterswitchenable, true);

    if (avionicsmasterswitchenable == 2) {
        av_master_switch_on = getOptionToString("av_master_switch_on_cmd");
        av_master_switch_off = getOptionToString("av_master_switch_off_cmd");
        AvMasterSwitchOnCmd = XPLMFindCommand(av_master_switch_on.c_str());
        AvMasterSwitchOffCmd = XPLMFindCommand(av_master_switch_off.c_str());

        av2_master_switch_on = getOptionToString("av2_master_switch_on_cmd");
        av2_master_switch_off = getOptionToString("av2_master_switch_off_cmd");
        AvMaster2SwitchOnCmd = XPLMFindCommand(av2_master_switch_on.c_str());
        AvMaster2SwitchOffCmd = XPLMFindCommand(av2_master_switch_off.c_str());

        av3_master_switch_on = getOptionToString("av3_master_switch_on_cmd");
        av3_master_switch_off = getOptionToString("av3_master_switch_off_cmd");
        AvMaster3SwitchOnCmd = XPLMFindCommand(av3_master_switch_on.c_str());
        AvMaster3SwitchOffCmd = XPLMFindCommand(av3_master_switch_off.c_str());

        av4_master_switch_on = getOptionToString("av4_master_switch_on_cmd");
        av4_master_switch_off = getOptionToString("av4_master_switch_off_cmd");
        AvMaster4SwitchOnCmd = XPLMFindCommand(av4_master_switch_on.c_str());
        AvMaster4SwitchOffCmd = XPLMFindCommand(av4_master_switch_off.c_str());

        av5_master_switch_on = getOptionToString("av5_master_switch_on_cmd");
        av5_master_switch_off = getOptionToString("av5_master_switch_off_cmd");
        AvMaster5SwitchOnCmd = XPLMFindCommand(av5_master_switch_on.c_str());
        AvMaster5SwitchOffCmd = XPLMFindCommand(av5_master_switch_off.c_str());

        av6_master_switch_on = getOptionToString("av6_master_switch_on_cmd");
        av6_master_switch_off = getOptionToString("av6_master_switch_off_cmd");
        AvMaster6SwitchOnCmd = XPLMFindCommand(av6_master_switch_on.c_str());
        AvMaster6SwitchOffCmd = XPLMFindCommand(av6_master_switch_off.c_str());

        av7_master_switch_on = getOptionToString("av7_master_switch_on_cmd");
        av7_master_switch_off = getOptionToString("av7_master_switch_off_cmd");
        AvMaster7SwitchOnCmd = XPLMFindCommand(av7_master_switch_on.c_str());
        AvMaster7SwitchOffCmd = XPLMFindCommand(av7_master_switch_off.c_str());

        av8_master_switch_on = getOptionToString("av8_master_switch_on_cmd");
        av8_master_switch_off = getOptionToString("av8_master_switch_off_cmd");
        AvMaster8SwitchOnCmd = XPLMFindCommand(av8_master_switch_on.c_str());
        AvMaster8SwitchOffCmd = XPLMFindCommand(av8_master_switch_off.c_str());

    }

    if ((avionicsmasterswitchenable == 3) || (avionicsmasterswitchenable == 4)) {
        av_master_switch_data = getOptionToString("av_master_switch_data");
        AvMasterSwitchData = XPLMFindDataRef(av_master_switch_data.c_str());
        av_master_switch_dataf = getOptionToString("av_master_switch_dataf");
        AvMasterSwitchDataf = XPLMFindDataRef(av_master_switch_dataf.c_str());
        av_master_switch_data_on_value = getOptionToInt("av_master_switch_data_on_value");
        av_master_switch_data_off_value = getOptionToInt("av_master_switch_data_off_value");

        av2_master_switch_data = getOptionToString("av2_master_switch_data");
        Av2MasterSwitchData = XPLMFindDataRef(av2_master_switch_data.c_str());
        av2_master_switch_dataf = getOptionToString("av2_master_switch_dataf");
        Av2MasterSwitchDataf = XPLMFindDataRef(av2_master_switch_dataf.c_str());
        av2_master_switch_data_on_value = getOptionToInt("av2_master_switch_data_on_value");
        av2_master_switch_data_off_value = getOptionToInt("av2_master_switch_data_off_value")
            ;
        av3_master_switch_data = getOptionToString("av3_master_switch_data");
        Av3MasterSwitchData = XPLMFindDataRef(av3_master_switch_data.c_str());
        av3_master_switch_dataf = getOptionToString("av3_master_switch_dataf");
        Av3MasterSwitchDataf = XPLMFindDataRef(av3_master_switch_dataf.c_str());
        av3_master_switch_data_on_value = getOptionToInt("av3_master_switch_data_on_value");
        av3_master_switch_data_off_value = getOptionToInt("av3_master_switch_data_off_value");

        av4_master_switch_data = getOptionToString("av4_master_switch_data");
        Av4MasterSwitchData = XPLMFindDataRef(av4_master_switch_data.c_str());
        av4_master_switch_dataf = getOptionToString("av4_master_switch_dataf");
        Av4MasterSwitchDataf = XPLMFindDataRef(av4_master_switch_dataf.c_str());
        av4_master_switch_data_on_value = getOptionToInt("av4_master_switch_data_on_value");
        av4_master_switch_data_off_value = getOptionToInt("av4_master_switch_data_off_value");

        av5_master_switch_data = getOptionToString("av5_master_switch_data");
        Av5MasterSwitchData = XPLMFindDataRef(av5_master_switch_data.c_str());
        av5_master_switch_dataf = getOptionToString("av5_master_switch_dataf");
        Av5MasterSwitchDataf = XPLMFindDataRef(av5_master_switch_dataf.c_str());
        av5_master_switch_data_on_value = getOptionToInt("av5_master_switch_data_on_value");
        av5_master_switch_data_off_value = getOptionToInt("av5_master_switch_data_off_value");

        av6_master_switch_data = getOptionToString("av6_master_switch_data");
        Av6MasterSwitchData = XPLMFindDataRef(av6_master_switch_data.c_str());
        av6_master_switch_dataf = getOptionToString("av6_master_switch_dataf");
        Av6MasterSwitchDataf = XPLMFindDataRef(av6_master_switch_dataf.c_str());
        av6_master_switch_data_on_value = getOptionToInt("av6_master_switch_data_on_value");
        av6_master_switch_data_off_value = getOptionToInt("av6_master_switch_data_off_value");

        av7_master_switch_data = getOptionToString("av7_master_switch_data");
        Av7MasterSwitchData = XPLMFindDataRef(av7_master_switch_data.c_str());
        av7_master_switch_dataf = getOptionToString("av7_master_switch_dataf");
        Av7MasterSwitchDataf = XPLMFindDataRef(av7_master_switch_dataf.c_str());
        av7_master_switch_data_on_value = getOptionToInt("av7_master_switch_data_on_value");
        av7_master_switch_data_off_value = getOptionToInt("av7_master_switch_data_off_value");

        av8_master_switch_data = getOptionToString("av8_master_switch_data");
        Av8MasterSwitchData = XPLMFindDataRef(av8_master_switch_data.c_str());
        av8_master_switch_dataf = getOptionToString("av8_master_switch_dataf");
        Av8MasterSwitchDataf = XPLMFindDataRef(av8_master_switch_dataf.c_str());
        av8_master_switch_data_on_value = getOptionToInt("av8_master_switch_data_on_value");
        av8_master_switch_data_off_value = getOptionToInt("av8_master_switch_data_off_value");



        av9_master_switch_data = getOptionToString("av9_master_switch_data");
        Av9MasterSwitchData = XPLMFindDataRef(av9_master_switch_data.c_str());
        av9_master_switch_dataf = getOptionToString("av9_master_switch_dataf");
        Av9MasterSwitchDataf = XPLMFindDataRef(av9_master_switch_dataf.c_str());
        av9_master_switch_data_on_value = getOptionToInt("av9_master_switch_data_on_value");
        av9_master_switch_data_off_value = getOptionToInt("av9_master_switch_data_off_value");

        av10_master_switch_data = getOptionToString("av10_master_switch_data");
        Av10MasterSwitchData = XPLMFindDataRef(av10_master_switch_data.c_str());
        av10_master_switch_dataf = getOptionToString("av10_master_switch_dataf");
        Av10MasterSwitchDataf = XPLMFindDataRef(av10_master_switch_dataf.c_str());
        av10_master_switch_data_on_value = getOptionToInt("av10_master_switch_data_on_value");
        av10_master_switch_data_off_value = getOptionToInt("av10_master_switch_data_off_value")
            ;
        av11_master_switch_data = getOptionToString("av11_master_switch_data");
        Av11MasterSwitchData = XPLMFindDataRef(av11_master_switch_data.c_str());
        av11_master_switch_dataf = getOptionToString("av11_master_switch_dataf");
        Av11MasterSwitchDataf = XPLMFindDataRef(av11_master_switch_dataf.c_str());
        av11_master_switch_data_on_value = getOptionToInt("av11_master_switch_data_on_value");
        av11_master_switch_data_off_value = getOptionToInt("av11_master_switch_data_off_value");

        av12_master_switch_data = getOptionToString("av12_master_switch_data");
        Av12MasterSwitchData = XPLMFindDataRef(av12_master_switch_data.c_str());
        av12_master_switch_dataf = getOptionToString("av12_master_switch_dataf");
        Av12MasterSwitchDataf = XPLMFindDataRef(av12_master_switch_dataf.c_str());
        av12_master_switch_data_on_value = getOptionToInt("av12_master_switch_data_on_value");
        av12_master_switch_data_off_value = getOptionToInt("av12_master_switch_data_off_value");

        av13_master_switch_data = getOptionToString("av13_master_switch_data");
        Av13MasterSwitchData = XPLMFindDataRef(av13_master_switch_data.c_str());
        av13_master_switch_dataf = getOptionToString("av13_master_switch_dataf");
        Av13MasterSwitchDataf = XPLMFindDataRef(av13_master_switch_dataf.c_str());
        av13_master_switch_data_on_value = getOptionToInt("av13_master_switch_data_on_value");
        av13_master_switch_data_off_value = getOptionToInt("av13_master_switch_data_off_value");

        av14_master_switch_data = getOptionToString("av14_master_switch_data");
        Av14MasterSwitchData = XPLMFindDataRef(av14_master_switch_data.c_str());
        av14_master_switch_dataf = getOptionToString("av14_master_switch_dataf");
        Av14MasterSwitchDataf = XPLMFindDataRef(av14_master_switch_dataf.c_str());
        av14_master_switch_data_on_value = getOptionToInt("av14_master_switch_data_on_value");
        av14_master_switch_data_off_value = getOptionToInt("av14_master_switch_data_off_value");

        av15_master_switch_data = getOptionToString("av15_master_switch_data");
        Av15MasterSwitchData = XPLMFindDataRef(av15_master_switch_data.c_str());
        av15_master_switch_dataf = getOptionToString("av15_master_switch_dataf");
        Av15MasterSwitchDataf = XPLMFindDataRef(av15_master_switch_dataf.c_str());
        av15_master_switch_data_on_value = getOptionToInt("av15_master_switch_data_on_value");
        av15_master_switch_data_off_value = getOptionToInt("av15_master_switch_data_off_value");

        av16_master_switch_data = getOptionToString("av16_master_switch_data");
        Av16MasterSwitchData = XPLMFindDataRef(av16_master_switch_data.c_str());
        av16_master_switch_dataf = getOptionToString("av16_master_switch_dataf");
        Av16MasterSwitchDataf = XPLMFindDataRef(av16_master_switch_dataf.c_str());
        av16_master_switch_data_on_value = getOptionToInt("av16_master_switch_data_on_value");
        av16_master_switch_data_off_value = getOptionToInt("av16_master_switch_data_off_value");

    }


    // fuel pump switch disable - enable - remap
    readOptionAsInt("Fuel Pump Switch enable", &fuelpumpswitchenable, true);

    if (fuelpumpswitchenable == 2) {
        fuel_pump_switch_on = getOptionToString("fuel_pump_switch_on_cmd");
        fuel_pump_switch_off = getOptionToString("fuel_pump_switch_off_cmd");
        FuelPumpOnCmd = XPLMFindCommand(fuel_pump_switch_on.c_str());
        FuelPumpOffCmd = XPLMFindCommand(fuel_pump_switch_off.c_str());

        fuel_pump2_switch_on = getOptionToString("fuel_pump2_switch_on_cmd");
        fuel_pump2_switch_off = getOptionToString("fuel_pump2_switch_off_cmd");
        FuelPump2OnCmd = XPLMFindCommand(fuel_pump2_switch_on.c_str());
        FuelPump2OffCmd = XPLMFindCommand(fuel_pump2_switch_off.c_str());

        fuel_pump3_switch_on = getOptionToString("fuel_pump3_switch_on_cmd");
        fuel_pump3_switch_off = getOptionToString("fuel_pump3_switch_off_cmd");
        FuelPump3OnCmd = XPLMFindCommand(fuel_pump3_switch_on.c_str());
        FuelPump3OffCmd = XPLMFindCommand(fuel_pump3_switch_off.c_str());

        fuel_pump4_switch_on = getOptionToString("fuel_pump4_switch_on_cmd");
        fuel_pump4_switch_off = getOptionToString("fuel_pump4_switch_off_cmd");
        FuelPump4OnCmd = XPLMFindCommand(fuel_pump4_switch_on.c_str());
        FuelPump4OffCmd = XPLMFindCommand(fuel_pump4_switch_off.c_str());

        fuel_pump5_switch_on = getOptionToString("fuel_pump5_switch_on_cmd");
        fuel_pump5_switch_off = getOptionToString("fuel_pump5_switch_off_cmd");
        FuelPump5OnCmd = XPLMFindCommand(fuel_pump5_switch_on.c_str());
        FuelPump5OffCmd = XPLMFindCommand(fuel_pump5_switch_off.c_str());

        fuel_pump6_switch_on = getOptionToString("fuel_pump6_switch_on_cmd");
        fuel_pump6_switch_off = getOptionToString("fuel_pump6_switch_off_cmd");
        FuelPump6OnCmd = XPLMFindCommand(fuel_pump6_switch_on.c_str());
        FuelPump6OffCmd = XPLMFindCommand(fuel_pump6_switch_off.c_str());

        fuel_pump7_switch_on = getOptionToString("fuel_pump7_switch_on_cmd");
        fuel_pump7_switch_off = getOptionToString("fuel_pump7_switch_off_cmd");
        FuelPump7OnCmd = XPLMFindCommand(fuel_pump7_switch_on.c_str());
        FuelPump7OffCmd = XPLMFindCommand(fuel_pump7_switch_off.c_str());

        fuel_pump8_switch_on = getOptionToString("fuel_pump8_switch_on_cmd");
        fuel_pump8_switch_off = getOptionToString("fuel_pump8_switch_off_cmd");
        FuelPump8OnCmd = XPLMFindCommand(fuel_pump8_switch_on.c_str());
        FuelPump8OffCmd = XPLMFindCommand(fuel_pump8_switch_off.c_str());
    }

    if ((fuelpumpswitchenable == 3) || (fuelpumpswitchenable == 4)) {
        fuel_pump_switch_data = getOptionToString("fuel_pump_switch_data");
        FuelPumpSwitchData = XPLMFindDataRef(fuel_pump_switch_data.c_str());
        fuel_pump_switch_data_on_value = getOptionToInt("fuel_pump_switch_data_on_value");
        fuel_pump_switch_data_off_value = getOptionToInt("fuel_pump_switch_data_off_value");

        fuel_pump2_switch_data = getOptionToString("fuel_pump2_switch_data");
        FuelPump2SwitchData = XPLMFindDataRef(fuel_pump2_switch_data.c_str());
        fuel_pump2_switch_data_on_value = getOptionToInt("fuel_pump2_switch_data_on_value");
        fuel_pump2_switch_data_off_value = getOptionToInt("fuel_pump2_switch_data_off_value");

        fuel_pump3_switch_data = getOptionToString("fuel_pump3_switch_data");
        FuelPump3SwitchData = XPLMFindDataRef(fuel_pump3_switch_data.c_str());
        fuel_pump3_switch_data_on_value = getOptionToInt("fuel_pump3_switch_data_on_value");
        fuel_pump3_switch_data_off_value = getOptionToInt("fuel_pump3_switch_data_off_value");

        fuel_pump4_switch_data = getOptionToString("fuel_pump4_switch_data");
        FuelPump4SwitchData = XPLMFindDataRef(fuel_pump4_switch_data.c_str());
        fuel_pump4_switch_data_on_value = getOptionToInt("fuel_pump4_switch_data_on_value");
        fuel_pump4_switch_data_off_value = getOptionToInt("fuel_pump4_switch_data_off_value");

        fuel_pump5_switch_data = getOptionToString("fuel_pump5_switch_data");
        FuelPump5SwitchData = XPLMFindDataRef(fuel_pump5_switch_data.c_str());
        fuel_pump5_switch_data_on_value = getOptionToInt("fuel_pump5_switch_data_on_value");
        fuel_pump5_switch_data_off_value = getOptionToInt("fuel_pump5_switch_data_off_value");

        fuel_pump6_switch_data = getOptionToString("fuel_pump6_switch_data");
        FuelPump6SwitchData = XPLMFindDataRef(fuel_pump6_switch_data.c_str());
        fuel_pump6_switch_data_on_value = getOptionToInt("fuel_pump6_switch_data_on_value");
        fuel_pump6_switch_data_off_value = getOptionToInt("fuel_pump6_switch_data_off_value");

        fuel_pump7_switch_data = getOptionToString("fuel_pump7_switch_data");
        FuelPump7SwitchData = XPLMFindDataRef(fuel_pump7_switch_data.c_str());
        fuel_pump7_switch_data_on_value = getOptionToInt("fuel_pump7_switch_data_on_value");
        fuel_pump7_switch_data_off_value = getOptionToInt("fuel_pump7_switch_data_off_value");

        fuel_pump8_switch_data = getOptionToString("fuel_pump8_switch_data");
        FuelPump8SwitchData = XPLMFindDataRef(fuel_pump8_switch_data.c_str());
        fuel_pump8_switch_data_on_value = getOptionToInt("fuel_pump8_switch_data_on_value");
        fuel_pump8_switch_data_off_value = getOptionToInt("fuel_pump8_switch_data_off_value");

    }



    // deice switch disable - enable - remap
    readOptionAsInt("Deice Switch enable", &deiceswitchenable, true);

    if (deiceswitchenable == 2) {
        deice_switch_on = getOptionToString("deice_switch_on_cmd");
        deice_switch_off = getOptionToString("deice_switch_off_cmd");
        DeiceOnCmd = XPLMFindCommand(deice_switch_on.c_str());
        DeiceOffCmd = XPLMFindCommand(deice_switch_off.c_str());

        deice2_switch_on = getOptionToString("deice2_switch_on_cmd");
        deice2_switch_off = getOptionToString("deice2_switch_off_cmd");
        DeiceOnCmd2 = XPLMFindCommand(deice2_switch_on.c_str());
        DeiceOffCmd2 = XPLMFindCommand(deice2_switch_off.c_str());

        deice3_switch_on = getOptionToString("deice3_switch_on_cmd");
        deice3_switch_off = getOptionToString("deice3_switch_off_cmd");
        DeiceOnCmd3 = XPLMFindCommand(deice3_switch_on.c_str());
        DeiceOffCmd3 = XPLMFindCommand(deice3_switch_off.c_str());

        deice4_switch_on = getOptionToString("deice4_switch_on_cmd");
        deice4_switch_off = getOptionToString("deice4_switch_off_cmd");
        DeiceOnCmd4 = XPLMFindCommand(deice4_switch_on.c_str());
        DeiceOffCmd4 = XPLMFindCommand(deice4_switch_off.c_str());

        deice5_switch_on = getOptionToString("deice5_switch_on_cmd");
        deice5_switch_off = getOptionToString("deice5_switch_off_cmd");
        DeiceOnCmd5 = XPLMFindCommand(deice5_switch_on.c_str());
        DeiceOffCmd5 = XPLMFindCommand(deice5_switch_off.c_str());

        deice6_switch_on = getOptionToString("deice6_switch_on_cmd");
        deice6_switch_off = getOptionToString("deice6_switch_off_cmd");
        DeiceOnCmd6 = XPLMFindCommand(deice6_switch_on.c_str());
        DeiceOffCmd6 = XPLMFindCommand(deice6_switch_off.c_str());

        deice7_switch_on = getOptionToString("deice7_switch_on_cmd");
        deice7_switch_off = getOptionToString("deice7_switch_off_cmd");
        DeiceOnCmd7 = XPLMFindCommand(deice7_switch_on.c_str());
        DeiceOffCmd7 = XPLMFindCommand(deice7_switch_off.c_str());

        deice8_switch_on = getOptionToString("deice8_switch_on_cmd");
        deice8_switch_off = getOptionToString("deice8_switch_off_cmd");
        DeiceOnCmd8 = XPLMFindCommand(deice8_switch_on.c_str());
        DeiceOffCmd8 = XPLMFindCommand(deice8_switch_off.c_str());
    }

    if ((deiceswitchenable == 3) || (deiceswitchenable == 4)) {

        deice_switch_data = getOptionToString("deice_switch_data");
        DeiceSwitchData = XPLMFindDataRef(deice_switch_data.c_str());
        deice_switch_data_on_value = getOptionToInt("deice_switch_data_on_value");
        deice_switch_data_off_value = getOptionToInt("deice_switch_data_off_value");

        deice2_switch_data = getOptionToString("deice2_switch_data");
        Deice2SwitchData = XPLMFindDataRef(deice2_switch_data.c_str());
        deice2_switch_data_on_value = getOptionToInt("deice2_switch_data_on_value");
        deice2_switch_data_off_value = getOptionToInt("deice2_switch_data_off_value");

        deice3_switch_data = getOptionToString("deice3_switch_data");
        Deice3SwitchData = XPLMFindDataRef(deice3_switch_data.c_str());
        deice3_switch_data_on_value = getOptionToInt("deice3_switch_data_on_value");
        deice3_switch_data_off_value = getOptionToInt("deice3_switch_data_off_value");

        deice4_switch_data = getOptionToString("deice4_switch_data");
        Deice4SwitchData = XPLMFindDataRef(deice4_switch_data.c_str());
        deice4_switch_data_on_value = getOptionToInt("deice4_switch_data_on_value");
        deice4_switch_data_off_value = getOptionToInt("deice4_switch_data_off_value");

        deice5_switch_data = getOptionToString("deice5_switch_data");
        Deice5SwitchData = XPLMFindDataRef(deice5_switch_data.c_str());
        deice5_switch_data_on_value = getOptionToInt("deice5_switch_data_on_value");
        deice5_switch_data_off_value = getOptionToInt("deice5_switch_data_off_value");

        deice6_switch_data = getOptionToString("deice6_switch_data");
        Deice6SwitchData = XPLMFindDataRef(deice6_switch_data.c_str());
        deice6_switch_data_on_value = getOptionToInt("deice6_switch_data_on_value");
        deice6_switch_data_off_value = getOptionToInt("deice6_switch_data_off_value");

        deice7_switch_data = getOptionToString("deice7_switch_data");
        Deice7SwitchData = XPLMFindDataRef(deice7_switch_data.c_str());
        deice7_switch_data_on_value = getOptionToInt("deice7_switch_data_on_value");
        deice7_switch_data_off_value = getOptionToInt("deice7_switch_data_off_value");

        deice8_switch_data = getOptionToString("deice8_switch_data");
        Deice8SwitchData = XPLMFindDataRef(deice8_switch_data.c_str());
        deice8_switch_data_on_value = getOptionToInt("deice8_switch_data_on_value");
        deice8_switch_data_off_value = getOptionToInt("deice8_switch_data_off_value");

    }


    // pitot heat switch disable - enable - remap
    readOptionAsInt("Pitot Heat Switch enable", &pitotheatswitchenable, true);

    if (pitotheatswitchenable == 2) {
        pitot_heat_switch_on = getOptionToString("pitot_heat_switch_on_cmd");
        pitot_heat_switch_off = getOptionToString("pitot_heat_switch_off_cmd");
        PitotHeatOnCmd = XPLMFindCommand(pitot_heat_switch_on.c_str());
        PitotHeatOffCmd = XPLMFindCommand(pitot_heat_switch_off.c_str());

        pitot2_heat_switch_on = getOptionToString("pitot2_heat_switch_on_cmd");
        pitot2_heat_switch_off = getOptionToString("pitot2_heat_switch_off_cmd");
        PitotHeat2OnCmd = XPLMFindCommand(pitot2_heat_switch_on.c_str());
        PitotHeat2OffCmd = XPLMFindCommand(pitot2_heat_switch_off.c_str());

        pitot3_heat_switch_on = getOptionToString("pitot3_heat_switch_on_cmd");
        pitot3_heat_switch_off = getOptionToString("pitot3_heat_switch_off_cmd");
        PitotHeat3OnCmd = XPLMFindCommand(pitot3_heat_switch_on.c_str());
        PitotHeat3OffCmd = XPLMFindCommand(pitot3_heat_switch_off.c_str());

        pitot4_heat_switch_on = getOptionToString("pitot4_heat_switch_on_cmd");
        pitot4_heat_switch_off = getOptionToString("pitot4_heat_switch_off_cmd");
        PitotHeat4OnCmd = XPLMFindCommand(pitot4_heat_switch_on.c_str());
        PitotHeat4OffCmd = XPLMFindCommand(pitot4_heat_switch_off.c_str());

        pitot5_heat_switch_on = getOptionToString("pitot5_heat_switch_on_cmd");
        pitot5_heat_switch_off = getOptionToString("pitot5_heat_switch_off_cmd");
        PitotHeat5OnCmd = XPLMFindCommand(pitot5_heat_switch_on.c_str());
        PitotHeat5OffCmd = XPLMFindCommand(pitot5_heat_switch_off.c_str());

        pitot6_heat_switch_on = getOptionToString("pitot6_heat_switch_on_cmd");
        pitot6_heat_switch_off = getOptionToString("pitot6_heat_switch_off_cmd");
        PitotHeat6OnCmd = XPLMFindCommand(pitot6_heat_switch_on.c_str());
        PitotHeat6OffCmd = XPLMFindCommand(pitot6_heat_switch_off.c_str());

        pitot7_heat_switch_on = getOptionToString("pitot7_heat_switch_on_cmd");
        pitot7_heat_switch_off = getOptionToString("pitot7_heat_switch_off_cmd");
        PitotHeat7OnCmd = XPLMFindCommand(pitot7_heat_switch_on.c_str());
        PitotHeat7OffCmd = XPLMFindCommand(pitot7_heat_switch_off.c_str());

        pitot8_heat_switch_on = getOptionToString("pitot8_heat_switch_on_cmd");
        pitot8_heat_switch_off = getOptionToString("pitot8_heat_switch_off_cmd");
        PitotHeat8OnCmd = XPLMFindCommand(pitot8_heat_switch_on.c_str());
        PitotHeat8OffCmd = XPLMFindCommand(pitot8_heat_switch_off.c_str());
    }

    if ((pitotheatswitchenable == 3) || (pitotheatswitchenable == 4)) {
        pitot_heat_switch_data = getOptionToString("pitot_heat_switch_data");
        PitotHeatSwitchData = XPLMFindDataRef(pitot_heat_switch_data.c_str());
        pitot_heat_switch_data_on_value = getOptionToInt("pitot_heat_switch_data_on_value");
        pitot_heat_switch_data_off_value = getOptionToInt("pitot_heat_switch_data_off_value");

        pitot2_heat_switch_data = getOptionToString("pitot2_heat_switch_data");
        Pitot2HeatSwitchData = XPLMFindDataRef(pitot2_heat_switch_data.c_str());
        pitot2_heat_switch_data_on_value = getOptionToInt("pitot2_heat_switch_data_on_value");
        pitot2_heat_switch_data_off_value = getOptionToInt("pitot2_heat_switch_data_off_value");

        pitot3_heat_switch_data = getOptionToString("pitot3_heat_switch_data");
        Pitot3HeatSwitchData = XPLMFindDataRef(pitot3_heat_switch_data.c_str());
        pitot3_heat_switch_data_on_value = getOptionToInt("pitot3_heat_switch_data_on_value");
        pitot3_heat_switch_data_off_value = getOptionToInt("pitot3_heat_switch_data_off_value");

        pitot4_heat_switch_data = getOptionToString("pitot4_heat_switch_data");
        Pitot4HeatSwitchData = XPLMFindDataRef(pitot4_heat_switch_data.c_str());
        pitot4_heat_switch_data_on_value = getOptionToInt("pitot4_heat_switch_data_on_value");
        pitot4_heat_switch_data_off_value = getOptionToInt("pitot4_heat_switch_data_off_value");

        pitot5_heat_switch_data = getOptionToString("pitot5_heat_switch_data");
        Pitot5HeatSwitchData = XPLMFindDataRef(pitot5_heat_switch_data.c_str());
        pitot5_heat_switch_data_on_value = getOptionToInt("pitot5_heat_switch_data_on_value");
        pitot5_heat_switch_data_off_value = getOptionToInt("pitot5_heat_switch_data_off_value");

        pitot6_heat_switch_data = getOptionToString("pitot6_heat_switch_data");
        Pitot6HeatSwitchData = XPLMFindDataRef(pitot6_heat_switch_data.c_str());
        pitot6_heat_switch_data_on_value = getOptionToInt("pitot6_heat_switch_data_on_value");
        pitot6_heat_switch_data_off_value = getOptionToInt("pitot6_heat_switch_data_off_value");

        pitot7_heat_switch_data = getOptionToString("pitot7_heat_switch_data");
        Pitot7HeatSwitchData = XPLMFindDataRef(pitot7_heat_switch_data.c_str());
        pitot7_heat_switch_data_on_value = getOptionToInt("pitot7_heat_switch_data_on_value");
        pitot7_heat_switch_data_off_value = getOptionToInt("pitot7_heat_switch_data_off_value");

        pitot8_heat_switch_data = getOptionToString("pitot8_heat_switch_data");
        Pitot8HeatSwitchData = XPLMFindDataRef(pitot8_heat_switch_data.c_str());
        pitot8_heat_switch_data_on_value = getOptionToInt("pitot8_heat_switch_data_on_value");
        pitot8_heat_switch_data_off_value = getOptionToInt("pitot8_heat_switch_data_off_value");

    }

    // landing gear up knob disable - enable - remap
    readOptionAsInt("Landing Gear Knob Up enable", &landinggearknobupenable, true);

    if (landinggearknobupenable == 2) {
        gear_switch_up_on = getOptionToString("gear_up_switch_on_cmd");
        gear_switch_up_off = getOptionToString("gear_up_switch_off_cmd");
        GearUpOnCmd = XPLMFindCommand(gear_switch_up_on.c_str());
        GearUpOffCmd = XPLMFindCommand(gear_switch_up_off.c_str());

        gear2_switch_up_on = getOptionToString("gear2_up_switch_on_cmd");
        gear2_switch_up_off = getOptionToString("gear2_up_switch_off_cmd");
        GearUp2OnCmd = XPLMFindCommand(gear2_switch_up_on.c_str());
        GearUp2OffCmd = XPLMFindCommand(gear2_switch_up_off.c_str());

        gear3_switch_up_on = getOptionToString("gear3_up_switch_on_cmd");
        gear3_switch_up_off = getOptionToString("gear3_up_switch_off_cmd");
        GearUp3OnCmd = XPLMFindCommand(gear3_switch_up_on.c_str());
        GearUp3OffCmd = XPLMFindCommand(gear3_switch_up_off.c_str());

        gear4_switch_up_on = getOptionToString("gear4_up_switch_on_cmd");
        gear4_switch_up_off = getOptionToString("gear4_up_switch_off_cmd");
        GearUp4OnCmd = XPLMFindCommand(gear4_switch_up_on.c_str());
        GearUp4OffCmd = XPLMFindCommand(gear4_switch_up_off.c_str());

        gear5_switch_up_on = getOptionToString("gear5_up_switch_on_cmd");
        gear5_switch_up_off = getOptionToString("gear5_up_switch_off_cmd");
        GearUp5OnCmd = XPLMFindCommand(gear5_switch_up_on.c_str());
        GearUp5OffCmd = XPLMFindCommand(gear5_switch_up_off.c_str());

        gear6_switch_up_on = getOptionToString("gear6_up_switch_on_cmd");
        gear6_switch_up_off = getOptionToString("gear6_up_switch_off_cmd");
        GearUp6OnCmd = XPLMFindCommand(gear6_switch_up_on.c_str());
        GearUp6OffCmd = XPLMFindCommand(gear6_switch_up_off.c_str());

        gear7_switch_up_on = getOptionToString("gear7_up_switch_on_cmd");
        gear7_switch_up_off = getOptionToString("gear7_up_switch_off_cmd");
        GearUp7OnCmd = XPLMFindCommand(gear7_switch_up_on.c_str());
        GearUp7OffCmd = XPLMFindCommand(gear7_switch_up_off.c_str());

        gear8_switch_up_on = getOptionToString("gear8_up_switch_on_cmd");
        gear8_switch_up_off = getOptionToString("gear8_up_switch_off_cmd");
        GearUp8OnCmd = XPLMFindCommand(gear8_switch_up_on.c_str());
        GearUp8OffCmd = XPLMFindCommand(gear8_switch_up_off.c_str());
    }

    if ((landinggearknobupenable == 3) || (landinggearknobupenable == 4)) {
        gear_switch_up_data = getOptionToString("gear_up_switch_data");
        GearUpData = XPLMFindDataRef(gear_switch_up_on.c_str());
        gear_switch_up_data_on_value = getOptionToInt("gear_up_switch_data_on_value");
        gear_switch_up_data_off_value = getOptionToInt("gear_up_switch_data_off_value");

    }

    // landing gear dn knob disable - enable - remap
    readOptionAsInt("Landing Gear Knob Up enable", &landinggearknobdnenable, true);

    if (landinggearknobdnenable == 2) {
        gear_switch_down_on = getOptionToString("gear_dn_switch_on_cmd");
        gear_switch_down_off = getOptionToString("gear_dn_switch_off_cmd");
        GearDnOnCmd = XPLMFindCommand(gear_switch_down_on.c_str());
        GearDnOffCmd = XPLMFindCommand(gear_switch_down_off.c_str());

        gear2_switch_down_on = getOptionToString("gear2_dn_switch_on_cmd");
        gear2_switch_down_off = getOptionToString("gear2_dn_switch_off_cmd");
        GearDn2OnCmd = XPLMFindCommand(gear2_switch_down_on.c_str());
        GearDn2OffCmd = XPLMFindCommand(gear2_switch_down_off.c_str());

        gear3_switch_down_on = getOptionToString("gear3_dn_switch_on_cmd");
        gear3_switch_down_off = getOptionToString("gear3_dn_switch_off_cmd");
        GearDn3OnCmd = XPLMFindCommand(gear3_switch_down_on.c_str());
        GearDn3OffCmd = XPLMFindCommand(gear3_switch_down_off.c_str());

        gear4_switch_down_on = getOptionToString("gear4_dn_switch_on_cmd");
        gear4_switch_down_off = getOptionToString("gear4_dn_switch_off_cmd");
        GearDn4OnCmd = XPLMFindCommand(gear4_switch_down_on.c_str());
        GearDn4OffCmd = XPLMFindCommand(gear4_switch_down_off.c_str());

        gear5_switch_down_on = getOptionToString("gear5_dn_switch_on_cmd");
        gear5_switch_down_off = getOptionToString("gear5_dn_switch_off_cmd");
        GearDn5OnCmd = XPLMFindCommand(gear5_switch_down_on.c_str());
        GearDn5OffCmd = XPLMFindCommand(gear5_switch_down_off.c_str());

        gear6_switch_down_on = getOptionToString("gear6_dn_switch_on_cmd");
        gear6_switch_down_off = getOptionToString("gear6_dn_switch_off_cmd");
        GearDn6OnCmd = XPLMFindCommand(gear6_switch_down_on.c_str());
        GearDn6OffCmd = XPLMFindCommand(gear6_switch_down_off.c_str());

        gear7_switch_down_on = getOptionToString("gear7_dn_switch_on_cmd");
        gear7_switch_down_off = getOptionToString("gear7_dn_switch_off_cmd");
        GearDn7OnCmd = XPLMFindCommand(gear7_switch_down_on.c_str());
        GearDn7OffCmd = XPLMFindCommand(gear7_switch_down_off.c_str());

        gear8_switch_down_on = getOptionToString("gear8_dn_switch_on_cmd");
        gear8_switch_down_off = getOptionToString("gear8_dn_switch_off_cmd");
        GearDn8OnCmd = XPLMFindCommand(gear8_switch_down_on.c_str());
        GearDn8OffCmd = XPLMFindCommand(gear8_switch_down_off.c_str());
    }

    if ((landinggearknobdnenable == 3) || (landinggearknobdnenable == 4)) {
        gear_switch_down_data = getOptionToString("gear_dn_switch_data");
        GearDnData = XPLMFindDataRef(gear_switch_down_data.c_str());
        gear_switch_down_data_on_value = getOptionToInt("gear_dn_switch_data_on_value");
        gear_switch_down_data_off_value = getOptionToInt("gear_dn_switch_data_off_value");
    }


    // landing gear led disable - enable - remap
    readOptionAsInt("Landing Gear Led enable", &gearledenable);
    if (gearledenable == 2) {
        landing_gear_nose_led_data = getOptionToString("landing_gear_nose_led_data");
        LandingGearNoseLedData = XPLMFindDataRef(landing_gear_nose_led_data.c_str());

        landing_gear_left_led_data = getOptionToString("landing_gear_left_led_data");
        LandingGearLeftLedData = XPLMFindDataRef(landing_gear_left_led_data.c_str());

        landing_gear_right_led_data = getOptionToString("landing_gear_right_led_data");
        LandingGearRightLedData = XPLMFindDataRef(landing_gear_right_led_data.c_str());
    }

    // cowl flaps switch disable - enable - remap
    readOptionAsInt("Cowl Flaps enable", &cowlflapsenable);

    if (cowlflapsenable == 2) {
        cowl_flaps_open = getOptionToString("cowl_flaps_open_cmd");
        cowl_flaps_close = getOptionToString("cowl_flaps_close_cmd");
        CowlFlapsOpenCmd = XPLMFindCommand(cowl_flaps_open.c_str());
        CowlFlapsCloseCmd = XPLMFindCommand(cowl_flaps_close.c_str());

        cowl2_flaps_open = getOptionToString("cowl2_flaps_open_cmd");
        cowl2_flaps_close = getOptionToString("cowl2_flaps_close_cmd");
        CowlFlaps2OpenCmd = XPLMFindCommand(cowl2_flaps_open.c_str());
        CowlFlaps2CloseCmd = XPLMFindCommand(cowl2_flaps_close.c_str());

        cowl3_flaps_open = getOptionToString("cowl3_flaps_open_cmd");
        cowl3_flaps_close = getOptionToString("cowl3_flaps_close_cmd");
        CowlFlaps3OpenCmd = XPLMFindCommand(cowl3_flaps_open.c_str());
        CowlFlaps3CloseCmd = XPLMFindCommand(cowl3_flaps_close.c_str());

        cowl4_flaps_open = getOptionToString("cowl4_flaps_open_cmd");
        cowl4_flaps_close = getOptionToString("cowl4_flaps_close_cmd");
        CowlFlaps4OpenCmd = XPLMFindCommand(cowl4_flaps_open.c_str());
        CowlFlaps4CloseCmd = XPLMFindCommand(cowl4_flaps_close.c_str());

        cowl5_flaps_open = getOptionToString("cowl5_flaps_open_cmd");
        cowl5_flaps_close = getOptionToString("cowl5_flaps_close_cmd");
        CowlFlaps5OpenCmd = XPLMFindCommand(cowl5_flaps_open.c_str());
        CowlFlaps5CloseCmd = XPLMFindCommand(cowl5_flaps_close.c_str());

        cowl6_flaps_open = getOptionToString("cowl6_flaps_open_cmd");
        cowl6_flaps_close = getOptionToString("cowl6_flaps_close_cmd");
        CowlFlaps6OpenCmd = XPLMFindCommand(cowl6_flaps_open.c_str());
        CowlFlaps6CloseCmd = XPLMFindCommand(cowl6_flaps_close.c_str());

        cowl7_flaps_open = getOptionToString("cowl7_flaps_open_cmd");
        cowl7_flaps_close = getOptionToString("cowl7_flaps_close_cmd");
        CowlFlaps7OpenCmd = XPLMFindCommand(cowl7_flaps_open.c_str());
        CowlFlaps7CloseCmd = XPLMFindCommand(cowl7_flaps_close.c_str());

        cowl8_flaps_open = getOptionToString("cowl8_flaps_open_cmd");
        cowl8_flaps_close = getOptionToString("cowl8_flaps_close_cmd");
        CowlFlaps8OpenCmd = XPLMFindCommand(cowl8_flaps_open.c_str());
        CowlFlaps8CloseCmd = XPLMFindCommand(cowl8_flaps_close.c_str());

    }

    if ((cowlflapsenable == 3) || (cowlflapsenable == 4)) {
        cowl_flaps_data = getOptionToString("cowl_flaps_data");
        CowlFlapsData = XPLMFindDataRef(cowl_flaps_data.c_str());
        cowl_flaps_data_on_value = getOptionToInt("cowl_flaps_data_open_value");
        cowl_flaps_data_off_value = getOptionToInt("cowl_flaps_data_close_value");

        cowl2_flaps_data = getOptionToString("cowl2_flaps_data");
        Cowl2FlapsData = XPLMFindDataRef(cowl2_flaps_data.c_str());
        cowl2_flaps_data_on_value = getOptionToInt("cowl2_flaps_data_open_value");
        cowl2_flaps_data_off_value = getOptionToInt("cowl2_flaps_data_close_value");

        cowl3_flaps_data = getOptionToString("cowl3_flaps_data");
        Cowl3FlapsData = XPLMFindDataRef(cowl3_flaps_data.c_str());
        cowl3_flaps_data_on_value = getOptionToInt("cowl3_flaps_data_open_value");
        cowl3_flaps_data_off_value = getOptionToInt("cowl3_flaps_data_close_value");

        cowl4_flaps_data = getOptionToString("cowl4_flaps_data");
        Cowl4FlapsData = XPLMFindDataRef(cowl4_flaps_data.c_str());
        cowl4_flaps_data_on_value = getOptionToInt("cowl4_flaps_data_open_value");
        cowl4_flaps_data_off_value = getOptionToInt("cowl4_flaps_data_close_value");

        cowl5_flaps_data = getOptionToString("cowl5_flaps_data");
        Cowl5FlapsData = XPLMFindDataRef(cowl5_flaps_data.c_str());
        cowl5_flaps_data_on_value = getOptionToInt("cowl5_flaps_data_open_value");
        cowl5_flaps_data_off_value = getOptionToInt("cowl5_flaps_data_close_value");

        cowl6_flaps_data = getOptionToString("cowl6_flaps_data");
        Cowl6FlapsData = XPLMFindDataRef(cowl6_flaps_data.c_str());
        cowl6_flaps_data_on_value = getOptionToInt("cowl6_flaps_data_open_value");
        cowl6_flaps_data_off_value = getOptionToInt("cowl6_flaps_data_close_value");

        cowl7_flaps_data = getOptionToString("cowl7_flaps_data");
        Cowl7FlapsData = XPLMFindDataRef(cowl7_flaps_data.c_str());
        cowl7_flaps_data_on_value = getOptionToInt("cowl7_flaps_data_open_value");
        cowl7_flaps_data_off_value = getOptionToInt("cowl7_flaps_data_close_value");

        cowl8_flaps_data = getOptionToString("cowl8_flaps_data");
        Cowl8FlapsData = XPLMFindDataRef(cowl8_flaps_data.c_str());
        cowl8_flaps_data_on_value = getOptionToInt("cowl8_flaps_data_open_value");
        cowl8_flaps_data_off_value = getOptionToInt("cowl8_flaps_data_close_value");

    }


    // panel lights switch disable - enable - remap
    readOptionAsInt("Panel Lights Switch enable", &panellightswitchenable);

    if (panellightswitchenable == 2) {
        panel_lights_switch_on = getOptionToString("panel_lights_switch_on_cmd");
        panel_lights_switch_off = getOptionToString("panel_lights_switch_off_cmd");
        PanelLightsOnCmd = XPLMFindCommand(panel_lights_switch_on.c_str());
        PanelLightsOffCmd = XPLMFindCommand(panel_lights_switch_off.c_str());

        panel_lights_switch2_on = getOptionToString("panel_lights_switch2_on_cmd");
        panel_lights_switch2_off = getOptionToString("panel_lights_switch2_off_cmd");
        PanelLights2OnCmd = XPLMFindCommand(panel_lights_switch2_on.c_str());
        PanelLights2OffCmd = XPLMFindCommand(panel_lights_switch2_off.c_str());

        panel_lights_switch3_on = getOptionToString("panel_lights_switch3_on_cmd");
        panel_lights_switch3_off = getOptionToString("panel_lights_switch3_off_cmd");
        PanelLights3OnCmd = XPLMFindCommand(panel_lights_switch3_on.c_str());
        PanelLights3OffCmd = XPLMFindCommand(panel_lights_switch3_off.c_str());

        panel_lights_switch4_on = getOptionToString("panel_lights_switch4_on_cmd");
        panel_lights_switch4_off = getOptionToString("panel_lights_switch4_off_cmd");
        PanelLights4OnCmd = XPLMFindCommand(panel_lights_switch4_on.c_str());
        PanelLights4OffCmd = XPLMFindCommand(panel_lights_switch4_off.c_str());

        panel_lights_switch5_on = getOptionToString("panel_lights_switch5_on_cmd");
        panel_lights_switch5_off = getOptionToString("panel_lights_switch5_off_cmd");
        PanelLights5OnCmd = XPLMFindCommand(panel_lights_switch5_on.c_str());
        PanelLights5OffCmd = XPLMFindCommand(panel_lights_switch5_off.c_str());

        panel_lights_switch6_on = getOptionToString("panel_lights_switch6_on_cmd");
        panel_lights_switch6_off = getOptionToString("panel_lights_switch6_off_cmd");
        PanelLights6OnCmd = XPLMFindCommand(panel_lights_switch6_on.c_str());
        PanelLights6OffCmd = XPLMFindCommand(panel_lights_switch6_off.c_str());

        panel_lights_switch7_on = getOptionToString("panel_lights_switch7_on_cmd");
        panel_lights_switch7_off = getOptionToString("panel_lights_switch7_off_cmd");
        PanelLights7OnCmd = XPLMFindCommand(panel_lights_switch7_on.c_str());
        PanelLights7OffCmd = XPLMFindCommand(panel_lights_switch7_off.c_str());

        panel_lights_switch8_on = getOptionToString("panel_lights_switch8_on_cmd");
        panel_lights_switch8_off = getOptionToString("panel_lights_switch8_off_cmd");
        PanelLights8OnCmd = XPLMFindCommand(panel_lights_switch8_on.c_str());
        PanelLights8OffCmd = XPLMFindCommand(panel_lights_switch8_off.c_str());
    }



    if ((panellightswitchenable == 3) || (panellightswitchenable == 4) || (panellightswitchenable == 5)) {
        panel_lights_switch_data = getOptionToString("panel_lights_switch_data");
        PanelLightsData = XPLMFindDataRef(panel_lights_switch_data.c_str());
        panel_lights_switch_data_on_value = getOptionToInt("panel_lights_switch_data_on_value");
        panel_lights_switch_data_off_value = getOptionToInt("panel_lights_switch_data_off_value");
        panel_lights_switch_data_array_offset = getOptionToInt("panel_lights_switch_data_array_offset");
        panel_lights_switch_data_array_size = getOptionToInt("panel_lights_switch_data_array_size");

        panel_lights_switch2_data = getOptionToString("panel_lights_switch2_data");
        PanelLights2Data = XPLMFindDataRef(panel_lights_switch2_data.c_str());
        panel_lights_switch2_data_on_value = getOptionToInt("panel_lights_switch2_data_on_value");
        panel_lights_switch2_data_off_value = getOptionToInt("panel_lights_switch2_data_off_value");
        panel_lights_switch2_data_array_offset = getOptionToInt("panel_lights_switch2_data_array_offset");
        panel_lights_switch2_data_array_size = getOptionToInt("panel_lights_switch2_data_array_size");

        panel_lights_switch3_data = getOptionToString("panel_lights_switch3_data");
        PanelLights3Data = XPLMFindDataRef(panel_lights_switch3_data.c_str());
        panel_lights_switch3_data_on_value = getOptionToInt("panel_lights_switch3_data_on_value");
        panel_lights_switch3_data_off_value = getOptionToInt("panel_lights_switch3_data_off_value");
        panel_lights_switch3_data_array_offset = getOptionToInt("panel_lights_switch3_data_array_offset");
        panel_lights_switch3_data_array_size = getOptionToInt("panel_lights_switch3_data_array_size");

        panel_lights_switch4_data = getOptionToString("panel_lights_switch4_data");
        PanelLights4Data = XPLMFindDataRef(panel_lights_switch4_data.c_str());
        panel_lights_switch4_data_on_value = getOptionToInt("panel_lights_switch4_data_on_value");
        panel_lights_switch4_data_off_value = getOptionToInt("panel_lights_switch4_data_off_value");
        panel_lights_switch4_data_array_offset = getOptionToInt("panel_lights_switch4_data_array_offset");
        panel_lights_switch4_data_array_size = getOptionToInt("panel_lights_switch4_data_array_size");

        panel_lights_switch5_data = getOptionToString("panel_lights_switch5_data");
        PanelLights5Data = XPLMFindDataRef(panel_lights_switch5_data.c_str());
        panel_lights_switch5_data_on_value = getOptionToInt("panel_lights_switch5_data_on_value");
        panel_lights_switch5_data_off_value = getOptionToInt("panel_lights_switch5_data_off_value");
        panel_lights_switch5_data_array_offset = getOptionToInt("panel_lights_switch5_data_array_offset");
        panel_lights_switch5_data_array_size = getOptionToInt("panel_lights_switch5_data_array_size");

        panel_lights_switch6_data = getOptionToString("panel_lights_switch6_data");
        PanelLights6Data = XPLMFindDataRef(panel_lights_switch6_data.c_str());
        panel_lights_switch6_data_on_value = getOptionToInt("panel_lights_switch6_data_on_value");
        panel_lights_switch6_data_off_value = getOptionToInt("panel_lights_switch6_data_off_value");
        panel_lights_switch6_data_array_offset = getOptionToInt("panel_lights_switch6_data_array_offset");
        panel_lights_switch6_data_array_size = getOptionToInt("panel_lights_switch6_data_array_size");

        panel_lights_switch7_data = getOptionToString("panel_lights_switch7_data");
        PanelLights7Data = XPLMFindDataRef(panel_lights_switch7_data.c_str());
        panel_lights_switch7_data_on_value = getOptionToInt("panel_lights_switch7_data_on_value");
        panel_lights_switch7_data_off_value = getOptionToInt("panel_lights_switch7_data_off_value");
        panel_lights_switch7_data_array_offset = getOptionToInt("panel_lights_switch7_data_array_offset");
        panel_lights_switch7_data_array_size = getOptionToInt("panel_lights_switch7_data_array_size");

        panel_lights_switch8_data = getOptionToString("panel_lights_switch8_data");
        PanelLights8Data = XPLMFindDataRef(panel_lights_switch8_data.c_str());
        panel_lights_switch8_data_on_value = getOptionToInt("panel_lights_switch8_data_on_value");
        panel_lights_switch8_data_off_value = getOptionToInt("panel_lights_switch8_data_off_value");
        panel_lights_switch8_data_array_offset = getOptionToInt("panel_lights_switch8_data_array_offset");
        panel_lights_switch8_data_array_size = getOptionToInt("panel_lights_switch8_data_array_size");

    }

    // beacon lights switch disable - enable - remap
    readOptionAsInt("Beacon Lights Switch enable", &beaconlightswitchenable, true);

    if (beaconlightswitchenable == 2) {
        beacon_lights_switch_on = getOptionToString("beacon_lights_switch_on_cmd");
        beacon_lights_switch_off = getOptionToString("beacon_lights_switch_off_cmd");
        BeaconLightsOnCmd = XPLMFindCommand(beacon_lights_switch_on.c_str());
        BeaconLightsOffCmd = XPLMFindCommand(beacon_lights_switch_off.c_str());

        beacon_lights_switch2_on = getOptionToString("beacon_lights_switch2_on_cmd");
        beacon_lights_switch2_off = getOptionToString("beacon_lights_switch2_off_cmd");
        BeaconLights2OnCmd = XPLMFindCommand(beacon_lights_switch2_on.c_str());
        BeaconLights2OffCmd = XPLMFindCommand(beacon_lights_switch2_off.c_str());

        beacon_lights_switch3_on = getOptionToString("beacon_lights_switch3_on_cmd");
        beacon_lights_switch3_off = getOptionToString("beacon_lights_switch3_off_cmd");
        BeaconLights3OnCmd = XPLMFindCommand(beacon_lights_switch3_on.c_str());
        BeaconLights3OffCmd = XPLMFindCommand(beacon_lights_switch3_off.c_str());

        beacon_lights_switch4_on = getOptionToString("beacon_lights_switch4_on_cmd");
        beacon_lights_switch4_off = getOptionToString("beacon_lights_switch4_off_cmd");
        BeaconLights4OnCmd = XPLMFindCommand(beacon_lights_switch4_on.c_str());
        BeaconLights4OffCmd = XPLMFindCommand(beacon_lights_switch4_off.c_str());

        beacon_lights_switch5_on = getOptionToString("beacon_lights_switch5_on_cmd");
        beacon_lights_switch5_off = getOptionToString("beacon_lights_switch5_off_cmd");
        BeaconLights5OnCmd = XPLMFindCommand(beacon_lights_switch5_on.c_str());
        BeaconLights5OffCmd = XPLMFindCommand(beacon_lights_switch5_off.c_str());

        beacon_lights_switch6_on = getOptionToString("beacon_lights_switch6_on_cmd");
        beacon_lights_switch6_off = getOptionToString("beacon_lights_switch6_off_cmd");
        BeaconLights6OnCmd = XPLMFindCommand(beacon_lights_switch6_on.c_str());
        BeaconLights6OffCmd = XPLMFindCommand(beacon_lights_switch6_off.c_str());

        beacon_lights_switch7_on = getOptionToString("beacon_lights_switch7_on_cmd");
        beacon_lights_switch7_off = getOptionToString("beacon_lights_switch7_off_cmd");
        BeaconLights7OnCmd = XPLMFindCommand(beacon_lights_switch7_on.c_str());
        BeaconLights7OffCmd = XPLMFindCommand(beacon_lights_switch7_off.c_str());

        beacon_lights_switch8_on = getOptionToString("beacon_lights_switch8_on_cmd");
        beacon_lights_switch8_off = getOptionToString("beacon_lights_switch8_off_cmd");
        BeaconLights8OnCmd = XPLMFindCommand(beacon_lights_switch8_on.c_str());
        BeaconLights8OffCmd = XPLMFindCommand(beacon_lights_switch8_off.c_str());
    }

    if ((beaconlightswitchenable == 3) || (beaconlightswitchenable == 4)) {
        beacon_lights_switch_data = getOptionToString("beacon_lights_switch_data");
        BeaconLightsData = XPLMFindDataRef(beacon_lights_switch_data.c_str());
        beacon_lights_switch_data_on_value = getOptionToInt("beacon_lights_switch_data_on_value");
        beacon_lights_switch_data_off_value = getOptionToInt("beacon_lights_switch_data_off_value");

        beacon_lights_switch2_data = getOptionToString("beacon_lights_switch2_data");
        BeaconLights2Data = XPLMFindDataRef(beacon_lights_switch2_data.c_str());
        beacon_lights_switch2_data_on_value = getOptionToInt("beacon_lights_switch2_data_on_value");
        beacon_lights_switch2_data_off_value = getOptionToInt("beacon_lights_switch2_data_off_value");

        beacon_lights_switch3_data = getOptionToString("beacon_lights_switch3_data");
        BeaconLights3Data = XPLMFindDataRef(beacon_lights_switch3_data.c_str());
        beacon_lights_switch3_data_on_value = getOptionToInt("beacon_lights_switch3_data_on_value");
        beacon_lights_switch3_data_off_value = getOptionToInt("beacon_lights_switch3_data_off_value");

        beacon_lights_switch4_data = getOptionToString("beacon_lights_switch4_data");
        BeaconLights4Data = XPLMFindDataRef(beacon_lights_switch4_data.c_str());
        beacon_lights_switch4_data_on_value = getOptionToInt("beacon_lights_switch4_data_on_value");
        beacon_lights_switch4_data_off_value = getOptionToInt("beacon_lights_switch4_data_off_value");

    }


    // nav lights switch disable - enable - remap
    readOptionAsInt("Nav Lights Switch enable", &navlightswitchenable, true);

    if (navlightswitchenable == 2) {
        nav_lights_switch_on = getOptionToString("nav_lights_switch_on_cmd");
        nav_lights_switch_off = getOptionToString("nav_lights_switch_off_cmd");
        NavLightsOnCmd = XPLMFindCommand(nav_lights_switch_on.c_str());
        NavLightsOffCmd = XPLMFindCommand(nav_lights_switch_off.c_str());

        nav_lights_switch2_on = getOptionToString("nav_lights_switch2_on_cmd");
        nav_lights_switch2_off = getOptionToString("nav_lights_switch2_off_cmd");
        NavLights2OnCmd = XPLMFindCommand(nav_lights_switch2_on.c_str());
        NavLights2OffCmd = XPLMFindCommand(nav_lights_switch2_off.c_str());

        nav_lights_switch3_on = getOptionToString("nav_lights_switch3_on_cmd");
        nav_lights_switch3_off = getOptionToString("nav_lights_switch3_off_cmd");
        NavLights3OnCmd = XPLMFindCommand(nav_lights_switch3_on.c_str());
        NavLights3OffCmd = XPLMFindCommand(nav_lights_switch3_off.c_str());

        nav_lights_switch4_on = getOptionToString("nav_lights_switch4_on_cmd");
        nav_lights_switch4_off = getOptionToString("nav_lights_switch4_off_cmd");
        NavLights4OnCmd = XPLMFindCommand(nav_lights_switch4_on.c_str());
        NavLights4OffCmd = XPLMFindCommand(nav_lights_switch4_off.c_str());

        nav_lights_switch5_on = getOptionToString("nav_lights_switch5_on_cmd");
        nav_lights_switch5_off = getOptionToString("nav_lights_switch5_off_cmd");
        NavLights5OnCmd = XPLMFindCommand(nav_lights_switch5_on.c_str());
        NavLights5OffCmd = XPLMFindCommand(nav_lights_switch5_off.c_str());

        nav_lights_switch6_on = getOptionToString("nav_lights_switch6_on_cmd");
        nav_lights_switch6_off = getOptionToString("nav_lights_switch6_off_cmd");
        NavLights6OnCmd = XPLMFindCommand(nav_lights_switch6_on.c_str());
        NavLights6OffCmd = XPLMFindCommand(nav_lights_switch6_off.c_str());

        nav_lights_switch7_on = getOptionToString("nav_lights_switch7_on_cmd");
        nav_lights_switch7_off = getOptionToString("nav_lights_switch7_off_cmd");
        NavLights7OnCmd = XPLMFindCommand(nav_lights_switch7_on.c_str());
        NavLights7OffCmd = XPLMFindCommand(nav_lights_switch7_off.c_str());

        nav_lights_switch8_on = getOptionToString("nav_lights_switch8_on_cmd");
        nav_lights_switch8_off = getOptionToString("nav_lights_switch8_off_cmd");
        NavLights8OnCmd = XPLMFindCommand(nav_lights_switch8_on.c_str());
        NavLights8OffCmd = XPLMFindCommand(nav_lights_switch8_off.c_str());
    }

    if ((navlightswitchenable == 3) || (navlightswitchenable == 4)) {
        nav_lights_switch_data = getOptionToString("nav_lights_switch_data");
        NavLightsData = XPLMFindDataRef(nav_lights_switch_data.c_str());
        nav_lights_switch_data_on_value = getOptionToInt("nav_lights_switch_data_on_value");
        nav_lights_switch_data_off_value = getOptionToInt("nav_lights_switch_data_off_value");

        nav_lights_switch2_data = getOptionToString("nav_lights_switch2_data");
        NavLights2Data = XPLMFindDataRef(nav_lights_switch2_data.c_str());
        nav_lights_switch2_data_on_value = getOptionToInt("nav_lights_switch2_data_on_value");
        nav_lights_switch2_data_off_value = getOptionToInt("nav_lights_switch2_data_off_value");

        nav_lights_switch3_data = getOptionToString("nav_lights_switch3_data");
        NavLights3Data = XPLMFindDataRef(nav_lights_switch3_data.c_str());
        nav_lights_switch3_data_on_value = getOptionToInt("nav_lights_switch3_data_on_value");
        nav_lights_switch3_data_off_value = getOptionToInt("nav_lights_switch3_data_off_value");

        nav_lights_switch4_data = getOptionToString("nav_lights_switch4_data");
        NavLights4Data = XPLMFindDataRef(nav_lights_switch4_data.c_str());
        nav_lights_switch4_data_on_value = getOptionToInt("nav_lights_switch4_data_on_value");
        nav_lights_switch_data_off_value = getOptionToInt("nav_lights_switch4_data_off_value");

    }

    // strobe lights switch disable - enable - remap
    readOptionAsInt("Strobe Lights Switch enable", &strobelightswitchenable, true);

    if (strobelightswitchenable == 2) {
        strobe_lights_switch_on = getOptionToString("strobe_lights_switch_on_cmd");
        strobe_lights_switch_off = getOptionToString("strobe_lights_switch_off_cmd");
        StrobeLightsOnCmd = XPLMFindCommand(strobe_lights_switch_on.c_str());
        StrobeLightsOffCmd = XPLMFindCommand(strobe_lights_switch_off.c_str());

        strobe_lights_switch2_on = getOptionToString("strobe_lights_switch2_on_cmd");
        strobe_lights_switch2_off = getOptionToString("strobe_lights_switch2_off_cmd");
        StrobeLights2OnCmd = XPLMFindCommand(strobe_lights_switch2_on.c_str());
        StrobeLights2OffCmd = XPLMFindCommand(strobe_lights_switch2_off.c_str());

        strobe_lights_switch3_on = getOptionToString("strobe_lights_switch3_on_cmd");
        strobe_lights_switch3_off = getOptionToString("strobe_lights_switch3_off_cmd");
        StrobeLights3OnCmd = XPLMFindCommand(strobe_lights_switch3_on.c_str());
        StrobeLights3OffCmd = XPLMFindCommand(strobe_lights_switch3_off.c_str());

        strobe_lights_switch4_on = getOptionToString("strobe_lights_switch4_on_cmd");
        strobe_lights_switch4_off = getOptionToString("strobe_lights_switch4_off_cmd");
        StrobeLights4OnCmd = XPLMFindCommand(strobe_lights_switch4_on.c_str());
        StrobeLights4OffCmd = XPLMFindCommand(strobe_lights_switch4_off.c_str());

        strobe_lights_switch5_on = getOptionToString("strobe_lights_switch5_on_cmd");
        strobe_lights_switch5_off = getOptionToString("strobe_lights_switch5_off_cmd");
        StrobeLights5OnCmd = XPLMFindCommand(strobe_lights_switch5_on.c_str());
        StrobeLights5OffCmd = XPLMFindCommand(strobe_lights_switch5_off.c_str());

        strobe_lights_switch6_on = getOptionToString("strobe_lights_switch6_on_cmd");
        strobe_lights_switch6_off = getOptionToString("strobe_lights_switch6_off_cmd");
        StrobeLights6OnCmd = XPLMFindCommand(strobe_lights_switch6_on.c_str());
        StrobeLights6OffCmd = XPLMFindCommand(strobe_lights_switch6_off.c_str());

        strobe_lights_switch7_on = getOptionToString("strobe_lights_switch7_on_cmd");
        strobe_lights_switch7_off = getOptionToString("strobe_lights_switch7_off_cmd");
        StrobeLights7OnCmd = XPLMFindCommand(strobe_lights_switch7_on.c_str());
        StrobeLights7OffCmd = XPLMFindCommand(strobe_lights_switch7_off.c_str());

        strobe_lights_switch8_on = getOptionToString("strobe_lights_switch8_on_cmd");
        strobe_lights_switch8_off = getOptionToString("strobe_lights_switch8_off_cmd");
        StrobeLights8OnCmd = XPLMFindCommand(strobe_lights_switch8_on.c_str());
        StrobeLights8OffCmd = XPLMFindCommand(strobe_lights_switch8_off.c_str());
    }

    if ((strobelightswitchenable == 3) || (strobelightswitchenable == 4)) {
        strobe_lights_switch_data = getOptionToString("strobe_lights_switch_data");
        StrobeLightsData = XPLMFindDataRef(strobe_lights_switch_data.c_str());
        strobe_lights_switch_data_on_value = getOptionToInt("strobe_lights_switch_data_on_value");
        strobe_lights_switch_data_off_value = getOptionToInt("strobe_lights_switch_data_off_value");

        strobe_lights_switch2_data = getOptionToString("strobe_lights_switch2_data");
        StrobeLights2Data = XPLMFindDataRef(strobe_lights_switch2_data.c_str());
        strobe_lights_switch2_data_on_value = getOptionToInt("strobe_lights_switch2_data_on_value");
        strobe_lights_switch2_data_off_value = getOptionToInt("strobe_lights_switch2_data_off_value");

        strobe_lights_switch3_data = getOptionToString("strobe_lights_switch3_data");
        StrobeLights3Data = XPLMFindDataRef(strobe_lights_switch3_data.c_str());
        strobe_lights_switch3_data_on_value = getOptionToInt("strobe_lights_switch3_data_on_value");
        strobe_lights_switch3_data_off_value = getOptionToInt("strobe_lights_switch3_data_off_value");

        strobe_lights_switch4_data = getOptionToString("strobe_lights_switch4_data");
        StrobeLights4Data = XPLMFindDataRef(strobe_lights_switch4_data.c_str());
        strobe_lights_switch4_data_on_value = getOptionToInt("strobe_lights_switch4_data_on_value");
        strobe_lights_switch4_data_off_value = getOptionToInt("strobe_lights_switch4_data_off_value");

    }

    // taxi lights switch disable - enable - remap
    readOptionAsInt("Taxi Lights Switch enable", &taxilightswitchenable, true);

    if (taxilightswitchenable == 2) {
        taxi_lights_switch_on = getOptionToString("taxi_lights_switch_on_cmd");
        taxi_lights_switch_off = getOptionToString("taxi_lights_switch_off_cmd");
        TaxiLightsOnCmd = XPLMFindCommand(taxi_lights_switch_on.c_str());
        TaxiLightsOffCmd = XPLMFindCommand(taxi_lights_switch_off.c_str());

        taxi_lights_switch2_on = getOptionToString("taxi_lights_switch2_on_cmd");
        taxi_lights_switch2_off = getOptionToString("taxi_lights_switch2_off_cmd");
        TaxiLights2OnCmd = XPLMFindCommand(taxi_lights_switch2_on.c_str());
        TaxiLights2OffCmd = XPLMFindCommand(taxi_lights_switch2_off.c_str());

        taxi_lights_switch3_on = getOptionToString("taxi_lights_switch3_on_cmd");
        taxi_lights_switch3_off = getOptionToString("taxi_lights_switch3_off_cmd");
        TaxiLights3OnCmd = XPLMFindCommand(taxi_lights_switch3_on.c_str());
        TaxiLights3OffCmd = XPLMFindCommand(taxi_lights_switch3_off.c_str());

        taxi_lights_switch4_on = getOptionToString("taxi_lights_switch4_on_cmd");
        taxi_lights_switch4_off = getOptionToString("taxi_lights_switch4_off_cmd");
        TaxiLights4OnCmd = XPLMFindCommand(taxi_lights_switch4_on.c_str());
        TaxiLights4OffCmd = XPLMFindCommand(taxi_lights_switch4_off.c_str());

        taxi_lights_switch5_on = getOptionToString("taxi_lights_switch5_on_cmd");
        taxi_lights_switch5_off = getOptionToString("taxi_lights_switch5_off_cmd");
        TaxiLights5OnCmd = XPLMFindCommand(taxi_lights_switch5_on.c_str());
        TaxiLights5OffCmd = XPLMFindCommand(taxi_lights_switch5_off.c_str());

        taxi_lights_switch6_on = getOptionToString("taxi_lights_switch6_on_cmd");
        taxi_lights_switch6_off = getOptionToString("taxi_lights_switch6_off_cmd");
        TaxiLights6OnCmd = XPLMFindCommand(taxi_lights_switch6_on.c_str());
        TaxiLights6OffCmd = XPLMFindCommand(taxi_lights_switch6_off.c_str());

        taxi_lights_switch7_on = getOptionToString("taxi_lights_switch7_on_cmd");
        taxi_lights_switch7_off = getOptionToString("taxi_lights_switch7_off_cmd");
        TaxiLights7OnCmd = XPLMFindCommand(taxi_lights_switch7_on.c_str());
        TaxiLights7OffCmd = XPLMFindCommand(taxi_lights_switch7_off.c_str());

        taxi_lights_switch8_on = getOptionToString("taxi_lights_switch8_on_cmd");
        taxi_lights_switch8_off = getOptionToString("taxi_lights_switch8_off_cmd");
        TaxiLights8OnCmd = XPLMFindCommand(taxi_lights_switch8_on.c_str());
        TaxiLights8OffCmd = XPLMFindCommand(taxi_lights_switch8_off.c_str());
    }

    if ((taxilightswitchenable == 3) || (taxilightswitchenable == 4)) {
        taxi_lights_switch_data = getOptionToString("taxi_lights_switch_data");
        TaxiLightsData = XPLMFindDataRef(taxi_lights_switch_data.c_str());
        taxi_lights_switch_data_on_value = getOptionToInt("taxi_lights_switch_data_on_value");
        taxi_lights_switch_data_off_value = getOptionToInt("taxi_lights_switch_data_off_value");

        taxi_lights_switch2_data = getOptionToString("taxi_lights_switch2_data");
        TaxiLights2Data = XPLMFindDataRef(taxi_lights_switch2_data.c_str());
        taxi_lights_switch2_data_on_value = getOptionToInt("taxi_lights_switch2_data_on_value");
        taxi_lights_switch2_data_off_value = getOptionToInt("taxi_lights_switch2_data_off_value");

        taxi_lights_switch3_data = getOptionToString("taxi_lights_switch3_data");
        TaxiLights3Data = XPLMFindDataRef(taxi_lights_switch3_data.c_str());
        taxi_lights_switch3_data_on_value = getOptionToInt("taxi_lights_switch3_data_on_value");
        taxi_lights_switch3_data_off_value = getOptionToInt("taxi_lights_switch3_data_off_value");

        taxi_lights_switch4_data = getOptionToString("taxi_lights_switch4_data");
        TaxiLights4Data = XPLMFindDataRef(taxi_lights_switch4_data.c_str());
        taxi_lights_switch4_data_on_value = getOptionToInt("taxi_lights_switch4_data_on_value");
        taxi_lights_switch4_data_off_value = getOptionToInt("taxi_lights_switch4_data_off_value");

    }

    // landing lights switch disable - enable - remap
    readOptionAsInt("Landing Lights Switch enable", &landinglightswitchenable, true);

    if (landinglightswitchenable == 2) {
        landing_lights_switch_on = getOptionToString("landing_lights_switch_on_cmd");
        landing_lights_switch_off = getOptionToString("landing_lights_switch_off_cmd");
        LandingLightsOnCmd = XPLMFindCommand(landing_lights_switch_on.c_str());
        LandingLightsOffCmd = XPLMFindCommand(landing_lights_switch_off.c_str());

        landing_lights_switch2_on = getOptionToString("landing_lights_switch2_on_cmd");
        landing_lights_switch2_off = getOptionToString("landing_lights_switch2_off_cmd");
        LandingLights2OnCmd = XPLMFindCommand(landing_lights_switch2_on.c_str());
        LandingLights2OffCmd = XPLMFindCommand(landing_lights_switch2_off.c_str());

        landing_lights_switch3_on = getOptionToString("landing_lights_switch3_on_cmd");
        landing_lights_switch3_off = getOptionToString("landing_lights_switch3_off_cmd");
        LandingLights3OnCmd = XPLMFindCommand(landing_lights_switch3_on.c_str());
        LandingLights3OffCmd = XPLMFindCommand(landing_lights_switch3_off.c_str());

        landing_lights_switch4_on = getOptionToString("landing_lights_switch4_on_cmd");
        landing_lights_switch4_off = getOptionToString("landing_lights_switch4_off_cmd");
        LandingLights4OnCmd = XPLMFindCommand(landing_lights_switch4_on.c_str());
        LandingLights4OffCmd = XPLMFindCommand(landing_lights_switch4_off.c_str());

        landing_lights_switch5_on = getOptionToString("landing_lights_switch5_on_cmd");
        landing_lights_switch5_off = getOptionToString("landing_lights_switch5_off_cmd");
        LandingLights5OnCmd = XPLMFindCommand(landing_lights_switch5_on.c_str());
        LandingLights5OffCmd = XPLMFindCommand(landing_lights_switch5_off.c_str());

        landing_lights_switch6_on = getOptionToString("landing_lights_switch6_on_cmd");
        landing_lights_switch6_off = getOptionToString("landing_lights_switch6_off_cmd");
        LandingLights6OnCmd = XPLMFindCommand(landing_lights_switch6_on.c_str());
        LandingLights6OffCmd = XPLMFindCommand(landing_lights_switch6_off.c_str());

        landing_lights_switch7_on = getOptionToString("landing_lights_switch7_on_cmd");
        landing_lights_switch7_off = getOptionToString("landing_lights_switch7_off_cmd");
        LandingLights7OnCmd = XPLMFindCommand(landing_lights_switch7_on.c_str());
        LandingLights7OffCmd = XPLMFindCommand(landing_lights_switch7_off.c_str());

        landing_lights_switch8_on = getOptionToString("landing_lights_switch8_on_cmd");
        landing_lights_switch8_off = getOptionToString("landing_lights_switch8_off_cmd");
        LandingLights8OnCmd = XPLMFindCommand(landing_lights_switch8_on.c_str());
        LandingLights8OffCmd = XPLMFindCommand(landing_lights_switch8_off.c_str());
    }

    if ((landinglightswitchenable == 3) || (landinglightswitchenable == 4)) {
        landing_lights_switch_data = getOptionToString("landing_lights_switch_data");
        LandingLightsData = XPLMFindDataRef(landing_lights_switch_data.c_str());
        landing_lights_switch_data_on_value = getOptionToInt("landing_lights_switch_data_on_value");
        landing_lights_switch_data_off_value = getOptionToInt("landing_lights_switch_data_off_value");

        landing_lights_switch2_data = getOptionToString("landing_lights_switch2_data");
        LandingLights2Data = XPLMFindDataRef(landing_lights_switch2_data.c_str());
        landing_lights_switch2_data_on_value = getOptionToInt("landing_lights_switch2_data_on_value");
        landing_lights_switch2_data_off_value = getOptionToInt("landing_lights_switch2_data_off_value");

        landing_lights_switch3_data = getOptionToString("landing_lights_switch3_data");
        LandingLights3Data = XPLMFindDataRef(landing_lights_switch3_data.c_str());
        landing_lights_switch3_data_on_value = getOptionToInt("landing_lights_switch3_data_on_value");
        landing_lights_switch3_data_off_value = getOptionToInt("landing_lights_switch3_data_off_value");

        landing_lights_switch4_data = getOptionToString("landing_lights_switch4_data");
        LandingLights4Data = XPLMFindDataRef(landing_lights_switch4_data.c_str());
        landing_lights_switch4_data_on_value = getOptionToInt("landing_lights_switch4_data_on_value");
        landing_lights_switch4_data_off_value = getOptionToInt("landing_lights_switch4_data_off_value");

    }


    // landing lights switch disable - enable - remap
    readOptionAsInt("Landing Lights Switch enable", &landinglightswitchenable, true);


    // *******************  Radio Panel Commands   **********************************

    readOptionAsInt("Radio Freq Knob Pulse per Command", &radspeed, true);
    readOptionAsInt("Radio Number of ADF's", &numadf, true);
    readOptionAsInt("Metric Press enable", &metricpressenable, true);
    readOptionAsInt("Channel Spacing 883 enable", &channelspacing833enable);

    sprintf(radtestbuf1, "Xsaitekpanels: channelspacing833enable ==  %d \n", channelspacing833enable);
    XPLMDebugString(radtestbuf1);

    readOptionAsInt("Dme Display Dist Speed enable", &dmedistspeedenable);


    // ***************************  Upper Radio1 remaping  ***********************************
    // Radio1 Upper com1 switch - remapable
    readOptionAsInt("Radio1 Upper Com1 Switch remapable", &rad1uprcom1switchremap);
    if (rad1uprcom1switchremap == 1) {
        rad1_upper_com1_corse_up_remapable = getOptionToString("rad1_upper_com1_corse_up_cmd");
        Rad1UprCom1CrsUpRemapableCmd = XPLMFindCommand(rad1_upper_com1_corse_up_remapable.c_str());

        rad1_upper_com1_corse_dn_remapable = getOptionToString("rad1_upper_com1_corse_dn_cmd");
        Rad1UprCom1CrsDnRemapableCmd = XPLMFindCommand(rad1_upper_com1_corse_dn_remapable.c_str());

        rad1_upper_com1_fine_up_remapable = getOptionToString("rad1_upper_com1_fine_up_cmd");
        Rad1UprCom1FnUpRemapableCmd = XPLMFindCommand(rad1_upper_com1_fine_up_remapable.c_str());

        rad1_upper_com1_fine_dn_remapable = getOptionToString("rad1_upper_com1_fine_dn_cmd");
        Rad1UprCom1FnDnRemapableCmd = XPLMFindCommand(rad1_upper_com1_fine_dn_remapable.c_str());

        rad1_upper_com1_act_data_remapable = getOptionToString("rad1_upper_com1_act_data");
        Rad1UpperCom1ActRemapableData = XPLMFindDataRef(rad1_upper_com1_act_data_remapable.c_str());

        rad1_upper_com1_stby_data_remapable = getOptionToString("rad1_upper_com1_stby_data");
        Rad1UpperCom1StbyRemapableData = XPLMFindDataRef(rad1_upper_com1_stby_data_remapable.c_str());

    }

    // Radio1 Upper com1 active stanby button - remapable
    readOptionAsInt("Radio1 Upper Com1 ActStby remapable", &rad1uprcom1actstbybtnremap);
    if (rad1uprcom1actstbybtnremap == 1) {
        rad1_upper_com1_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_com1_actstby_btn_cmd");
        Rad1UprCom1ActStbyRemapableCmd = XPLMFindCommand(rad1_upper_com1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1uprcom1actstbybtnremap == 2) {
        rad1_upper_com1_actstby_btn_remapable_data = getOptionToString("rad1_upper_com1_actstby_btn_data");
        Rad1UprCom1ActStbyRemapableData = XPLMFindDataRef(rad1_upper_com1_actstby_btn_remapable_data.c_str());
        rad1_upper_com1_actstby_btn_remapable_dataf = getOptionToString("rad1_upper_com1_actstby_btn_dataf");
        Rad1UprCom1ActStbyRemapableDataf = XPLMFindDataRef(rad1_upper_com1_actstby_btn_remapable_dataf.c_str());
        rad1_upr_com1_actstby_btn_data_on_value = getOptionToInt("rad1_upr_com1_actstby_btn_data_on_value");
        rad1_upr_com1_actstby_btn_data_off_value = getOptionToInt("rad1_upr_com1_actstby_btn_data_off_value");

    }

    // Radio1 Upper com2 switch - remapable
    readOptionAsInt("Radio1 Upper Com2 Switch remapable", &rad1uprcom2switchremap);
    if (rad1uprcom2switchremap == 1) {
        rad1_upper_com2_corse_up_remapable = getOptionToString("rad1_upper_com2_corse_up_cmd");
        Rad1UprCom2CrsUpRemapableCmd = XPLMFindCommand(rad1_upper_com2_corse_up_remapable.c_str());

        rad1_upper_com2_corse_dn_remapable = getOptionToString("rad1_upper_com2_corse_dn_cmd");
        Rad1UprCom2CrsDnRemapableCmd = XPLMFindCommand(rad1_upper_com2_corse_dn_remapable.c_str());

        rad1_upper_com2_fine_up_remapable = getOptionToString("rad1_upper_com2_fine_up_cmd");
        Rad1UprCom2FnUpRemapableCmd = XPLMFindCommand(rad1_upper_com2_fine_up_remapable.c_str());

        rad1_upper_com2_fine_dn_remapable = getOptionToString("rad1_upper_com2_fine_dn_cmd");
        Rad1UprCom2FnDnRemapableCmd = XPLMFindCommand(rad1_upper_com2_fine_dn_remapable.c_str());

        rad1_upper_com2_act_data_remapable = getOptionToString("rad1_upper_com2_act_data");
        Rad1UpperCom2ActRemapableData = XPLMFindDataRef(rad1_upper_com2_act_data_remapable.c_str());

        rad1_upper_com2_stby_data_remapable = getOptionToString("rad1_upper_com2_stby_data");
        Rad1UpperCom2StbyRemapableData = XPLMFindDataRef(rad1_upper_com2_stby_data_remapable.c_str());

    }

    // Radio1 Upper com2 active stanby button - remapable
    readOptionAsInt("Radio1 Upper Com2 ActStby remapable", &rad1uprcom2actstbybtnremap);
    if (rad1uprcom2actstbybtnremap == 1) {
        rad1_upper_com2_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_com2_actstby_btn_cmd");
        Rad1UprCom2ActStbyRemapableCmd = XPLMFindCommand(rad1_upper_com2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1uprcom2actstbybtnremap == 2) {
        rad1_upper_com2_actstby_btn_remapable_data = getOptionToString("rad1_upper_com2_actstby_btn_data");
        Rad1UprCom2ActStbyRemapableData = XPLMFindDataRef(rad1_upper_com2_actstby_btn_remapable_data.c_str());
        rad1_upper_com2_actstby_btn_remapable_dataf = getOptionToString("rad1_upper_com2_actstby_btn_dataf");
        Rad1UprCom2ActStbyRemapableDataf = XPLMFindDataRef(rad1_upper_com2_actstby_btn_remapable_dataf.c_str());
        rad1_upr_com2_actstby_btn_data_on_value = getOptionToInt("rad1_upr_com2_actstby_btn_data_on_value");
        rad1_upr_com2_actstby_btn_data_off_value = getOptionToInt("rad1_upr_com2_actstby_btn_data_off_value");
    }



    // Radio1 Upper Nav1 switch - remapable
    readOptionAsInt("Radio1 Upper Nav1 Switch remapable", &rad1uprnav1switchremap);
    if (rad1uprnav1switchremap == 1) {
        rad1_upper_obs1_corse_up_remapable = getOptionToString("rad1_upper_obs1_corse_up_cmd");
        Rad1UprObs1CrsUpRemapableCmd = XPLMFindCommand(rad1_upper_obs1_corse_up_remapable.c_str());

        rad1_upper_obs1_corse_dn_remapable = getOptionToString("rad1_upper_obs1_corse_dn_cmd");
        Rad1UprObs1CrsDnRemapableCmd = XPLMFindCommand(rad1_upper_obs1_corse_dn_remapable.c_str());

        rad1_upper_obs1_fine_up_remapable = getOptionToString("rad1_upper_obs1_fine_up_cmd");
        Rad1UprObs1FnUpRemapableCmd = XPLMFindCommand(rad1_upper_obs1_fine_up_remapable.c_str());

        rad1_upper_obs1_fine_dn_remapable = getOptionToString("rad1_upper_obs1_fine_dn_cmd");
        Rad1UprObs1FnDnRemapableCmd = XPLMFindCommand(rad1_upper_obs1_fine_dn_remapable.c_str());

        rad1_upper_obs1_remapable_dataf = getOptionToString("rad1_upper_obs1_dataf");
        Rad1UpperObs1RemapableDataf = XPLMFindDataRef(rad1_upper_obs1_remapable_dataf.c_str());




        rad1_upper_nav1_corse_up_remapable = getOptionToString("rad1_upper_nav1_corse_up_cmd");
        Rad1UprNav1CrsUpRemapableCmd = XPLMFindCommand(rad1_upper_nav1_corse_up_remapable.c_str());

        rad1_upper_nav1_corse_dn_remapable = getOptionToString("rad1_upper_nav1_corse_dn_cmd");
        Rad1UprNav1CrsDnRemapableCmd = XPLMFindCommand(rad1_upper_nav1_corse_dn_remapable.c_str());

        rad1_upper_nav1_fine_up_remapable = getOptionToString("rad1_upper_nav1_fine_up_cmd");
        Rad1UprNav1FnUpRemapableCmd = XPLMFindCommand(rad1_upper_nav1_fine_up_remapable.c_str());

        rad1_upper_nav1_fine_dn_remapable = getOptionToString("rad1_upper_nav1_fine_dn_cmd");
        Rad1UprNav1FnDnRemapableCmd = XPLMFindCommand(rad1_upper_nav1_fine_dn_remapable.c_str());

        rad1_upper_nav1_act_data_remapable = getOptionToString("rad1_upper_nav1_act_data");
        Rad1UpperNav1ActRemapableData = XPLMFindDataRef(rad1_upper_nav1_act_data_remapable.c_str());

        rad1_upper_nav1_stby_data_remapable = getOptionToString("rad1_upper_nav1_stby_data");
        Rad1UpperNav1StbyRemapableData = XPLMFindDataRef(rad1_upper_nav1_stby_data_remapable.c_str());

    }

    // Radio1 Upper Nav1 active stanby button - remapable
    readOptionAsInt("Radio1 Upper Nav1 ActStby remapable", &rad1uprnav1actstbybtnremap);
    if (rad1uprnav1actstbybtnremap == 1) {
        rad1_upper_nav1_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_nav1_actstby_btn_cmd");
        Rad1UprNav1ActStbyRemapableCmd = XPLMFindCommand(rad1_upper_nav1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1uprnav1actstbybtnremap == 2) {

        rad1_upper_nav1_actstby_btn_remapable_data = getOptionToString("rad1_upper_nav1_actstby_btn_data");
        Rad1UprNav1ActStbyRemapableData = XPLMFindDataRef(rad1_upper_nav1_actstby_btn_remapable_data.c_str());
        rad1_upper_nav1_actstby_btn_remapable_dataf = getOptionToString("rad1_upper_nav1_actstby_btn_dataf");
        Rad1UprNav1ActStbyRemapableDataf = XPLMFindDataRef(rad1_upper_nav1_actstby_btn_remapable_dataf.c_str());
        rad1_upr_nav1_actstby_btn_data_on_value = getOptionToInt("rad1_upr_nav1_actstby_btn_data_on_value");
        rad1_upr_nav1_actstby_btn_data_off_value = getOptionToInt("rad1_upr_nav1_actstby_btn_data_off_value");

    }

    // Radio1 Upper Nav2 switch - remapable
    readOptionAsInt("Radio1 Upper Nav2 Switch remapable", &rad1uprnav2switchremap);
    if (rad1uprnav2switchremap == 1) {
        rad1_upper_obs2_corse_up_remapable = getOptionToString("rad1_upper_obs2_corse_up_cmd");
        Rad1UprObs2CrsUpRemapableCmd = XPLMFindCommand(rad1_upper_obs2_corse_up_remapable.c_str());

        rad1_upper_obs2_corse_dn_remapable = getOptionToString("rad1_upper_obs2_corse_dn_cmd");
        Rad1UprObs2CrsDnRemapableCmd = XPLMFindCommand(rad1_upper_obs2_corse_dn_remapable.c_str());

        rad1_upper_obs2_fine_up_remapable = getOptionToString("rad1_upper_obs2_fine_up_cmd");
        Rad1UprObs2FnUpRemapableCmd = XPLMFindCommand(rad1_upper_obs2_fine_up_remapable.c_str());

        rad1_upper_obs2_fine_dn_remapable = getOptionToString("rad1_upper_obs2_fine_dn_cmd");
        Rad1UprObs2FnDnRemapableCmd = XPLMFindCommand(rad1_upper_obs2_fine_dn_remapable.c_str());

        rad1_upper_obs2_remapable_dataf = getOptionToString("rad1_upper_obs2_dataf");
        Rad1UpperObs2RemapableDataf = XPLMFindDataRef(rad1_upper_obs2_remapable_dataf.c_str());


        rad1_upper_nav2_corse_up_remapable = getOptionToString("rad1_upper_nav2_corse_up_cmd");
        Rad1UprNav2CrsUpRemapableCmd = XPLMFindCommand(rad1_upper_nav2_corse_up_remapable.c_str());

        rad1_upper_nav2_corse_dn_remapable = getOptionToString("rad1_upper_nav2_corse_dn_cmd");
        Rad1UprNav2CrsDnRemapableCmd = XPLMFindCommand(rad1_upper_nav2_corse_dn_remapable.c_str());

        rad1_upper_nav2_fine_up_remapable = getOptionToString("rad1_upper_nav2_fine_up_cmd");
        Rad1UprNav2FnUpRemapableCmd = XPLMFindCommand(rad1_upper_nav2_fine_up_remapable.c_str());

        rad1_upper_nav2_fine_dn_remapable = getOptionToString("rad1_upper_nav2_fine_dn_cmd");
        Rad1UprNav2FnDnRemapableCmd = XPLMFindCommand(rad1_upper_nav2_fine_dn_remapable.c_str());

        rad1_upper_nav2_act_data_remapable = getOptionToString("rad1_upper_nav2_act_data");
        Rad1UpperNav2ActRemapableData = XPLMFindDataRef(rad1_upper_nav2_act_data_remapable.c_str());

        rad1_upper_nav2_stby_data_remapable = getOptionToString("rad1_upper_nav2_stby_data");
        Rad1UpperNav2StbyRemapableData = XPLMFindDataRef(rad1_upper_nav2_stby_data_remapable.c_str());

    }

    // Radio1 Upper Nav2 active stanby button - remapable
    readOptionAsInt("Radio1 Upper Nav2 ActStby remapable", &rad1uprnav2actstbybtnremap);
    if (rad1uprnav2actstbybtnremap == 1) {
        rad1_upper_nav2_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_nav2_actstby_btn_cmd");
        Rad1UprNav2ActStbyRemapableCmd = XPLMFindCommand(rad1_upper_nav2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1uprnav2actstbybtnremap == 2) {

        rad1_upper_nav2_actstby_btn_remapable_data = getOptionToString("rad1_upper_nav2_actstby_btn_data");
        Rad1UprNav2ActStbyRemapableData = XPLMFindDataRef(rad1_upper_nav2_actstby_btn_remapable_data.c_str());
        rad1_upper_nav2_actstby_btn_remapable_dataf = getOptionToString("rad1_upper_nav2_actstby_btn_dataf");
        Rad1UprNav2ActStbyRemapableDataf = XPLMFindDataRef(rad1_upper_nav2_actstby_btn_remapable_dataf.c_str());
        rad1_upr_nav2_actstby_btn_data_on_value = getOptionToInt("rad1_upr_nav2_actstby_btn_data_on_value");
        rad1_upr_nav2_actstby_btn_data_off_value = getOptionToInt("rad1_upr_nav2_actstby_btn_data_off_value");
    }


    // Radio1 Upper Adf switch - remapable
    readOptionAsInt("Radio1 Upper Adf Switch remapable", &rad1upradfswitchremap);
    if (rad1upradfswitchremap == 1) {

        rad1_upper_adf_corse_up_remapable = getOptionToString("rad1_upper_adf_corse_up_cmd");
        Rad1UprAdfCrsUpRemapableCmd = XPLMFindCommand(rad1_upper_adf_corse_up_remapable.c_str());

        rad1_upper_adf_corse_dn_remapable = getOptionToString("rad1_upper_adf_corse_dn_cmd");
        Rad1UprAdfCrsDnRemapableCmd = XPLMFindCommand(rad1_upper_adf_corse_dn_remapable.c_str());

        rad1_upper_adf_fine_up_remapable = getOptionToString("rad1_upper_adf_fine_up_cmd");
        Rad1UprAdfFnUpRemapableCmd = XPLMFindCommand(rad1_upper_adf_fine_up_remapable.c_str());

        rad1_upper_adf_fine_dn_remapable = getOptionToString("rad1_upper_adf_fine_dn_cmd");
        Rad1UprAdfFnDnRemapableCmd = XPLMFindCommand(rad1_upper_adf_fine_dn_remapable.c_str());

        rad1_upper_adf_act_data_remapable = getOptionToString("rad1_upper_adf_act_data");
        Rad1UpperAdfActRemapableData = XPLMFindDataRef(rad1_upper_adf_act_data_remapable.c_str());

        rad1_upper_adf_stby_data_remapable = getOptionToString("rad1_upper_adf_stby_data");
        Rad1UpperAdfStbyRemapableData = XPLMFindDataRef(rad1_upper_adf_stby_data_remapable.c_str());

    }

    // Radio1 Upper Adf active stanby button - remapable
    readOptionAsInt("Radio1 Upper Adf ActStby remapable", &rad1upradfactstbybtnremap);
    if (rad1upradfactstbybtnremap == 1) {
        rad1_upper_adf_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_adf_actstby_btn_cmd");
        Rad1UprAdfActStbyRemapableCmd = XPLMFindCommand(rad1_upper_adf_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1upradfactstbybtnremap == 2) {

        rad1_upper_adf_actstby_btn_remapable_data = getOptionToString("rad1_upper_adf_actstby_btn_data");
        Rad1UprAdfActStbyRemapableData = XPLMFindDataRef(rad1_upper_adf_actstby_btn_remapable_data.c_str());
        rad1_upper_adf_actstby_btn_remapable_dataf = getOptionToString("rad1_upper_adf_actstby_btn_dataf");
        Rad1UprAdfActStbyRemapableDataf = XPLMFindDataRef(rad1_upper_adf_actstby_btn_remapable_dataf.c_str());
        rad1_upr_adf_actstby_btn_data_on_value = getOptionToInt("rad1_upr_adf_actstby_btn_data_on_value");
        rad1_upr_adf_actstby_btn_data_off_value = getOptionToInt("rad1_upr_adf_actstby_btn_data_off_value");
    }


    // Radio1 Upper Dme switch - remapable
    readOptionAsInt("Radio1 Upper Dme remapable", &rad1uprdmeswitchremap);



    // Radio1 Upper Xpdr switch - remapable

    readOptionAsInt("Radio1 Upper Xpdr Switch remapable", &rad1uprxpdrswitchremap);
    if (rad1uprxpdrswitchremap == 777) {
        rad1_upper_xpdr_data_remapable = getOptionToString("rad1_upper_xpdr_data");
        Rad1UpperXpdrRemapableData = XPLMFindDataRef(rad1_upper_xpdr_data_remapable.c_str());

        rad1_upper_xpdr_mode_remapable = getOptionToString("rad1_upper_xpdr_mode");
        Rad1UpperXpdrRemapableMode = XPLMFindDataRef(rad1_upper_xpdr_mode_remapable.c_str());

        rad1_upper_xpdr_baro_std_data_remapable = getOptionToString("rad1_upper_xpdr_baro_std_data");
        Rad1UpperXpdrBaroStdRemapableData = XPLMFindDataRef(rad1_upper_xpdr_baro_std_data_remapable.c_str());

        rad1_upper_xpdr_baro_up_remapable_cmd = getOptionToString("rad1_upper_xpdr_baro_up_cmd");
        Rad1UpperXpdrBaroUpRemapableCmd = XPLMFindCommand(rad1_upper_xpdr_baro_up_remapable_cmd.c_str());

        rad1_upper_xpdr_baro_dn_remapable_cmd = getOptionToString("rad1_upper_xpdr_baro_dn_cmd");
        Rad1UpperXpdrBaroDnRemapableCmd = XPLMFindCommand(rad1_upper_xpdr_baro_dn_remapable_cmd.c_str());


    }


    // ************************  Lower Radio1 remaping  *********************************************
    // Radio1 Lower Com1 switch - remapable
    readOptionAsInt("Radio1 Lower Com1 Switch remapable", &rad1lwrcom1switchremap);
    if (rad1lwrcom1switchremap == 1) {
        rad1_lower_com1_corse_up_remapable = getOptionToString("rad1_lower_com1_corse_up_cmd");
        Rad1LowrCom1CrsUpRemapableCmd = XPLMFindCommand(rad1_lower_com1_corse_up_remapable.c_str());

        rad1_lower_com1_corse_dn_remapable = getOptionToString("rad1_lower_com1_corse_dn_cmd");
        Rad1LowrCom1CrsDnRemapableCmd = XPLMFindCommand(rad1_lower_com1_corse_dn_remapable.c_str());

        rad1_lower_com1_fine_up_remapable = getOptionToString("rad1_lower_com1_fine_up_cmd");
        Rad1LowrCom1FnUpRemapableCmd = XPLMFindCommand(rad1_lower_com1_fine_up_remapable.c_str());

        rad1_lower_com1_fine_dn_remapable = getOptionToString("rad1_lower_com1_fine_dn_cmd");
        Rad1LowrCom1FnDnRemapableCmd = XPLMFindCommand(rad1_lower_com1_fine_dn_remapable.c_str());

        rad1_lower_com1_act_data_remapable = getOptionToString("rad1_lower_com1_act_data");
        Rad1LowerCom1ActRemapableData = XPLMFindDataRef(rad1_lower_com1_act_data_remapable.c_str());

        rad1_lower_com1_stby_data_remapable = getOptionToString("rad1_lower_com1_stby_data");
        Rad1LowerCom1StbyRemapableData = XPLMFindDataRef(rad1_lower_com1_stby_data_remapable.c_str());

    }

    // Radio1 Lower Com1 active stanby button - remapable
    readOptionAsInt("Radio1 Lower Com1 ActStby remapable", &rad1lwrcom1actstbybtnremap);
    if (rad1lwrcom1actstbybtnremap == 1) {
        rad1_lower_com1_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_com1_actstby_btn_cmd");
        Rad1LowrCom1ActStbyRemapableCmd = XPLMFindCommand(rad1_lower_com1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1lwrcom1actstbybtnremap == 2) {
        rad1_lower_com1_actstby_btn_remapable_data = getOptionToString("rad1_lower_com1_actstby_btn_data");
        Rad1LowrCom1ActStbyRemapableData = XPLMFindDataRef(rad1_lower_com1_actstby_btn_remapable_data.c_str());
        rad1_lower_com1_actstby_btn_remapable_dataf = getOptionToString("rad1_lower_com1_actstby_btn_dataf");
        Rad1LowrCom1ActStbyRemapableDataf = XPLMFindDataRef(rad1_lower_com1_actstby_btn_remapable_dataf.c_str());
        rad1_lwr_com1_actstby_btn_data_on_value = getOptionToInt("rad1_lwr_com1_actstby_btn_data_on_value");
        rad1_lwr_com1_actstby_btn_data_off_value = getOptionToInt("rad1_lwr_com1_actstby_btn_data_off_value");
    }

    // Radio1 Lower Com2 switch - remapable
    readOptionAsInt("Radio1 Lower Com2 Switch remapable", &rad1lwrcom2switchremap);
    if (rad1lwrcom2switchremap == 1) {
        rad1_lower_com2_corse_up_remapable = getOptionToString("rad1_lower_com2_corse_up_cmd");
        Rad1LowrCom2CrsUpRemapableCmd = XPLMFindCommand(rad1_lower_com2_corse_up_remapable.c_str());

        rad1_lower_com2_corse_dn_remapable = getOptionToString("rad1_lower_com2_corse_dn_cmd");
        Rad1LowrCom2CrsDnRemapableCmd = XPLMFindCommand(rad1_lower_com2_corse_dn_remapable.c_str());

        rad1_lower_com2_fine_up_remapable = getOptionToString("rad1_lower_com2_fine_up_cmd");
        Rad1LowrCom2FnUpRemapableCmd = XPLMFindCommand(rad1_lower_com2_fine_up_remapable.c_str());

        rad1_lower_com2_fine_dn_remapable = getOptionToString("rad1_lower_com2_fine_dn_cmd");
        Rad1LowrCom2FnDnRemapableCmd = XPLMFindCommand(rad1_lower_com2_fine_dn_remapable.c_str());

        rad1_lower_com2_act_data_remapable = getOptionToString("rad1_lower_com2_act_data");
        Rad1LowerCom2ActRemapableData = XPLMFindDataRef(rad1_lower_com2_act_data_remapable.c_str());

        rad1_lower_com2_stby_data_remapable = getOptionToString("rad1_lower_com2_stby_data");
        Rad1LowerCom2StbyRemapableData = XPLMFindDataRef(rad1_lower_com2_stby_data_remapable.c_str());

    }

    // Radio1 Lower Com2 active stanby button - remapable
    readOptionAsInt("Radio1 Lower Com2 ActStby remapable", &rad1lwrcom2actstbybtnremap);
    if (rad1lwrcom2actstbybtnremap == 1) {
        rad1_lower_com2_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_com2_actstby_btn_cmd");
        Rad1LowrCom2ActStbyRemapableCmd = XPLMFindCommand(rad1_lower_com2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1lwrcom2actstbybtnremap == 2) {
        rad1_lower_com2_actstby_btn_remapable_data = getOptionToString("rad1_lower_com2_actstby_btn_data");
        Rad1LowrCom2ActStbyRemapableData = XPLMFindDataRef(rad1_lower_com2_actstby_btn_remapable_data.c_str());
        rad1_lower_com2_actstby_btn_remapable_dataf = getOptionToString("rad1_lower_com2_actstby_btn_dataf");
        Rad1LowrCom2ActStbyRemapableDataf = XPLMFindDataRef(rad1_lower_com2_actstby_btn_remapable_dataf.c_str());
        rad1_lwr_com2_actstby_btn_data_on_value = getOptionToInt("rad1_lwr_com2_actstby_btn_data_on_value");
        rad1_lwr_com2_actstby_btn_data_off_value = getOptionToInt("rad1_lwr_com2_actstby_btn_data_off_value");
    }

    // Radio1 Lower Nav1 switch - remapable
    readOptionAsInt("Radio1 Lower Nav1 Switch remapable", &rad1lwrnav1switchremap);
    if (rad1lwrnav1switchremap == 1) {
        rad1_lower_obs1_corse_up_remapable = getOptionToString("rad1_lower_obs1_corse_up_cmd");
        Rad1LowrObs1CrsUpRemapableCmd = XPLMFindCommand(rad1_lower_obs1_corse_up_remapable.c_str());

        rad1_lower_obs1_corse_dn_remapable = getOptionToString("rad1_lower_obs1_corse_dn_cmd");
        Rad1LowrObs1CrsDnRemapableCmd = XPLMFindCommand(rad1_lower_obs1_corse_dn_remapable.c_str());

        rad1_lower_obs1_fine_up_remapable = getOptionToString("rad1_lower_obs1_fine_up_cmd");
        Rad1LowrObs1FnUpRemapableCmd = XPLMFindCommand(rad1_lower_obs1_fine_up_remapable.c_str());

        rad1_lower_obs1_fine_dn_remapable = getOptionToString("rad1_lower_obs1_fine_dn_cmd");
        Rad1LowrObs1FnDnRemapableCmd = XPLMFindCommand(rad1_lower_obs1_fine_dn_remapable.c_str());

        rad1_lower_obs1_remapable_dataf = getOptionToString("rad1_lower_obs1_dataf");
        Rad1LowerObs1RemapableDataf = XPLMFindDataRef(rad1_lower_obs1_remapable_dataf.c_str());


        rad1_lower_nav1_corse_up_remapable = getOptionToString("rad1_lower_nav1_corse_up_cmd");
        Rad1LowrNav1CrsUpRemapableCmd = XPLMFindCommand(rad1_lower_nav1_corse_up_remapable.c_str());

        rad1_lower_nav1_corse_dn_remapable = getOptionToString("rad1_lower_nav1_corse_dn_cmd");
        Rad1LowrNav1CrsDnRemapableCmd = XPLMFindCommand(rad1_lower_nav1_corse_dn_remapable.c_str());

        rad1_lower_nav1_fine_up_remapable = getOptionToString("rad1_lower_nav1_fine_up_cmd");
        Rad1LowrNav1FnUpRemapableCmd = XPLMFindCommand(rad1_lower_nav1_fine_up_remapable.c_str());

        rad1_lower_nav1_fine_dn_remapable = getOptionToString("rad1_lower_nav1_fine_dn_cmd");
        Rad1LowrNav1FnDnRemapableCmd = XPLMFindCommand(rad1_lower_nav1_fine_dn_remapable.c_str());

        rad1_lower_nav1_act_data_remapable = getOptionToString("rad1_lower_nav1_act_data");
        Rad1LowerNav1ActRemapableData = XPLMFindDataRef(rad1_lower_nav1_act_data_remapable.c_str());

        rad1_lower_nav1_stby_data_remapable = getOptionToString("rad1_lower_nav1_stby_data");
        Rad1LowerNav1StbyRemapableData = XPLMFindDataRef(rad1_lower_nav1_stby_data_remapable.c_str());


    }

    // Radio1 Lower Nav1 active stanby button - remapable
    readOptionAsInt("Radio1 Lower Nav1 ActStby remapable", &rad1lwrnav1actstbybtnremap);
    if (rad1lwrnav1actstbybtnremap == 1) {
        rad1_lower_nav1_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_nav1_actstby_btn_cmd");
        Rad1LowrNav1ActStbyRemapableCmd = XPLMFindCommand(rad1_lower_nav1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1lwrnav1actstbybtnremap == 2) {
        rad1_lower_nav1_actstby_btn_remapable_data = getOptionToString("rad1_lower_nav1_actstby_btn_data");
        Rad1LowrNav1ActStbyRemapableData = XPLMFindDataRef(rad1_lower_nav1_actstby_btn_remapable_data.c_str());
        rad1_lower_nav1_actstby_btn_remapable_dataf = getOptionToString("rad1_lower_nav1_actstby_btn_dataf");
        Rad1LowrNav1ActStbyRemapableDataf = XPLMFindDataRef(rad1_lower_nav1_actstby_btn_remapable_dataf.c_str());
        rad1_lwr_nav1_actstby_btn_data_on_value = getOptionToInt("rad1_lwr_nav1_actstby_btn_data_on_value");
        rad1_lwr_nav1_actstby_btn_data_off_value = getOptionToInt("rad1_lwr_nav1_actstby_btn_data_off_value");
    }

    // Radio1 Lower Nav2 switch - remapable
    readOptionAsInt("Radio1 Lower Nav2 Switch remapable", &rad1lwrnav2switchremap);
    if (rad1lwrnav2switchremap == 1) {
        rad1_lower_obs2_corse_up_remapable = getOptionToString("rad1_lower_obs2_corse_up_cmd");
        Rad1LowrObs2CrsUpRemapableCmd = XPLMFindCommand(rad1_lower_obs2_corse_up_remapable.c_str());

        rad1_lower_obs2_corse_dn_remapable = getOptionToString("rad1_lower_obs2_corse_dn_cmd");
        Rad1LowrObs2CrsDnRemapableCmd = XPLMFindCommand(rad1_lower_obs2_corse_dn_remapable.c_str());

        rad1_lower_obs2_fine_up_remapable = getOptionToString("rad1_lower_obs2_fine_up_cmd");
        Rad1LowrObs2FnUpRemapableCmd = XPLMFindCommand(rad1_lower_obs2_fine_up_remapable.c_str());

        rad1_lower_obs2_fine_dn_remapable = getOptionToString("rad1_lower_obs2_fine_dn_cmd");
        Rad1LowrObs2FnDnRemapableCmd = XPLMFindCommand(rad1_lower_obs2_fine_dn_remapable.c_str());

        rad1_lower_obs2_remapable_dataf = getOptionToString("rad1_lower_obs2_dataf");
        Rad1LowerObs2RemapableDataf = XPLMFindDataRef(rad1_lower_obs2_remapable_dataf.c_str());


        rad1_lower_nav2_corse_up_remapable = getOptionToString("rad1_lower_nav2_corse_up_cmd");
        Rad1LowrNav2CrsUpRemapableCmd = XPLMFindCommand(rad1_lower_nav2_corse_up_remapable.c_str());

        rad1_lower_nav2_corse_dn_remapable = getOptionToString("rad1_lower_nav2_corse_dn_cmd");
        Rad1LowrNav2CrsDnRemapableCmd = XPLMFindCommand(rad1_lower_nav2_corse_dn_remapable.c_str());

        rad1_lower_nav2_fine_up_remapable = getOptionToString("rad1_lower_nav2_fine_up_cmd");
        Rad1LowrNav2FnUpRemapableCmd = XPLMFindCommand(rad1_lower_nav2_fine_up_remapable.c_str());

        rad1_lower_nav2_fine_dn_remapable = getOptionToString("rad1_lower_nav2_fine_dn_cmd");
        Rad1LowrNav2FnDnRemapableCmd = XPLMFindCommand(rad1_lower_nav2_fine_dn_remapable.c_str());

        rad1_lower_nav2_act_data_remapable = getOptionToString("rad1_lower_nav2_act_data");
        Rad1LowerNav2ActRemapableData = XPLMFindDataRef(rad1_lower_nav2_act_data_remapable.c_str());

        rad1_lower_nav2_stby_data_remapable = getOptionToString("rad1_lower_nav2_stby_data");
        Rad1LowerNav2StbyRemapableData = XPLMFindDataRef(rad1_lower_nav2_stby_data_remapable.c_str());

    }

    // Radio1 Lower Nav2 active stanby button - remapable
    readOptionAsInt("Radio1 Lower Nav2 ActStby remapable", &rad1lwrnav2actstbybtnremap);
    if (rad1lwrnav2actstbybtnremap == 1) {
        rad1_lower_nav2_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_nav2_actstby_btn_cmd");
        Rad1LowrNav2ActStbyRemapableCmd = XPLMFindCommand(rad1_lower_nav2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1lwrnav2actstbybtnremap == 2) {
        rad1_lower_nav2_actstby_btn_remapable_data = getOptionToString("rad1_lower_nav2_actstby_btn_data");
        Rad1LowrNav2ActStbyRemapableData = XPLMFindDataRef(rad1_lower_nav2_actstby_btn_remapable_data.c_str());
        rad1_lower_nav2_actstby_btn_remapable_dataf = getOptionToString("rad1_lower_nav2_actstby_btn_dataf");
        Rad1LowrNav2ActStbyRemapableDataf = XPLMFindDataRef(rad1_lower_nav2_actstby_btn_remapable_dataf.c_str());
        rad1_lwr_nav2_actstby_btn_data_on_value = getOptionToInt("rad1_lwr_nav2_actstby_btn_data_on_value");
        rad1_lwr_nav2_actstby_btn_data_off_value = getOptionToInt("rad1_lwr_nav2_actstby_btn_data_off_value");
    }


    // Radio1 Lower Adf switch - remapable
    readOptionAsInt("Radio1 Lower Adf Switch remapable", &rad1lwradfswitchremap);
    if (rad1lwradfswitchremap == 1) {

        rad1_lower_adf_corse_up_remapable = getOptionToString("rad1_lower_adf_corse_up_cmd");
        Rad1LowrAdfCrsUpRemapableCmd = XPLMFindCommand(rad1_lower_adf_corse_up_remapable.c_str());

        rad1_lower_adf_corse_dn_remapable = getOptionToString("rad1_lower_adf_corse_dn_cmd");
        Rad1LowrAdfCrsDnRemapableCmd = XPLMFindCommand(rad1_lower_adf_corse_dn_remapable.c_str());

        rad1_lower_adf_fine_up_remapable = getOptionToString("rad1_lower_adf_fine_up_cmd");
        Rad1LowrAdfFnUpRemapableCmd = XPLMFindCommand(rad1_lower_adf_fine_up_remapable.c_str());

        rad1_lower_adf_fine_dn_remapable = getOptionToString("rad1_lower_adf_fine_dn_cmd");
        Rad1LowrAdfFnDnRemapableCmd = XPLMFindCommand(rad1_lower_adf_fine_dn_remapable.c_str());

        rad1_lower_adf_act_data_remapable = getOptionToString("rad1_lower_adf_act_data");
        Rad1LowerAdfActRemapableData = XPLMFindDataRef(rad1_lower_adf_act_data_remapable.c_str());

        rad1_lower_adf_stby_data_remapable = getOptionToString("rad1_lower_adf_stby_data");
        Rad1LowerAdfStbyRemapableData = XPLMFindDataRef(rad1_lower_adf_stby_data_remapable.c_str());

    }

    // Radio1 Lower Adf active stanby button - remapable
    readOptionAsInt("Radio1 Lower Adf ActStby remapable", &rad1lwradfactstbybtnremap);
    if (rad1lwradfactstbybtnremap == 1) {
        rad1_lower_adf_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_adf_actstby_btn_cmd");
        Rad1LowrAdfActStbyRemapableCmd = XPLMFindCommand(rad1_lower_adf_actstby_btn_remapable_cmd.c_str());
    }
    if (rad1upradfactstbybtnremap == 2) {

        rad1_lower_adf_actstby_btn_remapable_data = getOptionToString("rad1_lower_adf_actstby_btn_data");
        Rad1UprAdfActStbyRemapableData = XPLMFindDataRef(rad1_lower_adf_actstby_btn_remapable_data.c_str());
        rad1_lower_adf_actstby_btn_remapable_dataf = getOptionToString("rad1_upper_adf_actstby_btn_dataf");
        Rad1LowrAdfActStbyRemapableDataf = XPLMFindDataRef(rad1_lower_adf_actstby_btn_remapable_dataf.c_str());
        rad1_lwr_adf_actstby_btn_data_on_value = getOptionToInt("rad1_lwr_adf_actstby_btn_data_on_value");
        rad1_lwr_adf_actstby_btn_data_off_value = getOptionToInt("rad1_lwr_adf_actstby_btn_data_off_value");
    }


    // Radio1 Lower Dme switch - remapable
    readOptionAsInt("Radio1 Lower Dme remapable", &rad1lwrdmeswitchremap);


    // Radio1 Lower Xpdr switch - remapable

    readOptionAsInt("Radio1 Lower Xpdr Switch remapable", &rad1lwrxpdrswitchremap);
    if (rad1lwrxpdrswitchremap == 777) {
        rad1_lower_xpdr_data_remapable = getOptionToString("rad1_lower_xpdr_data");
        Rad1LowerXpdrRemapableData = XPLMFindDataRef(rad1_lower_xpdr_data_remapable.c_str());

        rad1_lower_xpdr_mode_remapable = getOptionToString("rad1_lower_xpdr_mode");
        Rad1LowerXpdrRemapableMode = XPLMFindDataRef(rad1_lower_xpdr_mode_remapable.c_str());

        rad1_lower_xpdr_baro_std_data_remapable = getOptionToString("rad1_lower_xpdr_baro_std_data");
        Rad1LowerXpdrBaroStdRemapableData = XPLMFindDataRef(rad1_lower_xpdr_baro_std_data_remapable.c_str());

        rad1_lower_xpdr_baro_up_remapable_cmd = getOptionToString("rad1_lower_xpdr_baro_up_cmd");
        Rad1LowrXpdrBaroUpRemapableCmd = XPLMFindCommand(rad1_lower_xpdr_baro_up_remapable_cmd.c_str());

        rad1_lower_xpdr_baro_dn_remapable_cmd = getOptionToString("rad1_lower_xpdr_baro_dn_cmd");
        Rad1LowrXpdrBaroDnRemapableCmd = XPLMFindCommand(rad1_lower_xpdr_baro_dn_remapable_cmd.c_str());

    }



    // **************************  Upper Radio2 remaping  ******************************************
   // Radio2 Upper Com1 switch - remapable
    readOptionAsInt("Radio2 Upper Com1 Switch remapable", &rad2uprcom1switchremap);
    if (rad2uprcom1switchremap == 1) {
        rad2_upper_com1_corse_up_remapable = getOptionToString("rad2_upper_com1_corse_up_cmd");
        Rad2UprCom1CrsUpRemapableCmd = XPLMFindCommand(rad2_upper_com1_corse_up_remapable.c_str());

        rad2_upper_com1_corse_dn_remapable = getOptionToString("rad2_upper_com1_corse_dn_cmd");
        Rad2UprCom1CrsDnRemapableCmd = XPLMFindCommand(rad2_upper_com1_corse_dn_remapable.c_str());

        rad2_upper_com1_fine_up_remapable = getOptionToString("rad2_upper_com1_fine_up_cmd");
        Rad2UprCom1FnUpRemapableCmd = XPLMFindCommand(rad2_upper_com1_fine_up_remapable.c_str());

        rad2_upper_com1_fine_dn_remapable = getOptionToString("rad2_upper_com1_fine_dn_cmd");
        Rad2UprCom1FnDnRemapableCmd = XPLMFindCommand(rad2_upper_com1_fine_dn_remapable.c_str());

        rad2_upper_com1_act_data_remapable = getOptionToString("rad2_upper_com1_act_data");
        Rad2UpperCom1ActRemapableData = XPLMFindDataRef(rad2_upper_com1_act_data_remapable.c_str());

        rad2_upper_com1_stby_data_remapable = getOptionToString("rad2_upper_com1_stby_data");
        Rad2UpperCom1StbyRemapableData = XPLMFindDataRef(rad2_upper_com1_stby_data_remapable.c_str());

    }

    // Radio2 Upper Com1 active stanby button - remapable
    readOptionAsInt("Radio2 Upper Com1 ActStby remapable", &rad2uprcom1actstbybtnremap);
    if (rad2uprcom1actstbybtnremap == 1) {
        rad2_upper_com1_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_com1_actstby_btn_cmd");
        Rad2UprCom1ActStbyRemapableCmd = XPLMFindCommand(rad2_upper_com1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2uprcom1actstbybtnremap == 2) {
        rad2_upper_com1_actstby_btn_remapable_data = getOptionToString("rad2_upper_com1_actstby_btn_data");
        Rad2UprCom1ActStbyRemapableData = XPLMFindDataRef(rad2_upper_com1_actstby_btn_remapable_data.c_str());
        rad2_upper_com1_actstby_btn_remapable_dataf = getOptionToString("rad2_upper_com1_actstby_btn_dataf");
        Rad2UprCom1ActStbyRemapableDataf = XPLMFindDataRef(rad2_upper_com1_actstby_btn_remapable_dataf.c_str());
        rad2_upr_com1_actstby_btn_data_on_value = getOptionToInt("rad2_upr_com1_actstby_btn_data_on_value");
        rad2_upr_com1_actstby_btn_data_off_value = getOptionToInt("rad2_upr_com1_actstby_btn_data_off_value");
    }

    // Radio2 Upper Com2 switch - remapable
    readOptionAsInt("Radio2 Upper Com2 Switch remapable", &rad2uprcom2switchremap);
    if (rad2uprcom2switchremap == 1) {
        rad2_upper_com2_corse_up_remapable = getOptionToString("rad2_upper_com2_corse_up_cmd");
        Rad2UprCom2CrsUpRemapableCmd = XPLMFindCommand(rad2_upper_com2_corse_up_remapable.c_str());

        rad2_upper_com2_corse_dn_remapable = getOptionToString("rad2_upper_com2_corse_dn_cmd");
        Rad2UprCom2CrsDnRemapableCmd = XPLMFindCommand(rad2_upper_com2_corse_dn_remapable.c_str());

        rad2_upper_com2_fine_up_remapable = getOptionToString("rad2_upper_com2_fine_up_cmd");
        Rad2UprCom2FnUpRemapableCmd = XPLMFindCommand(rad2_upper_com2_fine_up_remapable.c_str());

        rad2_upper_com2_fine_dn_remapable = getOptionToString("rad2_upper_com2_fine_dn_cmd");
        Rad2UprCom2FnDnRemapableCmd = XPLMFindCommand(rad2_upper_com2_fine_dn_remapable.c_str());

        rad2_upper_com2_act_data_remapable = getOptionToString("rad2_upper_com2_act_data");
        Rad2UpperCom2ActRemapableData = XPLMFindDataRef(rad2_upper_com2_act_data_remapable.c_str());

        rad2_upper_com2_stby_data_remapable = getOptionToString("rad2_upper_com2_stby_data");
        Rad2UpperCom2StbyRemapableData = XPLMFindDataRef(rad2_upper_com2_stby_data_remapable.c_str());

    }

    // Radio2 Upper Com2 active stanby button - remapable
    readOptionAsInt("Radio2 Upper Com2 ActStby remapable", &rad2uprcom2actstbybtnremap);
    if (rad2uprcom2actstbybtnremap == 1) {
        rad2_upper_com2_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_com2_actstby_btn_cmd");
        Rad2UprCom2ActStbyRemapableCmd = XPLMFindCommand(rad2_upper_com2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2uprcom2actstbybtnremap == 2) {
        rad2_upper_com2_actstby_btn_remapable_data = getOptionToString("rad2_upper_com2_actstby_btn_data");
        Rad2UprCom2ActStbyRemapableData = XPLMFindDataRef(rad2_upper_com2_actstby_btn_remapable_data.c_str());
        rad2_upper_com2_actstby_btn_remapable_dataf = getOptionToString("rad2_upper_com2_actstby_btn_dataf");
        Rad2UprCom2ActStbyRemapableDataf = XPLMFindDataRef(rad2_upper_com2_actstby_btn_remapable_dataf.c_str());
        rad2_upr_com2_actstby_btn_data_on_value = getOptionToInt("rad2_upr_com2_actstby_btn_data_on_value");
        rad2_upr_com2_actstby_btn_data_off_value = getOptionToInt("rad2_upr_com2_actstby_btn_data_off_value");
    }

    // Radio2 Upper Nav1 switch - remapable
    readOptionAsInt("Radio2 Upper Nav1 Switch remapable", &rad2uprnav1switchremap);
    if (rad2uprnav1switchremap == 1) {
        rad2_upper_obs1_corse_up_remapable = getOptionToString("rad2_upper_obs1_corse_up_cmd");
        Rad2UprObs1CrsUpRemapableCmd = XPLMFindCommand(rad2_upper_obs1_corse_up_remapable.c_str());

        rad2_upper_obs1_corse_dn_remapable = getOptionToString("rad2_upper_obs1_corse_dn_cmd");
        Rad2UprObs1CrsDnRemapableCmd = XPLMFindCommand(rad2_upper_obs1_corse_dn_remapable.c_str());

        rad2_upper_obs1_fine_up_remapable = getOptionToString("rad2_upper_obs1_fine_up_cmd");
        Rad2UprObs1FnUpRemapableCmd = XPLMFindCommand(rad2_upper_obs1_fine_up_remapable.c_str());

        rad2_upper_obs1_fine_dn_remapable = getOptionToString("rad2_upper_obs1_fine_dn_cmd");
        Rad2UprObs1FnDnRemapableCmd = XPLMFindCommand(rad2_upper_obs1_fine_dn_remapable.c_str());

        rad2_upper_obs1_remapable_dataf = getOptionToString("rad2_upper_obs1_dataf");
        Rad2UpperObs1RemapableDataf = XPLMFindDataRef(rad2_upper_obs1_remapable_dataf.c_str());


        rad2_upper_nav1_corse_up_remapable = getOptionToString("rad2_upper_nav1_corse_up_cmd");
        Rad2UprNav1CrsUpRemapableCmd = XPLMFindCommand(rad2_upper_nav1_corse_up_remapable.c_str());

        rad2_upper_nav1_corse_dn_remapable = getOptionToString("rad2_upper_nav1_corse_dn_cmd");
        Rad2UprNav1CrsDnRemapableCmd = XPLMFindCommand(rad2_upper_nav1_corse_dn_remapable.c_str());

        rad2_upper_nav1_fine_up_remapable = getOptionToString("rad2_upper_nav1_fine_up_cmd");
        Rad2UprNav1FnUpRemapableCmd = XPLMFindCommand(rad2_upper_nav1_fine_up_remapable.c_str());

        rad2_upper_nav1_fine_dn_remapable = getOptionToString("rad2_upper_nav1_fine_dn_cmd");
        Rad2UprNav1FnDnRemapableCmd = XPLMFindCommand(rad2_upper_nav1_fine_dn_remapable.c_str());

        rad2_upper_nav1_act_data_remapable = getOptionToString("rad2_upper_nav1_act_data");
        Rad2UpperNav1ActRemapableData = XPLMFindDataRef(rad2_upper_nav1_act_data_remapable.c_str());

        rad2_upper_nav1_stby_data_remapable = getOptionToString("rad2_upper_nav1_stby_data");
        Rad2UpperNav1StbyRemapableData = XPLMFindDataRef(rad2_upper_nav1_stby_data_remapable.c_str());

    }

    // Radio2 Upper Nav1 active stanby button - remapable
    readOptionAsInt("Radio2 Upper Nav1 ActStby remapable", &rad2uprnav1actstbybtnremap);
    if (rad2uprnav1actstbybtnremap == 1) {
        rad2_upper_nav1_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_nav1_actstby_btn_cmd");
        Rad2UprNav1ActStbyRemapableCmd = XPLMFindCommand(rad2_upper_nav1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2uprnav1actstbybtnremap == 2) {
        rad2_upper_nav1_actstby_btn_remapable_data = getOptionToString("rad2_upper_nav1_actstby_btn_data");
        Rad2UprNav1ActStbyRemapableData = XPLMFindDataRef(rad2_upper_nav1_actstby_btn_remapable_data.c_str());
        rad2_upper_nav1_actstby_btn_remapable_dataf = getOptionToString("rad2_upper_nav1_actstby_btn_dataf");
        Rad2UprNav1ActStbyRemapableDataf = XPLMFindDataRef(rad2_upper_nav1_actstby_btn_remapable_dataf.c_str());
        rad2_upr_nav1_actstby_btn_data_on_value = getOptionToInt("rad2_upr_nav1_actstby_btn_data_on_value");
        rad2_upr_nav1_actstby_btn_data_off_value = getOptionToInt("rad2_upr_nav1_actstby_btn_data_off_value");
    }

    // Radio2 Upper Nav2 switch - remapable
    readOptionAsInt("Radio2 Upper Nav2 Switch remapable", &rad2uprnav2switchremap);
    if (rad2uprnav2switchremap == 1) {
        rad2_upper_obs2_corse_up_remapable = getOptionToString("rad2_upper_obs2_corse_up_cmd");
        Rad2UprObs2CrsUpRemapableCmd = XPLMFindCommand(rad2_upper_obs2_corse_up_remapable.c_str());

        rad2_upper_obs2_corse_dn_remapable = getOptionToString("rad2_upper_obs2_corse_dn_cmd");
        Rad2UprObs2CrsDnRemapableCmd = XPLMFindCommand(rad2_upper_obs2_corse_dn_remapable.c_str());

        rad2_upper_obs2_fine_up_remapable = getOptionToString("rad2_upper_obs2_fine_up_cmd");
        Rad2UprObs2FnUpRemapableCmd = XPLMFindCommand(rad2_upper_obs2_fine_up_remapable.c_str());

        rad2_upper_obs2_fine_dn_remapable = getOptionToString("rad2_upper_obs2_fine_dn_cmd");
        Rad2UprObs2FnDnRemapableCmd = XPLMFindCommand(rad2_upper_obs2_fine_dn_remapable.c_str());

        rad2_upper_obs2_remapable_dataf = getOptionToString("rad2_upper_obs2_dataf");
        Rad2UpperObs2RemapableDataf = XPLMFindDataRef(rad2_upper_obs2_remapable_dataf.c_str());


        rad2_upper_nav2_corse_up_remapable = getOptionToString("rad2_upper_nav2_corse_up_cmd");
        Rad2UprNav2CrsUpRemapableCmd = XPLMFindCommand(rad2_upper_nav2_corse_up_remapable.c_str());

        rad2_upper_nav2_corse_dn_remapable = getOptionToString("rad2_upper_nav2_corse_dn_cmd");
        Rad2UprNav2CrsDnRemapableCmd = XPLMFindCommand(rad2_upper_nav2_corse_dn_remapable.c_str());

        rad2_upper_nav2_fine_up_remapable = getOptionToString("rad2_upper_nav2_fine_up_cmd");
        Rad2UprNav2FnUpRemapableCmd = XPLMFindCommand(rad2_upper_nav2_fine_up_remapable.c_str());

        rad2_upper_nav2_fine_dn_remapable = getOptionToString("rad2_upper_nav2_fine_dn_cmd");
        Rad2UprNav2FnDnRemapableCmd = XPLMFindCommand(rad2_upper_nav2_fine_dn_remapable.c_str());

        rad2_upper_nav2_act_data_remapable = getOptionToString("rad2_upper_nav2_act_data");
        Rad2UpperNav2ActRemapableData = XPLMFindDataRef(rad2_upper_nav2_act_data_remapable.c_str());

        rad2_upper_nav2_stby_data_remapable = getOptionToString("rad2_upper_nav2_stby_data");
        Rad2UpperNav2StbyRemapableData = XPLMFindDataRef(rad2_upper_nav2_stby_data_remapable.c_str());

    }

    // Radio2 Upper Nav2 active stanby button - remapable
    readOptionAsInt("Radio2 Upper Nav2 ActStby remapable", &rad2uprnav2actstbybtnremap);
    if (rad2uprnav2actstbybtnremap == 1) {
        rad2_upper_nav2_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_nav2_actstby_btn_cmd");
        Rad2UprNav2ActStbyRemapableCmd = XPLMFindCommand(rad2_upper_nav2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2uprnav2actstbybtnremap == 2) {
        rad2_upper_nav2_actstby_btn_remapable_data = getOptionToString("rad2_upper_nav2_actstby_btn_data");
        Rad2UprNav2ActStbyRemapableData = XPLMFindDataRef(rad2_upper_nav2_actstby_btn_remapable_data.c_str());
        rad2_upper_nav2_actstby_btn_remapable_dataf = getOptionToString("rad2_upper_nav2_actstby_btn_dataf");
        Rad2UprNav2ActStbyRemapableDataf = XPLMFindDataRef(rad2_upper_nav2_actstby_btn_remapable_dataf.c_str());
        rad2_upr_nav2_actstby_btn_data_on_value = getOptionToInt("rad2_upr_nav2_actstby_btn_data_on_value");
        rad2_upr_nav2_actstby_btn_data_off_value = getOptionToInt("rad2_upr_nav2_actstby_btn_data_off_value");
    }


    // Radio2 Upper Adf switch - remapable
    readOptionAsInt("Radio2 Upper Adf Switch remapable", &rad2upradfswitchremap);
    if (rad2upradfswitchremap == 1) {

        rad2_upper_adf_corse_up_remapable = getOptionToString("rad2_upper_adf_corse_up_cmd");
        Rad2UprAdfCrsUpRemapableCmd = XPLMFindCommand(rad2_upper_adf_corse_up_remapable.c_str());

        rad2_upper_adf_corse_dn_remapable = getOptionToString("rad2_upper_adf_corse_dn_cmd");
        Rad2UprAdfCrsDnRemapableCmd = XPLMFindCommand(rad2_upper_adf_corse_dn_remapable.c_str());

        rad2_upper_adf_fine_up_remapable = getOptionToString("rad2_upper_adf_fine_up_cmd");
        Rad2UprAdfFnUpRemapableCmd = XPLMFindCommand(rad2_upper_adf_fine_up_remapable.c_str());

        rad2_upper_adf_fine_dn_remapable = getOptionToString("rad2_upper_adf_fine_dn_cmd");
        Rad2UprAdfFnDnRemapableCmd = XPLMFindCommand(rad2_upper_adf_fine_dn_remapable.c_str());

        rad2_upper_adf_act_data_remapable = getOptionToString("rad2_upper_adf_act_data");
        Rad2UpperAdfActRemapableData = XPLMFindDataRef(rad2_upper_adf_act_data_remapable.c_str());

        rad2_upper_adf_stby_data_remapable = getOptionToString("rad2_upper_adf_stby_data");
        Rad2UpperAdfStbyRemapableData = XPLMFindDataRef(rad2_upper_adf_stby_data_remapable.c_str());

    }

    // Radio2 Upper Adf active stanby button - remapable
    readOptionAsInt("Radio2 Upper Adf ActStby remapable", &rad2upradfactstbybtnremap);
    if (rad2upradfactstbybtnremap == 1) {
        rad2_upper_adf_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_adf_actstby_btn_cmd");
        Rad2UprAdfActStbyRemapableCmd = XPLMFindCommand(rad2_upper_adf_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2upradfactstbybtnremap == 2) {

        rad2_upper_adf_actstby_btn_remapable_data = getOptionToString("rad2_upper_adf_actstby_btn_data");
        Rad2UprAdfActStbyRemapableData = XPLMFindDataRef(rad2_upper_adf_actstby_btn_remapable_data.c_str());
        rad2_upper_adf_actstby_btn_remapable_dataf = getOptionToString("rad2_upper_adf_actstby_btn_dataf");
        Rad2UprAdfActStbyRemapableDataf = XPLMFindDataRef(rad2_upper_adf_actstby_btn_remapable_dataf.c_str());
        rad2_upr_adf_actstby_btn_data_on_value = getOptionToInt("rad2_upr_adf_actstby_btn_data_on_value");
        rad2_upr_adf_actstby_btn_data_off_value = getOptionToInt("rad2_upr_adf_actstby_btn_data_off_value");
    }


    // Radio2 Upper Dme switch - remapable
    readOptionAsInt("Radio2 Upper Dme remapable", &rad2uprdmeswitchremap);


    // Radio2 Upper Xpdr switch - remapable

    readOptionAsInt("Radio2 Upper Xpdr Switch remapable", &rad2uprxpdrswitchremap);
    if (rad2uprxpdrswitchremap == 777) {
        rad2_upper_xpdr_data_remapable = getOptionToString("rad2_upper_xpdr_data");
        Rad2UpperXpdrRemapableData = XPLMFindDataRef(rad2_upper_xpdr_data_remapable.c_str());

        rad2_upper_xpdr_mode_remapable = getOptionToString("rad2_upper_xpdr_mode");
        Rad2UpperXpdrRemapableMode = XPLMFindDataRef(rad2_upper_xpdr_mode_remapable.c_str());

        rad2_upper_xpdr_baro_std_data_remapable = getOptionToString("rad2_upper_xpdr_baro_std_data");
        Rad2UpperXpdrBaroStdRemapableData = XPLMFindDataRef(rad2_upper_xpdr_baro_std_data_remapable.c_str());

        rad2_upper_xpdr_baro_up_remapable_cmd = getOptionToString("rad2_upper_xpdr_baro_up_cmd");
        Rad2UpperXpdrBaroUpRemapableCmd = XPLMFindCommand(rad2_upper_xpdr_baro_up_remapable_cmd.c_str());

        rad2_upper_xpdr_baro_dn_remapable_cmd = getOptionToString("rad2_upper_xpdr_baro_dn_cmd");
        Rad2UpperXpdrBaroDnRemapableCmd = XPLMFindCommand(rad2_upper_xpdr_baro_dn_remapable_cmd.c_str());


    }




    //  *****************************  Lower Radio2 remaping  **************************************
    // Radio2 Lower Com1 switch - remapable
    readOptionAsInt("Radio2 Lower Com1 Switch remapable", &rad2lwrcom1switchremap);
    if (rad2lwrcom1switchremap == 1) {
        rad2_lower_com1_corse_up_remapable = getOptionToString("rad2_lower_com1_corse_up_cmd");
        Rad2LowrCom1CrsUpRemapableCmd = XPLMFindCommand(rad2_lower_com1_corse_up_remapable.c_str());

        rad2_lower_com1_corse_dn_remapable = getOptionToString("rad2_lower_com1_corse_dn_cmd");
        Rad2LowrCom1CrsDnRemapableCmd = XPLMFindCommand(rad2_lower_com1_corse_dn_remapable.c_str());

        rad2_lower_com1_fine_up_remapable = getOptionToString("rad2_lower_com1_fine_up_cmd");
        Rad2LowrCom1FnUpRemapableCmd = XPLMFindCommand(rad2_lower_com1_fine_up_remapable.c_str());

        rad2_lower_com1_fine_dn_remapable = getOptionToString("rad2_lower_com1_fine_dn_cmd");
        Rad2LowrCom1FnDnRemapableCmd = XPLMFindCommand(rad2_lower_com1_fine_dn_remapable.c_str());

        rad2_lower_com1_act_data_remapable = getOptionToString("rad2_lower_com1_act_data");
        Rad2LowerCom1ActRemapableData = XPLMFindDataRef(rad2_lower_com1_act_data_remapable.c_str());

        rad2_lower_com1_stby_data_remapable = getOptionToString("rad2_lower_com1_stby_data");
        Rad2LowerCom1StbyRemapableData = XPLMFindDataRef(rad2_lower_com1_stby_data_remapable.c_str());

    }

    // Radio2 Lower Com1 active stanby button - remapable
    readOptionAsInt("Radio2 Lower Com1 ActStby remapable", &rad2lwrcom1actstbybtnremap);
    if (rad2lwrcom1actstbybtnremap == 1) {
        rad2_lower_com1_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_com1_actstby_btn_cmd");
        Rad2LowrCom1ActStbyRemapableCmd = XPLMFindCommand(rad2_lower_com1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2lwrcom1actstbybtnremap == 2) {
        rad2_lower_com1_actstby_btn_remapable_data = getOptionToString("rad2_lower_com1_actstby_btn_data");
        Rad2LowrCom1ActStbyRemapableData = XPLMFindDataRef(rad2_lower_com1_actstby_btn_remapable_data.c_str());
        rad2_lower_com1_actstby_btn_remapable_dataf = getOptionToString("rad2_lower_com1_actstby_btn_dataf");
        Rad2LowrCom1ActStbyRemapableDataf = XPLMFindDataRef(rad2_lower_com1_actstby_btn_remapable_dataf.c_str());
        rad2_lwr_com1_actstby_btn_data_on_value = getOptionToInt("rad2_lwr_com1_actstby_btn_data_on_value");
        rad2_lwr_com1_actstby_btn_data_off_value = getOptionToInt("rad2_lwr_com1_actstby_btn_data_off_value");
    }

    // Radio2 Lower Com2 switch - remapable
    readOptionAsInt("Radio2 Lower Com2 Switch remapable", &rad2lwrcom2switchremap);
    if (rad2lwrcom2switchremap == 1) {
        rad2_lower_com2_corse_up_remapable = getOptionToString("rad2_lower_com2_corse_up_cmd");
        Rad2LowrCom2CrsUpRemapableCmd = XPLMFindCommand(rad2_lower_com2_corse_up_remapable.c_str());

        rad2_lower_com2_corse_dn_remapable = getOptionToString("rad2_lower_com2_corse_dn_cmd");
        Rad2LowrCom2CrsDnRemapableCmd = XPLMFindCommand(rad2_lower_com2_corse_dn_remapable.c_str());

        rad2_lower_com2_fine_up_remapable = getOptionToString("rad2_lower_com2_fine_up_cmd");
        Rad2LowrCom2FnUpRemapableCmd = XPLMFindCommand(rad2_lower_com2_fine_up_remapable.c_str());

        rad2_lower_com2_fine_dn_remapable = getOptionToString("rad2_lower_com2_fine_dn_cmd");
        Rad2LowrCom2FnDnRemapableCmd = XPLMFindCommand(rad2_lower_com2_fine_dn_remapable.c_str());

        rad2_lower_com2_act_data_remapable = getOptionToString("rad2_lower_com2_act_data");
        Rad2LowerCom2ActRemapableData = XPLMFindDataRef(rad2_lower_com2_act_data_remapable.c_str());

        rad2_lower_com2_stby_data_remapable = getOptionToString("rad2_lower_com2_stby_data");
        Rad2LowerCom2StbyRemapableData = XPLMFindDataRef(rad2_lower_com2_stby_data_remapable.c_str());

    }

    // Radio2 Lower Com2 active stanby button - remapable
    readOptionAsInt("Radio2 Lower Com2 ActStby remapable", &rad2lwrcom2actstbybtnremap);
    if (rad2lwrcom2actstbybtnremap == 1) {
        rad2_lower_com2_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_com2_actstby_btn_cmd");
        Rad2LowrCom2ActStbyRemapableCmd = XPLMFindCommand(rad2_lower_com2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2lwrcom2actstbybtnremap == 2) {
        rad2_lower_com2_actstby_btn_remapable_data = getOptionToString("rad2_lower_com2_actstby_btn_data");
        Rad2LowrCom2ActStbyRemapableData = XPLMFindDataRef(rad2_lower_com2_actstby_btn_remapable_data.c_str());
        rad2_lower_com2_actstby_btn_remapable_dataf = getOptionToString("rad2_lower_com2_actstby_btn_dataf");
        Rad2LowrCom2ActStbyRemapableDataf = XPLMFindDataRef(rad2_lower_com2_actstby_btn_remapable_dataf.c_str());
        rad2_lwr_com2_actstby_btn_data_on_value = getOptionToInt("rad2_lwr_com2_actstby_btn_data_on_value");
        rad2_lwr_com2_actstby_btn_data_off_value = getOptionToInt("rad2_lwr_com2_actstby_btn_data_off_value");
    }

    // Radio2 Lower Nav1 switch - remapable
    readOptionAsInt("Radio2 Lower Nav1 Switch remapable", &rad2lwrnav1switchremap);
    if (rad2lwrnav1switchremap == 1) {
        rad2_lower_obs1_corse_up_remapable = getOptionToString("rad2_lower_obs1_corse_up_cmd");
        Rad2LowrObs1CrsUpRemapableCmd = XPLMFindCommand(rad2_lower_obs1_corse_up_remapable.c_str());

        rad2_lower_obs1_corse_dn_remapable = getOptionToString("rad2_lower_obs1_corse_dn_cmd");
        Rad2LowrObs1CrsDnRemapableCmd = XPLMFindCommand(rad2_lower_obs1_corse_dn_remapable.c_str());

        rad2_lower_obs1_fine_up_remapable = getOptionToString("rad2_lower_obs1_fine_up_cmd");
        Rad2LowrObs1FnUpRemapableCmd = XPLMFindCommand(rad2_lower_obs1_fine_up_remapable.c_str());

        rad2_lower_obs1_fine_dn_remapable = getOptionToString("rad2_lower_obs1_fine_dn_cmd");
        Rad2LowrObs1FnDnRemapableCmd = XPLMFindCommand(rad2_lower_obs1_fine_dn_remapable.c_str());

        rad2_lower_obs1_remapable_dataf = getOptionToString("rad2_lower_obs1_dataf");
        Rad2LowerObs1RemapableDataf = XPLMFindDataRef(rad2_lower_obs1_remapable_dataf.c_str());


        rad2_lower_nav1_corse_up_remapable = getOptionToString("rad2_lower_nav1_corse_up_cmd");
        Rad2LowrNav1CrsUpRemapableCmd = XPLMFindCommand(rad2_lower_nav1_corse_up_remapable.c_str());

        rad2_lower_nav1_corse_dn_remapable = getOptionToString("rad2_lower_nav1_corse_dn_cmd");
        Rad2LowrNav1CrsDnRemapableCmd = XPLMFindCommand(rad2_lower_nav1_corse_dn_remapable.c_str());

        rad2_lower_nav1_fine_up_remapable = getOptionToString("rad2_lower_nav1_fine_up_cmd");
        Rad2LowrNav1FnUpRemapableCmd = XPLMFindCommand(rad2_lower_nav1_fine_up_remapable.c_str());

        rad2_lower_nav1_fine_dn_remapable = getOptionToString("rad2_lower_nav1_fine_dn_cmd");
        Rad2LowrNav1FnDnRemapableCmd = XPLMFindCommand(rad2_lower_nav1_fine_dn_remapable.c_str());

        rad2_lower_nav1_act_data_remapable = getOptionToString("rad2_lower_nav1_act_data");
        Rad2LowerNav1ActRemapableData = XPLMFindDataRef(rad2_lower_nav1_act_data_remapable.c_str());

        rad2_lower_nav1_stby_data_remapable = getOptionToString("rad2_lower_nav1_stby_data");
        Rad2LowerNav1StbyRemapableData = XPLMFindDataRef(rad2_lower_nav1_stby_data_remapable.c_str());

    }

    // Radio2 Lower Nav1 active stanby button - remapable
    readOptionAsInt("Radio2 Lower Nav1 ActStby remapable", &rad2lwrnav1actstbybtnremap);
    if (rad2lwrnav1actstbybtnremap == 1) {
        rad2_lower_nav1_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_nav1_actstby_btn_cmd");
        Rad2LowrNav1ActStbyRemapableCmd = XPLMFindCommand(rad2_lower_nav1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2lwrnav1actstbybtnremap == 2) {
        rad2_lower_nav1_actstby_btn_remapable_data = getOptionToString("rad2_lower_nav1_actstby_btn_data");
        Rad2LowrNav1ActStbyRemapableData = XPLMFindDataRef(rad2_lower_nav1_actstby_btn_remapable_data.c_str());
        rad2_lower_nav1_actstby_btn_remapable_dataf = getOptionToString("rad2_lower_nav1_actstby_btn_dataf");
        Rad2LowrNav1ActStbyRemapableDataf = XPLMFindDataRef(rad2_lower_nav1_actstby_btn_remapable_dataf.c_str());
        rad2_lwr_nav1_actstby_btn_data_on_value = getOptionToInt("rad2_lwr_nav1_actstby_btn_data_on_value");
        rad2_lwr_nav1_actstby_btn_data_off_value = getOptionToInt("rad2_lwr_nav1_actstby_btn_data_off_value");
    }

    // Radio2 Lower Nav2 switch - remapable
    readOptionAsInt("Radio2 Lower Nav2 Switch remapable", &rad2lwrnav2switchremap);
    if (rad2lwrnav2switchremap == 1) {
        rad2_lower_obs2_corse_up_remapable = getOptionToString("rad2_lower_obs2_corse_up_cmd");
        Rad2LowrObs2CrsUpRemapableCmd = XPLMFindCommand(rad2_lower_obs2_corse_up_remapable.c_str());

        rad2_lower_obs2_corse_dn_remapable = getOptionToString("rad2_lower_obs2_corse_dn_cmd");
        Rad2LowrObs2CrsDnRemapableCmd = XPLMFindCommand(rad2_lower_obs2_corse_dn_remapable.c_str());

        rad2_lower_obs2_fine_up_remapable = getOptionToString("rad2_lower_obs2_fine_up_cmd");
        Rad2LowrObs2FnUpRemapableCmd = XPLMFindCommand(rad2_lower_obs2_fine_up_remapable.c_str());

        rad2_lower_obs2_fine_dn_remapable = getOptionToString("rad2_lower_obs2_fine_dn_cmd");
        Rad2LowrObs2FnDnRemapableCmd = XPLMFindCommand(rad2_lower_obs2_fine_dn_remapable.c_str());

        rad2_lower_obs2_remapable_dataf = getOptionToString("rad2_lower_obs2_dataf");
        Rad2LowerObs2RemapableDataf = XPLMFindDataRef(rad2_lower_obs2_remapable_dataf.c_str());


        rad2_lower_nav2_corse_up_remapable = getOptionToString("rad2_lower_nav2_corse_up_cmd");
        Rad2LowrNav2CrsUpRemapableCmd = XPLMFindCommand(rad2_lower_nav2_corse_up_remapable.c_str());

        rad2_lower_nav2_corse_dn_remapable = getOptionToString("rad2_lower_nav2_corse_dn_cmd");
        Rad2LowrNav2CrsDnRemapableCmd = XPLMFindCommand(rad2_lower_nav2_corse_dn_remapable.c_str());

        rad2_lower_nav2_fine_up_remapable = getOptionToString("rad2_lower_nav2_fine_up_cmd");
        Rad2LowrNav2FnUpRemapableCmd = XPLMFindCommand(rad2_lower_nav2_fine_up_remapable.c_str());

        rad2_lower_nav2_fine_dn_remapable = getOptionToString("rad2_lower_nav2_fine_dn_cmd");
        Rad2LowrNav2FnDnRemapableCmd = XPLMFindCommand(rad2_lower_nav2_fine_dn_remapable.c_str());

        rad2_lower_nav2_act_data_remapable = getOptionToString("rad2_lower_nav2_act_data");
        Rad2LowerNav2ActRemapableData = XPLMFindDataRef(rad2_lower_nav2_act_data_remapable.c_str());

        rad2_lower_nav2_stby_data_remapable = getOptionToString("rad2_lower_nav2_stby_data");
        Rad2LowerNav2StbyRemapableData = XPLMFindDataRef(rad2_lower_nav2_stby_data_remapable.c_str());

    }

    // Radio2 Lower Nav2 active stanby button - remapable
    readOptionAsInt("Radio2 Lower Nav2 ActStby remapable", &rad2lwrnav2actstbybtnremap);
    if (rad2lwrnav2actstbybtnremap == 1) {
        rad2_lower_nav2_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_nav2_actstby_btn_cmd");
        Rad2LowrNav2ActStbyRemapableCmd = XPLMFindCommand(rad2_lower_nav2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2lwrnav2actstbybtnremap == 2) {
        rad2_lower_nav2_actstby_btn_remapable_data = getOptionToString("rad2_lower_nav2_actstby_btn_data");
        Rad2LowrNav2ActStbyRemapableData = XPLMFindDataRef(rad2_lower_nav2_actstby_btn_remapable_data.c_str());
        rad2_lower_nav2_actstby_btn_remapable_dataf = getOptionToString("rad2_lower_nav2_actstby_btn_dataf");
        Rad2LowrNav2ActStbyRemapableDataf = XPLMFindDataRef(rad2_lower_nav2_actstby_btn_remapable_dataf.c_str());
        rad2_lwr_nav2_actstby_btn_data_on_value = getOptionToInt("rad2_lwr_nav2_actstby_btn_data_on_value");
        rad2_lwr_nav2_actstby_btn_data_off_value = getOptionToInt("rad2_lwr_nav2_actstby_btn_data_off_value");
    }


    // Radio2 Lower Adf switch - remapable
    readOptionAsInt("Radio2 Lower Adf Switch remapable", &rad2lwradfswitchremap);
    if (rad2lwradfswitchremap == 1) {

        rad2_lower_adf_corse_up_remapable = getOptionToString("rad2_lower_adf_corse_up_cmd");
        Rad2LowrAdfCrsUpRemapableCmd = XPLMFindCommand(rad2_lower_adf_corse_up_remapable.c_str());

        rad2_lower_adf_corse_dn_remapable = getOptionToString("rad2_lower_adf_corse_dn_cmd");
        Rad2LowrAdfCrsDnRemapableCmd = XPLMFindCommand(rad2_lower_adf_corse_dn_remapable.c_str());

        rad2_lower_adf_fine_up_remapable = getOptionToString("rad2_lower_adf_fine_up_cmd");
        Rad2LowrAdfFnUpRemapableCmd = XPLMFindCommand(rad2_lower_adf_fine_up_remapable.c_str());

        rad2_lower_adf_fine_dn_remapable = getOptionToString("rad2_lower_adf_fine_dn_cmd");
        Rad2LowrAdfFnDnRemapableCmd = XPLMFindCommand(rad2_lower_adf_fine_dn_remapable.c_str());

        rad2_lower_adf_act_data_remapable = getOptionToString("rad2_lower_adf_act_data");
        Rad2LowerAdfActRemapableData = XPLMFindDataRef(rad2_lower_adf_act_data_remapable.c_str());

        rad2_lower_adf_stby_data_remapable = getOptionToString("rad2_lower_adf_stby_data");
        Rad2LowerAdfStbyRemapableData = XPLMFindDataRef(rad2_lower_adf_stby_data_remapable.c_str());

    }

    // Radio2 Lower Adf active stanby button - remapable
    readOptionAsInt("Radio2 Lower Adf ActStby remapable", &rad2lwradfactstbybtnremap);
    if (rad2lwradfactstbybtnremap == 1) {
        rad2_lower_adf_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_adf_actstby_btn_cmd");
        Rad2LowrAdfActStbyRemapableCmd = XPLMFindCommand(rad2_lower_adf_actstby_btn_remapable_cmd.c_str());
    }
    if (rad2upradfactstbybtnremap == 2) {

        rad2_lower_adf_actstby_btn_remapable_data = getOptionToString("rad2_lower_adf_actstby_btn_data");
        Rad2UprAdfActStbyRemapableData = XPLMFindDataRef(rad2_lower_adf_actstby_btn_remapable_data.c_str());
        rad2_lower_adf_actstby_btn_remapable_dataf = getOptionToString("rad2_upper_adf_actstby_btn_dataf");
        Rad2LowrAdfActStbyRemapableDataf = XPLMFindDataRef(rad2_lower_adf_actstby_btn_remapable_dataf.c_str());
        rad2_lwr_adf_actstby_btn_data_on_value = getOptionToInt("rad2_lwr_adf_actstby_btn_data_on_value");
        rad2_lwr_adf_actstby_btn_data_off_value = getOptionToInt("rad2_lwr_adf_actstby_btn_data_off_value");
    }

    // Radio2 Lower Dme switch - remapable
    readOptionAsInt("Radio2 Lower Dme remapable", &rad2lwrdmeswitchremap);



    // Radio2 Lower Xpdr switch - remapable

    readOptionAsInt("Radio2 Lower Xpdr Switch remapable", &rad2lwrxpdrswitchremap);
    if (rad2lwrxpdrswitchremap == 777) {
        rad2_lower_xpdr_data_remapable = getOptionToString("rad2_lower_xpdr_data");
        Rad2LowerXpdrRemapableData = XPLMFindDataRef(rad2_lower_xpdr_data_remapable.c_str());

        rad2_lower_xpdr_mode_remapable = getOptionToString("rad2_lower_xpdr_mode");
        Rad2LowerXpdrRemapableMode = XPLMFindDataRef(rad2_lower_xpdr_mode_remapable.c_str());

        rad2_lower_xpdr_baro_std_data_remapable = getOptionToString("rad2_lower_xpdr_baro_std_data");
        Rad2LowerXpdrBaroStdRemapableData = XPLMFindDataRef(rad2_lower_xpdr_baro_std_data_remapable.c_str());

        rad2_lower_xpdr_baro_up_remapable_cmd = getOptionToString("rad2_lower_xpdr_baro_up_cmd");
        Rad2LowrXpdrBaroUpRemapableCmd = XPLMFindCommand(rad2_lower_xpdr_baro_up_remapable_cmd.c_str());

        rad2_lower_xpdr_baro_dn_remapable_cmd = getOptionToString("rad2_lower_xpdr_baro_dn_cmd");
        Rad2LowrXpdrBaroDnRemapableCmd = XPLMFindCommand(rad2_lower_xpdr_baro_dn_remapable_cmd.c_str());

    }


    // **************************  Upper Radio3 remaping  ******************************************
   // Radio3 Upper Com1 switch - remapable
    readOptionAsInt("Radio3 Upper Com1 Switch remapable", &rad3uprcom1switchremap);
    if (rad3uprcom1switchremap == 1) {
        rad3_upper_com1_corse_up_remapable = getOptionToString("rad3_upper_com1_corse_up_cmd");
        Rad3UprCom1CrsUpRemapableCmd = XPLMFindCommand(rad3_upper_com1_corse_up_remapable.c_str());

        rad3_upper_com1_corse_dn_remapable = getOptionToString("rad3_upper_com1_corse_dn_cmd");
        Rad3UprCom1CrsDnRemapableCmd = XPLMFindCommand(rad3_upper_com1_corse_dn_remapable.c_str());

        rad3_upper_com1_fine_up_remapable = getOptionToString("rad3_upper_com1_fine_up_cmd");
        Rad3UprCom1FnUpRemapableCmd = XPLMFindCommand(rad3_upper_com1_fine_up_remapable.c_str());

        rad3_upper_com1_fine_dn_remapable = getOptionToString("rad3_upper_com1_fine_dn_cmd");
        Rad3UprCom1FnDnRemapableCmd = XPLMFindCommand(rad3_upper_com1_fine_dn_remapable.c_str());

        rad3_upper_com1_act_data_remapable = getOptionToString("rad3_upper_com1_act_data");
        Rad3UpperCom1ActRemapableData = XPLMFindDataRef(rad3_upper_com1_act_data_remapable.c_str());

        rad3_upper_com1_stby_data_remapable = getOptionToString("rad3_upper_com1_stby_data");
        Rad3UpperCom1StbyRemapableData = XPLMFindDataRef(rad3_upper_com1_stby_data_remapable.c_str());

    }

    // Radio3 Upper Com1 active stanby button - remapable
    readOptionAsInt("Radio3 Upper Com1 ActStby remapable", &rad3uprcom1actstbybtnremap);
    if (rad3uprcom1actstbybtnremap == 1) {
        rad3_upper_com1_actstby_btn_remapable_cmd = getOptionToString("rad3_upper_com1_actstby_btn_cmd");
        Rad3UprCom1ActStbyRemapableCmd = XPLMFindCommand(rad3_upper_com1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3uprcom1actstbybtnremap == 2) {
        rad3_upper_com1_actstby_btn_remapable_data = getOptionToString("rad3_upper_com1_actstby_btn_data");
        Rad3UprCom1ActStbyRemapableData = XPLMFindDataRef(rad3_upper_com1_actstby_btn_remapable_data.c_str());
        rad3_upper_com1_actstby_btn_remapable_dataf = getOptionToString("rad3_upper_com1_actstby_btn_dataf");
        Rad3UprCom1ActStbyRemapableDataf = XPLMFindDataRef(rad3_upper_com1_actstby_btn_remapable_dataf.c_str());
        rad3_upr_com1_actstby_btn_data_on_value = getOptionToInt("rad3_upr_com1_actstby_btn_data_on_value");
        rad3_upr_com1_actstby_btn_data_off_value = getOptionToInt("rad3_upr_com1_actstby_btn_data_off_value");
    }

    // Radio3 Upper Com2 switch - remapable
    readOptionAsInt("Radio3 Upper Com2 Switch remapable", &rad3uprcom2switchremap);
    if (rad3uprcom2switchremap == 1) {
        rad3_upper_com2_corse_up_remapable = getOptionToString("rad3_upper_com2_corse_up_cmd");
        Rad3UprCom2CrsUpRemapableCmd = XPLMFindCommand(rad3_upper_com2_corse_up_remapable.c_str());

        rad3_upper_com2_corse_dn_remapable = getOptionToString("rad3_upper_com2_corse_dn_cmd");
        Rad3UprCom2CrsDnRemapableCmd = XPLMFindCommand(rad3_upper_com2_corse_dn_remapable.c_str());

        rad3_upper_com2_fine_up_remapable = getOptionToString("rad3_upper_com2_fine_up_cmd");
        Rad3UprCom2FnUpRemapableCmd = XPLMFindCommand(rad3_upper_com2_fine_up_remapable.c_str());

        rad3_upper_com2_fine_dn_remapable = getOptionToString("rad3_upper_com2_fine_dn_cmd");
        Rad3UprCom2FnDnRemapableCmd = XPLMFindCommand(rad3_upper_com2_fine_dn_remapable.c_str());

        rad3_upper_com2_act_data_remapable = getOptionToString("rad3_upper_com2_act_data");
        Rad3UpperCom2ActRemapableData = XPLMFindDataRef(rad3_upper_com2_act_data_remapable.c_str());

        rad3_upper_com2_stby_data_remapable = getOptionToString("rad3_upper_com2_stby_data");
        Rad3UpperCom2StbyRemapableData = XPLMFindDataRef(rad3_upper_com2_stby_data_remapable.c_str());

    }

    // Radio3 Upper Com2 active stanby button - remapable
    readOptionAsInt("Radio3 Upper Com2 ActStby remapable", &rad3uprcom2actstbybtnremap);
    if (rad3uprcom2actstbybtnremap == 1) {
        rad3_upper_com2_actstby_btn_remapable_cmd = getOptionToString("rad3_upper_com2_actstby_btn_cmd");
        Rad3UprCom2ActStbyRemapableCmd = XPLMFindCommand(rad3_upper_com2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3uprcom2actstbybtnremap == 2) {
        rad3_upper_com2_actstby_btn_remapable_data = getOptionToString("rad3_upper_com2_actstby_btn_data");
        Rad3UprCom2ActStbyRemapableData = XPLMFindDataRef(rad3_upper_com2_actstby_btn_remapable_data.c_str());
        rad3_upper_com2_actstby_btn_remapable_dataf = getOptionToString("rad3_upper_com2_actstby_btn_dataf");
        Rad3UprCom2ActStbyRemapableDataf = XPLMFindDataRef(rad3_upper_com2_actstby_btn_remapable_dataf.c_str());
        rad3_upr_com2_actstby_btn_data_on_value = getOptionToInt("rad3_upr_com2_actstby_btn_data_on_value");
        rad3_upr_com2_actstby_btn_data_off_value = getOptionToInt("rad3_upr_com2_actstby_btn_data_off_value");
    }

    // Radio3 Upper Nav1 switch - remapable
    readOptionAsInt("Radio3 Upper Nav1 Switch remapable", &rad3uprnav1switchremap);
    if (rad3uprnav1switchremap == 1) {
        rad3_upper_obs1_corse_up_remapable = getOptionToString("rad3_upper_obs1_corse_up_cmd");
        Rad3UprObs1CrsUpRemapableCmd = XPLMFindCommand(rad3_upper_obs1_corse_up_remapable.c_str());

        rad3_upper_obs1_corse_dn_remapable = getOptionToString("rad3_upper_obs1_corse_dn_cmd");
        Rad3UprObs1CrsDnRemapableCmd = XPLMFindCommand(rad3_upper_obs1_corse_dn_remapable.c_str());

        rad3_upper_obs1_fine_up_remapable = getOptionToString("rad3_upper_obs1_fine_up_cmd");
        Rad3UprObs1FnUpRemapableCmd = XPLMFindCommand(rad3_upper_obs1_fine_up_remapable.c_str());

        rad3_upper_obs1_fine_dn_remapable = getOptionToString("rad3_upper_obs1_fine_dn_cmd");
        Rad3UprObs1FnDnRemapableCmd = XPLMFindCommand(rad3_upper_obs1_fine_dn_remapable.c_str());

        rad3_upper_obs1_remapable_dataf = getOptionToString("rad3_upper_obs1_dataf");
        Rad3UpperObs1RemapableDataf = XPLMFindDataRef(rad3_upper_obs1_remapable_dataf.c_str());


        rad3_upper_nav1_corse_up_remapable = getOptionToString("rad3_upper_nav1_corse_up_cmd");
        Rad3UprNav1CrsUpRemapableCmd = XPLMFindCommand(rad3_upper_nav1_corse_up_remapable.c_str());

        rad3_upper_nav1_corse_dn_remapable = getOptionToString("rad3_upper_nav1_corse_dn_cmd");
        Rad3UprNav1CrsDnRemapableCmd = XPLMFindCommand(rad3_upper_nav1_corse_dn_remapable.c_str());

        rad3_upper_nav1_fine_up_remapable = getOptionToString("rad3_upper_nav1_fine_up_cmd");
        Rad3UprNav1FnUpRemapableCmd = XPLMFindCommand(rad3_upper_nav1_fine_up_remapable.c_str());

        rad3_upper_nav1_fine_dn_remapable = getOptionToString("rad3_upper_nav1_fine_dn_cmd");
        Rad3UprNav1FnDnRemapableCmd = XPLMFindCommand(rad3_upper_nav1_fine_dn_remapable.c_str());

        rad3_upper_nav1_act_data_remapable = getOptionToString("rad3_upper_nav1_act_data");
        Rad2UpperNav1ActRemapableData = XPLMFindDataRef(rad3_upper_nav1_act_data_remapable.c_str());

        rad3_upper_nav1_stby_data_remapable = getOptionToString("rad3_upper_nav1_stby_data");
        Rad3UpperNav1StbyRemapableData = XPLMFindDataRef(rad3_upper_nav1_stby_data_remapable.c_str());

    }

    // Radio3 Upper Nav1 active stanby button - remapable
    readOptionAsInt("Radio3 Upper Nav1 ActStby remapable", &rad3uprnav1actstbybtnremap);
    if (rad3uprnav1actstbybtnremap == 1) {
        rad3_upper_nav1_actstby_btn_remapable_cmd = getOptionToString("rad3_upper_nav1_actstby_btn_cmd");
        Rad3UprNav1ActStbyRemapableCmd = XPLMFindCommand(rad3_upper_nav1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3uprnav1actstbybtnremap == 2) {
        rad3_upper_nav1_actstby_btn_remapable_data = getOptionToString("rad3_upper_nav1_actstby_btn_data");
        Rad3UprNav1ActStbyRemapableData = XPLMFindDataRef(rad3_upper_nav1_actstby_btn_remapable_data.c_str());
        rad3_upper_nav1_actstby_btn_remapable_dataf = getOptionToString("rad3_upper_nav1_actstby_btn_dataf");
        Rad3UprNav1ActStbyRemapableDataf = XPLMFindDataRef(rad3_upper_nav1_actstby_btn_remapable_dataf.c_str());
        rad3_upr_nav1_actstby_btn_data_on_value = getOptionToInt("rad3_upr_nav1_actstby_btn_data_on_value");
        rad3_upr_nav1_actstby_btn_data_off_value = getOptionToInt("rad3_upr_nav1_actstby_btn_data_off_value");
    }

    // Radio3 Upper Nav2 switch - remapable
    readOptionAsInt("Radio3 Upper Nav2 Switch remapable", &rad3uprnav2switchremap);
    if (rad3uprnav2switchremap == 1) {
        rad3_upper_obs2_corse_up_remapable = getOptionToString("rad3_upper_obs2_corse_up_cmd");
        Rad3UprObs2CrsUpRemapableCmd = XPLMFindCommand(rad3_upper_obs2_corse_up_remapable.c_str());

        rad3_upper_obs2_corse_dn_remapable = getOptionToString("rad3_upper_obs2_corse_dn_cmd");
        Rad3UprObs2CrsDnRemapableCmd = XPLMFindCommand(rad3_upper_obs2_corse_dn_remapable.c_str());

        rad3_upper_obs2_fine_up_remapable = getOptionToString("rad3_upper_obs2_fine_up_cmd");
        Rad2UprObs2FnUpRemapableCmd = XPLMFindCommand(rad3_upper_obs2_fine_up_remapable.c_str());

        rad3_upper_obs2_fine_dn_remapable = getOptionToString("rad3_upper_obs2_fine_dn_cmd");
        Rad3UprObs2FnDnRemapableCmd = XPLMFindCommand(rad3_upper_obs2_fine_dn_remapable.c_str());

        rad3_upper_obs2_remapable_dataf = getOptionToString("rad3_upper_obs2_dataf");
        Rad3UpperObs2RemapableDataf = XPLMFindDataRef(rad3_upper_obs2_remapable_dataf.c_str());


        rad3_upper_nav2_corse_up_remapable = getOptionToString("rad3_upper_nav2_corse_up_cmd");
        Rad3UprNav2CrsUpRemapableCmd = XPLMFindCommand(rad3_upper_nav2_corse_up_remapable.c_str());

        rad3_upper_nav2_corse_dn_remapable = getOptionToString("rad3_upper_nav2_corse_dn_cmd");
        Rad3UprNav2CrsDnRemapableCmd = XPLMFindCommand(rad3_upper_nav2_corse_dn_remapable.c_str());

        rad3_upper_nav2_fine_up_remapable = getOptionToString("rad3_upper_nav2_fine_up_cmd");
        Rad2UprNav2FnUpRemapableCmd = XPLMFindCommand(rad3_upper_nav2_fine_up_remapable.c_str());

        rad3_upper_nav2_fine_dn_remapable = getOptionToString("rad3_upper_nav2_fine_dn_cmd");
        Rad3UprNav2FnDnRemapableCmd = XPLMFindCommand(rad3_upper_nav2_fine_dn_remapable.c_str());

        rad3_upper_nav2_act_data_remapable = getOptionToString("rad3_upper_nav2_act_data");
        Rad3UpperNav2ActRemapableData = XPLMFindDataRef(rad3_upper_nav2_act_data_remapable.c_str());

        rad3_upper_nav2_stby_data_remapable = getOptionToString("rad3_upper_nav2_stby_data");
        Rad3UpperNav2StbyRemapableData = XPLMFindDataRef(rad3_upper_nav2_stby_data_remapable.c_str());

    }

    // Radio3 Upper Nav2 active stanby button - remapable
    readOptionAsInt("Radio3 Upper Nav2 ActStby remapable", &rad3uprnav2actstbybtnremap);
    if (rad3uprnav2actstbybtnremap == 1) {
        rad3_upper_nav2_actstby_btn_remapable_cmd = getOptionToString("rad3_upper_nav2_actstby_btn_cmd");
        Rad3UprNav2ActStbyRemapableCmd = XPLMFindCommand(rad3_upper_nav2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3uprnav2actstbybtnremap == 2) {
        rad3_upper_nav2_actstby_btn_remapable_data = getOptionToString("rad3_upper_nav2_actstby_btn_data");
        Rad3UprNav2ActStbyRemapableData = XPLMFindDataRef(rad3_upper_nav2_actstby_btn_remapable_data.c_str());
        rad3_upper_nav2_actstby_btn_remapable_dataf = getOptionToString("rad3_upper_nav2_actstby_btn_dataf");
        Rad3UprNav2ActStbyRemapableDataf = XPLMFindDataRef(rad3_upper_nav2_actstby_btn_remapable_dataf.c_str());
        rad3_upr_nav2_actstby_btn_data_on_value = getOptionToInt("rad3_upr_nav2_actstby_btn_data_on_value");
        rad3_upr_nav2_actstby_btn_data_off_value = getOptionToInt("rad3_upr_nav2_actstby_btn_data_off_value");
    }

    // Radio3 Upper Adf switch - remapable
    readOptionAsInt("Radio3 Upper Adf Switch remapable", &rad3upradfswitchremap);
    if (rad3upradfswitchremap == 1) {

        rad3_upper_adf_corse_up_remapable = getOptionToString("rad3_upper_adf_corse_up_cmd");
        Rad3UprAdfCrsUpRemapableCmd = XPLMFindCommand(rad3_upper_adf_corse_up_remapable.c_str());

        rad3_upper_adf_corse_dn_remapable = getOptionToString("rad3_upper_adf_corse_dn_cmd");
        Rad3UprAdfCrsDnRemapableCmd = XPLMFindCommand(rad3_upper_adf_corse_dn_remapable.c_str());

        rad3_upper_adf_fine_up_remapable = getOptionToString("rad3_upper_adf_fine_up_cmd");
        Rad3UprAdfFnUpRemapableCmd = XPLMFindCommand(rad3_upper_adf_fine_up_remapable.c_str());

        rad3_upper_adf_fine_dn_remapable = getOptionToString("rad3_upper_adf_fine_dn_cmd");
        Rad3UprAdfFnDnRemapableCmd = XPLMFindCommand(rad3_upper_adf_fine_dn_remapable.c_str());

        rad3_upper_adf_act_data_remapable = getOptionToString("rad3_upper_adf_act_data");
        Rad3UpperAdfActRemapableData = XPLMFindDataRef(rad3_upper_adf_act_data_remapable.c_str());

        rad3_upper_adf_stby_data_remapable = getOptionToString("rad3_upper_adf_stby_data");
        Rad3UpperAdfStbyRemapableData = XPLMFindDataRef(rad3_upper_adf_stby_data_remapable.c_str());

    }

    // Radio3 Upper Adf active stanby button - remapable
    readOptionAsInt("Radio3 Upper Adf ActStby remapable", &rad3upradfactstbybtnremap);
    if (rad3upradfactstbybtnremap == 1) {
        rad3_upper_adf_actstby_btn_remapable_cmd = getOptionToString("rad3_upper_adf_actstby_btn_cmd");
        Rad3UprAdfActStbyRemapableCmd = XPLMFindCommand(rad3_upper_adf_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3upradfactstbybtnremap == 2) {

        rad3_upper_adf_actstby_btn_remapable_data = getOptionToString("rad3_upper_adf_actstby_btn_data");
        Rad3UprAdfActStbyRemapableData = XPLMFindDataRef(rad3_upper_adf_actstby_btn_remapable_data.c_str());
        rad3_upper_adf_actstby_btn_remapable_dataf = getOptionToString("rad3_upper_adf_actstby_btn_dataf");
        Rad3UprAdfActStbyRemapableDataf = XPLMFindDataRef(rad3_upper_adf_actstby_btn_remapable_dataf.c_str());
        rad3_upr_adf_actstby_btn_data_on_value = getOptionToInt("rad3_upr_adf_actstby_btn_data_on_value");
        rad3_upr_adf_actstby_btn_data_off_value = getOptionToInt("rad3_upr_adf_actstby_btn_data_off_value");
    }


    // Radio3 Upper Dme switch - remapable
    readOptionAsInt("Radio3 Upper Dme remapable", &rad3uprdmeswitchremap);



    // Radio3 Upper Xpdr switch - remapable

    readOptionAsInt("Radio3 Upper Xpdr Switch remapable", &rad3uprxpdrswitchremap);
    if (rad3uprxpdrswitchremap == 777) {
        rad3_upper_xpdr_data_remapable = getOptionToString("rad3_upper_xpdr_data");
        Rad3UpperXpdrRemapableData = XPLMFindDataRef(rad3_upper_xpdr_data_remapable.c_str());

        rad3_upper_xpdr_mode_remapable = getOptionToString("rad3_upper_xpdr_mode");
        Rad3UpperXpdrRemapableMode = XPLMFindDataRef(rad3_upper_xpdr_mode_remapable.c_str());

        rad3_upper_xpdr_baro_std_data_remapable = getOptionToString("rad3_upper_xpdr_baro_std_data");
        Rad3UpperXpdrBaroStdRemapableData = XPLMFindDataRef(rad3_upper_xpdr_baro_std_data_remapable.c_str());

        rad3_upper_xpdr_baro_up_remapable_cmd = getOptionToString("rad3_upper_xpdr_baro_up_cmd");
        Rad3UpperXpdrBaroUpRemapableCmd = XPLMFindCommand(rad3_upper_xpdr_baro_up_remapable_cmd.c_str());

        rad3_upper_xpdr_baro_dn_remapable_cmd = getOptionToString("rad3_upper_xpdr_baro_dn_cmd");
        Rad3UpperXpdrBaroDnRemapableCmd = XPLMFindCommand(rad3_upper_xpdr_baro_dn_remapable_cmd.c_str());


    }




    //  *****************************  Lower Radio3 remaping  **************************************
    // Radio3 Lower Com1 switch - remapable
    readOptionAsInt("Radio3 Lower Com1 Switch remapable", &rad3lwrcom1switchremap);
    if (rad3lwrcom1switchremap == 1) {
        rad3_lower_com1_corse_up_remapable = getOptionToString("rad3_lower_com1_corse_up_cmd");
        Rad3LowrCom1CrsUpRemapableCmd = XPLMFindCommand(rad3_lower_com1_corse_up_remapable.c_str());

        rad3_lower_com1_corse_dn_remapable = getOptionToString("rad3_lower_com1_corse_dn_cmd");
        Rad3LowrCom1CrsDnRemapableCmd = XPLMFindCommand(rad3_lower_com1_corse_dn_remapable.c_str());

        rad3_lower_com1_fine_up_remapable = getOptionToString("rad3_lower_com1_fine_up_cmd");
        Rad3LowrCom1FnUpRemapableCmd = XPLMFindCommand(rad3_lower_com1_fine_up_remapable.c_str());

        rad3_lower_com1_fine_dn_remapable = getOptionToString("rad3_lower_com1_fine_dn_cmd");
        Rad3LowrCom1FnDnRemapableCmd = XPLMFindCommand(rad3_lower_com1_fine_dn_remapable.c_str());

        rad3_lower_com1_act_data_remapable = getOptionToString("rad3_lower_com1_act_data");
        Rad3LowerCom1ActRemapableData = XPLMFindDataRef(rad3_lower_com1_act_data_remapable.c_str());

        rad3_lower_com1_stby_data_remapable = getOptionToString("rad3_lower_com1_stby_data");
        Rad3LowerCom1StbyRemapableData = XPLMFindDataRef(rad3_lower_com1_stby_data_remapable.c_str());

    }

    // Radio3 Lower Com1 active stanby button - remapable
    readOptionAsInt("Radio3 Lower Com1 ActStby remapable", &rad3lwrcom1actstbybtnremap);
    if (rad3lwrcom1actstbybtnremap == 1) {
        rad3_lower_com1_actstby_btn_remapable_cmd = getOptionToString("rad3_lower_com1_actstby_btn_cmd");
        Rad3LowrCom1ActStbyRemapableCmd = XPLMFindCommand(rad3_lower_com1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3lwrcom1actstbybtnremap == 2) {
        rad3_lower_com1_actstby_btn_remapable_data = getOptionToString("rad3_lower_com1_actstby_btn_data");
        Rad3LowrCom1ActStbyRemapableData = XPLMFindDataRef(rad3_lower_com1_actstby_btn_remapable_data.c_str());
        rad3_lower_com1_actstby_btn_remapable_dataf = getOptionToString("rad3_lower_com1_actstby_btn_dataf");
        Rad3LowrCom1ActStbyRemapableDataf = XPLMFindDataRef(rad3_lower_com1_actstby_btn_remapable_dataf.c_str());
        rad3_lwr_com1_actstby_btn_data_on_value = getOptionToInt("rad3_lwr_com1_actstby_btn_data_on_value");
        rad3_lwr_com1_actstby_btn_data_off_value = getOptionToInt("rad3_lwr_com1_actstby_btn_data_off_value");
    }

    // Radio3 Lower Com2 switch - remapable
    readOptionAsInt("Radio3 Lower Com2 Switch remapable", &rad3lwrcom2switchremap);
    if (rad3lwrcom2switchremap == 1) {
        rad3_lower_com2_corse_up_remapable = getOptionToString("rad3_lower_com2_corse_up_cmd");
        Rad3LowrCom2CrsUpRemapableCmd = XPLMFindCommand(rad3_lower_com2_corse_up_remapable.c_str());

        rad3_lower_com2_corse_dn_remapable = getOptionToString("rad3_lower_com2_corse_dn_cmd");
        Rad3LowrCom2CrsDnRemapableCmd = XPLMFindCommand(rad3_lower_com2_corse_dn_remapable.c_str());

        rad3_lower_com2_fine_up_remapable = getOptionToString("rad3_lower_com2_fine_up_cmd");
        Rad3LowrCom2FnUpRemapableCmd = XPLMFindCommand(rad3_lower_com2_fine_up_remapable.c_str());

        rad3_lower_com2_fine_dn_remapable = getOptionToString("rad3_lower_com2_fine_dn_cmd");
        Rad3LowrCom2FnDnRemapableCmd = XPLMFindCommand(rad3_lower_com2_fine_dn_remapable.c_str());

        rad3_lower_com2_act_data_remapable = getOptionToString("rad3_lower_com2_act_data");
        Rad3LowerCom2ActRemapableData = XPLMFindDataRef(rad3_lower_com2_act_data_remapable.c_str());

        rad3_lower_com2_stby_data_remapable = getOptionToString("rad3_lower_com2_stby_data");
        Rad3LowerCom2StbyRemapableData = XPLMFindDataRef(rad3_lower_com2_stby_data_remapable.c_str());

    }

    // Radio3 Lower Com2 active stanby button - remapable
    readOptionAsInt("Radio3 Lower Com2 ActStby remapable", &rad3lwrcom2actstbybtnremap);
    if (rad3lwrcom2actstbybtnremap == 1) {
        rad3_lower_com2_actstby_btn_remapable_cmd = getOptionToString("rad3_lower_com2_actstby_btn_cmd");
        Rad3LowrCom2ActStbyRemapableCmd = XPLMFindCommand(rad3_lower_com2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3lwrcom2actstbybtnremap == 2) {
        rad3_lower_com2_actstby_btn_remapable_data = getOptionToString("rad3_lower_com2_actstby_btn_data");
        Rad3LowrCom2ActStbyRemapableData = XPLMFindDataRef(rad3_lower_com2_actstby_btn_remapable_data.c_str());
        rad3_lower_com2_actstby_btn_remapable_dataf = getOptionToString("rad3_lower_com2_actstby_btn_dataf");
        Rad3LowrCom2ActStbyRemapableDataf = XPLMFindDataRef(rad3_lower_com2_actstby_btn_remapable_dataf.c_str());
        rad3_lwr_com2_actstby_btn_data_on_value = getOptionToInt("rad3_lwr_com2_actstby_btn_data_on_value");
        rad3_lwr_com2_actstby_btn_data_off_value = getOptionToInt("rad3_lwr_com2_actstby_btn_data_off_value");
    }

    // Radio3 Lower Nav1 switch - remapable
    readOptionAsInt("Radio3 Lower Nav1 Switch remapable", &rad3lwrnav1switchremap);
    if (rad3lwrnav1switchremap == 1) {
        rad3_lower_obs1_corse_up_remapable = getOptionToString("rad3_lower_obs1_corse_up_cmd");
        Rad3LowrObs1CrsUpRemapableCmd = XPLMFindCommand(rad3_lower_obs1_corse_up_remapable.c_str());

        rad3_lower_obs1_corse_dn_remapable = getOptionToString("rad3_lower_obs1_corse_dn_cmd");
        Rad3LowrObs1CrsDnRemapableCmd = XPLMFindCommand(rad3_lower_obs1_corse_dn_remapable.c_str());

        rad3_lower_obs1_fine_up_remapable = getOptionToString("rad3_lower_obs1_fine_up_cmd");
        Rad3LowrObs1FnUpRemapableCmd = XPLMFindCommand(rad3_lower_obs1_fine_up_remapable.c_str());

        rad3_lower_obs1_fine_dn_remapable = getOptionToString("rad3_lower_obs1_fine_dn_cmd");
        Rad3LowrObs1FnDnRemapableCmd = XPLMFindCommand(rad3_lower_obs1_fine_dn_remapable.c_str());

        rad3_lower_obs1_remapable_dataf = getOptionToString("rad3_lower_obs1_dataf");
        Rad3LowerObs1RemapableDataf = XPLMFindDataRef(rad3_lower_obs1_remapable_dataf.c_str());



        rad3_lower_nav1_corse_up_remapable = getOptionToString("rad3_lower_nav1_corse_up_cmd");
        Rad3LowrNav1CrsUpRemapableCmd = XPLMFindCommand(rad3_lower_nav1_corse_up_remapable.c_str());

        rad3_lower_nav1_corse_dn_remapable = getOptionToString("rad3_lower_nav1_corse_dn_cmd");
        Rad3LowrNav1CrsDnRemapableCmd = XPLMFindCommand(rad3_lower_nav1_corse_dn_remapable.c_str());

        rad3_lower_nav1_fine_up_remapable = getOptionToString("rad3_lower_nav1_fine_up_cmd");
        Rad3LowrNav1FnUpRemapableCmd = XPLMFindCommand(rad3_lower_nav1_fine_up_remapable.c_str());

        rad3_lower_nav1_fine_dn_remapable = getOptionToString("rad3_lower_nav1_fine_dn_cmd");
        Rad3LowrNav1FnDnRemapableCmd = XPLMFindCommand(rad3_lower_nav1_fine_dn_remapable.c_str());

        rad3_lower_nav1_act_data_remapable = getOptionToString("rad3_lower_nav1_act_data");
        Rad3LowerNav1ActRemapableData = XPLMFindDataRef(rad3_lower_nav1_act_data_remapable.c_str());

        rad3_lower_nav1_stby_data_remapable = getOptionToString("rad3_lower_nav1_stby_data");
        Rad3LowerNav1StbyRemapableData = XPLMFindDataRef(rad3_lower_nav1_stby_data_remapable.c_str());

    }

    // Radio3 Lower Nav1 active stanby button - remapable
    readOptionAsInt("Radio3 Lower Nav1 ActStby remapable", &rad3lwrnav1actstbybtnremap);
    if (rad3lwrnav1actstbybtnremap == 1) {
        rad3_lower_nav1_actstby_btn_remapable_cmd = getOptionToString("rad3_lower_nav1_actstby_btn_cmd");
        Rad3LowrNav1ActStbyRemapableCmd = XPLMFindCommand(rad3_lower_nav1_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3lwrnav1actstbybtnremap == 2) {
        rad3_lower_nav1_actstby_btn_remapable_data = getOptionToString("rad3_lower_nav1_actstby_btn_data");
        Rad3LowrNav1ActStbyRemapableData = XPLMFindDataRef(rad3_lower_nav1_actstby_btn_remapable_data.c_str());
        rad3_lower_nav1_actstby_btn_remapable_dataf = getOptionToString("rad3_lower_nav1_actstby_btn_dataf");
        Rad3LowrNav1ActStbyRemapableDataf = XPLMFindDataRef(rad3_lower_nav1_actstby_btn_remapable_dataf.c_str());
        rad3_lwr_nav1_actstby_btn_data_on_value = getOptionToInt("rad3_lwr_nav1_actstby_btn_data_on_value");
        rad3_lwr_nav1_actstby_btn_data_off_value = getOptionToInt("rad3_lwr_nav1_actstby_btn_data_off_value");
    }

    // Radio3 Lower Nav2 switch - remapable
    readOptionAsInt("Radio3 Lower Nav2 Switch remapable", &rad3lwrnav2switchremap);
    if (rad3lwrnav2switchremap == 1) {
        rad3_lower_obs2_corse_up_remapable = getOptionToString("rad3_lower_obs2_corse_up_cmd");
        Rad3LowrObs2CrsUpRemapableCmd = XPLMFindCommand(rad3_lower_obs2_corse_up_remapable.c_str());

        rad3_lower_obs2_corse_dn_remapable = getOptionToString("rad3_lower_obs2_corse_dn_cmd");
        Rad3LowrObs2CrsDnRemapableCmd = XPLMFindCommand(rad3_lower_obs2_corse_dn_remapable.c_str());

        rad3_lower_obs2_fine_up_remapable = getOptionToString("rad3_lower_obs2_fine_up_cmd");
        Rad3LowrObs2FnUpRemapableCmd = XPLMFindCommand(rad3_lower_obs2_fine_up_remapable.c_str());

        rad3_lower_obs2_fine_dn_remapable = getOptionToString("rad3_lower_obs2_fine_dn_cmd");
        Rad3LowrObs2FnDnRemapableCmd = XPLMFindCommand(rad3_lower_obs2_fine_dn_remapable.c_str());

        rad3_lower_obs2_remapable_dataf = getOptionToString("rad3_lower_obs2_dataf");
        Rad3LowerObs2RemapableDataf = XPLMFindDataRef(rad3_lower_obs2_remapable_dataf.c_str());


        rad3_lower_nav2_corse_up_remapable = getOptionToString("rad3_lower_nav2_corse_up_cmd");
        Rad3LowrNav2CrsUpRemapableCmd = XPLMFindCommand(rad3_lower_nav2_corse_up_remapable.c_str());

        rad3_lower_nav2_corse_dn_remapable = getOptionToString("rad3_lower_nav2_corse_dn_cmd");
        Rad3LowrNav2CrsDnRemapableCmd = XPLMFindCommand(rad3_lower_nav2_corse_dn_remapable.c_str());

        rad3_lower_nav2_fine_up_remapable = getOptionToString("rad3_lower_nav2_fine_up_cmd");
        Rad3LowrNav2FnUpRemapableCmd = XPLMFindCommand(rad3_lower_nav2_fine_up_remapable.c_str());

        rad3_lower_nav2_fine_dn_remapable = getOptionToString("rad3_lower_nav2_fine_dn_cmd");
        Rad3LowrNav2FnDnRemapableCmd = XPLMFindCommand(rad3_lower_nav2_fine_dn_remapable.c_str());

        rad3_lower_nav2_act_data_remapable = getOptionToString("rad3_lower_nav2_act_data");
        Rad3LowerNav2ActRemapableData = XPLMFindDataRef(rad3_lower_nav2_act_data_remapable.c_str());

        rad3_lower_nav2_stby_data_remapable = getOptionToString("rad3_lower_nav2_stby_data");
        Rad3LowerNav2StbyRemapableData = XPLMFindDataRef(rad3_lower_nav2_stby_data_remapable.c_str());

    }

    // Radio3 Lower Nav2 active stanby button - remapable
    readOptionAsInt("Radio3 Lower Nav2 ActStby remapable", &rad3lwrnav2actstbybtnremap);
    if (rad3lwrnav2actstbybtnremap == 1) {
        rad3_lower_nav2_actstby_btn_remapable_cmd = getOptionToString("rad3_lower_nav2_actstby_btn_cmd");
        Rad3LowrNav2ActStbyRemapableCmd = XPLMFindCommand(rad3_lower_nav2_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3lwrnav2actstbybtnremap == 2) {
        rad3_lower_nav2_actstby_btn_remapable_data = getOptionToString("rad3_lower_nav2_actstby_btn_data");
        Rad3LowrNav2ActStbyRemapableData = XPLMFindDataRef(rad3_lower_nav2_actstby_btn_remapable_data.c_str());
        rad3_lower_nav2_actstby_btn_remapable_dataf = getOptionToString("rad3_lower_nav2_actstby_btn_dataf");
        Rad3LowrNav2ActStbyRemapableDataf = XPLMFindDataRef(rad3_lower_nav2_actstby_btn_remapable_dataf.c_str());
        rad3_lwr_nav2_actstby_btn_data_on_value = getOptionToInt("rad3_lwr_nav2_actstby_btn_data_on_value");
        rad3_lwr_nav2_actstby_btn_data_off_value = getOptionToInt("rad3_lwr_nav2_actstby_btn_data_off_value");
    }

    // Radio3 Lower Adf switch - remapable
    readOptionAsInt("Radio3 Lower Adf Switch remapable", &rad3lwradfswitchremap);
    if (rad3lwradfswitchremap == 1) {

        rad3_lower_adf_corse_up_remapable = getOptionToString("rad3_lower_adf_corse_up_cmd");
        Rad3LowrAdfCrsUpRemapableCmd = XPLMFindCommand(rad3_lower_adf_corse_up_remapable.c_str());

        rad3_lower_adf_corse_dn_remapable = getOptionToString("rad3_lower_adf_corse_dn_cmd");
        Rad3LowrAdfCrsDnRemapableCmd = XPLMFindCommand(rad2_lower_adf_corse_dn_remapable.c_str());

        rad3_lower_adf_fine_up_remapable = getOptionToString("rad3_lower_adf_fine_up_cmd");
        Rad3LowrAdfFnUpRemapableCmd = XPLMFindCommand(rad3_lower_adf_fine_up_remapable.c_str());

        rad3_lower_adf_fine_dn_remapable = getOptionToString("rad3_lower_adf_fine_dn_cmd");
        Rad3LowrAdfFnDnRemapableCmd = XPLMFindCommand(rad3_lower_adf_fine_dn_remapable.c_str());

        rad3_lower_adf_act_data_remapable = getOptionToString("rad3_lower_adf_act_data");
        Rad3LowerAdfActRemapableData = XPLMFindDataRef(rad3_lower_adf_act_data_remapable.c_str());

        rad3_lower_adf_stby_data_remapable = getOptionToString("rad3_lower_adf_stby_data");
        Rad3LowerAdfStbyRemapableData = XPLMFindDataRef(rad3_lower_adf_stby_data_remapable.c_str());

    }

    // Radio3 Lower Adf active stanby button - remapable
    readOptionAsInt("Radio3 Lower Adf ActStby remapable", &rad3lwradfactstbybtnremap);
    if (rad3lwradfactstbybtnremap == 1) {
        rad3_lower_adf_actstby_btn_remapable_cmd = getOptionToString("rad3_lower_adf_actstby_btn_cmd");
        Rad3LowrAdfActStbyRemapableCmd = XPLMFindCommand(rad3_lower_adf_actstby_btn_remapable_cmd.c_str());
    }
    if (rad3upradfactstbybtnremap == 2) {

        rad3_lower_adf_actstby_btn_remapable_data = getOptionToString("rad2_lower_adf_actstby_btn_data");
        Rad3UprAdfActStbyRemapableData = XPLMFindDataRef(rad3_lower_adf_actstby_btn_remapable_data.c_str());
        rad3_lower_adf_actstby_btn_remapable_dataf = getOptionToString("rad3_upper_adf_actstby_btn_dataf");
        Rad3LowrAdfActStbyRemapableDataf = XPLMFindDataRef(rad3_lower_adf_actstby_btn_remapable_dataf.c_str());
        rad3_lwr_adf_actstby_btn_data_on_value = getOptionToInt("rad3_lwr_adf_actstby_btn_data_on_value");
        rad3_lwr_adf_actstby_btn_data_off_value = getOptionToInt("rad3_lwr_adf_actstby_btn_data_off_value");
    }


    // Radio3 Lower Dme switch - remapable
    readOptionAsInt("Radio3 Lower Dme remapable", &rad3lwrdmeswitchremap);


    // Radio3 Lower Xpdr switch - remapable

    readOptionAsInt("Radio3 Lower Xpdr Switch remapable", &rad3lwrxpdrswitchremap);
    if (rad3lwrxpdrswitchremap == 777) {
        rad3_lower_xpdr_data_remapable = getOptionToString("rad3_lower_xpdr_data");
        Rad3LowerXpdrRemapableData = XPLMFindDataRef(rad3_lower_xpdr_data_remapable.c_str());

        rad3_lower_xpdr_mode_remapable = getOptionToString("rad3_lower_xpdr_mode");
        Rad3LowerXpdrRemapableMode = XPLMFindDataRef(rad3_lower_xpdr_mode_remapable.c_str());

        rad3_lower_xpdr_baro_std_data_remapable = getOptionToString("rad3_lower_xpdr_baro_std_data");
        Rad3LowerXpdrBaroStdRemapableData = XPLMFindDataRef(rad3_lower_xpdr_baro_std_data_remapable.c_str());

        rad3_lower_xpdr_baro_up_remapable_cmd = getOptionToString("rad3_lower_xpdr_baro_up_cmd");
        Rad3LowrXpdrBaroUpRemapableCmd = XPLMFindCommand(rad3_lower_xpdr_baro_up_remapable_cmd.c_str());

        rad3_lower_xpdr_baro_dn_remapable_cmd = getOptionToString("rad3_lower_xpdr_baro_dn_cmd");
        Rad3LowrXpdrBaroDnRemapableCmd = XPLMFindCommand(rad3_lower_xpdr_baro_dn_remapable_cmd.c_str());

    }


    //  ***********************   Multi Panel Commands **************************

    readOptionAsInt("Multi Freq Knob Acceleration Threshold", &multiaccelthreshold);
    readOptionAsInt("Multi Freq Knob Pulse per Command", &multispeed, true);

    // Dynamic Trim Wheel
    readOptionAsInt("Dynamic Trim Wheel", &dynamicTrimWheel, true);

    // Dynamic Trim Max Val
    readOptionAsInt("Dynamic Trim Max Val", &dynamicTrimMaxVal, true);

    // "Dynamic Trim Min Val
    readOptionAsInt("Dynamic Trim Min Val", &dynamicTrimMinVal, true);

    // "Dynamic Trim Acceleration Point
    readOptionAsDouble("Dynamic Trim Acceleration Point", &dynamicTrimAccelerationPoint, true);

    readOptionAsInt("Multi Trim Speed", &trimspeed, true);

    sprintf(buf, "Xsaitekpanels: multispeed = %d  multiaccelthreshold = %d  trimspeed = %d  ", multispeed, multiaccelthreshold, trimspeed);
    XPLMDebugString(buf);

    float FPS = XPLMGetDataf(Frp);

    sprintf(buf, "  FPS = %f \n\n", 1 / FPS);
    XPLMDebugString(buf);

    // auto throttle switch - remapable
    readOptionAsInt("Auto Throttle Switch enable", &autothrottleswitchenable, true);

    // auto throttle switch armed value
    readOptionAsInt("Auto Throttle Switch Armed value", &autothrottleswitcharmedvalue);

    // alt switch - remapable
    readOptionAsInt("Alt Switch remapable", &altswitchremap);
    if (altswitchremap == 1) {
        alt_switch_up_remapable = getOptionToString("alt_switch_up_remapable_cmd");
        AltSwitchUpRemapableCmd = XPLMFindCommand(alt_switch_up_remapable.c_str());
        alt_switch_dn_remapable = getOptionToString("alt_switch_dn_remapable_cmd");
        AltSwitchDnRemapableCmd = XPLMFindCommand(alt_switch_dn_remapable.c_str());
        alt_switch_data_remapable = getOptionToString("alt_switch_remapable_data");
        AltSwitchRemapableData = XPLMFindDataRef(alt_switch_data_remapable.c_str());

    }
    else if (altswitchremap == 2) {
        alt_switch_data_remapable = getOptionToString("alt_switch_remapable_data");
        AltSwitchRemapableData = XPLMFindDataRef(alt_switch_data_remapable.c_str());

    }

    // vs switch - remapable
    readOptionAsInt("Vs Switch remapable", &vsswitchremap);
    if (vsswitchremap == 1) {
        vs_switch_up_remapable = getOptionToString("vs_switch_up_remapable_cmd");
        VsSwitchUpRemapableCmd = XPLMFindCommand(vs_switch_up_remapable.c_str());
        vs_switch_dn_remapable = getOptionToString("vs_switch_dn_remapable_cmd");
        VsSwitchDnRemapableCmd = XPLMFindCommand(vs_switch_dn_remapable.c_str());
        vs_switch_data_remapable = getOptionToString("vs_switch_remapable_data");
        VsSwitchRemapableData = XPLMFindDataRef(vs_switch_data_remapable.c_str());

    }
    else if (vsswitchremap == 2) {
        vs_switch_data_remapable = getOptionToString("vs_switch_remapable_data");
        VsSwitchRemapableData = XPLMFindDataRef(vs_switch_data_remapable.c_str());
    }

    // ias switch - remapable
    readOptionAsInt("Ias Switch remapable", &iasswitchremap);
    if (iasswitchremap == 1) {
        ias_switch_up_remapable = getOptionToString("ias_switch_up_remapable_cmd");
        IasSwitchUpRemapableCmd = XPLMFindCommand(ias_switch_up_remapable.c_str());
        ias_switch_dn_remapable = getOptionToString("ias_switch_dn_remapable_cmd");
        IasSwitchDnRemapableCmd = XPLMFindCommand(ias_switch_dn_remapable.c_str());
        ias_switch_data_remapable = getOptionToString("ias_switch_remapable_data");
        IasSwitchRemapableData = XPLMFindDataRef(ias_switch_data_remapable.c_str());

    }
    else if (iasswitchremap == 2) {
        ias_switch_data_remapable = getOptionToString("ias_switch_remapable_data");
        IasSwitchRemapableData = XPLMFindDataRef(ias_switch_data_remapable.c_str());
    }

    // hdg switch - remapable
    readOptionAsInt("Hdg Switch remapable", &hdgswitchremap);
    if (hdgswitchremap == 1) {
        hdg_switch_up_remapable = getOptionToString("hdg_switch_up_remapable_cmd");
        HdgSwitchUpRemapableCmd = XPLMFindCommand(hdg_switch_up_remapable.c_str());
        hdg_switch_dn_remapable = getOptionToString("hdg_switch_dn_remapable_cmd");
        HdgSwitchDnRemapableCmd = XPLMFindCommand(hdg_switch_dn_remapable.c_str());
        hdg_switch_data_remapable = getOptionToString("hdg_switch_remapable_data");
        HdgSwitchRemapableData = XPLMFindDataRef(hdg_switch_data_remapable.c_str());

    }
    else if (hdgswitchremap == 2) {
        hdg_switch_data_remapable = getOptionToString("hdg_switch_remapable_data");
        HdgSwitchRemapableData = XPLMFindDataRef(hdg_switch_data_remapable.c_str());
    }

    // crs switch - remapable
    readOptionAsInt("Crs Switch remapable", &crsswitchremap);
    if (crsswitchremap == 1) {
        crs_switch_up_remapable = getOptionToString("crs_switch_up_remapable_cmd");
        CrsSwitchUpRemapableCmd = XPLMFindCommand(crs_switch_up_remapable.c_str());
        crs_switch_dn_remapable = getOptionToString("crs_switch_dn_remapable_cmd");
        CrsSwitchDnRemapableCmd = XPLMFindCommand(crs_switch_dn_remapable.c_str());
        crs_switch_data_remapable = getOptionToString("crs_switch_remapable_data");
        CrsSwitchRemapableData = XPLMFindDataRef(crs_switch_data_remapable.c_str());

    }
    else if (crsswitchremap == 2) {
        crs_switch_data_remapable = getOptionToString("crs_switch_remapable_data");
        CrsSwitchRemapableData = XPLMFindDataRef(crs_switch_data_remapable.c_str());
    }

    // ias ismach - remapable
    readOptionAsInt("Ias Ismach remapable", &iasismachremap);
    if (iasismachremap == 1) {
        ias_ismach_remapable = getOptionToString("ias_ismach_remapable_data");
        IasIsmachRemapableData = XPLMFindDataRef(ias_ismach_remapable.c_str());
        iasismachvalue = getOptionToInt("ias_ismach_remapable_value");
    }

    // auto throttle switch - remapable (autothrottleswitchenable == 2 or 4)
    if (autothrottleswitchenable == 2 || autothrottleswitchenable == 4) {
        AttrSwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle_switch_remapable_data").c_str());
        Attr2SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle2_switch_remapable_data").c_str());
        Attr3SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle3_switch_remapable_data").c_str());
        Attr4SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle4_switch_remapable_data").c_str());
        Attr5SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle5_switch_remapable_data").c_str());
        Attr6SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle6_switch_remapable_data").c_str());
        Attr7SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle7_switch_remapable_data").c_str());
        Attr8SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle8_switch_remapable_data").c_str());
        Attr9SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle9_switch_remapable_data").c_str());
        Attr10SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle10_switch_remapable_data").c_str());
        Attr11SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle11_switch_remapable_data").c_str());
        Attr12SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle12_switch_remapable_data").c_str());
        Attr13SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle13_switch_remapable_data").c_str());
        Attr14SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle14_switch_remapable_data").c_str());
        Attr15SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle15_switch_remapable_data").c_str());
        Attr16SwitchRemapableData = XPLMFindDataRef(getOptionToString("auto_throttle16_switch_remapable_data").c_str());

        AttrSwitch_1_DataOnValue = getOptionToInt("auto_throttle_switch_remapable_data_on_value");
        AttrSwitch_1_DataOffValue = getOptionToInt("auto_throttle_switch_remapable_data_off_value");
        AttrSwitch_2_DataOnValue  = getOptionToInt("auto_throttle2_switch_remapable_data_on_value");
        AttrSwitch_2_DataOffValue = getOptionToInt("auto_throttle2_switch_remapable_data_off_value");
        AttrSwitch_3_DataOnValue = getOptionToInt("auto_throttle3_switch_remapable_data_on_value");
        AttrSwitch_3_DataOffValue = getOptionToInt("auto_throttle3_switch_remapable_data_off_value");
        AttrSwitch_4_DataOnValue = getOptionToInt("auto_throttle4_switch_remapable_data_on_value");
        AttrSwitch_4_DataOffValue = getOptionToInt("auto_throttle4_switch_remapable_data_off_value");
        AttrSwitch_5_DataOnValue = getOptionToInt("auto_throttle5_switch_remapable_data_on_value");
        AttrSwitch_5_DataOffValue = getOptionToInt("auto_throttle5_switch_remapable_data_off_value");
        AttrSwitch_6_DataOnValue = getOptionToInt("auto_throttle6_switch_remapable_data_on_value");
        AttrSwitch_6_DataOffValue = getOptionToInt("auto_throttle6_switch_remapable_data_off_value");
        AttrSwitch_7_DataOnValue = getOptionToInt("auto_throttle7_switch_remapable_data_on_value");
        AttrSwitch_7_DataOffValue = getOptionToInt("auto_throttle7_switch_remapable_data_off_value");
        AttrSwitch_8_DataOnValue = getOptionToInt("auto_throttle8_switch_remapable_data_on_value");
        AttrSwitch_8_DataOffValue = getOptionToInt("auto_throttle8_switch_remapable_data_off_value");
        AttrSwitch_9_DataOnValue = getOptionToInt("auto_throttle9_switch_remapable_data_on_value");
        AttrSwitch_9_DataOffValue = getOptionToInt("auto_throttle9_switch_remapable_data_off_value");
        AttrSwitch_10_DataOnValue = getOptionToInt("auto_throttle10_switch_remapable_data_on_value");
        AttrSwitch_10_DataOffValue = getOptionToInt("auto_throttle10_switch_remapable_data_off_value");
        AttrSwitch_11_DataOnValue = getOptionToInt("auto_throttle11_switch_remapable_data_on_value");
        AttrSwitch_11_DataOffValue = getOptionToInt("auto_throttle11_switch_remapable_data_off_value");
        AttrSwitch_12_DataOnValue = getOptionToInt("auto_throttle12_switch_remapable_data_on_value");
        AttrSwitch_12_DataOffValue = getOptionToInt("auto_throttle12_switch_remapable_data_off_value");
        AttrSwitch_13_DataOnValue = getOptionToInt("auto_throttle13_switch_remapable_data_on_value");
        AttrSwitch_13_DataOffValue = getOptionToInt("auto_throttle13_switch_remapable_data_off_value");
        AttrSwitch_14_DataOnValue = getOptionToInt("auto_throttle14_switch_remapable_data_on_value");
        AttrSwitch_14_DataOffValue = getOptionToInt("auto_throttle14_switch_remapable_data_off_value");
        AttrSwitch_15_DataOnValue = getOptionToInt("auto_throttle15_switch_remapable_data_on_value");
        AttrSwitch_15_DataOffValue = getOptionToInt("auto_throttle15_switch_remapable_data_off_value");
        AttrSwitch_16_DataOnValue = getOptionToInt("auto_throttle16_switch_remapable_data_on_value");
        AttrSwitch_16_DataOffValue = getOptionToInt("auto_throttle16_switch_remapable_data_off_value");
    }

    // auto throttle switch - remapable (autothrottleswitchenable == 3)
    if (autothrottleswitchenable == 3) {
        AttrSwitch_1_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle_switch_on_cmd").c_str());
        AttrSwitch_1_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle_switch_off_cmd").c_str());
        AttrSwitch_2_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle2_switch_on_cmd").c_str());
        AttrSwitch_2_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle2_switch_off_cmd").c_str());
        AttrSwitch_3_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle3_switch_on_cmd").c_str());
        AttrSwitch_3_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle3_switch_off_cmd").c_str());
        AttrSwitch_4_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle4_switch_on_cmd").c_str());
        AttrSwitch_4_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle4_switch_off_cmd").c_str());
        AttrSwitch_5_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle5_switch_on_cmd").c_str());
        AttrSwitch_5_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle5_switch_off_cmd").c_str());
        AttrSwitch_6_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle6_switch_on_cmd").c_str());
        AttrSwitch_6_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle6_switch_off_cmd").c_str());
        AttrSwitch_7_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle7_switch_on_cmd").c_str());
        AttrSwitch_7_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle7_switch_off_cmd").c_str());
        AttrSwitch_8_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle8_switch_on_cmd").c_str());
        AttrSwitch_8_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle8_switch_off_cmd").c_str());
        AttrSwitch_9_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle9_switch_on_cmd").c_str());
        AttrSwitch_9_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle9_switch_off_cmd").c_str());
        AttrSwitch_10_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle10_switch_on_cmd").c_str());
        AttrSwitch_10_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle10_switch_off_cmd").c_str());
        AttrSwitch_11_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle11_switch_on_cmd").c_str());
        AttrSwitch_11_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle11_switch_off_cmd").c_str());
        AttrSwitch_12_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle12_switch_on_cmd").c_str());
        AttrSwitch_12_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle12_switch_off_cmd").c_str());
        AttrSwitch_13_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle13_switch_on_cmd").c_str());
        AttrSwitch_13_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle13_switch_off_cmd").c_str());
        AttrSwitch_14_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle14_switch_on_cmd").c_str());
        AttrSwitch_14_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle14_switch_off_cmd").c_str());
        AttrSwitch_15_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle15_switch_on_cmd").c_str());
        AttrSwitch_15_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle15_switch_off_cmd").c_str());
        AttrSwitch_16_OnCmd = XPLMFindCommand(getOptionToString("auto_throttle16_switch_on_cmd").c_str());
        AttrSwitch_16_OffCmd = XPLMFindCommand(getOptionToString("auto_throttle16_switch_off_cmd").c_str());
    }


    // Light datareference type
    readOptionAsInt("Light datareference type", &lightdatareferencetype);

    // ap button - remapable
    readOptionAsInt("Ap Button remapable", &apbuttonremap);
    if (apbuttonremap == 1) {
        ap_button_remapable = getOptionToString("ap_button_remapable_cmd");
        ApButtonRemapableCmd = XPLMFindCommand(ap_button_remapable.c_str());
    }
    else if ((apbuttonremap == 2) || (apbuttonremap == 3)) {
        ap_button_data_remapable = getOptionToString("ap_button_remapable_data");
        ApButtonRemapableData = XPLMFindDataRef(ap_button_data_remapable.c_str());
    }

    // ap light - remapable
    if ((apbuttonremap == 1) || (apbuttonremap == 2) || (apbuttonremap == 3)) {
        ap_light_remapable = getOptionToString("ap_light_remapable_data");
        ApLightRemapableData = XPLMFindDataRef(ap_light_remapable.c_str());
        ap_light_flash_remapable = getOptionToString("ap_light_flash_remapable_data");
        ApLightFlashRemapableData = XPLMFindDataRef(ap_light_flash_remapable.c_str());
    }

    // hdg button - remapable
    readOptionAsInt("Hdg Button remapable", &hdgbuttonremap);
    if (hdgbuttonremap == 1) {
        hdg_button_remapable = getOptionToString("hdg_button_remapable_cmd");
        HdgButtonRemapableCmd = XPLMFindCommand(hdg_button_remapable.c_str());
    }
    else  if ((hdgbuttonremap == 2) || (hdgbuttonremap == 3)) {
        hdg_button_data_remapable = getOptionToString("hdg_button_remapable_data");
        HdgButtonRemapableData = XPLMFindDataRef(hdg_button_data_remapable.c_str());
    }

    // hdg light - remapable
    if ((hdgbuttonremap == 1) || (hdgbuttonremap == 2) || (hdgbuttonremap == 3)) {
        hdg_light_remapable = getOptionToString("hdg_light_remapable_data");
        HdgLightRemapableData = XPLMFindDataRef(hdg_light_remapable.c_str());
        hdg_light_flash_remapable = getOptionToString("hdg_light_flash_remapable_data");
        HdgLightFlashRemapableData = XPLMFindDataRef(hdg_light_flash_remapable.c_str());
    }

    // nav button - remapable
    readOptionAsInt("Nav Button remapable", &navbuttonremap);
    if (navbuttonremap == 1) {
        nav_button_vorloc_remapable = getOptionToString("nav_button_vorloc_remapable_cmd");
        NavButtonVorlocRemapableCmd = XPLMFindCommand(nav_button_vorloc_remapable.c_str());
        nav_button_lnav_remapable = getOptionToString("nav_button_lnav_remapable_cmd");
        NavButtonLnavRemapableCmd = XPLMFindCommand(nav_button_lnav_remapable.c_str());
    }
    else if ((navbuttonremap == 2) || (navbuttonremap == 3)) {
        nav_button_data_vorloc_remapable = getOptionToString("nav_button_vorloc_remapable_data");
        NavButtonVorlocRemapableData = XPLMFindDataRef(nav_button_data_vorloc_remapable.c_str());
        nav_button_data_lnav_remapable = getOptionToString("nav_button_lnav_remapable_data");
        NavButtonLnavRemapableData = XPLMFindDataRef(nav_button_data_lnav_remapable.c_str());
    }

    // nav light - remapable
    if ((navbuttonremap == 1) || (navbuttonremap == 2) || (navbuttonremap == 3)) {
        nav_light_vorloc_remapable = getOptionToString("nav_light_vorloc_remapable_data");
        NavLightVorlocRemapableData = XPLMFindDataRef(nav_light_vorloc_remapable.c_str());
        nav_light_vorloc_flash_remapable = getOptionToString("nav_light_vorloc_flash_remapable_data");
        NavLightVorlocFlashRemapableData = XPLMFindDataRef(nav_light_vorloc_flash_remapable.c_str());

        nav_light_lnav_remapable = getOptionToString("nav_light_lnav_remapable_data");
        NavLightLnavRemapableData = XPLMFindDataRef(nav_light_lnav_remapable.c_str());
        nav_light_lnav_flash_remapable = getOptionToString("nav_light_lnav_flash_remapable_data");
        NavLightLnavFlashRemapableData = XPLMFindDataRef(nav_light_lnav_flash_remapable.c_str());
    }


    // ias button - remapable
    readOptionAsInt("Ias Button remapable", &iasbuttonremap);
    if (iasbuttonremap == 1) {
        ias_button_remapable = getOptionToString("ias_button_remapable_cmd");
        IasButtonRemapableCmd = XPLMFindCommand(ias_button_remapable.c_str());
        ias_changeover_button_remapable = getOptionToString("ias_changeover_button_remapable_cmd");
        IasChangeoverButtonRemapableCmd = XPLMFindCommand(ias_changeover_button_remapable.c_str());
    }
    else if ((iasbuttonremap == 2) || (iasbuttonremap == 3)) {
        ias_button_data_remapable = getOptionToString("ias_button_remapable_data");
        IasButtonRemapableData = XPLMFindDataRef(ias_button_data_remapable.c_str());
        ias_changeover_button_data_remapable = getOptionToString("ias_changeover_button_remapable_data");
        IasChangeoverButtonRemapableData = XPLMFindDataRef(ias_changeover_button_data_remapable.c_str());
    }

    // ias light - remapable
    if ((iasbuttonremap == 1) || (iasbuttonremap == 2) || (iasbuttonremap == 3)) {
        ias_light_remapable = getOptionToString("ias_light_remapable_data");
        IasLightRemapableData = XPLMFindDataRef(ias_light_remapable.c_str());
        ias_light_flash_remapable = getOptionToString("ias_light_flash_remapable_data");
        IasLightFlashRemapableData = XPLMFindDataRef(ias_light_flash_remapable.c_str());
    }


    // alt button - remapable
    readOptionAsInt("Alt Button remapable", &altbuttonremap);
    if (altbuttonremap == 1) {
        alt_button_remapable = getOptionToString("alt_button_remapable_cmd");
        AltButtonRemapableCmd = XPLMFindCommand(alt_button_remapable.c_str());
    }
    else if ((altbuttonremap == 2) || (altbuttonremap == 3)) {
        alt_button_data_remapable = getOptionToString("alt_button_remapable_data");
        AltButtonRemapableData = XPLMFindDataRef(alt_button_data_remapable.c_str());
    }

    // alt light - remapable
    if ((altbuttonremap == 1) || (altbuttonremap == 2) || (altbuttonremap == 3)) {
        alt_light_remapable = getOptionToString("alt_light_remapable_data");
        AltLightRemapableData = XPLMFindDataRef(alt_light_remapable.c_str());
        alt_light_flash_remapable = getOptionToString("alt_light_flash_remapable_data");
        AltLightFlashRemapableData = XPLMFindDataRef(alt_light_flash_remapable.c_str());
    }

    // vs button - remapable
    readOptionAsInt("Vs Button remapable", &vsbuttonremap);
    if (vsbuttonremap == 1) {
        vs_button_remapable = getOptionToString("vs_button_remapable_cmd");
        VsButtonRemapableCmd = XPLMFindCommand(vs_button_remapable.c_str());
    }
    else if ((vsbuttonremap == 2) || (vsbuttonremap == 3)) {
        vs_button_data_remapable = getOptionToString("vs_button_remapable_data");
        VsButtonRemapableData = XPLMFindDataRef(vs_button_data_remapable.c_str());
    }

    // vs light - remapable
    if ((vsbuttonremap == 1) || (vsbuttonremap == 2) || (vsbuttonremap == 3)) {
        vs_light_remapable = getOptionToString("vs_light_remapable_data");
        VsLightRemapableData = XPLMFindDataRef(vs_light_remapable.c_str());
        vs_light_flash_remapable = getOptionToString("vs_light_flash_remapable_data");
        VsLightFlashRemapableData = XPLMFindDataRef(vs_light_flash_remapable.c_str());
    }

    // apr button - remapable
    readOptionAsInt("Apr Button remapable", &aprbuttonremap);
    if (aprbuttonremap == 1) {
        apr_button_remapable = getOptionToString("apr_button_remapable_cmd");
        AprButtonRemapableCmd = XPLMFindCommand(apr_button_remapable.c_str());
    }
    else  if ((aprbuttonremap == 2) || (aprbuttonremap == 3)) {
        apr_button_data_remapable = getOptionToString("apr_button_remapable_data");
        AprButtonRemapableData = XPLMFindDataRef(apr_button_data_remapable.c_str());
    }

    // apr light - remapable
    if ((aprbuttonremap == 1) || (aprbuttonremap == 2) || (aprbuttonremap == 3)) {
        apr_light_remapable = getOptionToString("apr_light_remapable_data");
        AprLightRemapableData = XPLMFindDataRef(apr_light_remapable.c_str());
        apr_light_flash_remapable = getOptionToString("apr_light_flash_remapable_data");
        AprLightFlashRemapableData = XPLMFindDataRef(apr_light_flash_remapable.c_str());
    }

    // rev button - remapable
    readOptionAsInt("Rev Button remapable", &revbuttonremap);
    if (revbuttonremap == 1) {
        rev_button_remapable = getOptionToString("rev_button_remapable_cmd");
        RevButtonRemapableCmd = XPLMFindCommand(rev_button_remapable.c_str());
    }
    else if ((revbuttonremap == 2) || (revbuttonremap == 3)) {
        rev_button_data_remapable = getOptionToString("rev_button_remapable_data");
        RevButtonRemapableData = XPLMFindDataRef(rev_button_data_remapable.c_str());
    }

    // rev light - remapable
    if ((revbuttonremap == 1) || (revbuttonremap == 2) || (revbuttonremap == 3)) {
        rev_light_remapable = getOptionToString("rev_light_remapable_data");
        RevLightRemapableData = XPLMFindDataRef(rev_light_remapable.c_str());
        rev_light_flash_remapable = getOptionToString("rev_light_flash_remapable_data");
        RevLightFlashRemapableData = XPLMFindDataRef(rev_light_flash_remapable.c_str());
    }

    // trim up - remapable
    readOptionAsInt("Trim Up remapable", &trimupremap);
    if (trimupremap == 1) {
        trim_up_remapable = getOptionToString("trim_up_remapable_cmd");
        TrimUpRemapableCmd = XPLMFindCommand(trim_up_remapable.c_str());
    }

    // trim dn - remapable
    readOptionAsInt("Trim Dn remapable", &trimdnremap);
    if (trimdnremap == 1) {
        trim_dn_remapable = getOptionToString("trim_dn_remapable_cmd");
        TrimDnRemapableCmd = XPLMFindCommand(trim_dn_remapable.c_str());
    }


    // flaps up - remapable
    readOptionAsInt("Flaps Up remapable", &flapsupremap);
    if (flapsupremap == 1) {
        flaps_up_remapable = getOptionToString("flaps_up_remapable_cmd");
        FlapsUpRemapableCmd = XPLMFindCommand(flaps_up_remapable.c_str());
    }

    // flaps dn - remapable
    readOptionAsInt("Flaps Dn remapable", &flapsdnremap);
    if (flapsdnremap == 1) {
        flaps_dn_remapable = getOptionToString("flaps_dn_remapable_cmd");
        FlapsDnRemapableCmd = XPLMFindCommand(flaps_dn_remapable.c_str());
    }

    readOptionAsInt("Battery Power On", &BatPwrOnConfig);
    if (BatPwrOnConfig == 2) {
        BatPwrOnCustomDataref = XPLMFindDataRef(getOptionToString(
            "battery_power_on_remapable_data").c_str());
    }

    readOptionAsInt("Avionics Power On", &AvPwrOnConfig);
    if (AvPwrOnConfig == 2) {
        AvPwrOnCustomDataref = XPLMFindDataRef(getOptionToString(
            "avionics_power_on_remapable_data").c_str());
    }

    UpdateUI();

    return;
}
