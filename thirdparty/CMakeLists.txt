# Dependency settings

# boost
set(BOOST_INCLUDE_LIBRARIES geometry)

# enet
set(ENET_STATIC ON)

# sdl
set(SDL_SUBSYSTEMS
    Atomic
    Video
    Render
    Events
    Threads
    Locale
    Misc
)

set(SDL_AUDIO OFF)
set(SDL_OPENGL OFF)
set(SDL_RENDER_D3D OFF)
set(SDL_OPENGLES OFF)
set(SDL_DIRECTX OFF)
set(SDL_HIDAPI OFF)

# recastnavigation

set(RECASTNAVIGATION_DEMO OFF)
set(RECASTNAVIGATION_TESTS OFF)
set(RECASTNAVIGATION_EXAMPLES OFF)

# dependencies

add_subdirectory(boost EXCLUDE_FROM_ALL)
add_subdirectory(enet EXCLUDE_FROM_ALL)
add_subdirectory(entt EXCLUDE_FROM_ALL)
add_subdirectory(spdlog EXCLUDE_FROM_ALL)
add_subdirectory(sdl EXCLUDE_FROM_ALL)
add_subdirectory(imgui EXCLUDE_FROM_ALL)
add_subdirectory(glm EXCLUDE_FROM_ALL)
add_subdirectory(recastnavigation EXCLUDE_FROM_ALL)