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

	BYTE invincibility = 1;
	size_t pPlayer = 0;

	for (;;)
	{
		ReadProcessMemory(handle, (LPVOID)(0x1020A13C), &pPlayer, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x740), &pPlayer, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x34), &pPlayer, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x8), &pPlayer, sizeof(int), 0);
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x18), &pPlayer, sizeof(int), 0);
		WriteProcessMemory(handle, (LPVOID)(pPlayer + 0x84), &invincibility, sizeof(invincibility), 0);
		Sleep(1);
	}
	return 0;
}
