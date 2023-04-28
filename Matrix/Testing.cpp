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

    for (iter i = test.begin(); i != test.end(); ++i) {
        std::cout << *i << ' ';
    }

    return 0;
}
