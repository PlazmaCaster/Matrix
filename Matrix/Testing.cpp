#include <iostream>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include <ctime>
#include <cmath>
#include <vector>
#include <type_traits>


using value_type = int;
using iter = Tensor::Matrix<value_type>::Iterator;

int main() {
    std::srand(static_cast<unsigned int>(time(nullptr)));
    Tensor::Matrix<value_type> test(6, 10);
    int factor = 1;
    for (int i = 0; i != test.rows(); ++i) {
        for (int j = 0; j != test.columns(); ++j) {
            test(i, j) = j * factor;
        }
        factor *= 10;
    }

    test.print(", ");

    return 0;
}
