//
// Created by alexm on 6/03/2022.
//

#ifndef SLIMEMATHS_MATRIXCONVERSION_H
#define SLIMEMATHS_MATRIXCONVERSION_H

#include <cmath>

namespace Sm {
    template<class M, template<typename> class Q, typename T>
    void matrix_to_quaternion(Q<T> &out, const M &in) {
        static_assert(
                M::rows >= 3 && M::columns >= 3,
                "matrix can only be converted to quaternion, if the matrix has at least 3 rows and 3 column"
        );

        /* Only get the trace of the 3x3 upper left matrix */
        const T trace = in.At(0, 0) + in.At(1, 1) + in.At(2, 2) + T(1);

        if (trace > T(0)) {
            const T s = T(2) * std::sqrt(trace);
            out.x = (in.At(2, 1) - in.At(1, 2)) / s;
            out.y = (in.At(0, 2) - in.At(2, 0)) / s;
            out.z = (in.At(1, 0) - in.At(0, 1)) / s;
            out.w = T(0.25) * s;
        } else {
            if (in.At(0, 0) > in.At(1, 1) && in.At(0, 0) > in.At(2, 2)) {
                const T s = T(2) * std::sqrt(T(1) + in.At(0, 0) - in.At(1, 1) - in.At(2, 2));
                out.x = T(0.25) * s;
                out.y = (in.At(0, 1) + in.At(1, 0)) / s;
                out.z = (in.At(2, 0) + in.At(0, 2)) / s;
                out.w = (in.At(2, 1) - in.At(1, 2)) / s;
            } else if (in.At(1, 1) > in.At(2, 2)) {
                const T s = T(2) * std::sqrt(T(1) + in.At(1, 1) - in.At(0, 0) - in.At(2, 2));
                out.x = (in.At(0, 1) + in.At(1, 0)) / s;
                out.y = T(0.25) * s;
                out.z = (in.At(1, 2) + in.At(2, 1)) / s;
                out.w = (in.At(0, 2) - in.At(2, 0)) / s;
            } else {
                const T s = T(2) * std::sqrt(T(1) + in.At(2, 2) - in.At(0, 0) - in.At(1, 1));
                out.x = (in.At(0, 2) + in.At(2, 0)) / s;
                out.y = (in.At(1, 2) + in.At(2, 1)) / s;
                out.z = T(0.25) * s;
                out.w = (in.At(1, 0) - in.At(0, 1)) / s;
            }
        }

        Normalize(out);
    }

    template<class M, template<typename> class Q, typename T>
    void quaternion_to_matrix(M &out, const Q<T> &in) {
        static_assert(
                M::rows >= 3 && M::columns >= 3,
                "quaternion can only be converted to matrix, if the matrix has at least 3 rows and 3 column"
        );

        const auto &x = in.x;
        const auto &y = in.y;
        const auto &z = in.z;
        const auto &w = in.w;

        out.At(0, 0) = T(1) - T(2) * y * y - T(2) * z * z;
        out.At(1, 0) = T(2) * x * y + T(2) * z * w;
        out.At(2, 0) = T(2) * x * z - T(2) * y * w;

        out.At(0, 1) = T(2) * x * y - T(2) * z * w;
        out.At(1, 1) = T(1) - T(2) * x * x - T(2) * z * z;
        out.At(2, 1) = T(2) * z * y + T(2) * x * w;

        out.At(0, 2) = T(2) * x * z + T(2) * y * w;
        out.At(1, 2) = T(2) * z * y - T(2) * x * w;
        out.At(2, 2) = T(1) - T(2) * x * x - T(2) * y * y;
    }

    template<class M, template<typename> class Q, typename T>
    void quaternion_to_matrix_transposed(M &out, const Q<T> &in) {
        static_assert(
                M::rows >= 3 && M::columns >= 3,
                "quaternion can only be converted to matrix, if the matrix has at least 3 rows and 3 column"
        );

        const auto &x = in.x;
        const auto &y = in.y;
        const auto &z = in.z;
        const auto &w = in.w;

        out.At(0, 0) = T(1) - T(2) * y * y - T(2) * z * z;
        out.At(0, 1) = T(2) * x * y - T(2) * z * w;
        out.At(0, 2) = T(2) * x * z + T(2) * y * w;

        out.At(1, 0) = T(2) * x * y + T(2) * z * w;
        out.At(1, 1) = T(1) - T(2) * x * x - T(2) * z * z;
        out.At(1, 2) = T(2) * z * y - T(2) * x * w;

        out.At(2, 0) = T(2) * x * z - T(2) * y * w;
        out.At(2, 1) = T(2) * z * y + T(2) * x * w;
        out.At(2, 2) = T(1) - T(2) * x * x - T(2) * y * y;
    }
};


#endif //SLIMEMATHS_MATRIXCONVERSION_H
