// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
   : integer( 1 )
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger( unsigned int n )
   : integer( ( n > 0 ) ? n : 1 )
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger( const HugeInteger &integerToCopy )
   : integer( integerToCopy.integer )
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::assign( const HugeInteger &right )
{
   if( &right != this ) // avoid self-assignment
      integer.assign( right.integer );

   return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal( const HugeInteger &right ) const
{

} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less( const HugeInteger &right ) const
{

} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual( const HugeInteger &right ) const
{
   return ( less( right ) || equal( right ) );
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add( HugeInteger &op2 )
{
   unsigned int op1Size = integer.size();
   unsigned int op2Size = op2.integer.size();
   unsigned int sumSize = ( op1Size >= op2Size ) ? op1Size + 1 : op2Size + 1;

   HugeInteger sum( sumSize );

   vector::iterator it1 = integer.begin();
   vector::iterator it3 = sum.integer.begin();
   for( ; it1 != integer.end(); ++it1, ++it3 )
      *it3 = *it1;

   vector::iterator it2 = op2.integer.begin();
   for( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
      *it3 += *it2;

   for( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
      if( *it3 > 9 )
      {
         ( *it3 ) -= 10;
         ( *( it3 + 1 ) )++;
      }

   if( *it3 == 0 )
      sum.integer.erase( sum.integer.end() - 1 );

   return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract( HugeInteger &op2 )
{
   HugeInteger zero;

   if( equal( op2 ) )
      return zero;

   HugeInteger difference( *this );


   return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply( HugeInteger &op2 )
{
   HugeInteger zero;
   if( isZero() || op2.isZero() )
      return zero;

   unsigned int productSize = integer.size() + op2.integer.size();
   HugeInteger product( productSize );
   

   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide( HugeInteger &op2 )
{
   HugeInteger zero;
   if( less( op2 ) )
      return zero;


   return quotient;
} // end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus( HugeInteger &op2 )
{
   HugeInteger quotient = divide( op2 );
   HugeInteger product = quotient.multiply( op2 );
   HugeInteger remainder = subtract( product );
   return remainder;
}

// assign a vector of decimal digits into a HugeInteger
void HugeInteger::assign( const vector &v )
{
   integer.assign( v );
} // end function assign

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
   for( vector::iterator it = integer.begin(); it != integer.end(); ++it )
      if ( *it != 0 )
         return false;
         
   return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
   vector::iterator it = integer.begin();
   vector::iterator it2 = it;
   for( ++it2; it2 != integer.end(); ++it, ++it2 )
      *it = *it2;
   integer.erase( integer.end() - 1 );
}

// overloaded output operator
void HugeInteger::output( ostream &outFile )
{
   vector::iterator it = integer.end() - 1;
   for( ; it != integer.begin() - 1; --it )
      if( *it < 10 )
         outFile << *it;
   outFile << endl;
} // end function output