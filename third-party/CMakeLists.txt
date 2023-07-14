cmake_minimum_required(VERSION 3.22)

include(ExternalProject)

# Packages on the system
# GLFW for window and Inputs
find_package(SDL2 REQUIRED)
target_link_libraries(dat-engine SDL2::SDL2)

# Vulkan for vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(dat-engine vulkan)

# Packages loaded
# vk-bootstrap to setup vulkan
add_subdirectory(vk-bootstrap)
target_link_libraries(dat-engine vk-bootstrap::vk-bootstrap)

# Vulkan Memory Manager
add_subdirectory(vulkan-memory-manager)
target_link_libraries(dat-engine VulkanMemoryAllocator)

# SPDLog
add_subdirectory(spdlog)
target_link_libraries(dat-engine spdlog::spdlog)