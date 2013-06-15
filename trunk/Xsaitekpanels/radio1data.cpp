// ****** radio1data.cpp **********
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

//  ***** Radio1 Data Process  *****
void process_radio1_upper_datareference()

{


        Rad1UpperCom1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprcom1/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprCom1StatusGetDataiCallback,
                                 Rad1UprCom1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperCom2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprcom2/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprCom2StatusGetDataiCallback,
                                 Rad1UprCom2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperNav1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprnav1/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprNav1StatusGetDataiCallback,
                                 Rad1UprNav1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperNav2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprnav2/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprNav2StatusGetDataiCallback,
                                 Rad1UprNav2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperAdfOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1upradf/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprAdfStatusGetDataiCallback,
                                 Rad1UprAdfStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDmeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdme/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDmeStatusGetDataiCallback,
                                 Rad1UprDmeStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperXpdrOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprxpdr/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprXpdrStatusGetDataiCallback,
                                 Rad1UprXpdrStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperCorseIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprcorseinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprCorseIncStatusGetDataiCallback,
                                 Rad1UprCorseIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperCorseDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprcorsedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprCorseDecStatusGetDataiCallback,
                                 Rad1UprCorseDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperFineIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprfineinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprFineIncStatusGetDataiCallback,
                                 Rad1UprFineIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperFineDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprfinedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprFineDecStatusGetDataiCallback,
                                 Rad1UprFineDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1upractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprActStbyStatusGetDataiCallback,
                                 Rad1UprActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


}

void process_radio1_lower_datareference()

{



        Rad1LowerCom1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrcom1/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrCom1StatusGetDataiCallback,
                                 Rad1LwrCom1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerCom2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrcom2/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrCom2StatusGetDataiCallback,
                                 Rad1LwrCom2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerNav1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrnav1/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrNav1StatusGetDataiCallback,
                                 Rad1LwrNav1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerNav2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrnav2/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrNav2StatusGetDataiCallback,
                                 Rad1LwrNav2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerAdfOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwradf/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrAdfStatusGetDataiCallback,
                                 Rad1LwrAdfStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDmeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdme/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDmeStatusGetDataiCallback,
                                 Rad1LwrDmeStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerXpdrOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrxpdr/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrXpdrStatusGetDataiCallback,
                                 Rad1LwrXpdrStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerCorseIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrcorseinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrCorseIncStatusGetDataiCallback,
                                 Rad1LwrCorseIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerCorseDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrcorsedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrCorseDecStatusGetDataiCallback,
                                 Rad1LwrCorseDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerFineIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrfineinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrFineIncStatusGetDataiCallback,
                                 Rad1LwrFineIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerFineDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrfinedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrFineDecStatusGetDataiCallback,
                                 Rad1LwrFineDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrActStbyStatusGetDataiCallback,
                                 Rad1LwrActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


}

void process_radio1_unregister_xsaitekpanels_datareference()
{
    XPLMUnregisterDataAccessor(Rad1UpperCom1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperCom2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperNav1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperNav2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperAdfOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDmeOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperXpdrOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperCorseIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperCorseDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperFineIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperFineDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperActStbyOwnedDataRef);

    XPLMUnregisterDataAccessor(Rad1LowerCom1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerCom2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerNav1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerNav2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerAdfOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDmeOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerXpdrOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerCorseIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerCorseDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerFineIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerFineDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerActStbyOwnedDataRef);

    return;

}

void process_radio_find_xplane_commands()
{
    // ************ Find Radio Panel Commands Ref ******************
      Com1StbyFineDn = XPLMFindCommand("sim/radios/stby_com1_fine_down");
      Com1StbyFineUp = XPLMFindCommand("sim/radios/stby_com1_fine_up");
      Com1StbyCorseDn = XPLMFindCommand("sim/radios/stby_com1_coarse_down");
      Com1StbyCorseUp = XPLMFindCommand("sim/radios/stby_com1_coarse_up");

      Com2StbyFineDn = XPLMFindCommand("sim/radios/stby_com2_fine_down");
      Com2StbyFineUp = XPLMFindCommand("sim/radios/stby_com2_fine_up");
      Com2StbyCorseDn = XPLMFindCommand("sim/radios/stby_com2_coarse_down");
      Com2StbyCorseUp = XPLMFindCommand("sim/radios/stby_com2_coarse_up");

      Nav1StbyFineDn = XPLMFindCommand("sim/radios/stby_nav1_fine_down");
      Nav1StbyFineUp = XPLMFindCommand("sim/radios/stby_nav1_fine_up");
      Nav1StbyCorseDn = XPLMFindCommand("sim/radios/stby_nav1_coarse_down");
      Nav1StbyCorseUp = XPLMFindCommand("sim/radios/stby_nav1_coarse_up");

      Nav2StbyFineDn = XPLMFindCommand("sim/radios/stby_nav2_fine_down");
      Nav2StbyFineUp = XPLMFindCommand("sim/radios/stby_nav2_fine_up");
      Nav2StbyCorseDn = XPLMFindCommand("sim/radios/stby_nav2_coarse_down");
      Nav2StbyCorseUp = XPLMFindCommand("sim/radios/stby_nav2_coarse_up");

      Afd1StbyHunUp = XPLMFindCommand("sim/radios/stby_adf1_hundreds_up");
      Afd1StbyHunDn = XPLMFindCommand("sim/radios/stby_adf1_hundreds_down");
      Afd1StbyTensUp = XPLMFindCommand("sim/radios/stby_adf1_tens_up");
      Afd1StbyTensDn = XPLMFindCommand("sim/radios/stby_adf1_tens_down");
      Afd1StbyOnesUp = XPLMFindCommand("sim/radios/stby_adf1_ones_up");
      Afd1StbyOnesDn = XPLMFindCommand("sim/radios/stby_adf1_ones_down");

      Afd2StbyHunUp = XPLMFindCommand("sim/radios/stby_adf2_hundreds_up");
      Afd2StbyHunDn = XPLMFindCommand("sim/radios/stby_adf2_hundreds_down");
      Afd2StbyTensUp = XPLMFindCommand("sim/radios/stby_adf2_tens_up");
      Afd2StbyTensDn = XPLMFindCommand("sim/radios/stby_adf2_tens_down");
      Afd2StbyOnesUp = XPLMFindCommand("sim/radios/stby_adf2_ones_up");
      Afd2StbyOnesDn = XPLMFindCommand("sim/radios/stby_adf2_ones_down");

      XpdrThUp = XPLMFindCommand("sim/transponder/transponder_thousands_up");
      XpdrThDn = XPLMFindCommand("sim/transponder/transponder_thousands_down");
      XpdrHunUp	= XPLMFindCommand("sim/transponder/transponder_hundreds_up");
      XpdrHunDn	= XPLMFindCommand("sim/transponder/transponder_hundreds_down");
      XpdrTensUp = XPLMFindCommand("sim/transponder/transponder_tens_up");
      XpdrTensDn = XPLMFindCommand("sim/transponder/transponder_tens_down");
      XpdrOnesUp = XPLMFindCommand("sim/transponder/transponder_ones_up");
      XpdrOnesDn = XPLMFindCommand("sim/transponder/transponder_ones_down");

      BaroUp = XPLMFindCommand("sim/instruments/barometer_up");
      BaroDn = XPLMFindCommand("sim/instruments/barometer_down");
      BaroStd = XPLMFindCommand("sim/instruments/barometer_2992");

      Com1ActStby = XPLMFindCommand("sim/radios/com1_standy_flip");
      Com2ActStby = XPLMFindCommand("sim/radios/com2_standy_flip");
      Nav1ActStby = XPLMFindCommand("sim/radios/nav1_standy_flip");
      Nav2ActStby = XPLMFindCommand("sim/radios/nav2_standy_flip");
      Adf1ActStby = XPLMFindCommand("sim/radios/adf1_standy_flip");
      Adf2ActStby = XPLMFindCommand("sim/radios/adf2_standy_flip");

      Obs1Down = XPLMFindCommand("sim/radios/obs1_down");
      Obs1Up = XPLMFindCommand("sim/radios/obs1_up");
      Obs2Down = XPLMFindCommand("sim/radios/obs2_down");
      Obs2Up = XPLMFindCommand("sim/radios/obs2_up");

    return;
}

void process_radio_find_xplane_datareference()
{

    // ************ Find Radio Panel Data Ref ******************
      Com1ActFreq = XPLMFindDataRef("sim/cockpit/radios/com1_freq_hz");
      Com2ActFreq = XPLMFindDataRef("sim/cockpit/radios/com2_freq_hz");
      Nav1ActFreq = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz");
      Nav2ActFreq = XPLMFindDataRef("sim/cockpit/radios/nav2_freq_hz");

      Com1StbyFreq = XPLMFindDataRef("sim/cockpit/radios/com1_stdby_freq_hz");
      Com2StbyFreq = XPLMFindDataRef("sim/cockpit/radios/com2_stdby_freq_hz");
      Nav1StbyFreq = XPLMFindDataRef("sim/cockpit/radios/nav1_stdby_freq_hz");
      Nav2StbyFreq = XPLMFindDataRef("sim/cockpit/radios/nav2_stdby_freq_hz");

      Adf1StbyFreq = XPLMFindDataRef("sim/cockpit/radios/adf1_stdby_freq_hz");
      Adf2StbyFreq = XPLMFindDataRef("sim/cockpit/radios/adf2_stdby_freq_hz");
      Adf1ActFreq = XPLMFindDataRef("sim/cockpit/radios/adf1_freq_hz");
      Adf2ActFreq = XPLMFindDataRef("sim/cockpit/radios/adf2_freq_hz");

      XpdrCode = XPLMFindDataRef("sim/cockpit/radios/transponder_code");
      XpdrMode = XPLMFindDataRef("sim/cockpit/radios/transponder_mode");
      BaroSetting = XPLMFindDataRef("sim/cockpit/misc/barometer_setting");
      MetricPress = XPLMFindDataRef("sim/physics/metric_press");

      DmeMode = XPLMFindDataRef("sim/cockpit2/radios/actuators/DME_mode");
      DmeSlvSource = XPLMFindDataRef("sim/cockpit2/radios/actuators/DME_slave_source");


      Nav1DmeNmDist	= XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_distance_nm");
      Nav1DmeSpeed = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_speed_kts");
      Nav2DmeNmDist	= XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_distance_nm");
      Nav2DmeSpeed = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_speed_kts");
      DmeSpeed = XPLMFindDataRef("sim/cockpit2/radios/indicators/dme_dme_speed_kts");

      DmeFreq = XPLMFindDataRef("sim/cockpit2/radios/actuators/dme_frequency_hz");
      DmeTime = XPLMFindDataRef("sim/cockpit2/radios/indicators/dme_dme_time_min");

      AvPwrOn = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
      BatPwrOn = XPLMFindDataRef("sim/cockpit/electrical/battery_on");

      Nav1PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/nav1_power");
      Nav2PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/nav2_power");
      Com1PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/com1_power");
      Com2PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/com2_power");
      Afd1PwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/adf1_power");
      DmePwrOn = XPLMFindDataRef("sim/cockpit2/radios/actuators/dme_power");

      Nav1ObsDegm = XPLMFindDataRef("sim/cockpit/radios/nav1_obs_degm");
      Nav2ObsDegm = XPLMFindDataRef("sim/cockpit/radios/nav2_obs_degm");

      Adf1CardDirDegm = XPLMFindDataRef("sim/cockpit/radios/adf1_cardinal_dir");
      Adf2CardDirDegm = XPLMFindDataRef("sim/cockpit/radios/adf2_cardinal_dir");

    return;

}




void process_radio1_register_xsaitekpanels_datareference()
{
    process_radio1_upper_datareference();
    process_radio1_lower_datareference();

 return;
}

