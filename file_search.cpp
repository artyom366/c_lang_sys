#include<iostream>
#include<windows.h>
#include<tchar.h>
using namespace std;
int main()
{
	HANDLE hFileResult;
	hFileResult = CreateFile(_TEXT("a.txt"), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	SetCurrentDirectory(_TEXT("C:\\"));

	//find first file
	SYSTEMTIME lpSys;
	WIN32_FIND_DATA lpFile;
	HANDLE hFileMask = FindFirstFile(_TEXT("*.*"), &lpFile);

	FileTimeToSystemTime(&lpFile.ftLastWriteTime, &lpSys);

	//write first file 
	char buffer[50];
	sprintf_s(buffer, "%ws\t%d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);

	DWORD all;
	SetFilePointer(hFileResult, 0, NULL, FILE_END);
	WriteFile(hFileResult, buffer, strlen(buffer), &all, NULL);
	
	//find other files
	while (FindNextFile(hFileMask, &lpFile)) {
		
		//write other files
		DWORD nb;
		char buffer[50];
		sprintf_s(buffer, "%ws %d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);
		
		SetFilePointer(hFileResult, 0, NULL, FILE_END);
		WriteFile(hFileResult, buffer, strlen(buffer), &nb, NULL);

		//collect all the bytes written
		all = all + nb;
	}

	CloseHandle(hFileResult);
	
	//read file names from result file
	SetCurrentDirectory(_TEXT("D:\\TSI\\Sys\\c_lang_sys\\lab\\files"));
	hFileResult = CreateFile(_TEXT("a.txt"), GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	while (all != 0) {
		DWORD read;
		char buff;
		ReadFile(hFileResult, &buff, sizeof(char), &read, NULL);
		cout << buff;
		all = all - read;
	}

	
	
	
	CloseHandle(hFileResult);
	system("PAUSE");
	
	return 0;
}
