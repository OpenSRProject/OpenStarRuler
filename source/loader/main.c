#include <windows.h>
#include <stdint.h>
#include <string.h>

int wmain(int argc, wchar_t* argv[]) {

	STARTUPINFOW startup = {};
	startup.cb = sizeof(startup);

	PROCESS_INFORMATION process = {};

	wchar_t* path = L"bin\\win64\\Star Ruler 2.exe";

	size_t size = 0;
	for (int i = 0; i < argc; i++) {
		if (wcscmp(argv[i], L"--legacy") == 0) {
			path = L"bin_legacy\\win64\\Star Ruler 2.exe";
		}
		else {
			// worst-case estimate of expected escaped argument size, two output characters for every input character
			// (to handle quotes and backslashes), one separator space and a leading and trailing quote
			// first argument has no space, use it for the null terminator
			size += wcslen(argv[i]) * 2 + 3;
		}
	}

	//Create command, passing all of our arguments

	wchar_t* cmdline = malloc(size * sizeof(wchar_t));
	wchar_t* cur = cmdline;

	for (int i = 0; i < argc; i++) {
		if (wcscmp(argv[i], L"--legacy") == 0) {
			continue;
		}

		for (wchar_t* arg = argv[i]; *arg != L'\0'; arg++) {
			if (i != 0) {
				*cur++ = L' ';
			}
			*cur++ = L'"';
			switch (*arg) {
			case L'"':
				*cur++ = L'\\';
				*cur++ = L'"';
				arg++;
				break;
			case L'\\':
				int backslashes = 0;
				do {
					backslashes++;
				} while (arg[backslashes] == L'\\');
				if (arg[backslashes] != 0 && arg[backslashes] != L'"') {
					for (int j = 0; j < backslashes; j++) {
						*cur++ = L'\\';
					}
				}
				else {
					for (int j = 0; j < backslashes; j++) {
						*cur++ = L'\\';
						*cur++ = L'\\';
					}
				}
				arg += backslashes;
				break;
			default:
				*cur++ = *arg++;
			}
			*cur++ = L'"';
		}
	}
	*cur = L'\0';

	if (CreateProcessW(path, cmdline, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &startup, &process) != FALSE) {
		CloseHandle(process.hProcess);
		CloseHandle(process.hThread);
	}
	free(cmdline);
	return 0;
}
