#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	HWND hwnd = FindWindowA(0, ("Cuphead"));
	DWORD processID;
	GetWindowThreadProcessId(hwnd, &processID);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);

	int buffer = 0;

	ReadProcessMemory(handle, (LPVOID)(0x1020A13C), &buffer, sizeof(buffer), 0);
	ReadProcessMemory(handle, (LPVOID)(buffer + 0x740), &buffer, sizeof(buffer), 0);
	ReadProcessMemory(handle, (LPVOID)(buffer + 0x34), &buffer, sizeof(buffer), 0);
	ReadProcessMemory(handle, (LPVOID)(buffer + 0x8), &buffer, sizeof(buffer), 0);
	ReadProcessMemory(handle, (LPVOID)(buffer + 0x18), &buffer, sizeof(buffer), 0);

	int counter = 0;

	for (;;)
	{
		counter++;
		int buffer1 = 0;
		ReadProcessMemory(handle, (LPVOID)(buffer + 0x60), &buffer1, sizeof(buffer1), 0);
		if (buffer1 = 1)
		{
			int NewHealth = 4;
			WriteProcessMemory(handle, (LPVOID)(buffer + 0x60), &NewHealth, sizeof(NewHealth), 0);
		}
		Sleep(2000);
		if (counter < 5)
		{
			ReadProcessMemory(handle, (LPVOID)(0x1020A13C), &buffer, sizeof(buffer), 0);
			ReadProcessMemory(handle, (LPVOID)(buffer + 0x740), &buffer, sizeof(buffer), 0);
			ReadProcessMemory(handle, (LPVOID)(buffer + 0x34), &buffer, sizeof(buffer), 0);
			ReadProcessMemory(handle, (LPVOID)(buffer + 0x8), &buffer, sizeof(buffer), 0);
			ReadProcessMemory(handle, (LPVOID)(buffer + 0x18), &buffer, sizeof(buffer), 0);
			counter = 0;
		}
	}
	return 0;
}