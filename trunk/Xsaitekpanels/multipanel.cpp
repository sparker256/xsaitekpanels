// ****** multipanel.cpp **********
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

#define testbit(x, y)  ( ( ((const char*)&(x))[(y)>>3] & 0x80 >> ((y)&0x07)) >> (7-((y)&0x07) ) )

// ********************** Multi Panel variables ***********************
static int multinowrite = 0, lastmultiseldis = 0;
static int mulres, multires;

static int multimul = 10;

static int n = 5;

static int appushed = 0;
static int lastappos = 0;
static int aploop = 0;

static int upapalt, upapvs, upapas, upaphdg, upapcrs, upapcrs2, neg;
static int apas, apasout, apmas;

static int flashcnt = 0, flashon = 0;

static int altdbncinc = 0, altdbncdec = 0, vsdbncinc = 0, vsdbncdec = 0;
static int iasdbncinc = 0, iasdbncdec = 0, hdgdbncinc = 0, hdgdbncdec = 0;
static int crsdbncinc = 0, crsdbncdec = 0; 

static float upapaltf, upapvsf, upapasf, upaphdgf, upapcrsf, upapcrsf2, rhdgf;
static float apasf, apmasf;

static int multiaactv, multiadig1, multiarem1, multiadig2, multiarem2;
static int multiadig3, multiarem3, multiadig4, multiarem4, multiadig5;
static int multibstby, multibdig1, multibdig2, multibrem2;
static int multibdig3, multibrem3, multibdig4, multibrem4, multibdig5;  
static int btnleds = 0, lastbtnleds = 0, multiseldis = 1;

static int ALT_SWITCH = 7, VS_SWITCH = 6;
static int IAS_SWITCH = 5, HDG_SWITCH = 4;
static int CRS_SWITCH = 3, AUTO_THROTTLE_SWITCH = 8;
static int AP_MASTER_BUTTON = 0, HDG_BUTTON = 15;
static int NAV_BUTTON = 14, IAS_BUTTON = 13;
static int ALT_BUTTON = 12, VS_BUTTON = 11;
static int APR_BUTTON = 10, REV_BUTTON = 9;
static int FLAPS_UP_SWITCH = 23, FLAPS_DN_SWITCH = 22;
static int TRIM_WHEEL_UP = 20, TRIM_WHEEL_DN = 21;
static int ADJUSTMENT_UP = 2, ADJUSTMENT_DN = 1;

static unsigned char multibuf[4];
static unsigned char multiwbuf[13];


void process_multi_menu()
{
    XPLMClearAllMenuItems(MultiMenuId);
    XPLMAppendMenuItem(MultiMenuId, "Multi Panel Widget", (void *) "MULTI_WIDGET", 1);
}


void process_multi_display()
{
  switch(multiseldis){
    case 1:
    // ***** Setup Display for ALT or VS Switch Position *********
      multiaactv = upapalt;
      multiadig1 = multiaactv/10000, multiarem1 = multiaactv%10000;
      multiadig2 = multiarem1 /1000, multiarem2 = multiarem1%1000;
      multiadig3 = multiarem2/100, multiarem3 = multiarem2%100;
      multiadig4 = multiarem3/10, multiarem4 = multiarem3%10;
      multiadig5 = multiarem4;
      multibstby = upapvs;
      
      if (neg == 1) {
        multibdig1 = 254;
      } else {
        multibdig1 = 15;
      }
      
      multibdig2 = multibstby /1000, multibrem2 = multibstby%1000;
      multibdig3 = multibrem2/100, multibrem3 = multibrem2%100;
      multibdig4 = multibrem3/10, multibrem4 = multibrem3%10;
      multibdig5 = multibrem4;
      break;
    case 2:
    // ***** Setup Display for IAS Switch Position *********
      if (XPLMGetDatai(AirspeedIsMach) == 1) {
          multiaactv = apasout;
          multiadig1 = 15, multiadig2 = 15 ;
          multiadig3 = multiaactv/100, multiarem3 = multiaactv%100;
          multiadig4 = multiarem3/10, multiarem4 = multiarem3%10;
          multiadig5 = multiarem4;

      } else if (XPLMGetDatai(IasIsmachRemapableData) == 1) {

          multiaactv = apasout;
          multiadig1 = 15, multiadig2 = 15 ;
          multiadig3 = multiaactv/100, multiarem3 = multiaactv%100;
          multiadig4 = multiarem3/10, multiarem4 = multiarem3%10;
          multiadig5 = multiarem4;

      } else {
          multiaactv = apasout;
          multiadig1 = 15, multiadig2 = 15 ;
          multiadig3 = multiaactv/100, multiarem3 = multiaactv%100;
          multiadig4 = multiarem3/10, multiarem4 = multiarem3%10;
          multiadig5 = multiarem4;
      }

      break;
    case 3:
    // ***** Setup Display for HDG Switch Position *********
      multiaactv = upaphdg;
      multiadig1 = 15, multiadig2 = 15 ;
      multiadig3 = multiaactv/100, multiarem3 = multiaactv%100;
      multiadig4 = multiarem3/10, multiarem4 = multiarem3%10;
      multiadig5 = multiarem4;
      break;
    case 4:
    // ***** Setup Display for CRS Switch Position *********
      multiaactv = upapcrs;
      multiadig1 = 15, multiadig2 = 15 ;
      multiadig3 = multiaactv/100, multiarem3 = multiaactv%100;
      multiadig4 = multiarem3/10, multiarem4 = multiarem3%10;
      multiadig5 = multiarem4;
      break;
    case 5:
    default:
    // ********** Setup the Display to be Blank *******************
      multiadig1 = 15, multiadig2 = 15, multiadig3 = 15, multiadig4 = 15, multiadig5 = 15;
      multibdig1 = 15, multibdig2 = 15, multibdig3 = 15, multibdig4 = 15, multibdig5 = 15;
      btnleds = 0;
      break;
  }
// ****** Make Message One Digit at A Time and Turn on Button LEDS  *******
  char multiadigit1 = multiadig1, multiadigit2 = multiadig2, multiadigit3 = multiadig3;
  char multiadigit4 = multiadig4, multiadigit5 = multiadig5;
  char multibdigit1 = multibdig1, multibdigit2 = multibdig2, multibdigit3 = multibdig3;
  char multibdigit4 = multibdig4, multibdigit5 = multibdig5;	
  char cdigit1 = btnleds; 

// ****** Load Array with Message of Digits and Button LEDS *************
  multiwbuf[0] = 0;
  multiwbuf[1] = multiadigit1, multiwbuf[2] = multiadigit2, multiwbuf[3] = multiadigit3;
  multiwbuf[4] = multiadigit4, multiwbuf[5] = multiadigit5;
  multiwbuf[6] = multibdigit1, multiwbuf[7] = multibdigit2, multiwbuf[8] = multibdigit3;
  multiwbuf[9] = multibdigit4, multiwbuf[10] = multibdigit5, multiwbuf[11] = cdigit1;

}

// ***************** ALT Switch Position *******************
void process_alt_switch()
{
    if(testbit(multibuf,ALT_SWITCH)) {
        multiseldis = 1;
        if (altswitchremap == 2) {
            upapaltf = XPLMGetDataf(AltSwitchRemapableData);
        } else {
            upapaltf = XPLMGetDataf(ApAlt);
        }
        upapaltf = XPLMGetDataf(ApAlt);
        upapalt = (int)(upapaltf);
        if(testbit(multibuf,ADJUSTMENT_UP)) {
            altdbncinc++;
            if (altdbncinc > multispeed) {
                n = multimul;
                if(xpanelsfnbutton == 1) {
                    if(altswitchremap == 1) {
                        while (n>0) {
                           XPLMCommandOnce(AltSwitchUpRemapableCmd);
                           --n;
                        }

                    } else {
                        upapalt = upapalt + 1000;
                        upapalt = (upapalt / 1000);
                        upapalt = (upapalt * 1000);
                        altdbncinc = 0;

                    }

                }
                if (xpanelsfnbutton == 0) {
                    if(altswitchremap == 1) {
                       XPLMCommandOnce(AltSwitchUpRemapableCmd);
                    } else {
                        upapalt = upapalt + 100;
                        upapalt = (upapalt / 100);
                        upapalt = (upapalt * 100);
                        altdbncinc = 0;
                    }

                }
            }
        }
        if(testbit(multibuf,ADJUSTMENT_DN)) {
            altdbncdec++;
            if (altdbncdec > multispeed) {
                n = multimul;
                if(xpanelsfnbutton == 1) {
                    if(altswitchremap == 1) {
                        while (n>0) {
                           XPLMCommandOnce(AltSwitchUpRemapableCmd);
                           --n;
                        }
                    } else {
                        if (upapalt >= 1000) {
                            upapalt = upapalt - 1000;
                        }
                        if(upapalt > 100) {
                            upapalt = (upapalt / 100);
                            upapalt = (upapalt * 100);
                        }
                        altdbncdec = 0;
                    }

                }

                if (xpanelsfnbutton == 0) {
                     if(altswitchremap == 1) {
                        XPLMCommandOnce(AltSwitchDnRemapableCmd);
                     } else {
                         if (upapalt >= 100) {
                             upapalt = upapalt - 100;
                         }
                         if(upapalt > 100) {
                             upapalt = (upapalt / 100);
                             upapalt = (upapalt * 100);
                         }
                         altdbncdec = 0;
                     }

                }

            }
        }
        upapaltf = upapalt;

        if (altswitchremap == 2) {
            XPLMSetDataf(AltSwitchRemapableData, upapaltf);
        } else {
            XPLMSetDataf(ApAlt, upapaltf);
        }

        if (vsswitchremap == 2) {
            upapvsf = XPLMGetDataf(VsSwitchRemapableData);
        } else {
            upapvsf = XPLMGetDataf(ApVs);
        }
        upapvs = (int)(upapvsf);
        if (upapvs < 0) {
            upapvs = (upapvs * -1);
            neg = 1;
        } else {
            neg = 0;
        }

	}
}

// ***************** VS Switch Position *******************
void process_vs_switch()
{
    if(testbit(multibuf,VS_SWITCH)) {
        multiseldis = 1;
        if (vsswitchremap == 2) {
            upapvsf = XPLMGetDataf(VsSwitchRemapableData);
        } else {
            upapvsf = XPLMGetDataf(ApVs);
        }
        upapvs = (int)(upapvsf);
        if(testbit(multibuf,ADJUSTMENT_UP)) {
            vsdbncinc++;
            if (vsdbncinc > multispeed) {
                n = multimul;
                if (xpanelsfnbutton == 1) {
                    if (vsswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(VsSwitchUpRemapableCmd);
                            --n;
                        }
                    } else {
                        while (n>0) {
                            //XPLMCommandOnce(ApVsUp);
                            upapvs = upapvs + 100;
                            --n;
                        }
                    }
                    vsdbncinc = 0;

                }
                if (xpanelsfnbutton == 0) {
                    if (vsswitchremap == 1) {
                        XPLMCommandOnce(VsSwitchUpRemapableCmd);
                    } else {
                        //XPLMCommandOnce(ApVsUp);
                        upapvs = upapvs + 100;

                    }
                    vsdbncinc = 0;
                }
             }
        }
        if(testbit(multibuf,ADJUSTMENT_DN)) {
            vsdbncdec++;
            if (vsdbncdec > multispeed) {
                n = multimul;
                if(xpanelsfnbutton == 1) {
                    if (vsswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(VsSwitchDnRemapableCmd);
                            --n;
                        }
                    } else {
                        while (n>0) {
                            //XPLMCommandOnce(ApVsUp);
                            upapvs = upapvs - 100;
                            --n;
                        }
                    }
                }
                vsdbncdec = 0;
                if(xpanelsfnbutton == 0) {
                    if (vsswitchremap == 1) {
                        XPLMCommandOnce(VsSwitchDnRemapableCmd);
                    } else {
                        //XPLMCommandOnce(ApVsUp);
                        upapvs = upapvs - 100;
                    }
                    vsdbncdec = 0;
                }
            }
        }

        upapvsf = upapvs;
        if (vsswitchremap == 2) {
            XPLMSetDataf(VsSwitchRemapableData, upapvsf);
        } else {
            XPLMSetDataf(ApVs, upapvsf);
        }

        if (altswitchremap == 2) {
            upapaltf = XPLMGetDataf(AltSwitchRemapableData);
        } else {
            upapaltf = XPLMGetDataf(ApAlt);
        }

        if (vsswitchremap == 2) {
            upapvsf = XPLMGetDataf(VsSwitchRemapableData);
        } else {
            upapvsf = XPLMGetDataf(ApVs);
        }

        upapalt = (int)(upapaltf);
        upapvs = (int)(upapvsf);
        if (upapvs < 0) {
            upapvs = (upapvs * -1);
            neg = 1;
        } else {
            neg = 0;
        }
    }
}

// ***************** IAS Switch Position *******************
void process_ias_switch()
{
    if (testbit(multibuf,IAS_SWITCH)) {
        multiseldis = 2;
        if (iasismachremap == 1) {
            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                apmasf = XPLMGetDataf(IasSwitchRemapableData);
            } else {
                apasf = XPLMGetDataf(IasSwitchRemapableData);
            }
        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
            apmasf = XPLMGetDataf(ApAs);
        } else {
            apasf = XPLMGetDataf(ApAs);
            apas = (int)(apasf);
        }
        if (testbit(multibuf,ADJUSTMENT_UP)) {
            iasdbncinc++;
            if (iasdbncinc > multispeed) {
                n = multimul;
                if (xpanelsfnbutton == 1) {
                    if (iasswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(IasSwitchUpRemapableCmd);
                            --n;
                        }
                    } else {
                        while (n>0) {
                            if (iasismachremap == 1) {
                                if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                                    apmasf = apmasf + .01;
                                } else {
                                    apas = apas + 1;
                                }
                            } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                                apmasf = apmasf + .01;
                            } else {
                                apas = apas + 1;
                            }
                            --n;
                        }
                    }
                    iasdbncinc = 0;
                }
                if (xpanelsfnbutton == 0) {
                    if (iasswitchremap == 1) {
                        XPLMCommandOnce(IasSwitchUpRemapableCmd);
                    } else {
                        if (iasismachremap == 1) {
                            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                                apmasf = apmasf + .01;
                            } else {
                                apas = apas + 1;
                            }
                        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                            apmasf = apmasf + .01;
                        } else {
                            apas = apas + 1;
                        }
                    }
                    iasdbncinc = 0;
                }
            }
        }
        if (testbit(multibuf,ADJUSTMENT_DN)) {
            iasdbncdec++;
            if (iasdbncdec > multispeed) {
                n = multimul;
                if (xpanelsfnbutton == 1) {
                    if (iasswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(IasSwitchDnRemapableCmd);
                            --n;
                        }
                    } else {
                        while (n>0) {
                            if (iasismachremap == 1) {
                                if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                                    apmasf = apmasf - .01;
                                } else {
                                    apas = apas - 1;
                                }

                            } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                                apmasf = apmasf - .01;
                            } else {
                                apas = apas - 1;
                            }
                            --n;
                        }
                    }
                    iasdbncdec = 0;
                }
                if (xpanelsfnbutton == 0) {
                    if (iasswitchremap == 1) {
                        XPLMCommandOnce(IasSwitchDnRemapableCmd);
                    } else {
                        if (iasismachremap == 1) {
                            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                                apmasf = apmasf - .01;
                            } else {
                                apas = apas - 1;
                            }
                        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                            apmasf = apmasf - .01;
                        } else {
                            apas = apas - 1;
                        }
                    }
                    iasdbncdec = 0;
                }
            }
        }

        if (iasismachremap == 1) {
            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                if (iasswitchremap == 1) {
                   apmasf = XPLMGetDataf(IasSwitchRemapableData);
                }
                apmas = (int)(apmasf * 100);
                apasout = apmas;
                //XPLMSetDataf(IasSwitchRemapableData, apmasf);
            } else {
                if (iasswitchremap == 1) {
                   apasf = XPLMGetDataf(IasSwitchRemapableData);
                   apas = (int)(apasf);
                }
                apasout = apas;
                apasf = apas;
                //XPLMSetDataf(IasSwitchRemapableData, apasf);
            }
        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
            apmas = (int)(apmasf * 100);
            apasout = apmas;
            XPLMSetDataf(ApAs, apmasf);
        } else {
            apasout = apas;
            apasf = apas;
            XPLMSetDataf(ApAs, apasf);
        }

    }
}

// ***************** HDG Switch Position *******************
void process_hdg_switch()
{

    if(testbit(multibuf,HDG_SWITCH)) {
        multiseldis = 3;
        if (hdgswitchremap == 2) {
            upaphdgf = XPLMGetDataf(HdgSwitchRemapableData);
        } else {
            upaphdgf = XPLMGetDataf(ApHdg);
        }

        upaphdg = (int)(upaphdgf);
        if(testbit(multibuf,ADJUSTMENT_UP)) {
            hdgdbncinc++;
            if (hdgdbncinc > multispeed) {
                n = multimul;
                if(xpanelsfnbutton == 1) {
                    if (hdgswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(HdgSwitchUpRemapableCmd);
                            --n;
                        }
                    } else {
                        upaphdg = upaphdg + multimul;
                    }
                    hdgdbncinc = 0;

                }
                if(xpanelsfnbutton == 0) {
                    if (hdgswitchremap == 1) {
                        XPLMCommandOnce(HdgSwitchUpRemapableCmd);
                    } else {
                        upaphdg = upaphdg + 1;
                    }
                    hdgdbncinc = 0;
                }
            }
        }
        if(testbit(multibuf,ADJUSTMENT_DN)) {
            hdgdbncdec++;
            if (hdgdbncdec > multispeed) {
                n = multimul;
                if(xpanelsfnbutton == 1) {
                    if (hdgswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(HdgSwitchDnRemapableCmd);
                            --n;
                        }
                    } else {
                        upaphdg = upaphdg - multimul;
                    }
                    hdgdbncdec = 0;
                }
                if(xpanelsfnbutton == 0) {
                    if (hdgswitchremap == 1) {
                        XPLMCommandOnce(HdgSwitchDnRemapableCmd);
                    } else {
                        upaphdg = upaphdg - 1;
                    }
                    hdgdbncdec = 0;
                }
            }
        }
        if(upaphdg > 360) {
            upaphdg = 1;
        }
        if(upaphdg < 0) {
            upaphdg = 359;
        }
        upaphdgf = upaphdg;
        if (hdgswitchremap == 2) {
            XPLMSetDataf(HdgSwitchRemapableData, upaphdgf);
        } else {
            XPLMSetDataf(ApHdg, upaphdgf);
        }

    }
}

// ***************** CRS Switch Position *******************
void process_crs_switch()
{
    float cur_apcrsf = 0;
    int   cur_apcrs  = 0;

    // if the toggle is selected, use nav2, otherwise, nav1
    XPLMDataRef crs_dataref =  !xpanelscrstoggle ? ApCrs : ApCrs2;

	if(testbit(multibuf,CRS_SWITCH)) {
        multiseldis = 4;
        upapcrsf = XPLMGetDataf(ApCrs);
        upapcrs = (int)(upapcrsf);

        if (crsswitchremap == 1) {
            cur_apcrsf = XPLMGetDataf(CrsSwitchRemapableData);
        } else {
            //  get the appropriate course setting depending on if the toggle is down
            cur_apcrsf = XPLMGetDataf(crs_dataref);
        }
        cur_apcrs = (int)(cur_apcrsf);
        if(testbit(multibuf,ADJUSTMENT_UP)) {
            crsdbncinc++;
            if (crsdbncinc > multispeed) {
                n = multimul;
                if (xpanelsfnbutton == 1) {
                    if (crsswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(CrsSwitchUpRemapableCmd);
                            --n;
                        }
                    } else {
                        cur_apcrs = cur_apcrs + multimul;
                    }
                }
                if(xpanelsfnbutton == 0) {
                    if (crsswitchremap == 1) {
                        XPLMCommandOnce(CrsSwitchUpRemapableCmd);
                    } else {
                        cur_apcrs = cur_apcrs + 1;
                    }

                }
                crsdbncinc = 0;
            }
        }

        if(testbit(multibuf,ADJUSTMENT_DN)) {
            crsdbncdec++;
            if (crsdbncdec > multispeed) {
                n = multimul;
                if (xpanelsfnbutton == 1) {
                    if (crsswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(CrsSwitchDnRemapableCmd);
                            --n;
                        }
                    } else {
                        cur_apcrs = cur_apcrs - multimul;
                    }

                }
                if(xpanelsfnbutton == 0) {
                    if (crsswitchremap == 1) {
                        XPLMCommandOnce(CrsSwitchDnRemapableCmd);
                    } else {
                        cur_apcrs = cur_apcrs - 1;
                    }

                }

                crsdbncdec = 0;
            }
        }

        if(cur_apcrs > 360) {
            cur_apcrs = 1;
        }

        if(cur_apcrs < 0) {
            cur_apcrs = 359;
        }

        cur_apcrsf = cur_apcrs;
        if (crsswitchremap == 1) {
            XPLMSetDataf(CrsSwitchRemapableData, cur_apcrsf);
        } else {
            XPLMSetDataf(crs_dataref, cur_apcrsf);
        }

        if (crsswitchremap == 1) {

        } else {
            //  set the appropriate global based on whether the crs toggle is on
            if( !xpanelscrstoggle ) {
                //  toggle off - nav1
                upapcrsf = cur_apcrsf;
                upapcrs  = cur_apcrs;
            } else {
                //  toggle on - nav2
                upapcrsf2 = cur_apcrsf;
                upapcrs2   = cur_apcrs;
                upapcrs   = cur_apcrs;
            }
        }

	}
}

// ***************** Auto Throttle Switch Position *******************
void process_autothrottle_switch()
{
    if(autothrottleswitchenable == 0) {
        return;
    }
    if(testbit(multibuf,AUTO_THROTTLE_SWITCH)) {
        if (attrswitchremap == 2) {
            XPLMSetDatai(AttrSwitchRemapableData, 1);
        } else {
            XPLMSetDatai(ApAutThr, 1);
        }
    } else {
        if (attrswitchremap == 2) {
            XPLMSetDatai(AttrSwitchRemapableData, 0);
        } else {
            XPLMSetDatai(ApAutThr, 0);
        }
    }
}

// ***************** AP Master Button and light *******************
void process_ap_master_switch()
{
    if (apbuttonremap == 1) {
        if (appushed == 0) {
            if (testbit(multibuf, AP_MASTER_BUTTON)) {
                XPLMCommandOnce(ApButtonRemapableCmd);
                appushed = 1;
                lastappos = 1;
            }
        }

        if (appushed == 1) {
            aploop++;
            if (aploop == 50) {
               appushed = 0;
               aploop = 0;
            }
        }

        if (aplightremap == 1) {
            switch(XPLMGetDatai(ApLightRemapableData)) {
            case 1:
                btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDatai(ApLightFlashRemapableData)) {
                    if (flashon == 1) {
                        btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                    } else {
                        btnleds &= ~(1<<0);   // * clear bit 0 in btnleds to 0 *
                    }
                } else {
                    btnleds &= ~(1<<0);   // * clear bit 0 in btnleds to 0 *
                }
                break;
            }

        } else {
            switch(XPLMGetDatai(ApMstrStat)) {
            case 0:
                btnleds &= ~(1<<0);   // * clear bit 0 in btnleds to 0 *
                break;
            case 1:
                if (flashon == 1) {
                    btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                } else {
                    btnleds &= ~(1<<0);   // * clear bit 0 in btnleds to 0 *
                }
                break;
            case 2:
                btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                break;
            }
        }


    } else {
        if (appushed == 0) {
          switch(XPLMGetDatai(ApMstrStat)){
          case 0:
              if(testbit(multibuf, AP_MASTER_BUTTON)) {
                  XPLMSetDatai(ApMstrStat, 1);
                  appushed = 1;
                  lastappos = 1;
              }
              break;
          case 1:
              if(testbit(multibuf, AP_MASTER_BUTTON)) {
                  if (lastappos == 1) {
                      XPLMSetDatai(ApMstrStat, 2);
                      appushed = 1;
                  }
                  if (lastappos == 2) {
                      XPLMSetDatai(ApMstrStat, 0);
                      appushed = 1;
                  }
              }
              break;
          case 2:
              if(testbit(multibuf, AP_MASTER_BUTTON)) {
                  XPLMSetDatai(ApMstrStat, 1);
                  appushed = 1;
                  lastappos = 2;
              }
              break;
          }
        }

        if (appushed == 1) {
            aploop++;
            if (aploop == 50) {
                appushed = 0;
                aploop = 0;
            }

        }
        
        switch(XPLMGetDatai(ApMstrStat)) {
        case 0:
            btnleds &= ~(1<<0);   // * clear bit 0 in btnleds to 0 *
            break;
        case 1:
            if (flashon == 1) {
                btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
            } else {
                btnleds &= ~(1<<0);   // * clear bit 0 in btnleds to 0 *
            }
            break;
        case 2:
            btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
            break;
        }
    }
}

// ***************** HDG Button and light *******************
void process_hdg_button()
{
    if (hdgbuttonremap == 1) {
            if (multires > 0) {
                if (testbit(multibuf, HDG_BUTTON)) {
                    XPLMCommandOnce(HdgButtonRemapableCmd);
                    lastappos = 1;
                }
            }
            if (hdglightremap == 1) {
                switch(XPLMGetDatai(HdgLightRemapableData)) {
                case 1:
                    btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                    break;
                case 0:
                    if (XPLMGetDatai(HdgLightFlashRemapableData)) {
                        if (flashon == 1) {
                            btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                        } else {
                            btnleds &= ~(1<<1);   // * clear bit 1 in btnleds to 0 *
                        }
                    } else {
                        btnleds &= ~(1<<1);   // * clear bit 1 in btnleds to 0 *
                    }
                    break;
                }

            } else {
                switch(XPLMGetDatai(ApHdgStat)){
                  case 2:
                    btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                    break;
                  case 1:
                    if (flashon == 1) {
                      btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                }else{
                      btnleds &= ~(1<<1);   // * clear bit 1 in btnleds to 0 *
                }
                    break;
                  case 0:
                    btnleds &= ~(1<<1);   // * clear bit 1 in btnleds to 0 *
                    break;
                }
            }

    } else {
        if (multires > 0) {
          if(testbit(multibuf,HDG_BUTTON)) {

            if(xpanelsfnbutton == 1) {
                rhdgf = XPLMGetDataf(MHdg);
                XPLMSetDataf(ApHdg, rhdgf);
            }
            if(xpanelsfnbutton == 0) {
                XPLMCommandOnce(ApHdgBtn);
                lastappos = 1;
            }
          }
        }
        
        switch(XPLMGetDatai(ApHdgStat)){
          case 2:
            btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
            break;
          case 1:
            if (flashon == 1) {
              btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
        }else{
              btnleds &= ~(1<<1);   // * clear bit 1 in btnleds to 0 *
	    }
            break;
          case 0:
            btnleds &= ~(1<<1);   // * clear bit 1 in btnleds to 0 *
            break;
        }
        if (XPLMGetDatai(ApMstrStat) == 0) {
            btnleds &= ~(1<<1);   // * clear bit 1 in btnleds to 0 *
        }
    }
}

// ***************** NAV Button and light *******************
void process_nav_button()
{
    if (navbuttonremap == 1){
        if (multires > 0) {
          if(testbit(multibuf,NAV_BUTTON)) {
              switch (XPLMGetDatai(HsiSelector)) {
                  case 0:
                  case 1:
                      XPLMCommandOnce(NavButtonVorlocRemapableCmd);
                      break;
                  case 2:
                      XPLMCommandOnce(NavButtonLnavRemapableCmd);
                      break;
              }

             lastappos = 1;
          }
        }

        if (navlightremap == 1) {

            switch (XPLMGetDatai(HsiSelector)) {
                case 0:
                case 1:
                    // Use LED to match power state
                    switch (XPLMGetDatai(NavLightVorlocRemapableData)) {
                        case 1:
                            btnleds |= (1<<2);
                            break;
                        case 0:
                            // Although x737 LED has no armed status, the PFD does
                            if (XPLMGetDatai(NavLightVorlocFlashRemapableData)) {
                                if (flashon == 1) {
                                    btnleds |= (1<<2);
                                } else {
                                    btnleds &= ~(1<<2);
                                }
                            } else {
                                btnleds &= ~(1<<2);
                            }
                            break;
                    }
                    break;
                case 2:
                    switch (XPLMGetDatai(NavLightLnavRemapableData)) {
                        case 1:
                            btnleds |= (1<<2);
                            break;
                        case 0:
                            if (XPLMGetDatai(NavLightLnavFlashRemapableData)) {
                                if (flashon == 1) {
                                    btnleds |= (1<<2);
                                } else {
                                    btnleds &= ~(1<<2);
                                }
                            } else {
                                btnleds &= ~(1<<2);
                            }
                            break;
                    }
                    break;
            }


        } else {
            switch(XPLMGetDatai(ApNavStat)){
              case 2:
                btnleds |= (1<<2);   // * set bit 2 in btnleds to 1 *
                break;
              case 1:
                if (flashon == 1) {
                  btnleds |= (1<<2);   // * set bit 1 in btnleds to 1 *
                }else{
                  btnleds &= ~(1<<2);   // * clear bit 2 in btnleds to 0 *
                }
                break;
              case 0:
                btnleds &= ~(1<<2);   // * clear bit 2 in btnleds to 0 *
                break;
            }
        }

    } else {
        if (multires > 0) {
          if(testbit(multibuf,NAV_BUTTON)) {
            if(xpanelsfnbutton == 1) {
                xpanelscrstoggle = !xpanelscrstoggle;
            }
            if(xpanelsfnbutton == 0) {
                XPLMCommandOnce(ApNavBtn);
                lastappos = 1;
            }

          }
        }

	switch(XPLMGetDatai(ApNavStat)){
	  case 2:
            btnleds |= (1<<2);   // * set bit 2 in btnleds to 1 *
            break;
          case 1:
	    if (flashon == 1) {
              btnleds |= (1<<2);   // * set bit 1 in btnleds to 1 *
	    }else{
              btnleds &= ~(1<<2);   // * clear bit 2 in btnleds to 0 *
	    }
	    break;
	  case 0:
            btnleds &= ~(1<<2);   // * clear bit 2 in btnleds to 0 *
	    break;
	}
   }
}

// ***************** IAS Button and light ******************
void process_ias_button()
{
    if (loaded737 == 1) {
         if (multires > 0) {
             if (testbit(multibuf, IAS_BUTTON)) {
                 if (xpanelsfnbutton == 1) {
                     XPLMCommandOnce(x737mcp_spd_changeover);
                 }
                 if (xpanelsfnbutton == 0) {
                     XPLMCommandOnce(x737mcp_lvlchange_toggle);
                     lastappos = 1;
                 }
             }
         }

         // Always match x737 glareshield LED
         switch (XPLMGetDatai(x737mcp_lvlchange_led)) {
             case 1:
                 btnleds |= (1<<3);
                 break;
             case 0:
                 btnleds &= ~(1<<3);
                 break;
         }

       } else if (iasbuttonremap == 1) {
              if (multires > 0) {
                  if (testbit(multibuf, IAS_BUTTON)) {
                      XPLMCommandOnce(IasButtonRemapableCmd);
                      lastappos = 1;

                  }
              }
              if (iaslightremap == 1) {
                  switch(XPLMGetDatai(IasLightRemapableData)) {
                  case 1:
                      btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                      break;
                  case 0:
                      if (XPLMGetDatai(IasLightFlashRemapableData)) {
                          if (flashon == 1) {
                              btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                          } else {
                              btnleds &= ~(1<<3);   // * clear bit 3 in btnleds to 0 *
                          }
                      } else {
                          btnleds &= ~(1<<3);   // * clear bit 3 in btnleds to 0 *
                      }
                      break;
                  }

              } else {
                  switch(XPLMGetDatai(ApIasStat)){
                    case 2:
                      btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                      break;
                    case 1:
                      if (flashon == 1) {
                        btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                      }
                      if (flashon == 0) {
                        btnleds &= ~(1<<3);   // * clear bit 3 in btnleds to 0 *
                      }
                      break;
                    case 0:
                      btnleds &= ~(1<<3);   // * clear bit 3 in btnleds to 0 *
                      break;
                  }
              }

     } else {
        if (multires > 0) {
          if(testbit(multibuf,IAS_BUTTON)) {
            if(xpanelsfnbutton == 1) {
                 if (XPLMGetDatai(AirspeedIsMach) == 1) {
                     XPLMCommandOnce(ApKnotsMachTgl);
                 } else {
                     XPLMCommandOnce(ApKnotsMachTgl);
                 }
             }
             if(xpanelsfnbutton == 0) {
                 XPLMCommandOnce(ApIasBtn);
                 lastappos = 1;
             }

          }
        }
        switch(XPLMGetDatai(ApIasStat)){
          case 2:
            btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
            break;
          case 1:
            if (flashon == 1) {
              btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
            }
            if (flashon == 0) {
              btnleds &= ~(1<<3);   // * clear bit 3 in btnleds to 0 *
            }
            break;
          case 0:
            btnleds &= ~(1<<3);   // * clear bit 3 in btnleds to 0 *
            break;
        }
    }
}

// ***************** ALT Button and light *******************
void process_alt_button()
{
     if (altbuttonremap == 1) {
            if (multires > 0) {
                if (testbit(multibuf, ALT_BUTTON)) {
                    XPLMCommandOnce(AltButtonRemapableCmd);
                    lastappos = 1;
                }
            }
            if (altlightremap == 1) {
                switch(XPLMGetDatai(AltLightRemapableData)) {
                case 1:
                    btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                    break;
                case 0:
                    if (XPLMGetDatai(AltLightFlashRemapableData)) {
                        if (flashon == 1) {
                            btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                        } else {
                            btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
                        }
                    } else {
                        btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
                    }
                    break;
                }

            } else {
                switch(XPLMGetDatai(ApAltStat)){
                  case 2:
                        btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                        break;
                      case 1:
                    if (flashon == 1) {
                          btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                    }else{
                          btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
                    }
                        break;
                      case 0:
                        btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
                        break;
                }
            }

    } else {
        if (multires > 0) {
          if(testbit(multibuf,ALT_BUTTON)) {
           XPLMCommandOnce(ApAltBtn);
           lastappos = 1;
          }
        }
	switch(XPLMGetDatai(ApAltStat)){
	  case 2:
            btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
            break;
          case 1:
	    if (flashon == 1) {
              btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
	    }else{    
              btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
	    }
            break;
          case 0:
            btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
            break;
	} 
	
	if (XPLMGetDatai(ApMstrStat) == 0) {
          btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
	}
    }
}

// ***************** VS Button and light *******************
void process_vs_button()
{

    if (loaded737 == 1) {
        if (multires > 0) {
            if (testbit(multibuf, VS_BUTTON)) {
                XPLMCommandOnce(x737mcp_vs_toggle);
                lastappos = 1;
            }
        }
        switch (XPLMGetDatai(x737mcp_vvi_led)) {
            case 1:
                btnleds |= (1<<5);
                break;
            case 0:
                if (XPLMGetDatai(x737mcp_vvi_armed_led)) {
                    if (flashon == 0) {
                        btnleds |= (1<<5);
                    } else {
                        btnleds &= ~(1<<5);
                    }
                } else {
                    btnleds &= ~(1<<5);
                }
                break;
        }

    } else if (vsbuttonremap == 1) {
            if (multires > 0) {
                if (testbit(multibuf, VS_BUTTON)) {
                    XPLMCommandOnce(VsButtonRemapableCmd);
                    lastappos = 1;
                }
            }
            if (vslightremap == 1) {
                switch(XPLMGetDatai(VsLightRemapableData)) {
                case 1:
                    btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                    break;
                case 0:
                    if (XPLMGetDatai(VsLightFlashRemapableData)) {
                        if (flashon == 1) {
                            btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                        } else {
                            btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                        }
                    } else {
                        btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                    }
                    break;
                }


            } else {
                switch (XPLMGetDatai(x737mcp_vvi_led)) {
                    case 1:
                        btnleds |= (1<<5);
                        break;
                    case 0:
                        if (XPLMGetDatai(x737mcp_vvi_armed_led)) {
                            if (flashon == 0) {
                                btnleds |= (1<<5);
                            } else {
                                btnleds &= ~(1<<5);
                            }
                        } else {
                            btnleds &= ~(1<<5);
                        }
                        break;
                }
            }

    } else {
        if (multires > 0) {
          if(testbit(multibuf,VS_BUTTON)) {
            XPLMCommandOnce(ApVsBtn);
            lastappos = 1;
          }
        }
	switch(XPLMGetDatai(ApVsStat)){
	  case 2:
            btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
            break;
          case 1:
	    if (flashon == 0) {
              btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
	    }else{   
              btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
	    }
            break;
          case 0:
            btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
            break;
        }
    }
}

// ***************** APR Button and light *******************
void process_apr_button()
{

    if (aprbuttonremap == 1){
        if (multires > 0) {
          if(testbit(multibuf,APR_BUTTON)) {
             XPLMCommandOnce(AprButtonRemapableCmd);
             lastappos = 1;
          }
        }
        if (aprlightremap == 1) {
            switch(XPLMGetDatai(AprLightRemapableData)) {
            case 1:
                btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDatai(AprLightFlashRemapableData)) {
                    if (flashon == 1) {
                        btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                    } else {
                        btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
                    }
                } else {
                    btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
                }
                break;
            }


        } else {
            switch(XPLMGetDatai(ApAprStat)){
              case 2:
                btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                break;
              case 1:
                if (flashon == 1) {
                  btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                }else{
                  btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
                }
                break;
              case 0:
                btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
                break;
            }
        }


    } else {
        if (multires > 0) {
          if(testbit(multibuf,APR_BUTTON)) {
            if(xpanelsfnbutton == 1) {
                rhdgf = XPLMGetDataf(MHdg);
                XPLMSetDataf(ApCrs, rhdgf);
            }
            if(xpanelsfnbutton == 0) {
                XPLMCommandOnce(ApAprBtn);
                lastappos = 1;
            }
          }
        }
	switch(XPLMGetDatai(ApAprStat)){
	  case 2:
            btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
            break;
          case 1:
	    if (flashon == 1) {
              btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
	    }else{   
              btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
	    }
            break;
          case 0:
            btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
            break;
        }
    }
}

// ***************** REV Button and light *******************
void process_rev_button()
{
    if (revbuttonremap == 1) {
        if (multires > 0) {
            if(testbit(multibuf,REV_BUTTON)) {
                XPLMCommandOnce(RevButtonRemapableCmd);
                lastappos = 1;
            }
        }
        if (revlightremap == 1) {
            switch(XPLMGetDatai(RevLightRemapableData)) {
            case 1:
                btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDatai(RevLightFlashRemapableData)) {
                    if (flashon == 1) {
                        btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                    } else {
                        btnleds &= ~(1<<7);   // * clear bit 7 in btnleds to 0 *
                    }
                } else {
                    btnleds &= ~(1<<7);   // * clear bit 7 in btnleds to 0 *
                }
                break;
            }


        } else {
            switch(XPLMGetDatai(ApRevStat)) {
            case 2:
                btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                break;
            case 1:
                if (flashon == 1) {
                    btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                } else {
                    btnleds &= ~(1<<7);   // * clear bit 7 in btnleds to 0 *
                }
                    break;
            case 0:
                btnleds &= ~(1<<7);   // * clear bit 7 in btnleds to 0 *
                break;
            }
        }




    } else {
        if (multires > 0) {
            if(testbit(multibuf,REV_BUTTON)) {
                XPLMCommandOnce(ApRevBtn);
                lastappos = 1;
            }
        }
        switch(XPLMGetDatai(ApRevStat)) {
        case 2:
            btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
            break;
        case 1:
            if (flashon == 1) {
                btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
            } else {
                btnleds &= ~(1<<7);   // * clear bit 7 in btnleds to 0 *
            }

            break;
        case 0:
            btnleds &= ~(1<<7);   // * clear bit 7 in btnleds to 0 *
            break;
        }

    }

}

// ***************** Flaps Switch *******************
void process_flaps_switch()
{
    if (XPLMGetDatai(BatPwrOn) == 1) {
        if (multires > 0) {
            if(testbit(multibuf,FLAPS_UP_SWITCH)) {
                XPLMCommandOnce(FlapsUp);
            }
            if(testbit(multibuf,FLAPS_DN_SWITCH)) {
                XPLMCommandOnce(FlapsDn);
            }
        }
    }
}

// *************** Trim Wheel *********************
void process_trim_wheel()
{
    int i;
    if (multires > 0) {
        if(testbit(multibuf,TRIM_WHEEL_UP)) {
            for(i = 0; i < trimspeed; ++i) {
                if (trimupremap == 1) {
                    XPLMCommandOnce(TrimUpRemapableCmd);
                } else {
                    XPLMCommandOnce(PitchTrimUp);
                }
            }
        }
        if(testbit(multibuf,TRIM_WHEEL_DN)) {
            for(i = 0; i < trimspeed; ++i) {
                if (trimdnremap == 1) {
                    XPLMCommandOnce(TrimDnRemapableCmd);
                } else {
                    XPLMCommandOnce(PitchTrimDn);
                }
            }
        }
    }
}

// ***************** Flasher for Button LEDS *******************
void process_multi_flash()
{
    flashcnt++;
    if (flashcnt < 50) {
        flashon = 0;
    }
    if (flashcnt > 50) {
        flashon = 1;
    }
    if (flashcnt == 100) {
        flashcnt = 0;
    }
}

// ***************** Blank Display *******************
void process_multi_blank_display()
{
    if (XPLMGetDatai(AvPwrOn) == 0) {
        multiseldis = 5;
    }
    if (XPLMGetDatai(BatPwrOn) == 0) {
        multiseldis = 5;
    }

}


// ***** Multi Panel Process ******
void process_multi_panel()

{
    process_multi_menu();

    // ******* Only do a read if something new to be read ********
    hid_set_nonblocking(multihandle, 1);
    int multi_safety_cntr = 30;
    do {
        multires = hid_read(multihandle, multibuf, sizeof(multibuf));
        process_alt_switch();
        process_vs_switch();
        process_ias_switch();
        process_hdg_switch();
        process_crs_switch();
        process_autothrottle_switch();
        process_ap_master_switch();
        process_hdg_button();
        process_nav_button();
        process_ias_button();
        process_alt_button();
        process_vs_button();
        process_apr_button();
        process_rev_button();
        process_flaps_switch();
        process_trim_wheel();
        if(multires > 0) {
            process_multi_flash();
            process_multi_blank_display();
            process_multi_display();
            hid_send_feature_report(multihandle, multiwbuf, sizeof(multiwbuf));

        }
        --multi_safety_cntr;
    } while((multires > 0) && (multi_safety_cntr > 0));

    process_multi_flash();
    process_multi_blank_display();
    process_multi_display();

    // ******* Write on changes or timeout ********
    if ((lastmultiseldis != multiseldis) || (lastbtnleds != btnleds) || (multinowrite > 50)) {
        mulres = hid_send_feature_report(multihandle, multiwbuf, sizeof(multiwbuf));
        multinowrite = 1;
        lastmultiseldis = multiseldis;
        lastbtnleds = btnleds;
    } else {
        multinowrite++;
    }
    return;
}
