cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
        "VkStub.cpp"
        "VulkanGpu.h" "VulkanGpu.cpp"
        "VkShortcuts.h" "VkShortcuts.cpp"
        "VkTypes.h" "VkTypes.cpp"
        "VkPipeline.h" "VkPipeline.cpp"
        "FrameData.h"
        "VkTypes.h"
)