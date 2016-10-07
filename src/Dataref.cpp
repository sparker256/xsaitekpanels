#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <vector>

#include "Log.h"
#include "Dataref.h"

using namespace xsaitekpanels;

Dataref::Dataref(const char *drname_in)
{
    const char *bracket;

    drname = (char *)malloc(strlen(drname_in) + 1);
    strcpy(drname, drname_in);

    bracket = strstr(drname, "[");
    if (bracket != NULL) {
        char drname_only[strlen(drname) + 1];
        strcpy(drname_only, drname);
        drname_only[bracket - drname] = '\0';
        dr = XPLMFindDataRef(drname_only);
        if (sscanf(&drname[1], "%lu", &offset) != -1)
            dr = NULL;
    } else {
        dr = XPLMFindDataRef(drname);
        offset = 0;
    }
    if (dr != NULL) {
        type = XPLMGetDataRefTypes(dr);
        writable = XPLMCanWriteDataRef(dr);
    }
}

Dataref::~Dataref()
{
    free(drname);
}

template <typename T>void Dataref::get(T *value) const
{
    if (dr == NULL) {
        logMsg("attempting to scalar-read nonexistent dataref %s\n", drname);
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
        logMsg("attempting to scalar-read unknown type (%d) dataref %s\n",
            type, drname);
    }
}

int Dataref::geti() const
{
    int x;
    this->get(&x);
    return (x);
}

float Dataref::getf() const
{
    float x;
    this->get(&x);
    return (x);
}

double Dataref::getd() const
{
    double x;
    this->get(&x);
    return (x);
}

template <typename T>void Dataref::set(T value)
{
    if (dr == NULL) {
        logMsg("attempting to scalar-write nonexistent dataref %s\n", drname);
        return;
    }
    if (!writable) {
        logMsg("attempting to scalar-write read-only dataref %s\n", drname);
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
        logMsg("attempting to scalar-write unknown type (%d) dataref %s\n",
            type, drname);
    }
}

template void Dataref::set<bool>(bool);
template void Dataref::set<int>(int);
template void Dataref::set<float>(float);
template void Dataref::set<double>(double);

template <typename T>size_t Dataref::getv(T *values, size_t off,
    size_t num) const
{
    assert(num > 0);

    if (dr == NULL) {
        logMsg("attempting to scalar-read nonexistent dataref %s\n", drname);
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

template size_t Dataref::getv(int *values, size_t off, size_t num) const;
template size_t Dataref::getv(float *values, size_t off, size_t num) const;

template <typename T>void Dataref::setv(const T *values, size_t off, size_t num)
{
    assert(num > 0);

    if (dr == NULL) {
        logMsg("attempting to vector-write to nonexistent dataref %s\n",
            drname);
        return;
    }
    if (!writable) {
        logMsg("Attempting to vector-write to read-only dataref %s\n", drname);
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
        logMsg("attempting to vector-write unknown type (%d) dataref %s\n",
            type, drname);
    }
}

template void Dataref::setv(const int *values, size_t off, size_t num);
template void Dataref::setv(const float *values, size_t off, size_t num);

XPLMDataRef Dataref::getDataref()
{
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
    if (user_info == NULL || values == NULL)
        return (0);
    std::vector<int> *src = (std::vector<int> *)user_info;
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
    logMsg("write: %p, v[0]: %i, off: %i, cnt: %i size: %lu\n",
        user_info, values[0], offset, count, dst->size());
    for (int i = 0, n = dst->size(); i + offset < n && i < count; i++) {
        (*dst)[i + offset] = values[i];
    }
}
