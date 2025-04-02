Fix Bugs in DIY Shared Pointer

This folder contains a simple implementation of a shared pointer in C++. The goal is to fix bugs and improve the implementation. You will also implement a function UseSmartPtr that uses the shared pointer to manage a dynamically allocated object.

The shared pointer is a template class that takes a type parameter T. It has a constructor that takes a raw pointer of type T and a destructor that deletes the object when the last shared pointer to it is destroyed.

The code has some issues that need to be fixed. The issues are related to the implementation of the shared pointer, including memory management, reference counting, and thread safety. 



