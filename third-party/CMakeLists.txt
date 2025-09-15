cmake_minimum_required(VERSION 3.22)

# SDL 3
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.20")
target_link_libraries(dat-engine PUBLIC SDL3::SDL3)

# Vulkan
CPMAddPackage(gh:KhronosGroup/Vulkan-Headers@1.4.322)
target_link_libraries(dat-engine PUBLIC Vulkan-Headers)


# VMA
CPMAddPackage(gh:GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator@3.2.1)
CPMAddPackage(gh:YaaZ/VulkanMemoryAllocator-Hpp@3.2.1)
target_link_libraries(dat-engine PUBLIC Vulkan::Headers GPUOpen::VulkanMemoryAllocator VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp)

# MMIO
CPMAddPackage("gh:Ryan-rsm-McKenzie/mmio#2.0.0")
target_link_libraries(dat-engine PUBLIC spdlog::spdlog)

## fastIO
#CPMAddPackage("gh:cppfastio/fast_io#87eee28c6130fc01459c62b708f9afde9d766b60")
#target_link_libraries(dat-engine PUBLIC fast_io:fast_io)

# FMT
CPMAddPackage("gh:fmtlib/fmt#11.2.0")
target_link_libraries(dat-engine PUBLIC fmt::fmt)

# SPDLog
CPMAddPackage(gh:gabime/spdlog@1.15.3)
target_link_libraries(dat-engine PUBLIC spdlog::spdlog)
