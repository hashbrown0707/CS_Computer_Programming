#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"

class Reservation
{
public:
   Reservation( int theCustomerNumber = 0, Date theDate = Date(), int theTime = 0,
                string theName = "", string theMobileNumber = "", string theEmail = "",
                string thePassword = "", string theReservationNumber = "" );

   void setNumCustomers( int theCustomerNumber );
   void setDate( Date theDate );
   void setTime( int theTime );
   void setName( string theName );
   void setMobileNumber( string theMobileNumber );
   void setEmail( string theEmail );
   void setPassword( string thePassword );
   void setReservationNumber( string theReservationNumber );

   int getNumCustomers();
   Date getDate();
   int getTime();
   string getName();
   string getMobileNumber();
   string getEmail();
   string getPassword();
   string getReservationNumber();

   // displays mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
   void displayReservationInfo();

private:
   int numCustomers = 0;              // number of customers
   Date date = Date();                // reservation date
   int time = 0;                      // reservation time code
   char name[ 8 ] = "";               // name
   char mobileNumber[ 12 ] = "";      // mobile phone number
   char email[ 40 ] = "";             // email address
   char password[ 12 ] = "";          // reservation password
   char reservationNumber[ 12 ] = ""; // reservation number
};

#endif // RESERVATION_H