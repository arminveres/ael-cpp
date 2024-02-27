add_subdirectory(main)
add_subdirectory(boards)
add_subdirectory(peripherals)

add_library(ael INTERFACE)

target_link_libraries(ael INTERFACE
    ael_main
    ael_boards
    ael_peripherals
)

target_compile_options(ael INTERFACE
    # -Werror
    -Wall
    -Wextra
    -Wconversion
    -Wpedantic
    # note covered by above
    -Wshadow
    -Wundef
    -Wdouble-promotion
    -Os
    -mtune=cortex-m0plus
    -fno-common
    -fstack-usage
    -ffunction-sections
    -fdata-sections
    -fdiagnostics-color
)

target_link_options(ael INTERFACE
    -Wl,-gc-sections
    -Wl,-print-memory-usage
)
