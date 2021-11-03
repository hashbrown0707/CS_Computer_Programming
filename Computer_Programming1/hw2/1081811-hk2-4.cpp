#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int a, b, c, d, L;
	vector<int> ans;

	while (true)
	{
		cin >> a >> b >> c >> d >> L;

		if (!(a || b || c || d || L))
			break;

		if ((a > 1000 || a < -1000) || (b > 1000 || b < -1000) || (c > 1000 || c < -1000) || (d >= 1000000 || d <= 1) || (L >= 1000 || L < 0))
			continue;

		int temp = 0;

		if (!(a || b))
		{
			temp = c % d == 0 ? L + 1 : 0;
			ans.push_back(temp);
		}
		else
		{
			for (size_t i = 0; i < L; ++i)
				if ((a * i * i + b * i + c) % d == 0)
					temp++;

			ans.push_back(temp);
		}
	}

	for (auto i = ans.begin(); i < ans.end(); ++i)
		cout << *i << "\n";

	system("pause");
	return 0;
}