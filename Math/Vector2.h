//
// Created by alexm on 6/03/2022.
//

#ifndef SLIMEMATHS_VECTOR2_H
#define SLIMEMATHS_VECTOR2_H

#include <cstdint>
#include <ostream>
#include <sstream>
#include "Vector.h"
#include "SlimeAlgebra.h"

template<typename T>
struct Vector<T, 2> {
    using ScalarType = T;

    static const std::size_t components = 2;

    // -- Constructors --
    Vector() :
            x{T(0)},
            y{T(0)} {}

    Vector(const Vector<T, 2> &rhs) :
            x{rhs.x},
            y{rhs.y} {}

    explicit Vector(const Vector<T, 3> &rhs) :
            x{rhs.x},
            y{rhs.y} {}

    explicit Vector(const Vector<T, 4> &rhs) :
            x{rhs.x},
            y{rhs.y} {}


    explicit Vector(const T &scalar) :
            x{scalar},
            y{scalar} {}

    Vector(const T &x, const T &y) :
            x{x},
            y{y} {}

    // -- Math Operators --
    Vector<T, 2> &operator+=(const Vector<T, 2> &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector<T, 2> &operator-=(const Vector<T, 2> &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector<T, 2> &operator*=(const Vector<T, 2> &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vector<T, 2> &operator/=(const Vector<T, 2> &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Vector<T, 2> &operator*=(const T rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vector<T, 2> &operator/=(const T rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    Vector<T, 2> operator-() const {
        return Vector<T, 2>{-x, -y};
    }


    // -- Getter/Setter Operators --
    T &operator[](std::size_t component) {
        return *((&x) + component);
    }

    const T &operator[](std::size_t component) const {
        return *((&x) + component);
    }

    template<typename C>
    Vector<C, 2> cast() const {
        return Vector<C, 2>(
                static_cast<C>(x),
                static_cast<C>(y)
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

    Vector<T, 2> normalized() const {
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

        os << output.str();

        return os;
    }


    T x, y;
};

// Alias
template<typename T>
using Vector2T = Vector<T, 2>;

using Vector2 = Vector2T<int>;
using Vector2f = Vector2T<float>;
using Vector2d = Vector2T<double>;
using Vector2i = Vector2T<std::int32_t>;
using Vector2ui = Vector2T<std::uint32_t>;
using Vector2b = Vector2T<std::int8_t>;
using Vector2ub = Vector2T<std::uint8_t>;
using Vec2 = Vector2f;


#endif //SLIMEMATHS_VECTOR2_H
