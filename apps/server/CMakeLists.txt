add_executable(SelkieServer src/main.cpp)

target_link_libraries(SelkieServer EnTT::EnTT spdlog::spdlog enet_static boost_program_options)