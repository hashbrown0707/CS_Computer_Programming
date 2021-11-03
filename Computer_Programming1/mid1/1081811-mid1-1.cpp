#include <iostream>
using namespace std;

// returns the maximum cycle-length over all integers
// between and including first and last
int maxCycleLength( int first, int last );

int cycleLength( int n ); // returns the cycle-length of n

int main()
{
   int i, j;
   while( cin >> i >> j )
   {
      cout << i << ' ' << j << ' ';

      if( i > j )
      {
         int buf = i;
         i = j;
         j = buf;
      }

      cout << maxCycleLength( i, j ) << endl;
   }
}

int maxCycleLength( int first, int last )
{
    int max = cycleLength( first );

    if( first >= last )
        return max;
    
    int a = maxCycleLength( first + 1, last );
    max = max > a ? max : a;
    return max;

    //int max = 0;
    //for( size_t i = first; i <= last; i++ ) 
    //{
    //    int a = cycleLength( i );
    //    max = a > max ? a : max;
    //}

    //return max;
}

int cycleLength( int n )
{
    if( n == 1 ) return 1;
    if( n % 2 == 1 ) n = 3 * n + 1;
    else n /= 2;
    int sum = cycleLength( n );
    ++sum;
    return sum;
}