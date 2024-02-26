add_library(ael_boards INTERFACE)

add_subdirectory(pico)

target_link_libraries(ael_boards INTERFACE
    pico
)
