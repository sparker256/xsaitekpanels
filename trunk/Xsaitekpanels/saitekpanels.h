#ifndef SAITEKPANELS_H
#define SAITEKPANELS_H

#include "XPLMUtilities.h"
#include "XPLMMenus.h"
#include "XPWidgets.h"
#include "XPStandardWidgets.h"

#include "hidapi.h"

#include <string>

using namespace std;

// ****************  Start Radio Panel Section  ***************************

// ************** Radio Panel SDK Command Ref **********************
extern XPLMCommandRef Com1StbyFineDn, Com1StbyFineUp, Com1StbyCorseDn, Com1StbyCorseUp;
extern XPLMCommandRef Com2StbyFineDn, Com2StbyFineUp, Com2StbyCorseDn, Com2StbyCorseUp;
extern XPLMCommandRef Nav1StbyFineDn, Nav1StbyFineUp, Nav1StbyCorseDn, Nav1StbyCorseUp;
extern XPLMCommandRef Nav2StbyFineDn, Nav2StbyFineUp, Nav2StbyCorseDn, Nav2StbyCorseUp;

extern XPLMCommandRef Afd1StbyHunUp, Afd1StbyHunDn, Afd1StbyTensUp, Afd1StbyTensDn;
extern XPLMCommandRef Afd1StbyOnesUp, Afd1StbyOnesDn;

extern XPLMCommandRef Afd2StbyHunUp, Afd2StbyHunDn, Afd2StbyTensUp, Afd2StbyTensDn;
extern XPLMCommandRef Afd2StbyOnesUp, Afd2StbyOnesDn;

extern XPLMCommandRef XpdrThUp, XpdrThDn, XpdrHunUp, XpdrHunDn;
extern XPLMCommandRef XpdrTensUp, XpdrTensDn, XpdrOnesUp, XpdrOnesDn;
extern XPLMCommandRef BaroUp, BaroDn, BaroStd;

extern XPLMCommandRef Com1ActStby, Com2ActStby, Nav1ActStby, Nav2ActStby;
extern XPLMCommandRef Adf1ActStby, Adf2ActStby;

extern XPLMCommandRef Obs1Down, Obs1Up;
extern XPLMCommandRef Obs2Down, Obs2Up;

extern XPLMCommandRef Rad1UprCom1CrsUpRemapableCmd, Rad1UprCom1CrsDnRemapableCmd;
extern XPLMCommandRef Rad1UprCom1FnUpRemapableCmd, Rad1UprCom1FnDnRemapableCmd;
extern XPLMCommandRef Rad1UprCom1ActStbyRemapableCmd;
extern XPLMCommandRef Rad1UprCom2CrsUpRemapableCmd, Rad1UprCom2CrsDnRemapableCmd;
extern XPLMCommandRef Rad1UprCom2FnUpRemapableCmd, Rad1UprCom2FnDnRemapableCmd;
extern XPLMCommandRef Rad1UprCom2ActStbyRemapableCmd;
extern XPLMCommandRef Rad1UprNav1CrsUpRemapableCmd, Rad1UprNav1CrsDnRemapableCmd;
extern XPLMCommandRef Rad1UprNav1FnUpRemapableCmd, Rad1UprNav1FnDnRemapableCmd;
extern XPLMCommandRef Rad1UprNav1ActStbyRemapableCmd;
extern XPLMCommandRef Rad1UprNav2CrsUpRemapableCmd, Rad1UprNav2CrsDnRemapableCmd;
extern XPLMCommandRef Rad1UprNav2FnUpRemapableCmd, Rad1UprNav2FnDnRemapableCmd;
extern XPLMCommandRef Rad1UprNav2ActStbyRemapableCmd;
extern XPLMCommandRef Rad1UpperXpdrBaroUpRemapableCmd, Rad1UpperXpdrBaroDnRemapableCmd;


extern XPLMCommandRef Rad1LowrCom1CrsUpRemapableCmd, Rad1LowrCom1CrsDnRemapableCmd;
extern XPLMCommandRef Rad1LowrCom1FnUpRemapableCmd, Rad1LowrCom1FnDnRemapableCmd;
extern XPLMCommandRef Rad1LowrCom1ActStbyRemapableCmd;
extern XPLMCommandRef Rad1LowrCom2CrsUpRemapableCmd, Rad1LowrCom2CrsDnRemapableCmd;
extern XPLMCommandRef Rad1LowrCom2FnUpRemapableCmd, Rad1LowrCom2FnDnRemapableCmd;
extern XPLMCommandRef Rad1LowrCom2ActStbyRemapableCmd;
extern XPLMCommandRef Rad1LowrNav1CrsUpRemapableCmd, Rad1LowrNav1CrsDnRemapableCmd;
extern XPLMCommandRef Rad1LowrNav1FnUpRemapableCmd, Rad1LowrNav1FnDnRemapableCmd;
extern XPLMCommandRef Rad1LowrNav1ActStbyRemapableCmd;
extern XPLMCommandRef Rad1LowrNav2CrsUpRemapableCmd, Rad1LowrNav2CrsDnRemapableCmd;
extern XPLMCommandRef Rad1LowrNav2FnUpRemapableCmd, Rad1LowrNav2FnDnRemapableCmd;
extern XPLMCommandRef Rad1LowrNav2ActStbyRemapableCmd;
extern XPLMCommandRef Rad1LowrXpdrBaroUpRemapableCmd, Rad1LowrXpdrBaroDnRemapableCmd;


extern XPLMCommandRef Rad2UprCom1CrsUpRemapableCmd, Rad2UprCom1CrsDnRemapableCmd;
extern XPLMCommandRef Rad2UprCom1FnUpRemapableCmd, Rad2UprCom1FnDnRemapableCmd;
extern XPLMCommandRef Rad2UprCom1ActStbyRemapableCmd;
extern XPLMCommandRef Rad2UprCom2CrsUpRemapableCmd, Rad2UprCom2CrsDnRemapableCmd;
extern XPLMCommandRef Rad2UprCom2FnUpRemapableCmd, Rad2UprCom2FnDnRemapableCmd;
extern XPLMCommandRef Rad2UprCom2ActStbyRemapableCmd;
extern XPLMCommandRef Rad2UprNav1CrsUpRemapableCmd, Rad2UprNav1CrsDnRemapableCmd;
extern XPLMCommandRef Rad2UprNav1FnUpRemapableCmd, Rad2UprNav1FnDnRemapableCmd;
extern XPLMCommandRef Rad2UprNav1ActStbyRemapableCmd;
extern XPLMCommandRef Rad2UprNav2CrsUpRemapableCmd, Rad2UprNav2CrsDnRemapableCmd;
extern XPLMCommandRef Rad2UprNav2FnUpRemapableCmd, Rad2UprNav2FnDnRemapableCmd;
extern XPLMCommandRef Rad2UprNav2ActStbyRemapableCmd;
extern XPLMCommandRef Rad2UpperXpdrBaroUpRemapableCmd, Rad2UpperXpdrBaroDnRemapableCmd;


extern XPLMCommandRef Rad2LowrCom1CrsUpRemapableCmd, Rad2LowrCom1CrsDnRemapableCmd;
extern XPLMCommandRef Rad2LowrCom1FnUpRemapableCmd, Rad2LowrCom1FnDnRemapableCmd;
extern XPLMCommandRef Rad2LowrCom1ActStbyRemapableCmd;
extern XPLMCommandRef Rad2LowrCom2CrsUpRemapableCmd, Rad2LowrCom2CrsDnRemapableCmd;
extern XPLMCommandRef Rad2LowrCom2FnUpRemapableCmd, Rad2LowrCom2FnDnRemapableCmd;
extern XPLMCommandRef Rad2LowrCom2ActStbyRemapableCmd;
extern XPLMCommandRef Rad2LowrNav1CrsUpRemapableCmd, Rad2LowrNav1CrsDnRemapableCmd;
extern XPLMCommandRef Rad2LowrNav1FnUpRemapableCmd, Rad2LowrNav1FnDnRemapableCmd;
extern XPLMCommandRef Rad2LowrNav1ActStbyRemapableCmd;
extern XPLMCommandRef Rad2LowrNav2CrsUpRemapableCmd, Rad2LowrNav2CrsDnRemapableCmd;
extern XPLMCommandRef Rad2LowrNav2FnUpRemapableCmd, Rad2LowrNav2FnDnRemapableCmd;
extern XPLMCommandRef Rad2LowrNav2ActStbyRemapableCmd;
extern XPLMCommandRef Rad2LowrXpdrBaroUpRemapableCmd, Rad2LowrXpdrBaroDnRemapableCmd;


// ************** Radio Panel SDK Data Ref **********************
extern XPLMDataRef Com1ActFreq, Com2ActFreq, Nav1ActFreq, Nav2ActFreq;
extern XPLMDataRef Com1StbyFreq, Com2StbyFreq, Nav1StbyFreq, Nav2StbyFreq;

extern XPLMDataRef Adf1StbyFreq, Adf2StbyFreq;
extern XPLMDataRef Adf1ActFreq, Adf2ActFreq;

extern XPLMDataRef XpdrCode, XpdrMode, BaroSetting;
extern XPLMDataRef MetricPress;
extern XPLMDataRef DmeMode, DmeSlvSource;
extern XPLMDataRef Nav1DmeNmDist, Nav1DmeSpeed;
extern XPLMDataRef Nav2DmeNmDist, Nav2DmeSpeed;
extern XPLMDataRef DmeFreq, DmeTime, DmeSpeed;

extern XPLMDataRef AvPwrOn, BatPwrOn;

extern XPLMDataRef Nav1PwrOn, Nav2PwrOn, Com1PwrOn, Com2PwrOn;
extern XPLMDataRef Afd1PwrOn, DmePwrOn;

extern XPLMDataRef Nav1ObsDegm, Nav2ObsDegm;
extern XPLMDataRef Adf1CardDirDegm,  Adf2CardDirDegm;


extern XPLMDataRef Rad1UpperCom1ActRemapableData, Rad1UpperCom1StbyRemapableData, Rad1UprCom1ActStbyRemapableData;
extern XPLMDataRef Rad1UpperCom2ActRemapableData, Rad1UpperCom2StbyRemapableData, Rad1UprCom2ActStbyRemapableData;
extern XPLMDataRef Rad1UpperNav1ActRemapableData, Rad1UpperNav1StbyRemapableData, Rad1UprNav1ActStbyRemapableData;
extern XPLMDataRef Rad1UpperNav2ActRemapableData, Rad1UpperNav2StbyRemapableData, Rad1UprNav2ActStbyRemapableData;
extern XPLMDataRef Rad1UpperXpdrRemapableData, Rad1UpperXpdrRemapableMode, Rad1UpperXpdrBaroStdRemapableData;

extern XPLMDataRef Rad1LowerCom1ActRemapableData, Rad1LowerCom1StbyRemapableData, Rad1LowrCom1ActStbyRemapableData;
extern XPLMDataRef Rad1LowerCom2ActRemapableData, Rad1LowerCom2StbyRemapableData, Rad1LowrCom2ActStbyRemapableData;
extern XPLMDataRef Rad1LowerNav1ActRemapableData, Rad1LowerNav1StbyRemapableData, Rad1LowrNav1ActStbyRemapableData;
extern XPLMDataRef Rad1LowerNav2ActRemapableData, Rad1LowerNav2StbyRemapableData, Rad1LowrNav2ActStbyRemapableData;
extern XPLMDataRef Rad1LowerXpdrRemapableData, Rad1LowerXpdrRemapableMode, Rad1LowerXpdrBaroStdRemapableData;


extern XPLMDataRef Rad2UpperCom1ActRemapableData, Rad2UpperCom1StbyRemapableData, Rad2UprCom1ActStbyRemapableData;
extern XPLMDataRef Rad2UpperCom2ActRemapableData, Rad2UpperCom2StbyRemapableData, Rad2UprCom2ActStbyRemapableData;
extern XPLMDataRef Rad2UpperNav1ActRemapableData, Rad2UpperNav1StbyRemapableData, Rad2UprNav1ActStbyRemapableData;
extern XPLMDataRef Rad2UpperNav2ActRemapableData, Rad2UpperNav2StbyRemapableData, Rad2UprNav2ActStbyRemapableData;
extern XPLMDataRef Rad2UpperXpdrRemapableData, Rad2UpperXpdrRemapableMode, Rad2UpperXpdrBaroStdRemapableData;

extern XPLMDataRef Rad2LowerCom1ActRemapableData, Rad2LowerCom1StbyRemapableData, Rad2LowrCom1ActStbyRemapableData;
extern XPLMDataRef Rad2LowerCom2ActRemapableData, Rad2LowerCom2StbyRemapableData, Rad2LowrCom2ActStbyRemapableData;
extern XPLMDataRef Rad2LowerNav1ActRemapableData, Rad2LowerNav1StbyRemapableData, Rad2LowrNav1ActStbyRemapableData;
extern XPLMDataRef Rad2LowerNav2ActRemapableData, Rad2LowerNav2StbyRemapableData, Rad2LowrNav2ActStbyRemapableData;
extern XPLMDataRef Rad2LowerXpdrRemapableData, Rad2LowerXpdrRemapableMode, Rad2LowerXpdrBaroStdRemapableData;

extern XPLMDataRef Rad1UpperCom1OwnedDataRef, Rad1UpperCom2OwnedDataRef;
extern XPLMDataRef Rad1UpperNav1OwnedDataRef, Rad1UpperNav2OwnedDataRef;
extern XPLMDataRef Rad1UpperAdfOwnedDataRef, Rad1UpperDmeOwnedDataRef;
extern XPLMDataRef Rad1UpperCom1OwnedDataRef, Rad1UpperCom2OwnedDataRef;
extern XPLMDataRef Rad1UpperXpdrOwnedDataRef, Rad1UpperCorseIncOwnedDataRef;
extern XPLMDataRef Rad1UpperCorseDecOwnedDataRef, Rad1UpperFineIncOwnedDataRef;
extern XPLMDataRef Rad1UpperFineDecOwnedDataRef, Rad1UpperActStbyOwnedDataRef;

extern XPLMDataRef Rad1LowerCom1OwnedDataRef, Rad1LowerCom2OwnedDataRef;
extern XPLMDataRef Rad1LowerNav1OwnedDataRef, Rad1LowerNav2OwnedDataRef;
extern XPLMDataRef Rad1LowerAdfOwnedDataRef, Rad1LowerDmeOwnedDataRef;
extern XPLMDataRef Rad1LowerXpdrOwnedDataRef, Rad1LowerCorseIncOwnedDataRef;
extern XPLMDataRef Rad1LowerCorseDecOwnedDataRef, Rad1LowerFineIncOwnedDataRef;
extern XPLMDataRef Rad1LowerFineDecOwnedDataRef, Rad1LowerActStbyOwnedDataRef;

extern XPLMDataRef Rad2UpperCom1OwnedDataRef, Rad2UpperCom2OwnedDataRef;
extern XPLMDataRef Rad2UpperNav1OwnedDataRef, Rad2UpperNav2OwnedDataRef;
extern XPLMDataRef Rad2UpperAdfOwnedDataRef, Rad2UpperDmeOwnedDataRef;
extern XPLMDataRef Rad2UpperCom1OwnedDataRe, Rad2UpperCom2OwnedDataRef;
extern XPLMDataRef Rad2UpperXpdrOwnedDataRef, Rad2UpperCorseIncOwnedDataRef;
extern XPLMDataRef Rad2UpperCorseDecOwnedDataRef, Rad2UpperFineIncOwnedDataRef;
extern XPLMDataRef Rad2UpperFineDecOwnedDataRef, Rad2UpperActStbyOwnedDataRef;

extern XPLMDataRef Rad2LowerCom1OwnedDataRef, Rad2LowerCom2OwnedDataRef;
extern XPLMDataRef Rad2LowerNav1OwnedDataRef, Rad2LowerNav2OwnedDataRef;
extern XPLMDataRef Rad2LowerAdfOwnedDataRef, Rad2LowerDmeOwnedDataRef;
extern XPLMDataRef Rad2LowerCom1OwnedDataRe, Rad2LowerCom2OwnedDataRef;
extern XPLMDataRef Rad2LowerXpdrOwnedDataRef, Rad2LowerCorseIncOwnedDataRef;
extern XPLMDataRef Rad2LowerCorseDecOwnedDataRef, Rad2LowerFineIncOwnedDataRef;
extern XPLMDataRef Rad2LowerFineDecOwnedDataRef, Rad2LowerActStbyOwnedDataRef;

extern XPLMMenuID      RadioMenu;
extern XPLMMenuID      RadioMenuId;

extern XPWidgetID	RadioWidgetID;
extern XPWidgetID	RadioWindow;
extern XPWidgetID	RadioSpeed1CheckWidget[50];
extern XPWidgetID	RadioSpeed2CheckWidget[50];
extern XPWidgetID	RadioSpeed3CheckWidget[50];
extern XPWidgetID	RadioSpeed4CheckWidget[50];
extern XPWidgetID	RadioSpeed5CheckWidget[50];

extern XPWidgetID	RadioAdf1CheckWidget[50];
extern XPWidgetID	RadioAdf2CheckWidget[50];

extern XPWidgetID	RadioQnh0CheckWidget[50];
extern XPWidgetID	RadioQnh1CheckWidget[50];


// ************************ Radio Panel variables **************************
extern int radio0fd, radio1fd, radio2fd, radio3fd, radio4fd, radio5fd, radio6fd, radio7fd;
extern int radio8fd, radio9fd, radio10fd, radio11fd, radio12fd, radio13fd, radio14fd, radio15fd;
extern int radiofd[4], radcnt, radres;
extern int radspeed, metricpressenable;

extern int rad1uprcom1switchremap, rad1uprcom1actstbybtnremap;
extern int rad1uprcom2switchremap, rad1uprcom2actstbybtnremap;
extern int rad1uprnav1switchremap, rad1uprnav1actstbybtnremap;
extern int rad1uprnav2switchremap, rad1uprnav2actstbybtnremap;
extern int rad1uprxpdrswitchremap;
extern int rad1lwrcom1switchremap, rad1lwrcom1actstbybtnremap;
extern int rad1lwrcom2switchremap, rad1lwrcom2actstbybtnremap;
extern int rad1lwrnav1switchremap, rad1lwrnav1actstbybtnremap;
extern int rad1lwrnav2switchremap, rad1lwrnav2actstbybtnremap;
extern int rad1lwrxpdrswitchremap;

extern int rad2uprcom1switchremap, rad2uprcom1actstbybtnremap;
extern int rad2uprcom2switchremap, rad2uprcom2actstbybtnremap;
extern int rad2uprnav1switchremap, rad2uprnav1actstbybtnremap;
extern int rad2uprnav2switchremap, rad2uprnav2actstbybtnremap;
extern int rad2uprxpdrswitchremap;
extern int rad2lwrcom1switchremap, rad2lwrcom1actstbybtnremap;
extern int rad2lwrcom2switchremap, rad2lwrcom2actstbybtnremap;
extern int rad2lwrnav1switchremap, rad2lwrnav1actstbybtnremap;
extern int rad2lwrnav2switchremap, rad2lwrnav2actstbybtnremap;
extern int rad2lwrxpdrswitchremap;

extern int	Rad1UprCom1StatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprCom1StatusSetDataiCallback(void * inRefcon, int Rad1UprCom1Status);

extern int	Rad1UprCom2StatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprCom2StatusSetDataiCallback(void * inRefcon, int Rad1UprCom2Status);

extern int	Rad1UprNav1StatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprNav1StatusSetDataiCallback(void * inRefcon, int Rad1UprNav1Status);

extern int	Rad1UprNav2StatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprNav2StatusSetDataiCallback(void * inRefcon, int Rad1UprNav2Status);

extern int	Rad1UprAdfStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprAdfStatusSetDataiCallback(void * inRefcon, int Rad1UprAdfStatus);

extern int	Rad1UprDmeStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprDmeStatusSetDataiCallback(void * inRefcon, int Rad1UprDmeStatus);

extern int	Rad1UprXpdrStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprXpdrStatusSetDataiCallback(void * inRefcon, int Rad1UprXpdrStatus);

extern int	Rad1UprCorseIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprCorseIncStatusSetDataiCallback(void * inRefcon, int Rad1UprCorseIncStatus);

extern int	Rad1UprCorseDecStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprCorseDecStatusSetDataiCallback(void * inRefcon, int Rad1UprCorseDecStatus);

extern int	Rad1UprFineIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprFineIncStatusSetDataiCallback(void * inRefcon, int Rad1UprFineIncStatus);

extern int	Rad1UprFineDecStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprFineDecStatusSetDataiCallback(void * inRefcon, int Rad1UprFineDecStatus);

extern int	Rad1UprActStbyStatusGetDataiCallback(void * inRefcon);
extern void	Rad1UprActStbyStatusSetDataiCallback(void * inRefcon, int Rad1UprActStbyStatus);


extern int	Rad1LwrCom1StatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrCom1StatusSetDataiCallback(void * inRefcon, int Rad1LwrCom1Status);

extern int	Rad1LwrCom2StatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrCom2StatusSetDataiCallback(void * inRefcon, int Rad1LwrCom2Status);

extern int	Rad1LwrNav1StatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrNav1StatusSetDataiCallback(void * inRefcon, int Rad1LwrNav1Status);

extern int	Rad1LwrNav2StatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrNav2StatusSetDataiCallback(void * inRefcon, int Rad1LwrNav2Status);

extern int	Rad1LwrAdfStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrAdfStatusSetDataiCallback(void * inRefcon, int Rad1LwrAdfStatus);

extern int	Rad1LwrDmeStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrDmeStatusSetDataiCallback(void * inRefcon, int Rad1LwrDmeStatus);

extern int	Rad1LwrXpdrStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrXpdrStatusSetDataiCallback(void * inRefcon, int Rad1LwrXpdrStatus);

extern int	Rad1LwrCorseIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrCorseIncStatusSetDataiCallback(void * inRefcon, int Rad1LwrCorseIncStatus);

extern int	Rad1LwrCorseDecStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrCorseDecStatusSetDataiCallback(void * inRefcon, int Rad1LwrCorseDecStatus);

extern int	Rad1LwrFineIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrFineIncStatusSetDataiCallback(void * inRefcon, int Rad1LwrFineIncStatus);

extern int	Rad1LwrFineDecStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrFineDecStatusSetDataiCallback(void * inRefcon, int Rad1LwrFineDecStatus);

extern int	Rad1LwrActStbyStatusGetDataiCallback(void * inRefcon);
extern void	Rad1LwrActStbyStatusSetDataiCallback(void * inRefcon, int Rad1LwrActStbyStatus);


extern int	Rad2UprCom1StatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprCom1StatusSetDataiCallback(void * inRefcon, int Rad2UprCom1Status);

extern int	Rad2UprCom2StatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprCom2StatusSetDataiCallback(void * inRefcon, int Rad2UprCom2Status);

extern int	Rad2UprNav1StatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprNav1StatusSetDataiCallback(void * inRefcon, int Rad2UprNav1Status);

extern int	Rad2UprNav2StatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprNav2StatusSetDataiCallback(void * inRefcon, int Rad2UprNav2Status);

extern int	Rad2UprAdfStatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprAdfStatusSetDataiCallback(void * inRefcon, int Rad2UprAdfStatus);

extern int	Rad2UprDmeStatusGetDataiCallback(void * inRefcon);
void	Rad2UprDmeStatusSetDataiCallback(void * inRefcon, int Rad2UprDmeStatus);

extern int	Rad2UprXpdrStatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprXpdrStatusSetDataiCallback(void * inRefcon, int Rad2UprXpdrStatus);

extern int	Rad2UprCorseIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprCorseIncStatusSetDataiCallback(void * inRefcon, int Rad2UprCorseIncStatus);

extern int	Rad2UprCorseDecStatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprCorseDecStatusSetDataiCallback(void * inRefcon, int Rad2UprCorseDecStatus);

extern int	Rad2UprFineIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprFineIncStatusSetDataiCallback(void * inRefcon, int Rad2UprFineIncStatus);

extern int	Rad2UprFineDecStatusGetDataiCallback(void * inRefcon);
void	Rad2UprFineDecStatusSetDataiCallback(void * inRefcon, int Rad2UprFineDecStatus);

extern int	Rad2UprActStbyStatusGetDataiCallback(void * inRefcon);
extern void	Rad2UprActStbyStatusSetDataiCallback(void * inRefcon, int Rad2UprActStbyStatus);


extern int	Rad2LwrCom1StatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrCom1StatusSetDataiCallback(void * inRefcon, int Rad2LwrCom1Status);

extern int	Rad2LwrCom2StatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrCom2StatusSetDataiCallback(void * inRefcon, int Rad2LwrCom2Status);

extern int	Rad2LwrNav1StatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrNav1StatusSetDataiCallback(void * inRefcon, int Rad2LwrNav1Status);

extern int	Rad2LwrNav2StatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrNav2StatusSetDataiCallback(void * inRefcon, int Rad2LwrNav2Status);

extern int	Rad2LwrAdfStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrAdfStatusSetDataiCallback(void * inRefcon, int Rad2LwrAdfStatus);

extern int	Rad2LwrDmeStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrDmeStatusSetDataiCallback(void * inRefcon, int Rad2LwrDmeStatus);

extern int	Rad2LwrXpdrStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrXpdrStatusSetDataiCallback(void * inRefcon, int Rad2LwrXpdrStatus);

extern int	Rad2LwrCorseIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrCorseIncStatusSetDataiCallback(void * inRefcon, int Rad2LwrCorseIncStatus);

extern int	Rad2LwrCorseDecStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrCorseDecStatusSetDataiCallback(void * inRefcon, int Rad2LwrCorseDecStatus);

extern int	Rad2LwrFineIncStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrFineIncStatusSetDataiCallback(void * inRefcon, int Rad2LwrFineIncStatus);

extern int	Rad2LwrFineDecStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrFineDecStatusSetDataiCallback(void * inRefcon, int Rad2LwrFineDecStatus);

extern int	Rad2LwrActStbyStatusGetDataiCallback(void * inRefcon);
extern void	Rad2LwrActStbyStatusSetDataiCallback(void * inRefcon, int Rad2LwrActStbyStatus);







extern string rad1_upper_com1_corse_up_remapable, rad1_upper_com1_corse_dn_remapable;
extern string rad1_upper_com1_fine_up_remapable, rad1_upper_com1_fine_dn_remapable;
extern string rad1_upper_com1_act_data_remapable, rad1_upper_com1_stby_data_remapable;
extern string rad1_upper_com1_actstby_btn_remapable_cmd, rad1_upper_com1_actstby_btn_remapable_data;

extern string rad1_upper_com2_corse_up_remapable, rad1_upper_com2_corse_dn_remapable;
extern string rad1_upper_com2_fine_up_remapable, rad1_upper_com2_fine_dn_remapable;
extern string rad1_upper_com2_act_data_remapable, rad1_upper_com2_stby_data_remapable;
extern string rad1_upper_com2_actstby_btn_remapable_cmd, rad1_upper_com2_actstby_btn_remapable_data;

extern string rad1_upper_nav1_corse_up_remapable, rad1_upper_nav1_corse_dn_remapable;
extern string rad1_upper_nav1_fine_up_remapable, rad1_upper_nav1_fine_dn_remapable;
extern string rad1_upper_nav1_act_data_remapable, rad1_upper_nav1_stby_data_remapable;
extern string rad1_upper_nav1_actstby_btn_remapable_cmd, rad1_upper_nav1_actstby_btn_remapable_data;

extern string rad1_upper_nav2_corse_up_remapable, rad1_upper_nav2_corse_dn_remapable;
extern string rad1_upper_nav2_fine_up_remapable, rad1_upper_nav2_fine_dn_remapable;
extern string rad1_upper_nav2_act_data_remapable, rad1_upper_nav2_stby_data_remapable;
extern string rad1_upper_nav2_actstby_btn_remapable_cmd, rad1_upper_nav2_actstby_btn_remapable_data;

extern string rad1_upper_xpdr_data_remapable, rad1_upper_xpdr_mode_remapable, rad1_upper_xpdr_baro_std_data_remapable;
extern string rad1_upper_xpdr_baro_up_remapable_cmd, rad1_upper_xpdr_baro_dn_remapable_cmd;


extern string rad1_lower_com1_corse_up_remapable, rad1_lower_com1_corse_dn_remapable;
extern string rad1_lower_com1_fine_up_remapable, rad1_lower_com1_fine_dn_remapable;
extern string rad1_lower_com1_act_data_remapable, rad1_lower_com1_stby_data_remapable;
extern string rad1_lower_com1_actstby_btn_remapable_cmd, rad1_lower_com1_actstby_btn_remapable_data;

extern string rad1_lower_com2_corse_up_remapable, rad1_lower_com2_corse_dn_remapable;
extern string rad1_lower_com2_fine_up_remapable, rad1_lower_com2_fine_dn_remapable;
extern string rad1_lower_com2_act_data_remapable, rad1_lower_com2_stby_data_remapable;
extern string rad1_lower_com2_actstby_btn_remapable_cmd, rad1_lower_com2_actstby_btn_remapable_data;

extern string rad1_lower_nav1_corse_up_remapable, rad1_lower_nav1_corse_dn_remapable;
extern string rad1_lower_nav1_fine_up_remapable, rad1_lower_nav1_fine_dn_remapable;
extern string rad1_lower_nav1_act_data_remapable, rad1_lower_nav1_stby_data_remapable;
extern string rad1_lower_nav1_actstby_btn_remapable_cmd, rad1_lower_nav1_actstby_btn_remapable_data;

extern string rad1_lower_nav2_corse_up_remapable, rad1_lower_nav2_corse_dn_remapable;
extern string rad1_lower_nav2_fine_up_remapable, rad1_lower_nav2_fine_dn_remapable;
extern string rad1_lower_nav2_act_data_remapable, rad1_lower_nav2_stby_data_remapable;
extern string rad1_lower_nav2_actstby_btn_remapable_cmd, rad1_lower_nav2_actstby_btn_remapable_data;

extern string rad1_lower_xpdr_data_remapable, rad1_lower_xpdr_mode_remapable;
extern string rad1_lower_xpdr_baro_std_data_remapable;
extern string rad1_lower_xpdr_baro_up_remapable_cmd, rad1_lower_xpdr_baro_dn_remapable_cmd;

extern string rad2_upper_com1_corse_up_remapable, rad2_upper_com1_corse_dn_remapable;
extern string rad2_upper_com1_fine_up_remapable, rad2_upper_com1_fine_dn_remapable;
extern string rad2_upper_com1_act_data_remapable, rad2_upper_com1_stby_data_remapable;
extern string rad2_upper_com1_actstby_btn_remapable_cmd, rad2_upper_com1_actstby_btn_remapable_data;

extern string rad2_upper_com2_corse_up_remapable, rad2_upper_com2_corse_dn_remapable;
extern string rad2_upper_com2_fine_up_remapable, rad2_upper_com2_fine_dn_remapable;
extern string rad2_upper_com2_act_data_remapable, rad2_upper_com2_stby_data_remapable;
extern string rad2_upper_com2_actstby_btn_remapable_cmd, rad2_upper_com2_actstby_btn_remapable_data;

extern string rad2_upper_nav1_corse_up_remapable, rad2_upper_nav1_corse_dn_remapable;
extern string rad2_upper_nav1_fine_up_remapable, rad2_upper_nav1_fine_dn_remapable;
extern string rad2_upper_nav1_act_data_remapable, rad2_upper_nav1_stby_data_remapable;
extern string rad2_upper_nav1_actstby_btn_remapable_cmd, rad2_upper_nav1_actstby_btn_remapable_data;

extern string rad2_upper_nav2_corse_up_remapable, rad2_upper_nav2_corse_dn_remapable;
extern string rad2_upper_nav2_fine_up_remapable, rad2_upper_nav2_fine_dn_remapable;
extern string rad2_upper_nav2_act_data_remapable, rad2_upper_nav2_stby_data_remapable;
extern string rad2_upper_nav2_actstby_btn_remapable_cmd, rad2_upper_nav2_actstby_btn_remapable_data;

extern string rad2_upper_xpdr_data_remapable, rad2_upper_xpdr_mode_remapable, rad2_upper_xpdr_baro_std_data_remapable;

extern string rad2_upper_xpdr_baro_up_remapable_cmd, rad2_upper_xpdr_baro_dn_remapable_cmd;


extern string rad2_lower_com1_corse_up_remapable, rad2_lower_com1_corse_dn_remapable;
extern string rad2_lower_com1_fine_up_remapable, rad2_lower_com1_fine_dn_remapable;
extern string rad2_lower_com1_act_data_remapable, rad2_lower_com1_stby_data_remapable;
extern string rad2_lower_com1_actstby_btn_remapable_cmd, rad2_lower_com1_actstby_btn_remapable_data;

extern string rad2_lower_com2_corse_up_remapable, rad2_lower_com2_corse_dn_remapable;
extern string rad2_lower_com2_fine_up_remapable, rad2_lower_com2_fine_dn_remapable;
extern string rad2_lower_com2_act_data_remapable, rad2_lower_com2_stby_data_remapable;
extern string rad2_lower_com2_actstby_btn_remapable_cmd, rad2_lower_com2_actstby_btn_remapable_data;

extern string rad2_lower_nav1_corse_up_remapable, rad2_lower_nav1_corse_dn_remapable;
extern string rad2_lower_nav1_fine_up_remapable, rad2_lower_nav1_fine_dn_remapable;
extern string rad2_lower_nav1_act_data_remapable, rad2_lower_nav1_stby_data_remapable;
extern string rad2_lower_nav1_actstby_btn_remapable_cmd, rad2_lower_nav1_actstby_btn_remapable_data;

extern string rad2_lower_nav2_corse_up_remapable, rad2_lower_nav2_corse_dn_remapable;
extern string rad2_lower_nav2_fine_up_remapable, rad2_lower_nav2_fine_dn_remapable;
extern string rad2_lower_nav2_act_data_remapable, rad2_lower_nav2_stby_data_remapable;
extern string rad2_lower_nav2_actstby_btn_remapable_cmd, rad2_lower_nav2_actstby_btn_remapable_data;

extern string rad2_lower_xpdr_data_remapable, rad2_lower_xpdr_mode_remapable, rad2_lower_xpdr_baro_std_data_remapable;

extern string rad2_lower_xpdr_baro_up_remapable_cmd, rad2_lower_xpdr_baro_dn_remapable_cmd;

extern float interval;
extern unsigned char radbuf[4], radwbuf[21];

extern hid_device *radiohandle[4];

// ****************  End Radio Panel Section  ***************************

// *************************************************************************

// ****************  Start Multi Panel Section  ***************************

// ********** Multi Panel Command Ref ***************
extern XPLMCommandRef ApAltDn, ApAltUp, ApVsDn, ApVsUp;
extern XPLMCommandRef ApAsDn, ApAsUp, ApHdgDn, ApHdgUp;
extern XPLMCommandRef ApCrsDn, ApCrsUp, ApCrsDn2, ApCrsUp2;

extern XPLMCommandRef ApMstrBtnUp, ApMstrBtnDn, ApMstrBtnOff;
extern XPLMCommandRef ApHdgBtn, ApNavBtn, ApAltBtn, ApAltArmBtn;
extern XPLMCommandRef ApIasBtn;
extern XPLMCommandRef ApVsBtn, ApAprBtn, ApRevBtn;
extern XPLMCommandRef ApKnotsMachTgl;

extern XPLMCommandRef FlapsDn, FlapsUp;
extern XPLMCommandRef PitchTrimDn, PitchTrimUp, PitchTrimTkOff;

extern XPLMCommandRef ApButtonRemapableCmd, HdgButtonRemapableCmd;
extern XPLMCommandRef NavButtonVorlocRemapableCmd, NavButtonLnavRemapableCmd;
extern XPLMCommandRef IasButtonRemapableCmd, IasChangeoverButtonRemapableCmd;
extern XPLMCommandRef AltButtonRemapableCmd, VsButtonRemapableCmd;
extern XPLMCommandRef AprButtonRemapableCmd, RevButtonRemapableCmd;

extern XPLMCommandRef AltSwitchUpRemapableCmd, AltSwitchDnRemapableCmd;
extern XPLMCommandRef VsSwitchUpRemapableCmd, VsSwitchDnRemapableCmd;
extern XPLMCommandRef IasSwitchUpRemapableCmd, IasSwitchDnRemapableCmd;
extern XPLMCommandRef HdgSwitchUpRemapableCmd, HdgSwitchDnRemapableCmd;
extern XPLMCommandRef CrsSwitchUpRemapableCmd, CrsSwitchDnRemapableCmd;

extern XPLMCommandRef ApVsUpRemapableCmd, ApVsDnRemapableCmd;
extern XPLMCommandRef TrimUpRemapableCmd, TrimDnRemapableCmd;

// ************ Multi Panel Data Ref *****************
extern XPLMDataRef ApAlt, ApVs, ApAs, ApHdg, ApCrs, ApCrs2;

extern XPLMDataRef ApMstrStat, ApHdgStat, ApNavStat, ApIasStat;
extern XPLMDataRef ApAltStat, ApVsStat, ApAprStat, ApRevStat;
extern XPLMDataRef ApState, ApAutThr;
extern XPLMDataRef AirspeedIsMach, Airspeed;

extern XPLMDataRef ApButtonRemapableData, HdgButtonRemapableData;
extern XPLMDataRef NavButtonVorlocRemapableData, NavButtonLnavRemapableData;
extern XPLMDataRef IasButtonRemapableData, IasChangeoverButtonRemapableData;
extern XPLMDataRef AltButtonRemapableData, VsButtonRemapableData;
extern XPLMDataRef AprButtonRemapableData, RevButtonRemapableData;

extern XPLMDataRef AltSwitchRemapableData;
extern XPLMDataRef VsSwitchRemapableData;
extern XPLMDataRef IasSwitchRemapableData;
extern XPLMDataRef HdgSwitchRemapableData;
extern XPLMDataRef CrsSwitchRemapableData;

extern XPLMDataRef AttrSwitchRemapableData;

extern XPLMDataRef IasIsmachRemapableData;

extern XPLMDataRef ApLightRemapableData, HdgLightRemapableData;
extern XPLMDataRef NavLightVorlocRemapableData, NavLightLnavRemapableData;
extern XPLMDataRef IasLightRemapableData;
extern XPLMDataRef AltLightRemapableData, VsLightRemapableData;
extern XPLMDataRef AprLightRemapableData, RevLightRemapableData;

extern XPLMDataRef ApLightFlashRemapableData, HdgLightFlashRemapableData;
extern XPLMDataRef NavLightVorlocFlashRemapableData, NavLightLnavFlashRemapableData;
extern XPLMDataRef IasLightFlashRemapableData;
extern XPLMDataRef AltLightFlashRemapableData, VsLightFlashRemapableData;
extern XPLMDataRef AprLightFlashRemapableData, RevLightFlashRemapableData;

extern XPLMDataRef HsiSelector;

extern XPLMMenuID      MultiMenu;
extern XPLMMenuID      MultiMenuId;
extern XPLMMenuID      Frp;
extern XPLMMenuID      MHdg;

extern XPWidgetID	MultiSpeed1CheckWidget[50];
extern XPWidgetID	MultiSpeed2CheckWidget[50];
extern XPWidgetID	MultiSpeed3CheckWidget[50];
extern XPWidgetID	MultiSpeed4CheckWidget[50];
extern XPWidgetID	MultiSpeed5CheckWidget[50];
extern XPWidgetID	MultiTrimSpeed1CheckWidget[50];
extern XPWidgetID	MultiTrimSpeed2CheckWidget[50];
extern XPWidgetID	MultiTrimSpeed3CheckWidget[50];
extern XPWidgetID	MultiAt0CheckWidget[50];
extern XPWidgetID	MultiAt1CheckWidget[50];

// **************** Multi Panel variables *******************
extern int multifd;
extern int numadf;
extern int loaded737;
extern int trimspeed, multispeed, autothrottleswitchenable, autothrottleswitcharmedvalue;

extern int apbuttonremap, hdgbuttonremap, navbuttonremap, iasbuttonremap;
extern int altbuttonremap, vsbuttonremap, aprbuttonremap, revbuttonremap;
extern int lightdatareferencetype;

extern int aplightdata, hdglightdata, navlightvorlocdata, navlightlnavdata;
extern int iaslightdata, altlightdata, vslightdata, aprlightdata, revlightdata;

extern int aplightflashdata, hdglightflashdata, navlightflashvorlocdata, navlightflashlnavdata;
extern int iaslightflashdata,altlightflashdata, vslightflashdata, aprlightflashdata, revlightflashdata;

extern int altswitchremap, vsswitchremap, iasswitchremap;
extern int hdgswitchremap, crsswitchremap;

extern int attrswitchremap;

extern int iasismachremap, iasismachvalue;

extern int trimupremap, trimdnremap;

extern int xpanelsfnbutton;
extern int xpanelscrstoggle;
extern int multi_auto_mul;

extern string ap_button_remapable, hdg_button_remapable, nav_button_vorloc_remapable, nav_button_lnav_remapable;
extern string ias_button_remapable, ias_changeover_button_remapable, alt_button_remapable, vs_button_remapable;
extern string apr_button_remapable, rev_button_remapable;

extern string ap_button_data_remapable, hdg_button_data_remapable, nav_button_data_vorloc_remapable, nav_button_data_lnav_remapable;
extern string ias_button_data_remapable, ias_changeover_button_data_remapable, alt_button_data_remapable, vs_button_data_remapable;
extern string apr_button_data_remapable, rev_button_data_remapable;

extern string ap_light_remapable, hdg_light_remapable, nav_light_vorloc_remapable, nav_light_lnav_remapable;
extern string ias_light_remapable, alt_light_remapable, vs_light_remapable, apr_light_remapable, rev_light_remapable;

extern string ap_light_flash_remapable, hdg_light_flash_remapable, nav_light_vorloc_flash_remapable, nav_light_lnav_flash_remapable;
extern string ias_light_flash_remapable, alt_light_flash_remapable, vs_light_flash_remapable, apr_light_flash_remapable, rev_light_flash_remapable;

extern string alt_switch_up_remapable, alt_switch_dn_remapable;
extern string vs_switch_up_remapable, vs_switch_dn_remapable;
extern string ias_switch_up_remapable, ias_switch_dn_remapable;
extern string hdg_switch_up_remapable, hdg_switch_dn_remapable;
extern string crs_switch_up_remapable, crs_switch_dn_remapable;

extern string attr_switch_remapable;


extern string ias_ismach_remapable;

extern string alt_switch_data_remapable;
extern string vs_switch_data_remapable;
extern string ias_switch_data_remapable;
extern string hdg_switch_data_remapable;
extern string crs_switch_data_remapable;

extern string ap_vs_up_remapable, ap_vs_dn_remapable;
extern string trim_up_remapable, trim_dn_remapable;

extern hid_device *multihandle;

// ****************  End Multi Panel Section  ***************************

// **************************************************************************

// ****************  Start Switch Panel Section  ***************************

// ************ Switch Panel Command Ref ***************
extern XPLMCommandRef ClFlOpn, ClFlCls, PtHtOn, PtHtOff;
extern XPLMCommandRef PtHt0On, PtHt0Off, PtHt1On, PtHt1Off;

extern XPLMCommandRef AvLtOn, AvLtOff, BatOn, BatOff;
extern XPLMCommandRef LnLtOn, LnLtOff, TxLtOn, TxLtOff;
extern XPLMCommandRef StLtOn, StLtOff, NvLtOn, NvLtOff;
extern XPLMCommandRef BcLtOn, BcLtOff, GearUp, GearDn;

extern XPLMCommandRef MagOffSwitchOnCmd, MagOffSwitchOffCmd;
extern XPLMCommandRef MagRightSwitchOnCmd, MagRightSwitchOffCmd;
extern XPLMCommandRef MagLeftSwitchOnCmd, MagLeftSwitchOffCmd;
extern XPLMCommandRef MagBothSwitchOnCmd, MagBothSwitchOffCmd;
extern XPLMCommandRef MagStartSwitchOnCmd, MagStartSwitchOffCmd;

extern XPLMCommandRef BatMasterSwitchOnCmd, BatMasterSwitchOffCmd;



extern XPLMCommandRef AltMasterSwitchOnCmd, AltMasterSwitchOffCmd;



extern XPLMCommandRef AvMasterSwitchOnCmd, AvMasterSwitchOffCmd;




extern XPLMCommandRef FuelPumpOnCmd, FuelPumpOffCmd;
extern XPLMCommandRef FuelPump2OnCmd, FuelPump2OffCmd;
extern XPLMCommandRef FuelPump3OnCmd, FuelPump3OffCmd;
extern XPLMCommandRef FuelPump4OnCmd, FuelPump4OffCmd;

extern XPLMCommandRef DeiceOnCmd, DeiceOffCmd;
extern XPLMCommandRef DeiceOnCmd2, DeiceOffCmd2;
extern XPLMCommandRef DeiceOnCmd3, DeiceOffCmd3;
extern XPLMCommandRef DeiceOnCmd4, DeiceOffCmd4;
extern XPLMCommandRef DeiceOnCmd5, DeiceOffCmd5;
extern XPLMCommandRef DeiceOnCmd6, DeiceOffCmd6;
extern XPLMCommandRef DeiceOnCmd7, DeiceOffCmd7;
extern XPLMCommandRef DeiceOnCmd8, DeiceOffCmd8;

extern XPLMCommandRef PitotHeatOnCmd, PitotHeatOffCmd;
extern XPLMCommandRef Pitot2HeatOnCmd, Pitot2HeatOffCmd;

extern XPLMCommandRef GearUpOnCmd, GearUpOffCmd;
extern XPLMCommandRef GearDnOnCmd, GearDnOffCmd;

extern XPLMCommandRef CowlFlapsOpenCmd, CowlFlapsCloseCmd;
extern XPLMCommandRef Cowl2FlapsOpenCmd, Cowl2FlapsCloseCmd;
extern XPLMCommandRef Cowl3FlapsOpenCmd, Cowl3FlapsCloseCmd;
extern XPLMCommandRef Cowl4FlapsOpenCmd, Cowl4FlapsCloseCmd;

extern XPLMCommandRef PanelLightsOnCmd, PanelLightsOffCmd;
extern XPLMCommandRef BeaconLightsOnCmd, BeaconLightsOffCmd;
extern XPLMCommandRef NavLightsOnCmd, NavLightsOffCmd;
extern XPLMCommandRef StrobeLightsOnCmd, StrobeLightsOffCmd;
extern XPLMCommandRef TaxiLightsOnCmd, TaxiLightsOffCmd;
extern XPLMCommandRef LandingLightsOnCmd, LandingLightsOffCmd;

extern XPLMCommandRef MagOff1, MagOff2, MagOff3, MagOff4;
extern XPLMCommandRef MagOff5, MagOff6, MagOff7, MagOff8;

extern XPLMCommandRef MagLeft1, MagLeft2, MagLeft3, MagLeft4;
extern XPLMCommandRef MagLeft5, MagLeft6, MagLeft7, MagLeft8;

extern XPLMCommandRef MagRight1, MagRight2, MagRight3, MagRight4;
extern XPLMCommandRef MagRight5, MagRight6, MagRight7, MagRight8;

extern XPLMCommandRef MagBoth1, MagBoth2, MagBoth3, MagBoth4;
extern XPLMCommandRef MagBoth5, MagBoth6, MagBoth7, MagBoth8;

extern XPLMCommandRef EngStart1, EngStart2, EngStart3, EngStart4;
extern XPLMCommandRef EngStart5, EngStart6, EngStart7, EngStart8;

extern XPLMCommandRef BatOn1, BatOn2, BatOff1, BatOff2;

extern XPLMCommandRef GenOn1, GenOn2, GenOn3, GenOn4;
extern XPLMCommandRef GenOn5, GenOn6, GenOn7, GenOn8;

extern XPLMCommandRef GenOff1, GenOff2, GenOff3, GenOff4;
extern XPLMCommandRef GenOff5, GenOff6, GenOff7, GenOff8;

extern XPLMCommandRef FuelPumpOn1, FuelPumpOn2, FuelPumpOn3, FuelPumpOn4;
extern XPLMCommandRef FuelPumpOn5, FuelPumpOn6, FuelPumpOn7, FuelPumpOn8;

extern XPLMCommandRef FuelPumpOff1, FuelPumpOff2, FuelPumpOff3, FuelPumpOff4;
extern XPLMCommandRef FuelPumpOff5, FuelPumpOff6, FuelPumpOff7, FuelPumpOff8;


// ************** Switch Panel Data Ref ******************
extern XPLMDataRef BatNum, GenNum, EngNum;
extern XPLMDataRef BatArrayOnDR, IgnSwitchArray;
extern XPLMDataRef EngnMixt, IgniterOn;
extern XPLMDataRef AcfEnType;

extern XPLMDataRef CowlFlaps, CockpitLights, AntiIce;
extern XPLMDataRef GearRetract, OnGround, LandingGearStatus;
extern XPLMDataRef Gear1Fail, Gear2Fail, Gear3Fail;

extern XPLMDataRef MagOffSwitchData, MagOff2SwitchData;
extern XPLMDataRef MagOff3SwitchData, MagOff4SwitchData;
extern XPLMDataRef MagOff5SwitchData, MagOff6SwitchData;
extern XPLMDataRef MagOff7SwitchData, MagOff8SwitchData;
extern XPLMDataRef MagOff9SwitchData, MagOff10SwitchData;

extern XPLMDataRef MagRightSwitchData, MagRight2SwitchData;
extern XPLMDataRef MagRight3SwitchData, MagRight4SwitchData;
extern XPLMDataRef MagRight5SwitchData, MagRight6SwitchData;
extern XPLMDataRef MagRight7SwitchData, MagRight8SwitchData;
extern XPLMDataRef MagRight9SwitchData, MagRight10SwitchData;

extern XPLMDataRef MagLeftSwitchData, MagLeft2SwitchData;
extern XPLMDataRef MagLeft3SwitchData, MagLeft4SwitchData;
extern XPLMDataRef MagLeft5SwitchData, MagLeft6SwitchData;
extern XPLMDataRef MagLeft7SwitchData, MagLeft8SwitchData;
extern XPLMDataRef MagLeft9SwitchData, MagLeft10SwitchData;

extern XPLMDataRef MagBothSwitchData, MagBoth2SwitchData;
extern XPLMDataRef MagBoth3SwitchData, MagBoth4SwitchData;
extern XPLMDataRef MagBoth5SwitchData, MagBoth6SwitchData;
extern XPLMDataRef MagBoth7SwitchData, MagBoth8SwitchData;
extern XPLMDataRef MagBoth9SwitchData, MagBoth10SwitchData;

extern XPLMDataRef MagStartSwitchData, MagStart2SwitchData;
extern XPLMDataRef MagStart3SwitchData, MagStart4SwitchData;
extern XPLMDataRef MagStart5SwitchData, MagStart6SwitchData;
extern XPLMDataRef MagStart7SwitchData, MagStart8SwitchData;
extern XPLMDataRef MagStart9SwitchData, MagStart10SwitchData;


extern XPLMDataRef BatMasterSwitchData, Bat2MasterSwitchData;
extern XPLMDataRef Bat3MasterSwitchData, Bat4MasterSwitchData;
extern XPLMDataRef Bat5MasterSwitchData, Bat6MasterSwitchData;
extern XPLMDataRef Bat7MasterSwitchData, Bat8MasterSwitchData;

extern XPLMDataRef AltMasterSwitchData, Alt2MasterSwitchData;
extern XPLMDataRef Alt3MasterSwitchData, Alt4MasterSwitchData;
extern XPLMDataRef Alt5MasterSwitchData, Alt6MasterSwitchData;
extern XPLMDataRef Alt7MasterSwitchData, Alt8MasterSwitchData;

extern XPLMDataRef AvMasterSwitchData, Av2MasterSwitchData;
extern XPLMDataRef Av3MasterSwitchData, Av4MasterSwitchData;
extern XPLMDataRef Av5MasterSwitchData, Av6MasterSwitchData;
extern XPLMDataRef Av7MasterSwitchData, Av8MasterSwitchData;

extern XPLMDataRef FuelPumpSwitchData, FuelPump2SwitchData;
extern XPLMDataRef FuelPump3SwitchData, FuelPump4SwitchData;
extern XPLMDataRef FuelPump5SwitchData, FuelPump6SwitchData;
extern XPLMDataRef FuelPump7SwitchData, FuelPump8SwitchData;

extern XPLMDataRef DeiceSwitchData;
extern XPLMDataRef Deice2SwitchData;
extern XPLMDataRef Deice3SwitchData;
extern XPLMDataRef Deice4SwitchData;
extern XPLMDataRef Deice5SwitchData;
extern XPLMDataRef Deice6SwitchData;
extern XPLMDataRef Deice7SwitchData;
extern XPLMDataRef Deice8SwitchData;

extern XPLMDataRef PitotHeatSwitchData, Pitot2HeatSwitchData;
extern XPLMDataRef Pitot3HeatSwitchData, Pitot4HeatSwitchData;
extern XPLMDataRef Pitot5HeatSwitchData, Pitot6HeatSwitchData;
extern XPLMDataRef Pitot7HeatSwitchData, Pitot8HeatSwitchData;


extern XPLMDataRef GearUpData;
extern XPLMDataRef GearDnData;

extern XPLMDataRef CowlFlapsData, Cowl2FlapsData;
extern XPLMDataRef Cowl3FlapsData, Cowl4FlapsData;
extern XPLMDataRef Cowl5FlapsData, Cowl6FlapsData;
extern XPLMDataRef Cowl7FlapsData, Cowl8FlapsData;

extern XPLMDataRef PanelLightsData, PanelLights2Data;
extern XPLMDataRef PanelLights3Data, PanelLights4Data;
extern XPLMDataRef PanelLights5Data, PanelLights6Data;
extern XPLMDataRef PanelLights7Data, PanelLights8Data;

extern XPLMDataRef BeaconLightsData, BeaconLights2Data;
extern XPLMDataRef BeaconLights3Data, BeaconLights4Data;

extern XPLMDataRef NavLightsData, NavLights2Data;
extern XPLMDataRef NavLights3Data, NavLights4Data;

extern XPLMDataRef StrobeLightsData, StrobeLights2Data;
extern XPLMDataRef StrobeLights3Data, StrobeLights4Data;

extern XPLMDataRef TaxiLightsData, TaxiLights2Data;
extern XPLMDataRef TaxiLights3Data, TaxiLights4Data;

extern XPLMDataRef LandingLightsData, LandingLights2Data;
extern XPLMDataRef LandingLights3Data, LandingLights4Data;

extern XPLMDataRef	SwitchStartOffOwnedDataRef, SwitchStartRightOwnedDataRef;
extern XPLMDataRef	SwitchStartLeftOwnedDataRef, SwitchStartBothOwnedDataRef;
extern XPLMDataRef	SwitchStartStartOwnedDataRef;
extern XPLMDataRef	SwitchBatOwnedDataRef, SwitchAltOwnedDataRef;
extern XPLMDataRef	SwitchAvOwnedDataRef, SwitchFuelOwnedDataRef;
extern XPLMDataRef	SwitchDiceOwnedDataRef, SwitchPitotOwnedDataRef;
extern XPLMDataRef	SwitchGearUpOwnedDataRef, SwitchGearDnOwnedDataRef;
extern XPLMDataRef	SwitchCowlOwnedDataRef, SwitchPanelOwnedDataRef;
extern XPLMDataRef	SwitchBeaconOwnedDataRef, SwitchNavOwnedDataRef;
extern XPLMDataRef	SwitchStrobeOwnedDataRef, SwitchTaxiOwnedDataRef;
extern XPLMDataRef	SwitchLandingOwnedDataRef;

extern int	SwitchStartOffPositionGetDataiCallback(void * inRefcon);
extern void	SwitchStartOffPositionSetDataiCallback(void * inRefcon, int SwitchStartOffPosition);

extern int	SwitchStartRightPositionGetDataiCallback(void * inRefcon);
extern void	SwitchStartRightPositionSetDataiCallback(void * inRefcon, int SwitchStartRightPosition);

extern int	SwitchStartLeftPositionGetDataiCallback(void * inRefcon);
extern void	SwitchStartLeftPositionSetDataiCallback(void * inRefcon, int SwitchStartLeftPosition);

extern int	SwitchStartBothPositionGetDataiCallback(void * inRefcon);
extern void	SwitchStartBothPositionSetDataiCallback(void * inRefcon, int SwitchStartBothPosition);

extern int	SwitchStartStartPositionGetDataiCallback(void * inRefcon);
extern void	SwitchStartStartPositionSetDataiCallback(void * inRefcon, int SwitchStartStartPosition);

extern int	SwitchBatPositionGetDataiCallback(void * inRefcon);
extern void	SwitchBatPositionSetDataiCallback(void * inRefcon, int SwitchBatPosition);

extern int	SwitchAltPositionGetDataiCallback(void * inRefcon);
extern void	SwitchAltPositionSetDataiCallback(void * inRefcon, int SwitchAltPosition);

extern int	SwitchAvPositionGetDataiCallback(void * inRefcon);
extern void	SwitchAvPositionSetDataiCallback(void * inRefcon, int SwitchAvPosition);

extern int	SwitchFuelPositionGetDataiCallback(void * inRefcon);
extern void	SwitchFuelPositionSetDataiCallback(void * inRefcon, int SwitchFuelPosition);

extern int	SwitchDicePositionGetDataiCallback(void * inRefcon);
extern void	SwitchDicePositionSetDataiCallback(void * inRefcon, int SwitchDicePosition);

extern int	SwitchPitotPositionGetDataiCallback(void * inRefcon);
extern void	SwitchPitotPositionSetDataiCallback(void * inRefcon, int SwitchPitotPosition);

extern int	SwitchGearUpPositionGetDataiCallback(void * inRefcon);
extern void	SwitchGearUpPositionSetDataiCallback(void * inRefcon, int SwitchGearUpPosition);

extern int	SwitchGearDnPositionGetDataiCallback(void * inRefcon);
extern void	SwitchGearDnPositionSetDataiCallback(void * inRefcon, int SwitchGearDnPosition);

extern int	SwitchCowlPositionGetDataiCallback(void * inRefcon);
extern void	SwitchCowlPositionSetDataiCallback(void * inRefcon, int SwitchCowPosition);

extern int	SwitchPanelPositionGetDataiCallback(void * inRefcon);
extern void	SwitchPanelPositionSetDataiCallback(void * inRefcon, int SwitchPanelPosition);

extern int	SwitchBeaconPositionGetDataiCallback(void * inRefcon);
extern void	SwitchBeaconPositionSetDataiCallback(void * inRefcon, int SwitchBeaconPosition);

extern int	SwitchNavPositionGetDataiCallback(void * inRefcon);
extern void	SwitchNavPositionSetDataiCallback(void * inRefcon, int SwitchNavPosition);

extern int	SwitchStrobePositionGetDataiCallback(void * inRefcon);
extern void	SwitchStrobePositionSetDataiCallback(void * inRefcon, int SwitchStrobePosition);

extern int	SwitchTaxiPositionGetDataiCallback(void * inRefcon);
extern void	SwitchTaxiPositionSetDataiCallback(void * inRefcon, int SwitchTaxiPosition);

extern int	SwitchLandingPositionGetDataiCallback(void * inRefcon);
extern void	SwitchLandingPositionSetDataiCallback(void * inRefcon, int SwitchLandingPosition);



extern XPLMMenuID      SwitchMenu;
extern XPLMMenuID      SwitchMenuId;
extern XPWidgetID      SwitchEnableCheckWidget[50];
extern XPWidgetID      SwitchDisableCheckWidget[50];
extern XPWidgetID      SwitchRemapCheckWidget[50];
extern XPWidgetID      SwitchBatAltCheckWidget[50];
extern XPWidgetID      SwitchAltBatCheckWidget[50];
extern XPWidgetID	   SwitchStartSwitchOldCheckWidget[50];
extern XPWidgetID	   SwitchStartSwitchNewCheckWidget[50];

// ***************** Switch Panel variables ********************
extern int switchfd;

extern int magoffswitchenable, magrightswitchenable, magleftswitchenable;
extern int magbothswitchenable, magstartswitchenable;
extern int batmasterswitchenable, altmasterswitchenable;
extern int avionicsmasterswitchenable, fuelpumpswitchenable;
extern int deiceswitchenable, pitotheatswitchenable;
extern int landinggearknobupenable, landinggearknobdnenable;
extern int cowlflapsenable, panellightswitchenable;
extern int beaconlightswitchenable, navlightswitchenable;
extern int strobelightswitchenable, taxilightswitchenable;
extern int landinglightswitchenable, bataltinverse;
extern int starterswitchenable;

extern int mag_off_switch_data_on_value, mag_off_switch_data_off_value;
extern int mag_off2_switch_data_on_value, mag_off2_switch_data_off_value;
extern int mag_off3_switch_data_on_value, mag_off3_switch_data_off_value;
extern int mag_off4_switch_data_on_value, mag_off4_switch_data_off_value;
extern int mag_off5_switch_data_on_value, mag_off5_switch_data_off_value;
extern int mag_off6_switch_data_on_value, mag_off6_switch_data_off_value;
extern int mag_off7_switch_data_on_value, mag_off7_switch_data_off_value;
extern int mag_off8_switch_data_on_value, mag_off8_switch_data_off_value;
extern int mag_off9_switch_data_on_value, mag_off9_switch_data_off_value;
extern int mag_off10_switch_data_on_value, mag_off10_switch_data_off_value;

extern int mag_right_switch_data_on_value, mag_right_switch_data_off_value;
extern int mag_right2_switch_data_on_value, mag_right2_switch_data_off_value;
extern int mag_right3_switch_data_on_value, mag_right3_switch_data_off_value;
extern int mag_right4_switch_data_on_value, mag_right4_switch_data_off_value;
extern int mag_right5_switch_data_on_value, mag_right5_switch_data_off_value;
extern int mag_right6_switch_data_on_value, mag_right6_switch_data_off_value;
extern int mag_right7_switch_data_on_value, mag_right7_switch_data_off_value;
extern int mag_right8_switch_data_on_value, mag_right8_switch_data_off_value;
extern int mag_right9_switch_data_on_value, mag_right9_switch_data_off_value;
extern int mag_right10_switch_data_on_value, mag_right10_switch_data_off_value;

extern int mag_left_switch_data_on_value, mag_left_switch_data_off_value;
extern int mag_left2_switch_data_on_value, mag_left2_switch_data_off_value;
extern int mag_left3_switch_data_on_value, mag_left3_switch_data_off_value;
extern int mag_left4_switch_data_on_value, mag_left4_switch_data_off_value;
extern int mag_left5_switch_data_on_value, mag_left5_switch_data_off_value;
extern int mag_left6_switch_data_on_value, mag_left6_switch_data_off_value;
extern int mag_left7_switch_data_on_value, mag_left7_switch_data_off_value;
extern int mag_left8_switch_data_on_value, mag_left8_switch_data_off_value;
extern int mag_left9_switch_data_on_value, mag_left9_switch_data_off_value;
extern int mag_left10_switch_data_on_value, mag_left10_switch_data_off_value;

extern int mag_both_switch_data_on_value, mag_both_switch_data_off_value;
extern int mag_both2_switch_data_on_value, mag_both2_switch_data_off_value;
extern int mag_both3_switch_data_on_value, mag_both3_switch_data_off_value;
extern int mag_both4_switch_data_on_value, mag_both4_switch_data_off_value;
extern int mag_both5_switch_data_on_value, mag_both5_switch_data_off_value;
extern int mag_both6_switch_data_on_value, mag_both6_switch_data_off_value;
extern int mag_both7_switch_data_on_value, mag_both7_switch_data_off_value;
extern int mag_both8_switch_data_on_value, mag_both8_switch_data_off_value;
extern int mag_both9_switch_data_on_value, mag_both9_switch_data_off_value;
extern int mag_both10_switch_data_on_value, mag_both10_switch_data_off_value;

extern int mag_start_switch_data_on_value, mag_start_switch_data_off_value;
extern int mag_start2_switch_data_on_value, mag_start2_switch_data_off_value;
extern int mag_start3_switch_data_on_value, mag_start3_switch_data_off_value;
extern int mag_start4_switch_data_on_value, mag_start4_switch_data_off_value;
extern int mag_start5_switch_data_on_value, mag_start5_switch_data_off_value;
extern int mag_start6_switch_data_on_value, mag_start6_switch_data_off_value;
extern int mag_start7_switch_data_on_value, mag_start7_switch_data_off_value;
extern int mag_start8_switch_data_on_value, mag_start8_switch_data_off_value;
extern int mag_start9_switch_data_on_value, mag_start9_switch_data_off_value;
extern int mag_start10_switch_data_on_value, mag_start10_switch_data_off_value;


extern int bat_master_switch_data_on_value, bat_master_switch_data_off_value;
extern int bat2_master_switch_data_on_value, bat2_master_switch_data_off_value;
extern int bat3_master_switch_data_on_value, bat3_master_switch_data_off_value;
extern int bat4_master_switch_data_on_value, bat4_master_switch_data_off_value;
extern int bat5_master_switch_data_on_value, bat5_master_switch_data_off_value;
extern int bat6_master_switch_data_on_value, bat6_master_switch_data_off_value;
extern int bat7_master_switch_data_on_value, bat7_master_switch_data_off_value;
extern int bat8_master_switch_data_on_value, bat8_master_switch_data_off_value;

extern int alt_master_switch_data_on_value, alt_master_switch_data_off_value;
extern int alt2_master_switch_data_on_value, alt2_master_switch_data_off_value;
extern int alt3_master_switch_data_on_value, alt3_master_switch_data_off_value;
extern int alt4_master_switch_data_on_value, alt4_master_switch_data_off_value;
extern int alt5_master_switch_data_on_value, alt5_master_switch_data_off_value;
extern int alt6_master_switch_data_on_value, alt6_master_switch_data_off_value;
extern int alt7_master_switch_data_on_value, alt7_master_switch_data_off_value;
extern int alt8_master_switch_data_on_value, alt8_master_switch_data_off_value;

extern int av_master_switch_data_on_value, av_master_switch_data_off_value;
extern int av2_master_switch_data_on_value, av2_master_switch_data_off_value;
extern int av3_master_switch_data_on_value, av3_master_switch_data_off_value;
extern int av4_master_switch_data_on_value, av4_master_switch_data_off_value;
extern int av5_master_switch_data_on_value, av5_master_switch_data_off_value;
extern int av6_master_switch_data_on_value, av6_master_switch_data_off_value;
extern int av7_master_switch_data_on_value, av7_master_switch_data_off_value;
extern int av8_master_switch_data_on_value, av8_master_switch_data_off_value;

extern int fuel_pump_switch_data_on_value, fuel_pump_switch_data_off_value;
extern int fuel_pump2_switch_data_on_value, fuel_pump2_switch_data_off_value;
extern int fuel_pump3_switch_data_on_value, fuel_pump3_switch_data_off_value;
extern int fuel_pump4_switch_data_on_value, fuel_pump4_switch_data_off_value;
extern int fuel_pump5_switch_data_on_value, fuel_pump5_switch_data_off_value;
extern int fuel_pump6_switch_data_on_value, fuel_pump6_switch_data_off_value;
extern int fuel_pump7_switch_data_on_value, fuel_pump7_switch_data_off_value;
extern int fuel_pump8_switch_data_on_value, fuel_pump8_switch_data_off_value;


extern int deice_switch_data_on_value, deice_switch_data_off_value;
extern int deice2_switch_data_on_value, deice2_switch_data_off_value;
extern int deice3_switch_data_on_value, deice3_switch_data_off_value;
extern int deice4_switch_data_on_value, deice4_switch_data_off_value;
extern int deice5_switch_data_on_value, deice5_switch_data_off_value;
extern int deice6_switch_data_on_value, deice6_switch_data_off_value;
extern int deice7_switch_data_on_value, deice7_switch_data_off_value;
extern int deice8_switch_data_on_value, deice8_switch_data_off_value;

extern int pitot_heat_switch_data_on_value, pitot_heat_switch_data_off_value;
extern int pitot2_heat_switch_data_on_value, pitot2_heat_switch_data_off_value;
extern int pitot3_heat_switch_data_on_value, pitot3_heat_switch_data_off_value;
extern int pitot4_heat_switch_data_on_value, pitot4_heat_switch_data_off_value;
extern int pitot5_heat_switch_data_on_value, pitot5_heat_switch_data_off_value;
extern int pitot6_heat_switch_data_on_value, pitot6_heat_switch_data_off_value;
extern int pitot7_heat_switch_data_on_value, pitot7_heat_switch_data_off_value;
extern int pitot8_heat_switch_data_on_value, pitot8_heat_switch_data_off_value;

extern int gear_switch_up_data_on_value, gear_switch_up_data_off_value;
extern int gear_switch_down_data_on_value, gear_switch_down_data_off_value;

extern int cowl_flaps_data_on_value, cowl_flaps_data_off_value;
extern int cowl2_flaps_data_on_value, cowl2_flaps_data_off_value;
extern int cowl3_flaps_data_on_value, cowl3_flaps_data_off_value;
extern int cowl4_flaps_data_on_value, cowl4_flaps_data_off_value;
extern int cowl5_flaps_data_on_value, cowl5_flaps_data_off_value;
extern int cowl6_flaps_data_on_value, cowl6_flaps_data_off_value;
extern int cowl7_flaps_data_on_value, cowl7_flaps_data_off_value;
extern int cowl8_flaps_data_on_value, cowl8_flaps_data_off_value;


extern int panel_lights_switch_data_on_value, panel_lights_switch_data_off_value;
extern int panel_lights_switch2_data_on_value, panel_lights_switch2_data_off_value;
extern int panel_lights_switch3_data_on_value, panel_lights_switch3_data_off_value;
extern int panel_lights_switch4_data_on_value, panel_lights_switch4_data_off_value;
extern int panel_lights_switch5_data_on_value, panel_lights_switch5_data_off_value;
extern int panel_lights_switch6_data_on_value, panel_lights_switch6_data_off_value;
extern int panel_lights_switch7_data_on_value, panel_lights_switch7_data_off_value;
extern int panel_lights_switch8_data_on_value, panel_lights_switch8_data_off_value;

extern int beacon_lights_switch_data_on_value, beacon_lights_switch_data_off_value;
extern int beacon_lights_switch2_data_on_value, beacon_lights_switch2_data_off_value;
extern int beacon_lights_switch3_data_on_value, beacon_lights_switch3_data_off_value;
extern int beacon_lights_switch4_data_on_value, beacon_lights_switch4_data_off_value;

extern int nav_lights_switch_data_on_value, nav_lights_switch_data_off_value;
extern int nav_lights_switch2_data_on_value, nav_lights_switch2_data_off_value;
extern int nav_lights_switch3_data_on_value, nav_lights_switch3_data_off_value;
extern int nav_lights_switch4_data_on_value, nav_lights_switch4_data_off_value;

extern int strobe_lights_switch_data_on_value, strobe_lights_switch_data_off_value;
extern int strobe_lights_switch2_data_on_value, strobe_lights_switch2_data_off_value;
extern int strobe_lights_switch3_data_on_value, strobe_lights_switch3_data_off_value;
extern int strobe_lights_switch4_data_on_value, strobe_lights_switch4_data_off_value;

extern int taxi_lights_switch_data_on_value, taxi_lights_switch_data_off_value;
extern int taxi_lights_switch2_data_on_value, taxi_lights_switch2_data_off_value;
extern int taxi_lights_switch3_data_on_value, taxi_lights_switch3_data_off_value;
extern int taxi_lights_switch4_data_on_value, taxi_lights_switch4_data_off_value;

extern int landing_lights_switch_data_on_value, landing_lights_switch_data_off_value;
extern int landing_lights_switch2_data_on_value, landing_lights_switch2_data_off_value;
extern int landing_lights_switch3_data_on_value, landing_lights_switch3_data_off_value;
extern int landing_lights_switch4_data_on_value, landing_lights_switch4_data_off_value;

extern float panel_lights_switch_dataf_on_value, panel_lights_switch_dataf_off_value;
extern float panel_lights_switch2_dataf_on_value, panel_lights_switch2_dataf_off_value;
extern float panel_lights_switch3_dataf_on_value, panel_lights_switch3_dataf_off_value;
extern float panel_lights_switch4_dataf_on_value, panel_lights_switch4_dataf_off_value;
extern float panel_lights_switch5_dataf_on_value, panel_lights_switch5_dataf_off_value;
extern float panel_lights_switch6_dataf_on_value, panel_lights_switch6_dataf_off_value;
extern float panel_lights_switch7_dataf_on_value, panel_lights_switch7_dataf_off_value;
extern float panel_lights_switch8_dataf_on_value, panel_lights_switch8_dataf_off_value;

extern float beacon_lights_switch_dataf_on_value, beacon_lights_switch_dataf_off_value;
extern float beacon_lights_switch2_dataf_on_value, beacon_lights_switch2_dataf_off_value;
extern float beacon_lights_switch3_dataf_on_value, beacon_lights_switch3_dataf_off_value;
extern float beacon_lights_switch4_dataf_on_value, beacon_lights_switch4_dataf_off_value;

extern float nav_lights_switch_dataf_on_value, nav_lights_switch_dataf_off_value;
extern float nav_lights_switch2_dataf_on_value, nav_lights_switch2_dataf_off_value;
extern float nav_lights_switch3_dataf_on_value, nav_lights_switch3_dataf_off_value;
extern float nav_lights_switch4_dataf_on_value, nav_lights_switch4_dataf_off_value;

extern float strobe_lights_switch_dataf_on_value, strobe_lights_switch_dataf_off_value;
extern float strobe_lights_switch2_dataf_on_value, strobe_lights_switch2_dataf_off_value;
extern float strobe_lights_switch3_dataf_on_value, strobe_lights_switch3_dataf_off_value;
extern float strobe_lights_switch4_dataf_on_value, strobe_lights_switch4_dataf_off_value;

extern float taxi_lights_switch_dataf_on_value, taxi_lights_switch_dataf_off_value;
extern float taxi_lights_switch2_dataf_on_value, taxi_lights_switch2_dataf_off_value;
extern float taxi_lights_switch3_dataf_on_value, taxi_lights_switch3_dataf_off_value;
extern float taxi_lights_switch4_dataf_on_value, taxi_lights_switch4_dataf_off_value;

extern float landing_lights_switch_dataf_on_value, landing_lights_switch_dataf_off_value;
extern float landing_lights_switch2_dataf_on_value, landing_lights_switch2_dataf_off_value;
extern float landing_lights_switch3_dataf_on_value, landing_lights_switch3_dataf_off_value;
extern float landing_lights_switch4_dataf_on_value, landing_lights_switch4_dataf_off_value;

extern string mag_off_switch_on, mag_off_switch_off, mag_off_switch_data;
extern string mag_off2_switch_on, mag_off2_switch_off, mag_off2_switch_data;
extern string mag_off3_switch_on, mag_off3_switch_off, mag_off3_switch_data;
extern string mag_off4_switch_on, mag_off4_switch_off, mag_off4_switch_data;
extern string mag_off5_switch_on, mag_off5_switch_off, mag_off5_switch_data;
extern string mag_off6_switch_on, mag_off6_switch_off, mag_off6_switch_data;
extern string mag_off7_switch_on, mag_off7_switch_off, mag_off7_switch_data;
extern string mag_off8_switch_on, mag_off8_switch_off, mag_off8_switch_data;
extern string mag_off9_switch_on, mag_off9_switch_off, mag_off9_switch_data;
extern string mag_off10_switch_on, mag_off10_switch_off, mag_off10_switch_data;

extern string mag_right_switch_on, mag_right_switch_off, mag_right_switch_data;
extern string mag_right2_switch_on, mag_right2_switch_off, mag_right2_switch_data;
extern string mag_right3_switch_on, mag_right3_switch_off, mag_right3_switch_data;
extern string mag_right4_switch_on, mag_right4_switch_off, mag_right4_switch_data;
extern string mag_right5_switch_on, mag_right5_switch_off, mag_right5_switch_data;
extern string mag_right6_switch_on, mag_right6_switch_off, mag_right6_switch_data;
extern string mag_right7_switch_on, mag_right7_switch_off, mag_right7_switch_data;
extern string mag_right8_switch_on, mag_right8_switch_off, mag_right8_switch_data;
extern string mag_right9_switch_on, mag_right9_switch_off, mag_right9_switch_data;
extern string mag_right10_switch_on, mag_right10_switch_off, mag_right10_switch_data;

extern string mag_left_switch_on, mag_left_switch_off, mag_left_switch_data;
extern string mag_left2_switch_on, mag_left2_switch_off, mag_left2_switch_data;
extern string mag_left3_switch_on, mag_left3_switch_off, mag_left3_switch_data;
extern string mag_left4_switch_on, mag_left4_switch_off, mag_left4_switch_data;
extern string mag_left5_switch_on, mag_left5_switch_off, mag_left5_switch_data;
extern string mag_left6_switch_on, mag_left6_switch_off, mag_left6_switch_data;
extern string mag_left7_switch_on, mag_left7_switch_off, mag_left7_switch_data;
extern string mag_left8_switch_on, mag_left8_switch_off, mag_left8_switch_data;
extern string mag_left9_switch_on, mag_left9_switch_off, mag_left9_switch_data;
extern string mag_left10_switch_on, mag_left10_switch_off, mag_left10_switch_data;

extern string mag_both_switch_on, mag_both_switch_off, mag_both_switch_data;
extern string mag_both2_switch_on, mag_both2_switch_off, mag_both2_switch_data;
extern string mag_both3_switch_on, mag_both3_switch_off, mag_both3_switch_data;
extern string mag_both4_switch_on, mag_both4_switch_off, mag_both4_switch_data;
extern string mag_both5_switch_on, mag_both5_switch_off, mag_both5_switch_data;
extern string mag_both6_switch_on, mag_both6_switch_off, mag_both6_switch_data;
extern string mag_both7_switch_on, mag_both7_switch_off, mag_both7_switch_data;
extern string mag_both8_switch_on, mag_both8_switch_off, mag_both8_switch_data;
extern string mag_both9_switch_on, mag_both9_switch_off, mag_both9_switch_data;
extern string mag_both10_switch_on, mag_both10_switch_off, mag_both10_switch_data;

extern string mag_start_switch_on, mag_start_switch_off, mag_start_switch_data;
extern string mag_start2_switch_on, mag_start2_switch_off, mag_start2_switch_data;
extern string mag_start3_switch_on, mag_start3_switch_off, mag_start3_switch_data;
extern string mag_start4_switch_on, mag_start4_switch_off, mag_start4_switch_data;
extern string mag_start5_switch_on, mag_start5_switch_off, mag_start5_switch_data;
extern string mag_start6_switch_on, mag_start6_switch_off, mag_start6_switch_data;
extern string mag_start7_switch_on, mag_start7_switch_off, mag_start7_switch_data;
extern string mag_start8_switch_on, mag_start8_switch_off, mag_start8_switch_data;
extern string mag_start9_switch_on, mag_start9_switch_off, mag_start9_switch_data;
extern string mag_start10_switch_on, mag_start10_switch_off, mag_start10_switch_data;


extern string bat_master_switch_on, bat_master_switch_off, bat_master_switch_data;
extern string bat2_master_switch_on, bat2_master_switch_off, bat2_master_switch_data;
extern string bat3_master_switch_on, bat3_master_switch_off, bat3_master_switch_data;
extern string bat4_master_switch_on, bat4_master_switch_off, bat4_master_switch_data;
extern string bat5_master_switch_on, bat5_master_switch_off, bat5_master_switch_data;
extern string bat6_master_switch_on, bat6_master_switch_off, bat6_master_switch_data;
extern string bat7_master_switch_on, bat7_master_switch_off, bat7_master_switch_data;
extern string bat8_master_switch_on, bat8_master_switch_off, bat8_master_switch_data;

extern string alt_master_switch_on, alt_master_switch_off, alt_master_switch_data;
extern string alt2_master_switch_on, alt2_master_switch_off, alt2_master_switch_data;
extern string alt3_master_switch_on, alt3_master_switch_off, alt3_master_switch_data;
extern string alt4_master_switch_on, alt4_master_switch_off, alt4_master_switch_data;
extern string alt5_master_switch_on, alt5_master_switch_off, alt5_master_switch_data;
extern string alt6_master_switch_on, alt6_master_switch_off, alt6_master_switch_data;
extern string alt7_master_switch_on, alt7_master_switch_off, alt7_master_switch_data;
extern string alt8_master_switch_on, alt8_master_switch_off, alt8_master_switch_data;

extern string av_master_switch_on, av_master_switch_off, av_master_switch_data;
extern string av2_master_switch_on, av2_master_switch_off, av2_master_switch_data;
extern string av3_master_switch_on, av3_master_switch_off, av3_master_switch_data;
extern string av4_master_switch_on, av4_master_switch_off, av4_master_switch_data;
extern string av5_master_switch_on, av5_master_switch_off, av5_master_switch_data;
extern string av6_master_switch_on, av6_master_switch_off, av6_master_switch_data;
extern string av7_master_switch_on, av7_master_switch_off, av7_master_switch_data;
extern string av8_master_switch_on, av8_master_switch_off, av8_master_switch_data;

extern string fuel_pump_switch_on, fuel_pump_switch_off, fuel_pump_switch_data;
extern string fuel_pump2_switch_on, fuel_pump2_switch_off, fuel_pump2_switch_data;
extern string fuel_pump3_switch_on, fuel_pump3_switch_off, fuel_pump3_switch_data;
extern string fuel_pump4_switch_on, fuel_pump4_switch_off, fuel_pump4_switch_data;
extern string fuel_pump5_switch_on, fuel_pump5_switch_off, fuel_pump5_switch_data;
extern string fuel_pump6_switch_on, fuel_pump6_switch_off, fuel_pump6_switch_data;
extern string fuel_pump7_switch_on, fuel_pump7_switch_off, fuel_pump7_switch_data;
extern string fuel_pump8_switch_on, fuel_pump8_switch_off, fuel_pump8_switch_data;

extern string deice_switch_on, deice_switch_off, deice_switch_data;
extern string deice2_switch_on, deice2_switch_off, deice2_switch_data;
extern string deice3_switch_on, deice3_switch_off, deice3_switch_data;
extern string deice4_switch_on, deice4_switch_off, deice4_switch_data ;
extern string deice5_switch_on, deice5_switch_off, deice5_switch_data;
extern string deice6_switch_on, deice6_switch_off, deice6_switch_data;
extern string deice7_switch_on, deice7_switch_off, deice7_switch_data;
extern string deice8_switch_on, deice8_switch_off, deice8_switch_data;

extern string pitot_heat_switch_on, pitot_heat_switch_off, pitot_heat_switch_data;
extern string pitot2_heat_switch_on, pitot2_heat_switch_off, pitot2_heat_switch_data;
extern string pitot3_heat_switch_on, pitot3_heat_switch_off, pitot3_heat_switch_data;
extern string pitot4_heat_switch_on, pitot4_heat_switch_off, pitot4_heat_switch_data;
extern string pitot5_heat_switch_on, pitot5_heat_switch_off, pitot5_heat_switch_data;
extern string pitot6_heat_switch_on, pitot6_heat_switch_off, pitot6_heat_switch_data;
extern string pitot7_heat_switch_on, pitot7_heat_switch_off, pitot7_heat_switch_data;
extern string pitot8_heat_switch_on, pitot8_heat_switch_off, pitot8_heat_switch_data;

extern string gear_switch_up_on, gear_switch_up_off, gear_switch_up_data;
extern string gear_switch_down_on, gear_switch_down_off, gear_switch_down_data ;

extern string cowl_flaps_open, cowl_flaps_close, cowl_flaps_data ;
extern string cowl2_flaps_open, cowl2_flaps_close, cowl2_flaps_data;
extern string cowl3_flaps_open, cowl3_flaps_close, cowl3_flaps_data;
extern string cowl4_flaps_open, cowl4_flaps_close, cowl4_flaps_data;
extern string cowl5_flaps_open, cowl5_flaps_close, cowl5_flaps_data;
extern string cowl6_flaps_open, cowl6_flaps_close, cowl6_flaps_data;
extern string cowl7_flaps_open, cowl7_flaps_close, cowl7_flaps_data;
extern string cowl8_flaps_open, cowl8_flaps_close, cowl8_flaps_data;

extern string panel_lights_switch_on, panel_lights_switch_off, panel_lights_switch_data;
extern string panel_lights_switch2_on, panel_lights_switch2_off, panel_lights_switch2_data;
extern string panel_lights_switch3_on, panel_lights_switch3_off, panel_lights_switch3_data;
extern string panel_lights_switch4_on, panel_lights_switch4_off, panel_lights_switch4_data;
extern string panel_lights_switch5_on, panel_lights_switch5_off, panel_lights_switch5_data;
extern string panel_lights_switch6_on, panel_lights_switch6_off, panel_lights_switch6_data;
extern string panel_lights_switch7_on, panel_lights_switch7_off, panel_lights_switch7_data;
extern string panel_lights_switch8_on, panel_lights_switch8_off, panel_lights_switch8_data;

extern string beacon_lights_switch_on, beacon_lights_switch_off, beacon_lights_switch_data;
extern string beacon_lights_switch2_on, beacon_lights_switch2_off, beacon_lights_switch2_data;
extern string beacon_lights_switch3_on, beacon_lights_switch3_off, beacon_lights_switch3_data;
extern string beacon_lights_switch4_on, beacon_lights_switch4_off, beacon_lights_switch4_data;

extern string nav_lights_switch_on, nav_lights_switch_off, nav_lights_switch_data;
extern string nav_lights_switch2_on, nav_lights_switch2_off, nav_lights_switch2_data;
extern string nav_lights_switch3_on, nav_lights_switch3_off, nav_lights_switch3_data;
extern string nav_lights_switch4_on, nav_lights_switc4h_off, nav_lights_switch4_data;

extern string strobe_lights_switch_on, strobe_lights_switch_off, strobe_lights_switch_data;
extern string strobe_lights_switch2_on, strobe_lights_switch2_off, strobe_lights_switch2_data;
extern string strobe_lights_switch3_on, strobe_lights_switch3_off, strobe_lights_switch3_data;
extern string strobe_lights_switch4_on, strobe_lights_switch4_off, strobe_lights_switch4_data;

extern string taxi_lights_switch_on, taxi_lights_switch_off, taxi_lights_switch_data;
extern string taxi_lights_switch2_on, taxi_lights_switch2_off, taxi_lights_switch2_data;
extern string taxi_lights_switch3_on, taxi_lights_switch3_off, taxi_lights_switch3_data;
extern string taxi_lights_switch4_on, taxi_lights_switch4_off, taxi_lights_switch4_data;

extern string landing_lights_switch_on, landing_lights_switch_off, landing_lights_switch_data;
extern string landing_lights_switch2_on, landing_lights_switch2_off, landing_lights_switch2_data;
extern string landing_lights_switch3_on, landing_lights_switch3_off, landing_lights_switch3_data;
extern string landing_lights_switch4_on, landing_lights_switch4_off, landing_lights_switch4_data;

extern int switchloop;

extern float LandingGearDeployRatio[10];
extern hid_device *switchhandle;

// ************** Bip Panel Data Ref ******************
extern XPLMDataRef gTimeSimIsRunningXDataRef;

extern XPLMMenuID      BipMenu;
extern XPLMMenuID      BipMenuId, Bip2MenuId, Bip3MenuId, Bip4MenuId;
extern XPWidgetID      BipWidgetID, Bip2WidgetID, Bip3WidgetID, Bip4WidgetID;

// ***************** Bip Panel variables ********************
extern hid_device *biphandle[4];
extern int bipcnt, biptmpcnt, bipnum;
extern int bipwcscmp0, bipwcscmp1;

void WriteCSVTableToDisk(void);
bool ReadConfigFile(std::string PlaneICAO);

// ***************** Saitek Panel variables ********************

extern int wrgXPlaneVersion;
extern int wrgXPLMVersion;
extern int wrgHostID;


#endif
