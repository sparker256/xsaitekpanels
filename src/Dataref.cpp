#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <vector>

#include "Log.h"
#include "Dataref.h"

using namespace std;
using namespace xsaitekpanels;

Dataref::Dataref(string drname_in)
{
    drname = drname_in;
    dr = NULL;
    drname_only = drname;
    dr_index = 0;
    is_null = (drname_in == "null");

    if (!is_null) {
        size_t open_bracket = drname.find('[');
        size_t close_bracket = drname.find(']');

        if (open_bracket != string::npos && close_bracket != string::npos &&
            open_bracket < close_bracket) {
            string idx = drname.substr(open_bracket + 1,
                close_bracket - open_bracket - 1);

            drname_only = drname.substr(0, open_bracket - 1);

            if (sscanf(idx.c_str(), "%u", (unsigned *)&dr_index) != 1) {
                logMsg("Error parsing bracket array offset in dataref "
                    "specifier \"%s\"", drname_in.c_str());
            }
        }
    }
}

bool Dataref::lazy_init()
{
    ASSERT(!is_null);
    if (dr != NULL)
        return (true);

    dr = XPLMFindDataRef(drname_only.c_str());
    if (dr == NULL)
        return (false);

    type = XPLMGetDataRefTypes(dr);
    writable = XPLMCanWriteDataRef(dr);

    return (true);
}

template <typename T>void Dataref::get(T *value)
{
    *value = (T)0;
    if (is_null)
        return;
    if (!lazy_init()) {
        logMsg("attempting to scalar-read nonexistent dataref \"%s\"",
            drname.c_str());
        return;
    }

    if (type == xplmType_Int) {
        *value = XPLMGetDatai(dr);
    } else if (type & xplmType_Double) {
        *value = XPLMGetDatad(dr);
    } else if (type & xplmType_Float) {
        *value = XPLMGetDataf(dr);
    } else if (type == xplmType_IntArray) {
        int ivalue = 0;
        XPLMGetDatavi(dr, &ivalue, offset, 1);
        *value = ivalue;
    } else if (type == xplmType_FloatArray) {
        float fvalue = 0;
        XPLMGetDatavf(dr, &fvalue, offset, 1);
        *value = fvalue;
    } else {
        logMsg("attempting to scalar-read unknown type (%d) dataref \"%s\"",
            type, drname.c_str());
    }
}

const string Dataref::get_drname() const
{
    return (drname);
}

int Dataref::geti()
{
    int x;
    this->get(&x);
    return (x);
}

float Dataref::getf()
{
    float x;
    this->get(&x);
    return (x);
}

double Dataref::getd()
{
    double x;
    this->get(&x);
    return (x);
}

template <typename T>void Dataref::set(T value)
{
    if (is_null)
        return;
    if (!lazy_init()) {
        logMsg("attempting to scalar-write nonexistent dataref \"%s\"",
            drname.c_str());
        return;
    }
    if (!writable) {
        logMsg("attempting to scalar-write read-only dataref \"%s\"",
            drname.c_str());
        return;
    }

    if (type == xplmType_Int) {
        XPLMSetDatai(dr, value);
    } else if (type & xplmType_Double) {
        XPLMSetDatad(dr, value);
    } else if (type & xplmType_Float) {
        XPLMSetDataf(dr, value);
    } else if (type == xplmType_IntArray) {
        int ivalue = value;
        XPLMSetDatavi(dr, &ivalue, offset, 1);
    } else if (type == xplmType_FloatArray) {
        float fvalue = value;
        XPLMSetDatavf(dr, &fvalue, offset, 1);
    } else {
        logMsg("attempting to scalar-write unknown type (%d) dataref \"%s\"",
            type, drname.c_str());
    }
}

template void Dataref::set(bool);
template void Dataref::set(int);
template void Dataref::set(float);
template void Dataref::set(double);

template <typename T>size_t Dataref::getv(T *values, size_t off, size_t num)
{
    assert(num > 0);

    if (is_null) {
        for (size_t i = 0; i < num; i++)
            values[i] = (T)0;
        return (num);
    }

    if (!lazy_init()) {
        logMsg("attempting to vector-read nonexistent dataref \"%s\"",
            drname.c_str());
        return (0);
    }

    if (type == xplmType_Int) {
        values[0] = XPLMGetDatai(dr);
        return (1);
    } else if (type & xplmType_Double) {
        values[0] = XPLMGetDatad(dr);
        return (1);
    } else if (type & xplmType_Float) {
        values[0] = XPLMGetDataf(dr);
        return (1);
    } else if (type == xplmType_IntArray) {
        int ivalues[num];
        int n = XPLMGetDatavi(dr, ivalues, off == -1lu ? offset : off, num);
        for (int i = 0; i < n; i++)
            values[i] = ivalues[i];
        return (n);
    } else if (type == xplmType_FloatArray) {
        float fvalues[num];
        int n = XPLMGetDatavf(dr, fvalues, off == -1lu ? offset : off, num);
        for (int i = 0; i < n; i++)
            values[i] = fvalues[i];
        return (n);
    }
    return (0);
}

template size_t Dataref::getv(int *, size_t, size_t);
template size_t Dataref::getv(float *, size_t, size_t);

template <typename T>void Dataref::setv(const T *values, size_t off, size_t num)
{
    assert(num > 0);

    if (is_null)
        return;

    if (!lazy_init()) {
        logMsg("attempting to vector-write to nonexistent dataref \"%s\"",
            drname.c_str());
        return;
    }

    if (!writable) {
        logMsg("Attempting to vector-write to read-only dataref \"%s\"",
            drname.c_str());
        return;
    }

    if (type == xplmType_Int) {
        XPLMSetDatai(dr, values[0]);
    } else if (type & xplmType_Double) {
        XPLMSetDatad(dr, values[0]);
    } else if (type & xplmType_Float) {
        XPLMSetDataf(dr, values[0]);
    } else if (type == xplmType_IntArray) {
        int ivalues[num];
        for (size_t i = 0; i < num; i++)
            ivalues[i] = values[i];
        XPLMSetDatavi(dr, ivalues, off == -1lu ? offset : off, num);
    } else if (type == xplmType_FloatArray) {
        float fvalues[num];
        for (size_t i = 0; i < num; i++)
            fvalues[i] = values[i];
        XPLMSetDatavf(dr, fvalues, off == -1lu ? offset : off, num);
    } else {
        logMsg("attempting to vector-write unknown type (%d) dataref \"%s\"",
            type, drname.c_str());
    }
}

template void Dataref::setv(const int *, size_t, size_t);
template void Dataref::setv(const float *, size_t, size_t);

XPLMDataRef Dataref::getDataref()
{
    (void) lazy_init();
    return (dr);
}

int xsaitekpanels::read_int(void *user_info)
{
    if (user_info == NULL)
        return (0);
    int *src = (int*)user_info;
    return (*src);
}

void xsaitekpanels::write_int(void *user_info, int value)
{
    if (user_info == NULL)
        return;
    int *dst = (int*)user_info;
    *dst = value;
}

int xsaitekpanels::read_int_array(void *user_info, int *values, int offset,
    int count)
{
    if (user_info == NULL)
        return (0);
    std::vector<int> *src = (std::vector<int> *)user_info;
    if (values == NULL)
        return (src->size());
    for (int i = 0, n = src->size(); i + offset < n && i < count; i++)
        values[i] = (*src)[i + offset];
    return (count);
}

void xsaitekpanels::write_int_array(void *user_info, int *values, int offset,
    int count)
{
    if (user_info == NULL || values == NULL)
        return;
    std::vector<int> *dst = (std::vector<int> *)user_info;
    for (int i = 0, n = dst->size(); i + offset < n && i < count; i++) {
        (*dst)[i + offset] = values[i];
    }
}
