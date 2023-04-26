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
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer ptr = nullptr) : m_ptr(ptr) {}
        Iterator(const Iterator& other) : m_ptr(other.m_ptr) {}
        reference operator* () const { return *m_ptr; };
        Iterator& operator++() { ++m_ptr; return *this; }
        Iterator& operator--() { --m_ptr; return *this; }


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
        friend Iterator& operator+(const Iterator& lhs, const Iterator& rhs) {
            return
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

    /// ----- Constructors & Initialization -----------------------------------
    // Default Constructor
    Matrix();

    // Initialized Constructor
    Matrix(const size_type& rows, const size_type& cols, 
        const value_type& value = value_type());

    // Initializer_list Constructor
    Matrix(
        const size_type& rows, const size_type& cols, 
        const std::initializer_list<value_type>& init
    );

    // Copy Constructor
    Matrix(const Matrix& other);

    // Move Constructor
    Matrix(Matrix&& other);

    // Destructor
    ~Matrix();

    // Copy Assignment Operator
    Matrix& operator=(const Matrix& rhs);

    // Move Assignment Operator
    Matrix& operator=(Matrix&& rhs);

    /// ----- Indexing functions ----------------------------------------------
          reference at(const size_type& x, const size_type& y);
    const_reference at(const size_type& x, const size_type& y) const;

          reference operator()(const size_type& x, const size_type& y);
    const_reference operator()(const size_type& x, const size_type& y) const;


    /// ----- Basic Matrix Operations -----------------------------------------
    Matrix& operator+=(const Matrix& rhs);       // M + N
    Matrix& operator-=(const Matrix& rhs);       // M - N
    Matrix& operator*=(const Matrix& rhs);       // M * N
    Matrix& operator/=(const Matrix& rhs);       // M / N

    /// ----- Scale Multiplication --------------------------------------------
           Matrix& operator*=(const value_type& value); // M * Scalar
    friend Matrix& operator*=(const value_type& value, const Matrix& rhs);

    /// ---- MISC. ------------------------------------------------------------

/// ----- Private Members -----------------------------------------------------
//private:
    size_type m_width;
    size_type m_length;
    pointer m_data;
};
/// ----- Non-Member Overloads ------------------------------------------------
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

///----- Definition -----------------------------------------------------------
template <class T>
Matrix<T>::Matrix() {
    m_width = 0;
    m_length = 0;
    m_data = nullptr;
}





}

#endif /* MATRIX_H */