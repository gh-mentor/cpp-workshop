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
    // Getter for _data
    T* GetData() const { return _data; }

    // Getter for _refCounter
    RefCounter* GetRefCounter() const { return _refCounter; }

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
    // Create a SmartPtr instance
    SmartPtr<int> sp1(new int(42));
    assert(*sp1.GetData() == 42); // Assert that sp1 holds the correct value

    // Copy constructor
    SmartPtr<int> sp2 = sp1;
    assert(*sp2.GetData() == 42); // Assert that sp2 holds the same value as sp1
    assert(sp1.GetRefCounter() == sp2.GetRefCounter()); // Assert that sp1 and sp2 share the same reference counter
    assert(sp1.GetRefCounter()->refCount == 2); // Assert that the reference count is incremented

    // Assignment operator
    SmartPtr<int> sp3(new int(100));
    assert(*sp3.GetData() == 100); // Assert that sp3 holds the correct value initially
    sp3 = sp1;
    assert(*sp3.GetData() == 42); // Assert that sp3 now holds the same value as sp1
    assert(sp1.GetRefCounter() == sp3.GetRefCounter()); // Assert that sp1 and sp3 share the same reference counter
    assert(sp1.GetRefCounter()->refCount == 3); // Assert that the reference count is incremented

    // Scope test
    {
        SmartPtr<int> sp4 = sp1;
        assert(*sp4.GetData() == 42); // Assert that sp4 holds the same value as sp1
        assert(sp1.GetRefCounter() == sp4.GetRefCounter()); // Assert that sp1 and sp4 share the same reference counter
        assert(sp1.GetRefCounter()->refCount == 4); // Assert that the reference count is incremented
    }
    // After exiting the scope, the reference count should decrease
    assert(sp1.GetRefCounter()->refCount == 3); // Assert that the reference count is decremented

    // write a message to the console
    cout << "All tests passed!" << endl;
}

int main()
{
    UseSmartPtr();
    return 0;
}