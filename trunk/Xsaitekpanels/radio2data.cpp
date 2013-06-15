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


//  ***** Radio2 Data Process  *****
void process_radio2_upper_datareference()

{
    Rad2UpperCom1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprcom1/status",
                                                         xplmType_Int,
                                                         1,
                                                         Rad2UprCom1StatusGetDataiCallback,
                                                         Rad2UprCom1StatusSetDataiCallback,
                                                         NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                                         NULL, NULL, NULL, NULL, NULL);





        Rad2UpperCom2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprcom2/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprCom2StatusGetDataiCallback,
                                 Rad2UprCom2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




        Rad2UpperNav1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprnav1/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprNav1StatusGetDataiCallback,
                                 Rad2UprNav1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperNav2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprnav2/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprNav2StatusGetDataiCallback,
                                 Rad2UprNav2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperAdfOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2upradf/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprAdfStatusGetDataiCallback,
                                 Rad2UprAdfStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperDmeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprdme/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprDmeStatusGetDataiCallback,
                                 Rad2UprDmeStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperXpdrOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprxpdr/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprXpdrStatusGetDataiCallback,
                                 Rad2UprXpdrStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




        Rad2UpperCorseIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprcorseinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprCorseIncStatusGetDataiCallback,
                                 Rad2UprCorseIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperCorseDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprcorsedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprCorseDecStatusGetDataiCallback,
                                 Rad2UprCorseDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperFineIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprfineinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprFineIncStatusGetDataiCallback,
                                 Rad2UprFineIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperFineDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2uprfinedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprFineDecStatusGetDataiCallback,
                                 Rad2UprFineDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2UpperActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2upractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad2UprActStbyStatusGetDataiCallback,
                                 Rad2UprActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




}


void process_radio2_lower_datareference()

{




        Rad2LowerCom1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrcom1/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrCom1StatusGetDataiCallback,
                                 Rad2LwrCom1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerCom2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrcom2/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrCom2StatusGetDataiCallback,
                                 Rad2LwrCom2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerNav1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrnav1/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrNav1StatusGetDataiCallback,
                                 Rad2LwrNav1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerNav2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrnav2/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrNav2StatusGetDataiCallback,
                                 Rad2LwrNav2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerAdfOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwradf/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrAdfStatusGetDataiCallback,
                                 Rad2LwrAdfStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerDmeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrdme/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrDmeStatusGetDataiCallback,
                                 Rad2LwrDmeStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerXpdrOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrxpdr/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrXpdrStatusGetDataiCallback,
                                 Rad2LwrXpdrStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerCorseIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrcorseinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrCorseIncStatusGetDataiCallback,
                                 Rad2LwrCorseIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerCorseDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrcorsedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrCorseDecStatusGetDataiCallback,
                                 Rad2LwrCorseDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerFineIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrfineinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrFineIncStatusGetDataiCallback,
                                 Rad2LwrFineIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerFineDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwrfinedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrFineDecStatusGetDataiCallback,
                                 Rad2LwrFineDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad2LowerActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad2lwractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad2LwrActStbyStatusGetDataiCallback,
                                 Rad2LwrActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


}


void process_radio2_unregister_xsaitekpanels_datareference()
{
    XPLMUnregisterDataAccessor(Rad2UpperCom1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperCom2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperNav1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperNav2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperAdfOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDmeOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperXpdrOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperCorseIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperCorseDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperFineIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperFineDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperActStbyOwnedDataRef);

    XPLMUnregisterDataAccessor(Rad2LowerCom1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerCom2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerNav1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerNav2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerAdfOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDmeOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerXpdrOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerCorseIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerCorseDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerFineIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerFineDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerActStbyOwnedDataRef);

    return;

}





void process_radio2_register_xsaitekpanels_datareference()
{
    process_radio2_upper_datareference();
    process_radio2_lower_datareference();

 return;
}
