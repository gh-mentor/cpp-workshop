## Instructions to create a C++application from scratch

Part 1:

```
1. Create a new C++ file named `app.cpp` and a `.gitignore` for the C++ app.

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
	- For each input number:
	-  print its value, its square, and its cube in a formatted row (e.g., `n: 2.5   Squared: 6.25    Cubed: 15.625`).

7. Compile and run the program to test its functionality.
```

Part 2:

```	
8. Refactor the code to separate the function definitions and the main logic for better readability and maintainability. The main program wil be stored in 'main.cpp' and the function definitions in 'lambda.h' and 'lambda.cpp'.

9. Add comments to explain the purpose of each function and major code sections.

10. Compile and run the final version of the program to ensure it works as expected.

Optional: Before compiling generate a Makefile to automate the build process.
```

