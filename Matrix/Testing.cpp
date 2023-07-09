#include <iostream>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include <ctime>
#include <cmath>
#include <vector>
#include <type_traits>

//using namespace Tensor;
using value_type = int;
using iter = Matrix<value_type>::Iterator;



int main() {
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    

    Matrix<value_type> unary(3, 4);
    Matrix<value_type> rhs(4, 4);
    Matrix<value_type> CRASH(4, 3);
    value_type scalar = 4;
    Matrix<value_type> binary(3, 4);

    for (auto& i : unary) {
        i = std::rand() % 10;
    }
    for (auto& i : rhs) {
        i = std::rand() % 10;
    }
    unary.print();
    std::cout << "---------------------------\n";
    rhs.print();
    std::cout << "---------------------------\n";
    binary.print();
    std::cout << "---------------------------\n\n";


    binary = scalar * unary;
    unary *= scalar;
    binary.print();
    std::cout << "---------------------------\n";
    unary.print();

    return 0;
}
