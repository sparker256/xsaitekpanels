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
extern int rad1lwrcom1switchremap, rad1lwrcom1actstbybtnremap;
extern int rad1lwrcom2switchremap, rad1lwrcom2actstbybtnremap;
extern int rad1lwrnav1switchremap, rad1lwrnav1actstbybtnremap;
extern int rad1lwrnav2switchremap, rad1lwrnav2actstbybtnremap;

extern int rad2uprcom1switchremap, rad2uprcom1actstbybtnremap;
extern int rad2uprcom2switchremap, rad2uprcom2actstbybtnremap;
extern int rad2uprnav1switchremap, rad2uprnav1actstbybtnremap;
extern int rad2uprnav2switchremap, rad2uprnav2actstbybtnremap;
extern int rad2lwrcom1switchremap, rad2lwrcom1actstbybtnremap;
extern int rad2lwrcom2switchremap, rad2lwrcom2actstbybtnremap;
extern int rad2lwrnav1switchremap, rad2lwrnav1actstbybtnremap;
extern int rad2lwrnav2switchremap, rad2lwrnav2actstbybtnremap;

extern string rad1_upper_com1_corse_up_remapable, rad1_upper_com1_corse_dn_remapable;
extern string rad1_upper_com1_fine_up_remapable, rad1_upper_com1_fine_dn_remapable;
extern string rad1_upper_com1_actstby_btn_remapable;
extern string rad1_upper_com2_corse_up_remapable, rad1_upper_com2_corse_dn_remapable;
extern string rad1_upper_com2_fine_up_remapable, rad1_upper_com2_fine_dn_remapable;
extern string rad1_upper_com2_actstby_btn_remapable;
extern string rad1_upper_nav1_corse_up_remapable, rad1_upper_nav1_corse_dn_remapable;
extern string rad1_upper_nav1_fine_up_remapable, rad1_upper_nav1_fine_dn_remapable;
extern string rad1_upper_nav1_actstby_btn_remapable;
extern string rad1_upper_nav2_corse_up_remapable, rad1_upper_nav2_corse_dn_remapable;
extern string rad1_upper_nav2_fine_up_remapable, rad1_upper_nav2_fine_dn_remapable;
extern string rad1_upper_nav2_actstby_btn_remapable;

extern string rad1_lower_com1_corse_up_remapable, rad1_lower_com1_corse_dn_remapable;
extern string rad1_lower_com1_fine_up_remapable, rad1_lower_com1_fine_dn_remapable;
extern string rad1_lower_com1_actstby_btn_remapable;
extern string rad1_lower_com2_corse_up_remapable, rad1_lower_com2_corse_dn_remapable;
extern string rad1_lower_com2_fine_up_remapable, rad1_lower_com2_fine_dn_remapable;
extern string rad1_lower_com2_actstby_btn_remapable;
extern string rad1_lower_nav1_corse_up_remapable, rad1_lower_nav1_corse_dn_remapable;
extern string rad1_lower_nav1_fine_up_remapable, rad1_lower_nav1_fine_dn_remapable;
extern string rad1_lower_nav1_actstby_btn_remapable;
extern string rad1_lower_nav2_corse_up_remapable, rad1_lower_nav2_corse_dn_remapable;
extern string rad1_lower_nav2_fine_up_remapable, rad1_lower_nav2_fine_dn_remapable;
extern string rad1_lower_nav2_actstby_btn_remapable;

extern string rad2_upper_com1_corse_up_remapable, rad2_upper_com1_corse_dn_remapable;
extern string rad2_upper_com1_fine_up_remapable, rad2_upper_com1_fine_dn_remapable;
extern string rad2_upper_com1_actstby_btn_remapable;
extern string rad2_upper_com2_corse_up_remapable, rad2_upper_com2_corse_dn_remapable;
extern string rad2_upper_com2_fine_up_remapable, rad2_upper_com2_fine_dn_remapable;
extern string rad2_upper_com2_actstby_btn_remapable;
extern string rad2_upper_nav1_corse_up_remapable, rad2_upper_nav1_corse_dn_remapable;
extern string rad2_upper_nav1_fine_up_remapable, rad2_upper_nav1_fine_dn_remapable;
extern string rad2_upper_nav1_actstby_btn_remapable;
extern string rad2_upper_nav2_corse_up_remapable, rad2_upper_nav2_corse_dn_remapable;
extern string rad2_upper_nav2_fine_up_remapable, rad2_upper_nav2_fine_dn_remapable;
extern string rad2_upper_nav2_actstby_btn_remapable;

extern string rad2_lower_com1_corse_up_remapable, rad2_lower_com1_corse_dn_remapable;
extern string rad2_lower_com1_fine_up_remapable, rad2_lower_com1_fine_dn_remapable;
extern string rad2_lower_com1_actstby_btn_remapable;
extern string rad2_lower_com2_corse_up_remapable, rad2_lower_com2_corse_dn_remapable;
extern string rad2_lower_com2_fine_up_remapable, rad2_lower_com2_fine_dn_remapable;
extern string rad2_lower_com2_actstby_btn_remapable;
extern string rad2_lower_nav1_corse_up_remapable, rad2_lower_nav1_corse_dn_remapable;
extern string rad2_lower_nav1_fine_up_remapable, rad2_lower_nav1_fine_dn_remapable;
extern string rad2_lower_nav1_actstby_btn_remapable;
extern string rad2_lower_nav2_corse_up_remapable, rad2_lower_nav2_corse_dn_remapable;
extern string rad2_lower_nav2_fine_up_remapable, rad2_lower_nav2_fine_dn_remapable;
extern string rad2_lower_nav2_actstby_btn_remapable;

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


extern string mag_off_switch_on, mag_off_switch_off;
extern string mag_right_switch_on, mag_right_switch_off;
extern string mag_left_switch_on, mag_left_switch_off;
extern string mag_both_switch_on, mag_both_switch_off;
extern string mag_start_switch_on, mag_start_switch_off;

extern string bat_master_switch_on, bat_master_switch_off;
extern string alt_master_switch_on, alt_master_switch_off;
extern string av_master_switch_on, av_master_switch_off;

extern string fuel_pump_switch_on, fuel_pump_switch_off;
extern string fuel_pump2_switch_on, fuel_pump2_switch_off;
extern string fuel_pump3_switch_on, fuel_pump3_switch_off;
extern string fuel_pump4_switch_on, fuel_pump4_switch_off;


extern string deice_switch_on, deice_switch_off;
extern string deice2_switch_on, deice2_switch_off;
extern string deice3_switch_on, deice3_switch_off;
extern string deice4_switch_on, deice4_switch_off;
extern string deice5_switch_on, deice5_switch_off;
extern string deice6_switch_on, deice6_switch_off;
extern string deice7_switch_on, deice7_switch_off;
extern string deice8_switch_on, deice8_switch_off;

extern string pitot_heat_switch_on, pitot_heat_switch_off;
extern string pitot2_heat_switch_on, pitot2_heat_switch_off;

extern string gear_switch_up_on, gear_switch_up_off;
extern string gear_switch_down_on, gear_switch_down_off;

extern string cowl_flaps_open, cowl_flaps_close;
extern string cowl2_flaps_open, cowl2_flaps_close;
extern string panel_lights_switch_on, panel_lights_switch_off;
extern string beacon_lights_switch_on, beacon_lights_switch_off;
extern string nav_lights_switch_on, nav_lights_switch_off;
extern string strobe_lights_switch_on, strobe_lights_switch_off;
extern string taxi_lights_switch_on, taxi_lights_switch_off;
extern string landing_lights_switch_on, landing_lights_switch_off;



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
