// ****** switchdata.cpp **********
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

//  ***** Process Switch Panel Datareferences  *****
void process_switch_register_xsaitekpanels_datareference()

{
    SwitchStartOffOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/startoff/status",
                             xplmType_Int,
                             1,
                             SwitchStartOffPositionGetDataiCallback,
                             SwitchStartOffPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartRightOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/startright/status",
                             xplmType_Int,
                             1,
                             SwitchStartRightPositionGetDataiCallback,
                             SwitchStartRightPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartLeftOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/startleft/status",
                             xplmType_Int,
                             1,
                             SwitchStartLeftPositionGetDataiCallback,
                             SwitchStartLeftPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartBothOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/startboth/status",
                             xplmType_Int,
                             1,
                             SwitchStartBothPositionGetDataiCallback,
                             SwitchStartBothPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartStartOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/startstart/status",
                             xplmType_Int,
                             1,
                             SwitchStartStartPositionGetDataiCallback,
                             SwitchStartStartPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);


    SwitchBatOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/bat/status",
                             xplmType_Int,
                             1,
                             SwitchBatPositionGetDataiCallback,
                             SwitchBatPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);


    SwitchAltOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/alt/status",
                             xplmType_Int,
                             1,
                             SwitchAltPositionGetDataiCallback,
                             SwitchAltPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchAvOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/av/status",
                             xplmType_Int,
                             1,
                             SwitchAvPositionGetDataiCallback,
                             SwitchAvPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchFuelOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/fuel/status",
                             xplmType_Int,
                             1,
                             SwitchFuelPositionGetDataiCallback,
                             SwitchFuelPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchDiceOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/dice/status",
                             xplmType_Int,
                             1,
                             SwitchDicePositionGetDataiCallback,
                             SwitchDicePositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchPitotOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/pitot/status",
                             xplmType_Int,
                             1,
                             SwitchPitotPositionGetDataiCallback,
                             SwitchPitotPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchGearUpOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/gearup/status",
                             xplmType_Int,
                             1,
                             SwitchGearUpPositionGetDataiCallback,
                             SwitchGearUpPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchGearDnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/geardn/status",
                             xplmType_Int,
                             1,
                             SwitchGearDnPositionGetDataiCallback,
                             SwitchGearDnPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchCowlOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/cowl/status",
                             xplmType_Int,
                             1,
                             SwitchCowlPositionGetDataiCallback,
                             SwitchCowlPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);


    SwitchPanelOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/panel/status",
                             xplmType_Int,
                             1,
                             SwitchPanelPositionGetDataiCallback,
                             SwitchPanelPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchBeaconOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/beacon/status",
                             xplmType_Int,
                             1,
                             SwitchBeaconPositionGetDataiCallback,
                             SwitchBeaconPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchNavOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/nav/status",
                             xplmType_Int,
                             1,
                             SwitchNavPositionGetDataiCallback,
                             SwitchNavPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStrobeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/strobe/status",
                             xplmType_Int,
                             1,
                             SwitchStrobePositionGetDataiCallback,
                             SwitchStrobePositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchTaxiOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/taxi/status",
                             xplmType_Int,
                             1,
                             SwitchTaxiPositionGetDataiCallback,
                             SwitchTaxiPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchLandingOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/landing/status",
                             xplmType_Int,
                             1,
                             SwitchLandingPositionGetDataiCallback,
                             SwitchLandingPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);
return;
}

void process_switch_unregister_xsaitekpanels_datareference()

{
    XPLMUnregisterDataAccessor(SwitchStartOffOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchStartRightOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchStartLeftOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchStartBothOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchStartStartOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchBatOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchAltOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchAvOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchFuelOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchDiceOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchPitotOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchGearUpOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchGearDnOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchCowlOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchPanelOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchBeaconOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchNavOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchStrobeOwnedDataRef);


    XPLMUnregisterDataAccessor(SwitchTaxiOwnedDataRef);
    XPLMUnregisterDataAccessor(SwitchStrobeOwnedDataRef);


    return;

}

// Find the X-Plane commands used by the switch panel

void process_switch_find_xplane_commands()

{
    // **************** Find Switch Panel Commands Ref *******************
    ClFlOpn  = XPLMFindCommand("sim/flight_controls/cowl_flaps_open");
    ClFlCls  = XPLMFindCommand("sim/flight_controls/cowl_flaps_closed");
    PtHt0On   = XPLMFindCommand("sim/ice/pitot_heat0_on");
    PtHt0Off  = XPLMFindCommand("sim/ice/pitot_heat0_off");
    PtHt1On   = XPLMFindCommand("sim/ice/pitot_heat1_on");
    PtHt1Off  = XPLMFindCommand("sim/ice/pitot_heat1_off");

    PtHtOn   = XPLMFindCommand("sim/ice/pitot_heat_on");
    PtHtOff  = XPLMFindCommand("sim/ice/pitot_heat_off");

    AvLtOn   = XPLMFindCommand("sim/systems/avionics_on");
    AvLtOff  = XPLMFindCommand("sim/systems/avionics_off");
    BatOn   = XPLMFindCommand("sim/electrical/battery_1_on");
    BatOff  = XPLMFindCommand("sim/electrical/battery_1_off");

    LnLtOn   = XPLMFindCommand("sim/lights/landing_lights_on");
    LnLtOff  = XPLMFindCommand("sim/lights/landing_lights_off");
    TxLtOn   = XPLMFindCommand("sim/lights/taxi_lights_on");
    TxLtOff  = XPLMFindCommand("sim/lights/taxi_lights_off");
    StLtOn   = XPLMFindCommand("sim/lights/strobe_lights_on");
    StLtOff  = XPLMFindCommand("sim/lights/strobe_lights_off");
    NvLtOn   = XPLMFindCommand("sim/lights/nav_lights_on");
    NvLtOff  = XPLMFindCommand("sim/lights/nav_lights_off");
    BcLtOn   = XPLMFindCommand("sim/lights/beacon_lights_on");
    BcLtOff  = XPLMFindCommand("sim/lights/beacon_lights_off");
    GearUp   = XPLMFindCommand("sim/flight_controls/landing_gear_up");
    GearDn   = XPLMFindCommand("sim/flight_controls/landing_gear_down");

    MagOff1   = XPLMFindCommand("sim/magnetos/magnetos_off_1");
    MagOff2   = XPLMFindCommand("sim/magnetos/magnetos_off_2");
    MagOff3   = XPLMFindCommand("sim/magnetos/magnetos_off_3");
    MagOff4   = XPLMFindCommand("sim/magnetos/magnetos_off_4");
    MagOff5   = XPLMFindCommand("sim/magnetos/magnetos_off_5");
    MagOff6   = XPLMFindCommand("sim/magnetos/magnetos_off_6");
    MagOff7   = XPLMFindCommand("sim/magnetos/magnetos_off_7");
    MagOff8   = XPLMFindCommand("sim/magnetos/magnetos_off_8");

    MagLeft1  = XPLMFindCommand("sim/magnetos/magnetos_left_1");
    MagLeft2  = XPLMFindCommand("sim/magnetos/magnetos_left_2");
    MagLeft3  = XPLMFindCommand("sim/magnetos/magnetos_left_3");
    MagLeft4  = XPLMFindCommand("sim/magnetos/magnetos_left_4");
    MagLeft5  = XPLMFindCommand("sim/magnetos/magnetos_left_5");
    MagLeft6  = XPLMFindCommand("sim/magnetos/magnetos_left_6");
    MagLeft7  = XPLMFindCommand("sim/magnetos/magnetos_left_7");
    MagLeft8  = XPLMFindCommand("sim/magnetos/magnetos_left_8");

    MagRight1 = XPLMFindCommand("sim/magnetos/magnetos_right_1");
    MagRight2 = XPLMFindCommand("sim/magnetos/magnetos_right_2");
    MagRight3 = XPLMFindCommand("sim/magnetos/magnetos_right_3");
    MagRight4 = XPLMFindCommand("sim/magnetos/magnetos_right_4");
    MagRight5 = XPLMFindCommand("sim/magnetos/magnetos_right_5");
    MagRight6 = XPLMFindCommand("sim/magnetos/magnetos_right_6");
    MagRight7 = XPLMFindCommand("sim/magnetos/magnetos_right_7");
    MagRight8 = XPLMFindCommand("sim/magnetos/magnetos_right_8");

    MagBoth1  = XPLMFindCommand("sim/magnetos/magnetos_both_1");
    MagBoth2  = XPLMFindCommand("sim/magnetos/magnetos_both_2");
    MagBoth3  = XPLMFindCommand("sim/magnetos/magnetos_both_3");
    MagBoth4  = XPLMFindCommand("sim/magnetos/magnetos_both_4");
    MagBoth5  = XPLMFindCommand("sim/magnetos/magnetos_both_5");
    MagBoth6  = XPLMFindCommand("sim/magnetos/magnetos_both_6");
    MagBoth7  = XPLMFindCommand("sim/magnetos/magnetos_both_7");
    MagBoth8  = XPLMFindCommand("sim/magnetos/magnetos_both_8");

    EngStart1 = XPLMFindCommand("sim/starters/engage_starter_1");
    EngStart2 = XPLMFindCommand("sim/starters/engage_starter_2");
    EngStart3 = XPLMFindCommand("sim/starters/engage_starter_3");
    EngStart4 = XPLMFindCommand("sim/starters/engage_starter_4");
    EngStart5 = XPLMFindCommand("sim/starters/engage_starter_5");
    EngStart6 = XPLMFindCommand("sim/starters/engage_starter_6");
    EngStart7 = XPLMFindCommand("sim/starters/engage_starter_7");
    EngStart8 = XPLMFindCommand("sim/starters/engage_starter_8");

    BatOn1 = XPLMFindCommand("sim/electrical/battery_1_on");
    BatOn2 = XPLMFindCommand("sim/electrical/battery_2_on");
    BatOff1 = XPLMFindCommand("sim/electrical/battery_1_off");
    BatOff2 = XPLMFindCommand("sim/electrical/battery_2_off");

    GenOn1 = XPLMFindCommand("sim/electrical/generator_1_on");
    GenOn2 = XPLMFindCommand("sim/electrical/generator_2_on");
    GenOn3 = XPLMFindCommand("sim/electrical/generator_3_on");
    GenOn4 = XPLMFindCommand("sim/electrical/generator_4_on");
    GenOn5 = XPLMFindCommand("sim/electrical/generator_5_on");
    GenOn6 = XPLMFindCommand("sim/electrical/generator_6_on");
    GenOn7 = XPLMFindCommand("sim/electrical/generator_7_on");
    GenOn8 = XPLMFindCommand("sim/electrical/generator_8_on");

    GenOff1 = XPLMFindCommand("sim/electrical/generator_1_off");
    GenOff2 = XPLMFindCommand("sim/electrical/generator_2_off");
    GenOff3 = XPLMFindCommand("sim/electrical/generator_3_off");
    GenOff4 = XPLMFindCommand("sim/electrical/generator_4_off");
    GenOff5 = XPLMFindCommand("sim/electrical/generator_5_off");
    GenOff6 = XPLMFindCommand("sim/electrical/generator_6_off");
    GenOff7 = XPLMFindCommand("sim/electrical/generator_7_off");
    GenOff8 = XPLMFindCommand("sim/electrical/generator_8_off");

    FuelPumpOn1 = XPLMFindCommand("sim/fuel/fuel_pump_1_on");
    FuelPumpOn2 = XPLMFindCommand("sim/fuel/fuel_pump_2_on");
    FuelPumpOn3 = XPLMFindCommand("sim/fuel/fuel_pump_3_on");
    FuelPumpOn4 = XPLMFindCommand("sim/fuel/fuel_pump_4_on");
    FuelPumpOn5 = XPLMFindCommand("sim/fuel/fuel_pump_5_on");
    FuelPumpOn6 = XPLMFindCommand("sim/fuel/fuel_pump_6_on");
    FuelPumpOn7 = XPLMFindCommand("sim/fuel/fuel_pump_7_on");
    FuelPumpOn8 = XPLMFindCommand("sim/fuel/fuel_pump_8_on");

    FuelPumpOff1 = XPLMFindCommand("sim/fuel/fuel_pump_1_off");
    FuelPumpOff2 = XPLMFindCommand("sim/fuel/fuel_pump_2_off");
    FuelPumpOff3 = XPLMFindCommand("sim/fuel/fuel_pump_3_off");
    FuelPumpOff4 = XPLMFindCommand("sim/fuel/fuel_pump_4_off");
    FuelPumpOff5 = XPLMFindCommand("sim/fuel/fuel_pump_5_off");
    FuelPumpOff6 = XPLMFindCommand("sim/fuel/fuel_pump_6_off");
    FuelPumpOff7 = XPLMFindCommand("sim/fuel/fuel_pump_7_off");
    FuelPumpOff8 = XPLMFindCommand("sim/fuel/fuel_pump_8_off");

    return;
}


// Find the X-Plane datareferences used by the switch panel

void process_switch_find_xplane_datareference()

{
    // **************** Find Switch Panel Data Ref *******************
    AntiIce           = XPLMFindDataRef("sim/cockpit/switches/anti_ice_on");
    CockpitLights     = XPLMFindDataRef("sim/cockpit/electrical/cockpit_lights");
    CowlFlaps         = XPLMFindDataRef("sim/flightmodel/engine/ENGN_cowl");
    GearRetract       = XPLMFindDataRef("sim/aircraft/gear/acf_gear_retract");
    LandingGearStatus = XPLMFindDataRef("sim/aircraft/parts/acf_gear_deploy");
    Gear1Fail         = XPLMFindDataRef("sim/operation/failures/rel_lagear1");
    Gear2Fail         = XPLMFindDataRef("sim/operation/failures/rel_lagear2");
    Gear3Fail         = XPLMFindDataRef("sim/operation/failures/rel_lagear3");

    OnGround          = XPLMFindDataRef("sim/flightmodel/failures/onground_any");

    BatNum            = XPLMFindDataRef("sim/aircraft/electrical/num_batteries");
    GenNum            = XPLMFindDataRef("sim/aircraft/electrical/num_generators");
    EngNum            = XPLMFindDataRef("sim/aircraft/engine/acf_num_engines");
    BatArrayOnDR      = XPLMFindDataRef("sim/cockpit/electrical/battery_array_on");

    IgnSwitchArray    = XPLMFindDataRef("sim/cockpit2/engine/actuators/ignition_key");
    EngnMixt          = XPLMFindDataRef("sim/flightmodel/engine/ENGN_mixt");
    IgniterOn         = XPLMFindDataRef("sim/cockpit2/engine/actuators/igniter_on");
    AcfEnType         = XPLMFindDataRef("sim/aircraft/prop/acf_en_type");

    return;

}
