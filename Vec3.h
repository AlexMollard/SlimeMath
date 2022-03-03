//
// Created by alexm on 1/03/2022.
//

#ifndef SLIMEMATHS_VEC3_H
#define SLIMEMATHS_VEC3_H


struct Vec3 {
    // Constructors
    Vec3() = default;
    Vec3(float x, float y, float z);

    // Overriders
    Vec3 operator+(const Vec3& other);
    Vec3 operator-(const Vec3& other);
    Vec3 operator*(const Vec3& other);
    Vec3 operator/(const Vec3& other);

    // Member Variables
    float m[3] = {0.0f,0.0f,0.0f};
    float &x = m[0];
    float &y = m[1];
    float &z = m[2];

    // Methods
    float dot(const Vec3& other);
    Vec3 cross(const Vec3& other);

    // Static Vectors
    static Vec3 up();
};


#endif //SLIMEMATHS_VEC3_H
