#ifndef _XSAITEKPANELS_LOG_H_
#define _XSAITEKPANELS_LOG_H_

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

namespace xsaitekpanels {

    /*
     * This lets us chop out the basename (last path component) of the
     * __FILE__ being compiled at compile time. This works on GCC and Clang.
     * The fallback mechanism below just chops it out at compile time.
     */
#if     defined(__GNUC__) || defined(__clang__)
#define logMsg(...) logMsg_impl(__builtin_strrchr(__FILE__, DIRSEP) ? \
    __builtin_strrchr(__FILE__, DIRSEP) + 1 : __FILE__, __LINE__, __VA_ARGS__)
#else   /* !__GNUC__ && !__clang__ */
    const char *log_basename(const char *filename);
#define logMsg(...) logMsg_impl(log_basename(__FILE__), \
    __LINE__, __VA_ARGS__)
#endif  /* !__GNUC__ && !__clang__ */

    void logMsg_impl(const char *filename, int line, const char *fmt, ...)
        PRINTF_ATTR(3);
    void logMsg_v_impl(const char *filename, int line, const char *fmt,
        va_list ap);
}

#endif /* _XSAITEKPANELS_LOG_H_ */
