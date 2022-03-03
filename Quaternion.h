//
// Created by alexm on 3/03/2022.
//

#ifndef SLIMEMATHS_QUATERNION_H
#define SLIMEMATHS_QUATERNION_H


#include "Vec3.h"

struct Quaternion {
    // Constructors
    Quaternion() = default;
    Quaternion(float x, float y, float z, float w);

    // Quaternion defaults
    static Quaternion identity();

    // Properties
    Vec3 eulerAngles;
    float p[4] = {};
    float& x = p[0];
    float& y = p[1];
    float& z = p[2];
    float& w = p[3];

    // Methods
    void set(float x,float y, float z, float w);
    void set_from_to_rotation(Vec3 fromDirection, Vec3 toDirection);
    void set_look_rotation(Vec3 view, Vec3 up = Vec3::up());
    void to_angle_axis(float& angle,Vec3& axis);

    // Static Methods
    static float angle(Quaternion a, Quaternion b);
    static Quaternion angle_axis(float angle, Vec3 axis);
    //... https://docs.unity3d.com/ScriptReference/Quaternion.html
};


#endif //SLIMEMATHS_QUATERNION_H
