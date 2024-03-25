find_package(Vulkan REQUIRED)

add_library(imgui
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_demo.cpp
    imgui/backends/imgui_impl_sdl2.cpp
    imgui/backends/imgui_impl_vulkan.cpp
)

target_link_libraries(imgui SDL2::SDL2-static Vulkan::Vulkan)

target_include_directories(imgui PUBLIC imgui imgui_fonts)

add_executable(binary_to_compressed_c imgui/misc/fonts/binary_to_compressed_c.cpp)

target_link_libraries(binary_to_compressed_c imgui)