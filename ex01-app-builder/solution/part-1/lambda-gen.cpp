#include <iostream>
#include <functional>
#include <vector>

using std::cin, std::cout, std::endl;

namespace {
    // Create a function 'sqrGen' that returns a function that will square the incoming real (double) argument.
        auto sqrGen() {
            return [](double m)->double {return m * m;};
    }

    // Create a function 'cubeGen' that returns a function that will cube the incoming real (double) argument.
        auto cubeGen() {
            return [](double m)->double {return m * m * m;};
    }
};


int main(int argc, char* argv[]) {
    // declare an std::vector v to match the 'sqrGen' and 'cubeGen' functions (accepting double)
    std::vector<std::function<double(double)>> v;

    // Prompt user to enter up to 10 real numbers
    cout << "Enter up to 10 real numbers (enter -1 to stop):" << endl;
    std::vector<double> ar;
    double num;
    while (ar.size() < 10 && cin >> num && num != -1) {
        ar.push_back(num);
    }

    // push 'sqrGen' and 'cubeGen' into vector
    v.push_back( sqrGen());
    v.push_back( cubeGen());

    // for every element 'n' in the input vector: print the value, its square, and its cube.
    // sample row: n: 2.5   Squared: 6.25    Cubed: 15.625
    for (auto n : ar){
        cout << "n: "
             << n
             << "\tSquared: " 
             << v[0](n) 
             << "\tCubed: " 
             << v[1](n)
             << endl;
    }
 
 	return 0;
}
