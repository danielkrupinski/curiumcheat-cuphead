#include <iostream>
#include <Windows.h>

int main()
{
	HANDLE handle = NULL;
	
	while (handle == NULL)
	{
		HWND hwnd = FindWindowA(0, ("Cuphead"));
		DWORD processID;
		GetWindowThreadProcessId(hwnd, &processID);
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
		Sleep(1);
	}

	printf("Process found!");

	Sleep(2000);
	system("cls");
	std::cout << "Select mode: " << std::endl;
	std::cout << "1. Hard invincibility and supermeter cheat." << std::endl;
	std::cout << "2. Full invincibility but no sepermeter cheat." << std::endl;
	int mode = 0;
	std::cin >> mode;
	system("cls");

	BYTE invincibility = 1;
	float supermeter = 50;
	//int coins = 60;
	size_t player = 0;
	//size_t money = 0;

	for (;;)
	{
		ReadProcessMemory(handle, (LPVOID)(0x1020A13C), &player, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(player + 0x740), &player, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(player + 0x34), &player, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(player + 0x8), &player, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(player + 0x18), &player, sizeof(int), 0);

		// experimental coins cheat (buggy)

		/*
		ReadProcessMemory(handle, (LPVOID)(0x101F40AC), &money, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(money + 0xCC), &money, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(money + 0x320), &money, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(money + 0x658), &money, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(money + 0x12C), &money, sizeof(int), 0);
		WriteProcessMemory(handle, (LPVOID)(money + 0xB4), &coins, sizeof(coins), 0);
		*/

		switch (mode)
		{
		case 1:
			WriteProcessMemory(handle, (LPVOID)(player + 0x84), &invincibility, sizeof(invincibility), 0);
			WriteProcessMemory(handle, (LPVOID)(player + 0x68), &supermeter, sizeof(supermeter), 0);
			break;
		case 2:
			WriteProcessMemory(handle, (LPVOID)(player + 0x6C), &invincibility, sizeof(invincibility), 0);
			break;
		default:
			return 0;
		}
		Sleep(1);
	}
	return 0;
}
