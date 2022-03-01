cmake_minimum_required(VERSION 3.21)
project(SlimeMaths)

set(CMAKE_CXX_STANDARD 17)

set(FILES main.cpp Mat4.cpp Vec3.cpp Transform.cpp Transform.h)

add_executable(SlimeMaths ${FILES})
