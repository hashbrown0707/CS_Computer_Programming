#include <iostream>
#include <fstream>
using namespace::std;

#include "AvailTableDatabase.h"

// tableTypes[ i ] is the table type for i customers
const int tableTypes[ 13 ] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

extern Date computeCurrentDate();

// calls loadAvailTables(), removes outdated available table informations and
// adds new available table informations
AvailTableDatabase::AvailTableDatabase()
{
   loadAvailTables();

   Date currentDate = computeCurrentDate();
   int initNum[4] = { 2, 2, 2, 2 };

   if (availTables.empty())
       for (size_t i = 1; i <= 30; ++i)
           availTables.push_back(AvailTable(currentDate + i, initNum));

   vector<AvailTable>::iterator it = availTables.begin();
   Date dataDate = it->getDate();

   if (dataDate < currentDate)
       for (; it->getDate() < currentDate; ++it)
       {
           availTables.push_back(AvailTable(it->getDate() + 30, initNum));
           availTables.erase(it);
       }
}

// call storeAvailTables
AvailTableDatabase::~AvailTableDatabase()
{
   storeAvailTables();
}

// increases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::increaseAvailTables( int numCustomers, Date date, int timeCode )
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->increaseAvailTables( timeCode, tableType );
}

// decreases the number of available tables by one on date and timeCode for corresponding table type
void AvailTableDatabase::decreaseAvailTables( int numCustomers, Date date, int timeCode )
{
   int tableType = tableTypes[ numCustomers ];
   vector< AvailTable >::iterator it = getAvailTable( date );
   it->decreaseAvailTables( timeCode, tableType );
}

// returns true if there are available tables on date for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date )
{
    vector<AvailTable>::iterator it = getAvailTable(date);

    if (it == nullptr)
        return false;

    for (size_t i = 1; i < 4; ++i)
        if (it->getNumAvailTables(i, tableTypes[numCustomers]) > 0)
            return true;

    return false;
}

// returns true if there are available tables on date and timeCode for corresponding table type
bool AvailTableDatabase::availableTables( int numCustomers, Date date, int timeCode )
{
    vector<AvailTable>::iterator it = getAvailTable(date);

    if (it == nullptr)
        return false;

    if (it->getNumAvailTables(timeCode, tableTypes[numCustomers]) > 0)
        return true;
}

void AvailTableDatabase::loadAvailTables()
{
    ifstream inFile("AvailTables.dat", ios::binary);
    AvailTable temp;

    if (inFile.is_open())
    {
        while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(AvailTable)))
            availTables.push_back(temp);

        inFile.close();
    }
    else
    {
        cout << "Can not open the file" << endl;
        system("pause");
        exit(1);
    }
}

void AvailTableDatabase::storeAvailTables()
{
    ofstream outFile("AvailTables.dat", ios::binary | ios::app);

    if (outFile.is_open())
    {
        vector<AvailTable>::iterator it = availTables.begin();

        for (; it != availTables.end(); ++it)    //30days
            outFile.write(reinterpret_cast<const char*>(&*it), sizeof(AvailTable));

        outFile.close();
    }
    else
    {
        cout << "Can not open the file" << endl;
        system("pause");
        exit(1);
    }
}

// returns an iterator that points to the AvailTable object containing specified date
vector< AvailTable >::iterator AvailTableDatabase::getAvailTable( Date date )
{
    vector< AvailTable >::iterator it = availTables.begin();

    for (; it != availTables.end(); ++it)
        if (it->getDate() == date)
            return it;

    cerr << "iterator is not found";
    return nullptr;
}