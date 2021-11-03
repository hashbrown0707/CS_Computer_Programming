#include<iostream>
using namespace std;

int main()
{
	int num;
	int a[110], b[110];
	int* ans = new int[110]{ 0 };

	do
	{
		cin >> num;
	} while (num < 0 || num > 100);

	for (size_t i = 1; i <= num; ++i)
	{
		cin >> a[i];
		cin >> b[i];

		a[i] = a[i] % 2 == 1 ? a[i] : a[i] + 1;

		for (; a[i] <= b[i]; a[i] += 2)
			ans[i] += a[i];
	}

	for (size_t i = 1; i <= num; ++i)
		cout << "Case" << i <<": " << ans[i] << "\n";

	system("pause");
	return 0;
}