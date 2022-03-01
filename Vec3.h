//
// Created by alexm on 1/03/2022.
//

#ifndef SLIMEMATHS_VEC3_H
#define SLIMEMATHS_VEC3_H


struct Vec3 {
    Vec3 operator+(const Vec3& other);
    Vec3 operator-(const Vec3& other);
    Vec3 operator*(const Vec3& other);
    Vec3 operator/(const Vec3& other);

    float m[3] = {0.0f,0.0f,0.0f};

    float &x = m[0];
    float &y = m[1];
    float &z = m[2];

    Vec3() = default;
    Vec3(float x, float y, float z);

    float dot(const Vec3& other);
    Vec3 cross(const Vec3& other);
};


#endif //SLIMEMATHS_VEC3_H
