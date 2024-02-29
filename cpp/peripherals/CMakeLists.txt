add_subdirectory(lis3dh)

add_library(ael_peripherals INTERFACE)

target_link_libraries(ael_peripherals INTERFACE
    # ael::peripherals::lis3dh
    ael_peripherals_lis3dh
)
