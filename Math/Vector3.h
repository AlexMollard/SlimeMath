//
// Created by alexm on 6/03/2022.
//

#ifndef SLIMEMATHS_VECTOR3_H
#define SLIMEMATHS_VECTOR3_H

#include <cstdint>
#include <ostream>
#include <sstream>
#include "Vector.h"
#include "SlimeAlgebra.h"

template<typename T>
struct Vector<T, 3> {
    using ScalarType = T;

    static const std::size_t components = 3;

    // -- Constructors --
    Vector() :
            x{T(0)},
            y{T(0)},
            z{T(0)} {}

    Vector(const Vector<T, 3> &rhs) :
            x{rhs.x},
            y{rhs.y},
            z{rhs.z} {}

    explicit Vector(const Vector<T, 4> &rhs) :
            x{rhs.x},
            y{rhs.y},
            z{rhs.z} {
    }

    explicit Vector(const Vector<T, 2> &xy, const T &z) :
            x{xy.x},
            y{xy.y},
            z{z} {
    }

    explicit Vector(const T &scalar) :
            x{scalar},
            y{scalar},
            z{scalar} {
    }

    Vector(const T &x, const T &y, const T &z) :
            x{x},
            y{y},
            z{z} {
    }

    // -- Math Operators --
    Vector<T, 3> &operator+=(const Vector<T, 3> &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector<T, 3> &operator-=(const Vector<T, 3> &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vector<T, 3> &operator*=(const Vector<T, 3> &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    Vector<T, 3> &operator/=(const Vector<T, 3> &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    Vector<T, 3> &operator*=(const T rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    Vector<T, 3> &operator/=(const T rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    Vector<T, 3> operator-() const {
        return Vector<T, 3>{-x, -y, -z};
    }


    // -- Getter/Setter Operators --
    T &operator[](std::size_t component) {
        return *((&x) + component);
    }

    const T &operator[](std::size_t component) const {
        return *((&x) + component);
    }

    template<typename C>
    Vector<C, 3> cast() const {
        return Vector<C, 3>(
                static_cast<C>(x),
                static_cast<C>(y),
                static_cast<C>(z)
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

    Vector<T, 3> normalized() const {
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

        os << output.str();

        return os;
    }


    T x, y, z;
};

// Alias
template<typename T>
using Vector3T = Vector<T, 3>;

using Vector3 = Vector3T<int>;
using Vector3f = Vector3T<float>;
using Vector3d = Vector3T<double>;
using Vector3i = Vector3T<std::int32_t>;
using Vector3ui = Vector3T<std::uint32_t>;
using Vector3b = Vector3T<std::int8_t>;
using Vector3ub = Vector3T<std::uint8_t>;
using Vec3 = Vector3f;

#endif //SLIMEMATHS_VECTOR3_H
