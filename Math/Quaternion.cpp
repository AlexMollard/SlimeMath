//
// Created by alexm on 3/03/2022.
//

#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w) {
    p[0] = x;
    p[1] = y;
    p[2] = z;
    p[3] = w;
}

void Quaternion::set(float newX, float newY, float newZ, float newW) {
    p[0] = newX;
    p[1] = newY;
    p[2] = newZ;
    p[3] = newW;
}
