// string class member-function definitions.

#include <iostream>
using std::cout;

#include "string.h" // string class definition

string::string()
   : myData()
{
}

string::string( const char *const ptr, const size_type count )
   : myData()
{


}

string::string( const size_type count, const char ch )
   : myData()
{


}

string::string( const string &right )
   : myData()
{


}

string::~string()
{
   if( myData.myRes > 15 )
      delete[] myData.bx.ptr;
}

string& string::operator=( const string &right )
{
   if( this != &right )
   {


   }

   return *this;
}

string& string::operator=( const char * const ptr )
{


   return *this;
}

string& string::erase( size_t off, size_t count )
{
   if( off < myData.mySize )
   {


   }

   return *this;
}

void string::clear()
{
   myData.mySize = 0;
   myData.myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return iterator( myData.myPtr() );
}

string::const_iterator string::begin() const
{
   return const_iterator( myData.myPtr() );
}

string::iterator string::end()
{
   return iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
}

string::const_iterator string::end() const
{
   return const_iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
}

string::reference string::operator[]( size_type off )
{
   // check for off out-of-range error
   if( off > myData.mySize )
   {
      cout << "\nstring subscript out of range\n";
      system( "pause" );
      exit( 1 ); // terminate program; off out of range
   }

   return myData.myPtr()[ off ]; // returns copy of this element
}

string::const_reference string::operator[]( size_type off ) const
{
   // check for off out-of-range error
   if( off > myData.mySize )
   {
      cout << "\nstring subscript out of range\n";
      system( "pause" );
      exit( 1 ); // terminate program; off out of range
   }

   return myData.myPtr()[ off ]; // returns copy of this element
}

string::const_pointer string::data() const
{
   return myData.myPtr();
}

string::size_type string::size() const
{
   return myData.mySize;
}

string::size_type string::find( char ch, size_type off ) const
{


}

string string::substr( size_type off, size_type count ) const
{


}

// compare [ 0, size() ) with right for equality
bool string::equal( const string &right ) const
{


}

bool operator==( const string &left, const string &right )
{
   return left.equal( right );
//   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=( const string &left, const string &right )
{
   return !left.equal( right );
}

ostream& operator<<( ostream &ostr, string &str )
{
   for( size_t i = 0; i < str.size(); i++ )
      ostr << str.data()[ i ];

   return ostr; // enables cout << x << y;
}