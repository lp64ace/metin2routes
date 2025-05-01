#ifndef LIB_STRING_UTF_H
#define LIB_STRING_UTF_H

#include "LIB_utildefines.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HOOK_UTF8_MAX 6
#define HOOK_UTF8_WIDTH_MAX 2 /* columns */
#define HOOK_UTF8_ERR ((unsigned int)-1)

/* -------------------------------------------------------------------- */
/** \name Unicode
 * \{ */

/** Encode a unicode code point using UTF-8. */
size_t LIB_unicode_encode_as_utf8(char *out, size_t maxncpy, uint32_t unicode);
/** Encode a unicode string using UTF-8. */
size_t LIB_strncpy_wchar_as_utf8(char *out, size_t maxncpy, const wchar_t *unicode);

/** \} */

#ifdef __cplusplus
}
#endif

#endif	// LIB_STRING_UTF_H