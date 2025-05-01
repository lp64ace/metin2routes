#include "LIB_path_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

HOOK_INLINE bool LIB_path_slash_is_native_compat(const char ch) {
#ifdef WIN32
	if (ch == ALTSEP) {
		return true;
	}
#endif
	return (ch == SEP) ? true : false;
}

#ifdef __cplusplus
}
#endif
