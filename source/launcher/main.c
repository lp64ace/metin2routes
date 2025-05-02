#ifndef NDEBUG
#	include "MEM_guardedalloc.h"
#endif

#include "LIB_string.h"
#include "LIB_path_utils.h"
#include "LIB_utildefines.h"

#include "KER_global.h"

#include <stdio.h>
#include <windows.h>

void launch(const char *dll) {
	STARTUPINFO startup;
	PROCESS_INFORMATION process;

	ZeroMemory(&startup, sizeof(STARTUPINFO));
	startup.cb = sizeof(STARTUPINFO);
	startup.dwFlags |= STARTF_USESTDHANDLES;
	startup.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	startup.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	char client[1024];
	LIB_path_join(client, ARRAY_SIZE(client), G.m2_folder, G.m2_client);

	if (CreateProcess(client, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, G.m2_folder, &startup, &process)) {
		fprintf(stdout, "Process '%s' has been launched in suspended mode, pid %d!\n", G.m2_client, process.dwProcessId);
		fprintf(stdout, "Press any key to resume the application...\n");
		(void)getchar();

		LPVOID alloc = VirtualAllocEx(process.hProcess, NULL, LIB_strlen(dll) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (alloc) {
			WriteProcessMemory(process.hProcess, alloc, dll, LIB_strlen(dll) + 1, NULL);
			HANDLE hThread = CreateRemoteThread(process.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, alloc, 0, NULL);
			if (hThread != NULL) {
				WaitForSingleObject(hThread, INFINITE);
				CloseHandle(hThread);
			}
		}

		ResumeThread(process.hThread);
		WaitForSingleObject(process.hThread, INFINITE);

		DWORD exitCode = 0;
		if (GetExitCodeProcess(process.hProcess, &exitCode)) {
			fprintf(stdout, "Process exited with code %lu\n", exitCode);
		}

		CloseHandle(process.hProcess);
		CloseHandle(process.hThread);
	}
}

int main(void) {
#ifndef NDEBUG
	MEM_init_memleak_detection();
	MEM_enable_fail_on_memleak();
	MEM_use_guarded_allocator();
#endif

	KER_globals_init();
	do {
		launch(OUTPUT_RUNTIME_PATH "/Debug/client.dll");
	} while (false);
	KER_globals_exit();

	return 0;
}
