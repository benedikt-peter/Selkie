add_library(SelkieServerCore
    include/selkie/test_system.hpp
    src/test_system.cpp
    include/selkie/world.hpp
    include/selkie/system.hpp
)

target_include_directories(SelkieServerCore PUBLIC include)

target_link_libraries(SelkieServerCore EnTT::EnTT)

