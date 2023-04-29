#include <iostream>
#include "Matrix.h"
#include "SquareMatrix.hpp"
#include <ctime>
#include <cmath>

using namespace Tensor;
using value_type = int;
using iter = Matrix<value_type>::Iterator;

int main() {

    std::srand(static_cast<size_t>(time(nullptr)));

    SquareMatrix<int> test;

    std::cout << test.rows();

    Matrix<value_type> lhs(3, 3);
    Matrix<value_type> rhs(3, 3);

    for (int i = 0; i != 3; ++i) {
        for (int j = 0; j != 3; ++j) {
            lhs.at(i, j) = rand() % 5;
            rhs.at(i, j) = rand() % 5;
        }
    }

    lhs.print();
    std::cout << std::endl;
    //rhs.print();
    std::cout << std::endl;
    lhs *= 5;
    lhs.print();
    return 0;
}
