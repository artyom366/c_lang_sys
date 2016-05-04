#include<iostream>
#include<windows.h>
#include<tchar.h>

using namespace std;


void main()
{
	HANDLE hFileResult;
	hFileResult = CreateFile(_TEXT("files.dat."), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	HANDLE hFileBase;
	WIN32_FIND_DATA lpFile;
	SYSTEMTIME lpSys;
	SetCurrentDirectory(_TEXT("C:\\"));
	hFileBase = FindFirstFile(_TEXT("*.*"), &lpFile);

	SetFilePointer(hFileResult, 4, NULL, FILE_END);

	if (hFileBase != INVALID_HANDLE_VALUE) {

		if (lpFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//printf("DIRECTORY\t");
		}
		else
		{
			//printf("FILE\t\t");
		}

		FileTimeToSystemTime(&lpFile.ftLastWriteTime, &lpSys);
		//printf_s("%ws\t%d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);

		char buffer[50];
		sprintf_s(buffer, "%ws\t\t%d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);

		WriteFile(hFileResult, buffer, sizeof(buffer), NULL, NULL);


	} 
	else {
		return;
	}

	while (FindNextFile(hFileBase, &lpFile))
	{
		if (lpFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("DIRECTORY\t");

		}
		else
		{
			printf("FILE\t\t");
		}

		FileTimeToSystemTime(&lpFile.ftLastWriteTime, &lpSys);

		printf_s("%ws\t\t%d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);

	}

	FindClose(hFileBase);
	system("PAUSE");
}
}

