#include <iostream>
#include "Transform.h"
#include "Matrix.h"

#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)

int main() {
    Mat4 mat{};
    mat.load_identity();
    mat[0] = 12.0f;

    Mat4 second_mat{};
    second_mat.reset();
    second_mat[0] = 3.0f;

    Mat4 newMat = mat + second_mat;

    std::cout << MACRO_VARIABLE_TO_STRING(newMat) << ":\n" << newMat << std::endl;

    Vec3 first{10, 0, 0};
    Vec3 second{92, 19, 19};

    float dot = Sm::dot(first, second);
    std::cout << "Cross: " << dot << std::endl;

    auto cross = Sm::cross(first, second);
    std::cout << "Cross: " << cross << std::endl;

    return 0;
}
