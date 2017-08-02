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
static int lastappos = 0, lastappos2 = 0;
static int aploop = 0;
//static int multitestloop = 0;


static int upapalt, upapvs, upaphdg, upapcrs, upapcrs2, neg;
static int apas, apasout, apmas;

static int flashcnt = 0, flashon = 0;

static int altdbncinc = 0, altdbncdec = 0, vsdbncinc = 0, vsdbncdec = 0;
static int iasdbncinc = 0, iasdbncdec = 0, hdgdbncinc = 0, hdgdbncdec = 0;
static int crsdbncinc = 0, crsdbncdec = 0; 

static int altbiginc = 0, altbigdec = 0, vsbiginc = 0, vsbigdec = 0;
static int iasbiginc = 0, iasbigdec = 0, hdgbiginc = 0, hdgbigdec = 0;
static int crsbiginc = 0, crsbigdec = 0;

static float upapaltf, upapvsf, upaphdgf, upapcrsf, upapcrsf2, rhdgf;
static float apasf, apmasf;

static int multiaactv, multiadig1, multiarem1, multiadig2, multiarem2;
static int multiadig3, multiarem3, multiadig4, multiarem4, multiadig5;
static int multibstby, multibdig1, multibdig2, multibrem2;
static int multibdig3, multibrem3, multibdig4, multibrem4, multibdig5;  
static int btnleds = 0, lastbtnleds = 0, multiseldis = 5;

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

static int Last_Adjustment_Up, Last_Adjustment_Dn;


float MultiAltKnobSpeedThreshold = 0.40f;  // Steve Bootes  Bill Good: speed thresholds for alt knob acceleration
float MultiVsKnobSpeedThreshold =  0.40f;  // Steve Bootes Bill Good: speed thresholds for vs knob acceleration
float MultiIasKnobSpeedThreshold =  0.40f;  // Steve Bootes Bill Good: speed thresholds for ias knob acceleration
float MultiHdgKnobSpeedThreshold =  0.40f;  // Steve Bootes Bill Good: speed thresholds for hdg knob acceleration
float MultiCrsKnobSpeedThreshold =  0.40f;  // Steve Bootes Bill Good: speed thresholds for crs knob acceleration


static unsigned char multibuf[4];
static unsigned char multiwbuf[13];


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
void process_multi_panel_datareference_values()
{
    if(testbit(multibuf,ALT_SWITCH)) {
        XPLMSetDatai(MultiAltSwitchOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiAltSwitchOwnedDataRef, 0);
    }

    if(testbit(multibuf,VS_SWITCH)) {
        XPLMSetDatai(MultiVsSwitchOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiVsSwitchOwnedDataRef, 0);
    }

    if(testbit(multibuf,IAS_SWITCH)) {
        XPLMSetDatai(MultiIasSwitchOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiIasSwitchOwnedDataRef, 0);
    }

    if(testbit(multibuf,HDG_SWITCH)) {
        XPLMSetDatai(MultiHdgSwitchOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiHdgSwitchOwnedDataRef, 0);
    }

    if(testbit(multibuf,CRS_SWITCH)) {
        XPLMSetDatai(MultiCrsSwitchOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiCrsSwitchOwnedDataRef, 0);
    }

    if(testbit(multibuf,ADJUSTMENT_UP)) {
        XPLMSetDatai(MultiKnobIncOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiKnobIncOwnedDataRef, 0);
    }

    if(testbit(multibuf,ADJUSTMENT_DN)) {
        XPLMSetDatai(MultiKnobDecOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiKnobDecOwnedDataRef, 0);
    }

    if(testbit(multibuf,AUTO_THROTTLE_SWITCH)) {
        XPLMSetDatai(MultiAtOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiAtOwnedDataRef, 0);
    }

    if(testbit(multibuf,TRIM_WHEEL_UP)) {
        XPLMSetDatai(MultiTrimUpOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiTrimUpOwnedDataRef, 0);
    }

    if(testbit(multibuf,TRIM_WHEEL_DN)) {
        XPLMSetDatai(MultiTrimDnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiTrimDnOwnedDataRef, 0);
    }

    if(testbit(multibuf,TRIM_WHEEL_UP)) {
        XPLMSetDatai(MultiTrimUpOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiTrimUpOwnedDataRef, 0);
    }

    if(testbit(multibuf,FLAPS_UP_SWITCH)) {
        XPLMSetDatai(MultiFlapsUpOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiFlapsUpOwnedDataRef, 0);
    }

    if(testbit(multibuf,FLAPS_DN_SWITCH)) {
        XPLMSetDatai(MultiFlapsDnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiFlapsDnOwnedDataRef, 0);
    }


    if(testbit(multibuf,AP_MASTER_BUTTON)) {
        XPLMSetDatai(MultiApBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiApBtnOwnedDataRef, 0);
    }


    if(testbit(multibuf,HDG_BUTTON)) {
        XPLMSetDatai(MultiHdgBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiHdgBtnOwnedDataRef, 0);
    }

    if(testbit(multibuf,NAV_BUTTON)) {
        XPLMSetDatai(MultiNavBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiNavBtnOwnedDataRef, 0);
    }

    if(testbit(multibuf,IAS_BUTTON)) {
        XPLMSetDatai(MultiIasBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiIasBtnOwnedDataRef, 0);
    }

    if(testbit(multibuf,ALT_BUTTON)) {
        XPLMSetDatai(MultiAltBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiAltBtnOwnedDataRef, 0);
    }

    if(testbit(multibuf,VS_BUTTON)) {
        XPLMSetDatai(MultiVsBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiVsBtnOwnedDataRef, 0);
    }

    if(testbit(multibuf,APR_BUTTON)) {
        XPLMSetDatai(MultiAprBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiAprBtnOwnedDataRef, 0);
    }

    if(testbit(multibuf,REV_BUTTON)) {
        XPLMSetDatai(MultiRevBtnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(MultiRevBtnOwnedDataRef, 0);
    }

    int adjustment_up = XPLMGetDatai(MultiKnobIncOwnedDataRef);
    if (Last_Adjustment_Up != 0 && adjustment_up == 0)
    {
      XPLMSetDatai(MultiKnobIncTicksOwnedDataRef, XPLMGetDatai(MultiKnobIncTicksOwnedDataRef) + 1);
    }
    int adjustment_dn = XPLMGetDatai(MultiKnobDecOwnedDataRef);
    if (Last_Adjustment_Dn != 0 && adjustment_dn == 0)
    {
      XPLMSetDatai(MultiKnobDecTicksOwnedDataRef, XPLMGetDatai(MultiKnobDecTicksOwnedDataRef) + 1);
    }
}

// ***************** ALT Switch Position *******************
void process_alt_switch()
{
    if(testbit(multibuf,ALT_SWITCH)) {
        MultiAltKnobSpeedThreshold = (float)(multiaccelthreshold * .01);

        if (!AvPwrIsOn()) {
            multiseldis = 5;
        } else {
           multiseldis = 1;
        }

        if ((altswitchremap == 2) | (altswitchremap == 1)) {
            upapaltf = XPLMGetDataf(AltSwitchRemapableData);
        } else {
            upapaltf = XPLMGetDataf(ApAlt);
        }
 //       upapaltf = XPLMGetDataf(ApAlt);
        upapalt = (int)(upapaltf);
        if((Last_Adjustment_Up == 1) && (testbit(multibuf,ADJUSTMENT_UP) == 0)) {
            altdbncinc++;
			if (altdbncinc > multispeed) {
                n = multimul;
                MultiKnobLastCurrentUpTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentUpTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentUpTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentUpTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "Xsaitekpanels:MultiKnobLastCurrentUpTimeDiff = %f MultiAltKnobSpeedThreshold = %f\n",MultiKnobLastCurrentUpTimeDiff, MultiAltKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }
                if((xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiAltKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: alt up if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiAltKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
					if(altswitchremap == 1) {
                        while (n>0) {
                           XPLMCommandOnce(AltSwitchUpRemapableCmd);
                           --n;
                        }

                    } else {
                        if (log_enable == 1) {
                            sprintf(buf, "Xsaitekpanels: upapalt = %d ", upapalt);
                            XPLMDebugString(buf);
                        }
                        upapalt = upapalt + 1000;
                        upapalt = (upapalt / 1000);
                        upapalt = (upapalt * 1000);
                        altdbncinc = 0;
                        altbiginc = 1;
                        if (log_enable == 1) {
                            sprintf(buf, "upapalt + 1000 = %d\n\n", upapalt);
                            XPLMDebugString(buf);
                        }
                    }
                }
                MultiKnobLastCurrentUpTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if (xpanelsfnbutton == 0) {
                    if(altswitchremap == 1) {
                       XPLMCommandOnce(AltSwitchUpRemapableCmd);
                    } else {
                        if (altbiginc == 0) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: upapalt = %d ", upapalt);
                                XPLMDebugString(buf);
                            }
                            upapalt = upapalt + 100;
                            upapalt = (upapalt / 100);
                            upapalt = (upapalt * 100);
                            altdbncinc = 0;
                            if (log_enable == 1) {
                                sprintf(buf, "upapalt + 100 = %d\n\n", upapalt);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                }
            }
		}
        Last_Adjustment_Up = testbit(multibuf,ADJUSTMENT_UP);
        altbiginc = 0;

        if((Last_Adjustment_Dn == 1) && (testbit(multibuf,ADJUSTMENT_DN) == 0)) {
            altdbncdec++;
			if (altdbncdec > multispeed) {
                n = multimul;
                MultiKnobLastCurrentDnTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentDnTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentDnTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentDnTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "Xsaitekpanels: MultiKnobLastCurrentDnTimeDiff = %f MultiAltKnobSpeedThreshold = %f\n",MultiKnobLastCurrentDnTimeDiff, MultiAltKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }
                if((xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiAltKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: alt dn if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiAltKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
					if(altswitchremap == 1) {
                        while (n>0) {
                           XPLMCommandOnce(AltSwitchDnRemapableCmd);
                           --n;
                        }
                    } else {
                        if (upapalt >= 1000) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: upapalt = %d ", upapalt);
                                XPLMDebugString(buf);
                            }
                            upapalt = upapalt - 1000;
                            altbigdec = 1;
                            if (log_enable == 1) {
                                sprintf(buf, "upapalt - 1000 = %d\n\n", upapalt);
                                XPLMDebugString(buf);
                            }
                        }
                        if(upapalt > 100) {
                            upapalt = (upapalt / 100);
                            upapalt = (upapalt * 100);
                        }
                        altdbncdec = 0;
                    }
                }
                MultiKnobLastCurrentDnTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if (xpanelsfnbutton == 0) {
                     if(altswitchremap == 1) {
                        XPLMCommandOnce(AltSwitchDnRemapableCmd);
                     } else {
                         if (upapalt >= 100) {
                             if (altbigdec == 0) {
                                 if (log_enable == 1) {
                                     sprintf(buf, "Xsaitekpanels: upapalt = %d ", upapalt);
                                     XPLMDebugString(buf);
                                 }
                                 upapalt = upapalt - 100;
                                 if (log_enable == 1) {
                                     sprintf(buf, "upapalt - 100 = %d\n\n", upapalt);
                                     XPLMDebugString(buf);
                                 }
                             }
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
        Last_Adjustment_Dn = testbit(multibuf,ADJUSTMENT_DN);
        upapaltf = upapalt;
        altbigdec = 0;

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
        MultiVsKnobSpeedThreshold = (float)(multiaccelthreshold * .01);
        if (!AvPwrIsOn() || !BatPwrIsOn()) {
            multiseldis = 5;
        } else {
           multiseldis = 1;
        }

        if (vsswitchremap == 2) {
            upapvsf = XPLMGetDataf(VsSwitchRemapableData);
        } else {
            upapvsf = XPLMGetDataf(ApVs);
        }
        upapvs = (int)(upapvsf);
        if((Last_Adjustment_Up == 1) && (testbit(multibuf,ADJUSTMENT_UP) == 0)) {
            vsdbncinc++;
            if (vsdbncinc > multispeed) {
                n = multimul;
                MultiKnobLastCurrentUpTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentUpTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentUpTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentUpTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentUpTimeDiff = %f MultiVsKnobSpeedThreshold = %f\n",MultiKnobLastCurrentUpTimeDiff, MultiVsKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }
                if((xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiVsKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: vs up if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiVsKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                //if (xpanelsfnbutton == 1) {

                    if (vsswitchremap == 1) {
                        XPLMCommandOnce(VsSwitchUpRemapableCmd);
                        XPLMCommandOnce(VsSwitchUpRemapableCmd);
                    } else {
                        //XPLMCommandOnce(ApVsUp);
                        if (log_enable == 1) {
                            sprintf(buf, "Xsaitekpanels: upapvs = %d ", upapvs);
                            XPLMDebugString(buf);
                        }
                        upapvs = upapvs + 200;
                        upapvs = (upapvs / 100);
                        upapvs = (upapvs * 100);
                        vsbiginc = 1;
                        if (log_enable == 1) {
                            sprintf(buf, "upapvs + 200 = %d\n\n", upapvs);
                            XPLMDebugString(buf);
                        }
                    }
                    vsdbncinc = 0;

                }
                MultiKnobLastCurrentUpTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if (xpanelsfnbutton == 0) {
                    if (vsswitchremap == 1) {
                        XPLMCommandOnce(VsSwitchUpRemapableCmd);
                    } else {
                        if (vsbiginc == 0) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: upapvs = %d ", upapvs);
                                XPLMDebugString(buf);
                            }
                            //XPLMCommandOnce(ApVsUp);
                            upapvs = upapvs + 100;
                            upapvs = (upapvs / 100);
                            upapvs = (upapvs * 100);
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: upapvs + 100 = %d\n\n", upapvs);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                    vsdbncinc = 0;
                }
             }
		}
        Last_Adjustment_Up = testbit(multibuf,ADJUSTMENT_UP);
        vsbiginc = 0;

        if((Last_Adjustment_Dn == 1) && (testbit(multibuf,ADJUSTMENT_DN) == 0)) {
            vsdbncdec++;
            if (vsdbncdec > multispeed) {
                n = multimul;
                MultiKnobLastCurrentDnTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentDnTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentDnTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentDnTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentDnTimeDiff = %f MultiVsKnobSpeedThreshold = %f\n",MultiKnobLastCurrentDnTimeDiff, MultiVsKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }
                if((xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiVsKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: vs dn if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiVsKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                //if (xpanelsfnbutton == 1) {
                    if (vsswitchremap == 1) {
                        XPLMCommandOnce(VsSwitchDnRemapableCmd);
                        XPLMCommandOnce(VsSwitchDnRemapableCmd);
                    } else {
                        //XPLMCommandOnce(ApVsUp);
                        if (log_enable == 1) {
                            sprintf(buf, "Xsaitekpanels: upapvs = %d ", upapvs);
                            XPLMDebugString(buf);
                        }
                        upapvs = upapvs - 200;
                        if (upapvs > 100) {
                            upapvs = (upapvs / 100);
                            upapvs = (upapvs * 100);
                        }
                        if (upapvs < (-100)) {
                            upapvs = (upapvs / 100);
                            upapvs = (upapvs * 100);
                        }
                        vsbigdec = 1;
                        if (log_enable == 1) {
                            sprintf(buf, "upapvs - 200 = %d\n\n", upapvs);
                            XPLMDebugString(buf);
                        }
                    }
                }
                vsdbncdec = 0;
                MultiKnobLastCurrentDnTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if(xpanelsfnbutton == 0) {
                    if (vsswitchremap == 1) {
                        XPLMCommandOnce(VsSwitchDnRemapableCmd);
                    } else {
                        //XPLMCommandOnce(ApVsUp);
                        if (vsbigdec == 0) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: upapvs = %d ", upapvs);
                                XPLMDebugString(buf);
                            }
                            upapvs = upapvs - 100;
                            if (upapvs > 100) {
                                upapvs = (upapvs / 100);
                                upapvs = (upapvs * 100);
                            }
                            if (upapvs < (-100)) {
                                upapvs = (upapvs / 100);
                                upapvs = (upapvs * 100);
                            }
                            if (log_enable == 1) {
                                sprintf(buf, "upapvs - 100 = %d\n\n", upapvs);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                    vsdbncdec = 0;
                }
            }
        }
        Last_Adjustment_Dn = testbit(multibuf,ADJUSTMENT_DN);
        vsbigdec = 0;

        upapvsf = upapvs;
        if (vsswitchremap == 2) {
            XPLMSetDataf(VsSwitchRemapableData, upapvsf);
        } else if (vsswitchremap == 1) {
            upapvsf = XPLMGetDataf(VsSwitchRemapableData);
            upapvs = (int)(upapvsf);
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
        MultiIasKnobSpeedThreshold = (float)(multiaccelthreshold * .01);
        //multiseldis = 2;
        if (!AvPwrIsOn() || !BatPwrIsOn()) {
            multiseldis = 5;
        } else {
           multiseldis = 2;
        }

        if (iasismachremap == 1) {
            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                apmasf = XPLMGetDataf(IasSwitchRemapableData);
            } else {
                apasf = XPLMGetDataf(IasSwitchRemapableData);
            }
        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
            apmasf = XPLMGetDataf(ApAs);
        } else if ((iasswitchremap == 1) | (iasswitchremap == 2)) {
            apasf = XPLMGetDataf(IasSwitchRemapableData);
            apas = (int)(apasf);
        } else {
            apasf = XPLMGetDataf(ApAs);
            apas = (int)(apasf);
        }
        if ((Last_Adjustment_Up == 1) && (testbit(multibuf,ADJUSTMENT_UP) == 0)) {
            iasdbncinc++;
            if (iasdbncinc > multispeed) {
                n = multimul;
                MultiKnobLastCurrentUpTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentUpTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentUpTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentUpTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentUpTimeDiff = %f MultiIasKnobSpeedThreshold = %f\n",MultiKnobLastCurrentUpTimeDiff, MultiIasKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }

                if ((xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiIasKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: ias up if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiIasKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                    if (iasswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(IasSwitchUpRemapableCmd);
                            --n;
                        }
                    } else {
                        if (iasismachremap == 1) {
                            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                                apmasf = apmasf + .10;
                            } else {
                                apas = apas + 1;
                            }
                        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: apmasf = %f ", apmasf);
                                XPLMDebugString(buf);
                            }
                            apmasf = apmasf + .10;
                            if (log_enable == 1) {
                                sprintf(buf, "apmasf + .10 = %f\n\n", apmasf);
                                XPLMDebugString(buf);
                            }
                        } else {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: apas = %d ", apas);
                                XPLMDebugString(buf);
                            }
                            apas = apas + 10;
                            iasbiginc = 1;
                            if (log_enable == 1) {
                                sprintf(buf, "apas + 10 = %d\n\n", apas);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                    iasdbncinc = 0;
                }
                MultiKnobLastCurrentUpTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if (xpanelsfnbutton == 0) {
                    if (iasswitchremap == 1) {
                        XPLMCommandOnce(IasSwitchUpRemapableCmd);
                    } else if (iasswitchremap == 2) {
                        apas = apas + 1;
                    } else {
                        if (iasismachremap == 1) {
                            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                                apmasf = apmasf + .01;
                            } else {
                                apas = apas + 1;
                            }
                        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: apmasf = %f ", apmasf);
                                XPLMDebugString(buf);
                            }
                            apmasf = apmasf + .01;
                            if (log_enable == 1) {
                                sprintf(buf, "apmasf + .01 = %f\n\n", apmasf);
                                XPLMDebugString(buf);
                            }
                        } else {
                            if (iasbiginc == 0) {
                                if (log_enable == 1) {
                                    sprintf(buf, "Xsaitekpanels: apas = %d ", apas);
                                    XPLMDebugString(buf);
                                }
                                apas = apas + 1;
                                if (log_enable == 1) {
                                    sprintf(buf, "apas + 1 = %d\n\n", apas);
                                    XPLMDebugString(buf);
                                }
                            }
                        }
                    }
                    iasdbncinc = 0;
                }
            }
        }
        Last_Adjustment_Up = testbit(multibuf,ADJUSTMENT_UP);
        iasbiginc = 0;


        if ((Last_Adjustment_Dn == 1) && (testbit(multibuf,ADJUSTMENT_DN) == 0)) {
            iasdbncdec++;
            if (iasdbncdec > multispeed) {
                n = multimul;
                MultiKnobLastCurrentDnTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentDnTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentDnTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentDnTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentDnTimeDiff = %f MultiIasKnobSpeedThreshold = %f\n",MultiKnobLastCurrentDnTimeDiff, MultiIasKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }
                if ((xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiIasKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: ias dn if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiIasKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                    if (iasswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(IasSwitchDnRemapableCmd);
                            --n;
                        }
                    } else {
                       if (iasismachremap == 1) {
                           if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                               apmasf = apmasf - .01;
                           } else {
                               apas = apas - 1;
                           }
                       } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                           if (log_enable == 1) {
                               sprintf(buf, "Xsaitekpanels: apmasf = %f ", apmasf);
                               XPLMDebugString(buf);
                           }
                           apmasf = apmasf - .01;
                           if (log_enable == 1) {
                               sprintf(buf, "apmasf - .01 = %f\n\n", apmasf);
                               XPLMDebugString(buf);
                           }
                       } else {
                           if (log_enable == 1) {
                               sprintf(buf, "Xsaitekpanels: apas = %d ", apas);
                               XPLMDebugString(buf);
                           }
                           apas = apas - 10;
                           iasbigdec = 1;
                           if (log_enable == 1) {
                               sprintf(buf, "apas - 10 = %d\n\n", apas);
                               XPLMDebugString(buf);
                           }
                       }
                    }
                    iasdbncdec = 0;
                }
                MultiKnobLastCurrentDnTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time

                if (xpanelsfnbutton == 0) {
                    if (iasswitchremap == 1) {
                        XPLMCommandOnce(IasSwitchDnRemapableCmd);
                    } else if (iasswitchremap == 2) {
                        apas = apas - 1;
                    } else {
                        if (iasismachremap == 1) {
                            if (XPLMGetDatai(IasIsmachRemapableData) == iasismachvalue) {
                                apmasf = apmasf - .01;
                            } else {
                                apas = apas - 1;
                            }
                        } else if (XPLMGetDatai(AirspeedIsMach) == 1) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: apmasf = %f ", apmasf);
                                XPLMDebugString(buf);
                            }
                            apmasf = apmasf - .01;
                            if (log_enable == 1) {
                                sprintf(buf, "apmasf - .01 = %f\n\n", apmasf);
                                XPLMDebugString(buf);
                            }
                        } else {
                            if (iasbigdec == 0) {
                                if (log_enable == 1) {
                                    sprintf(buf, "Xsaitekpanels: apas = %d ", apas);
                                    XPLMDebugString(buf);
                                }
                                apas = apas - 1;
                                if (log_enable == 1) {
                                    sprintf(buf, "apas - 1 = %d\n\n", apas);
                                    XPLMDebugString(buf);
                                }
                            }
                        }
                    }
                    iasdbncdec = 0;
                }
            }
        }
        Last_Adjustment_Dn = testbit(multibuf,ADJUSTMENT_DN);
        iasbigdec = 0;

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
            if ((iasswitchremap == 1) | (iasswitchremap == 2)) {
                XPLMSetDataf(IasSwitchRemapableData, apasf);
            } else {
                XPLMSetDataf(ApAs, apasf);
            }
        }
    }
}

// ***************** HDG Switch Position *******************
void process_hdg_switch()
{

    if(testbit(multibuf,HDG_SWITCH)) {
        MultiHdgKnobSpeedThreshold = (float)(multiaccelthreshold * .01);
        //multiseldis = 3;
        if (!AvPwrIsOn() || !BatPwrIsOn()) {
            multiseldis = 5;
        } else {
           multiseldis = 3;
        }

        if (hdgswitchremap == 2) {
            upaphdgf = XPLMGetDataf(HdgSwitchRemapableData);
        } else {
            upaphdgf = XPLMGetDataf(ApHdg);
        }

        upaphdg = (int)(upaphdgf);
        if((Last_Adjustment_Up == 1) && (testbit(multibuf,ADJUSTMENT_UP) == 0)) {
            hdgdbncinc++;
            if (hdgdbncinc > multispeed) {
                n = multimul;
                MultiKnobLastCurrentUpTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentUpTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentUpTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentUpTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentUpTimeDiff = %f MultiHdgKnobSpeedThreshold = %f\n",MultiKnobLastCurrentUpTimeDiff, MultiHdgKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }

                if((xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiHdgKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: hdg up if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiHdgKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                    if (hdgswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(HdgSwitchUpRemapableCmd);
                            --n;
                        }
                    } else {
                        if (log_enable == 1) {
                            sprintf(buf, "Xsaitekpanels: upaphdg = %d ", upaphdg);
                            XPLMDebugString(buf);
                        }
                        upaphdg = upaphdg + 10;
                        hdgbiginc = 1;
                        if (log_enable == 1) {
                            sprintf(buf, "upaphdg + 10 = %d\n\n", upaphdg);
                            XPLMDebugString(buf);
                        }
                    }
                    hdgdbncinc = 0;

                }
                MultiKnobLastCurrentUpTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if(xpanelsfnbutton == 0) {
                    if (hdgswitchremap == 1) {
                        XPLMCommandOnce(HdgSwitchUpRemapableCmd);
                    } else {
                        if (hdgbiginc == 0) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: upaphdg = %d ", upaphdg);
                                XPLMDebugString(buf);
                            }
                            upaphdg = upaphdg + 1;
                            if (log_enable == 1) {
                                sprintf(buf, "upaphdg + 1 = %d\n\n", upaphdg);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                    hdgdbncinc = 0;
                }
            }
        }
        Last_Adjustment_Up = testbit(multibuf,ADJUSTMENT_UP);
        hdgbiginc = 0;

        if((Last_Adjustment_Dn == 1) && (testbit(multibuf,ADJUSTMENT_DN) == 0)) {
            hdgdbncdec++;
            if (hdgdbncdec > multispeed) {
                n = multimul;
                MultiKnobLastCurrentDnTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentDnTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentDnTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentDnTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentDnTimeDiff = %f MultiHdgKnobSpeedThreshold = %f\n",MultiKnobLastCurrentDnTimeDiff, MultiHdgKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }
                if((xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiHdgKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: hdg up if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiHdgKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                    if (hdgswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(HdgSwitchDnRemapableCmd);
                            --n;
                        }
                    } else {
                        if (log_enable == 1) {
                            sprintf(buf, "Xsaitekpanels: upaphdg = %d ", upaphdg);
                            XPLMDebugString(buf);
                        }
                        upaphdg = upaphdg - 10;
                        hdgbigdec = 1;
                        if (log_enable == 1) {
                            sprintf(buf, "upaphdg - 10 = %d\n\n", upaphdg);
                            XPLMDebugString(buf);
                        }
                    }
                    hdgdbncdec = 0;
                }
                MultiKnobLastCurrentDnTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if(xpanelsfnbutton == 0) {
                    if (hdgswitchremap == 1) {
                        XPLMCommandOnce(HdgSwitchDnRemapableCmd);
                    } else {
                        if (hdgbigdec == 0) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: upaphdg = %d ", upaphdg);
                                XPLMDebugString(buf);
                            }
                            upaphdg = upaphdg - 1;
                            if (log_enable == 1) {
                                sprintf(buf, "upaphdg - 1 = %d\n\n", upaphdg);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                    hdgdbncdec = 0;
                }
            }
        }
        Last_Adjustment_Dn = testbit(multibuf,ADJUSTMENT_DN);
        hdgbigdec = 0;

        if(upaphdg > 360) {
            upaphdg = 1;
        }
        if(upaphdg < 0) {
            upaphdg = 359;
        }
        upaphdgf = upaphdg;
        if (hdgswitchremap == 2) {
            XPLMSetDataf(HdgSwitchRemapableData, upaphdgf);
        } else if (hdgswitchremap == 1) {
            upaphdgf = XPLMGetDataf(HdgSwitchRemapableData);
            upaphdg = (int)(upaphdgf);
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
         MultiCrsKnobSpeedThreshold = (float)(multiaccelthreshold * .01);
        //multiseldis = 4;
        if (!AvPwrIsOn() || !BatPwrIsOn()) {
            multiseldis = 5;
        } else {
           multiseldis = 4;
        }

        upapcrsf = XPLMGetDataf(ApCrs);
        upapcrs = (int)(upapcrsf);

        if ((crsswitchremap == 1) || (crsswitchremap == 2)) {
            cur_apcrsf = XPLMGetDataf(CrsSwitchRemapableData);
        } else {
            //  get the appropriate course setting depending on if the toggle is down
            cur_apcrsf = XPLMGetDataf(crs_dataref);
        }
        cur_apcrs = (int)(cur_apcrsf);
        if((Last_Adjustment_Up == 1) && (testbit(multibuf,ADJUSTMENT_UP) == 0)) {
            crsdbncinc++;
            if (crsdbncinc > multispeed) {
                n = multimul;
                MultiKnobLastCurrentUpTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentUpTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentUpTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentUpTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentUpTimeDiff = %f MultiCrsKnobSpeedThreshold = %f\n",MultiKnobLastCurrentUpTimeDiff, MultiCrsKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }

                if ((xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiCrsKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: crs up if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentUpTimeDiff < MultiCrsKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                    if (crsswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(CrsSwitchUpRemapableCmd);
                            --n;
                        }
                    } else {
                        if (log_enable == 1) {
                            sprintf(buf, "Xsaitekpanels: cur_apcrs = %d ", cur_apcrs);
                            XPLMDebugString(buf);
                        }
                        cur_apcrs = cur_apcrs + 10;
                        crsbiginc = 1;
                        if (log_enable == 1) {
                            sprintf(buf, "cur_apcrs + 10 = %d\n\n", cur_apcrs);
                            XPLMDebugString(buf);
                        }
                    }
                }
                MultiKnobLastCurrentUpTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if(xpanelsfnbutton == 0) {
                    if (crsswitchremap == 1) {
                        XPLMCommandOnce(CrsSwitchUpRemapableCmd);
                    } else {
                        if (crsbiginc == 0) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: cur_apcrs = %d ", cur_apcrs);
                                XPLMDebugString(buf);
                            }
                            cur_apcrs = cur_apcrs + 1;
                            if (log_enable == 1) {
                                sprintf(buf, "cur_apcrs + 1 = %d\n\n", cur_apcrs);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                }
                crsdbncinc = 0;
            }
        }
        Last_Adjustment_Up = testbit(multibuf,ADJUSTMENT_UP);
        crsbiginc = 0;

        if((Last_Adjustment_Dn == 1) && (testbit(multibuf,ADJUSTMENT_DN) == 0)) {
            crsdbncdec++;
            if (crsdbncdec > multispeed) {
                n = multimul;
                MultiKnobLastCurrentDnTimeDiff = wrgCurrentTime -  MultiKnobLastCurrentDnTime;
                if (log_enable == 1) {
                    sprintf(buf, "Xsaitekpanels: wrgCurrentTime = %f MultiKnobLastCurrentDnTime = %f\n",wrgCurrentTime, MultiKnobLastCurrentDnTime);
                    XPLMDebugString(buf);
                    sprintf(buf, "MultiKnobLastCurrentDnTimeDiff = %f MultiCrsKnobSpeedThreshold = %f\n",MultiKnobLastCurrentDnTimeDiff, MultiCrsKnobSpeedThreshold);
                    XPLMDebugString(buf);
                }

                if ((xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiCrsKnobSpeedThreshold)) {  // Steve Bootes : add test for MultiKnob rotation time)
                    if (log_enable == 1) {
                        sprintf(buf, "Xsaitekpanels: crs dn if true (xpanelsfnbutton == 1) || (MultiKnobLastCurrentDnTimeDiff < MultiCrsKnobSpeedThreshold)\n");
                        XPLMDebugString(buf);
                    }
                    if (crsswitchremap == 1) {
                        while (n>0) {
                            XPLMCommandOnce(CrsSwitchDnRemapableCmd);
                            --n;
                        }
                    } else {
                        if (log_enable == 1) {
                            sprintf(buf, "Xsaitekpanels: cur_apcrs = %d ", cur_apcrs);
                            XPLMDebugString(buf);
                        }
                        cur_apcrs = cur_apcrs - 10;
                        crsbigdec = 1;
                        if (log_enable == 1) {
                            sprintf(buf, "cur_apcrs - 10 = %d\n\n", cur_apcrs);
                            XPLMDebugString(buf);
                        }
                    }

                }
                MultiKnobLastCurrentDnTime = wrgCurrentTime; // Steve Bootes  Bill Good: set last current time to current time
                if(xpanelsfnbutton == 0) {
                    if (crsswitchremap == 1) {
                        XPLMCommandOnce(CrsSwitchDnRemapableCmd);
                    } else {
                        if (crsbigdec == 0) {
                            if (log_enable == 1) {
                                sprintf(buf, "Xsaitekpanels: cur_apcrs = %d ", cur_apcrs);
                                XPLMDebugString(buf);
                            }
                            cur_apcrs = cur_apcrs - 1;
                            if (log_enable == 1) {
                                sprintf(buf, "cur_apcrs - 1 = %d\n\n", cur_apcrs);
                                XPLMDebugString(buf);
                            }
                        }
                    }
                }

                crsdbncdec = 0;
            }
        }
        Last_Adjustment_Dn = testbit(multibuf,ADJUSTMENT_DN);
        crsbigdec = 0;

        if(cur_apcrs > 360) {
            cur_apcrs = 1;
        }

        if(cur_apcrs < 0) {
            cur_apcrs = 359;
        }

        cur_apcrsf = cur_apcrs;
        if (crsswitchremap == 1) {
            upapcrsf = XPLMGetDataf(CrsSwitchRemapableData);
            upapcrs = (int)(upapcrsf);
        } else if (crsswitchremap == 2) {
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
            if(autothrottleswitcharmedvalue == 1) {
               XPLMSetDatai(AttrSwitchRemapableData, 1);
            } else {
               XPLMSetDatai(AttrSwitchRemapableData, 0);
            }

        } else {
            XPLMSetDatai(ApAutThr, 1);
        }
    } else {
        if (attrswitchremap == 2) {
            if(autothrottleswitcharmedvalue == 1) {
                XPLMSetDatai(AttrSwitchRemapableData, 0);
            } else {
               XPLMSetDatai(AttrSwitchRemapableData, 1);
            }

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
        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(ApLightRemapableData) > .50) {
                aplightdata = 1;
            } else if (XPLMGetDataf(ApLightRemapableData) < .50) {
                aplightdata = 0;
            }
            switch(aplightdata) {
            case 1:
                btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(ApLightFlashRemapableData) > .50) {
                    aplightflashdata = 1;
                } else if (XPLMGetDataf(ApLightFlashRemapableData) < .50) {
                    aplightflashdata = 0;
                }
                if (aplightflashdata) {
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
        } else if (lightdatareferencetype == 2) {
                switch(XPLMGetDatai(ApLightRemapableData)) {
                case 1:
                    btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                    break;
                case 0:
                    aplightflashdata = XPLMGetDatai(ApLightFlashRemapableData);
                    if (aplightflashdata) {
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

        } else if (lightdatareferencetype == 3) {
            aplightdata = XPLMGetDatai(ApLightRemapableData);
            switch(aplightdata) {
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

    } else if (apbuttonremap == 2) {
            if (appushed == 0) {
                if (testbit(multibuf, AP_MASTER_BUTTON)) {
                    XPLMSetDatai(ApButtonRemapableData, 1);
                    appushed = 1;
                    lastappos = 1;
                } else if (!testbit(multibuf, AP_MASTER_BUTTON)) {
                    XPLMSetDatai(ApButtonRemapableData, 0);
                }
            }

            if (appushed == 1) {
                aploop++;
                if (aploop == 50) {
                   appushed = 0;
                   aploop = 0;
                }
            }
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(ApLightRemapableData) > .50) {
                    aplightdata = 1;
                } else if (XPLMGetDataf(ApLightRemapableData) < .50) {
                    aplightdata = 0;
                }
                switch(aplightdata) {
                case 1:
                    btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                    break;
                case 0:
                    if (XPLMGetDataf(ApLightFlashRemapableData) > .50) {
                        aplightflashdata = 1;
                    } else if (XPLMGetDataf(ApLightFlashRemapableData) < .50) {
                            aplightflashdata = 0;
                    }
                    if (aplightflashdata) {
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
            } else if (lightdatareferencetype == 2) {

                    switch(XPLMGetDatai(ApLightRemapableData)) {
                    case 1:
                        btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                        break;
                    case 0:
                        aplightflashdata = XPLMGetDatai(ApLightFlashRemapableData);

                        if (aplightflashdata) {
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

            } else if (lightdatareferencetype == 3) {
                aplightdata = XPLMGetDatai(ApLightRemapableData);
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

    } else if (apbuttonremap == 3) {
        if (appushed == 0) {
            if (testbit(multibuf, AP_MASTER_BUTTON)) {
                lastappos = XPLMGetDatai(ApButtonRemapableData);
                appushed = 1;
                if (lastappos == 1) {
                    XPLMSetDatai(ApButtonRemapableData, 0);
                } else {
                    XPLMSetDatai(ApButtonRemapableData, 1);

                }

            }
        }

        if (appushed == 1) {
            aploop++;
            if (aploop == 50) {
               appushed = 0;
               aploop = 0;
            }
        }
        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(ApLightRemapableData) > .50) {
                aplightdata = 1;
            } else if (XPLMGetDataf(ApLightRemapableData) < .50) {
                aplightdata = 0;
            }
            switch(aplightdata) {
            case 1:
                btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(ApLightFlashRemapableData) > .50) {
                    aplightflashdata = 1;
                } else if (XPLMGetDataf(ApLightFlashRemapableData) < .50) {
                        aplightflashdata = 0;
                }
                if (aplightflashdata) {
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
        } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(ApLightRemapableData)) {
                case 1:
                    btnleds |= (1<<0);   // * set bit 0 in btnleds to 1 *
                    break;
                case 0:
                    aplightflashdata = XPLMGetDatai(ApLightFlashRemapableData);

                    if (aplightflashdata) {
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

        } else if (lightdatareferencetype == 3) {
            aplightdata = XPLMGetDatai(ApLightRemapableData);
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
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(HdgLightRemapableData) > .50) {
                    hdglightdata = 1;
                } else if (XPLMGetDataf(HdgLightRemapableData) < .50) {
                    hdglightdata = 0;
                }
                switch(hdglightdata) {
                case 1:
                    btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                    break;
                case 0:
                    if (XPLMGetDataf(HdgLightFlashRemapableData) > .50) {
                        hdglightflashdata = 1;
                    } else if (XPLMGetDataf(HdgLightFlashRemapableData) < .50) {
                        hdglightflashdata = 0;
                    }
                    if (hdglightflashdata) {
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

              } else if (lightdatareferencetype == 2) {

                    switch(XPLMGetDatai(HdgLightRemapableData)) {
                    case 1:
                        btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                        break;
                    case 0:
                        hdglightflashdata = XPLMGetDatai(HdgLightFlashRemapableData);

                        if (hdglightflashdata) {
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

            } else if (lightdatareferencetype == 3) {
                hdglightdata = XPLMGetDatai(HdgLightRemapableData);
                switch(hdglightdata) {
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

    } else if (hdgbuttonremap == 2) {
        if (multires > 0) {
            if (testbit(multibuf, HDG_BUTTON)) {
                XPLMSetDatai(HdgButtonRemapableData, 1);
                lastappos = 1;
            } else if (!testbit(multibuf, HDG_BUTTON)) {
                XPLMSetDatai(HdgButtonRemapableData, 0);
                lastappos = 1;
            }
        }
        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(HdgLightRemapableData) > .50) {
                hdglightdata = 1;
            } else if (XPLMGetDataf(HdgLightRemapableData) < .50) {
                hdglightdata = 0;
            }
            switch(hdglightdata) {
            case 1:
                btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(HdgLightFlashRemapableData) > .50) {
                    hdglightflashdata = 1;
                } else if (XPLMGetDataf(HdgLightFlashRemapableData) < .50) {
                    hdglightflashdata = 0;
                }
                if (hdglightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(HdgLightRemapableData)) {
                case 1:
                    btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                    break;
                case 0:
                    hdglightflashdata = XPLMGetDatai(HdgLightFlashRemapableData);

                    if (hdglightflashdata) {
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

        } else if (lightdatareferencetype == 3) {
            hdglightdata = XPLMGetDatai(HdgLightRemapableData);
            switch(hdglightdata) {
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

    } else if (hdgbuttonremap == 3) {
        if (multires > 0) {
            if (testbit(multibuf, HDG_BUTTON)) {
                lastappos = XPLMGetDatai(HdgButtonRemapableData);
                if (lastappos == 1) {
                    XPLMSetDatai(HdgButtonRemapableData, 0);
                } else {
                    XPLMSetDatai(HdgButtonRemapableData, 1);
                }

            }
        }
        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(HdgLightRemapableData) > .50) {
                hdglightdata = 1;
            } else if (XPLMGetDataf(HdgLightRemapableData) < .50) {
                hdglightdata = 0;
            }
            switch(hdglightdata) {
            case 1:
                btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(HdgLightFlashRemapableData) > .50) {
                    hdglightflashdata = 1;
                } else if (XPLMGetDataf(HdgLightFlashRemapableData) < .50) {
                    hdglightflashdata = 0;
                }
                if (hdglightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(HdgLightRemapableData)) {
                case 1:
                    btnleds |= (1<<1);   // * set bit 1 in btnleds to 1 *
                    break;
                case 0:
                    hdglightflashdata = XPLMGetDatai(HdgLightFlashRemapableData);

                    if (hdglightflashdata) {
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

        } else if (lightdatareferencetype == 3) {
            hdglightdata = XPLMGetDatai(HdgLightRemapableData);
            switch(hdglightdata) {
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
        
        switch(XPLMGetDatai(ApHdgStat)) {
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
    if (navbuttonremap == 1) {
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
        switch (XPLMGetDatai(HsiSelector)) {
        case 0:
        case 1:
            // Use LED to match power state
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(NavLightVorlocRemapableData) > .50) {
                    navlightvorlocdata = 1;
                } else if (XPLMGetDataf(NavLightVorlocRemapableData) < .50) {
                    navlightvorlocdata = 0;
                }
                switch(navlightvorlocdata) {
                case 1:
                    btnleds |= (1<<2);
                    break;
                case 0:
                    if (XPLMGetDataf(NavLightVorlocFlashRemapableData) > .50) {
                        navlightflashvorlocdata = 1;
                    } else if (XPLMGetDataf(NavLightVorlocFlashRemapableData) < .50) {
                        navlightflashvorlocdata = 0;
                    }
                    if (navlightflashvorlocdata) {
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

            } else if (lightdatareferencetype == 2) {

                    switch(XPLMGetDatai(NavLightVorlocRemapableData)) {
                    case 1:
                        btnleds |= (1<<2);
                        break;
                    case 0:
                        navlightflashvorlocdata = XPLMGetDatai(NavLightVorlocFlashRemapableData);

                        if (navlightflashvorlocdata) {
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

            } else if (lightdatareferencetype == 3) {
                navlightvorlocdata = XPLMGetDatai(NavLightVorlocRemapableData);
                switch(navlightvorlocdata) {
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

            break;
        case 2:
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(NavLightLnavRemapableData) > .50) {
                    navlightlnavdata = 1;
                } else if (XPLMGetDataf(NavLightLnavRemapableData) < .50) {
                    navlightlnavdata = 0;
                }
                switch(navlightlnavdata) {

                case 1:
                    btnleds |= (1<<2);
                    break;
                case 0:
                    if (XPLMGetDataf(NavLightLnavFlashRemapableData) > .50) {
                        navlightflashlnavdata = 1;
                    } else if (XPLMGetDataf(NavLightLnavFlashRemapableData) < .50) {
                         navlightflashlnavdata = 0;
                    }
                    if (navlightflashlnavdata) {
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

            } else if (lightdatareferencetype == 2) {

                    switch(XPLMGetDatai(NavLightLnavRemapableData)) {

                    case 1:
                        btnleds |= (1<<2);
                        break;
                    case 0:
                        navlightflashlnavdata = XPLMGetDatai(NavLightLnavFlashRemapableData);

                        if (navlightflashlnavdata) {
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


            } else if (lightdatareferencetype == 3) {
                navlightlnavdata = XPLMGetDatai(NavLightLnavRemapableData);
                switch(XPLMGetDatai(ApNavStat)) {
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
            break;
        }


    } else if (navbuttonremap == 2) {
        if (multires > 0) {
            if(testbit(multibuf,NAV_BUTTON)) {
                switch (XPLMGetDatai(HsiSelector)) {
                case 0:
                case 1:
                    XPLMSetDatai(NavButtonVorlocRemapableData, 1);
                    break;
                case 2:
                    XPLMSetDatai(NavButtonLnavRemapableData, 1);
                    break;
                }
                lastappos = 1;
            }
        } else if(!testbit(multibuf,NAV_BUTTON)) {
                switch (XPLMGetDatai(HsiSelector)) {
                case 0:
                case 1:
                    XPLMSetDatai(NavButtonVorlocRemapableData, 0);
                    break;
                case 2:
                    XPLMSetDatai(NavButtonLnavRemapableData, 0);
                    break;
                }
                lastappos = 1;
            }

        switch (XPLMGetDatai(HsiSelector)) {
        case 0:
        case 1:
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(NavLightVorlocRemapableData) > .50) {
                    navlightvorlocdata = 1;
                } else if (XPLMGetDataf(NavLightVorlocRemapableData) < .50) {
                    navlightvorlocdata = 0;
                }
                switch(navlightvorlocdata) {
                case 1:
                    btnleds |= (1<<2);
                    break;
                case 0:
                    if (XPLMGetDataf(NavLightVorlocFlashRemapableData) > .50) {
                        navlightflashvorlocdata = 1;
                    } else if (XPLMGetDataf(NavLightVorlocFlashRemapableData) < .50) {
                        navlightflashvorlocdata = 0;
                    }
                    if (navlightflashvorlocdata) {
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

            } else if (lightdatareferencetype == 2) {

                    switch(XPLMGetDatai(NavLightVorlocRemapableData)) {
                    case 1:
                        btnleds |= (1<<2);
                        break;
                    case 0:
                        navlightflashvorlocdata = XPLMGetDatai(NavLightVorlocFlashRemapableData);

                        if (navlightflashvorlocdata) {
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

            } else if (lightdatareferencetype == 3) {
                navlightvorlocdata = XPLMGetDatai(NavLightVorlocRemapableData);
                switch(navlightvorlocdata) {
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

            break;
        case 2:
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(NavLightLnavRemapableData) > .50) {
                    navlightlnavdata = 1;
                } else if (XPLMGetDataf(NavLightLnavRemapableData) < .50) {
                    navlightlnavdata = 0;
                }
                switch (navlightlnavdata) {
                case 1:
                    btnleds |= (1<<2);
                    break;
                case 0:
                    if (XPLMGetDataf(NavLightLnavFlashRemapableData) > .50) {
                        navlightflashlnavdata = 1;
                    } else if (XPLMGetDataf(NavLightLnavFlashRemapableData) < .50) {
                        navlightflashlnavdata = 0;
                    }
                    if (navlightflashlnavdata) {
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

            } else if (lightdatareferencetype == 2) {

                    switch (XPLMGetDatai(NavLightLnavRemapableData)) {
                    case 1:
                        btnleds |= (1<<2);
                        break;
                    case 0:
                        navlightflashlnavdata = XPLMGetDatai(NavLightLnavFlashRemapableData);

                        if (navlightflashlnavdata) {
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


            } else if (lightdatareferencetype == 3) {
                navlightlnavdata = XPLMGetDatai(NavLightLnavRemapableData);
                switch(XPLMGetDatai(ApNavStat)) {
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
           break;
        }

    } else if (navbuttonremap == 3) {
        if (multires > 0) {
            if(testbit(multibuf,NAV_BUTTON)) {
                lastappos = XPLMGetDatai(NavButtonVorlocRemapableData);
                lastappos2 = XPLMGetDatai(NavButtonLnavRemapableData);
                switch (XPLMGetDatai(HsiSelector)) {
                case 0:
                case 1:
                    if (lastappos == 1) {
                        XPLMSetDatai(NavButtonVorlocRemapableData, 0);
                    } else {
                        XPLMSetDatai(NavButtonVorlocRemapableData, 1);
                    }
                    break;
                case 2:
                    if (lastappos2 == 1) {
                        XPLMSetDatai(NavButtonLnavRemapableData, 0);
                    } else {
                        XPLMSetDatai(NavButtonLnavRemapableData, 1);
                    }

                    break;
                }

            }
        }

        switch (XPLMGetDatai(HsiSelector)) {
        case 0:
        case 1:
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(NavLightVorlocRemapableData) > .50) {
                    navlightvorlocdata = 1;
                } else if (XPLMGetDataf(NavLightVorlocRemapableData) < .50) {
                    navlightvorlocdata = 0;
                }
                switch(navlightvorlocdata) {
                case 1:
                    btnleds |= (1<<2);
                    break;
                case 0:
                    if (XPLMGetDataf(NavLightVorlocFlashRemapableData) > .50) {
                        navlightflashvorlocdata = 1;
                    } else if (XPLMGetDataf(NavLightVorlocFlashRemapableData) < .50) {
                        navlightflashvorlocdata = 0;
                    }
                    if (navlightflashvorlocdata) {
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

            } else if (lightdatareferencetype == 2) {

                    switch(XPLMGetDatai(NavLightVorlocRemapableData)) {
                    case 1:
                        btnleds |= (1<<2);
                        break;
                    case 0:
                        navlightflashvorlocdata = XPLMGetDatai(NavLightVorlocFlashRemapableData);

                        if (navlightflashvorlocdata) {
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

            } else if (lightdatareferencetype == 3) {
                navlightvorlocdata = XPLMGetDatai(NavLightVorlocRemapableData);
                switch(XPLMGetDatai(NavLightVorlocRemapableData)) {
                  case 2:
                    btnleds |= (1<<2);   // * set bit 2 in btnleds to 1 *
                    break;
                  case 1:
                    if (flashon == 1) {
                    btnleds |= (1<<2);   // * set bit 1 in btnleds to 1 *
                    } else {
                        btnleds &= ~(1<<2);   // * clear bit 2 in btnleds to 0 *
                    }
                    break;
                  case 0:
                        btnleds &= ~(1<<2);   // * clear bit 2 in btnleds to 0 *
                    break;
                }
            }

            break;
        case 2:
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(NavLightLnavRemapableData) > .50) {
                    navlightlnavdata = 1;
                } else if (XPLMGetDataf(NavLightLnavRemapableData) < .50) {
                    navlightlnavdata = 0;
                }
                switch (navlightlnavdata) {
                case 1:
                    btnleds |= (1<<2);
                    break;
                case 0:
                    if (XPLMGetDataf(NavLightLnavFlashRemapableData) > .50) {
                        navlightflashlnavdata = 1;
                    } else if (XPLMGetDataf(NavLightLnavFlashRemapableData) < .50) {
                        navlightflashlnavdata = 0;
                    }
                    if (navlightflashlnavdata) {
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

            } else if (lightdatareferencetype == 2) {

                    switch (XPLMGetDatai(NavLightLnavRemapableData)) {
                    case 1:
                        btnleds |= (1<<2);
                        break;
                    case 0:
                        navlightflashlnavdata = XPLMGetDatai(NavLightLnavFlashRemapableData);

                        if (navlightflashlnavdata) {
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


            } else if (lightdatareferencetype == 3) {
                navlightlnavdata = XPLMGetDatai(NavLightLnavRemapableData);
                switch(XPLMGetDatai(ApNavStat)) {
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
           break;
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

    switch(XPLMGetDatai(ApNavStat)) {
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

       if (iasbuttonremap == 1) {
           if (multires > 0) {
               if (testbit(multibuf, IAS_BUTTON)) {
                   if (xpanelsfnbutton == 1) {
                       XPLMCommandOnce(IasChangeoverButtonRemapableCmd);
                   }
                   if (xpanelsfnbutton == 0) {
                       XPLMCommandOnce(IasButtonRemapableCmd);
                       lastappos = 1;
                   }

               }
           }
           if (lightdatareferencetype == 1) {
               if (XPLMGetDataf(IasLightRemapableData) > .50) {
                   iaslightdata = 1;

               } else if (XPLMGetDataf(IasLightRemapableData) < .50) {
                   iaslightdata = 0;
               }
               switch(iaslightdata) {
               case 1:
                   btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                   break;
               case 0:
                   if (XPLMGetDataf(IasLightFlashRemapableData) > .50) {
                       iaslightflashdata = 1;
                   } else if (XPLMGetDataf(IasLightFlashRemapableData) < .50) {
                       iaslightflashdata = 0;
                   }
                   if (iaslightflashdata) {
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

           } else if (lightdatareferencetype == 2) {

                   switch(XPLMGetDatai(IasLightRemapableData)) {
                   case 1:
                       btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                       break;
                   case 0:
                       iaslightflashdata = XPLMGetDatai(IasLightFlashRemapableData);

                       if (iaslightflashdata) {
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

            } else if (lightdatareferencetype == 3) {
               iaslightdata = XPLMGetDatai(IasLightRemapableData);
               switch(iaslightdata) {
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


       } else  if (iasbuttonremap == 2) {
           if (multires > 0) {
               if (testbit(multibuf, IAS_BUTTON)) {
                   if (xpanelsfnbutton == 1) {
                       XPLMSetDatai(IasChangeoverButtonRemapableData, 1);
                   }
                   if (xpanelsfnbutton == 0) {
                       XPLMSetDatai(IasButtonRemapableData, 1);
                       lastappos = 1;
                   }
               }
           } else if (!testbit(multibuf, IAS_BUTTON)) {
                   if (xpanelsfnbutton == 1) {
                       XPLMSetDatai(IasChangeoverButtonRemapableData, 0);
                   }
                   if (xpanelsfnbutton == 0) {
                       XPLMSetDatai(IasButtonRemapableData, 0);
                       lastappos = 1;
                   }
           }
           if (lightdatareferencetype == 1) {
               if (XPLMGetDataf(IasLightRemapableData) > .50) {
                   iaslightdata = 1;
               } else if (XPLMGetDataf(IasLightRemapableData) < .50) {
                   iaslightdata = 0;
               }
               switch(iaslightdata) {
               case 1:
                   btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                   break;
               case 0:
                   if (XPLMGetDataf(IasLightFlashRemapableData) > .50) {
                       iaslightflashdata = 1;
                   } else if (XPLMGetDataf(IasLightFlashRemapableData) < .50) {
                       iaslightflashdata = 0;
                   }
                   if (iaslightflashdata) {
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

           } else if (lightdatareferencetype == 2) {

                   switch(XPLMGetDatai(IasLightRemapableData)) {
                   case 1:
                       btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                       break;
                   case 0:
                       iaslightflashdata = XPLMGetDatai(IasLightFlashRemapableData);

                       if (iaslightflashdata) {
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

           } else if (lightdatareferencetype == 3) {
               iaslightdata = XPLMGetDatai(IasLightRemapableData);
               switch(iaslightdata) {
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


       } else  if (iasbuttonremap == 3) {
           if (multires > 0) {
               if (xpanelsfnbutton == 1) {
                   if (testbit(multibuf, IAS_BUTTON)) {
                       XPLMSetDatai(IasChangeoverButtonRemapableData, 1);
                   } else if (!testbit(multibuf, IAS_BUTTON)) {
                       XPLMSetDatai(IasChangeoverButtonRemapableData, 0);
                   }
               }
               if (xpanelsfnbutton == 0) {
                   if (testbit(multibuf, IAS_BUTTON)) {
                       lastappos = XPLMGetDatai(IasButtonRemapableData);
                       if (lastappos == 1) {
                           XPLMSetDatai(IasButtonRemapableData, 0);
                       } else {
                           XPLMSetDatai(IasButtonRemapableData, 1);

                       }
                   }
               }
           }
           if (lightdatareferencetype == 1) {
               if (XPLMGetDataf(IasLightRemapableData) > .50) {
                   iaslightdata = 1;
               } else if (XPLMGetDataf(IasLightRemapableData) < .50) {
                   iaslightdata = 0;
               }
               switch(iaslightdata) {
               case 1:
                   btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                   break;
               case 0:
                   if (XPLMGetDataf(IasLightFlashRemapableData) > .50) {
                       iaslightflashdata = 1;
                   } else if (XPLMGetDataf(IasLightFlashRemapableData) < .50) {
                       iaslightflashdata = 0;
                   }
                   if (iaslightflashdata) {
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

           } else if (lightdatareferencetype == 2) {

                   switch(XPLMGetDatai(IasLightRemapableData)) {
                   case 1:
                       btnleds |= (1<<3);   // * set bit 3 in btnleds to 1 *
                       break;
                   case 0:
                       iaslightflashdata = XPLMGetDatai(IasLightFlashRemapableData);

                       if (iaslightflashdata) {
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

           } else if (lightdatareferencetype == 3) {
               iaslightdata = XPLMGetDatai(IasLightRemapableData);
               switch(iaslightdata) {
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
        switch(XPLMGetDatai(ApIasStat)) {
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
         if (lightdatareferencetype == 0) {
             switch(XPLMGetDatai(ApAltStat)) {
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

         } else if (lightdatareferencetype == 1) {
             if (XPLMGetDataf(AltLightRemapableData) > .50) {
                 altlightdata = 1;
             } else if (XPLMGetDataf(AltLightRemapableData) < .50) {
                 altlightdata = 0;
             }
             switch(altlightdata) {
             case 1:
                 btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                 break;
             case 0:
                 if (XPLMGetDataf(AltLightFlashRemapableData) > .50) {
                     altlightflashdata = 1;
                 } else if (XPLMGetDataf(AltLightFlashRemapableData) < .50) {
                     altlightflashdata = 0;
                 }
                 if (altlightflashdata) {
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

         } else if (lightdatareferencetype == 2) {

                 switch(XPLMGetDatai(AltLightRemapableData)) {
                 case 1:
                     btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                     break;
                 case 0:
                     altlightflashdata = XPLMGetDatai(AltLightFlashRemapableData);

                     if (altlightflashdata) {
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

         } else if (lightdatareferencetype == 3) {
             altlightdata = XPLMGetDatai(AltLightRemapableData);
             switch(altlightdata) {
             case 2:
                 btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                 break;
             case 1:
                 if (flashon == 1) {
                     btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                 } else {
                     btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
                 }
                 break;
             case 0:
                 btnleds &= ~(1<<4);   // * clear bit 4 in btnleds to 0 *
                 break;
             }
         }

     } else if (altbuttonremap == 2) {
         if (multires > 0) {
             if (testbit(multibuf, ALT_BUTTON)) {
                 XPLMSetDatai(AltButtonRemapableData, 1);
                 lastappos = 1;
             } else if (!testbit(multibuf, ALT_BUTTON)) {
                 XPLMSetDatai(AltButtonRemapableData, 0);
                 lastappos = 1;
             }
         }
         if (lightdatareferencetype == 1) {
             if (XPLMGetDataf(AltLightRemapableData) > .50) {
                 altlightdata = 1;
             } else if (XPLMGetDataf(AltLightRemapableData) < .50) {
                 altlightdata = 0;
             }
             switch(altlightdata) {
             case 1:
                 btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                 break;
             case 0:
                 if (XPLMGetDataf(AltLightFlashRemapableData) > .50) {
                     altlightflashdata = 1;
                 } else if (XPLMGetDataf(AltLightFlashRemapableData) < .50) {
                     altlightflashdata = 0;
                 }
                 if (altlightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                 switch(XPLMGetDatai(AltLightRemapableData)) {
                 case 1:
                     btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                     break;
                 case 0:
                     altlightflashdata = XPLMGetDatai(AltLightFlashRemapableData);

                     if (altlightflashdata) {
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

         } else if (lightdatareferencetype == 3) {
             altlightdata = XPLMGetDatai(AltLightRemapableData);
             switch(altlightdata) {
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

     } else if (altbuttonremap == 3) {
         if (multires > 0) {
             if (testbit(multibuf, ALT_BUTTON)) {
                 lastappos = XPLMGetDatai(AltButtonRemapableData);
                 if (lastappos == 1) {
                     XPLMSetDatai(AltButtonRemapableData, 0);
                 } else {
                     XPLMSetDatai(AltButtonRemapableData, 1);
                 }

             }
         }
         if (lightdatareferencetype == 1) {
             if (XPLMGetDataf(AltLightRemapableData) > .50) {
                 altlightdata = 1;
             } else if (XPLMGetDataf(AltLightRemapableData) < .50) {
                 altlightdata = 0;
             }
             switch(altlightdata) {
             case 1:
                 btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                 break;
             case 0:
                 if (XPLMGetDataf(AltLightFlashRemapableData) > .50) {
                     altlightflashdata = 1;
                 } else if (XPLMGetDataf(AltLightFlashRemapableData) < .50) {
                     altlightflashdata = 0;
                 }
                 if (altlightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                 switch(XPLMGetDatai(AltLightRemapableData)) {
                 case 1:
                     btnleds |= (1<<4);   // * set bit 4 in btnleds to 1 *
                     break;
                 case 0:
                     altlightflashdata = XPLMGetDatai(AltLightFlashRemapableData);

                     if (altlightflashdata) {
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

         } else if (lightdatareferencetype == 3) {
             altlightdata = XPLMGetDatai(AltLightRemapableData);
             switch(altlightdata) {
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
    switch(XPLMGetDatai(ApAltStat)) {
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

    if (vsbuttonremap == 1) {
        if (multires > 0) {
            if (testbit(multibuf, VS_BUTTON)) {
                XPLMCommandOnce(VsButtonRemapableCmd);
                lastappos = 1;
            }
        }
        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(VsLightRemapableData) > .50) {
                vslightdata = 1;
            } else if (XPLMGetDataf(VsLightRemapableData) < .50) {
                vslightdata = 0;

            }
            switch(vslightdata) {
            case 1:
                btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(VsLightFlashRemapableData) > .50) {
                    vslightflashdata = 1;
                } else if (XPLMGetDataf(VsLightFlashRemapableData) < .50) {
                    vslightflashdata = 0;
                }
                if (vslightflashdata) {
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

         } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(VsLightRemapableData)) {
                case 1:
                    btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                    break;
                case 0:
                    vslightflashdata = XPLMGetDatai(VsLightFlashRemapableData);

                    if (vslightflashdata) {
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


        } else if (lightdatareferencetype == 3) {
            vslightdata = XPLMGetDatai(VsLightRemapableData);
            switch(vslightdata) {
            case 2:
                btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                break;
            case 1:
                if (flashon == 0) {
                    btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                } else {
                    btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                }
                break;
            case 0:
                btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                break;
            }

        }


    } else if (vsbuttonremap == 2) {
            if (multires > 0) {
                if (testbit(multibuf, VS_BUTTON)) {
                    XPLMSetDatai(VsButtonRemapableData, 1);
                    lastappos = 1;
                } else if (!testbit(multibuf, VS_BUTTON)) {
                    XPLMSetDatai(VsButtonRemapableData, 0);
                    lastappos = 1;

                }
            }
            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(VsLightRemapableData) > .50) {
                    vslightdata = 1;
                } else if (XPLMGetDataf(VsLightRemapableData) < .50) {
                    vslightdata = 0;
                }
                switch(vslightdata) {
                case 1:
                    btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                    break;
                case 0:
                    if (XPLMGetDataf(VsLightFlashRemapableData) > .50) {
                        vslightflashdata = 1;
                    } else if (XPLMGetDataf(VsLightFlashRemapableData) < .50) {
                        vslightflashdata = 0;
                    }
                    if (vslightflashdata) {
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

            } else if (lightdatareferencetype == 2) {

                    switch(XPLMGetDatai(VsLightRemapableData)) {
                    case 1:
                        btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                        break;
                    case 0:
                        vslightflashdata = XPLMGetDatai(VsLightFlashRemapableData);

                        if (vslightflashdata) {
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


            } else if (lightdatareferencetype == 3) {
                vslightdata = XPLMGetDatai(VsLightRemapableData);
                switch(vslightdata) {
                case 2:
                    btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                    break;
                case 1:
                    if (flashon == 0) {
                        btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                    } else {
                        btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                    }
                    break;
                case 0:
                    btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                    break;
                }


            }

    } else if (vsbuttonremap == 3) {

        if (multires > 0) {
            if (testbit(multibuf, VS_BUTTON)) {
                lastappos = XPLMGetDatai(VsButtonRemapableData);
                if (lastappos == 1) {
                    XPLMSetDatai(VsButtonRemapableData, 0);
                } else {
                    XPLMSetDatai(VsButtonRemapableData, 1);
                }
            }
        }
        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(VsLightRemapableData) > .50) {
                vslightdata = 1;
            } else if (XPLMGetDataf(VsLightRemapableData) < .50) {
                vslightdata = 0;
            }
            switch(vslightdata) {
            case 1:
                btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(VsLightFlashRemapableData) > .50) {
                    vslightflashdata = 1;
                } else if (XPLMGetDataf(VsLightFlashRemapableData) < .50) {
                    vslightflashdata = 0;
                }
                if (vslightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(VsLightRemapableData)) {
                case 1:
                    btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                    break;
                case 0:
                    vslightflashdata = XPLMGetDatai(VsLightFlashRemapableData);

                    if (vslightflashdata) {
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


        } else if (lightdatareferencetype == 3) {
            vslightdata = XPLMGetDatai(VsLightRemapableData);
            switch(vslightdata) {
            case 2:
                btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                break;
            case 1:
                if (flashon == 0) {
                    btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
                } else {
                    btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                }
                break;
            case 0:
                btnleds &= ~(1<<5);   // * clear bit 5 in btnleds to 0 *
                break;
            }


        }

    } else {
        if (multires > 0) {
            if(testbit(multibuf,VS_BUTTON)) {
                XPLMCommandOnce(ApVsBtn);
                upapvsf = 0;
                XPLMSetDataf(ApVs, upapvsf);
                lastappos = 1;
             }
        }
        switch(XPLMGetDatai(ApVsStat)) {
        case 2:
            btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
            break;
        case 1:
            if (flashon == 0) {
                btnleds |= (1<<5);   // * set bit 5 in btnleds to 1 *
            } else {
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

    if (aprbuttonremap == 1) {
        if (multires > 0) {
          if(testbit(multibuf,APR_BUTTON)) {
              XPLMCommandOnce(AprButtonRemapableCmd);
              lastappos = 1;
          }
        }

        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(AprLightRemapableData) > .50) {
                aprlightdata = 1;
            } else if (XPLMGetDataf(AprLightRemapableData) < .50) {
                aprlightdata = 0;
            }
            switch(aprlightdata) {
            case 1:
                btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(AprLightFlashRemapableData) > .50) {
                    aprlightflashdata = 1;
                } else if (XPLMGetDataf(AprLightFlashRemapableData) < .50) {
                        aprlightflashdata = 0;
                }

                if (aprlightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(AprLightRemapableData)) {
                case 1:
                    btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                    break;
                case 0:
                    aprlightflashdata = XPLMGetDatai(AprLightFlashRemapableData);


                    if (aprlightflashdata) {
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

        } else if (lightdatareferencetype == 3) {
            aprlightdata = XPLMGetDatai(AprLightRemapableData);
            switch(aprlightdata) {
            case 2:
                btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                break;
            case 1:
                if (flashon == 1) {
                    btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                } else {
                    btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
                }
                break;
            case 0:
                btnleds &= ~(1<<6);   // * clear bit 6 in btnleds to 0 *
                break;
            }
        }


    } else if (aprbuttonremap == 2) {
            if (multires > 0) {
              if(testbit(multibuf,APR_BUTTON)) {
                  XPLMSetDatai(AprButtonRemapableData, 1);
                  lastappos = 1;

              } else if(!testbit(multibuf,APR_BUTTON)) {
                 XPLMSetDatai(AprButtonRemapableData, 0);
                 lastappos = 1;

              }
            }

            if (lightdatareferencetype == 1) {
                if (XPLMGetDataf(AprLightRemapableData) > .50) {
                    aprlightdata = 1;
                } else if (XPLMGetDataf(AprLightRemapableData) < .50) {
                    aprlightdata = 0;
                }
                switch(aprlightdata) {
                case 1:
                    btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                    break;
                case 0:
                    if (XPLMGetDataf(AprLightFlashRemapableData) > .50) {
                        aprlightflashdata = 1;
                    } else if (XPLMGetDataf(AprLightFlashRemapableData) < .50) {
                         aprlightflashdata = 0;
                    }

                    if (aprlightflashdata) {
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

            } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(AprLightRemapableData)) {
                case 1:
                    btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                    break;
                case 0:
                    aprlightflashdata = XPLMGetDatai(AprLightFlashRemapableData);

                    if (aprlightflashdata) {
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


            } else if (lightdatareferencetype == 3) {
                aprlightdata = XPLMGetDatai(AprLightRemapableData);
                switch(XPLMGetDatai(ApAprStat)) {
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

    } else if (aprbuttonremap == 3) {

        if (multires > 0) {
          if(testbit(multibuf,APR_BUTTON)) {
              lastappos = XPLMGetDatai(AprButtonRemapableData);
              if (lastappos == 1) {
                  XPLMSetDatai(AprButtonRemapableData, 0);
              } else {
                  XPLMSetDatai(AprButtonRemapableData, 1);
              }
          }
        }

        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(AprLightRemapableData) > .50) {
                aprlightdata = 1;
            } else if (XPLMGetDataf(AprLightRemapableData) < .50) {
                aprlightdata = 0;
            }
            switch(aprlightdata) {
            case 1:
                btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(AprLightFlashRemapableData) > .50) {
                    aprlightflashdata = 1;
                } else if (XPLMGetDataf(AprLightFlashRemapableData) < .50) {
                     aprlightflashdata = 0;
                }

                if (aprlightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

            switch(XPLMGetDatai(AprLightRemapableData)) {
            case 1:
                btnleds |= (1<<6);   // * set bit 6 in btnleds to 1 *
                break;
            case 0:
                aprlightflashdata = XPLMGetDatai(AprLightFlashRemapableData);

                if (aprlightflashdata) {
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


        } else if (lightdatareferencetype == 3) {
            aprlightdata = XPLMGetDatai(AprLightRemapableData);
            switch(XPLMGetDatai(ApAprStat)) {
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
    switch(XPLMGetDatai(ApAprStat)) {
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


        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(RevLightRemapableData) > .50) {
                revlightdata = 1;
            } else if (XPLMGetDataf(RevLightRemapableData) < .50) {
                revlightdata = 0;
            }
            switch(revlightdata) {
            case 1:
                btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(RevLightFlashRemapableData) > .50) {
                    revlightflashdata = 1;
                } else if (XPLMGetDataf(RevLightFlashRemapableData) < .50) {
                    revlightflashdata = 0;
                }
                if (revlightflashdata) {
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

          } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(RevLightRemapableData)) {
                case 1:
                    btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                    break;
                case 0:
                    revlightflashdata = XPLMGetDatai(RevLightFlashRemapableData);

                    if (revlightflashdata) {
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


        } else if (lightdatareferencetype == 3) {
            revlightdata = XPLMGetDatai(RevLightRemapableData);
            switch(revlightdata) {
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

    } else if (revbuttonremap == 2) {
        if (multires > 0) {
            if(testbit(multibuf,REV_BUTTON)) {
                XPLMSetDatai(RevButtonRemapableData, 1);
                lastappos = 1;
            } else if(!testbit(multibuf,REV_BUTTON)) {
                XPLMSetDatai(RevButtonRemapableData, 0);
                lastappos = 1;
            }
        }

        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(RevLightRemapableData) > .50) {
                revlightdata = 1;
            } else if (XPLMGetDataf(RevLightRemapableData) < .50) {
                revlightflashdata = 0;
            }
            switch(revlightflashdata) {
            case 1:
                btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(RevLightFlashRemapableData) > .50) {
                    revlightflashdata = 1;
                } else if (XPLMGetDataf(RevLightFlashRemapableData) < .50) {
                    revlightflashdata = 0;
                }
                if (revlightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(RevLightRemapableData)) {
                case 1:
                    btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                    break;
                case 0:
                    revlightflashdata = XPLMGetDatai(RevLightFlashRemapableData);

                    if (revlightflashdata) {
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

        } else if (lightdatareferencetype == 3) {
            revlightdata = XPLMGetDatai(RevLightRemapableData);
            switch(revlightdata) {
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

    } else if (revbuttonremap == 3) {

        if (multires > 0) {
            if(testbit(multibuf,REV_BUTTON)) {
                lastappos = XPLMGetDatai(RevButtonRemapableData);
                if (lastappos == 1) {
                    XPLMSetDatai(RevButtonRemapableData, 0);
                } else {
                    XPLMSetDatai(RevButtonRemapableData, 1);
                }
            }
        }

        if (lightdatareferencetype == 1) {
            if (XPLMGetDataf(RevLightRemapableData) > .50) {
                revlightdata = 1;
            } else if (XPLMGetDataf(RevLightRemapableData) < .50) {
                revlightflashdata = 0;
            }
            switch(revlightflashdata) {
            case 1:
                btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                break;
            case 0:
                if (XPLMGetDataf(RevLightFlashRemapableData) > .50) {
                    revlightflashdata = 1;
                } else if (XPLMGetDataf(RevLightFlashRemapableData) < .50) {
                    revlightflashdata = 0;
                }
                if (revlightflashdata) {
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

        } else if (lightdatareferencetype == 2) {

                switch(XPLMGetDatai(RevLightRemapableData)) {
                case 1:
                    btnleds |= (1<<7);   // * set bit 7 in btnleds to 1 *
                    break;
                case 0:
                    revlightflashdata = XPLMGetDatai(RevLightFlashRemapableData);

                    if (revlightflashdata) {
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

        } else if (lightdatareferencetype == 3) {
            revlightdata = XPLMGetDatai(RevLightRemapableData);
            switch(revlightdata) {
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
    if (multires > 0) {
        if(testbit(multibuf,FLAPS_UP_SWITCH)) {
            if (flapsupremap == 1) {
                XPLMCommandOnce(FlapsUpRemapableCmd);
            } else {
                if (BatPwrIsOn()) {
                    XPLMCommandOnce(FlapsUp);
                }
            }
        }
        if(testbit(multibuf,FLAPS_DN_SWITCH)) {
            if (flapsdnremap == 1) {
                XPLMCommandOnce(FlapsDnRemapableCmd);
            } else {
                if (BatPwrIsOn()) {
                    XPLMCommandOnce(FlapsDn);
                }
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
    if (!AvPwrIsOn()) {
        multiseldis = 5;
    }
    if (!BatPwrIsOn()) {
        multiseldis = 5;
    }
    if(switchcnt > 0)  {
        if (XPLMGetDatai(SwitchAvOwnedDataRef) == 0) {
            if (AvPwrOnConfig == 0) {
               multiseldis = 5;
            }
        }

    } else {

    }



}


// ***** Multi Panel Process ******
void process_multi_panel()

{

    XPLMSetDatai(MultiKnobIncTicksOwnedDataRef, 0);
    XPLMSetDatai(MultiKnobDecTicksOwnedDataRef, 0);

    // ******* Only do a read if something new to be read ********
    hid_set_nonblocking(multihandle, 1);
    int multi_safety_cntr = 30;
    do {
        multires = hid_read(multihandle, multibuf, sizeof(multibuf));
        process_multi_panel_datareference_values();
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

    /*
    printf("multitestloop = %d AvPwrOn = %d BatPwrOn = %d multiseldis  %d\n", multitestloop, XPLMGetDatai(AvPwrOn), XPLMGetDatai(BatPwrOn), multiseldis);
    multitestloop ++;
    if (multitestloop > 5000) {
        multitestloop = 0;
    }

    */

    return;
}
