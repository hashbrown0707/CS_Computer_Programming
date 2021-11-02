#include "vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
   : myFirst(nullptr),
     myLast(nullptr),
     myEnd(nullptr)
{
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
   : 
    myFirst(new value_type[count]{ 0 }),
    myLast(myFirst + count),
    myEnd(myFirst + count)
{
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )
{
    size_type rightSize = static_cast<size_type>(right.myLast - right.myFirst);
    //size_type rightCapacity = static_cast<size_type>(right.myEnd - right.myFirst);
    myFirst = new value_type[rightSize];

    for (size_type i = 0; i < rightSize; i++)
        *(myFirst + i) = *(right.myFirst + i);

    myLast = myFirst + rightSize;
    myEnd = myFirst + rightSize;
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert( const_iterator where, const value_type &val )
{
    /*if (where < myFirst || where > myEnd)
        return iterator(nullptr);

    size_type index = static_cast<size_type>(where - myFirst);

    if (myLast == myEnd)  //�X
    {
        size_type count = this->capacity() * 3 / 2;
        iterator v = new value_type[count];

        for (size_type i = 0; i < index; i++)
            v[i] = *(myFirst + i);

        *(myFirst + index) = val;

        myFirst = v;
        delete[] v;
        myEnd = myFirst + count;
    }
    else  //���X
    {
        for (size_type i = (myLast - myFirst); i > index; i--)
            *(myFirst + i) = *(myFirst + i + 1);

        *(myFirst + index) = val;
    }

    myLast++;
    return nullptr;*/

    if (where < myFirst || where > myEnd)
        return nullptr;

    size_type count = capacity() * 3 / 2;
    size_type originalSize = size();
    if (count == 0 || count == 1) count++;

    size_type index = static_cast<size_type>(where - myFirst);

    //if (myFirst == nullptr)
    //{
    //    myFirst = new value_type[1]; //
    //    myLast = myFirst + count;
    //    myEnd = myFirst + count;
    //}

    if (myLast == myEnd)
    {
        pointer v = new value_type[count];

        for (size_type i = 0; i < index; i++)
            *(v + i) = *(myFirst + i);

        *(v + index) = val;

        for (size_type i = index + 1; i <= size(); i++)
            *(v + i) = *(myFirst + i - 1);

        myLast = v + originalSize + 1;
        myEnd = v + count;
        delete[] myFirst;         //��heap corruption
        myFirst = v;
    }
    else
    {
        for (size_type i = capacity() - 1; i >= index; i--)
        {
            myFirst[i] = myFirst[i - 1];

            if (i == index)
            {
                myFirst[i] = val;
                break;
            }
        }
        myLast++;
    }

    return myFirst;
}

// overloaded assignment operator
// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
       size_type rightSize = static_cast<size_type>(right.myLast - right.myFirst);

       if (rightSize <= capacity())
       {
           for (size_type i = 0; i < rightSize; i++)
               *(myFirst + i) = *(right.myFirst + i);

           if (right.myFirst != nullptr)
               myLast = myFirst + rightSize;
       }
       else
       {
           size_type count = (capacity() * 3 / 2 > rightSize) ? capacity() * 3 / 2 : rightSize;

           delete[] myFirst;
           myFirst = myLast = myEnd = nullptr;

           for (size_type i = 0; i < rightSize; i++)
               this->insert(end(), *(right.myFirst + i));

           myEnd = myFirst + count;
       }
   }

   return *this; // enables x = y = z, for example
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase( const_iterator where )
{
    size_type index = static_cast<size_type>(where - myFirst);

    for (size_type i = index; i < size(); i++)
        myFirst[i] = myFirst[i + 1];

    myLast--;

    return nullptr;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear() // erase all
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::begin() const
{
   return const_iterator( myFirst );
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::const_iterator vector::end() const
{
   return const_iterator( myLast );
}

// Returns a const_iterator pointing to the first element in the container.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::cbegin() const
{
   return begin();
}

// Returns a const_iterator pointing to the past-the-end element in the container.
// If the container is empty, this function returns the same as vector::cbegin.
// The value returned shall not be dereferenced.
vector::const_iterator vector::cend() const
{
   return end();
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty() const
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size() const
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity() const
{
   return static_cast< size_type >( myEnd - myFirst );
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::front()
{
   return *myFirst;
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::front() const
{
   return *myFirst;
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::back()
{
   return myLast[ -1 ];
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::back() const
{
   return myLast[ -1 ];
}