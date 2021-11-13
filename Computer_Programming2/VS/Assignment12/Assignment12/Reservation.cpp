#include <iostream>
#include <iomanip>
using namespace::std;

#include "Reservation.h" // Reservation class definition

Reservation::Reservation( int theCustomerNumber, Date theDate, int theTime,
                          string theName, string theMobileNumber, string theEmail,
                          string thePassword, string theReservationNumber )
{
   setNumCustomers( theCustomerNumber );
   setDate( theDate );
   setTime( theTime );
   setName( theName );
   setMobileNumber( theMobileNumber );
   setEmail( theEmail );
   setPassword( thePassword );
   setReservationNumber( theReservationNumber );
}

void Reservation::setNumCustomers( int theCustomerNumber )
{
   numCustomers = ( theCustomerNumber >= 0 ? theCustomerNumber : 0 );
}

void Reservation::setDate( Date theDate )
{
   date = theDate;
}

void Reservation::setTime( int theTime )
{
   time = ( theTime >= 0 ? theTime : 0 );
}

void Reservation::setName( string theName )
{
   unsigned int length = theName.size();
   length = ( length < 8 ? length : 7 );
   for( unsigned int i = 0; i < length; i++ )
      name[ i ] = theName[ i ];
   name[ length ] = '\0';
}

void Reservation::setMobileNumber( string theMobileNumber )
{
   unsigned int length = theMobileNumber.size();
   length = ( length < 12 ? length : 11 );
   for( unsigned int i = 0; i < length; i++ )
      mobileNumber[ i ] = theMobileNumber[ i ];
   mobileNumber[ length ] = '\0';
}

void Reservation::setEmail( string theEmail )
{
   unsigned int length = theEmail.size();
   length = ( length < 40 ? length : 39 );
   for( unsigned int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

void Reservation::setPassword( string thePassword )
{
   unsigned int length = thePassword.size();
   length = ( length < 12 ? length : 11 );
   for( unsigned int i = 0; i < length; i++ )
      password[ i ] = thePassword[ i ];
   password[ length ] = '\0';
}

void Reservation::setReservationNumber( string theReservationNumber )
{
   unsigned int length = theReservationNumber.size();
   length = ( length < 12 ? length : 11 );
   for( unsigned int i = 0; i < length; i++ )
      reservationNumber[ i ] = theReservationNumber[ i ];
   reservationNumber[ length ] = '\0';
}

int Reservation::getNumCustomers()
{
   return numCustomers;
}

Date Reservation::getDate()
{
   return date;
}

int Reservation::getTime()
{
   return time;
}

string Reservation::getName()
{
   return name;
}

string Reservation::getMobileNumber()
{
   return mobileNumber;
}

string Reservation::getEmail()
{
   return email;
}

string Reservation::getPassword()
{
   return password;
}

string Reservation::getReservationNumber()
{
   return reservationNumber;
}

// displays mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
void Reservation::displayReservationInfo()
{
   char times[ 4 ][ 8 ] = { "", "11:30", "14:30", "17:30" };
   cout << setfill( ' ' ) << setw( 11 ) << mobileNumber << setw( 10 ) << name << "    " << date
        << setfill( ' ' ) << setw( 9 ) << times[ time ] << setw( 30 ) << email
        << setw( 19 ) << numCustomers << setw( 12 ) << password << setw( 19 ) << reservationNumber << endl;
}