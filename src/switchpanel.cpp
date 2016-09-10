// ****** switchpanels.cpp **********
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

// ****************** Switch Panel variables *******************************
static int switchnowrite = 0;
static int switchres,
  switchwres;
//static int avf, avf2, avf3, avf4, avf5, avf6, avf7, avf8;
//static int avf9, avf10, avf11, avf12, avf13, avf14, avf15, avf16;

static int batnum = 0,
    gennum = 0,
    engnum = 0;
static int acf_en_type[8];

static float opencowl[8],
  closecowl[8];
static float engn_mixt[8];

static float panel_lights_switch_dataf_array[8];
static float panel_lights_switch2_dataf_array[8];
static float panel_lights_switch3_dataf_array[8];
static float panel_lights_switch4_dataf_array[8];
static float panel_lights_switch5_dataf_array[8];
static float panel_lights_switch6_dataf_array[8];
static float panel_lights_switch7_dataf_array[8];
static float panel_lights_switch8_dataf_array[8];

//float ThrottleList[8];


static int MAG_OFF = 10,
    MAG_RIGHT = 9,
    MAG_LEFT = 8,
    MAG_BOTH = 23;
static int ENG_START = 22;
static int MASTER_BATTERY = 7,
    MASTER_ALTENATOR = 6;
static int AVIONICS_POWER = 5,
    FUEL_PUMP = 4;
static int DE_ICE = 3,
    PITOT_HEAT = 2;
static int COWL_FLAPS = 1,
    PANEL_LIGHTS = 0;
static int BEACON_LIGHTS = 15,
    NAV_LIGHTS = 14;
static int STROBE_LIGHTS = 13,
    TAXI_LIGHTS = 12;
static int LANDING_LIGHTS = 11;
static int GEAR_SWITCH_UP = 21,
    GEAR_SWITCH_DN = 20;
static int BatArrayOn[8];
static int failed1up = 0,
    failed2up = 0,
    failed3up = 0;
static int failed1dn = 0,
    failed2dn = 0,
    failed3dn = 0;
static int ignition_key_array[8],
  igniter_on[8];
// static int bleed_air_mode, fuel_tank_transfer;

static unsigned char switchbuf[4];
static unsigned char switchwbuf[2],
  gearled;


void process_switch_menu()
{

    XPLMClearAllMenuItems(SwitchMenuId);

    XPLMAppendMenuItem(SwitchMenuId, "Switch Panel Widget",
        (void *) "SWITCH_WIDGET", 4);


    switchwbuf[0] = 0;
    switchwbuf[1] = gearled;
    if (bataltinverse == 0) {
        MASTER_BATTERY = 7, MASTER_ALTENATOR = 6;
    }
    if (bataltinverse == 1) {
        MASTER_BATTERY = 6, MASTER_ALTENATOR = 7;
    }

}

// ***************** Engines Mag Off ********************

void process_engines_mag_off_switch()
{

    if (testbit(switchbuf, MAG_OFF)) {
        XPLMSetDatai(SwitchStartOffOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchStartOffOwnedDataRef, 0);
    }

    if (magoffswitchenable == 0) {
        return;
    }

    if (magoffswitchenable == 2) {
        if (testbit(switchbuf, MAG_OFF)) {
            XPLMCommandOnce(MagOffSwitchOnCmd);
        }
        if (!testbit(switchbuf, MAG_OFF)) {
            XPLMCommandOnce(MagOffSwitchOffCmd);
        }
        return;
    }

    if (magoffswitchenable == 3) {
        if (testbit(switchbuf, MAG_OFF)) {
            XPLMSetDatai(MagOffSwitchData, mag_off_switch_data_on_value);
            XPLMSetDatai(MagOff2SwitchData, mag_off2_switch_data_on_value);
            XPLMSetDatai(MagOff3SwitchData, mag_off3_switch_data_on_value);
            XPLMSetDatai(MagOff4SwitchData, mag_off4_switch_data_on_value);
            XPLMSetDatai(MagOff5SwitchData, mag_off5_switch_data_on_value);
            XPLMSetDatai(MagOff6SwitchData, mag_off6_switch_data_on_value);
            XPLMSetDatai(MagOff7SwitchData, mag_off7_switch_data_on_value);
            XPLMSetDatai(MagOff8SwitchData, mag_off8_switch_data_on_value);
            XPLMSetDatai(MagOff9SwitchData, mag_off9_switch_data_on_value);
            XPLMSetDatai(MagOff10SwitchData, mag_off10_switch_data_on_value);
        }
        return;
    }


    if (magoffswitchenable == 4) {
        if (testbit(switchbuf, MAG_OFF)) {
            mag_off_switch_dataf_on_value = mag_off_switch_data_on_value;
            mag_off_switch_dataf_on_value =
                mag_off_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOffSwitchData, mag_off_switch_dataf_on_value);

            mag_off2_switch_dataf_on_value = mag_off2_switch_data_on_value;
            mag_off2_switch_dataf_on_value =
                mag_off2_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff2SwitchData, mag_off2_switch_dataf_on_value);

            mag_off3_switch_dataf_on_value = mag_off3_switch_data_on_value;
            mag_off3_switch_dataf_on_value =
                mag_off3_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff3SwitchData, mag_off3_switch_dataf_on_value);

            mag_off4_switch_dataf_on_value = mag_off4_switch_data_on_value;
            mag_off4_switch_dataf_on_value =
                mag_off4_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff4SwitchData, mag_off4_switch_dataf_on_value);

            mag_off5_switch_dataf_on_value = mag_off5_switch_data_on_value;
            mag_off5_switch_dataf_on_value =
                mag_off5_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff5SwitchData, mag_off5_switch_dataf_on_value);

            mag_off6_switch_dataf_on_value = mag_off6_switch_data_on_value;
            mag_off6_switch_dataf_on_value =
                mag_off6_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff6SwitchData, mag_off6_switch_dataf_on_value);

            mag_off7_switch_dataf_on_value = mag_off7_switch_data_on_value;
            mag_off7_switch_dataf_on_value =
                mag_off7_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff7SwitchData, mag_off7_switch_dataf_on_value);

            mag_off8_switch_dataf_on_value = mag_off8_switch_data_on_value;
            mag_off8_switch_dataf_on_value =
                mag_off8_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff8SwitchData, mag_off8_switch_dataf_on_value);

            mag_off9_switch_dataf_on_value = mag_off9_switch_data_on_value;
            mag_off9_switch_dataf_on_value =
                mag_off9_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff9SwitchData, mag_off9_switch_dataf_on_value);

            mag_off10_switch_dataf_on_value = mag_off10_switch_data_on_value;
            mag_off10_switch_dataf_on_value =
                mag_off10_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagOff10SwitchData, mag_off10_switch_dataf_on_value);
        }
        return;
    }

    if (testbit(switchbuf, MAG_OFF)) {
        if (engnum == 1) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 0;
                engn_mixt[0] = 0;
                igniter_on[0] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagOff1);
            }
        }

        if (engnum == 2) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 0, ignition_key_array[1] = 0;
                engn_mixt[0] = 0, engn_mixt[1] = 0;
                igniter_on[0] = 0, igniter_on[1] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagOff1);
                XPLMCommandOnce(MagOff2);
            }
        }

        if (engnum == 3) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 0, ignition_key_array[1] = 0;
                ignition_key_array[2] = 0;
                engn_mixt[0] = 0, engn_mixt[1] = 0, engn_mixt[2] = 0;
                igniter_on[0] = 0, igniter_on[1] = 0, igniter_on[2] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagOff1);
                XPLMCommandOnce(MagOff2);
                XPLMCommandOnce(MagOff3);
            }
        }

        if (engnum == 4) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 0, ignition_key_array[1] = 0;
                ignition_key_array[2] = 0, ignition_key_array[3] = 0;
                engn_mixt[0] = 0, engn_mixt[1] = 0;
                engn_mixt[2] = 0, engn_mixt[3] = 0;
                igniter_on[0] = 0, igniter_on[1] = 0;
                igniter_on[2] = 0, igniter_on[3] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagOff1);
                XPLMCommandOnce(MagOff2);
                XPLMCommandOnce(MagOff3);
                XPLMCommandOnce(MagOff4);
            }
        }
    }
}

// ***************** Engines Right Mag *******************

void process_engines_right_mag_switch()
{

    if (testbit(switchbuf, MAG_RIGHT)) {
        XPLMSetDatai(SwitchStartRightOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchStartRightOwnedDataRef, 0);
    }

    if (magrightswitchenable == 0) {
        return;
    }

    if (magrightswitchenable == 2) {
        if (testbit(switchbuf, MAG_RIGHT)) {
            XPLMCommandOnce(MagRightSwitchOnCmd);
        }
        if (!testbit(switchbuf, MAG_RIGHT)) {
            XPLMCommandOnce(MagRightSwitchOffCmd);
        }
        return;
    }

    if (magrightswitchenable == 3) {
        if (testbit(switchbuf, MAG_RIGHT)) {
            XPLMSetDatai(MagRightSwitchData, mag_right_switch_data_on_value);
            XPLMSetDatai(MagRight2SwitchData,
                mag_right2_switch_data_on_value);
            XPLMSetDatai(MagRight3SwitchData,
                mag_right3_switch_data_on_value);
            XPLMSetDatai(MagRight4SwitchData,
                mag_right4_switch_data_on_value);
            XPLMSetDatai(MagRight5SwitchData,
                mag_right5_switch_data_on_value);
            XPLMSetDatai(MagRight6SwitchData,
                mag_right6_switch_data_on_value);
            XPLMSetDatai(MagRight7SwitchData,
                mag_right7_switch_data_on_value);
            XPLMSetDatai(MagRight8SwitchData,
                mag_right8_switch_data_on_value);
            XPLMSetDatai(MagRight9SwitchData,
                mag_right9_switch_data_on_value);
            XPLMSetDatai(MagRight10SwitchData,
                mag_right10_switch_data_on_value);
        }
        return;
    }

    if (magrightswitchenable == 4) {
        if (testbit(switchbuf, MAG_RIGHT)) {
            mag_right_switch_dataf_on_value = mag_right_switch_data_on_value;
            mag_right_switch_dataf_on_value =
                mag_right_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRightSwitchData, mag_right_switch_dataf_on_value);

            mag_right2_switch_dataf_on_value =
                mag_right2_switch_data_on_value;
            mag_right2_switch_dataf_on_value =
                mag_right2_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight2SwitchData,
                mag_right2_switch_dataf_on_value);

            mag_right3_switch_dataf_on_value =
                mag_right3_switch_data_on_value;
            mag_right3_switch_dataf_on_value =
                mag_right3_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight3SwitchData,
                mag_right3_switch_dataf_on_value);

            mag_right4_switch_dataf_on_value =
                mag_right4_switch_data_on_value;
            mag_right4_switch_dataf_on_value =
                mag_right4_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight4SwitchData,
                mag_right4_switch_dataf_on_value);

            mag_right5_switch_dataf_on_value =
                mag_right5_switch_data_on_value;
            mag_right5_switch_dataf_on_value =
                mag_right5_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight5SwitchData,
                mag_right5_switch_dataf_on_value);

            mag_right6_switch_dataf_on_value =
                mag_right6_switch_data_on_value;
            mag_right6_switch_dataf_on_value =
                mag_right6_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight6SwitchData,
                mag_right6_switch_dataf_on_value);

            mag_right7_switch_dataf_on_value =
                mag_right7_switch_data_on_value;
            mag_right7_switch_dataf_on_value =
                mag_right7_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight7SwitchData,
                mag_right7_switch_dataf_on_value);

            mag_right8_switch_dataf_on_value =
                mag_right8_switch_data_on_value;
            mag_right8_switch_dataf_on_value =
                mag_right8_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight8SwitchData,
                mag_right8_switch_dataf_on_value);

            mag_right9_switch_dataf_on_value =
                mag_right9_switch_data_on_value;
            mag_right9_switch_dataf_on_value =
                mag_right9_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight9SwitchData,
                mag_right9_switch_dataf_on_value);

            mag_right10_switch_dataf_on_value =
                mag_right10_switch_data_on_value;
            mag_right10_switch_dataf_on_value =
                mag_right10_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagRight10SwitchData,
                mag_right10_switch_dataf_on_value);
        }
        return;
    }

    if (testbit(switchbuf, MAG_RIGHT)) {
        if (engnum == 1) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagRight1);
            }
        }

        if (engnum == 2) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 1, ignition_key_array[1] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagRight1);
                XPLMCommandOnce(MagRight2);
            }
        }

        if (engnum == 3) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 1, ignition_key_array[1] = 1;
                ignition_key_array[2] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagRight1);
                XPLMCommandOnce(MagRight2);
                XPLMCommandOnce(MagRight3);
            }
        }

        if (engnum == 4) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 1, ignition_key_array[1] = 1;
                ignition_key_array[2] = 1, ignition_key_array[3] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagRight1);
                XPLMCommandOnce(MagRight2);
                XPLMCommandOnce(MagRight3);
                XPLMCommandOnce(MagRight4);
            }
        }
    }
}

// ***************** Engines Left Mag *******************

void process_engines_left_mag_switch()
{
    if (testbit(switchbuf, MAG_LEFT)) {
        XPLMSetDatai(SwitchStartLeftOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchStartLeftOwnedDataRef, 0);
    }

    if (magleftswitchenable == 0) {
        return;
    }

    if (magleftswitchenable == 2) {
        if (testbit(switchbuf, MAG_LEFT)) {
            XPLMCommandOnce(MagLeftSwitchOnCmd);
        }
        if (!testbit(switchbuf, MAG_LEFT)) {
            XPLMCommandOnce(MagLeftSwitchOffCmd);
        }
        return;
    }

    if (magleftswitchenable == 3) {
        if (testbit(switchbuf, MAG_LEFT)) {
            XPLMSetDatai(MagLeftSwitchData, mag_left_switch_data_on_value);
            XPLMSetDatai(MagLeft2SwitchData, mag_left2_switch_data_on_value);
            XPLMSetDatai(MagLeft3SwitchData, mag_left3_switch_data_on_value);
            XPLMSetDatai(MagLeft4SwitchData, mag_left4_switch_data_on_value);
            XPLMSetDatai(MagLeft5SwitchData, mag_left5_switch_data_on_value);
            XPLMSetDatai(MagLeft6SwitchData, mag_left6_switch_data_on_value);
            XPLMSetDatai(MagLeft7SwitchData, mag_left7_switch_data_on_value);
            XPLMSetDatai(MagLeft8SwitchData, mag_left8_switch_data_on_value);
            XPLMSetDatai(MagLeft9SwitchData, mag_left9_switch_data_on_value);
            XPLMSetDatai(MagLeft10SwitchData,
                mag_left10_switch_data_on_value);
        }
        return;
    }

    if (magleftswitchenable == 4) {
        if (testbit(switchbuf, MAG_LEFT)) {
            mag_left_switch_dataf_on_value = mag_left_switch_data_on_value;
            mag_left_switch_dataf_on_value =
                mag_left_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeftSwitchData, mag_left_switch_dataf_on_value);

            mag_left2_switch_dataf_on_value = mag_left2_switch_data_on_value;
            mag_left2_switch_dataf_on_value =
                mag_left2_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeft2SwitchData, mag_left2_switch_dataf_on_value);

            mag_left3_switch_dataf_on_value = mag_left3_switch_data_on_value;
            mag_left3_switch_dataf_on_value =
                mag_left3_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeft3SwitchData, mag_left3_switch_dataf_on_value);

            mag_left4_switch_dataf_on_value = mag_left4_switch_data_on_value;
            mag_left4_switch_dataf_on_value =
                mag_left4_switch_dataf_on_value / 100.0f;
            XPLMSetDatai(MagLeft4SwitchData, mag_left4_switch_data_on_value);

            mag_left5_switch_dataf_on_value = mag_left5_switch_data_on_value;
            mag_left5_switch_dataf_on_value =
                mag_left5_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeft5SwitchData, mag_left5_switch_dataf_on_value);

            mag_left6_switch_dataf_on_value = mag_left6_switch_data_on_value;
            mag_left6_switch_dataf_on_value =
                mag_left6_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeft6SwitchData, mag_left6_switch_dataf_on_value);

            mag_left7_switch_dataf_on_value = mag_left7_switch_data_on_value;
            mag_left7_switch_dataf_on_value =
                mag_left7_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeft7SwitchData, mag_left7_switch_dataf_on_value);

            mag_left8_switch_dataf_on_value = mag_left8_switch_data_on_value;
            mag_left8_switch_dataf_on_value =
                mag_left8_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeft8SwitchData, mag_left8_switch_dataf_on_value);

            mag_left9_switch_dataf_on_value = mag_left9_switch_data_on_value;
            mag_left9_switch_dataf_on_value =
                mag_left9_switch_dataf_on_value / 100.0f;
            XPLMSetDatai(MagLeft9SwitchData, mag_left9_switch_data_on_value);

            mag_left10_switch_dataf_on_value =
                mag_left10_switch_data_on_value;
            mag_left10_switch_dataf_on_value =
                mag_left10_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagLeft10SwitchData,
                mag_left10_switch_dataf_on_value);


        }
        return;
    }

    if (testbit(switchbuf, MAG_LEFT)) {
        if (engnum == 1) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 2;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagLeft1);
            }
        }

        if (engnum == 2) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 2, ignition_key_array[1] = 2;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagLeft1);
                XPLMCommandOnce(MagLeft2);
            }
        }

        if (engnum == 3) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 2, ignition_key_array[1] = 2;
                ignition_key_array[2] = 2;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagLeft1);
                XPLMCommandOnce(MagLeft2);
                XPLMCommandOnce(MagLeft3);
            }
        }

        if (engnum == 4) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 2, ignition_key_array[1] = 2;
                ignition_key_array[2] = 2, ignition_key_array[3] = 2;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagLeft1);
                XPLMCommandOnce(MagLeft2);
                XPLMCommandOnce(MagLeft3);
                XPLMCommandOnce(MagLeft4);
            }
        }
    }
}

// ***************** Engines Both Mags *******************

void process_engines_both_mag_switch()
{
    if (testbit(switchbuf, MAG_BOTH)) {
        XPLMSetDatai(SwitchStartBothOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchStartBothOwnedDataRef, 0);

    }

    if (magbothswitchenable == 0) {
        return;
    }

    if (magbothswitchenable == 2) {
        if (testbit(switchbuf, MAG_BOTH)) {
            XPLMCommandOnce(MagBothSwitchOnCmd);
        }
        if (!testbit(switchbuf, MAG_BOTH)) {
            XPLMCommandOnce(MagBothSwitchOffCmd);
        }
        return;
    }

    if (magbothswitchenable == 3) {
        if (testbit(switchbuf, MAG_BOTH)) {
            XPLMSetDatai(MagBothSwitchData, mag_both_switch_data_on_value);
            XPLMSetDatai(MagBoth2SwitchData, mag_both2_switch_data_on_value);
            XPLMSetDatai(MagBoth3SwitchData, mag_both3_switch_data_on_value);
            XPLMSetDatai(MagBoth4SwitchData, mag_both4_switch_data_on_value);
            XPLMSetDatai(MagBoth5SwitchData, mag_both5_switch_data_on_value);
            XPLMSetDatai(MagBoth6SwitchData, mag_both6_switch_data_on_value);
            XPLMSetDatai(MagBoth7SwitchData, mag_both7_switch_data_on_value);
            XPLMSetDatai(MagBoth8SwitchData, mag_both8_switch_data_on_value);
            XPLMSetDatai(MagBoth9SwitchData, mag_both9_switch_data_on_value);
            XPLMSetDatai(MagBoth10SwitchData,
                mag_both10_switch_data_on_value);
        }
        return;
    }

    if (magbothswitchenable == 4) {
        if (testbit(switchbuf, MAG_BOTH)) {

            mag_both_switch_dataf_on_value = mag_both_switch_data_on_value;
            mag_both_switch_dataf_on_value =
                mag_both_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBothSwitchData, mag_both_switch_dataf_on_value);

            mag_both2_switch_dataf_on_value = mag_both2_switch_data_on_value;
            mag_both2_switch_dataf_on_value =
                mag_both2_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth2SwitchData, mag_both2_switch_dataf_on_value);

            mag_both3_switch_dataf_on_value = mag_both3_switch_data_on_value;
            mag_both3_switch_dataf_on_value =
                mag_both3_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth3SwitchData, mag_both3_switch_dataf_on_value);

            mag_both4_switch_dataf_on_value = mag_both4_switch_data_on_value;
            mag_both4_switch_dataf_on_value =
                mag_both4_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth4SwitchData, mag_both4_switch_dataf_on_value);

            mag_both5_switch_dataf_on_value = mag_both5_switch_data_on_value;
            mag_both5_switch_dataf_on_value =
                mag_both5_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth5SwitchData, mag_both5_switch_dataf_on_value);

            mag_both6_switch_dataf_on_value = mag_both6_switch_data_on_value;
            mag_both6_switch_dataf_on_value =
                mag_both6_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth6SwitchData, mag_both6_switch_dataf_on_value);

            mag_both7_switch_dataf_on_value = mag_both7_switch_data_on_value;
            mag_both7_switch_dataf_on_value =
                mag_both7_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth7SwitchData, mag_both7_switch_dataf_on_value);

            mag_both8_switch_dataf_on_value = mag_both8_switch_data_on_value;
            mag_both8_switch_dataf_on_value =
                mag_both8_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth8SwitchData, mag_both8_switch_dataf_on_value);

            mag_both9_switch_dataf_on_value = mag_both9_switch_data_on_value;
            mag_both9_switch_dataf_on_value =
                mag_both9_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth9SwitchData, mag_both9_switch_dataf_on_value);

            mag_both10_switch_dataf_on_value =
                mag_both10_switch_data_on_value;
            mag_both10_switch_dataf_on_value =
                mag_both10_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(MagBoth10SwitchData,
                mag_both10_switch_dataf_on_value);


        }
        return;
    }


    if (testbit(switchbuf, MAG_BOTH)) {
        if (engnum == 1) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 3;
                igniter_on[0] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagBoth1);
            }
        }

        if (engnum == 2) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 3, ignition_key_array[1] = 3;
                igniter_on[0] = 0, igniter_on[1] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagBoth1);
                XPLMCommandOnce(MagBoth2);
            }
        }

        if (engnum == 3) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 3, ignition_key_array[1] = 3;
                ignition_key_array[2] = 3;
                igniter_on[0] = 0, igniter_on[1] = 0;
                igniter_on[2] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagBoth1);
                XPLMCommandOnce(MagBoth2);
                XPLMCommandOnce(MagBoth3);
            }
        }

        if (engnum == 4) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 3, ignition_key_array[1] = 3;
                ignition_key_array[2] = 3, ignition_key_array[3] = 3;
                igniter_on[0] = 0, igniter_on[1] = 0;
                igniter_on[2] = 0, igniter_on[3] = 0;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(MagBoth1);
                XPLMCommandOnce(MagBoth2);
                XPLMCommandOnce(MagBoth3);
                XPLMCommandOnce(MagBoth4);
            }
        }
    }
}

// ***************** Engines Starting *******************

void process_engines_start_switch()
{
    if (testbit(switchbuf, ENG_START)) {
        XPLMSetDatai(SwitchStartStartOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchStartStartOwnedDataRef, 0);
    }

    if (magstartswitchenable == 0) {
        return;
    }

    if (magstartswitchenable == 2) {
        if (testbit(switchbuf, ENG_START)) {
            XPLMCommandOnce(MagStartSwitchOnCmd);
        }
        if (!testbit(switchbuf, ENG_START)) {
            XPLMCommandOnce(MagStartSwitchOffCmd);
        }
        return;
    }

    if (magstartswitchenable == 3) {
        if (testbit(switchbuf, ENG_START)) {
            if (xpanelsleftstartfnbutton == 1) {
                XPLMSetDatai(MagStartSwitchLeftData,
                    mag_start_switch_left_data_on_value);
                XPLMSetDatai(MagStart2SwitchLeftData,
                    mag_start2_switch_left_data_on_value);
                XPLMSetDatai(MagStart3SwitchLeftData,
                    mag_start3_switch_left_data_on_value);
                XPLMSetDatai(MagStart4SwitchLeftData,
                    mag_start4_switch_left_data_on_value);
                XPLMSetDatai(MagStart5SwitchLeftData,
                    mag_start5_switch_left_data_on_value);
                XPLMSetDatai(MagStart6SwitchLeftData,
                    mag_start6_switch_left_data_on_value);
                XPLMSetDatai(MagStart7SwitchLeftData,
                    mag_start7_switch_left_data_on_value);
                XPLMSetDatai(MagStart8SwitchLeftData,
                    mag_start8_switch_left_data_on_value);
                XPLMSetDatai(MagStart9SwitchLeftData,
                    mag_start9_switch_left_data_on_value);
                XPLMSetDatai(MagStart10SwitchLeftData,
                    mag_start10_switch_left_data_on_value);


            } else {
                XPLMSetDatai(MagStartSwitchData,
                    mag_start_switch_data_on_value);
                XPLMSetDatai(MagStart2SwitchData,
                    mag_start2_switch_data_on_value);
                XPLMSetDatai(MagStart3SwitchData,
                    mag_start3_switch_data_on_value);
                XPLMSetDatai(MagStart4SwitchData,
                    mag_start4_switch_data_on_value);
                XPLMSetDatai(MagStart5SwitchData,
                    mag_start5_switch_data_on_value);
                XPLMSetDatai(MagStart6SwitchData,
                    mag_start6_switch_data_on_value);
                XPLMSetDatai(MagStart7SwitchData,
                    mag_start7_switch_data_on_value);
                XPLMSetDatai(MagStart8SwitchData,
                    mag_start8_switch_data_on_value);
                XPLMSetDatai(MagStart9SwitchData,
                    mag_start9_switch_data_on_value);
                XPLMSetDatai(MagStart10SwitchData,
                    mag_start10_switch_data_on_value);

            }
        }
        return;
    }



    if (magstartswitchenable == 4) {
        if (testbit(switchbuf, ENG_START)) {
            if (xpanelsleftstartfnbutton == 1) {

                mag_start_switch_left_dataf_on_value =
                    mag_start_switch_left_data_on_value;
                mag_start_switch_left_dataf_on_value =
                    mag_start_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStartSwitchLeftData,
                    mag_start_switch_left_dataf_on_value);


                mag_start2_switch_left_dataf_on_value =
                    mag_start2_switch_left_data_on_value;
                mag_start2_switch_left_dataf_on_value =
                    mag_start2_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart2SwitchLeftData,
                    mag_start2_switch_left_dataf_on_value);

                mag_start3_switch_left_dataf_on_value =
                    mag_start3_switch_left_data_on_value;
                mag_start3_switch_left_dataf_on_value =
                    mag_start3_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart3SwitchLeftData,
                    mag_start3_switch_left_dataf_on_value);

                mag_start4_switch_left_dataf_on_value =
                    mag_start4_switch_left_data_on_value;
                mag_start4_switch_left_dataf_on_value =
                    mag_start4_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart4SwitchLeftData,
                    mag_start4_switch_left_dataf_on_value);

                mag_start5_switch_left_dataf_on_value =
                    mag_start5_switch_left_data_on_value;
                mag_start5_switch_left_dataf_on_value =
                    mag_start5_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart5SwitchLeftData,
                    mag_start5_switch_left_dataf_on_value);

                mag_start6_switch_left_dataf_on_value =
                    mag_start6_switch_left_data_on_value;
                mag_start6_switch_left_dataf_on_value =
                    mag_start6_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart6SwitchLeftData,
                    mag_start6_switch_left_dataf_on_value);


                mag_start7_switch_left_dataf_on_value =
                    mag_start7_switch_left_data_on_value;
                mag_start7_switch_left_dataf_on_value =
                    mag_start7_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart7SwitchLeftData,
                    mag_start7_switch_left_dataf_on_value);

                mag_start8_switch_left_dataf_on_value =
                    mag_start8_switch_left_data_on_value;
                mag_start8_switch_left_dataf_on_value =
                    mag_start8_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart8SwitchLeftData,
                    mag_start8_switch_left_dataf_on_value);

                mag_start9_switch_left_dataf_on_value =
                    mag_start9_switch_left_data_on_value;
                mag_start9_switch_left_dataf_on_value =
                    mag_start9_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart9SwitchLeftData,
                    mag_start9_switch_left_dataf_on_value);

                mag_start10_switch_left_dataf_on_value =
                    mag_start10_switch_left_data_on_value;
                mag_start10_switch_left_dataf_on_value =
                    mag_start10_switch_left_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart10SwitchLeftData,
                    mag_start10_switch_left_dataf_on_value);




            } else {

                mag_start_switch_dataf_on_value =
                    mag_start_switch_data_on_value;
                mag_start_switch_dataf_on_value =
                    mag_start_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStartSwitchData,
                    mag_start_switch_dataf_on_value);

                mag_start2_switch_dataf_on_value =
                    mag_start2_switch_data_on_value;
                mag_start2_switch_dataf_on_value =
                    mag_start2_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart2SwitchData,
                    mag_start2_switch_dataf_on_value);

                mag_start3_switch_dataf_on_value =
                    mag_start3_switch_data_on_value;
                mag_start3_switch_dataf_on_value =
                    mag_start3_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart3SwitchData,
                    mag_start3_switch_dataf_on_value);

                mag_start4_switch_dataf_on_value =
                    mag_start4_switch_data_on_value;
                mag_start4_switch_dataf_on_value =
                    mag_start4_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart4SwitchData,
                    mag_start4_switch_dataf_on_value);

                mag_start5_switch_dataf_on_value =
                    mag_start5_switch_data_on_value;
                mag_start5_switch_dataf_on_value =
                    mag_start5_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart5SwitchData,
                    mag_start5_switch_dataf_on_value);


                mag_start6_switch_dataf_on_value =
                    mag_start6_switch_data_on_value;
                mag_start6_switch_dataf_on_value =
                    mag_start6_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart6SwitchData,
                    mag_start6_switch_dataf_on_value);

                mag_start7_switch_dataf_on_value =
                    mag_start7_switch_data_on_value;
                mag_start7_switch_dataf_on_value =
                    mag_start7_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart7SwitchData,
                    mag_start7_switch_dataf_on_value);

                mag_start8_switch_dataf_on_value =
                    mag_start8_switch_data_on_value;
                mag_start8_switch_dataf_on_value =
                    mag_start8_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart8SwitchData,
                    mag_start8_switch_dataf_on_value);

                mag_start9_switch_dataf_on_value =
                    mag_start9_switch_data_on_value;
                mag_start9_switch_dataf_on_value =
                    mag_start9_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart9SwitchData,
                    mag_start9_switch_dataf_on_value);

                mag_start10_switch_dataf_on_value =
                    mag_start10_switch_data_on_value;
                mag_start10_switch_dataf_on_value =
                    mag_start10_switch_dataf_on_value / 100.0f;
                XPLMSetDataf(MagStart10SwitchData,
                    mag_start10_switch_dataf_on_value);

            }
        }
        return;
    }

    if (testbit(switchbuf, ENG_START)) {
        if (engnum == 1) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 4;
                engn_mixt[0] = 1;
                igniter_on[0] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(EngStart1);
            }
        }

        if (engnum == 2) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 4, ignition_key_array[1] = 4;
                engn_mixt[0] = 1, engn_mixt[1] = 1;
                igniter_on[0] = 1, igniter_on[1] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(EngStart1);
                XPLMCommandOnce(EngStart2);
            }
        }

        if (engnum == 3) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 4, ignition_key_array[1] = 4;
                ignition_key_array[2] = 4;
                engn_mixt[0] = 1, engn_mixt[1] = 1;
                engn_mixt[2] = 1;
                igniter_on[0] = 1, igniter_on[1] = 1;
                igniter_on[2] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(EngStart1);
                XPLMCommandOnce(EngStart2);
                XPLMCommandOnce(EngStart3);
            }
        }

        if (engnum == 4) {
            if (starterswitchenable == 1) {
                ignition_key_array[0] = 4, ignition_key_array[1] = 4;
                ignition_key_array[2] = 4, ignition_key_array[3] = 4;
                engn_mixt[0] = 1, engn_mixt[1] = 1;
                engn_mixt[2] = 1, engn_mixt[3] = 1;
                igniter_on[0] = 1, igniter_on[1] = 1;
                igniter_on[2] = 1, igniter_on[3] = 1;
            } else if (starterswitchenable == 0) {
                XPLMCommandOnce(EngStart1);
                XPLMCommandOnce(EngStart2);
                XPLMCommandOnce(EngStart3);
                XPLMCommandOnce(EngStart4);
            }
        }
    }

    if (starterswitchenable == 1) {
        XPLMSetDatavi(IgnSwitchArray, ignition_key_array, 0, 8);
        if (acf_en_type[0] > 1) {
            XPLMSetDatavf(EngnMixt, engn_mixt, 0, 8);
            XPLMSetDatavi(IgniterOn, igniter_on, 0, 8);
        }
    } else if (starterswitchenable == 0) {

    }
}

// ***************** Master Battery *******************

void process_master_battery_switch()
{
    if (testbit(switchbuf, MASTER_BATTERY)) {
        XPLMSetDatai(SwitchBatOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchBatOwnedDataRef, 0);
    }

    if (batmasterswitchenable == 0) {
        return;
    }



    if (batmasterswitchenable == 2) {

        if (testbit(switchbuf, MASTER_BATTERY)) {
            XPLMCommandOnce(BatMasterSwitchOnCmd);
        }

        if (!testbit(switchbuf, MASTER_BATTERY)) {
            XPLMCommandOnce(BatMasterSwitchOffCmd);
        }

        return;
    }

    if (batmasterswitchenable == 3) {

        if (testbit(switchbuf, MASTER_BATTERY)) {
            XPLMSetDatai(BatMasterSwitchData,
                bat_master_switch_data_on_value);
            XPLMSetDatai(Bat2MasterSwitchData,
                bat2_master_switch_data_on_value);
            XPLMSetDatai(Bat3MasterSwitchData,
                bat3_master_switch_data_on_value);
            XPLMSetDatai(Bat4MasterSwitchData,
                bat4_master_switch_data_on_value);
            XPLMSetDatai(Bat5MasterSwitchData,
                bat5_master_switch_data_on_value);
            XPLMSetDatai(Bat6MasterSwitchData,
                bat6_master_switch_data_on_value);
            XPLMSetDatai(Bat7MasterSwitchData,
                bat7_master_switch_data_on_value);
            XPLMSetDatai(Bat8MasterSwitchData,
                bat8_master_switch_data_on_value);
        }

        if (!testbit(switchbuf, MASTER_BATTERY)) {
            XPLMSetDatai(BatMasterSwitchData,
                bat_master_switch_data_off_value);
            XPLMSetDatai(Bat2MasterSwitchData,
                bat2_master_switch_data_off_value);
            XPLMSetDatai(Bat3MasterSwitchData,
                bat3_master_switch_data_off_value);
            XPLMSetDatai(Bat4MasterSwitchData,
                bat4_master_switch_data_off_value);
            XPLMSetDatai(Bat5MasterSwitchData,
                bat5_master_switch_data_off_value);
            XPLMSetDatai(Bat6MasterSwitchData,
                bat6_master_switch_data_off_value);
            XPLMSetDatai(Bat7MasterSwitchData,
                bat7_master_switch_data_off_value);
            XPLMSetDatai(Bat8MasterSwitchData,
                bat8_master_switch_data_off_value);
        }

        return;
    }

    if (batmasterswitchenable == 4) {

        if (testbit(switchbuf, MASTER_BATTERY)) {

            bat_master_switch_dataf_on_value =
                bat_master_switch_data_on_value;
            bat_master_switch_dataf_on_value =
                bat_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(BatMasterSwitchData,
                bat_master_switch_dataf_on_value);

            bat2_master_switch_dataf_on_value =
                bat2_master_switch_data_on_value;
            bat2_master_switch_dataf_on_value =
                bat2_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Bat2MasterSwitchData,
                bat2_master_switch_dataf_on_value);

            bat3_master_switch_dataf_on_value =
                bat3_master_switch_data_on_value;
            bat3_master_switch_dataf_on_value =
                bat3_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Bat3MasterSwitchData,
                bat3_master_switch_dataf_on_value);

            bat4_master_switch_dataf_on_value =
                bat4_master_switch_data_on_value;
            bat4_master_switch_dataf_on_value =
                bat4_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Bat4MasterSwitchData,
                bat4_master_switch_dataf_on_value);

            bat5_master_switch_dataf_on_value =
                bat5_master_switch_data_on_value;
            bat5_master_switch_dataf_on_value =
                bat5_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Bat5MasterSwitchData,
                bat5_master_switch_dataf_on_value);

            bat6_master_switch_dataf_on_value =
                bat6_master_switch_data_on_value;
            bat6_master_switch_dataf_on_value =
                bat6_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Bat6MasterSwitchData,
                bat6_master_switch_dataf_on_value);

            bat7_master_switch_dataf_on_value =
                bat7_master_switch_data_on_value;
            bat7_master_switch_dataf_on_value =
                bat7_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Bat7MasterSwitchData,
                bat7_master_switch_dataf_on_value);

            bat8_master_switch_dataf_on_value =
                bat8_master_switch_data_on_value;
            bat8_master_switch_dataf_on_value =
                bat8_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Bat8MasterSwitchData,
                bat8_master_switch_dataf_on_value);


        }

        if (!testbit(switchbuf, MASTER_BATTERY)) {

            bat_master_switch_dataf_off_value =
                bat_master_switch_data_off_value;
            bat_master_switch_dataf_off_value =
                bat_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(BatMasterSwitchData,
                bat_master_switch_dataf_off_value);

            bat2_master_switch_dataf_off_value =
                bat2_master_switch_data_off_value;
            bat2_master_switch_dataf_off_value =
                bat2_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Bat2MasterSwitchData,
                bat2_master_switch_dataf_off_value);

            bat3_master_switch_dataf_off_value =
                bat3_master_switch_data_off_value;
            bat3_master_switch_dataf_off_value =
                bat3_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Bat3MasterSwitchData,
                bat3_master_switch_dataf_off_value);

            bat4_master_switch_dataf_off_value =
                bat4_master_switch_data_off_value;
            bat4_master_switch_dataf_off_value =
                bat4_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Bat4MasterSwitchData,
                bat4_master_switch_dataf_off_value);

            bat5_master_switch_dataf_off_value =
                bat5_master_switch_data_off_value;
            bat5_master_switch_dataf_off_value =
                bat5_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Bat5MasterSwitchData,
                bat5_master_switch_dataf_off_value);

            bat6_master_switch_dataf_off_value =
                bat6_master_switch_data_off_value;
            bat6_master_switch_dataf_off_value =
                bat6_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Bat6MasterSwitchData,
                bat6_master_switch_dataf_off_value);

            bat7_master_switch_dataf_off_value =
                bat7_master_switch_data_off_value;
            bat7_master_switch_dataf_off_value =
                bat7_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Bat7MasterSwitchData,
                bat7_master_switch_dataf_off_value);

            bat8_master_switch_dataf_off_value =
                bat8_master_switch_data_off_value;
            bat8_master_switch_dataf_off_value =
                bat8_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Bat8MasterSwitchData,
                bat8_master_switch_dataf_off_value);


        }

        return;
    }


    if (testbit(switchbuf, MASTER_BATTERY)) {
        if (batnum == 1) {
            BatArrayOn[0] = 1;
        }
        if (batnum == 2) {
            BatArrayOn[0] = 1;
            BatArrayOn[1] = 1;
        }
        if (batnum == 3) {
            BatArrayOn[0] = 1;
            BatArrayOn[1] = 1;
            BatArrayOn[2] = 1;
        }
        if (batnum == 4) {
            BatArrayOn[0] = 1;
            BatArrayOn[1] = 1;
            BatArrayOn[2] = 1;
            BatArrayOn[3] = 1;
        }
        if (batnum == 5) {
            BatArrayOn[0] = 1;
            BatArrayOn[1] = 1;
            BatArrayOn[2] = 1;
            BatArrayOn[3] = 1;
            BatArrayOn[4] = 1;
        }
        if (batnum == 6) {
            BatArrayOn[0] = 1;
            BatArrayOn[1] = 1;
            BatArrayOn[2] = 1;
            BatArrayOn[3] = 1;
            BatArrayOn[4] = 1;
            BatArrayOn[5] = 1;
        }
        if (batnum == 7) {
            BatArrayOn[0] = 1;
            BatArrayOn[1] = 1;
            BatArrayOn[2] = 1;
            BatArrayOn[3] = 1;
            BatArrayOn[4] = 1;
            BatArrayOn[5] = 1;
            BatArrayOn[6] = 1;
        }
        if (batnum == 8) {
            BatArrayOn[0] = 1;
            BatArrayOn[1] = 1;
            BatArrayOn[2] = 1;
            BatArrayOn[3] = 1;
            BatArrayOn[4] = 1;
            BatArrayOn[5] = 1;
            BatArrayOn[6] = 1;
            BatArrayOn[7] = 1;
        }

    }
    if (!testbit(switchbuf, MASTER_BATTERY)) {
        if (batnum == 1) {
            BatArrayOn[0] = 0;
        }
        if (batnum == 2) {
            BatArrayOn[0] = 0;
            BatArrayOn[1] = 0;
        }
        if (batnum == 3) {
            BatArrayOn[0] = 0;
            BatArrayOn[1] = 0;
            BatArrayOn[2] = 0;
        }
        if (batnum == 4) {
            BatArrayOn[0] = 0;
            BatArrayOn[1] = 0;
            BatArrayOn[2] = 0;
            BatArrayOn[3] = 0;
        }
        if (batnum == 5) {
            BatArrayOn[0] = 0;
            BatArrayOn[1] = 0;
            BatArrayOn[2] = 0;
            BatArrayOn[3] = 0;
            BatArrayOn[4] = 0;
        }
        if (batnum == 6) {
            BatArrayOn[0] = 0;
            BatArrayOn[1] = 0;
            BatArrayOn[2] = 0;
            BatArrayOn[3] = 0;
            BatArrayOn[4] = 0;
            BatArrayOn[5] = 0;
        }
        if (batnum == 7) {
            BatArrayOn[0] = 0;
            BatArrayOn[1] = 0;
            BatArrayOn[2] = 0;
            BatArrayOn[3] = 0;
            BatArrayOn[4] = 0;
            BatArrayOn[5] = 0;
            BatArrayOn[6] = 0;
        }
        if (batnum == 8) {
            BatArrayOn[0] = 0;
            BatArrayOn[1] = 0;
            BatArrayOn[2] = 0;
            BatArrayOn[3] = 0;
            BatArrayOn[4] = 0;
            BatArrayOn[5] = 0;
            BatArrayOn[6] = 0;
            BatArrayOn[7] = 0;
        }

    }

    XPLMSetDatavi(BatArrayOnDR, BatArrayOn, 0, 8);
}

// ***************** Master Altenator *******************

void process_master_altenator_switch()
{
    if (testbit(switchbuf, MASTER_ALTENATOR)) {
        XPLMSetDatai(SwitchAltOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchAltOwnedDataRef, 0);
    }

    if (altmasterswitchenable == 0) {
        return;
    }

    if (altmasterswitchenable == 2) {

        if (testbit(switchbuf, MASTER_ALTENATOR)) {
            XPLMCommandOnce(AltMasterSwitchOnCmd);
        }

        if (!testbit(switchbuf, MASTER_ALTENATOR)) {
            XPLMCommandOnce(AltMasterSwitchOffCmd);
        }

        return;
    }

    if (altmasterswitchenable == 3) {

        if (testbit(switchbuf, MASTER_ALTENATOR)) {
            XPLMSetDatai(AltMasterSwitchData,
                alt_master_switch_data_on_value);
            XPLMSetDatai(Alt2MasterSwitchData,
                alt2_master_switch_data_on_value);
            XPLMSetDatai(Alt3MasterSwitchData,
                alt3_master_switch_data_on_value);
            XPLMSetDatai(Alt4MasterSwitchData,
                alt4_master_switch_data_on_value);
            XPLMSetDatai(Alt5MasterSwitchData,
                alt5_master_switch_data_on_value);
            XPLMSetDatai(Alt6MasterSwitchData,
                alt6_master_switch_data_on_value);
            XPLMSetDatai(Alt7MasterSwitchData,
                alt7_master_switch_data_on_value);
            XPLMSetDatai(Alt8MasterSwitchData,
                alt8_master_switch_data_on_value);
        }

        if (!testbit(switchbuf, MASTER_ALTENATOR)) {
            XPLMSetDatai(AltMasterSwitchData,
                alt_master_switch_data_off_value);
            XPLMSetDatai(Alt2MasterSwitchData,
                alt2_master_switch_data_off_value);
            XPLMSetDatai(Alt3MasterSwitchData,
                alt3_master_switch_data_off_value);
            XPLMSetDatai(Alt4MasterSwitchData,
                alt4_master_switch_data_off_value);
            XPLMSetDatai(Alt5MasterSwitchData,
                alt5_master_switch_data_off_value);
            XPLMSetDatai(Alt6MasterSwitchData,
                alt6_master_switch_data_off_value);
            XPLMSetDatai(Alt7MasterSwitchData,
                alt7_master_switch_data_off_value);
            XPLMSetDatai(Alt8MasterSwitchData,
                alt8_master_switch_data_off_value);
        }

        return;
    }


    if (altmasterswitchenable == 4) {

        if (testbit(switchbuf, MASTER_ALTENATOR)) {

            alt_master_switch_dataf_on_value =
                alt_master_switch_data_on_value;
            alt_master_switch_dataf_on_value =
                alt_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(AltMasterSwitchData,
                alt_master_switch_dataf_on_value);

            alt2_master_switch_dataf_on_value =
                alt2_master_switch_data_on_value;
            alt2_master_switch_dataf_on_value =
                alt2_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Alt2MasterSwitchData,
                alt2_master_switch_dataf_on_value);

            alt3_master_switch_dataf_on_value =
                alt3_master_switch_data_on_value;
            alt3_master_switch_dataf_on_value =
                alt3_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Alt3MasterSwitchData,
                alt3_master_switch_dataf_on_value);

            alt4_master_switch_dataf_on_value =
                alt4_master_switch_data_on_value;
            alt4_master_switch_dataf_on_value =
                alt4_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Alt4MasterSwitchData,
                alt4_master_switch_dataf_on_value);

            alt5_master_switch_dataf_on_value =
                alt5_master_switch_data_on_value;
            alt5_master_switch_dataf_on_value =
                alt5_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Alt5MasterSwitchData,
                alt5_master_switch_dataf_on_value);

            alt6_master_switch_dataf_on_value =
                alt6_master_switch_data_on_value;
            alt6_master_switch_dataf_on_value =
                alt6_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Alt6MasterSwitchData,
                alt6_master_switch_dataf_on_value);

            alt7_master_switch_dataf_on_value =
                alt7_master_switch_data_on_value;
            alt7_master_switch_dataf_on_value =
                alt7_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Alt7MasterSwitchData,
                alt7_master_switch_dataf_on_value);

            alt8_master_switch_dataf_on_value =
                alt8_master_switch_data_on_value;
            alt8_master_switch_dataf_on_value =
                alt8_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Alt8MasterSwitchData,
                alt8_master_switch_dataf_on_value);

        }

        if (!testbit(switchbuf, MASTER_ALTENATOR)) {

            alt_master_switch_dataf_off_value =
                alt_master_switch_data_off_value;
            alt_master_switch_dataf_off_value =
                alt_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(AltMasterSwitchData,
                alt_master_switch_dataf_off_value);

            alt2_master_switch_dataf_off_value =
                alt2_master_switch_data_off_value;
            alt2_master_switch_dataf_off_value =
                alt2_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Alt2MasterSwitchData,
                alt2_master_switch_dataf_off_value);

            alt3_master_switch_dataf_off_value =
                alt3_master_switch_data_off_value;
            alt3_master_switch_dataf_off_value =
                alt3_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Alt3MasterSwitchData,
                alt3_master_switch_dataf_off_value);

            alt4_master_switch_dataf_off_value =
                alt4_master_switch_data_off_value;
            alt4_master_switch_dataf_off_value =
                alt4_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Alt4MasterSwitchData,
                alt4_master_switch_dataf_off_value);


            alt5_master_switch_dataf_off_value =
                alt5_master_switch_data_off_value;
            alt5_master_switch_dataf_off_value =
                alt5_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Alt5MasterSwitchData,
                alt5_master_switch_dataf_off_value);

            alt6_master_switch_dataf_off_value =
                alt6_master_switch_data_off_value;
            alt6_master_switch_dataf_off_value =
                alt6_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Alt6MasterSwitchData,
                alt6_master_switch_dataf_off_value);

            alt7_master_switch_dataf_off_value =
                alt7_master_switch_data_off_value;
            alt7_master_switch_dataf_off_value =
                alt7_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Alt7MasterSwitchData,
                alt7_master_switch_dataf_off_value);

            alt8_master_switch_dataf_off_value =
                alt8_master_switch_data_off_value;
            alt8_master_switch_dataf_off_value =
                alt8_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Alt8MasterSwitchData,
                alt8_master_switch_dataf_off_value);


        }

        return;
    }

    if (testbit(switchbuf, MASTER_ALTENATOR)) {
        if (gennum == 1) {
            XPLMCommandOnce(GenOn1);
        }
        if (gennum == 2) {
            XPLMCommandOnce(GenOn1);
            XPLMCommandOnce(GenOn2);
        }
        if (gennum == 3) {
            XPLMCommandOnce(GenOn1);
            XPLMCommandOnce(GenOn2);
            XPLMCommandOnce(GenOn3);
        }
        if (gennum == 4) {
            XPLMCommandOnce(GenOn1);
            XPLMCommandOnce(GenOn2);
            XPLMCommandOnce(GenOn3);
            XPLMCommandOnce(GenOn4);
        }

    }

    if (!testbit(switchbuf, MASTER_ALTENATOR)) {
        if (gennum == 1) {
            XPLMCommandOnce(GenOff1);
        }
        if (gennum == 2) {
            XPLMCommandOnce(GenOff1);
            XPLMCommandOnce(GenOff2);
        }
        if (gennum == 3) {
            XPLMCommandOnce(GenOff1);
            XPLMCommandOnce(GenOff2);
            XPLMCommandOnce(GenOff3);
        }
        if (gennum == 4) {
            XPLMCommandOnce(GenOff1);
            XPLMCommandOnce(GenOff2);
            XPLMCommandOnce(GenOff3);
            XPLMCommandOnce(GenOff4);
        }

    }
}

// ***************** Avionics Power *******************

void process_avionics_power_switch()
{

    if (testbit(switchbuf, AVIONICS_POWER)) {
        XPLMSetDatai(SwitchAvOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchAvOwnedDataRef, 0);
    }

    if (avionicsmasterswitchenable == 0) {
        return;
    }

    if (avionicsmasterswitchenable == 1) {
        if (testbit(switchbuf, AVIONICS_POWER)) {

            if (BatPwrIsOn()) {
                XPLMSetDatai(AvPwrOn, 1);
            }

            if (!BatPwrIsOn()) {
                XPLMSetDatai(AvPwrOn, 0);
            }
        }

        if (!testbit(switchbuf, AVIONICS_POWER)) {
            XPLMSetDatai(AvPwrOn, 0);
        }


        return;
    }

    if (avionicsmasterswitchenable == 2) {

        if (testbit(switchbuf, AVIONICS_POWER)) {
            XPLMCommandOnce(AvMasterSwitchOnCmd);
        }

        if (!testbit(switchbuf, AVIONICS_POWER)) {
            XPLMCommandOnce(AvMasterSwitchOffCmd);
        }

        return;
    }

    if (avionicsmasterswitchenable == 3) {

        if (testbit(switchbuf, AVIONICS_POWER)) {
            XPLMSetDatai(AvMasterSwitchData, av_master_switch_data_on_value);
            XPLMSetDatai(Av2MasterSwitchData,
                av2_master_switch_data_on_value);
            XPLMSetDatai(Av3MasterSwitchData,
                av3_master_switch_data_on_value);
            XPLMSetDatai(Av4MasterSwitchData,
                av4_master_switch_data_on_value);
            XPLMSetDatai(Av5MasterSwitchData,
                av5_master_switch_data_on_value);
            XPLMSetDatai(Av6MasterSwitchData,
                av6_master_switch_data_on_value);
            XPLMSetDatai(Av7MasterSwitchData,
                av7_master_switch_data_on_value);
            XPLMSetDatai(Av8MasterSwitchData,
                av8_master_switch_data_on_value);
            XPLMSetDatai(Av9MasterSwitchData,
                av9_master_switch_data_on_value);
            XPLMSetDatai(Av10MasterSwitchData,
                av10_master_switch_data_on_value);
            XPLMSetDatai(Av11MasterSwitchData,
                av11_master_switch_data_on_value);
            XPLMSetDatai(Av12MasterSwitchData,
                av12_master_switch_data_on_value);
            XPLMSetDatai(Av13MasterSwitchData,
                av13_master_switch_data_on_value);
            XPLMSetDatai(Av14MasterSwitchData,
                av14_master_switch_data_on_value);
            XPLMSetDatai(Av15MasterSwitchData,
                av15_master_switch_data_on_value);
            XPLMSetDatai(Av16MasterSwitchData,
                av16_master_switch_data_on_value);

        }

        if (!testbit(switchbuf, AVIONICS_POWER)) {
            XPLMSetDatai(AvMasterSwitchData, av_master_switch_data_off_value);
            XPLMSetDatai(Av2MasterSwitchData,
                av2_master_switch_data_off_value);
            XPLMSetDatai(Av3MasterSwitchData,
                av3_master_switch_data_off_value);
            XPLMSetDatai(Av4MasterSwitchData,
                av4_master_switch_data_off_value);
            XPLMSetDatai(Av5MasterSwitchData,
                av5_master_switch_data_off_value);
            XPLMSetDatai(Av6MasterSwitchData,
                av6_master_switch_data_off_value);
            XPLMSetDatai(Av7MasterSwitchData,
                av7_master_switch_data_off_value);
            XPLMSetDatai(Av8MasterSwitchData,
                av8_master_switch_data_off_value);
            XPLMSetDatai(Av9MasterSwitchData,
                av9_master_switch_data_off_value);
            XPLMSetDatai(Av10MasterSwitchData,
                av10_master_switch_data_off_value);
            XPLMSetDatai(Av11MasterSwitchData,
                av11_master_switch_data_off_value);
            XPLMSetDatai(Av12MasterSwitchData,
                av12_master_switch_data_off_value);
            XPLMSetDatai(Av13MasterSwitchData,
                av13_master_switch_data_off_value);
            XPLMSetDatai(Av14MasterSwitchData,
                av14_master_switch_data_off_value);
            XPLMSetDatai(Av15MasterSwitchData,
                av15_master_switch_data_off_value);
            XPLMSetDatai(Av16MasterSwitchData,
                av16_master_switch_data_off_value);

        }

        return;
    }


    if (avionicsmasterswitchenable == 4) {

        if (testbit(switchbuf, AVIONICS_POWER)) {
            av_master_switch_dataf_on_value = av_master_switch_data_on_value;
            av_master_switch_dataf_on_value =
                av_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(AvMasterSwitchData, av_master_switch_dataf_on_value);

            av2_master_switch_dataf_on_value =
                av2_master_switch_data_on_value;
            av2_master_switch_dataf_on_value =
                av2_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av2MasterSwitchData,
                av2_master_switch_dataf_on_value);

            av3_master_switch_dataf_on_value =
                av3_master_switch_data_on_value;
            av3_master_switch_dataf_on_value =
                av3_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av3MasterSwitchData,
                av3_master_switch_dataf_on_value);

            av4_master_switch_dataf_on_value =
                av4_master_switch_data_on_value;
            av4_master_switch_dataf_on_value =
                av4_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av4MasterSwitchData,
                av4_master_switch_dataf_on_value);

            av5_master_switch_dataf_on_value =
                av5_master_switch_data_on_value;
            av5_master_switch_dataf_on_value =
                av5_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av5MasterSwitchData,
                av5_master_switch_dataf_on_value);

            av6_master_switch_dataf_on_value =
                av6_master_switch_data_on_value;
            av6_master_switch_dataf_on_value =
                av6_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av6MasterSwitchData,
                av6_master_switch_dataf_on_value);

            av7_master_switch_dataf_on_value =
                av7_master_switch_data_on_value;
            av7_master_switch_dataf_on_value =
                av7_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av7MasterSwitchData,
                av7_master_switch_dataf_on_value);

            av8_master_switch_dataf_on_value =
                av8_master_switch_data_on_value;
            av8_master_switch_dataf_on_value =
                av8_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av8MasterSwitchData,
                av8_master_switch_dataf_on_value);

            av9_master_switch_dataf_on_value =
                av9_master_switch_data_on_value;
            av9_master_switch_dataf_on_value =
                av9_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av9MasterSwitchData,
                av9_master_switch_dataf_on_value);

            av10_master_switch_dataf_on_value =
                av10_master_switch_data_on_value;
            av10_master_switch_dataf_on_value =
                av10_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av10MasterSwitchData,
                av10_master_switch_dataf_on_value);

            av11_master_switch_dataf_on_value =
                av11_master_switch_data_on_value;
            av11_master_switch_dataf_on_value =
                av11_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av11MasterSwitchData,
                av11_master_switch_dataf_on_value);

            av12_master_switch_dataf_on_value =
                av12_master_switch_data_on_value;
            av12_master_switch_dataf_on_value =
                av12_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av12MasterSwitchData,
                av12_master_switch_dataf_on_value);

            av13_master_switch_dataf_on_value =
                av13_master_switch_data_on_value;
            av13_master_switch_dataf_on_value =
                av13_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av13MasterSwitchData,
                av13_master_switch_dataf_on_value);

            av14_master_switch_dataf_on_value =
                av14_master_switch_data_on_value;
            av14_master_switch_dataf_on_value =
                av14_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av14MasterSwitchData,
                av14_master_switch_dataf_on_value);

            av15_master_switch_dataf_on_value =
                av15_master_switch_data_on_value;
            av15_master_switch_dataf_on_value =
                av15_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av15MasterSwitchData,
                av15_master_switch_dataf_on_value);

            av16_master_switch_dataf_on_value =
                av16_master_switch_data_on_value;
            av16_master_switch_dataf_on_value =
                av16_master_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Av16MasterSwitchData,
                av16_master_switch_dataf_on_value);

        }

        if (!testbit(switchbuf, AVIONICS_POWER)) {
            av_master_switch_dataf_off_value =
                av_master_switch_data_off_value;
            av_master_switch_dataf_off_value =
                av_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(AvMasterSwitchData,
                av_master_switch_dataf_off_value);

            av2_master_switch_dataf_off_value =
                av2_master_switch_data_off_value;
            av2_master_switch_dataf_off_value =
                av2_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av2MasterSwitchData,
                av2_master_switch_dataf_off_value);

            av3_master_switch_dataf_off_value =
                av3_master_switch_data_off_value;
            av3_master_switch_dataf_off_value =
                av3_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av3MasterSwitchData,
                av3_master_switch_dataf_off_value);

            av4_master_switch_dataf_off_value =
                av4_master_switch_data_off_value;
            av4_master_switch_dataf_off_value =
                av4_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av4MasterSwitchData,
                av4_master_switch_dataf_off_value);

            av5_master_switch_dataf_off_value =
                av5_master_switch_data_off_value;
            av5_master_switch_dataf_off_value =
                av5_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av5MasterSwitchData,
                av5_master_switch_dataf_off_value);

            av6_master_switch_dataf_off_value =
                av6_master_switch_data_off_value;
            av6_master_switch_dataf_off_value =
                av6_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av6MasterSwitchData,
                av6_master_switch_dataf_off_value);

            av7_master_switch_dataf_off_value =
                av7_master_switch_data_off_value;
            av7_master_switch_dataf_off_value =
                av7_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av7MasterSwitchData,
                av7_master_switch_dataf_off_value);

            av8_master_switch_dataf_off_value =
                av8_master_switch_data_off_value;
            av8_master_switch_dataf_off_value =
                av8_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av8MasterSwitchData,
                av8_master_switch_dataf_off_value);

            av9_master_switch_dataf_off_value =
                av9_master_switch_data_off_value;
            av9_master_switch_dataf_off_value =
                av9_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av9MasterSwitchData,
                av9_master_switch_dataf_off_value);

            av10_master_switch_dataf_off_value =
                av10_master_switch_data_off_value;
            av10_master_switch_dataf_off_value =
                av10_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av10MasterSwitchData,
                av10_master_switch_dataf_off_value);

            av11_master_switch_dataf_off_value =
                av11_master_switch_data_off_value;
            av11_master_switch_dataf_off_value =
                av11_master_switch_dataf_off_value / 100.0f;
            XPLMSetDatai(Av11MasterSwitchData,
                av11_master_switch_data_off_value);

            av12_master_switch_dataf_off_value =
                av12_master_switch_data_off_value;
            av12_master_switch_dataf_off_value =
                av12_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av12MasterSwitchData,
                av12_master_switch_dataf_off_value);

            av13_master_switch_dataf_off_value =
                av13_master_switch_data_off_value;
            av13_master_switch_dataf_off_value =
                av13_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av13MasterSwitchData,
                av13_master_switch_dataf_off_value);

            av14_master_switch_dataf_off_value =
                av14_master_switch_data_off_value;
            av14_master_switch_dataf_off_value =
                av14_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av14MasterSwitchData,
                av14_master_switch_dataf_off_value);

            av15_master_switch_dataf_off_value =
                av15_master_switch_data_off_value;
            av15_master_switch_dataf_off_value =
                av15_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av15MasterSwitchData,
                av15_master_switch_dataf_off_value);

            av16_master_switch_dataf_off_value =
                av16_master_switch_data_off_value;
            av16_master_switch_dataf_off_value =
                av16_master_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Av16MasterSwitchData,
                av16_master_switch_dataf_off_value);

        }

        return;
    }

}

// ***************** Fuel Pump *******************

void process_fuel_pump_switch()
{
    if (testbit(switchbuf, FUEL_PUMP)) {
        XPLMSetDatai(SwitchFuelOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchFuelOwnedDataRef, 0);
    }

    if (fuelpumpswitchenable == 0) {
        return;
    }

    if (fuelpumpswitchenable == 2) {

        if (testbit(switchbuf, FUEL_PUMP)) {
            XPLMCommandOnce(FuelPumpOnCmd);
            XPLMCommandOnce(FuelPump2OnCmd);
            XPLMCommandOnce(FuelPump3OnCmd);
            XPLMCommandOnce(FuelPump4OnCmd);
        }

        if (!testbit(switchbuf, FUEL_PUMP)) {
            XPLMCommandOnce(FuelPumpOffCmd);
            XPLMCommandOnce(FuelPump2OffCmd);
            XPLMCommandOnce(FuelPump3OffCmd);
            XPLMCommandOnce(FuelPump4OffCmd);
        }

        return;
    }


    if (fuelpumpswitchenable == 3) {

        if (testbit(switchbuf, FUEL_PUMP)) {
            XPLMSetDatai(FuelPumpSwitchData, fuel_pump_switch_data_on_value);
            XPLMSetDatai(FuelPump2SwitchData,
                fuel_pump2_switch_data_on_value);
            XPLMSetDatai(FuelPump3SwitchData,
                fuel_pump3_switch_data_on_value);
            XPLMSetDatai(FuelPump4SwitchData,
                fuel_pump4_switch_data_on_value);
            XPLMSetDatai(FuelPump5SwitchData,
                fuel_pump5_switch_data_on_value);
            XPLMSetDatai(FuelPump6SwitchData,
                fuel_pump6_switch_data_on_value);
            XPLMSetDatai(FuelPump7SwitchData,
                fuel_pump7_switch_data_on_value);
            XPLMSetDatai(FuelPump8SwitchData,
                fuel_pump8_switch_data_on_value);
        }

        if (!testbit(switchbuf, FUEL_PUMP)) {
            XPLMSetDatai(FuelPumpSwitchData, fuel_pump_switch_data_off_value);
            XPLMSetDatai(FuelPump2SwitchData,
                fuel_pump2_switch_data_off_value);
            XPLMSetDatai(FuelPump3SwitchData,
                fuel_pump3_switch_data_off_value);
            XPLMSetDatai(FuelPump4SwitchData,
                fuel_pump4_switch_data_off_value);
            XPLMSetDatai(FuelPump5SwitchData,
                fuel_pump5_switch_data_off_value);
            XPLMSetDatai(FuelPump6SwitchData,
                fuel_pump6_switch_data_off_value);
            XPLMSetDatai(FuelPump7SwitchData,
                fuel_pump7_switch_data_off_value);
            XPLMSetDatai(FuelPump8SwitchData,
                fuel_pump8_switch_data_off_value);

        }

        return;
    }

    if (fuelpumpswitchenable == 4) {

        if (testbit(switchbuf, FUEL_PUMP)) {

            fuel_pump_switch_dataf_on_value = fuel_pump_switch_data_on_value;
            fuel_pump_switch_dataf_on_value =
                fuel_pump_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPumpSwitchData, fuel_pump_switch_dataf_on_value);

            fuel_pump2_switch_dataf_on_value =
                fuel_pump2_switch_data_on_value;
            fuel_pump2_switch_dataf_on_value =
                fuel_pump2_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPump2SwitchData,
                fuel_pump2_switch_dataf_on_value);

            fuel_pump3_switch_dataf_on_value =
                fuel_pump3_switch_data_on_value;
            fuel_pump3_switch_dataf_on_value =
                fuel_pump3_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPump3SwitchData,
                fuel_pump3_switch_dataf_on_value);

            fuel_pump4_switch_dataf_on_value =
                fuel_pump4_switch_data_on_value;
            fuel_pump4_switch_dataf_on_value =
                fuel_pump4_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPump4SwitchData,
                fuel_pump4_switch_dataf_on_value);

            fuel_pump5_switch_dataf_on_value =
                fuel_pump5_switch_data_on_value;
            fuel_pump5_switch_dataf_on_value =
                fuel_pump5_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPump5SwitchData,
                fuel_pump5_switch_dataf_on_value);

            fuel_pump6_switch_dataf_on_value =
                fuel_pump6_switch_data_on_value;
            fuel_pump6_switch_dataf_on_value =
                fuel_pump6_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPump6SwitchData,
                fuel_pump6_switch_dataf_on_value);

            fuel_pump7_switch_dataf_on_value =
                fuel_pump7_switch_data_on_value;
            fuel_pump7_switch_dataf_on_value =
                fuel_pump7_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPump7SwitchData,
                fuel_pump7_switch_dataf_on_value);

            fuel_pump8_switch_dataf_on_value =
                fuel_pump8_switch_data_on_value;
            fuel_pump8_switch_dataf_on_value =
                fuel_pump8_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(FuelPump8SwitchData,
                fuel_pump8_switch_dataf_on_value);


        }

        if (!testbit(switchbuf, FUEL_PUMP)) {

            fuel_pump_switch_dataf_off_value =
                fuel_pump_switch_data_off_value;
            fuel_pump_switch_dataf_off_value =
                fuel_pump_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPumpSwitchData,
                fuel_pump_switch_dataf_off_value);

            fuel_pump2_switch_dataf_off_value =
                fuel_pump2_switch_data_off_value;
            fuel_pump2_switch_dataf_off_value =
                fuel_pump2_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPump2SwitchData,
                fuel_pump2_switch_dataf_off_value);

            fuel_pump3_switch_dataf_off_value =
                fuel_pump3_switch_data_off_value;
            fuel_pump3_switch_dataf_off_value =
                fuel_pump3_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPump3SwitchData,
                fuel_pump3_switch_dataf_off_value);

            fuel_pump4_switch_dataf_off_value =
                fuel_pump4_switch_data_off_value;
            fuel_pump4_switch_dataf_off_value =
                fuel_pump4_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPump4SwitchData,
                fuel_pump4_switch_dataf_off_value);

            fuel_pump5_switch_dataf_off_value =
                fuel_pump5_switch_data_off_value;
            fuel_pump5_switch_dataf_off_value =
                fuel_pump5_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPump5SwitchData,
                fuel_pump5_switch_dataf_off_value);

            fuel_pump6_switch_dataf_off_value =
                fuel_pump6_switch_data_off_value;
            fuel_pump6_switch_dataf_off_value =
                fuel_pump6_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPump6SwitchData,
                fuel_pump6_switch_dataf_off_value);

            fuel_pump7_switch_dataf_off_value =
                fuel_pump7_switch_data_off_value;
            fuel_pump7_switch_dataf_off_value =
                fuel_pump7_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPump7SwitchData,
                fuel_pump7_switch_dataf_off_value);

            fuel_pump8_switch_dataf_off_value =
                fuel_pump8_switch_data_off_value;
            fuel_pump8_switch_dataf_off_value =
                fuel_pump8_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(FuelPump8SwitchData,
                fuel_pump8_switch_dataf_off_value);


        }

        return;
    }




    if (testbit(switchbuf, FUEL_PUMP)) {
        if (engnum == 1) {
            XPLMCommandOnce(FuelPumpOn1);
        }
        if (engnum == 2) {
            XPLMCommandOnce(FuelPumpOn1);
            XPLMCommandOnce(FuelPumpOn2);
        }
        if (engnum == 3) {
            XPLMCommandOnce(FuelPumpOn1);
            XPLMCommandOnce(FuelPumpOn2);
            XPLMCommandOnce(FuelPumpOn3);
        }
        if (engnum == 4) {
            XPLMCommandOnce(FuelPumpOn1);
            XPLMCommandOnce(FuelPumpOn2);
            XPLMCommandOnce(FuelPumpOn3);
            XPLMCommandOnce(FuelPumpOn4);
        }
    }
    if (!testbit(switchbuf, FUEL_PUMP)) {
        if (engnum == 1) {
            XPLMCommandOnce(FuelPumpOff1);
        }
        if (engnum == 2) {
            XPLMCommandOnce(FuelPumpOff1);
            XPLMCommandOnce(FuelPumpOff2);
        }
        if (engnum == 3) {
            XPLMCommandOnce(FuelPumpOff1);
            XPLMCommandOnce(FuelPumpOff2);
            XPLMCommandOnce(FuelPumpOff3);
        }
        if (engnum == 4) {
            XPLMCommandOnce(FuelPumpOff1);
            XPLMCommandOnce(FuelPumpOff2);
            XPLMCommandOnce(FuelPumpOff3);
            XPLMCommandOnce(FuelPumpOff4);
        }
    }
}

// ***************** De Ice *******************

void process_de_ice_switch()
{
    if (testbit(switchbuf, DE_ICE)) {
        XPLMSetDatai(SwitchDiceOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchDiceOwnedDataRef, 0);
    }

    if (deiceswitchenable == 0) {
        return;
    }

    if (deiceswitchenable == 1) {
        if (testbit(switchbuf, DE_ICE)) {
            XPLMSetDatai(AntiIce, 1);
        }
        if (!testbit(switchbuf, DE_ICE)) {
            XPLMSetDatai(AntiIce, 0);
        }

        return;
    }

    if (deiceswitchenable == 2) {
        if (testbit(switchbuf, DE_ICE)) {
            XPLMCommandOnce(DeiceOnCmd);
            XPLMCommandOnce(DeiceOnCmd2);
            XPLMCommandOnce(DeiceOnCmd3);
            XPLMCommandOnce(DeiceOnCmd4);
            XPLMCommandOnce(DeiceOnCmd5);
            XPLMCommandOnce(DeiceOnCmd6);
            XPLMCommandOnce(DeiceOnCmd7);
            XPLMCommandOnce(DeiceOnCmd8);
        }

        if (!testbit(switchbuf, DE_ICE)) {
            XPLMCommandOnce(DeiceOffCmd);
            XPLMCommandOnce(DeiceOffCmd2);
            XPLMCommandOnce(DeiceOffCmd3);
            XPLMCommandOnce(DeiceOffCmd4);
            XPLMCommandOnce(DeiceOffCmd5);
            XPLMCommandOnce(DeiceOffCmd6);
            XPLMCommandOnce(DeiceOffCmd7);
            XPLMCommandOnce(DeiceOffCmd8);
        }

        return;
    }

    if (deiceswitchenable == 3) {
        if (testbit(switchbuf, DE_ICE)) {
            XPLMSetDatai(DeiceSwitchData, deice_switch_data_on_value);
            XPLMSetDatai(Deice2SwitchData, deice2_switch_data_on_value);
            XPLMSetDatai(Deice3SwitchData, deice3_switch_data_on_value);
            XPLMSetDatai(Deice4SwitchData, deice4_switch_data_on_value);
            XPLMSetDatai(Deice5SwitchData, deice5_switch_data_on_value);
            XPLMSetDatai(Deice6SwitchData, deice6_switch_data_on_value);
            XPLMSetDatai(Deice7SwitchData, deice7_switch_data_on_value);
            XPLMSetDatai(Deice8SwitchData, deice8_switch_data_on_value);
        }

        if (!testbit(switchbuf, DE_ICE)) {
            XPLMSetDatai(DeiceSwitchData, deice_switch_data_off_value);
            XPLMSetDatai(Deice2SwitchData, deice2_switch_data_off_value);
            XPLMSetDatai(Deice3SwitchData, deice3_switch_data_off_value);
            XPLMSetDatai(Deice4SwitchData, deice4_switch_data_off_value);
            XPLMSetDatai(Deice5SwitchData, deice5_switch_data_off_value);
            XPLMSetDatai(Deice6SwitchData, deice6_switch_data_off_value);
            XPLMSetDatai(Deice7SwitchData, deice7_switch_data_off_value);
            XPLMSetDatai(Deice8SwitchData, deice8_switch_data_off_value);
        }

        return;
    }


    if (deiceswitchenable == 4) {
        if (testbit(switchbuf, DE_ICE)) {

            deice_switch_dataf_on_value = deice_switch_data_on_value;
            deice_switch_dataf_on_value =
                deice_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(DeiceSwitchData, deice_switch_dataf_on_value);

            deice2_switch_dataf_on_value = deice2_switch_data_on_value;
            deice2_switch_dataf_on_value =
                deice2_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Deice2SwitchData, deice2_switch_dataf_on_value);

            deice3_switch_dataf_on_value = deice3_switch_data_on_value;
            deice3_switch_dataf_on_value =
                deice3_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Deice3SwitchData, deice3_switch_dataf_on_value);

            deice4_switch_dataf_on_value = deice4_switch_data_on_value;
            deice4_switch_dataf_on_value =
                deice4_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Deice4SwitchData, deice4_switch_dataf_on_value);

            deice5_switch_dataf_on_value = deice5_switch_data_on_value;
            deice5_switch_dataf_on_value =
                deice5_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Deice5SwitchData, deice5_switch_dataf_on_value);

            deice6_switch_dataf_on_value = deice6_switch_data_on_value;
            deice6_switch_dataf_on_value =
                deice6_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Deice6SwitchData, deice6_switch_dataf_on_value);

            deice7_switch_dataf_on_value = deice7_switch_data_on_value;
            deice7_switch_dataf_on_value =
                deice7_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Deice7SwitchData, deice7_switch_dataf_on_value);

            deice8_switch_dataf_on_value = deice8_switch_data_on_value;
            deice8_switch_dataf_on_value =
                deice8_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Deice8SwitchData, deice8_switch_dataf_on_value);


        }

        if (!testbit(switchbuf, DE_ICE)) {

            deice_switch_dataf_off_value = deice_switch_data_off_value;
            deice_switch_dataf_off_value =
                deice_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(DeiceSwitchData, deice_switch_dataf_off_value);

            deice2_switch_dataf_off_value = deice2_switch_data_off_value;
            deice2_switch_dataf_off_value =
                deice2_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Deice2SwitchData, deice2_switch_dataf_off_value);

            deice3_switch_dataf_off_value = deice3_switch_data_off_value;
            deice3_switch_dataf_off_value =
                deice3_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Deice3SwitchData, deice3_switch_dataf_off_value);


            deice4_switch_dataf_off_value = deice4_switch_data_off_value;
            deice4_switch_dataf_off_value =
                deice4_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Deice4SwitchData, deice4_switch_dataf_off_value);

            deice5_switch_dataf_off_value = deice5_switch_data_off_value;
            deice5_switch_dataf_off_value =
                deice5_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Deice5SwitchData, deice5_switch_dataf_off_value);

            deice6_switch_dataf_off_value = deice6_switch_data_off_value;
            deice6_switch_dataf_off_value =
                deice6_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Deice6SwitchData, deice6_switch_dataf_off_value);

            deice7_switch_dataf_off_value = deice7_switch_data_off_value;
            deice7_switch_dataf_off_value =
                deice7_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Deice7SwitchData, deice7_switch_dataf_off_value);

            deice8_switch_dataf_off_value = deice8_switch_data_off_value;
            deice8_switch_dataf_off_value =
                deice8_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Deice8SwitchData, deice8_switch_dataf_off_value);


        }

        return;
    }


}

// ***************** Pitot Heat *******************

void process_pitot_heat_switch()
{
    if (testbit(switchbuf, PITOT_HEAT)) {
        XPLMSetDatai(SwitchPitotOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchPitotOwnedDataRef, 0);
    }

    if (pitotheatswitchenable == 0) {
        return;
    }

    if (pitotheatswitchenable == 1) {
        if (testbit(switchbuf, PITOT_HEAT)) {
            if (wrgXPlaneVersion > 9700) {
                XPLMCommandOnce(PtHt0On);
                XPLMCommandOnce(PtHt1On);
            } else {
                XPLMCommandOnce(PtHtOn);
            }
        }
        if (!testbit(switchbuf, PITOT_HEAT)) {
            if (wrgXPlaneVersion > 9700) {
                XPLMCommandOnce(PtHt0Off);
                XPLMCommandOnce(PtHt1Off);
            } else {
                XPLMCommandOnce(PtHtOff);
            }
        }
        return;
    }

    if (pitotheatswitchenable == 2) {
        if (testbit(switchbuf, PITOT_HEAT)) {
            XPLMCommandOnce(PitotHeatOnCmd);
            XPLMCommandOnce(Pitot2HeatOnCmd);
        }
        if (!testbit(switchbuf, PITOT_HEAT)) {
            XPLMCommandOnce(PitotHeatOffCmd);
            XPLMCommandOnce(Pitot2HeatOffCmd);
        }
        return;
    }

    if (pitotheatswitchenable == 3) {
        if (testbit(switchbuf, PITOT_HEAT)) {
            XPLMSetDatai(PitotHeatSwitchData,
                pitot_heat_switch_data_on_value);
            XPLMSetDatai(Pitot2HeatSwitchData,
                pitot2_heat_switch_data_on_value);
            XPLMSetDatai(Pitot3HeatSwitchData,
                pitot3_heat_switch_data_on_value);
            XPLMSetDatai(Pitot4HeatSwitchData,
                pitot4_heat_switch_data_on_value);
            XPLMSetDatai(Pitot5HeatSwitchData,
                pitot5_heat_switch_data_on_value);
            XPLMSetDatai(Pitot6HeatSwitchData,
                pitot6_heat_switch_data_on_value);
            XPLMSetDatai(Pitot7HeatSwitchData,
                pitot7_heat_switch_data_on_value);
            XPLMSetDatai(Pitot8HeatSwitchData,
                pitot8_heat_switch_data_on_value);
        }
        if (!testbit(switchbuf, PITOT_HEAT)) {
            XPLMSetDatai(PitotHeatSwitchData,
                pitot_heat_switch_data_off_value);
            XPLMSetDatai(Pitot2HeatSwitchData,
                pitot2_heat_switch_data_off_value);
            XPLMSetDatai(Pitot3HeatSwitchData,
                pitot3_heat_switch_data_off_value);
            XPLMSetDatai(Pitot4HeatSwitchData,
                pitot4_heat_switch_data_off_value);
            XPLMSetDatai(Pitot5HeatSwitchData,
                pitot5_heat_switch_data_off_value);
            XPLMSetDatai(Pitot6HeatSwitchData,
                pitot6_heat_switch_data_off_value);
            XPLMSetDatai(Pitot7HeatSwitchData,
                pitot7_heat_switch_data_off_value);
            XPLMSetDatai(Pitot8HeatSwitchData,
                pitot8_heat_switch_data_off_value);
        }
        return;
    }

    if (pitotheatswitchenable == 4) {
        if (testbit(switchbuf, PITOT_HEAT)) {

            pitot_heat_switch_dataf_on_value =
                pitot_heat_switch_data_on_value;
            pitot_heat_switch_dataf_on_value =
                pitot_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(PitotHeatSwitchData,
                pitot_heat_switch_dataf_on_value);

            pitot2_heat_switch_dataf_on_value =
                pitot2_heat_switch_data_on_value;
            pitot2_heat_switch_dataf_on_value =
                pitot2_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Pitot2HeatSwitchData,
                pitot2_heat_switch_dataf_on_value);

            pitot3_heat_switch_dataf_on_value =
                pitot3_heat_switch_data_on_value;
            pitot3_heat_switch_dataf_on_value =
                pitot3_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Pitot3HeatSwitchData,
                pitot3_heat_switch_dataf_on_value);

            pitot4_heat_switch_dataf_on_value =
                pitot4_heat_switch_data_on_value;
            pitot4_heat_switch_dataf_on_value =
                pitot4_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Pitot4HeatSwitchData,
                pitot4_heat_switch_dataf_on_value);

            pitot5_heat_switch_dataf_on_value =
                pitot5_heat_switch_data_on_value;
            pitot5_heat_switch_dataf_on_value =
                pitot5_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Pitot5HeatSwitchData,
                pitot5_heat_switch_dataf_on_value);

            pitot6_heat_switch_dataf_on_value =
                pitot6_heat_switch_data_on_value;
            pitot6_heat_switch_dataf_on_value =
                pitot6_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Pitot6HeatSwitchData,
                pitot6_heat_switch_dataf_on_value);

            pitot7_heat_switch_dataf_on_value =
                pitot7_heat_switch_data_on_value;
            pitot7_heat_switch_dataf_on_value =
                pitot7_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Pitot7HeatSwitchData,
                pitot7_heat_switch_dataf_on_value);

            pitot8_heat_switch_dataf_on_value =
                pitot8_heat_switch_data_on_value;
            pitot8_heat_switch_dataf_on_value =
                pitot8_heat_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(Pitot8HeatSwitchData,
                pitot8_heat_switch_dataf_on_value);


        }
        if (!testbit(switchbuf, PITOT_HEAT)) {

            pitot_heat_switch_dataf_off_value =
                pitot_heat_switch_data_off_value;
            pitot_heat_switch_dataf_off_value =
                pitot_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(PitotHeatSwitchData,
                pitot_heat_switch_dataf_off_value);

            pitot2_heat_switch_dataf_off_value =
                pitot2_heat_switch_data_off_value;
            pitot2_heat_switch_dataf_off_value =
                pitot2_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Pitot2HeatSwitchData,
                pitot2_heat_switch_dataf_off_value);

            pitot3_heat_switch_dataf_off_value =
                pitot3_heat_switch_data_off_value;
            pitot3_heat_switch_dataf_off_value =
                pitot3_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Pitot3HeatSwitchData,
                pitot3_heat_switch_dataf_off_value);

            pitot4_heat_switch_dataf_off_value =
                pitot4_heat_switch_data_off_value;
            pitot4_heat_switch_dataf_off_value =
                pitot4_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Pitot4HeatSwitchData,
                pitot4_heat_switch_dataf_off_value);

            pitot5_heat_switch_dataf_off_value =
                pitot5_heat_switch_data_off_value;
            pitot5_heat_switch_dataf_off_value =
                pitot5_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Pitot5HeatSwitchData,
                pitot5_heat_switch_dataf_off_value);

            pitot6_heat_switch_dataf_off_value =
                pitot6_heat_switch_data_off_value;
            pitot6_heat_switch_dataf_off_value =
                pitot6_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Pitot6HeatSwitchData,
                pitot6_heat_switch_dataf_off_value);

            pitot7_heat_switch_dataf_off_value =
                pitot7_heat_switch_data_off_value;
            pitot7_heat_switch_dataf_off_value =
                pitot7_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Pitot7HeatSwitchData,
                pitot7_heat_switch_dataf_off_value);

            pitot8_heat_switch_dataf_off_value =
                pitot8_heat_switch_data_off_value;
            pitot8_heat_switch_dataf_off_value =
                pitot8_heat_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(Pitot8HeatSwitchData,
                pitot8_heat_switch_dataf_off_value);
        }
        return;
    }



}

// ***************** Cowl Flaps *******************

void process_cowl_flaps_switch()
{
    if (testbit(switchbuf, COWL_FLAPS)) {
        XPLMSetDatai(SwitchCowlOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchCowlOwnedDataRef, 0);
    }


    if (cowlflapsenable == 0) {
        return;
    }

    if (cowlflapsenable == 1) {
        if (!testbit(switchbuf, COWL_FLAPS)) {
            if (engnum == 1) {
                opencowl[0] = 1;
            }

            if (engnum == 2) {
                opencowl[0] = 1;
                opencowl[1] = 1;

            }
            if (engnum == 3) {
                opencowl[0] = 1;
                opencowl[1] = 1;
                opencowl[2] = 1;

            }
            if (engnum == 4) {
                opencowl[0] = 1;
                opencowl[1] = 1;
                opencowl[2] = 1;
                opencowl[3] = 1;

            }
            XPLMSetDatavf(CowlFlaps, opencowl, 0, 8);
        }

        if (testbit(switchbuf, COWL_FLAPS)) {
            if (engnum == 1) {
                closecowl[0] = 0;
            }
            if (engnum == 2) {
                closecowl[0] = 0;
                closecowl[1] = 0;
            }
            if (engnum == 3) {
                closecowl[0] = 0;
                closecowl[1] = 0;
                closecowl[2] = 0;
            }
            if (engnum == 4) {
                closecowl[0] = 0;
                closecowl[1] = 0;
                closecowl[2] = 0;
                closecowl[3] = 0;

            }
            XPLMSetDatavf(CowlFlaps, closecowl, 0, 8);

        }
        return;
    }

    if (cowlflapsenable == 2) {
        if (testbit(switchbuf, COWL_FLAPS)) {
            XPLMCommandOnce(CowlFlapsOpenCmd);
            XPLMCommandOnce(Cowl2FlapsOpenCmd);
            XPLMCommandOnce(Cowl3FlapsOpenCmd);
            XPLMCommandOnce(Cowl4FlapsOpenCmd);
        }

        if (!testbit(switchbuf, COWL_FLAPS)) {
            XPLMCommandOnce(CowlFlapsCloseCmd);
            XPLMCommandOnce(Cowl2FlapsCloseCmd);
            XPLMCommandOnce(Cowl3FlapsCloseCmd);
            XPLMCommandOnce(Cowl4FlapsCloseCmd);
        }
        return;
    }

    if (cowlflapsenable == 3) {
        if (testbit(switchbuf, COWL_FLAPS)) {
            XPLMSetDatai(CowlFlapsData, cowl_flaps_data_on_value);
            XPLMSetDatai(Cowl2FlapsData, cowl2_flaps_data_on_value);
            XPLMSetDatai(Cowl3FlapsData, cowl3_flaps_data_on_value);
            XPLMSetDatai(Cowl4FlapsData, cowl4_flaps_data_on_value);
            XPLMSetDatai(Cowl5FlapsData, cowl5_flaps_data_on_value);
            XPLMSetDatai(Cowl6FlapsData, cowl6_flaps_data_on_value);
            XPLMSetDatai(Cowl7FlapsData, cowl7_flaps_data_on_value);
            XPLMSetDatai(Cowl8FlapsData, cowl8_flaps_data_on_value);
        }
        if (!testbit(switchbuf, COWL_FLAPS)) {
            XPLMSetDatai(CowlFlapsData, cowl_flaps_data_off_value);
            XPLMSetDatai(Cowl2FlapsData, cowl2_flaps_data_off_value);
            XPLMSetDatai(Cowl3FlapsData, cowl3_flaps_data_off_value);
            XPLMSetDatai(Cowl4FlapsData, cowl4_flaps_data_off_value);
            XPLMSetDatai(Cowl5FlapsData, cowl5_flaps_data_off_value);
            XPLMSetDatai(Cowl6FlapsData, cowl6_flaps_data_off_value);
            XPLMSetDatai(Cowl7FlapsData, cowl7_flaps_data_off_value);
            XPLMSetDatai(Cowl8FlapsData, cowl8_flaps_data_off_value);
        }
        return;
    }


    if (cowlflapsenable == 4) {
        if (testbit(switchbuf, COWL_FLAPS)) {

            cowl_flaps_dataf_on_value = cowl_flaps_data_on_value;
            cowl_flaps_dataf_on_value = cowl_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(CowlFlapsData, cowl_flaps_dataf_on_value);

            cowl2_flaps_dataf_on_value = cowl2_flaps_data_on_value;
            cowl2_flaps_dataf_on_value = cowl2_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(Cowl2FlapsData, cowl2_flaps_dataf_on_value);

            cowl3_flaps_dataf_on_value = cowl3_flaps_data_on_value;
            cowl3_flaps_dataf_on_value = cowl3_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(Cowl3FlapsData, cowl3_flaps_dataf_on_value);

            cowl4_flaps_dataf_on_value = cowl4_flaps_data_on_value;
            cowl4_flaps_dataf_on_value = cowl4_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(Cowl4FlapsData, cowl4_flaps_dataf_on_value);

            cowl5_flaps_dataf_on_value = cowl5_flaps_data_on_value;
            cowl5_flaps_dataf_on_value = cowl5_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(Cowl5FlapsData, cowl5_flaps_dataf_on_value);

            cowl6_flaps_dataf_on_value = cowl6_flaps_data_on_value;
            cowl6_flaps_dataf_on_value = cowl6_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(Cowl6FlapsData, cowl6_flaps_dataf_on_value);

            cowl7_flaps_dataf_on_value = cowl7_flaps_data_on_value;
            cowl7_flaps_dataf_on_value = cowl7_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(Cowl7FlapsData, cowl7_flaps_dataf_on_value);

            cowl8_flaps_dataf_on_value = cowl8_flaps_data_on_value;
            cowl8_flaps_dataf_on_value = cowl8_flaps_dataf_on_value / 100.0f;
            XPLMSetDataf(Cowl8FlapsData, cowl8_flaps_dataf_on_value);


        }
        if (!testbit(switchbuf, COWL_FLAPS)) {

            cowl_flaps_dataf_off_value = cowl_flaps_data_off_value;
            cowl_flaps_dataf_off_value = cowl_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(CowlFlapsData, cowl_flaps_dataf_off_value);

            cowl2_flaps_dataf_off_value = cowl2_flaps_data_off_value;
            cowl2_flaps_dataf_off_value =
                cowl2_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(Cowl2FlapsData, cowl2_flaps_dataf_off_value);

            cowl3_flaps_dataf_off_value = cowl3_flaps_data_off_value;
            cowl3_flaps_dataf_off_value =
                cowl3_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(Cowl3FlapsData, cowl3_flaps_dataf_off_value);

            cowl4_flaps_dataf_off_value = cowl4_flaps_data_off_value;
            cowl4_flaps_dataf_off_value =
                cowl4_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(Cowl4FlapsData, cowl4_flaps_dataf_off_value);

            cowl5_flaps_dataf_off_value = cowl5_flaps_data_off_value;
            cowl5_flaps_dataf_off_value =
                cowl5_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(Cowl5FlapsData, cowl5_flaps_dataf_off_value);

            cowl6_flaps_dataf_off_value = cowl6_flaps_data_off_value;
            cowl6_flaps_dataf_off_value =
                cowl6_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(Cowl6FlapsData, cowl6_flaps_dataf_off_value);

            cowl7_flaps_dataf_off_value = cowl7_flaps_data_off_value;
            cowl7_flaps_dataf_off_value =
                cowl7_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(Cowl7FlapsData, cowl7_flaps_dataf_off_value);

            cowl8_flaps_dataf_off_value = cowl8_flaps_data_off_value;
            cowl8_flaps_dataf_off_value =
                cowl8_flaps_dataf_off_value / 100.0f;
            XPLMSetDataf(Cowl8FlapsData, cowl8_flaps_dataf_off_value);


        }
        return;
    }


}

// ***************** Panel Lights *******************

void process_panel_lights_switch()
{
    if (testbit(switchbuf, PANEL_LIGHTS)) {
        XPLMSetDatai(SwitchPanelOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchPanelOwnedDataRef, 0);
    }

    if (panellightswitchenable == 0) {
        return;
    }

    if (panellightswitchenable == 1) {
        if (testbit(switchbuf, PANEL_LIGHTS)) {
            XPLMSetDataf(CockpitLights, 1);
        }
        if (!testbit(switchbuf, PANEL_LIGHTS)) {
            XPLMSetDataf(CockpitLights, 0);
        }
        return;

    }

    if (panellightswitchenable == 2) {
        if (testbit(switchbuf, PANEL_LIGHTS)) {

            XPLMCommandOnce(PanelLightsOnCmd);
        }
        if (!testbit(switchbuf, PANEL_LIGHTS)) {

            XPLMCommandOnce(PanelLightsOffCmd);
        }
        return;
    }

    if (panellightswitchenable == 3) {
        if (testbit(switchbuf, PANEL_LIGHTS)) {
            XPLMSetDatai(PanelLightsData, panel_lights_switch_data_on_value);
            XPLMSetDatai(PanelLights2Data,
                panel_lights_switch2_data_on_value);
            XPLMSetDatai(PanelLights3Data,
                panel_lights_switch3_data_on_value);
            XPLMSetDatai(PanelLights4Data,
                panel_lights_switch4_data_on_value);
            XPLMSetDatai(PanelLights5Data,
                panel_lights_switch5_data_on_value);
            XPLMSetDatai(PanelLights6Data,
                panel_lights_switch6_data_on_value);
            XPLMSetDatai(PanelLights7Data,
                panel_lights_switch7_data_on_value);
            XPLMSetDatai(PanelLights8Data,
                panel_lights_switch8_data_on_value);
        }
        if (!testbit(switchbuf, PANEL_LIGHTS)) {
            XPLMSetDatai(PanelLightsData, panel_lights_switch_data_off_value);
            XPLMSetDatai(PanelLights2Data,
                panel_lights_switch2_data_off_value);
            XPLMSetDatai(PanelLights3Data,
                panel_lights_switch3_data_off_value);
            XPLMSetDatai(PanelLights4Data,
                panel_lights_switch4_data_off_value);
            XPLMSetDatai(PanelLights5Data,
                panel_lights_switch5_data_off_value);
            XPLMSetDatai(PanelLights6Data,
                panel_lights_switch6_data_off_value);
            XPLMSetDatai(PanelLights7Data,
                panel_lights_switch7_data_off_value);
            XPLMSetDatai(PanelLights8Data,
                panel_lights_switch8_data_off_value);
        }
        return;
    }

    if (panellightswitchenable == 4) {
        if (testbit(switchbuf, PANEL_LIGHTS)) {
            panel_lights_switch_dataf_on_value =
                panel_lights_switch_data_on_value;
            panel_lights_switch_dataf_on_value =
                panel_lights_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLightsData, panel_lights_switch_dataf_on_value);

            panel_lights_switch2_dataf_on_value =
                panel_lights_switch2_data_on_value;
            panel_lights_switch2_dataf_on_value =
                panel_lights_switch2_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLights2Data,
                panel_lights_switch2_dataf_on_value);

            panel_lights_switch3_dataf_on_value =
                panel_lights_switch3_data_on_value;
            panel_lights_switch3_dataf_on_value =
                panel_lights_switch3_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLights3Data,
                panel_lights_switch3_dataf_on_value);

            panel_lights_switch4_dataf_on_value =
                panel_lights_switch4_data_on_value;
            panel_lights_switch4_dataf_on_value =
                panel_lights_switch4_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLights4Data,
                panel_lights_switch4_dataf_on_value);

            panel_lights_switch5_dataf_on_value =
                panel_lights_switch5_data_on_value;
            panel_lights_switch5_dataf_on_value =
                panel_lights_switch5_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLights5Data,
                panel_lights_switch5_dataf_on_value);

            panel_lights_switch6_dataf_on_value =
                panel_lights_switch6_data_on_value;
            panel_lights_switch6_dataf_on_value =
                panel_lights_switch6_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLights6Data,
                panel_lights_switch6_dataf_on_value);

            panel_lights_switch7_dataf_on_value =
                panel_lights_switch7_data_on_value;
            panel_lights_switch7_dataf_on_value =
                panel_lights_switch7_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLights7Data,
                panel_lights_switch7_dataf_on_value);

            panel_lights_switch8_dataf_on_value =
                panel_lights_switch8_data_on_value;
            panel_lights_switch8_dataf_on_value =
                panel_lights_switch8_dataf_on_value / 100.0f;
            XPLMSetDataf(PanelLights8Data,
                panel_lights_switch8_dataf_on_value);

        }
        if (!testbit(switchbuf, PANEL_LIGHTS)) {
            panel_lights_switch_dataf_off_value =
                panel_lights_switch_data_off_value;
            panel_lights_switch_dataf_off_value =
                panel_lights_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLightsData,
                panel_lights_switch_dataf_off_value);

            panel_lights_switch2_dataf_off_value =
                panel_lights_switch2_data_off_value;
            panel_lights_switch2_dataf_off_value =
                panel_lights_switch2_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLights2Data,
                panel_lights_switch2_dataf_off_value);

            panel_lights_switch3_dataf_off_value =
                panel_lights_switch3_data_off_value;
            panel_lights_switch3_dataf_off_value =
                panel_lights_switch3_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLights3Data,
                panel_lights_switch3_dataf_off_value);

            panel_lights_switch4_dataf_off_value =
                panel_lights_switch4_data_off_value;
            panel_lights_switch4_dataf_off_value =
                panel_lights_switch4_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLights4Data,
                panel_lights_switch4_dataf_off_value);

            panel_lights_switch5_dataf_off_value =
                panel_lights_switch5_data_off_value;
            panel_lights_switch5_dataf_off_value =
                panel_lights_switch5_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLights5Data,
                panel_lights_switch5_dataf_off_value);

            panel_lights_switch6_dataf_off_value =
                panel_lights_switch6_data_off_value;
            panel_lights_switch6_dataf_off_value =
                panel_lights_switch6_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLights6Data,
                panel_lights_switch6_dataf_off_value);

            panel_lights_switch7_dataf_off_value =
                panel_lights_switch7_data_off_value;
            panel_lights_switch7_dataf_off_value =
                panel_lights_switch7_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLights7Data,
                panel_lights_switch7_dataf_off_value);

            panel_lights_switch8_dataf_off_value =
                panel_lights_switch8_data_off_value;
            panel_lights_switch8_dataf_off_value =
                panel_lights_switch8_dataf_off_value / 100.0f;
            XPLMSetDataf(PanelLights8Data,
                panel_lights_switch8_dataf_off_value);

        }
        return;
    }


    if (panellightswitchenable == 5) {
        if (testbit(switchbuf, PANEL_LIGHTS)) {
            panel_lights_switch_dataf_on_value =
                panel_lights_switch_data_on_value;
            panel_lights_switch_dataf_on_value =
                panel_lights_switch_dataf_on_value / 100.0f;
            panel_lights_switch_dataf_array
                [panel_lights_switch_data_array_offset] =
                panel_lights_switch_dataf_on_value;
            XPLMSetDatavf(PanelLightsData, panel_lights_switch_dataf_array, 0,
                panel_lights_switch_data_array_size);

            panel_lights_switch2_dataf_on_value =
                panel_lights_switch2_data_on_value;
            panel_lights_switch2_dataf_on_value =
                panel_lights_switch2_dataf_on_value / 100.0f;
            panel_lights_switch2_dataf_array
                [panel_lights_switch2_data_array_offset] =
                panel_lights_switch2_dataf_on_value;
            XPLMSetDatavf(PanelLights2Data, panel_lights_switch2_dataf_array,
                0, panel_lights_switch2_data_array_size);

            panel_lights_switch3_dataf_on_value =
                panel_lights_switch3_data_on_value;
            panel_lights_switch3_dataf_on_value =
                panel_lights_switch3_dataf_on_value / 100.0f;
            panel_lights_switch3_dataf_array
                [panel_lights_switch3_data_array_offset] =
                panel_lights_switch3_dataf_on_value;
            XPLMSetDatavf(PanelLights3Data, panel_lights_switch3_dataf_array,
                0, panel_lights_switch3_data_array_size);

            panel_lights_switch4_dataf_on_value =
                panel_lights_switch4_data_on_value;
            panel_lights_switch4_dataf_on_value =
                panel_lights_switch4_dataf_on_value / 100.0f;
            panel_lights_switch4_dataf_array
                [panel_lights_switch4_data_array_offset] =
                panel_lights_switch4_dataf_on_value;
            XPLMSetDatavf(PanelLights4Data, panel_lights_switch4_dataf_array,
                0, panel_lights_switch4_data_array_size);

            panel_lights_switch5_dataf_on_value =
                panel_lights_switch5_data_on_value;
            panel_lights_switch5_dataf_on_value =
                panel_lights_switch5_dataf_on_value / 100.0f;
            panel_lights_switch5_dataf_array
                [panel_lights_switch5_data_array_offset] =
                panel_lights_switch5_dataf_on_value;
            XPLMSetDatavf(PanelLights5Data, panel_lights_switch5_dataf_array,
                0, panel_lights_switch5_data_array_size);

            panel_lights_switch6_dataf_on_value =
                panel_lights_switch6_data_on_value;
            panel_lights_switch6_dataf_on_value =
                panel_lights_switch6_dataf_on_value / 100.0f;
            panel_lights_switch6_dataf_array
                [panel_lights_switch6_data_array_offset] =
                panel_lights_switch6_dataf_on_value;
            XPLMSetDatavf(PanelLights6Data, panel_lights_switch6_dataf_array,
                0, panel_lights_switch6_data_array_size);

            panel_lights_switch7_dataf_on_value =
                panel_lights_switch7_data_on_value;
            panel_lights_switch7_dataf_on_value =
                panel_lights_switch7_dataf_on_value / 100.0f;
            panel_lights_switch7_dataf_array
                [panel_lights_switch7_data_array_offset] =
                panel_lights_switch7_dataf_on_value;
            XPLMSetDatavf(PanelLights7Data, panel_lights_switch7_dataf_array,
                0, panel_lights_switch7_data_array_size);

            panel_lights_switch8_dataf_on_value =
                panel_lights_switch8_data_on_value;
            panel_lights_switch8_dataf_on_value =
                panel_lights_switch8_dataf_on_value / 100.0f;
            panel_lights_switch8_dataf_array
                [panel_lights_switch8_data_array_offset] =
                panel_lights_switch8_dataf_on_value;
            XPLMSetDatavf(PanelLights8Data, panel_lights_switch8_dataf_array,
                0, panel_lights_switch8_data_array_size);

        }
        if (!testbit(switchbuf, PANEL_LIGHTS)) {
            panel_lights_switch_dataf_off_value =
                panel_lights_switch_data_off_value;
            panel_lights_switch_dataf_off_value =
                panel_lights_switch_dataf_off_value / 100.0f;
            panel_lights_switch_dataf_array
                [panel_lights_switch_data_array_offset] =
                panel_lights_switch_dataf_off_value;
            XPLMSetDatavf(PanelLightsData, panel_lights_switch_dataf_array, 0,
                panel_lights_switch_data_array_size);

            panel_lights_switch2_dataf_off_value =
                panel_lights_switch2_data_off_value;
            panel_lights_switch2_dataf_off_value =
                panel_lights_switch2_dataf_off_value / 100.0f;
            panel_lights_switch2_dataf_array
                [panel_lights_switch2_data_array_offset] =
                panel_lights_switch2_dataf_off_value;
            XPLMSetDatavf(PanelLights2Data, panel_lights_switch2_dataf_array,
                0, panel_lights_switch2_data_array_size);

            panel_lights_switch3_dataf_off_value =
                panel_lights_switch3_data_off_value;
            panel_lights_switch3_dataf_off_value =
                panel_lights_switch3_dataf_off_value / 100.0f;
            panel_lights_switch3_dataf_array
                [panel_lights_switch3_data_array_offset] =
                panel_lights_switch3_dataf_off_value;
            XPLMSetDatavf(PanelLights3Data, panel_lights_switch3_dataf_array,
                0, panel_lights_switch3_data_array_size);

            panel_lights_switch4_dataf_off_value =
                panel_lights_switch4_data_off_value;
            panel_lights_switch4_dataf_off_value =
                panel_lights_switch4_dataf_off_value / 100.0f;
            panel_lights_switch4_dataf_array
                [panel_lights_switch4_data_array_offset] =
                panel_lights_switch4_dataf_off_value;
            XPLMSetDatavf(PanelLights4Data, panel_lights_switch4_dataf_array,
                0, panel_lights_switch4_data_array_size);

            panel_lights_switch5_dataf_off_value =
                panel_lights_switch5_data_off_value;
            panel_lights_switch5_dataf_off_value =
                panel_lights_switch5_dataf_off_value / 100.0f;
            panel_lights_switch5_dataf_array
                [panel_lights_switch5_data_array_offset] =
                panel_lights_switch5_dataf_off_value;
            XPLMSetDatavf(PanelLights5Data, panel_lights_switch5_dataf_array,
                0, panel_lights_switch5_data_array_size);

            panel_lights_switch6_dataf_off_value =
                panel_lights_switch6_data_off_value;
            panel_lights_switch6_dataf_off_value =
                panel_lights_switch6_dataf_off_value / 100.0f;
            panel_lights_switch6_dataf_array
                [panel_lights_switch6_data_array_offset] =
                panel_lights_switch6_dataf_off_value;
            XPLMSetDatavf(PanelLights6Data, panel_lights_switch6_dataf_array,
                0, panel_lights_switch6_data_array_size);

            panel_lights_switch7_dataf_off_value =
                panel_lights_switch7_data_off_value;
            panel_lights_switch7_dataf_off_value =
                panel_lights_switch7_dataf_off_value / 100.0f;
            panel_lights_switch7_dataf_array
                [panel_lights_switch7_data_array_offset] =
                panel_lights_switch7_dataf_off_value;
            XPLMSetDatavf(PanelLights7Data, panel_lights_switch7_dataf_array,
                0, panel_lights_switch7_data_array_size);

            panel_lights_switch8_dataf_off_value =
                panel_lights_switch8_data_off_value;
            panel_lights_switch8_dataf_off_value =
                panel_lights_switch8_dataf_off_value / 100.0f;
            panel_lights_switch8_dataf_array
                [panel_lights_switch8_data_array_offset] =
                panel_lights_switch8_dataf_off_value;
            XPLMSetDatavf(PanelLights8Data, panel_lights_switch8_dataf_array,
                0, panel_lights_switch8_data_array_size);

        }
        return;
    }

}

// ***************** Beacon Lights *******************

void process_beacon_lights_switch()
{
    if (testbit(switchbuf, BEACON_LIGHTS)) {
        XPLMSetDatai(SwitchBeaconOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchBeaconOwnedDataRef, 0);
    }

    if (beaconlightswitchenable == 0) {
        return;
    }

    if (beaconlightswitchenable == 2) {
        if (testbit(switchbuf, BEACON_LIGHTS)) {
            XPLMCommandOnce(BeaconLightsOnCmd);
        }
        if (!testbit(switchbuf, BEACON_LIGHTS)) {
            XPLMCommandOnce(BeaconLightsOffCmd);
        }
        return;
    }

    if (beaconlightswitchenable == 3) {
        if (testbit(switchbuf, BEACON_LIGHTS)) {
            XPLMSetDatai(BeaconLightsData,
                beacon_lights_switch_data_on_value);
            XPLMSetDatai(BeaconLights2Data,
                beacon_lights_switch2_data_on_value);
            XPLMSetDatai(BeaconLights3Data,
                beacon_lights_switch3_data_on_value);
            XPLMSetDatai(BeaconLights4Data,
                beacon_lights_switch4_data_on_value);

        }
        if (!testbit(switchbuf, BEACON_LIGHTS)) {
            XPLMSetDatai(BeaconLightsData,
                beacon_lights_switch_data_off_value);
            XPLMSetDatai(BeaconLights2Data,
                beacon_lights_switch2_data_off_value);
            XPLMSetDatai(BeaconLights3Data,
                beacon_lights_switch3_data_off_value);
            XPLMSetDatai(BeaconLights4Data,
                beacon_lights_switch4_data_off_value);
        }
        return;
    }

    if (beaconlightswitchenable == 4) {
        if (testbit(switchbuf, BEACON_LIGHTS)) {
            beacon_lights_switch_dataf_on_value =
                beacon_lights_switch_data_on_value;
            beacon_lights_switch_dataf_on_value =
                beacon_lights_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(BeaconLightsData,
                beacon_lights_switch_dataf_on_value);

            beacon_lights_switch2_dataf_on_value =
                beacon_lights_switch2_data_on_value;
            beacon_lights_switch2_dataf_on_value =
                beacon_lights_switch2_dataf_on_value / 100.0f;
            XPLMSetDataf(BeaconLights2Data,
                beacon_lights_switch2_dataf_on_value);

            beacon_lights_switch3_dataf_on_value =
                beacon_lights_switch3_data_on_value;
            beacon_lights_switch3_dataf_on_value =
                beacon_lights_switch3_dataf_on_value / 100.0f;
            XPLMSetDataf(BeaconLights3Data,
                beacon_lights_switch3_dataf_on_value);

            beacon_lights_switch4_dataf_on_value =
                beacon_lights_switch4_data_on_value;
            beacon_lights_switch4_dataf_on_value =
                beacon_lights_switch4_dataf_on_value / 100.0f;
            XPLMSetDataf(BeaconLights4Data,
                beacon_lights_switch4_dataf_on_value);

        }
        if (!testbit(switchbuf, BEACON_LIGHTS)) {
            beacon_lights_switch_dataf_off_value =
                beacon_lights_switch_data_off_value;
            beacon_lights_switch_dataf_off_value =
                beacon_lights_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(BeaconLightsData,
                beacon_lights_switch_dataf_off_value);

            beacon_lights_switch2_dataf_off_value =
                beacon_lights_switch2_data_off_value;
            beacon_lights_switch2_dataf_off_value =
                beacon_lights_switch2_dataf_off_value / 100.0f;
            XPLMSetDataf(BeaconLights2Data,
                beacon_lights_switch2_dataf_off_value);

            beacon_lights_switch3_dataf_off_value =
                beacon_lights_switch3_data_off_value;
            beacon_lights_switch3_dataf_off_value =
                beacon_lights_switch3_dataf_off_value / 100.0f;
            XPLMSetDataf(BeaconLights3Data,
                beacon_lights_switch3_dataf_off_value);

            beacon_lights_switch4_dataf_off_value =
                beacon_lights_switch4_data_off_value;
            beacon_lights_switch4_dataf_off_value =
                beacon_lights_switch4_dataf_off_value / 100.0f;
            XPLMSetDataf(BeaconLights4Data,
                beacon_lights_switch4_dataf_off_value);
        }
        return;
    }




    if (testbit(switchbuf, BEACON_LIGHTS)) {
        XPLMCommandOnce(BcLtOn);
    }
    if (!testbit(switchbuf, BEACON_LIGHTS)) {
        XPLMCommandOnce(BcLtOff);
    }
}

// ***************** Nav Lights *******************

void process_nav_lights_switch()
{
    if (testbit(switchbuf, NAV_LIGHTS)) {
        XPLMSetDatai(SwitchNavOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchNavOwnedDataRef, 0);
    }

    if (navlightswitchenable == 0) {
        return;
    }

    if (navlightswitchenable == 2) {
        if (testbit(switchbuf, NAV_LIGHTS)) {
            XPLMCommandOnce(NavLightsOnCmd);
        }
        if (!testbit(switchbuf, NAV_LIGHTS)) {
            XPLMCommandOnce(NavLightsOffCmd);
        }
        return;
    }

    if (navlightswitchenable == 3) {
        if (testbit(switchbuf, NAV_LIGHTS)) {
            XPLMSetDatai(NavLightsData, nav_lights_switch_data_on_value);
            XPLMSetDatai(NavLights2Data, nav_lights_switch2_data_on_value);
            XPLMSetDatai(NavLights3Data, nav_lights_switch3_data_on_value);
            XPLMSetDatai(NavLights4Data, nav_lights_switch4_data_on_value);
        }
        if (!testbit(switchbuf, NAV_LIGHTS)) {
            XPLMSetDatai(NavLightsData, nav_lights_switch_data_off_value);
            XPLMSetDatai(NavLights2Data, nav_lights_switch2_data_off_value);
            XPLMSetDatai(NavLights3Data, nav_lights_switch3_data_off_value);
            XPLMSetDatai(NavLights4Data, nav_lights_switch4_data_off_value);
        }
        return;
    }

    if (navlightswitchenable == 4) {
        if (testbit(switchbuf, NAV_LIGHTS)) {
            nav_lights_switch_dataf_on_value =
                nav_lights_switch_data_on_value;
            nav_lights_switch_dataf_on_value =
                nav_lights_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(NavLightsData, nav_lights_switch_dataf_on_value);

            nav_lights_switch2_dataf_on_value =
                nav_lights_switch2_data_on_value;
            nav_lights_switch2_dataf_on_value =
                nav_lights_switch2_dataf_on_value / 100.0f;
            XPLMSetDataf(NavLights2Data, nav_lights_switch2_dataf_on_value);

            nav_lights_switch3_dataf_on_value =
                nav_lights_switch3_data_on_value;
            nav_lights_switch3_dataf_on_value =
                nav_lights_switch3_dataf_on_value / 100.0f;
            XPLMSetDataf(NavLights3Data, nav_lights_switch3_dataf_on_value);

            nav_lights_switch4_dataf_on_value =
                nav_lights_switch4_data_on_value;
            nav_lights_switch4_dataf_on_value =
                nav_lights_switch4_dataf_on_value / 100.0f;
            XPLMSetDataf(NavLights4Data, nav_lights_switch4_dataf_on_value);

        }
        if (!testbit(switchbuf, NAV_LIGHTS)) {
            nav_lights_switch_dataf_off_value =
                nav_lights_switch_data_off_value;
            nav_lights_switch_dataf_off_value =
                nav_lights_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(NavLightsData, nav_lights_switch_dataf_off_value);

            nav_lights_switch2_dataf_off_value =
                nav_lights_switch2_data_off_value;
            nav_lights_switch2_dataf_off_value =
                nav_lights_switch2_dataf_off_value / 100.0f;
            XPLMSetDataf(NavLights2Data, nav_lights_switch2_dataf_off_value);

            nav_lights_switch3_dataf_off_value =
                nav_lights_switch3_data_off_value;
            nav_lights_switch3_dataf_off_value =
                nav_lights_switch3_dataf_off_value / 100.0f;
            XPLMSetDataf(NavLights3Data, nav_lights_switch3_dataf_off_value);

            nav_lights_switch4_dataf_off_value =
                nav_lights_switch4_data_off_value;
            nav_lights_switch4_dataf_off_value =
                nav_lights_switch4_dataf_off_value / 100.0f;
            XPLMSetDataf(NavLights4Data, nav_lights_switch4_dataf_off_value);

        }
        return;
    }

    if (testbit(switchbuf, NAV_LIGHTS)) {
        XPLMCommandOnce(NvLtOn);
    }
    if (!testbit(switchbuf, NAV_LIGHTS)) {
        XPLMCommandOnce(NvLtOff);
    }
}

// ***************** Strobe Lights *******************

void process_strobe_lights_switch()
{
    if (testbit(switchbuf, STROBE_LIGHTS)) {
        XPLMSetDatai(SwitchStrobeOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchStrobeOwnedDataRef, 0);
    }

    if (strobelightswitchenable == 0) {
        return;
    }

    if (strobelightswitchenable == 2) {
        if (testbit(switchbuf, STROBE_LIGHTS)) {
            XPLMCommandOnce(StrobeLightsOnCmd);
        }
        if (!testbit(switchbuf, STROBE_LIGHTS)) {
            XPLMCommandOnce(StrobeLightsOffCmd);
        }
        return;
    }

    if (strobelightswitchenable == 3) {
        if (testbit(switchbuf, STROBE_LIGHTS)) {
            XPLMSetDatai(StrobeLightsData,
                strobe_lights_switch_data_on_value);
            XPLMSetDatai(StrobeLights2Data,
                strobe_lights_switch2_data_on_value);
            XPLMSetDatai(StrobeLights3Data,
                strobe_lights_switch3_data_on_value);
            XPLMSetDatai(StrobeLights4Data,
                strobe_lights_switch4_data_on_value);
        }
        if (!testbit(switchbuf, STROBE_LIGHTS)) {
            XPLMSetDatai(StrobeLightsData,
                strobe_lights_switch_data_off_value);
            XPLMSetDatai(StrobeLights2Data,
                strobe_lights_switch2_data_off_value);
            XPLMSetDatai(StrobeLights3Data,
                strobe_lights_switch3_data_off_value);
            XPLMSetDatai(StrobeLights4Data,
                strobe_lights_switch4_data_off_value);
        }
        return;
    }

    if (strobelightswitchenable == 4) {
        if (testbit(switchbuf, STROBE_LIGHTS)) {
            strobe_lights_switch_dataf_on_value =
                strobe_lights_switch_data_on_value;
            strobe_lights_switch_dataf_on_value =
                strobe_lights_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(StrobeLightsData,
                strobe_lights_switch_dataf_on_value);

            strobe_lights_switch2_dataf_on_value =
                strobe_lights_switch2_data_on_value;
            strobe_lights_switch2_dataf_on_value =
                strobe_lights_switch2_dataf_on_value / 100.0f;
            XPLMSetDataf(StrobeLights2Data,
                strobe_lights_switch2_dataf_on_value);

            strobe_lights_switch3_dataf_on_value =
                strobe_lights_switch3_data_on_value;
            strobe_lights_switch3_dataf_on_value =
                strobe_lights_switch3_dataf_on_value / 100.0f;
            XPLMSetDataf(StrobeLights3Data,
                strobe_lights_switch3_dataf_on_value);

            strobe_lights_switch4_dataf_on_value =
                strobe_lights_switch4_data_on_value;
            strobe_lights_switch4_dataf_on_value =
                strobe_lights_switch4_dataf_on_value / 100.0f;
            XPLMSetDataf(StrobeLights4Data,
                strobe_lights_switch4_dataf_on_value);

        }
        if (!testbit(switchbuf, STROBE_LIGHTS)) {
            strobe_lights_switch_dataf_off_value =
                strobe_lights_switch_data_off_value;
            strobe_lights_switch_dataf_off_value =
                strobe_lights_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(StrobeLightsData,
                strobe_lights_switch_dataf_off_value);

            strobe_lights_switch2_dataf_off_value =
                strobe_lights_switch2_data_off_value;
            strobe_lights_switch2_dataf_off_value =
                strobe_lights_switch2_dataf_off_value / 100.0f;
            XPLMSetDataf(StrobeLights2Data,
                strobe_lights_switch2_dataf_off_value);

            strobe_lights_switch3_dataf_off_value =
                strobe_lights_switch3_data_off_value;
            strobe_lights_switch3_dataf_off_value =
                strobe_lights_switch3_dataf_off_value / 100.0f;
            XPLMSetDataf(StrobeLights3Data,
                strobe_lights_switch3_dataf_off_value);

            strobe_lights_switch4_dataf_off_value =
                strobe_lights_switch4_data_off_value;
            strobe_lights_switch4_dataf_off_value =
                strobe_lights_switch4_dataf_off_value / 100.0f;
            XPLMSetDataf(StrobeLights4Data,
                strobe_lights_switch4_dataf_off_value);
        }
        return;
    }

    if (testbit(switchbuf, STROBE_LIGHTS)) {
        XPLMCommandOnce(StLtOn);
    }
    if (!testbit(switchbuf, STROBE_LIGHTS)) {
        XPLMCommandOnce(StLtOff);
    }
}

// ***************** Taxi Lights *******************

void process_taxi_lights_switch()
{
    if (testbit(switchbuf, TAXI_LIGHTS)) {
        XPLMSetDatai(SwitchTaxiOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchTaxiOwnedDataRef, 0);
    }

    if (taxilightswitchenable == 0) {
        return;
    }

    if (taxilightswitchenable == 2) {
        if (testbit(switchbuf, TAXI_LIGHTS)) {
            XPLMCommandOnce(TaxiLightsOnCmd);
        }
        if (!testbit(switchbuf, TAXI_LIGHTS)) {
            XPLMCommandOnce(TaxiLightsOffCmd);
        }
        return;
    }

    if (taxilightswitchenable == 3) {
        if (testbit(switchbuf, TAXI_LIGHTS)) {
            XPLMSetDatai(TaxiLightsData, taxi_lights_switch_data_on_value);
            XPLMSetDatai(TaxiLights2Data, taxi_lights_switch2_data_on_value);
            XPLMSetDatai(TaxiLights3Data, taxi_lights_switch3_data_on_value);
            XPLMSetDatai(TaxiLights4Data, taxi_lights_switch4_data_on_value);

        }
        if (!testbit(switchbuf, TAXI_LIGHTS)) {
            XPLMSetDatai(TaxiLightsData, taxi_lights_switch_data_off_value);
            XPLMSetDatai(TaxiLights2Data, taxi_lights_switch2_data_off_value);
            XPLMSetDatai(TaxiLights3Data, taxi_lights_switch3_data_off_value);
            XPLMSetDatai(TaxiLights4Data, taxi_lights_switch4_data_off_value);
        }
        return;
    }

    if (taxilightswitchenable == 4) {
        if (testbit(switchbuf, TAXI_LIGHTS)) {
            taxi_lights_switch_dataf_on_value =
                taxi_lights_switch_data_on_value;
            taxi_lights_switch_dataf_on_value =
                taxi_lights_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(TaxiLightsData, taxi_lights_switch_dataf_on_value);

            taxi_lights_switch2_dataf_on_value =
                taxi_lights_switch2_data_on_value;
            taxi_lights_switch2_dataf_on_value =
                taxi_lights_switch2_dataf_on_value / 100.0f;
            XPLMSetDataf(TaxiLights2Data, taxi_lights_switch2_dataf_on_value);

            taxi_lights_switch3_dataf_on_value =
                taxi_lights_switch3_data_on_value;
            taxi_lights_switch3_dataf_on_value =
                taxi_lights_switch3_dataf_on_value / 100.0f;
            XPLMSetDataf(TaxiLights3Data, taxi_lights_switch3_dataf_on_value);

            taxi_lights_switch4_dataf_on_value =
                taxi_lights_switch4_data_on_value;
            taxi_lights_switch4_dataf_on_value =
                taxi_lights_switch4_dataf_on_value / 100.0f;
            XPLMSetDataf(TaxiLights4Data, taxi_lights_switch4_dataf_on_value);

        }
        if (!testbit(switchbuf, TAXI_LIGHTS)) {
            taxi_lights_switch_dataf_off_value =
                taxi_lights_switch_data_off_value;
            taxi_lights_switch_dataf_off_value =
                taxi_lights_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(TaxiLightsData, taxi_lights_switch_dataf_off_value);

            taxi_lights_switch2_dataf_off_value =
                taxi_lights_switch2_data_off_value;
            taxi_lights_switch2_dataf_off_value =
                taxi_lights_switch2_dataf_off_value / 100.0f;
            XPLMSetDataf(TaxiLights2Data,
                taxi_lights_switch2_dataf_off_value);

            taxi_lights_switch3_dataf_off_value =
                taxi_lights_switch3_data_off_value;
            taxi_lights_switch3_dataf_off_value =
                taxi_lights_switch3_dataf_off_value / 100.0f;
            XPLMSetDataf(TaxiLights3Data,
                taxi_lights_switch3_dataf_off_value);

            taxi_lights_switch4_dataf_off_value =
                taxi_lights_switch4_data_off_value;
            taxi_lights_switch4_dataf_off_value =
                taxi_lights_switch4_dataf_off_value / 100.0f;
            XPLMSetDataf(TaxiLights4Data,
                taxi_lights_switch4_dataf_off_value);
        }
        return;
    }


    if (testbit(switchbuf, TAXI_LIGHTS)) {
        XPLMCommandOnce(TxLtOn);
    }
    if (!testbit(switchbuf, TAXI_LIGHTS)) {
        XPLMCommandOnce(TxLtOff);
    }
}

// ***************** Landing Lights *******************

void process_landing_lights_switch()
{

    if (testbit(switchbuf, LANDING_LIGHTS)) {
        XPLMSetDatai(SwitchLandingOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchLandingOwnedDataRef, 0);
    }

    if (landinglightswitchenable == 0) {
        return;
    }

    if (landinglightswitchenable == 2) {
        if (testbit(switchbuf, LANDING_LIGHTS)) {
            XPLMCommandOnce(LandingLightsOnCmd);
        }
        if (!testbit(switchbuf, LANDING_LIGHTS)) {
            XPLMCommandOnce(LandingLightsOffCmd);
        }
        return;
    }

    if (landinglightswitchenable == 3) {
        if (testbit(switchbuf, LANDING_LIGHTS)) {
            XPLMSetDatai(LandingLightsData,
                landing_lights_switch_data_on_value);
            XPLMSetDatai(LandingLights2Data,
                landing_lights_switch2_data_on_value);
            XPLMSetDatai(LandingLights3Data,
                landing_lights_switch3_data_on_value);
            XPLMSetDatai(LandingLights4Data,
                landing_lights_switch4_data_on_value);
        }
        if (!testbit(switchbuf, LANDING_LIGHTS)) {
            XPLMSetDatai(LandingLightsData,
                landing_lights_switch_data_off_value);
            XPLMSetDatai(LandingLights2Data,
                landing_lights_switch2_data_off_value);
            XPLMSetDatai(LandingLights3Data,
                landing_lights_switch3_data_off_value);
            XPLMSetDatai(LandingLights4Data,
                landing_lights_switch4_data_off_value);
        }
        return;
    }

    if (landinglightswitchenable == 4) {
        if (testbit(switchbuf, LANDING_LIGHTS)) {
            landing_lights_switch_dataf_on_value =
                landing_lights_switch_data_on_value;
            landing_lights_switch_dataf_on_value =
                landing_lights_switch_dataf_on_value / 100.0f;
            XPLMSetDataf(LandingLightsData,
                landing_lights_switch_dataf_on_value);

            landing_lights_switch2_dataf_on_value =
                landing_lights_switch2_data_on_value;
            landing_lights_switch2_dataf_on_value =
                landing_lights_switch2_dataf_on_value / 100.0f;
            XPLMSetDataf(LandingLights2Data,
                landing_lights_switch2_dataf_on_value);

            landing_lights_switch3_dataf_on_value =
                landing_lights_switch3_data_on_value;
            landing_lights_switch3_dataf_on_value =
                landing_lights_switch3_dataf_on_value / 100.0f;
            XPLMSetDataf(LandingLights3Data,
                landing_lights_switch3_dataf_on_value);

            landing_lights_switch4_dataf_on_value =
                landing_lights_switch4_data_on_value;
            landing_lights_switch4_dataf_on_value =
                landing_lights_switch4_dataf_on_value / 100.0f;
            XPLMSetDataf(LandingLights4Data,
                landing_lights_switch4_dataf_on_value);

        }
        if (!testbit(switchbuf, LANDING_LIGHTS)) {
            landing_lights_switch_dataf_off_value =
                landing_lights_switch_data_off_value;
            landing_lights_switch_dataf_off_value =
                landing_lights_switch_dataf_off_value / 100.0f;
            XPLMSetDataf(LandingLightsData,
                landing_lights_switch_dataf_off_value);

            landing_lights_switch2_dataf_off_value =
                landing_lights_switch2_data_off_value;
            landing_lights_switch2_dataf_off_value =
                landing_lights_switch2_dataf_off_value / 100.0f;
            XPLMSetDataf(LandingLights2Data,
                landing_lights_switch2_dataf_off_value);

            landing_lights_switch3_dataf_off_value =
                landing_lights_switch3_data_off_value;
            landing_lights_switch3_dataf_off_value =
                landing_lights_switch3_dataf_off_value / 100.0f;
            XPLMSetDataf(LandingLights3Data,
                landing_lights_switch3_dataf_off_value);

            landing_lights_switch4_dataf_off_value =
                landing_lights_switch4_data_off_value;
            landing_lights_switch4_dataf_off_value =
                landing_lights_switch4_dataf_off_value / 100.0f;
            XPLMSetDataf(LandingLights4Data,
                landing_lights_switch4_dataf_off_value);
        }
        return;
    }


    if (testbit(switchbuf, LANDING_LIGHTS)) {
        XPLMCommandOnce(LnLtOn);
    }
    if (!testbit(switchbuf, LANDING_LIGHTS)) {
        XPLMCommandOnce(LnLtOff);
    }
}

// ***************** Gear Switch *******************

void process_gear_switch_switch()
{
    if (testbit(switchbuf, GEAR_SWITCH_UP)) {
        XPLMSetDatai(SwitchGearUpOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchGearUpOwnedDataRef, 0);
    }

    if (testbit(switchbuf, GEAR_SWITCH_DN)) {
        XPLMSetDatai(SwitchGearDnOwnedDataRef, 1);
    } else {
        XPLMSetDatai(SwitchGearDnOwnedDataRef, 0);
    }

    if (landinggearknobupenable == 0) {
        return;
    }

    if (landinggearknobupenable == 2) {

        if (testbit(switchbuf, GEAR_SWITCH_UP)) {
            XPLMCommandOnce(GearUpOnCmd);
        }

        if (testbit(switchbuf, GEAR_SWITCH_DN)) {
            XPLMCommandOnce(GearDnOnCmd);
        }

        return;
    }

    if (landinggearknobupenable == 3) {
        if (testbit(switchbuf, GEAR_SWITCH_UP)) {
            XPLMSetDatai(GearUpData, gear_switch_up_data_on_value);
        }
        if (!testbit(switchbuf, GEAR_SWITCH_UP)) {
            XPLMSetDatai(GearUpData, gear_switch_up_data_off_value);

        }
        if (testbit(switchbuf, GEAR_SWITCH_DN)) {
            XPLMSetDatai(GearDnData, gear_switch_down_data_on_value);
        }
        if (!testbit(switchbuf, GEAR_SWITCH_DN)) {
            XPLMSetDatai(GearDnData, gear_switch_down_data_off_value);
        }
        return;
    }

    if (landinggearknobupenable == 4) {
        if (testbit(switchbuf, GEAR_SWITCH_UP)) {
            gear_switch_up_dataf_on_value = gear_switch_up_data_on_value;
            gear_switch_up_dataf_on_value =
                gear_switch_up_dataf_on_value / 100.0f;
            XPLMSetDataf(GearUpData, gear_switch_up_dataf_on_value);
        }
        if (!testbit(switchbuf, GEAR_SWITCH_UP)) {
            gear_switch_up_dataf_off_value = gear_switch_up_data_off_value;
            gear_switch_up_dataf_off_value =
                gear_switch_up_dataf_off_value / 100.0f;
            XPLMSetDataf(GearUpData, gear_switch_up_dataf_off_value);

        }
        if (testbit(switchbuf, GEAR_SWITCH_DN)) {
            gear_switch_down_dataf_on_value = gear_switch_down_data_on_value;
            gear_switch_down_dataf_on_value =
                gear_switch_down_dataf_on_value / 100.0f;
            XPLMSetDataf(GearDnData, gear_switch_down_dataf_on_value);
        }
        if (!testbit(switchbuf, GEAR_SWITCH_DN)) {
            gear_switch_down_dataf_off_value =
                gear_switch_down_data_off_value;
            gear_switch_down_dataf_off_value =
                gear_switch_down_dataf_off_value / 100.0f;
            XPLMSetDataf(GearDnData, gear_switch_down_dataf_off_value);
        }
        return;
    }



    if (XPLMGetDatai(GearRetract) > 0) {
        XPLMGetDatavf(LandingGearStatus, LandingGearDeployRatio, 0, 10);
        // Gear is down and locked
        if (LandingGearDeployRatio[0] == 1) {
            gearled |= (1 << 0);        // * set bit 0 in gearled to 1 *
            gearled &= ~(1 << 3);       // * clear bit 3 in gearled to 0 *
        }
        if (LandingGearDeployRatio[1] == 1) {
            gearled |= (1 << 1);        // * set bit 1 in gearled to 1 *
            gearled &= ~(1 << 4);       // * clear bit 4 in gearled to 0 *
        }
        if (LandingGearDeployRatio[2] == 1) {
            gearled |= (1 << 2);        // * set bit 2 in gearled to 1 *
            gearled &= ~(1 << 5);       // * clear bit 5 in gearled to 0 *
        }
        // Gear is in motion
        if ((LandingGearDeployRatio[0] > 0)
            && (LandingGearDeployRatio[0] < 1)) {
            gearled |= (1 << 3);        // * set bit 3 in gearled to 1 *
            gearled &= ~(1 << 0);       // * clear bit 0 in gearled to 0 *
        }
        if ((LandingGearDeployRatio[1] > 0)
            && (LandingGearDeployRatio[1] < 1)) {
            gearled |= (1 << 4);        // * set bit 4 in gearled to 1 *
            gearled &= ~(1 << 1);       // * clear bit 1 in gearled to 0 *
        }
        if ((LandingGearDeployRatio[2] > 0)
            && (LandingGearDeployRatio[2] < 1)) {
            gearled |= (1 << 5);        // * set bit 5 in gearled to 1 *
            gearled &= ~(1 << 2);       // * clear bit 2 in gearled to 0 *
        }
        // Gear is up
        if (LandingGearDeployRatio[0] == 0) {
            gearled &= ~(1 << 0);       // * clear bit 0 in gearled to 0 *
            gearled &= ~(1 << 3);       // * clear bit 3 in gearled to 0 *
        }
        if (LandingGearDeployRatio[1] == 0) {
            gearled &= ~(1 << 1);       // * clear bit 1 in gearled to 0 *
            gearled &= ~(1 << 4);       // * clear bit 4 in gearled to 0 *
        }
        if (LandingGearDeployRatio[2] == 0) {
            gearled &= ~(1 << 2);       // * clear bit 2 in gearled to 0 *
            gearled &= ~(1 << 5);       // * clear bit 5 in gearled to 0 *
        }
        // Gear has failed

        if (testbit(switchbuf, GEAR_SWITCH_UP)) {

            // ********************************************************************************************
            // Nose gear had failed

            if (failed1dn == 0) {
                if (XPLMGetDatai(Gear1Fail) == 6) {
                    failed1up = 1;
                }
                if (XPLMGetDatai(Gear1Fail) == 0) {
                    failed1up = 0;
                }
                if (failed1up == 1) {
                    gearled &= ~(1 << 3);       // * set bit 3 in gearled to 1 *
                    gearled &= ~(1 << 0);       // * clear bit 1 in gearled to 0 *
                }

            }
            if (failed1dn == 1) {
                gearled |= (1 << 3);    // * set bit 3 in gearled to 1 *
                gearled &= ~(1 << 0);   // * clear bit 0 in gearled to 0 *
            }
            // *********************************************************************************************
            // Left gear has failed

            if (failed2dn == 0) {
                if (XPLMGetDatai(Gear2Fail) == 6) {
                    failed2up = 1;
                }
                if (XPLMGetDatai(Gear2Fail) == 0) {
                    failed2up = 0;
                }
                if (failed2up == 1) {
                    gearled &= ~(1 << 4);       // * set bit 3 in gearled to 1 *
                    gearled &= ~(1 << 1);       // * clear bit 1 in gearled to 0 *
                }

            }
            if (failed2dn == 1) {
                gearled |= (1 << 4);    // * set bit 3 in gearled to 1 *
                gearled &= ~(1 << 1);   // * clear bit 0 in gearled to 0 *
            }
            // **************************************************************************************************
            // Right gear has failed

            if (failed3dn == 0) {
                if (XPLMGetDatai(Gear3Fail) == 6) {
                    failed3up = 1;
                }
                if (XPLMGetDatai(Gear3Fail) == 0) {
                    failed3up = 0;
                }
                if (failed3up == 1) {
                    gearled &= ~(1 << 5);       // * set bit 3 in gearled to 1 *
                    gearled &= ~(1 << 2);       // * clear bit 1 in gearled to 0 *
                }

            }
            if (failed3dn == 1) {
                gearled |= (1 << 5);    // * set bit 3 in gearled to 1 *
                gearled &= ~(1 << 2);   // * clear bit 0 in gearled to 0 *
            }



        }

        if (testbit(switchbuf, GEAR_SWITCH_DN)) {

            // ******************************************************************************************************
            // Nose gear has failed

            if (failed1up == 0) {
                if (XPLMGetDatai(Gear1Fail) == 6) {
                    failed1dn = 1;
                }
                if (XPLMGetDatai(Gear1Fail) == 0) {
                    failed1dn = 0;
                }
                if (failed1dn == 1) {
                    gearled |= (1 << 0);        // * set bit 0 in gearled to 1 *
                    gearled &= ~(1 << 3);       // * clear bit 3 in gearled to 0 *
                }

            }
            if (failed1up == 1) {
                gearled |= (1 << 3);    // * set bit 3 in gearled to 1 *
                gearled &= ~(1 << 0);   // * clear bit 0 in gearled to 0 *
            }
            // *******************************************************************************************************
            // Left gear has failed

            if (failed2up == 0) {
                if (XPLMGetDatai(Gear2Fail) == 6) {
                    failed2dn = 1;
                }
                if (XPLMGetDatai(Gear2Fail) == 0) {
                    failed2dn = 0;
                }
                if (failed2dn == 1) {
                    gearled |= (1 << 1);        // * set bit 0 in gearled to 1 *
                    gearled &= ~(1 << 4);       // * clear bit 3 in gearled to 0 *
                }

            }
            if (failed2up == 1) {
                gearled |= (1 << 4);    // * set bit 3 in gearled to 1 *
                gearled &= ~(1 << 1);   // * clear bit 0 in gearled to 0 *
            }
            // *******************************************************************************************************
            // Right gear has failed

            if (failed3up == 0) {
                if (XPLMGetDatai(Gear3Fail) == 6) {
                    failed3dn = 1;
                }
                if (XPLMGetDatai(Gear3Fail) == 0) {
                    failed3dn = 0;
                }
                if (failed3dn == 1) {
                    gearled |= (1 << 2);        // * set bit 0 in gearled to 1 *
                    gearled &= ~(1 << 5);       // * clear bit 3 in gearled to 0 *
                }

            }
            if (failed3up == 1) {
                gearled |= (1 << 5);    // * set bit 3 in gearled to 1 *
                gearled &= ~(1 << 2);   // * clear bit 0 in gearled to 0 *
            }

        }

        if (testbit(switchbuf, GEAR_SWITCH_UP)) {
            XPLMCommandOnce(GearUp);
            if (XPLMGetDatai(OnGround) > 0) {
                gearled = 0x38;
            }

        }

        if (testbit(switchbuf, GEAR_SWITCH_DN)) {
            XPLMCommandOnce(GearDn);
        }

    }
    if (XPLMGetDatai(GearRetract) == 0) {
        gearled = 0x00;
    }
}


//  ***** Switch Panel Process  *****
void process_switch_panel()
{
    process_switch_menu();

    // ******* Only do a read if something new to be read ********

    hid_set_nonblocking(switchhandle, 1);
    XPLMGetDatavi(AcfEnType, acf_en_type, 0, 8);
    int switch_safety_cntr = 30;
    do {
        switchres = hid_read(switchhandle, switchbuf, sizeof(switchbuf));
        process_engines_mag_off_switch();
        process_engines_right_mag_switch();
        process_engines_left_mag_switch();
        process_engines_both_mag_switch();
        process_engines_start_switch();
        process_master_battery_switch();
        process_master_altenator_switch();
        process_avionics_power_switch();
        process_fuel_pump_switch();
        process_de_ice_switch();
        process_pitot_heat_switch();
        process_cowl_flaps_switch();
        process_panel_lights_switch();
        process_beacon_lights_switch();
        process_nav_lights_switch();
        process_strobe_lights_switch();
        process_taxi_lights_switch();
        process_landing_lights_switch();
        process_gear_switch_switch();

        --switch_safety_cntr;
    } while ((switchres > 0) && (switch_safety_cntr > 0));

    switchnowrite = 1;

    // * if no gear do not write *

    if (XPLMGetDatai(GearRetract) > 0) {
        if (!BatPwrIsOn()) {
            switchwbuf[0] = 0, switchwbuf[1] = 0;
            switchwres = hid_send_feature_report(switchhandle, switchwbuf, 2);
        }
        if (BatPwrIsOn()) {
            switchwres = hid_send_feature_report(switchhandle, switchwbuf, 2);
        }
    } else {
    }

    batnum = XPLMGetDatai(BatNum), gennum = XPLMGetDatai(GenNum);
    engnum = XPLMGetDatai(EngNum);

    return;
}
