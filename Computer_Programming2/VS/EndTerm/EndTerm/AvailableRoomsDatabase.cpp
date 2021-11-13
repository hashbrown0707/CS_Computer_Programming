// AvailableRoomsDatabase.cpp
// Member-function definitions for class AvailableRoomsDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailableRoomsDatabase.h" // AvailableRoomsDatabase class definition

extern Date computeCurrentDate();

extern bool leapYear( int year );

extern const int totalNumRooms[ 6 ]; // total number of rooms for each room type

const int monthLastDays[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

AvailableRoomsDatabase::AvailableRoomsDatabase()
{
   loadAvailableRooms();

   Date currentDate = computeCurrentDate();
   if( numAvailableDays == 0 )
      initilizeAvailableRooms( currentDate, 0, 6 );
   else
      if( availableRooms[ numAvailableDays - 1 ].getDate() < currentDate )  //最後一筆小於今天
         initilizeAvailableRooms( currentDate, 0, 6 );
      else if( availableRooms[ 0 ].getDate() < currentDate )     //第一筆小於今天
         adjustAvailableRooms( currentDate );
      // It cannot happen that availableRooms[ 0 ].getDate() > currentDate
}

AvailableRoomsDatabase::~AvailableRoomsDatabase()
{
   saveAvailableRooms();
}

void AvailableRoomsDatabase::initilizeAvailableRooms( const Date &firstDate, int first, int numMonths )
{
    ////搜到curDate的index
    //int firstDateIndex = 0;
    //
    //for (; firstDateIndex < 183; ++firstDateIndex)
    //    if (availableRooms[firstDateIndex].getDate() == firstDate)
    //        break;

    ////補替到今天
    //int i = first;

    //for (; availableRooms[i].getDate() < firstDate; ++i, ++firstDateIndex)
    //    availableRooms[i] = availableRooms[firstDateIndex];

    ////補滿  (i 現在是今天 - 被換掉的天的index)
    //int monthDaysSum = 0;

    //for (int j = 0; j < numMonths; ++j)
    //    monthDaysSum += monthLastDays[firstDate.getMonth() + j];

    //for (int k = 0; i < monthDaysSum - firstDate.getDay(); ++i, ++k)
    //{
    //    AvailableRooms temp;
    //    temp.initilizeAvailableRooms(firstDate.getDay() + k, firstDate.getMonth() + k, firstDate.getYear() + k);
    //    availableRooms[i] = temp;
    //}


    int i = first;
    int monthDaysSum = 0;

    for (int j = 0; j < numMonths; ++j)
        monthDaysSum += monthLastDays[firstDate.getMonth() + j];

    for (int k = 0; i < monthDaysSum - firstDate.getDay(); ++i, ++k)
    {
        AvailableRooms temp;
        Date d(firstDate.getYear(), firstDate.getMonth(), firstDate.getDay() + k);
        temp.initilizeAvailableRooms(d.getYear(), d.getMonth(), d.getDay());
        availableRooms[i] = temp;
    }

    numAvailableDays = i;
}

// remove outdated data from availableRooms, and
// add new data into availableRooms if necessary
void AvailableRoomsDatabase::adjustAvailableRooms( const Date &currentDate )
{
    //initilizeAvailableRooms(currentDate, 0, 6);
}

void AvailableRoomsDatabase::displayAvailableRooms( Date checkInDate, Date checkOutDate )
{
   cout << "\nAvailable Rooms:\n\n";
   cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

   // checkInDateIndex is the index of checkInDate in availableRooms
   // checkOutDateIndex is the index of checkOutDate in availableRooms
   int checkInDateIndex = getDateIndex( checkInDate, 0 );
   int checkOutDateIndex = getDateIndex( checkOutDate, checkInDateIndex + 1 );

   for( int i = checkInDateIndex; i < checkOutDateIndex; i++ )
      cout << availableRooms[ i ].getDate().getYear() << "-"
           << setw( 2 ) << setfill( '0' ) << availableRooms[ i ].getDate().getMonth() << "-"
           << setw( 2 ) << availableRooms[ i ].getDate().getDay()
           << setw( 16 ) << setfill( ' ' ) << availableRooms[ i ].getAvailableRooms( 1 )
           << setw( 14 ) << availableRooms[ i ].getAvailableRooms( 2 )
           << setw( 19 ) << availableRooms[ i ].getAvailableRooms( 3 )
           << setw( 17 ) << availableRooms[ i ].getAvailableRooms( 4 )
           << setw( 15 ) << availableRooms[ i ].getAvailableRooms( 5 ) << "\n";
}

int AvailableRoomsDatabase::findMinNumRooms( int roomType,
                            const Date &checkInDate, const Date &checkOutDate )
{
   int minNumRooms = totalNumRooms[ roomType ];

   int checkInDateIndex = getDateIndex( checkInDate, 0 );
   int checkOutDateIndex = getDateIndex( checkOutDate, checkInDateIndex + 1 );

   for( int i = checkInDateIndex; i < checkOutDateIndex; i++ )
      if( minNumRooms > availableRooms[ i ].getAvailableRooms( roomType ) )
          minNumRooms = availableRooms[ i ].getAvailableRooms( roomType );

   return minNumRooms;
}

void AvailableRoomsDatabase::decreaseAvailableRooms( int roomType, int numRooms,
                             const Date &checkInDate, const Date &checkOutDate )
{
   int checkInDateIndex = getDateIndex( checkInDate, 0 );
   int checkOutDateIndex = getDateIndex( checkOutDate, checkInDateIndex + 1 );

   for( int i = checkInDateIndex; i < checkOutDateIndex; i++ )
      availableRooms[ i ].decreaseAvailableRooms( roomType, numRooms );
}

void AvailableRoomsDatabase::loadAvailableRooms()
{
   ifstream inFile( "Available Rooms.dat", ios::in | ios::binary );

   if( !inFile )
   {
      cout << "Available rooms.dat could not be opened!\n";
      system( "pause" );
      exit( 1 );
   }

   numAvailableDays = 0;
   while( inFile.read( reinterpret_cast< char * >( &availableRooms[ numAvailableDays ] ), sizeof( AvailableRooms ) ) )
      ++numAvailableDays;

   inFile.close();
}

void AvailableRoomsDatabase::saveAvailableRooms()
{
   ofstream outFile( "Available Rooms.dat", ios::out | ios::binary );

   if( !outFile )
   {
      cout << "Available rooms.dat could not be opened." << endl;
      system( "pause" );
      exit ( 1 );
   }

   for( int i = 0; i < numAvailableDays; i++ )
      outFile.write( reinterpret_cast< const char * > ( &availableRooms[ i ] ), sizeof( AvailableRooms ) );

   outFile.close();
}

// return the index i in [ dateIndex, numAvailableDays ) such that availableRooms[ i ].date == date
int AvailableRoomsDatabase::getDateIndex( const Date &date, int dateIndex )
{
   for( int i = dateIndex; i < numAvailableDays; i++ )
      if( availableRooms[ i ].getDate() == date )
         return i;

   return -1;
}