// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include <iostream>
#include "list.h" // include definition of class vector 

using namespace std;

template< typename T >
class HugeInteger
{
	template< typename T >
	friend ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger);
public:
	HugeInteger(unsigned int n = 0); // constructor; construct a zero HugeInteger with size n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger& integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger& operator=(const HugeInteger& right); // assignment operator

	// assign right to integer, i.e., integer = right
	void operator=(T& right);

	bool operator==(HugeInteger& right); // less than or equal to

	bool operator<(HugeInteger& right);  // less than

	bool operator<=(HugeInteger& right); // less than or equal to

	// addition operator; HugeInteger + HugeInteger
	HugeInteger operator+(HugeInteger& op2);

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	HugeInteger operator-(HugeInteger& op2);

	// multiplication operator; HugeInteger * HugeInteger
	HugeInteger operator*(HugeInteger& op2);

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(HugeInteger& op2);

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(HugeInteger& op2);

	HugeInteger& operator++(); // prefix increment operator

	HugeInteger operator++(int); // postfix increment operator

	HugeInteger& operator--(); // prefix decrement operator

	HugeInteger operator--(int); // postfix decrement operator

	bool isZero();           // return true if and only if all digits are zero
private:
	T integer;

	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: integer((n == 0) ? 1 : n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger& right)
{
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

template< typename T >
void HugeInteger< T >::operator=(T& right)
{
	integer = right;
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return (integer == right.integer);
} // end function operator==

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
{
	if (this->integer.size() < right.integer.size())
		return true;

	typename T::iterator it1 = this->integer.end()->prev;
	typename T::iterator it2 = right.integer.end()->prev;

	if (this->integer.size() == right.integer.size())
		for (; it1 != this->integer.end(); it1 = it1->prev, it2 = it2->prev)
			if (it1->myVal < it2->myVal)
				return true;
			else if (it1->myVal == it2->myVal)
				continue;
			else break;

	return false;
} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger& right)
{
	return (*this == right || *this < right);
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger& op2)
{
	size_t op1Size = integer.size();
	size_t op2Size = op2.integer.size();
	size_t sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	typename T::iterator it1 = integer.begin();
	typename T::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); it1 = it1->next, it3 = it3->next)
		it3->myVal = it1->myVal;

	typename T::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); it2 = it2->next, it3 = it3->next)
		it3->myVal += it2->myVal;

	for (it3 = sum.integer.begin(); it3 != sum.integer.end()->prev; it3 = it3->next)
		if (it3->myVal > 9)
		{
			it3->myVal -= 10;
			((it3->next)->myVal)++;
		}

	if (it3->myVal == 0)
		sum.integer.erase(sum.integer.end()->prev);

	return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger& op2)
{
	HugeInteger zero;

	if (*this == op2)
		return zero;

	HugeInteger difference(*this);
	HugeInteger buffer(op2);

	typename T::iterator it1 = difference.integer.begin();
	typename T::iterator it2 = buffer.integer.begin();

	for (; it1 != difference.integer.end() && it2 != buffer.integer.end(); it1 = it1->next, it2 = it2->next)
	{
		int temp1 = static_cast<int>(it1->myVal);
		int temp2 = static_cast<int>(it2->myVal);

		if (temp1 - temp2 < 0)
		{
			it1->myVal += 10;

			typename T::iterator it3 = it1->next;
			while (it3->myVal == 0)
			{
				it3->myVal = 9;
				it3 = it3->next;
			}

			it3->myVal--;
		}

		it1->myVal -= it2->myVal;
	}

	typename T::iterator it4 = difference.integer.end()->prev;
	while (it4 != difference.integer.begin())
	{
		it4 = it4->prev;

		if (it4->next->myVal == 0)
			difference.integer.erase(it4->next);
		else
			break;
	}

	return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger& op2)  ////
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	HugeInteger product(integer.size() + op2.integer.size());
	HugeInteger temp(integer.size() + op2.integer.size());

	typename T::iterator it1 = op2.integer.begin();

	for (size_t i = 0; it1 != op2.integer.end(); it1 = it1->next, i++)  //i => 位數
	{
		for (size_t j = 0; j < it1->myVal; j++)   //temp += this 做 *it1 次
			temp = temp + (*this);

		for (size_t k = 0; k < i; k++)
			temp.integer.insert(temp.integer.begin(), 0);      //if (temp.integer.capacity() > temp.integer.size())

		product = product + temp;  //product += temp;
		temp.integer.clear();
	}

	typename T::iterator it2 = product.integer.end();
	while (it2->prev->myVal == 0)
		product.integer.erase(it2->prev);
	

	return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;

	unsigned int thisSize = static_cast<unsigned int>(this->integer.size());
	HugeInteger quotient(thisSize);
	HugeInteger remainder(*this);
	HugeInteger buffer(op2);

	unsigned int n = this->integer.size() - op2.integer.size();

	for (; n > 0; n--)
		buffer.integer.insert(buffer.integer.begin(), 0);

	typename T::iterator it1 = quotient.integer.end();

	for (size_t i = 0; i < op2.integer.size(); i++, it1 = it1->prev);

	for (; it1 != quotient.integer.end(); it1 = it1->prev)
	{
		while (buffer <= remainder)
		{
			remainder = remainder - buffer;
			it1->myVal++;
			if (remainder.isZero())
			{
				typename T::iterator it2 = quotient.integer.end();
				while (it2->prev->myVal == 0)
					quotient.integer.erase(it2->prev);

				return quotient;
			}
		}

		buffer.divideByTen();
	}

	typename T::iterator it2 = quotient.integer.end();
	while (it2->prev->myVal == 0)
		quotient.integer.erase(it2->prev);

	return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger& op2)
{
	HugeInteger quotient = (*this) / op2;
	HugeInteger product = quotient * op2;
	HugeInteger remainder = (*this) - product;
	return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
	helpIncrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++(int)
{
	HugeInteger temp = *this; // hold current state of object
	helpIncrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
	helpDecrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--(int)
{
	HugeInteger temp = *this; // hold current state of object
	helpDecrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	typename T::iterator it = integer.begin();
	for (; it != integer.end(); it = it->next)
		if (it->myVal != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename T::iterator it = integer.begin()->next;
	for (; it != integer.end(); it = it->next)
		(it->prev)->myVal = it->myVal;
	integer.erase(integer.end()->prev);
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	typename T::iterator it = integer.begin();
	(it->myVal)++;
	typename T::iterator it2 = it;
	for (it2 = it2->next; it2 != integer.end(); it = it->next, it2 = it2->next)
		if (it->myVal == 10)
		{
			it->myVal = 0;
			(it2->myVal)++;
		}

	if ((it->myVal) == 10)
	{
		it->myVal = 0;
		integer.insert(integer.end(), 1);
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename T::iterator it = integer.begin();
	for (; it->myVal == 0; it = it->next)
		it->myVal = 9;

	(it->myVal)--;

	if (!isZero() && integer.back() == 0)
		integer.erase(integer.end()->prev);
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	typename T::iterator it = hugeInteger.integer.end()->prev;
	for (; it != hugeInteger.integer.begin()->prev; it = it->prev)
		if (it->myVal < 10)
			output << it->myVal;

	return output; // enables cout << x << y;
}

#endif