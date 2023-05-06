#include <iostream>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include <ctime>
#include <cmath>

using namespace Tensor;
using value_type = int;
using iter = Matrix<value_type>::Iterator;

int main() {

    std::srand(static_cast<size_t>(time(nullptr)));

    Matrix<int> test(4,5);

    int insert = 0;
    for (auto i = test.begin(); i != test.end(); ++i) {
        *i = insert * insert;
        ++insert;
    }

    test.print();
    std::cout << '\n' << test(0, 4);



    return 0;
}
