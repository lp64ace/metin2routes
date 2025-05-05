#include "MEM_guardedalloc.h"

#include "LIB_assert.h"
#include "LIB_memory.h"
#include "LIB_string.h"

#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

HOOK_INLINE unsigned char hex2half(const char hex[1]) {
	if ('0' <= hex[0] && hex[0] <= '9') return hex[0] - '0';
	if ('A' <= hex[0] && hex[0] <= 'F') return hex[0] - 'A' + 10;
    if ('a' <= hex[0] && hex[0] <= 'f') return hex[0] - 'a' + 10;
	return 255;
}

HOOK_INLINE unsigned char hex2byte(const char hex[2]) {
	return (hex2half(hex + 0) << 4) + hex2half(hex + 1);
}

uintptr_t LIB_pattern_offset_ex(const void *base, size_t size, const unsigned char *bytes, const unsigned char *mask, size_t length, uintptr_t pre, uintptr_t post) {
	for (const void *itr = POINTER_OFFSET(base, post); itr != POINTER_OFFSET(base, size - (length + pre - post)); itr = POINTER_OFFSET(itr, 1)) {
		size_t index = 0;
		while (index < length) {
			unsigned char byte = (mask) ? mask[index] : 0xff;
			if (((*(const unsigned char *)POINTER_OFFSET(itr, index + pre - post)) & byte) != (bytes[index] & byte)) {
				break;
			}
			if (++index == length) {
				const size_t remaining = (const char *)POINTER_OFFSET(base, size) - (const char *)itr;
				HOOK_assert(LIB_pattern_offset_ex(POINTER_OFFSET(itr, 1), remaining, bytes, mask, length, pre, post) == NULL);
				return (uintptr_t)itr;
			}
		}
	}
	return (uintptr_t)NULL;
}

uintptr_t LIB_pattern_offset(const void *base, size_t size, const char *text, uintptr_t pre, uintptr_t post) {
	unsigned char *bytes = MEM_mallocN(LIB_strlen(text), "pattern::bytes");
	unsigned char *masks = MEM_mallocN(LIB_strlen(text), "pattern::masks");
	size_t length = 0;

	for (const char *itr = text; !ELEM(itr[0], '\0'); itr++) {
		if (ELEM(itr[0], ' ', '\t', '\n', '\r')) {
			continue;
		}
		HOOK_assert(((hex2half(&itr[0]) != 0xff && hex2half(&itr[1]) != 0xff)) || (ELEM(itr[0], '?') && ELEM(itr[1], '?')));
		if (ELEM(itr[0], '?') && ELEM(itr[1], '?')) {
			bytes[length] = hex2byte(itr);
			masks[length++] = 0x00;
			itr++;
		}
		if (hex2half(&itr[0]) != 0xff && hex2half(&itr[1]) != 0xff) {
			bytes[length] = hex2byte(itr);
			masks[length++] = 0xff;
			itr++;
		}
	}

	uintptr_t offset = LIB_pattern_offset_ex(base, size, bytes, masks, length, pre, post);

	MEM_freeN(bytes);
	MEM_freeN(masks);

	return offset;
}

void *LIB_pattern_find(void *module, const char *text, uintptr_t pre, uintptr_t post) {
	MODULEINFO info;
	if (GetModuleInformation(GetCurrentProcess(), (HMODULE)module, &info, sizeof(MODULEINFO))) {
		return (void *)LIB_pattern_offset((HMODULE)module, info.SizeOfImage, text, pre, post);
	}
	return NULL;
}
