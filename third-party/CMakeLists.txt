cmake_minimum_required(VERSION 3.22)

# Packages on the system
# GLFW for window and Inputs
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(dat-engine glfw)

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
