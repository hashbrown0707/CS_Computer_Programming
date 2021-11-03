// Determine whether a number is a palindrome.
#include <iostream>
#include<list>
using namespace std; 

int main()
{
   int number, numCache; // user input number
   list<int> ls;

   cout << "Enter a 5-digit number: "; // prompt for a number
   cin >> number; // get number
   numCache = number;

   while (number > 0)
   {
	   int n = number % 10;
	   number /= 10;

	   ls.push_back(n);
   }

   for (size_t i = 0; i < ls.size() / 2; ++i)
   {
	   if (ls.front() == ls.back())
	   {
		   ls.pop_front(); 
		   ls.pop_back();
	   }
	   else
	   {
		   cout << numCache << " is not a palindrome.";
		   return 0;
	   }
   }

   cout << numCache << " is a palindrome!!!";

   system( "pause" );
} // end main