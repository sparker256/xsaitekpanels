#ifndef _MULTIPANEL_H_
#define _MULTIPANEL_H_

#include <stdlib.h>

#if     IBM
#include <windows.h>
#else   /* !IBM */
#include <pthread.h>
#endif  /* !IBM */

#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "hidapi.h"

namespace xsaitekpanels {

    /*
     * See Multipanel::process_button_common for info on how these button
     * types behave.
     */
    enum button_type_t {
        MomentaryPushButton,
        OneShotButton,
        ToggleButton,
        MomentaryPushUpHoldDownButton
    };

    enum button_light_type_t {
        NoLight = 0,
        OnOffFlashLight,
        OnOffFlashLight_dup,
        OnOffFlash3StateLight
    };

    enum {
        AP_BTN_INFO = 0,
        HDG_BTN_INFO,
        NAV_BTN_INFO,
        LNAV_BTN_INFO,
        IAS_BTN_INFO,
        IAS_CHANGEOVER_BTN_INFO,
        ALT_BTN_INFO,
        VS_BTN_INFO,
        APR_BTN_INFO,
        REV_BTN_INFO,
        FLAPS_UP_BTN_INFO,
        FLAPS_DN_BTN_INFO,
        NUM_BTN_INFOS
    };

    enum {
        ALT_SW_INFO = 0,
        VS_SW_INFO,
        IAS_SW_INFO,
        IAS_MACH_SW_INFO,
        HDG_SW_INFO,
        CRS_SW_INFO,
        CRS2_SW_INFO,
        NUM_SW_INFOS
    };

    enum {
        STATUS_BITS = 24
    };

    struct button_info_t {
        bool press_state;
        uint64_t press_time, release_time;
        uint64_t n_fired;
        button_type_t type;
        XPLMCommandRef cmd, rev_cmd;
        Dataref *dr;
        double on_value, off_value;
        double max_value, min_value;
    };

    struct button_light_info_t {
        button_light_type_t type;
        Dataref *dr, *flash_dr;
    };

    struct switch_info_t {
        Dataref *dr;
        XPLMCommandRef up_cmd, dn_cmd;
        float maxval, minval, step;
        float max_accel, accel;
        bool loop;
    };

    void *multipanel_reader_thread(void *arg);

    class Multipanel {
        unsigned        panel_num;
        hid_device      *handle;
        int             display_readout;
        uint8_t         adigits[5], bdigits[5];
        int             btnleds;

        double altitude, vs, airspeed, hdg, crs;

        uint64_t last_auto_update_time;
        bool knob_last_up, knob_last_dn;
        int accel_mult, knob_up_dampen, knob_dn_dampen;
        uint64_t knob_up_time, knob_dn_time;

        int knob_speed;

        bool athr_sw_enabled;
        double athr_sw_enabled_val, athr_sw_disabled_val;
        Dataref *athr_sw_dr;

        button_info_t button_info[NUM_BTN_INFOS];
        switch_info_t switches[NUM_SW_INFOS];
        button_light_info_t button_lights[NUM_BTN_INFOS];
        Dataref *ias_is_mach_dr;

        XPLMCommandRef trim_up_cmd;
        int trim_wheel_up_dampen;
        uint64_t trim_up_last;
        float trim_up_accel, trim_up_max_accel;

        XPLMCommandRef trim_down_cmd;
        int trim_wheel_down_dampen;
        uint64_t trim_down_last;
        float trim_down_accel, trim_down_max_accel;

        bool flashon;

        bool process_light(const button_light_info_t *info, int bitn,
            bool flash_on);
        bool process_lights();

        void process_switch_adjustment(int value, uint64_t *lastadj_time,
            Dataref *dr, XPLMCommandRef cmd, double maxval, double minval,
            double step, bool loop, float accel, int max_accel_mult);
        void process_switch(const switch_info_t *sw);

        void update_alt_vs_readout();
        void enable_readout(int readout);

        void nav_light_set_hsi();
        void multibuf_button();

        void process_alt_switch();
        void process_vs_switch();
        void process_ias_switch();
        void process_hdg_switch();
        void process_crs_switch();
        void process_autothrottle_switch();

        void process_button_common(int button_id, button_info_t *info);

        void process_trim_wheel();

        void process_multi_display();
        void process_multi_flash();

        void process_drs();
        void sched_update_command();

        /* this is a private copy of `buttons' used only by the main thread */
        int buttons_main[STATUS_BITS];

#if IBM
        HANDLE mtx;
        HANDLE reader;
#else
        pthread_mutex_t mtx;
        pthread_t reader;
#endif
        /*
         * These are protected by the mutex above, as they're shared between
         * the main thread and the reader thread.
         */
        uint8_t sendbuf[13];
        int buttons[STATUS_BITS];
        bool buttons_updated;
        bool send_cmd, reader_shutdown;

    public:
        Multipanel(unsigned panel_number, const char *hidpath);
        ~Multipanel();
        void reconfigure();
        void process();
        void shutdown();

        void reader_main();
    };

    int get_num_multipanels();

    void open_all_multipanels();
    void close_all_multipanels();
    void reconfigure_all_multipanels();
    void process_all_multipanels();

    void register_multipanel_drs();
    void unregister_multipanel_drs();
}

#endif /* _MULTIPANEL_H_ */
