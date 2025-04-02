/*
A shared pointer keeps a pointer to an object and a pointer to a shared reference count.

Every time a copy of the smart pointer is made using the copy constructor,
the reference count is incremented.

When a shared pointer is destroyed, the reference count for its object is decremented.
*/

#include <iostream>

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
    T *_data;

public:
    SmartPtr(T *data) : _data(data)
    {
        if (_refCounter == nullptr)
        {
            _refCounter = new RefCounter();
        }
        _refCounter->refCount++;
    }
    SmartPtr(const SmartPtr &rhs)
    {
        if (this == &rhs)
            return;
        this->_data = rhs._data;
        this->_refCounter = rhs._refCounter;
        this->_refCounter->refCount++;
    }
    const SmartPtr &operator=(const SmartPtr &rhs)
    {
        if (this == &rhs)
            return *this;
        this->_refCounter->refCount--;
        this->_refCounter = rhs._refCounter;
        this->_refCounter->refCount++;
        this->_data = rhs._data;
        return *this;
    }
    void Dump()
    {
        cout << *_data << endl;
    }

    ~SmartPtr()
    {
        _refCounter->refCount--;
        if (_refCounter->refCount == 0)
        {
            delete[] _data;
            delete _refCounter;

            return;
        }
    }
};

void UseSmartPtr()
{
    cout << "Starting SmartPtr Test" << endl;

    // Create a SmartPtr instance
    SmartPtr<int> sp1(new int(42));
    cout << "Created sp1 with value: ";
    sp1.Dump();

    // Copy constructor
    SmartPtr<int> sp2 = sp1;
    cout << "Copied sp1 to sp2. Value in sp2: ";
    sp2.Dump();

    // Assignment operator
    SmartPtr<int> sp3(new int(100));
    cout << "Created sp3 with value: ";
    sp3.Dump();
    sp3 = sp1;
    cout << "Assigned sp1 to sp3. Value in sp3: ";
    sp3.Dump();

    // Scope test
    {
        cout << "Entering inner scope" << endl;
        SmartPtr<int> sp4 = sp1;
        cout << "Copied sp1 to sp4. Value in sp4: ";
        sp4.Dump();
        cout << "Exiting inner scope" << endl;
    }

    cout << "Exiting SmartPtr Test" << endl;
}

int main()
{
    UseSmartPtr();
    return 0;
}