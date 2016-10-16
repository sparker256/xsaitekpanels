#ifndef _XSP_DATAREF_H_
#define _XSP_DATAREF_H_

#include <string>
#include <stdlib.h>
#include "XPLMDataAccess.h"

namespace xsaitekpanels {
    class Dataref {
        bool is_null;
        std::string drname;
        std::string drname_only;
        int dr_index;

        XPLMDataRef dr;
        XPLMDataTypeID type;
        size_t offset;
        bool writable;

        bool lazy_init();

    public:
        Dataref(std::string drname);
        Dataref(XPLMDataRef xplm_dr);

        const std::string get_drname() const;

        template <typename T>void get(T *value);
        template <typename T>void set(T value);
        template <typename T>size_t getv(T *values, size_t off, size_t num);
        template <typename T>void setv(const T *values, size_t off, size_t num);

        /* helpers for get() overloading */
        int geti();
        float getf();
        double getd();

        XPLMDataRef getDataref();
    };

    int read_int(void *user_info);
    void write_int(void *user_info, int value);

    int read_int_array(void *user_info, int *values, int offset, int count);
    void write_int_array(void *user_info, int *values, int offset, int count);
}

#endif  /* _XSP_DATAREF_H_ */
