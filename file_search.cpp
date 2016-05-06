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
	SYSTEMTIME creationTime;
	SYSTEMTIME accessTime;
	SYSTEMTIME modificationTime;

	WIN32_FIND_DATA lpFile;
	HANDLE hFileMask = FindFirstFile(_TEXT("*.*"), &lpFile);

	//write first file 
	char buffer[100];
	FileTimeToSystemTime(&lpFile.ftCreationTime, &creationTime);
	FileTimeToSystemTime(&lpFile.ftLastAccessTime, &accessTime);
	FileTimeToSystemTime(&lpFile.ftLastWriteTime, &modificationTime);

	sprintf_s(buffer, "%ws\t%d.%d.%d %d:%d \t%d.%d.%d %d:%d \t%d.%d.%d %d:%d \n", lpFile.cFileName, 
		creationTime.wDay, creationTime.wMonth, creationTime.wYear, creationTime.wHour, creationTime.wMinute,
		accessTime.wDay, accessTime.wMonth, accessTime.wYear, accessTime.wHour, accessTime.wMinute,
		modificationTime.wDay, modificationTime.wMonth, modificationTime.wYear, modificationTime.wHour, modificationTime.wMinute);

	DWORD all;
	SetFilePointer(hFileResult, 0, NULL, FILE_END);
	WriteFile(hFileResult, buffer, strlen(buffer), &all, NULL);
	
	//find other files
	while (FindNextFile(hFileMask, &lpFile)) {
		
		//write other files
		FileTimeToSystemTime(&lpFile.ftCreationTime, &creationTime);
		FileTimeToSystemTime(&lpFile.ftLastAccessTime, &accessTime);
		FileTimeToSystemTime(&lpFile.ftLastWriteTime, &modificationTime);

		DWORD nb;
		char buffer[100];
		sprintf_s(buffer, "%ws %d.%d.%d %d:%d \t%d.%d.%d %d:%d \t%d.%d.%d %d:%d \n", lpFile.cFileName, 
			creationTime.wDay, creationTime.wMonth, creationTime.wYear, creationTime.wHour, creationTime.wMinute,
			accessTime.wDay, accessTime.wMonth, accessTime.wYear, accessTime.wHour, accessTime.wMinute,
			modificationTime.wDay, modificationTime.wMonth, modificationTime.wYear, modificationTime.wHour, modificationTime.wMinute);
		
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
