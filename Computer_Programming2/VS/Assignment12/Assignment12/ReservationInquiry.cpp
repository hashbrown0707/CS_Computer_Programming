#include <iostream>
using namespace::std;

#include "ReservationInquiry.h"

extern int inputAnInteger( int begin, int end );

ReservationInquiry::ReservationInquiry( ReservationDatabase &theReservationDatabase,
                                        AvailTableDatabase &theAvailTableDatabase )
   : reservationDatabase( theReservationDatabase ),
     availTableDatabase( theAvailTableDatabase )
{
}

// reservation inquiry
void ReservationInquiry::execute()
{
   if( reservationDatabase.empty() )
   {
      cout << "\nNo reservations!\n";
      return;
   }

#pragma region login
   string reservationNum;
   string password;

   cout << "Enter reservation number: ";
   cin >> reservationNum;

   if (!reservationDatabase.exist(reservationNum))
   {
       cout << "Reservation number doesn't exist";
       return;
   }

   cout << "Enter reservation password: ";
   cin >> password;

   if (reservationDatabase.legal(reservationNum, password))
       reservationDatabase.displayReservationInfo(reservationNum);
   else
   {
       cout << "Password is wrong";
       return;
   }
#pragma endregion

#pragma region delete
   char checkdelete;

   cout << "Cancel this reservation? ( y/n ) ";
   cin >> checkdelete;

   if (checkdelete == 'y')
   {
       availTableDatabase.increaseAvailTables(reservationDatabase.getNumCustomers(reservationNum)
           , reservationDatabase.getDate(reservationNum), reservationDatabase.getTime(reservationNum));
       reservationDatabase.cancelReservation(reservationNum);
       cout << "\nThis reservation has been cancelled.\n";
   }
   else
       return;
#pragma endregion
}