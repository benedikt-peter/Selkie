add_executable(SelkieConsoleClient main.cpp)

target_link_libraries(SelkieConsoleClient spdlog::spdlog enet_static)