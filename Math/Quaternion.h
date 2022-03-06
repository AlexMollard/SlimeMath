//
// Created by alexm on 3/03/2022.
//

#ifndef SLIMEMATHS_QUATERNION_H
#define SLIMEMATHS_QUATERNION_H

#include "SlimeAlgebra.h"
#include "Matrix.h"
#include "MatrixConversion.h"

template<typename T>
struct Quaternion {
    static_assert(std::is_floating_point<T>::value, "quaternions can only be used with floating point types");

    using ScalarType = T;
    static const std::size_t components = 4;


    Quaternion() :
            x{T(0)},
            y{T(0)},
            z{T(0)},
            w{T(1)} {
    }

    Quaternion(const Quaternion<T> &rhs) :
            x{rhs.x},
            y{rhs.y},
            z{rhs.z},
            w{rhs.w} {
    }

    Quaternion(const T &x, const T &y, const T &z, const T &w) :
            x{x},
            y{y},
            z{z},
            w{w} {
    }

    template<template<typename, std::size_t, std::size_t> class M, std::size_t Rows, std::size_t Cols>
    explicit Quaternion(const M<T, Rows, Cols> &matrix) {
        Sm::matrix_to_quaternion(*this, matrix);
    }

    Quaternion<T> &operator+=(const Quaternion<T> &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    Quaternion<T> &operator-=(const Quaternion<T> &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    Quaternion<T> &operator*=(const Quaternion<T> &rhs) {
        *this = (*this * rhs);
        return *this;
    }

    Quaternion<T> &operator*=(const T &rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    T &operator[](std::size_t component) {
        return *((&x) + component);
    }

    const T &operator[](std::size_t component) const {
        return *((&x) + component);
    }

    void Normalize() {
        Sm::normalize(*this);
    }

    Quaternion<T> Normalized() const {
        auto quat = *this;
        quat.Normalize();
        return quat;
    }

    void LoadIdentity() {
        x = y = z = T(0);
        w = T(1);
    }

    void MakeInverse() {
        x = -x;
        y = -y;
        z = -z;
    }

    Quaternion<T> Inverse() const {
        return Quaternion<T>{-x, -y, -z, w};
    }

    void slerp(const Quaternion<T> &from, Quaternion<T> to, const T &t) {
        *this = Sm::slerp(from, to, t);
    }

    void set_euler_angles(const Vector<T, 3> &angles) {
        const T cr = std::cos(angles.x / T(2));
        const T cp = std::cos(angles.y / T(2));
        const T cy = std::cos(angles.z / T(2));

        const T sr = std::sin(angles.x / T(2));
        const T sp = std::sin(angles.y / T(2));
        const T sy = std::sin(angles.z / T(2));

        const T cpcy = cp * cy;
        const T spsy = sp * sy;
        const T cpsy = cp * sy;
        const T spcy = sp * cy;

        x = sr * cpcy - cr * spsy;
        y = cr * spcy + sr * cpsy;
        z = cr * cpsy - sr * spcy;
        w = cr * cpcy + sr * spsy;

        Normalize();
    }

    void get_euler_angles(Vector<T, 3> &angles) const {
        const T xx = x * x;
        const T yy = y * y;
        const T zz = z * z;
        const T ww = w * w;

        angles.x = std::atan2(T(2) * (y * z + x * w), -xx - yy + zz + ww);
        angles.y = std::asin(Clamp(T(2) * (y * w - x * z), T(-1), T(1)));
        angles.z = std::atan2(T(2) * (x * y + z * w), xx - yy - zz + ww);
    }

    void set_angle_axis(const Vector<T, 3> &axis, const T &angle) {
        const T halfAngle = angle / T(2);
        const T sine = std::sin(halfAngle);

        x = sine * axis.x;
        y = sine * axis.y;
        z = sine * axis.z;
        w = std::cos(halfAngle);
    }

    void get_angle_axis(Vector<T, 3> &axis, T &angle) const {
        const T scale = std::sqrt(x * x + y * y + z * z);

        if ((std::abs(scale) <= std::numeric_limits<T>::epsilon()) || w > T(1) || w < T(-1)) {
            axis.x = T(0);
            axis.y = T(1);
            axis.z = T(0);
            angle = T(0);
        } else {
            const T invScale = T(1) / scale;
            axis.x = x * invScale;
            axis.y = y * invScale;
            axis.z = z * invScale;
            angle = T(2) * std::acos(w);
        }
    }

    Mat3 ToMatrix3() const {
        Mat3 result{};
        Sm::quaternion_to_matrix(result, *this);
        return result;
    }

    Mat3 ToMatrix3Transposed() const {
        Mat3 result{};
        Sm::quaternion_to_matrix_transposed(result, *this);
        return result;
    }

    template<typename C>
    Quaternion<C> Cast() const {
        return Quaternion<C>(
                static_cast<C>(x),
                static_cast<C>(y),
                static_cast<C>(z),
                static_cast<C>(w)
        );
    }

    T *Ptr() {
        return &x;
    }

    const T *Ptr() const {
        return &x;
    }

    static Quaternion<T> EulerAngles(const Vector<T, 3> &angles) {
        Quaternion<T> result;
        result.SetEulerAngles(angles);
        return result;
    }

    static Quaternion<T> AngleAxis(const Vector<T, 3> &axis, const T &angle) {
        Quaternion<T> result;
        result.SetAngleAxis(axis, angle);
        return result;
    }

    T x, y, z, w;

};

template<typename T>
Quaternion<T> operator+(const Quaternion<T> &lhs, const Quaternion<T> &rhs) {
    auto result = lhs;
    result += rhs;
    return result;
}

template<typename T>
Quaternion<T> operator-(const Quaternion<T> &lhs, const Quaternion<T> &rhs) {
    auto result = lhs;
    result -= rhs;
    return result;
}

template<typename T>
Quaternion<T> operator*(const Quaternion<T> &lhs, const Quaternion<T> &rhs) {
    return Quaternion<T>
            {
                    ((lhs.x * rhs.w) + (lhs.w * rhs.x) + (lhs.z * rhs.y) - (lhs.y * rhs.z)),
                    ((lhs.y * rhs.w) - (lhs.z * rhs.x) + (lhs.w * rhs.y) + (lhs.x * rhs.z)),
                    ((lhs.z * rhs.w) + (lhs.y * rhs.x) - (lhs.x * rhs.y) + (lhs.w * rhs.z)),
                    ((lhs.w * rhs.w) - (lhs.x * rhs.x) - (lhs.y * rhs.y) - (lhs.z * rhs.z))
            };
}

template<typename T>
Quaternion<T> operator*(const Quaternion<T> &lhs, const T &rhs) {
    auto result = lhs;
    result *= rhs;
    return result;
}

template<typename T>
Quaternion<T> operator*(const T &lhs, const Quaternion<T> &rhs) {
    auto result = rhs;
    result *= lhs;
    return result;
}

template<typename T>
Vector<T, 3> operator*(const Quaternion<T> &lhs, const Vector<T, 3> &rhs) {
    Vector<T, 3> qvec{lhs.x, lhs.y, lhs.z};

    auto uv = Cross(qvec, rhs);
    auto uuv = Cross(qvec, uv);

    uv *= (T(2) * lhs.w);
    uuv *= T(2);

    /* Result := vec + uv + uuv */
    uv += uuv;
    uv += rhs;

    return uv;
}

using Quaternionf = Quaternion<float>;


#endif //SLIMEMATHS_QUATERNION_H
