#ifndef LIB_PATTERN_H
#define LIB_PATTERN_H

#include "LIB_utildefines.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Iterates an array of bytes until the pattern is found. */
uintptr_t LIB_pattern_offset_ex(const void *base, size_t size, const unsigned char *bytes, const unsigned char *mask, size_t length, uintptr_t pre, uintptr_t post);
uintptr_t LIB_pattern_offset(const void *base, size_t size, const char *text, uintptr_t pre, uintptr_t post);

void *LIB_pattern_find(void *module, const char *text, uintptr_t pre, uintptr_t post);

#ifdef __cplusplus
}
#endif

#endif // LIB_PATTERN_H
