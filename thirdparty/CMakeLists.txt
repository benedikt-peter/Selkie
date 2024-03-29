# Dependency settings

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

add_subdirectory(enet)
add_subdirectory(entt)
add_subdirectory(spdlog)
add_subdirectory(sdl)
add_subdirectory(imgui)
add_subdirectory(glm)