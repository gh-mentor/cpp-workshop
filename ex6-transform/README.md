Byte Manipulation with C++

In this exercise you will design and implement a C++ class that performs byte manipulation using modern C++ features, adhering to SOLID design principles. The class should allow for both fixed and custom transformation strategies on a collection of bytes. The goal is to create a flexible and reusable component that can be easily extended for future requirements.

- Create a class `ByteFactory` with the following features:
  - A private vector to store byte data, initialized via the constructor.
  - Ensure the vector size does not exceed 100 bytes. Throw an exception if the limit is exceeded.

- Implement a method 'transform' that takes ab unsigned byte mask as an argument
  - Apply the mask to each byte in the vector and return a new vector with the transformed bytes.
- Overload `transform` to accept a function/lambda expression:
  - The function should define a custom transformation strategy for the bytes.

- Ensure the class is single-responsibility and open for extension but closed for modification.
- Use dependency injection for the transformation strategy.

- Implement a simple test suite using Doctest or GoogleTest to validate the functionality of the `ByteFactory` class.
- Write unit tests to cover various scenarios, including edge cases and error handling:
  - Initialization with valid and invalid byte containers.
  - Transformation with different masks and custom functions.
  - Edge cases such as empty containers and maximum size.

- Document the code with comments and provide a README file explaining the design choices, usage, and testing instructions.

