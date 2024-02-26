add_library(pico INTERFACE)

target_include_directories(pico INTERFACE
    includes
)

target_link_directories(pico INTERFACE
    includes
)

target_link_libraries(pico INTERFACE
    pico_stdlib
    hardware_spi
    hardware_gpio
)
