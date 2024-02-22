set(CMAKE_EXPORT_COMPILE_COMMANDS yes)
cmake_minimum_required(VERSION 3.20)

project(AEL_TEST
    VERSION 0.1.0
    DESCRIPTION "Armins Embedded Library"
)

add_subdirectory(
    ..
    ./build
)

add_executable(test1
    test1.cpp
)
target_link_libraries(test1
    ael
)
