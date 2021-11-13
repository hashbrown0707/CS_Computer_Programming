#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

//#include <vector>
#include "vector.h"
#include "Reservation.h"

class ReservationDatabase
{
public:
   // call loadReservations and removes outdated reservation informations
   ReservationDatabase();

   ~ReservationDatabase(); // call storeReservations

   bool empty(); // returns true if the ReservationDatabase is empty

   // returns true if there is a Reservation object containing specified reservationNumber
   bool exist( string reservationNumber );

   // returns true if there is a Reservation object containing specified reservationNumber and password
   bool legal( string reservationNumber, string password );

   // returns numCustomers in the Reservation object containing specified reservationNumber
   int getNumCustomers( string reservationNumber );

   // returns date in the Reservation object containing specified reservationNumber
   Date getDate( string reservationNumber );

   // returns time in the Reservation object containing specified reservationNumber
   int getTime( string reservationNumber );

   // cancels the Reservation object containing specified reservationNumber,
   void cancelReservation( string reservationNumber );

   // for the Reservation object containing specified reservationNumber,
   // displays all the reservation informations
   void displayReservationInfo( string reservationNumber );

   // adds newReservation at the end of reservations
   void pushBack( Reservation newReservation );

private:
   vector< Reservation > reservations; // vector of all reservations

   void loadReservations();  // loads reservations from the file Reservations.dat
   void storeReservations(); // stores reservations into the file Reservations.dat

   // returns an iterator that points to the Reservation object containing specified reservationNumber
   vector< Reservation >::iterator getReservation( string reservationNumber );
};

#endif // RESERVATION_DATABASE_H