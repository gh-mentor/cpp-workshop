#include <iostream>
#include <vector>
#include <cassert>

using std::cout, std::endl;

template <typename T>
class Resource
{
private:
    size_t _length; 
    T *_data;     // The real resource.
public:

    Resource(size_t length) : _length(length), _data(new T[length])    { }

    Resource(const Resource &rhs)
    {
        _length = rhs._length;
        this->_data = new T[_length];
        for (size_t i = 0; i < _length; i++)
        {
            _data[i] = rhs._data[i];
        }
    }

    Resource &operator=(const Resource &rhs)
    {
        cout << "copy assign" << endl;
        if (this == &rhs)
            return *this;

        delete[] _data;

        _length = rhs._length;
        _data = new T[_length];
        for (size_t i = 0; i < _length; i++)
        {
            _data[i] = rhs._data[i];
        }
        return *this;
    }

    ~Resource()
    {
        if (_data != nullptr)
        {
            delete[] _data;
        }
    }

    // Retrieves the length of the data resource.
    size_t Length() const
    {
        return _length;
    }
};

void test()
{
    std::vector<Resource<int>> v;

    // Add Resource objects to the vector
    v.push_back(Resource<int>(10));
    v.push_back(Resource<int>(30));
    v.push_back(Resource<int>(50));

    // Assert that the size of the vector is correct
    assert(v.size() == 3);

    // Assert that the lengths of the Resource objects are correct
    assert(v[0].Length() == 10);
    assert(v[1].Length() == 30);
    assert(v[2].Length() == 50);

    // Clear the vector
    v.clear();

    // Assert that the vector is empty after clearing
    assert(v.empty());

    // display a message indicating that the test passed
    cout << "Test passed!" << endl;

}

int main()
{
    test();

    return 0;
}