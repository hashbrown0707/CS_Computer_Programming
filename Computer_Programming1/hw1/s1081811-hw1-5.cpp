#include <iostream>
using namespace std;

int main()
{
	int year;
	cout << "Enter a year ( 1583-3000 ): ";
	cin >> year;

	bool isLeap = ((year % 4 == 0) && !(year % 100 == 0)) || (year % 400 == 0);

	if (isLeap)
		cout << "Year " << year << " is a leap year.";
	else
		cout << "Year " << year << " is a common year.";


	system("pause");
}