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

	DWORD nb;
	SetFilePointer(hFileResult, 0, NULL, FILE_END);
	WriteFile(hFileResult, buffer, strlen(buffer), &nb, NULL);
	
	//find other files
	while (FindNextFile(hFileMask, &lpFile)) {

		//write other files
		char buffer[50];
		sprintf_s(buffer, "%ws\t%d.%d.%d %d:%d\n", lpFile.cFileName, lpSys.wDay, lpSys.wMonth, lpSys.wYear, lpSys.wHour, lpSys.wMinute);
		SetFilePointer(hFileResult, 0, NULL, FILE_END);
		WriteFile(hFileResult, buffer, strlen(buffer), &nb, NULL);
	}

	//read file names from result file


	CloseHandle(hFileResult);


	hFileResult = CreateFile(_TEXT("a.txt"), GENERIC_READ, 0, NULL,OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char m;
	ReadFile(hFileResult, &m, sizeof(char), &nb, NULL);
	
	while (nb != 0)
	{
		cout << m << endl;
		ReadFile(hFileResult, &m, sizeof(char), &nb, NULL);
	}
	
	CloseHandle(hFileResult);
	system("PAUSE");
	
	return 0;
}
