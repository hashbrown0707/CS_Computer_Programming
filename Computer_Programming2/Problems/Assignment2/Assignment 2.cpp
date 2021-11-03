// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <string>
#include "string.h"

void testFromBufferConstructor();
void testFillConstructor();
void testCopyConstructor();
void testAssignment1();
void testAssignment2();
void testInsert1();
void testInsert2();
void testString();

// return true iff left == right
bool equal( string &left, std::string &right );

const unsigned int number = 1000;

int main()
{
   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testFromBufferConstructor();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testFillConstructor();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testCopyConstructor();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testAssignment1();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testAssignment2();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testInsert1();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testInsert2();
   }

   for( unsigned int seed = 1; seed <= 5; seed++ )
   {
      srand( seed );
      testString();
   }

   cout << endl;

   system( "pause" );
}

void testFromBufferConstructor()
{
   unsigned int numErrors = number;
   unsigned int length;
   char s[ 100 ];
   for( unsigned int i = 0; i < number; i++ )
   {
      length = 1 + rand() % 50;
      for( unsigned int i = 0; i < length; i++ )
         s[ i ] = static_cast< char >( 97 + rand() % 26 );
      s[ length ] = '\0';

      string string1( s, length );
      std::string string2( s, length );
      if( equal( string1, string2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testFillConstructor()
{
   unsigned int numErrors = number;
   unsigned int length;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      length = rand() % 200;
      value = static_cast< char >( 97 + rand() % 26 );
      string string1( length, value );
      std::string string2( length, value );

      if( equal( string1, string2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testCopyConstructor()
{
   unsigned int numErrors = number;
   unsigned int length;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      string string1;
      std::string string2;
      length = rand() % 200;
      for( unsigned int j = 0; j < length; j++ )
      {
         value = static_cast< char >( 97 + rand() % 26 );
         string1.insert( string1.end(), value );
         string2.insert( string2.end(), value );
      }

      string string3( string1 );
      std::string string4( string2 );

      if( equal( string3, string4 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment1()
{
   string string3;
   std::string string4;

   unsigned int numErrors = number;
   unsigned int length;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      string string1;
      std::string string2;
      length = rand() % 200;
      for( unsigned int j = 0; j < length; j++ )
      {
         value = static_cast< char >( 97 + rand() % 26 );
         string1.insert( string1.end(), value );
         string2.insert( string2.end(), value );
      }

      string3.assign( string1 );
      string4.assign( string2 );

      if( equal( string3, string4 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment2()
{
   unsigned int numErrors = number;
   unsigned int length;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      length = rand() % 200;
      value = static_cast< char >( 97 + rand() % 26 );
      string string1( length, value );

      length = rand() % 200;
      value = static_cast< char >( 97 + rand() % 26 );
      string string2( length, value );

      size_t capacity1 = string1.capacity();
      string::pointer oldAddress = string1.begin(); // oldAddress = string1.myPtr()

      string1.assign( string2 );

      if( string2.size() > capacity1 )
         numErrors--;
      else
         if( string1.begin() == oldAddress )
            numErrors--;
   }

   // string1.begin() == oldAddress if and only if
   // the array pointed by string1.bx.ptr before
   // the excution of string1.assign( string2 ) is the same as
   // the array pointed by string1.bx.ptr after
   // the excution of string1.assign( string2 )
   // i.e., there is no memory allocation during
   // the excution of string1.assign( string2 )

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert1()
{
   string string1;
   std::string string2;

   unsigned int numErrors = number;
   unsigned int position;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      position = rand() % ( string1.size() + 1 );
      value = static_cast< char >( 97 + rand() % 26 );
      string1.insert( string1.begin() + position, value );
      string2.insert( string2.begin() + position, value );

      if( equal( string1, string2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert2()
{
   string str;

   unsigned int numErrors = number;
   unsigned int position;
   char value;
   for( unsigned int i = 0; i < number; i++ )
   {
      size_t oldSize = str.size();
      size_t oldCapacity = str.capacity();

      char *oldAddress = str.begin(); // oldAddress = str.myPtr()

      position = rand() % ( str.size() + 1 );
      value = static_cast< char >( 97 + rand() % 26 );
      str.insert( str.begin() + position, value );

      char *newAddress = str.begin(); // newAddress = str.myPtr()

      if( oldSize == oldCapacity )
         numErrors--;
      else
         if( newAddress == oldAddress )
            numErrors--;
   }

   // newAddress == oldAddress if and only if
   // the array pointed by str.bx.ptr before
   // the excution of str.insert( str.begin() + position, value ) is the same as
   // the array pointed by str.bx.ptr after
   // the excution of str.insert( str.begin() + position, value )
   // i.e., there is no memory allocation during the excution of
   // str.insert( str.begin() + position, value )

   cout << "There are " << numErrors << " errors.\n";
}

void testString()
{
   string str1;
   std::string str2;

   unsigned int numErrors = number;
   unsigned int position;
   char c;
   unsigned int choice;
   for( unsigned int i = 0; i < number; i++ )
   {
      choice = rand() % 3;
      switch( choice )
      {
      case 0:
      case 1:
         // Randomly generates a lower-case letter of English.
         c = static_cast< char >( 97 + rand() % 26 );
         position = rand() % ( str2.size() + 1 );
         str1.insert( str1.begin() + position, c ); // Inserts c into str1 right before the position.
         str2.insert( str2.begin() + position, c ); // Inserts c into str2 right before the position.
         break;
      case 2:
         if( !str2.empty() )
         {
            position = rand() % str2.size();
            str1.erase( str1.begin() + position ); // Erases the character of str1 at the position.
            str2.erase( str2.begin() + position ); // Erases the character of str2 at the position.
         }
         break;
      }

      if( equal( str1, str2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// return true iff left == right
bool equal( string &left, std::string &right )
{
   if( left.capacity() != right.capacity() )
      return false;

   if( left.size() != right.size() )
      return false;

   for( size_t i = 0; i < right.size(); i++ )
      if( left.element( i ) != right[ i ] )
         return false;

   return true;
}