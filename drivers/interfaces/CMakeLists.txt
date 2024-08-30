add_library(ael_drivers_interfaces INTERFACE)

target_include_directories(ael_drivers_interfaces INTERFACE
    includes
)

target_link_libraries(ael_drivers_interfaces INTERFACE
    pico_stdlib
    hardware_spi
    hardware_gpio
)
