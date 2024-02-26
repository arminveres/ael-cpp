add_subdirectory(main)
add_subdirectory(boards)
add_subdirectory(peripherals)

add_library(ael INTERFACE)

target_link_libraries(ael INTERFACE
    ael_main
    ael_boards
    ael_peripherals
)
