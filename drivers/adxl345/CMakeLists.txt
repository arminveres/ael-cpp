add_library(ael_drivers_adxl345 INTERFACE)

target_include_directories(ael_drivers_adxl345 INTERFACE
    includes
)

target_link_libraries(ael_drivers_adxl345 INTERFACE
    pico_stdlib
    hardware_spi
    hardware_gpio
)
