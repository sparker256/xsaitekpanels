#ifndef _XSP_DATAREF_H_
#define _XSP_DATAREF_H_

#include <stdlib.h>
#include "XPLMDataAccess.h"

namespace xsaitekpanels {
    class Dataref {
        char *drname;
        XPLMDataRef dr;
        XPLMDataTypeID type;
        size_t offset;
        bool writable;

    public:
        Dataref(const char *drname);
        Dataref(XPLMDataRef xplm_dr);
        ~Dataref();

        const char *get_drname();

        template <typename T>void get(T *value) const;
        template <typename T>void set(T value);
        template <typename T>size_t getv(T *values, size_t off, size_t num)
            const;
        template <typename T>void setv(const T *values, size_t off, size_t num);

        /* helpers for get() overloading */
        int geti() const;
        float getf() const;
        double getd() const;

        XPLMDataRef getDataref();
    };

    int read_int(void *user_info);
    void write_int(void *user_info, int value);

    int read_int_array(void *user_info, int *values, int offset, int count);
    void write_int_array(void *user_info, int *values, int offset, int count);
}

#endif  /* _XSP_DATAREF_H_ */
