#include <Windows.h>
#include <iostream>



//__declspec(naked) void patch() {
//	__asm {
//		mov edx, [0x004010C5]
//		mov edx, 0x5
//	}
//}
//




int __cdecl main()
{
	const char crackme[] = "trnme by keng";
	
	HWND hwnd = FindWindowA(NULL, crackme);
	if (hwnd == NULL)
	{
		printf("FindWindowA is failed\n");
		system("pause");
		return EXIT_FAILURE;
	}


	DWORD pID = 0;
	GetWindowThreadProcessId(hwnd, &pID);

	if (pID == NULL)
	{
		printf("GetWindowThreadProcessId is failed\n");
		system("pause");
		return EXIT_FAILURE;
	}
	
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if (hProc == NULL)
	{
		printf("OpenProcess is failed\n");
		system("pause");
		return EXIT_FAILURE;
	}

	BYTE patch[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }; 

	if (!WriteProcessMemory(hProc, reinterpret_cast<void*>(0x0040217B), patch, sizeof(patch), NULL))
	{
		printf("WriteProcessMemory is failed: 0x%X\n", GetLastError());
		system("pause");
		return EXIT_FAILURE;
	}
	CloseHandle(hProc);

	return EXIT_SUCCESS;
}
