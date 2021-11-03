#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int testAmount, storeAmount;
	cin >> testAmount;
	int* ans = new int[testAmount + 1];

	if (testAmount < 1 || testAmount > 100)
		return 0;

	for (size_t i = 0; i < testAmount; ++i)
	{
		int store, maxStore = 0, minStore = 100;
		cin >> storeAmount;

		for (size_t j = 1; j <= storeAmount; ++j)
		{
			cin >> store;

			maxStore = max(store, maxStore);
			minStore = min(store, minStore);
		}

		ans[i] = (maxStore - minStore) * 2;
	}

	for (size_t i = 0; i < testAmount; ++i)
		cout << ans[i] << "\n";

	delete[] ans;
	system("pause");
	return 0;
}