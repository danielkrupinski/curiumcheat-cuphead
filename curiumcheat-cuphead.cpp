#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>

DWORD_PTR dwGetModuleBaseAddress(DWORD dwProcID, TCHAR *szModuleName)
{
	DWORD_PTR dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32;
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				if (_tcsicmp(ModuleEntry32.szModule, szModuleName) == 0)
				{
					dwModuleBaseAddress = (DWORD_PTR)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return dwModuleBaseAddress;
}

int main()
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, "Cuphead.exe") == 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

				DWORD_PTR monodlladress = dwGetModuleBaseAddress(entry.th32ProcessID, (TCHAR*)("mono.dll"));

				printf("Process found!");
				Sleep(1000);
				system("cls");
				printf("Select mode: \n");
				printf("1. Hard invincibility and supermeter cheat.\n");
				printf("2. Full invincibility but no sepermeter cheat.\n");
				int mode = 0;
				scanf_s("%d", &mode);
				system("cls");
				printf("Cheat activated!");

				BYTE invincibility = 1;
				float supermeter = 50;
				size_t player = 0;

				for (;;)
				{
					ReadProcessMemory(hProcess, (LPVOID)(monodlladress+0x20A13C), &player, sizeof(int), 0);
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x740), &player, sizeof(int), 0);
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x34), &player, sizeof(int), 0);
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x8), &player, sizeof(int), 0);
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x18), &player, sizeof(int), 0);

					switch (mode)
					{
					case 1:
						WriteProcessMemory(hProcess, (LPVOID)(player + 0x84), &invincibility, sizeof(invincibility), 0);
						WriteProcessMemory(hProcess, (LPVOID)(player + 0x68), &supermeter, sizeof(supermeter), 0);
						break;
					case 2:
						WriteProcessMemory(hProcess, (LPVOID)(player + 0x6C), &invincibility, sizeof(invincibility), 0);
						break;
					default:
						return 0;
					}
					Sleep(1);
				}
				CloseHandle(hProcess);
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}
