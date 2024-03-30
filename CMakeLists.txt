cmake_minimum_required(VERSION 3.22)

# Project settings

project(Selkie)

set(CMAKE_CXX_STANDARD 20)

# Dependencies

add_subdirectory(thirdparty)

# Targets

add_subdirectory(libs/protocol)
add_subdirectory(libs/server_core)

add_subdirectory(apps/server)
add_subdirectory(apps/gui_server)
add_subdirectory(apps/console_client)
