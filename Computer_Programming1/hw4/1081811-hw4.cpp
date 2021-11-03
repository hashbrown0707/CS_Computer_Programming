#include<iostream>
using std::cin;
using std::cout;
using std::endl;

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// --hugeInt
void decrement( int hugeInt[], int size );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize );

// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size );

const int arraySize = 200;

int main()
{
   int t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         int dividend[ arraySize ] = {};
         int divisor[ arraySize ] = {};
         int quotient[ arraySize ] = {};
         int remainder[ arraySize ] = {};

         int dividendSize = 1;
         int divisorSize = 1;
         int quotientSize = 1;
         int remainderSize = 1;

         // put all digits of t into base
         int base[ arraySize ] = {};
         int baseSize = 0;
         for( int i = t; i > 0; i /= 10 )
            base[ baseSize++ ] = i % 10;

         // dividend = pow( t, a )
         dividend[ 0 ] = 1;
         for( int i = 0; i < a; ++i )
         {
            multiplication( dividend, base, dividendSize, baseSize );
            if( dividendSize > arraySize )
               break;
         }

         if( dividendSize > arraySize )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            // divisor = pow( t, b )
            divisor[ 0 ] = 1;
            for( int i = 0; i < b; ++i )
               multiplication( divisor, base, divisorSize, baseSize );

            decrement( dividend, dividendSize ); // --dividend
            decrement( divisor, divisorSize );   // --divisor

            division( dividend, divisor, quotient, remainder,
                      dividendSize, divisorSize, quotientSize, remainderSize );

            // quotient is an integer with less than 100 digits
            if( quotientSize < 100 && isZero( remainder, remainderSize ) )
               for( int i = quotientSize - 1; i >= 0; i-- )
                  cout << quotient[ i ];
            else
               cout << "is not an integer with less than 100 digits.";
            cout << endl;
         }
      }
   }
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
    if (size1 > size2)
        return false;

    if(size1 == size2)
        for (int i = size1; i >= 0; --i)
        {
            if (hugeInt1[i] < hugeInt2[i])
                return true;
            else if (hugeInt1[i] == hugeInt2[i])
            {
                if (i > 0)
                    continue;
                else
                    return false;
            }
            else
                return false;
        }

    return true;
}

// --hugeInt
void decrement( int hugeInt[], int size )
{
    hugeInt[0]--;

    for (size_t i = 0; i < size - 1; ++i)
    {
        if (hugeInt[i] < 0)
        {
            hugeInt[i] += 10;
            hugeInt[i + 1]--;
        }
        else
            break;
    }
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize )
{
    size_t differenceSize = minuendSize;

    for (size_t i = 0; i < subtrahendSize; ++i)
        minuend[i] -= subtrahend[i];

    for (size_t i = 0; i < differenceSize - 1; ++i)
    {
        if (minuend[i] < 0)
        {
            minuend[i] += 10;
            minuend[i + 1]--;
        }
    }

    for (size_t i = differenceSize - 1; i > 0; --i)
    {
        if (minuend[i] == 0)
            differenceSize--;
        else
            break;
    }

    minuendSize = differenceSize;
}

// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize )
{
    //size_t productSize = multiplicandSize + multiplierSize;
    //for (size_t i = 0; i < multiplicandSize; ++i)
    //    for (size_t j = 0; j < multiplierSize; ++j)
    //        multiplicand[i] *= multiplier[j];
    //for (size_t i = 0; i < productSize; ++i)
    //{
    //    if (multiplicand[i] > 9)
    //    {
    //        multiplicand[i + 1] += multiplicand[i] / 10;
    //        multiplicand[i] %= 10;
    //    }
    //}
    //for (size_t i = productSize - 1; i > 0; --i)
    //{
    //    if (multiplicand[i] == 0)
    //        productSize--;
    //    else
    //        break;
    //}
    //multiplicandSize = productSize;

    int product[arraySize + 10] = {};
    int productSize = multiplicandSize + multiplierSize;

    for (size_t i = 0; i < multiplicandSize; ++i)
        for (size_t j = 0; j < multiplierSize; ++j)
            product[i + j] += multiplicand[i] * multiplier[j];

    for (size_t i = 0; i < productSize; ++i)
    {
        if (product[i] > 9)
        {
            int temp = product[i] % 10;
            product[i + 1] += (product[i] - temp) / 10;
            product[i] %= 10;
        }
    }

    for (int i = productSize - 1; i > 0; --i)
    {
        if (product[i] == 0)
            productSize--;
        else
            break;
    }

    //if (productSize > arraySize)
    //    return;

    multiplicandSize = productSize;
    for (size_t i = 0; i < productSize; ++i)
        multiplicand[i] = product[i];
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
    if (less(dividend, divisor, dividendSize, divisorSize))
    {
        quotient = { 0 };
        return;
    }

    quotientSize = dividendSize - divisorSize;

    remainderSize = dividendSize;
    for (size_t i = 0; i < dividendSize; ++i)
        remainder[i] = dividend[i];

    int buffer[arraySize] = {};
    int bufferSize = dividendSize;
    for (int i = dividendSize - divisorSize, j = 0; i <= dividendSize; ++i, ++j)
        buffer[i] = divisor[j];

    if (less(dividend, buffer, dividendSize, bufferSize))
        divideBy10(buffer, bufferSize);
    else
        quotientSize++;

    for (int quoientIndex = quotientSize - 1; quoientIndex >= 0; --quoientIndex)
    {
        while (!less(remainder, buffer, remainderSize, bufferSize))  //remainder >= buffer
        {
            subtraction(remainder, buffer, remainderSize, bufferSize);
            quotient[quoientIndex]++;

            if (isZero(remainder, remainderSize))
                return;
        }

        divideBy10(buffer, bufferSize);
    }
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size )
{
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      size--;
      hugeInt[ size ] = 0;
   }
}