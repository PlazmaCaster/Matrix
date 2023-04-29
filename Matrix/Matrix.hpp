#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdexcept>
//#include <memory>         // TODO: use smart pointers for the love of god
#include <iostream>
#include <iterator>
#include <initializer_list>

namespace Tensor {

/// TODO: Create custom exception class
/// M rows by N columns ( M x N )
/// Matrix<T>
/// Row-major matrix class. Allows for basic arithmetic operations on the matrices
template <class T>
class Matrix {
/// ----- Public Members ---------------------------------------------------------------------------
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

    Iterator begin()    { return Iterator(m_data); }
    Iterator end()      { return Iterator(m_data + m_size); }
    size_type columns() const { return m_width; }
    size_type rows() const { return m_height; }

    /// ----- Basic Matrix Operations --------------------------------------------------------------
    Matrix& operator+=(const Matrix& rhs);       // M + N
    Matrix& operator-=(const Matrix& rhs);       // M - N
    Matrix& operator*=(const Matrix& rhs);       // M * N
    Matrix& operator*=(const value_type& value); // M * Scalar

    /// ---- MISC. ---------------------------------------------------------------------------------
    void print();
    size_type size() const { return m_size; }
    void resize(size_type new_width, size_type new_height);
    Matrix& transpose();

/// ----- Private Members --------------------------------------------------------------------------
private:
    size_type m_width;
    size_type m_height;
    size_type m_size;
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

///----- Definitions -------------------------------------------------------------------------------

/// Matrix() 
/// @brief Default Constructor
template <class T>
Matrix<T>::Matrix() {
    m_width = 0;
    m_height = 0;
    m_size = 0;
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
    if (width == 0 || height == 0) {
        throw std::length_error("minimum dimensions of 1x1 required\n");
    }
    m_width = width;
    m_height = height;
    m_size = m_width * m_height;
    
    m_data = new value_type[m_size];
    //std::cout << m_data << '\n';
    
    for (size_type i = 0; i < m_size; ++i) {
        m_data[i] = value;
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
Matrix<T>::Matrix(const Matrix<T>& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_size = other.m_size;

    m_data = new value_type[m_width * m_height];
    std::copy(other.begin(), other.end(), begin());
}

template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator+=(const Matrix& rhs) {
    // TODO: Exception class
    // if (m_width != rhs.m_width || m_height != rhs.m_height) {
    //     throw ERROR
    // }
    for (size_type row = 0; row != rows(); ++row) {
        for (size_type col = 0; col != columns(); ++col) {
            at(col, row) += rhs.at(col, row);
        }
    }
    return *this;
}

template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator-=(const Matrix& rhs) {
    for (size_type row = 0; row != rows(); ++row) {
        for (size_type col = 0; col != columns(); ++col) {
            at(col, row) -= rhs.at(col, row);
        }
    }
    return *this;
}

template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator*=(const Matrix& rhs) {

}

template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator*=(const value_type& value) {
    for (size_type row = 0; row != rows(); ++row) {
        for (size_type col = 0; col != columns(); ++col) {
            at(col, row) *= value;
        }
    }
    return *this;
}


/// ----------------------------------------------------------------------------
/// T& at()
///
/// @brief returns the value at the index of column x and the row y
/// 
/// @param x: The x-coord on the matrix (from top-left)
/// @param y: The y-coord on the matrix (from top-left)
/// 
/// @throws std::out_of_range()
/// @return The value at (x,y)
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::reference 
Matrix<T>::at(size_type x, size_type y) {

    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("at() out of bounds");
    }
    return (*this)(x,y);
}

/// ----------------------------------------------------------------------------
/// const T& at()
///
/// @brief returns the value at the index of column x and the row y
/// 
/// @param x: The x-coord on the matrix (from top-left)
/// @param y: The y-coord on the matrix (from top-left)
/// 
/// @throws std::out_of_range()
/// @return The value at (x,y)
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::const_reference 
Matrix<T>::at(size_type x, size_type y) const {

    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("at() out of bounds");
    }
    return (*this)(x,y);
}

/// ----------------------------------------------------------------------------
/// T& operator()
///
/// @brief returns the value at the index of column x and the row y. Overloads
/// the operator() to act as the subscript operator '[]'
/// 
/// @param x: The x-coord on the matrix (from top-left)
/// @param y: The y-coord on the matrix (from top-left)
/// 
/// @throws std::out_of_range()
/// @return The value at (x,y)
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::reference 
Matrix<T>::operator()(const size_type& x, const size_type& y) {

    if (x >= m_width || y >= m_height) {
        throw std::out_of_range("at() out of bounds");
    }
    return *(m_data + (m_width * y) + x);

}

/// ----------------------------------------------------------------------------
/// const T& operator()
///
/// @brief returns the value at the index of column x and the row y. Overloads
/// the operator() to act as the subscript operator '[]'
/// 
/// @param x: The x-coord on the matrix (from top-left)
/// @param y: The y-coord on the matrix (from top-left)
/// 
/// @throws std::out_of_range()
/// @return The value at (x,y)
/// ----------------------------------------------------------------------------
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


/// void resize()
/// 
/// @brief Function will resize the Matrix to a new given dimension. If the
/// Matrix is going to be shrunk, then the data within the dimensions will be
/// the same. If the Matrix is going to be expanded, the default value will fill
/// the new area.
/// 
/// @warning Will delete data when shrinking
/// 
/// @note Example:
/// 
/// Matrix(3,3)     resize(2,2)     resize(3,3)
/// 1 2 3           1 2             1 2 0
/// 4 5 6           4 5             4 5 0
/// 7 8 9                           0 0 0
/// 
/// @param new_width: The new width of the Matrix (i.e.: num of columns)
/// @param new_height: The new hieght of the Matrix (i.e.: num of rows)
/// 
/// @throws std::length_error("Minium Dimensions of 1x1 required")
/// 
/// @note If the dimensions are the same then the function does nothing
template <class T>
void Matrix<T>::resize(size_type new_width, size_type new_height) {
    if (new_width == 0 || new_height == 0) {
        throw std::length_error("minimum dimensions of 1x1 required\n");
    }
    if (new_width != m_width || new_height != m_height) {
        size_type new_elements = new_width * new_height;

        pointer temp_data = new value_type[new_elements];

        for (size_type y = 0; y < new_height; ++y) {
            for (size_type x = 0; x < new_width; ++x) {
                if (x >= m_width || y >= m_width) {
                    *(temp_data + x + y * new_width) = value_type();
                }
                else {
                    *(temp_data + x + y * new_width) = at(x, y);
                }
            }
        }

        delete[] m_data;
        m_data = temp_data;
        m_size = new_elements;
        m_width = new_width;
        m_height = new_height;
    }
}

}

#endif /* MATRIX_HPP */