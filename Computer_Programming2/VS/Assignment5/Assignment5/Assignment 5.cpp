#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ios;

#include "vector.h"
#include "Polynomial.h"

void load( ifstream &inFile, int coefficient[], int exponent[], int &numTerms );

const int numTestCases = 200; // the number of test cases
const int arraySize = 20;

int main()
{
   ifstream inFile( "Polynomials.dat", ios::in | ios::binary );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      int coefficient[ arraySize ] = {};
      int exponent[ arraySize ] = {};
      int numTerms;

      load( inFile, coefficient, exponent, numTerms );
      Polynomial< vector< Term > > dividend( numTerms );
      dividend.setPolynomial( coefficient, exponent, numTerms );
      cout << "dividend: " << dividend << endl;

      load( inFile, coefficient, exponent, numTerms );
      Polynomial< vector< Term > > divisor( numTerms );
      divisor.setPolynomial( coefficient, exponent, numTerms );
      cout << " divisor: " << divisor << endl;

      Polynomial< vector< Term > > quotient = dividend / divisor;
      cout << "quotient: " << quotient << endl << endl;

      Polynomial< vector< Term > > remainder = dividend % divisor;
      Polynomial< vector< Term > > buffer = divisor * quotient;

      buffer += remainder;

      if( buffer == dividend )
         numErrors--;
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

void load( ifstream &inFile, int coefficient[], int exponent[], int &numTerms )
{
   inFile.read( reinterpret_cast< char * >( coefficient ), arraySize * sizeof( int ) );
   inFile.read( reinterpret_cast< char * >( exponent ), arraySize * sizeof( int ) );

   numTerms = arraySize;
   while( numTerms > 0 && coefficient[ numTerms - 1 ] == 0 )
      numTerms--;
}