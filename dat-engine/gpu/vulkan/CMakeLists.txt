cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
        "vulkan-gpu.h" "source/vulkan-gpu.cpp"
        "frame-data.h"
)