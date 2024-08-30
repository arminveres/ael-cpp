cmake_minimum_required(VERSION 3.12)

if (AEL_USE_PICO_SDK)
    if (AEL_PICO_IMPORT)
        include(cmake/pico_sdk_import.cmake)
    else()
        include(external/pico-sdk/pico_sdk_init.cmake)
    endif()
    # NOTE(aver): nicer way to inlude, but sadly unsupported...
    # add_subdirectory(external/pico-sdk SYSTEM)
    set(PICO_BOARD ${AEL_BOARD})
    set(PICO_TOOLCHAIN_PATH ${AEL_TOOLCHAIN_PATH})
else()
    # TODO(aver): Add other options
endif()

project(AEL
    LANGUAGES C CXX ASM
    VERSION 0.1.0
    DESCRIPTION "Armins Embedded Library (AEL)"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS yes)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

if(NOT DEFINED AEL_TOOLCHAIN_PATH)
    message(WARNING "AEL_TOOLCHAIN_PATH is not set, trying to set it to '/opt'!")
    set(AEL_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin/)
    if(NOT DEFINED AEL_TOOLCHAIN_PATH)
        message(FATAL_ERROR "AEL_TOOLCHAIN_PATH is not set!")
    endif()
else()
    message(STATUS "Found AEL Toolchain at ${AEL_TOOLCHAIN_PATH}")
endif()

if (AEL_USE_PICO_SDK)
    pico_sdk_init()
else()
    # TODO(aver): Add other options
    message(TRACE "Nothing configured...")
endif()

add_subdirectory(main)
add_subdirectory(boards)
add_subdirectory(drivers)

add_library(ael INTERFACE)

target_link_libraries(ael INTERFACE
    ael_main
    ael_boards
    ael_drivers
)

target_compile_options(ael INTERFACE
    -Werror
    -Wall
    -Wextra
    -Wconversion
    -Wpedantic
    # note covered by above
    -Wshadow
    -Wundef
    -Wdouble-promotion
    -Os
    -mtune=cortex-m0plus
    -fno-common
    -fstack-usage
    -ffunction-sections
    -fdata-sections
    -fdiagnostics-color
)

target_link_options(ael INTERFACE
    -Wl,-gc-sections
    -Wl,-print-memory-usage
)
