add_library(SelkieServerCore
    include/selkie/world.hpp
    include/selkie/system.hpp
    include/selkie/game_loop.hpp
    src/game_loop.cpp
    include/selkie/components.hpp
    include/selkie/math/vector2.hpp
    src/minions/lane_movement_system.cpp
    include/selkie/minions/lane_movement_system.hpp
    include/selkie/map_data.hpp
    src/minions/minion_spawner_system.cpp
    include/selkie/minions/minion_spawner_system.hpp
    include/selkie/math/r_tree.hpp
)

target_include_directories(SelkieServerCore PUBLIC include)

target_link_libraries(SelkieServerCore Boost::geometry EnTT::EnTT spdlog::spdlog glm::glm-header-only)

