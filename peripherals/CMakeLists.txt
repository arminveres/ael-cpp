add_subdirectory(lis3dh)
add_subdirectory(adxl345)
add_subdirectory(interfaces)

add_library(ael_peripherals INTERFACE)

target_link_libraries(ael_peripherals INTERFACE
    ael_peripherals_interfaces

    ael_peripherals_adxl345
    ael_peripherals_lis3dh
)
