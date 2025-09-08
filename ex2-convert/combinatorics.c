#include <stdio.h>
#include <assert.h>

/*
Define a factorial function 'fact' that takes an
unsigned integer 'n' and returns an unsigned long long.
The function will be recursive.
Algorithm:
if n = 0 or n = 1 =>  return 1
n * fact(n - 1)
*/

unsigned long long fact(unsigned int n) {
    // Base case
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    // Recursive case
    return n * fact(n - 1);
}


/*
Create a function 'perm' that calcluates the permutation of n and r.
Algorithm:
P(n, r) = n! / (n - r)!
*/
unsigned int perm(unsigned int n, unsigned int r) {
    // Calculate permutation
    return fact(n) / fact(n - r);
}



int main() {


    return 0;
}



    















// Create a test function to test the 'fact' function



int main() {

    return 0;
}


