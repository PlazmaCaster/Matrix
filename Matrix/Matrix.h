#ifndef Matrix_H
#define Matrix_H

#include <stdexcept>
//#include <memory>         // TODO: use smart pointers for the love of god
#include <iostream>
#include <iterator>
#include <initializer_list>


namespace Tensor {

template <class T>
class Matrix {
///----- Public Members -------------------------------------------------------
public:
    class Iterator {
    public:
        using iterator_catgetory = std::random_access_iterator_tag;
        using difference_type    = std::ptrdiff_t;
        using value_type         = T;
        using pointer            = T*;
        using reference          = T&;

        Iterator(pointer ptr = nullptr) : m_ptr(ptr) {}
        Iterator(const Iterator& other) : m_ptr(other.m_ptr) {}
        
        /// ----- Access Overloads -----------------------------------------------------------------
        reference operator*() const { return *m_ptr; };
        pointer operator->() const { return m_ptr; }
        reference operator[](difference_type rhs) const { return m_ptr[rhs]; }
        
        /// ----- Comparison Overloads -------------------------------------------------------------
        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.m_ptr == rhs.m_ptr;
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.m_ptr != rhs.m_ptr;
        }
        friend bool operator<(const Iterator& lhs, const Iterator& rhs) {
            return lhs.m_ptr < rhs.ptr;
        }
        friend bool operator<=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.m_ptr <= rhs.ptr;
        }
        friend bool operator>=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.m_ptr >= rhs.ptr;
        }
        friend bool operator>(const Iterator& lhs, const Iterator& rhs) {
            return lhs.m_ptr > rhs.ptr;
        }
        /// ----- Iterator Math Overloads ----------------------------------------------------------
        Iterator& operator+=(difference_type rhs) { m_ptr += rhs; return *this; }
        Iterator& operator-=(difference_type rhs) { m_ptr -= rhs; return *this; }
        Iterator& operator++() { ++m_ptr; return *this; }
        Iterator& operator--() { --m_ptr; return *this; }

        difference_type operator-(const Iterator& rhs) { return m_ptr - rhs.m_ptr; }
        Iterator operator+(difference_type rhs) const { return Iterator(m_ptr + rhs); }
        Iterator operator-(difference_type rhs) const { return Iterator(m_ptr - rhs); }
        friend Iterator operator+(difference_type lhs, const Iterator& rhs) { 
            return Iterator(lhs + rhs.m_ptr);
        }
        friend Iterator operator-(difference_type lhs, const Iterator& rhs) { 
            return Iterator(lhs - rhs.m_ptr);
        }

    private:
        pointer m_ptr;
    };

    using value_type        = T;
    using size_type         = std::size_t;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using pointer           = value_type*;
    using const_pointer     = const value_type*;

    /// ----- Constructors & Initialization --------------------------------------------------------
    // Default Constructor
    Matrix();

    // Initialized Constructor
    Matrix(const size_type& width, const size_type& height, 
        const value_type& value = value_type());

    // Initializer_list Constructor
    //Matrix(
    //    const size_type& width, const size_type& height, 
    //    const std::initializer_list<value_type>& init
    //);

    // Copy Constructor
    Matrix(const Matrix& other);
    
    // Move Constructor
    Matrix(Matrix&& other);

    // Destructor
    ~Matrix() { delete[] m_data; }

    // Copy Assignment Operator
    Matrix& operator=(const Matrix& rhs);

    // Move Assignment Operator
    Matrix& operator=(Matrix&& rhs);

    /// ----- Indexing functions -------------------------------------------------------------------
          reference at(size_type x, size_type y);
    const_reference at(size_type x, size_type y) const;

          reference operator()(const size_type& x, const size_type& y);
    const_reference operator()(const size_type& x, const size_type& y) const;

    Iterator begin() { return Iterator(m_data); }
    Iterator end() { return Iterator(m_data + m_width * m_height); }

    /// ----- Basic Matrix Operations --------------------------------------------------------------
    Matrix& operator+=(const Matrix& rhs);       // M + N
    Matrix& operator-=(const Matrix& rhs);       // M - N
    Matrix& operator*=(const Matrix& rhs);       // M * N
    Matrix& operator/=(const Matrix& rhs);       // M / N

    /// ----- Scalar Multiplication ----------------------------------------------------------------
           Matrix& operator*=(const value_type& value); // M * Scalar
    friend Matrix& operator*=(const value_type& value, const Matrix& rhs);

    /// ---- MISC. ---------------------------------------------------------------------------------
    void print();


/// ----- Private Members --------------------------------------------------------------------------
private:
    size_type m_width;
    size_type m_height;
    pointer m_data;
};
/// ----- Non-Member Overloads ---------------------------------------------------------------------
template <class T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <class T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <class T>
Matrix<T>& operator+(const Matrix<T>& lhs, const Matrix<T>& rhs);     // M + N

template <class T>
Matrix<T>& operator-(const Matrix<T>& lhs, const Matrix<T>& rhs);     // M - N

template <class T>
Matrix<T>& operator*(const Matrix<T>& lhs, const Matrix<T>& rhs);     // M * N

template <class T>
Matrix<T>& operator/(const Matrix<T>& lhs, const Matrix<T>& rhs);     // M / N

///----- Definitions -------------------------------------------------------------------------------

/// Matrix() 
/// @brief Default Constructor
template <class T>
Matrix<T>::Matrix() {
    m_width = 0;
    m_height = 0;
    m_data = nullptr;
}

/// Matrix()
/// @brief Initialized Constructor
/// 
/// @param width: How wide the Matrix is (i.e.: number of columns)
/// @param height: How tall the Matrix is (i.e.: number of rows)
/// @param value: What to fill the Matrix 
/// 
/// @note default value is whatever the default ctor of value_type
/// 
/// @throws std::lenght_error: Minimum Dimensions of 1x1 required
template <class T>
Matrix<T>::Matrix(const size_type& width, const size_type& height,
                  const value_type& value) {
    if (!(width >= 1 && height >= 1)) {
        throw std::length_error("Minimum Dimensions of 1x1 required\n");
    }
    else {
        m_width = width;
        m_height = height;

        m_data = new value_type[m_width * m_height];

        for (size_type i = 0; i < m_width * m_height; ++i) {
            m_data[i] = value;
        }
    }
}

// TODO: Finish initializer list CTOR after all other are done... may come in handy
//template <class T>
//Matrix<T>::Matrix(const size_type& width, const size_type& height,
//                  const std::initializer_list<value_type>& init) {
//    if (!(width >= 1 && height >= 1)) {
//        throw std::length_error("Minimum Dimensions of 1x1 required\n");
//    }
//    else {
//        m_width = width;
//        m_height = height;
//
//        m_data = new value_type[m_width * m_height];
//    }
//}

template <class T>
typename Matrix<T>::reference 
Matrix<T>::at(size_type x, size_type y) {

    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("at() out of bounds");
    }
    return (*this)(x,y);
}

template <class T>
typename Matrix<T>::const_reference 
Matrix<T>::at(size_type x, size_type y) const {

    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("at() out of bounds");
    }
    return (*this)(x,y);
}

template <class T>
typename Matrix<T>::reference 
Matrix<T>::operator()(const size_type& x, const size_type& y) {

    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("at() out of bounds");
    }
    return *(m_data + (m_width * y) + x);

}

template <class T>
typename Matrix<T>::const_reference 
Matrix<T>::operator()(const size_type& x, const size_type& y) const {

    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("at() out of bounds");
    }
    return *(m_data + (m_width * y) + x);
}


// HACK: TEMPORARY ONLY FOR VIEWING THE INSIDE OF THE ARRAY
template <class T>
void Matrix<T>::print() {
    int x = 0;

    for (size_type i = 0; i < m_height; ++i) {
        for (size_type j = 0; j < m_width; ++j) {
            std::cout << m_data[x];
            ++x;
            if (j == m_width - 1) {
                std::cout << '\n';
            }
            else {
                std::cout << ' ';
            }
        }
    }
}
}

#endif /* MATRIX_H */