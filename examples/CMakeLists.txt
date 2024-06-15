cmake_minimum_required(VERSION 3.12)

include(../external/pico-sdk/pico_sdk_init.cmake)

# use pico sdk defined in ael
set(AEL_USE_PICO_SDK true)
set(AEL_BOARD pico_w)
set(AEL_TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin)

# add AEL
add_subdirectory(..
    build
)

project(AEL_SAMPLES
    LANGUAGES C CXX ASM
    VERSION 0.1.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS yes)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

# =================================================================================================
# Sample 1: Accelerometer
# =================================================================================================
add_executable(lis3dh-accel
    lis3dh.cpp
)
target_compile_options(lis3dh-accel PRIVATE
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

target_link_options(lis3dh-accel PRIVATE
    -Wl,-gc-sections
    -Wl,-print-memory-usage
)

target_link_libraries(lis3dh-accel PRIVATE
    ael_main
    ael_boards_pi_pico
    ael_peripherals_lis3dh

    pico_stdlib
)

target_link_libraries(lis3dh-accel PUBLIC
    pico_stdlib
)

pico_add_extra_outputs(lis3dh-accel)
# enable usb output, disable uart
pico_enable_stdio_usb(lis3dh-accel 1)
pico_enable_stdio_uart(lis3dh-accel 0)

# =================================================================================================
# Sample 2: Accelerometer
# =================================================================================================
add_executable(adxl345-accel
    adxl345.cpp
)
target_compile_options(adxl345-accel PRIVATE
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

target_link_options(adxl345-accel PRIVATE
    -Wl,-gc-sections
    -Wl,-print-memory-usage
)

target_link_libraries(adxl345-accel PRIVATE
    ael_main
    ael_boards_pi_pico
    ael_peripherals_adxl345

    pico_stdlib
)

target_link_libraries(adxl345-accel PUBLIC
    pico_stdlib
)

pico_add_extra_outputs(adxl345-accel)
# enable usb output, disable uart
pico_enable_stdio_usb(adxl345-accel 1)
pico_enable_stdio_uart(adxl345-accel 0)
