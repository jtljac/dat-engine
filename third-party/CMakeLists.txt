cmake_minimum_required(VERSION 3.22)

include(ExternalProject)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(dat-engine SDL2::SDL2)

# Vulkan for vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(dat-engine vulkan)

# Vulkan Memory Manager
find_package(unofficial-vulkan-memory-allocator-hpp CONFIG REQUIRED)
target_link_libraries(dat-engine unofficial::VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp)

# LLFIO
find_package(llfio CONFIG REQUIRED)
target_link_libraries(dat-engine llfio::sl)

# SPDLog
find_package(fmt CONFIG REQUIRED)
target_link_libraries(dat-engine fmt::fmt)

# SPDLog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(dat-engine spdlog::spdlog)

# No third party git submodules yet