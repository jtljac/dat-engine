cmake_minimum_required(VERSION 3.22)

include(ExternalProject)

# SDL3 for window and input
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
target_link_libraries(dat-engine PRIVATE SDL3::SDL3)

# Vulkan for vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(dat-engine PUBLIC vulkan)

# Vulkan Memory Manager
find_package(unofficial-vulkan-memory-allocator-hpp CONFIG REQUIRED)
target_link_libraries(dat-engine PUBLIC unofficial::VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp)

# LLFIO
find_package(llfio CONFIG REQUIRED)
target_link_libraries(dat-engine PUBLIC llfio::sl)

# SPDLog
find_package(fmt CONFIG REQUIRED)
target_link_libraries(dat-engine PUBLIC fmt::fmt)

# SPDLog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(dat-engine PUBLIC spdlog::spdlog)

# No third party git submodules yet