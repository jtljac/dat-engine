cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
#        "vma-wrapper.h" "source/vma-wrapper.cpp"
        "VkStub.cpp"
        "VulkanGpu.h" "VulkanGpu.cpp"
        "VkShortcuts.h" "VkShortcuts.cpp"
        "FrameData.h"
        "VkTypes.h"
)