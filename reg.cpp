#include<iostream>
#include<windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>

using namespace std;

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

void rec(HKEY hOpenKey);

int main()
{
	
	char str1[8];
	scanf_s("%s", &str1);
	

	LPTSTR test = TEXT("System");

	LONG lRValue;
	HKEY hOpenKey;
	TCHAR achKey[MAX_KEY_LENGTH];

	lRValue = RegOpenKeyEx(HKEY_CURRENT_USER, test, 0, KEY_READ, &hOpenKey);

	rec(hOpenKey);

	system("PAUSE");
}

void rec(HKEY hOpenKey) {

	HKEY hKey;
	TCHAR achClass[MAX_PATH] = TEXT("System");
	DWORD cchClassName = MAX_PATH;
	DWORD cSubKeys = 0;
	DWORD cbMaxSubKey;
	DWORD cchMaxClass;
	DWORD cValues;
	DWORD cchMaxValue;
	DWORD cbMaxValueData;
	DWORD cbSecurityDescriptor;
	FILETIME ftLastWriteTime;

	RegQueryInfoKey(hOpenKey,
		achClass,
		&cchClassName,
		NULL,
		&cSubKeys,
		&cbMaxSubKey,
		&cchMaxClass,
		&cValues,
		&cchMaxValue,
		&cbMaxValueData,
		&cbSecurityDescriptor,
		&ftLastWriteTime);


	DWORD i, retCode;
	DWORD cbName;
	TCHAR achKey[MAX_KEY_LENGTH];

	if (cSubKeys)
	{
		printf("\nNumber of subkeys: %d\n", cSubKeys);

		for (i = 0; i<cSubKeys; i++)
		{
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hOpenKey, i,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);
			if (retCode == ERROR_SUCCESS)
			{
				_tprintf(TEXT("(%d) %s\n"), i + 1, achKey);
			}
		}
	}


	//if (lRValue == ERROR_SUCCESS) {
	//	cout << "OK";
	//}

	//DWORD dwIndex;
	//DWORD dwKeyNameLength = 256;

	//lRValue = RegEnumKeyEx(hOpenKey, dwIndex, keyName, &dwKeyNameLength, 0, NULL, NULL, &structFT);


	
}