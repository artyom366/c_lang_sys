#include <iostream>
#include <conio.h>

using namespace std;
unsigned long long int getBits(unsigned long long int num);
unsigned long long int get8bitMask(unsigned long long int num);

int main()
{
	unsigned long long int num = 3;
	int shift = 1;
	char direction = 'R';

	int result;
	switch (direction)
	{
	case 'R': {
		result = (num >> shift) | (num << (8 - shift));
	}
	break;

	case 'L': {
		printf("%d", sizeof(int));
		printf("%d", sizeof(int) - shift);
		result = (num << shift) | (num >> (8 - shift));
	}
	break;

	default:
		cout << "error" << endl;
		return 1;
	}

	result = get8bitMask(result);

	cout << "Number is: " << num << endl;
	cout << "Binary number is: " << getBits(num) << endl;
	cout << "Shifted number is: " <<  result << endl;
	cout << "Shifted binary number is: " << getBits(result) << endl;

	_getch();
	return 0;
}

unsigned long long int getBits(unsigned long long int num) {

	int shift = 1;
	unsigned long long int result = 0;
	while (num) {
		result = result + shift * (num % 2);
		num = num / 2;
		shift = shift * 10;
	}

	return result;
}

unsigned long long int get8bitMask(unsigned long long int num) {
	return num & 255;
}
