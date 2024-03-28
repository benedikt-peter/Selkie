add_library(SelkieServerCore
    include/selkie/test_system.hpp
    src/test_system.cpp
    include/selkie/world.hpp
    include/selkie/system.hpp
    include/selkie/game_loop.hpp
    src/game_loop.cpp
    include/selkie/components.hpp
    include/selkie/vector2.hpp
)

target_include_directories(SelkieServerCore PUBLIC include)

target_link_libraries(SelkieServerCore EnTT::EnTT spdlog::spdlog glm::glm-header-only)

