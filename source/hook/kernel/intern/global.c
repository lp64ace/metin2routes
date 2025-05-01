#include "MEM_guardedalloc.h"

#include "LIB_fileops.h"
#include "LIB_listbase.h"
#include "LIB_utildefines.h"

#include "KER_global.h"

#include <cjson.h>

#define BINARY(datatoc, filename, filepath) \
	extern const size_t datatoc ## _size; \
	extern const char datatoc[];
#include "launch.h"
#undef BINARY

Global G;

void KER_globals_init() {
	KER_globals_launch_opt_init();
}

void KER_globals_exit() {
}
