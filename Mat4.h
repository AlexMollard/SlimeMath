//
// Created by alexm on 1/03/2022.
//

#ifndef SLIMEMATHS_MAT4_H
#define SLIMEMATHS_MAT4_H

#include "Vec3.h"
#include <string>

struct Mat4 {
    // Matrix
    float m[4][4]{};

    // static matrix's
    static Mat4 identity();
    static Mat4 zero();

    // Constructors
    Mat4() = default;
    explicit Mat4(float (*members)[4]);
    explicit Mat4(const Vec3 &xyz);

    // Overriders
    Mat4& operator=(const Mat4 &other);

    // Debug
    std::string debug_output();

    // Properties
    bool is_identity();
};


#endif //SLIMEMATHS_MAT4_H
