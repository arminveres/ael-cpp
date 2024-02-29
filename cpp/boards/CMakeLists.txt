add_subdirectory(pi_pico)

add_library(ael_boards INTERFACE)

target_link_libraries(ael_boards INTERFACE
    # ael::boards::pi_pico
    ael_boards_pi_pico
)

