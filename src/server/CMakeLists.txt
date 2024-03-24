add_executable(SelkieServer main.cpp)

target_link_libraries(SelkieServer EnTT::EnTT spdlog::spdlog enet_static)