#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    bx.buf[mySize] = '\0';
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    mySize = count;

    if (mySize <= 15)
    {
        for (size_type i = 0; i < mySize; i++)
            bx.buf[i] = ptr[i];

        bx.buf[mySize] = '\0';
    }
    else
    {
        myRes = mySize / 16 * 16 + 15;
        bx.ptr = new value_type[myRes + 1];

        for (size_type i = 0; i < mySize; i++)
            bx.ptr[i] = ptr[i];

        bx.ptr[mySize] = '\0';
    }
}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    mySize = count;

    if (mySize <= 15)
    {
        for (size_type i = 0; i < mySize; i++)
            bx.buf[i] = ch;

        bx.buf[mySize] = '\0';
    }
    else   //need to use bx.ptr
    {
        myRes = mySize / 16 * 16 + 15;
        bx.ptr = new value_type[myRes + 1];

        for (size_type i = 0; i < mySize; i++)
            bx.ptr[i] = ch;

        bx.ptr[mySize] = '\0';
    }

    //pointer s = new value_type[count]{ch};        //clean code possibility use assign
    //string output(s, count);
    //mySize = output.mySize;
    //myRes = output.myRes;
    //bx = output.bx;
}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
    mySize = right.mySize;

    if (mySize <= 15)
    {
        for (size_type i = 0; i < mySize; i++)
            bx.buf[i] = right.bx.buf[i];

        bx.buf[mySize] = '\0';
    }
    else   //need to use bx.ptr
    {
        myRes = mySize / 16 * 16 + 15;
        bx.ptr = new value_type[myRes + 1];

        for (size_type i = 0; i < mySize; i++)
            bx.ptr[i] = right.bx.ptr[i];

        bx.ptr[mySize] = '\0';
    }
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

string& string::assign( const string &right )
{
    mySize = right.mySize;

    if (myRes >= right.mySize)
    {
        for (size_type i = 0; i < mySize; i++)
            myPtr()[i] = right.myPtr()[i];
    }
    else
    {
        size_type count = (mySize / 16 * 16 + 15 > myRes * 3 / 2) ? mySize / 16 * 16 + 15 : myRes * 3 / 2;
        pointer v = new value_type[count]{ 0 };

        for (size_type i = 0; i < right.mySize; i++)
            *(v + i) = right.myPtr()[i];

        bx.ptr = v;
        //delete[] v;

        myRes = count;
    }

   return *this;
}

string::iterator string::insert( const_iterator where, const char ch )
{
   if( where < myPtr() || where > myPtr() + mySize )
      return iterator( nullptr );

   if (bx.ptr == NULL)
       bx.ptr = new value_type[1]{ 0 };

   size_type index = static_cast<size_type>(where - myPtr());
   mySize++;

   if (mySize <= myRes)  //using bx.buf case
   {
       for (size_type i = mySize - 1; i > index; i--)
           myPtr()[i] = myPtr()[i - 1];

       myPtr()[index] = ch;
   }
   else //using bx.ptr case
   {
       int count = ((mySize / 16 * 16) + 15 > myRes * 3 / 2) ? (mySize / 16 * 16) + 15 : myRes * 3 / 2;
       pointer v = new value_type[count]{ 0 };

       for (size_type i = 0; i < index; i++)
           *(v + i) = myPtr()[i];

       *(v + index) = ch;

       for (size_t i = index + 1; i < mySize; i++)
           *(v + i) = myPtr()[i - 1];

       myRes = count;
       //delete[] bx.ptr;
       bx.ptr = v;
   }
}

string::iterator string::erase( const_iterator where )
{
   if( where >= myPtr() && where < myPtr() + mySize )
   {
       size_type index = static_cast<size_type>(where - myPtr());

       for (size_type i = index; i < mySize; i++)
           myPtr()[i] = myPtr()[i + 1];

       mySize--;
   }
   else
      return iterator( nullptr );
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::element( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::element( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}