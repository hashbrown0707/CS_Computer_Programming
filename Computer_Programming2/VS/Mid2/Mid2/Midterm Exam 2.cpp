#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <deque>
#include "deque.h"

void testPushFront( size_t size );
void testAssignment1();
void testAssignment2();
bool equal( std::deque< int > &deque1, deque< int > &deque2 );

const size_t number = 200;

int main()
{
   //for( size_t i = 1; i <= 10; i++ )
   //   testPushFront( 32 * i );

   //cout << endl;

   //for( size_t seed = 1; seed <= 10; seed++ )
   //{
   //   srand( seed );
   //   testAssignment1();
   //}

   cout << endl;

   for( size_t seed = 1; seed <= 10; seed++ )
   {
      srand( seed );
      testAssignment2();
   }

   cout << endl;

   system( "pause" );
}

void testPushFront( size_t size )
{
   size_t numErrors = size;
   std::deque< int > deque1;
   deque< int > deque2;
   for( size_t i = 1; i <= size; i++ )
   {
      deque1.push_front( i );
      deque2.push_front( i );

      if( equal( deque1, deque2 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment1()
{
   size_t numErrors = number;
   size_t length;
   int value;
   for( size_t i = 0; i < number; i++ )
   {
      std::deque< int > deque1;
      deque< int > deque2;
      length = rand() % 200;
      for( size_t j = 0; j < length; j++ )
      {
         value = 1 + rand() % 99;
         deque1.push_front( value );
         deque2.push_front( value );
      }

      std::deque< int > deque3;
      deque< int > deque4;
      length = rand() % 200;
      for( size_t j = 0; j < length; j++ )
      {
         value = 1 + rand() % 99;
         deque1.push_front( value );
         deque2.push_front( value );
      }

      deque3 = deque1;
      deque4 = deque2;

      if( equal( deque3, deque4 ) )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors\n";
}

void testAssignment2()
{
   unsigned int numErrors = number;
   unsigned int length;
   for( unsigned int i = 0; i < number; i++ )
   {
      deque< int > deque1;
      length = rand() % 200;
      for( unsigned int j = 0; j < length; j++ )
         deque1.push_front( 1 + rand() % 99 );

      deque< int > deque2;
      length = rand() % 200;
      for( unsigned int j = 0; j < length; j++ )
         deque2.push_front( 1 + rand() % 99 );

      int **mapBefore = *( reinterpret_cast< int *** > ( &deque2 ) );
      size_t mapSizeBefore = *( reinterpret_cast< size_t * >( &deque2 ) + 1 );
      size_t myOffBefore = *( reinterpret_cast< size_t * >( &deque2 ) + 2 );
      size_t mySizeBefore = *( reinterpret_cast< size_t * >( &deque2 ) + 3 );

      if( mapSizeBefore == 0 || mySizeBefore == 0 )
      {
         numErrors--;
         continue;
      }
      else
          cout << "before";

      size_t first = myOffBefore / 4 % mapSizeBefore;
      size_t last = ( myOffBefore + mySizeBefore - 1 ) / 4 % mapSizeBefore;
      size_t numRows = ( last - first + 1 ) % mapSizeBefore;

      int **addressBefore = new int *[ mapSizeBefore ]();

      size_t rowBefore = first;
      for( size_t i = 0; i < numRows; ++i )
      {
         addressBefore[ rowBefore ] = mapBefore[ rowBefore ];
         rowBefore = ( rowBefore + 1 ) % mapSizeBefore;
      }

      deque2 = deque1;

      int **mapAfter = *( reinterpret_cast< int *** > ( &deque2 ) );
      size_t mapSizeAfter = *( reinterpret_cast< size_t * >( &deque2 ) + 1 );
      size_t myOffAfter = *( reinterpret_cast< size_t * >( &deque2 ) + 2 );
      size_t mySizeAfter = *( reinterpret_cast< size_t * >( &deque2 ) + 3 );

      if( mapSizeAfter == 0 || mySizeAfter == 0 )
      {
         numErrors--;
         continue;
      }

      last = ( myOffAfter + mySizeAfter - 1 ) / 4 % mapSizeAfter;
      if( numRows > ( last - first + 1 ) % mapSizeAfter )
         numRows = ( last - first + 1 ) % mapSizeAfter;

      int **addressAfter = new int *[ mapSizeAfter ]();
      size_t rowAfter = first;
      for( size_t i = 0; i < numRows; ++i )
      {
         addressAfter[ rowAfter ] = mapAfter[ rowAfter ];
         rowAfter = ( rowAfter + 1 ) % mapSizeAfter;
      }

      bool correct = true;
      rowBefore = first;
      rowAfter = first;
      for( size_t i = 0; i < numRows; ++i )
      {
         if( addressBefore[ rowBefore ] != addressAfter[ rowAfter ] )
         {
            correct = false;
            break;
         }
         rowBefore = ( rowBefore + 1 ) % mapSizeBefore;
         rowAfter = ( rowAfter + 1 ) % mapSizeAfter;
      }

      if( correct )
         numErrors--;
   }

   cout << "There are " << numErrors << " errors.\n";
}

bool equal( std::deque< int > &deque1, deque< int > &deque2 )
{
   int **map1 = *( reinterpret_cast< int *** > ( &deque1 ) + 1 );
   size_t mapSize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 2 );
   size_t myOff1 = *( reinterpret_cast< size_t * >( &deque1 ) + 3 );
   size_t mySize1 = *( reinterpret_cast< size_t * >( &deque1 ) + 4 );

   int **map2 = *( reinterpret_cast< int *** > ( &deque2 ) );
   size_t mapSize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 1 );
   size_t myOff2 = *( reinterpret_cast< size_t * >( &deque2 ) + 2 );
   size_t mySize2 = *( reinterpret_cast< size_t * >( &deque2 ) + 3 );

   if (mapSize1 != mapSize2)
   {
       cout << "msize";
      return false;
   }

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
         return true;
      else
      {
          cout << "what";
         return false;
      }

   if (myOff1 != myOff2)
   {
       cout << "off";
      return false;
   }

   if( mySize1 != mySize2 )
   {
       cout << "size";
      return false;
   }

   size_t row, col;
   for( size_t i = myOff1; i < myOff1 + mySize1; ++i )
   {
      row = ( i / 4 ) % mapSize1;
      if (map1[row] != nullptr && map2[row] == nullptr)
      {
          cout << "ptr1";
         return false;
      }

      if (map1[row] == nullptr && map2[row] != nullptr)
      {
          cout << "ptr2";
         return false;
      }

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % 4;
         if (map1[row][col] != map2[row][col])
         {
             cout << "val";
            return false;
         }
      }
   }

   return true;
}