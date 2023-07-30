#ifndef SQUAREMATRIX_HPP
#define SQUAREMATRIX_HPP

#include "Matrix.hpp"
#include <initializer_list>
#include <vector>

namespace Tensor {

template <class T>
class SquareMatrix : public Tensor::Matrix<T> {
public:
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using size_type = size_t;

    SquareMatrix(const size_type& length = 1, const value_type& value = value_type())
        : Matrix<T>(length, length, value) {};
    SquareMatrix(const std::initializer_list<std::initializer_list<value_type>>& init);
    SquareMatrix(const std::vector<std::vector<value_type>>& vec);

    value_type determinate();
    value_type trace();
    void resize(const size_type& new_length);
protected:
    using Matrix<T>::m_size;
    using Matrix<T>::m_width;
    using Matrix<T>::m_height;
    using Matrix<T>::m_data;
};

template <class T>
SquareMatrix<T>::SquareMatrix(const std::initializer_list<std::initializer_list<value_type>>& init) 
    : m_height(0), m_width(0), m_size(0), m_data(nullptr) {
    
    using Iterator = typename Matrix<T>::Iterator;

    size_type init_height = init.size();
    size_type init_width = largest_row(init.begin(), init.end());

    if (init_height > init_width) {
        this->m_height = this->m_width = init_height;
    }
    else {
        this->m_height = this->m_width = init_width;
    }

    this->m_size = this->m_width * this->m_height;
    this->m_data = new value_type[this->m_size];

    for (Iterator it = SquareMatrix::begin(); it != this->end(); ++it) {
        *it = value_type();
    }

    initialize(init.begin(), init.end());
}

template <class T>
SquareMatrix<T>::SquareMatrix(const std::vector<std::vector<value_type>>& vec) 
    : m_height(0), m_width(0), m_size(0), m_data(nullptr) {

    using Iterator = typename Matrix<T>::Iterator;

    size_type init_height = vec.size();
    size_type init_width = largest_row(vec.begin(), vec.end());

    if (init_height > init_width) {
        this->m_height = this->m_width = init_height;
    }
    else {
        this->m_height = this->m_width = init_width;
    }

    this->m_size = this->m_width * this->m_height;
    this->m_data = new value_type[this->m_size];
 
    for (Iterator it = this->begin(); it != this->end(); ++it) {
        *it = value_type();
    }

    initialize(vec.begin(), vec.end());
}

template <class T>
typename SquareMatrix<T>::value_type SquareMatrix<T>::determinate() {

}

template <class T>
typename SquareMatrix<T>::value_type SquareMatrix<T>::trace() {

}

template <class T>
void SquareMatrix<T>::resize(const size_type& new_length) {
    this->resize(new_length, new_length);
}
}
#endif /* SQUAREMATRIX_HPP */