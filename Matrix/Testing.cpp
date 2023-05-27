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
    Matrix<int> size_dif(5, 4);
    Matrix<int> value_dif(4, 5);
    Matrix<int> same_value(4, 5);

    std::vector<int> ex(5);


    //int counter = 0;
    //
    //for (auto i = base.begin(); i != base.end(); ++i) {
    //    *i = counter * counter;
    //    ++counter;
    //    std::cout << *i << ' ';
    //
    //}
    // 
 
    for (auto& it : base) {
        it = 42;
    }
    base.print();


    //for (auto i : value_dif) {
    //    i = 4;
    //}
    //counter = 0;
    //for (auto i : same_value) {
    //    i = counter * counter;
    //    ++counter;
    //}
    //
    //std::cout << "base == size_dif  : " << (base == size_dif) << '\n';
    //std::cout << "base == value_dif : " << (base == value_dif) << '\n';
    //std::cout << "base == same_value: " << (base == same_value) << '\n';
    //

    return 0;
}
