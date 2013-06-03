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
    SwitchStartOffOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/startoff/position",
                             xplmType_Int,
                             1,
                             SwitchStartOffPositionGetDataiCallback,
                             SwitchStartOffPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartRightOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/startright/position",
                             xplmType_Int,
                             1,
                             SwitchStartRightPositionGetDataiCallback,
                             SwitchStartRightPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartLeftOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/startleft/position",
                             xplmType_Int,
                             1,
                             SwitchStartLeftPositionGetDataiCallback,
                             SwitchStartLeftPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartBothOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/startboth/position",
                             xplmType_Int,
                             1,
                             SwitchStartBothPositionGetDataiCallback,
                             SwitchStartBothPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStartStartOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/startstart/position",
                             xplmType_Int,
                             1,
                             SwitchStartStartPositionGetDataiCallback,
                             SwitchStartStartPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);


    SwitchBatOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/bat/position",
                             xplmType_Int,
                             1,
                             SwitchBatPositionGetDataiCallback,
                             SwitchBatPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);


    SwitchAltOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/alt/position",
                             xplmType_Int,
                             1,
                             SwitchAltPositionGetDataiCallback,
                             SwitchAltPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchAvOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/av/position",
                             xplmType_Int,
                             1,
                             SwitchAvPositionGetDataiCallback,
                             SwitchAvPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchFuelOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/fuel/position",
                             xplmType_Int,
                             1,
                             SwitchFuelPositionGetDataiCallback,
                             SwitchFuelPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchDiceOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/dice/position",
                             xplmType_Int,
                             1,
                             SwitchDicePositionGetDataiCallback,
                             SwitchDicePositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchPitotOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/pitot/position",
                             xplmType_Int,
                             1,
                             SwitchPitotPositionGetDataiCallback,
                             SwitchPitotPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchGearUpOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/gearup/position",
                             xplmType_Int,
                             1,
                             SwitchGearUpPositionGetDataiCallback,
                             SwitchGearUpPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchGearDnOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/geardn/position",
                             xplmType_Int,
                             1,
                             SwitchGearDnPositionGetDataiCallback,
                             SwitchGearDnPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchCowlOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/cowl/position",
                             xplmType_Int,
                             1,
                             SwitchCowlPositionGetDataiCallback,
                             SwitchCowlPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);


    SwitchPanelOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/panel/position",
                             xplmType_Int,
                             1,
                             SwitchPanelPositionGetDataiCallback,
                             SwitchPanelPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchBeaconOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/beacon/position",
                             xplmType_Int,
                             1,
                             SwitchBeaconPositionGetDataiCallback,
                             SwitchBeaconPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchNavOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/nav/position",
                             xplmType_Int,
                             1,
                             SwitchNavPositionGetDataiCallback,
                             SwitchNavPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchStrobeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/strobe/position",
                             xplmType_Int,
                             1,
                             SwitchStrobePositionGetDataiCallback,
                             SwitchStrobePositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchTaxiOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/taxi/position",
                             xplmType_Int,
                             1,
                             SwitchTaxiPositionGetDataiCallback,
                             SwitchTaxiPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

    SwitchLandingOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/switch/landing/position",
                             xplmType_Int,
                             1,
                             SwitchLandingPositionGetDataiCallback,
                             SwitchLandingPositionSetDataiCallback,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL);

return;
}
