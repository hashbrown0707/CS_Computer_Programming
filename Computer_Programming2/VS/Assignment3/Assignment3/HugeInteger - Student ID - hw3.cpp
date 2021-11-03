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
    if (this->integer.size() != right.integer.size())
        return false;

    for (size_t i = 0; i < this->integer.size(); i++)
        if (*(this->integer.begin() + i) != *(right.integer.begin() + i))
            return false;
    
    return true;
} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less( const HugeInteger &right ) const
{
    if (this->integer.size() < right.integer.size())
        return true;

    if (this->integer.size() == right.integer.size())
        for (size_t i = 1; i <= integer.size(); i++)
            if (*(this->integer.end() - i) < *(right.integer.end() - i))
                return true;
            else if (*(this->integer.end() - i) == *(right.integer.end() - i))
                continue;
            else break;

    return false;
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
   HugeInteger op2Copy(this->integer.size());
   op2Copy.assign(op2);

   vector::iterator it1 = difference.integer.begin();
   vector::iterator it2 =  op2Copy.integer.begin();
   vector::pointer diffSize = difference.integer.begin();  //差的最高位數

   for (; it1 != difference.integer.end(); it1++, it2++)
   {
       *it1 -= *it2;
       if (*it1 != 0) diffSize = it1;
   }

   vector::iterator it3 = difference.integer.begin();
   for (; it3 != difference.integer.end(); it3++)
   {
       if (*it3 < 0)
       {
           if (*(diffSize) > 0)  //the difference is postive
           {
               *it3 += 10;
               (*(it3 + 1))--;
           }
           else if(it3 != diffSize)  //the difference is negative
               *it3 = abs(*it3);
       }
   }

   vector::iterator it4 = difference.integer.end() - 1;
   for (; it4 > difference.integer.begin(); it4--)
       if (*it4 == 0)
           difference.integer.erase(it4);
       else
           break;

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
   HugeInteger temp(productSize);
   
   vector::iterator it1 = op2.integer.begin();

   for (size_t i = 0; it1 != op2.integer.end(); it1++, i++)  //i => 位數
   {
       for (size_t j = 0; j < *it1; j++)   //temp += this 做 *it1 次
           temp.assign(temp.add(*this));

       for (size_t k = 0; k < i; k++)
           if(temp.integer.capacity() > temp.integer.size())
                temp.integer.insert(temp.integer.begin(), 0);

        product.assign(product.add(temp));  //product += temp;
        temp.integer.clear();
   }

   vector::iterator it2 = product.integer.end() - 1;
   for (; *it2 == 0; it2--)
       product.integer.erase(it2);

   return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide( HugeInteger &op2 )
{
   HugeInteger zero;

   if (less(op2))
      return zero;

   unsigned int thisSize = static_cast<unsigned int>(this->integer.size());
   HugeInteger quotient(thisSize);
   HugeInteger remainder(*this);
   HugeInteger buffer(op2);

   unsigned int n = this->integer.size() - op2.integer.size();

   for (; n > 0; n--)
       buffer.integer.insert(buffer.integer.begin(), 0);

   vector::iterator it1 = quotient.integer.end() - op2.integer.size();
   for (; it1 >= quotient.integer.begin(); it1--)
   {
       while (buffer.lessEqual(remainder))
       {
           remainder.assign(remainder.subtract(buffer));
           (*(it1))++;
           if (remainder.isZero())
           {
               vector::iterator it2 = quotient.integer.end() - 1;
               for (; *it2 == 0; it2--)
                   quotient.integer.erase(it2);

               return quotient;
           }
       }

        buffer.divideByTen();
   }

   vector::iterator it2 = quotient.integer.end() - 1;
   for (; *it2 == 0; it2--)
       quotient.integer.erase(it2);

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