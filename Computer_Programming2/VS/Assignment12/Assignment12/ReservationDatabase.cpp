#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace::std;

#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

// call loadReservations and removes outdated reservation informations
ReservationDatabase::ReservationDatabase()
{
   loadReservations();

   Date currentDate = computeCurrentDate();
   vector<Reservation>::iterator it = reservations.begin();

   for (; it != reservations.end(); ++it)
       if (it->getDate() <= currentDate)
           reservations.erase(it);
}

// call storeReservations
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

// returns true if there is a Reservation object containing specified reservationNumber
bool ReservationDatabase::exist( string reservationNumber )
{
    vector<Reservation>::iterator it = reservations.begin();

    for (; it != reservations.end(); ++it)
        if (it->getReservationNumber() == reservationNumber)
            return true;

    return false;
}

// returns true if there is a Reservation object containing specified reservationNumber and password
bool ReservationDatabase::legal( string reservationNumber, string password )
{
    vector<Reservation>::iterator it = reservations.begin();

    for (; it != reservations.end(); ++it)
        if (it->getReservationNumber() == reservationNumber && it->getPassword() == password)
            return true;

    return false;
}

// returns numCustomers in the Reservation object containing specified reservationNumber
int ReservationDatabase::getNumCustomers( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   return it->getNumCustomers();
}

// returns date in the Reservation object containing specified reservationNumber
Date ReservationDatabase::getDate( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   return it->getDate();
}

// returns time in the Reservation object containing specified reservationNumber
int ReservationDatabase::getTime( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   return it->getTime();
}

// cancels the Reservation object containing specified reservationNumber,
void ReservationDatabase::cancelReservation( string reservationNumber )
{
   vector< Reservation >::iterator it = getReservation( reservationNumber );
   reservations.erase( it );
}

// for the Reservation object containing specified reservationNumber,
// displays all the reservation informations
void ReservationDatabase::displayReservationInfo( string reservationNumber )
{
   cout << setfill( ' ' ) << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
        << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
        << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
        << setw( 19 ) << "Reservation No." << endl;

   vector< Reservation >::iterator it = getReservation( reservationNumber );
   it->displayReservationInfo();
}

// adds newReservation at the end of reservations
void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

// loads reservations from the file Reservations.dat
void ReservationDatabase::loadReservations()
{
    ifstream inFile("Reservation.dat", ios::binary);
    Reservation temp;

    if (inFile.is_open())
    {
        while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(Reservation)))
            reservations.push_back(temp);

        inFile.close();
    }
    else
    {
        cout << "Can not open the file" << endl;
        system("pause");
        exit(1);
    }
}

// stores reservations into the file Reservations.dat
void ReservationDatabase::storeReservations()
{
    ofstream outFile("Reservation.dat", ios::binary | ios::app);

    if (outFile.is_open())
    {
        vector<Reservation>::iterator it = reservations.begin();

        for (; it != reservations.end(); ++it)
            outFile.write(reinterpret_cast<char*>(&*it), sizeof(Reservation));

        outFile.close();
    }
    else
    {
        cout << "Can not open the file" << endl;
        system("pause");
        exit(1);
    }
}

// returns an iterator that points to the Reservation object containing specified reservationNumber
vector< Reservation >::iterator ReservationDatabase::getReservation( string reservationNumber )
{
    vector< Reservation >::iterator it = reservations.begin();

    for (; it != reservations.end(); ++it)
        if (it->getReservationNumber() == reservationNumber)
            return it;

    cerr << "iterator is not found";
    return nullptr;
}