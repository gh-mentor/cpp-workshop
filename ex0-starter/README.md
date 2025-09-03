## Instructions to Recreate `lambda-gen.cpp` from Scratch

1. Create a new C++ file named `lambda-gen.cpp`.

2. At the top, include the necessary headers for input/output, functional objects, and vectors.

3. Use the standard input/output objects for reading and writing to the console.

4. Create an anonymous namespace and place the following functions inside it:
	- `sqrGen`: Returns a function which squares a real (double) argument.
	- `cubeGen`: Returns a function which cubes a real (double) argument.

6. In the main function:
	- Declare a vector to store functions that accept a double and return a double, matching the `sqrGen` and `cubeGen` functions.
	- Prompt the user to enter up to 10 real numbers, stopping if the user enters -1.
	- Store the input numbers in a vector.
	- Add the `sqrGen` and `cubeGen` functions to the function vector.
	- For each input number, print its value, its square, and its cube in a formatted row (e.g., `n: 2.5   Squared: 6.25    Cubed: 15.625`).

7. Compile and run the program to test its functionality.
