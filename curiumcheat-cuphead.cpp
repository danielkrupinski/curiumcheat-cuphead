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

	int pPlayer = 0;

	ReadProcessMemory(handle, (LPVOID)(0x1020A13C), &pPlayer, sizeof(pPlayer), 0);
	ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x740), &pPlayer, sizeof(pPlayer), 0);
	ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x34), &pPlayer, sizeof(pPlayer), 0);
	ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x8), &pPlayer, sizeof(pPlayer), 0);
	ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x18), &pPlayer, sizeof(pPlayer), 0);

	system("cls");
	printf("Select max health you want: ");
	int NewHealth = 0;
	cin >> NewHealth;
	WriteProcessMemory(handle, (LPVOID)(pPlayer + 0x5C), &NewHealth, sizeof(NewHealth), 0);

	int counter = 0;

	for (;;)
	{
		counter++;
		int pPlayer1 = 0;
		ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x60), &pPlayer1, sizeof(pPlayer1), 0);
		if (pPlayer1!=NewHealth)
		{
			WriteProcessMemory(handle, (LPVOID)(pPlayer + 0x60), &NewHealth, sizeof(NewHealth), 0);
		}
		Sleep(1000);
		if (counter==5)
		{
			ReadProcessMemory(handle, (LPVOID)(0x1020A13C), &pPlayer, sizeof(pPlayer), 0);
			ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x740), &pPlayer, sizeof(pPlayer), 0);
			ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x34), &pPlayer, sizeof(pPlayer), 0);
			ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x8), &pPlayer, sizeof(pPlayer), 0);
			ReadProcessMemory(handle, (LPVOID)(pPlayer + 0x18), &pPlayer, sizeof(pPlayer), 0);
			counter = 0;
		}
	}
	return 0;
}
