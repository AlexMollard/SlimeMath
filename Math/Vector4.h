//
// Created by alexm on 6/03/2022.
//

#ifndef SLIMEMATHS_VECTOR4_H
#define SLIMEMATHS_VECTOR4_H


#include <cstdint>
#include <ostream>
#include <sstream>
#include "Vector.h"
#include "SlimeAlgebra.h"

template<typename T>
struct Vector<T, 4> {
    using ScalarType = T;

    static const std::size_t components = 4;

    // -- Constructors --
    Vector() :
            x{T(0)},
            y{T(0)},
            z{T(0)},
            w{T(1)} {}

    Vector(const Vector<T, 4> &rhs) :
            x{rhs.x},
            y{rhs.y},
            z{rhs.y},
            w{rhs.z} {}

    explicit Vector(const Vector<T, 2> &xy, const Vector<T, 2> &zw) :
            x{xy.x},
            y{xy.y},
            z{zw.x},
            w{zw.y} {}

    explicit Vector(const Vector<T, 2> &xy, const T &z, const T &w) :
            x{xy.x},
            y{xy.y},
            z{z},
            w{w} {}

    explicit Vector(const Vector<T, 3> &xyz, const T &w) :
            x{xyz.x},
            y{xyz.y},
            z{xyz.z},
            w{w} {}

    explicit Vector(const T &scalar) :
            x{scalar},
            y{scalar},
            z{scalar},
            w{scalar} {}

    Vector(const T &x, const T &y, const T &z, const T &w) :
            x{x},
            y{y},
            z{z},
            w{w} {}

    // -- Math Operators --
    Vector<T, 4> &operator+=(const Vector<T, 4> &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    Vector<T, 4> &operator-=(const Vector<T, 4> &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    Vector<T, 4> &operator*=(const Vector<T, 4> &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        return *this;
    }

    Vector<T, 4> &operator/=(const Vector<T, 4> &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    Vector<T, 4> &operator*=(const T rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    Vector<T, 4> &operator/=(const T rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    Vector<T, 4> operator-() const {
        return Vector<T, 4>{-x, -y, -z, -w};
    }

    // -- Getter/Setter Operators --
    T &operator[](std::size_t component) {
        return *((&x) + component);
    }

    const T &operator[](std::size_t component) const {
        return *((&x) + component);
    }

    template<typename C>
    Vector<C, 4> cast() const {
        return Vector<C, 4>(
                static_cast<C>(x),
                static_cast<C>(y),
                static_cast<C>(z),
                static_cast<C>(w)
        );
    }

    T *ptr() {
        return &x;
    }

    const T *ptr() const {
        return &x;
    }

    // -- Math Functions --
    T length_sq() const {
        return Sm::length_sq(*this);
    }

    T length() const {
        return Sm::length(*this);
    }

    void normalize() {
        Sm::normalize(*this);
    }

    Vector<T, 4> normalized() const {
        auto vec = *this;
        vec.normalize();
        return vec;
    }

    void resize(const T &length) {
        Sm::resize(*this, length);
    }

    // OStream Overrider
    friend std::ostream &operator<<(std::ostream &os, const Vector &m) {
        std::stringstream output;

        output << "[" << m.x << "] ";
        output << "[" << m.y << "] ";
        output << "[" << m.z << "] ";
        output << "[" << m.w << "] ";

        os << output.str();

        return os;
    }

    T x, y, z, w;
};

// Alias
template<typename T>
using Vector4T = Vector<T, 4>;

using Vector4 = Vector4T<int>;
using Vector4f = Vector4T<float>;
using Vector4d = Vector4T<double>;
using Vector4i = Vector4T<std::int32_t>;
using Vector4ui = Vector4T<std::uint32_t>;
using Vector4b = Vector4T<std::int8_t>;
using Vector4ub = Vector4T<std::uint8_t>;
using Vec4 = Vector4f;


#endif //SLIMEMATHS_VECTOR4_H
