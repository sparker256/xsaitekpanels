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


void process_radio1_data()
{
    process_radio1_upper_datareference();
    process_radio1_lower_datareference();

 return;
}

