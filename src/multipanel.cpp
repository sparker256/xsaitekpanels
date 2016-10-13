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
#include <math.h>
#include <vector>
#if     APL || LIN
#include <arpa/inet.h>
#endif  /* APL || LIN */

#include "Command.h"
#include "Log.h"
#include "time.h"
#include "inireader.h"
#include "readinifile.h"

#include "multipanel.h"

using namespace xsaitekpanels;

enum {
    AP_LIGHT_BIT = 0,
    HDG_LIGHT_BIT = 1,
    NAV_LIGHT_BIT = 2,
    IAS_LIGHT_BIT = 3,
    ALT_LIGHT_BIT = 4,
    VS_LIGHT_BIT = 5,
    APR_LIGHT_BIT = 6,
    REV_LIGHT_BIT = 7
};

enum {
    READOUT_ALT_VS,
    READOUT_IAS,
    READOUT_HDG,
    READOUT_CRS,
    READOUT_PANEL_NUM,
    READOUT_NONE
};

enum {
    ACCEL_THRESH = 80000,                       /* 80 ms*/
    HOLD_BTN_TIMEOUT = 1000000,                 /* 1 second */
    AUTO_UPDATE_INTVAL = 250000,                /* 200 ms */
    BTN_DOUBLE_PRESS_SUPP_INTVAL = 70000        /* 70 ms */
};

#define DFL_FLASH_INTVAL 1.0                    /* 1 second */

enum {
    FLAPS_UP_SWITCH = 0,
    FLAPS_DN_SWITCH = 1,
    TRIM_WHEEL_DN = 2,
    TRIM_WHEEL_UP = 3,
    HDG_BUTTON = 8,
    NAV_BUTTON = 9,
    IAS_BUTTON = 10,
    ALT_BUTTON = 11,
    VS_BUTTON = 12,
    APR_BUTTON = 13,
    REV_BUTTON = 14,
    AUTO_THROTTLE_SWITCH = 15,
    ALT_SWITCH = 16,
    VS_SWITCH = 17,
    IAS_SWITCH = 18,
    HDG_SWITCH = 19,
    CRS_SWITCH = 20,
    ADJUSTMENT_UP = 21,
    ADJUSTMENT_DN = 22,
    AP_MASTER_BUTTON = 23
};

enum {
    NUM_DIGITS = 5,
    MINUS_SYMBOL = 254,
    SPACE_SYMBOL = 15
};

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define VAR_DESTROY(var) \
    do { \
        if ((var) != NULL) \
            delete (var); \
        (var) = NULL; \
    } while (0)

#if     IBM
#define mutex_enter(mtx) \
    VERIFY(WaitForSingleObject(*(mtx), INFINITE) == WAIT_OBJECT_0)
#define mutex_exit(mtx)         VERIFY(ReleaseMutex(*(mtx)) != 0)
#else   /* !IBM */
#define mutex_enter(mtx)        VERIFY(pthread_mutex_lock(mtx) == 0)
#define mutex_exit(mtx)         VERIFY(pthread_mutex_unlock(mtx) == 0)
#endif  /* !IBM */

static vector<Multipanel *> multipanels;
static double flash_intval = DFL_FLASH_INTVAL;

static vector<int> MultiAltSwitchOwnedData,
    MultiVsSwitchOwnedData,
    MultiIasSwitchOwnedData,
    MultiHdgSwitchOwnedData,
    MultiCrsSwitchOwnedData,
    MultiKnobIncOwnedData,
    MultiKnobDecOwnedData,
    MultiKnobIncTicksOwnedData,
    MultiKnobDecTicksOwnedData,
    MultiAtOwnedData,
    MultiTrimUpOwnedData,
    MultiTrimDnOwnedData,
    MultiFlapsUpOwnedData,
    MultiFlapsDnOwnedData,
    MultiApBtnOwnedData,
    MultiHdgBtnOwnedData,
    MultiNavBtnOwnedData,
    MultiIasBtnOwnedData,
    MultiAltBtnOwnedData,
    MultiVsBtnOwnedData,
    MultiAprBtnOwnedData,
    MultiRevBtnOwnedData;

static Dataref *MultiAltSwitchOwnedDataRef = NULL,
    *MultiVsSwitchOwnedDataRef = NULL,
    *MultiIasSwitchOwnedDataRef = NULL,
    *MultiHdgSwitchOwnedDataRef = NULL,
    *MultiCrsSwitchOwnedDataRef = NULL,
    *MultiKnobIncOwnedDataRef = NULL,
    *MultiKnobDecOwnedDataRef = NULL,
    *MultiKnobIncTicksOwnedDataRef = NULL,
    *MultiKnobDecTicksOwnedDataRef = NULL,
    *MultiAtOwnedDataRef = NULL,
    *MultiTrimUpOwnedDataRef = NULL,
    *MultiTrimDnOwnedDataRef = NULL,
    *MultiFlapsUpOwnedDataRef = NULL,
    *MultiFlapsDnOwnedDataRef = NULL,
    *MultiApBtnOwnedDataRef = NULL,
    *MultiHdgBtnOwnedDataRef = NULL,
    *MultiNavBtnOwnedDataRef = NULL,
    *MultiIasBtnOwnedDataRef = NULL,
    *MultiAltBtnOwnedDataRef = NULL,
    *MultiVsBtnOwnedDataRef = NULL,
    *MultiAprBtnOwnedDataRef = NULL,
    *MultiRevBtnOwnedDataRef = NULL;

#define getbit(arg, bit)        (((arg) >> bit) & 1)

static void setbit(int *targ, int bitn, int val)
{
    if (val)
        *targ |= (1 << bitn);
    else
        *targ &= ~(1 << bitn);
}

Multipanel::Multipanel(unsigned panel_number, const char *hidpath)
{
    memset(switches, 0, sizeof (switches));
    memset(button_info, 0, sizeof (button_info));
    memset(button_lights, 0, sizeof (button_lights));
    memset(sendbuf, 0, sizeof (sendbuf));
    panel_num = panel_number;

    display_readout = READOUT_NONE;
    memset(adigits, 0, sizeof (adigits));
    memset(bdigits, 0, sizeof (bdigits));
    btnleds = 0;

    altitude = vs = airspeed = hdg = crs = 0.0;

    handle = hid_open_path(hidpath);
    hid_set_nonblocking(handle, 0);

    last_auto_update_time = 0;
    knob_last_up = false;
    knob_last_dn = false;
    knob_up_dampen = 0;
    knob_dn_dampen = 0;
    knob_up_time = 0;
    knob_dn_time = 0;

    reconfigure();

    memset(buttons, 0, sizeof (buttons));
    memset(buttons_main, 0, sizeof (buttons_main));
    send_cmd = false;
    reader_shutdown = false;

#if IBM
    mtx = CreateMutex(NULL, FALSE, NULL);
    VERIFY(mtx != NULL);
    reader = CreateThread(NULL, 0,
        (LPTHREAD_START_ROUTINE)multipanel_reader_thread, this, 0, NULL);
    VERIFY(reader != NULL);
#else
    VERIFY(pthread_mutex_init(&mtx, NULL) == 0);
    VERIFY(pthread_create(&reader, NULL, multipanel_reader_thread, this) == 0);
#endif

    enable_readout(READOUT_PANEL_NUM);
    process_multi_display();
    sched_update_command();
}

void *xsaitekpanels::multipanel_reader_thread(void *arg)
{
    Multipanel *mp = (Multipanel *)arg;
    mp->reader_main();
    return (NULL);
}

Multipanel::~Multipanel()
{
    hid_close(handle);

    VAR_DESTROY(athr_sw_dr);
    for (int i = 0; i < NUM_SW_INFOS; i++) {
        VAR_DESTROY(switches[i].dr);
        VAR_DESTROY(switches[i].up_cmd);
        VAR_DESTROY(switches[i].dn_cmd);
    }
    for (int i = 0; i < NUM_BTN_INFOS; i++) {
        VAR_DESTROY(button_info[i].dr);
        VAR_DESTROY(button_info[i].cmd);
        VAR_DESTROY(button_info[i].rev_cmd);
    }
    VAR_DESTROY(ias_is_mach_dr);

#if     IBM
    CloseHandle(mtx);
    CloseHandle(reader);
#else   /* !IBM */
    pthread_mutex_destroy(&mtx);
#endif  /* !IBM */
}

int
xsaitekpanels::get_num_multipanels()
{
    return (multipanels.size());
}

void xsaitekpanels::open_all_multipanels()
{
    struct hid_device_info *multi_devs, *multi_cur_dev;

    multi_devs = hid_enumerate(0x6a3, 0x0d06);
    multi_cur_dev = multi_devs;
    for (unsigned int i = 0; multi_cur_dev != NULL; i++) {
        Multipanel *mp = new Multipanel(i, multi_cur_dev->path);
        if (mp != NULL)
            multipanels.push_back(mp);
        multi_cur_dev = multi_cur_dev->next;
    }
    hid_free_enumeration(multi_devs);

    if (multipanels.size() > 0) {
        register_multipanel_drs();
    }
}

void xsaitekpanels::close_all_multipanels()
{
    for (size_t i = 0, n = multipanels.size(); i < n; i++) {
        Multipanel *mp = multipanels[i];
        mp->shutdown();
        delete (mp);
    }
    multipanels.clear();
}

static void int2digits(uint8_t digits[NUM_DIGITS], const char *fmt, int value)
{
    char strbuf[NUM_DIGITS + 1];
    int n = snprintf(strbuf, sizeof(strbuf), fmt, value);

    n = MIN(n, NUM_DIGITS);
    for (int i = 1; i <= NUM_DIGITS; i++) {
        if (n - i >= 0) {
            switch (strbuf[n - i]) {
            case '-':
                digits[NUM_DIGITS - i] = MINUS_SYMBOL;
                break;
            case ' ':
                digits[NUM_DIGITS - i] = SPACE_SYMBOL;
                break;
            default:
                digits[NUM_DIGITS - i] = strbuf[n - i] - '0';
                break;
            }
        } else {
            digits[NUM_DIGITS - i] = SPACE_SYMBOL;
        }
    }
}

void Multipanel::process_multi_display()
{
    switch (display_readout) {
    case READOUT_ALT_VS:
        int2digits(adigits, "%04d", altitude);
        int2digits(bdigits, "%03d", vs);
        break;
    case READOUT_IAS:
        int2digits(adigits, "%02d", airspeed);
        int2digits(bdigits, "", 0);
        break;
    case READOUT_HDG:
        int2digits(adigits, "%03d", hdg);
        int2digits(bdigits, "", 0);
        break;
    case READOUT_CRS:
        int2digits(adigits, "%03d", crs);
        int2digits(bdigits, "", 0);
        break;
    case READOUT_PANEL_NUM:
        int2digits(adigits, "%05d", panel_num);
        int2digits(bdigits, "%05d", panel_num);
        btnleds = 0;
        break;
    case READOUT_NONE:
    default:
        int2digits(adigits, "", 0);
        int2digits(bdigits, "", 0);
        btnleds = 0;
        break;
    }
}

void Multipanel::sched_update_command()
{
    /* load array with message of digits and button LEDs */
    mutex_enter(&mtx);

    sendbuf[0] = 0;
    memcpy(&sendbuf[1], adigits, sizeof(adigits));
    memcpy(&sendbuf[6], bdigits, sizeof(bdigits));
    sendbuf[11] = btnleds;
    sendbuf[12] = 0;
    send_cmd = true;

    mutex_exit(&mtx);
}

void Multipanel::process_drs()
{
    int val;

    val = (buttons_main[ALT_SWITCH] != 0);
    MultiAltSwitchOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[VS_SWITCH] != 0);
    MultiVsSwitchOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[IAS_SWITCH] != 0);
    MultiIasSwitchOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[HDG_SWITCH] != 0);
    MultiHdgSwitchOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[CRS_SWITCH] != 0);
    MultiCrsSwitchOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[ADJUSTMENT_UP] != 0);
    MultiKnobIncOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[ADJUSTMENT_DN] != 0);
    MultiKnobDecOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[AUTO_THROTTLE_SWITCH] != 0);
    MultiAtOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[TRIM_WHEEL_UP] != 0);
    MultiTrimUpOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[TRIM_WHEEL_DN] != 0);
    MultiTrimDnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[FLAPS_UP_SWITCH] != 0);
    MultiFlapsUpOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[FLAPS_DN_SWITCH] != 0);
    MultiFlapsDnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[AP_MASTER_BUTTON] != 0);
    MultiApBtnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[HDG_BUTTON] != 0);
    MultiHdgBtnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[NAV_BUTTON] != 0);
    MultiNavBtnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[IAS_BUTTON] != 0);
    MultiIasBtnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[ALT_BUTTON] != 0);
    MultiAltBtnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[VS_BUTTON] != 0);
    MultiVsBtnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[APR_BUTTON] != 0);
    MultiAprBtnOwnedDataRef->setv(&val, panel_num, 1);
    val = (buttons_main[REV_BUTTON] != 0);
    MultiRevBtnOwnedDataRef->setv(&val, panel_num, 1);

    MultiKnobIncTicksOwnedDataRef->setv(&buttons_main[ADJUSTMENT_UP],
        panel_num, 1);
    MultiKnobDecTicksOwnedDataRef->setv(&buttons_main[ADJUSTMENT_DN],
        panel_num, 1);
}

static double adjust_value(double value, double maxval, double minval,
    double step, bool loop)
{
    /* round to the nearest multiple of `step' */
    value = round(value / step) * step;

    /* normalize the value, either by looping or simply cutting it off */
    while (value < minval) {
        if (loop)
            value+= maxval - minval;
        else
            value = minval;
    }
    while (value > maxval) {
        if (loop)
            value -= maxval - minval;
        else
            value = maxval;
    }

    return (value);
}

void Multipanel::process_switch_adjustment(int value, uint64_t *lastadj_time,
    Dataref *dr, Command *cmd, double maxval, double minval, double step,
    bool loop, float accel, int max_accel_mult)
{
    if (value <= 0)
        return;

    uint64_t now = microclock();
    uint64_t delta, keep_delta, accel_delta;
    int mult;

    delta = (now - *lastadj_time) / value;
    keep_delta = ACCEL_THRESH / accel;
    accel_delta = (ACCEL_THRESH / 2.0) / accel;

    if (delta <= accel_delta)
        accel_mult++;
    else if (delta > keep_delta)
        accel_mult = 1;

    mult = MIN(accel_mult, max_accel_mult);

    /*
     * We first try the command to adjust and only then directly manipulate
     * the dataref.
     */
    if (cmd != NULL) {
        while (mult-- > 0)
            cmd->once();
    } else if (dr != NULL) {
        dr->set(adjust_value(dr->getd() + step * mult, maxval, minval,
            step, loop));
    }

    *lastadj_time = now;
}

void Multipanel::process_switch(const switch_info_t *sw)
{
    uint64_t now = microclock();

    if (now - knob_dn_time > ACCEL_THRESH) {
        process_switch_adjustment(buttons_main[ADJUSTMENT_UP],
            &knob_up_time, sw->dr, sw->up_cmd, sw->maxval, sw->minval,
            sw->step, sw->loop, sw->accel, sw->max_accel);
    }
    if (now - knob_up_time > ACCEL_THRESH) {
        process_switch_adjustment(buttons_main[ADJUSTMENT_DN],
            &knob_dn_time, sw->dr, sw->dn_cmd, sw->maxval, sw->minval,
            -sw->step, sw->loop, sw->accel, sw->max_accel);
    }
    /* mark events as consumed */
    buttons_main[ADJUSTMENT_UP] = 0;
    buttons_main[ADJUSTMENT_DN] = 0;
}

void Multipanel::enable_readout(int readout)
{
    VERIFY(readout >= READOUT_ALT_VS && readout <= READOUT_NONE);
    display_readout = readout;
}

void Multipanel::update_alt_vs_readout()
{
    enable_readout(READOUT_ALT_VS);
    altitude = lroundf(switches[ALT_SW_INFO].dr->getf());
    vs = lroundf(switches[VS_SW_INFO].dr->getf());
}

void Multipanel::process_alt_switch()
{
    process_switch(&switches[ALT_SW_INFO]);
    update_alt_vs_readout();
}

void Multipanel::process_vs_switch()
{
    process_switch(&switches[VS_SW_INFO]);
    update_alt_vs_readout();
}

void Multipanel::process_ias_switch()
{
    bool ismach;

    ismach = (ias_is_mach_dr->geti() == 1);
    process_switch(&switches[!ismach ? IAS_SW_INFO : IAS_MACH_SW_INFO]);

    enable_readout(READOUT_IAS);
    if (!ismach)
        airspeed = lroundf(switches[IAS_SW_INFO].dr->getd());
    else
        airspeed = lroundf(switches[IAS_MACH_SW_INFO].dr->getd() * 100);
}

void Multipanel::process_hdg_switch()
{
    process_switch(&switches[HDG_SW_INFO]);
    enable_readout(READOUT_HDG);
    hdg = lroundf(switches[HDG_SW_INFO].dr->getf());
}

void Multipanel::process_crs_switch()
{
    int info = xpanelsfnbutton == 0 ? CRS_SW_INFO : CRS2_SW_INFO;
    process_switch(&switches[info]);
    enable_readout(READOUT_CRS);
    crs = lroundf(switches[info].dr->getd());
}

void Multipanel::process_autothrottle_switch()
{
    if (!athr_sw_enabled)
        return;
    if (buttons_main[AUTO_THROTTLE_SWITCH] != 0)
        athr_sw_dr->set(athr_sw_enabled_val);
    else
        athr_sw_dr->set(athr_sw_disabled_val);
}

#define UPDATE_LIGHT_BIT(bitn, newval) \
    do { \
        int v = (newval); \
        if (getbit(btnleds, bitn) != v) { \
            setbit(&btnleds, bitn, v); \
            updated = true; \
        } \
    } while (0)

bool Multipanel::process_light(const button_light_info_t *info, int bitn,
    bool flash_on)
{
    bool updated = false;

    switch(info->type) {
    case OnOffFlashLight:
    case OnOffFlashLight_dup:
        if (info->flash_dr != NULL && info->flash_dr->getd() >= 0.5)
            UPDATE_LIGHT_BIT(bitn, flash_on);
        else if (info->dr != NULL)
            UPDATE_LIGHT_BIT(bitn, info->dr->getd() >= 0.5);
        break;
    case OnOffFlash3StateLight:
        if (info->dr != NULL) {
            switch(info->dr->geti()) {
            case 0:
                UPDATE_LIGHT_BIT(bitn, 0);
                break;
            case 1:
                UPDATE_LIGHT_BIT(bitn, flash_on);
                break;
            case 2:
                UPDATE_LIGHT_BIT(bitn, 1);
                break;
            }
        }
        break;
    default:
        UPDATE_LIGHT_BIT(bitn, 0);
        break;
    }

    return (updated);
}

#undef UPDATE_LIGHT_BIT

/*
 * Here we process all the light datarefs for our buttons and illuminate them
 * accordingly.
 */
bool Multipanel::process_lights()
{
    /*
     * When a button is supposed to be flashing, the `flash_on' variable
     * determines if the button is supposed to be illumuninated at this
     * instant. We base it on the system clock and the flash_intval. We
     * modularly subdivide the current system time by the flash_intval
     * and if the remainder is in the first half of flash_intval, the
     * lights are off, otherwise they are on.
     */
    uint64_t now_ms = microclock() / 1000.0;
    uint64_t flash_ms = flash_intval * 1000;
    bool flash_on = (now_ms % flash_ms) > (flash_ms / 2);
    bool updated = false;

    /*
     * The bitwise OR here is so that any single light update triggers
     * us to return true.
     */
    updated =
        process_light(&button_lights[AP_BTN_INFO], AP_LIGHT_BIT, flash_on) |
        process_light(&button_lights[HDG_BTN_INFO], HDG_LIGHT_BIT, flash_on) |
        process_light(&button_lights[NAV_BTN_INFO], NAV_LIGHT_BIT, flash_on) |
        process_light(&button_lights[IAS_BTN_INFO], IAS_LIGHT_BIT, flash_on) |
        process_light(&button_lights[ALT_BTN_INFO], ALT_LIGHT_BIT, flash_on) |
        process_light(&button_lights[VS_BTN_INFO], VS_LIGHT_BIT, flash_on) |
        process_light(&button_lights[APR_BTN_INFO], APR_LIGHT_BIT, flash_on) |
        process_light(&button_lights[REV_BTN_INFO], REV_LIGHT_BIT, flash_on);

    return (updated);
}

/*
 * We support four configurable button types:
 *
 * 1) MomentaryPushButton: this button activates immediately when it is
 *      depressed and deactivates when it is released.
 *      If the user defined a command for this button, we will BEGIN
 *      the command on depression of the button and END the command when
 *      the button is released.
 *      If the user defined dataref, we will try to continuously set
 *      this dataref to the on_value on depression and set it once to the
 *      off_value on release.
 *
 * 2) OneShotButton: this button activates immediately when it is
 *      depressed and does nothing when it is released.
 *      If the user defined a command, we will execute the command ONCE
 *      when the button is depressed.
 *      If the user defined a dataref, we will try to set it to the
 *      on_value once when the button is depressed.
 *
 * 3) ToggleButton: this button toggles between two states each time that
 *      it is depressed. It does nothing when it is released.
 *      If the user defined a command, we behave the same as the OneShotButton.
 *      If the user defined a dataref, we will first examine the value of
 *      this dataref. If the value is == on_value, we will try to set the
 *      dataref once to the off_value. Otherwise we will try to set it
 *      once to the on_value.
 *
 * 4) MomentaryPushUpHoldDownButton: this button allows a user to move between
 *      several linearly ordered states, either up the sequence or down the
 *      sequence. Pushing the button momentarily and releasing it moves up
 *      the sequence. Pushing and holding the button depressed for at least
 *      1 second moves down the sequence. Continuing to hold the button
 *      will continue to move down the sequence at 1 second intervals.
 *      If the user defined a command a reverse command (cmd, rev_cmd), the
 *      normal `cmd' is performed ONCE each time the button fires in the up
 *      direction and the `rev_cmd" is performed ONCE for each time the
 *      button fires in the down direction.
 *      If the user defined a dataref, an on_value, an off_value, a max_value
 *      and a min_value, the button works as follows. On firing in the up
 *      direction, the button checks if the dataref to see if it is less than
 *      the max_value. If it is, it'll increment the value of the dataref
 *      by the on_value. On firing in the down direction, the button checks
 *      if the dataref is greater than the min_value. If it is, it'll
 *      decrement the dataref by the off_value.
 */
void Multipanel::process_button_common(int btn_id, button_info_t *btn_info)
{
    if (buttons_main[btn_id] != 0) {
        /* record whether the button was just depressed this cycle */
        bool first_press = !btn_info->press_state;

        if (first_press) {
            uint64_t now = microclock();

            /*
             * Sometimes, when lightly pressed and quickly released, buttons
             * can double-press, sending a rapid succession of button
             * push & release updates. To protect against that, we limit the
             * rate at which buttons can be pressed to 20 presses per second.
             */
            if (now - btn_info->release_time < BTN_DOUBLE_PRESS_SUPP_INTVAL)
                return;

            btn_info->press_state = true;
            btn_info->press_time = now;
            btn_info->n_fired = 0;
        }

        if (btn_info->type == MomentaryPushButton) {
            if (btn_info->cmd != NULL) {
                /* start the command on depression */
                if (first_press)
                    btn_info->cmd->begin();
            } else if (btn_info->dr != NULL) {
                /* keep trying to set the on_value continuously */
                btn_info->dr->set(btn_info->on_value);
            }
        } else if (btn_info->type == OneShotButton) {
            if (btn_info->cmd != NULL) {
                /* run the command once on depression */
                if (first_press)
                    btn_info->cmd->once();
            } else if (btn_info->dr != NULL) {
                /* try to set the on_value once on depression */
                if (first_press)
                    btn_info->dr->set(btn_info->on_value);
            }
        } else if (btn_info->type == ToggleButton) {
            if (btn_info->cmd != NULL) {
                /* run the command once on depression */
                if (first_press)
                    btn_info->cmd->once();
            } else if (btn_info->dr != NULL) {
                /* toggle the dataref between the on_value and off_value */
                if (first_press) {
                    if (btn_info->dr->getd() == btn_info->on_value)
                        btn_info->dr->set(btn_info->off_value);
                    else
                        btn_info->dr->set(btn_info->on_value);
                }
            }
        } else {
            uint64_t now = microclock();

            if (now - btn_info->press_time > HOLD_BTN_TIMEOUT) {
                /* reset the timer so holding the button fires again */
                btn_info->press_time = now;
                btn_info->n_fired++;

                if (btn_info->rev_cmd != NULL) {
                    btn_info->rev_cmd->once();
                } else if (btn_info->dr != NULL) {
                    double old_val = btn_info->dr->getd();
                    /* only decrement if we're above min_value */
                    if (old_val > btn_info->min_value)
                        btn_info->dr->set(old_val - btn_info->off_value);
                }
            }
        }
    } else if (buttons_main[btn_id] == 0 && btn_info->press_state) {
        if (btn_info->type == MomentaryPushButton) {
            if (btn_info->cmd != NULL)
                /* end the command on button release */
                btn_info->cmd->end();
            else if (btn_info->dr != NULL)
                /* try to set the off_value once */
                btn_info->dr->set(btn_info->off_value);
        } else if (btn_info->type == MomentaryPushUpHoldDownButton) {
            /* only fire the up action if we weren't held for too long */
            if (btn_info->n_fired == 0) {
                if (btn_info->cmd != NULL)
                    btn_info->cmd->once();
                else if (btn_info->dr != NULL) {
                    double old_val = btn_info->dr->getd();
                    /* only increment if we're below min_value */
                    if (old_val < btn_info->max_value)
                        btn_info->dr->set(old_val + btn_info->on_value);
                }
            }
        }
        /*
         * The other button types don't do anything on button release.
         */

        btn_info->press_state = false;
        btn_info->release_time = microclock();
    }
}

void Multipanel::process_trim_wheel()
{
    process_switch_adjustment(buttons_main[TRIM_WHEEL_UP],
        &trim_up_last, NULL, trim_up_cmd, 0, 0, 0,
        false, trim_up_accel, trim_up_max_accel);
    process_switch_adjustment(buttons_main[TRIM_WHEEL_DN],
        &trim_down_last, NULL, trim_down_cmd, 0, 0, 0,
        false, trim_down_accel, trim_down_max_accel);
    /* mark events as consumed */
    buttons_main[TRIM_WHEEL_UP] = 0;
    buttons_main[TRIM_WHEEL_DN] = 0;
}

static int dampen_knob_ticks(int ticks, int *dampen, int ticks_per_step)
{
    int out_ticks = 0;

    for (int t = ticks; t > 0; t--) {
        (*dampen)++;
        if (*dampen == ticks_per_step) {
            *dampen = 0;
            out_ticks++;
        }
    }

    return (out_ticks);
}

void Multipanel::process()
{
    bool sched_update = false;
    bool updated;
    uint64_t now = microclock();

    mutex_enter(&mtx);

    updated = buttons_updated;
    buttons_updated = false;
    if (updated) {
        memcpy(buttons_main, buttons, sizeof (buttons_main));
        memset(buttons, 0, sizeof (buttons));
    }

    mutex_exit(&mtx);

    /* check power status */
    if (!BatPwrIsOn() || !AvPwrIsOn()) {
        if (display_readout != READOUT_NONE) {
            enable_readout(READOUT_NONE);
            process_multi_display();
            sched_update_command();
        }
        return;
    }
    /* if the display was blank, we're coming out of power-off */
    if (display_readout == READOUT_NONE)
        updated = true;

    /* process the knob dampening */
    if (updated) {
        buttons_main[ADJUSTMENT_UP] = dampen_knob_ticks(
            buttons_main[ADJUSTMENT_UP], &knob_up_dampen, knob_speed);
        buttons_main[ADJUSTMENT_DN] = dampen_knob_ticks(
            buttons_main[ADJUSTMENT_DN], &knob_dn_dampen, knob_speed);
    }

    if (updated) {
        /*
         * We need to process these first, because the switch processing
         * consumes the knob & trim wheel events.
         */
        process_drs();

        if (buttons_main[CRS_SWITCH])
            process_crs_switch();
        else if (buttons_main[HDG_SWITCH])
            process_hdg_switch();
        else if (buttons_main[IAS_SWITCH])
            process_ias_switch();
        else if (buttons_main[VS_SWITCH])
            process_vs_switch();
        else if (buttons_main[ALT_SWITCH])
            process_alt_switch();

        process_autothrottle_switch();
        process_trim_wheel();
    }

    process_button_common(AP_MASTER_BUTTON, &button_info[AP_BTN_INFO]);
    process_button_common(HDG_BUTTON, &button_info[HDG_BTN_INFO]);
    if (xpanelsfnbutton == 0) {
        process_button_common(NAV_BUTTON, &button_info[NAV_BTN_INFO]);
        process_button_common(IAS_BUTTON, &button_info[IAS_BTN_INFO]);
    } else {
        process_button_common(NAV_BUTTON, &button_info[LNAV_BTN_INFO]);
        process_button_common(IAS_BUTTON,
            &button_info[IAS_CHANGEOVER_BTN_INFO]);
    }
    process_button_common(ALT_BUTTON, &button_info[ALT_BTN_INFO]);
    process_button_common(VS_BUTTON, &button_info[VS_BTN_INFO]);
    process_button_common(APR_BUTTON, &button_info[APR_BTN_INFO]);
    process_button_common(REV_BUTTON, &button_info[REV_BTN_INFO]);
    process_button_common(FLAPS_UP_SWITCH, &button_info[FLAPS_UP_BTN_INFO]);
    process_button_common(FLAPS_DN_SWITCH, &button_info[FLAPS_DN_BTN_INFO]);

    sched_update = process_lights();

    if (updated || now - last_auto_update_time > AUTO_UPDATE_INTVAL) {
        process_multi_display();
        last_auto_update_time = now;
        sched_update = true;
    }

    if (sched_update)
        sched_update_command();
}

void Multipanel::shutdown()
{
    reader_shutdown = true;
#if     IBM
    WaitForSingleObject(reader, INFINITE);
#else   /* !IBM */
    pthread_join(reader, NULL);
#endif  /* !IBM */
}

void xsaitekpanels::process_all_multipanels()
{
    for (size_t i = 0, n = multipanels.size(); i < n; i++) {
        Multipanel *mp = multipanels[i];
        mp->process();
    }
}

template <typename T>static void ini_opt_setup(const char *optname,
    T *option, T dfl_value)
{
    if (getOptionToString(optname) != "")
        *option = getOptionToFloat(optname);
    else
        *option = dfl_value;
}

void xsaitekpanels::reconfigure_all_multipanels()
{
    for (size_t i = 0, n = multipanels.size(); i < n; i++) {
        Multipanel *mp = multipanels[i];
        mp->reconfigure();
    }
}

void Multipanel::reconfigure()
{
    ini_opt_setup("Multi Freq Knob Pulse per Command", &knob_speed, 2);
    ini_opt_setup("Multi Flash Interval", &flash_intval, DFL_FLASH_INTVAL);

    ini_opt_setup("Auto Throttle Switch enable", &athr_sw_enabled, true);
    ini_opt_setup("Auto Throttle Switch Armed value",
        &athr_sw_enabled_val, 1.0);
    ini_opt_setup("Auto Throttle Switch Disarmed value",
        &athr_sw_disabled_val, 0.0);
    ini2remap("Auto Throttle Switch enable",
        I2R_DR_ARG, "auto_throttle_switch_remapable_data",
        "sim/cockpit2/autopilot/autothrottle_enabled", &athr_sw_dr,
        I2R_END_ARG);

#define SWITCH_FROM_INI_ARGS(sw, basename, dfl_data, dfl_maxval, dfl_minval, \
    dfl_step, dfl_accel, dfl_max_accel, dfl_loop) \
        I2R_CMD_ARG, basename "_up_remapable_cmd", NULL, &(sw)->up_cmd, \
        I2R_CMD_ARG, basename "_dn_remapable_cmd", NULL, &(sw)->dn_cmd, \
        I2R_DR_ARG, basename "_remapable_data", dfl_data, &(sw)->dr, \
        I2R_FLOAT_ARG, basename "_maxval", dfl_maxval, &(sw)->maxval, \
        I2R_FLOAT_ARG, basename "_minval", dfl_minval, &(sw)->minval, \
        I2R_FLOAT_ARG, basename "_step", dfl_step, &(sw)->step, \
        I2R_FLOAT_ARG, basename "_accel", dfl_accel, &(sw)->accel, \
        I2R_FLOAT_ARG, basename "_max_accel", dfl_max_accel, &(sw)->max_accel, \
        I2R_INT_ARG, basename "_loop", dfl_loop, &(sw)->loop, \
        I2R_END_ARG
    ini2remap("Alt Switch remapable",
        SWITCH_FROM_INI_ARGS(&switches[ALT_SW_INFO], "alt_switch",
        "sim/cockpit/autopilot/altitude", 99900.0, 0.0, 100.0, 1.0, 10.0, 0));
    ini2remap("Vs Switch remapable",
        SWITCH_FROM_INI_ARGS(&switches[VS_SW_INFO], "vs_switch",
        "sim/cockpit/autopilot/vertical_velocity", 9900.0, -9900.0, 100.0, 1.0,
        1.0, 0));
    ini2remap("Ias Switch remapable",
        SWITCH_FROM_INI_ARGS(&switches[IAS_SW_INFO], "ias_switch",
        "sim/cockpit/autopilot/airspeed", 999.0, 0.0, 1.0, 1.0, 5.0, 0));
    ini2remap("Ias Switch remapable",
        SWITCH_FROM_INI_ARGS(&switches[IAS_MACH_SW_INFO], "ias_switch_mach",
        "sim/cockpit/autopilot/airspeed", 0.99, 0.5, 0.01, 1.0, 1.0, 0));
    ini2remap("Ias Ismach remapable", I2R_DR_ARG,
        "ias_ismach_remapable_data", "sim/cockpit/autopilot/airspeed_is_mach",
        &ias_is_mach_dr, I2R_END_ARG);
    ini2remap("Hdg Switch remapable",
        SWITCH_FROM_INI_ARGS(&switches[HDG_SW_INFO], "hdg_switch",
        "sim/cockpit/autopilot/heading_mag", 359.9, 0.0, 1.0, 1.0, 10.0, 1));
    ini2remap("Crs Switch remapable",
        SWITCH_FROM_INI_ARGS(&switches[CRS_SW_INFO], "crs_switch",
        "sim/cockpit/radios/nav1_obs_degm", 359.9, 0.0, 1.0, 1.0, 10.0, 1));
    ini2remap("Crs Switch remapable",
        SWITCH_FROM_INI_ARGS(&switches[CRS2_SW_INFO], "crs_switch2",
        "sim/cockpit/radios/nav2_obs_degm", 359.9, 0.0, 1.0, 1.0, 10.0, 1));
#undef SWITCH_FROM_INI_ARGS

    ini2remap("Trim Up remapable",
        I2R_CMD_ARG, "trim_up_remapable_cmd",
        "sim/flight_controls/pitch_trim_up", &trim_up_cmd,
        I2R_FLOAT_ARG, "trim_up_accel", 1.0, &trim_up_accel,
        I2R_FLOAT_ARG, "trim_up_max_accel", 3.0, &trim_up_max_accel,
        I2R_END_ARG);
    ini2remap("Trim Dn remapable",
        I2R_CMD_ARG, "trim_dn_remapable_cmd",
        "sim/flight_controls/pitch_trim_down", &trim_down_cmd,
        I2R_FLOAT_ARG, "trim_dn_accel", 1.0, &trim_down_accel,
        I2R_FLOAT_ARG, "trim_dn_max_accel", 3.0, &trim_down_max_accel,
        I2R_END_ARG);

#define BUTTON_FROM_INI_ARGS(btn, basename, dfl_type, dfl_cmd, dfl_rev_cmd, \
    dfl_dr, dfl_on_val, dfl_off_val, dfl_max, dfl_min) \
        I2R_INT_ARG, basename "_type", dfl_type, &(btn)->type, \
        I2R_CMD_ARG, basename "_remapable_cmd", dfl_cmd, &(btn)->cmd, \
        I2R_CMD_ARG, basename "_remapable_cmd_rev", dfl_rev_cmd, \
        &(btn)->rev_cmd, \
        I2R_DR_ARG, basename "_remapable_data", dfl_dr, &(btn)->dr, \
        I2R_FLOAT_ARG, basename "_remapable_data_on_value", \
        dfl_on_val, &(btn)->on_value, \
        I2R_FLOAT_ARG, basename "_remapable_data_off_value", \
        dfl_off_val, &(btn)->off_value, \
        I2R_FLOAT_ARG, basename "_remapable_data_max_value", dfl_max, \
        &(btn)->max_value, \
        I2R_FLOAT_ARG, basename "_remapable_data_min_value", dfl_min, \
        &(btn)->min_value, \
        I2R_END_ARG
    ini2remap("Ap Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[AP_BTN_INFO], "ap_button",
        MomentaryPushUpHoldDownButton, "sim/autopilot/fdir_servos_up_one",
        "sim/autopilot/fdir_servos_down_one", NULL, 0.0, 0.0, 0.0, 0.0));
    ini2remap("Hdg Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[HDG_BTN_INFO], "hdg_button",
        OneShotButton, "sim/autopilot/heading", NULL, NULL, 0.0, 0.0, 0.0,
        0.0));
    ini2remap("Nav Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[NAV_BTN_INFO], "nav_button",
        OneShotButton, "sim/autopilot/NAV", NULL, NULL, 0.0, 0.0, 0.0, 0.0));
    ini2remap("Lnav Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[LNAV_BTN_INFO], "lnav_button",
        OneShotButton, "sim/autopilot/NAV", NULL, NULL, 0.0, 0.0, 0.0, 0.0));
    ini2remap("Ias Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[IAS_BTN_INFO], "ias_button",
        OneShotButton, "sim/autopilot/level_change", NULL, NULL, 0.0, 0.0,
        0.0, 0.0));
    ini2remap("Ias Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[IAS_CHANGEOVER_BTN_INFO],
        "ias_changeover_button", OneShotButton,
        "sim/autopilot/knots_mach_toggle", NULL, NULL, 0.0, 0.0, 0.0, 0.0));
    ini2remap("Alt Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[ALT_BTN_INFO], "alt_button",
        OneShotButton, "sim/autopilot/altitude_hold", NULL, NULL, 0.0, 0.0,
        0.0, 0.0));
    ini2remap("Vs Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[VS_BTN_INFO], "vs_button",
        OneShotButton, "sim/autopilot/vertical_speed", NULL, NULL, 0.0, 0.0,
        0.0, 0.0));
    ini2remap("Apr Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[APR_BTN_INFO], "apr_button",
        OneShotButton, "sim/autopilot/approach", NULL, NULL, 0.0, 0.0,
        0.0, 0.0));
    ini2remap("Rev Button remapable",
        BUTTON_FROM_INI_ARGS(&button_info[REV_BTN_INFO], "rev_button",
        OneShotButton, "sim/autopilot/back_course", NULL, NULL, 0.0, 0.0,
        0.0, 0.0));
    ini2remap("Flaps Up remapable",
        BUTTON_FROM_INI_ARGS(&button_info[FLAPS_UP_BTN_INFO], "flaps_up",
        OneShotButton, "sim/flight_controls/flaps_up", NULL, NULL,
        0.0, 0.0, 0.0, 0.0));
    ini2remap("Flaps Dn remapable",
        BUTTON_FROM_INI_ARGS(&button_info[FLAPS_DN_BTN_INFO], "flaps_dn",
        OneShotButton, "sim/flight_controls/flaps_down", NULL, NULL,
        0.0, 0.0, 0.0, 0.0));
#undef BUTTON_FROM_INI_ARGS

#define BUTTON_LIGHT_FROM_INI_ARGS(lt, basename, dfl_lt_type, dfl_dr, \
    dfl_flash_dr) \
        I2R_INT_ARG, "Light datareference type", dfl_lt_type, &(lt)->type, \
        I2R_DR_ARG, basename "_light_remapable_data", dfl_dr, &(lt)->dr, \
        I2R_DR_ARG, basename "_light_flash_remapable_data", dfl_flash_dr, \
        &(lt)->flash_dr, \
        I2R_END_ARG
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[AP_BTN_INFO], "ap",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/flight_director_mode",
        NULL));
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[HDG_BTN_INFO], "hdg",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/heading_status", NULL));
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[NAV_BTN_INFO], "nav",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/nav_status", NULL));
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[IAS_BTN_INFO], "ias",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/speed_status", NULL));
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[ALT_BTN_INFO], "alt",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/altitude_hold_status",
        NULL));
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[VS_BTN_INFO], "vs",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/vvi_status", NULL));
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[APR_BTN_INFO], "apr",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/approach_status",
        NULL));
    ini2remap("Light datareference type",
        BUTTON_LIGHT_FROM_INI_ARGS(&button_lights[REV_BTN_INFO], "rev",
        OnOffFlash3StateLight, "sim/cockpit2/autopilot/backcourse_status",
        NULL));
#undef BUTTON_LIGHT_FROM_INI_ARGS
}

void xsaitekpanels::register_multipanel_drs()
{
#define DR_REGISTER_ACCESSOR(basename, name) \
    do { \
        const char *drname = "bgood/xsaitekpanels/multipanel/" name "/status"; \
        vector<int> *data = &(basename ## OwnedData); \
        XPLMRegisterDataAccessor(drname, xplmType_IntArray, 1, NULL, NULL, \
            NULL, NULL, NULL, NULL, read_int_array, write_int_array, NULL, \
            NULL, NULL, NULL, data, data); \
        (basename ## OwnedDataRef) = new Dataref(drname); \
        data->resize(multipanels.size()); \
    } while (0)
    DR_REGISTER_ACCESSOR(MultiAltBtn, "altbtn");
    DR_REGISTER_ACCESSOR(MultiAltSwitch, "altswitch");
    DR_REGISTER_ACCESSOR(MultiApBtn, "apbtn");
    DR_REGISTER_ACCESSOR(MultiAprBtn, "aprbtn");
    DR_REGISTER_ACCESSOR(MultiAt, "at");
    DR_REGISTER_ACCESSOR(MultiCrsSwitch, "crsswitch");
    DR_REGISTER_ACCESSOR(MultiFlapsDn, "flapsdn");
    DR_REGISTER_ACCESSOR(MultiFlapsUp, "flapsup");
    DR_REGISTER_ACCESSOR(MultiHdgBtn, "hdgbtn");
    DR_REGISTER_ACCESSOR(MultiHdgSwitch, "hdgswitch");
    DR_REGISTER_ACCESSOR(MultiIasBtn, "iasbtn");
    DR_REGISTER_ACCESSOR(MultiIasSwitch, "iasswitch");
    DR_REGISTER_ACCESSOR(MultiKnobDec, "knobdec");
    DR_REGISTER_ACCESSOR(MultiKnobDecTicks, "knobdecticks");
    DR_REGISTER_ACCESSOR(MultiKnobInc, "knobinc");
    DR_REGISTER_ACCESSOR(MultiKnobIncTicks, "knobincticks");
    DR_REGISTER_ACCESSOR(MultiNavBtn, "navbtn");
    DR_REGISTER_ACCESSOR(MultiRevBtn, "revbtn");
    DR_REGISTER_ACCESSOR(MultiTrimDn, "trimdn");
    DR_REGISTER_ACCESSOR(MultiTrimUp, "trimup");
    DR_REGISTER_ACCESSOR(MultiVsBtn, "vsbtn");
    DR_REGISTER_ACCESSOR(MultiVsSwitch, "vsswitch");
#undef DR_REGISTER_ACCESSOR
}

void xsaitekpanels::unregister_multipanel_drs()
{
#define DR_DESTROY_ACCESSOR(dr) \
    do { \
        if ((dr) != NULL) { \
            XPLMUnregisterDataAccessor((dr)->getDataref()); \
            delete (dr); \
            (dr) = NULL; \
        } \
    } while (0)
    DR_DESTROY_ACCESSOR(MultiAltSwitchOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiVsSwitchOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiIasSwitchOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiHdgSwitchOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiCrsSwitchOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiKnobIncOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiKnobDecOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiKnobIncTicksOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiKnobDecTicksOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiAtOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiTrimUpOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiTrimDnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiFlapsUpOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiFlapsDnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiApBtnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiHdgBtnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiNavBtnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiIasBtnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiAltBtnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiVsBtnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiAprBtnOwnedDataRef);
    DR_DESTROY_ACCESSOR(MultiRevBtnOwnedDataRef);
#undef DR_DESTROY_ACCESSOR
}

static uint32_t read_status(hid_device *handle, int timeout, unsigned panel_num)
{
    uint8_t recvbuf[4];
    uint32_t status_word = 0;

    int sz = hid_read_timeout(handle, recvbuf, sizeof(recvbuf), timeout);

    if (sz < 0) {
        logMsg("Error reading USB message from multipanel %u: %s",
            panel_num, (const char *)hid_error(handle));
        return (-1u);
    }
    if (sz == 0)
        return (-1u);

    VERIFY((unsigned long)sz <= sizeof (status_word));

    /* right-align as big endian & bswap to native endianness */
    memcpy(((uint8_t *)&status_word) + (sizeof (status_word) - sz),
        recvbuf, sz);
    status_word = ntohl(status_word);

    return (status_word);
}

void Multipanel::reader_main()
{
#define POLLING_INTVAL 50       /* ms */

    while (!reader_shutdown) {
        uint32_t new_status = read_status(handle, POLLING_INTVAL, panel_num);
        uint8_t sendbuf_copy[sizeof (sendbuf)];
        bool send_cmd_copy = false;

        mutex_enter(&mtx);

        if (new_status != -1u) {
            for (int i = 0; i < STATUS_BITS; i++)
                buttons[i] += (new_status >> i) & 1;
            buttons_updated = true;
        }

        if (send_cmd) {
            send_cmd_copy = true;
            memcpy(sendbuf_copy, sendbuf, sizeof (sendbuf));
            memset(sendbuf, 0, sizeof (sendbuf));
            send_cmd = false;
        }

        mutex_exit(&mtx);

        if (send_cmd_copy)
            hid_send_feature_report(handle, sendbuf_copy, sizeof(sendbuf_copy));
    }

    /*
     * Blank out the display on shutdown. No need for locking, parent thread
     * is just waiting on us at this time.
     */
    enable_readout(READOUT_NONE);
    process_multi_display();
    sched_update_command();
    hid_send_feature_report(handle, sendbuf, sizeof(sendbuf));
}
