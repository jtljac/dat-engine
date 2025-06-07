cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
        "source/vulkan-gpu.cpp"
        "source/vk-shortcuts.cpp"
        "frame-data.h"
        "source/vk-types.cpp"
        "source/vk-pipeline.cpp"
)