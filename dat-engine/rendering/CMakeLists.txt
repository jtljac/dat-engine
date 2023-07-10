cmake_minimum_required(VERSION 3.22)

if (${DAT_ENGINE_TARGET_PLATFORM} STREQUAL "linux")
    add_subdirectory(vulkan)
elseif (${DAT_ENGINE_TARGET_PLATFORM} STREQUAL "windows")
    add_subdirectory(vulkan)
endif()

target_sources(dat-engine PRIVATE
        "irenderer.h" "source/irenderer.cpp"
        "iwindow.h" "source/iwindow.cpp"
)