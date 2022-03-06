cmake_minimum_required(VERSION 3.21)
project(SlimeMaths)

set(CMAKE_CXX_STANDARD 17)

include_directories(Math)

file(GLOB source_files CONFIGURE_DEPENDS
        "*.h"
        "*.cpp"
        "Math/*.cpp"
        "Math/*.h"
        )

add_executable(SlimeMaths ${source_files} Math/SlimeMath.h)
