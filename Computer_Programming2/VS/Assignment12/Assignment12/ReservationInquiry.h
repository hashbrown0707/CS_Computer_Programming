#ifndef RESERVATION_INQUIRY_H
#define RESERVATION_INQUIRY_H

#include "ReservationDatabase.h"
#include "AvailTableDatabase.h"

class ReservationInquiry
{
public:
   ReservationInquiry( ReservationDatabase &theReservationDatabase,
                       AvailTableDatabase &theAvailTableDatabase );
   virtual void execute(); // reservation inquiry
private:
   ReservationDatabase &reservationDatabase;
   AvailTableDatabase &availTableDatabase;
};

#endif // RESERVATION_INQUIRY_H