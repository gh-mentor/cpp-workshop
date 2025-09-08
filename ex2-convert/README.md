The  c program combinatorics.c contains functions for calculating factorials and permutations. 

The program is missing the combination function and its associated comments. Start by adding a comment block that describes the combination function, including its formula. Then, implement the combination function using the formula C(n, r) = n! / (r! * (n - r)!). 

Change the file extension from .c to .cpp to convert the file to C++. 

Update the include directives to use C++ headers instead of C headers. 

Refactor the code to use C++ features, such as using 'std::cout' for output instead of 'printf'. 

Refactor the global functions into member functions of a class named 'Combinatorics'. 

To improve performance and avoid potential overflow issues, modify the 'fact' function to use an iterative approach instead of recursion.

Add a memoization technique to the 'fact' function to cache previously computed factorials.

Finally, add a main function that tests the 'fact', 'perm', and 'comb' functions using assertions to verify their correctness with arguments in the range of -1 to 5.

