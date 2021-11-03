// Determine whether three values represent the sides of a right triangle.
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int side1; // length of side 1
	int side2; // length of side 2
	int side3; // length of side 3

	// get values of three sides
	cout << "Enter side 1: ";
	cin >> side1;

	cout << "Enter side 2: ";
	cin >> side2;

	cout << "Enter side 3: ";
	cin >> side3;

	int sorted[] = { side1, side2, side3 };
	sort(sorted, sorted + 3);

	bool isTriangle = (pow(sorted[2], 2) == pow(sorted[0], 2) + pow(sorted[1], 2));

	if (isTriangle)
		cout << "These are the sides of a right triangle.";
	else
		cout << "These do not form a right triangle.";

	system("pause");
} // end main