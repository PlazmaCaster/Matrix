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
    
    Matrix<value_type> source(3, 4);
    Matrix<value_type> copy(source);


    return 0;
}
