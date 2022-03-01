//
// Created by alexm on 1/03/2022.
//

#include "Mat4.h"

Mat4::Mat4(float (*members)[4]) {
    m[0][0] = members[0][0];
    m[0][1] = members[0][1];
    m[0][2] = members[0][2];
    m[0][3] = members[0][3];

    m[1][0] = members[1][0];
    m[1][1] = members[1][1];
    m[1][2] = members[1][2];
    m[1][3] = members[1][3];

    m[2][0] = members[2][0];
    m[2][1] = members[2][1];
    m[2][2] = members[2][2];
    m[2][3] = members[2][3];

    m[3][0] = members[3][0];
    m[3][1] = members[3][1];
    m[3][2] = members[3][2];
    m[3][3] = members[3][3];
}

Mat4::Mat4(const Vec3 &xyz) {
    m[0][3] = xyz.x;
    m[1][3] = xyz.y;
    m[2][3] = xyz.z;
}
