add_executable(SelkieConsoleClient src/main.cpp)

target_link_libraries(SelkieConsoleClient spdlog::spdlog enet_static)

set_property(TARGET SelkieConsoleClient PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)