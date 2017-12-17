#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HANDLE handle = NULL;
	
	while (handle == NULL)
	{
		printf("Searching for game process");
		Sleep(900);
		printf(".");
		Sleep(900);
		printf(".");
		Sleep(900);
		printf(".");
		Sleep(900);
		HWND hwnd = FindWindowA(0, ("Cuphead"));
		DWORD processID;
		GetWindowThreadProcessId(hwnd, &processID);
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
		system("cls");
	}

	system("cls");
	printf("Process found!");

	DWORD pPlayer = 0;
	BYTE invictible = 1;

	for (;;)
	{
		ReadProcessMemory(handle, (LPVOID)(0x1020A13C), &pPlayer, sizeof(pPlayer), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x740), &pPlayer, sizeof(pPlayer), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x34), &pPlayer, sizeof(pPlayer), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x8), &pPlayer, sizeof(pPlayer), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x18), &pPlayer, sizeof(pPlayer), 0);
		WriteProcessMemory(handle, (LPVOID)(pPlayer + 0x6C), &invictible, sizeof(invictible), 0);
		Sleep(5000);
	}
	return 0;
}
