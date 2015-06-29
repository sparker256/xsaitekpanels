// ****** radio3data.cpp **********
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


//  ***** Radio3 Data Process  *****
void process_radio3_upper_datareference()

{
    Rad3UpperCom1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprcom1/status",
                                                         xplmType_Int,
                                                         1,
                                                         Rad3UprCom1StatusGetDataiCallback,
                                                         Rad3UprCom1StatusSetDataiCallback,
                                                         NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                                         NULL, NULL, NULL, NULL, NULL);





        Rad3UpperCom2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprcom2/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprCom2StatusGetDataiCallback,
                                 Rad3UprCom2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




        Rad3UpperNav1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprnav1/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprNav1StatusGetDataiCallback,
                                 Rad3UprNav1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperNav2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprnav2/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprNav2StatusGetDataiCallback,
                                 Rad3UprNav2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperAdfOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3upradf/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprAdfStatusGetDataiCallback,
                                 Rad3UprAdfStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDmeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdme/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDmeStatusGetDataiCallback,
                                 Rad3UprDmeStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperXpdrOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprxpdr/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprXpdrStatusGetDataiCallback,
                                 Rad3UprXpdrStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




        Rad3UpperCorseIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprcorseinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprCorseIncStatusGetDataiCallback,
                                 Rad3UprCorseIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperCorseDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprcorsedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprCorseDecStatusGetDataiCallback,
                                 Rad3UprCorseDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperFineIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprfineinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprFineIncStatusGetDataiCallback,
                                 Rad3UprFineIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperFineDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprfinedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprFineDecStatusGetDataiCallback,
                                 Rad3UprFineDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3upractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprActStbyStatusGetDataiCallback,
                                 Rad3UprActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




}


void process_radio3_lower_datareference()

{




        Rad3LowerCom1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrcom1/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrCom1StatusGetDataiCallback,
                                 Rad3LwrCom1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerCom2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrcom2/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrCom2StatusGetDataiCallback,
                                 Rad3LwrCom2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerNav1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrnav1/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrNav1StatusGetDataiCallback,
                                 Rad3LwrNav1StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerNav2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrnav2/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrNav2StatusGetDataiCallback,
                                 Rad3LwrNav2StatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerAdfOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwradf/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrAdfStatusGetDataiCallback,
                                 Rad3LwrAdfStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDmeOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdme/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDmeStatusGetDataiCallback,
                                 Rad3LwrDmeStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerXpdrOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrxpdr/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrXpdrStatusGetDataiCallback,
                                 Rad3LwrXpdrStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerCorseIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrcorseinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrCorseIncStatusGetDataiCallback,
                                 Rad3LwrCorseIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerCorseDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrcorsedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrCorseDecStatusGetDataiCallback,
                                 Rad3LwrCorseDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerFineIncOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrfineinc/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrFineIncStatusGetDataiCallback,
                                 Rad3LwrFineIncStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerFineDecOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrfinedec/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrFineDecStatusGetDataiCallback,
                                 Rad3LwrFineDecStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrActStbyStatusGetDataiCallback,
                                 Rad3LwrActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


}


void process_radio3_unregister_xsaitekpanels_datareference()
{
    XPLMUnregisterDataAccessor(Rad3UpperCom1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperCom2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperNav1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperNav2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperAdfOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDmeOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperXpdrOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperCorseIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperCorseDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperFineIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperFineDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperActStbyOwnedDataRef);

    XPLMUnregisterDataAccessor(Rad3LowerCom1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerCom2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerNav1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerNav2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerAdfOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDmeOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerXpdrOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerCorseIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerCorseDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerFineIncOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerFineDecOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerActStbyOwnedDataRef);

    return;

}





void process_radio3_register_xsaitekpanels_datareference()
{
    process_radio3_upper_datareference();
    process_radio3_lower_datareference();

 return;
}
