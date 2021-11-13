// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition

extern Date computeCurrentDate();

extern bool leapYear( int year );

extern int inputAnInteger( int begin, int end );

// MakeReservation constructor initializes base-class data members
MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
                                  AvailableRoomsDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomsDatabase( theAvailableRoomsDatabase )
{
} // end MakeReservation constructor

// performs transaction
void MakeReservation::execute()
{
   Date currentDate = computeCurrentDate();

   Date availableMonths[ 7 ];
   computeAvailableMonths( currentDate, availableMonths );

   int checkInCode;
   int firstDay;
   int lastDay;

   Date checkInDate;
   Date checkOutDate;

   inputCheckInDate( checkInDate, currentDate, availableMonths, checkInCode, firstDay, lastDay );
   inputCheckOutDate( checkOutDate, checkInDate, availableMonths, checkInCode, firstDay, lastDay );

   cout << "\nCheck in date: " << checkInDate.getYear() << '-'
        << setw( 2 ) << setfill( '0' ) << checkInDate.getMonth() << '-'
        << setw( 2 ) << checkInDate.getDay() << endl;

   cout << "Check out date: " << checkOutDate.getYear() << '-'
        << setw( 2 ) << checkOutDate.getMonth() << '-'
        << setw( 2 ) << checkOutDate.getDay() << endl;

   availableRoomsDatabase.displayAvailableRooms( checkInDate, checkOutDate );

   int roomType;
   do {
      cout << "\nSelect Room Type:\n"
           << "1. Superior Room\n" << "2. Deluxe Room\n" << "3. Deluxe Twin Room\n"
           << "4. Superior Suite\n" << "5. Deluxe Suite\n? ";
   } while( ( roomType = inputAnInteger( 1, 5 ) ) == -1 );

   int minNumRooms = availableRoomsDatabase.findMinNumRooms( roomType, checkInDate, checkOutDate );

   if( minNumRooms == 0 )
   {
      cout << "\nThere are no rooms available!\n";
      return;
   }

   int numRooms;
   do cout << "\nEnter the number of rooms (1 ~ " << minNumRooms << ", 0 to end): ";
   while( ( numRooms = inputAnInteger( 0, minNumRooms ) ) == -1 );
   if( numRooms == 0 )
      return;

   availableRoomsDatabase.decreaseAvailableRooms( roomType, numRooms, checkInDate, checkOutDate );

   cout << "\nID Number: ";
   string IDNumber;
   getline( cin, IDNumber, '\n' );

   cout << "\nName: ";
   string name;
   getline( cin, name, '\n' );

   cout << "\nMobile Phone: ";
   string mobile;
   getline( cin, mobile, '\n' );

   newReservation.setReservation( roomType, numRooms, checkInDate, checkOutDate, IDNumber, name, mobile );

   cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
   newReservation.displayReservation();

   reservationDatabase.pushBack( newReservation );

   cout << "\nReservation successfully!" << endl;
}

void MakeReservation::computeAvailableMonths( Date currentDate, Date availableMonths[] )
{
   int year = currentDate.getYear();
   int month = currentDate.getMonth();
   for( int i = 1; i <= 6; i++ )
   {
      availableMonths[ i ].setYear( year );
      availableMonths[ i ].setMonth( month );

      if( month < 12 )
         month++;
      else
      {
         year++;
         month = 1;
      }
   }
}

const int monthLastDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

void MakeReservation::inputCheckInDate( Date &checkInDate, Date currentDate, Date availableMonths[],
                                        int &checkInCode, int &firstDay, int &lastDay )
{
    cout << "Please Input Check In Date\n Months:\n";

    for (int i = 1; i <= 6; ++i)
        cout << i << ". " << availableMonths[i].getYear() << " - " << availableMonths[i].getMonth() << "\n";

    cin >> checkInCode;

    //compute availDays
    firstDay = currentDate.getDay();

    if(leapYear(currentDate.getYear()) && currentDate.getMonth() == 2)
        lastDay = monthLastDays[currentDate.getMonth()] + 1;
    else
        lastDay = monthLastDays[currentDate.getMonth()];
        

    int d;

    cout << "Day (" << firstDay << " ~ " << lastDay << ") : ";
    cin >> d;

    checkInDate = availableMonths[checkInCode];
    checkInDate.setDay(d);
}

void MakeReservation::inputCheckOutDate( Date &checkOutDate, Date checkInDate, Date availableMonths[],
                                         int checkInCode, int firstDay, int lastDay )
{
    cout << "Please Input Check Out Date\n Month¡G\n";

    //if checkInDate is the last day of month
    if (checkInDate.getDay() == monthLastDays[checkInDate.getMonth()])
    {
        for (int i = 1; i <= 6; ++i)
            cout << i << ". " << availableMonths[i].getYear() << " - " << availableMonths[i].getMonth() + 1 << "\n";

        cin >> checkInCode;

        //compute availDays
        firstDay = 1;

        if (leapYear(checkInDate.getYear()) && checkInDate.getMonth() == 2)
            lastDay = 29;
        else
            lastDay = monthLastDays[checkInDate.getMonth() + checkInCode];

        cout << "Day (" << 1 << " ~ " << lastDay << ") : ";

        checkOutDate = availableMonths[checkInCode + 1];
    }
    else
    {
        for (int i = 1; i <= 6; ++i)
            cout << i << ". " << availableMonths[i].getYear() << " - " << availableMonths[i].getMonth() << "\n";

        cin >> checkInCode;

        //compute availDays
        firstDay = checkInDate.getDay() + 1;

        if (leapYear(checkInDate.getYear()) && checkInDate.getMonth() == 2)
            lastDay = monthLastDays[checkInDate.getMonth()] + 1;
        else
            lastDay = monthLastDays[checkInDate.getMonth()];

        cout << "Day (" << firstDay << " ~ " << lastDay << ") : ";

        checkOutDate = availableMonths[checkInCode];
    }


    int d;
    cin >> d;

    cin.ignore();    //add

    checkOutDate.setDay(d);
}