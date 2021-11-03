#include <iostream> // allows program to perform input and output
#include<stack>
using namespace std; // program uses names from the std namespace

int main()
{
	int number; // integer read from user
	stack<int> s;

	cout << "Enter a five-digit integer: "; // prompt
	cin >> number; // read integer from user

	while (number > 0)
	{
		int n = number % 10;
		number /= 10;

		s.push(n);
		//cout << n << " ";
	}

	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}

	system("pause");
} // end main