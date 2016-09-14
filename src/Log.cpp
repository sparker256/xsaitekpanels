#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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
