#include <iostream>
#include "Transform.h"

int main() {
    Vec3 first(12.0f, 4.0f, 3.0f);
    Vec3 second(91.0f, 3.0f, 24.0f);
    Transform dadda;

    dadda.m[1][1];

    std::cout << "x: " << first.cross(second).x << std::endl;
    std::cout << "y: " << first.cross(second).y << std::endl;
    std::cout << "z: " << first.cross(second).z << std::endl;

    return 0;
}
