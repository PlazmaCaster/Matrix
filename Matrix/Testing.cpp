#include <iostream>
#include "Matrix.hpp"
#include "SquareMatrix.hpp"
#include <ctime>
#include <cmath>
#include <vector>
#include <type_traits>
#include <chrono>
#include <numeric>

using value_type = int;
using iter = Tensor::Matrix<value_type>::Iterator;
using size_type = Tensor::Matrix<value_type>::size_type;
using Tensor::Matrix;

template <class T>
void print(const Matrix<T>* mtx) {
    for (size_type row = 0; row != mtx->rows(); ++row) {
        for (size_type col = 0; col != mtx->columns(); ++col) {
            std::cout << mtx->at(row, col);
            if (col == mtx->columns() - 1) {
                std::cout << '\n';
            }
            else {
                std::cout << "  ";
            }
        }
    }
}

static constexpr int ITERATIONS = 1000;
static constexpr int SIZE = 200;

int main() {
    std::srand(static_cast<unsigned int>(time(nullptr))); 
    Tensor::SquareMatrix<int> test(0);
    std::cout << test.rows() << '\n';
    std::cout << test.columns();

    return 0;
}