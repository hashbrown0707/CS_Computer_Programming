#ifndef AVAIL_TABLE_H
#define AVAIL_TABLE_H

#include "Date.h"

class AvailTable
{
public:
   AvailTable();
   AvailTable( Date theDate, int *theNumAvailTables );

   void setDate( Date theDate );
   void setNumAvailTables( int timeCode, int tableType, int theNumAvailTables );

   Date getDate();
   int getNumAvailTables( int timeCode, int tableType );

   // increases numAvailTables[ timeCode ][ tableType ] by one
   void increaseAvailTables( int timeCode, int tableType );

   // decreases numAvailTables[ timeCode ][ tableType ] by one
   void decreaseAvailTables( int timeCode, int tableType );

private:
   Date date;
   int numAvailTables[ 4 ][ 6 ]; // the number of available tables, specifically,
};  // numAvailTables[ 1 ][ i ] is  the number of available type i tables on 11:30
    // numAvailTables[ 2 ][ i ] is  the number of available type i tables on 14:30
    // numAvailTables[ 3 ][ i ] is  the number of available type i tables on 17:30

#endif // AVAIL_TABLE_H