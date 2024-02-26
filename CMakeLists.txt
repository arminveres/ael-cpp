cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS yes)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)

project(ael
    LANGUAGES C CXX ASM
    VERSION 0.1.0
    DESCRIPTION "Armins Embedded Library (AEL)"
)

if(NOT DEFINED AEL_TOOLCHAIN_PATH)
    message(FATAL_ERROR "AEL_TOOLCHAIN_PATH is not set!")
else()
    message(STATUS "Found AEL Toolchain at ${AEL_TOOLCHAIN_PATH}")
endif()

if (AEL_USE_PICO_SDK)
    include(external/pico-sdk/pico_sdk_init.cmake)
    # include(cmake/pico_sdk_import.cmake)
    set(PICO_BOARD ${AEL_BOARD})
    set(PICO_TOOLCHAIN_PATH ${AEL_TOOLCHAIN_PATH})
    pico_sdk_init()
else()
    # TODO(aver): Add other options
    message("Nothing configured...")
endif()

add_library(${PROJECT_NAME} INTERFACE)

add_subdirectory(cpp)

target_link_libraries(${PROJECT_NAME} INTERFACE
    ael_main
)
