#include <iostream>
#include "Transform.h"

int main() {
    Vec3 first(12.0f, 4.0f, 3.0f);
    Vec3 second(91.0f, 3.0f, 24.0f);

    std::cout << "x: " << first.cross(second).x << std::endl;
    std::cout << "y: " << first.cross(second).y << std::endl;
    std::cout << "z: " << first.cross(second).z << std::endl;

    Transform engineObject{};
    engineObject.m[0][0] = 1;
    engineObject.m[1][1] = 11;
    engineObject.m[2][2] = 1;
    engineObject.m[3][3] = 1;


    std::cout << engineObject.is_identity() << std::endl;
    std::cout << engineObject.debug_output() << std::endl;


    return 0;
}
