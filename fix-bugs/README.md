Fix Bugs in DIY Shared Pointer

This folder contains a simple implementation of a shared pointer in C++. The goal is to fix bugs and improve the implementation.

The code in 'diy-shared' is a simple implementation of a shared  pointer, similiar to
the one in C++11. It is a smart pointer that retains shared ownership of an object through a pointer.

The shared pointer is a template class that takes a type parameter T. It has a constructor that takes a raw pointer of type T and a destructor that deletes the object when the last shared pointer to it is destroyed.

The code has some issues that need to be fixed. The issues are related to the implementation of the shared pointer, including memory management, reference counting, and thread safety. 

Also, it would be good to add some real unit tests to ensure the shared pointer works as expected.

