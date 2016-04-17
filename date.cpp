#include <iostream>
#include <conio.h>

using namespace std;
unsigned long long int getBits(int num);
int getDateToBits(int date, int month, int year);
int getDateToInt(int binary);

int main()
{
	int year;
	int month;
	int date;

	cout << "Enter a date DD: " << endl;
	cin >> date;

	if (date > 31) {
		return 1;
	}

	cout << "Enter a month MM: " << endl;
	cin >> month;

	if (month > 12) {
		return 1;
	}

	cout << "Enter a year YYYY: " << endl;
	cin >> year;

	if (year > 2047) {
		return 1;
	}

	cout << endl;

	int binary = getDateToBits(date, month, year);
	cout << "Packed date is: " << binary << endl;

	cout << endl;

	int decimal = getDateToInt(binary);

	_getch();
	return 0;
}

unsigned long long int getBits(int num) {

	unsigned  long long int shift = 1;
	unsigned  long long int result = 0;
	while (num) {
		result = result + shift * (num % 2);
		num = num / 2;
		shift = shift * 10;
	}

	return result;
}

int getDateToBits(int date, int month, int year) {

	int binary = date;
	cout << getBits(binary) << endl;

	binary = binary << 4;
	cout << getBits(binary) << endl;

	binary = binary + month;
	cout << getBits(binary) << endl;

	binary = binary << 11;
	cout << getBits(binary) << endl;

	binary = binary + year;
	cout << getBits(binary) << endl;
	cout << endl;

	return binary;
}

int getDateToInt(int binary) {

	int year = binary & 2047;
	cout << year << endl;

	binary = binary >> 11;
	int month = binary & 15;
	cout << month << endl;

	int day = binary >> 4;
	cout << day << endl;

	return 0;
}

