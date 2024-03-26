add_executable(SelkieGUIServer src/main.cpp
    src/gui.cpp
    src/gui.hpp
    src/main_window.cpp
    src/main_window.hpp)

target_compile_definitions(SelkieGUIServer PUBLIC SDL_MAIN_HANDLED)

target_link_libraries(SelkieGUIServer SDL2::SDL2-static imgui spdlog::spdlog SelkieServerCore)