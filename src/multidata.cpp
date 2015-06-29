// ****** multidata.cpp **********
// ****  William R. Good  ********

#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"

#include "saitekpanels.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

//  ***** Switch Data Process  *****
void process_multi_panel_datareferences()

{
    MultiAltSwitchOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/altswitch/status",
                             xplmType_Int,
                             1,
                             MultiAltSwitchStatusGetDataiCallback,
                             MultiAltSwitchStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiVsSwitchOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/vsswitch/status",
                             xplmType_Int,
                             1,
                             MultiVsSwitchStatusGetDataiCallback,
                             MultiVsSwitchStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiIasSwitchOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/iasswitch/status",
                             xplmType_Int,
                             1,
                             MultiIasSwitchStatusGetDataiCallback,
                             MultiIasSwitchStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiHdgSwitchOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/hdgswitch/status",
                             xplmType_Int,
                             1,
                             MultiHdgSwitchStatusGetDataiCallback,
                             MultiHdgSwitchStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiCrsSwitchOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/crsswitch/status",
                             xplmType_Int,
                             1,
                             MultiCrsSwitchStatusGetDataiCallback,
                             MultiCrsSwitchStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiKnobIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/knobinc/status",
                             xplmType_Int,
                             1,
                             MultiKnobIncStatusGetDataiCallback,
                             MultiKnobIncStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiKnobDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/knobdec/status",
                             xplmType_Int,
                             1,
                             MultiKnobDecStatusGetDataiCallback,
                             MultiKnobDecStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiAtOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/at/status",
                             xplmType_Int,
                             1,
                             MultiAtStatusGetDataiCallback,
                             MultiAtStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiTrimUpOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/trimup/status",
                             xplmType_Int,
                             1,
                             MultiTrimUpStatusGetDataiCallback,
                             MultiTrimUpStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiTrimDnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/trimdn/status",
                             xplmType_Int,
                             1,
                             MultiTrimDnStatusGetDataiCallback,
                             MultiTrimDnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiFlapsUpOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/flapsup/status",
                             xplmType_Int,
                             1,
                             MultiFlapsUpStatusGetDataiCallback,
                             MultiFlapsUpStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiFlapsDnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/flapsdn/status",
                             xplmType_Int,
                             1,
                             MultiFlapsDnStatusGetDataiCallback,
                             MultiFlapsDnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiApBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/apbtn/status",
                             xplmType_Int,
                             1,
                             MultiApBtnStatusGetDataiCallback,
                             MultiApBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiHdgBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/hdgbtn/status",
                             xplmType_Int,
                             1,
                             MultiHdgBtnStatusGetDataiCallback,
                             MultiHdgBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiNavBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/navbtn/status",
                             xplmType_Int,
                             1,
                             MultiNavBtnStatusGetDataiCallback,
                             MultiNavBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiIasBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/iasbtn/status",
                             xplmType_Int,
                             1,
                             MultiIasBtnStatusGetDataiCallback,
                             MultiIasBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiAltBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/altbtn/status",
                             xplmType_Int,
                             1,
                             MultiAltBtnStatusGetDataiCallback,
                             MultiAltBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiVsBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/vsbtn/status",
                             xplmType_Int,
                             1,
                             MultiVsBtnStatusGetDataiCallback,
                             MultiVsBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiAprBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/aprbtn/status",
                             xplmType_Int,
                             1,
                             MultiAprBtnStatusGetDataiCallback,
                             MultiAprBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    MultiRevBtnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/revbtn/status",
                             xplmType_Int,
                             1,
                             MultiRevBtnStatusGetDataiCallback,
                             MultiRevBtnStatusSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

}

void process_multi_unregister_xsaitekpanels_datareference()

{
     XPLMUnregisterDataAccessor(MultiAltSwitchOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiVsSwitchOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiIasSwitchOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiHdgSwitchOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiCrsSwitchOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiKnobIncOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiKnobDecOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiAtOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiTrimUpOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiTrimDnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiFlapsUpOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiFlapsDnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiApBtnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiHdgBtnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiNavBtnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiIasBtnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiAltBtnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiVsBtnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiAprBtnOwnedDataRef);
     XPLMUnregisterDataAccessor(MultiRevBtnOwnedDataRef);

    return;
}

void process_multi_find_xplane_commands()

{
    // ************ Find Multi Panel Commands Ref ***************
      ApAltDn = XPLMFindCommand("sim/autopilot/altitude_down");
      ApAltUp = XPLMFindCommand("sim/autopilot/altitude_up");
      ApVsDn = XPLMFindCommand("sim/autopilot/vertical_speed_down");
      ApVsUp = XPLMFindCommand("sim/autopilot/vertical_speed_up");
      ApAsDn = XPLMFindCommand("sim/autopilot/airspeed_down");
      ApAsUp = XPLMFindCommand("sim/autopilot/airspeed_up");
      ApHdgDn = XPLMFindCommand("sim/autopilot/heading_down");
      ApHdgUp = XPLMFindCommand("sim/autopilot/heading_up");

      ApCrsDn = XPLMFindCommand("sim/radios/obs1_down");
      ApCrsUp = XPLMFindCommand("sim/radios/obs1_up");
      ApCrsDn2 = XPLMFindCommand("sim/radios/obs2_down");
      ApCrsUp2 = XPLMFindCommand("sim/radios/obs2_up");

      ApMstrBtnUp = XPLMFindCommand("sim/autopilot/fdir_servos_up_one");
      ApMstrBtnDn = XPLMFindCommand("sim/autopilot/fdir_servos_down_one");
      ApMstrBtnOff = XPLMFindCommand("sim/autopilot/servos_and_flight_dir_off");
      ApHdgBtn = XPLMFindCommand("sim/autopilot/heading");
      ApNavBtn = XPLMFindCommand("sim/autopilot/NAV");
      ApIasBtn = XPLMFindCommand("sim/autopilot/level_change");
      ApAltBtn = XPLMFindCommand("sim/autopilot/altitude_hold");
      ApAltArmBtn = XPLMFindCommand("sim/autopilot/altitude_arm");
      ApVsBtn = XPLMFindCommand("sim/autopilot/vertical_speed");
      ApAprBtn = XPLMFindCommand("sim/autopilot/approach");
      ApRevBtn = XPLMFindCommand("sim/autopilot/back_course");
      ApKnotsMachTgl = XPLMFindCommand("sim/autopilot/knots_mach_toggle");


      PitchTrimDn = XPLMFindCommand("sim/flight_controls/pitch_trim_down");
      PitchTrimUp = XPLMFindCommand("sim/flight_controls/pitch_trim_up");
      PitchTrimTkOff = XPLMFindCommand("sim/flight_controls/pitch_trim_takeoff");
      FlapsDn = XPLMFindCommand("sim/flight_controls/flaps_down");
      FlapsUp = XPLMFindCommand("sim/flight_controls/flaps_up");

      HsiSelector = XPLMFindDataRef("sim/cockpit/switches/HSI_selector");


    return;

}


void process_multi_find_xplane_datareference()

{
    // **************** Find Multi Panel Data Ref ********************

      ApAlt = XPLMFindDataRef("sim/cockpit/autopilot/altitude");
      ApVs = XPLMFindDataRef("sim/cockpit/autopilot/vertical_velocity");
      ApAs = XPLMFindDataRef("sim/cockpit/autopilot/airspeed");
      ApHdg = XPLMFindDataRef("sim/cockpit/autopilot/heading_mag");

      ApCrs  = XPLMFindDataRef("sim/cockpit/radios/nav1_obs_degm");
      ApCrs2 = XPLMFindDataRef("sim/cockpit/radios/nav2_obs_degm");

      ApMstrStat = XPLMFindDataRef("sim/cockpit2/autopilot/flight_director_mode");
      ApState = XPLMFindDataRef("sim/cockpit/autopilot/autopilot_state");
      ApHdgStat = XPLMFindDataRef("sim/cockpit2/autopilot/heading_status");
      ApNavStat = XPLMFindDataRef("sim/cockpit2/autopilot/nav_status");
      ApIasStat = XPLMFindDataRef("sim/cockpit2/autopilot/speed_status");
      ApAltStat = XPLMFindDataRef("sim/cockpit2/autopilot/altitude_hold_status");
      ApVsStat = XPLMFindDataRef("sim/cockpit2/autopilot/vvi_status");
      ApAprStat = XPLMFindDataRef("sim/cockpit2/autopilot/approach_status");
      ApRevStat = XPLMFindDataRef("sim/cockpit2/autopilot/backcourse_status");

      Frp = XPLMFindDataRef("sim/operation/misc/frame_rate_period");

      MHdg = XPLMFindDataRef("sim/flightmodel/position/magpsi");

      AirspeedIsMach = XPLMFindDataRef("sim/cockpit/autopilot/airspeed_is_mach");
      Airspeed = XPLMFindDataRef("sim/cockpit/autopilot/airspeed");

      ApAutThr = XPLMFindDataRef("sim/cockpit2/autopilot/autothrottle_enabled");


    return;

}



void process_multi_register_xsaitekpanels_datareference()

{

    process_multi_panel_datareferences();
    return;
}
