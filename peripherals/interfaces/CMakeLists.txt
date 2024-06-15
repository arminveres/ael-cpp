add_library(ael_peripherals_interfaces INTERFACE)

target_include_directories(ael_peripherals_interfaces INTERFACE
    includes
)

target_link_libraries(ael_peripherals_interfaces INTERFACE
    pico_stdlib
    hardware_spi
    hardware_gpio
)
