#include <iostream>
#include "Matrix.h"

using namespace Tensor;
using iter = Matrix<int>::Iterator;

int main() {

    Tensor::Matrix<int> test(5, 5);
    for (size_t x = 0; x != 5; ++x) {
        for (size_t y = 0; y != 5; ++y) {
            test(x, y) = static_cast<int>(x + y);
        }
    }
    test.print();
    std::cout << '\n';

    test.resize(3, 3);
    test.print();
    std::cout << '\n';

    test.resize(5, 5);
    test.print();

    return 0;
}
