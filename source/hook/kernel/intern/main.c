#include "MEM_guardedalloc.h"

#include "KER_main.h"

Main *KER_main_init() {
	Main *main = MEM_callocN(sizeof(Main), "Main");
	main->is_global = false;
	return main;
}

void KER_main_free(Main *main) {
	MEM_freeN(main);
}
