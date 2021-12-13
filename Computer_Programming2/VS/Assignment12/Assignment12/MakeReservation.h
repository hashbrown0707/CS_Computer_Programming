#ifndef MAKE_RESERVATION_H
#define MAKE_RESERVATION_H

#include "ReservationDatabase.h"
#include "AvailTableDatabase.h"

class MakeReservation
{
public:
   MakeReservation( ReservationDatabase &theReservationDatabase,
                    AvailTableDatabase &theAvailTableDatabase );
   virtual void execute(); // make reservation
private:
   ReservationDatabase &reservationDatabase;
   AvailTableDatabase &availTableDatabase;

   void chooseDate( Date &date, Date currentDate, int numCustomers ); // choose a date
   void chooseTime( int &timeCode, Date date, int numCustomers ); // choose a time
};

#endif // MAKE_RESERVATION_H