#include <iostream>
#include <ctime>
using namespace::std;

#include "MakeReservation.h"    // MakeReservation class definition
#include "ReservationInquiry.h" // ReservationInquiry class definition

int inputAnInteger( int begin, int end ); // input an integer in the range [ begin, end ]
Date computeCurrentDate(); // compute current date
bool leapYear( int year ); // if the year is a leap year, return true; otherwise, return false

int main()
{
   cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

   ReservationDatabase reservationDatabase; // reservation information database
   AvailTableDatabase availTableDatabase;   // available table information database

   MakeReservation makeReservation( reservationDatabase, availTableDatabase );
   ReservationInquiry reservationInquiry( reservationDatabase, availTableDatabase );

   bool userExited = false; // user has not chosen to exit
   int choice;

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      cout << "\n1 - Book a Table\n";
      cout << "2 - My Bookings\n";
      cout << "3 - End\n\n";

      do cout << "Enter your choice: (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      // decide how to proceed based on user's menu selection
      switch( choice )
      {
      case 1:
         makeReservation.execute(); // make reservation
         break;
      case 2:
         reservationInquiry.execute(); // reservation inquiry
         break;
      case 3: // user chose to exit
         userExited = true;
         cout << endl;
         break;
      default: // user did not enter an integer from 1-3
         cout << "\nIncorrect choice!" << endl;
      }
   }

   system( "pause" );
}

int inputAnInteger( int begin, int end )
{
    int input;
    cin >> input;

    if (input <= end && input >= begin)
        return input;
    else
        return -1;
}

Date computeCurrentDate()
{
    tm structuredTime;
    time_t rawTime = time(0);
    localtime_s(&structuredTime, &rawTime);

    return Date(structuredTime.tm_year + 1900, structuredTime.tm_mon + 1, structuredTime.tm_mday);
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}