cmake_minimum_required(VERSION 3.27)

# Project settings

project(Selkie)

set(CMAKE_CXX_STANDARD 20)

# Dependency settings

# enet
set(ENET_STATIC ON)

# boost
set(BOOST_INCLUDE_LIBRARIES program_options)

# Dependencies

add_subdirectory(thirdparty)

# Targets

add_subdirectory(libs/protocol)

add_subdirectory(apps/server)
add_subdirectory(apps/gui_server)
add_subdirectory(apps/console_client)
