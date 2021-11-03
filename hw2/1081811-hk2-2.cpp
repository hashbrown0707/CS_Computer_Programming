#include<iostream>
#include<vector>
using namespace std;

int main()
{
	unsigned int num;
	int sum = 0;
	vector<int> ans;

	while (true)
	{
		sum = 0;
		cin >> num;

		if (num <= 0 || num > 2000000000)
			break;

		while (num > 0)
		{
			sum += (num % 10);
			num /= 10;

			if (sum > 9)
			{
				num = sum;
				sum = 0;
			}
		}

		ans.push_back(sum);
	}

	for (auto i = ans.begin(); i < ans.end(); ++i)
		cout << *i << "\n";

	system("pause");
	return 0;
}