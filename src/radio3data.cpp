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



        Rad3UpperCorseIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprcorseincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprCorseIncTicksStatusGetDataiCallback,
                                 Rad3UprCorseIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperCorseDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprcorsedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprCorseDecTicksStatusGetDataiCallback,
                                 Rad3UprCorseDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperFineIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprfineincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprFineIncTicksStatusGetDataiCallback,
                                 Rad3UprFineIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperFineDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprfinedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprFineDecTicksStatusGetDataiCallback,
                                 Rad3UprFineDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




        Rad3UpperActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3upractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad3UprActStbyStatusGetDataiCallback,
                                 Rad3UprActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);



        Rad3UpperDigit1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit1/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit1ValueGetDataiCallback,
                                 Rad3UprDigit1ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad3UpperDigit2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit2/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit2ValueGetDataiCallback,
                                 Rad3UprDigit2ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDigit3OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit3/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit3ValueGetDataiCallback,
                                 Rad3UprDigit3ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDigit4OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit4/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit4ValueGetDataiCallback,
                                 Rad3UprDigit4ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDigit5OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit5/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit5ValueGetDataiCallback,
                                 Rad3UprDigit5ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDigit6OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit6/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit6ValueGetDataiCallback,
                                 Rad3UprDigit6ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDigit7OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit7/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit7ValueGetDataiCallback,
                                 Rad3UprDigit7ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDigit8OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit8/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit8ValueGetDataiCallback,
                                 Rad3UprDigit8ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3UpperDigit9OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit9/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit9ValueGetDataiCallback,
                                 Rad3UprDigit9ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad3UpperDigit10OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3uprdigit10/value",
                                 xplmType_Int,
                                 1,
                                 Rad3UprDigit10ValueGetDataiCallback,
                                 Rad3UprDigit10ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad3WriteNowOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3writenow",
                                 xplmType_Int,
                                 1,
                                 Rad3WriteNowGetDataiCallback,
                                 Rad3WriteNowSetDataiCallback,
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




        Rad3LowerCorseIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrcorseincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrCorseIncTicksStatusGetDataiCallback,
                                 Rad3LwrCorseIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerCorseDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrcorsedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrCorseDecTicksStatusGetDataiCallback,
                                 Rad3LwrCorseDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerFineIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrfineincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrFineIncTicksStatusGetDataiCallback,
                                 Rad3LwrFineIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerFineDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrfinedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrFineDecTicksStatusGetDataiCallback,
                                 Rad3LwrFineDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);





        Rad3LowerActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrActStbyStatusGetDataiCallback,
                                 Rad3LwrActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);



        Rad3LowerDigit1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit1/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit1ValueGetDataiCallback,
                                 Rad3LwrDigit1ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad3LowerDigit2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit2/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit2ValueGetDataiCallback,
                                 Rad3LwrDigit2ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDigit3OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit3/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit3ValueGetDataiCallback,
                                 Rad3LwrDigit3ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDigit4OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit4/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit4ValueGetDataiCallback,
                                 Rad3LwrDigit4ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDigit5OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit5/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit5ValueGetDataiCallback,
                                 Rad3LwrDigit5ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDigit6OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit6/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit6ValueGetDataiCallback,
                                 Rad3LwrDigit6ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDigit7OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit7/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit7ValueGetDataiCallback,
                                 Rad3LwrDigit7ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDigit8OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit8/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit8ValueGetDataiCallback,
                                 Rad3LwrDigit8ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad3LowerDigit9OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit9/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit9ValueGetDataiCallback,
                                 Rad3LwrDigit9ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad3LowerDigit10OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad3lwrdigit10/value",
                                 xplmType_Int,
                                 1,
                                 Rad3LwrDigit10ValueGetDataiCallback,
                                 Rad3LwrDigit10ValueSetDataiCallback,
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
    XPLMUnregisterDataAccessor(Rad3UpperCorseIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperCorseDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperFineIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperFineDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperActStbyOwnedDataRef);

    XPLMUnregisterDataAccessor(Rad3UpperDigit1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit3OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit4OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit5OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit6OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit7OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit8OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit9OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3UpperDigit10OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3WriteNowOwnedDataRef);


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
    XPLMUnregisterDataAccessor(Rad3LowerCorseIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerCorseDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerFineIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerFineDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerActStbyOwnedDataRef);


    XPLMUnregisterDataAccessor(Rad3LowerDigit1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit3OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit4OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit5OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit6OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit7OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit8OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit9OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad3LowerDigit10OwnedDataRef);


    return;

}





void process_radio3_register_xsaitekpanels_datareference()
{
    process_radio3_upper_datareference();
    process_radio3_lower_datareference();

 return;
}
