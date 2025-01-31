add_executable(SelkieGUIServer src/main.cpp
    src/gui/gui.cpp
    src/gui/gui.hpp
    src/windows/main_window.cpp
    src/windows/main_window.hpp
    src/windows/world_inspector.cpp
    src/windows/world_inspector.hpp
    src/inspectors/position_inspector.hpp
    src/inspectors/component_inspector.hpp
    src/inspectors/debug_info_inspector.hpp
    src/windows/world_view.cpp
    src/windows/world_view.hpp
    src/views/minion_view.cpp
    src/views/minion_view.hpp
    src/views/view.hpp
    src/test_map.hpp
    src/inspectors/team_inspector.hpp
    src/inspectors/hitbox_inspector.hpp
    src/inspectors/targeting_inspector.hpp
)

target_compile_definitions(SelkieGUIServer PUBLIC SDL_MAIN_HANDLED)

target_link_libraries(SelkieGUIServer SDL2::SDL2-static imgui spdlog::spdlog SelkieServerCore)

set_property(TARGET SelkieGUIServer PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)