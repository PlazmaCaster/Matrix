#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdexcept>
//#include <memory>         // TODO: use smart pointers for the love of god
#include <iterator>
#include <initializer_list>
#include <vector>
#include <utility>


/// TODO: Create custom exception class

namespace Tensor {

/// M rows by N columns ( M x N )
/// Matrix<T>
/// Row-major matrix class. Allows for basic arithmetic operations on the matrices
/// Indices follow the conventional format seen in Mathematics (row,column)
template <class T>
// -------------------------------------------------------------------------------------------------
// Matrix
// -------------------------------------------------------------------------------------------------
class Matrix {
public:
    // ---------------------------------------------------------------------------------------------
    // Iterator
    // ---------------------------------------------------------------------------------------------
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(pointer ptr = nullptr) : m_ptr(ptr) {}
        Iterator(const Iterator& other) : m_ptr(other.m_ptr) {}

        // ----- Access Overloads ----------------------------------------------
        reference operator*() const { return *m_ptr; };
        pointer operator->() const { return m_ptr; }
        reference operator[](difference_type rhs) const { return m_ptr[rhs]; }

        // ----- Comparison Overloads ------------------------------------------
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
        // ----- Prefix & Postfix Overlodas ------------------------------------
        Iterator& operator++() { ++m_ptr; return *this; }
        Iterator& operator++(int) { Iterator tmp(*this); ++m_ptr; return tmp; }
        Iterator& operator--() { --m_ptr; return *this; }
        Iterator& operator--(int) { Iterator tmp(*this); --m_ptr; return tmp; }

        // ----- Iterator Math Overloads ---------------------------------------
        Iterator& operator+=(difference_type rhs) { m_ptr += rhs; return *this; }
        Iterator& operator-=(difference_type rhs) { m_ptr -= rhs; return *this; }

        difference_type operator-(const Iterator& rhs) const { return m_ptr - rhs.m_ptr; }

        Iterator operator+(difference_type rhs) { return Iterator(m_ptr + rhs); }
        Iterator operator-(difference_type rhs) { return Iterator(m_ptr - rhs); }

        friend Iterator operator+(difference_type lhs, const Iterator& rhs) {
            return Iterator(lhs + rhs.m_ptr);
        }
        friend Iterator operator-(difference_type lhs, const Iterator& rhs) {
            return Iterator(lhs - rhs.m_ptr);
        }

    private:
        pointer m_ptr;
    };
    // ---------------------------------------------------------------------------------------------
    using value_type = T;
    using size_type = std::size_t;
    using coordinate = std::pair<size_type, size_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    // ----- Constructors & Initialization -------------------------------------

    // Default Constructor
    Matrix(const size_type& height = 1, const size_type& width = 1,
           const value_type& value = value_type());

    // Initializer_list Constructor
    Matrix(const std::initializer_list<std::initializer_list<value_type>>& ilist);

    Matrix(const std::vector<std::vector<value_type>>& vec);

    // Copy Constructor
    Matrix(const Matrix<T>& other);

    // Move Constructor
    Matrix(Matrix<T>&& other) noexcept;

    // Destructor
    ~Matrix() { delete[] m_data; }

    // Copy Assignment Operator
    Matrix& operator=(const Matrix<T>& rhs);

    // Move Assignment Operator
    Matrix& operator=(Matrix<T>&& rhs) noexcept;

    // ----- Indexing functions ------------------------------------------------
    reference at(size_type row, size_type col);
    const_reference at(size_type row, size_type col) const;

    reference operator()(const size_type& row, const size_type& col);
    const_reference operator()(const size_type& row, const size_type& col) const;

    Iterator begin() const { return Iterator(m_data); }
    Iterator end() const { return Iterator(m_data + m_size); }
    size_type columns() const { return m_width; }
    size_type rows() const { return m_height; }

    // ----- Basic Matrix Operations -------------------------------------------
    Matrix& operator+=(const Matrix& rhs);            // M + N
    Matrix& operator-=(const Matrix& rhs);            // M - N
    Matrix& operator*=(const Matrix& rhs);            // M * N
    Matrix& operator*=(const value_type& rhs);        // M * Scalar
    Matrix operator+() const { return *this; }        // M * 1
    Matrix operator-() const { return (*this * -1); } // M * -1
    
    // ---- MISC. --------------------------------------------------------------
    size_type size() const { return m_size; }

    Matrix sub_matrix(const coordinate& top_left, const coordinate& bot_right) const;
    Matrix sub_matrix(const size_type& top_row, const size_type& left_col,
                      const size_type& bot_row, const size_type& right_col) const;

    Matrix transpose() const;

    void resize(size_type new_width, size_type new_height);

protected:
    template <class It>
    size_type largest_row(const It& first, const It& last) const;

    template <class It>
    void initialize(const It& first, const It& last);

    size_type m_height;
    size_type m_width;
    size_type m_size;
    pointer m_data;
};
// -------------------------------------------------------------------------------------------------

// ----- Non-Member Overloads --------------------------------------------------
template <class T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs);

template <class T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs) {
    return lhs += rhs;
}

template <class T>
Matrix<T> operator-(Matrix<T> lhs, const Matrix<T>& rhs) {
    return lhs -= rhs;
}

template <class T>
Matrix<T> operator*(Matrix<T> lhs, const Matrix<T>& rhs) {
    return lhs *= rhs;
}

template <class T>
Matrix<T> operator*(Matrix<T> lhs, const T& rhs) {
    return lhs *= rhs;
}

template <class T>
Matrix<T> operator*(const T& lhs, Matrix<T> rhs) {
    return rhs *= lhs;
}

//----- Definitions --------------------------------------------------------------------------------

/// ----------------------------------------------------------------------------
/// Matrix()
/// 
/// @brief Default / Initialized Constructor
/// 
/// @param width: How wide the Matrix is (i.e.: number of columns)
/// @param height: How tall the Matrix is (i.e.: number of rows)
/// @param value: What to fill the Matrix 
/// 
/// @note default width & height of 1 x 1
/// @note default value is whatever the default ctor of value_type
/// 
/// @throws std::invalid_argument: non-positive size not allowed
/// ----------------------------------------------------------------------------
template <class T>
Matrix<T>::Matrix(const size_type& height, const size_type& width,
                  const value_type& value) :
                  m_height(height), m_width(width), m_size(width * height), m_data(nullptr) {
    if (height == 0 || width == 0) {
        throw std::invalid_argument("minimum dimensions of 1x1 required\n");
    }
    
    m_data = new value_type[m_size];
    //std::cout << m_data << '\n';
    
    for (size_type i = 0; i < m_size; ++i) {
        m_data[i] = value;
    }
}

template <class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<value_type>>& init) :
    m_height(init.size()), m_width(0), m_size(0), m_data(nullptr) {

    m_width = largest_row(init.begin(), init.end());
    m_size = m_width * m_height;
    m_data = new value_type[m_size];

    for (Iterator it = begin(); it != end(); ++it) {
        *it = value_type();
    }
    initialize(init.begin(), init.end());

}

template <class T>
Matrix<T>::Matrix(const std::vector<std::vector<value_type>>& vec) :
    m_height(vec.size()), m_width(0), m_size(0), m_data(nullptr) {

    m_width = largest_row(vec.begin(), vec.end());
    m_size = m_width * m_height;
    m_data = new value_type[m_size];

    for (Iterator it = begin(); it != end(); ++it) {
        *it = value_type();
    }
    initialize(vec.begin(), vec.end());

}

/// ----------------------------------------------------------------------------
/// Matrix()
/// 
/// @brief Copy Constructor
/// 
/// @param other: Another Lvalue matrix
/// ----------------------------------------------------------------------------
template <class T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_size = other.m_size;

    m_data = new value_type[m_width * m_height];
    std::copy(other.begin(), other.end(), m_data);
}

/// ----------------------------------------------------------------------------
/// Matrix()
/// 
/// @brief Move Constructor
/// 
/// @param other: an Rvalue matrix
/// ----------------------------------------------------------------------------
template <class T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept {
    m_height = std::exchange(other.m_height, 0);
    m_width  = std::exchange(other.m_width, 0);
    m_size   = std::exchange(other.m_size, 0);
    m_data   = std::exchange(other.m_data, nullptr);
}

/// ----------------------------------------------------------------------------
/// Matrix<T>& operator=()
/// 
/// @brief Copy Assignment Operator
/// 
/// @param rhs: An Lvalue matrix to be copied
/// 
/// @note does nothing in case of self assignment
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator=(const Matrix& rhs) {
    if (this != &rhs) {
        delete[] m_data;

        m_height = rhs.rows();
        m_width  = rhs.columns();
        m_size   = rhs.size();
        m_data   = new value_type[m_width * m_height];
    
        std::copy(rhs.begin(), rhs.end(), begin());
    }
    return *this;
}

/// ----------------------------------------------------------------------------
/// Matrix<T>& operator=()
/// 
/// @brief Move Assignment Constructor
/// 
/// @param rhs: An Rvalue Matrix to be moved
/// 
/// @note does nothing in case of self assignment
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::Matrix&
Matrix<T>::operator=(Matrix<T>&& rhs) noexcept {

    if (this != &rhs) {
        delete[] m_data;

        m_height = std::exchange(rhs.m_height, 0);
        m_width  = std::exchange(rhs.m_width, 0);
        m_size   = std::exchange(rhs.m_size, 0);
        m_data   = std::exchange(rhs.m_data, nullptr);
    }
    return *this;
}

/// ----------------------------------------------------------------------------
/// T& at()
///
/// @brief returns the value at the index of specified row and column
/// 
/// @param row: The row on the matrix (from top to bottom)
/// @param col: The column on the matrix (from left to right)
/// 
/// @throws std::out_of_range()
/// @return The value at (row,col)
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::reference
Matrix<T>::at(size_type row, size_type col) {

    if (row >= m_height || col >= m_width) {
        throw std::out_of_range("at() out of bounds");
    }
    return (*this)(row, col);
}

/// ----------------------------------------------------------------------------
/// const T& at() const
///
/// @brief returns the value at the index of specified row and column
/// 
/// @param row: The row on the matrix (from top to bottom)
/// @param col: The column on the matrix (from left to right)
/// 
/// @throws std::out_of_range()
/// @return The value at (row,col)
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::const_reference
Matrix<T>::at(size_type row, size_type col) const {

    if (row >= m_height || col >= m_width) {
        throw std::out_of_range("at() out of bounds");
    }
    return (*this)(row, col);
}

/// ----------------------------------------------------------------------------
/// T& operator()()
///
/// @brief returns the value at the index of "row" and the "col". Overloads
/// the operator() to act as the subscript operator '[]'
/// 
/// @param row: The row on the matrix (from top to bottom)
/// @param col: The column on the matrix (from left to right)
/// 
/// @throws std::out_of_range()
/// @return The value at (row,col)
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::reference
Matrix<T>::operator()(const size_type& row, const size_type& col) {

    if (row >= m_height || col >= m_width) {
        throw std::out_of_range("at() out of bounds");
    }
    return *(m_data + (m_width * row) + col);
}

/// ----------------------------------------------------------------------------
/// const T& operator()() const
///
/// @brief returns the value at the index of "row" and the "col". Overloads
/// the operator() to act as the subscript operator '[]'
/// 
/// @param row: The row on the matrix (from top to bottom)
/// @param col: The column on the matrix (from left to right)
/// 
/// @throws std::out_of_range()
/// @return The value at (row,col)
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::const_reference
Matrix<T>::operator()(const size_type& row, const size_type& col) const {

    if (row >= m_height || col >= m_width) {
        throw std::out_of_range("at() out of bounds");
    }
    return *(m_data + (m_width * row) + col);
}

/// ----------------------------------------------------------------------------
/// Matrix<T>& operator+=()
/// 
/// @brief adds the value of each right matrix index to the corresponding left 
/// matrix index.
/// 
/// @param rhs: Right side matrix
/// 
/// @throws TODO: EXCEPTION CLASS
/// 
/// @returns *this: returns self after addition
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator+=(const Matrix& rhs) {
    // TODO: Exception class
    // if (m_width != rhs.m_width || m_height != rhs.m_height) {
    //     throw ERROR
    // }
    for (size_type row = 0; row != rows(); ++row) {
        for (size_type col = 0; col != columns(); ++col) {
            at(row, col) += rhs.at(row, col);
        }
    }
    return *this;
}

/// ----------------------------------------------------------------------------
/// Matrix<T>& operator-=()
/// 
/// @brief subtracts the value of each right matrix index to the corresponding 
/// left matrix index.
/// 
/// @param rhs: Right side matrix
/// 
/// @throws TODO: EXCEPTION CLASS
/// 
/// @returns *this: returns self after subtraction
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator-=(const Matrix& rhs) {
    for (size_type row = 0; row != rows(); ++row) {
        for (size_type col = 0; col != columns(); ++col) {
            at(row, col) -= rhs.at(row, col);
        }
    }
    return *this;
}

/// ----------------------------------------------------------------------------
/// Matrix<T>& operator*=()
/// 
/// @brief preforms the dot product of two matrices assuming they have 
/// dimensions (A x M) and (M x B)
/// 
/// @param rhs: Right side matrix
///
/// @throws TODO: EXCEPTION CLASS
/// 
/// @returns *this: returns self after multiplication
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator*=(const Matrix& rhs) {
    // TODO: Exception Class 
    //if (m_width != rhs.m_height) {
    //    throw 
    //}
    
    Matrix temp(rows(), rhs.columns());

    for (size_type row = 0; row != temp.rows(); ++row) {
        for (size_type col = 0; col != temp.columns(); ++col) {
            for (size_type lambda = 0; lambda != columns(); ++lambda) {
                temp(row, col) += at(row, lambda) * rhs.at(lambda, col);
            }
        }
    }
    *this = std::move(temp);

    return *this;
}

/// ----------------------------------------------------------------------------
/// Matrix<T>& operator*=()
/// 
/// @brief Preforms scalar multiplication to the entierty of matrix
/// 
/// @param value: The scalar value
///
/// @throws TODO: EXCEPTION CLASS
/// 
/// @returns *this: returns self after multiplication
/// ----------------------------------------------------------------------------
template <class T>
typename Matrix<T>::Matrix& 
Matrix<T>::operator*=(const value_type& value) {

    for (size_type row = 0; row != rows(); ++row) {
        for (size_type col = 0; col != columns(); ++col) {
            at(row, col) *= value;
        }
    
    }
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::sub_matrix(const coordinate& top_left, const coordinate& bot_right) const {
    return sub_matrix(top_left.first, top_left.second, bot_right.first, bot_right.second);
}

template <class T>
Matrix<T> Matrix<T>::sub_matrix(const size_type& top_row, const size_type& left_col,
                                const size_type& bot_row, const size_type& right_col) const {
    size_type sub_rows = bot_row - top_row;
    size_type sub_cols = right_col - left_col;
    size_type sub_row_idx = 0;
    size_type sub_col_idx = 0;

    Matrix<T> sub_mtx(sub_rows, sub_cols);

    for (auto i = top_row; i != bot_row; ++i) {
        for (auto j = left_col; j != right_col; ++j) {
            sub_mtx(sub_row_idx, sub_col_idx) = at(i, j);
            ++sub_col_idx;
        }
        sub_col_idx = 0;
        ++sub_row_idx;
    }
    return sub_mtx;
}

template <class T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> transpose(m_width,m_height);

    for (size_type original_row = 0; original_row != rows(); ++original_row) {
        for (size_type original_col = 0; original_col != columns(); ++original_col) {
            transpose(original_col, original_row) = at(original_row, original_col);
        }
    }
    return transpose;
}

/// ----------------------------------------------------------------------------
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
/// ----------------------------------------------------------------------------
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
                
                // Insert default value when expanding for safety
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

/// ----------------------------------------------------------------------------
/// bool operator==()
/// 
/// @brief Tests for equality between to Matrix<T> : same size & same contents
/// 
/// @param lhs, left hand arg
/// @param rhs, right hand arg
/// 
/// @return equal: true if Matrices are equivalent
/// ----------------------------------------------------------------------------
template <class T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    bool equal = true;

    if (lhs.rows() != rhs.rows() || lhs.columns() != rhs.columns()) {
        equal = false;
    }

    if (equal) {
        auto lhs_iter = lhs.begin();
        auto rhs_iter = rhs.begin();

        while (lhs_iter != lhs.end() || equal) {
            if (*lhs_iter != *rhs_iter) {
                equal = false;
            }
            ++lhs_iter;
            ++rhs_iter;
        }
    }
    return equal;
}

template <class T>
template <class It>
typename Matrix<T>::size_type Matrix<T>::largest_row(const It& first, const It& last) const {
    size_type largest = 0;
    for (auto iter = first; iter != last; ++iter) {
        if (iter->size() > largest) largest = iter->size();
    }
    return largest;
}

template <class T>
template <class It>
void Matrix<T>::initialize(const It& first, const It& last) {
    auto copy_location = this->begin();
    for (auto iter = first; iter != last; ++iter) {
        std::copy(iter->begin(), iter->end(), copy_location);
        copy_location += m_width;
    }
}

} /* Namespace Tensor */

#endif /* MATRIX_HPP */