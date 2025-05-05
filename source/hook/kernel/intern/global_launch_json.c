#include "MEM_guardedalloc.h"

#include "LIB_fileops.h"
#include "LIB_listbase.h"
#include "LIB_string.h"
#include "LIB_utildefines.h"

#include "KER_global.h"

#include <cjson.h>
#include <stdio.h>

HOOK_STATIC void hook_globals_launch_json_location(const char *json_data, const char *p, size_t *r_row, size_t *r_col) {
	*r_row = 1;
	*r_col = 1;

	for (const char *itr = json_data; itr && itr != p; itr++) {
		if (ELEM(*itr, '\n', '\r')) {
			*r_col = 1;
			*r_row = *r_row + 1;
		}
	}
}

HOOK_STATIC void hook_globals_launch_json_error(const char *name, const char *json_data, const char *itr) {
	const char *begin = (itr) ? itr : "unkown source location";
	while (json_data < begin && begin[-1] != '\n') {
		begin--;
	}

	const char *end = (itr) ? itr : "unkown source location";
	while (!ELEM(end[0], '\0', '\n')) {
		end++;
	}

	size_t row, col;

	hook_globals_launch_json_location(json_data, itr, &row, &col);

	int indent = fprintf(stderr, "%s:%zu(%zu): ", name, row, col);
	fprintf(stderr, "%.*s\n", (int)(end - begin), begin);
	fprintf(stderr, "%*s^ invalid expression\n", (int)(itr - begin) + indent, "");
}

HOOK_STATIC void hook_globals_launch_init(const char *name, const char *json_data) {
	cJSON *json = cJSON_Parse(json_data);
	if (!json) {
		hook_globals_launch_json_error(name, json_data, cJSON_GetErrorPtr());
		return;
	}

	do {
		cJSON *prop1;
		if (!cJSON_IsObject(prop1 = cJSON_GetObjectItemCaseSensitive(json, "metin2"))) {
			fprintf(stderr, "[Kernel] Expected 'metin2' object within %s.\n", name);
			return;
		}

		cJSON *prop2;
		if (!cJSON_IsString(prop2 = cJSON_GetObjectItemCaseSensitive(prop1, "directory"))) {
			fprintf(stderr, "[Kernel] Warning, expected 'directory' field for object metin2.\n");
			// return;
		}
		else {
			LIB_strcpy(G.m2_folder, ARRAY_SIZE(G.m2_folder), prop2->valuestring);
		}
		if (!cJSON_IsString(prop2 = cJSON_GetObjectItemCaseSensitive(prop1, "metin2client.exe"))) {
			fprintf(stderr, "[Kernel] Warning, expected 'metin2client.exe' field for object metin2.\n");
			// return;
		}
		else {
			LIB_strcpy(G.m2_client, ARRAY_SIZE(G.m2_client), prop2->valuestring);
		}
	} while (false);

	do {
		cJSON *prop1;
		if (!cJSON_IsObject(prop1 = cJSON_GetObjectItemCaseSensitive(json, "Raventor_V2"))) {
			fprintf(stderr, "[Kernel] Expected 'Raventor_V2' object within %s.\n", name);
			return;
		}

		cJSON *prop2;
		if (!cJSON_IsObject(prop2 = cJSON_GetObjectItemCaseSensitive(prop1, "server"))) {
			fprintf(stderr, "[Kernel] Warning, expected 'server' object for object Raventor_V2.\n");
			// return;
		}
		else {
			cJSON *prop3;
			if (!cJSON_IsString(prop3 = cJSON_GetObjectItemCaseSensitive(prop2, "host"))) {
				fprintf(stderr, "[Kernel] Warning, expected 'host' object for object Raventor_V2/server.\n");
				// return;
			}
			else {
				LIB_strcpy(G.Raventor_V2.Server.host, ARRAY_SIZE(G.Raventor_V2.Server.host), prop3->valuestring);
			}

			if (!cJSON_IsNumber(prop3 = cJSON_GetObjectItemCaseSensitive(prop2, "port"))) {
				fprintf(stderr, "[Kernel] Warning, expected 'port' object for object Raventor_V2/server.\n");
				// return;
			}
			else {
				G.Raventor_V2.Server.port = prop3->valueint;
			}
		}
		
		if (!cJSON_IsObject(prop2 = cJSON_GetObjectItemCaseSensitive(prop1, "auth"))) {
			fprintf(stderr, "[Kernel] Warning, expected 'auth' object for object Raventor_V2.\n");
			// return;
		}
		else {
			cJSON *prop3;
			if (!cJSON_IsString(prop3 = cJSON_GetObjectItemCaseSensitive(prop2, "host"))) {
				fprintf(stderr, "[Kernel] Warning, expected 'host' object for object Raventor_V2/auth.\n");
				// return;
			}
			else {
				LIB_strcpy(G.Raventor_V2.Auth.host, ARRAY_SIZE(G.Raventor_V2.Auth.host), prop3->valuestring);
			}

			if (!cJSON_IsNumber(prop3 = cJSON_GetObjectItemCaseSensitive(prop2, "port"))) {
				fprintf(stderr, "[Kernel] Warning, expected 'port' object for object Raventor_V2/auth.\n");
				// return;
			}
			else {
				G.Raventor_V2.Auth.port = prop3->valueint;
			}
		}
	} while (false);

	cJSON_Delete(json);
}

#define BINARY(datatoc_name, filename, filepath) extern const char datatoc_name[];
#include "launch.h"
#undef BINARY

HOOK_STATIC void hook_globals_launch_pack_init() {
#define BINARY(datatoc_name, filename, filepath) hook_globals_launch_init(filename, datatoc_name);
#include "launch.h"
#undef BINARY
}
HOOK_STATIC void hook_globals_launch_user_init() {
	int fd;
	if (LIB_exist("launch.json") && (fd = LIB_open("launch.json", O_BINARY | O_RDONLY, 0))) {
		uint64_t size;
		if ((size = LIB_seek(fd, 0, SEEK_END))) {
			char *buf = (char *)MEM_mallocN(++size, "launch.json:data");
			if (buf) {
				LIB_seek(fd, 0, SEEK_SET);
				buf[LIB_read(fd, buf, size)] = '\0';
				hook_globals_launch_init("launch.json", buf);
				MEM_freeN(buf);
			}
			close(fd);
		}
	}
}

void KER_globals_launch_opt_init() {
	hook_globals_launch_pack_init(); // Load defaults
	hook_globals_launch_user_init();  // Load userdef
}
