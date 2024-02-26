add_library(pi_pico INTERFACE)

target_include_directories(pi_pico INTERFACE
    includes
)

target_link_directories(pi_pico INTERFACE
    includes
)

target_link_libraries(pi_pico INTERFACE
    pico_stdlib
    hardware_spi
    hardware_gpio
)
