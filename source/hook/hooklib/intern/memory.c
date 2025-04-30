#include "LIB_memory.h"

HOOK_INLINE unsigned char hex2half(const char hex[1]) {
	if ('0' <= hex[0] && hex[0] <= '9') return hex[0] - '0';
	if ('A' <= hex[0] && hex[0] <= 'F') return hex[0] - 'A' + 10;
    if ('a' <= hex[0] && hex[0] <= 'f') return hex[0] - 'a' + 10;
	return 0;
}

HOOK_INLINE unsigned char hex2byte(const char hex[2]) {
	return (hex2half(hex + 0) << 4) + hex2half(hex + 1);
}

uintptr_t LIB_pattern_offset(const void *base, size_t size, const unsigned char *bytes, const unsigned char *mask, size_t length, uintptr_t pre) {
	for (const void *itr = base; itr != POINTER_OFFSET(base, size - (length + pre)); itr = POINTER_OFFSET(itr, 1)) {
		size_t index = 0;
		while (index < length) {
			unsigned char m = (mask) ? mask[index] : 0xff;
			if (((*(const unsigned char *)POINTER_OFFSET(itr, index + pre)) & m) != (bytes[index] & m)) {
				break;
			}
			if (++index == length) {
				return ((const unsigned char *)itr - (const unsigned char *)base);
			}
		}
	}
	return (uintptr_t)-1;
}
