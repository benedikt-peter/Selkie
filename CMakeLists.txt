cmake_minimum_required(VERSION 3.27)

# Project settings

project(Selkie)

set(CMAKE_CXX_STANDARD 20)

# Dependency settings

# enet
set(ENET_STATIC ON)

# boost
set(BOOST_INCLUDE_LIBRARIES system)

# Dependencies

add_subdirectory(thirdparty/enet)
add_subdirectory(thirdparty/entt)
add_subdirectory(thirdparty/spdlog)
add_subdirectory(thirdparty/boost)

# Targets

add_subdirectory(src/protocol)
add_subdirectory(src/server)
add_subdirectory(src/console_client)
