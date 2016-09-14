#if IBM
#include <windows.h>
#else
#include <sys/time.h>
#endif  // !IBM

#include "time.h"

uint64_t xsaitekpanels::microclock()
{
#if IBM
    LARGE_INTEGER val, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&val);
    return ((val.QuadPart * 1000000llu) / freq.QuadPart);
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000000llu) + tv.tv_usec);
#endif
}
