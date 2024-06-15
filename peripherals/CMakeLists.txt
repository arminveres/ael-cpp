add_subdirectory(lis3dh)
add_subdirectory(interfaces)

add_library(ael_peripherals INTERFACE)

target_link_libraries(ael_peripherals INTERFACE
    ael_peripherals_interfaces
    ael_peripherals_lis3dh
)
