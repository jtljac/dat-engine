cmake_minimum_required(VERSION 3.22)
target_sources(dat-engine PRIVATE
        "IGpu.h" "IGpu.cpp"
        "IWindow.h" "IWindow.cpp"
)
add_subdirectory(vulkan)
