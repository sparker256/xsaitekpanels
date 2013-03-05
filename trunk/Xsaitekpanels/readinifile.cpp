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
    starterswitchenable = 1;

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
    autothrottleswitchenable = 1;

    altswitchremap          = 0;
    vsswitchremap           = 0;
    iasswitchremap          = 0;
    hdgswitchremap          = 0;
    crsswitchremap          = 0;



    apbuttonremap           = 0;
    hdgbuttonremap          = 0;
    navbuttonremap          = 0;
    iasbuttonremap          = 0;
    altbuttonremap          = 0;
    vsbuttonremap           = 0;
    aprbuttonremap          = 0;
    revbuttonremap          = 0;

    aplightremap            = 0;
    hdglightremap           = 0;
    navlightremap           = 0;
    iaslightremap           = 0;
    altlightremap           = 0;
    vslightremap            = 0;
    aprlightremap           = 0;
    revlightremap           = 0;

    //apvsupremap             = 0;
    //apvsdnremap             = 0;

    trimupremap             = 0;
    trimdnremap             = 0;

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
    }

    // Radio1 Upper com1 active stanby button - remapable
    rad1uprcom1actstbybtnremap = getOptionToInt("Radio1 Upper Com1 ActStby remapable");
    if (rad1uprcom1actstbybtnremap == 1) {
        rad1_upper_com1_actstby_btn_remapable = getOptionToString("rad1_upper_com1_actstby_btn_cmd");
        Rad1UprCom1ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_com1_actstby_btn_remapable.c_str());
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
    }

    // Radio1 Upper com2 active stanby button - remapable
    rad1uprcom2actstbybtnremap = getOptionToInt("Radio1 Upper Com2 ActStby remapable");
    if (rad1uprcom2actstbybtnremap == 1) {
        rad1_upper_com2_actstby_btn_remapable = getOptionToString("rad1_upper_com2_actstby_btn_cmd");
        Rad1UprCom2ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_com2_actstby_btn_remapable.c_str());
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
    }

    // Radio1 Upper Nav1 active stanby button - remapable
    rad1uprnav1actstbybtnremap = getOptionToInt("Radio1 Upper Nav1 ActStby remapable");
    if (rad1uprnav1actstbybtnremap == 1) {
        rad1_upper_nav1_actstby_btn_remapable = getOptionToString("rad1_upper_nav1_actstby_btn_cmd");
        Rad1UprNav1ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_nav1_actstby_btn_remapable.c_str());
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
    }

    // Radio1 Upper Nav2 active stanby button - remapable
    rad1uprnav2actstbybtnremap = getOptionToInt("Radio1 Upper Nav2 ActStby remapable");
    if (rad1uprnav2actstbybtnremap == 1) {
        rad1_upper_nav2_actstby_btn_remapable = getOptionToString("rad1_upper_nav2_actstby_btn_cmd");
        Rad1UprNav2ActStbyRemapableCmd   = XPLMFindCommand(rad1_upper_nav2_actstby_btn_remapable.c_str());
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

    }

    // Radio1 Lower Com1 active stanby button - remapable
    rad1lwrcom1actstbybtnremap = getOptionToInt("Radio1 Lower Com1 ActStby remapable");
    if (rad1lwrcom1actstbybtnremap == 1) {
        rad1_lower_com1_actstby_btn_remapable = getOptionToString("rad1_lower_com1_actstby_btn_cmd");
        Rad1LowrCom1ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_com1_actstby_btn_remapable.c_str());
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
    }

    // Radio1 Lower Com2 active stanby button - remapable
    rad1lwrcom2actstbybtnremap = getOptionToInt("Radio1 Lower Com2 ActStby remapable");
    if (rad1lwrcom2actstbybtnremap == 1) {
        rad1_lower_com2_actstby_btn_remapable = getOptionToString("rad1_lower_com2_actstby_btn_cmd");
        Rad1LowrCom2ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_com2_actstby_btn_remapable.c_str());
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

    }

    // Radio1 Lower Nav1 active stanby button - remapable
    rad1lwrnav1actstbybtnremap = getOptionToInt("Radio1 Lower Nav1 ActStby remapable");
    if (rad1lwrnav1actstbybtnremap == 1) {
        rad1_lower_nav1_actstby_btn_remapable = getOptionToString("rad1_lower_nav1_actstby_btn_cmd");
        Rad1LowrNav1ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_nav1_actstby_btn_remapable.c_str());
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

     }

     // Radio1 Lower Nav2 active stanby button - remapable
     rad1lwrnav2actstbybtnremap = getOptionToInt("Radio1 Lower Nav2 ActStby remapable");
     if (rad1lwrnav2actstbybtnremap == 1) {
         rad1_lower_nav2_actstby_btn_remapable = getOptionToString("rad1_lower_nav2_actstby_btn_cmd");
         Rad1LowrNav2ActStbyRemapableCmd   = XPLMFindCommand(rad1_lower_nav2_actstby_btn_remapable.c_str());
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
    }

    // Radio2 Upper Com1 active stanby button - remapable
    rad2uprcom1actstbybtnremap = getOptionToInt("Radio2 Upper Com1 ActStby remapable");
    if (rad2uprcom1actstbybtnremap == 1) {
        rad2_upper_com1_actstby_btn_remapable = getOptionToString("rad2_upper_com1_actstby_btn_cmd");
        Rad2UprCom1ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_com1_actstby_btn_remapable.c_str());
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
    }

    // Radio2 Upper Com2 active stanby button - remapable
    rad2uprcom2actstbybtnremap = getOptionToInt("Radio2 Upper Com2 ActStby remapable");
    if (rad2uprcom2actstbybtnremap == 1) {
        rad2_upper_com2_actstby_btn_remapable = getOptionToString("rad2_upper_com2_actstby_btn_cmd");
        Rad2UprCom2ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_com2_actstby_btn_remapable.c_str());
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
    }

    // Radio2 Upper Nav1 active stanby button - remapable
    rad2uprnav1actstbybtnremap = getOptionToInt("Radio2 Upper Nav1 ActStby remapable");
    if (rad2uprnav1actstbybtnremap == 1) {
        rad2_upper_nav1_actstby_btn_remapable = getOptionToString("rad2_upper_nav1_actstby_btn_cmd");
        Rad2UprNav1ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_nav1_actstby_btn_remapable.c_str());
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
    }

    // Radio2 Upper Nav2 active stanby button - remapable
    rad2uprnav2actstbybtnremap = getOptionToInt("Radio2 Upper Nav2 ActStby remapable");
    if (rad2uprnav2actstbybtnremap == 1) {
        rad2_upper_nav2_actstby_btn_remapable = getOptionToString("rad2_upper_nav2_actstby_btn_cmd");
        Rad2UprNav2ActStbyRemapableCmd   = XPLMFindCommand(rad2_upper_nav2_actstby_btn_remapable.c_str());
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
    }

    // Radio2 Lower Com1 active stanby button - remapable
    rad2lwrcom1actstbybtnremap = getOptionToInt("Radio2 Lower Com1 ActStby remapable");
    if (rad2lwrcom1actstbybtnremap == 1) {
        rad2_lower_com1_actstby_btn_remapable = getOptionToString("rad2_lower_com1_actstby_btn_cmd");
        Rad2LowrCom1ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_com1_actstby_btn_remapable.c_str());
    }

    // Radio2 Lower Com2 switch - remapable
    rad2lwrcom2switchremap = getOptionToInt("Radio2 Lower Com2 Switch remapable");
    if (rad2lwrcom2switchremap == 1) {
        rad2_lower_com2_corse_up_remapable = getOptionToString("rad2_lower_com2_corse_up_cmd");
        Rad2LowrCom2CrsUpRemapableCmd   = XPLMFindCommand(rad2_lower_com2_corse_up_remapable.c_str());

        rad2_lower_com2_corse_dn_remapable = getOptionToString("rad2_lower_com2_corse_dn_cmd");
        Rad2LowrCom2CrsDnRemapableCmd   = XPLMFindCommand(rad2_lower_com2_corse_dn_remapable.c_str());

        rad2_lower_com2_fine_up_remapable = getOptionToString("rad2_lower_com2_fine_up_cmd");
        Rad2LowrCom2FnUpRemapableCmd   = XPLMFindCommand(rad2_lower_com1_fine_up_remapable.c_str());

        rad2_lower_com2_fine_dn_remapable = getOptionToString("rad2_lower_com2_fine_dn_cmd");
        Rad2LowrCom2FnDnRemapableCmd   = XPLMFindCommand(rad2_lower_com2_fine_dn_remapable.c_str());
    }

    // Radio2 Lower Com2 active stanby button - remapable
    rad2lwrcom2actstbybtnremap = getOptionToInt("Radio2 Lower Com2 ActStby remapable");
    if (rad2lwrcom2actstbybtnremap == 1) {
        rad2_lower_com2_actstby_btn_remapable = getOptionToString("rad2_lower_com2_actstby_btn_cmd");
        Rad2LowrCom2ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_com2_actstby_btn_remapable.c_str());
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
    }

    // Radio2 Lower Nav1 active stanby button - remapable
    rad2lwrnav1actstbybtnremap = getOptionToInt("Radio2 Lower Nav1 ActStby remapable");
    if (rad2lwrnav1actstbybtnremap == 1) {
        rad2_lower_nav1_actstby_btn_remapable = getOptionToString("rad2_lower_nav1_actstby_btn_cmd");
        Rad2LowrNav1ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_nav1_actstby_btn_remapable.c_str());
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
    }

    // Radio2 Lower Nav2 active stanby button - remapable
    rad2lwrnav2actstbybtnremap = getOptionToInt("Radio2 Lower Nav2 ActStby remapable");
    if (rad2lwrnav2actstbybtnremap == 1) {
        rad2_lower_nav2_actstby_btn_remapable = getOptionToString("rad2_lower_nav2_actstby_btn_cmd");
        Rad2LowrNav2ActStbyRemapableCmd   = XPLMFindCommand(rad2_lower_nav2_actstby_btn_remapable.c_str());
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


    autothrottleswitchenable = getOptionToInt("Auto Throttle Switch enable");
    XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonState, 0);
    XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonState, 0);
    if (autothrottleswitchenable == 0) {
         XPSetWidgetProperty(MultiAt0CheckWidget[0], xpProperty_ButtonState, 1);
    }
    if (autothrottleswitchenable == 1) {
         XPSetWidgetProperty(MultiAt1CheckWidget[0], xpProperty_ButtonState, 1);
    }

    // alt switch - remapable
    altswitchremap = getOptionToInt("Alt Switch remapable");
    if (altswitchremap == 1) {
       alt_switch_up_remapable = getOptionToString("alt_switch_up_remapable_cmd");
       AltSwitchUpRemapableCmd   = XPLMFindCommand(alt_switch_up_remapable.c_str());
       alt_switch_dn_remapable = getOptionToString("alt_switch_dn_remapable_cmd");
       AltSwitchDnRemapableCmd   = XPLMFindCommand(alt_switch_dn_remapable.c_str());

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

    } else if (crsswitchremap == 2) {
        crs_switch_data_remapable = getOptionToString("crs_switch_remapable_data");
        CrsSwitchRemapableData = XPLMFindDataRef(crs_switch_data_remapable.c_str());
    }

    // ias ismach - remapable
    iasismachremap = getOptionToInt("Ias Ismach remapable");
    if (iasismachremap == 1) {
        ias_ismach_remapable = getOptionToString("ias_ismach_remapable_data");
        IasIsmachRemapableData = XPLMFindCommand(ias_ismach_remapable.c_str());
        iasismachvalue = getOptionToInt("ias_ismach_remapable_value");
    }


    // ap button - remapable
    apbuttonremap = getOptionToInt("Ap Button remapable");
    if (apbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         ap_button_remapable = getOptionToString("ap_button_remapable_cmd");
         ApButtonRemapableCmd   = XPLMFindCommand(ap_button_remapable.c_str());
    }

    // ap light - remapable
    aplightremap = getOptionToInt("Ap Light remapable");
    if (aplightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         ap_light_remapable = getOptionToString("ap_light_remapable_data");
         ApLightRemapableData   = XPLMFindDataRef(ap_light_remapable.c_str());
    }

    // hdg button - remapable
    hdgbuttonremap = getOptionToInt("Hdg Button remapable");
    if (hdgbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         hdg_button_remapable = getOptionToString("hdg_button_remapable_cmd");
         HdgButtonRemapableCmd   = XPLMFindCommand(hdg_button_remapable.c_str());
    }

    // hdg light - remapable
    hdglightremap = getOptionToInt("Hdg Light remapable");
    if (hdglightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         hdg_light_remapable = getOptionToString("hdg_light_remapable_data");
         HdgLightRemapableData   = XPLMFindDataRef(hdg_light_remapable.c_str());
    }

    // nav button - remapable
    navbuttonremap = getOptionToInt("Nav Button remapable");
    if (navbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         nav_button_remapable = getOptionToString("nav_button_remapable_cmd");
         NavButtonRemapableCmd   = XPLMFindCommand(nav_button_remapable.c_str());
    }

    // nav light - remapable
    navlightremap = getOptionToInt("Nav Light remapable");
    if (navlightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         nav_light_remapable = getOptionToString("nav_light_remapable_data");
         NavLightRemapableData   = XPLMFindDataRef(nav_light_remapable.c_str());
    }

    // ias button - remapable
    iasbuttonremap = getOptionToInt("Ias Button remapable");
    if (iasbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         ias_button_remapable = getOptionToString("ias_button_remapable_cmd");
         IasButtonRemapableCmd   = XPLMFindCommand(ias_button_remapable.c_str());
    }

    // ias light - remapable
    iasbuttonremap = getOptionToInt("Ias Light remapable");
    if (iaslightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         ias_light_remapable = getOptionToString("ias_light_remapable_data");
         IasLightRemapableData   = XPLMFindDataRef(ias_light_remapable.c_str());
    }


    // alt button - remapable
    altbuttonremap = getOptionToInt("Alt Button remapable");
    if (altbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         alt_button_remapable = getOptionToString("alt_button_remapable_cmd");
         AltButtonRemapableCmd   = XPLMFindCommand(alt_button_remapable.c_str());
    }

    // alt light - remapable
    altbuttonremap = getOptionToInt("Alt Light remapable");
    if (altlightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         alt_light_remapable = getOptionToString("alt_light_remapable_data");
         AltLightRemapableData   = XPLMFindDataRef(alt_light_remapable.c_str());
    }

    // vs button - remapable
    vsbuttonremap = getOptionToInt("Vs Button remapable");
    if (vsbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         vs_button_remapable = getOptionToString("vs_button_remapable_cmd");
         VsButtonRemapableCmd   = XPLMFindCommand(vs_button_remapable.c_str());
    }

    // vs light - remapable
    vslightremap = getOptionToInt("Vs Light remapable");
    if (vslightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         vs_light_remapable = getOptionToString("vs_light_remapable_data");
         VsLightRemapableData   = XPLMFindDataRef(vs_light_remapable.c_str());
    }

    // apr button - remapable
    aprbuttonremap = getOptionToInt("Apr Button remapable");
    if (aprbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         apr_button_remapable = getOptionToString("apr_button_remapable_cmd");
         AprButtonRemapableCmd   = XPLMFindCommand(apr_button_remapable.c_str());
    }

    // apr light - remapable
    aprbuttonremap = getOptionToInt("Apr Light remapable");
    if (aprlightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         apr_light_remapable = getOptionToString("apr_light_remapable_data");
         AprLightRemapableData   = XPLMFindDataRef(apr_light_remapable.c_str());
    }

    // rev button - remapable
    revbuttonremap = getOptionToInt("Rev Button remapable");
    if (revbuttonremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         rev_button_remapable = getOptionToString("rev_button_remapable_cmd");
         RevButtonRemapableCmd   = XPLMFindCommand(rev_button_remapable.c_str());
    }

    // rev light - remapable
    revbuttonremap = getOptionToInt("Rev Light remapable");
    if (revlightremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
         rev_light_remapable = getOptionToString("rev_light_remapable_data");
         RevLightRemapableData   = XPLMFindDataRef(rev_light_remapable.c_str());
    }


    // trim up - remapable
    trimupremap = getOptionToInt("Trim Up remapable");
    if (trimupremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
        // ApVsUp
         trim_up_remapable = getOptionToString("trim_up_remapable_cmd");
         TrimUpRemapableCmd   = XPLMFindCommand(trim_up_remapable.c_str());
    }

    // trim dn - remapable
    trimdnremap = getOptionToInt("Trim Dn remapable");
    if (trimdnremap == 1) {
         //XPSetWidgetProperty(SwitchRemapCheckWidget[16], xpProperty_ButtonState, 1);
        // ApVsUp
         trim_dn_remapable = getOptionToString("trim_dn_remapable_cmd");
         TrimDnRemapableCmd   = XPLMFindCommand(trim_dn_remapable.c_str());
    }


  return;
}
