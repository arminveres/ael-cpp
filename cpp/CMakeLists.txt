add_library(ael_main INTERFACE)

target_include_directories(ael_main INTERFACE
    includes
)
target_link_directories(ael_main INTERFACE
    includes
)

add_subdirectory(boards)
# add_subdirectory(peripherals)

target_link_libraries(ael_main INTERFACE
    ael_boards
    # ael_peripherals
)
