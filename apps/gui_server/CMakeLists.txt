add_executable(SelkieGUIServer src/main.cpp
    src/gui.cpp
    src/gui.hpp
    src/windows/main_window.cpp
    src/windows/main_window.hpp
    src/windows/world_inspector.cpp
    src/windows/world_inspector.hpp
    src/inspectors/position_inspector.cpp
    src/inspectors/position_inspector.hpp
    src/inspectors/component_inspector.hpp
    src/inspectors/debug_info_inspector.hpp
    src/windows/world_view.cpp
    src/windows/world_view.hpp
)

target_compile_definitions(SelkieGUIServer PUBLIC SDL_MAIN_HANDLED)

target_link_libraries(SelkieGUIServer SDL2::SDL2-static imgui spdlog::spdlog SelkieServerCore)