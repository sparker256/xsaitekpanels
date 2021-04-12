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



        Rad1UpperCorseIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprcorseincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprCorseIncTicksStatusGetDataiCallback,
                                 Rad1UprCorseIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperCorseDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprcorsedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprCorseDecTicksStatusGetDataiCallback,
                                 Rad1UprCorseDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperFineIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprfineincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprFineIncTicksStatusGetDataiCallback,
                                 Rad1UprFineIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperFineDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprfinedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprFineDecTicksStatusGetDataiCallback,
                                 Rad1UprFineDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);





        Rad1UpperActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1upractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad1UprActStbyStatusGetDataiCallback,
                                 Rad1UprActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);





        Rad1UpperDigit1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit1/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit1ValueGetDataiCallback,
                                 Rad1UprDigit1ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad1UpperDigit2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit2/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit2ValueGetDataiCallback,
                                 Rad1UprDigit2ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDigit3OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit3/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit3ValueGetDataiCallback,
                                 Rad1UprDigit3ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDigit4OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit4/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit4ValueGetDataiCallback,
                                 Rad1UprDigit4ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDigit5OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit5/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit5ValueGetDataiCallback,
                                 Rad1UprDigit5ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDigit6OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit6/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit6ValueGetDataiCallback,
                                 Rad1UprDigit6ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDigit7OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit7/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit7ValueGetDataiCallback,
                                 Rad1UprDigit7ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDigit8OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit8/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit8ValueGetDataiCallback,
                                 Rad1UprDigit8ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1UpperDigit9OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit9/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit9ValueGetDataiCallback,
                                 Rad1UprDigit9ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad1UpperDigit10OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1uprdigit10/value",
                                 xplmType_Int,
                                 1,
                                 Rad1UprDigit10ValueGetDataiCallback,
                                 Rad1UprDigit10ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad1WriteNowOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1writenow",
                                 xplmType_Int,
                                 1,
                                 Rad1WriteNowGetDataiCallback,
                                 Rad1WriteNowSetDataiCallback,
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




        Rad1LowerCorseIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrcorseincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrCorseIncTicksStatusGetDataiCallback,
                                 Rad1LwrCorseIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerCorseDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrcorsedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrCorseDecTicksStatusGetDataiCallback,
                                 Rad1LwrCorseDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerFineIncTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrfineincticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrFineIncTicksStatusGetDataiCallback,
                                 Rad1LwrFineIncTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerFineDecTicksOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrfinedecticks/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrFineDecTicksStatusGetDataiCallback,
                                 Rad1LwrFineDecTicksStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);






        Rad1LowerActStbyOwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwractstby/status",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrActStbyStatusGetDataiCallback,
                                 Rad1LwrActStbyStatusSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);




        Rad1LowerDigit1OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit1/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit1ValueGetDataiCallback,
                                 Rad1LwrDigit1ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad1LowerDigit2OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit2/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit2ValueGetDataiCallback,
                                 Rad1LwrDigit2ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDigit3OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit3/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit3ValueGetDataiCallback,
                                 Rad1LwrDigit3ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDigit4OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit4/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit4ValueGetDataiCallback,
                                 Rad1LwrDigit4ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDigit5OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit5/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit5ValueGetDataiCallback,
                                 Rad1LwrDigit5ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDigit6OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit6/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit6ValueGetDataiCallback,
                                 Rad1LwrDigit6ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDigit7OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit7/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit7ValueGetDataiCallback,
                                 Rad1LwrDigit7ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDigit8OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit8/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit8ValueGetDataiCallback,
                                 Rad1LwrDigit8ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);

        Rad1LowerDigit9OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit9/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit9ValueGetDataiCallback,
                                 Rad1LwrDigit9ValueSetDataiCallback,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL);


        Rad1LowerDigit10OwnedDataRef = XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/rad1lwrdigit10/value",
                                 xplmType_Int,
                                 1,
                                 Rad1LwrDigit10ValueGetDataiCallback,
                                 Rad1LwrDigit10ValueSetDataiCallback,
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
    XPLMUnregisterDataAccessor(Rad1UpperCorseIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperCorseDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperFineIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperFineDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperActStbyOwnedDataRef);


    XPLMUnregisterDataAccessor(Rad1UpperDigit1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit3OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit4OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit5OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit6OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit7OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit8OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit9OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1UpperDigit10OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1WriteNowOwnedDataRef);


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
    XPLMUnregisterDataAccessor(Rad1LowerCorseIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerCorseDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerFineIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerFineDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerActStbyOwnedDataRef);


    XPLMUnregisterDataAccessor(Rad1LowerDigit1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit3OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit4OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit5OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit6OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit7OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit8OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit9OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad1LowerDigit10OwnedDataRef);

    return;

}

void process_radio_find_xplane_commands()
{
    // ************ Find Radio Panel Commands Ref ******************
      Com1StbyFineDn = XPLMFindCommand("sim/radios/stby_com1_fine_down");
      Com1StbyFineUp = XPLMFindCommand("sim/radios/stby_com1_fine_up");
      Com1StbyFineDn_833 = XPLMFindCommand("sim/radios/stby_com1_fine_down_833");
      Com1StbyFineUp_833 = XPLMFindCommand("sim/radios/stby_com1_fine_up_833");
      Com1StbyCorseDn = XPLMFindCommand("sim/radios/stby_com1_coarse_down");
      Com1StbyCorseUp = XPLMFindCommand("sim/radios/stby_com1_coarse_up");

      Com2StbyFineDn = XPLMFindCommand("sim/radios/stby_com2_fine_down");
      Com2StbyFineUp = XPLMFindCommand("sim/radios/stby_com2_fine_up");
      Com2StbyFineDn_833 = XPLMFindCommand("sim/radios/stby_com2_fine_down_833");
      Com2StbyFineUp_833 = XPLMFindCommand("sim/radios/stby_com2_fine_up_833");
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

      Afd1StbyHunUp = XPLMFindCommand("sim/radios/stby_adf1_hundreds_thous_up");
      Afd1StbyHunDn = XPLMFindCommand("sim/radios/stby_adf1_hundreds_thous_down");
      Afd1StbyTensUp = XPLMFindCommand("sim/radios/stby_adf1_tens_up");
      Afd1StbyTensDn = XPLMFindCommand("sim/radios/stby_adf1_tens_down");
      Afd1StbyOnesUp = XPLMFindCommand("sim/radios/stby_adf1_ones_up");
      Afd1StbyOnesDn = XPLMFindCommand("sim/radios/stby_adf1_ones_down");

      Afd2StbyHunUp = XPLMFindCommand("sim/radios/stby_adf2_hundreds_thous_up");
      Afd2StbyHunDn = XPLMFindCommand("sim/radios/stby_adf2_hundreds_thous_down");
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
      Com1ActFreq_833 = XPLMFindDataRef("sim/cockpit2/radios/actuators/com1_frequency_hz_833");
      Com2ActFreq = XPLMFindDataRef("sim/cockpit/radios/com2_freq_hz");
      Com2ActFreq_833 = XPLMFindDataRef("sim/cockpit2/radios/actuators/com2_frequency_hz_833");

      Nav1ActFreq = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz");
      Nav2ActFreq = XPLMFindDataRef("sim/cockpit/radios/nav2_freq_hz");

      Com1StbyFreq = XPLMFindDataRef("sim/cockpit/radios/com1_stdby_freq_hz");
      Com1StbyFreq_833 = XPLMFindDataRef("sim/cockpit2/radios/actuators/com1_standby_frequency_hz_833");
      Com2StbyFreq = XPLMFindDataRef("sim/cockpit/radios/com2_stdby_freq_hz");
      Com2StbyFreq_833 = XPLMFindDataRef("sim/cockpit2/radios/actuators/com2_standby_frequency_hz_833");

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

