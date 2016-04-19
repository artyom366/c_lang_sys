#include <stdio.h>
#include <conio.h>
#include <limits.h>
#include <iostream>

unsigned long long int getBits(int num);
int getSetBits(int num);
char* getLookupTable();
int getSetBits(int num, char* lookupTable);

using namespace std;

int main()
{
	int num;
	printf("Enter an integer number: ");
	scanf_s("%d", &num);

	int counterNaive = getSetBits(num);
	cout << "Bits set: " << counterNaive << endl;

	unsigned long long int binary = getBits(num);
	cout << "Binary form check: " << binary << endl;

	char* lookupTable = getLookupTable();
	int counterLookup = getSetBits(num, lookupTable);
	cout << "Bits set (lookup table): " << counterLookup << endl;

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

char* getLookupTable() {

	char maskMatrix[256];
	for (short i = 0; i < 256; i++) {

		short mask = 1 << 7;
		i = i & 0b0000000011111111;

		int counter = 0;
		for (int j = 0; j < 8; j++) {

			if ((i & mask) > 0) {
				counter++;
			}

			mask = mask >> 1;
		}

		maskMatrix[i] = counter;
	}

	return maskMatrix;
}

int getSetBits(int num, char* lookupTable) {

	int counter = 0;
	for (int i = 0; i < 4; i++) {

		int byte = (num >> 8 * i) & 0b11111111;
		int bits = lookupTable[byte];
		counter = counter + bits;
	}

	return counter;
}
