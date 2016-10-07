#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#if     !IBM
#include <execinfo.h>   /* used for stack tracing */
#endif  /* !IBM */

#include "XPLMUtilities.h"
#include "Log.h"

using namespace xsaitekpanels;

#define PREFIX          "Xsaitekpanels"
#if     IBM
#define PREFIX_FMT      "%s[%s:%d]: ", PREFIX, strrchr(filename, '\\') ? \
    strrchr(filename, '\\') + 1 : filename, line
#else   /* !IBM */
#define PREFIX_FMT      "%s[%s:%d]: ", PREFIX, filename, line
#endif  /* !IBM */

/*
 * The fallback mechanism for chopping out the basename of a path at runtime,
 * if the compile-time mechanism isn't supported.
 */
#if     !defined(__GNUC__) && !defined(__clang__)
const char *
xsaitekpanels::log_basename(const char *filename)
{
    const char *sep = strrchr(filename, DIRSEP);
    return (sep != NULL ? sep + 1 : filename);
}
#endif  /* !defined(__GNUC__) && !defined(__clang__) */

void xsaitekpanels::logMsg_impl(const char *filename, int line,
    const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    logMsg_v_impl(filename, line, fmt, ap);
    va_end(ap);
}

void xsaitekpanels::logMsg_v_impl(const char *filename, int line,
    const char *fmt, va_list ap)
{
    va_list ap_copy;
    char *buf;
    size_t prefix_len, len;

    prefix_len = snprintf(NULL, 0, PREFIX_FMT);
    va_copy(ap_copy, ap);
    len = vsnprintf(NULL, 0, fmt, ap_copy);

    buf = (char *)malloc(prefix_len + len + 1);

    (void) snprintf(buf, prefix_len + 1, PREFIX_FMT);
    (void) vsnprintf(&buf[prefix_len], len + 1, fmt, ap);

    XPLMDebugString(buf);

    free(buf);
}

#define MAX_TRACE        128
#define BACKTRACE_STR    "Backtrace is:\n"
#if     defined(__GNUC__) || defined(__clang__)
#define BACKTRACE_STRLEN __builtin_strlen(BACKTRACE_STR)
#else   /* !__GNUC__ && !__clang__ */
#define BACKTRACE_STRLEN strlen(BACKTRACE_STR)
#endif  /* !__GNUC__ && !__clang__ */

void xsaitekpanels::logBacktrace()
{
#if     IBM
#else   /* !IBM */
    char *msg;
    size_t msg_len;
    void *trace[MAX_TRACE];
    size_t i, j, sz;
    char **fnames;

    sz = backtrace(trace, MAX_TRACE);
    fnames = backtrace_symbols(trace, sz);

    for (i = 1, msg_len = BACKTRACE_STRLEN; i < sz; i++)
        msg_len += snprintf(NULL, 0, "%s\n", fnames[i]);

    msg = (char *)malloc(msg_len + 1);
    strcpy(msg, BACKTRACE_STR);
    for (i = 1, j = BACKTRACE_STRLEN; i < sz; i++)
        j += sprintf(&msg[j], "%s\n", fnames[i]);

    XPLMDebugString(msg);

    free(msg);
    free(fnames);
#endif  /* !IBM */
}
