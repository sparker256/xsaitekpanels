// ****** saitekpanels.cpp ***********
// ****  William R. Good   ***********
// ****** Nov 27 2016   **************
#define PLUGIN_VERSION "3.00 0stable build " __DATE__ " " __TIME__
#define PLUGIN_VERSION_NUMBER 300
#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMPlugin.h"
#include "XPLMPlanes.h"
#include "XPLMMenus.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"
#define MSG_ADD_DATAREF 0x01000000
#include "hidapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <string>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <wchar.h>
#include <errno.h>

#include "Log.h"
#include "saitekpanels.h"
#include "multipanel.h"

using namespace std;
using namespace xsaitekpanels;

// ************* Radio Panel Command Ref ****************
XPLMCommandRef Com1StbyFineDn = NULL,
    Com1StbyFineUp = NULL,
    Com1StbyCorseDn = NULL,
    Com1StbyCorseUp = NULL;
XPLMCommandRef Com1StbyFineDn_833 = NULL,
    Com1StbyFineUp_833 = NULL;
XPLMCommandRef Com2StbyFineDn = NULL,
    Com2StbyFineUp = NULL,
    Com2StbyCorseDn = NULL,
    Com2StbyCorseUp = NULL;
XPLMCommandRef Com2StbyFineDn_833 = NULL,
    Com2StbyFineUp_833 = NULL;
XPLMCommandRef Nav1StbyFineDn = NULL,
    Nav1StbyFineUp = NULL,
    Nav1StbyCorseDn = NULL,
    Nav1StbyCorseUp = NULL;
XPLMCommandRef Nav2StbyFineDn = NULL,
    Nav2StbyFineUp = NULL,
    Nav2StbyCorseDn = NULL,
    Nav2StbyCorseUp = NULL;

XPLMCommandRef Afd1StbyHunUp = NULL,
    Afd1StbyHunDn = NULL,
    Afd1StbyTensUp = NULL,
    Afd1StbyTensDn = NULL;
XPLMCommandRef Afd1StbyOnesUp = NULL,
    Afd1StbyOnesDn = NULL;

XPLMCommandRef Afd2StbyHunUp = NULL,
    Afd2StbyHunDn = NULL,
    Afd2StbyTensUp = NULL,
    Afd2StbyTensDn = NULL;
XPLMCommandRef Afd2StbyOnesUp = NULL,
    Afd2StbyOnesDn = NULL;

XPLMCommandRef XpdrThUp = NULL,
    XpdrThDn = NULL,
    XpdrHunUp = NULL,
    XpdrHunDn = NULL;
XPLMCommandRef XpdrTensUp = NULL,
    XpdrTensDn = NULL,
    XpdrOnesUp = NULL,
    XpdrOnesDn = NULL;
XPLMCommandRef BaroUp = NULL,
    BaroDn = NULL,
    BaroStd = NULL;


XPLMCommandRef Com1ActStby = NULL,
    Com2ActStby = NULL,
    Nav1ActStby = NULL,
    Nav2ActStby = NULL;
XPLMCommandRef Adf1ActStby = NULL,
    Adf2ActStby = NULL;

XPLMCommandRef Obs1Down = NULL,
    Obs1Up = NULL;
XPLMCommandRef Obs2Down = NULL,
    Obs2Up = NULL;

XPLMCommandRef Rad1UprCom1CrsUpRemapableCmd = NULL,
    Rad1UprCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom1FnUpRemapableCmd = NULL,
    Rad1UprCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom2CrsUpRemapableCmd = NULL,
    Rad1UprCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom2FnUpRemapableCmd = NULL,
    Rad1UprCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprObs1CrsUpRemapableCmd = NULL,
    Rad1UprObs1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprObs1FnUpRemapableCmd = NULL,
    Rad1UprObs1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav1CrsUpRemapableCmd = NULL,
    Rad1UprNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav1FnUpRemapableCmd = NULL,
    Rad1UprNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprObs2CrsUpRemapableCmd = NULL,
    Rad1UprObs2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprObs2FnUpRemapableCmd = NULL,
    Rad1UprObs2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav2CrsUpRemapableCmd = NULL,
    Rad1UprNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav2FnUpRemapableCmd = NULL,
    Rad1UprNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprNav2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprAdfCrsUpRemapableCmd = NULL,
    Rad1UprAdfCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprAdfFnUpRemapableCmd = NULL,
    Rad1UprAdfFnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprAdfActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UprDmeCrsUpRemapableCmd = NULL,
    Rad1UprDmeCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprDmeFnUpRemapableCmd = NULL,
    Rad1UprDmeFnDnRemapableCmd = NULL;
XPLMCommandRef Rad1UprDmeActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1UpperXpdrBaroUpRemapableCmd = NULL,
    Rad1UpperXpdrBaroDnRemapableCmd = NULL;


XPLMCommandRef Rad1LowrCom1CrsUpRemapableCmd = NULL,
    Rad1LowrCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom1FnUpRemapableCmd = NULL,
    Rad1LowrCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom2CrsUpRemapableCmd = NULL,
    Rad1LowrCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom2FnUpRemapableCmd = NULL,
    Rad1LowrCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrObs1CrsUpRemapableCmd = NULL,
    Rad1LowrObs1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrObs1FnUpRemapableCmd = NULL,
    Rad1LowrObs1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav1CrsUpRemapableCmd = NULL,
    Rad1LowrNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav1FnUpRemapableCmd = NULL,
    Rad1LowrNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrObs2CrsUpRemapableCmd = NULL,
    Rad1LowrObs2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrObs2FnUpRemapableCmd = NULL,
    Rad1LowrObs2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav2CrsUpRemapableCmd = NULL,
    Rad1LowrNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav2FnUpRemapableCmd = NULL,
    Rad1LowrNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrNav2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrAdfCrsUpRemapableCmd = NULL,
    Rad1LowrAdfCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrAdfFnUpRemapableCmd = NULL,
    Rad1LowrAdfFnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrAdfActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrDmeCrsUpRemapableCmd = NULL,
    Rad1LowrDmeCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrDmeFnUpRemapableCmd = NULL,
    Rad1LowrDmeFnDnRemapableCmd = NULL;
XPLMCommandRef Rad1LowrDmeActStbyRemapableCmd = NULL;
XPLMCommandRef Rad1LowrXpdrBaroUpRemapableCmd = NULL,
    Rad1LowrXpdrBaroDnRemapableCmd = NULL;


XPLMCommandRef Rad2UprCom1CrsUpRemapableCmd = NULL,
    Rad2UprCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom1FnUpRemapableCmd = NULL,
    Rad2UprCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom2CrsUpRemapableCmd = NULL,
    Rad2UprCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom2FnUpRemapableCmd = NULL,
    Rad2UprCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprObs1CrsUpRemapableCmd = NULL,
    Rad2UprObs1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprObs1FnUpRemapableCmd = NULL,
    Rad2UprObs1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav1CrsUpRemapableCmd = NULL,
    Rad2UprNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav1FnUpRemapableCmd = NULL,
    Rad2UprNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprObs2CrsUpRemapableCmd = NULL,
    Rad2UprObs2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprObs2FnUpRemapableCmd = NULL,
    Rad2UprObs2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav2CrsUpRemapableCmd = NULL,
    Rad2UprNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav2FnUpRemapableCmd = NULL,
    Rad2UprNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprNav2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprAdfCrsUpRemapableCmd = NULL,
    Rad2UprAdfCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprAdfFnUpRemapableCmd = NULL,
    Rad2UprAdfFnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprAdfActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UprDmeCrsUpRemapableCmd = NULL,
    Rad2UprDmeCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprDmeFnUpRemapableCmd = NULL,
    Rad2UprDmeFnDnRemapableCmd = NULL;
XPLMCommandRef Rad2UprDmeActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2UpperXpdrBaroUpRemapableCmd = NULL,
    Rad2UpperXpdrBaroDnRemapableCmd = NULL;


XPLMCommandRef Rad2LowrCom1CrsUpRemapableCmd = NULL,
    Rad2LowrCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom1FnUpRemapableCmd = NULL,
    Rad2LowrCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom2CrsUpRemapableCmd = NULL,
    Rad2LowrCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom2FnUpRemapableCmd = NULL,
    Rad2LowrCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrObs1CrsUpRemapableCmd = NULL,
    Rad2LowrObs1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrObs1FnUpRemapableCmd = NULL,
    Rad2LowrObs1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav1CrsUpRemapableCmd = NULL,
    Rad2LowrNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav1FnUpRemapableCmd = NULL,
    Rad2LowrNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrObs2CrsUpRemapableCmd = NULL,
    Rad2LowrObs2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrObs2FnUpRemapableCmd = NULL,
    Rad2LowrObs2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav2CrsUpRemapableCmd = NULL,
    Rad2LowrNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav2FnUpRemapableCmd = NULL,
    Rad2LowrNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrNav2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrAdfCrsUpRemapableCmd = NULL,
    Rad2LowrAdfCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrAdfFnUpRemapableCmd = NULL,
    Rad2LowrAdfFnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrAdfActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrDmeCrsUpRemapableCmd = NULL,
    Rad2LowrDmeCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrDmeFnUpRemapableCmd = NULL,
    Rad2LowrDmeFnDnRemapableCmd = NULL;
XPLMCommandRef Rad2LowrDmeActStbyRemapableCmd = NULL;
XPLMCommandRef Rad2LowrXpdrBaroUpRemapableCmd = NULL,
    Rad2LowrXpdrBaroDnRemapableCmd = NULL;


XPLMCommandRef Rad3UprCom1CrsUpRemapableCmd = NULL,
    Rad3UprCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprCom1FnUpRemapableCmd = NULL,
    Rad3UprCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3UprCom2CrsUpRemapableCmd = NULL,
    Rad3UprCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprCom2FnUpRemapableCmd = NULL,
    Rad3UprCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3UprObs1CrsUpRemapableCmd = NULL,
    Rad3UprObs1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprObs1FnUpRemapableCmd = NULL,
    Rad3UprObs1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprNav1CrsUpRemapableCmd = NULL,
    Rad3UprNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprNav1FnUpRemapableCmd = NULL,
    Rad3UprNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3UprObs2CrsUpRemapableCmd = NULL,
    Rad3UprObs2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprObs2FnUpRemapableCmd = NULL,
    Rad3UprObs2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprNav2CrsUpRemapableCmd = NULL,
    Rad3UprNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprNav2FnUpRemapableCmd = NULL,
    Rad3UprNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprNav2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3UprAdfCrsUpRemapableCmd = NULL,
    Rad3UprAdfCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprAdfFnUpRemapableCmd = NULL,
    Rad3UprAdfFnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprAdfActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3UprDmeCrsUpRemapableCmd = NULL,
    Rad3UprDmeCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprDmeFnUpRemapableCmd = NULL,
    Rad3UprDmeFnDnRemapableCmd = NULL;
XPLMCommandRef Rad3UprDmeActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3UpperXpdrBaroUpRemapableCmd = NULL,
    Rad3UpperXpdrBaroDnRemapableCmd = NULL;


XPLMCommandRef Rad3LowrCom1CrsUpRemapableCmd = NULL,
    Rad3LowrCom1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrCom1FnUpRemapableCmd = NULL,
    Rad3LowrCom1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrCom1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3LowrCom2CrsUpRemapableCmd = NULL,
    Rad3LowrCom2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrCom2FnUpRemapableCmd = NULL,
    Rad3LowrCom2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrCom2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3LowrObs1CrsUpRemapableCmd = NULL,
    Rad3LowrObs1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrObs1FnUpRemapableCmd = NULL,
    Rad3LowrObs1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrNav1CrsUpRemapableCmd = NULL,
    Rad3LowrNav1CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrNav1FnUpRemapableCmd = NULL,
    Rad3LowrNav1FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrNav1ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3LowrObs2CrsUpRemapableCmd = NULL,
    Rad3LowrObs2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrObs2FnUpRemapableCmd = NULL,
    Rad3LowrObs2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrNav2CrsUpRemapableCmd = NULL,
    Rad3LowrNav2CrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrNav2FnUpRemapableCmd = NULL,
    Rad3LowrNav2FnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrNav2ActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3LowrAdfCrsUpRemapableCmd = NULL,
    Rad3LowrAdfCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrAdfFnUpRemapableCmd = NULL,
    Rad3LowrAdfFnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrAdfActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3LowrDmeCrsUpRemapableCmd = NULL,
    Rad3LowrDmeCrsDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrDmeFnUpRemapableCmd = NULL,
    Rad3LowrDmeFnDnRemapableCmd = NULL;
XPLMCommandRef Rad3LowrDmeActStbyRemapableCmd = NULL;
XPLMCommandRef Rad3LowrXpdrBaroUpRemapableCmd = NULL,
    Rad3LowrXpdrBaroDnRemapableCmd = NULL;


// ************* Radio Panel Data Ref ****************
XPLMDataRef Com1ActFreq = NULL,
    Com2ActFreq = NULL,
    Nav1ActFreq = NULL,
    Nav2ActFreq = NULL;
XPLMDataRef Com1ActFreq_833 = NULL,
    Com2ActFreq_833 = NULL;
XPLMDataRef Com1StbyFreq = NULL,
    Com2StbyFreq = NULL,
    Nav1StbyFreq = NULL,
    Nav2StbyFreq = NULL;
XPLMDataRef Com1StbyFreq_833 = NULL,
    Com2StbyFreq_833 = NULL;

XPLMDataRef Adf1StbyFreq = NULL,
    Adf2StbyFreq = NULL;
XPLMDataRef Adf1ActFreq = NULL,
    Adf2ActFreq = NULL;

XPLMDataRef XpdrCode = NULL,
    XpdrMode = NULL,
    BaroSetting = NULL;
XPLMDataRef MetricPress = NULL;

XPLMDataRef DmeMode = NULL,
    DmeSlvSource = NULL;
XPLMDataRef Nav1DmeNmDist = NULL,
    Nav1DmeSpeed = NULL;
XPLMDataRef Nav2DmeNmDist = NULL,
    Nav2DmeSpeed = NULL;
XPLMDataRef DmeFreq = NULL,
    DmeTime = NULL,
    DmeSpeed = NULL;

XPLMDataRef AvPwrOn = NULL,
    BatPwrOn = NULL;
int AvPwrOnConfig = 0,
    BatPwrOnConfig = 0;
XPLMDataRef AvPwrOnCustomDataref = NULL,
    BatPwrOnCustomDataref = NULL;

XPLMDataRef Nav1PwrOn = NULL,
    Nav2PwrOn = NULL,
    Com1PwrOn = NULL,
    Com2PwrOn = NULL;
XPLMDataRef Afd1PwrOn = NULL,
    DmePwrOn = NULL;

XPLMDataRef Nav1ObsDegm = NULL,
    Nav2ObsDegm = NULL;
XPLMDataRef Adf1CardDirDegm = NULL,
    Adf2CardDirDegm = NULL;


XPLMDataRef Rad1UpperCom1ActRemapableData = NULL,
    Rad1UpperCom1StbyRemapableData = NULL;
XPLMDataRef Rad1UprCom1ActStbyRemapableData = NULL,
    Rad1UprCom1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad1UpperCom2ActRemapableData = NULL,
    Rad1UpperCom2StbyRemapableData = NULL;
XPLMDataRef Rad1UprCom2ActStbyRemapableData = NULL,
    Rad1UprCom2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad1UpperNav1ActRemapableData = NULL,
    Rad1UpperNav1StbyRemapableData = NULL;
XPLMDataRef Rad1UprNav1ActStbyRemapableData = NULL,
    Rad1UprNav1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad1UpperNav2ActRemapableData = NULL,
    Rad1UpperNav2StbyRemapableData = NULL;
XPLMDataRef Rad1UprNav2ActStbyRemapableData = NULL,
    Rad1UprNav2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad1UpperObs1RemapableDataf = NULL,
    Rad1UpperObs2RemapableDataf = NULL;
XPLMDataRef Rad1UpperAdfActRemapableData = NULL,
    Rad1UpperAdfStbyRemapableData = NULL;
XPLMDataRef Rad1UprAdfActStbyRemapableData = NULL,
    Rad1UprAdfActStbyRemapableDataf = NULL;
XPLMDataRef Rad1UpperDmeActRemapableData = NULL,
    Rad1UpperDmeStbyRemapableData = NULL;
XPLMDataRef Rad1UpperXpdrRemapableData = NULL,
    Rad1UpperXpdrRemapableMode = NULL,
    Rad1UpperXpdrBaroStdRemapableData = NULL;

XPLMDataRef RadioPanelCountDataRef = NULL;

XPLMDataRef Rad1LowerCom1ActRemapableData = NULL,
    Rad1LowerCom1StbyRemapableData = NULL;
XPLMDataRef Rad1LowrCom1ActStbyRemapableData = NULL,
    Rad1LowrCom1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad1LowerCom2ActRemapableData = NULL,
    Rad1LowerCom2StbyRemapableData = NULL;
XPLMDataRef Rad1LowrCom2ActStbyRemapableData = NULL,
    Rad1LowrCom2ActStbyRemapableDataf;
XPLMDataRef Rad1LowerNav1ActRemapableData = NULL,
    Rad1LowerNav1StbyRemapableData = NULL;
XPLMDataRef Rad1LowrNav1ActStbyRemapableData = NULL,
    Rad1LowrNav1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad1LowerNav2ActRemapableData = NULL,
    Rad1LowerNav2StbyRemapableData = NULL;
XPLMDataRef Rad1LowrNav2ActStbyRemapableData = NULL,
    Rad1LowrNav2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad1LowerObs1RemapableDataf = NULL,
    Rad1LowerObs2RemapableDataf = NULL;
XPLMDataRef Rad1LowerAdfActRemapableData = NULL,
    Rad1LowerAdfStbyRemapableData = NULL;
XPLMDataRef Rad1LowrAdfActStbyRemapableData = NULL,
    Rad1LowrAdfActStbyRemapableDataf = NULL;
XPLMDataRef Rad1LowerDmeActRemapableData = NULL,
    Rad1LowerDmeStbyRemapableData = NULL;
XPLMDataRef Rad1LowerXpdrRemapableData = NULL,
    Rad1LowerXpdrRemapableMode = NULL,
    Rad1LowerXpdrBaroStdRemapableData = NULL;


XPLMDataRef Rad2UpperCom1ActRemapableData = NULL,
    Rad2UpperCom1StbyRemapableData = NULL;
XPLMDataRef Rad2UprCom1ActStbyRemapableData = NULL,
    Rad2UprCom1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2UpperCom2ActRemapableData = NULL,
    Rad2UpperCom2StbyRemapableData = NULL;
XPLMDataRef Rad2UprCom2ActStbyRemapableData = NULL,
    Rad2UprCom2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2UpperNav1ActRemapableData = NULL,
    Rad2UpperNav1StbyRemapableData = NULL;
XPLMDataRef Rad2UprNav1ActStbyRemapableData = NULL,
    Rad2UprNav1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2UpperNav2ActRemapableData = NULL,
    Rad2UpperNav2StbyRemapableData = NULL;
XPLMDataRef Rad2UprNav2ActStbyRemapableData = NULL,
    Rad2UprNav2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2UpperObs1RemapableDataf = NULL,
    Rad2UpperObs2RemapableDataf = NULL;
XPLMDataRef Rad2UpperAdfActRemapableData = NULL,
    Rad2UpperAdfStbyRemapableData;
XPLMDataRef Rad2UprAdfActStbyRemapableData = NULL,
    Rad2UprAdfActStbyRemapableDataf = NULL;
XPLMDataRef Rad2UpperDmeActRemapableData = NULL,
    Rad2UpperDmeStbyRemapableData = NULL;
XPLMDataRef Rad2UpperXpdrRemapableData = NULL,
    Rad2UpperXpdrRemapableMode = NULL,
    Rad2UpperXpdrBaroStdRemapableData = NULL;


XPLMDataRef Rad2LowerCom1ActRemapableData = NULL,
    Rad2LowerCom1StbyRemapableData = NULL;
XPLMDataRef Rad2LowrCom1ActStbyRemapableData = NULL,
    Rad2LowrCom1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2LowerCom2ActRemapableData = NULL,
    Rad2LowerCom2StbyRemapableData = NULL;
XPLMDataRef Rad2LowrCom2ActStbyRemapableData = NULL,
    Rad2LowrCom2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2LowerNav1ActRemapableData = NULL,
    Rad2LowerNav1StbyRemapableData = NULL;
XPLMDataRef Rad2LowrNav1ActStbyRemapableData = NULL,
    Rad2LowrNav1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2LowerNav2ActRemapableData = NULL,
    Rad2LowerNav2StbyRemapableData = NULL;
XPLMDataRef Rad2LowrNav2ActStbyRemapableData = NULL,
    Rad2LowrNav2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad2LowerObs1RemapableDataf = NULL,
    Rad2LowerObs2RemapableDataf = NULL;
XPLMDataRef Rad2LowerAdfActRemapableData = NULL,
    Rad2LowerAdfStbyRemapableData = NULL;
XPLMDataRef Rad2LowrAdfActStbyRemapableData = NULL,
    Rad2LowrAdfActStbyRemapableDataf = NULL;
XPLMDataRef Rad2LowerDmeActRemapableData = NULL,
    Rad2LowerDmeStbyRemapableData = NULL;
XPLMDataRef Rad2LowerXpdrRemapableData = NULL,
    Rad2LowerXpdrRemapableMode = NULL,
    Rad2LowerXpdrBaroStdRemapableData = NULL;


XPLMDataRef Rad3UpperCom1ActRemapableData = NULL,
    Rad3UpperCom1StbyRemapableData = NULL;
XPLMDataRef Rad3UprCom1ActStbyRemapableData = NULL,
    Rad3UprCom1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3UpperCom2ActRemapableData = NULL,
    Rad3UpperCom2StbyRemapableData = NULL;
XPLMDataRef Rad3UprCom2ActStbyRemapableData = NULL,
    Rad3UprCom2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3UpperNav1ActRemapableData = NULL,
    Rad3UpperNav1StbyRemapableData = NULL;
XPLMDataRef Rad3UprNav1ActStbyRemapableData = NULL,
    Rad3UprNav1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3UpperNav2ActRemapableData = NULL,
    Rad3UpperNav2StbyRemapableData = NULL;
XPLMDataRef Rad3UprNav2ActStbyRemapableData = NULL,
    Rad3UprNav2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3UpperObs1RemapableDataf = NULL,
    Rad3UpperObs2RemapableDataf = NULL;
XPLMDataRef Rad3UpperAdfActRemapableData = NULL,
    Rad3UpperAdfStbyRemapableData = NULL;
XPLMDataRef Rad3UprAdfActStbyRemapableData = NULL,
    Rad3UprAdfActStbyRemapableDataf = NULL;
XPLMDataRef Rad3UpperDmeActRemapableData = NULL,
    Rad3UpperDmeStbyRemapableData = NULL;
XPLMDataRef Rad3UpperXpdrRemapableData = NULL,
    Rad3UpperXpdrRemapableMode = NULL,
    Rad3UpperXpdrBaroStdRemapableData = NULL;


XPLMDataRef Rad3LowerCom1ActRemapableData = NULL,
    Rad3LowerCom1StbyRemapableData = NULL;
XPLMDataRef Rad3LowrCom1ActStbyRemapableData = NULL,
    Rad3LowrCom1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3LowerCom2ActRemapableData = NULL,
    Rad3LowerCom2StbyRemapableData = NULL;
XPLMDataRef Rad3LowrCom2ActStbyRemapableData = NULL,
    Rad3LowrCom2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3LowerNav1ActRemapableData = NULL,
    Rad3LowerNav1StbyRemapableData = NULL;
XPLMDataRef Rad3LowrNav1ActStbyRemapableData = NULL,
    Rad3LowrNav1ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3LowerNav2ActRemapableData = NULL,
    Rad3LowerNav2StbyRemapableData = NULL;
XPLMDataRef Rad3LowrNav2ActStbyRemapableData = NULL,
    Rad3LowrNav2ActStbyRemapableDataf = NULL;
XPLMDataRef Rad3LowerObs1RemapableDataf = NULL,
    Rad3LowerObs2RemapableDataf = NULL;
XPLMDataRef Rad3LowerAdfActRemapableData = NULL,
    Rad3LowerAdfStbyRemapableData = NULL;
XPLMDataRef Rad3LowrAdfActStbyRemapableData = NULL,
    Rad3LowrAdfActStbyRemapableDataf = NULL;
XPLMDataRef Rad3LowerDmeActRemapableData = NULL,
    Rad3LowerDmeStbyRemapableData = NULL;
XPLMDataRef Rad3LowerXpdrRemapableData = NULL,
    Rad3LowerXpdrRemapableMode = NULL,
    Rad3LowerXpdrBaroStdRemapableData = NULL;


XPLMDataRef Rad1UpperCom1OwnedDataRef = NULL,
    Rad1UpperCom2OwnedDataRef = NULL;
XPLMDataRef Rad1UpperNav1OwnedDataRef = NULL,
    Rad1UpperNav2OwnedDataRef = NULL;
XPLMDataRef Rad1UpperAdfOwnedDataRef = NULL,
    Rad1UpperDmeOwnedDataRef = NULL;
XPLMDataRef Rad1UpperXpdrOwnedDataRef = NULL,
    Rad1UpperActStbyOwnedDataRef = NULL;

XPLMDataRef Rad1UpperFineIncOwnedDataRef = NULL,
    Rad1UpperFineDecOwnedDataRef = NULL;
XPLMDataRef Rad1UpperCorseIncOwnedDataRef = NULL,
    Rad1UpperCorseDecOwnedDataRef = NULL;

XPLMDataRef Rad1UpperFineIncTicksOwnedDataRef = NULL,
    Rad1UpperFineDecTicksOwnedDataRef = NULL;
XPLMDataRef Rad1UpperCorseIncTicksOwnedDataRef = NULL,
    Rad1UpperCorseDecTicksOwnedDataRef = NULL;


XPLMDataRef Rad1UpperDigit1OwnedDataRef = NULL,
    Rad1UpperDigit2OwnedDataRef = NULL;
XPLMDataRef Rad1UpperDigit3OwnedDataRef = NULL,
    Rad1UpperDigit4OwnedDataRef = NULL;
XPLMDataRef Rad1UpperDigit5OwnedDataRef = NULL,
    Rad1UpperDigit6OwnedDataRef = NULL;
XPLMDataRef Rad1UpperDigit7OwnedDataRef = NULL,
    Rad1UpperDigit8OwnedDataRef = NULL;
XPLMDataRef Rad1UpperDigit9OwnedDataRef = NULL,
    Rad1UpperDigit10OwnedDataRef = NULL;
XPLMDataRef Rad1WriteNowOwnedDataRef = NULL;


XPLMDataRef Rad1LowerCom1OwnedDataRef = NULL,
    Rad1LowerCom2OwnedDataRef = NULL;
XPLMDataRef Rad1LowerNav1OwnedDataRef = NULL,
    Rad1LowerNav2OwnedDataRef = NULL;
XPLMDataRef Rad1LowerAdfOwnedDataRef = NULL,
    Rad1LowerDmeOwnedDataRef = NULL;
XPLMDataRef Rad1LowerXpdrOwnedDataRef = NULL,
    Rad1LowerActStbyOwnedDataRef = NULL;

XPLMDataRef Rad1LowerFineIncOwnedDataRef = NULL,
    Rad1LowerFineDecOwnedDataRef = NULL;
XPLMDataRef Rad1LowerCorseIncOwnedDataRef = NULL,
    Rad1LowerCorseDecOwnedDataRef = NULL;

XPLMDataRef Rad1LowerFineIncTicksOwnedDataRef = NULL,
    Rad1LowerFineDecTicksOwnedDataRef = NULL;
XPLMDataRef Rad1LowerCorseIncTicksOwnedDataRef = NULL,
    Rad1LowerCorseDecTicksOwnedDataRef = NULL;


XPLMDataRef Rad1LowerDigit1OwnedDataRef = NULL,
    Rad1LowerDigit2OwnedDataRef = NULL;
XPLMDataRef Rad1LowerDigit3OwnedDataRef = NULL,
    Rad1LowerDigit4OwnedDataRef = NULL;
XPLMDataRef Rad1LowerDigit5OwnedDataRef = NULL,
    Rad1LowerDigit6OwnedDataRef = NULL;
XPLMDataRef Rad1LowerDigit7OwnedDataRef = NULL,
    Rad1LowerDigit8OwnedDataRef = NULL;
XPLMDataRef Rad1LowerDigit9OwnedDataRef = NULL,
    Rad1LowerDigit10OwnedDataRef = NULL;



XPLMDataRef Rad2UpperCom1OwnedDataRef = NULL,
    Rad2UpperCom2OwnedDataRef = NULL;
XPLMDataRef Rad2UpperNav1OwnedDataRef = NULL,
    Rad2UpperNav2OwnedDataRef = NULL;
XPLMDataRef Rad2UpperAdfOwnedDataRef = NULL,
    Rad2UpperDmeOwnedDataRef = NULL;
XPLMDataRef Rad2UpperXpdrOwnedDataRef = NULL,
    Rad2UpperActStbyOwnedDataRef = NULL;

XPLMDataRef Rad2UpperFineIncOwnedDataRef = NULL,
    Rad2UpperFineDecOwnedDataRef = NULL;
XPLMDataRef Rad2UpperCorseIncOwnedDataRef = NULL,
    Rad2UpperCorseDecOwnedDataRef = NULL;

XPLMDataRef Rad2UpperFineIncTicksOwnedDataRef = NULL,
    Rad2UpperFineDecTicksOwnedDataRef = NULL;
XPLMDataRef Rad2UpperCorseIncTicksOwnedDataRef = NULL,
    Rad2UpperCorseDecTicksOwnedDataRef = NULL;


XPLMDataRef Rad2UpperDigit1OwnedDataRef = NULL,
    Rad2UpperDigit2OwnedDataRef = NULL;
XPLMDataRef Rad2UpperDigit3OwnedDataRef = NULL,
    Rad2UpperDigit4OwnedDataRef = NULL;
XPLMDataRef Rad2UpperDigit5OwnedDataRef = NULL,
    Rad2UpperDigit6OwnedDataRef = NULL;
XPLMDataRef Rad2UpperDigit7OwnedDataRef = NULL,
    Rad2UpperDigit8OwnedDataRef = NULL;
XPLMDataRef Rad2UpperDigit9OwnedDataRef = NULL,
    Rad2UpperDigit10OwnedDataRef = NULL;
XPLMDataRef Rad2WriteNowOwnedDataRef = NULL;


XPLMDataRef Rad2LowerCom1OwnedDataRef = NULL,
    Rad2LowerCom2OwnedDataRef = NULL;
XPLMDataRef Rad2LowerNav1OwnedDataRef = NULL,
    Rad2LowerNav2OwnedDataRef = NULL;
XPLMDataRef Rad2LowerAdfOwnedDataRef = NULL,
    Rad2LowerDmeOwnedDataRef = NULL;
XPLMDataRef Rad2LowerXpdrOwnedDataRef = NULL,
    Rad2LowerActStbyOwnedDataRef = NULL;

XPLMDataRef Rad2LowerFineIncOwnedDataRef = NULL,
    Rad2LowerFineDecOwnedDataRef = NULL;
XPLMDataRef Rad2LowerCorseIncOwnedDataRef = NULL,
    Rad2LowerCorseDecOwnedDataRef = NULL;

XPLMDataRef Rad2LowerFineIncTicksOwnedDataRef = NULL,
    Rad2LowerFineDecTicksOwnedDataRef = NULL;
XPLMDataRef Rad2LowerCorseIncTicksOwnedDataRef = NULL,
    Rad2LowerCorseDecTicksOwnedDataRef = NULL;


XPLMDataRef Rad2LowerDigit1OwnedDataRef = NULL,
    Rad2LowerDigit2OwnedDataRef = NULL;
XPLMDataRef Rad2LowerDigit3OwnedDataRef = NULL,
    Rad2LowerDigit4OwnedDataRef = NULL;
XPLMDataRef Rad2LowerDigit5OwnedDataRef = NULL,
    Rad2LowerDigit6OwnedDataRef = NULL;
XPLMDataRef Rad2LowerDigit7OwnedDataRef = NULL,
    Rad2LowerDigit8OwnedDataRef = NULL;
XPLMDataRef Rad2LowerDigit9OwnedDataRef = NULL,
    Rad2LowerDigit10OwnedDataRef = NULL;


XPLMDataRef Rad3UpperCom1OwnedDataRef = NULL,
    Rad3UpperCom2OwnedDataRef = NULL;
XPLMDataRef Rad3UpperNav1OwnedDataRef = NULL,
    Rad3UpperNav2OwnedDataRef = NULL;
XPLMDataRef Rad3UpperAdfOwnedDataRef = NULL,
    Rad3UpperDmeOwnedDataRef = NULL;
XPLMDataRef Rad3UpperXpdrOwnedDataRef = NULL,
    Rad3UpperActStbyOwnedDataRef = NULL;

XPLMDataRef Rad3UpperFineIncOwnedDataRef = NULL,
    Rad3UpperFineDecOwnedDataRef = NULL;
XPLMDataRef Rad3UpperCorseIncOwnedDataRef = NULL,
    Rad3UpperCorseDecOwnedDataRef = NULL;

XPLMDataRef Rad3UpperFineIncTicksOwnedDataRef = NULL,
    Rad3UpperFineDecTicksOwnedDataRef = NULL;
XPLMDataRef Rad3UpperCorseIncTicksOwnedDataRef = NULL,
    Rad3UpperCorseDecTicksOwnedDataRef = NULL;


XPLMDataRef Rad3UpperDigit1OwnedDataRef = NULL,
    Rad3UpperDigit2OwnedDataRef = NULL;
XPLMDataRef Rad3UpperDigit3OwnedDataRef = NULL,
    Rad3UpperDigit4OwnedDataRef = NULL;
XPLMDataRef Rad3UpperDigit5OwnedDataRef = NULL,
    Rad3UpperDigit6OwnedDataRef = NULL;
XPLMDataRef Rad3UpperDigit7OwnedDataRef = NULL,
    Rad3UpperDigit8OwnedDataRef = NULL;
XPLMDataRef Rad3UpperDigit9OwnedDataRef = NULL,
    Rad3UpperDigit10OwnedDataRef = NULL;
XPLMDataRef Rad3WriteNowOwnedDataRef = NULL;


XPLMDataRef Rad3LowerCom1OwnedDataRef = NULL,
    Rad3LowerCom2OwnedDataRef = NULL;
XPLMDataRef Rad3LowerNav1OwnedDataRef = NULL,
    Rad3LowerNav2OwnedDataRef = NULL;
XPLMDataRef Rad3LowerAdfOwnedDataRef = NULL,
    Rad3LowerDmeOwnedDataRef = NULL;
XPLMDataRef Rad3LowerXpdrOwnedDataRef = NULL,
    Rad3LowerActStbyOwnedDataRef = NULL;

XPLMDataRef Rad3LowerFineIncOwnedDataRef = NULL,
    Rad3LowerFineDecOwnedDataRef = NULL;
XPLMDataRef Rad3LowerCorseIncOwnedDataRef = NULL,
    Rad3LowerCorseDecOwnedDataRef = NULL;

XPLMDataRef Rad3LowerFineIncTicksOwnedDataRef = NULL,
    Rad3LowerFineDecTicksOwnedDataRef = NULL;
XPLMDataRef Rad3LowerCorseIncTicksOwnedDataRef = NULL,
    Rad3LowerCorseDecTicksOwnedDataRef = NULL;


XPLMDataRef Rad3LowerDigit1OwnedDataRef = NULL,
    Rad3LowerDigit2OwnedDataRef = NULL;
XPLMDataRef Rad3LowerDigit3OwnedDataRef = NULL,
    Rad3LowerDigit4OwnedDataRef = NULL;
XPLMDataRef Rad3LowerDigit5OwnedDataRef = NULL,
    Rad3LowerDigit6OwnedDataRef = NULL;
XPLMDataRef Rad3LowerDigit7OwnedDataRef = NULL,
    Rad3LowerDigit8OwnedDataRef = NULL;
XPLMDataRef Rad3LowerDigit9OwnedDataRef = NULL,
    Rad3LowerDigit10OwnedDataRef = NULL;


XPLMCommandRef XpanelsFnButtonCommand = NULL,
    XpanelsCrsToggleCommand = NULL;
XPLMCommandRef XpanelsLeftStartFnButtonCommand = NULL;


XPLMDataRef HsiSelector = NULL;



XPLMDataRef MultiPanelCountDataRef = NULL;


// *************** Switch Panel Command Ref *******************
XPLMCommandRef ClFlOpn = NULL,
    ClFlCls = NULL;
XPLMCommandRef PtHtOn = NULL,
    PtHtOff = NULL;
XPLMCommandRef PtHt0On = NULL,
    PtHt0Off = NULL,
    PtHt1On = NULL,
    PtHt1Off = NULL;

XPLMCommandRef AvLtOn = NULL,
    AvLtOff = NULL,
    BatOn = NULL,
    BatOff = NULL;
XPLMCommandRef LnLtOn = NULL,
    LnLtOff = NULL,
    TxLtOn = NULL,
    TxLtOff = NULL;
XPLMCommandRef StLtOn = NULL,
    StLtOff = NULL,
    NvLtOn = NULL,
    NvLtOff = NULL;
XPLMCommandRef BcLtOn = NULL,
    BcLtOff = NULL,
    GearUp = NULL,
    GearDn = NULL;

XPLMCommandRef MagOffSwitchOnCmd = NULL,
    MagOffSwitchOffCmd = NULL;
XPLMCommandRef MagRightSwitchOnCmd = NULL,
    MagRightSwitchOffCmd = NULL;
XPLMCommandRef MagLeftSwitchOnCmd = NULL,
    MagLeftSwitchOffCmd = NULL;
XPLMCommandRef MagBothSwitchOnCmd = NULL,
    MagBothSwitchOffCmd = NULL;
XPLMCommandRef MagStartSwitchOnCmd = NULL,
    MagStartSwitchOffCmd = NULL;

XPLMCommandRef BatMasterSwitchOnCmd = NULL,
    BatMasterSwitchOffCmd = NULL;
XPLMCommandRef AltMasterSwitchOnCmd = NULL,
    AltMasterSwitchOffCmd = NULL;
XPLMCommandRef AvMasterSwitchOnCmd = NULL,
    AvMasterSwitchOffCmd = NULL;

XPLMCommandRef FuelPumpOnCmd = NULL,
    FuelPumpOffCmd = NULL;
XPLMCommandRef FuelPump2OnCmd = NULL,
    FuelPump2OffCmd = NULL;
XPLMCommandRef FuelPump3OnCmd = NULL,
    FuelPump3OffCmd = NULL;
XPLMCommandRef FuelPump4OnCmd = NULL,
    FuelPump4OffCmd = NULL;

XPLMCommandRef DeiceOnCmd = NULL,
    DeiceOffCmd = NULL;
XPLMCommandRef DeiceOnCmd1 = NULL,
    DeiceOffCmd1 = NULL;
XPLMCommandRef DeiceOnCmd2 = NULL,
    DeiceOffCmd2 = NULL;
XPLMCommandRef DeiceOnCmd3 = NULL,
    DeiceOffCmd3 = NULL;
XPLMCommandRef DeiceOnCmd4 = NULL,
    DeiceOffCmd4 = NULL;
XPLMCommandRef DeiceOnCmd5 = NULL,
    DeiceOffCmd5 = NULL;
XPLMCommandRef DeiceOnCmd6 = NULL,
    DeiceOffCmd6 = NULL;
XPLMCommandRef DeiceOnCmd7 = NULL,
    DeiceOffCmd7 = NULL;
XPLMCommandRef DeiceOnCmd8 = NULL,
    DeiceOffCmd8 = NULL;

XPLMCommandRef PitotHeatOnCmd = NULL,
    PitotHeatOffCmd = NULL;
XPLMCommandRef Pitot2HeatOnCmd = NULL,
    Pitot2HeatOffCmd = NULL;
XPLMCommandRef GearUpOnCmd = NULL,
    GearOnOffCmd = NULL;
XPLMCommandRef GearDnOnCmd = NULL,
    GearDnOffCmd = NULL;

XPLMCommandRef CowlFlapsOpenCmd = NULL,
    CowlFlapsCloseCmd = NULL;
XPLMCommandRef Cowl2FlapsOpenCmd = NULL,
    Cowl2FlapsCloseCmd = NULL;
XPLMCommandRef Cowl3FlapsOpenCmd = NULL,
    Cowl3FlapsCloseCmd = NULL;
XPLMCommandRef Cowl4FlapsOpenCmd = NULL,
    Cowl4FlapsCloseCmd = NULL;

XPLMCommandRef PanelLightsOnCmd = NULL,
    PanelLightsOffCmd = NULL;
XPLMCommandRef BeaconLightsOnCmd = NULL,
    BeaconLightsOffCmd = NULL;
XPLMCommandRef NavLightsOnCmd = NULL,
    NavLightsOffCmd = NULL;
XPLMCommandRef StrobeLightsOnCmd = NULL,
    StrobeLightsOffCmd = NULL;
XPLMCommandRef TaxiLightsOnCmd = NULL,
    TaxiLightsOffCmd = NULL;
XPLMCommandRef LandingLightsOnCmd = NULL,
    LandingLightsOffCmd = NULL;

XPLMCommandRef MagOff1 = NULL,
    MagOff2 = NULL,
    MagOff3 = NULL,
    MagOff4 = NULL;
XPLMCommandRef MagOff5 = NULL,
    MagOff6 = NULL,
    MagOff7 = NULL,
    MagOff8 = NULL;

XPLMCommandRef MagLeft1 = NULL,
    MagLeft2 = NULL,
    MagLeft3 = NULL,
    MagLeft4 = NULL;
XPLMCommandRef MagLeft5 = NULL,
    MagLeft6 = NULL,
    MagLeft7 = NULL,
    MagLeft8 = NULL;

XPLMCommandRef MagRight1 = NULL,
    MagRight2 = NULL,
    MagRight3 = NULL,
    MagRight4 = NULL;
XPLMCommandRef MagRight5 = NULL,
    MagRight6 = NULL,
    MagRight7 = NULL,
    MagRight8 = NULL;

XPLMCommandRef MagBoth1 = NULL,
    MagBoth2 = NULL,
    MagBoth3 = NULL,
    MagBoth4 = NULL;
XPLMCommandRef MagBoth5 = NULL,
    MagBoth6 = NULL,
    MagBoth7 = NULL,
    MagBoth8 = NULL;

XPLMCommandRef EngStart1 = NULL,
    EngStart2 = NULL,
    EngStart3 = NULL,
    EngStart4 = NULL;
XPLMCommandRef EngStart5 = NULL,
    EngStart6 = NULL,
    EngStart7 = NULL,
    EngStart8 = NULL;

XPLMCommandRef BatOn1 = NULL,
    BatOn2 = NULL,
    BatOff1 = NULL,
    BatOff2 = NULL;

XPLMCommandRef GenOn1 = NULL,
    GenOn2 = NULL,
    GenOn3 = NULL,
    GenOn4 = NULL;
XPLMCommandRef GenOn5 = NULL,
    GenOn6 = NULL,
    GenOn7 = NULL,
    GenOn8 = NULL;

XPLMCommandRef GenOff1 = NULL,
    GenOff2 = NULL,
    GenOff3 = NULL,
    GenOff4 = NULL;
XPLMCommandRef GenOff5 = NULL,
    GenOff6 = NULL,
    GenOff7 = NULL,
    GenOff8 = NULL;

XPLMCommandRef FuelPumpOn1 = NULL,
    FuelPumpOn2 = NULL,
    FuelPumpOn3 = NULL,
    FuelPumpOn4 = NULL;
XPLMCommandRef FuelPumpOn5 = NULL,
    FuelPumpOn6 = NULL,
    FuelPumpOn7 = NULL,
    FuelPumpOn8 = NULL;

XPLMCommandRef FuelPumpOff1 = NULL,
    FuelPumpOff2 = NULL,
    FuelPumpOff3 = NULL,
    FuelPumpOff4 = NULL;
XPLMCommandRef FuelPumpOff5 = NULL,
    FuelPumpOff6 = NULL,
    FuelPumpOff7 = NULL,
    FuelPumpOff8 = NULL;

// ******************* Switch Panel Data Ref ********************
XPLMDataRef BatNum = NULL,
    GenNum = NULL,
    EngNum = NULL;
XPLMDataRef BatArrayOnDR = NULL,
    IgnSwitchArray = NULL;
XPLMDataRef EngnMixt = NULL,
    IgniterOn = NULL;
XPLMDataRef AcfEnType = NULL;

XPLMDataRef CowlFlaps = NULL,
    CockpitLights = NULL,
    AntiIce = NULL;
XPLMDataRef GearRetract = NULL,
    OnGround = NULL,
LandingGearStatus = { NULL };

XPLMDataRef Gear1Fail = NULL,
    Gear2Fail = NULL,
    Gear3Fail = NULL;

XPLMDataRef MagOffSwitchData = NULL,
    MagOff2SwitchData = NULL;
XPLMDataRef MagOff3SwitchData = NULL,
    MagOff4SwitchData = NULL;
XPLMDataRef MagOff5SwitchData = NULL,
    MagOff6SwitchData = NULL;
XPLMDataRef MagOff7SwitchData = NULL,
    MagOff8SwitchData = NULL;
XPLMDataRef MagOff9SwitchData = NULL,
    MagOff10SwitchData = NULL;

XPLMDataRef MagRightSwitchData = NULL,
    MagRight2SwitchData = NULL;
XPLMDataRef MagRight3SwitchData = NULL,
    MagRight4SwitchData = NULL;
XPLMDataRef MagRight5SwitchData = NULL,
    MagRight6SwitchData = NULL;
XPLMDataRef MagRight7SwitchData = NULL,
    MagRight8SwitchData = NULL;
XPLMDataRef MagRight9SwitchData = NULL,
    MagRight10SwitchData = NULL;

XPLMDataRef MagLeftSwitchData = NULL,
    MagLeft2SwitchData = NULL;
XPLMDataRef MagLeft3SwitchData = NULL,
    MagLeft4SwitchData = NULL;
XPLMDataRef MagLeft5SwitchData = NULL,
    MagLeft6SwitchData = NULL;
XPLMDataRef MagLeft7SwitchData = NULL,
    MagLeft8SwitchData = NULL;
XPLMDataRef MagLeft9SwitchData = NULL,
    MagLeft10SwitchData = NULL;

XPLMDataRef MagBothSwitchData = NULL,
    MagBoth2SwitchData = NULL;
XPLMDataRef MagBoth3SwitchData = NULL,
    MagBoth4SwitchData = NULL;
XPLMDataRef MagBoth5SwitchData = NULL,
    MagBoth6SwitchData = NULL;
XPLMDataRef MagBoth7SwitchData = NULL,
    MagBoth8SwitchData = NULL;
XPLMDataRef MagBoth9SwitchData = NULL,
    MagBoth10SwitchData = NULL;

XPLMDataRef MagStartSwitchData = NULL,
    MagStart2SwitchData = NULL;
XPLMDataRef MagStart3SwitchData = NULL,
    MagStart4SwitchData = NULL;
XPLMDataRef MagStart5SwitchData = NULL,
    MagStart6SwitchData = NULL;
XPLMDataRef MagStart7SwitchData = NULL,
    MagStart8SwitchData = NULL;
XPLMDataRef MagStart9SwitchData = NULL,
    MagStart10SwitchData = NULL;

XPLMDataRef MagStartSwitchLeftData = NULL,
    MagStart2SwitchLeftData = NULL;
XPLMDataRef MagStart3SwitchLeftData = NULL,
    MagStart4SwitchLeftData = NULL;
XPLMDataRef MagStart5SwitchLeftData = NULL,
    MagStart6SwitchLeftData = NULL;
XPLMDataRef MagStart7SwitchLeftData = NULL,
    MagStart8SwitchLeftData = NULL;
XPLMDataRef MagStart9SwitchLeftData = NULL,
    MagStart10SwitchLeftData = NULL;


XPLMDataRef BatMasterSwitchData = NULL,
    Bat2MasterSwitchData = NULL;
XPLMDataRef Bat3MasterSwitchData = NULL,
    Bat4MasterSwitchData = NULL;
XPLMDataRef Bat5MasterSwitchData = NULL,
    Bat6MasterSwitchData = NULL;
XPLMDataRef Bat7MasterSwitchData = NULL,
    Bat8MasterSwitchData = NULL;

XPLMDataRef AltMasterSwitchData = NULL,
    Alt2MasterSwitchData = NULL;
XPLMDataRef Alt3MasterSwitchData = NULL,
    Alt4MasterSwitchData = NULL;
XPLMDataRef Alt5MasterSwitchData = NULL,
    Alt6MasterSwitchData = NULL;
XPLMDataRef Alt7MasterSwitchData = NULL,
    Alt8MasterSwitchData = NULL;

XPLMDataRef AvMasterSwitchData = NULL,
    Av2MasterSwitchData = NULL;
XPLMDataRef Av3MasterSwitchData = NULL,
    Av4MasterSwitchData = NULL;
XPLMDataRef Av5MasterSwitchData = NULL,
    Av6MasterSwitchData = NULL;
XPLMDataRef Av7MasterSwitchData = NULL,
    Av8MasterSwitchData = NULL;
XPLMDataRef Av9MasterSwitchData = NULL,
    Av10MasterSwitchData = NULL;
XPLMDataRef Av11MasterSwitchData = NULL,
    Av12MasterSwitchData = NULL;
XPLMDataRef Av13MasterSwitchData = NULL,
    Av14MasterSwitchData = NULL;
XPLMDataRef Av15MasterSwitchData = NULL,
    Av16MasterSwitchData = NULL;

XPLMDataRef AvMasterSwitchDataf = NULL,
    Av2MasterSwitchDataf = NULL;
XPLMDataRef Av3MasterSwitchDataf = NULL,
    Av4MasterSwitchDataf = NULL;
XPLMDataRef Av5MasterSwitchDataf = NULL,
    Av6MasterSwitchDataf = NULL;
XPLMDataRef Av7MasterSwitchDataf = NULL,
    Av8MasterSwitchDataf = NULL;
XPLMDataRef Av9MasterSwitchDataf = NULL,
    Av10MasterSwitchDataf = NULL;
XPLMDataRef Av11MasterSwitchDataf = NULL,
    Av12MasterSwitchDataf = NULL;
XPLMDataRef Av13MasterSwitchDataf = NULL,
    Av14MasterSwitchDataf = NULL;
XPLMDataRef Av15MasterSwitchDataf = NULL,
    Av16MasterSwitchDataf = NULL;


XPLMDataRef FuelPumpSwitchData = NULL,
    FuelPump2SwitchData = NULL;
XPLMDataRef FuelPump3SwitchData = NULL,
    FuelPump4SwitchData = NULL;
XPLMDataRef FuelPump5SwitchData = NULL,
    FuelPump6SwitchData = NULL;
XPLMDataRef FuelPump7SwitchData = NULL,
    FuelPump8SwitchData = NULL;

XPLMDataRef DeiceSwitchData = NULL;
XPLMDataRef Deice2SwitchData = NULL;
XPLMDataRef Deice3SwitchData = NULL;
XPLMDataRef Deice4SwitchData = NULL;
XPLMDataRef Deice5SwitchData = NULL;
XPLMDataRef Deice6SwitchData = NULL;
XPLMDataRef Deice7SwitchData = NULL;
XPLMDataRef Deice8SwitchData = NULL;

XPLMDataRef PitotHeatSwitchData = NULL,
    Pitot2HeatSwitchData = NULL;
XPLMDataRef Pitot3HeatSwitchData = NULL,
    Pitot4HeatSwitchData = NULL;
XPLMDataRef Pitot5HeatSwitchData = NULL,
    Pitot6HeatSwitchData = NULL;
XPLMDataRef Pitot7HeatSwitchData = NULL,
    Pitot8HeatSwitchData = NULL;


XPLMDataRef GearUpData = NULL;
XPLMDataRef GearDnData = NULL;

XPLMDataRef CowlFlapsData = NULL,
    Cowl2FlapsData = NULL;
XPLMDataRef Cowl3FlapsData = NULL,
    Cowl4FlapsData = NULL;
XPLMDataRef Cowl5FlapsData = NULL,
    Cowl6FlapsData = NULL;
XPLMDataRef Cowl7FlapsData = NULL,
    Cowl8FlapsData = NULL;

XPLMDataRef PanelLightsData = NULL,
    PanelLights2Data = NULL;
XPLMDataRef PanelLights3Data = NULL,
    PanelLights4Data = NULL;
XPLMDataRef PanelLights5Data = NULL,
    PanelLights6Data = NULL;
XPLMDataRef PanelLights7Data = NULL,
    PanelLights8Data = NULL;

XPLMDataRef BeaconLightsData = NULL,
    BeaconLights2Data = NULL;
XPLMDataRef BeaconLights3Data = NULL,
    BeaconLights4Data = NULL;

XPLMDataRef NavLightsData = NULL,
    NavLights2Data = NULL;
XPLMDataRef NavLights3Data = NULL,
    NavLights4Data = NULL;

XPLMDataRef StrobeLightsData = NULL,
    StrobeLights2Data = NULL;
XPLMDataRef StrobeLights3Data = NULL,
    StrobeLights4Data = NULL;

XPLMDataRef TaxiLightsData = NULL,
    TaxiLights2Data = NULL;
XPLMDataRef TaxiLights3Data = NULL,
    TaxiLights4Data = NULL;

XPLMDataRef LandingLightsData = NULL,
    LandingLights2Data = NULL;
XPLMDataRef LandingLights3Data = NULL,
    LandingLights4Data = NULL;

XPLMDataRef SwitchPanelCountDataRef = NULL;

XPLMDataRef SwitchStartOffOwnedDataRef = NULL,
    SwitchStartRightOwnedDataRef = NULL;
XPLMDataRef SwitchStartLeftOwnedDataRef = NULL,
    SwitchStartBothOwnedDataRef = NULL;
XPLMDataRef SwitchStartStartOwnedDataRef = NULL;
XPLMDataRef SwitchBatOwnedDataRef = NULL,
    SwitchAltOwnedDataRef = NULL;
XPLMDataRef SwitchAvOwnedDataRef = NULL,
    SwitchFuelOwnedDataRef = NULL;
XPLMDataRef SwitchDiceOwnedDataRef = NULL,
    SwitchPitotOwnedDataRef = NULL;
XPLMDataRef SwitchGearUpOwnedDataRef = NULL,
    SwitchGearDnOwnedDataRef = NULL;
XPLMDataRef SwitchCowlOwnedDataRef = NULL,
    SwitchPanelOwnedDataRef = NULL;
XPLMDataRef SwitchBeaconOwnedDataRef = NULL,
    SwitchNavOwnedDataRef = NULL;
XPLMDataRef SwitchStrobeOwnedDataRef = NULL,
    SwitchTaxiOwnedDataRef = NULL;
XPLMDataRef SwitchLandingOwnedDataRef = NULL;


typedef std::vector < XPLMDataRef > aXPLMDataRefID;

static aXPLMDataRefID DataRefID;

// ****************** BIP Panel Command Ref **********************

//  ***************** BIP Panel Data Ref *********************
XPLMDataRef gTimeSimIsRunningXDataRef = NULL;

XPLMDataRef BipPanelCountData = NULL;

XPLMMenuID XsaitekpanelsMenu;
XPLMMenuID BipMenu;
XPLMMenuID BipMenuId,
    Bip2MenuId,
    Bip3MenuId,
    Bip4MenuId;
XPLMMenuID ConfigMenuId;

XPWidgetID XsaitekpanelsWidgetID = NULL;
XPWidgetID BipWidgetID = NULL;
XPWidgetID Bip2WidgetID = NULL;
XPWidgetID Bip3WidgetID = NULL;
XPWidgetID Bip4WidgetID = NULL;


// ******************* TPM Panel Data Ref ********************

XPLMDataRef TpmPanelCountDataRef = NULL;

// ********************* Saitek Panels Data Ref  ************************
static XPLMDataRef XsaitekpanelsVersionDataRef = NULL;
static XPLMDataRef XsaitekpanelsFnButtonDataRef = NULL;
static XPLMDataRef XsaitekpanelsLeftStartFnButtonDataRef = NULL;

static XPLMDataRef XsaitekpanelsInteger1SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger2SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger3SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger4SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger5SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger6SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger7SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger8SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger9SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger10SharedDataRef = NULL;

static XPLMDataRef XsaitekpanelsInteger11SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger12SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger13SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger14SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger15SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger16SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger17SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger18SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger19SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsInteger20SharedDataRef = NULL;


static XPLMDataRef XsaitekpanelsFloat1SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat2SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat3SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat4SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat5SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat6SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat7SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat8SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat9SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat10SharedDataRef = NULL;

static XPLMDataRef XsaitekpanelsFloat11SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat12SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat13SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat14SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat15SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat16SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat17SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat18SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat19SharedDataRef = NULL;
static XPLMDataRef XsaitekpanelsFloat20SharedDataRef = NULL;


// ********************** Radio Panel variables ************************
int radcnt = 0,
    radiores,
    stopradcnt;
int radres,
    radnum = 0;
float interval = -1;
static unsigned char blankradiowbuf[4][23];
static unsigned char radiobuf[4][4],
    radiowbuf[4][23];

unsigned char radbuf[4],
    radwbuf[21];

int radspeed,
    numadf,
    metricpressenable,
    channelspacing833enable;
int dmedistspeedenable;

int rad1uprcom1switchremap,
    rad1uprcom1actstbybtnremap;
int rad1uprcom2switchremap,
    rad1uprcom2actstbybtnremap;
int rad1uprnav1switchremap,
    rad1uprnav1actstbybtnremap;
int rad1uprnav2switchremap,
    rad1uprnav2actstbybtnremap;
int rad1upradfswitchremap,
    rad1upradfactstbybtnremap;
int rad1uprdmeswitchremap,
    rad1uprdmeactstbybtnremap;
int rad1uprxpdrswitchremap;
int rad1lwrcom1switchremap,
    rad1lwrcom1actstbybtnremap;
int rad1lwrcom2switchremap,
    rad1lwrcom2actstbybtnremap;
int rad1lwrnav1switchremap,
    rad1lwrnav1actstbybtnremap;
int rad1lwrnav2switchremap,
    rad1lwrnav2actstbybtnremap;
int rad1lwradfswitchremap,
    rad1lwradfactstbybtnremap;
int rad1lwrdmeswitchremap,
    rad1lwrdmeactstbybtnremap;
int rad1lwrxpdrswitchremap;

int rad2uprcom1switchremap,
    rad2uprcom1actstbybtnremap;
int rad2uprcom2switchremap,
    rad2uprcom2actstbybtnremap;
int rad2uprnav1switchremap,
    rad2uprnav1actstbybtnremap;
int rad2uprnav2switchremap,
    rad2uprnav2actstbybtnremap;
int rad2upradfswitchremap,
    rad2upradfactstbybtnremap;
int rad2uprdmeswitchremap,
    rad2uprdmeactstbybtnremap;
int rad2uprxpdrswitchremap;
int rad2lwrcom1switchremap,
    rad2lwrcom1actstbybtnremap;
int rad2lwrcom2switchremap,
    rad2lwrcom2actstbybtnremap;
int rad2lwrnav1switchremap,
    rad2lwrnav1actstbybtnremap;
int rad2lwrnav2switchremap,
    rad2lwrnav2actstbybtnremap;
int rad2lwradfswitchremap,
    rad2lwradfactstbybtnremap;
int rad2lwrdmeswitchremap,
    rad2lwrdmeactstbybtnremap;
int rad2lwrxpdrswitchremap;

int rad3uprcom1switchremap,
    rad3uprcom1actstbybtnremap;
int rad3uprcom2switchremap,
    rad3uprcom2actstbybtnremap;
int rad3uprnav1switchremap,
    rad3uprnav1actstbybtnremap;
int rad3uprnav2switchremap,
    rad3uprnav2actstbybtnremap;
int rad3upradfswitchremap,
    rad3upradfactstbybtnremap;
int rad3uprdmeswitchremap,
    rad3uprdmeactstbybtnremap;
int rad3uprxpdrswitchremap;
int rad3lwrcom1switchremap,
    rad3lwrcom1actstbybtnremap;
int rad3lwrcom2switchremap,
    rad3lwrcom2actstbybtnremap;
int rad3lwrnav1switchremap,
    rad3lwrnav1actstbybtnremap;
int rad3lwrnav2switchremap,
    rad3lwrnav2actstbybtnremap;
int rad3lwradfswitchremap,
    rad3lwradfactstbybtnremap;
int rad3lwrdmeswitchremap,
    rad3lwrdmeactstbybtnremap;
int rad3lwrxpdrswitchremap;


int rad1_upr_com1_actstby_btn_data_on_value,
    rad1_upr_com1_actstby_btn_data_off_value;
int rad1_upr_com2_actstby_btn_data_on_value,
    rad1_upr_com2_actstby_btn_data_off_value;
int rad1_upr_nav1_actstby_btn_data_on_value,
    rad1_upr_nav1_actstby_btn_data_off_value;
int rad1_upr_nav2_actstby_btn_data_on_value,
    rad1_upr_nav2_actstby_btn_data_off_value;
int rad1_upr_adf_actstby_btn_data_on_value,
    rad1_upr_adf_actstby_btn_data_off_value;
int rad1_upr_dme_actstby_btn_data_on_value,
    rad1_upr_dme_actstby_btn_data_off_value;

int rad1_lwr_com1_actstby_btn_data_on_value,
    rad1_lwr_com1_actstby_btn_data_off_value;
int rad1_lwr_com2_actstby_btn_data_on_value,
    rad1_lwr_com2_actstby_btn_data_off_value;
int rad1_lwr_nav1_actstby_btn_data_on_value,
    rad1_lwr_nav1_actstby_btn_data_off_value;
int rad1_lwr_nav2_actstby_btn_data_on_value,
    rad1_lwr_nav2_actstby_btn_data_off_value;
int rad1_lwr_adf_actstby_btn_data_on_value,
    rad1_lwr_adf_actstby_btn_data_off_value;
int rad1_lwr_dme_actstby_btn_data_on_value,
    rad1_lwr_dme_actstby_btn_data_off_value;

int rad2_upr_com1_actstby_btn_data_on_value,
    rad2_upr_com1_actstby_btn_data_off_value;
int rad2_upr_com2_actstby_btn_data_on_value,
    rad2_upr_com2_actstby_btn_data_off_value;
int rad2_upr_nav1_actstby_btn_data_on_value,
    rad2_upr_nav1_actstby_btn_data_off_value;
int rad2_upr_nav2_actstby_btn_data_on_value,
    rad2_upr_nav2_actstby_btn_data_off_value;
int rad2_upr_adf_actstby_btn_data_on_value,
    rad2_upr_adf_actstby_btn_data_off_value;
int rad2_upr_dme_actstby_btn_data_on_value,
    rad2_upr_dme_actstby_btn_data_off_value;

int rad2_lwr_com1_actstby_btn_data_on_value,
    rad2_lwr_com1_actstby_btn_data_off_value;
int rad2_lwr_com2_actstby_btn_data_on_value,
    rad2_lwr_com2_actstby_btn_data_off_value;
int rad2_lwr_nav1_actstby_btn_data_on_value,
    rad2_lwr_nav1_actstby_btn_data_off_value;
int rad2_lwr_nav2_actstby_btn_data_on_value,
    rad2_lwr_nav2_actstby_btn_data_off_value;
int rad2_lwr_adf_actstby_btn_data_on_value,
    rad2_lwr_adf_actstby_btn_data_off_value;
int rad2_lwr_dme_actstby_btn_data_on_value,
    rad2_lwr_dme_actstby_btn_data_off_value;

int rad3_upr_com1_actstby_btn_data_on_value,
    rad3_upr_com1_actstby_btn_data_off_value;
int rad3_upr_com2_actstby_btn_data_on_value,
    rad3_upr_com2_actstby_btn_data_off_value;
int rad3_upr_nav1_actstby_btn_data_on_value,
    rad3_upr_nav1_actstby_btn_data_off_value;
int rad3_upr_nav2_actstby_btn_data_on_value,
    rad3_upr_nav2_actstby_btn_data_off_value;
int rad3_upr_adf_actstby_btn_data_on_value,
    rad3_upr_adf_actstby_btn_data_off_value;
int rad3_upr_dme_actstby_btn_data_on_value,
    rad3_upr_dme_actstby_btn_data_off_value;

int rad3_lwr_com1_actstby_btn_data_on_value,
    rad3_lwr_com1_actstby_btn_data_off_value;
int rad3_lwr_com2_actstby_btn_data_on_value,
    rad3_lwr_com2_actstby_btn_data_off_value;
int rad3_lwr_nav1_actstby_btn_data_on_value,
    rad3_lwr_nav1_actstby_btn_data_off_value;
int rad3_lwr_nav2_actstby_btn_data_on_value,
    rad3_lwr_nav2_actstby_btn_data_off_value;
int rad3_lwr_adf_actstby_btn_data_on_value,
    rad3_lwr_adf_actstby_btn_data_off_value;
int rad3_lwr_dme_actstby_btn_data_on_value,
    rad3_lwr_dme_actstby_btn_data_off_value;


float rad1_upr_com1_actstby_btn_dataf_on_value,
    rad1_upr_com1_actstby_btn_dataf_off_value;
float rad1_upr_com2_actstby_btn_dataf_on_value,
    rad1_upr_com2_actstby_btn_dataf_off_value;
float rad1_upr_nav1_actstby_btn_dataf_on_value,
    rad1_upr_nav1_actstby_btn_dataf_off_value;
float rad1_upr_nav2_actstby_btn_dataf_on_value,
    rad1_upr_nav2_actstby_btn_dataf_off_value;
float rad1_upr_adf_actstby_btn_dataf_on_value,
    rad1_upr_adf_actstby_btn_dataf_off_value;
float rad1_upr_dme_actstby_btn_datfa_on_value,
    rad1_upr_dme_actstby_btn_dataf_off_value;

float rad1_lwr_com1_actstby_btn_dataf_on_value,
    rad1_lwr_com1_actstby_btn_dataf_off_value;
float rad1_lwr_com2_actstby_btn_dataf_on_value,
    rad1_lwr_com2_actstby_btn_dataf_off_value;
float rad1_lwr_nav1_actstby_btn_dataf_on_value,
    rad1_lwr_nav1_actstby_btn_dataf_off_value;
float rad1_lwr_nav2_actstby_btn_dataf_on_value,
    rad1_lwr_nav2_actstby_btn_dataf_off_value;
float rad1_lwr_adf_actstby_btn_dataf_on_value,
    rad1_lwr_adf_actstby_btn_dataf_off_value;
float rad1_lwr_dme_actstby_btn_dataf_on_value,
    rad1_lwr_dme_actstby_btn_dataf_off_value;

float rad2_upr_com1_actstby_btn_dataf_on_value,
    rad2_upr_com1_actstby_btn_dataf_off_value;
float rad2_upr_com2_actstby_btn_dataf_on_value,
    rad2_upr_com2_actstby_btn_dataf_off_value;
float rad2_upr_nav1_actstby_btn_dataf_on_value,
    rad2_upr_nav1_actstby_btn_dataf_off_value;
float rad2_upr_nav2_actstby_btn_datfa_on_value,
    rad2_upr_nav2_actstby_btn_dataf_off_value;
float rad2_upr_adf_actstby_btn_dataf_on_value,
    rad2_upr_adf_actstby_btn_dataf_off_value;
float rad2_upr_dme_actstby_btn_dataf_on_value,
    rad2_upr_dme_actstby_btn_dataf_off_value;

float rad2_lwr_com1_actstby_btn_dataf_on_value,
    rad2_lwr_com1_actstby_btn_dataf_off_value;
float rad2_lwr_com2_actstby_btn_dataf_on_value,
    rad2_lwr_com2_actstby_btn_dataf_off_value;
float rad2_lwr_nav1_actstby_btn_dataf_on_value,
    rad2_lwr_nav1_actstby_btn_dataf_off_value;
float rad2_lwr_nav2_actstby_btn_dataf_on_value,
    rad2_lwr_nav2_actstby_btn_dataf_off_value;
float rad2_lwr_adf_actstby_btn_dataf_on_value,
    rad2_lwr_adf_actstby_btn_dataf_off_value;
float rad2_lwr_dme_actstby_btn_dataf_on_value,
    rad2_lwr_dme_actstby_btn_dataf_off_value;

float rad3_upr_com1_actstby_btn_dataf_on_value,
    rad3_upr_com1_actstby_btn_dataf_off_value;
float rad3_upr_com2_actstby_btn_dataf_on_value,
    rad3_upr_com2_actstby_btn_dataf_off_value;
float rad3_upr_nav1_actstby_btn_dataf_on_value,
    rad3_upr_nav1_actstby_btn_dataf_off_value;
float rad3_upr_nav2_actstby_btn_datfa_on_value,
    rad3_upr_nav2_actstby_btn_dataf_off_value;
float rad3_upr_adf_actstby_btn_dataf_on_value,
    rad3_upr_adf_actstby_btn_dataf_off_value;
float rad3_upr_dme_actstby_btn_datfa_on_value,
    rad3_upr_dme_actstby_btn_dataf_off_value;

float rad3_lwr_com1_actstby_btn_dataf_on_value,
    rad3_lwr_com1_actstby_btn_dataf_off_value;
float rad3_lwr_com2_actstby_btn_dataf_on_value,
    rad3_lwr_com2_actstby_btn_dataf_off_value;
float rad3_lwr_nav1_actstby_btn_dataf_on_value,
    rad3_lwr_nav1_actstby_btn_dataf_off_value;
float rad3_lwr_nav2_actstby_btn_dataf_on_value,
    rad3_lwr_nav2_actstby_btn_dataf_off_value;
float rad3_lwr_adf_actstby_btn_dataf_on_value,
    rad3_lwr_adf_actstby_btn_dataf_off_value;
float rad3_lwr_dme_actstby_btn_dataf_on_value,
    rad3_lwr_dme_actstby_btn_dataf_off_value;


static int RadioPanelCountData = 0;
static int Rad1UprCom1OwnedData = 0,
    Rad1UprCom2OwnedData = 0;
static int Rad1UprNav1OwnedData = 0,
    Rad1UprNav2OwnedData = 0;
static int Rad1UprAdfOwnedData = 0,
    Rad1UprDmeOwnedData = 0;
static int Rad1UprXpdrOwnedData = 0,
    Rad1UprActStbyOwnedData = 0;

static int Rad1UprFineIncOwnedData = 0,
    Rad1UprFineDecOwnedData = 0;
static int Rad1UprCorseIncOwnedData = 0,
    Rad1UprCorseDecOwnedData = 0;

static int Rad1UprFineIncTicksOwnedData = 0,
    Rad1UprFineDecTicksOwnedData = 0;
static int Rad1UprCorseIncTicksOwnedData = 0,
    Rad1UprCorseDecTicksOwnedData = 0;


int Rad1UprDigit1OwnedData = 0,
    Rad1UprDigit2OwnedData = 0;
int Rad1UprDigit3OwnedData = 0,
    Rad1UprDigit4OwnedData = 0;
int Rad1UprDigit5OwnedData = 0,
    Rad1UprDigit6OwnedData = 0;
int Rad1UprDigit7OwnedData = 0,
    Rad1UprDigit8OwnedData = 0;
int Rad1UprDigit9OwnedData = 0,
    Rad1UprDigit10OwnedData = 0;
int Rad1WriteNowOwnedData = 0;

static int Rad1LwrCom1OwnedData = 0,
    Rad1LwrCom2OwnedData = 0;
static int Rad1LwrNav1OwnedData = 0,
    Rad1LwrNav2OwnedData = 0;
static int Rad1LwrAdfOwnedData = 0,
    Rad1LwrDmeOwnedData = 0;
static int Rad1LwrXpdrOwnedData = 0,
    Rad1LwrActStbyOwnedData = 0;

static int Rad1LwrFineIncOwnedData = 0,
    Rad1LwrFineDecOwnedData = 0;
static int Rad1LwrCorseIncOwnedData = 0,
    Rad1LwrCorseDecOwnedData = 0;

static int Rad1LwrFineIncTicksOwnedData = 0,
    Rad1LwrFineDecTicksOwnedData = 0;
static int Rad1LwrCorseIncTicksOwnedData = 0,
    Rad1LwrCorseDecTicksOwnedData = 0;


int Rad1LwrDigit1OwnedData = 0,
    Rad1LwrDigit2OwnedData = 0;
int Rad1LwrDigit3OwnedData = 0,
    Rad1LwrDigit4OwnedData = 0;
int Rad1LwrDigit5OwnedData = 0,
    Rad1LwrDigit6OwnedData = 0;
int Rad1LwrDigit7OwnedData = 0,
    Rad1LwrDigit8OwnedData = 0;
int Rad1LwrDigit9OwnedData = 0,
    Rad1LwrDigit10OwnedData = 0;


static int Rad2UprCom1OwnedData = 0,
    Rad2UprCom2OwnedData = 0;
static int Rad2UprNav1OwnedData = 0,
    Rad2UprNav2OwnedData = 0;
static int Rad2UprAdfOwnedData = 0,
    Rad2UprDmeOwnedData = 0;
static int Rad2UprXpdrOwnedData = 0,
    Rad2UprActStbyOwnedData = 0;

static int Rad2UprFineIncOwnedData = 0,
    Rad2UprFineDecOwnedData = 0;
static int Rad2UprCorseIncOwnedData = 0,
    Rad2UprCorseDecOwnedData = 0;

static int Rad2UprFineIncTicksOwnedData = 0,
    Rad2UprFineDecTicksOwnedData = 0;
static int Rad2UprCorseIncTicksOwnedData = 0,
    Rad2UprCorseDecTicksOwnedData = 0;


int Rad2UprDigit1OwnedData = 0,
    Rad2UprDigit2OwnedData = 0;
int Rad2UprDigit3OwnedData = 0,
    Rad2UprDigit4OwnedData = 0;
int Rad2UprDigit5OwnedData = 0,
    Rad2UprDigit6OwnedData = 0;
int Rad2UprDigit7OwnedData = 0,
    Rad2UprDigit8OwnedData = 0;
int Rad2UprDigit9OwnedData = 0,
    Rad2UprDigit10OwnedData = 0;
int Rad2WriteNowOwnedData = 0;

static int Rad2LwrCom1OwnedData = 0,
    Rad2LwrCom2OwnedData = 0;
static int Rad2LwrNav1OwnedData = 0,
    Rad2LwrNav2OwnedData = 0;
static int Rad2LwrAdfOwnedData = 0,
    Rad2LwrDmeOwnedData = 0;
static int Rad2LwrXpdrOwnedData = 0,
    Rad2LwrActStbyOwnedData = 0;

static int Rad2LwrFineIncOwnedData = 0,
    Rad2LwrFineDecOwnedData = 0;
static int Rad2LwrCorseIncOwnedData = 0,
    Rad2LwrCorseDecOwnedData = 0;

static int Rad2LwrFineIncTicksOwnedData = 0,
    Rad2LwrFineDecTicksOwnedData = 0;
static int Rad2LwrCorseIncTicksOwnedData = 0,
    Rad2LwrCorseDecTicksOwnedData = 0;


int Rad2LwrDigit1OwnedData = 0,
    Rad2LwrDigit2OwnedData = 0;
int Rad2LwrDigit3OwnedData = 0,
    Rad2LwrDigit4OwnedData = 0;
int Rad2LwrDigit5OwnedData = 0,
    Rad2LwrDigit6OwnedData = 0;
int Rad2LwrDigit7OwnedData = 0,
    Rad2LwrDigit8OwnedData = 0;
int Rad2LwrDigit9OwnedData = 0,
    Rad2LwrDigit10OwnedData = 0;


int Rad3UprCom1OwnedData = 0,
    Rad3UprCom2OwnedData = 0;
int Rad3UprNav1OwnedData = 0,
    Rad3UprNav2OwnedData = 0;
int Rad3UprAdfOwnedData = 0,
    Rad3UprDmeOwnedData = 0;
int Rad3UprXpdrOwnedData = 0,
    Rad3UprActStbyOwnedData = 0;

int Rad3UprFineIncOwnedData = 0,
    Rad3UprFineDecOwnedData = 0;
int Rad3UprCorseIncOwnedData = 0,
    Rad3UprCorseDecOwnedData = 0;

int Rad3UprFineIncTicksOwnedData = 0,
    Rad3UprFineDecTicksOwnedData = 0;
int Rad3UprCorseIncTicksOwnedData = 0,
    Rad3UprCorseDecTicksOwnedData = 0;


int Rad3UprDigit1OwnedData = 0,
    Rad3UprDigit2OwnedData = 0;
int Rad3UprDigit3OwnedData = 0,
    Rad3UprDigit4OwnedData = 0;
int Rad3UprDigit5OwnedData = 0,
    Rad3UprDigit6OwnedData = 0;
int Rad3UprDigit7OwnedData = 0,
    Rad3UprDigit8OwnedData = 0;
int Rad3UprDigit9OwnedData = 0,
    Rad3UprDigit10OwnedData = 0;
int Rad3WriteNowOwnedData = 0;


static int Rad3LwrCom1OwnedData = 0,
    Rad3LwrCom2OwnedData = 0;
static int Rad3LwrNav1OwnedData = 0,
    Rad3LwrNav2OwnedData = 0;
static int Rad3LwrAdfOwnedData = 0,
    Rad3LwrDmeOwnedData = 0;
static int Rad3LwrXpdrOwnedData = 0,
    Rad3LwrActStbyOwnedData = 0;

static int Rad3LwrFineIncOwnedData = 0,
    Rad3LwrFineDecOwnedData = 0;
static int Rad3LwrCorseIncOwnedData = 0,
    Rad3LwrCorseDecOwnedData = 0;

static int Rad3LwrFineIncTicksOwnedData = 0,
    Rad3LwrFineDecTicksOwnedData = 0;
static int Rad3LwrCorseIncTicksOwnedData = 0,
    Rad3LwrCorseDecTicksOwnedData = 0;


int Rad3LwrDigit1OwnedData = 0,
    Rad3LwrDigit2OwnedData = 0;
int Rad3LwrDigit3OwnedData = 0,
    Rad3LwrDigit4OwnedData = 0;
int Rad3LwrDigit5OwnedData = 0,
    Rad3LwrDigit6OwnedData = 0;
int Rad3LwrDigit7OwnedData = 0,
    Rad3LwrDigit8OwnedData = 0;
int Rad3LwrDigit9OwnedData = 0,
    Rad3LwrDigit10OwnedData = 0;


int RadioPanelCountGetDataiCallback(void *inRefcon);
void RadioPanelCountSetDataiCallback(void *inRefcon, int RadioPanelCount);


int Rad1UprCom1StatusGetDataiCallback(void *inRefcon);
void Rad1UprCom1StatusSetDataiCallback(void *inRefcon, int Rad1UprCom1Status);

int Rad1UprCom2StatusGetDataiCallback(void *inRefcon);
void Rad1UprCom2StatusSetDataiCallback(void *inRefcon, int Rad1UprCom2Status);

int Rad1UprNav1StatusGetDataiCallback(void *inRefcon);
void Rad1UprNav1StatusSetDataiCallback(void *inRefcon, int Rad1UprNav1Status);

int Rad1UprNav2StatusGetDataiCallback(void *inRefcon);
void Rad1UprNav2StatusSetDataiCallback(void *inRefcon, int Rad1UprNav2Status);

int Rad1UprAdfStatusGetDataiCallback(void *inRefcon);
void Rad1UprAdfStatusSetDataiCallback(void *inRefcon, int Rad1UprAdfStatus);

int Rad1UprDmeStatusGetDataiCallback(void *inRefcon);
void Rad1UprDmeStatusSetDataiCallback(void *inRefcon, int Rad1UprDmeStatus);

int Rad1UprXpdrStatusGetDataiCallback(void *inRefcon);
void Rad1UprXpdrStatusSetDataiCallback(void *inRefcon, int Rad1UprXpdrStatus);



int Rad1UprCorseIncStatusGetDataiCallback(void *inRefcon);
void Rad1UprCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseIncStatus);

int Rad1UprCorseDecStatusGetDataiCallback(void *inRefcon);
void Rad1UprCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseDecStatus);

int Rad1UprFineIncStatusGetDataiCallback(void *inRefcon);
void Rad1UprFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineIncStatus);

int Rad1UprFineDecStatusGetDataiCallback(void *inRefcon);
void Rad1UprFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineDecStatus);


int Rad1UprCorseIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad1UprCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseIncTicksStatus);

int Rad1UprCorseDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad1UprCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseDecTicksStatus);

int Rad1UprFineIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad1UprFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineIncTicksStatus);

int Rad1UprFineDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad1UprFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineDecTicksStatus);



int Rad1UprActStbyStatusGetDataiCallback(void *inRefcon);
void Rad1UprActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad1UprActStbyStatus);



int Rad1UprDigit1ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit1Value);

int Rad1UprDigit2ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit2Value);

int Rad1UprDigit3ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit3Value);

int Rad1UprDigit4ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit4Value);

int Rad1UprDigit5ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit5Value);

int Rad1UprDigit6ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit6Value);

int Rad1UprDigit7ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit7Value);

int Rad1UprDigit8ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit8Value);

int Rad1UprDigit9ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit9Value);

int Rad1UprDigit10ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit10Value);

int Rad1WriteNowGetDataiCallback(void *inRefcon);
void Rad1WriteNowSetDataiCallback(void *inRefcon, int Rad1WriteNow);




int Rad1LwrCom1StatusGetDataiCallback(void *inRefcon);
void Rad1LwrCom1StatusSetDataiCallback(void *inRefcon, int Rad1LwrCom1Status);

int Rad1LwrCom2StatusGetDataiCallback(void *inRefcon);
void Rad1LwrCom2StatusSetDataiCallback(void *inRefcon, int Rad1LwrCom2Status);

int Rad1LwrNav1StatusGetDataiCallback(void *inRefcon);
void Rad1LwrNav1StatusSetDataiCallback(void *inRefcon, int Rad1LwrNav1Status);

int Rad1LwrNav2StatusGetDataiCallback(void *inRefcon);
void Rad1LwrNav2StatusSetDataiCallback(void *inRefcon, int Rad1LwrNav2Status);

int Rad1LwrAdfStatusGetDataiCallback(void *inRefcon);
void Rad1UprAdfStatusSetDataiCallback(void *inRefcon, int Rad1LwrAdfStatus);

int Rad1LwrDmeStatusGetDataiCallback(void *inRefcon);
void Rad1LwrDmeStatusSetDataiCallback(void *inRefcon, int Rad1LwrDmeStatus);

int Rad1LwrXpdrStatusGetDataiCallback(void *inRefcon);
void Rad1LwrXpdrStatusSetDataiCallback(void *inRefcon, int Rad1LwrXpdrStatus);



int Rad1LwrCorseIncStatusGetDataiCallback(void *inRefcon);
void Rad1LwrCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseIncStatus);

int Rad1LwrCorseDecStatusGetDataiCallback(void *inRefcon);
void Rad1LwrCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseDecStatus);

int Rad1LwrFineIncStatusGetDataiCallback(void *inRefcon);
void Rad1LwrFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineIncStatus);

int Rad1LwrFineDecStatusGetDataiCallback(void *inRefcon);
void Rad1LwrFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineDecStatus);



int Rad1LwrCorseIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad1LwrCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseIncTicksStatus);

int Rad1LwrCorseDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad1LwrCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseDecTicksStatus);

int Rad1LwrFineIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad1LwrFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineIncTicksStatus);

int Rad1LwrFineDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad1LwrFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineDecTicksStatus);



int Rad1LwrActStbyStatusGetDataiCallback(void *inRefcon);
void Rad1LwrActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrActStbyStatus);


int Rad1LwrDigit1ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit1Value);

int Rad1LwrDigit2ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit2Value);

int Rad1LwrDigit3ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit3Value);

int Rad1LwrDigit4ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit4Value);

int Rad1LwrDigit5ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit5Value);

int Rad1LwrDigit6ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit6Value);

int Rad1LwrDigit7ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit7Value);

int Rad1LwrDigit8ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit8Value);

int Rad1LwrDigit9ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit9Value);

int Rad1LwrDigit10ValueGetDataiCallback(void *inRefcon);
void Rad1LwrDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit10Value);


int Rad2UprCom1StatusGetDataiCallback(void *inRefcon);
void Rad2UprCom1StatusSetDataiCallback(void *inRefcon, int Rad2UprCom1Status);

int Rad2UprCom2StatusGetDataiCallback(void *inRefcon);
void Rad2UprCom2StatusSetDataiCallback(void *inRefcon, int Rad2UprCom2Status);

int Rad2UprNav1StatusGetDataiCallback(void *inRefcon);
void Rad2UprNav1StatusSetDataiCallback(void *inRefcon, int Rad2UprNav1Status);

int Rad2UprNav2StatusGetDataiCallback(void *inRefcon);
void Rad2UprNav2StatusSetDataiCallback(void *inRefcon, int Rad2UprNav2Status);

int Rad2UprAdfStatusGetDataiCallback(void *inRefcon);
void Rad2UprAdfStatusSetDataiCallback(void *inRefcon, int Rad2UprAdfStatus);

int Rad2UprDmeStatusGetDataiCallback(void *inRefcon);
void Rad2UprDmeStatusSetDataiCallback(void *inRefcon, int Rad2UprDmeStatus);

int Rad2UprXpdrStatusGetDataiCallback(void *inRefcon);
void Rad2UprXpdrStatusSetDataiCallback(void *inRefcon, int Rad2UprXpdrStatus);



int Rad2UprCorseIncStatusGetDataiCallback(void *inRefcon);
void Rad2UprCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseIncStatus);

int Rad2UprCorseDecStatusGetDataiCallback(void *inRefcon);
void Rad2UprCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseDecStatus);

int Rad2UprFineIncStatusGetDataiCallback(void *inRefcon);
void Rad2UprFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineIncStatus);

int Rad2UprFineDecStatusGetDataiCallback(void *inRefcon);
void Rad2UprFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineDecStatus);



int Rad2UprCorseIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad2UprCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseIncTicksStatus);

int Rad2UprCorseDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad2UprCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseDecTicksStatus);

int Rad2UprFineIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad2UprFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineIncTicksStatus);

int Rad2UprFineDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad2UprFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineDecTicksStatus);



int Rad2UprActStbyStatusGetDataiCallback(void *inRefcon);
void Rad2UprActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad2UprActStbyStatus);



int Rad2UprDigit1ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit1Value);

int Rad2UprDigit2ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit2Value);

int Rad2UprDigit3ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit3Value);

int Rad2UprDigit4ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit4Value);

int Rad1UprDigit5ValueGetDataiCallback(void *inRefcon);
void Rad1UprDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit5Value);

int Rad2UprDigit6ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit6Value);

int Rad2UprDigit7ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit7Value);

int Rad2UprDigit8ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit8Value);

int Rad2UprDigit9ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit9Value);

int Rad2UprDigit10ValueGetDataiCallback(void *inRefcon);
void Rad2UprDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit10Value);

int Rad2WriteNowGetDataiCallback(void *inRefcon);
void Rad2WriteNowSetDataiCallback(void *inRefcon, int Rad2WriteNow);


int Rad2LwrCom1StatusGetDataiCallback(void *inRefcon);
void Rad2LwrCom1StatusSetDataiCallback(void *inRefcon, int Rad2LwrCom1Status);

int Rad2LwrCom2StatusGetDataiCallback(void *inRefcon);
void Rad2LwrCom2StatusSetDataiCallback(void *inRefcon, int Rad2LwrCom2Status);

int Rad2LwrNav1StatusGetDataiCallback(void *inRefcon);
void Rad2LwrNav1StatusSetDataiCallback(void *inRefcon, int Rad2LwrNav1Status);

int Rad2LwrNav2StatusGetDataiCallback(void *inRefcon);
void Rad2LwrNav2StatusSetDataiCallback(void *inRefcon, int Rad2LwrNav2Status);

int Rad2LwrAdfStatusGetDataiCallback(void *inRefcon);
void Rad2LwrAdfStatusSetDataiCallback(void *inRefcon, int Rad2LwrAdfStatus);

int Rad2LwrDmeStatusGetDataiCallback(void *inRefcon);
void Rad2LwrDmeStatusSetDataiCallback(void *inRefcon, int Rad2LwrDmeStatus);

int Rad2LwrXpdrStatusGetDataiCallback(void *inRefcon);
void Rad2LwrXpdrStatusSetDataiCallback(void *inRefcon, int Rad2LwrXpdrStatus);



int Rad2LwrCorseIncStatusGetDataiCallback(void *inRefcon);
void Rad2LwrCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseIncStatus);

int Rad2LwrCorseDecStatusGetDataiCallback(void *inRefcon);
void Rad2LwrCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseDecStatus);

int Rad2LwrFineIncStatusGetDataiCallback(void *inRefcon);
void Rad2LwrFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineIncStatus);

int Rad2LwrFineDecStatusGetDataiCallback(void *inRefcon);
void Rad2LwrFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineDecStatus);



int Rad2LwrCorseIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad2LwrCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseIncTicksStatus);

int Rad2LwrCorseDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad2LwrCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseDecTicksStatus);

int Rad2LwrFineIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad2LwrFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineIncTicksStatus);

int Rad2LwrFineDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad2LwrFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineDecTicksStatus);



int Rad2LwrActStbyStatusGetDataiCallback(void *inRefcon);
void Rad2LwrActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrActStbyStatus);



int Rad2LwrDigit1ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit1Value);

int Rad2LwrDigit2ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit2Value);

int Rad2LwrDigit3ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit3Value);

int Rad2LwrDigit4ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit4Value);

int Rad2LwrDigit5ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit5Value);

int Rad2LwrDigit6ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit6Value);

int Rad2LwrDigit7ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit7Value);

int Rad2LwrDigit8ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit8Value);

int Rad2LwrDigit9ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit9Value);

int Rad2LwrDigit10ValueGetDataiCallback(void *inRefcon);
void Rad2LwrDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit10Value);



int Rad3UprCom1StatusGetDataiCallback(void *inRefcon);
void Rad3UprCom1StatusSetDataiCallback(void *inRefcon, int Rad3UprCom1Status);

int Rad3UprCom2StatusGetDataiCallback(void *inRefcon);
void Rad3UprCom2StatusSetDataiCallback(void *inRefcon, int Rad3UprCom2Status);

int Rad3UprNav1StatusGetDataiCallback(void *inRefcon);
void Rad3UprNav1StatusSetDataiCallback(void *inRefcon, int Rad3UprNav1Status);

int Rad3UprNav2StatusGetDataiCallback(void *inRefcon);
void Rad3UprNav2StatusSetDataiCallback(void *inRefcon, int Rad3UprNav2Status);

int Rad3UprAdfStatusGetDataiCallback(void *inRefcon);
void Rad3UprAdfStatusSetDataiCallback(void *inRefcon, int Rad3UprAdfStatus);

int Rad3UprDmeStatusGetDataiCallback(void *inRefcon);
void Rad3UprDmeStatusSetDataiCallback(void *inRefcon, int Rad3UprDmeStatus);

int Rad3UprXpdrStatusGetDataiCallback(void *inRefcon);
void Rad3UprXpdrStatusSetDataiCallback(void *inRefcon, int Rad3UprXpdrStatus);



int Rad3UprCorseIncStatusGetDataiCallback(void *inRefcon);
void Rad3UprCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseIncStatus);

int Rad3UprCorseDecStatusGetDataiCallback(void *inRefcon);
void Rad3UprCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseDecStatus);

int Rad3UprFineIncStatusGetDataiCallback(void *inRefcon);
void Rad3UprFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineIncStatus);

int Rad3UprFineDecStatusGetDataiCallback(void *inRefcon);
void Rad3UprFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineDecStatus);



int Rad3UprCorseIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad3UprCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseIncTicksStatus);

int Rad3UprCorseDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad3UprCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseDecTicksStatus);

int Rad3UprFineIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad3UprFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineIncTicksStatus);

int Rad3UprFineDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad3UprFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineDecTicksStatus);



int Rad3UprActStbyStatusGetDataiCallback(void *inRefcon);
void Rad3UprActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad3UprActStbyStatus);



int Rad3UprDigit1ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit1Value);

int Rad3UprDigit2ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit2Value);

int Rad3UprDigit3ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit3Value);

int Rad3UprDigit4ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit4Value);

int Rad3UprDigit5ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit5Value);

int Rad3UprDigit6ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit6Value);

int Rad3UprDigit7ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit7Value);

int Rad3UprDigit8ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit8Value);

int Rad3UprDigit9ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit9Value);

int Rad3UprDigit10ValueGetDataiCallback(void *inRefcon);
void Rad3UprDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit10Value);

int Rad3WriteNowGetDataiCallback(void *inRefcon);
void Rad3WriteNowSetDataiCallback(void *inRefcon, int Rad3WriteNow);


int Rad3LwrCom1StatusGetDataiCallback(void *inRefcon);
void Rad3LwrCom1StatusSetDataiCallback(void *inRefcon, int Rad3LwrCom1Status);

int Rad3LwrCom2StatusGetDataiCallback(void *inRefcon);
void Rad3LwrCom2StatusSetDataiCallback(void *inRefcon, int Rad3LwrCom2Status);

int Rad3LwrNav1StatusGetDataiCallback(void *inRefcon);
void Rad3LwrNav1StatusSetDataiCallback(void *inRefcon, int Rad3LwrNav1Status);

int Rad3LwrNav2StatusGetDataiCallback(void *inRefcon);
void Rad3LwrNav2StatusSetDataiCallback(void *inRefcon, int Rad3LwrNav2Status);

int Rad3LwrAdfStatusGetDataiCallback(void *inRefcon);
void Rad3LwrAdfStatusSetDataiCallback(void *inRefcon, int Rad3LwrAdfStatus);

int Rad3LwrDmeStatusGetDataiCallback(void *inRefcon);
void Rad3LwrDmeStatusSetDataiCallback(void *inRefcon, int Rad3LwrDmeStatus);

int Rad3LwrXpdrStatusGetDataiCallback(void *inRefcon);
void Rad3LwrXpdrStatusSetDataiCallback(void *inRefcon, int Rad3LwrXpdrStatus);




int Rad3LwrCorseIncStatusGetDataiCallback(void *inRefcon);
void Rad3LwrCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseIncStatus);

int Rad3LwrCorseDecStatusGetDataiCallback(void *inRefcon);
void Rad3LwrCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseDecStatus);

int Rad3LwrFineIncStatusGetDataiCallback(void *inRefcon);
void Rad3LwrFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineIncStatus);

int Rad3LwrFineDecStatusGetDataiCallback(void *inRefcon);
void Rad3LwrFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineDecStatus);




int Rad3LwrCorseIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad3LwrCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseIncTicksStatus);

int Rad3LwrCorseDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad3LwrCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseDecTicksStatus);

int Rad3LwrFineIncTicksStatusGetDataiCallback(void *inRefcon);
void Rad3LwrFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineIncTicksStatus);

int Rad3LwrFineDecTicksStatusGetDataiCallback(void *inRefcon);
void Rad3LwrFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineDecTicksStatus);




int Rad3LwrActStbyStatusGetDataiCallback(void *inRefcon);
void Rad3LwrActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrActStbyStatus);


int Rad3LwrDigit1ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit1Value);

int Rad3LwrDigit2ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit2Value);

int Rad3LwrDigit3ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit3Value);

int Rad3LwrDigit4ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit4Value);

int Rad3LwrDigit5ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit5Value);

int Rad3LwrDigit6ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit6Value);

int Rad3LwrDigit7ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit7Value);

int Rad3LwrDigit8ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit8Value);

int Rad3LwrDigit9ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit9Value);

int Rad3LwrDigit10ValueGetDataiCallback(void *inRefcon);
void Rad3LwrDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit10Value);



string rad1_upper_com1_corse_up_remapable,
    rad1_upper_com1_corse_dn_remapable;
string rad1_upper_com1_fine_up_remapable,
    rad1_upper_com1_fine_dn_remapable;
string rad1_upper_com1_act_data_remapable,
    rad1_upper_com1_stby_data_remapable;
string rad1_upper_com1_actstby_btn_remapable_cmd,
    rad1_upper_com1_actstby_btn_remapable_data;
string rad1_upper_com1_actstby_btn_remapable_dataf;

string rad1_upper_com2_corse_up_remapable,
    rad1_upper_com2_corse_dn_remapable;
string rad1_upper_com2_fine_up_remapable,
    rad1_upper_com2_fine_dn_remapable;
string rad1_upper_com2_act_data_remapable,
    rad1_upper_com2_stby_data_remapable;
string rad1_upper_com2_actstby_btn_remapable_cmd,
    rad1_upper_com2_actstby_btn_remapable_data;
string rad1_upper_com2_actstby_btn_remapable_dataf;

string rad1_upper_obs1_corse_up_remapable,
    rad1_upper_obs1_corse_dn_remapable;
string rad1_upper_obs1_fine_up_remapable,
    rad1_upper_obs1_fine_dn_remapable;
string rad1_upper_obs1_remapable_dataf;
string rad1_upper_nav1_corse_up_remapable,
    rad1_upper_nav1_corse_dn_remapable;
string rad1_upper_nav1_fine_up_remapable,
    rad1_upper_nav1_fine_dn_remapable;
string rad1_upper_nav1_act_data_remapable,
    rad1_upper_nav1_stby_data_remapable;
string rad1_upper_nav1_actstby_btn_remapable_cmd,
    rad1_upper_nav1_actstby_btn_remapable_data;
string rad1_upper_nav1_actstby_btn_remapable_dataf;

string rad1_upper_obs2_corse_up_remapable,
    rad1_upper_obs2_corse_dn_remapable;
string rad1_upper_obs2_fine_up_remapable,
    rad1_upper_obs2_fine_dn_remapable;
string rad1_upper_obs2_remapable_dataf;
string rad1_upper_nav2_corse_up_remapable,
    rad1_upper_nav2_corse_dn_remapable;
string rad1_upper_nav2_fine_up_remapable,
    rad1_upper_nav2_fine_dn_remapable;
string rad1_upper_nav2_act_data_remapable,
    rad1_upper_nav2_stby_data_remapable;
string rad1_upper_nav2_actstby_btn_remapable_cmd,
    rad1_upper_nav2_actstby_btn_remapable_data;
string rad1_upper_nav2_actstby_btn_remapable_dataf;

string rad1_upper_adf_corse_up_remapable,
    rad1_upper_adf_corse_dn_remapable;
string rad1_upper_adf_fine_up_remapable,
    rad1_upper_adf_fine_dn_remapable;
string rad1_upper_adf_act_data_remapable,
    rad1_upper_adf_stby_data_remapable;
string rad1_upper_adf_actstby_btn_remapable_cmd,
    rad1_upper_adf_actstby_btn_remapable_data;
string rad1_upper_adf_actstby_btn_remapable_dataf;

string rad1_upper_dme_corse_up_remapable,
    rad1_upper_dme_corse_dn_remapable;
string rad1_upper_dme_fine_up_remapable,
    rad1_upper_dme_fine_dn_remapable;
string rad1_upper_dme_act_data_remapable,
    rad1_upper_dme_stby_data_remapable;
string rad1_upper_dme_actstby_btn_remapable_cmd,
    rad1_upper_dme_actstby_btn_remapable_data;
string rad1_upper_dme_actstby_btn_remapable_dataf;

string rad1_upper_xpdr_data_remapable,
    rad1_upper_xpdr_mode_remapable,
    rad1_upper_xpdr_baro_std_data_remapable;
string rad1_upper_xpdr_baro_up_remapable_cmd,
    rad1_upper_xpdr_baro_dn_remapable_cmd;

string rad1_lower_com1_corse_up_remapable,
    rad1_lower_com1_corse_dn_remapable;
string rad1_lower_com1_fine_up_remapable,
    rad1_lower_com1_fine_dn_remapable;
string rad1_lower_com1_act_data_remapable,
    rad1_lower_com1_stby_data_remapable;
string rad1_lower_com1_actstby_btn_remapable_cmd,
    rad1_lower_com1_actstby_btn_remapable_data;
string rad1_lower_com1_actstby_btn_remapable_dataf;

string rad1_lower_com2_corse_up_remapable,
    rad1_lower_com2_corse_dn_remapable;
string rad1_lower_com2_fine_up_remapable,
    rad1_lower_com2_fine_dn_remapable;
string rad1_lower_com2_act_data_remapable,
    rad1_lower_com2_stby_data_remapable;
string rad1_lower_com2_actstby_btn_remapable_cmd,
    rad1_lower_com2_actstby_btn_remapable_data;
string rad1_lower_com2_actstby_btn_remapable_dataf;

string rad1_lower_obs1_corse_up_remapable,
    rad1_lower_obs1_corse_dn_remapable;
string rad1_lower_obs1_fine_up_remapable,
    rad1_lower_obs1_fine_dn_remapable;
string rad1_lower_obs1_remapable_dataf;
string rad1_lower_nav1_corse_up_remapable,
    rad1_lower_nav1_corse_dn_remapable;
string rad1_lower_nav1_fine_up_remapable,
    rad1_lower_nav1_fine_dn_remapable;
string rad1_lower_nav1_act_data_remapable,
    rad1_lower_nav1_stby_data_remapable;
string rad1_lower_nav1_actstby_btn_remapable_cmd,
    rad1_lower_nav1_actstby_btn_remapable_data;
string rad1_lower_nav1_actstby_btn_remapable_dataf;

string rad1_lower_obs2_corse_up_remapable,
    rad1_lower_obs2_corse_dn_remapable;
string rad1_lower_obs2_fine_up_remapable,
    rad1_lower_obs2_fine_dn_remapable;
string rad1_lower_obs2_remapable_dataf;
string rad1_lower_nav2_corse_up_remapable,
    rad1_lower_nav2_corse_dn_remapable;
string rad1_lower_nav2_fine_up_remapable,
    rad1_lower_nav2_fine_dn_remapable;
string rad1_lower_nav2_act_data_remapable,
    rad1_lower_nav2_stby_data_remapable;
string rad1_lower_nav2_actstby_btn_remapable_cmd,
    rad1_lower_nav2_actstby_btn_remapable_data;
string rad1_lower_nav2_actstby_btn_remapable_dataf;

string rad1_lower_adf_corse_up_remapable,
    rad1_lower_adf_corse_dn_remapable;
string rad1_lower_adf_fine_up_remapable,
    rad1_lower_adf_fine_dn_remapable;
string rad1_lower_adf_act_data_remapable,
    rad1_lower_adf_stby_data_remapable;
string rad1_lower_adf_actstby_btn_remapable_cmd,
    rad1_lower_adf_actstby_btn_remapable_data;
string rad1_lower_adf_actstby_btn_remapable_dataf;

string rad1_lower_dme_corse_up_remapable,
    rad1_lower_dme_corse_dn_remapable;
string rad1_lower_dme_fine_up_remapable,
    rad1_lower_dme_fine_dn_remapable;
string rad1_lower_dme_act_data_remapable,
    rad1_lower_dme_stby_data_remapable;
string rad1_lower_dme_actstby_btn_remapable_cmd,
    rad1_lower_dme_actstby_btn_remapable_data;
string rad1_lower_dme_actstby_btn_remapable_dataf;

string rad1_lower_xpdr_data_remapable,
    rad1_lower_xpdr_mode_remapable;
string rad1_lower_xpdr_baro_std_data_remapable;
string rad1_lower_xpdr_baro_up_remapable_cmd,
    rad1_lower_xpdr_baro_dn_remapable_cmd;


string rad2_upper_com1_corse_up_remapable,
    rad2_upper_com1_corse_dn_remapable;
string rad2_upper_com1_fine_up_remapable,
    rad2_upper_com1_fine_dn_remapable;
string rad2_upper_com1_act_data_remapable,
    rad2_upper_com1_stby_data_remapable;
string rad2_upper_com1_actstby_btn_remapable_cmd,
    rad2_upper_com1_actstby_btn_remapable_data;
string rad2_upper_com1_actstby_btn_remapable_dataf;

string rad2_upper_com2_corse_up_remapable,
    rad2_upper_com2_corse_dn_remapable;
string rad2_upper_com2_fine_up_remapable,
    rad2_upper_com2_fine_dn_remapable;
string rad2_upper_com2_act_data_remapable,
    rad2_upper_com2_stby_data_remapable;
string rad2_upper_com2_actstby_btn_remapable_cmd,
    rad2_upper_com2_actstby_btn_remapable_data;
string rad2_upper_com2_actstby_btn_remapable_dataf;

string rad2_upper_obs1_corse_up_remapable,
    rad2_upper_obs1_corse_dn_remapable;
string rad2_upper_obs1_fine_up_remapable,
    rad2_upper_obs1_fine_dn_remapable;
string rad2_upper_obs1_remapable_dataf;
string rad2_upper_nav1_corse_up_remapable,
    rad2_upper_nav1_corse_dn_remapable;
string rad2_upper_nav1_fine_up_remapable,
    rad2_upper_nav1_fine_dn_remapable;
string rad2_upper_nav1_act_data_remapable,
    rad2_upper_nav1_stby_data_remapable;
string rad2_upper_nav1_actstby_btn_remapable_cmd,
    rad2_upper_nav1_actstby_btn_remapable_data;
string rad2_upper_nav1_actstby_btn_remapable_dataf;

string rad2_upper_obs2_corse_up_remapable,
    rad2_upper_obs2_corse_dn_remapable;
string rad2_upper_obs2_fine_up_remapable,
    rad2_upper_obs2_fine_dn_remapable;
string rad2_upper_obs2_remapable_dataf;
string rad2_upper_nav2_corse_up_remapable,
    rad2_upper_nav2_corse_dn_remapable;
string rad2_upper_nav2_fine_up_remapable,
    rad2_upper_nav2_fine_dn_remapable;
string rad2_upper_nav2_act_data_remapable,
    rad2_upper_nav2_stby_data_remapable;
string rad2_upper_nav2_actstby_btn_remapable_cmd,
    rad2_upper_nav2_actstby_btn_remapable_data;
string rad2_upper_nav2_actstby_btn_remapable_dataf;

string rad2_upper_adf_corse_up_remapable,
    rad2_upper_adf_corse_dn_remapable;
string rad2_upper_adf_fine_up_remapable,
    rad2_upper_adf_fine_dn_remapable;
string rad2_upper_adf_act_data_remapable,
    rad2_upper_adf_stby_data_remapable;
string rad2_upper_adf_actstby_btn_remapable_cmd,
    rad2_upper_adf_actstby_btn_remapable_data;
string rad2_upper_adf_actstby_btn_remapable_dataf;

string rad2_upper_dme_corse_up_remapable,
    rad2_upper_dme_corse_dn_remapable;
string rad2_upper_dme_fine_up_remapable,
    rad2_upper_dme_fine_dn_remapable;
string rad2_upper_dme_act_data_remapable,
    rad2_upper_dme_stby_data_remapable;
string rad2_upper_dme_actstby_btn_remapable_cmd,
    rad2_upper_dme_actstby_btn_remapable_data;
string rad2_upper_dme_actstby_btn_remapable_dataf;

string rad2_upper_xpdr_data_remapable,
    rad2_upper_xpdr_mode_remapable,
    rad2_upper_xpdr_baro_std_data_remapable;
string rad2_upper_xpdr_baro_up_remapable_cmd,
    rad2_upper_xpdr_baro_dn_remapable_cmd;

string rad2_lower_com1_corse_up_remapable,
    rad2_lower_com1_corse_dn_remapable;
string rad2_lower_com1_fine_up_remapable,
    rad2_lower_com1_fine_dn_remapable;
string rad2_lower_com1_act_data_remapable,
    rad2_lower_com1_stby_data_remapable;
string rad2_lower_com1_actstby_btn_remapable_cmd,
    rad2_lower_com1_actstby_btn_remapable_data;
string rad2_lower_com1_actstby_btn_remapable_dataf;

string rad2_lower_com2_corse_up_remapable,
    rad2_lower_com2_corse_dn_remapable;
string rad2_lower_com2_fine_up_remapable,
    rad2_lower_com2_fine_dn_remapable;
string rad2_lower_com2_act_data_remapable,
    rad2_lower_com2_stby_data_remapable;
string rad2_lower_com2_actstby_btn_remapable_cmd,
    rad2_lower_com2_actstby_btn_remapable_data;
string rad2_lower_com2_actstby_btn_remapable_dataf;

string rad2_lower_obs1_corse_up_remapable,
    rad2_lower_obs1_corse_dn_remapable;
string rad2_lower_obs1_fine_up_remapable,
    rad2_lower_obs1_fine_dn_remapable;
string rad2_lower_obs1_remapable_dataf;
string rad2_lower_nav1_corse_up_remapable,
    rad2_lower_nav1_corse_dn_remapable;
string rad2_lower_nav1_fine_up_remapable,
    rad2_lower_nav1_fine_dn_remapable;
string rad2_lower_nav1_act_data_remapable,
    rad2_lower_nav1_stby_data_remapable;
string rad2_lower_nav1_actstby_btn_remapable_cmd,
    rad2_lower_nav1_actstby_btn_remapable_data;
string rad2_lower_nav1_actstby_btn_remapable_dataf;

string rad2_lower_obs2_corse_up_remapable,
    rad2_lower_obs2_corse_dn_remapable;
string rad2_lower_obs2_fine_up_remapable,
    rad2_lower_obs2_fine_dn_remapable;
string rad2_lower_obs2_remapable_dataf;
string rad2_lower_nav2_corse_up_remapable,
    rad2_lower_nav2_corse_dn_remapable;
string rad2_lower_nav2_fine_up_remapable,
    rad2_lower_nav2_fine_dn_remapable;
string rad2_lower_nav2_act_data_remapable,
    rad2_lower_nav2_stby_data_remapable;
string rad2_lower_nav2_actstby_btn_remapable_cmd,
    rad2_lower_nav2_actstby_btn_remapable_data;
string rad2_lower_nav2_actstby_btn_remapable_dataf;

string rad2_lower_adf_corse_up_remapable,
    rad2_lower_adf_corse_dn_remapable;
string rad2_lower_adf_fine_up_remapable,
    rad2_lower_adf_fine_dn_remapable;
string rad2_lower_adf_act_data_remapable,
    rad2_lower_adf_stby_data_remapable;
string rad2_lower_adf_actstby_btn_remapable_cmd,
    rad2_lower_adf_actstby_btn_remapable_data;
string rad2_lower_adf_actstby_btn_remapable_dataf;

string rad2_lower_dme_corse_up_remapable,
    rad2_lower_dme_corse_dn_remapable;
string rad2_lower_dme_fine_up_remapable,
    rad2_lower_dme_fine_dn_remapable;
string rad2_lower_dme_act_data_remapable,
    rad2_lower_dme_stby_data_remapable;
string rad2_lower_dme_actstby_btn_remapable_cmd,
    rad2_lower_dme_actstby_btn_remapable_data;
string rad2_lower_dme_actstby_btn_remapable_dataf;

string rad2_lower_xpdr_data_remapable,
    rad2_lower_xpdr_mode_remapable,
    rad2_lower_xpdr_baro_std_data_remapable;
string rad2_lower_xpdr_baro_up_remapable_cmd,
    rad2_lower_xpdr_baro_dn_remapable_cmd;


string rad3_upper_com1_corse_up_remapable,
    rad3_upper_com1_corse_dn_remapable;
string rad3_upper_com1_fine_up_remapable,
    rad3_upper_com1_fine_dn_remapable;
string rad3_upper_com1_act_data_remapable,
    rad3_upper_com1_stby_data_remapable;
string rad3_upper_com1_actstby_btn_remapable_cmd,
    rad3_upper_com1_actstby_btn_remapable_data;
string rad3_upper_com1_actstby_btn_remapable_dataf;

string rad3_upper_com2_corse_up_remapable,
    rad3_upper_com2_corse_dn_remapable;
string rad3_upper_com2_fine_up_remapable,
    rad3_upper_com2_fine_dn_remapable;
string rad3_upper_com2_act_data_remapable,
    rad3_upper_com2_stby_data_remapable;
string rad3_upper_com2_actstby_btn_remapable_cmd,
    rad3_upper_com2_actstby_btn_remapable_data;
string rad3_upper_com2_actstby_btn_remapable_dataf;

string rad3_upper_obs1_corse_up_remapable,
    rad3_upper_obs1_corse_dn_remapable;
string rad3_upper_obs1_fine_up_remapable,
    rad3_upper_obs1_fine_dn_remapable;
string rad3_upper_obs1_remapable_dataf;
string rad3_upper_nav1_corse_up_remapable,
    rad3_upper_nav1_corse_dn_remapable;
string rad3_upper_nav1_fine_up_remapable,
    rad3_upper_nav1_fine_dn_remapable;
string rad3_upper_nav1_act_data_remapable,
    rad3_upper_nav1_stby_data_remapable;
string rad3_upper_nav1_actstby_btn_remapable_cmd,
    rad3_upper_nav1_actstby_btn_remapable_data;
string rad3_upper_nav1_actstby_btn_remapable_dataf;

string rad3_upper_obs2_corse_up_remapable,
    rad3_upper_obs2_corse_dn_remapable;
string rad3_upper_obs2_fine_up_remapable,
    rad3_upper_obs2_fine_dn_remapable;
string rad3_upper_obs2_remapable_dataf;
string rad3_upper_nav2_corse_up_remapable,
    rad3_upper_nav2_corse_dn_remapable;
string rad3_upper_nav2_fine_up_remapable,
    rad3_upper_nav2_fine_dn_remapable;
string rad3_upper_nav2_act_data_remapable,
    rad3_upper_nav2_stby_data_remapable;
string rad3_upper_nav2_actstby_btn_remapable_cmd,
    rad3_upper_nav2_actstby_btn_remapable_data;
string rad3_upper_nav2_actstby_btn_remapable_dataf;

string rad3_upper_adf_corse_up_remapable,
    rad3_upper_adf_corse_dn_remapable;
string rad3_upper_adf_fine_up_remapable,
    rad3_upper_adf_fine_dn_remapable;
string rad3_upper_adf_act_data_remapable,
    rad3_upper_adf_stby_data_remapable;
string rad3_upper_adf_actstby_btn_remapable_cmd,
    rad3_upper_adf_actstby_btn_remapable_data;
string rad3_upper_adf_actstby_btn_remapable_dataf;

string rad3_upper_dme_corse_up_remapable,
    rad3_upper_dme_corse_dn_remapable;
string rad3_upper_dme_fine_up_remapable,
    rad3_upper_dme_fine_dn_remapable;
string rad3_upper_dme_act_data_remapable,
    rad3_upper_dme_stby_data_remapable;
string rad3_upper_dme_actstby_btn_remapable_cmd,
    rad3_upper_dme_actstby_btn_remapable_data;
string rad3_upper_dme_actstby_btn_remapable_dataf;

string rad3_upper_xpdr_data_remapable,
    rad3_upper_xpdr_mode_remapable,
    rad3_upper_xpdr_baro_std_data_remapable;
string rad3_upper_xpdr_baro_up_remapable_cmd,
    rad3_upper_xpdr_baro_dn_remapable_cmd;

string rad3_lower_com1_corse_up_remapable,
    rad3_lower_com1_corse_dn_remapable;
string rad3_lower_com1_fine_up_remapable,
    rad3_lower_com1_fine_dn_remapable;
string rad3_lower_com1_act_data_remapable,
    rad3_lower_com1_stby_data_remapable;
string rad3_lower_com1_actstby_btn_remapable_cmd,
    rad3_lower_com1_actstby_btn_remapable_data;
string rad3_lower_com1_actstby_btn_remapable_dataf;

string rad3_lower_com2_corse_up_remapable,
    rad3_lower_com2_corse_dn_remapable;
string rad3_lower_com2_fine_up_remapable,
    rad3_lower_com2_fine_dn_remapable;
string rad3_lower_com2_act_data_remapable,
    rad3_lower_com2_stby_data_remapable;
string rad3_lower_com2_actstby_btn_remapable_cmd,
    rad3_lower_com2_actstby_btn_remapable_data;
string rad3_lower_com2_actstby_btn_remapable_dataf;

string rad3_lower_obs1_corse_up_remapable,
    rad3_lower_obs1_corse_dn_remapable;
string rad3_lower_obs1_fine_up_remapable,
    rad3_lower_obs1_fine_dn_remapable;
string rad3_lower_obs1_remapable_dataf;
string rad3_lower_nav1_corse_up_remapable,
    rad3_lower_nav1_corse_dn_remapable;
string rad3_lower_nav1_fine_up_remapable,
    rad3_lower_nav1_fine_dn_remapable;
string rad3_lower_nav1_act_data_remapable,
    rad3_lower_nav1_stby_data_remapable;
string rad3_lower_nav1_actstby_btn_remapable_cmd,
    rad3_lower_nav1_actstby_btn_remapable_data;
string rad3_lower_nav1_actstby_btn_remapable_dataf;

string rad3_lower_obs2_corse_up_remapable,
    rad3_lower_obs2_corse_dn_remapable;
string rad3_lower_obs2_fine_up_remapable,
    rad3_lower_obs2_fine_dn_remapable;
string rad3_lower_obs2_remapable_dataf;
string rad3_lower_nav2_corse_up_remapable,
    rad3_lower_nav2_corse_dn_remapable;
string rad3_lower_nav2_fine_up_remapable,
    rad3_lower_nav2_fine_dn_remapable;
string rad3_lower_nav2_act_data_remapable,
    rad3_lower_nav2_stby_data_remapable;
string rad3_lower_nav2_actstby_btn_remapable_cmd,
    rad3_lower_nav2_actstby_btn_remapable_data;
string rad3_lower_nav2_actstby_btn_remapable_dataf;

string rad3_lower_adf_corse_up_remapable,
    rad3_lower_adf_corse_dn_remapable;
string rad3_lower_adf_fine_up_remapable,
    rad3_lower_adf_fine_dn_remapable;
string rad3_lower_adf_act_data_remapable,
    rad3_lower_adf_stby_data_remapable;
string rad3_lower_adf_actstby_btn_remapable_cmd,
    rad3_lower_adf_actstby_btn_remapable_data;
string rad3_lower_adf_actstby_btn_remapable_dataf;

string rad3_lower_dme_corse_up_remapable,
    rad3_lower_dme_corse_dn_remapable;
string rad3_lower_dme_fine_up_remapable,
    rad3_lower_dme_fine_dn_remapable;
string rad3_lower_dme_act_data_remapable,
    rad3_lower_dme_stby_data_remapable;
string rad3_lower_dme_actstby_btn_remapable_cmd,
    rad3_lower_dme_actstby_btn_remapable_data;
string rad3_lower_dme_actstby_btn_remapable_dataf;

string rad3_lower_xpdr_data_remapable,
    rad3_lower_xpdr_mode_remapable,
    rad3_lower_xpdr_baro_std_data_remapable;
string rad3_lower_xpdr_baro_up_remapable_cmd,
    rad3_lower_xpdr_baro_dn_remapable_cmd;


char RadioSpeedText[50][200] = {
    "FREQ KNOB  1 PULSE PER COMMAND",
    "FREQ KNOB  2 PULSES PER COMMAND",
    "FREQ KNOB  3 PULSES PER COMMAND",
    "FREQ KNOB  4 PULSES PER COMMAND",
    "FREQ KNOB  5 PULSES PER COMMAND",
    "end"
};

hid_device *radiohandle[4];

// ********************** Multi Panel variables ***********************


int xpanelsfnbutton = 0,
    xpanelscrstoggle = 0;
int xpanelsleftstartfnbutton = 0;


// This is the storage for the data we own.



string trim_up_remapable,
    trim_dn_remapable;
string flaps_up_remapable,
    flaps_dn_remapable;



char MultiSpeedText[50][200] = {
    "FREQ KNOB  1 PULSE PER COMMAND",
    "FREQ KNOB  2 PULSES PER COMMAND",
    "FREQ KNOB  3 PULSES PER COMMAND",
    "FREQ KNOB  4 PULSES PER COMMAND",
    "FREQ KNOB  5 PULSES PER COMMAND",
    "end"
};

char MultiTrimSpeedText[50][200] = {
    "TRIM X1",
    "TRIM X2",
    "TRIM X3",
    "end"
};

hid_device *multihandle;



// ****************** Switch Panel variables *******************************
int switchcnt = 0,
    switchres,
    stopswitchcnt;

int magoffswitchenable,
    magrightswitchenable,
    magleftswitchenable;
int magbothswitchenable,
    magstartswitchenable;
int batmasterswitchenable,
    altmasterswitchenable;
int avionicsmasterswitchenable,
    fuelpumpswitchenable;
int deiceswitchenable,
    pitotheatswitchenable;
int landinggearknobupenable,
    landinggearknobdnenable;
int cowlflapsenable,
    panellightswitchenable;
int beaconlightswitchenable,
    navlightswitchenable;
int strobelightswitchenable,
    taxilightswitchenable;
int landinglightswitchenable,
    bataltinverse;
int panellightsenable,
    starterswitchenable;

int mag_off_switch_data_on_value,
    mag_off_switch_data_off_value;
int mag_off2_switch_data_on_value,
    mag_off2_switch_data_off_value;
int mag_off3_switch_data_on_value,
    mag_off3_switch_data_off_value;
int mag_off4_switch_data_on_value,
    mag_off4_switch_data_off_value;
int mag_off5_switch_data_on_value,
    mag_off5_switch_data_off_value;
int mag_off6_switch_data_on_value,
    mag_off6_switch_data_off_value;
int mag_off7_switch_data_on_value,
    mag_off7_switch_data_off_value;
int mag_off8_switch_data_on_value,
    mag_off8_switch_data_off_value;
int mag_off9_switch_data_on_value,
    mag_off9_switch_data_off_value;
int mag_off10_switch_data_on_value,
    mag_off10_switch_data_off_value;

int mag_right_switch_data_on_value,
    mag_right_switch_data_off_value;
int mag_right2_switch_data_on_value,
    mag_right2_switch_data_off_value;
int mag_right3_switch_data_on_value,
    mag_right3_switch_data_off_value;
int mag_right4_switch_data_on_value,
    mag_right4_switch_data_off_value;
int mag_right5_switch_data_on_value,
    mag_right5_switch_data_off_value;
int mag_right6_switch_data_on_value,
    mag_right6_switch_data_off_value;
int mag_right7_switch_data_on_value,
    mag_right7_switch_data_off_value;
int mag_right8_switch_data_on_value,
    mag_right8_switch_data_off_value;
int mag_right9_switch_data_on_value,
    mag_right9_switch_data_off_value;
int mag_right10_switch_data_on_value,
    mag_right10_switch_data_off_value;

int mag_left_switch_data_on_value,
    mag_left_switch_data_off_value;
int mag_left2_switch_data_on_value,
    mag_left2_switch_data_off_value;
int mag_left3_switch_data_on_value,
    mag_left3_switch_data_off_value;
int mag_left4_switch_data_on_value,
    mag_left4_switch_data_off_value;
int mag_left5_switch_data_on_value,
    mag_left5_switch_data_off_value;
int mag_left6_switch_data_on_value,
    mag_left6_switch_data_off_value;
int mag_left7_switch_data_on_value,
    mag_left7_switch_data_off_value;
int mag_left8_switch_data_on_value,
    mag_left8_switch_data_off_value;
int mag_left9_switch_data_on_value,
    mag_left9_switch_data_off_value;
int mag_left10_switch_data_on_value,
    mag_left10_switch_data_off_value;

int mag_both_switch_data_on_value,
    mag_both_switch_data_off_value;
int mag_both2_switch_data_on_value,
    mag_both2_switch_data_off_value;
int mag_both3_switch_data_on_value,
    mag_both3_switch_data_off_value;
int mag_both4_switch_data_on_value,
    mag_both4_switch_data_off_value;
int mag_both5_switch_data_on_value,
    mag_both5_switch_data_off_value;
int mag_both6_switch_data_on_value,
    mag_both6_switch_data_off_value;
int mag_both7_switch_data_on_value,
    mag_both7_switch_data_off_value;
int mag_both8_switch_data_on_value,
    mag_both8_switch_data_off_value;
int mag_both9_switch_data_on_value,
    mag_both9_switch_data_off_value;
int mag_both10_switch_data_on_value,
    mag_both10_switch_data_off_value;


int mag_start_switch_data_on_value,
    mag_start_switch_data_off_value;
int mag_start2_switch_data_on_value,
    mag_start2_switch_data_off_value;
int mag_start3_switch_data_on_value,
    mag_start3_switch_data_off_value;
int mag_start4_switch_data_on_value,
    mag_start4_switch_data_off_value;
int mag_start5_switch_data_on_value,
    mag_start5_switch_data_off_value;
int mag_start6_switch_data_on_value,
    mag_start6_switch_data_off_value;
int mag_start7_switch_data_on_value,
    mag_start7_switch_data_off_value;
int mag_start8_switch_data_on_value,
    mag_start8_switch_data_off_value;
int mag_start9_switch_data_on_value,
    mag_start9_switch_data_off_value;
int mag_start10_switch_data_on_value,
    mag_start10_switch_data_off_value;

int mag_start_switch_left_data_on_value,
    mag_start_switch_left_data_off_value;
int mag_start2_switch_left_data_on_value,
    mag_start2_switch_left_data_off_value;
int mag_start3_switch_left_data_on_value,
    mag_start3_switch_left_data_off_value;
int mag_start4_switch_left_data_on_value,
    mag_start4_switch_left_data_off_value;
int mag_start5_switch_left_data_on_value,
    mag_start5_switch_left_data_off_value;
int mag_start6_switch_left_data_on_value,
    mag_start6_switch_left_data_off_value;
int mag_start7_switch_left_data_on_value,
    mag_start7_switch_left_data_off_value;
int mag_start8_switch_left_data_on_value,
    mag_start8_switch_left_data_off_value;
int mag_start9_switch_left_data_on_value,
    mag_start9_switch_left_data_off_value;
int mag_start10_switch_left_data_on_value,
    mag_start10_switch_left_data_off_value;


int bat_master_switch_data_on_value,
    bat_master_switch_data_off_value;
int bat2_master_switch_data_on_value,
    bat2_master_switch_data_off_value;
int bat3_master_switch_data_on_value,
    bat3_master_switch_data_off_value;
int bat4_master_switch_data_on_value,
    bat4_master_switch_data_off_value;
int bat5_master_switch_data_on_value,
    bat5_master_switch_data_off_value;
int bat6_master_switch_data_on_value,
    bat6_master_switch_data_off_value;
int bat7_master_switch_data_on_value,
    bat7_master_switch_data_off_value;
int bat8_master_switch_data_on_value,
    bat8_master_switch_data_off_value;

int alt_master_switch_data_on_value,
    alt_master_switch_data_off_value;
int alt2_master_switch_data_on_value,
    alt2_master_switch_data_off_value;
int alt3_master_switch_data_on_value,
    alt3_master_switch_data_off_value;
int alt4_master_switch_data_on_value,
    alt4_master_switch_data_off_value;
int alt5_master_switch_data_on_value,
    alt5_master_switch_data_off_value;
int alt6_master_switch_data_on_value,
    alt6_master_switch_data_off_value;
int alt7_master_switch_data_on_value,
    alt7_master_switch_data_off_value;
int alt8_master_switch_data_on_value,
    alt8_master_switch_data_off_value;


int av_master_switch_data_on_value,
    av_master_switch_data_off_value;
int av2_master_switch_data_on_value,
    av2_master_switch_data_off_value;
int av3_master_switch_data_on_value,
    av3_master_switch_data_off_value;
int av4_master_switch_data_on_value,
    av4_master_switch_data_off_value;
int av5_master_switch_data_on_value,
    av5_master_switch_data_off_value;
int av6_master_switch_data_on_value,
    av6_master_switch_data_off_value;
int av7_master_switch_data_on_value,
    av7_master_switch_data_off_value;
int av8_master_switch_data_on_value,
    av8_master_switch_data_off_value;

int av9_master_switch_data_on_value,
    av9_master_switch_data_off_value;
int av10_master_switch_data_on_value,
    av10_master_switch_data_off_value;
int av11_master_switch_data_on_value,
    av11_master_switch_data_off_value;
int av12_master_switch_data_on_value,
    av12_master_switch_data_off_value;
int av13_master_switch_data_on_value,
    av13_master_switch_data_off_value;
int av14_master_switch_data_on_value,
    av14_master_switch_data_off_value;
int av15_master_switch_data_on_value,
    av15_master_switch_data_off_value;
int av16_master_switch_data_on_value,
    av16_master_switch_data_off_value;


int fuel_pump_switch_data_on_value,
    fuel_pump_switch_data_off_value;
int fuel_pump2_switch_data_on_value,
    fuel_pump2_switch_data_off_value;
int fuel_pump3_switch_data_on_value,
    fuel_pump3_switch_data_off_value;
int fuel_pump4_switch_data_on_value,
    fuel_pump4_switch_data_off_value;
int fuel_pump5_switch_data_on_value,
    fuel_pump5_switch_data_off_value;
int fuel_pump6_switch_data_on_value,
    fuel_pump6_switch_data_off_value;
int fuel_pump7_switch_data_on_value,
    fuel_pump7_switch_data_off_value;
int fuel_pump8_switch_data_on_value,
    fuel_pump8_switch_data_off_value;


int deice_switch_data_on_value,
    deice_switch_data_off_value;
int deice2_switch_data_on_value,
    deice2_switch_data_off_value;
int deice3_switch_data_on_value,
    deice3_switch_data_off_value;
int deice4_switch_data_on_value,
    deice4_switch_data_off_value;
int deice5_switch_data_on_value,
    deice5_switch_data_off_value;
int deice6_switch_data_on_value,
    deice6_switch_data_off_value;
int deice7_switch_data_on_value,
    deice7_switch_data_off_value;
int deice8_switch_data_on_value,
    deice8_switch_data_off_value;

int pitot_heat_switch_data_on_value,
    pitot_heat_switch_data_off_value;
int pitot2_heat_switch_data_on_value,
    pitot2_heat_switch_data_off_value;
int pitot3_heat_switch_data_on_value,
    pitot3_heat_switch_data_off_value;
int pitot4_heat_switch_data_on_value,
    pitot4_heat_switch_data_off_value;
int pitot5_heat_switch_data_on_value,
    pitot5_heat_switch_data_off_value;
int pitot6_heat_switch_data_on_value,
    pitot6_heat_switch_data_off_value;
int pitot7_heat_switch_data_on_value,
    pitot7_heat_switch_data_off_value;
int pitot8_heat_switch_data_on_value,
    pitot8_heat_switch_data_off_value;

int gear_switch_up_data_on_value,
    gear_switch_up_data_off_value;
int gear_switch_down_data_on_value,
    gear_switch_down_data_off_value;

int cowl_flaps_data_on_value,
    cowl_flaps_data_off_value;
int cowl2_flaps_data_on_value,
    cowl2_flaps_data_off_value;
int cowl3_flaps_data_on_value,
    cowl3_flaps_data_off_value;
int cowl4_flaps_data_on_value,
    cowl4_flaps_data_off_value;
int cowl5_flaps_data_on_value,
    cowl5_flaps_data_off_value;
int cowl6_flaps_data_on_value,
    cowl6_flaps_data_off_value;
int cowl7_flaps_data_on_value,
    cowl7_flaps_data_off_value;
int cowl8_flaps_data_on_value,
    cowl8_flaps_data_off_value;

int panel_lights_switch_data_on_value,
    panel_lights_switch_data_off_value,
    panel_lights_switch_data_array_offset,
    panel_lights_switch_data_array_size;
int panel_lights_switch2_data_on_value,
    panel_lights_switch2_data_off_value,
    panel_lights_switch2_data_array_offset,
    panel_lights_switch2_data_array_size;
int panel_lights_switch3_data_on_value,
    panel_lights_switch3_data_off_value,
    panel_lights_switch3_data_array_offset,
    panel_lights_switch3_data_array_size;
int panel_lights_switch4_data_on_value,
    panel_lights_switch4_data_off_value,
    panel_lights_switch4_data_array_offset,
    panel_lights_switch4_data_array_size;
int panel_lights_switch5_data_on_value,
    panel_lights_switch5_data_off_value,
    panel_lights_switch5_data_array_offset,
    panel_lights_switch5_data_array_size;
int panel_lights_switch6_data_on_value,
    panel_lights_switch6_data_off_value,
    panel_lights_switch6_data_array_offset,
    panel_lights_switch6_data_array_size;
int panel_lights_switch7_data_on_value,
    panel_lights_switch7_data_off_value,
    panel_lights_switch7_data_array_offset,
    panel_lights_switch7_data_array_size;
int panel_lights_switch8_data_on_value,
    panel_lights_switch8_data_off_value,
    panel_lights_switch8_data_array_offset,
    panel_lights_switch8_data_array_size;

int beacon_lights_switch_data_on_value,
    beacon_lights_switch_data_off_value;
int beacon_lights_switch2_data_on_value,
    beacon_lights_switch2_data_off_value;
int beacon_lights_switch3_data_on_value,
    beacon_lights_switch3_data_off_value;
int beacon_lights_switch4_data_on_value,
    beacon_lights_switch4_data_off_value;

int nav_lights_switch_data_on_value,
    nav_lights_switch_data_off_value;
int nav_lights_switch2_data_on_value,
    nav_lights_switch2_data_off_value;
int nav_lights_switch3_data_on_value,
    nav_lights_switch3_data_off_value;
int nav_lights_switch4_data_on_value,
    nav_lights_switch4_data_off_value;

int strobe_lights_switch_data_on_value,
    strobe_lights_switch_data_off_value;
int strobe_lights_switch2_data_on_value,
    strobe_lights_switch2_data_off_value;
int strobe_lights_switch3_data_on_value,
    strobe_lights_switch3_data_off_value;
int strobe_lights_switch4_data_on_value,
    strobe_lights_switch4_data_off_value;

int taxi_lights_switch_data_on_value,
    taxi_lights_switch_data_off_value;
int taxi_lights_switch2_data_on_value,
    taxi_lights_switch2_data_off_value;
int taxi_lights_switch3_data_on_value,
    taxi_lights_switch3_data_off_value;
int taxi_lights_switch4_data_on_value,
    taxi_lights_switch4_data_off_value;

int landing_lights_switch_data_on_value,
    landing_lights_switch_data_off_value;
int landing_lights_switch2_data_on_value,
    landing_lights_switch2_data_off_value;
int landing_lights_switch3_data_on_value,
    landing_lights_switch3_data_off_value;
int landing_lights_switch4_data_on_value,
    landing_lights_switch4_data_off_value;

// This is the storage for the data we own.

static int XsaitekpanelsVersionData = 0;
static int XsaitekpanelsFnButtonData = 0;
static int XsaitekpanelsLeftStartFnButtonData = 0;

int XsaitekpanelsVersionGetDataiCallback(void *inRefcon);
void XsaitekpanelsVersionSetDataiCallback(void *inRefcon,
    int XsaitekpanelsVersion);

int XsaitekpanelsFnButtonGetDataiCallback(void *inRefcon);
void XsaitekpanelsFnButtonSetDataiCallback(void *inRefcon,
    int XsaitekpanelsFnButton);

int XsaitekpanelsLeftStartFnButtonGetDataiCallback(void *inRefcon);
void XsaitekpanelsLeftStartFnButtonSetDataiCallback(void *inRefcon,
    int XsaitekpanelsLeftStartFnButton);

/* This callback is called whenever our shared data is changed. */

static void XsaitekpanelsInteger1DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger2DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger3DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger4DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger5DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger6DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger7DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger8DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger9DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger10DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger11DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger12DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger13DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger14DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger15DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger16DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger17DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger18DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger19DataChangedCallback(void *inRefcon);
static void XsaitekpanelsInteger20DataChangedCallback(void *inRefcon);


static void XsaitekpanelsFloat1DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat2DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat3DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat4DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat5DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat6DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat7DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat8DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat9DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat10DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat11DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat12DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat13DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat14DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat15DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat16DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat17DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat18DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat19DataChangedCallback(void *inRefcon);
static void XsaitekpanelsFloat20DataChangedCallback(void *inRefcon);



static int SwitchPanelCountData = 0;
static int SwitchStartOffOwnedData = 0,
    SwitchStartRightOwnedData = 0;
static int SwitchStartLeftOwnedData = 0,
    SwitchStartBothOwnedData = 0;
static int SwitchStartStartOwnedData = 0;
static int SwitchBatOwnedData = 0,
    SwitchAltOwnedData = 0;
static int SwitchAvOwnedData = 0,
    SwitchFuelOwnedData = 0;
static int SwitchDiceOwnedData = 0,
    SwitchPitotOwnedData = 0;
static int SwitchGearUpOwnedData = 0,
    SwitchGearDnOwnedData = 0;
static int SwitchCowlOwnedData = 0,
    SwitchPanelOwnedData = 0;
static int SwitchBeaconOwnedData = 0,
    SwitchNavOwnedData = 0;
static int SwitchStrobeOwnedData = 0,
    SwitchTaxiOwnedData = 0;
static int SwitchLandingOwnedData = 0;



int SwitchPanelCountGetDataiCallback(void *inRefcon);
void SwitchPanelCountSetDataiCallback(void *inRefcon, int SwitchPanelCount);

int SwitchStartOffPositionGetDataiCallback(void *inRefcon);
void SwitchStartOffPositionSetDataiCallback(void *inRefcon,
    int SwitchStartOffPosition);

int SwitchStartRightPositionGetDataiCallback(void *inRefcon);
void SwitchStartRightPositionSetDataiCallback(void *inRefcon,
    int SwitchStartRightPosition);

int SwitchStartLeftPositionGetDataiCallback(void *inRefcon);
void SwitchStartLeftPositionSetDataiCallback(void *inRefcon,
    int SwitchStartLeftPosition);

int SwitchStartBothPositionGetDataiCallback(void *inRefcon);
void SwitchStartBothPositionSetDataiCallback(void *inRefcon,
    int SwitchStartBothPosition);

int SwitchStartStartPositionGetDataiCallback(void *inRefcon);
void SwitchStartStartPositionSetDataiCallback(void *inRefcon,
    int SwitchStartStartPosition);

int SwitchBatPositionGetDataiCallback(void *inRefcon);
void SwitchBatPositionSetDataiCallback(void *inRefcon, int SwitchBatPosition);

int SwitchAltPositionGetDataiCallback(void *inRefcon);
void SwitchAltPositionSetDataiCallback(void *inRefcon, int SwitchAltPosition);

int SwitchAvPositionGetDataiCallback(void *inRefcon);
void SwitchAvPositionSetDataiCallback(void *inRefcon, int SwitchAvPosition);

int SwitchFuelPositionGetDataiCallback(void *inRefcon);
void SwitchFuelPositionSetDataiCallback(void *inRefcon,
    int SwitchFuelPosition);

int SwitchDicePositionGetDataiCallback(void *inRefcon);
void SwitchDicePositionSetDataiCallback(void *inRefcon,
    int SwitchDicePosition);

int SwitchPitotPositionGetDataiCallback(void *inRefcon);
void SwitchPitotPositionSetDataiCallback(void *inRefcon,
    int SwitchPitotPosition);

int SwitchGearUpPositionGetDataiCallback(void *inRefcon);
void SwitchGearUpPositionSetDataiCallback(void *inRefcon,
    int SwitchGearUpPosition);

int SwitchGearDnPositionGetDataiCallback(void *inRefcon);
void SwitchGearDnPositionSetDataiCallback(void *inRefcon,
    int SwitchGearDnPosition);

int SwitchCowlPositionGetDataiCallback(void *inRefcon);
void SwitchCowPositionSetDataiCallback(void *inRefcon, int SwitchCowPosition);

int SwitchPanelPositionGetDataiCallback(void *inRefcon);
void SwitchPanelPositionSetDataiCallback(void *inRefcon,
    int SwitchPanelPosition);

int SwitchBeaconPositionGetDataiCallback(void *inRefcon);
void SwitchBeaconPositionSetDataiCallback(void *inRefcon,
    int SwitchBeaconPosition);

int SwitchNavPositionGetDataiCallback(void *inRefcon);
void SwitchNavPositionSetDataiCallback(void *inRefcon, int SwitchNavPosition);

int SwitchStrobePositionGetDataiCallback(void *inRefcon);
void SwitchStrobePositionSetDataiCallback(void *inRefcon,
    int SwitchStrobePosition);

int SwitchTaxiPositionGetDataiCallback(void *inRefcon);
void SwitchTaxiPositionSetDataiCallback(void *inRefcon,
    int SwitchTaxiPosition);

int SwitchLandingPositionGetDataiCallback(void *inRefcon);
void SwitchLandingPositionSetDataiCallback(void *inRefcon,
    int SwitchLandingPosition);



float mag_off_switch_dataf_on_value,
    mag_off_switch_dataf_off_value;
float mag_off2_switch_dataf_on_value,
    mag_off2_switch_dataf_off_value;
float mag_off3_switch_dataf_on_value,
    mag_off3_switch_dataf_off_value;
float mag_off4_switch_dataf_on_value,
    mag_off4_switch_dataf_off_value;
float mag_off5_switch_dataf_on_value,
    mag_off5_switch_dataf_off_value;
float mag_off6_switch_dataf_on_value,
    mag_off6_switch_dataf_off_value;
float mag_off7_switch_dataf_on_value,
    mag_off7_switch_dataf_off_value;
float mag_off8_switch_dataf_on_value,
    mag_off8_switch_dataf_off_value;
float mag_off9_switch_dataf_on_value,
    mag_off9_switch_dataf_off_value;
float mag_off10_switch_dataf_on_value,
    mag_off10_switch_dataf_off_value;


float mag_right_switch_dataf_on_value,
    mag_right_switch_dataf_off_value;
float mag_right2_switch_dataf_on_value,
    mag_right2_switch_dataf_off_value;
float mag_right3_switch_dataf_on_value,
    mag_right3_switch_dataf_off_value;
float mag_right4_switch_dataf_on_value,
    mag_right4_switch_dataf_off_value;
float mag_right5_switch_dataf_on_value,
    mag_right5_switch_dataf_off_value;
float mag_right6_switch_dataf_on_value,
    mag_right6_switch_dataf_off_value;
float mag_right7_switch_dataf_on_value,
    mag_right7_switch_dataf_off_value;
float mag_right8_switch_dataf_on_value,
    mag_right8_switch_dataf_off_value;
float mag_right9_switch_dataf_on_value,
    mag_right9_switch_dataf_off_value;
float mag_right10_switch_dataf_on_value,
    mag_right10_switch_dataf_off_value;

float mag_left_switch_dataf_on_value,
    mag_left_switch_dataf_off_value;
float mag_left2_switch_dataf_on_value,
    mag_left2_switch_dataf_off_value;
float mag_left3_switch_dataf_on_value,
    mag_left3_switch_dataf_off_value;
float mag_left4_switch_dataf_on_value,
    mag_left4_switch_dataf_off_value;
float mag_left5_switch_dataf_on_value,
    mag_left5_switch_dataf_off_value;
float mag_left6_switch_dataf_on_value,
    mag_left6_switch_dataf_off_value;
float mag_left7_switch_dataf_on_value,
    mag_left7_switch_dataf_off_value;
float mag_left8_switch_dataf_on_value,
    mag_left8_switch_dataf_off_value;
float mag_left9_switch_dataf_on_value,
    mag_left9_switch_dataf_off_value;
float mag_left10_switch_dataf_on_value,
    mag_left10_switch_dataf_off_value;

float mag_both_switch_dataf_on_value,
    mag_both_switch_dataf_off_value;
float mag_both2_switch_dataf_on_value,
    mag_both2_switch_dataf_off_value;
float mag_both3_switch_dataf_on_value,
    mag_both3_switch_dataf_off_value;
float mag_both4_switch_dataf_on_value,
    mag_both4_switch_dataf_off_value;
float mag_both5_switch_dataf_on_value,
    mag_both5_switch_dataf_off_value;
float mag_both6_switch_dataf_on_value,
    mag_both6_switch_dataf_off_value;
float mag_both7_switch_dataf_on_value,
    mag_both7_switch_dataf_off_value;
float mag_both8_switch_dataf_on_value,
    mag_both8_switch_dataf_off_value;
float mag_both9_switch_dataf_on_value,
    mag_both9_switch_dataf_off_value;
float mag_both10_switch_dataf_on_value,
    mag_both10_switch_dataf_off_value;


float mag_start_switch_dataf_on_value,
    mag_start_switch_dataf_off_value;
float mag_start2_switch_dataf_on_value,
    mag_start2_switch_dataf_off_value;
float mag_start3_switch_dataf_on_value,
    mag_start3_switch_dataf_off_value;
float mag_start4_switch_dataf_on_value,
    mag_start4_switch_dataf_off_value;
float mag_start5_switch_dataf_on_value,
    mag_start5_switch_dataf_off_value;
float mag_start6_switch_dataf_on_value,
    mag_start6_switch_dataf_off_value;
float mag_start7_switch_dataf_on_value,
    mag_start7_switch_dataf_off_value;
float mag_start8_switch_dataf_on_value,
    mag_start8_switch_dataf_off_value;
float mag_start9_switch_dataf_on_value,
    mag_start9_switch_dataf_off_value;
float mag_start10_switch_dataf_on_value,
    mag_start10_switch_dataf_off_value;

float mag_start_switch_left_dataf_on_value,
    mag_start_switch_left_dataf_off_value;
float mag_start2_switch_left_dataf_on_value,
    mag_start2_switch_left_dataf_off_value;
float mag_start3_switch_left_dataf_on_value,
    mag_start3_switch_left_dataf_off_value;
float mag_start4_switch_left_dataf_on_value,
    mag_start4_switch_left_dataf_off_value;
float mag_start5_switch_left_dataf_on_value,
    mag_start5_switch_left_dataf_off_value;
float mag_start6_switch_left_dataf_on_value,
    mag_start6_switch_left_dataf_off_value;
float mag_start7_switch_left_dataf_on_value,
    mag_start7_switch_left_dataf_off_value;
float mag_start8_switch_left_dataf_on_value,
    mag_start8_switch_left_dataf_off_value;
float mag_start9_switch_left_dataf_on_value,
    mag_start9_switch_left_dataf_off_value;
float mag_start10_switch_left_dataf_on_value,
    mag_start10_switch_left_dataf_off_value;



float bat_master_switch_dataf_on_value,
    bat_master_switch_dataf_off_value;
float bat2_master_switch_dataf_on_value,
    bat2_master_switch_dataf_off_value;
float bat3_master_switch_dataf_on_value,
    bat3_master_switch_dataf_off_value;
float bat4_master_switch_dataf_on_value,
    bat4_master_switch_dataf_off_value;
float bat5_master_switch_dataf_on_value,
    bat5_master_switch_dataf_off_value;
float bat6_master_switch_dataf_on_value,
    bat6_master_switch_dataf_off_value;
float bat7_master_switch_dataf_on_value,
    bat7_master_switch_dataf_off_value;
float bat8_master_switch_dataf_on_value,
    bat8_master_switch_dataf_off_value;

float alt_master_switch_dataf_on_value,
    alt_master_switch_dataf_off_value;
float alt2_master_switch_dataf_on_value,
    alt2_master_switch_dataf_off_value;
float alt3_master_switch_dataf_on_value,
    alt3_master_switch_dataf_off_value;
float alt4_master_switch_dataf_on_value,
    alt4_master_switch_dataf_off_value;
float alt5_master_switch_dataf_on_value,
    alt5_master_switch_dataf_off_value;
float alt6_master_switch_dataf_on_value,
    alt6_master_switch_dataf_off_value;
float alt7_master_switch_dataf_on_value,
    alt7_master_switch_dataf_off_value;
float alt8_master_switch_dataf_on_value,
    alt8_master_switch_dataf_off_value;


float av_master_switch_dataf_on_value,
    av_master_switch_dataf_off_value;
float av2_master_switch_dataf_on_value,
    av2_master_switch_dataf_off_value;
float av3_master_switch_dataf_on_value,
    av3_master_switch_dataf_off_value;
float av4_master_switch_dataf_on_value,
    av4_master_switch_dataf_off_value;
float av5_master_switch_dataf_on_value,
    av5_master_switch_dataf_off_value;
float av6_master_switch_dataf_on_value,
    av6_master_switch_dataf_off_value;
float av7_master_switch_dataf_on_value,
    av7_master_switch_dataf_off_value;
float av8_master_switch_dataf_on_value,
    av8_master_switch_dataf_off_value;

float av9_master_switch_dataf_on_value,
    av9_master_switch_dataf_off_value;
float av10_master_switch_dataf_on_value,
    av10_master_switch_dataf_off_value;
float av11_master_switch_dataf_on_value,
    av11_master_switch_dataf_off_value;
float av12_master_switch_dataf_on_value,
    av12_master_switch_dataf_off_value;
float av13_master_switch_dataf_on_value,
    av13_master_switch_dataf_off_value;
float av14_master_switch_dataf_on_value,
    av14_master_switch_dataf_off_value;
float av15_master_switch_dataf_on_value,
    av15_master_switch_dataf_off_value;
float av16_master_switch_dataf_on_value,
    av16_master_switch_dataf_off_value;

float fuel_pump_switch_dataf_on_value,
    fuel_pump_switch_dataf_off_value;
float fuel_pump2_switch_dataf_on_value,
    fuel_pump2_switch_dataf_off_value;
float fuel_pump3_switch_dataf_on_value,
    fuel_pump3_switch_dataf_off_value;
float fuel_pump4_switch_dataf_on_value,
    fuel_pump4_switch_dataf_off_value;
float fuel_pump5_switch_dataf_on_value,
    fuel_pump5_switch_dataf_off_value;
float fuel_pump6_switch_dataf_on_value,
    fuel_pump6_switch_dataf_off_value;
float fuel_pump7_switch_dataf_on_value,
    fuel_pump7_switch_dataf_off_value;
float fuel_pump8_switch_dataf_on_value,
    fuel_pump8_switch_dataf_off_value;


float deice_switch_dataf_on_value,
    deice_switch_dataf_off_value;
float deice2_switch_dataf_on_value,
    deice2_switch_dataf_off_value;
float deice3_switch_dataf_on_value,
    deice3_switch_dataf_off_value;
float deice4_switch_dataf_on_value,
    deice4_switch_dataf_off_value;
float deice5_switch_dataf_on_value,
    deice5_switch_dataf_off_value;
float deice6_switch_dataf_on_value,
    deice6_switch_dataf_off_value;
float deice7_switch_dataf_on_value,
    deice7_switch_dataf_off_value;
float deice8_switch_dataf_on_value,
    deice8_switch_dataf_off_value;

float pitot_heat_switch_dataf_on_value,
    pitot_heat_switch_dataf_off_value;
float pitot2_heat_switch_dataf_on_value,
    pitot2_heat_switch_dataf_off_value;
float pitot3_heat_switch_dataf_on_value,
    pitot3_heat_switch_dataf_off_value;
float pitot4_heat_switch_dataf_on_value,
    pitot4_heat_switch_dataf_off_value;
float pitot5_heat_switch_dataf_on_value,
    pitot5_heat_switch_dataf_off_value;
float pitot6_heat_switch_dataf_on_value,
    pitot6_heat_switch_dataf_off_value;
float pitot7_heat_switch_dataf_on_value,
    pitot7_heat_switch_dataf_off_value;
float pitot8_heat_switch_dataf_on_value,
    pitot8_heat_switch_dataf_off_value;

float gear_switch_up_dataf_on_value,
    gear_switch_up_dataf_off_value;
float gear_switch_down_dataf_on_value,
    gear_switch_down_dataf_off_value;

float cowl_flaps_dataf_on_value,
    cowl_flaps_dataf_off_value;
float cowl2_flaps_dataf_on_value,
    cowl2_flaps_dataf_off_value;
float cowl3_flaps_dataf_on_value,
    cowl3_flaps_dataf_off_value;
float cowl4_flaps_dataf_on_value,
    cowl4_flaps_dataf_off_value;
float cowl5_flaps_dataf_on_value,
    cowl5_flaps_dataf_off_value;
float cowl6_flaps_dataf_on_value,
    cowl6_flaps_dataf_off_value;
float cowl7_flaps_dataf_on_value,
    cowl7_flaps_dataf_off_value;
float cowl8_flaps_dataf_on_value,
    cowl8_flaps_dataf_off_value;

float panel_lights_switch_dataf_on_value,
    panel_lights_switch_dataf_off_value;
float panel_lights_switch2_dataf_on_value,
    panel_lights_switch2_dataf_off_value;
float panel_lights_switch3_dataf_on_value,
    panel_lights_switch3_dataf_off_value;
float panel_lights_switch4_dataf_on_value,
    panel_lights_switch4_dataf_off_value;
float panel_lights_switch5_dataf_on_value,
    panel_lights_switch5_dataf_off_value;
float panel_lights_switch6_dataf_on_value,
    panel_lights_switch6_dataf_off_value;
float panel_lights_switch7_dataf_on_value,
    panel_lights_switch7_dataf_off_value;
float panel_lights_switch8_dataf_on_value,
    panel_lights_switch8_dataf_off_value;

float beacon_lights_switch_dataf_on_value,
    beacon_lights_switch_dataf_off_value;
float beacon_lights_switch2_dataf_on_value,
    beacon_lights_switch2_dataf_off_value;
float beacon_lights_switch3_dataf_on_value,
    beacon_lights_switch3_dataf_off_value;
float beacon_lights_switch4_dataf_on_value,
    beacon_lights_switch4_dataf_off_value;

float nav_lights_switch_dataf_on_value,
    nav_lights_switch_dataf_off_value;
float nav_lights_switch2_dataf_on_value,
    nav_lights_switch2_dataf_off_value;
float nav_lights_switch3_dataf_on_value,
    nav_lights_switch3_dataf_off_value;
float nav_lights_switch4_dataf_on_value,
    nav_lights_switch4_dataf_off_value;

float strobe_lights_switch_dataf_on_value,
    strobe_lights_switch_dataf_off_value;
float strobe_lights_switch2_dataf_on_value,
    strobe_lights_switch2_dataf_off_value;
float strobe_lights_switch3_dataf_on_value,
    strobe_lights_switch3_dataf_off_value;
float strobe_lights_switch4_dataf_on_value,
    strobe_lights_switch4_dataf_off_value;

float taxi_lights_switch_dataf_on_value,
    taxi_lights_switch_dataf_off_value;
float taxi_lights_switch2_dataf_on_value,
    taxi_lights_switch2_dataf_off_value;
float taxi_lights_switch3_dataf_on_value,
    taxi_lights_switch3_dataf_off_value;
float taxi_lights_switch4_dataf_on_value,
    taxi_lights_switch4_dataf_off_value;

float landing_lights_switch_dataf_on_value,
    landing_lights_switch_dataf_off_value;
float landing_lights_switch2_dataf_on_value,
    landing_lights_switch2_dataf_off_value;
float landing_lights_switch3_dataf_on_value,
    landing_lights_switch3_dataf_off_value;
float landing_lights_switch4_dataf_on_value,
    landing_lights_switch4_dataf_off_value;

string mag_off_switch_on,
    mag_off_switch_off,
    mag_off_switch_data;
string mag_off2_switch_on,
    mag_off2_switch_off,
    mag_off2_switch_data;
string mag_off3_switch_on,
    mag_off3_switch_off,
    mag_off3_switch_data;
string mag_off4_switch_on,
    mag_off4_switch_off,
    mag_off4_switch_data;
string mag_off5_switch_on,
    mag_off5_switch_off,
    mag_off5_switch_data;
string mag_off6_switch_on,
    mag_off6_switch_off,
    mag_off6_switch_data;
string mag_off7_switch_on,
    mag_off7_switch_off,
    mag_off7_switch_data;
string mag_off8_switch_on,
    mag_off8_switch_off,
    mag_off8_switch_data;
string mag_off9_switch_on,
    mag_off9_switch_off,
    mag_off9_switch_data;
string mag_off10_switch_on,
    mag_off10_switch_off,
    mag_off10_switch_data;

string mag_right_switch_on,
    mag_right_switch_off,
    mag_right_switch_data;
string mag_right2_switch_on,
    mag_right2_switch_off,
    mag_right2_switch_data;
string mag_right3_switch_on,
    mag_right3_switch_off,
    mag_right3_switch_data;
string mag_right4_switch_on,
    mag_right4_switch_off,
    mag_right4_switch_data;
string mag_right5_switch_on,
    mag_right5_switch_off,
    mag_right5_switch_data;
string mag_right6_switch_on,
    mag_right6_switch_off,
    mag_right6_switch_data;
string mag_right7_switch_on,
    mag_right7_switch_off,
    mag_right7_switch_data;
string mag_right8_switch_on,
    mag_right8_switch_off,
    mag_right8_switch_data;
string mag_right9_switch_on,
    mag_right9_switch_off,
    mag_right9_switch_data;
string mag_right10_switch_on,
    mag_right10_switch_off,
    mag_right10_switch_data;

string mag_left_switch_on,
    mag_left_switch_off,
    mag_left_switch_data;
string mag_left2_switch_on,
    mag_left2_switch_off,
    mag_left2_switch_data;
string mag_left3_switch_on,
    mag_left3_switch_off,
    mag_left3_switch_data;
string mag_left4_switch_on,
    mag_left4_switch_off,
    mag_left4_switch_data;
string mag_left5_switch_on,
    mag_left5_switch_off,
    mag_left5_switch_data;
string mag_left6_switch_on,
    mag_left6_switch_off,
    mag_left6_switch_data;
string mag_left7_switch_on,
    mag_left7_switch_off,
    mag_left7_switch_data;
string mag_left8_switch_on,
    mag_left8_switch_off,
    mag_left8_switch_data;
string mag_left9_switch_on,
    mag_left9_switch_off,
    mag_left9_switch_data;
string mag_left10_switch_on,
    mag_left10_switch_off,
    mag_left10_switch_data;

string mag_both_switch_on,
    mag_both_switch_off,
    mag_both_switch_data;
string mag_both2_switch_on,
    mag_both2_switch_off,
    mag_both2_switch_data;
string mag_both3_switch_on,
    mag_both3_switch_off,
    mag_both3_switch_data;
string mag_both4_switch_on,
    mag_both4_switch_off,
    mag_both4_switch_data;
string mag_both5_switch_on,
    mag_both5_switch_off,
    mag_both5_switch_data;
string mag_both6_switch_on,
    mag_both6_switch_off,
    mag_both6_switch_data;
string mag_both7_switch_on,
    mag_both7_switch_off,
    mag_both7_switch_data;
string mag_both8_switch_on,
    mag_both8_switch_off,
    mag_both8_switch_data;
string mag_both9_switch_on,
    mag_both9_switch_off,
    mag_both9_switch_data;
string mag_both10_switch_on,
    mag_both10_switch_off,
    mag_both10_switch_data;

string mag_start_switch_on,
    mag_start_switch_off,
    mag_start_switch_data;
string mag_start2_switch_on,
    mag_start2_switch_off,
    mag_start2_switch_data;
string mag_start3_switch_on,
    mag_start3_switch_off,
    mag_start3_switch_data;
string mag_start4_switch_on,
    mag_start4_switch_off,
    mag_start4_switch_data;
string mag_start5_switch_on,
    mag_start5_switch_off,
    mag_start5_switch_data;
string mag_start6_switch_on,
    mag_start6_switch_off,
    mag_start6_switch_data;
string mag_start7_switch_on,
    mag_start7_switch_off,
    mag_start7_switch_data;
string mag_start8_switch_on,
    mag_start8_switch_off,
    mag_start8_switch_data;
string mag_start9_switch_on,
    mag_start9_switch_off,
    mag_start9_switch_data;
string mag_start10_switch_on,
    mag_start10_switch_off,
    mag_start10_switch_data;

string mag_start_switch_left_on,
    mag_start_switch_left_off,
    mag_start_switch_left_data;
string mag_start2_switch_left_on,
    mag_start2_switch_left_off,
    mag_start2_switch_left_data;
string mag_start3_switch_left_on,
    mag_start3_switch_left_off,
    mag_start3_switch_left_data;
string mag_start4_switch_left_on,
    mag_start4_switch_left_off,
    mag_start4_switch_left_data;
string mag_start5_switch_left_on,
    mag_start5_switch_left_off,
    mag_start5_switch_left_data;
string mag_start6_switch_left_on,
    mag_start6_switch_left_off,
    mag_start6_switch_left_data;
string mag_start7_switch_left_on,
    mag_start7_switch_left_off,
    mag_start7_switch_left_data;
string mag_start8_switch_left_on,
    mag_start8_switch_left_off,
    mag_start8_switch_left_data;
string mag_start9_switch_left_on,
    mag_start9_switch_left_off,
    mag_start9_switch_left_data;
string mag_start10_switch_left_on,
    mag_start10_switch_left_off,
    mag_start10_switch_left_data;


string bat_master_switch_on,
    bat_master_switch_off,
    bat_master_switch_data;
string bat2_master_switch_on,
    bat2_master_switch_off,
    bat2_master_switch_data;
string bat3_master_switch_on,
    bat3_master_switch_off,
    bat3_master_switch_data;
string bat4_master_switch_on,
    bat4_master_switch_off,
    bat4_master_switch_data;
string bat5_master_switch_on,
    bat5_master_switch_off,
    bat5_master_switch_data;
string bat6_master_switch_on,
    bat6_master_switch_off,
    bat6_master_switch_data;
string bat7_master_switch_on,
    bat7_master_switch_off,
    bat7_master_switch_data;
string bat8_master_switch_on,
    bat8_master_switch_off,
    bat8_master_switch_data;

string alt_master_switch_on,
    alt_master_switch_off,
    alt_master_switch_data;
string alt2_master_switch_on,
    alt2_master_switch_off,
    alt2_master_switch_data;
string alt3_master_switch_on,
    alt3_master_switch_off,
    alt3_master_switch_data;
string alt4_master_switch_on,
    alt4_master_switch_off,
    alt4_master_switch_data;
string alt5_master_switch_on,
    alt5_master_switch_off,
    alt5_master_switch_data;
string alt6_master_switch_on,
    alt6_master_switch_off,
    alt6_master_switch_data;
string alt7_master_switch_on,
    alt7_master_switch_off,
    alt7_master_switch_data;
string alt8_master_switch_on,
    alt8_master_switch_off,
    alt8_master_switch_data;

string av_master_switch_on,
    av_master_switch_off,
    av_master_switch_data,
    av_master_switch_dataf;
string av2_master_switch_on,
    av2_master_switch_off,
    av2_master_switch_data,
    av2_master_switch_dataf;
string av3_master_switch_on,
    av3_master_switch_off,
    av3_master_switch_data,
    av3_master_switch_dataf;
string av4_master_switch_on,
    av4_master_switch_off,
    av4_master_switch_data,
    av4_master_switch_dataf;
string av5_master_switch_on,
    av5_master_switch_off,
    av5_master_switch_data,
    av5_master_switch_dataf;
string av6_master_switch_on,
    av6_master_switch_off,
    av6_master_switch_data,
    av6_master_switch_dataf;
string av7_master_switch_on,
    av7_master_switch_off,
    av7_master_switch_data,
    av7_master_switch_dataf;
string av8_master_switch_on,
    av8_master_switch_off,
    av8_master_switch_data,
    av8_master_switch_dataf;

string av9_master_switch_on,
    av9_master_switch_off,
    av9_master_switch_data,
    av9_master_switch_dataf;
string av10_master_switch_on,
    av10_master_switch_off,
    av10_master_switch_data,
    av10_master_switch_dataf;
string av11_master_switch_on,
    av11_master_switch_off,
    av11_master_switch_data,
    av11_master_switch_dataf;
string av12_master_switch_on,
    av12_master_switch_off,
    av12_master_switch_data,
    av12_master_switch_dataf;
string av13_master_switch_on,
    av13_master_switch_off,
    av13_master_switch_data,
    av13_master_switch_dataf;
string av14_master_switch_on,
    av14_master_switch_off,
    av14_master_switch_data,
    av14_master_switch_dataf;
string av15_master_switch_on,
    av15_master_switch_off,
    av15_master_switch_data,
    av15_master_switch_dataf;
string av16_master_switch_on,
    av16_master_switch_off,
    av16_master_switch_data,
    av16_master_switch_dataf;


string fuel_pump_switch_on,
    fuel_pump_switch_off,
    fuel_pump_switch_data;
string fuel_pump2_switch_on,
    fuel_pump2_switch_off,
    fuel_pump2_switch_data;
string fuel_pump3_switch_on,
    fuel_pump3_switch_off,
    fuel_pump3_switch_data;
string fuel_pump4_switch_on,
    fuel_pump4_switch_off,
    fuel_pump4_switch_data;
string fuel_pump5_switch_on,
    fuel_pump5_switch_off,
    fuel_pump5_switch_data;
string fuel_pump6_switch_on,
    fuel_pump6_switch_off,
    fuel_pump6_switch_data;
string fuel_pump7_switch_on,
    fuel_pump7_switch_off,
    fuel_pump7_switch_data;
string fuel_pump8_switch_on,
    fuel_pump8_switch_off,
    fuel_pump8_switch_data;


string deice_switch_on,
    deice_switch_off,
    deice_switch_data;
string deice2_switch_on,
    deice2_switch_off,
    deice2_switch_data;
string deice3_switch_on,
    deice3_switch_off,
    deice3_switch_data;
string deice4_switch_on,
    deice4_switch_off,
    deice4_switch_data;
string deice5_switch_on,
    deice5_switch_off,
    deice5_switch_data;
string deice6_switch_on,
    deice6_switch_off,
    deice6_switch_data;
string deice7_switch_on,
    deice7_switch_off,
    deice7_switch_data;
string deice8_switch_on,
    deice8_switch_off,
    deice8_switch_data;

string pitot_heat_switch_on,
    pitot_heat_switch_off,
    pitot_heat_switch_data;
string pitot2_heat_switch_on,
    pitot2_heat_switch_off,
    pitot2_heat_switch_data;
string pitot3_heat_switch_on,
    pitot3_heat_switch_off,
    pitot3_heat_switch_data;
string pitot4_heat_switch_on,
    pitot4_heat_switch_off,
    pitot4_heat_switch_data;
string pitot5_heat_switch_on,
    pitot5_heat_switch_off,
    pitot5_heat_switch_data;
string pitot6_heat_switch_on,
    pitot6_heat_switch_off,
    pitot6_heat_switch_data;
string pitot7_heat_switch_on,
    pitot7_heat_switch_off,
    pitot7_heat_switch_data;
string pitot8_heat_switch_on,
    pitot8_heat_switch_off,
    pitot8_heat_switch_data;

string gear_switch_up_on,
    gear_switch_up_off,
    gear_switch_up_data;
string gear_switch_down_on,
    gear_switch_down_off,
    gear_switch_down_data;

string cowl_flaps_open,
    cowl_flaps_close,
    cowl_flaps_data;
string cowl2_flaps_open,
    cowl2_flaps_close,
    cowl2_flaps_data;
string cowl3_flaps_open,
    cowl3_flaps_close,
    cowl3_flaps_data;
string cowl4_flaps_open,
    cowl4_flaps_close,
    cowl4_flaps_data;
string cowl5_flaps_open,
    cowl5_flaps_close,
    cowl5_flaps_data;
string cowl6_flaps_open,
    cowl6_flaps_close,
    cowl6_flaps_data;
string cowl7_flaps_open,
    cowl7_flaps_close,
    cowl7_flaps_data;
string cowl8_flaps_open,
    cowl8_flaps_close,
    cowl8_flaps_data;


string panel_lights_switch_on,
    panel_lights_switch_off,
    panel_lights_switch_data;
string panel_lights_switch2_on,
    panel_lights_switch2_off,
    panel_lights_switch2_data;
string panel_lights_switch3_on,
    panel_lights_switch3_off,
    panel_lights_switch3_data;
string panel_lights_switch4_on,
    panel_lights_switch4_off,
    panel_lights_switch4_data;
string panel_lights_switch5_on,
    panel_lights_switch5_off,
    panel_lights_switch5_data;
string panel_lights_switch6_on,
    panel_lights_switch6_off,
    panel_lights_switch6_data;
string panel_lights_switch7_on,
    panel_lights_switch7_off,
    panel_lights_switch7_data;
string panel_lights_switch8_on,
    panel_lights_switch8_off,
    panel_lights_switch8_data;

string beacon_lights_switch_on,
    beacon_lights_switch_off,
    beacon_lights_switch_data;
string beacon_lights_switch2_on,
    beacon_lights_switch2_off,
    beacon_lights_switch2_data;
string beacon_lights_switch3_on,
    beacon_lights_switch3_off,
    beacon_lights_switch3_data;
string beacon_lights_switch4_on,
    beacon_lights_switch4_off,
    beacon_lights_switch4_data;

string nav_lights_switch_on,
    nav_lights_switch_off,
    nav_lights_switch_data;
string nav_lights_switch2_on,
    nav_lights_switch2_off,
    nav_lights_switch2_data;
string nav_lights_switch3_on,
    nav_lights_switch3_off,
    nav_lights_switch3_data;
string nav_lights_switch4_on,
    nav_lights_switch4_off,
    nav_lights_switch4_data;

string strobe_lights_switch_on,
    strobe_lights_switch_off,
    strobe_lights_switch_data;
string strobe_lights_switch2_on,
    strobe_lights_switch2_off,
    strobe_lights_switch2_data;
string strobe_lights_switch3_on,
    strobe_lights_switch3_off,
    strobe_lights_switch3_data;
string strobe_lights_switch4_on,
    strobe_lights_switch4_off,
    strobe_lights_switch4_data;

string taxi_lights_switch_on,
    taxi_lights_switch_off,
    taxi_lights_switch_data;
string taxi_lights_switch2_on,
    taxi_lights_switc2h_off,
    taxi_lights_switch2_data;
string taxi_lights_switch3_on,
    taxi_lights_switch3_off,
    taxi_lights_switch3_data;
string taxi_lights_switch4_on,
    taxi_lights_switch4_off,
    taxi_lights_switch4_data;

string landing_lights_switch_on,
    landing_lights_switch_off,
    landing_lights_switch_data;
string landing_lights_switch2_on,
    landing_lights_switch2_off,
    landing_lights_switch2_data;
string landing_lights_switch3_on,
    landing_lights_switch3_off,
    landing_lights_switch3_data;
string landing_lights_switch4_on,
    landing_lights_switch4_off,
    landing_lights_switch4_data;




const char *GearTestStrUp;

static unsigned char blankswitchwbuf[2];
unsigned char switchbuf[4],
    switchwbuf[2];
float LandingGearDeployRatio[10];


hid_device *switchhandle;

// ****************** BIP Panel variables *******************************
int bipcnt = 0,
    biptmpcnt = 0,
    bipres,
    biploop[4],
    stopbipcnt;
int bipnum = 0;
int bipwcscmp0 = 0,
    bipwcscmp1 = 1,
    bipwcscmp2 = 2;
unsigned char bipwbuf[4][10];

#define MAX_STR 255
wchar_t bip_serial_string[4][MAX_STR];
int bip_serial_number[4];

hid_device *biphandle[4];


// ****************** TPM Panel variables *******************************
int tpmcnt = 0,
    tpmres;
unsigned char tpmbuf[4];
hid_device *tpmhandle;

static int TpmPanelCountData = 0;

int TpmPanelCountGetDataiCallback(void *inRefcon);
void TpmPanelCountSetDataiCallback(void *inRefcon, int TpmPanelCount);


// ****************** Saitek Panels variables *******************************
void XsaitekpanelsMenuHandler(void *, void *);
void WriteCSVTableToDisk(void);

int XsaitekpanelsMenuItem;
int XsaitekpanelsVersion;
int XsaitekpanelsFnButton;
int XsaitekpanelsLeftStartFnButton;


int BipMenuItem;

int Fps,
    multi_auto_mul;

int wrgXPlaneVersion = 0;
int wrgXPLMVersion = 0;
int wrgHostID = 0;

int dre_enable = 0;

int readiniloop = 0;


void process_radio_panel();
void process_radio1_register_xsaitekpanels_datareference();
void process_radio1_unregister_xsaitekpanels_datareference();
void process_radio2_register_xsaitekpanels_datareference();
void process_radio2_unregister_xsaitekpanels_datareference();
void process_radio3_register_xsaitekpanels_datareference();
void process_radio3_unregister_xsaitekpanels_datareference();
void process_radio_find_xplane_commands();
void process_radio_find_xplane_datareference();

void process_switch_panel();
void process_switch_register_xsaitekpanels_datareference();
void process_switch_unregister_xsaitekpanels_datareference();
void process_switch_find_xplane_commands();
void process_switch_find_xplane_datareference();
void process_bip_panel();
void process_pref_file();
void process_read_ini_file();


// ********************* MyPanelsFlightLoopCallback **************************
float MyPanelsFlightLoopCallback(float inElapsedSinceLastCall,
    float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon);

float MyPanelsDeferredInitNewAircraftFLCB(float inElapsedSinceLastCall,
    float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon);


float XsaitekpanelsCustomDatarefLoopCB(float elapsedMe, float elapsedSim,
    int counter, void *refcon);


int XpanelsFnButtonCommandHandler(XPLMCommandRef inCommand,     //  custom command handler
    XPLMCommandPhase inPhase, void *inRefcon);

int XpanelsLeftStartFnButtonCommandHandler(XPLMCommandRef inCommand,    //  custom command handler
    XPLMCommandPhase inPhase, void *inRefcon);

void WriteCSVTableToDisk(void);

bool ReadConfigFile(std::string PlaneICAO);
// ******************Plugin Calls ******************
PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc)
{

    int ConfigSubMenuItem;
    int BipSubMenuItem,
        Bip2SubMenuItem,
        Bip3SubMenuItem;
//    int RadioSubMenuItem;
//    int SwitchSubMenuItem;
    int XsaitekpanelsSharedRetVal;

    XPLMGetVersions(&wrgXPlaneVersion, &wrgXPLMVersion, &wrgHostID);

    printf("gXPlaneVersion = %d gXPLMVersion = %d gHostID = %d\n",
        wrgXPlaneVersion, wrgXPLMVersion, wrgHostID);

    XsaitekpanelsVersion = PLUGIN_VERSION_NUMBER;

    XPLMDebugString("Xsaitekpanels: ver " PLUGIN_VERSION "\n");

    /* First set up our plugin info. */
    strcpy(outName, "Xsaitekpanels ver " PLUGIN_VERSION);
    strcpy(outSig, "bgood.xsaitekpanels");
    strcpy(outDesc,
        "A plugin allows use of Saitek Pro Flight Panels on all platforms using hidapi");


    XpanelsFnButtonCommand =
        XPLMCreateCommand("bgood/xsaitekpanels/x_panels_fn_button",
        "Xpanels Fn Button");
    XpanelsLeftStartFnButtonCommand =
        XPLMCreateCommand("bgood/xsaitekpanels/left_start_fn_button",
        "Xpanels Left Start Fn Button");



// ************* Open any Radio that is connected *****************

    struct hid_device_info *rad_devs,
    *rad_cur_dev;

    rad_devs = hid_enumerate(0x6a3, 0x0d05);
    rad_cur_dev = rad_devs;
    for (rad_cur_dev = rad_devs; rad_cur_dev != NULL;
        rad_cur_dev = rad_cur_dev->next) {
        radiohandle[radcnt] = hid_open_path(rad_cur_dev->path);
        if (radiohandle[radcnt] == NULL) {
            logMsg("Error opening radio path %s: %s\n", rad_cur_dev->path,
                strerror(errno));
            continue;
        }
        hid_set_nonblocking(radiohandle[radcnt], 1);
        radiores =
            hid_read(radiohandle[radcnt], radiobuf[radcnt],
            sizeof(radiobuf[radcnt]));
        radiowbuf[0][1] = 1, radiowbuf[1][1] = 2, radiowbuf[2][1] = 3;
        radiowbuf[0][11] = 1, radiowbuf[1][11] = 2, radiowbuf[2][11] = 3;
        hid_send_feature_report(radiohandle[radcnt], radiowbuf[radcnt], 23);
        radcnt++;
    }
    hid_free_enumeration(rad_devs);

// *** Find Connected Multi Panel *****

    open_all_multipanels();

// *** Find Connected Switch Panel *****

    struct hid_device_info *switch_devs,
    *switch_cur_dev;

    switch_devs = hid_enumerate(0x6a3, 0x0d67);
    switch_cur_dev = switch_devs;
    while (switch_cur_dev) {
        switchhandle = hid_open_path(switch_cur_dev->path);
        hid_set_nonblocking(switchhandle, 1);
        switchres = hid_read(switchhandle, switchbuf, sizeof(switchbuf));
        hid_send_feature_report(switchhandle, switchwbuf, 2);
        switchcnt++;
        switch_cur_dev = switch_cur_dev->next;
    }
    hid_free_enumeration(switch_devs);


    // *** Find Connected BIP Panel *****

    struct hid_device_info *bip_devs,
    *bip_cur_dev;

    bip_devs = hid_enumerate(0x6a3, 0xb4e);
    bip_cur_dev = bip_devs;
    char buf[256];
    int bip_result01,
        bip_result10;
    int bip_result02,
        bip_result20;
    int bip_result12,
        bip_result21;

    // find serial numbers of all BIP's connected
    while (bip_cur_dev) {
        biphandle[biptmpcnt] = hid_open_path(bip_cur_dev->path);
        hid_get_serial_number_string(biphandle[biptmpcnt],
            bip_serial_string[biptmpcnt], MAX_STR);
        sprintf(buf,
            "Xsaitekpanels: biptmpcnt = %d  Serial Number String: %ls\n",
            biptmpcnt, bip_serial_string[biptmpcnt]);
        XPLMDebugString(buf);
        hid_close(biphandle[biptmpcnt]);
        biptmpcnt++;
        bip_cur_dev = bip_cur_dev->next;
    }

    hid_free_enumeration(bip_devs);

    if (biptmpcnt == 3) {

        bip_result01 = wcscmp(bip_serial_string[0], bip_serial_string[1]);
        bip_result10 = wcscmp(bip_serial_string[1], bip_serial_string[0]);
        bip_result02 = wcscmp(bip_serial_string[0], bip_serial_string[2]);
        bip_result20 = wcscmp(bip_serial_string[2], bip_serial_string[0]);
        bip_result12 = wcscmp(bip_serial_string[1], bip_serial_string[2]);
        bip_result21 = wcscmp(bip_serial_string[2], bip_serial_string[1]);

        sprintf(buf,
            "Xsaitekpanels: bip_serial_string[0] = %ls  bip_serial_string[1] = %ls bip_serial_string[2] = %ls\n",
            bip_serial_string[0], bip_serial_string[1], bip_serial_string[2]);
        XPLMDebugString(buf);

        sprintf(buf,
            "Xsaitekpanels: bip_result01 = %d  bip_result02 = %d bip_result12 = %d\n",
            bip_result01, bip_result02, bip_result12);
        XPLMDebugString(buf);

        sprintf(buf,
            "Xsaitekpanels: bip_result10 = %d  bip_result20 = %d bip_result21 = %d\n",
            bip_result10, bip_result20, bip_result21);
        XPLMDebugString(buf);

        // Need to find a way to sort the serial numbers and put the biphandle in order

        if (bip_result01 > 0) {
            if (bip_result02 > 0) {
                if (bip_result12 > 0) {
                    // This is completed and checked
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[2], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[1], 10);
                    bipwcscmp2 = 2;

                } else if (bip_result12 < 0) {
                    // This is completed and checked
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[1], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[2], 10);
                    bipwcscmp2 = 2;

                }

            } else if (bip_result02 < 0) {
                if (bip_result12 > 0) {
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[1], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[2], 10);
                    bipwcscmp2 = 2;

                } else if (bip_result12 < 0) {
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[1], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[2], 10);
                    bipwcscmp2 = 2;

                }

            }

        } else if (bip_result01 < 0) {
            if (bip_result02 > 0) {
                if (bip_result12 > 0) {
                    // This is completed and checked
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[1], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[2], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[0], 10);
                    bipwcscmp2 = 2;

                } else if (bip_result12 < 0) {
                    // This is completed and checked
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[2], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[1], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[0], 10);
                    bipwcscmp2 = 2;


                }

            } else if (bip_result02 < 0) {
                if (bip_result12 > 0) {
                    // This is completed and checked
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[1], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[0], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[2], 10);
                    bipwcscmp2 = 2;

                } else if (bip_result12 < 0) {
                    // This is completed and checked
                    biphandle[0] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[2]);
                    bipwbuf[2][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[2][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[0], bipwbuf[2], 10);
                    bipwcscmp0 = 0;

                    biphandle[1] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
                    bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[0][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[1], bipwbuf[0], 10);
                    bipwcscmp1 = 1;

                    biphandle[2] =
                        hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
                    bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
                    bipwbuf[1][1] = 100;        // Set brightness to 100%
                    bipres =
                        hid_send_feature_report(biphandle[2], bipwbuf[1], 10);
                    bipwcscmp2 = 2;

                }

            }

        }




    } else if (biptmpcnt == 2) {

        bip_result01 = wcscmp(bip_serial_string[0], bip_serial_string[1]);
        if (bip_result01 > 0) {
            //sprintf(buf, "(result > 0) %ls > %ls\n", wstr[0], wstr[1]);
            //XPLMDebugString(buf);
            biphandle[0] = hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
            bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
            bipwbuf[0][1] = 100;        // Set brightness to 100%
            bipres = hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
            bipwcscmp0 = 0;

            biphandle[1] = hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
            bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
            bipwbuf[1][1] = 100;        // Set brightness to 100%
            bipres = hid_send_feature_report(biphandle[1], bipwbuf[1], 10);
            bipwcscmp1 = 1;

        } else if (bip_result01 < 0) {
            //sprintf(buf, "(bip_result < 0) %ls < %ls\n", wstr[0], wstr[1]);
            //XPLMDebugString(buf);
            biphandle[1] = hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
            bipwbuf[0][0] = 0xb2;       // 0xb2 Report ID for brightness
            bipwbuf[0][1] = 100;        // Set brightness to 100%
            bipres = hid_send_feature_report(biphandle[1], bipwbuf[0], 10);
            bipwcscmp0 = 0;

            biphandle[0] = hid_open(0x6a3, 0xb4e, bip_serial_string[1]);
            bipwbuf[1][0] = 0xb2;       // 0xb2 Report ID for brightness
            bipwbuf[1][1] = 100;        // Set brightness to 100%
            bipres = hid_send_feature_report(biphandle[0], bipwbuf[1], 10);
            bipwcscmp1 = 1;

        }

    } else if (biptmpcnt == 1) {
        biphandle[0] = hid_open(0x6a3, 0xb4e, bip_serial_string[0]);
        bipwbuf[0][0] = 0xb2;   // 0xb2 Report ID for brightness
        bipwbuf[0][1] = 100;    // Set brightness to 100%
        bipres = hid_send_feature_report(biphandle[0], bipwbuf[0], 10);
        bipwcscmp0 = 0;
    }

    bipcnt = biptmpcnt;


    // *** Find Connected TPM Panel *****

    struct hid_device_info *tpm_devs,
    *tpm_cur_dev;

    tpm_devs = hid_enumerate(0x6a3, 0x0b4d);
    tpm_cur_dev = tpm_devs;
    while (tpm_cur_dev) {
        tpmhandle = hid_open_path(tpm_cur_dev->path);
        hid_set_nonblocking(tpmhandle, 1);
        tpmres = hid_read(tpmhandle, tpmbuf, sizeof(tpmbuf));
//          hid_send_feature_report(tpmhandle, switchwbuf, 2);
        tpmcnt++;
        tpm_cur_dev = tpm_cur_dev->next;
    }
    hid_free_enumeration(tpm_devs);


    XsaitekpanelsVersionDataRef =
        XPLMRegisterDataAccessor("bgood/xsaitekpanels/version", xplmType_Int,
        1, XsaitekpanelsVersionGetDataiCallback,
        XsaitekpanelsVersionSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);


    XsaitekpanelsFnButtonDataRef =
        XPLMRegisterDataAccessor("bgood/xsaitekpanels/fnbutton/status",
        xplmType_Int, 1, XsaitekpanelsFnButtonGetDataiCallback,
        XsaitekpanelsFnButtonSetDataiCallback, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    XsaitekpanelsLeftStartFnButtonDataRef =
        XPLMRegisterDataAccessor
        ("bgood/xsaitekpanels/leftstartfnbutton/status", xplmType_Int, 1,
        XsaitekpanelsLeftStartFnButtonGetDataiCallback,
        XsaitekpanelsLeftStartFnButtonSetDataiCallback, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    SwitchPanelCountDataRef =
        XPLMRegisterDataAccessor("bgood/xsaitekpanels/switchpanel/count",
        xplmType_Int, 1, SwitchPanelCountGetDataiCallback,
        SwitchPanelCountSetDataiCallback, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL);

    RadioPanelCountDataRef =
        XPLMRegisterDataAccessor("bgood/xsaitekpanels/radiopanel/count",
        xplmType_Int, 1, RadioPanelCountGetDataiCallback,
        RadioPanelCountSetDataiCallback, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL);

    MultiPanelCountDataRef =
        XPLMRegisterDataAccessor("bgood/xsaitekpanels/multipanel/count",
        xplmType_Int, 1, (int(*)(void *))get_num_multipanels, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    TpmPanelCountDataRef =
        XPLMRegisterDataAccessor("bgood/xsaitekpanels/tpmpanel/count",
        xplmType_Int, 1, TpmPanelCountGetDataiCallback,
        TpmPanelCountSetDataiCallback, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL);

    sprintf(buf,
        "Xsaitekpanels: found %d Switch  %d Radio  %d Multi  %d BIP %d TPM Panels\n",
        switchcnt, radcnt, get_num_multipanels, bipcnt, tpmcnt);
    XPLMDebugString(buf);

    /* Subscribe to shared data.  If no one else has made it, this will
     * cause the SDK to allocate the data. */

    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer1", xplmType_Int,
        XsaitekpanelsInteger1DataChangedCallback, NULL);

    XsaitekpanelsInteger1SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer1");
    XPLMSetDatai(XsaitekpanelsInteger1SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer2", xplmType_Int,
        XsaitekpanelsInteger2DataChangedCallback, NULL);

    XsaitekpanelsInteger2SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer2");
    XPLMSetDatai(XsaitekpanelsInteger2SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer3", xplmType_Int,
        XsaitekpanelsInteger3DataChangedCallback, NULL);

    XsaitekpanelsInteger3SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer3");
    XPLMSetDatai(XsaitekpanelsInteger3SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer4", xplmType_Int,
        XsaitekpanelsInteger4DataChangedCallback, NULL);

    XsaitekpanelsInteger4SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer4");
    XPLMSetDatai(XsaitekpanelsInteger4SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer5", xplmType_Int,
        XsaitekpanelsInteger5DataChangedCallback, NULL);

    XsaitekpanelsInteger5SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer5");
    XPLMSetDatai(XsaitekpanelsInteger5SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer6", xplmType_Int,
        XsaitekpanelsInteger6DataChangedCallback, NULL);

    XsaitekpanelsInteger6SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer6");
    XPLMSetDatai(XsaitekpanelsInteger6SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer7", xplmType_Int,
        XsaitekpanelsInteger7DataChangedCallback, NULL);

    XsaitekpanelsInteger7SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer7");
    XPLMSetDatai(XsaitekpanelsInteger7SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer8", xplmType_Int,
        XsaitekpanelsInteger8DataChangedCallback, NULL);

    XsaitekpanelsInteger8SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer8");
    XPLMSetDatai(XsaitekpanelsInteger8SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer9", xplmType_Int,
        XsaitekpanelsInteger9DataChangedCallback, NULL);

    XsaitekpanelsInteger9SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer9");
    XPLMSetDatai(XsaitekpanelsInteger9SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer10", xplmType_Int,
        XsaitekpanelsInteger10DataChangedCallback, NULL);

    XsaitekpanelsInteger10SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer10");
    XPLMSetDatai(XsaitekpanelsInteger10SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer11", xplmType_Int,
        XsaitekpanelsInteger11DataChangedCallback, NULL);

    XsaitekpanelsInteger11SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer11");
    XPLMSetDatai(XsaitekpanelsInteger11SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer12", xplmType_Int,
        XsaitekpanelsInteger12DataChangedCallback, NULL);

    XsaitekpanelsInteger12SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer12");
    XPLMSetDatai(XsaitekpanelsInteger12SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer13", xplmType_Int,
        XsaitekpanelsInteger13DataChangedCallback, NULL);

    XsaitekpanelsInteger13SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer13");
    XPLMSetDatai(XsaitekpanelsInteger13SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer14", xplmType_Int,
        XsaitekpanelsInteger14DataChangedCallback, NULL);

    XsaitekpanelsInteger14SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer14");
    XPLMSetDatai(XsaitekpanelsInteger14SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer15", xplmType_Int,
        XsaitekpanelsInteger15DataChangedCallback, NULL);

    XsaitekpanelsInteger15SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer15");
    XPLMSetDatai(XsaitekpanelsInteger15SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer16", xplmType_Int,
        XsaitekpanelsInteger16DataChangedCallback, NULL);

    XsaitekpanelsInteger16SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer16");
    XPLMSetDatai(XsaitekpanelsInteger16SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer17", xplmType_Int,
        XsaitekpanelsInteger17DataChangedCallback, NULL);

    XsaitekpanelsInteger17SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer17");
    XPLMSetDatai(XsaitekpanelsInteger17SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer18", xplmType_Int,
        XsaitekpanelsInteger18DataChangedCallback, NULL);

    XsaitekpanelsInteger18SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer18");
    XPLMSetDatai(XsaitekpanelsInteger18SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer19", xplmType_Int,
        XsaitekpanelsInteger19DataChangedCallback, NULL);

    XsaitekpanelsInteger19SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer19");
    XPLMSetDatai(XsaitekpanelsInteger19SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/integer20", xplmType_Int,
        XsaitekpanelsInteger20DataChangedCallback, NULL);

    XsaitekpanelsInteger20SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/integer20");
    XPLMSetDatai(XsaitekpanelsInteger20SharedDataRef, 0);



    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float1", xplmType_Float,
        XsaitekpanelsFloat1DataChangedCallback, NULL);

    XsaitekpanelsFloat1SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float1");
    XPLMSetDataf(XsaitekpanelsFloat1SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float2", xplmType_Float,
        XsaitekpanelsFloat2DataChangedCallback, NULL);

    XsaitekpanelsFloat2SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float2");
    XPLMSetDataf(XsaitekpanelsFloat2SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float3", xplmType_Float,
        XsaitekpanelsFloat3DataChangedCallback, NULL);

    XsaitekpanelsFloat3SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float3");
    XPLMSetDataf(XsaitekpanelsFloat3SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float4", xplmType_Float,
        XsaitekpanelsFloat4DataChangedCallback, NULL);

    XsaitekpanelsFloat4SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float4");
    XPLMSetDataf(XsaitekpanelsFloat4SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float5", xplmType_Float,
        XsaitekpanelsFloat5DataChangedCallback, NULL);

    XsaitekpanelsFloat5SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float5");
    XPLMSetDataf(XsaitekpanelsFloat5SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float6", xplmType_Float,
        XsaitekpanelsFloat6DataChangedCallback, NULL);

    XsaitekpanelsFloat6SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float6");
    XPLMSetDataf(XsaitekpanelsFloat6SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float7", xplmType_Float,
        XsaitekpanelsFloat7DataChangedCallback, NULL);

    XsaitekpanelsFloat7SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float7");
    XPLMSetDataf(XsaitekpanelsFloat7SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float8", xplmType_Float,
        XsaitekpanelsFloat8DataChangedCallback, NULL);

    XsaitekpanelsFloat8SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float8");
    XPLMSetDataf(XsaitekpanelsFloat8SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float9", xplmType_Float,
        XsaitekpanelsFloat9DataChangedCallback, NULL);

    XsaitekpanelsFloat9SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float9");
    XPLMSetDataf(XsaitekpanelsFloat9SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float10", xplmType_Float,
        XsaitekpanelsFloat10DataChangedCallback, NULL);

    XsaitekpanelsFloat10SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float10");
    XPLMSetDataf(XsaitekpanelsFloat10SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float11", xplmType_Float,
        XsaitekpanelsFloat11DataChangedCallback, NULL);

    XsaitekpanelsFloat11SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float11");
    XPLMSetDataf(XsaitekpanelsFloat11SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float12", xplmType_Float,
        XsaitekpanelsFloat12DataChangedCallback, NULL);

    XsaitekpanelsFloat12SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float12");
    XPLMSetDataf(XsaitekpanelsFloat12SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float13", xplmType_Float,
        XsaitekpanelsFloat13DataChangedCallback, NULL);

    XsaitekpanelsFloat13SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float13");
    XPLMSetDataf(XsaitekpanelsFloat13SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float14", xplmType_Float,
        XsaitekpanelsFloat14DataChangedCallback, NULL);

    XsaitekpanelsFloat14SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float14");
    XPLMSetDataf(XsaitekpanelsFloat14SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float15", xplmType_Float,
        XsaitekpanelsFloat15DataChangedCallback, NULL);

    XsaitekpanelsFloat15SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float15");
    XPLMSetDataf(XsaitekpanelsFloat15SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float16", xplmType_Float,
        XsaitekpanelsFloat16DataChangedCallback, NULL);

    XsaitekpanelsFloat16SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float16");
    XPLMSetDataf(XsaitekpanelsFloat16SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float17", xplmType_Float,
        XsaitekpanelsFloat17DataChangedCallback, NULL);

    XsaitekpanelsFloat17SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float17");
    XPLMSetDataf(XsaitekpanelsFloat17SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float18", xplmType_Float,
        XsaitekpanelsFloat18DataChangedCallback, NULL);

    XsaitekpanelsFloat18SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float18");
    XPLMSetDataf(XsaitekpanelsFloat18SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float19", xplmType_Float,
        XsaitekpanelsFloat19DataChangedCallback, NULL);

    XsaitekpanelsFloat19SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float19");
    XPLMSetDataf(XsaitekpanelsFloat19SharedDataRef, 0);


    XsaitekpanelsSharedRetVal =
        XPLMShareData("bgood/xsaitekpanels/sharedata/float20", xplmType_Float,
        XsaitekpanelsFloat20DataChangedCallback, NULL);

    XsaitekpanelsFloat20SharedDataRef =
        XPLMFindDataRef("bgood/xsaitekpanels/sharedata/float20");
    XPLMSetDataf(XsaitekpanelsFloat20SharedDataRef, 0);


    (void) XsaitekpanelsSharedRetVal;



    // * Register our callback for every loop. Positive intervals
    // * are in seconds, negative are the negative of sim frames.  Zero
    // * registers but does not schedule a callback for time.
    XPLMRegisterFlightLoopCallback(MyPanelsFlightLoopCallback,  // * Callback *
        interval,               // * Interval -1 every loop*
        NULL);                  // * refcon not used. *

    XPLMRegisterFlightLoopCallback(MyPanelsDeferredInitNewAircraftFLCB, -1,
        NULL);


    // Register our custom commands
    XPLMRegisterCommandHandler(XpanelsFnButtonCommand,  // in Command name
        XpanelsFnButtonCommandHandler,  // in Handler
        1,                      // Receive input before plugin windows.
        (void *) 0);            // inRefcon.

    XPLMRegisterCommandHandler(XpanelsLeftStartFnButtonCommand, // in Command name
        XpanelsLeftStartFnButtonCommandHandler, // in Handler
        1,                      // Receive input before plugin windows.
        (void *) 0);            // inRefcon.


    AvPwrOn = XPLMFindDataRef("sim/cockpit2/switches/avionics_power_on");
    BatPwrOn = XPLMFindDataRef("sim/cockpit/electrical/battery_on");
    // If you find a switch panel then create
    // datareferences for all of the switch panel switch positions
    if (switchcnt > 0) {
        process_switch_register_xsaitekpanels_datareference();
        process_switch_find_xplane_commands();
        process_switch_find_xplane_datareference();
    }
    // If you find a radio panel then create
    // datareferences for all of the radio panel switch positions
    if (radcnt > 0) {
        process_radio1_register_xsaitekpanels_datareference();
        process_radio_find_xplane_commands();
        process_radio_find_xplane_datareference();

    }
    if (radcnt > 1) {
        process_radio2_register_xsaitekpanels_datareference();
    }

    if (radcnt > 2) {
        process_radio3_register_xsaitekpanels_datareference();
    }

    // Create our menu

    XsaitekpanelsMenuItem = XPLMAppendMenuItem(XPLMFindPluginsMenu(),
        "Xsaitekpanels", NULL, 1);

    XsaitekpanelsMenu = XPLMCreateMenu("Xsaitekpanels",
        XPLMFindPluginsMenu(),
        XsaitekpanelsMenuItem, XsaitekpanelsMenuHandler, (void *) 0);

    ConfigSubMenuItem = XPLMAppendMenuItem(XsaitekpanelsMenu,
        "xsaitekpanels.ini", NULL, 1);

    ConfigMenuId = XPLMCreateMenu("xsaitekpanels.ini",
        XsaitekpanelsMenu,
        ConfigSubMenuItem, XsaitekpanelsMenuHandler, (void *) 1);

    XPLMClearAllMenuItems(ConfigMenuId);
    XPLMAppendMenuItem(ConfigMenuId, "Reload xsaitekpanels.ini",
        (void *) "TRUE", 1);


    if (bipcnt > 0) {

        if (bipcnt > 0) {
            BipSubMenuItem = XPLMAppendMenuItem(XsaitekpanelsMenu,
                "Bip", NULL, 2);


            BipMenuId = XPLMCreateMenu("Bip",
                XsaitekpanelsMenu,
                BipSubMenuItem, XsaitekpanelsMenuHandler, (void *) 2);



            BipWidgetID = XPCreateWidget(XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_width")) - 150, XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_height")), XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_width")) - 10, XPLMGetDatai(XPLMFindDataRef("sim/graphics/view/window_height")) - 10,  // screen coordinates
                1,              // visible
                "BIP is working!",      // description
                1, NULL,        // we want it root
                xpWidgetClass_Caption);
            XPSetWidgetProperty(BipWidgetID, xpProperty_CaptionLit, 0);
        }

        if (bipcnt > 1) {
            Bip2SubMenuItem = XPLMAppendMenuItem(XsaitekpanelsMenu,
                "Bip2", NULL, 3);

            Bip2MenuId = XPLMCreateMenu("Bip2",
                XsaitekpanelsMenu,
                Bip2SubMenuItem, XsaitekpanelsMenuHandler, (void *) 3);
        }

        if (bipcnt > 2) {
            Bip3SubMenuItem = XPLMAppendMenuItem(XsaitekpanelsMenu,
                "Bip3", NULL, 3);

            Bip3MenuId = XPLMCreateMenu("Bip3",
                XsaitekpanelsMenu,
                Bip3SubMenuItem, XsaitekpanelsMenuHandler, (void *) 4);
        }

    }

    return 1;
}

PLUGIN_API void XPluginStop(void)
{

    XPLMDebugString("Xsaitekpanels: XPluginStop has been called \n");

    stopradcnt = radcnt - 1;

    // *** if open blank display and then close that radio panel ****

    if (stopradcnt == 3) {

        blankradiowbuf[3][0] = 0, blankradiowbuf[3][1] =
            15, blankradiowbuf[3][2] = 15;
        blankradiowbuf[3][3] = 15, blankradiowbuf[3][4] =
            15, blankradiowbuf[3][5] = 15;
        blankradiowbuf[3][6] = 15, blankradiowbuf[3][7] =
            15, blankradiowbuf[3][8] = 15;
        blankradiowbuf[3][9] = 15, blankradiowbuf[3][10] =
            15, blankradiowbuf[3][11] = 15;
        blankradiowbuf[3][12] = 15, blankradiowbuf[3][13] =
            15, blankradiowbuf[3][14] = 15;
        blankradiowbuf[3][15] = 15, blankradiowbuf[3][16] =
            15, blankradiowbuf[3][17] = 15;
        blankradiowbuf[3][18] = 15, blankradiowbuf[3][19] =
            15, blankradiowbuf[3][20] = 15;

        radres =
            hid_send_feature_report(radiohandle[stopradcnt],
            blankradiowbuf[stopradcnt], 23);
        hid_close(radiohandle[stopradcnt]);
        stopradcnt--;
    }

    if (stopradcnt == 2) {

        blankradiowbuf[2][0] = 0, blankradiowbuf[2][1] =
            15, blankradiowbuf[2][2] = 15;
        blankradiowbuf[2][3] = 15, blankradiowbuf[2][4] =
            15, blankradiowbuf[2][5] = 15;
        blankradiowbuf[2][6] = 15, blankradiowbuf[2][7] =
            15, blankradiowbuf[2][8] = 15;
        blankradiowbuf[2][9] = 15, blankradiowbuf[2][10] =
            15, blankradiowbuf[2][11] = 15;
        blankradiowbuf[2][12] = 15, blankradiowbuf[2][13] =
            15, blankradiowbuf[2][14] = 15;
        blankradiowbuf[2][15] = 15, blankradiowbuf[2][16] =
            15, blankradiowbuf[2][17] = 15;
        blankradiowbuf[2][18] = 15, blankradiowbuf[2][19] =
            15, blankradiowbuf[2][20] = 15;

        radres =
            hid_send_feature_report(radiohandle[stopradcnt],
            blankradiowbuf[stopradcnt], 23);
        hid_close(radiohandle[stopradcnt]);
        stopradcnt--;
    }

    if (stopradcnt == 1) {

        blankradiowbuf[1][0] = 0, blankradiowbuf[1][1] =
            15, blankradiowbuf[1][2] = 15;
        blankradiowbuf[1][3] = 15, blankradiowbuf[1][4] =
            15, blankradiowbuf[1][5] = 15;
        blankradiowbuf[1][6] = 15, blankradiowbuf[1][7] =
            15, blankradiowbuf[1][8] = 15;
        blankradiowbuf[1][9] = 15, blankradiowbuf[1][10] =
            15, blankradiowbuf[1][11] = 15;
        blankradiowbuf[1][12] = 15, blankradiowbuf[1][13] =
            15, blankradiowbuf[1][14] = 15;
        blankradiowbuf[1][15] = 15, blankradiowbuf[1][16] =
            15, blankradiowbuf[1][17] = 15;
        blankradiowbuf[1][18] = 15, blankradiowbuf[1][19] =
            15, blankradiowbuf[1][20] = 15;

        radres =
            hid_send_feature_report(radiohandle[stopradcnt],
            blankradiowbuf[stopradcnt], 23);
        hid_close(radiohandle[stopradcnt]);
        stopradcnt--;
    }

    if (stopradcnt == 0) {

        blankradiowbuf[0][0] = 0, blankradiowbuf[0][1] =
            15, blankradiowbuf[0][2] = 15;
        blankradiowbuf[0][3] = 15, blankradiowbuf[0][4] =
            15, blankradiowbuf[0][5] = 15;
        blankradiowbuf[0][6] = 15, blankradiowbuf[0][7] =
            15, blankradiowbuf[0][8] = 15;
        blankradiowbuf[0][9] = 15, blankradiowbuf[0][10] =
            15, blankradiowbuf[0][11] = 15;
        blankradiowbuf[0][12] = 15, blankradiowbuf[0][13] =
            15, blankradiowbuf[0][14] = 15;
        blankradiowbuf[0][15] = 15, blankradiowbuf[0][16] =
            15, blankradiowbuf[0][17] = 15;
        blankradiowbuf[0][18] = 15, blankradiowbuf[0][19] =
            15, blankradiowbuf[0][20] = 15;

        radres =
            hid_send_feature_report(radiohandle[stopradcnt],
            blankradiowbuf[stopradcnt], 23);
        hid_close(radiohandle[stopradcnt]);
    }


    // *** if open blank display and then close that multi panel ***
    close_all_multipanels();

// *** if open close that switch panel ***

    if (switchcnt > 0) {

        blankswitchwbuf[0] = 0;
        blankswitchwbuf[1] = 0;
        switchres = hid_send_feature_report(switchhandle, blankswitchwbuf, 2);
        hid_close(switchhandle);
    }
// *** if open close that bip panel ***

    stopbipcnt = bipcnt - 1;


    if (stopbipcnt == 3) {

        bipwbuf[3][0] = 0xb8;   //0xb8 Report ID to display
        bipwbuf[3][1] = 0, bipwbuf[3][2] = 0, bipwbuf[3][3] = 0;
        bipwbuf[3][4] = 0, bipwbuf[3][5] = 0, bipwbuf[3][6] = 0;

        bipres =
            hid_send_feature_report(biphandle[stopbipcnt],
            bipwbuf[stopbipcnt], 10);
        hid_close(biphandle[stopbipcnt]);
        stopbipcnt--;
    }

    if (stopbipcnt == 2) {

        bipwbuf[2][0] = 0xb8;   //0xb8 Report ID to display
        bipwbuf[2][1] = 0, bipwbuf[2][2] = 0, bipwbuf[2][3] = 0;
        bipwbuf[2][4] = 0, bipwbuf[2][5] = 0, bipwbuf[2][6] = 0;

        bipres =
            hid_send_feature_report(biphandle[stopbipcnt],
            bipwbuf[stopbipcnt], 10);
        hid_close(biphandle[stopbipcnt]);
        stopbipcnt--;
    }

    if (stopbipcnt == 1) {

        bipwbuf[1][0] = 0xb8;   //0xb8 Report ID to display
        bipwbuf[1][1] = 0, bipwbuf[1][2] = 0, bipwbuf[1][3] = 0;
        bipwbuf[1][4] = 0, bipwbuf[1][5] = 0, bipwbuf[1][6] = 0;

        bipres =
            hid_send_feature_report(biphandle[stopbipcnt],
            bipwbuf[stopbipcnt], 10);
        hid_close(biphandle[stopbipcnt]);
        stopbipcnt--;
    }

    if (stopbipcnt == 0) {

        bipwbuf[0][0] = 0xb8;   //0xb8 Report ID to display
        bipwbuf[0][1] = 0, bipwbuf[0][2] = 0, bipwbuf[0][3] = 0;
        bipwbuf[0][4] = 0, bipwbuf[0][5] = 0, bipwbuf[0][6] = 0;

        bipres =
            hid_send_feature_report(biphandle[stopbipcnt],
            bipwbuf[stopbipcnt], 10);
        hid_close(biphandle[stopbipcnt]);
        stopbipcnt--;
    }
    // ********** Unregitser the callback on quit. *************
    XPLMUnregisterFlightLoopCallback(MyPanelsFlightLoopCallback, NULL);
    XPLMUnregisterFlightLoopCallback(MyPanelsDeferredInitNewAircraftFLCB,
        NULL);
    XPLMUnregisterFlightLoopCallback(XsaitekpanelsCustomDatarefLoopCB, NULL);
    XPLMUnregisterCommandHandler(XpanelsFnButtonCommand,
        XpanelsFnButtonCommandHandler, 1, NULL);
    XPLMUnregisterCommandHandler(XpanelsLeftStartFnButtonCommand,
        XpanelsLeftStartFnButtonCommandHandler, 1, NULL);
    process_switch_unregister_xsaitekpanels_datareference();
    process_radio1_unregister_xsaitekpanels_datareference();
    process_radio2_unregister_xsaitekpanels_datareference();
    unregister_multipanel_drs();

    XPDestroyWidget(BipWidgetID, 1);
    XPLMDestroyMenu(BipMenuId);
    XPLMDestroyMenu(Bip2MenuId);
    XPLMDestroyMenu(Bip3MenuId);
}

PLUGIN_API void XPluginDisable(void)
{
}

PLUGIN_API int XPluginEnable(void)
{
    return 1;
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFromWho,
    int inMessage, void *inParam)
{
    (void) inFromWho;           // To get rid of warnings on unused variables
    std::string PlaneICAO = "[]";
    char ICAOString[40];

    XPLMGetDatab(XPLMFindDataRef("sim/aircraft/view/acf_ICAO"), ICAOString, 0,
        40);

    PlaneICAO.insert(1, ICAOString);



    if ((inMessage == XPLM_MSG_PLANE_LOADED) & ((intptr_t) inParam == 0)) {
        XPLMRegisterFlightLoopCallback(MyPanelsDeferredInitNewAircraftFLCB,
            -1, NULL);
    }

    if (bipcnt > 0) {

        if ((inMessage == XPLM_MSG_PLANE_LOADED) & ((intptr_t) inParam == 0)) {
            process_bip_panel();
            ReadConfigFile(PlaneICAO);
            if (bipcnt > 1) {
                process_bip_panel();
                ReadConfigFile(PlaneICAO);
            }
        }
        if (inMessage == XPLM_MSG_AIRPORT_LOADED) {
            ReadConfigFile(PlaneICAO);
            if (bipcnt > 1) {
                process_bip_panel();
                ReadConfigFile(PlaneICAO);
            }

        }

    }

}

// Saitek panels data references call backs

int XsaitekpanelsVersionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return XsaitekpanelsVersionData;
}

void XsaitekpanelsVersionSetDataiCallback(void *inRefcon,
    int XsaitekpanelsVersionData2)
{
    (void) inRefcon;
    XsaitekpanelsVersionData = XsaitekpanelsVersionData2;
}


int XsaitekpanelsFnButtonGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return XsaitekpanelsFnButtonData;
}

void XsaitekpanelsFnButtonSetDataiCallback(void *inRefcon,
    int XsaitekpanelsFnButtonData2)
{
    (void) inRefcon;
    XsaitekpanelsFnButtonData = XsaitekpanelsFnButtonData2;
}


int XsaitekpanelsLeftStartFnButtonGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return XsaitekpanelsLeftStartFnButtonData;
}

void XsaitekpanelsLeftStartFnButtonSetDataiCallback(void *inRefcon,
    int XsaitekpanelsLeftStartFnButtonData2)
{
    (void) inRefcon;
    XsaitekpanelsLeftStartFnButtonData = XsaitekpanelsLeftStartFnButtonData2;
}



/*
 * This is the callback for our shared data.  Right now we do not react
 * to our shared data being chagned.
 *
 */
void XsaitekpanelsInteger1DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger2DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger3DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger4DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger5DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger6DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger7DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger8DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger9DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger10DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger11DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger12DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger13DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger14DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger15DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger16DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger17DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger18DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger19DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsInteger20DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}






void XsaitekpanelsFloat1DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat2DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat3DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat4DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat5DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat6DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat7DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat8DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat9DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat10DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat11DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat12DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat13DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat14DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat15DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat16DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat17DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat18DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat19DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}

void XsaitekpanelsFloat20DataChangedCallback(void *inRefcon)
{
    (void) inRefcon;
}


// Switch panel data references call backs

int SwitchPanelCountGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchPanelCountData;
}

void SwitchPanelCountSetDataiCallback(void *inRefcon,
    int SwitchPanelCountData2)
{
    (void) inRefcon;
    SwitchPanelCountData = SwitchPanelCountData2;
}


int SwitchStartOffPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchStartOffOwnedData;
}

void SwitchStartOffPositionSetDataiCallback(void *inRefcon,
    int SwitchStartOffPosition2)
{
    (void) inRefcon;
    SwitchStartOffOwnedData = SwitchStartOffPosition2;
}


int SwitchStartRightPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchStartRightOwnedData;
}

void SwitchStartRightPositionSetDataiCallback(void *inRefcon,
    int SwitchStartRightPosition2)
{
    (void) inRefcon;
    SwitchStartRightOwnedData = SwitchStartRightPosition2;
}


int SwitchStartLeftPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchStartLeftOwnedData;
}

void SwitchStartLeftPositionSetDataiCallback(void *inRefcon,
    int SwitchStartLeftPosition2)
{
    (void) inRefcon;
    SwitchStartLeftOwnedData = SwitchStartLeftPosition2;
}


int SwitchStartBothPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchStartBothOwnedData;
}

void SwitchStartBothPositionSetDataiCallback(void *inRefcon,
    int SwitchStartBothPosition2)
{
    (void) inRefcon;
    SwitchStartBothOwnedData = SwitchStartBothPosition2;
}


int SwitchStartStartPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchStartStartOwnedData;
}

void SwitchStartStartPositionSetDataiCallback(void *inRefcon,
    int SwitchStartStartPosition2)
{
    (void) inRefcon;
    SwitchStartStartOwnedData = SwitchStartStartPosition2;
}


int SwitchBatPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchBatOwnedData;
}

void SwitchBatPositionSetDataiCallback(void *inRefcon, int SwitchBatPosition2)
{
    (void) inRefcon;
    SwitchBatOwnedData = SwitchBatPosition2;
}


int SwitchAltPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchAltOwnedData;
}

void SwitchAltPositionSetDataiCallback(void *inRefcon, int SwitchAltPosition2)
{
    (void) inRefcon;
    SwitchAltOwnedData = SwitchAltPosition2;
}


int SwitchAvPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchAvOwnedData;
}

void SwitchAvPositionSetDataiCallback(void *inRefcon, int SwitchAvPosition2)
{
    (void) inRefcon;
    SwitchAvOwnedData = SwitchAvPosition2;
}


int SwitchFuelPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchFuelOwnedData;
}

void SwitchFuelPositionSetDataiCallback(void *inRefcon,
    int SwitchFuelPosition2)
{
    (void) inRefcon;
    SwitchFuelOwnedData = SwitchFuelPosition2;
}


int SwitchDicePositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchDiceOwnedData;
}

void SwitchDicePositionSetDataiCallback(void *inRefcon,
    int SwitchDicePosition2)
{
    (void) inRefcon;
    SwitchDiceOwnedData = SwitchDicePosition2;
}


int SwitchPitotPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchPitotOwnedData;
}

void SwitchPitotPositionSetDataiCallback(void *inRefcon,
    int SwitchPitotPosition2)
{
    (void) inRefcon;
    SwitchPitotOwnedData = SwitchPitotPosition2;
}


int SwitchGearUpPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchGearUpOwnedData;
}

void SwitchGearUpPositionSetDataiCallback(void *inRefcon,
    int SwitchGearUpPosition2)
{
    (void) inRefcon;
    SwitchGearUpOwnedData = SwitchGearUpPosition2;
}


int SwitchGearDnPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchGearDnOwnedData;
}

void SwitchGearDnPositionSetDataiCallback(void *inRefcon,
    int SwitchGearDnPosition2)
{
    (void) inRefcon;
    SwitchGearDnOwnedData = SwitchGearDnPosition2;
}


int SwitchCowlPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchCowlOwnedData;
}

void SwitchCowlPositionSetDataiCallback(void *inRefcon,
    int SwitchCowlPosition2)
{
    (void) inRefcon;
    SwitchCowlOwnedData = SwitchCowlPosition2;
}


int SwitchPanelPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchPanelOwnedData;
}

void SwitchPanelPositionSetDataiCallback(void *inRefcon,
    int SwitchPanelPosition2)
{
    (void) inRefcon;
    SwitchPanelOwnedData = SwitchPanelPosition2;
}


int SwitchBeaconPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchBeaconOwnedData;
}

void SwitchBeaconPositionSetDataiCallback(void *inRefcon,
    int SwitchBeaconPosition2)
{
    (void) inRefcon;
    SwitchBeaconOwnedData = SwitchBeaconPosition2;
}


int SwitchNavPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchNavOwnedData;
}

void SwitchNavPositionSetDataiCallback(void *inRefcon, int SwitchNavPosition2)
{
    (void) inRefcon;
    SwitchNavOwnedData = SwitchNavPosition2;
}


int SwitchStrobePositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchStrobeOwnedData;
}

void SwitchStrobePositionSetDataiCallback(void *inRefcon,
    int SwitchStrobePosition2)
{
    (void) inRefcon;
    SwitchStrobeOwnedData = SwitchStrobePosition2;
}


int SwitchTaxiPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchTaxiOwnedData;
}

void SwitchTaxiPositionSetDataiCallback(void *inRefcon,
    int SwitchTaxiPosition2)
{
    (void) inRefcon;
    SwitchTaxiOwnedData = SwitchTaxiPosition2;
}


int SwitchLandingPositionGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return SwitchLandingOwnedData;
}

void SwitchLandingPositionSetDataiCallback(void *inRefcon,
    int SwitchLandingPosition2)
{
    (void) inRefcon;
    SwitchLandingOwnedData = SwitchLandingPosition2;
}


// Radio1 upper datareferences callbacks

int RadioPanelCountGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return RadioPanelCountData;
}

void RadioPanelCountSetDataiCallback(void *inRefcon, int RadioPanelCountData2)
{
    (void) inRefcon;
    RadioPanelCountData = RadioPanelCountData2;
}


int Rad1UprCom1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprCom1OwnedData;
}

void Rad1UprCom1StatusSetDataiCallback(void *inRefcon, int Rad1UprCom1Status2)
{
    (void) inRefcon;
    Rad1UprCom1OwnedData = Rad1UprCom1Status2;
}


int Rad1UprCom2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprCom2OwnedData;
}

void Rad1UprCom2StatusSetDataiCallback(void *inRefcon, int Rad1UprCom2Status2)
{
    (void) inRefcon;
    Rad1UprCom2OwnedData = Rad1UprCom2Status2;
}


int Rad1UprNav1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprNav1OwnedData;
}

void Rad1UprNav1StatusSetDataiCallback(void *inRefcon, int Rad1UprNav1Status2)
{
    (void) inRefcon;
    Rad1UprNav1OwnedData = Rad1UprNav1Status2;
}


int Rad1UprNav2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprNav2OwnedData;
}

void Rad1UprNav2StatusSetDataiCallback(void *inRefcon, int Rad1UprNav2Status2)
{
    (void) inRefcon;
    Rad1UprNav2OwnedData = Rad1UprNav2Status2;
}


int Rad1UprAdfStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprAdfOwnedData;
}

void Rad1UprAdfStatusSetDataiCallback(void *inRefcon, int Rad1UprAdfStatus2)
{
    (void) inRefcon;
    Rad1UprAdfOwnedData = Rad1UprAdfStatus2;
}


int Rad1UprDmeStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDmeOwnedData;
}

void Rad1UprDmeStatusSetDataiCallback(void *inRefcon, int Rad1UprDmeStatus2)
{
    (void) inRefcon;
    Rad1UprDmeOwnedData = Rad1UprDmeStatus2;
}


int Rad1UprXpdrStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprXpdrOwnedData;
}

void Rad1UprXpdrStatusSetDataiCallback(void *inRefcon, int Rad1UprXpdrStatus2)
{
    (void) inRefcon;
    Rad1UprXpdrOwnedData = Rad1UprXpdrStatus2;
}





int Rad1UprCorseIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprCorseIncOwnedData;
}

void Rad1UprCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseIncStatus2)
{
    (void) inRefcon;
    Rad1UprCorseIncOwnedData = Rad1UprCorseIncStatus2;
}

int Rad1UprCorseDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprCorseDecOwnedData;
}

void Rad1UprCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseDecStatus2)
{
    (void) inRefcon;
    Rad1UprCorseDecOwnedData = Rad1UprCorseDecStatus2;
}


int Rad1UprFineIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprFineIncOwnedData;
}

void Rad1UprFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineIncStatus2)
{
    (void) inRefcon;
    Rad1UprFineIncOwnedData = Rad1UprFineIncStatus2;
}

int Rad1UprFineDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprFineDecOwnedData;
}

void Rad1UprFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineDecStatus2)
{
    (void) inRefcon;
    Rad1UprFineDecOwnedData = Rad1UprFineDecStatus2;
}





int Rad1UprCorseIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprCorseIncTicksOwnedData;
}

void Rad1UprCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseIncTicksStatus2)
{
    (void) inRefcon;
    Rad1UprCorseIncTicksOwnedData = Rad1UprCorseIncTicksStatus2;
}

int Rad1UprCorseDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprCorseDecTicksOwnedData;
}

void Rad1UprCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprCorseDecTicksStatus2)
{
    (void) inRefcon;
    Rad1UprCorseDecTicksOwnedData = Rad1UprCorseDecTicksStatus2;
}


int Rad1UprFineIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprFineIncTicksOwnedData;
}

void Rad1UprFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineIncTicksStatus2)
{
    (void) inRefcon;
    Rad1UprFineIncTicksOwnedData = Rad1UprFineIncTicksStatus2;
}

int Rad1UprFineDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprFineDecTicksOwnedData;
}

void Rad1UprFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1UprFineDecTicksStatus2)
{
    (void) inRefcon;
    Rad1UprFineDecTicksOwnedData = Rad1UprFineDecTicksStatus2;
}






int Rad1UprActStbyStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprActStbyOwnedData;
}

void Rad1UprActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad1UprActStbyStatus2)
{
    (void) inRefcon;
    Rad1UprActStbyOwnedData = Rad1UprActStbyStatus2;
}



int Rad1UprDigit1ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit1OwnedData;
}

void Rad1UprDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit1Value2)
{
    (void) inRefcon;
    Rad1UprDigit1OwnedData = Rad1UprDigit1Value2;
}


int Rad1UprDigit2ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit2OwnedData;
}

void Rad1UprDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit2Value2)
{
    (void) inRefcon;
    Rad1UprDigit2OwnedData = Rad1UprDigit2Value2;
}

int Rad1UprDigit3ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit3OwnedData;
}

void Rad1UprDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit3Value2)
{
    (void) inRefcon;
    Rad1UprDigit3OwnedData = Rad1UprDigit3Value2;
}


int Rad1UprDigit4ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit4OwnedData;
}

void Rad1UprDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit4Value2)
{
    (void) inRefcon;
    Rad1UprDigit4OwnedData = Rad1UprDigit4Value2;
}


int Rad1UprDigit5ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit5OwnedData;
}

void Rad1UprDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit5Value2)
{
    (void) inRefcon;
    Rad1UprDigit5OwnedData = Rad1UprDigit5Value2;
}


int Rad1UprDigit6ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit6OwnedData;
}

void Rad1UprDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit6Value2)
{
    (void) inRefcon;
    Rad1UprDigit6OwnedData = Rad1UprDigit6Value2;
}


int Rad1UprDigit7ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit7OwnedData;
}

void Rad1UprDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit7Value2)
{
    (void) inRefcon;
    Rad1UprDigit7OwnedData = Rad1UprDigit7Value2;
}


int Rad1UprDigit8ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit8OwnedData;
}

void Rad1UprDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit8Value2)
{
    (void) inRefcon;
    Rad1UprDigit8OwnedData = Rad1UprDigit8Value2;
}


int Rad1UprDigit9ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit9OwnedData;
}

void Rad1UprDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit9Value2)
{
    (void) inRefcon;
    Rad1UprDigit9OwnedData = Rad1UprDigit9Value2;
}


int Rad1UprDigit10ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1UprDigit10OwnedData;
}

void Rad1UprDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad1UprDigit10Value2)
{
    (void) inRefcon;
    Rad1UprDigit10OwnedData = Rad1UprDigit10Value2;
}


int Rad1WriteNowGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1WriteNowOwnedData;
}

void Rad1WriteNowSetDataiCallback(void *inRefcon, int Rad1WriteNow2)
{
    (void) inRefcon;
    Rad1WriteNowOwnedData = Rad1WriteNow2;
}



// Radio1 lower datareferences callbacks

int Rad1LwrCom1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrCom1OwnedData;
}

void Rad1LwrCom1StatusSetDataiCallback(void *inRefcon, int Rad1LwrCom1Status2)
{
    (void) inRefcon;
    Rad1LwrCom1OwnedData = Rad1LwrCom1Status2;
}


int Rad1LwrCom2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrCom2OwnedData;
}

void Rad1LwrCom2StatusSetDataiCallback(void *inRefcon, int Rad1LwrCom2Status2)
{
    (void) inRefcon;

    Rad1LwrCom2OwnedData = Rad1LwrCom2Status2;
}


int Rad1LwrNav1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrNav1OwnedData;
}

void Rad1LwrNav1StatusSetDataiCallback(void *inRefcon, int Rad1LwrNav1Status2)
{
    (void) inRefcon;
    Rad1LwrNav1OwnedData = Rad1LwrNav1Status2;
}


int Rad1LwrNav2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrNav2OwnedData;
}

void Rad1LwrNav2StatusSetDataiCallback(void *inRefcon, int Rad1LwrNav2Status2)
{
    (void) inRefcon;
    Rad1LwrNav2OwnedData = Rad1LwrNav2Status2;
}


int Rad1LwrAdfStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrAdfOwnedData;
}

void Rad1LwrAdfStatusSetDataiCallback(void *inRefcon, int Rad1LwrAdfStatus2)
{
    (void) inRefcon;
    Rad1LwrAdfOwnedData = Rad1LwrAdfStatus2;
}


int Rad1LwrDmeStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDmeOwnedData;
}

void Rad1LwrDmeStatusSetDataiCallback(void *inRefcon, int Rad1LwrDmeStatus2)
{
    (void) inRefcon;
    Rad1LwrDmeOwnedData = Rad1LwrDmeStatus2;
}


int Rad1LwrXpdrStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrXpdrOwnedData;
}

void Rad1LwrXpdrStatusSetDataiCallback(void *inRefcon, int Rad1LwrXpdrStatus2)
{
    (void) inRefcon;
    Rad1LwrXpdrOwnedData = Rad1LwrXpdrStatus2;
}








int Rad1LwrCorseIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrCorseIncOwnedData;
}

void Rad1LwrCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseIncStatus2)
{
    (void) inRefcon;
    Rad1LwrCorseIncOwnedData = Rad1LwrCorseIncStatus2;
}


int Rad1LwrCorseDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrCorseDecOwnedData;
}

void Rad1LwrCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseDecStatus2)
{
    (void) inRefcon;
    Rad1LwrCorseDecOwnedData = Rad1LwrCorseDecStatus2;
}


int Rad1LwrFineIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrFineIncOwnedData;
}

void Rad1LwrFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineIncStatus2)
{
    (void) inRefcon;
    Rad1LwrFineIncOwnedData = Rad1LwrFineIncStatus2;
}


int Rad1LwrFineDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrFineDecOwnedData;
}

void Rad1LwrFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineDecStatus2)
{
    (void) inRefcon;
    Rad1LwrFineDecOwnedData = Rad1LwrFineDecStatus2;
}









int Rad1LwrCorseIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrCorseIncTicksOwnedData;
}

void Rad1LwrCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseIncTicksStatus2)
{
    (void) inRefcon;
    Rad1LwrCorseIncTicksOwnedData = Rad1LwrCorseIncTicksStatus2;
}


int Rad1LwrCorseDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrCorseDecTicksOwnedData;
}

void Rad1LwrCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrCorseDecTicksStatus2)
{
    (void) inRefcon;
    Rad1LwrCorseDecTicksOwnedData = Rad1LwrCorseDecTicksStatus2;
}


int Rad1LwrFineIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrFineIncTicksOwnedData;
}

void Rad1LwrFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineIncTicksStatus2)
{
    (void) inRefcon;
    Rad1LwrFineIncTicksOwnedData = Rad1LwrFineIncTicksStatus2;
}


int Rad1LwrFineDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrFineDecTicksOwnedData;
}

void Rad1LwrFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrFineDecTicksStatus2)
{
    (void) inRefcon;
    Rad1LwrFineDecTicksOwnedData = Rad1LwrFineDecTicksStatus2;
}







int Rad1LwrActStbyStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrActStbyOwnedData;
}

void Rad1LwrActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad1LwrActStbyStatus2)
{
    (void) inRefcon;
    Rad1LwrActStbyOwnedData = Rad1LwrActStbyStatus2;
}



int Rad1LwrDigit1ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit1OwnedData;
}

void Rad1LwrDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit1Value2)
{
    (void) inRefcon;
    Rad1LwrDigit1OwnedData = Rad1LwrDigit1Value2;
}


int Rad1LwrDigit2ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit2OwnedData;
}

void Rad1LwrDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit2Value2)
{
    (void) inRefcon;
    Rad1LwrDigit2OwnedData = Rad1LwrDigit2Value2;
}

int Rad1LwrDigit3ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit3OwnedData;
}

void Rad1LwrDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit3Value2)
{
    (void) inRefcon;
    Rad1LwrDigit3OwnedData = Rad1LwrDigit3Value2;
}


int Rad1LwrDigit4ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit4OwnedData;
}

void Rad1LwrDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit4Value2)
{
    (void) inRefcon;
    Rad1LwrDigit4OwnedData = Rad1LwrDigit4Value2;
}


int Rad1LwrDigit5ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit5OwnedData;
}

void Rad1LwrDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit5Value2)
{
    (void) inRefcon;
    Rad1LwrDigit5OwnedData = Rad1LwrDigit5Value2;
}


int Rad1LwrDigit6ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit6OwnedData;
}

void Rad1LwrDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit6Value2)
{
    (void) inRefcon;
    Rad1LwrDigit6OwnedData = Rad1LwrDigit6Value2;
}


int Rad1LwrDigit7ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit7OwnedData;
}

void Rad1LwrDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit7Value2)
{
    (void) inRefcon;
    Rad1LwrDigit7OwnedData = Rad1LwrDigit7Value2;
}


int Rad1LwrDigit8ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit8OwnedData;
}

void Rad1LwrDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit8Value2)
{
    (void) inRefcon;
    Rad1LwrDigit8OwnedData = Rad1LwrDigit8Value2;
}


int Rad1LwrDigit9ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit9OwnedData;
}

void Rad1LwrDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit9Value2)
{
    (void) inRefcon;
    Rad1LwrDigit9OwnedData = Rad1LwrDigit9Value2;
}


int Rad1LwrDigit10ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad1LwrDigit10OwnedData;
}

void Rad1LwrDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad1LwrDigit10Value2)
{
    (void) inRefcon;
    Rad1LwrDigit10OwnedData = Rad1LwrDigit10Value2;
}



// Radio2 upper datareferences callbacks

int Rad2UprCom1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprCom1OwnedData;
}

void Rad2UprCom1StatusSetDataiCallback(void *inRefcon, int Rad2UprCom1Status2)
{
    (void) inRefcon;
    Rad2UprCom1OwnedData = Rad2UprCom1Status2;
}


int Rad2UprCom2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprCom2OwnedData;
}

void Rad2UprCom2StatusSetDataiCallback(void *inRefcon, int Rad2UprCom2Status2)
{
    (void) inRefcon;
    Rad2UprCom2OwnedData = Rad2UprCom2Status2;
}


int Rad2UprNav1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprNav1OwnedData;
}

void Rad2UprNav1StatusSetDataiCallback(void *inRefcon, int Rad2UprNav1Status2)
{
    (void) inRefcon;
    Rad2UprNav1OwnedData = Rad2UprNav1Status2;
}


int Rad2UprNav2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprNav2OwnedData;
}

void Rad2UprNav2StatusSetDataiCallback(void *inRefcon, int Rad2UprNav2Status2)
{
    (void) inRefcon;
    Rad2UprNav2OwnedData = Rad2UprNav2Status2;
}


int Rad2UprAdfStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprAdfOwnedData;
}

void Rad2UprAdfStatusSetDataiCallback(void *inRefcon, int Rad2UprAdfStatus2)
{
    (void) inRefcon;
    Rad2UprAdfOwnedData = Rad2UprAdfStatus2;
}


int Rad2UprDmeStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDmeOwnedData;
}

void Rad2UprDmeStatusSetDataiCallback(void *inRefcon, int Rad2UprDmeStatus2)
{
    (void) inRefcon;
    Rad2UprDmeOwnedData = Rad2UprDmeStatus2;
}


int Rad2UprXpdrStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprXpdrOwnedData;
}

void Rad2UprXpdrStatusSetDataiCallback(void *inRefcon, int Rad2UprXpdrStatus2)
{
    (void) inRefcon;
    Rad2UprXpdrOwnedData = Rad2UprXpdrStatus2;
}








int Rad2UprCorseIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprCorseIncOwnedData;
}

void Rad2UprCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseIncStatus2)
{
    (void) inRefcon;
    Rad2UprCorseIncOwnedData = Rad2UprCorseIncStatus2;
}

int Rad2UprCorseDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprCorseDecOwnedData;
}

void Rad2UprCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseDecStatus2)
{
    (void) inRefcon;
    Rad2UprCorseDecOwnedData = Rad2UprCorseDecStatus2;
}


int Rad2UprFineIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprFineIncOwnedData;
}

void Rad2UprFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineIncStatus2)
{
    (void) inRefcon;
    Rad2UprFineIncOwnedData = Rad2UprFineIncStatus2;
}

int Rad2UprFineDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprFineDecOwnedData;
}

void Rad2UprFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineDecStatus2)
{
    (void) inRefcon;
    Rad2UprFineDecOwnedData = Rad2UprFineDecStatus2;
}






int Rad2UprCorseIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprCorseIncTicksOwnedData;
}

void Rad2UprCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseIncTicksStatus2)
{
    (void) inRefcon;
    Rad2UprCorseIncTicksOwnedData = Rad2UprCorseIncTicksStatus2;
}

int Rad2UprCorseDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprCorseDecTicksOwnedData;
}

void Rad2UprCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprCorseDecTicksStatus2)
{
    (void) inRefcon;
    Rad2UprCorseDecTicksOwnedData = Rad2UprCorseDecTicksStatus2;
}


int Rad2UprFineIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprFineIncTicksOwnedData;
}

void Rad2UprFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineIncTicksStatus2)
{
    (void) inRefcon;
    Rad2UprFineIncTicksOwnedData = Rad2UprFineIncTicksStatus2;
}

int Rad2UprFineDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprFineDecTicksOwnedData;
}

void Rad2UprFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2UprFineDecTicksStatus2)
{
    (void) inRefcon;
    Rad2UprFineDecTicksOwnedData = Rad2UprFineDecTicksStatus2;
}








int Rad2UprActStbyStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprActStbyOwnedData;
}

void Rad2UprActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad2UprActStbyStatus2)
{
    (void) inRefcon;
    Rad2UprActStbyOwnedData = Rad2UprActStbyStatus2;
}




int Rad2UprDigit1ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit1OwnedData;
}

void Rad2UprDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit1Value2)
{
    (void) inRefcon;
    Rad2UprDigit1OwnedData = Rad2UprDigit1Value2;
}


int Rad2UprDigit2ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit2OwnedData;
}

void Rad2UprDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit2Value2)
{
    (void) inRefcon;
    Rad2UprDigit2OwnedData = Rad2UprDigit2Value2;
}

int Rad2UprDigit3ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit3OwnedData;
}

void Rad2UprDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit3Value2)
{
    (void) inRefcon;
    Rad2UprDigit3OwnedData = Rad2UprDigit3Value2;
}


int Rad2UprDigit4ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit4OwnedData;
}

void Rad2UprDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit4Value2)
{
    (void) inRefcon;
    Rad2UprDigit4OwnedData = Rad2UprDigit4Value2;
}


int Rad2UprDigit5ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit5OwnedData;
}

void Rad2UprDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit5Value2)
{
    (void) inRefcon;
    Rad2UprDigit5OwnedData = Rad2UprDigit5Value2;
}


int Rad2UprDigit6ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit6OwnedData;
}

void Rad2UprDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit6Value2)
{
    (void) inRefcon;
    Rad2UprDigit6OwnedData = Rad2UprDigit6Value2;
}


int Rad2UprDigit7ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit7OwnedData;
}

void Rad2UprDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit7Value2)
{
    (void) inRefcon;
    Rad2UprDigit7OwnedData = Rad2UprDigit7Value2;
}


int Rad2UprDigit8ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit8OwnedData;
}

void Rad2UprDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit8Value2)
{
    (void) inRefcon;
    Rad2UprDigit8OwnedData = Rad2UprDigit8Value2;
}


int Rad2UprDigit9ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit9OwnedData;
}

void Rad2UprDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit9Value2)
{
    (void) inRefcon;
    Rad2UprDigit9OwnedData = Rad2UprDigit9Value2;
}


int Rad2UprDigit10ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2UprDigit10OwnedData;
}

void Rad2UprDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad2UprDigit10Value2)
{
    (void) inRefcon;
    Rad2UprDigit10OwnedData = Rad2UprDigit10Value2;
}


int Rad2WriteNowGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2WriteNowOwnedData;
}

void Rad2WriteNowSetDataiCallback(void *inRefcon, int Rad2WriteNow2)
{
    (void) inRefcon;
    Rad2WriteNowOwnedData = Rad2WriteNow2;
}




// Radio2 lower datareferences callbacks

int Rad2LwrCom1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrCom1OwnedData;
}

void Rad2LwrCom1StatusSetDataiCallback(void *inRefcon, int Rad2LwrCom1Status2)
{
    (void) inRefcon;
    Rad2LwrCom1OwnedData = Rad2LwrCom1Status2;
}


int Rad2LwrCom2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrCom2OwnedData;
}

void Rad2LwrCom2StatusSetDataiCallback(void *inRefcon, int Rad2LwrCom2Status2)
{
    (void) inRefcon;
    Rad2LwrCom2OwnedData = Rad2LwrCom2Status2;
}


int Rad2LwrNav1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrNav1OwnedData;
}

void Rad2LwrNav1StatusSetDataiCallback(void *inRefcon, int Rad2LwrNav1Status2)
{
    (void) inRefcon;
    Rad2LwrNav1OwnedData = Rad2LwrNav1Status2;
}


int Rad2LwrNav2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrNav2OwnedData;
}

void Rad2LwrNav2StatusSetDataiCallback(void *inRefcon, int Rad2LwrNav2Status2)
{
    (void) inRefcon;
    Rad2LwrNav2OwnedData = Rad2LwrNav2Status2;
}


int Rad2LwrAdfStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrAdfOwnedData;
}

void Rad2LwrAdfStatusSetDataiCallback(void *inRefcon, int Rad2LwrAdfStatus2)
{
    (void) inRefcon;
    Rad2LwrAdfOwnedData = Rad2LwrAdfStatus2;
}


int Rad2LwrDmeStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDmeOwnedData;
}

void Rad2LwrDmeStatusSetDataiCallback(void *inRefcon, int Rad2LwrDmeStatus2)
{
    (void) inRefcon;
    Rad2LwrDmeOwnedData = Rad2LwrDmeStatus2;
}


int Rad2LwrXpdrStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrXpdrOwnedData;
}

void Rad2LwrXpdrStatusSetDataiCallback(void *inRefcon, int Rad2LwrXpdrStatus2)
{
    (void) inRefcon;
    Rad2LwrXpdrOwnedData = Rad2LwrXpdrStatus2;
}









int Rad2LwrCorseIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrCorseIncOwnedData;
}

void Rad2LwrCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseIncStatus2)
{
    (void) inRefcon;
    Rad2LwrCorseIncOwnedData = Rad2LwrCorseIncStatus2;
}

int Rad2LwrCorseDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrCorseDecOwnedData;
}

void Rad2LwrCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseDecStatus2)
{
    (void) inRefcon;
    Rad2LwrCorseDecOwnedData = Rad2LwrCorseDecStatus2;
}


int Rad2LwrFineIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrFineIncOwnedData;
}

void Rad2LwrFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineIncStatus2)
{
    (void) inRefcon;
    Rad2LwrFineIncOwnedData = Rad2LwrFineIncStatus2;
}

int Rad2LwrFineDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrFineDecOwnedData;
}

void Rad2LwrFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineDecStatus2)
{
    (void) inRefcon;
    Rad2LwrFineDecOwnedData = Rad2LwrFineDecStatus2;
}






int Rad2LwrCorseIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrCorseIncTicksOwnedData;
}

void Rad2LwrCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseIncTicksStatus2)
{
    (void) inRefcon;
    Rad2LwrCorseIncTicksOwnedData = Rad2LwrCorseIncTicksStatus2;
}

int Rad2LwrCorseDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrCorseDecTicksOwnedData;
}

void Rad2LwrCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrCorseDecTicksStatus2)
{
    (void) inRefcon;
    Rad2LwrCorseDecTicksOwnedData = Rad2LwrCorseDecTicksStatus2;
}


int Rad2LwrFineIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrFineIncTicksOwnedData;
}

void Rad2LwrFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineIncTicksStatus2)
{
    (void) inRefcon;
    Rad2LwrFineIncTicksOwnedData = Rad2LwrFineIncTicksStatus2;
}

int Rad2LwrFineDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrFineDecTicksOwnedData;
}

void Rad2LwrFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrFineDecTicksStatus2)
{
    (void) inRefcon;
    Rad2LwrFineDecTicksOwnedData = Rad2LwrFineDecTicksStatus2;
}





int Rad2LwrActStbyStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrActStbyOwnedData;
}

void Rad2LwrActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad2LwrActStbyStatus2)
{
    (void) inRefcon;
    Rad2LwrActStbyOwnedData = Rad2LwrActStbyStatus2;
}



int Rad2LwrDigit1ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit1OwnedData;
}

void Rad2LwrDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit1Value2)
{
    (void) inRefcon;
    Rad2LwrDigit1OwnedData = Rad2LwrDigit1Value2;
}


int Rad2LwrDigit2ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit2OwnedData;
}

void Rad2LwrDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit2Value2)
{
    (void) inRefcon;
    Rad2LwrDigit2OwnedData = Rad2LwrDigit2Value2;
}

int Rad2LwrDigit3ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit3OwnedData;
}

void Rad2LwrDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit3Value2)
{
    (void) inRefcon;
    Rad2LwrDigit3OwnedData = Rad2LwrDigit3Value2;
}


int Rad2LwrDigit4ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit4OwnedData;
}

void Rad2LwrDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit4Value2)
{
    (void) inRefcon;
    Rad2LwrDigit4OwnedData = Rad2LwrDigit4Value2;
}


int Rad2LwrDigit5ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit5OwnedData;
}

void Rad2LwrDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit5Value2)
{
    (void) inRefcon;
    Rad2LwrDigit5OwnedData = Rad2LwrDigit5Value2;
}


int Rad2LwrDigit6ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit6OwnedData;
}

void Rad2LwrDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit6Value2)
{
    (void) inRefcon;
    Rad2LwrDigit6OwnedData = Rad2LwrDigit6Value2;
}


int Rad2LwrDigit7ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit7OwnedData;
}

void Rad2LwrDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit7Value2)
{
    (void) inRefcon;
    Rad2LwrDigit7OwnedData = Rad2LwrDigit7Value2;
}


int Rad2LwrDigit8ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit8OwnedData;
}

void Rad2LwrDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit8Value2)
{
    (void) inRefcon;
    Rad2LwrDigit8OwnedData = Rad2LwrDigit8Value2;
}


int Rad2LwrDigit9ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit9OwnedData;
}

void Rad2LwrDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit9Value2)
{
    (void) inRefcon;
    Rad2LwrDigit9OwnedData = Rad2LwrDigit9Value2;
}


int Rad2LwrDigit10ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad2LwrDigit10OwnedData;
}

void Rad2LwrDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad2LwrDigit10Value2)
{
    (void) inRefcon;
    Rad2LwrDigit10OwnedData = Rad2LwrDigit10Value2;
}



// Radio3 upper datareferences callbacks

int Rad3UprCom1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprCom1OwnedData;
}

void Rad3UprCom1StatusSetDataiCallback(void *inRefcon, int Rad3UprCom1Status2)
{
    (void) inRefcon;
    Rad3UprCom1OwnedData = Rad3UprCom1Status2;
}


int Rad3UprCom2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprCom2OwnedData;
}

void Rad3UprCom2StatusSetDataiCallback(void *inRefcon, int Rad3UprCom2Status2)
{
    (void) inRefcon;
    Rad3UprCom2OwnedData = Rad3UprCom2Status2;
}


int Rad3UprNav1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprNav1OwnedData;
}

void Rad3UprNav1StatusSetDataiCallback(void *inRefcon, int Rad3UprNav1Status2)
{
    (void) inRefcon;
    Rad3UprNav1OwnedData = Rad3UprNav1Status2;
}


int Rad3UprNav2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprNav2OwnedData;
}

void Rad3UprNav2StatusSetDataiCallback(void *inRefcon, int Rad3UprNav2Status2)
{
    (void) inRefcon;
    Rad3UprNav2OwnedData = Rad3UprNav2Status2;
}


int Rad3UprAdfStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprAdfOwnedData;
}

void Rad3UprAdfStatusSetDataiCallback(void *inRefcon, int Rad3UprAdfStatus2)
{
    (void) inRefcon;
    Rad3UprAdfOwnedData = Rad3UprAdfStatus2;
}


int Rad3UprDmeStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDmeOwnedData;
}

void Rad3UprDmeStatusSetDataiCallback(void *inRefcon, int Rad3UprDmeStatus2)
{
    (void) inRefcon;
    Rad3UprDmeOwnedData = Rad3UprDmeStatus2;
}


int Rad3UprXpdrStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprXpdrOwnedData;
}

void Rad3UprXpdrStatusSetDataiCallback(void *inRefcon, int Rad3UprXpdrStatus2)
{
    (void) inRefcon;
    Rad3UprXpdrOwnedData = Rad3UprXpdrStatus2;
}










int Rad3UprCorseIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprCorseIncOwnedData;
}

void Rad3UprCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseIncStatus2)
{
    (void) inRefcon;
    Rad3UprCorseIncOwnedData = Rad3UprCorseIncStatus2;
}

int Rad3UprCorseDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprCorseDecOwnedData;
}

void Rad3UprCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseDecStatus2)
{
    (void) inRefcon;
    Rad3UprCorseDecOwnedData = Rad3UprCorseDecStatus2;
}


int Rad3UprFineIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprFineIncOwnedData;
}

void Rad3UprFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineIncStatus2)
{
    (void) inRefcon;
    Rad3UprFineIncOwnedData = Rad3UprFineIncStatus2;
}

int Rad3UprFineDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprFineDecOwnedData;
}

void Rad3UprFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineDecStatus2)
{
    (void) inRefcon;
    Rad3UprFineDecOwnedData = Rad3UprFineDecStatus2;
}





int Rad3UprCorseIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprCorseIncTicksOwnedData;
}

void Rad3UprCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseIncTicksStatus2)
{
    (void) inRefcon;
    Rad3UprCorseIncTicksOwnedData = Rad3UprCorseIncTicksStatus2;
}

int Rad3UprCorseDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprCorseDecTicksOwnedData;
}

void Rad3UprCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprCorseDecTicksStatus2)
{
    (void) inRefcon;
    Rad3UprCorseDecTicksOwnedData = Rad3UprCorseDecTicksStatus2;
}


int Rad3UprFineIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprFineIncTicksOwnedData;
}

void Rad3UprFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineIncTicksStatus2)
{
    (void) inRefcon;
    Rad3UprFineIncTicksOwnedData = Rad3UprFineIncTicksStatus2;
}

int Rad3UprFineDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprFineDecTicksOwnedData;
}

void Rad3UprFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3UprFineDecTicksStatus2)
{
    (void) inRefcon;
    Rad3UprFineDecTicksOwnedData = Rad3UprFineDecTicksStatus2;
}







int Rad3UprActStbyStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprActStbyOwnedData;
}

void Rad3UprActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad3UprActStbyStatus2)
{
    (void) inRefcon;
    Rad3UprActStbyOwnedData = Rad3UprActStbyStatus2;
}




int Rad3UprDigit1ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit1OwnedData;
}

void Rad3UprDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit1Value2)
{
    (void) inRefcon;
    Rad3UprDigit1OwnedData = Rad3UprDigit1Value2;
}


int Rad3UprDigit2ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit2OwnedData;
}

void Rad3UprDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit2Value2)
{
    (void) inRefcon;
    Rad3UprDigit2OwnedData = Rad3UprDigit2Value2;
}

int Rad3UprDigit3ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit3OwnedData;
}

void Rad3UprDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit3Value2)
{
    (void) inRefcon;
    Rad3UprDigit3OwnedData = Rad3UprDigit3Value2;
}


int Rad3UprDigit4ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit4OwnedData;
}

void Rad3UprDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit4Value2)
{
    (void) inRefcon;
    Rad3UprDigit4OwnedData = Rad3UprDigit4Value2;
}


int Rad3UprDigit5ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit5OwnedData;
}

void Rad3UprDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit5Value2)
{
    (void) inRefcon;
    Rad3UprDigit5OwnedData = Rad3UprDigit5Value2;
}


int Rad3UprDigit6ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit6OwnedData;
}

void Rad3UprDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit6Value2)
{
    (void) inRefcon;
    Rad3UprDigit6OwnedData = Rad3UprDigit6Value2;
}


int Rad3UprDigit7ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit7OwnedData;
}

void Rad3UprDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit7Value2)
{
    (void) inRefcon;
    Rad3UprDigit7OwnedData = Rad3UprDigit7Value2;
}


int Rad3UprDigit8ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit8OwnedData;
}

void Rad3UprDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit8Value2)
{
    (void) inRefcon;
    Rad3UprDigit8OwnedData = Rad3UprDigit8Value2;
}


int Rad3UprDigit9ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit9OwnedData;
}

void Rad3UprDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit9Value2)
{
    (void) inRefcon;
    Rad3UprDigit9OwnedData = Rad3UprDigit9Value2;
}


int Rad3UprDigit10ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3UprDigit10OwnedData;
}

void Rad3UprDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad3UprDigit10Value2)
{
    (void) inRefcon;
    Rad3UprDigit10OwnedData = Rad3UprDigit10Value2;
}


int Rad3WriteNowGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3WriteNowOwnedData;
}

void Rad3WriteNowSetDataiCallback(void *inRefcon, int Rad3WriteNow2)
{
    (void) inRefcon;
    Rad3WriteNowOwnedData = Rad3WriteNow2;
}


// Radio3 lower datareferences callbacks

int Rad3LwrCom1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrCom1OwnedData;
}

void Rad3LwrCom1StatusSetDataiCallback(void *inRefcon, int Rad3LwrCom1Status2)
{
    (void) inRefcon;
    Rad3LwrCom1OwnedData = Rad3LwrCom1Status2;
}


int Rad3LwrCom2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrCom2OwnedData;
}

void Rad3LwrCom2StatusSetDataiCallback(void *inRefcon, int Rad3LwrCom2Status2)
{
    (void) inRefcon;
    Rad3LwrCom2OwnedData = Rad3LwrCom2Status2;
}


int Rad3LwrNav1StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrNav1OwnedData;
}

void Rad3LwrNav1StatusSetDataiCallback(void *inRefcon, int Rad3LwrNav1Status2)
{
    (void) inRefcon;
    Rad3LwrNav1OwnedData = Rad3LwrNav1Status2;
}


int Rad3LwrNav2StatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrNav2OwnedData;
}

void Rad3LwrNav2StatusSetDataiCallback(void *inRefcon, int Rad3LwrNav2Status2)
{
    (void) inRefcon;
    Rad3LwrNav2OwnedData = Rad3LwrNav2Status2;
}


int Rad3LwrAdfStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrAdfOwnedData;
}

void Rad3LwrAdfStatusSetDataiCallback(void *inRefcon, int Rad3LwrAdfStatus2)
{
    (void) inRefcon;
    Rad3LwrAdfOwnedData = Rad3LwrAdfStatus2;
}


int Rad3LwrDmeStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDmeOwnedData;
}

void Rad3LwrDmeStatusSetDataiCallback(void *inRefcon, int Rad3LwrDmeStatus2)
{
    (void) inRefcon;
    Rad3LwrDmeOwnedData = Rad3LwrDmeStatus2;
}


int Rad3LwrXpdrStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrXpdrOwnedData;
}

void Rad3LwrXpdrStatusSetDataiCallback(void *inRefcon, int Rad3LwrXpdrStatus2)
{
    (void) inRefcon;
    Rad3LwrXpdrOwnedData = Rad3LwrXpdrStatus2;
}








int Rad3LwrCorseIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrCorseIncOwnedData;
}

void Rad3LwrCorseIncStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseIncStatus2)
{
    (void) inRefcon;
    Rad3LwrCorseIncOwnedData = Rad3LwrCorseIncStatus2;
}

int Rad3LwrCorseDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrCorseDecOwnedData;
}

void Rad3LwrCorseDecStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseDecStatus2)
{
    (void) inRefcon;
    Rad3LwrCorseDecOwnedData = Rad3LwrCorseDecStatus2;
}


int Rad3LwrFineIncStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrFineIncOwnedData;
}

void Rad3LwrFineIncStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineIncStatus2)
{
    (void) inRefcon;
    Rad3LwrFineIncOwnedData = Rad3LwrFineIncStatus2;
}

int Rad3LwrFineDecStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrFineDecOwnedData;
}

void Rad3LwrFineDecStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineDecStatus2)
{
    (void) inRefcon;
    Rad3LwrFineDecOwnedData = Rad3LwrFineDecStatus2;
}






int Rad3LwrCorseIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrCorseIncTicksOwnedData;
}

void Rad3LwrCorseIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseIncTicksStatus2)
{
    (void) inRefcon;
    Rad3LwrCorseIncTicksOwnedData = Rad3LwrCorseIncTicksStatus2;
}

int Rad3LwrCorseDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrCorseDecTicksOwnedData;
}

void Rad3LwrCorseDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrCorseDecTicksStatus2)
{
    (void) inRefcon;
    Rad3LwrCorseDecTicksOwnedData = Rad3LwrCorseDecTicksStatus2;
}


int Rad3LwrFineIncTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrFineIncTicksOwnedData;
}

void Rad3LwrFineIncTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineIncTicksStatus2)
{
    (void) inRefcon;
    Rad3LwrFineIncTicksOwnedData = Rad3LwrFineIncTicksStatus2;
}

int Rad3LwrFineDecTicksStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrFineDecTicksOwnedData;
}

void Rad3LwrFineDecTicksStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrFineDecTicksStatus2)
{
    (void) inRefcon;
    Rad3LwrFineDecTicksOwnedData = Rad3LwrFineDecTicksStatus2;
}










int Rad3LwrActStbyStatusGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrActStbyOwnedData;
}

void Rad3LwrActStbyStatusSetDataiCallback(void *inRefcon,
    int Rad3LwrActStbyStatus2)
{
    (void) inRefcon;
    Rad3LwrActStbyOwnedData = Rad3LwrActStbyStatus2;
}




int Rad3LwrDigit1ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit1OwnedData;
}

void Rad3LwrDigit1ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit1Value2)
{
    (void) inRefcon;
    Rad3LwrDigit1OwnedData = Rad3LwrDigit1Value2;
}


int Rad3LwrDigit2ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit2OwnedData;
}

void Rad3LwrDigit2ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit2Value2)
{
    (void) inRefcon;
    Rad3LwrDigit2OwnedData = Rad3LwrDigit2Value2;
}

int Rad3LwrDigit3ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit3OwnedData;
}

void Rad3LwrDigit3ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit3Value2)
{
    (void) inRefcon;
    Rad3LwrDigit3OwnedData = Rad3LwrDigit3Value2;
}


int Rad3LwrDigit4ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit4OwnedData;
}

void Rad3LwrDigit4ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit4Value2)
{
    (void) inRefcon;
    Rad3LwrDigit4OwnedData = Rad3LwrDigit4Value2;
}


int Rad3LwrDigit5ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit5OwnedData;
}

void Rad3LwrDigit5ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit5Value2)
{
    (void) inRefcon;
    Rad3LwrDigit5OwnedData = Rad3LwrDigit5Value2;
}


int Rad3LwrDigit6ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit6OwnedData;
}

void Rad3LwrDigit6ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit6Value2)
{
    (void) inRefcon;
    Rad3LwrDigit6OwnedData = Rad3LwrDigit6Value2;
}


int Rad3LwrDigit7ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit7OwnedData;
}

void Rad3LwrDigit7ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit7Value2)
{
    (void) inRefcon;
    Rad3LwrDigit7OwnedData = Rad3LwrDigit7Value2;
}


int Rad3LwrDigit8ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit8OwnedData;
}

void Rad3LwrDigit8ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit8Value2)
{
    (void) inRefcon;
    Rad3LwrDigit8OwnedData = Rad3LwrDigit8Value2;
}


int Rad3LwrDigit9ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit9OwnedData;
}

void Rad3LwrDigit9ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit9Value2)
{
    (void) inRefcon;
    Rad3LwrDigit9OwnedData = Rad3LwrDigit9Value2;
}


int Rad3LwrDigit10ValueGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return Rad3LwrDigit10OwnedData;
}

void Rad3LwrDigit10ValueSetDataiCallback(void *inRefcon,
    int Rad3LwrDigit10Value2)
{
    (void) inRefcon;
    Rad3LwrDigit10OwnedData = Rad3LwrDigit10Value2;
}


// TPM panel data references call backs


int TpmPanelCountGetDataiCallback(void *inRefcon)
{
    (void) inRefcon;
    return TpmPanelCountData;
}

void TpmPanelCountSetDataiCallback(void *inRefcon, int TpmPanelCountData2)
{
    (void) inRefcon;
    TpmPanelCountData = TpmPanelCountData2;
}





// Menu handler

void XsaitekpanelsMenuHandler(void *inMenuRef, void *inItemRef)
{

    if ((intptr_t) inMenuRef == 1) {
        if (strcmp((char *) inItemRef, "TRUE") == 0) {
            process_read_ini_file();
        }

    }

    if ((intptr_t) inMenuRef == 2) {
        bipnum = 0;
        if (strcmp((char *) inItemRef, "[DEFAULT]") == 0) {
            ReadConfigFile((char *) inItemRef);
        }
        if (strcmp((char *) inItemRef, "<<CSV>>") == 0) {
            WriteCSVTableToDisk();
        }
        if (strcmp((char *) inItemRef, "[BIP_TEST]") == 0) {
            ReadConfigFile((char *) inItemRef);
        }

        else {
            ReadConfigFile((char *) inItemRef);

        }

    }

    if ((intptr_t) inMenuRef == 3) {
        bipnum = 1;
        if (strcmp((char *) inItemRef, "[DEFAULT]") == 0) {

            ReadConfigFile((char *) inItemRef);
        }

        if (strcmp((char *) inItemRef, "<<CSV>>") == 0) {
            WriteCSVTableToDisk();
        }

        if (strcmp((char *) inItemRef, "[BIP_TEST]") == 0) {
            ReadConfigFile((char *) inItemRef);
        }

        else {
            ReadConfigFile((char *) inItemRef);

        }

    }

    if ((intptr_t) inMenuRef == 4) {
        bipnum = 2;
        if (strcmp((char *) inItemRef, "[DEFAULT]") == 0) {

            ReadConfigFile((char *) inItemRef);
        }

        if (strcmp((char *) inItemRef, "<<CSV>>") == 0) {
            WriteCSVTableToDisk();
        }

        if (strcmp((char *) inItemRef, "[BIP_TEST]") == 0) {
            ReadConfigFile((char *) inItemRef);
        }

        else {
            ReadConfigFile((char *) inItemRef);

        }
    }
}


int XpanelsFnButtonCommandHandler(XPLMCommandRef inCommand,
    XPLMCommandPhase inPhase, void *inRefcon)
{
    (void) inCommand;
    (void) inRefcon;
//  If inPhase == 1 the command is executed continuously.
    if (inPhase == 1) {
        xpanelsfnbutton = 1;
    }
    if (inPhase == 2) {
        xpanelsfnbutton = 0;
    }

    return 0;
}

int XpanelsLeftStartFnButtonCommandHandler(XPLMCommandRef inCommand,
    XPLMCommandPhase inPhase, void *inRefcon)
{
    (void) inCommand;
    (void) inRefcon;
//  If inPhase == 1 the command is executed continuously.
    if (inPhase == 1) {
        xpanelsleftstartfnbutton = 1;
    }
    if (inPhase == 2) {
        xpanelsleftstartfnbutton = 0;
    }

    return 0;
}

float XsaitekpanelsCustomDatarefLoopCB(float elapsedMe, float elapsedSim,
    int counter, void *refcon)
{

    // void *Param = NULL;
    (void) elapsedMe;
    (void) elapsedSim;
    (void) counter;
    (void) refcon;


    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/version");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/fnbutton/status");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/leftstartfnbutton/status");

    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer1");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer2");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer3");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer4");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer5");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer6");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer7");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer8");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer9");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer10");

    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer11");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer12");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer13");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer14");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer15");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer16");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer17");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer18");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer19");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/integer20");


    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float1");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float2");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float3");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float4");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float5");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float6");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float7");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float8");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float9");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float10");

    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float11");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float12");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float13");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float14");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float15");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float16");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float17");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float18");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float19");
    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/sharedata/float20");


    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/switchpanel/count");
    if (switchcnt > 0) {
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/startoff/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/startright/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/startleft/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/startboth/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/startstart/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/bat/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/alt/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/av/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/fuel/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/dice/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/pitot/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/gearup/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/geardn/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/cowl/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/panel/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/beacon/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/nav/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/strobe/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/taxi/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/switchpanel/landing/status");
    }


    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/radiopanel/count");

    if (radcnt > 0) {
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprcom1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprcom2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprnav1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprnav2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1upradf/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdme/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprxpdr/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprcorseinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprcorsedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprfineinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprfinedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1upractstby/status");

        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit1/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit2/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit3/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit4/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit5/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit6/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit7/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit8/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit9/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1uprdigit10/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1writenow");


        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrcom1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrcom2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrnav1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrnav2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwradf/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdme/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrxpdr/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrcorseinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrcorsedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrfineinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrfinedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwractstby/status");

        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit1/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit2/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit3/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit4/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit5/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit6/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit7/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit8/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit9/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad1lwrdigit10/value");

    }

    if (radcnt > 1) {
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprcom1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprcom2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprnav1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprnav2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2upradf/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdme/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprxpdr/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprcorseinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprcorsedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprfineinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprfinedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2upractstby/status");

        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit1/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit2/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit3/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit4/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit5/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit6/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit7/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit8/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit9/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2uprdigit10/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2writenow");


        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrcom1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrcom2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrnav1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrnav2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwradf/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdme/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrxpdr/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrcorseinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrcorsedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrfineinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrfinedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwractstby/status");

        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit1/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit2/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit3/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit4/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit5/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit6/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit7/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit8/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit9/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad2lwrdigit10/value");

    }

    if (radcnt > 2) {
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprcom1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprcom2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprnav1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprnav2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3upradf/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdme/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprxpdr/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprcorseinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprcorsedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprfineinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprfinedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3upractstby/status");

        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit1/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit2/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit3/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit4/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit5/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit6/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit7/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit8/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit9/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3uprdigit10/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3writenow");


        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrcom1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrcom2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrnav1/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrnav2/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwradf/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdme/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrxpdr/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrcorseinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrcorsedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrfineinc/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrfinedec/status");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwractstby/status");

        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit1/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit2/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit3/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit4/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit5/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit6/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit7/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit8/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit9/value");
        XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
            (void *) "bgood/xsaitekpanels/radiopanel/rad3lwrdigit10/value");

    }

    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/multipanel/count");

    XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 0x01000000,
        (void *) "bgood/xsaitekpanels/tpmpanel/count");

    return 0;
}


// ************************* Aircraft Loaded Deferred Init Callback  *************************
float MyPanelsDeferredInitNewAircraftFLCB(float MyPanelselapsedMe,
    float MyPanelselapsedSim, int MyPanelscounter, void *MyPanelsrefcon)
{
    (void) MyPanelselapsedMe;   // To get rid of warnings on unused variables
    (void) MyPanelselapsedSim;  // To get rid of warnings on unused variables
    (void) MyPanelscounter;     // To get rid of warnings on unused variables
    (void) MyPanelsrefcon;      // To get rid of warnings on unused variables

    static int MyPanelsFLCBStartUpFlag = 0;
    if (MyPanelsFLCBStartUpFlag == 0) {
        MyPanelsFLCBStartUpFlag = 1;    // Flag tells init has already been completed
        process_read_ini_file();
    }
    return 0;                   // Returning 0 stops DeferredInitFLCB from being looped again.
}



// ************************* Panels Callback  *************************
float MyPanelsFlightLoopCallback(float inElapsedSinceLastCall,
    float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon)
{
    (void) inElapsedSinceLastCall;      // To get rid of warnings on unused variables
    (void) inElapsedTimeSinceLastFlightLoop;    // To get rid of warnings on unused variables
    (void) inCounter;           // To get rid of warnings on unused variables
    (void) inRefcon;            // To get rid of warnings on unused variables

    if (radcnt > 0) {
        process_radio_panel();
    }

    process_all_multipanels();

    if (switchcnt > 0) {
        process_switch_panel();
    }

    if (bipcnt > 0) {
        process_bip_panel();

    }

    if (readiniloop < 50) {
        readiniloop++;
    } else if (readiniloop == 50) {
        process_read_ini_file();
        readiniloop = 51;
        if (dre_enable == 1) {
            XPLMRegisterFlightLoopCallback(XsaitekpanelsCustomDatarefLoopCB,
                1, NULL);

        } else {

        }
    }

    XPLMSetDatai(XsaitekpanelsVersionDataRef, XsaitekpanelsVersion);

    XsaitekpanelsFnButton = xpanelsfnbutton;
    XPLMSetDatai(XsaitekpanelsFnButtonDataRef, XsaitekpanelsFnButton);

    XsaitekpanelsLeftStartFnButton = xpanelsleftstartfnbutton;
    XPLMSetDatai(XsaitekpanelsLeftStartFnButtonDataRef,
        XsaitekpanelsLeftStartFnButton);

    XPLMSetDatai(SwitchPanelCountDataRef, switchcnt);
    XPLMSetDatai(RadioPanelCountDataRef, radcnt);
//    XPLMSetDatai(MultiPanelCountDataRef, multicnt);
    XPLMSetDatai(TpmPanelCountDataRef, tpmcnt);

    return interval;
}

/*
 * Returns true if avionics power is on, otherwise returns false.
 * Related INI options:
 *	Avionics Power On = [0|1|2]
 *		0: consult sim/cockpit2/switches/avionics_power_on (default)
 *		1: ignore avionics power status, avionics is always on
 *		2: consult custom dataref set by the
 *		   avionics_power_on_remapable_data INI file option
 */
bool AvPwrIsOn()
{
    if (AvPwrOnConfig == 1) {
        return true;
    } else if (AvPwrOnConfig == 2 && AvPwrOnCustomDataref != NULL) {
        return XPLMGetDatai(AvPwrOnCustomDataref) == 1;
    } else {
        return XPLMGetDatai(AvPwrOn) == 1;
    }
}

/*
 * Returns true if battery power is on, otherwise returns false.
 * Related INI options:
 *	Battery Power On = [0|1|2]
 *		0: consult sim/cockpit/electrical/battery_on (default)
 *		1: ignore battery power status, battery is always on
 *		2: consult custom dataref set by the
 *		   battery_power_on_remapable_data INI file option
 */
bool BatPwrIsOn()
{
    if (BatPwrOnConfig == 1) {
        return true;
    } else if (BatPwrOnConfig == 2 && BatPwrOnCustomDataref != NULL) {
        return XPLMGetDatai(BatPwrOnCustomDataref) == 1;
    } else {
        return XPLMGetDatai(BatPwrOn) == 1;
    }
}
