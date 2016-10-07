#ifndef _XSAITEKPANELS_LOG_H_
#define _XSAITEKPANELS_LOG_H_

#include <stdio.h>
#include <stdarg.h>

#if     defined(__GNUC__) || defined(__clang__)
#define PRINTF_ATTR(x)  __attribute__ ((format (printf, x, x + 1)))
#else
#define PRINTF_ATTR(x)
#endif  /* __GNUC__ || __clang__ */

#if     IBM
#define DIRSEP '\\'
#else   /* !IBM */
#define DIRSEP '/'
#endif  /* !IBM */

/*
 * This lets us chop out the basename (last path component) from __FILE__
 * at compile time. This works on GCC and Clang. The fallback mechanism
 * below just chops it out at compile time.
 */
#if     defined(__GNUC__) || defined(__clang__)
#define log_basename(f) (__builtin_strrchr(f, DIRSEP) ? \
    __builtin_strrchr(f, DIRSEP) + 1 : f)
#else   /* !__GNUC__ && !__clang__ */
const char *xsaitekpanels::log_basename(const char *filename);
#endif  /* !__GNUC__ && !__clang__ */

/*
 * This is an assert-like macro, except that we always perform the assertion
 * check, regardless of the setting of the NDEBUG macro. We also drop a msg
 * into the X-Plane log file to help debugging.
 */
#define VERIFY(x) \
    do { \
        if (!(x)) { \
            xsaitekpanels::logMsg("assertion \"" #x "\" failed\n"); \
            fprintf(stderr, "%s:%d: assertion \"" #x "\" failed\n", __FILE__, \
                __LINE__); \
            xsaitekpanels::logBacktrace(); \
            abort(); \
        } \
    } while (0)

namespace xsaitekpanels {

#define logMsg(...) logMsg_impl(log_basename(__FILE__), __LINE__, __VA_ARGS__)
    void logMsg_impl(const char *filename, int line, const char *fmt, ...)
        PRINTF_ATTR(3);
    void logMsg_v_impl(const char *filename, int line, const char *fmt,
        va_list ap);
    void logBacktrace();
}

#endif /* _XSAITEKPANELS_LOG_H_ */
