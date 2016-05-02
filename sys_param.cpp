#include<iostream>
#include<windows.h>
#include<tchar.h>

using namespace std;

void main()
{

	//os version
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	int result = GetVersionEx((OSVERSIONINFO*)&osvi);

	if (result) {
		if (osvi.dwMajorVersion >= 6) {
			cout << "OS is Windows 7" << endl;
		}
	}

	//pc name
	wchar_t lpBuffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD lpnSize = sizeof(lpBuffer);
	GetComputerName(lpBuffer, &lpnSize);

	wcout << "PC name: " << lpBuffer << endl;

	//local time
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);

	cout << "Local time: " << systemTime.wHour << ":" << systemTime.wMinute << ":" << systemTime.wSecond << endl;

	//time zone
	TIME_ZONE_INFORMATION timeZone;
	GetTimeZoneInformation(&timeZone);

	wcout << "Time zone: " << timeZone.StandardName << endl;

	//default lang
	LANGID langId = GetUserDefaultLangID();

	if (langId == 1033) {
		cout << "Default language: US English" << endl;
	}
	
	//ver language name
	DWORD wLang = 0x0409;
	wchar_t szLang[100];
	DWORD cchLang = sizeof(szLang);
	VerLanguageName(wLang, szLang, cchLang);

	wcout << "Ver languange name: " << szLang << endl;

	//user name
	wchar_t lpBuffer_1[10];
	DWORD lpnSize_1 = sizeof(lpBuffer);
	GetUserName(lpBuffer_1, &lpnSize_1);

	wcout << "User name: " << lpBuffer << endl;

	//current directory
	wchar_t lpBuffer_2[MAX_PATH + 1];
	DWORD nBufferLength = sizeof(lpBuffer_2);
	GetCurrentDirectory(nBufferLength, lpBuffer_2);

	wcout << "Current directory: " << lpBuffer << endl;

	//windows directory
	wchar_t lpBuffer_3[MAX_PATH + 1];
	UINT uSize = sizeof(lpBuffer_3);
	GetWindowsDirectory(lpBuffer_3, uSize);

	wcout << "Windows directory: " << lpBuffer_3 << endl;

	//system directory
	wchar_t lpBuffer_4[MAX_PATH + 1];
	UINT uSize_1 = sizeof(lpBuffer_4);
	GetSystemDirectory(lpBuffer_4, uSize_1);

	wcout << "System directory: " << lpBuffer_4 << endl;

	//drives
	DWORD drives = GetLogicalDrives();
	unsigned int mask = 1 << 31;

	cout << "Drives: ";
	for (int i = 0; i < 31; i++) {

		if ((drives & mask) > 0) {
			
			switch (i) {
				case 31: {
					cout << "A ";
				}
						break;

				case 30: {
					cout << "B ";
				}
						break;

				case 29: {
					cout << "C ";
				}
						break;

				case 28: {
					cout << "D ";
				}
						break;

				case 27: {
					cout << "E ";
				}
						break;

				case 26: {
					cout << "F ";
				}
						break;

				case 25: {
					cout << "G ";
				}
						break;

				case 24: {
					cout << "H ";
				}
						break;

				case 23: {
					cout << "I ";
				}
						break;
			}
		}

		mask = mask >> 1;
	}
	cout << endl;

	//drives string
	wchar_t lpBuffer_5[MAX_PATH + 1];
	DWORD nBufferLength_1 = sizeof(lpBuffer_5);
	GetLogicalDriveStrings(nBufferLength_1, lpBuffer_5);

	wcout << "Drives string: " << lpBuffer_5 << endl;

	//drive type
	wchar_t lpRootPathName[] = {L"C:\\"};
	UINT type = GetDriveType(lpRootPathName);

	if (type == 3) {
		cout << "Drive type: HDD" << endl;
	}

	//disk free space
	wchar_t lpRootPathName_1[] = { L"C:\\" };
	DWORD lpSectorsPerCluster;
	DWORD lpBytesPerSector;
	DWORD lpNumberOfFreeClusters;
	DWORD lpTotalNumberOfClusters;
	GetDiskFreeSpace(lpRootPathName_1, &lpSectorsPerCluster, &lpBytesPerSector, &lpNumberOfFreeClusters, &lpTotalNumberOfClusters);

	cout << "Sectors per cluster: " << lpSectorsPerCluster << endl;
	cout << "Bytes per sector: " << lpBytesPerSector << endl;
	cout << "Number of free clusters: " << lpNumberOfFreeClusters << endl;
	cout << "Total number of clusters: " << lpTotalNumberOfClusters << endl;

	system("PAUSE");
}
