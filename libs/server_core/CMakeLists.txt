add_library(SelkieServerCore
    include/selkie/world.hpp
    include/selkie/system.hpp
    include/selkie/game_loop.hpp
    src/game_loop.cpp
    include/selkie/components.hpp
    include/selkie/math/vector2.hpp
    src/minions/lane_movement_system.cpp
    src/minions/lane_movement_system.hpp
    include/selkie/map_data.hpp
    src/minions/minion_spawner_system.cpp
    src/minions/minion_spawner_system.hpp
    src/math/r_tree.hpp
    src/combat/search_tree_update_system.cpp
    src/combat/search_tree_update_system.hpp
    include/selkie/systems.hpp
    src/systems.cpp
    src/combat/search_trees.hpp
    src/minions/targeting_system.cpp
    src/minions/targeting_system.hpp
)

target_include_directories(SelkieServerCore PUBLIC include)

target_link_libraries(SelkieServerCore Boost::geometry EnTT::EnTT spdlog::spdlog glm::glm-header-only)

set_property(TARGET SelkieServerCore PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)