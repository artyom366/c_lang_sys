#include <windows.h>
#include <string.h>
#include <stdio.h>
#include<tchar.h>
#include <wchar.h>

int recursive(HANDLE hfile, WIN32_FIND_DATA lpFile);

int main(int argc, char* argv[])
{
	HANDLE hFile;
	WIN32_FIND_DATA lpFile;
	SYSTEMTIME lpSys;

	int i = 0, j = 0;

	char fileName[] = "a.txt";

	SetCurrentDirectory(_TEXT("C:\\search"));
	hFile = FindFirstFile(_TEXT("*.*"), &lpFile);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		if (lpFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("DIRECTORY\t");
			i++;
		}
		else
		{
			printf("FILE\t\t");
			j++;
		}

		FileTimeToSystemTime(&lpFile.ftLastWriteTime, &lpSys);
		printf_s("%ws\t%d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);
	}
	else
		printf("NO");

	recursive(hFile, lpFile);

	system("PAUSE");
	return 0;
}

int recursive(HANDLE hFile, WIN32_FIND_DATA lpFile) {

	SYSTEMTIME lpSys;

	while (FindNextFile(hFile, &lpFile))
	{
		if (lpFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("DIRECTORY\t");

			wchar_t lpBuffer[MAX_COMPUTERNAME_LENGTH + 1];
			DWORD nBufferLength = sizeof(lpBuffer);
			GetCurrentDirectory(nBufferLength, lpBuffer);

			wchar_t* newDirectory = wcsncat(lpBuffer, lpFile.cFileName, nBufferLength);
			SetCurrentDirectory(newDirectory);

			recursive(hFile, lpFile);
		}
		else
		{
			printf("FILE\t\t");

		}

		FileTimeToSystemTime(&lpFile.ftLastWriteTime, &lpSys);
		printf_s("%ws\t\t%d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);
	}

	FindClose(hFile);
	

	system("PAUSE");
	return 0;
}