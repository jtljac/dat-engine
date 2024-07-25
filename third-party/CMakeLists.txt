cmake_minimum_required(VERSION 3.22)

include(ExternalProject)

# Packages on the system
# GLFW for window and Inputs
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(dat-engine SDL2::SDL2)

# Vulkan for vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(dat-engine vulkan)

# Packages loaded
# Vulkan Memory Manager
find_package(unofficial-vulkan-memory-allocator-hpp CONFIG REQUIRED)
target_link_libraries(dat-engine unofficial::VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp)

# SPDLog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(dat-engine spdlog::spdlog)