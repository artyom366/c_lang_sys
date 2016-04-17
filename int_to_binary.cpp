#include <stdio.h>
#include <conio.h>

unsigned long long int getBits(int num);

int main()
{
	int num;
	printf("Enter an integer number: ");
	scanf_s("%d", &num);

	unsigned long long int result = getBits(num);
	printf("Binary result is: %d", result);

	_getch();
	return 0;
}

unsigned long long int getBits(int num) {

	unsigned long long int shift = 1;
	unsigned long long int result = 0;
	while (num) {
		result = result + shift * (num % 2);
		num = num / 2;
		shift = shift * 10;
	}

	return result;
}