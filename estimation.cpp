#include <stdio.h>
#include <conio.h>
#include <limits.h>
#include <iostream>

unsigned long long int getBits(int num);
int getSetBits(int num);
char* getMaskMatrix();

using namespace std;

int main()
{
	int num;
	printf("Enter an integer number: ");
	scanf_s("%d", &num);

	int counter = getSetBits(num);
	cout << "Bits set: " << counter << endl;

	unsigned long long int binary = getBits(num);
	cout << "Binary form check: " << binary << endl;

	_getch();
	return 0;
}

unsigned long long int getBits(int num) {

	int shift = 1;
	unsigned  long long int result = 0;
	while (num) {
		result = result + shift * (num % 2);
		num = num / 2;
		shift = shift * 10;
	}

	return result;
}

int getSetBits(int num) {

	int counter = 0;
	unsigned int mask = 1 << 31;
	for (int i = 0; i < 32; i++) {

		if ((num & mask) > 0) {
			counter++;
			cout << 1;
		}
		else {
			cout << 0;
		}

		mask = mask >> 1;
	}

	cout << endl;
	return counter;
}

char* getMaskMatrix() {

	char mask[255];
	for (int i = 0; i < 255; i++) {
		mask[i] = i;
	}

	return mask;
}

