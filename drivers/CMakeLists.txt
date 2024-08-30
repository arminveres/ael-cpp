add_subdirectory(lis3dh)
add_subdirectory(adxl345)
add_subdirectory(interfaces)

add_library(ael_drivers INTERFACE)

target_link_libraries(ael_drivers INTERFACE
    ael_drivers_interfaces

    ael_drivers_adxl345
    ael_drivers_lis3dh
)
