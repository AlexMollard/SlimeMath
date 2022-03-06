//
// Created by alexm on 6/03/2022.
//

#ifndef SLIMEMATHS_SLIMEALGEBRA_H
#define SLIMEMATHS_SLIMEALGEBRA_H

#include <cmath>
#include "ForwardDecl.h"


namespace Sm {

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    ScalarType dot(const VectorType &lhs, const VectorType &rhs) {
        ScalarType result = ScalarType(0);

        for (std::size_t i = 0; i < VectorType::components; ++i)
            result += lhs[i] * rhs[i];

        return result;
    }

    template<typename VectorType>
    VectorType cross(const VectorType &lhs, const VectorType &rhs) {
        static_assert(VectorType::components == 3, "Vector type must have exactly three components");
        return VectorType
                {
                        lhs.y * rhs.z - rhs.y * lhs.z,
                        rhs.x * lhs.z - lhs.x * rhs.z,
                        lhs.x * rhs.y - rhs.x * lhs.y
                };
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    ScalarType length_sq(const VectorType &vec) {
        return dot<VectorType, ScalarType>(vec, vec);
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    ScalarType length(const VectorType &vec) {
        return std::sqrt(length_sq<VectorType, ScalarType>(vec));
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    ScalarType angle(const VectorType &lhs, const VectorType &rhs) {
        return std::acos(dot<VectorType, ScalarType>(lhs, rhs) /
                         (length<VectorType, ScalarType>(lhs) * length<VectorType, ScalarType>(rhs)));
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    ScalarType angle_norm(const VectorType &lhs, const VectorType &rhs) {
        return std::acos(dot<VectorType, ScalarType>(lhs, rhs));
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    ScalarType distance_sq(const VectorType &lhs, const VectorType &rhs) {
        auto result = rhs;
        result -= lhs;
        return length_sq<VectorType, ScalarType>(result);
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    ScalarType distance(const VectorType &lhs, const VectorType &rhs) {
        auto result = rhs;
        result -= lhs;
        return length<VectorType, ScalarType>(result);
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    VectorType reflect(const VectorType &incident, const VectorType &normal) {
        auto v = normal;
        v *= (dot<VectorType, ScalarType>(normal, incident) * ScalarType(-2));
        v += incident;
        return v;
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    void normalize(VectorType &vec) {
        auto len = length_sq<VectorType, ScalarType>(vec);
        if (len != ScalarType(0) && len != ScalarType(1)) {
            len = ScalarType(1) / std::sqrt(len);
            vec *= len;
        }
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    void resize(VectorType &vec, const ScalarType &length) {
        auto len = length_sq<VectorType, ScalarType>(vec);
        if (len != ScalarType(0)) {
            len = length / std::sqrt(len);
            vec *= len;
        }
    }

    template<typename T, typename I>
    void lerp(T &x, const T &a, const T &b, const I &t) {
        x = b;
        x -= a;
        x *= t;
        x += a;
    }

    template<typename T, typename I>
    T lerp(const T &a, const T &b, const I &t) {
        /* Return (b - a) * t + a */
        T x = b;
        x -= a;
        x *= t;
        x += a;
        return x;
    }

    template<typename VectorType, typename ScalarType = typename VectorType::ScalarType>
    VectorType slerp(const VectorType &from, const VectorType &to, const ScalarType &t) {
        ScalarType omega, cosom, sinom;
        ScalarType scale0, scale1;

        /* Calculate cosine */
        cosom = dot<VectorType, ScalarType>(from, to);

        /* Adjust signs (if necessary) */
        if (cosom < ScalarType(0)) {
            cosom = -cosom;
            scale1 = ScalarType(-1);
        } else
            scale1 = ScalarType(1);

        /* Calculate coefficients */
        if ((ScalarType(1) - cosom) > std::numeric_limits<ScalarType>::epsilon()) {
            /* Standard case (slerp) */
            omega = std::acos(cosom);
            sinom = std::sin(omega);
            scale0 = std::sin((ScalarType(1) - t) * omega) / sinom;
            scale1 *= std::sin(t * omega) / sinom;
        } else {
            /* 'from' and 'to' quaternions are very close, so we can do a linear interpolation */
            scale0 = ScalarType(1) - t;
            scale1 *= t;
        }

        /* Calculate final values */
        return Mix(from, to, scale0, scale1);
    }

    template<typename T, typename I>
    T mix(const T &v0, const T &v1, const I &scale0, const I &scale1) {
        return v0 * scale0 + v1 * scale1;
    }

    template<typename T>
    T saturate(const T &x) {
        return (std::max)(T(0), (std::min)(x, T(1)));
    }

    template<typename T>
    T clamp(const T &x, const T &minima, const T &maxima) {
        if (x <= minima)
            return minima;
        if (x >= maxima)
            return maxima;
        return x;
    }

    template<typename T>
    T smooth_step(const T &x) {
        return x * x * (T(3) - x * T(2));
    }

    template<typename T>
    T smoother_step(const T &x) {
        return x * x * x * (x * (x * T(6) - T(15)) + T(10));
    }

    template<typename T>
    T reciprocal(const T &x) {
        return T(1) / x;
    }

    template<typename T, std::size_t N>
    Vector<T, N> reciprocal(const Vector<T, N> &vec) {
        Vector<T, N> vecRcp{};

        for (std::size_t i = 0; i < N; ++i)
            vecRcp[i] = T(1) / vec[i];

        return vecRcp;
    }

    template<typename T, std::size_t N, std::size_t M>
    Matrix<T, N, M> reciprocal(const Matrix<T, N, M> &mat) {
        Matrix<T, N, M> matRcp{};

        for (std::size_t i = 0; i < N * M; ++i)
            matRcp[i] = T(1) / mat[i];

        return matRcp;
    }

    template<typename T, typename I>
    T rescale(const T &t, const I &lower0, const I &upper0, const I &lower1, const I &upper1) {
        /* Return (((t - lower0) / (upper0 - lower0)) * (upper1 - lower1) + lower1) */
        T x = t;
        x -= T(lower0);
        x /= (upper0 - lower0);
        x *= (upper1 - lower1);
        x += T(lower1);
        return x;
    }

    template<typename T, std::size_t Rows, std::size_t Cols>
    Vector<T, Cols> operator*(const Vector<T, Rows> &lhs, const Matrix<T, Rows, Cols> &rhs) {
        Vector<T, Cols> result;

        for (std::size_t c = 0; c < Cols; ++c) {
            result[c] = T(0);
            for (std::size_t r = 0; r < Rows; ++r)
                result[c] += rhs(r, c) * lhs[r];
        }

        return result;
    }


    template<typename T, std::size_t Rows, std::size_t Cols>
    Vector<T, Rows> operator*(const Matrix<T, Rows, Cols> &lhs, const Vector<T, Cols> &rhs) {
        Vector<T, Rows> result;

        for (std::size_t r = 0; r < Rows; ++r) {
            result[r] = T(0);
            for (std::size_t c = 0; c < Cols; ++c)
                result[r] += lhs(r, c) * rhs[c];
        }

        return result;
    }
}

#endif //SLIMEMATHS_SLIMEALGEBRA_H
