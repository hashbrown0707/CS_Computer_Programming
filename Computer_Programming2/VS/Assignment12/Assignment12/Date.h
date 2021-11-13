// Date.h
// Date class definition.
#ifndef DATA_H
#define DATA_H

#include <ostream>
using std::ostream;

class Date
{
   friend ostream& operator<<( ostream &, const Date & );
public:
   Date();
   Date( int y, int m, int d );
   const Date &operator=( const Date & ); // assignment operator
   void setDate( int, int, int ); // set month, day, year
   void setYear( int );
   void setMonth( int );
   void setDay( int );
   int getYear() const;
   int getMonth() const;
   int getDay() const;
   bool operator==( const Date &date2 );
   bool operator<( const Date &date2 );
   bool operator<=( const Date &date2 );
   bool leapYear( int ) const;
   int operator-( const Date &date2 );
   Date operator+( int numDays );

private:
	int year;
	int month;
   int day;
};

#endif // DATA_H