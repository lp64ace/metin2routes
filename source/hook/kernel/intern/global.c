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
	KER_globals_main_replace(KER_main_init());
}

void KER_globals_exit() {
	KER_globals_main_replace(NULL);
}

void KER_globals_main_replace(Main *main) {
	HOOK_assert((G.main == NULL || G.main->is_global) && (main == NULL || !main->is_global));
	if (G.main) {
		KER_main_free(G.main);
	}
	G.main = main;
	if (main) {
		main->is_global = true;
	}
}
