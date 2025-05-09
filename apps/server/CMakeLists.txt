add_executable(SelkieServer
        src/main.cpp
)

target_link_libraries(SelkieServer PRIVATE EnTT::EnTT boost_core spdlog::spdlog) # boost_program_options

set_property(TARGET SelkieServer PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)