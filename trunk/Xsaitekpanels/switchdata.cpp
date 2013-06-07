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

//  ***** Switch Data Process  *****
void process_switch_data()

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
