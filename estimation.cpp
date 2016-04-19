#include <stdio.h>
#include <conio.h>
#include <limits.h>
#include <iostream>

char* getBits(int num, char* binary);
int getSetBits(int num);
char* getLookupTable(char* lookupTable);
int getSetBits(int num, char* lookupTable);

using namespace std;

int main()
{
	int num;
	printf("Enter an integer number: ");
	scanf_s("%d", &num);

	int counterNaive = getSetBits(num);
	cout << "Bits set: " << counterNaive << endl;

	char binary[33];
	getBits(num, binary);
	cout << "Binary form check: " << binary << endl;

	char lookupTable[256];
	getLookupTable(lookupTable);

	int counterLookup = getSetBits(num, lookupTable);
	cout << "Bits set (lookup table): " << counterLookup << endl;

	_getch();
	return 0;
}

char* getBits(int num, char* binary) {

	unsigned int mask = 1 << 31;
	for (int i = 0; i < 32; i++) {

		if ((num & mask) > 0) {
			binary[i] = '1';
		}
		else {
			binary[i] = '0';
		}

		mask = mask >> 1;
	}

	binary[32] = '\0';
	return binary;
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

char* getLookupTable(char* lookupTable) {

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

		lookupTable[i] = counter;
	}

	return lookupTable;
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
