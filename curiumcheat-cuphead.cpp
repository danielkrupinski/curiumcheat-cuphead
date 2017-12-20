#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

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

				printf("Process found!");
				Sleep(1500);
				system("cls");
				std::cout << "Select mode: " << std::endl;
				std::cout << "1. Hard invincibility and supermeter cheat." << std::endl;
				std::cout << "2. Full invincibility but no sepermeter cheat." << std::endl;
				int mode = 0;
				std::cin >> mode;
				system("cls");
				printf("Cheat activated!");

				BYTE invincibility = 1;
				float supermeter = 50;
				size_t player = 0;

				for (;;)
				{
					/* Get player base address */
					ReadProcessMemory(hProcess, (LPVOID)(0x1020A13C), &player, sizeof(int), 0); // mono.dll(0x10000000)+0x20A13C
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x740), &player, sizeof(int), 0); // 0x740 - first offset
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x34), &player, sizeof(int), 0); // 0x34 - second offset
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x8), &player, sizeof(int), 0); // 0x8 - third offset
					ReadProcessMemory(hProcess, (LPVOID)(player + 0x18), &player, sizeof(int), 0); // 0x18 - fourth offset

					switch (mode)
					{
					case 1:
						WriteProcessMemory(hProcess, (LPVOID)(player + 0x84), &invincibility, sizeof(invincibility), 0); // invincibility - player base adress + 0x84
						WriteProcessMemory(hProcess, (LPVOID)(player + 0x68), &supermeter, sizeof(supermeter), 0); // super meter - player base adress + 0x68
						break;
					case 2:
						WriteProcessMemory(hProcess, (LPVOID)(player + 0x6C), &invincibility, sizeof(invincibility), 0); // full invincibility - player base adress + 0x6C
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
