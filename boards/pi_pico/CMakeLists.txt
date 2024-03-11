add_library(ael_boards_pi_pico STATIC
    extras/lis3dh.cpp
)

target_include_directories(ael_boards_pi_pico PUBLIC
    includes
    ${CMAKE_SOURCE_DIR}/cpp/main/includes
    ${CMAKE_SOURCE_DIR}/cpp/peripherals/lis3dh/includes
)

target_link_libraries(ael_boards_pi_pico PUBLIC
    ael_main
    ael_peripherals_lis3dh

    pico_stdlib
    pico_time
    hardware_gpio
    hardware_spi
    hardware_i2c
    hardware_timer
)

