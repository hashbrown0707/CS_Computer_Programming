// vector standard header

#ifndef VECTOR_H
#define VECTOR_H

#include "xutility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE VectorConstIterator
template< typename MyVec >
class VectorConstIterator
{
public:
   using value_type = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer = typename MyVec::const_pointer;
   using reference = const value_type &;
   using TPtr = typename MyVec::pointer;

   VectorConstIterator()
      : ptr()
   {
   }

   VectorConstIterator( TPtr parg )
      : ptr( parg )
   {
   }

   reference operator*() const
   {
      return *ptr;
   }

   pointer operator->() const
   {
      return ptr;
   }

   VectorConstIterator& operator++()
   {
      ++ptr;
      return *this;
   }

   VectorConstIterator operator++( int )
   {
      VectorConstIterator temp = *this;
      ++ *this;
      return temp;
   }

   VectorConstIterator& operator--()
   {
      --ptr;
      return *this;
   }

   VectorConstIterator operator--( int )
   {
      VectorConstIterator temp = *this;
      -- *this;
      return temp;
   }

   VectorConstIterator& operator+=( const difference_type off )
   {
      ptr += off;
      return *this;
   }

   VectorConstIterator operator+( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp += off;
   }

   VectorConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   VectorConstIterator operator-( const difference_type off ) const
   {
      VectorConstIterator temp = *this;
      return temp -= off;
   }

   difference_type operator-( const VectorConstIterator &right ) const
   {
      return ptr - right.ptr;
   }

   reference operator[]( const difference_type off ) const
   {
      return *( *this + off );
   }

   bool operator==( const VectorConstIterator &right ) const
   {
      return ptr == right.ptr;
   }

   bool operator!=( const VectorConstIterator &right ) const
   {
      return !( *this == right );
   }

   bool operator<( const VectorConstIterator &right ) const
   {
      return ptr < right.ptr;
   }

   bool operator>( const VectorConstIterator &right ) const
   {
      return right < *this;
   }

   bool operator<=( const VectorConstIterator &right ) const
   {
      return !( right < *this );
   }

   bool operator>=( const VectorConstIterator &right ) const
   {
      return !( *this < right );
   }

   TPtr ptr; // pointer to element in vector
};


// CLASS TEMPLATE VectorIterator
template< typename MyVec >
class VectorIterator : public VectorConstIterator< MyVec >
{
public:
   using MyBase = VectorConstIterator< MyVec >;

   using value_type      = typename MyVec::value_type;
   using difference_type = typename MyVec::difference_type;
   using pointer         = typename MyVec::pointer;
   using reference       = value_type &;

   using MyBase::MyBase;

   reference operator*() const
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const
   {
      return const_cast< pointer >( MyBase::operator->() );
   }

   VectorIterator& operator++()
   {
      MyBase::operator++();
      return *this;
   }

   VectorIterator operator++( int )
   {
      VectorIterator temp = *this;
      MyBase::operator++();
      return temp;
   }

   VectorIterator& operator--()
   {
      MyBase::operator--();
      return *this;
   }

   VectorIterator operator--( int )
   {
      VectorIterator temp = *this;
      MyBase::operator--();
      return temp;
   }

   VectorIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   VectorIterator operator+( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp += off;
   }

   VectorIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-;

   VectorIterator operator-( const difference_type off ) const
   {
      VectorIterator temp = *this;
      return temp -= off;
   }

   reference operator[]( const difference_type off ) const
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};


// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
        myLast(),
        myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = VectorIterator< ScaryVal >;
   using const_iterator = VectorConstIterator< ScaryVal >;
   using reverse_iterator = ReverseIterator< iterator >;
   using const_reverse_iterator = ReverseIterator< const_iterator >;

   // empty vector constructor (default constructor)
   // Constructs an empty vector, with no elements.
   vector()
      : myData()
   {
   }

   // fill constructor
   // Constructs a vector with "count" elements.
   // Each element is initialized as 0.
   vector( const size_type count )
      : myData()
   {
      if( count != 0 )
      {
         myData.myFirst = new value_type[ count ]();
         myData.myLast = myData.myFirst + count;
         myData.myEnd = myData.myFirst + count;
      }
   }

   // copy constructor
   // Constructs a vector with a copy of each of the elements in "right",
   // in the same order.
   vector( const vector &right )
      : myData()
   {
       myData.myFirst = new value_type[right.capacity()]();
       myData.myLast = myData.myFirst + right.size();
       myData.myEnd = myData.myFirst + right.capacity();

       iterator it1 = begin();
       iterator it2 = right.begin();

       for (; it2 != right.end(); ++it1, ++it2)
           *it1 = *it2;
   }

   // Vector destructor
   // Destroys the vector object.
   // Deallocates all the storage capacity allocated by the vector.
   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   // Adds a new element at the end of the vector, after its current last element.
   // The content of val is copied (or moved) to the new element.
   // This effectively increases the vector size by one,
   // which causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   void push_back( const value_type &val )
   {
      size_type originalSize = size();
      resize( originalSize + 1 );
      myData.myFirst[ originalSize ] = val;
   }

   // overloaded assignment operator
   // Assigns new contents to the vector, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the vector
   // (with "right" preserving its contents).
   vector& operator=( const vector &right )
   {
       if (this != &right) // avoid self-assignment
       {
           iterator it1 = begin();
           iterator it2 = right.begin();

           if (capacity() >= right.size())
           {
               for (; it2 != right.end(); ++it1, ++it2)
                   *it1 = *it2;

               myData.myLast = myData.myFirst + right.size();
           }
           else if (capacity() < right.size() && right.size() <= capacity() * 3 / 2)
           {
               size_type newCapa = capacity() * 3 / 2;
               pointer v = new value_type[newCapa];

               for (size_type i = 0; it2 != right.cend(); ++i, ++it2)
                   v[i] = *it2;

               delete[] myData.myFirst;
               myData.myFirst = v;
               myData.myLast = v + right.size();
               myData.myEnd = v + newCapa;
           }
           else if (right.size() > capacity() * 3 / 2)
           {
               delete[] myData.myFirst;
               myData.myFirst = new value_type[right.size()];
               myData.myLast = myData.myFirst + right.size();
               myData.myEnd = myData.myFirst + right.size();
               it1 = begin();

               for (; it2 != right.cend(); ++it1, ++it2)
                   *it1 = *it2;
           }
       }

      return *this; // enables x = y = z, for example
   }

   // Resizes the vector so that it contains "newSize" elements.
   // If "newSize" is smaller than the current vector size,
   // the content is reduced to its first "newSize" elements, removing those beyond.
   // If "newSize" is greater than the current vector size,
   // the content is expanded by inserting at the end as many elements as needed
   // to reach a size of "newSize".
   // The new elements are initialized as 0.
   // If "newSize" is also greater than the current vector capacity,
   // an automatic reallocation of the allocated storage space takes place.
   void resize( const size_type newSize )
   {
       if (size() < newSize)
       {
           if (capacity() < newSize)
           {
               pointer v = new value_type[newSize]();

               for (size_t i = 0; i < size(); i++)
                   v[i] = myData.myFirst[i];

               for (size_t i = size(); i < newSize; i++)
                   v[i] = Ty();

               delete[] myData.myFirst;
               myData.myFirst = v;
               myData.myEnd = v + newSize;
           }
           else
               for (size_t i = 0, j = size(); i < newSize - size(); i++, j++)
                   myData.myFirst[j] = Ty();
       }
       else if (size() > newSize)
           for (size_t i = 0; i < size() - newSize; i++)
               pop_back();

       myData.myLast = myData.myFirst + newSize;
   }

   // Removes the last element in the vector,
   // effectively reducing the vector size by one.
   void pop_back()
   {
      if( size() > 0 )
         --myData.myLast;
   }

   // Removes from the vector a single element (where).
   // This effectively reduces the vector size by one, which is destroyed.
   // Relocates all the elements after the element erased to their new positions.
   iterator erase( const_iterator where )
   {
      if( where.ptr >= myData.myFirst && where.ptr < myData.myLast )
      {
          iterator it = end();

          for (; it != where; --it)
              *(it - 1) = *it;

          --myData.myLast;
          return it;
      }
      else
         return iterator( nullptr );
   }

   // Removes all elements from the vector (which are destroyed),
   // leaving the vector with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear()
   {
      myData.myLast = myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the vector is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myFirst );
   }

   // Returns a const_iterator pointing to the first element in the vector.
   // If the vector is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myFirst );
   }

   // Returns an iterator referring to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the vector is empty, this function returns the same as vector::begin.
   iterator end()
   {
      return iterator( myData.myLast );
   }

   // Returns a const_iterator referring to the past-the-end element in the vector.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the vector is empty, this function returns the same as vector::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myLast );
   }

   // Returns a reverse iterator pointing to the last element in the vector
   // (i.e., its reverse beginning).
   // rbegin points to the element right before the one
   // that would be pointed to by member end.
   reverse_iterator rbegin()
   {
      return reverse_iterator( end() );
   }

   // Returns a reverse iterator pointing to the last element in the vector
   // (i.e., its reverse beginning).
   // rbegin points to the element right before the one
   // that would be pointed to by member end.
   const_reverse_iterator rbegin() const
   {
      return const_reverse_iterator( end() );
   }

   // Returns a reverse iterator pointing to the theoretical element
   // preceding the first element in the vector
   // (which is considered its reverse end).
   reverse_iterator rend()
   {
      return reverse_iterator( begin() );
   }

   // Returns a reverse iterator pointing to the theoretical element
   // preceding the first element in the vector
   // (which is considered its reverse end).
   const_reverse_iterator rend() const
   {
      return const_reverse_iterator( begin() );
   }

   // Returns a const_iterator pointing to the first element in the vector.
   // If the vector is empty, the returned iterator value shall not be dereferenced.
   const_iterator cbegin() const
   {
      return begin();
   }

   // Returns a const_iterator pointing to the past-the-end element in the vector.
   // If the vector is empty, this function returns the same as vector::cbegin.
   // The value returned shall not be dereferenced.
   const_iterator cend() const
   {
      return end();
   }

   // Returns a const_reverse_iterator pointing to the last element in the vector
   // (i.e., its reverse beginning).
   const_reverse_iterator crbegin() const
   {
      return rbegin();
   }

   // Returns a const_reverse_iterator pointing to the theoretical element
   // preceding the first element in the vector
   // (which is considered its reverse end).
   const_reverse_iterator crend() const
   {
      return rend();
   }

   // Returns whether the vector is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   // Returns a reference to the element at position "pos" in the vector.
   value_type& operator[]( const size_type pos )
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         system( "pause" );
         exit( 1 );
      }

      return myData.myFirst[ pos ];
   }

   // Returns a reference to the element at position "pos" in the vector.
   const value_type& operator[]( const size_type pos ) const
   {
      if( pos >= static_cast< size_type >( myData.myLast - myData.myFirst ) )
      {
         cout << "vector subscript out of range\n";
         system( "pause" );
         exit( 1 );
      }

      return myData.myFirst[ pos ];
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty vector causes undefined behavior.
   value_type& front()
   {
      return *myData.myFirst;
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty vector causes undefined behavior.
   const value_type& front() const
   {
      return *myData.myFirst;
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty vector causes undefined behavior.
   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty vector causes undefined behavior.
   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two vectors are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const vector< Ty > &left, const vector< Ty > &right )
{
    if (left.size() != right.size())
        return false;

    typename vector< Ty >::iterator it1 = left.begin();
    typename vector< Ty >::iterator it2 = right.begin();

    for (; it1 != left.end(); ++it1, ++it2)
        if (*it1 != *it2)
            return false;

    return true;
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( const vector< Ty > &left, const vector< Ty > &right )
{
   return !( left == right );
}

#endif // VECTOR_H