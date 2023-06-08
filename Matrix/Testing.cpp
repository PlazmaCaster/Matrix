#include <iostream>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include <ctime>
#include <cmath>
#include <vector>

using namespace Tensor;
using value_type = int;
using iter = Matrix<value_type>::Iterator;

int main() {

    std::srand(static_cast<unsigned>(time(nullptr)));

    Matrix<int> base(4, 5);

    int counter = 0;
    for (auto& i : base) {
        i = counter;
        ++counter;
    }
    base.print();

    Matrix<int> second(5, 3);

    for (int row = 0; row != second.rows(); ++row) {
        second(row, 0) = 1;
        second(row, 1) = 2;
        second(row, 2) = 3;
    }
    std::cout << '\n';
    second.print();

    base *= second;

    std::cout << '\n';
    base.print();


    return 0;
}
