add_library(ael_main INTERFACE)

target_include_directories(ael_main INTERFACE
    includes
)

set_target_properties(ael_main PROPERTIES
    OUTPUT_NAME "ael::main"
)
