#include <iostream>
using namespace std;

// prints the binary representation of number,
// for example, if number is 10, then prints 1010
void displayBinary(int number);

// returns the sum of all bits of the binary representation of number,
// or equivalently the number of 1s in the binary representation of number,
// for example, if number is 10, then returns 2
int sumBits(int number);

int main()
{
	int number;
	cin >> number;
	while (number > 0)
	{
		cout << "The parity of ";
		displayBinary(number);

		cout << " is " << sumBits(number) << " (mod 2).\n";

		cin >> number;
	}

	system("pause");
}

void displayBinary(int number)
{
	if (number == 0)
		return;

	int temp = number % 2;
	displayBinary(number / 2);

	cout << temp;
}

int sumBits(int number)
{
	int sum = 0;

	//while (number > 0)
	//{
	//	if (number % 2 == 1)
	//		sum++;

	//	number /= 2;
	//}

	if (number <= 0)
		return sum;

	if (number % 2 == 1)
		sum = 1;

	sum += sumBits(number / 2);

	return sum;
}