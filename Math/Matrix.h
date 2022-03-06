//
// Created by alexm on 6/03/2022.
//

#ifndef SLIMEMATHS_MATRIX_H
#define SLIMEMATHS_MATRIX_H

#include <cstdlib>
#include <initializer_list>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <ostream>

template<typename T, std::size_t Rows, std::size_t Cols>
struct Matrix {
    static_assert(Rows * Cols > 0, "Matrices must consist of at least 1x1 elements");

    // Static Members
    static const std::size_t rows = Rows;
    static const std::size_t columns = Cols;
    static const std::size_t elements = Rows * Cols;

    // Type names
    using ScalerType = T;
    using ThisType = Matrix<T, Rows, Cols>;
    using TransposedType = Matrix<T, Cols, Rows>;

    // Constructors
    Matrix() { load_identity(); };                        //Default Constructor
    Matrix(const ThisType &rhs) { *this = rhs; };          // Copy Constructor

    // Overriders
    // Output
    friend std::ostream &operator<<(std::ostream &os, const ThisType &m) {
        std::stringstream output;
        static int i;
        for (std::size_t r = 0; r < Rows; ++r) {
            for (std::size_t c = 0; c < Cols; ++c) {
                output << "[" << m._element[i] << "]\t";
                i++;
            }
            output << '\n';
        }

        os << output.str();

        return os;
    }

    // Element getters/setters
    T &operator()(std::size_t row, std::size_t col) {
        assert(row < Rows);
        assert(col < Cols);
        return _element[row * Cols + col];
    }

    const T &operator()(std::size_t row, std::size_t col) const {
        assert(row < Rows);
        assert(col < Cols);

        return _element[row * Cols + col];
    }


    T &operator[](std::size_t element) {
        return _element[element];
    }

    const T &operator[](std::size_t element) const {
        return _element[element];
    }

    T *ptr() {
        return &(_element[0]);
    }

    const T *ptr() const {
        return &(_element[0]);
    }

    // Matrix Math
    ThisType &operator+=(const ThisType &rhs) {
        for (std::size_t i = 0; i < ThisType::elements; ++i)
            _element[i] += rhs._element[i];
        return *this;
    }

    ThisType &operator-=(const ThisType &rhs) {
        for (std::size_t i = 0; i < ThisType::elements; ++i)
            _element[i] -= rhs._element[i];
        return *this;
    }

    ThisType &operator*=(const ThisType &rhs) {
        *this = (*this * rhs);
        return *this;
    }

    ThisType &operator*=(const T &rhs) {
        for (std::size_t i = 0; i < ThisType::elements; ++i)
            _element[i] *= rhs;
        return *this;
    }

    ThisType &operator=(const ThisType &rhs) {
        if (this == &rhs)
            return *this;

        for (std::size_t i = 0; i < ThisType::elements; ++i)
            _element[i] = rhs._element[i];
        return *this;
    }

    // Get element AT
    T &at(std::size_t col, std::size_t row) {
        return (*this)(row, col);
    }

    const T &at(std::size_t col, std::size_t row) const {
        return (*this)(row, col);
    }

    // Functions
    void load_identity() {
        for (std::size_t r = 0; r < Rows; ++r)
            for (std::size_t c = 0; c < Cols; ++c) {
                (*this)(r, c) = (r == c ? T(1) : T(0));
            }
    }

    static ThisType identity() {
        ThisType result;
        result.load_identity();
        return result;
    }

    void reset() {
        for (std::size_t i = 0; i < ThisType::elements; ++i)
            _element[i] = T(0);
    }

    //Returns a transposed matrix
    TransposedType transposed() const {
        TransposedType result;

        for (std::size_t r = 0; r < Rows; ++r)
            for (std::size_t c = 0; c < Cols; ++c) {
                result(c, r) = (*this)(r, c);
            }

        return result;
    }

    // Transposes current matrix.
    void transpose() {
        for (std::size_t i = 0; i + 1 < Cols; ++i) {
            for (std::size_t j = 1; j + i < Cols; ++j) {
                std::swap(
                        _element[i * (Cols + 1) + j],
                        _element[(j + i) * Cols + i]
                );
            }
        }
    }

    T trace() const {
        T trace = T(0);

        for (std::size_t i = 0; i < Rows; ++i)
            trace += (*this)(i, i);

        return trace;
    }


    template<typename C>
    Matrix<C, Rows, Cols> Cast() const {
        Matrix<C, Rows, Cols> result{};

        for (std::size_t i = 0; i < ThisType::elements; ++i)
            result[i] = static_cast<C>(_element[i]);

        return result;
    }


private:
    T _element[ThisType::elements];
};


// Global Operators

template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols> &lhs, const Matrix<T, Rows, Cols> &rhs) {
    auto result = lhs;
    result += rhs;
    return result;
}

template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols> &lhs, const Matrix<T, Rows, Cols> &rhs) {
    auto result = lhs;
    result -= rhs;
    return result;
}

template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> operator*(const Matrix<T, Rows, Cols> &lhs, const T &rhs) {
    auto result = lhs;
    result *= rhs;
    return result;
}

template<typename T, std::size_t Rows, std::size_t Cols>
Matrix<T, Rows, Cols> operator*(const T &lhs, const Matrix<T, Rows, Cols> &rhs) {
    auto result = rhs;
    result *= lhs;
    return result;
}

template<typename T, std::size_t Rows, std::size_t ColsRows, std::size_t Cols>
Matrix<T, Rows, Cols> operator*(const Matrix<T, Rows, ColsRows> &lhs, const Matrix<T, ColsRows, Cols> &rhs) {
    Matrix<T, Rows, Cols> result{};
    result.reset();

    for (std::size_t r = 0; r < Rows; ++r)
        for (std::size_t c = 0; c < Cols; ++c) {
            result(r, c) = T(0);
            for (std::size_t i = 0; i < ColsRows; ++i)
                result(r, c) += lhs(r, i) * rhs(i, c);
        }

    return result;
}

// --Default types--

// Matrix 2x2
using Mat2 = Matrix<float, 2, 2>;
using Mat2i = Matrix<int, 2, 2>;
using Mat2d = Matrix<double, 2, 2>;

// Matrix 3x3
using Mat3 = Matrix<float, 3, 3>;
using Mat3i = Matrix<int, 3, 3>;
using Mat3d = Matrix<double, 3, 3>;

// Matrix 4x4
using Mat4 = Matrix<float, 4, 4>;
using Mat4i = Matrix<int, 4, 4>;
using Mat4d = Matrix<double, 4, 4>;

#endif //SLIMEMATHS_MATRIX_H
