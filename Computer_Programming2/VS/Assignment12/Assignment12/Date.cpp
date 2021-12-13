// Date.cpp
// Date-function definitions for class Date.
#include <iostream>
#include <iomanip>
using namespace std;

#include "Date.h"

int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // array of days per month

extern bool leapYear( int year );

Date::Date()
{
   year = 2000;
   month = 0;
   day = 0;
}

Date::Date( int y, int m, int d )
{
   setDate( y, m, d );
}

// const return avoids: ( a1 = a2 ) = a3
const Date &Date::operator=( const Date &right )
{
   if( &right != this ) // avoid self-assignment
   {
      month = right.month;
      day = right.day;
      year = right.year;
   }

   return *this; // enables x = y = z, for example
} // end function operator=

void Date::setDate( int y, int m, int d )
{
   setYear( y );
   setMonth( m );
   setDay( d );
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000; // sets year
} // end function setYear

void Date::setMonth( int m )
{
   month = ( m >= 1 && m <= 12 ) ? m : 1; // sets month
} // end function setMonth

void Date::setDay( int d )
{
   if( month == 2 && leapYear( year ) )
      day = ( d >= 1 && d <= 29 ) ? d : 1;
   else
      day = ( d >= 1 && d <= days[ month ] ) ? d : 1;
} // end function setDay

int Date::getYear() const
{
   return year;
}

int Date::getMonth() const
{
   return month;
}

int Date::getDay() const
{
   return day;
}

bool Date::operator==( const Date &date2 )
{
   return ( year == date2.year && month == date2.month && day == date2.day );
}

bool Date::operator<( const Date &date2 )
{
   if( year < date2.year )
      return true;
   if( year > date2.year )
      return false;

   if( month < date2.month )
      return true;
   if( month > date2.month )
      return false;

   if( day < date2.day )
      return true;

   return false;
}

bool Date::operator<=( const Date &date2 )
{
   return ( *this < date2 || *this == date2 );
}

// if the year is a leap year, return true; otherwise, return false
bool Date::leapYear( int testYear ) const
{
   if( testYear % 400 == 0 ||
      ( testYear % 100 != 0 && testYear % 4 == 0 ) )
      return true; // a leap year
   else
      return false; // not a leap year
} // end function leapYear

// return *this - date2 provided that *this > date2
int Date::operator-( const Date &date2 )
{
    int y, m, d;

    y = this->getYear() - date2.getYear();
    m = this->getMonth() - date2.getMonth();
    d = this->getDay() - date2.getDay();

    if (d < 0)
    {
        d += days[date2.getMonth()];
        --m;
    }

    if (m <= 0)
    {
        m += 12;
        --y;
    }

    for (size_t i = y; i > 0; --i)
        if (leapYear(date2.getYear() - y))
            d += 365;
        else
            d += 366;

    for (size_t i = m; i > 0; --i)
        d += days[i];

    return d;
}

Date Date::operator+( int numDays )
{
    Date sum;

    int y, m, d;

    d = this->getDay() + numDays;
    m = this->getMonth();
    y = this->getYear();

    while (d > days[m])
    {
        d -= days[m];
        ++m;

        if (m > 12)
        {
            m -= 12;
            ++y;
        }
    }

    return Date(y, m, d);
}

// overloaded output operator
ostream& operator<<( ostream &output, const Date &d )
{
   output << setw( 4 ) << d.year << "/" << setfill( '0' ) << setw( 2 ) << d.month
                                                   << '/' << setw( 2 ) << d.day;
   return output; // enables cascading
} // end function operator<<