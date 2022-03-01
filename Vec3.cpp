//
// Created by alexm on 1/03/2022.
//

#include "Vec3.h"

Vec3::Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::operator+(const Vec3 &other) {
    return {x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3 &other) {
    return {x - other.x, y - other.y, z - other.z};
}

Vec3 Vec3::operator*(const Vec3 &other) {
    return {x * other.x, y * other.y, z * other.z};
}

Vec3 Vec3::operator/(const Vec3 &other) {
    return {x / other.x, y / other.y, z / other.z};
}

float Vec3::dot(const Vec3 &other) {
    return ((x * other.x) + (y * other.y) + (z* other.z));
}

Vec3 Vec3::cross(const Vec3 &other) {
    return {
        ((y * other.z) - (z * other.y)),
        ((z * other.x) - (x * other.z)),
        ((x * other.y) - (y * other.x))
    };
}
