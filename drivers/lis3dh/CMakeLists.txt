add_library(ael_drivers_lis3dh INTERFACE)

target_include_directories(ael_drivers_lis3dh INTERFACE
    includes
)

target_link_libraries(ael_drivers_lis3dh INTERFACE
    pico_stdlib
    hardware_spi
    hardware_gpio
)
