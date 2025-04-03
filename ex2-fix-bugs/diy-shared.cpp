/*
A shared pointer keeps a pointer to an object and a pointer to a shared reference count.

Every time a copy of the smart pointer is made using the copy constructor,
the reference count is incremented.

When a shared pointer is destroyed, the reference count for its object is decremented.
*/

#include <iostream>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

struct RefCounter
{
    int refCount = 0;
};

template <typename T>
class SmartPtr
{
private:
    RefCounter *_refCounter = nullptr;
    T *_data = nullptr;

public:
    // Constructor (bug)
    SmartPtr(T *data) : _data(data)
    {
        _refCounter = new RefCounter();
        _refCounter->refCount = 1;
    }

    // Copy Constructor
    SmartPtr(const SmartPtr &rhs) : _data(rhs._data), _refCounter(rhs._refCounter)
    {
        if (_refCounter)
        {
            _refCounter->refCount++;
        }
    }

    // Copy Assignment Operator (bug)
    SmartPtr &operator=(const SmartPtr &rhs)
    {
        if (this == &rhs)
            return *this;

        // Decrement current reference count and clean up if needed
        if (_refCounter && --_refCounter->refCount != 0)
        {
            delete _data;
            delete _refCounter;
        }

        // Copy data and reference counter from rhs 
        _data = rhs._data;
        _refCounter = rhs._refCounter;

        return *this;
    }

    // Destructor (bug)
    ~SmartPtr()
    { // Decrement reference count and clean up if needed 
        if (_refCounter && _refCounter->refCount == 0)
        {
            delete _data;
            delete _refCounter;
        }
    }

    // Utility function to print the value
    void Dump() const
    {
        if (_data)
        {
            cout << *_data << endl;
        }
        else
        {
            cout << "Null" << endl;
        }
    }
};

void UseSmartPtr()
{
    assert(false, "UseSmartPtr() is not implemented yet");

    // Create a SmartPtr instance

    // Make a copy of the SmartPtr instance

    // Assignment an instance to another instance

    // Perform a scope test inside a block

    // After exiting the scope, the reference count should decrease

    // If all tests passed write a message to the console

}

int main()
{
    UseSmartPtr();
    return 0;
}