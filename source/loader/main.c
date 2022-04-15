#include <Windows.h>

static inline __forceinline __declspec(allocator) wchar_t* wstrdup(const wchar_t *_String) {
	size_t i = 0;
	while (_String[i] != 0)
		i++;
	wchar_t* ret = (wchar_t *)HeapAlloc(GetProcessHeap(), 0, i + 1);
	wsprintfW(ret, L"%s", _String);
	return ret;
}

DWORD __stdcall mainCRTStartup(LPVOID p) {
	//Create command, passing all of our arguments
	LPWSTR cmdline = GetCommandLineW();
	wchar_t search = ' ';
	if (cmdline[0] == '"') {
		search = '"';
		cmdline++;
	}
	while (cmdline[0] != 0) {
		cmdline++;
		if (cmdline[0] == search) {
			cmdline++;
			break;
		}
	}
	while (cmdline[0] == ' ') {
		cmdline++;
	}

	STARTUPINFOW startup;
		SecureZeroMemory(&startup, sizeof(startup));
		startup.cb = sizeof(startup);

	PROCESS_INFORMATION process;
		SecureZeroMemory(&process, sizeof(process));

	if(CreateProcessW(L"bin\\win64\\Star Ruler 2.exe", wstrdup(cmdline), NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &startup, &process) != FALSE) {
		CloseHandle(process.hProcess);
		CloseHandle(process.hThread);
	}
	return 0;
}
