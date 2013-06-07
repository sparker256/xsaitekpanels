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

void process_multi_data()

{

    process_multi_panel_datareferences();
    return;
}
