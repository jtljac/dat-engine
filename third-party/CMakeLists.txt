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

ExternalProject_Add(spdlog
        PREFIX spdlog
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/third-party/spdlog
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
        -DCMAKE_INSTALL_PREFIX=${STAGING_DIR}
        -DSPDLOG_BUILD_SHARED=OFF
)

add_dependencies(${PROJECT_NAME} spdlog)
target_include_directories(dat-engine PRIVATE ${STAGING_DIR}/include/)