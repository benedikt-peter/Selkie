add_library(SelkieServerCore
    include/selkie/world.hpp
    include/selkie/system.hpp
    include/selkie/game_loop.hpp
    src/game_loop.cpp
    include/selkie/components.hpp
    include/selkie/vector2.hpp
    src/minions/waypoint_movement_system.cpp
    include/selkie/minions/waypoint_movement_system.hpp
)

target_include_directories(SelkieServerCore PUBLIC include)

target_link_libraries(SelkieServerCore EnTT::EnTT spdlog::spdlog glm::glm-header-only)

