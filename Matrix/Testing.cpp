#include <iostream>
#include "Matrix.h"

using namespace Tensor;

int main() {
    Matrix<int>::Iterator test(nullptr);
    int* foo = new int;
    Matrix<int>::Iterator bar(foo);

    std::cout << (test == Matrix<int>::Iterator(nullptr));


    return 0;
}
