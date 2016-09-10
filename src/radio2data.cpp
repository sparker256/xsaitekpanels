// ****** radio2data.cpp **********
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
    Rad2UpperCom1OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprcom1/status", xplmType_Int, 1,
        Rad2UprCom1StatusGetDataiCallback, Rad2UprCom1StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);





    Rad2UpperCom2OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprcom2/status", xplmType_Int, 1,
        Rad2UprCom2StatusGetDataiCallback, Rad2UprCom2StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);




    Rad2UpperNav1OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprnav1/status", xplmType_Int, 1,
        Rad2UprNav1StatusGetDataiCallback, Rad2UprNav1StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2UpperNav2OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprnav2/status", xplmType_Int, 1,
        Rad2UprNav2StatusGetDataiCallback, Rad2UprNav2StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2UpperAdfOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2upradf/status", xplmType_Int, 1,
        Rad2UprAdfStatusGetDataiCallback, Rad2UprAdfStatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2UpperDmeOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdme/status", xplmType_Int, 1,
        Rad2UprDmeStatusGetDataiCallback, Rad2UprDmeStatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2UpperXpdrOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprxpdr/status", xplmType_Int, 1,
        Rad2UprXpdrStatusGetDataiCallback, Rad2UprXpdrStatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);




    Rad2UpperCorseIncOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprcorseinc/status",
        xplmType_Int, 1, Rad2UprCorseIncStatusGetDataiCallback,
        Rad2UprCorseIncStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperCorseDecOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprcorsedec/status",
        xplmType_Int, 1, Rad2UprCorseDecStatusGetDataiCallback,
        Rad2UprCorseDecStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperFineIncOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprfineinc/status", xplmType_Int,
        1, Rad2UprFineIncStatusGetDataiCallback,
        Rad2UprFineIncStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperFineDecOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprfinedec/status", xplmType_Int,
        1, Rad2UprFineDecStatusGetDataiCallback,
        Rad2UprFineDecStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);




    Rad2UpperCorseIncTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprcorseincticks/status",
        xplmType_Int, 1, Rad2UprCorseIncTicksStatusGetDataiCallback,
        Rad2UprCorseIncTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperCorseDecTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprcorsedecticks/status",
        xplmType_Int, 1, Rad2UprCorseDecTicksStatusGetDataiCallback,
        Rad2UprCorseDecTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperFineIncTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprfineincticks/status",
        xplmType_Int, 1, Rad2UprFineIncTicksStatusGetDataiCallback,
        Rad2UprFineIncTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperFineDecTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprfinedecticks/status",
        xplmType_Int, 1, Rad2UprFineDecTicksStatusGetDataiCallback,
        Rad2UprFineDecTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);




    Rad2UpperActStbyOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2upractstby/status", xplmType_Int,
        1, Rad2UprActStbyStatusGetDataiCallback,
        Rad2UprActStbyStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);



    Rad2UpperDigit1OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit1/value", xplmType_Int,
        1, Rad2UprDigit1ValueGetDataiCallback,
        Rad2UprDigit1ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);


    Rad2UpperDigit2OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit2/value", xplmType_Int,
        1, Rad2UprDigit2ValueGetDataiCallback,
        Rad2UprDigit2ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperDigit3OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit3/value", xplmType_Int,
        1, Rad2UprDigit3ValueGetDataiCallback,
        Rad2UprDigit3ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperDigit4OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit4/value", xplmType_Int,
        1, Rad2UprDigit4ValueGetDataiCallback,
        Rad2UprDigit4ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperDigit5OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit5/value", xplmType_Int,
        1, Rad2UprDigit5ValueGetDataiCallback,
        Rad2UprDigit5ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperDigit6OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit6/value", xplmType_Int,
        1, Rad2UprDigit6ValueGetDataiCallback,
        Rad2UprDigit6ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperDigit7OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit7/value", xplmType_Int,
        1, Rad2UprDigit7ValueGetDataiCallback,
        Rad2UprDigit7ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperDigit8OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit8/value", xplmType_Int,
        1, Rad2UprDigit8ValueGetDataiCallback,
        Rad2UprDigit8ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2UpperDigit9OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit9/value", xplmType_Int,
        1, Rad2UprDigit9ValueGetDataiCallback,
        Rad2UprDigit9ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);


    Rad2UpperDigit10OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2uprdigit10/value", xplmType_Int,
        1, Rad2UprDigit10ValueGetDataiCallback,
        Rad2UprDigit10ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);


    Rad2WriteNowOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2writenow", xplmType_Int, 1,
        Rad2WriteNowGetDataiCallback, Rad2WriteNowSetDataiCallback, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

}


void process_radio2_lower_datareference()
{




    Rad2LowerCom1OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrcom1/status", xplmType_Int, 1,
        Rad2LwrCom1StatusGetDataiCallback, Rad2LwrCom1StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2LowerCom2OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrcom2/status", xplmType_Int, 1,
        Rad2LwrCom2StatusGetDataiCallback, Rad2LwrCom2StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2LowerNav1OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrnav1/status", xplmType_Int, 1,
        Rad2LwrNav1StatusGetDataiCallback, Rad2LwrNav1StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2LowerNav2OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrnav2/status", xplmType_Int, 1,
        Rad2LwrNav2StatusGetDataiCallback, Rad2LwrNav2StatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2LowerAdfOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwradf/status", xplmType_Int, 1,
        Rad2LwrAdfStatusGetDataiCallback, Rad2LwrAdfStatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2LowerDmeOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdme/status", xplmType_Int, 1,
        Rad2LwrDmeStatusGetDataiCallback, Rad2LwrDmeStatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);

    Rad2LowerXpdrOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrxpdr/status", xplmType_Int, 1,
        Rad2LwrXpdrStatusGetDataiCallback, Rad2LwrXpdrStatusSetDataiCallback,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL);




    Rad2LowerCorseIncOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrcorseinc/status",
        xplmType_Int, 1, Rad2LwrCorseIncStatusGetDataiCallback,
        Rad2LwrCorseIncStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerCorseDecOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrcorsedec/status",
        xplmType_Int, 1, Rad2LwrCorseDecStatusGetDataiCallback,
        Rad2LwrCorseDecStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerFineIncOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrfineinc/status", xplmType_Int,
        1, Rad2LwrFineIncStatusGetDataiCallback,
        Rad2LwrFineIncStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerFineDecOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrfinedec/status", xplmType_Int,
        1, Rad2LwrFineDecStatusGetDataiCallback,
        Rad2LwrFineDecStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);




    Rad2LowerCorseIncTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrcorseincticks/status",
        xplmType_Int, 1, Rad2LwrCorseIncTicksStatusGetDataiCallback,
        Rad2LwrCorseIncTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerCorseDecTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrcorsedecticks/status",
        xplmType_Int, 1, Rad2LwrCorseDecTicksStatusGetDataiCallback,
        Rad2LwrCorseDecTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerFineIncTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrfineincticks/status",
        xplmType_Int, 1, Rad2LwrFineIncTicksStatusGetDataiCallback,
        Rad2LwrFineIncTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerFineDecTicksOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrfinedecticks/status",
        xplmType_Int, 1, Rad2LwrFineDecTicksStatusGetDataiCallback,
        Rad2LwrFineDecTicksStatusSetDataiCallback, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);




    Rad2LowerActStbyOwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwractstby/status", xplmType_Int,
        1, Rad2LwrActStbyStatusGetDataiCallback,
        Rad2LwrActStbyStatusSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);




    Rad2LowerDigit1OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit1/value", xplmType_Int,
        1, Rad2LwrDigit1ValueGetDataiCallback,
        Rad2LwrDigit1ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);


    Rad2LowerDigit2OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit2/value", xplmType_Int,
        1, Rad2LwrDigit2ValueGetDataiCallback,
        Rad2LwrDigit2ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerDigit3OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit3/value", xplmType_Int,
        1, Rad2LwrDigit3ValueGetDataiCallback,
        Rad2LwrDigit3ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerDigit4OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit4/value", xplmType_Int,
        1, Rad2LwrDigit4ValueGetDataiCallback,
        Rad2LwrDigit4ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerDigit5OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit5/value", xplmType_Int,
        1, Rad2LwrDigit5ValueGetDataiCallback,
        Rad2LwrDigit5ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerDigit6OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit6/value", xplmType_Int,
        1, Rad2LwrDigit6ValueGetDataiCallback,
        Rad2LwrDigit6ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerDigit7OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit7/value", xplmType_Int,
        1, Rad2LwrDigit7ValueGetDataiCallback,
        Rad2LwrDigit7ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerDigit8OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit8/value", xplmType_Int,
        1, Rad2LwrDigit8ValueGetDataiCallback,
        Rad2LwrDigit8ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    Rad2LowerDigit9OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit9/value", xplmType_Int,
        1, Rad2LwrDigit9ValueGetDataiCallback,
        Rad2LwrDigit9ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);


    Rad2LowerDigit10OwnedDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/radiopanel/rad2lwrdigit10/value", xplmType_Int,
        1, Rad2LwrDigit10ValueGetDataiCallback,
        Rad2LwrDigit10ValueSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);




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
    XPLMUnregisterDataAccessor(Rad2UpperCorseIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperCorseDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperFineIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperFineDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperActStbyOwnedDataRef);

    XPLMUnregisterDataAccessor(Rad2UpperDigit1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit3OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit4OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit5OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit6OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit7OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit8OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit9OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2UpperDigit10OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2WriteNowOwnedDataRef);


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
    XPLMUnregisterDataAccessor(Rad2LowerCorseIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerCorseDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerFineIncTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerFineDecTicksOwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerActStbyOwnedDataRef);

    XPLMUnregisterDataAccessor(Rad2LowerDigit1OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit2OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit3OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit4OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit5OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit6OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit7OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit8OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit9OwnedDataRef);
    XPLMUnregisterDataAccessor(Rad2LowerDigit10OwnedDataRef);

    return;

}





void process_radio2_register_xsaitekpanels_datareference()
{
    process_radio2_upper_datareference();
    process_radio2_lower_datareference();

    return;
}
