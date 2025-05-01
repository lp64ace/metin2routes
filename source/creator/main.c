#ifndef NDEBUG
#	include "MEM_guardedalloc.h"
#endif

#include "KER_global.h"

#include <stdio.h>

int main(void) {
#ifndef NDEBUG
	MEM_init_memleak_detection();
	MEM_enable_fail_on_memleak();
	MEM_use_guarded_allocator();
#endif

	KER_globals_init();
	do {
		fprintf(stdout, "M2FOLDER %s\n", G.m2_folder);
		fprintf(stdout, "M2CLIENT %s\n", G.m2_client);
	} while (false);
	KER_globals_exit();

	return 0;
}
