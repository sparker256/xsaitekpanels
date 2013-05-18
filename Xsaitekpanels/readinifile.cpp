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

    char seperator_number_buffer[255] = {0};

    std::size_t len = in_path.length();
    std::size_t pos = in_path.find(":");

    in_path.erase (in_path.begin()+0, in_path.end()-(len - pos));

    int count = 0;
    for (int i = 0; i < in_path.size(); i++)
       if (in_path[i] == ':') count++;
            // sprintf(seperator_number_buffer, "Xsaitekpanels: How many path seperators are in the path = %d\n", count);
            // XPLMDebugString(seperator_number_buffer);

    size_t found;
    int n = count;

    while (n>0) {
       found = in_path.find(":");
       in_path.replace(found, 1,"/");
       --n;
    }

    std::size_t pos2 = in_path.find("/Aircraft");
    std::string tmp_in_path = in_path.substr (pos2);
    tmp_in_path.insert(0,".");
    in_path = tmp_in_path;

    return in_path;
}

// ***** Configuration File Process ******
void process_read_ini_file()

{

    char *iniDefaultPluginPath;
    //const char *defaultConfigFileName;

    iniDefaultPluginPath = "./Resources/plugins/Xsaitekpanels/xsaitekpanels.ini";
    //defaultConfigFileName = "xsaitekpanels.ini";
    int Index2;
    string version;

    /* set defaults */

        // switch panel defaults

    // switches
    magoffswitchenable           = 1;
    magrightswitchenable         = 1;
    magleftswitchenable          = 1;
    magbothswitchenable          = 1;
    magstartswitchenable         = 1;
    batmasterswitchenable        = 1;
    altmasterswitchenable        = 1;
    avionicsmasterswitchenable   = 1;
    fuelpumpswitchenable         = 1;
    deiceswitchenable            = 1;
    pitotheatswitchenable        = 1;
    landinggearknobupenable      = 1;
    landinggearknobdnenable      = 1;
    cowlflapsenable              = 1;
    panellightswitchenable       = 1;
    beaconlightswitchenable      = 1;
    navlightswitchenable         = 1;
    strobelightswitchenable      = 1;
    taxilightswitchenable        = 1;
    landinglightswitchenable     = 1;

    bataltinverse = 0;
    starterswitchenable = 0;

    // radio panel defaults
    radspeed                 = 3;
    numadf                   = 1;
    metricpressenable        = 0;
    rad1uprcom1switchremap   = 0, rad1uprcom1actstbybtnremap   = 0;
    rad1lwrcom1switchremap   = 0, rad1lwrcom1actstbybtnremap   = 0;
    rad1uprcom2switchremap   = 0, rad1uprcom2actstbybtnremap   = 0;
    rad1lwrcom2switchremap   = 0, rad1lwrcom2actstbybtnremap   = 0;
    rad1uprnav1switchremap   = 0, rad1uprnav1actstbybtnremap   = 0;
    rad1lwrnav1switchremap   = 0, rad1lwrnav1actstbybtnremap   = 0;
    rad1uprnav2switchremap   = 0, rad1uprnav2actstbybtnremap   = 0;
    rad1lwrnav2switchremap   = 0, rad1lwrnav2actstbybtnremap   = 0;


    rad2uprcom1switchremap   = 0, rad2uprcom1actstbybtnremap   = 0;
    rad2lwrcom1switchremap   = 0, rad2lwrcom1actstbybtnremap   = 0;
    rad2uprcom2switchremap   = 0, rad2uprcom2actstbybtnremap   = 0;
    rad2lwrcom2switchremap   = 0, rad2lwrcom2actstbybtnremap   = 0;
    rad2uprnav1switchremap   = 0, rad2uprnav1actstbybtnremap   = 0;
    rad2lwrnav1switchremap   = 0, rad2lwrnav1actstbybtnremap   = 0;
    rad2uprnav2switchremap   = 0, rad2uprnav2actstbybtnremap   = 0;
    rad2lwrnav2switchremap   = 0, rad2lwrnav2actstbybtnremap   = 0;


    if (numadf == 1) {
         XPSetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonState, 1);
    }

    // multi panel defaults
    trimspeed                = 1;
    multispeed               = 3;
    iasismachremap           = 0;
    iasismachvalue           = 1;

    altswitchremap          = 0;
    vsswitchremap           = 0;
    iasswitchremap          = 0;
    hdgswitchremap          = 0;
    crsswitchremap          = 0;

    autothrottleswitchenable = 1;
    autothrottleswitcharmedvalue = 1;

    trimupremap             = 0;
    trimdnremap             = 0;

    lightdatareferencetype  = 0;

    apbuttonremap           = 0;
    hdgbuttonremap          = 0;
    navbuttonremap          = 0;
    iasbuttonremap          = 0;
    altbuttonremap          = 0;
    vsbuttonremap           = 0;
    aprbuttonremap          = 0;
    revbuttonremap          = 0;

    //char *configPath;

    cleanupIniReader();

    char xpsacfname[512];
    char xpsacfpath[512];
    XPLMGetNthAircraftModel(0, xpsacfname, xpsacfpath);

    XPLMDebugString("\nXsaitekpanels: Raw Current aircraft path is \n");
    XPLMDebugString(xpsacfpath);
    XPLMDebugString("\n");

    if(strlen(xpsacfpath) == 0){
      return;
    }

    std::string xpsini_path_name = xpsacfpath;
    std::size_t pos = xpsini_path_name.find(xpsacfname);
    xpsini_path_name = xpsini_path_name.substr(0, pos);

    #if APL && __MACH__
        std::string mac_converted_path = convert_Mac_Path(xpsini_path_name);
        XPLMDebugString("\nXsaitekpanels: mac_converted_path is \n");
        XPLMDebugString(mac_converted_path.c_str());
        XPLMDebugString("\n");
        //mac_converted_path = "./Aircraft/General Aviation/KingAir C90B/";
        xpsini_path_name = mac_converted_path;
    #endif

    xpsini_path_name.append("xsaitekpanels.ini");

    XPLMDebugString("\nXsaitekpanels: The full path to xsaitekpanels.ini in the current aircraft folder is \n");
    XPLMDebugString(xpsini_path_name.c_str());
    XPLMDebugString("\n");

    std::vector<char> parse_ini_path_name(xpsini_path_name.size() + 1);
    std::copy(xpsini_path_name.begin(), xpsini_path_name.end(), parse_ini_path_name.begin());

    std::ifstream ifile(&parse_ini_path_name[0]);
    if (ifile) {
        XPLMDebugString("\nXsaitekpanels: Found xsaitekpanels.ini in the current aircraft path and it is\n");
        XPLMDebugString(&parse_ini_path_name[0]);
        XPLMDebugString("\n");

        parseIniFile(&parse_ini_path_name[0]);

    } else {
        std::ifstream ifile(iniDefaultPluginPath);
       if (ifile) {
           XPLMDebugString("\nXsaitekpanels: Found xsaitekpanels.ini in the Xsaitekpanels plugin path and it is\n");
           XPLMDebugString(iniDefaultPluginPath);
           XPLMDebugString("\n");

           parseIniFile(iniDefaultPluginPath);

       } else {
           return;
       }
    }

    // get xsaitekpanels.ini version
    version = getOptionToString("Version");
    XPLMDebugString("\nXsaitekpanels: xsaitekpanels.ini is version   ");
    XPLMDebugString(version.c_str());
    XPLMDebugString("\n");

    // bat alt normal alt bat cessna
    bataltinverse = getOptionToInt("Bat Alt inverse");
    if (bataltinverse == 0) {
        XPSetWidgetProperty(SwitchBatAltCheckWidget[0], xpProperty_ButtonState, 1);
        XPSetWidgetProperty(SwitchAltBatCheckWidget[0], xpProperty_ButtonState, 0);

    }

    if (bataltinverse == 1) {
        XPSetWidgetProperty(SwitchBatAltCheckWidget[0], xpProperty_ButtonState, 0);
        XPSetWidgetProperty(SwitchAltBatCheckWidget[0], xpProperty_ButtonState, 1);

    }

    // Starter Switch Old/New Style
    starterswitchenable = getOptionToInt("Starter Old New");
    if (starterswitchenable == 0) {
        XPSetWidgetProperty(SwitchStartSwitchOldCheckWidget[0], xpProperty_ButtonState, 1);
        XPSetWidgetProperty(SwitchStartSwitchNewCheckWidget[0], xpProperty_ButtonState, 0);

    }

    if (starterswitchenable == 1) {
        XPSetWidgetProperty(SwitchStartSwitchOldCheckWidget[0], xpProperty_ButtonState, 0);
        XPSetWidgetProperty(SwitchStartSwitchNewCheckWidget[0], xpProperty_ButtonState, 1);

    }

    for (Index2=0; Index2 < 19; Index2++)
    {
        XPSetWidgetProperty(SwitchDisableCheckWidget[Index2], xpProperty_ButtonState, 0);
        XPSetWidgetProperty(SwitchEnableCheckWidget[Index2], xpProperty_ButtonState, 0);
        XPSetWidgetProperty(SwitchRemapCheckWidget[Index2], xpProperty_ButtonState, 0);
    }

    // mag off switch disable - enable - remap
    magoffswitchenable = getOptionToInt("Mag Off Switch enable");
    if (magoffswitchenable == 0) {
        XPSetWidgetProperty(SwitchDisableCheckWidget[0], xpProperty_ButtonState, 1);
    }

    if (magoffswitchenable == 1) {
        XPSetWidgetProperty(SwitchEnableCheckWidget[0], xpProperty_ButtonState, 1);
    }

    if (magoffswitchenable == 2) {
        XPSetWidgetProperty(SwitchRemapCheckWidget[0], xpProperty_ButtonState, 1);
        mag_off_switch_on = getOptionToString("mag_off_switch_on_cmd");
        mag_off_switch_off = getOptionToString("mag_off_switch_off_cmd");
        MagOffSwitchOnCmd   = XPLMFindCommand(mag_off_switch_on.c_str());
        MagOffSwitchOffCmd   = XPLMFindCommand(mag_off_switch_off.c_str());
    }

    if (magoffswitchenable == 3) {
        mag_off_switch_data = getOptionToString("mag_off_switch_data");
        MagOffSwitchData   = XPLMFindDataRef(mag_off_switch_data.c_str());
        mag_off_switch_data_on_value = getOptionToInt("mag_off_switch_data_on_value");
        mag_off_switch_data_off_value = getOptionToInt("mag_off_switch_data_off_value");

        mag_off2_switch_data = getOptionToString("mag_off2_switch_data");
        MagOff2SwitchData   = XPLMFindDataRef(mag_off2_switch_data.c_str());
        mag_off2_switch_data_on_value = getOptionToInt("mag_off2_switch_data_on_value");
        mag_off2_switch_data_off_value = getOptionToInt("mag_off2_switch_data_off_value");

        mag_off3_switch_data = getOptionToString("mag_off3_switch_data");
        MagOff3SwitchData   = XPLMFindDataRef(mag_off3_switch_data.c_str());
        mag_off3_switch_data_on_value = getOptionToInt("mag_off3_switch_data_on_value");
        mag_off3_switch_data_off_value = getOptionToInt("mag_off3_switch_data_off_value");

        mag_off4_switch_data = getOptionToString("mag4_off_switch_data");
        MagOff4SwitchData   = XPLMFindDataRef(mag_off4_switch_data.c_str());
        mag_off4_switch_data_on_value = getOptionToInt("mag_off4_switch_data_on_value");
        mag_off4_switch_data_off_value = getOptionToInt("mag_off4_switch_data_off_value");
    }


    // mag right switch disable - enable - remap
    magrightswitchenable = getOptionToInt("Mag Right Switch enable");
    if (magrightswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[1], xpProperty_ButtonState, 1);
    }

    if (magrightswitchenable == 1) {
            XPSetWidgetProperty(SwitchEnableCheckWidget[1], xpProperty_ButtonState, 1);
    }

    if (magrightswitchenable == 2) {
            XPSetWidgetProperty(SwitchRemapCheckWidget[1], xpProperty_ButtonState, 1);
            mag_right_switch_on = getOptionToString("mag_right_switch_on_cmd");
            mag_right_switch_off = getOptionToString("mag_right_switch_off_cmd");
            MagRightSwitchOnCmd   = XPLMFindCommand(mag_right_switch_on.c_str());
            MagRightSwitchOffCmd   = XPLMFindCommand(mag_right_switch_off.c_str());
    }

    if (magrightswitchenable == 3) {
        mag_right_switch_data = getOptionToString("mag_right_switch_data");
        MagRightSwitchData   = XPLMFindDataRef(mag_right_switch_data.c_str());
        mag_right_switch_data_on_value = getOptionToInt("mag_right_switch_data_on_value");
        mag_right_switch_data_off_value = getOptionToInt("mag_right_switch_data_off_value");

        mag_right2_switch_data = getOptionToString("mag_right2_switch_data");
        MagRight2SwitchData   = XPLMFindDataRef(mag_right2_switch_data.c_str());
        mag_right2_switch_data_on_value = getOptionToInt("mag_right2_switch_data_on_value");
        mag_right2_switch_data_off_value = getOptionToInt("mag_right2_switch_data_off_value");

        mag_right3_switch_data = getOptionToString("mag_right3_switch_data");
        MagRight3SwitchData   = XPLMFindDataRef(mag_right3_switch_data.c_str());
        mag_right3_switch_data_on_value = getOptionToInt("mag_right3_switch_data_on_value");
        mag_right3_switch_data_off_value = getOptionToInt("mag_right3_switch_data_off_value");

        mag_right4_switch_data = getOptionToString("mag_right4_switch_data");
        MagRight4SwitchData   = XPLMFindDataRef(mag_right4_switch_data.c_str());
        mag_right4_switch_data_on_value = getOptionToInt("mag_right4_switch_data_on_value");
        mag_right4_switch_data_off_value = getOptionToInt("mag_right4_switch_data_off_value");


    }

    // mag left switch disable - enable - remap
    magleftswitchenable = getOptionToInt("Mag Left Switch enable");
    if (magleftswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[2], xpProperty_ButtonState, 1);
    }

    if (magleftswitchenable == 1) {
            XPSetWidgetProperty(SwitchEnableCheckWidget[2], xpProperty_ButtonState, 1);
    }

    if (magleftswitchenable == 2) {
            XPSetWidgetProperty(SwitchRemapCheckWidget[2], xpProperty_ButtonState, 1);
            mag_left_switch_on = getOptionToString("mag_left_switch_on_cmd");
            mag_left_switch_off = getOptionToString("mag_left_switch_off_cmd");
            MagLeftSwitchOnCmd   = XPLMFindCommand(mag_left_switch_on.c_str());
            MagLeftSwitchOffCmd   = XPLMFindCommand(mag_left_switch_off.c_str());
    }

    if (magleftswitchenable == 3) {
        mag_left_switch_data = getOptionToString("mag_left_switch_data");
        MagLeftSwitchData   = XPLMFindDataRef(mag_left_switch_data.c_str());
        mag_left_switch_data_on_value = getOptionToInt("mag_left_switch_data_on_value");
        mag_left_switch_data_off_value = getOptionToInt("mag_left_switch_data_off_value");

        mag_left2_switch_data = getOptionToString("mag_left2_switch_data");
        MagLeft2SwitchData   = XPLMFindDataRef(mag_left2_switch_data.c_str());
        mag_left2_switch_data_on_value = getOptionToInt("mag_left2_switch_data_on_value");
        mag_left2_switch_data_off_value = getOptionToInt("mag_left2_switch_data_off_value");

        mag_left3_switch_data = getOptionToString("mag_left3_switch_data");
        MagLeft3SwitchData   = XPLMFindDataRef(mag_left3_switch_data.c_str());
        mag_left3_switch_data_on_value = getOptionToInt("mag_left3_switch_data_on_value");
        mag_left3_switch_data_off_value = getOptionToInt("mag_left3_switch_data_off_value");

        mag_left4_switch_data = getOptionToString("mag_left4_switch_data");
        MagLeft4SwitchData   = XPLMFindDataRef(mag_left4_switch_data.c_str());
        mag_left4_switch_data_on_value = getOptionToInt("mag_left4_switch_data_on_value");
        mag_left4_switch_data_off_value = getOptionToInt("mag_left4_switch_data_off_value");
    }



    // mag both switch disable - enable - remap
    magbothswitchenable = getOptionToInt("Mag Both Switch enable");
    if (magbothswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[3], xpProperty_ButtonState, 1);
    }

    if (magbothswitchenable == 1) {

            XPSetWidgetProperty(SwitchEnableCheckWidget[3], xpProperty_ButtonState, 1);
    }

    if (magbothswitchenable == 2) {
            XPSetWidgetProperty(SwitchRemapCheckWidget[3], xpProperty_ButtonState, 1);
            mag_both_switch_on = getOptionToString("mag_both_switch_on_cmd");
            mag_both_switch_off = getOptionToString("mag_both_switch_off_cmd");
            MagBothSwitchOnCmd   = XPLMFindCommand(mag_both_switch_on.c_str());
            MagBothSwitchOffCmd   = XPLMFindCommand(mag_both_switch_off.c_str());
    }

    if (magbothswitchenable == 3) {
        mag_both_switch_data = getOptionToString("mag_both_switch_data");
        MagBothSwitchData   = XPLMFindDataRef(mag_both_switch_data.c_str());
        mag_both_switch_data_on_value = getOptionToInt("mag_both_switch_data_on_value");
        mag_both_switch_data_off_value = getOptionToInt("mag_both_switch_data_off_value");

        mag_both2_switch_data = getOptionToString("mag_both2_switch_data");
        MagBoth2SwitchData   = XPLMFindDataRef(mag_both2_switch_data.c_str());
        mag_both2_switch_data_on_value = getOptionToInt("mag_both2_switch_data_on_value");
        mag_both2_switch_data_off_value = getOptionToInt("mag_both2_switch_data_off_value");

        mag_both3_switch_data = getOptionToString("mag_both3_switch_data");
        MagBoth3SwitchData   = XPLMFindDataRef(mag_both3_switch_data.c_str());
        mag_both3_switch_data_on_value = getOptionToInt("mag_both3_switch_data_on_value");
        mag_both3_switch_data_off_value = getOptionToInt("mag_both3_switch_data_off_value");

        mag_both4_switch_data = getOptionToString("mag_both4_switch_data");
        MagBoth4SwitchData   = XPLMFindDataRef(mag_both4_switch_data.c_str());
        mag_both4_switch_data_on_value = getOptionToInt("mag_both4_switch_data_on_value");
        mag_both4_switch_data_off_value = getOptionToInt("mag_both4_switch_data_off_value");
    }


    // mag start switch disable - enable - remap
    magstartswitchenable = getOptionToInt("Mag Start Switch enable");
    if (magstartswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[4], xpProperty_ButtonState, 1);
    }

    if (magstartswitchenable == 1) {
             XPSetWidgetProperty(SwitchEnableCheckWidget[4], xpProperty_ButtonState, 1);
      }

    if (magstartswitchenable == 2) {

            XPSetWidgetProperty(SwitchRemapCheckWidget[4], xpProperty_ButtonState, 1);
            mag_start_switch_on = getOptionToString("mag_start_switch_on_cmd");
            mag_start_switch_off = getOptionToString("mag_start_switch_off_cmd");
            MagStartSwitchOnCmd   = XPLMFindCommand(mag_start_switch_on.c_str());
            MagStartSwitchOffCmd   = XPLMFindCommand(mag_start_switch_off.c_str());
    }

    if (magstartswitchenable == 3) {
        mag_start_switch_data = getOptionToString("mag_start_switch_data");
        MagStartSwitchData   = XPLMFindDataRef(mag_start_switch_data.c_str());
        mag_start_switch_data_on_value = getOptionToInt("mag_start_switch_data_on_value");
        mag_start_switch_data_off_value = getOptionToInt("mag_start_switch_data_off_value");

        mag_start2_switch_data = getOptionToString("mag_start2_switch_data");
        MagStart2SwitchData   = XPLMFindDataRef(mag_start2_switch_data.c_str());
        mag_start2_switch_data_on_value = getOptionToInt("mag_start2_switch_data_on_value");
        mag_start2_switch_data_off_value = getOptionToInt("mag_start2_switch_data_off_value");

        mag_start3_switch_data = getOptionToString("mag_start3_switch_data");
        MagStart3SwitchData   = XPLMFindDataRef(mag_start3_switch_data.c_str());
        mag_start3_switch_data_on_value = getOptionToInt("mag_start3_switch_data_on_value");
        mag_start3_switch_data_off_value = getOptionToInt("mag_start3_switch_data_off_value");

        mag_start4_switch_data = getOptionToString("mag_start4_switch_data");
        MagStart4SwitchData   = XPLMFindDataRef(mag_start4_switch_data.c_str());
        mag_start4_switch_data_on_value = getOptionToInt("mag_start4_switch_data_on_value");
        mag_start4_switch_data_off_value = getOptionToInt("mag_start4_switch_data_off_value");
    }

    // bat master switch disable - enable - remap
    batmasterswitchenable = getOptionToInt("Bat Master Switch enable");
    if (batmasterswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[5], xpProperty_ButtonState, 1);
    }

    if (batmasterswitchenable == 1) {
            XPSetWidgetProperty(SwitchEnableCheckWidget[5], xpProperty_ButtonState, 1);
    }

    if (batmasterswitchenable == 2) {
            XPSetWidgetProperty(SwitchRemapCheckWidget[5], xpProperty_ButtonState, 1);
            bat_master_switch_on = getOptionToString("bat_master_switch_on_cmd");
            bat_master_switch_off = getOptionToString("bat_master_switch_cmd");
            BatMasterSwitchOnCmd   = XPLMFindCommand(bat_master_switch_on.c_str());
            BatMasterSwitchOffCmd   = XPLMFindCommand(bat_master_switch_off.c_str());


    }

    if (batmasterswitchenable == 3) {
            bat_master_switch_data = getOptionToString("bat_master_switch_data");
            BatMasterSwitchData   = XPLMFindDataRef(bat_master_switch_data.c_str());
            bat_master_switch_data_on_value = getOptionToInt("bat_master_switch_data_on_value");
            bat_master_switch_data_off_value = getOptionToInt("bat_master_switch_data_off_value");

            bat2_master_switch_data = getOptionToString("bat2_master_switch_data");
            Bat2MasterSwitchData   = XPLMFindDataRef(bat2_master_switch_data.c_str());
            bat2_master_switch_data_on_value = getOptionToInt("bat2_master_switch_data_on_value");
            bat2_master_switch_data_off_value = getOptionToInt("bat2_master_switch_data_off_value");

            bat3_master_switch_data = getOptionToString("bat3_master_switch_data");
            Bat3MasterSwitchData   = XPLMFindDataRef(bat3_master_switch_data.c_str());
            bat3_master_switch_data_on_value = getOptionToInt("bat3_master_switch_data_on_value");
            bat3_master_switch_data_off_value = getOptionToInt("bat3_master_switch_data_off_value");

            bat4_master_switch_data = getOptionToString("bat4_master_switch_data");
            Bat4MasterSwitchData   = XPLMFindDataRef(bat4_master_switch_data.c_str());
            bat4_master_switch_data_on_value = getOptionToInt("bat4_master_switch_data_on_value");
            bat4_master_switch_data_off_value = getOptionToInt("bat4_master_switch_data_off_value");

            bat5_master_switch_data = getOptionToString("bat5_master_switch_data");
            Bat5MasterSwitchData   = XPLMFindDataRef(bat5_master_switch_data.c_str());
            bat5_master_switch_data_on_value = getOptionToInt("bat5_master_switch_data_on_value");
            bat5_master_switch_data_off_value = getOptionToInt("bat5_master_switch_data_off_value");

            bat6_master_switch_data = getOptionToString("bat6_master_switch_data");
            Bat6MasterSwitchData   = XPLMFindDataRef(bat6_master_switch_data.c_str());
            bat6_master_switch_data_on_value = getOptionToInt("bat6_master_switch_data_on_value");
            bat6_master_switch_data_off_value = getOptionToInt("bat6_master_switch_data_off_value");

            bat7_master_switch_data = getOptionToString("bat7_master_switch_data");
            Bat7MasterSwitchData   = XPLMFindDataRef(bat7_master_switch_data.c_str());
            bat7_master_switch_data_on_value = getOptionToInt("bat7_master_switch_data_on_value");
            bat7_master_switch_data_off_value = getOptionToInt("bat7_master_switch_data_off_value");

            bat8_master_switch_data = getOptionToString("bat8_master_switch_data");
            Bat8MasterSwitchData   = XPLMFindDataRef(bat8_master_switch_data.c_str());
            bat8_master_switch_data_on_value = getOptionToInt("bat8_master_switch_data_on_value");
            bat8_master_switch_data_off_value = getOptionToInt("bat8_master_switch_data_off_value");


    }


    // alt master switch disable - enable - remap
    altmasterswitchenable = getOptionToInt("Alt Master Switch enable");
    if (altmasterswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[6], xpProperty_ButtonState, 1);

    }

    if (altmasterswitchenable == 1) {
            XPSetWidgetProperty(SwitchEnableCheckWidget[6], xpProperty_ButtonState, 1);
     }

    if (altmasterswitchenable == 2) {
            XPSetWidgetProperty(SwitchRemapCheckWidget[6], xpProperty_ButtonState, 1);
            alt_master_switch_on = getOptionToString("alt_master_switch_on_cmd");
            alt_master_switch_off = getOptionToString("alt_master_switch_off_cmd");
            AltMasterSwitchOnCmd   = XPLMFindCommand(alt_master_switch_on.c_str());
            AltMasterSwitchOffCmd   = XPLMFindCommand(alt_master_switch_off.c_str());
    }

    if (altmasterswitchenable == 3) {
            alt_master_switch_data = getOptionToString("alt_master_switch_data");
            AltMasterSwitchData   = XPLMFindDataRef(alt_master_switch_data.c_str());
            alt_master_switch_data_on_value = getOptionToInt("alt_master_switch_data_on_value");
            alt_master_switch_data_off_value = getOptionToInt("alt_master_switch_data_off_value");

            alt2_master_switch_data = getOptionToString("alt2_master_switch_data");
            Alt2MasterSwitchData   = XPLMFindDataRef(alt2_master_switch_data.c_str());
            alt2_master_switch_data_on_value = getOptionToInt("alt2_master_switch_data_on_value");
            alt2_master_switch_data_off_value = getOptionToInt("alt2_master_switch_data_off_value");

            alt3_master_switch_data = getOptionToString("alt3_master_switch_data");
            Alt3MasterSwitchData   = XPLMFindDataRef(alt3_master_switch_data.c_str());
            alt3_master_switch_data_on_value = getOptionToInt("alt3_master_switch_data_on_value");
            alt3_master_switch_data_off_value = getOptionToInt("alt3_master_switch_data_off_value");

            alt4_master_switch_data = getOptionToString("alt4_master_switch_data");
            Alt4MasterSwitchData   = XPLMFindDataRef(alt4_master_switch_data.c_str());
            alt4_master_switch_data_on_value = getOptionToInt("alt4_master_switch_data_on_value");
            alt4_master_switch_data_off_value = getOptionToInt("alt4_master_switch_data_off_value");

            alt5_master_switch_data = getOptionToString("alt5_master_switch_data");
            Alt5MasterSwitchData   = XPLMFindDataRef(alt5_master_switch_data.c_str());
            alt5_master_switch_data_on_value = getOptionToInt("alt5_master_switch_data_on_value");
            alt5_master_switch_data_off_value = getOptionToInt("alt5_master_switch_data_off_value");

            alt6_master_switch_data = getOptionToString("alt6_master_switch_data");
            Alt6MasterSwitchData   = XPLMFindDataRef(alt6_master_switch_data.c_str());
            alt6_master_switch_data_on_value = getOptionToInt("alt6_master_switch_data_on_value");
            alt6_master_switch_data_off_value = getOptionToInt("alt6_master_switch_data_off_value");

            alt7_master_switch_data = getOptionToString("alt7_master_switch_data");
            Alt7MasterSwitchData   = XPLMFindDataRef(alt7_master_switch_data.c_str());
            alt7_master_switch_data_on_value = getOptionToInt("alt7_master_switch_data_on_value");
            alt7_master_switch_data_off_value = getOptionToInt("alt7_master_switch_data_off_value");

            alt8_master_switch_data = getOptionToString("alt8_master_switch_data");
            Alt8MasterSwitchData   = XPLMFindDataRef(alt8_master_switch_data.c_str());
            alt8_master_switch_data_on_value = getOptionToInt("alt8_master_switch_data_on_value");
            alt8_master_switch_data_off_value = getOptionToInt("alt8_master_switch_data_off_value");
    }

    // avionics master switch disable - enable - remap
    avionicsmasterswitchenable = getOptionToInt("Avionics master Switch enable");
    if (avionicsmasterswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[7], xpProperty_ButtonState, 1);
    }

    if (avionicsmasterswitchenable == 1) {
            XPSetWidgetProperty(SwitchEnableCheckWidget[7], xpProperty_ButtonState, 1);
    }

    if (avionicsmasterswitchenable == 2) {
            XPSetWidgetProperty(SwitchRemapCheckWidget[7], xpProperty_ButtonState, 1);
            av_master_switch_on = getOptionToString("av_master_switch_on_cmd");
            av_master_switch_off = getOptionToString("av_master_switch_off_cmd");
            AvMasterSwitchOnCmd   = XPLMFindCommand(av_master_switch_on.c_str());
            AvMasterSwitchOffCmd   = XPLMFindCommand(av_master_switch_off.c_str());
    }

    if (avionicsmasterswitchenable == 3) {
            av_master_switch_data = getOptionToString("av_master_switch_data");
            AvMasterSwitchData   = XPLMFindDataRef(av_master_switch_data.c_str());
            av_master_switch_data_on_value = getOptionToInt("av_master_switch_data_on_value");
            av_master_switch_data_off_value = getOptionToInt("av_master_switch_data_off_value");

            av2_master_switch_data = getOptionToString("av2_master_switch_data");
            Av2MasterSwitchData   = XPLMFindDataRef(av2_master_switch_data.c_str());
            av2_master_switch_data_on_value = getOptionToInt("av2_master_switch_data_on_value");
            av2_master_switch_data_off_value = getOptionToInt("av2_master_switch_data_off_value")
                    ;
            av3_master_switch_data = getOptionToString("av3_master_switch_data");
            Av3MasterSwitchData   = XPLMFindDataRef(av3_master_switch_data.c_str());
            av3_master_switch_data_on_value = getOptionToInt("av3_master_switch_data_on_value");
            av3_master_switch_data_off_value = getOptionToInt("av3_master_switch_data_off_value");

            av4_master_switch_data = getOptionToString("av4_master_switch_data");
            Av4MasterSwitchData   = XPLMFindDataRef(av4_master_switch_data.c_str());
            av4_master_switch_data_on_value = getOptionToInt("av4_master_switch_data_on_value");
            av4_master_switch_data_off_value = getOptionToInt("av4_master_switch_data_off_value");

            av5_master_switch_data = getOptionToString("av5_master_switch_data");
            Av5MasterSwitchData   = XPLMFindDataRef(av5_master_switch_data.c_str());
            av5_master_switch_data_on_value = getOptionToInt("av5_master_switch_data_on_value");
            av5_master_switch_data_off_value = getOptionToInt("av5_master_switch_data_off_value");

            av6_master_switch_data = getOptionToString("av6_master_switch_data");
            Av6MasterSwitchData   = XPLMFindDataRef(av6_master_switch_data.c_str());
            av6_master_switch_data_on_value = getOptionToInt("av6_master_switch_data_on_value");
            av6_master_switch_data_off_value = getOptionToInt("av6_master_switch_data_off_value");

            av7_master_switch_data = getOptionToString("av7_master_switch_data");
            Av7MasterSwitchData   = XPLMFindDataRef(av7_master_switch_data.c_str());
            av7_master_switch_data_on_value = getOptionToInt("av7_master_switch_data_on_value");
            av7_master_switch_data_off_value = getOptionToInt("av7_master_switch_data_off_value");

            av8_master_switch_data = getOptionToString("av8_master_switch_data");
            Av8MasterSwitchData   = XPLMFindDataRef(av8_master_switch_data.c_str());
            av8_master_switch_data_on_value = getOptionToInt("av8_master_switch_data_on_value");
            av8_master_switch_data_off_value = getOptionToInt("av8_master_switch_data_off_value");

    }


    // fuel pump switch disable - enable - remap
    fuelpumpswitchenable = getOptionToInt("Fuel Pump Switch enable");
    if (fuelpumpswitchenable == 0) {
        XPSetWidgetProperty(SwitchDisableCheckWidget[8], xpProperty_ButtonState, 1);
    }

    if (fuelpumpswitchenable == 1) {
        XPSetWidgetProperty(SwitchEnableCheckWidget[8], xpProperty_ButtonState, 1);
    }

    if (fuelpumpswitchenable == 2) {
        XPSetWidgetProperty(SwitchRemapCheckWidget[8], xpProperty_ButtonState, 1);
        fuel_pump_switch_on = getOptionToString("fuel_pump_switch_on_cmd");
        fuel_pump_switch_off = getOptionToString("fuel_pump_switch_off_cmd");
        FuelPumpOnCmd   = XPLMFindCommand(fuel_pump_switch_on.c_str());
        FuelPumpOffCmd   = XPLMFindCommand(fuel_pump_switch_off.c_str());

        fuel_pump2_switch_on = getOptionToString("fuel_pump2_switch_on_cmd");
        fuel_pump2_switch_off = getOptionToString("fuel_pump2_switch_off_cmd");
        FuelPump2OnCmd   = XPLMFindCommand(fuel_pump2_switch_on.c_str());
        FuelPump2OffCmd   = XPLMFindCommand(fuel_pump2_switch_off.c_str());

        fuel_pump3_switch_on = getOptionToString("fuel_pump3_switch_on_cmd");
        fuel_pump3_switch_off = getOptionToString("fuel_pump3_switch_off_cmd");
        FuelPump3OnCmd   = XPLMFindCommand(fuel_pump3_switch_on.c_str());
        FuelPump3OffCmd   = XPLMFindCommand(fuel_pump3_switch_off.c_str());

        fuel_pump4_switch_on = getOptionToString("fuel_pump4_switch_on_cmd");
        fuel_pump4_switch_off = getOptionToString("fuel_pump4_switch_off_cmd");
        FuelPump4OnCmd   = XPLMFindCommand(fuel_pump4_switch_on.c_str());
        FuelPump4OffCmd   = XPLMFindCommand(fuel_pump4_switch_off.c_str());

    }

    if (fuelpumpswitchenable == 3) {

        fuel_pump_switch_data = getOptionToString("fuel_pump_switch_data");
        FuelPumpSwitchData   = XPLMFindDataRef(fuel_pump_switch_data.c_str());
        fuel_pump_switch_data_on_value = getOptionToInt("fuel_pump_switch_data_on_value");
        fuel_pump_switch_data_off_value = getOptionToInt("fuel_pump_switch_data_off_value");

        fuel_pump2_switch_data = getOptionToString("fuel_pump2_switch_data");
        FuelPump2SwitchData   = XPLMFindDataRef(fuel_pump2_switch_data.c_str());
        fuel_pump2_switch_data_on_value = getOptionToInt("fuel_pump2_switch_data_on_value");
        fuel_pump2_switch_data_off_value = getOptionToInt("fuel_pump2_switch_data_off_value");

        fuel_pump3_switch_data = getOptionToString("fuel_pump3_switch_data");
        FuelPump3SwitchData   = XPLMFindDataRef(fuel_pump3_switch_data.c_str());
        fuel_pump3_switch_data_on_value = getOptionToInt("fuel_pump3_switch_data_on_value");
        fuel_pump3_switch_data_off_value = getOptionToInt("fuel_pump3_switch_data_off_value");

        fuel_pump4_switch_data = getOptionToString("fuel_pump4_switch_data");
        FuelPump4SwitchData   = XPLMFindDataRef(fuel_pump4_switch_data.c_str());
        fuel_pump4_switch_data_on_value = getOptionToInt("fuel_pump4_switch_data_on_value");
        fuel_pump4_switch_data_off_value = getOptionToInt("fuel_pump4_switch_data_off_value");

    }



    // deice switch disable - enable - remap
    deiceswitchenable = getOptionToInt("Deice Switch enable");
    if (deiceswitchenable == 0) {
        XPSetWidgetProperty(SwitchDisableCheckWidget[9], xpProperty_ButtonState, 1);
    }

    if (deiceswitchenable == 1) {
        XPSetWidgetProperty(SwitchEnableCheckWidget[9], xpProperty_ButtonState, 1);
    }

    if (deiceswitchenable == 2) {
        XPSetWidgetProperty(SwitchRemapCheckWidget[9], xpProperty_ButtonState, 1);
        deice_switch_on = getOptionToString("deice_switch_on_cmd");
        deice_switch_off = getOptionToString("deice_switch_off_cmd");
        DeiceOnCmd   = XPLMFindCommand(deice_switch_on.c_str());
        DeiceOffCmd   = XPLMFindCommand(deice_switch_off.c_str());

        deice2_switch_on = getOptionToString("deice2_switch_on_cmd");
        deice2_switch_off = getOptionToString("deice2_switch_off_cmd");
        DeiceOnCmd2   = XPLMFindCommand(deice2_switch_on.c_str());
        DeiceOffCmd2   = XPLMFindCommand(deice2_switch_off.c_str());

        deice3_switch_on = getOptionToString("deice3_switch_on_cmd");
        deice3_switch_off = getOptionToString("deice3_switch_off_cmd");
        DeiceOnCmd3   = XPLMFindCommand(deice3_switch_on.c_str());
        DeiceOffCmd3   = XPLMFindCommand(deice3_switch_off.c_str());

        deice4_switch_on = getOptionToString("deice4_switch_on_cmd");
        deice4_switch_off = getOptionToString("deice4_switch_off_cmd");
        DeiceOnCmd4   = XPLMFindCommand(deice4_switch_on.c_str());
        DeiceOffCmd4   = XPLMFindCommand(deice4_switch_off.c_str());

        deice5_switch_on = getOptionToString("deice5_switch_on_cmd");
        deice5_switch_off = getOptionToString("deice5_switch_off_cmd");
        DeiceOnCmd5   = XPLMFindCommand(deice5_switch_on.c_str());
        DeiceOffCmd5   = XPLMFindCommand(deice5_switch_off.c_str());

        deice6_switch_on = getOptionToString("deice6_switch_on_cmd");
        deice6_switch_off = getOptionToString("deice6_switch_off_cmd");
        DeiceOnCmd6   = XPLMFindCommand(deice6_switch_on.c_str());
        DeiceOffCmd6   = XPLMFindCommand(deice6_switch_off.c_str());


        deice7_switch_on = getOptionToString("deice7_switch_on_cmd");
        deice7_switch_off = getOptionToString("deice7_switch_off_cmd");
        DeiceOnCmd7   = XPLMFindCommand(deice7_switch_on.c_str());
        DeiceOffCmd7   = XPLMFindCommand(deice7_switch_off.c_str());

        deice8_switch_on = getOptionToString("deice8_switch_on_cmd");
        deice8_switch_off = getOptionToString("deice8_switch_off_cmd");
        DeiceOnCmd8   = XPLMFindCommand(deice8_switch_on.c_str());
        DeiceOffCmd8   = XPLMFindCommand(deice8_switch_off.c_str());

    }

    if (deiceswitchenable == 3) {

        deice_switch_data = getOptionToString("deice_switch_data");
        DeiceSwitchData   = XPLMFindDataRef(deice_switch_data.c_str());
        deice_switch_data_on_value = getOptionToInt("deice_switch_data_on_value");
        deice_switch_data_off_value = getOptionToInt("deice_switch_data_off_value");

        deice2_switch_data = getOptionToString("deice2_switch_data");
        Deice2SwitchData   = XPLMFindDataRef(deice2_switch_data.c_str());
        deice2_switch_data_on_value = getOptionToInt("deice2_switch_data_on_value");
        deice2_switch_data_off_value = getOptionToInt("deice2_switch_data_off_value");

        deice3_switch_data = getOptionToString("deice3_switch_data");
        Deice3SwitchData   = XPLMFindDataRef(deice3_switch_data.c_str());
        deice3_switch_data_on_value = getOptionToInt("deice3_switch_data_on_value");
        deice3_switch_data_off_value = getOptionToInt("deice3_switch_data_off_value");

        deice4_switch_data = getOptionToString("deice4_switch_data");
        Deice4SwitchData   = XPLMFindDataRef(deice4_switch_data.c_str());
        deice4_switch_data_on_value = getOptionToInt("deice4_switch_data_on_value");
        deice4_switch_data_off_value = getOptionToInt("deice4_switch_data_off_value");

        deice5_switch_data = getOptionToString("deice5_switch_data");
        Deice5SwitchData   = XPLMFindDataRef(deice5_switch_data.c_str());
        deice5_switch_data_on_value = getOptionToInt("deice5_switch_data_on_value");
        deice5_switch_data_off_value = getOptionToInt("deice5_switch_data_off_value");

        deice6_switch_data = getOptionToString("deice6_switch_data");
        Deice6SwitchData   = XPLMFindDataRef(deice6_switch_data.c_str());
        deice6_switch_data_on_value = getOptionToInt("deice6_switch_data_on_value");
        deice6_switch_data_off_value = getOptionToInt("deice6_switch_data_off_value");

        deice7_switch_data = getOptionToString("deice7_switch_data");
        Deice7SwitchData   = XPLMFindDataRef(deice7_switch_data.c_str());
        deice7_switch_data_on_value = getOptionToInt("deice7_switch_data_on_value");
        deice7_switch_data_off_value = getOptionToInt("deice7_switch_data_off_value");

        deice8_switch_data = getOptionToString("deice8_switch_data");
        Deice8SwitchData   = XPLMFindDataRef(deice8_switch_data.c_str());
        deice8_switch_data_on_value = getOptionToInt("deice8_switch_data_on_value");
        deice8_switch_data_off_value = getOptionToInt("deice8_switch_data_off_value");

    }


    // pitot heat switch disable - enable - remap
    pitotheatswitchenable = getOptionToInt("Pitot Heat Switch enable");
    if (pitotheatswitchenable == 0) {
        XPSetWidgetProperty(SwitchDisableCheckWidget[10], xpProperty_ButtonState, 1);
    }

    if (pitotheatswitchenable == 1) {
        XPSetWidgetProperty(SwitchEnableCheckWidget[10], xpProperty_ButtonState, 1);
    }


    if (pitotheatswitchenable == 2) {
        XPSetWidgetProperty(SwitchRemapCheckWidget[10], xpProperty_ButtonState, 1);
        pitot_heat_switch_on = getOptionToString("pitot_heat_switch_on_cmd");
        pitot_heat_switch_off = getOptionToString("pitot_heat_switch_off_cmd");
        PitotHeatOnCmd   = XPLMFindCommand(pitot_heat_switch_on.c_str());
        PitotHeatOffCmd   = XPLMFindCommand(pitot_heat_switch_off.c_str());

        pitot2_heat_switch_on = getOptionToString("pitot2_heat_switch_on_cmd");
        pitot2_heat_switch_off = getOptionToString("pitot2_heat_switch_off_cmd");
        Pitot2HeatOnCmd   = XPLMFindCommand(pitot2_heat_switch_on.c_str());
        Pitot2HeatOffCmd   = XPLMFindCommand(pitot2_heat_switch_off.c_str());
    }

    if (pitotheatswitchenable == 3) {
        pitot_heat_switch_data = getOptionToString("pitot_heat_switch_data");
        PitotHeatSwitchData   = XPLMFindDataRef(pitot_heat_switch_data.c_str());
        pitot_heat_switch_data_on_value = getOptionToInt("pitot_heat_switch_data_on_value");
        pitot_heat_switch_data_off_value = getOptionToInt("pitot_heat_switch_data_off_value");

        pitot2_heat_switch_data = getOptionToString("pitot2_heat_switch_data");
        Pitot2HeatSwitchData   = XPLMFindDataRef(pitot2_heat_switch_data.c_str());
        pitot2_heat_switch_data_on_value = getOptionToInt("pitot2_heat_switch_data_on_value");
        pitot2_heat_switch_data_off_value = getOptionToInt("pitot2_heat_switch_data_off_value");

        pitot3_heat_switch_data = getOptionToString("pitot3_heat_switch_data");
        Pitot3HeatSwitchData   = XPLMFindDataRef(pitot3_heat_switch_data.c_str());
        pitot3_heat_switch_data_on_value = getOptionToInt("pitot3_heat_switch_data_on_value");
        pitot3_heat_switch_data_off_value = getOptionToInt("pitot3_heat_switch_data_off_value");

        pitot4_heat_switch_data = getOptionToString("pitot4_heat_switch_data");
        Pitot4HeatSwitchData   = XPLMFindDataRef(pitot4_heat_switch_data.c_str());
        pitot4_heat_switch_data_on_value = getOptionToInt("pitot4_heat_switch_data_on_value");
        pitot4_heat_switch_data_off_value = getOptionToInt("pitot4_heat_switch_data_off_value");

        pitot5_heat_switch_data = getOptionToString("pitot5_heat_switch_data");
        Pitot5HeatSwitchData   = XPLMFindDataRef(pitot5_heat_switch_data.c_str());
        pitot5_heat_switch_data_on_value = getOptionToInt("pitot5_heat_switch_data_on_value");
        pitot5_heat_switch_data_off_value = getOptionToInt("pitot5_heat_switch_data_off_value");

        pitot6_heat_switch_data = getOptionToString("pitot6_heat_switch_data");
        Pitot6HeatSwitchData   = XPLMFindDataRef(pitot6_heat_switch_data.c_str());
        pitot6_heat_switch_data_on_value = getOptionToInt("pitot6_heat_switch_data_on_value");
        pitot6_heat_switch_data_off_value = getOptionToInt("pitot6_heat_switch_data_off_value");

        pitot7_heat_switch_data = getOptionToString("pitot7_heat_switch_data");
        Pitot7HeatSwitchData   = XPLMFindDataRef(pitot7_heat_switch_data.c_str());
        pitot7_heat_switch_data_on_value = getOptionToInt("pitot7_heat_switch_data_on_value");
        pitot7_heat_switch_data_off_value = getOptionToInt("pitot7_heat_switch_data_off_value");

        pitot8_heat_switch_data = getOptionToString("pitot8_heat_switch_data");
        Pitot8HeatSwitchData   = XPLMFindDataRef(pitot8_heat_switch_data.c_str());
        pitot8_heat_switch_data_on_value = getOptionToInt("pitot8_heat_switch_data_on_value");
        pitot8_heat_switch_data_off_value = getOptionToInt("pitot8_heat_switch_data_off_value");

    }

    // landing gear up knob disable - enable - remap
    landinggearknobupenable = getOptionToInt("Landing Gear Knob Up enable");
    if (landinggearknobupenable == 0) {
         XPSetWidgetProperty(SwitchDisableCheckWidget[11], xpProperty_ButtonState, 1);
     }

     if (landinggearknobupenable == 1) {
          XPSetWidgetProperty(SwitchEnableCheckWidget[11], xpProperty_ButtonState, 1);
     }

     if (landinggearknobupenable == 2) {
         XPSetWidgetProperty(SwitchRemapCheckWidget[11], xpProperty_ButtonState, 1);
         gear_switch_up_on = getOptionToString("gear_up_switch_on_cmd");
         gear_switch_up_off = getOptionToString("gear_up_switch_off_cmd");
         GearUpOnCmd   = XPLMFindCommand(gear_switch_up_on.c_str());
         GearUpOnCmd   = XPLMFindCommand(gear_switch_up_off.c_str());
     }

     if (landinggearknobupenable == 3) {
         gear_switch_up_data = getOptionToString("gear_up_switch_data");
         GearUpData   = XPLMFindDataRef(gear_switch_up_on.c_str());
         gear_switch_up_data_on_value = getOptionToInt("gear_up_switch_data_on_value");
         gear_switch_up_data_off_value = getOptionToInt("gear_up_switch_data_off_value");

     }

     // landing gear dn knob disable - enable - remap
     landinggearknobdnenable = getOptionToInt("Landing Gear Knob Up enable");
     if (landinggearknobdnenable == 0) {
          XPSetWidgetProperty(SwitchDisableCheckWidget[12], xpProperty_ButtonState, 1);
      }

      if (landinggearknobdnenable == 1) {
           XPSetWidgetProperty(SwitchEnableCheckWidget[12], xpProperty_ButtonState, 1);
       }

      if (landinggearknobdnenable == 2) {
          XPSetWidgetProperty(SwitchRemapCheckWidget[12], xpProperty_ButtonState, 1);
          gear_switch_down_on = getOptionToString("gear_dn_switch_on_cmd");
          gear_switch_down_off = getOptionToString("gear_dn_switch_off_cmd");
          GearDnOnCmd   = XPLMFindCommand(gear_switch_down_on.c_str());
          GearDnOffCmd   = XPLMFindCommand(gear_switch_down_off.c_str());
      }

      if (landinggearknobdnenable == 3) {
          gear_switch_down_data = getOptionToString("gear_dn_switch_data");
          GearDnData   = XPLMFindDataRef(gear_switch_down_data.c_str());
          gear_switch_down_data_on_value = getOptionToInt("gear_dn_switch_data_on_value");
          gear_switch_down_data_off_value = getOptionToInt("gear_dn_switch_data_off_value");
      }



   // cowl flaps switch disable - enable - remap
    cowlflapsenable = getOptionToInt("Cowl Flaps enable");
    if (cowlflapsenable == 0) {
        XPSetWidgetProperty(SwitchDisableCheckWidget[13], xpProperty_ButtonState, 1);
   }

    if (cowlflapsenable == 1) {
        XPSetWidgetProperty(SwitchEnableCheckWidget[13], xpProperty_ButtonState, 1);
    }


    if (cowlflapsenable == 2) {
        XPSetWidgetProperty(SwitchRemapCheckWidget[13], xpProperty_ButtonState, 1);
        cowl_flaps_open = getOptionToString("cowl_flaps_open_cmd");
        cowl_flaps_close = getOptionToString("cowl_flaps_close_cmd");
        CowlFlapsOpenCmd   = XPLMFindCommand(cowl_flaps_open.c_str());
        CowlFlapsCloseCmd   = XPLMFindCommand(cowl_flaps_close.c_str());

        cowl2_flaps_open = getOptionToString("cowl2_flaps_open_cmd");
        cowl2_flaps_close = getOptionToString("cowl2_flaps_close_cmd");
        Cowl2FlapsOpenCmd   = XPLMFindCommand(cowl2_flaps_open.c_str());
        Cowl2FlapsCloseCmd   = XPLMFindCommand(cowl2_flaps_close.c_str());
    }

    if (cowlflapsenable == 3) {
        cowl_flaps_data = getOptionToString("cowl_flaps_data");
        CowlFlapsData   = XPLMFindDataRef(cowl_flaps_data.c_str());
        cowl_flaps_data_on_value = getOptionToInt("cowl_flaps_data_open_value");
        cowl_flaps_data_off_value = getOptionToInt("cowl_flaps_data_close_value");

        cowl2_flaps_data = getOptionToString("cowl2_flaps_data");
        Cowl2FlapsData   = XPLMFindDataRef(cowl2_flaps_data.c_str());
        cowl2_flaps_data_on_value = getOptionToInt("cowl2_flaps_data_open_value");
        cowl2_flaps_data_off_value = getOptionToInt("cowl2_flaps_data_close_value");

    }


    // panel lights switch disable - enable - remap
    panellightswitchenable = getOptionToInt("Panel Lights Switch enable");
    if (panellightswitchenable == 0) {
         XPSetWidgetProperty(SwitchDisableCheckWidget[14], xpProperty_ButtonState, 1);
     }

     if (panellightswitchenable == 1) {
          XPSetWidgetProperty(SwitchEnableCheckWidget[14], xpProperty_ButtonState, 1);
      }

     if (panellightswitchenable == 2) {
         XPSetWidgetProperty(SwitchRemapCheckWidget[14], xpProperty_ButtonState, 1);
         panel_lights_switch_on = getOptionToString("panel_lights_switch_on_cmd");
         panel_lights_switch_off = getOptionToString("panel_lights_switch_off_cmd");
         PanelLightsOnCmd   = XPLMFindCommand(panel_lights_switch_on.c_str());
         PanelLightsOffCmd   = XPLMFindCommand(panel_lights_switch_off.c_str());
     }

     if (panellightswitchenable == 3) {
         panel_lights_switch_data = getOptionToString("panel_lights_switch_data");
         PanelLightsData   = XPLMFindDataRef(panel_lights_switch_data.c_str());
         panel_lights_switch_data_on_value = getOptionToInt("panel_lights_switch_data_on_value");
         panel_lights_switch_data_off_value = getOptionToInt("panel_lights_switch_data_off_value");
     }

     if (panellightswitchenable == 4) {
         panel_lights_switch_data = getOptionToString("panel_lights_switch_data");
         PanelLightsData   = XPLMFindDataRef(panel_lights_switch_data.c_str());
         panel_lights_switch_data_on_value = getOptionToInt("panel_lights_switch_data_on_value");
         panel_lights_switch_data_off_value = getOptionToInt("panel_lights_switch_data_off_value");

         panel_lights_switch2_data = getOptionToString("panel_lights_switch2_data");
         PanelLights2Data   = XPLMFindDataRef(panel_lights_switch2_data.c_str());
         panel_lights_switch2_data_on_value = getOptionToInt("panel_lights_switch2_data_on_value");
         panel_lights_switch2_data_off_value = getOptionToInt("panel_lights_switch2_data_off_value");

         panel_lights_switch3_data = getOptionToString("panel_lights_switch3_data");
         PanelLights3Data   = XPLMFindDataRef(panel_lights_switch3_data.c_str());
         panel_lights_switch3_data_on_value = getOptionToInt("panel_lights_switch3_data_on_value");
         panel_lights_switch3_data_off_value = getOptionToInt("panel_lights_switch3_data_off_value");

         panel_lights_switch4_data = getOptionToString("panel_lights_switch4_data");
         PanelLights4Data   = XPLMFindDataRef(panel_lights_switch4_data.c_str());
         panel_lights_switch4_data_on_value = getOptionToInt("panel_lights_switch4_data_on_value");
         panel_lights_switch4_data_off_value = getOptionToInt("panel_lights_switch4_data_off_value");

         panel_lights_switch5_data = getOptionToString("panel_lights_switch5_data");
         PanelLights5Data   = XPLMFindDataRef(panel_lights_switch5_data.c_str());
         panel_lights_switch5_data_on_value = getOptionToInt("panel_lights_switch5_data_on_value");
         panel_lights_switch5_data_off_value = getOptionToInt("panel_lights_switch5_data_off_value");

         panel_lights_switch6_data = getOptionToString("panel_lights_switch6_data");
         PanelLights6Data   = XPLMFindDataRef(panel_lights_switch6_data.c_str());
         panel_lights_switch6_data_on_value = getOptionToInt("panel_lights_switch6_data_on_value");
         panel_lights_switch6_data_off_value = getOptionToInt("panel_lights_switch6_data_off_value");

         panel_lights_switch7_data = getOptionToString("panel_lights_switch7_data");
         PanelLights7Data   = XPLMFindDataRef(panel_lights_switch7_data.c_str());
         panel_lights_switch7_data_on_value = getOptionToInt("panel_lights_switch7_data_on_value");
         panel_lights_switch7_data_off_value = getOptionToInt("panel_lights_switch7_data_off_value");

         panel_lights_switch8_data = getOptionToString("panel_lights_switch8_data");
         PanelLights8Data   = XPLMFindDataRef(panel_lights_switch8_data.c_str());
         panel_lights_switch8_data_on_value = getOptionToInt("panel_lights_switch8_data_on_value");
         panel_lights_switch8_data_off_value = getOptionToInt("panel_lights_switch8_data_off_value");

     }

     // beacon lights switch disable - enable - remap
     beaconlightswitchenable = getOptionToInt("Beacon Lights Switch enable");
     if (beaconlightswitchenable == 0) {
          XPSetWidgetProperty(SwitchDisableCheckWidget[15], xpProperty_ButtonState, 1);
      }

      if (beaconlightswitchenable == 1) {
          XPSetWidgetProperty(SwitchEnableCheckWidget[15], xpProperty_ButtonState, 1);
      }

      if (beaconlightswitchenable == 2) {
          XPSetWidgetProperty(SwitchRemapCheckWidget[15], xpProperty_ButtonState, 1);
          beacon_lights_switch_on = getOptionToString("beacon_lights_switch_on_cmd");
          beacon_lights_switch_off = getOptionToString("beacon_lights_switch_off_cmd");
          BeaconLightsOnCmd   = XPLMFindCommand(beacon_lights_switch_on.c_str());
          BeaconLightsOffCmd   = XPLMFindCommand(beacon_lights_switch_off.c_str());
      }

      if (beaconlightswitchenable == 3) {
          beacon_lights_switch_data = getOptionToString("beacon_lights_switch_data");
          BeaconLightsData   = XPLMFindDataRef(beacon_lights_switch_data.c_str());
          beacon_lights_switch_data_on_value = getOptionToInt("beacon_lights_switch_data_on_value");
          beacon_lights_switch_data_off_value = getOptionToInt("beacon_lights_switch_data_off_value");
      }

      // nav lights switch disable - enable - remap
      navlightswitchenable = getOptionToInt("Nav Lights Switch enable");
      if (navlightswitchenable == 0) {
           XPSetWidgetProperty(SwitchDisableCheckWidget[16], xpProperty_ButtonState, 1);
        }

       if (navlightswitchenable == 1) {
           XPSetWidgetProperty(SwitchEnableCheckWidget[16], xpProperty_ButtonState, 1);
       }

       if (navlightswitchenable == 2) {
           XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
           nav_lights_switch_on = getOptionToString("nav_lights_switch_on_cmd");
           nav_lights_switch_off = getOptionToString("nav_lights_switch_off_cmd");
           NavLightsOnCmd   = XPLMFindCommand(nav_lights_switch_on.c_str());
           NavLightsOffCmd   = XPLMFindCommand(nav_lights_switch_off.c_str());
       }

       if (navlightswitchenable == 3) {
           nav_lights_switch_data = getOptionToString("nav_lights_switch_data");
           NavLightsData   = XPLMFindDataRef(nav_lights_switch_data.c_str());
           nav_lights_switch_data_on_value = getOptionToInt("nav_lights_switch_data_on_value");
           nav_lights_switch_data_off_value = getOptionToInt("nav_lights_switch_data_off_value");
       }

       // strobe lights switch disable - enable - remap
       strobelightswitchenable = getOptionToInt("Strobe Lights Switch enable");
       if (strobelightswitchenable == 0) {
            XPSetWidgetProperty(SwitchDisableCheckWidget[17], xpProperty_ButtonState, 1);
        }

        if (strobelightswitchenable == 1) {
            XPSetWidgetProperty(SwitchEnableCheckWidget[17], xpProperty_ButtonState, 1);
        }
        if (strobelightswitchenable == 2) {
            XPSetWidgetProperty(SwitchRemapCheckWidget[17], xpProperty_ButtonState, 1);
            strobe_lights_switch_on = getOptionToString("strobe_lights_switch_on_cmd");
            strobe_lights_switch_off = getOptionToString("strobe_lights_switch_off_cmd");
            StrobeLightsOnCmd   = XPLMFindCommand(strobe_lights_switch_on.c_str());
            StrobeLightsOffCmd   = XPLMFindCommand(strobe_lights_switch_off.c_str());
        }

        if (strobelightswitchenable == 3) {
            strobe_lights_switch_data = getOptionToString("strobe_lights_switch_data");
            StrobeLightsData   = XPLMFindDataRef(strobe_lights_switch_data.c_str());
            strobe_lights_switch_data_on_value = getOptionToInt("strobe_lights_switch_data_on_value");
            strobe_lights_switch_data_off_value = getOptionToInt("strobe_lights_switch_data_off_value");

        }

        // taxi lights switch disable - enable - remap
        taxilightswitchenable = getOptionToInt("Taxi Lights Switch enable");
        if (taxilightswitchenable == 0) {
             XPSetWidgetProperty(SwitchDisableCheckWidget[18], xpProperty_ButtonState, 1);
         }

         if (taxilightswitchenable == 1) {
             XPSetWidgetProperty(SwitchEnableCheckWidget[18], xpProperty_ButtonState, 1);
         }

         if (taxilightswitchenable == 2) {
             XPSetWidgetProperty(SwitchRemapCheckWidget[18], xpProperty_ButtonState, 1);
             taxi_lights_switch_on = getOptionToString("taxi_lights_switch_on_cmd");
             taxi_lights_switch_off = getOptionToString("taxi_lights_switch_off_cmd");
             TaxiLightsOnCmd   = XPLMFindCommand(taxi_lights_switch_on.c_str());
             TaxiLightsOffCmd   = XPLMFindCommand(taxi_lights_switch_off.c_str());
         }

         if (taxilightswitchenable == 3) {
             taxi_lights_switch_data = getOptionToString("taxi_lights_switch_data");
             TaxiLightsData   = XPLMFindDataRef(taxi_lights_switch_data.c_str());
             taxi_lights_switch_data_on_value = getOptionToInt("taxi_lights_switch_data_on_value");
             taxi_lights_switch_data_off_value = getOptionToInt("taxi_lights_switch_data_off_value");

         }

         // landing lights switch disable - enable - remap
         landinglightswitchenable = getOptionToInt("Landing Lights Switch enable");
         if (landinglightswitchenable == 0) {
              XPSetWidgetProperty(SwitchDisableCheckWidget[19], xpProperty_ButtonState, 1);
          }

          if (landinglightswitchenable == 1) {
              XPSetWidgetProperty(SwitchEnableCheckWidget[19], xpProperty_ButtonState, 1);
              //XPSetWidgetProperty(SwitchRemapCheckWidget[19], xpProperty_ButtonState, 0);
          }

          if (landinglightswitchenable == 2) {
              XPSetWidgetProperty(SwitchRemapCheckWidget[19], xpProperty_ButtonState, 1);
              landing_lights_switch_on = getOptionToString("landing_lights_switch_on_cmd");
              landing_lights_switch_off = getOptionToString("landing_lights_switch_off_cmd");
              LandingLightsOnCmd   = XPLMFindCommand(landing_lights_switch_on.c_str());
              LandingLightsOffCmd   = XPLMFindCommand(landing_lights_switch_off.c_str());
          }

          if (landinglightswitchenable == 3) {
              landing_lights_switch_data = getOptionToString("landing_lights_switch_data");
              LandingLightsData   = XPLMFindDataRef(landing_lights_switch_data.c_str());
              landing_lights_switch_data_on_value = getOptionToInt("landing_lights_switch_data_on_value");
              landing_lights_switch_data_off_value = getOptionToInt("landing_lights_switch_data_off_value");
          }


    bataltinverse = getOptionToInt("Bat Alt inverse");

    starterswitchenable = getOptionToInt("Starter Old New");

    // landing lights switch disable - enable - remap
    landinglightswitchenable = getOptionToInt("Landing Lights Switch enable");
    if (landinglightswitchenable == 0) {
         XPSetWidgetProperty(SwitchDisableCheckWidget[19], xpProperty_ButtonState, 1);
     }

// *******************  Radio Panel Commands   **********************************

    radspeed = getOptionToInt("Radio Freq Knob Pulse per Command");
    XPSetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(RadioSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(RadioSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(RadioSpeed4CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(RadioSpeed5CheckWidget[0], xpProperty_ButtonState, 0);
    if (radspeed == 1) {
         XPSetWidgetProperty(RadioSpeed1CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (radspeed == 2) {
         XPSetWidgetProperty(RadioSpeed2CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (radspeed == 3) {
         XPSetWidgetProperty(RadioSpeed3CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (radspeed == 4) {
         XPSetWidgetProperty(RadioSpeed4CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (radspeed == 5) {
         XPSetWidgetProperty(RadioSpeed5CheckWidget[0], xpProperty_ButtonState, 1);
    }


    numadf = getOptionToInt("Radio Number of ADF's");
    XPSetWidgetProperty(RadioAdf1CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(RadioAdf2CheckWidget[0], xpProperty_ButtonState, 0);
    if (numadf == 1) {
         XPSetWidgetProperty(RadioAdf1CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (numadf == 2) {
         XPSetWidgetProperty(RadioAdf2CheckWidget[0], xpProperty_ButtonState, 1);
    }

    metricpressenable = getOptionToInt("Metric Press enable");
    XPSetWidgetProperty(RadioQnh0CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(RadioQnh1CheckWidget[0], xpProperty_ButtonState, 0);
    if (metricpressenable == 0) {
         XPSetWidgetProperty(RadioQnh0CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (metricpressenable == 1) {
         XPSetWidgetProperty(RadioQnh1CheckWidget[0], xpProperty_ButtonState, 1);
    }

    // ***************************  Upper Radio1 remaping  ***********************************
    // Radio1 Upper com1 switch - remapable
    rad1uprcom1switchremap = getOptionToInt("Radio1 Upper Com1 Switch remapable");
    if (rad1uprcom1switchremap == 1) {
        rad1_upper_com1_corse_up_remapable = getOptionToString("rad1_upper_com1_corse_up_cmd");
        Rad1UprCom1CrsUpRemapableCmd   = XPLMFindCommand(rad1_upper_com1_corse_up_remapable.c_str());

        rad1_upper_com1_corse_dn_remapable = getOptionToString("rad1_upper_com1_corse_dn_cmd");
        Rad1UprCom1CrsDnRemapableCmd   = XPLMFindCommand(rad1_upper_com1_corse_dn_remapable.c_str());

        rad1_upper_com1_fine_up_remapable = getOptionToString("rad1_upper_com1_fine_up_cmd");
        Rad1UprCom1FnUpRemapableCmd   = XPLMFindCommand(rad1_upper_com1_fine_up_remapable.c_str());

        rad1_upper_com1_fine_dn_remapable = getOptionToString("rad1_upper_com1_fine_dn_cmd");
        Rad1UprCom1FnDnRemapableCmd   = XPLMFindCommand(rad1_upper_com1_fine_dn_remapable.c_str());

        rad1_upper_com1_act_data_remapable = getOptionToString("rad1_upper_com1_act_data");
        Rad1UpperCom1ActRemapableData   = XPLMFindDataRef(rad1_upper_com1_act_data_remapable.c_str());

        rad1_upper_com1_stby_data_remapable = getOptionToString("rad1_upper_com1_stby_data");
        Rad1UpperCom1StbyRemapableData   = XPLMFindDataRef(rad1_upper_com1_stby_data_remapable.c_str());

    }

    // Radio1 Upper com1 active stanby button - remapable
    rad1uprcom1actstbybtnremap = getOptionToInt("Radio1 Upper Com1 ActStby remapable");
    if ((rad1uprcom1actstbybtnremap == 1) || (rad1uprcom1actstbybtnremap == 2)) {
        rad1_upper_com1_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_com1_actstby_btn_cmd");
        Rad1UprCom1ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_com1_actstby_btn_remapable_cmd.c_str());

        rad1_upper_com1_actstby_btn_remapable_data = getOptionToString("rad1_upper_com1_actstby_btn_data");
        Rad1UprCom1ActStbyRemapableData   = XPLMFindDataRef(rad1_upper_com1_actstby_btn_remapable_data.c_str());
    }

    // Radio1 Upper com2 switch - remapable
    rad1uprcom2switchremap = getOptionToInt("Radio1 Upper Com2 Switch remapable");
    if (rad1uprcom2switchremap == 1) {
        rad1_upper_com2_corse_up_remapable = getOptionToString("rad1_upper_com2_corse_up_cmd");
        Rad1UprCom2CrsUpRemapableCmd   = XPLMFindCommand(rad1_upper_com2_corse_up_remapable.c_str());

        rad1_upper_com2_corse_dn_remapable = getOptionToString("rad1_upper_com2_corse_dn_cmd");
        Rad1UprCom2CrsDnRemapableCmd   = XPLMFindCommand(rad1_upper_com2_corse_dn_remapable.c_str());

        rad1_upper_com2_fine_up_remapable = getOptionToString("rad1_upper_com2_fine_up_cmd");
        Rad1UprCom2FnUpRemapableCmd   = XPLMFindCommand(rad1_upper_com2_fine_up_remapable.c_str());

        rad1_upper_com2_fine_dn_remapable = getOptionToString("rad1_upper_com2_fine_dn_cmd");
        Rad1UprCom2FnDnRemapableCmd  = XPLMFindCommand(rad1_upper_com2_fine_dn_remapable.c_str());

        rad1_upper_com2_act_data_remapable = getOptionToString("rad1_upper_com2_act_data");
        Rad1UpperCom2ActRemapableData   = XPLMFindDataRef(rad1_upper_com2_act_data_remapable.c_str());

        rad1_upper_com2_stby_data_remapable = getOptionToString("rad1_upper_com2_stby_data");
        Rad1UpperCom2StbyRemapableData   = XPLMFindDataRef(rad1_upper_com2_stby_data_remapable.c_str());

    }

    // Radio1 Upper com2 active stanby button - remapable
    rad1uprcom2actstbybtnremap = getOptionToInt("Radio1 Upper Com2 ActStby remapable");
    if ((rad1uprcom2actstbybtnremap == 1) || (rad1uprcom2actstbybtnremap == 2)) {
        rad1_upper_com2_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_com2_actstby_btn_cmd");
        Rad1UprCom2ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_com2_actstby_btn_remapable_cmd.c_str());

        rad1_upper_com2_actstby_btn_remapable_data = getOptionToString("rad1_upper_com2_actstby_btn_data");
        Rad1UprCom2ActStbyRemapableData   = XPLMFindDataRef(rad1_upper_com2_actstby_btn_remapable_data.c_str());
    }



    // Radio1 Upper Nav1 switch - remapable
    rad1uprnav1switchremap = getOptionToInt("Radio1 Upper Nav1 Switch remapable");
    if (rad1uprnav1switchremap == 1) {
        rad1_upper_nav1_corse_up_remapable = getOptionToString("rad1_upper_nav1_corse_up_cmd");
        Rad1UprNav1CrsUpRemapableCmd   = XPLMFindCommand(rad1_upper_nav1_corse_up_remapable.c_str());

        rad1_upper_nav1_corse_dn_remapable = getOptionToString("rad1_upper_nav1_corse_dn_cmd");
        Rad1UprNav1CrsDnRemapableCmd   = XPLMFindCommand(rad1_upper_nav1_corse_dn_remapable.c_str());

        rad1_upper_nav1_fine_up_remapable = getOptionToString("rad1_upper_nav1_fine_up_cmd");
        Rad1UprNav1FnUpRemapableCmd   = XPLMFindCommand(rad1_upper_nav1_fine_up_remapable.c_str());

        rad1_upper_nav1_fine_dn_remapable = getOptionToString("rad1_upper_nav1_fine_dn_cmd");
        Rad1UprNav1FnDnRemapableCmd   = XPLMFindCommand(rad1_upper_nav1_fine_dn_remapable.c_str());

        rad1_upper_nav1_act_data_remapable = getOptionToString("rad1_upper_nav1_act_data");
        Rad1UpperNav1ActRemapableData   = XPLMFindDataRef(rad1_upper_nav1_act_data_remapable.c_str());

        rad1_upper_nav1_stby_data_remapable = getOptionToString("rad1_upper_nav1_stby_data");
        Rad1UpperNav1StbyRemapableData   = XPLMFindDataRef(rad1_upper_nav1_stby_data_remapable.c_str());

    }

    // Radio1 Upper Nav1 active stanby button - remapable
    rad1uprnav1actstbybtnremap = getOptionToInt("Radio1 Upper Nav1 ActStby remapable");
    if (rad1uprnav1actstbybtnremap == 1) {
        rad1_upper_nav1_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_nav1_actstby_btn_cmd");
        Rad1UprNav1ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_nav1_actstby_btn_remapable_cmd.c_str());

        rad1_upper_nav1_actstby_btn_remapable_data = getOptionToString("rad1_upper_nav1_actstby_btn_data");
        Rad1UprNav1ActStbyRemapableData   = XPLMFindDataRef(rad1_upper_nav1_actstby_btn_remapable_data.c_str());
    }

    // Radio1 Upper Nav2 switch - remapable
    rad1uprnav2switchremap = getOptionToInt("Radio1 Upper Nav2 Switch remapable");
    if (rad1uprnav2switchremap == 1) {
        rad1_upper_nav2_corse_up_remapable = getOptionToString("rad1_upper_nav2_corse_up_cmd");
        Rad1UprNav2CrsUpRemapableCmd   = XPLMFindCommand(rad1_upper_nav2_corse_up_remapable.c_str());

        rad1_upper_nav2_corse_dn_remapable = getOptionToString("rad1_upper_nav2_corse_dn_cmd");
        Rad1UprNav2CrsDnRemapableCmd   = XPLMFindCommand(rad1_upper_nav2_corse_dn_remapable.c_str());

        rad1_upper_nav2_fine_up_remapable = getOptionToString("rad1_upper_nav2_fine_up_cmd");
        Rad1UprNav2FnUpRemapableCmd   = XPLMFindCommand(rad1_upper_nav2_fine_up_remapable.c_str());

        rad1_upper_nav2_fine_dn_remapable = getOptionToString("rad1_upper_nav2_fine_dn_cmd");
        Rad1UprNav2FnDnRemapableCmd   = XPLMFindCommand(rad1_upper_nav2_fine_dn_remapable.c_str());

        rad1_upper_nav2_act_data_remapable = getOptionToString("rad1_upper_nav2_act_data");
        Rad1UpperNav2ActRemapableData   = XPLMFindDataRef(rad1_upper_nav2_act_data_remapable.c_str());

        rad1_upper_nav2_stby_data_remapable = getOptionToString("rad1_upper_nav2_stby_data");
        Rad1UpperNav2StbyRemapableData   = XPLMFindDataRef(rad1_upper_nav2_stby_data_remapable.c_str());

    }

    // Radio1 Upper Nav2 active stanby button - remapable
    rad1uprnav2actstbybtnremap = getOptionToInt("Radio1 Upper Nav2 ActStby remapable");
    if (rad1uprnav2actstbybtnremap == 1) {
        rad1_upper_nav2_actstby_btn_remapable_cmd = getOptionToString("rad1_upper_nav2_actstby_btn_cmd");
        Rad1UprNav2ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_nav2_actstby_btn_remapable_cmd.c_str());

        rad1_upper_nav2_actstby_btn_remapable_data = getOptionToString("rad1_upper_nav2_actstby_btn_data");
        Rad1UprNav2ActStbyRemapableData = XPLMFindDataRef(rad1_upper_nav2_actstby_btn_remapable_data.c_str());
    }


    // Radio1 Upper Xpdr switch - remapable

    rad1uprxpdrswitchremap = getOptionToInt("Radio1 Upper Xpdr Switch remapable");
    if (rad1uprxpdrswitchremap == 777) {
        rad1_upper_xpdr_data_remapable = getOptionToString("rad1_upper_xpdr_data");
        Rad1UpperXpdrRemapableData   = XPLMFindDataRef(rad1_upper_xpdr_data_remapable.c_str());

        rad1_upper_xpdr_mode_remapable = getOptionToString("rad1_upper_xpdr_mode");
        Rad1UpperXpdrRemapableMode   = XPLMFindDataRef(rad1_upper_xpdr_mode_remapable.c_str());

        rad1_upper_xpdr_baro_std_data_remapable = getOptionToString("rad1_upper_xpdr_baro_std_data");
        Rad1UpperXpdrBaroStdRemapableData   = XPLMFindDataRef(rad1_upper_xpdr_baro_std_data_remapable.c_str());

        rad1_upper_xpdr_baro_up_remapable_cmd = getOptionToString("rad1_upper_xpdr_baro_up_cmd");
        Rad1UpperXpdrBaroUpRemapableCmd   = XPLMFindCommand(rad1_upper_xpdr_baro_up_remapable_cmd.c_str());

        rad1_upper_xpdr_baro_dn_remapable_cmd = getOptionToString("rad1_upper_xpdr_baro_dn_cmd");
        Rad1UpperXpdrBaroDnRemapableCmd   = XPLMFindCommand(rad1_upper_xpdr_baro_dn_remapable_cmd.c_str());


    }


    // ************************  Lower Radio1 remaping  *********************************************
    // Radio1 Lower Com1 switch - remapable
    rad1lwrcom1switchremap = getOptionToInt("Radio1 Lower Com1 Switch remapable");
    if (rad1lwrcom1switchremap == 1) {
        rad1_lower_com1_corse_up_remapable = getOptionToString("rad1_lower_com1_corse_up_cmd");
        Rad1LowrCom1CrsUpRemapableCmd   = XPLMFindCommand(rad1_lower_com1_corse_up_remapable.c_str());

        rad1_lower_com1_corse_dn_remapable = getOptionToString("rad1_lower_com1_corse_dn_cmd");
        Rad1LowrCom1CrsDnRemapableCmd   = XPLMFindCommand(rad1_lower_com1_corse_dn_remapable.c_str());

        rad1_lower_com1_fine_up_remapable = getOptionToString("rad1_lower_com1_fine_up_cmd");
        Rad1LowrCom1FnUpRemapableCmd   = XPLMFindCommand(rad1_lower_com1_fine_up_remapable.c_str());

        rad1_lower_com1_fine_dn_remapable = getOptionToString("rad1_lower_com1_fine_dn_cmd");
        Rad1LowrCom1FnDnRemapableCmd   = XPLMFindCommand(rad1_lower_com1_fine_dn_remapable.c_str());

        rad1_lower_com1_act_data_remapable = getOptionToString("rad1_lower_com1_act_data");
        Rad1LowerCom1ActRemapableData   = XPLMFindDataRef(rad1_lower_com1_act_data_remapable.c_str());

        rad1_lower_com1_stby_data_remapable = getOptionToString("rad1_lower_com1_stby_data");
        Rad1LowerCom1StbyRemapableData   = XPLMFindDataRef(rad1_lower_com1_stby_data_remapable.c_str());

    }

    // Radio1 Lower Com1 active stanby button - remapable
    rad1lwrcom1actstbybtnremap = getOptionToInt("Radio1 Lower Com1 ActStby remapable");
    if ((rad1lwrcom1actstbybtnremap == 1) || (rad1lwrcom1actstbybtnremap == 2)) {
        rad1_lower_com1_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_com1_actstby_btn_cmd");
        Rad1LowrCom1ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_com1_actstby_btn_remapable_cmd.c_str());

        rad1_lower_com1_actstby_btn_remapable_data = getOptionToString("rad1_lower_com1_actstby_btn_data");
        Rad1LowrCom1ActStbyRemapableData   = XPLMFindDataRef(rad1_lower_com1_actstby_btn_remapable_data.c_str());
    }

    // Radio1 Lower Com2 switch - remapable
    rad1lwrcom2switchremap = getOptionToInt("Radio1 Lower Com2 Switch remapable");
    if (rad1lwrcom2switchremap == 1) {
        rad1_lower_com2_corse_up_remapable = getOptionToString("rad1_lower_com2_corse_up_cmd");
        Rad1LowrCom2CrsUpRemapableCmd   = XPLMFindCommand(rad1_lower_com2_corse_up_remapable.c_str());

        rad1_lower_com2_corse_dn_remapable = getOptionToString("rad1_lower_com2_corse_dn_cmd");
        Rad1LowrCom2CrsDnRemapableCmd   = XPLMFindCommand(rad1_lower_com2_corse_dn_remapable.c_str());

        rad1_lower_com2_fine_up_remapable = getOptionToString("rad1_lower_com2_fine_up_cmd");
        Rad1LowrCom2FnUpRemapableCmd   = XPLMFindCommand(rad1_lower_com2_fine_up_remapable.c_str());

        rad1_lower_com2_fine_dn_remapable = getOptionToString("rad1_lower_com2_fine_dn_cmd");
        Rad1LowrCom2FnDnRemapableCmd   = XPLMFindCommand(rad1_lower_com2_fine_dn_remapable.c_str());

        rad1_lower_com2_act_data_remapable = getOptionToString("rad1_lower_com2_act_data");
        Rad1LowerCom2ActRemapableData   = XPLMFindDataRef(rad1_lower_com2_act_data_remapable.c_str());

        rad1_lower_com2_stby_data_remapable = getOptionToString("rad1_lower_com2_stby_data");
        Rad1LowerCom2StbyRemapableData   = XPLMFindDataRef(rad1_lower_com2_stby_data_remapable.c_str());

    }

    // Radio1 Lower Com2 active stanby button - remapable
    rad1lwrcom2actstbybtnremap = getOptionToInt("Radio1 Lower Com2 ActStby remapable");
    if ((rad1lwrcom2actstbybtnremap == 1) || (rad1lwrcom2actstbybtnremap == 2)){
        rad1_lower_com2_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_com2_actstby_btn_cmd");
        Rad1LowrCom2ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_com2_actstby_btn_remapable_cmd.c_str());

        rad1_lower_com2_actstby_btn_remapable_data = getOptionToString("rad1_lower_com2_actstby_btn_data");
        Rad1LowrCom2ActStbyRemapableData   = XPLMFindDataRef(rad1_lower_com2_actstby_btn_remapable_data.c_str());
    }

    // Radio1 Lower Nav1 switch - remapable
    rad1lwrnav1switchremap = getOptionToInt("Radio1 Lower Nav1 Switch remapable");
    if (rad1lwrnav1switchremap == 1) {
        rad1_lower_nav1_corse_up_remapable = getOptionToString("rad1_lower_nav1_corse_up_cmd");
        Rad1LowrNav1CrsUpRemapableCmd   = XPLMFindCommand(rad1_lower_nav1_corse_up_remapable.c_str());

        rad1_lower_nav1_corse_dn_remapable = getOptionToString("rad1_lower_nav1_corse_dn_cmd");
        Rad1LowrNav1CrsDnRemapableCmd   = XPLMFindCommand(rad1_lower_nav1_corse_dn_remapable.c_str());

        rad1_lower_nav1_fine_up_remapable = getOptionToString("rad1_lower_nav1_fine_up_cmd");
        Rad1LowrNav1FnUpRemapableCmd   = XPLMFindCommand(rad1_lower_nav1_fine_up_remapable.c_str());

        rad1_lower_nav1_fine_dn_remapable = getOptionToString("rad1_lower_nav1_fine_dn_cmd");
        Rad1LowrNav1FnDnRemapableCmd   = XPLMFindCommand(rad1_lower_nav1_fine_dn_remapable.c_str());

        rad1_lower_nav1_act_data_remapable = getOptionToString("rad1_lower_nav1_act_data");
        Rad1LowerNav1ActRemapableData   = XPLMFindDataRef(rad1_lower_nav1_act_data_remapable.c_str());

        rad1_lower_nav1_stby_data_remapable = getOptionToString("rad1_lower_nav1_stby_data");
        Rad1LowerNav1StbyRemapableData   = XPLMFindDataRef(rad1_lower_nav1_stby_data_remapable.c_str());


    }

    // Radio1 Lower Nav1 active stanby button - remapable
    rad1lwrnav1actstbybtnremap = getOptionToInt("Radio1 Lower Nav1 ActStby remapable");
    if (rad1lwrnav1actstbybtnremap == 1) {
        rad1_lower_nav1_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_nav1_actstby_btn_cmd");
        Rad1LowrNav1ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_nav1_actstby_btn_remapable_cmd.c_str());

        rad1_lower_nav1_actstby_btn_remapable_data = getOptionToString("rad1_lower_nav1_actstby_btn_data");
        Rad1LowrNav1ActStbyRemapableData   = XPLMFindDataRef(rad1_lower_nav1_actstby_btn_remapable_data.c_str());
    }

     // Radio1 Lower Nav2 switch - remapable
     rad1lwrnav2switchremap = getOptionToInt("Radio1 Lower Nav2 Switch remapable");
     if (rad1lwrnav2switchremap == 1) {
         rad1_lower_nav2_corse_up_remapable = getOptionToString("rad1_lower_nav2_corse_up_cmd");
         Rad1LowrNav2CrsUpRemapableCmd   = XPLMFindCommand(rad1_lower_nav2_corse_up_remapable.c_str());

         rad1_lower_nav2_corse_dn_remapable = getOptionToString("rad1_lower_nav2_corse_dn_cmd");
         Rad1LowrNav2CrsDnRemapableCmd   = XPLMFindCommand(rad1_lower_nav2_corse_dn_remapable.c_str());

         rad1_lower_nav2_fine_up_remapable = getOptionToString("rad1_lower_nav2_fine_up_cmd");
         Rad1LowrNav2FnUpRemapableCmd   = XPLMFindCommand(rad1_lower_nav2_fine_up_remapable.c_str());

         rad1_lower_nav2_fine_dn_remapable = getOptionToString("rad1_lower_nav2_fine_dn_cmd");
         Rad1LowrNav2FnDnRemapableCmd   = XPLMFindCommand(rad1_lower_nav2_fine_dn_remapable.c_str());

         rad1_lower_nav2_act_data_remapable = getOptionToString("rad1_lower_nav2_act_data");
         Rad1LowerNav2ActRemapableData   = XPLMFindDataRef(rad1_lower_nav2_act_data_remapable.c_str());

         rad1_lower_nav2_stby_data_remapable = getOptionToString("rad1_lower_nav2_stby_data");
         Rad1LowerNav2StbyRemapableData   = XPLMFindDataRef(rad1_lower_nav2_stby_data_remapable.c_str());

     }

     // Radio1 Lower Nav2 active stanby button - remapable
     rad1lwrnav2actstbybtnremap = getOptionToInt("Radio1 Lower Nav2 ActStby remapable");
     if (rad1lwrnav2actstbybtnremap == 1) {
         rad1_lower_nav2_actstby_btn_remapable_cmd = getOptionToString("rad1_lower_nav2_actstby_btn_cmd");
         Rad1LowrNav2ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_nav2_actstby_btn_remapable_cmd.c_str());

         rad1_lower_nav2_actstby_btn_remapable_data = getOptionToString("rad1_lower_nav2_actstby_btn_data");
         Rad1LowrNav2ActStbyRemapableData   = XPLMFindDataRef(rad1_lower_nav2_actstby_btn_remapable_data.c_str());
     }

     // Radio1 Lower Xpdr switch - remapable

     rad1lwrxpdrswitchremap = getOptionToInt("Radio1 Lower Xpdr Switch remapable");
     if (rad1lwrxpdrswitchremap == 777) {
         rad1_lower_xpdr_data_remapable = getOptionToString("rad1_lower_xpdr_data");
         Rad1LowerXpdrRemapableData   = XPLMFindDataRef(rad1_lower_xpdr_data_remapable.c_str());

         rad1_lower_xpdr_mode_remapable = getOptionToString("rad1_lower_xpdr_mode");
         Rad1LowerXpdrRemapableMode   = XPLMFindDataRef(rad1_lower_xpdr_mode_remapable.c_str());

         rad1_lower_xpdr_baro_std_data_remapable = getOptionToString("rad1_lower_xpdr_baro_std_data");
         Rad1LowerXpdrBaroStdRemapableData   = XPLMFindDataRef(rad1_lower_xpdr_baro_std_data_remapable.c_str());

         rad1_lower_xpdr_baro_up_remapable_cmd = getOptionToString("rad1_lower_xpdr_baro_up_cmd");
         Rad1LowrXpdrBaroUpRemapableCmd   = XPLMFindCommand(rad1_lower_xpdr_baro_up_remapable_cmd.c_str());

         rad1_lower_xpdr_baro_dn_remapable_cmd = getOptionToString("rad1_lower_xpdr_baro_dn_cmd");
         Rad1LowrXpdrBaroDnRemapableCmd   = XPLMFindCommand(rad1_lower_xpdr_baro_dn_remapable_cmd.c_str());

     }



     // **************************  Upper Radio2 remaping  ******************************************
    // Radio2 Upper Com1 switch - remapable
    rad2uprcom1switchremap = getOptionToInt("Radio2 Upper Com1 Switch remapable");
    if (rad2uprcom1switchremap == 1) {
        rad2_upper_com1_corse_up_remapable = getOptionToString("rad2_upper_com1_corse_up_cmd");
        Rad2UprCom1CrsUpRemapableCmd   = XPLMFindCommand(rad2_upper_com1_corse_up_remapable.c_str());

        rad2_upper_com1_corse_dn_remapable = getOptionToString("rad2_upper_com1_corse_dn_cmd");
        Rad2UprCom1CrsDnRemapableCmd   = XPLMFindCommand(rad2_upper_com1_corse_dn_remapable.c_str());

        rad2_upper_com1_fine_up_remapable = getOptionToString("rad2_upper_com1_fine_up_cmd");
        Rad2UprCom1FnUpRemapableCmd   = XPLMFindCommand(rad2_upper_com1_fine_up_remapable.c_str());

        rad2_upper_com1_fine_dn_remapable = getOptionToString("rad2_upper_com1_fine_dn_cmd");
        Rad2UprCom1FnDnRemapableCmd   = XPLMFindCommand(rad2_upper_com1_fine_dn_remapable.c_str());

        rad2_upper_com1_act_data_remapable = getOptionToString("rad2_upper_com1_act_data");
        Rad2UpperCom1ActRemapableData   = XPLMFindDataRef(rad2_upper_com1_act_data_remapable.c_str());

        rad2_upper_com1_stby_data_remapable = getOptionToString("rad2_upper_com1_stby_data");
        Rad2UpperCom1StbyRemapableData   = XPLMFindDataRef(rad2_upper_com1_stby_data_remapable.c_str());

    }

    // Radio2 Upper Com1 active stanby button - remapable
    rad2uprcom1actstbybtnremap = getOptionToInt("Radio2 Upper Com1 ActStby remapable");
    if ((rad2uprcom1actstbybtnremap == 1) || (rad2uprcom1actstbybtnremap == 2)) {
        rad2_upper_com1_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_com1_actstby_btn_cmd");
        Rad2UprCom1ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_com1_actstby_btn_remapable_cmd.c_str());

        rad2_upper_com1_actstby_btn_remapable_data = getOptionToString("rad2_upper_com1_actstby_btn_data");
        Rad2UprCom1ActStbyRemapableData   = XPLMFindDataRef(rad2_upper_com1_actstby_btn_remapable_data.c_str());
    }

    // Radio2 Upper Com2 switch - remapable
    rad2uprcom2switchremap = getOptionToInt("Radio2 Upper Com2 Switch remapable");
    if (rad2uprcom2switchremap == 1) {
        rad2_upper_com2_corse_up_remapable = getOptionToString("rad2_upper_com2_corse_up_cmd");
        Rad2UprCom2CrsUpRemapableCmd   = XPLMFindCommand(rad2_upper_com2_corse_up_remapable.c_str());

        rad2_upper_com2_corse_dn_remapable = getOptionToString("rad2_upper_com2_corse_dn_cmd");
        Rad2UprCom2CrsDnRemapableCmd   = XPLMFindCommand(rad2_upper_com2_corse_dn_remapable.c_str());

        rad2_upper_com2_fine_up_remapable = getOptionToString("rad2_upper_com2_fine_up_cmd");
        Rad2UprCom2FnUpRemapableCmd   = XPLMFindCommand(rad2_upper_com2_fine_up_remapable.c_str());

        rad2_upper_com2_fine_dn_remapable = getOptionToString("rad2_upper_com2_fine_dn_cmd");
        Rad2UprCom2FnDnRemapableCmd   = XPLMFindCommand(rad2_upper_com2_fine_dn_remapable.c_str());

        rad2_upper_com2_act_data_remapable = getOptionToString("rad2_upper_com2_act_data");
        Rad2UpperCom2ActRemapableData   = XPLMFindDataRef(rad2_upper_com2_act_data_remapable.c_str());

        rad2_upper_com2_stby_data_remapable = getOptionToString("rad2_upper_com2_stby_data");
        Rad2UpperCom2StbyRemapableData   = XPLMFindDataRef(rad2_upper_com2_stby_data_remapable.c_str());

    }

    // Radio2 Upper Com2 active stanby button - remapable
    rad2uprcom2actstbybtnremap = getOptionToInt("Radio2 Upper Com2 ActStby remapable");
    if ((rad2uprcom2actstbybtnremap == 1) || (rad2uprcom2actstbybtnremap == 2)) {
        rad2_upper_com2_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_com2_actstby_btn_cmd");
        Rad2UprCom2ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_com2_actstby_btn_remapable_cmd.c_str());

        rad2_upper_com2_actstby_btn_remapable_data = getOptionToString("rad2_upper_com2_actstby_btn_data");
        Rad2UprCom2ActStbyRemapableData   = XPLMFindDataRef(rad2_upper_com2_actstby_btn_remapable_data.c_str());
    }

    // Radio2 Upper Nav1 switch - remapable
    rad2uprnav1switchremap = getOptionToInt("Radio2 Upper Nav1 Switch remapable");
    if (rad2uprnav1switchremap == 1) {
        rad2_upper_nav1_corse_up_remapable = getOptionToString("rad2_upper_nav1_corse_up_cmd");
        Rad2UprNav1CrsUpRemapableCmd   = XPLMFindCommand(rad2_upper_nav1_corse_up_remapable.c_str());

        rad2_upper_nav1_corse_dn_remapable = getOptionToString("rad2_upper_nav1_corse_dn_cmd");
        Rad2UprNav1CrsDnRemapableCmd   = XPLMFindCommand(rad2_upper_nav1_corse_dn_remapable.c_str());

        rad2_upper_nav1_fine_up_remapable = getOptionToString("rad2_upper_nav1_fine_up_cmd");
        Rad2UprNav1FnUpRemapableCmd   = XPLMFindCommand(rad2_upper_nav1_fine_up_remapable.c_str());

        rad2_upper_nav1_fine_dn_remapable = getOptionToString("rad2_upper_nav1_fine_dn_cmd");
        Rad2UprNav1FnDnRemapableCmd   = XPLMFindCommand(rad2_upper_nav1_fine_dn_remapable.c_str());

        rad2_upper_nav1_act_data_remapable = getOptionToString("rad2_upper_nav1_act_data");
        Rad2UpperNav1ActRemapableData   = XPLMFindDataRef(rad2_upper_nav1_act_data_remapable.c_str());

        rad2_upper_nav1_stby_data_remapable = getOptionToString("rad2_upper_nav1_stby_data");
        Rad2UpperNav1StbyRemapableData   = XPLMFindDataRef(rad2_upper_nav1_stby_data_remapable.c_str());

    }

    // Radio2 Upper Nav1 active stanby button - remapable
    rad2uprnav1actstbybtnremap = getOptionToInt("Radio2 Upper Nav1 ActStby remapable");
    if (rad2uprnav1actstbybtnremap == 1) {
        rad2_upper_nav1_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_nav1_actstby_btn_cmd");
        Rad2UprNav1ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_nav1_actstby_btn_remapable_cmd.c_str());

        rad2_upper_nav1_actstby_btn_remapable_data = getOptionToString("rad2_upper_nav1_actstby_btn_data");
        Rad2UprNav1ActStbyRemapableData   = XPLMFindDataRef(rad2_upper_nav1_actstby_btn_remapable_data.c_str());
    }

    // Radio2 Upper Nav2 switch - remapable
    rad2uprnav2switchremap = getOptionToInt("Radio2 Upper Nav2 Switch remapable");
    if (rad2uprnav2switchremap == 1) {
        rad2_upper_nav2_corse_up_remapable = getOptionToString("rad2_upper_nav2_corse_up_cmd");
        Rad2UprNav2CrsUpRemapableCmd   = XPLMFindCommand(rad2_upper_nav2_corse_up_remapable.c_str());

        rad2_upper_nav2_corse_dn_remapable = getOptionToString("rad2_upper_nav2_corse_dn_cmd");
        Rad2UprNav2CrsDnRemapableCmd   = XPLMFindCommand(rad2_upper_nav2_corse_dn_remapable.c_str());

        rad2_upper_nav2_fine_up_remapable = getOptionToString("rad2_upper_nav2_fine_up_cmd");
        Rad2UprNav2FnUpRemapableCmd   = XPLMFindCommand(rad2_upper_nav2_fine_up_remapable.c_str());

        rad2_upper_nav2_fine_dn_remapable = getOptionToString("rad2_upper_nav2_fine_dn_cmd");
        Rad2UprNav2FnDnRemapableCmd   = XPLMFindCommand(rad2_upper_nav2_fine_dn_remapable.c_str());

        rad2_upper_nav2_act_data_remapable = getOptionToString("rad2_upper_nav2_act_data");
        Rad2UpperNav2ActRemapableData   = XPLMFindDataRef(rad2_upper_nav2_act_data_remapable.c_str());

        rad2_upper_nav2_stby_data_remapable = getOptionToString("rad2_upper_nav2_stby_data");
        Rad2UpperNav2StbyRemapableData   = XPLMFindDataRef(rad2_upper_nav2_stby_data_remapable.c_str());

    }

    // Radio2 Upper Nav2 active stanby button - remapable
    rad2uprnav2actstbybtnremap = getOptionToInt("Radio2 Upper Nav2 ActStby remapable");
    if (rad2uprnav2actstbybtnremap == 1) {
        rad2_upper_nav2_actstby_btn_remapable_cmd = getOptionToString("rad2_upper_nav2_actstby_btn_cmd");
        Rad2UprNav2ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_nav2_actstby_btn_remapable_cmd.c_str());

        rad2_upper_nav2_actstby_btn_remapable_data = getOptionToString("rad2_upper_nav2_actstby_btn_data");
        Rad2UprNav2ActStbyRemapableData   = XPLMFindDataRef(rad2_upper_nav2_actstby_btn_remapable_data.c_str());
    }


    // Radio2 Upper Xpdr switch - remapable

    rad2uprxpdrswitchremap = getOptionToInt("Radio2 Upper Xpdr Switch remapable");
    if (rad2uprxpdrswitchremap == 777) {
        rad2_upper_xpdr_data_remapable = getOptionToString("rad2_upper_xpdr_data");
        Rad2UpperXpdrRemapableData   = XPLMFindDataRef(rad2_upper_xpdr_data_remapable.c_str());

        rad2_upper_xpdr_mode_remapable = getOptionToString("rad2_upper_xpdr_mode");
        Rad2UpperXpdrRemapableMode   = XPLMFindDataRef(rad2_upper_xpdr_mode_remapable.c_str());

        rad2_upper_xpdr_baro_std_data_remapable = getOptionToString("rad2_upper_xpdr_baro_std_data");
        Rad2UpperXpdrBaroStdRemapableData   = XPLMFindDataRef(rad2_upper_xpdr_baro_std_data_remapable.c_str());

        rad2_upper_xpdr_baro_up_remapable_cmd = getOptionToString("rad2_upper_xpdr_baro_up_cmd");
        Rad2UpperXpdrBaroUpRemapableCmd   = XPLMFindCommand(rad2_upper_xpdr_baro_up_remapable_cmd.c_str());

        rad2_upper_xpdr_baro_dn_remapable_cmd = getOptionToString("rad2_upper_xpdr_baro_dn_cmd");
        Rad2UpperXpdrBaroDnRemapableCmd   = XPLMFindCommand(rad2_upper_xpdr_baro_dn_remapable_cmd.c_str());


    }




    //  *****************************  Lower Radio2 remaping  **************************************
    // Radio2 Lower Com1 switch - remapable
    rad2lwrcom1switchremap = getOptionToInt("Radio2 Lower Com1 Switch remapable");
    if (rad2lwrcom1switchremap == 1) {
        rad2_lower_com1_corse_up_remapable = getOptionToString("rad2_lower_com1_corse_up_cmd");
        Rad2LowrCom1CrsUpRemapableCmd   = XPLMFindCommand(rad2_lower_com1_corse_up_remapable.c_str());

        rad2_lower_com1_corse_dn_remapable = getOptionToString("rad2_lower_com1_corse_dn_cmd");
        Rad2LowrCom1CrsDnRemapableCmd   = XPLMFindCommand(rad2_lower_com1_corse_dn_remapable.c_str());

        rad2_lower_com1_fine_up_remapable = getOptionToString("rad2_lower_com1_fine_up_cmd");
        Rad2LowrCom1FnUpRemapableCmd   = XPLMFindCommand(rad2_lower_com1_fine_up_remapable.c_str());

        rad2_lower_com1_fine_dn_remapable = getOptionToString("rad2_lower_com1_fine_dn_cmd");
        Rad2LowrCom1FnDnRemapableCmd   = XPLMFindCommand(rad2_lower_com1_fine_dn_remapable.c_str());

        rad2_lower_com1_act_data_remapable = getOptionToString("rad2_lower_com1_act_data");
        Rad2LowerCom1ActRemapableData   = XPLMFindDataRef(rad2_lower_com1_act_data_remapable.c_str());

        rad2_lower_com1_stby_data_remapable = getOptionToString("rad2_lower_com1_stby_data");
        Rad2LowerCom1StbyRemapableData   = XPLMFindDataRef(rad2_lower_com1_stby_data_remapable.c_str());

    }

    // Radio2 Lower Com1 active stanby button - remapable
    rad2lwrcom1actstbybtnremap = getOptionToInt("Radio2 Lower Com1 ActStby remapable");
    if ((rad2lwrcom1actstbybtnremap == 1) || (rad2lwrcom1actstbybtnremap == 2)) {
        rad2_lower_com1_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_com1_actstby_btn_cmd");
        Rad2LowrCom1ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_com1_actstby_btn_remapable_cmd.c_str());

        rad2_lower_com1_actstby_btn_remapable_data = getOptionToString("rad2_lower_com1_actstby_btn_data");
        Rad2LowrCom1ActStbyRemapableData   = XPLMFindDataRef(rad2_lower_com1_actstby_btn_remapable_data.c_str());
    }

    // Radio2 Lower Com2 switch - remapable
    rad2lwrcom2switchremap = getOptionToInt("Radio2 Lower Com2 Switch remapable");
    if (rad2lwrcom2switchremap == 1) {
        rad2_lower_com2_corse_up_remapable = getOptionToString("rad2_lower_com2_corse_up_cmd");
        Rad2LowrCom2CrsUpRemapableCmd   = XPLMFindCommand(rad2_lower_com2_corse_up_remapable.c_str());

        rad2_lower_com2_corse_dn_remapable = getOptionToString("rad2_lower_com2_corse_dn_cmd");
        Rad2LowrCom2CrsDnRemapableCmd   = XPLMFindCommand(rad2_lower_com2_corse_dn_remapable.c_str());

        rad2_lower_com2_fine_up_remapable = getOptionToString("rad2_lower_com2_fine_up_cmd");
        Rad2LowrCom2FnUpRemapableCmd   = XPLMFindCommand(rad2_lower_com2_fine_up_remapable.c_str());

        rad2_lower_com2_fine_dn_remapable = getOptionToString("rad2_lower_com2_fine_dn_cmd");
        Rad2LowrCom2FnDnRemapableCmd   = XPLMFindCommand(rad2_lower_com2_fine_dn_remapable.c_str());

        rad2_lower_com2_act_data_remapable = getOptionToString("rad2_lower_com2_act_data");
        Rad2LowerCom2ActRemapableData   = XPLMFindDataRef(rad2_lower_com2_act_data_remapable.c_str());

        rad2_lower_com2_stby_data_remapable = getOptionToString("rad2_lower_com2_stby_data");
        Rad2LowerCom2StbyRemapableData   = XPLMFindDataRef(rad2_lower_com2_stby_data_remapable.c_str());

    }

    // Radio2 Lower Com2 active stanby button - remapable
    rad2lwrcom2actstbybtnremap = getOptionToInt("Radio2 Lower Com2 ActStby remapable");
    if ((rad2lwrcom2actstbybtnremap == 1) || (rad2lwrcom2actstbybtnremap == 2)) {
        rad2_lower_com2_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_com2_actstby_btn_cmd");
        Rad2LowrCom2ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_com2_actstby_btn_remapable_cmd.c_str());

        rad2_lower_com2_actstby_btn_remapable_data = getOptionToString("rad2_lower_com2_actstby_btn_data");
        Rad2LowrCom2ActStbyRemapableData   = XPLMFindDataRef(rad2_lower_com2_actstby_btn_remapable_data.c_str());
    }

    // Radio2 Lower Nav1 switch - remapable
    rad2lwrnav1switchremap = getOptionToInt("Radio2 Lower Nav1 Switch remapable");
    if (rad2lwrnav1switchremap == 1) {
        rad2_lower_nav1_corse_up_remapable = getOptionToString("rad2_lower_nav1_corse_up_cmd");
        Rad2LowrNav1CrsUpRemapableCmd   = XPLMFindCommand(rad2_lower_nav1_corse_up_remapable.c_str());

        rad2_lower_nav1_corse_dn_remapable = getOptionToString("rad2_lower_nav1_corse_dn_cmd");
        Rad2LowrNav1CrsDnRemapableCmd   = XPLMFindCommand(rad2_lower_nav1_corse_dn_remapable.c_str());

        rad2_lower_nav1_fine_up_remapable = getOptionToString("rad2_lower_nav1_fine_up_cmd");
        Rad2LowrNav1FnUpRemapableCmd   = XPLMFindCommand(rad2_lower_nav1_fine_up_remapable.c_str());

        rad2_lower_nav1_fine_dn_remapable = getOptionToString("rad2_lower_nav1_fine_dn_cmd");
        Rad2LowrNav1FnDnRemapableCmd   = XPLMFindCommand(rad2_lower_nav1_fine_dn_remapable.c_str());

        rad2_lower_nav1_act_data_remapable = getOptionToString("rad2_lower_nav1_act_data");
        Rad2LowerNav1ActRemapableData   = XPLMFindDataRef(rad2_lower_nav1_act_data_remapable.c_str());

        rad2_lower_nav1_stby_data_remapable = getOptionToString("rad2_lower_nav1_stby_data");
        Rad2LowerNav1StbyRemapableData   = XPLMFindDataRef(rad2_lower_nav1_stby_data_remapable.c_str());

    }

    // Radio2 Lower Nav1 active stanby button - remapable
    rad2lwrnav1actstbybtnremap = getOptionToInt("Radio2 Lower Nav1 ActStby remapable");
    if (rad2lwrnav1actstbybtnremap == 1) {
        rad2_lower_nav1_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_nav1_actstby_btn_cmd");
        Rad2LowrNav1ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_nav1_actstby_btn_remapable_cmd.c_str());

        rad2_lower_nav1_actstby_btn_remapable_data = getOptionToString("rad2_lower_nav1_actstby_btn_data");
        Rad2LowrNav1ActStbyRemapableData   = XPLMFindDataRef(rad2_lower_nav1_actstby_btn_remapable_data.c_str());
    }

    // Radio2 Lower Nav2 switch - remapable
    rad2lwrnav2switchremap = getOptionToInt("Radio2 Lower Nav2 Switch remapable");
    if (rad2lwrnav2switchremap == 1) {
        rad2_lower_nav2_corse_up_remapable = getOptionToString("rad2_lower_nav2_corse_up_cmd");
        Rad2LowrNav2CrsUpRemapableCmd   = XPLMFindCommand(rad2_lower_nav2_corse_up_remapable.c_str());

        rad2_lower_nav2_corse_dn_remapable = getOptionToString("rad2_lower_nav2_corse_dn_cmd");
        Rad2LowrNav2CrsDnRemapableCmd   = XPLMFindCommand(rad2_lower_nav2_corse_dn_remapable.c_str());

        rad2_lower_nav2_fine_up_remapable = getOptionToString("rad2_lower_nav2_fine_up_cmd");
        Rad2LowrNav2FnUpRemapableCmd   = XPLMFindCommand(rad2_lower_nav2_fine_up_remapable.c_str());

        rad2_lower_nav2_fine_dn_remapable = getOptionToString("rad2_lower_nav2_fine_dn_cmd");
        Rad2LowrNav2FnDnRemapableCmd   = XPLMFindCommand(rad2_lower_nav2_fine_dn_remapable.c_str());

        rad2_lower_nav2_act_data_remapable = getOptionToString("rad2_lower_nav2_act_data");
        Rad2LowerNav2ActRemapableData   = XPLMFindDataRef(rad2_lower_nav2_act_data_remapable.c_str());

        rad2_lower_nav2_stby_data_remapable = getOptionToString("rad2_lower_nav2_stby_data");
        Rad2LowerNav2StbyRemapableData   = XPLMFindDataRef(rad2_lower_nav2_stby_data_remapable.c_str());

    }

    // Radio2 Lower Nav2 active stanby button - remapable
    rad2lwrnav2actstbybtnremap = getOptionToInt("Radio2 Lower Nav2 ActStby remapable");
    if (rad2lwrnav2actstbybtnremap == 1) {
        rad2_lower_nav2_actstby_btn_remapable_cmd = getOptionToString("rad2_lower_nav2_actstby_btn_cmd");
        Rad2LowrNav2ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_nav2_actstby_btn_remapable_cmd.c_str());

        rad2_lower_nav2_actstby_btn_remapable_data = getOptionToString("rad2_lower_nav2_actstby_btn_data");
        Rad2LowrNav2ActStbyRemapableData   = XPLMFindDataRef(rad2_lower_nav2_actstby_btn_remapable_data.c_str());
    }

    // Radio1 Lower Xpdr switch - remapable

    rad2lwrxpdrswitchremap = getOptionToInt("Radio2 Lower Xpdr Switch remapable");
    if (rad2lwrxpdrswitchremap == 777) {
        rad2_lower_xpdr_data_remapable = getOptionToString("rad2_lower_xpdr_data");
        Rad2LowerXpdrRemapableData   = XPLMFindDataRef(rad2_lower_xpdr_data_remapable.c_str());

        rad2_lower_xpdr_mode_remapable = getOptionToString("rad2_lower_xpdr_mode");
        Rad2LowerXpdrRemapableMode   = XPLMFindDataRef(rad2_lower_xpdr_mode_remapable.c_str());

        rad2_lower_xpdr_baro_std_data_remapable = getOptionToString("rad2_lower_xpdr_baro_std_data");
        Rad2LowerXpdrBaroStdRemapableData   = XPLMFindDataRef(rad2_lower_xpdr_baro_std_data_remapable.c_str());

        rad2_lower_xpdr_baro_up_remapable_cmd = getOptionToString("rad2_lower_xpdr_baro_up_cmd");
        Rad2LowrXpdrBaroUpRemapableCmd   = XPLMFindCommand(rad2_lower_xpdr_baro_up_remapable_cmd.c_str());

        rad2_lower_xpdr_baro_dn_remapable_cmd = getOptionToString("rad2_lower_xpdr_baro_dn_cmd");
        Rad2LowrXpdrBaroDnRemapableCmd   = XPLMFindCommand(rad2_lower_xpdr_baro_dn_remapable_cmd.c_str());

    }




//  ***********************   Multi Panel Commands **************************

    multispeed = getOptionToInt("Multi Freq Knob Pulse per Command");
    XPSetWidgetProperty(MultiSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiSpeed4CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiSpeed5CheckWidget[0], xpProperty_ButtonState, 0);
    if (multispeed == 1) {
         XPSetWidgetProperty(MultiSpeed1CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (multispeed == 2) {
         XPSetWidgetProperty(MultiSpeed2CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (multispeed == 3) {
         XPSetWidgetProperty(MultiSpeed3CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (multispeed == 4) {
         XPSetWidgetProperty(MultiSpeed4CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (multispeed == 5) {
         XPSetWidgetProperty(MultiSpeed5CheckWidget[0], xpProperty_ButtonState, 1);
    }

    trimspeed = getOptionToInt("Multi Trim Speed");
    XPSetWidgetProperty(MultiTrimSpeed1CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiTrimSpeed2CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiTrimSpeed3CheckWidget[0], xpProperty_ButtonState, 0);
    if (trimspeed == 1) {
         XPSetWidgetProperty(MultiTrimSpeed1CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (trimspeed == 2) {
         XPSetWidgetProperty(MultiTrimSpeed2CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (trimspeed == 3) {
         XPSetWidgetProperty(MultiTrimSpeed3CheckWidget[0], xpProperty_ButtonState, 1);
    }

    // auto throttle switch - remapable
    autothrottleswitchenable = getOptionToInt("Auto Throttle Switch enable");
    XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonState, 0);
    if (autothrottleswitchenable == 0) {
         XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (autothrottleswitchenable == 1) {
         XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonState, 1);
    }

    // auto throttle switch armed value
    autothrottleswitcharmedvalue = getOptionToInt("Auto Throttle Switch Armed value");

    // alt switch - remapable
    altswitchremap = getOptionToInt("Alt Switch remapable");
    if (altswitchremap == 1) {
       alt_switch_up_remapable = getOptionToString("alt_switch_up_remapable_cmd");
       AltSwitchUpRemapableCmd   = XPLMFindCommand(alt_switch_up_remapable.c_str());
       alt_switch_dn_remapable = getOptionToString("alt_switch_dn_remapable_cmd");
       AltSwitchDnRemapableCmd   = XPLMFindCommand(alt_switch_dn_remapable.c_str());
       alt_switch_data_remapable = getOptionToString("alt_switch_remapable_data");
       AltSwitchRemapableData   = XPLMFindDataRef(alt_switch_data_remapable.c_str());

    } else if (altswitchremap == 2) {
        alt_switch_data_remapable = getOptionToString("alt_switch_remapable_data");
        AltSwitchRemapableData   = XPLMFindDataRef(alt_switch_data_remapable.c_str());

    }

    // vs switch - remapable
    vsswitchremap = getOptionToInt("Vs Switch remapable");
    if (vsswitchremap == 1) {
       vs_switch_up_remapable = getOptionToString("vs_switch_up_remapable_cmd");
       VsSwitchUpRemapableCmd   = XPLMFindCommand(vs_switch_up_remapable.c_str());
       vs_switch_dn_remapable = getOptionToString("vs_switch_dn_remapable_cmd");
       VsSwitchDnRemapableCmd   = XPLMFindCommand(vs_switch_dn_remapable.c_str());
       vs_switch_data_remapable = getOptionToString("vs_switch_remapable_data");
       VsSwitchRemapableData   = XPLMFindDataRef(vs_switch_data_remapable.c_str());

    } else if (vsswitchremap == 2) {
        vs_switch_data_remapable = getOptionToString("vs_switch_remapable_data");
        VsSwitchRemapableData   = XPLMFindDataRef(vs_switch_data_remapable.c_str());
    }

    // ias switch - remapable
    iasswitchremap = getOptionToInt("Ias Switch remapable");
    if (iasswitchremap == 1) {
       ias_switch_up_remapable = getOptionToString("ias_switch_up_remapable_cmd");
       IasSwitchUpRemapableCmd   = XPLMFindCommand(ias_switch_up_remapable.c_str());
       ias_switch_dn_remapable = getOptionToString("ias_switch_dn_remapable_cmd");
       IasSwitchDnRemapableCmd = XPLMFindCommand(ias_switch_dn_remapable.c_str());
       ias_switch_data_remapable = getOptionToString("ias_switch_remapable_data");
       IasSwitchRemapableData = XPLMFindDataRef(ias_switch_data_remapable.c_str());

    } else if (iasswitchremap == 2) {
        ias_switch_data_remapable = getOptionToString("ias_switch_remapable_data");
        IasSwitchRemapableData = XPLMFindDataRef(ias_switch_data_remapable.c_str());
    }

    // hdg switch - remapable
    hdgswitchremap = getOptionToInt("Hdg Switch remapable");
    if (hdgswitchremap == 1) {
       hdg_switch_up_remapable = getOptionToString("hdg_switch_up_remapable_cmd");
       HdgSwitchUpRemapableCmd   = XPLMFindCommand(hdg_switch_up_remapable.c_str());
       hdg_switch_dn_remapable = getOptionToString("hdg_switch_dn_remapable_cmd");
       HdgSwitchDnRemapableCmd = XPLMFindCommand(hdg_switch_dn_remapable.c_str());
       hdg_switch_data_remapable = getOptionToString("hdg_switch_remapable_data");
       HdgSwitchRemapableData = XPLMFindDataRef(hdg_switch_data_remapable.c_str());

    } else if (hdgswitchremap == 2) {
        hdg_switch_data_remapable = getOptionToString("hdg_switch_remapable_data");
        HdgSwitchRemapableData = XPLMFindDataRef(hdg_switch_data_remapable.c_str());
    }

    // crs switch - remapable
    crsswitchremap = getOptionToInt("Crs Switch remapable");
    if (crsswitchremap == 1) {
       crs_switch_up_remapable = getOptionToString("crs_switch_up_remapable_cmd");
       CrsSwitchUpRemapableCmd   = XPLMFindCommand(crs_switch_up_remapable.c_str());
       crs_switch_dn_remapable = getOptionToString("crs_switch_dn_remapable_cmd");
       CrsSwitchDnRemapableCmd = XPLMFindCommand(crs_switch_dn_remapable.c_str());
       crs_switch_data_remapable = getOptionToString("crs_switch_remapable_data");
       CrsSwitchRemapableData = XPLMFindDataRef(crs_switch_data_remapable.c_str());

    } else if (crsswitchremap == 2) {
        crs_switch_data_remapable = getOptionToString("crs_switch_remapable_data");
        CrsSwitchRemapableData = XPLMFindDataRef(crs_switch_data_remapable.c_str());
    }

    // ias ismach - remapable
    iasismachremap = getOptionToInt("Ias Ismach remapable");
    if (iasismachremap == 1) {
        ias_ismach_remapable = getOptionToString("ias_ismach_remapable_data");
        IasIsmachRemapableData = XPLMFindDataRef(ias_ismach_remapable.c_str());
        iasismachvalue = getOptionToInt("ias_ismach_remapable_value");
    }

    // auto throttle switch - remapable
    attrswitchremap = getOptionToInt("Auto Throttle Switch enable");
    if (attrswitchremap == 2) {
         attr_switch_remapable = getOptionToString("auto_throttle_switch_remapable_data");
         AttrSwitchRemapableData   = XPLMFindDataRef(attr_switch_remapable.c_str());
    }


    // Light datareference type
    lightdatareferencetype = getOptionToInt("Light datareference type");

    // ap button - remapable
    apbuttonremap = getOptionToInt("Ap Button remapable");
    if (apbuttonremap == 1) {
         ap_button_remapable = getOptionToString("ap_button_remapable_cmd");
         ApButtonRemapableCmd   = XPLMFindCommand(ap_button_remapable.c_str());
    } else if (apbuttonremap == 2) {
        ap_button_data_remapable = getOptionToString("ap_button_remapable_data");
        ApButtonRemapableData   = XPLMFindDataRef(ap_button_data_remapable.c_str());
    }

    // ap light - remapable
    if ((apbuttonremap == 1) || (apbuttonremap == 2)) {
        ap_light_remapable = getOptionToString("ap_light_remapable_data");
        ApLightRemapableData   = XPLMFindDataRef(ap_light_remapable.c_str());
        ap_light_flash_remapable = getOptionToString("ap_light_flash_remapable_data");
        ApLightFlashRemapableData   = XPLMFindDataRef(ap_light_flash_remapable.c_str());
    }

    // hdg button - remapable
    hdgbuttonremap = getOptionToInt("Hdg Button remapable");
    if (hdgbuttonremap == 1) {
         hdg_button_remapable = getOptionToString("hdg_button_remapable_cmd");
         HdgButtonRemapableCmd   = XPLMFindCommand(hdg_button_remapable.c_str());
    } else  if (hdgbuttonremap == 2) {
        hdg_button_data_remapable = getOptionToString("hdg_button_remapable_data");
        HdgButtonRemapableData   = XPLMFindDataRef(hdg_button_data_remapable.c_str());
    }

    // hdg light - remapable
    if ((hdgbuttonremap == 1) || (hdgbuttonremap == 2)) {
        hdg_light_remapable = getOptionToString("hdg_light_remapable_data");
        HdgLightRemapableData   = XPLMFindDataRef(hdg_light_remapable.c_str());
        hdg_light_flash_remapable = getOptionToString("hdg_light_flash_remapable_data");
        HdgLightFlashRemapableData   = XPLMFindDataRef(hdg_light_flash_remapable.c_str());
    }

    // nav button - remapable
    navbuttonremap = getOptionToInt("Nav Button remapable");
    if (navbuttonremap == 1) {
         nav_button_vorloc_remapable = getOptionToString("nav_button_vorloc_remapable_cmd");
         NavButtonVorlocRemapableCmd   = XPLMFindCommand(nav_button_vorloc_remapable.c_str());
         nav_button_lnav_remapable = getOptionToString("nav_button_lnav_remapable_cmd");
         NavButtonLnavRemapableCmd   = XPLMFindCommand(nav_button_lnav_remapable.c_str());
    } else if (navbuttonremap == 2) {
        nav_button_data_vorloc_remapable = getOptionToString("nav_button_vorloc_remapable_data");
        NavButtonVorlocRemapableData   = XPLMFindDataRef(nav_button_data_vorloc_remapable.c_str());
        nav_button_data_lnav_remapable = getOptionToString("nav_button_lnav_remapable_data");
        NavButtonLnavRemapableData   = XPLMFindDataRef(nav_button_data_lnav_remapable.c_str());
    }

    // nav light - remapable
    if ((navbuttonremap == 1) || (navbuttonremap == 2)) {
        nav_light_vorloc_remapable = getOptionToString("nav_light_vorloc__remapable_data");
        NavLightVorlocRemapableData   = XPLMFindDataRef(nav_light_vorloc_remapable.c_str());
        nav_light_vorloc_flash_remapable = getOptionToString("nav_light_vorloc_flash_remapable_data");
        NavLightVorlocFlashRemapableData   = XPLMFindDataRef(nav_light_vorloc_flash_remapable.c_str());

        nav_light_lnav_remapable = getOptionToString("nav_light_lnav_remapable_data");
        NavLightLnavRemapableData   = XPLMFindDataRef( nav_light_lnav_remapable.c_str());
        nav_light_lnav_flash_remapable = getOptionToString("nav_light_lnav_flash_remapable_data");
        NavLightLnavFlashRemapableData   = XPLMFindDataRef( nav_light_lnav_flash_remapable.c_str());
    }


    // ias button - remapable
    iasbuttonremap = getOptionToInt("Ias Button remapable");
    if (iasbuttonremap == 1) {
         ias_button_remapable = getOptionToString("ias_button_remapable_cmd");
         IasButtonRemapableCmd   = XPLMFindCommand(ias_button_remapable.c_str());
         ias_changeover_button_remapable = getOptionToString("ias_changeover_button_remapable_cmd");
         IasChangeoverButtonRemapableCmd   = XPLMFindCommand(ias_changeover_button_remapable.c_str());
    } else if (iasbuttonremap == 2) {
         ias_button_data_remapable = getOptionToString("ias_button_remapable_data");
         IasButtonRemapableData   = XPLMFindDataRef(ias_button_data_remapable.c_str());
         ias_changeover_button_data_remapable = getOptionToString("ias_changeover_button_remapable_data");
         IasChangeoverButtonRemapableData   = XPLMFindDataRef(ias_changeover_button_data_remapable.c_str());
    }

    // ias light - remapable
    if ((iasbuttonremap == 1) || (iasbuttonremap == 2)) {
        ias_light_remapable = getOptionToString("ias_light_remapable_data");
        IasLightRemapableData   = XPLMFindDataRef(ias_light_remapable.c_str());
        ias_light_flash_remapable = getOptionToString("ias_light_flash_remapable_data");
        IasLightFlashRemapableData   = XPLMFindDataRef(ias_light_flash_remapable.c_str());
    }


    // alt button - remapable
    altbuttonremap = getOptionToInt("Alt Button remapable");
    if (altbuttonremap == 1) {
         alt_button_remapable = getOptionToString("alt_button_remapable_cmd");
         AltButtonRemapableCmd   = XPLMFindCommand(alt_button_remapable.c_str());
    } else if (altbuttonremap == 2) {
        alt_button_data_remapable = getOptionToString("alt_button_remapable_data");
        AltButtonRemapableData   = XPLMFindDataRef(alt_button_data_remapable.c_str());
    }

    // alt light - remapable
    if ((altbuttonremap == 1) || (altbuttonremap == 2)) {
        alt_light_remapable = getOptionToString("alt_light_remapable_data");
        AltLightRemapableData   = XPLMFindDataRef(alt_light_remapable.c_str());
        alt_light_flash_remapable = getOptionToString("alt_light_flash_remapable_data");
        AltLightFlashRemapableData   = XPLMFindDataRef(alt_light_flash_remapable.c_str());
    }

    // vs button - remapable
    vsbuttonremap = getOptionToInt("Vs Button remapable");
    if (vsbuttonremap == 1) {
         vs_button_remapable = getOptionToString("vs_button_remapable_cmd");
         VsButtonRemapableCmd   = XPLMFindCommand(vs_button_remapable.c_str());
    } else if (vsbuttonremap == 2) {
        vs_button_data_remapable = getOptionToString("vs_button_remapable_data");
        VsButtonRemapableData   = XPLMFindDataRef(vs_button_data_remapable.c_str());
    }

    // vs light - remapable
    if ((vsbuttonremap == 1) || (vsbuttonremap == 2)) {
        vs_light_remapable = getOptionToString("vs_light_remapable_data");
        VsLightRemapableData   = XPLMFindDataRef(vs_light_remapable.c_str());
        vs_light_flash_remapable = getOptionToString("vs_light_flash_remapable_data");
        VsLightFlashRemapableData   = XPLMFindDataRef(vs_light_flash_remapable.c_str());
    }

    // apr button - remapable
    aprbuttonremap = getOptionToInt("Apr Button remapable");
    if (aprbuttonremap == 1) {
         apr_button_remapable = getOptionToString("apr_button_remapable_cmd");
         AprButtonRemapableCmd   = XPLMFindCommand(apr_button_remapable.c_str());
    } else  if (aprbuttonremap == 2) {
        apr_button_data_remapable = getOptionToString("apr_button_remapable_data");
        AprButtonRemapableData   = XPLMFindDataRef(apr_button_data_remapable.c_str());
    }

    // apr light - remapable
    if ((aprbuttonremap == 1) || (aprbuttonremap == 2)) {
        apr_light_remapable = getOptionToString("apr_light_remapable_data");
        AprLightRemapableData   = XPLMFindDataRef(apr_light_remapable.c_str());
        apr_light_flash_remapable = getOptionToString("apr_light_flash_remapable_data");
        AprLightFlashRemapableData   = XPLMFindDataRef(apr_light_flash_remapable.c_str());
    }

    // rev button - remapable
    revbuttonremap = getOptionToInt("Rev Button remapable");
    if (revbuttonremap == 1) {
         rev_button_remapable = getOptionToString("rev_button_remapable_cmd");
         RevButtonRemapableCmd   = XPLMFindCommand(rev_button_remapable.c_str());
    } else if (revbuttonremap == 2) {
        rev_button_data_remapable = getOptionToString("rev_button_remapable_data");
        RevButtonRemapableData   = XPLMFindDataRef(rev_button_data_remapable.c_str());
    }

    // rev light - remapable
    if ((revbuttonremap == 1) || (revbuttonremap == 2)) {
        rev_light_remapable = getOptionToString("rev_light_remapable_data");
        RevLightRemapableData   = XPLMFindDataRef(rev_light_remapable.c_str());
        rev_light_flash_remapable = getOptionToString("rev_light_flash_remapable_data");
        RevLightFlashRemapableData   = XPLMFindDataRef(rev_light_flash_remapable.c_str());
    }


    // trim up - remapable
    trimupremap = getOptionToInt("Trim Up remapable");
    if (trimupremap == 1) {
         trim_up_remapable = getOptionToString("trim_up_remapable_cmd");
         TrimUpRemapableCmd   = XPLMFindCommand(trim_up_remapable.c_str());
    }

    // trim dn - remapable
    trimdnremap = getOptionToInt("Trim Dn remapable");
    if (trimdnremap == 1) {
         trim_dn_remapable = getOptionToString("trim_dn_remapable_cmd");
         TrimDnRemapableCmd   = XPLMFindCommand(trim_dn_remapable.c_str());
    }


  return;
}
