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

    return 0;
}
