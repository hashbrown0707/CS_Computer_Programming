// AvailTable-function definitions for class AvailTable.

#include "AvailTable.h"

AvailTable::AvailTable()
   : date(),
     numAvailTables()
{
}

AvailTable::AvailTable( Date theDate, int *theNumAvailTables )
{
   setDate( theDate );
   for( int timeCode = 1; timeCode <= 3; timeCode++ )
      for( int tableType = 1; tableType <= 5; tableType++ )
         setNumAvailTables( timeCode, tableType, theNumAvailTables[ timeCode ] );
}

void AvailTable::setDate( Date theDate )
{
   date = theDate;
}

void AvailTable::setNumAvailTables( int timeCode, int tableType, int theNumAvailTables )
{
   numAvailTables[ timeCode ][ tableType ] = ( theNumAvailTables >= 0 ? theNumAvailTables : 0 );
}

Date AvailTable::getDate()
{
   return date;
}

int AvailTable::getNumAvailTables( int timeCode, int tableType )
{
   return numAvailTables[ timeCode ][ tableType ];
}

// increases numAvailTables[ timeCode ][ tableType ] by one
void AvailTable::increaseAvailTables( int timeCode, int tableType )
{
   ++numAvailTables[ timeCode ][ tableType ];
}

// decreases numAvailTables[ timeCode ][ tableType ] by one
void AvailTable::decreaseAvailTables( int timeCode, int tableType )
{
   --numAvailTables[ timeCode ][ tableType ];
}