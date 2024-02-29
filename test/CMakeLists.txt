cmake_minimum_required(VERSION 3.12)

# FIXME(aver): find a fix not to have to import this ...
include(../cmake/pico_sdk_import.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS yes)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

# use pico sdk defined in ael
set(AEL_USE_PICO_SDK true)
set(AEL_BOARD pico_w)
set(AEL_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin)

# add AEL
add_subdirectory(..
    build
)

project(AEL_TEST
    LANGUAGES C CXX ASM
    VERSION 0.1.0
)

# =================================================================================================
# TEST 1
add_executable(test1 test1.cpp)
target_link_libraries(test1 PUBLIC
    ael
)

target_compile_options(test1 PUBLIC
    # -Werror
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

target_link_options(test1 PUBLIC
    -Wl,-gc-sections
    -Wl,-print-memory-usage
)


# pico_sdk_init()
# # enable usb output, disable uart output
# pico_enable_stdio_usb(test1 1)
# pico_enable_stdio_uart(test1 0)

# # create map/bin/hex/uf2 file etc.
# pico_add_extra_outputs(test1)
