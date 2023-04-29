#ifndef SQUAREMATRIX_HPP
#define SQUAREMATRIX_HPP

#include "Matrix.hpp"


template <class T>
class SquareMatrix : public Tensor::Matrix<T> {
public:    
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using size_type = size_t;
    
    value_type determinate();
    value_type trace();
    bool is_identity();


};

#endif /* SQUAREMATRIX_HPP */