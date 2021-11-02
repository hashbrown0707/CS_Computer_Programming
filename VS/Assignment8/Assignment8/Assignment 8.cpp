#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <deque>
#include "deque.h"

void testDeque1( size_t size );
void testDeque2( size_t size );
void testDeque3( size_t size );
void testDeque4( size_t size );
void testDeque5();

bool equal( std::deque< int > &deque1, deque< int > &deque2 );

int main()
{
   for( size_t i = 1; i <= 10; i++ )
   {
      testDeque1( 8 * i );
      testDeque2( 8 * i );
      testDeque3( 8 * i );
      testDeque4( 8 * i );
   }

   cout << endl;

   for( unsigned int seed = 1; seed <= 50; seed++ )
   {
      srand( seed );
      testDeque5();
   }

   cout << endl;

   system( "pause" );
}

void testDeque1( size_t size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > deque1( 1, 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 + 1 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 ), i );

      deque< int > deque2( 1, 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 + 1 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;

      deque1.insert( deque1.begin() + ( deque1.size() / 2 ), i );
      deque2.insert( deque2.begin() + ( deque2.size() / 2 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque2( size_t size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > deque1( 1, 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 + 1 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 ), i );

      deque< int > deque2( 1, 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 + 1 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;

      deque1.insert( deque1.begin() + ( deque1.size() / 2 + 1 ), i );
      deque2.insert( deque2.begin() + ( deque2.size() / 2 + 1 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque3( size_t size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > deque1;
      deque1.insert( deque1.begin(), 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 + 1 ), i );

      deque< int > deque2;
      deque2.insert( deque2.begin(), 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 + 1 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;

      deque1.insert( deque1.begin() + ( deque1.size() / 2 + 1 ), i );
      deque2.insert( deque2.begin() + ( deque2.size() / 2 + 1 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque4( size_t size )
{
   unsigned int numErrors = 8;
   for( unsigned int k = 0; k < 4; k++ )
   {
      std::deque< int > deque1;
      deque1.insert( deque1.begin(), 1 );
      unsigned int i;
      for( i = 2; i <= 4 * ( size / 2 - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 ), i );
      for( ; i <= 4 * ( size - 1 ) + k; i++ )
         deque1.insert( deque1.begin() + ( deque1.size() / 2 + 1 ), i );

      deque< int > deque2;
      deque2.insert( deque2.begin(), 1 );
      unsigned int j;
      for( j = 2; j <= 4 * ( size / 2 - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 ), j );
      for( ; j <= 4 * ( size - 1 ) + k; j++ )
         deque2.insert( deque2.begin() + ( deque2.size() / 2 + 1 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;

      deque1.insert( deque1.begin() + ( deque1.size() / 2 ), i );
      deque2.insert( deque2.begin() + ( deque2.size() / 2 ), j );

      if( equal( deque1, deque2 ) )
         numErrors--;
   }
   cout << "There are " << numErrors << " errors.\n";
}

void testDeque5()
{
   std::deque< int > deque1;
   deque< int > deque2;

   unsigned int numErrors = 1000;
   int value;
   unsigned int position;
   for( unsigned int i = 0; i < 1000; i++ )
   {
      switch( rand() % 2 )
      {
      case 0:         
         value = 1 + rand() % 99;
         position = rand() % ( deque1.size() + 1 );
         deque1.insert( deque1.begin() + position, value );
         deque2.insert( deque2.begin() + position, value );
         break;
      case 1:
         if( deque1.size() > 0 )
         {
            position = rand() % deque1.size();
            deque1.erase( deque1.begin() + position );
            deque2.erase( deque2.begin() + position );
         }
         break;
      }

      if( equal( deque1, deque2 ) )
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

   if( mapSize1 != mapSize2 )
      return false;

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
         return true;
      else
         return false;

   if( myOff1 != myOff2 )
      return false;

   if( mySize1 != mySize2 )
      return false;

   deque< int >::iterator it2( deque2.begin() );
   size_t row, col;
   for( size_t i = myOff1; i < myOff1 + mySize1; ++i, ++it2 )
   {
      row = ( i / 4 ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;

      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % 4;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
         if( *it2 != map2[ row ][ col ] )
            return false;
      }
   }

   std::deque< int >::iterator it1( deque1.begin() );
   deque< int > *myCont2;
   size_t offset1;
   size_t offset2;
   for( it2 = deque2.begin(); it1 < deque1.end(); ++it1, ++it2 )
   {
      myCont2 = *( reinterpret_cast< deque< int > ** >( &it2 ) );
      if( myCont2 != &deque2 )
         return false;

      offset1 = *( reinterpret_cast< size_t * >( &it1 ) + 2 );
      offset2 = *( reinterpret_cast< size_t * >( &it2 ) + 1 );
      if( offset1 != offset2 )
         return false;
   }

   std::deque< int >::reverse_iterator rIt1( deque1.rbegin() );
   deque< int >::reverse_iterator rIt2( deque2.rbegin() );
   for( ; rIt1 < deque1.rend(); ++rIt1, ++rIt2 )
   {
      myCont2 = *( reinterpret_cast< deque< int > ** >( &rIt2 ) );
      if( myCont2 != &deque2 )
         return false;

      offset1 = *( reinterpret_cast< size_t * >( &rIt1 ) + 2 );
      offset2 = *( reinterpret_cast< size_t * >( &rIt2 ) + 1 );
      if( offset1 != offset2 )
         return false;
   }

   return true;
}