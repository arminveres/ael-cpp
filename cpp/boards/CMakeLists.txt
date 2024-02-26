add_library(ael_boards INTERFACE)

add_subdirectory(pi_pico)

target_link_libraries(ael_boards INTERFACE
    pi_pico
)
