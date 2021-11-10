// vector< Term > division provided that the quotient and remainder have integer coefficients

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <fstream>
using std::istream;
using std::ifstream;
using std::ios;

#include <vector>
using std::vector;

struct Term
{
	int coef = 0;  // the coefficient of a term
	int expon = 0; // the exponent of a term
};

// term1 =m term2
void assign(Term& term1, const Term& term2);

// enable user to input a polynomial
void input(istream& inFile, vector< Term >& polynomial);

// outputs the specified polynomial
void output(const vector< Term >& polynomial);

// returns true if and only if the specified polynomial has at least a zero term
bool hasZeroTerm(const vector< Term >& polynomial);

// returns true if and only if polynomial1 == polynomial2
bool equal(const vector< Term >& polynomial1, const vector< Term >& polynomial2);

// polynomial1 = -polynomial2
void minus(vector< Term >& polynomial1, const vector< Term >& polynomial2);

// addend += adder
void addition(vector< Term >& addend, const vector< Term > adder);

// minuend -= subtrahend
void subtraction(vector< Term >& minuend, const vector< Term >& subtrahend);

// product = multiplicand * multiplier
void multiplication(const vector< Term >& multiplicand, const vector< Term >& multiplier, vector< Term >& product);

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division(const vector< Term >& dividend, const vector< Term >& divisor,
	vector< Term >& quotient, vector< Term >& remainder);

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
	ifstream inFile("Polynomials.dat", ios::in | ios::binary);

	// exit program if ifstream could not open file
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	vector< Term > dividend;
	vector< Term > divisor;
	vector< Term > quotient;
	vector< Term > remainder;
	vector< Term > buffer;

	int numErrors = numTestCases;
	for (int i = 0; i < numTestCases; i++)
	{
		// input dividend and divisor from the file vector< Term >s.dat
		input(inFile, dividend);
		input(inFile, divisor);
		/**/
		cout << "dividend:  ";
		output(dividend);

		cout << " divisor:  ";
		output(divisor);

		// quotient = dividend / divisor; remainder = dividend % divisor
		// thus, dividend == divisor * quotient + remainder
		division(dividend, divisor, quotient, remainder);

		/**/
		cout << "quotient:  ";
		output(quotient);
		cout << endl;


		if (hasZeroTerm(quotient))
			cout << "quotient has at least a zero term!\n";
		else
		{
			// buffer = divisor * quotient
			multiplication(divisor, quotient, buffer);

			if (hasZeroTerm(buffer))
				cout << "buffer has at least a zero term!\n";
			else
			{
				// buffer = buffer + remainder = divisor * quotient + remainder
				addition(buffer, remainder);

				if (hasZeroTerm(buffer))
					cout << "buffer has at least a zero term!\n";
				else
					// if buffer != dividend, an error occurred!
					if (equal(buffer, dividend))
						numErrors--;
					else
					{
						cout << "���{\n";
						output(buffer);
					}
			}
		}
	}

	inFile.close();

	cout << "There are " << numErrors << " errors!\n\n";

	system("pause");
}

void assign(Term& term1, const Term& term2)
{
	term1.coef = term2.coef;
	term1.expon = term2.expon;
}

// enable user to input a polynomial
void input(istream& inFile, vector< Term >& polynomial)
{
	int numericString[arraySize] = {};

	inFile.read(reinterpret_cast<char*>(numericString), 80);

	int size = arraySize;
	while (size > 0 && numericString[size - 1] == 0)
		size--;

	polynomial.resize(size);
	for (size_t i = 0; i < polynomial.size(); ++i)
		polynomial[i].coef = numericString[i];

	inFile.read(reinterpret_cast<char*>(numericString), 80);

	for (size_t i = 0; i < polynomial.size(); ++i)
		polynomial[i].expon = numericString[i];
}

// outputs the specified polynomial
void output(const vector< Term >& polynomial)
{
	// the specified polynomial is zero polynomial
	if (polynomial.size() == 0)
		cout << 0;
	else
	{
		if (polynomial[0].coef < 0)
			cout << "-" << -polynomial[0].coef;
		else if (polynomial[0].coef > 0)
			cout << polynomial[0].coef;

		if (polynomial[0].expon > 0)
		{
			if (polynomial[0].expon == 1)
				cout << "x";
			else
				cout << "x^" << polynomial[0].expon;
		}

		for (size_t i = 1; i < polynomial.size(); i++)
		{
			if (polynomial[i].coef < 0)
				cout << " - " << -polynomial[i].coef;
			else if (polynomial[i].coef > 0)
				cout << " + " << polynomial[i].coef;

			if (polynomial[i].expon > 0)
			{
				if (polynomial[i].expon == 1)
					cout << "x";
				else
					cout << "x^" << polynomial[i].expon;
			}
		}
	}

	cout << endl;
}

// returns true if and only if the specified polynomial has at least a zero term
bool hasZeroTerm(const vector< Term >& polynomial)
{
	if (polynomial.size() != 0)
		for (size_t i = 0; i < polynomial.size(); i++)
			if (polynomial[i].coef == 0)
				return true;

	return false;
}

// returns true if and only if polynomial1 == polynomial2
bool equal(const vector< Term >& polynomial1, const vector< Term >& polynomial2)
{
	if (polynomial1.size() != polynomial2.size())
		return false;

	for (size_t i = 0; i < polynomial1.size(); i++)
		if (polynomial1[i].coef != polynomial2[i].coef ||
			polynomial1[i].expon != polynomial2[i].expon)
			return false;

	return true;
}

// polynomial1 = -polynomial2
void minus(vector< Term >& polynomial1, const vector< Term >& polynomial2)
{
	polynomial1.resize(polynomial2.size());
	for (size_t i = 0; i < polynomial1.size(); i++)
	{
		polynomial1[i].coef = -polynomial2[i].coef;
		polynomial1[i].expon = polynomial2[i].expon;
	}
}

// addend += adder
void addition(vector< Term >& addend, const vector< Term > adder)
{
	vector< Term > sum;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	if (!addend.size())
	{
		for (; j < adder.size(); ++j, ++k)
		{
			//sum.at(k).coef = adder.at(j).coef;
			//sum.at(k).expon = adder.at(j).expon;
			sum.push_back(Term{ adder.at(j).coef, adder.at(j).expon });
		}
	}
	else if (!adder.size())
	{
		for (; i < addend.size(); ++i, ++k)
		{
			//sum.at(k).coef = addend.at(i).coef;
			//sum.at(k).expon = addend.at(i).expon;
			sum.push_back(Term{ addend.at(i).coef, addend.at(i).expon });
		}
	}
	else
	{
		while (true)
		{
			if (addend.at(i).expon > adder.at(j).expon)
			{
				//sum.at(k).coef = addend.at(i).coef;
				//sum.at(k).expon = addend.at(i).expon;
				sum.push_back(Term{ addend.at(i).coef, addend.at(i).expon });
				++i, ++k;
			}
			else if (addend.at(i).expon == adder.at(j).expon)
			{
				if (addend.at(i).coef + adder.at(j).coef == 0)
					++i, ++j;
				else
				{
					//sum.at(k).coef = addend.at(i).coef + adder.at(j).coef;
					//sum.at(k).expon = addend.at(i).expon;
					sum.push_back(Term{ addend.at(i).coef + adder.at(j).coef, addend.at(i).expon });
					++i, ++j, ++k;
				}
			}
			else
			{
				//sum.at(k).coef = adder.at(j).coef;
				//sum.at(k).expon = adder.at(j).expon;
				sum.push_back(Term{ adder.at(j).coef, adder.at(j).expon });
				++j, ++k;
			}

#pragma region Prevent i or j stuck
			if (i >= addend.size())
			{
				for (; j < adder.size(); ++j, ++k)
				{
					//sum.at(k).coef = adder.at(j).coef;
					//sum.at(k).expon = adder.at(j).expon;
					sum.push_back(Term{ adder.at(j).coef, adder.at(j).expon });
				}
				break;
			}
			else if (j >= adder.size())
			{
				for (; i < addend.size(); ++i, ++k)
				{
					//sum.at(k).coef = addend.at(i).coef;
					//sum.at(k).expon = addend.at(i).expon;
					sum.push_back(Term{ addend.at(i).coef, addend.at(i).expon });
				}
				break;
			}
#pragma endregion
		}
	}

	if (addend.size() != k)
		addend.resize(k);

	for (size_t i = 0; i < addend.size(); i++) // addend = sum
		assign(addend[i], sum[i]);
}

// minuend -= subtrahend
void subtraction(vector< Term >& minuend, const vector< Term >& subtrahend)
{
	// buffer = 0
	vector< Term > buffer(subtrahend.size());

	// buffer = -subtrahend
	minus(buffer, subtrahend);

	// minuend = minuend + buffer = minuend - subtrahend
	addition(minuend, buffer);

	if (minuend.size() > 0 && minuend[0].coef == 0)
		cout << "Leading zeroes in minuend not allowed!\n";
}

// product = multiplicand * multiplier
void multiplication(const vector< Term >& multiplicand, const vector< Term >& multiplier, vector< Term >& product)
{
	// product = 0;
	product.clear();

	vector< Term > buffer;

	// if( multiplicand != 0 && multiplier != 0 )
	if (multiplicand.size() != 0 && multiplier.size() != 0)
	{
		for (int i = 0; i < multiplier.size(); ++i)
		{
			for (int j = 0; j < multiplicand.size(); ++j)
			{
				//buffer.at(j).coef = multiplicand.at(j).coef * multiplier.at(i).coef;
				//buffer.at(j).expon = multiplicand.at(j).expon + multiplier.at(i).expon;
				buffer.push_back(Term{ multiplicand.at(j).coef * multiplier.at(i).coef, multiplicand.at(j).expon + multiplier.at(i).expon });
			}

			addition(product, buffer);
			buffer.clear();
		}
	}

	if (product.size() > 0 && product[0].coef == 0)
		cout << "Leading zeroes in product not allowed!\n";
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ]
void division(const vector< Term >& dividend, const vector< Term >& divisor,
	vector< Term >& quotient, vector< Term >& remainder)
{
	remainder = dividend;
	quotient.clear();

	//vector<Term> temp;
	vector<Term>monomial;
	vector<Term>buffer;

	while (remainder.size() > 0 && remainder.at(0).expon >= divisor.at(0).expon)
	{
		//temp.at(quotient.size()).coef = remainder.at(0).coef / divisor.at(0).coef;
		//temp.at(quotient.size()).expon = remainder.at(0).expon - divisor.at(0).expon;
		quotient.push_back(Term{ remainder.at(0).coef / divisor.at(0).coef, remainder.at(0).expon - divisor.at(0).expon });

		//monomial.at(0).coef = quotient.at(quotient.size()).coef;
		//monomial.at(0).expon = quotient.at(quotient.size()).expon;
		monomial.push_back(Term{ quotient.at(quotient.size() - 1).coef, quotient.at(quotient.size() - 1).expon });

		multiplication(divisor, monomial, buffer);
		subtraction(remainder, buffer);
		monomial.clear();
	}

	if (quotient.size() > 0 && quotient[0].coef == 0)
		cout << "Leading zeroes in quotient not allowed!\n";

	if (remainder.size() > 0 && remainder[0].coef == 0)
		cout << "Leading zeroes in remainder not allowed!\n";
}