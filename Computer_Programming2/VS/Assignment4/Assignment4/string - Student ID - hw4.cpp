// string class member-function definitions.

#include <iostream>
using std::cout;

#include "string.h" // string class definition

string::string()
   : myData()
{
    myData.bx.buf[myData.mySize] = '\0';
}

string::string( const char *const ptr, const size_type count )
   : myData()
{
    myData.mySize = count;

    if (myData.mySize <= 15)
    {
        for (size_type i = 0; i < myData.mySize; i++)
            myData.bx.buf[i] = ptr[i];

        myData.bx.buf[myData.mySize] = '\0';
    }
    else
    {
        myData.myRes = myData.mySize / 16 * 16 + 15;
        myData.bx.ptr = new value_type[myData.myRes + 1];

        for (size_type i = 0; i < myData.mySize; i++)
            myData.bx.ptr[i] = ptr[i];

        myData.bx.ptr[myData.mySize] = '\0';
    }
}

string::string( const size_type count, const char ch )
   : myData()
{
    myData.mySize = count;

    if (myData.mySize <= 15)
    {
        for (size_type i = 0; i < myData.mySize; i++)
            myData.bx.buf[i] = ch;

        myData.bx.buf[myData.mySize] = '\0';
    }
    else   //need to use bx.ptr
    {
        myData.myRes = myData.mySize / 16 * 16 + 15;
        myData.bx.ptr = new value_type[myData.myRes + 1];

        for (size_type i = 0; i < myData.mySize; i++)
            myData.bx.ptr[i] = ch;

        myData.bx.ptr[myData.mySize] = '\0';
    }
}

string::string( const string &right )
   : myData()
{
    myData.mySize = right.myData.mySize;

    if (myData.mySize <= 15)
    {
        for (size_type i = 0; i < myData.mySize; i++)
            myData.bx.buf[i] = right.myData.bx.buf[i];

        myData.bx.buf[myData.mySize] = '\0';
    }
    else   //need to use bx.ptr
    {
        myData.myRes = myData.mySize / 16 * 16 + 15;
        myData.bx.ptr = new value_type[myData.myRes + 1];

        for (size_type i = 0; i < myData.mySize; i++)
            myData.bx.ptr[i] = right.myData.bx.ptr[i];

        myData.bx.ptr[myData.mySize] = '\0';
    }
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
       for (size_t i = 0; i < myData.mySize; i++)
           myData.myPtr()[i] = '\0';

       myData.mySize = right.myData.mySize;

       if (myData.myRes >= right.myData.mySize)
       {
           for (size_type i = 0; i < right.myData.mySize; i++)
               myData.myPtr()[i] = right.myData.myPtr()[i];
       }
       else
       {
           size_type count = (right.myData.mySize / 16 * 16 + 15 > myData.myRes * 3 / 2) ? right.myData.mySize / 16 * 16 + 15 : myData.myRes * 3 / 2;
           pointer v = new value_type[count]{ 0 };

           for (size_type i = 0; i < right.myData.mySize; i++)
               *(v + i) = right.myData.myPtr()[i];

           myData.bx.ptr = v;
           myData.myRes = count;
       }
   }

   return *this;
}

string& string::operator=( const char * const ptr )
{
    myData.mySize = strlen(ptr);

    if(myData.mySize <= myData.myRes)
        for (size_t i = 0; i < strlen(ptr); i++)
            myData.myPtr()[i] = ptr[i];
    else
    {
        size_t count = (myData.mySize / 16 * 16 + 15 > myData.myRes * 3 / 2) ? myData.mySize / 16 * 16 + 15 : myData.myRes * 3 / 2;
        pointer v = new value_type[count]{ 0 };

        for (size_t i = 0; i < myData.mySize; i++)
            *(v + i) = ptr[i];

        myData.bx.ptr = v;
        myData.myRes = count;
    }

   return *this;
}

string& string::erase( size_t off, size_t count )
{
   if( off < myData.mySize )
   {
       if (count > (myData.mySize - off))  //erase all stuff after off
           myData.myPtr()[off] = '\0';

       for (size_type i = off; (i + count) <= myData.mySize; i++)
            myData.myPtr()[i] = myData.myPtr()[i + count];

       myData.mySize -= count;
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

string::size_type string::find( char ch, size_type off ) const  ////
{
    /*if(off >= myData.mySize)
        return npos;*/

    size_t index = npos;
    
    for (size_t i = off; i < myData.mySize; i++)
        if (*(myData.myPtr() + i) == ch)
            index = i;

    return index;
}

string string::substr( size_type off, size_type count ) const  ////
{
    if (off < myData.mySize)
    {
        string ss(myData.myPtr() + off, count - off);
        return ss;
    }

    string s;
    return s;
}

// compare [ 0, size() ) with right for equality
bool string::equal( const string &right ) const  ////
{
    if (myData.mySize != right.myData.mySize)
        return false;

    for (size_t i = 0; i < right.myData.mySize; i++)
        if (myData.myPtr()[i] != right.myData.myPtr()[i])
            return false;

    return true;
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