//
// Created by alexm on 1/03/2022.
//

#ifndef SLIMEMATHS_MAT4_H
#define SLIMEMATHS_MAT4_H
#include "Vec3.h"

struct Mat4 {
    float m[4][4] =
            {
            {1.0f,0.0f,0.0f,0.0f},
            {0.0f,1.0f,0.0f,0.0f},
            {0.0f,0.0f,1.0f,0.0f},
            {0.0f,0.0f,0.0f,1.0f}
            };

    Mat4() = default;
    explicit Mat4(float (*members)[4]);
    explicit Mat4(const Vec3& xyz);

    Mat4 operator*(const Mat4& other);

    Mat4& scale();
    Mat4& rotate();
    Mat4& ortho();
    Mat4& perspective();
    Mat4& look_at();
    Mat4& translate();
    Mat4& trs(); // Translate, rotate, scale


};


#endif //SLIMEMATHS_MAT4_H
