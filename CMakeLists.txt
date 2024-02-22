cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS yes)

project(mylib
    VERSION 0.1.0
    DESCRIPTION "Armins Embedded Library (AEL)"
)

add_library(ael INTERFACE)

target_include_directories(ael INTERFACE
    cpp/includes
)
