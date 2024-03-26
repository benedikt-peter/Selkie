# Dependency settings

# enet
set(ENET_STATIC ON)

# boost
set(BOOST_INCLUDE_LIBRARIES program_options)

# sdl
set(SDL_AUDIO OFF)
set(SDL_OPENGL OFF)
set(SDL_OPENGLES OFF)
set(SDL_DIRECTX OFF)
set(SDL_HIDAPI OFF)

add_subdirectory(enet)
add_subdirectory(entt)
add_subdirectory(spdlog)
#add_subdirectory(boost)
add_subdirectory(sdl)
add_subdirectory(imgui)