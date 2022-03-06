//
// Created by alexm on 6/03/2022.
//

#ifndef SLIMEMATHS_VECTOR_H
#define SLIMEMATHS_VECTOR_H

#include <cstdlib>
#include <algorithm>

template <typename T, std::size_t N>
struct Vector {

    using ScalarType = T;
    static const std::size_t components = N;

    // Constructors
    Vector()
    {
        std::fill(std::begin(_element), std::end(_element), T(0));
    }

    Vector(const Vector<T, N>& rhs)
    {
        std::copy(std::begin(rhs._element), std::end(rhs._element), _element);
    }

    explicit Vector(const T& scalar)
    {
        std::fill(std::begin(_element), std::end(_element), scalar);
    }

    //Overriders

    // Math operators
    Vector<T, N>& operator += (const Vector<T, N>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _element[i] += rhs[i];
        return *this;
    }

    Vector<T, N>& operator -= (const Vector<T, N>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _element[i] -= rhs[i];
        return *this;
    }

    Vector<T, N>& operator *= (const Vector<T, N>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _element[i] *= rhs[i];
        return *this;
    }

    Vector<T, N>& operator /= (const Vector<T, N>& rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _element[i] /= rhs[i];
        return *this;
    }

    Vector<T, N>& operator *= (const T rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _element[i] *= rhs;
        return *this;
    }

    Vector<T, N>& operator /= (const T rhs)
    {
        for (std::size_t i = 0; i < N; ++i)
            _element[i] /= rhs;
        return *this;
    }

    // Getter/Setter operators
    T& operator [] (std::size_t component)
    {
        static_assert(component < N);
        return _element[component];
    }

    const T& operator [] (std::size_t component) const
    {
        static_assert(component < N);
        return _element[component];
    }

    Vector<T, N> operator - () const
    {
        auto result = *this;
        for (std::size_t i = 0; i < N; ++i)
            result[i] = -result[i];
        return result;
    }

    template <typename C>
    Vector<C, N> Cast() const
    {
        Vector<C, N> result {};

        for (std::size_t i = 0; i < N; ++i)
            result[i] = static_cast<C>(_element[i]);

        return result;
    }

    T* ptr()
    {
        return _element;
    }

    const T* ptr() const
    {
        return _element;
    }

private:

    T _element[N];
};

// Global Operators

template <typename T, std::size_t N>
Vector<T, N> operator + (const Vector<T, N>& lhs, const Vector<T, N>& rhs)
{
    auto result = lhs;
    result += rhs;
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator - (const Vector<T, N>& lhs, const Vector<T, N>& rhs)
{
    auto result = lhs;
    result -= rhs;
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator * (const Vector<T, N>& lhs, const Vector<T, N>& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator / (const Vector<T, N>& lhs, const Vector<T, N>& rhs)
{
    auto result = lhs;
    result /= rhs;
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator * (const Vector<T, N>& lhs, const T& rhs)
{
    auto result = lhs;
    result *= rhs;
    return result;
}

//! \note This implementation is equivavlent to (rhs * lhs) for optimization purposes.
template <typename T, std::size_t N>
Vector<T, N> operator * (const T& lhs, const Vector<T, N>& rhs)
{
    auto result = rhs;
    result *= lhs;
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator / (const Vector<T, N>& lhs, const T& rhs)
{
    auto result = lhs;
    result /= rhs;
    return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator / (const T& lhs, const Vector<T, N>& rhs)
{
    auto result = Vector<T, N> { lhs };
    result /= rhs;
    return result;
}

// --Default types--

// Vector 2
using Vec2 = Vector<float, 2>;
using Vec2i = Vector<int, 2>;
using Vec2d = Vector<double, 2>;

// Vector 3
using Vec3 = Vector<float, 3>;
using Vec3i = Vector<int, 3>;
using Vec3d = Vector<double, 3>;

// Vector 4
using Vec4 = Vector<float, 4>;
using Vec4i = Vector<int, 4>;
using Vec4d = Vector<double, 4>;


#endif //SLIMEMATHS_VECTOR_H
