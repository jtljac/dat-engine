cmake_minimum_required(VERSION 3.22)

include(ExternalProject)

# SDL3 for window and input
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
target_link_libraries(dat-engine PRIVATE SDL3::SDL3)

# Vulkan for vulkan
find_package(Vulkan REQUIRED)
target_link_libraries(dat-engine PUBLIC vulkan)

add_library( VulkanHppModule )
target_sources( VulkanHppModule PRIVATE
        FILE_SET CXX_MODULES
        BASE_DIRS ${Vulkan_INCLUDE_DIR}
        FILES ${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm
)
target_compile_features( VulkanHppModule PUBLIC cxx_std_20 )
target_link_libraries( VulkanHppModule PUBLIC Vulkan::Vulkan )
target_link_libraries( dat-engine PRIVATE VulkanHppModule )
target_compile_definitions( VulkanHppModule PUBLIC
        VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
)

# Vulkan Memory Manager
find_package(unofficial-vulkan-memory-allocator-hpp CONFIG REQUIRED)
target_link_libraries(dat-engine PUBLIC unofficial::VulkanMemoryAllocator-Hpp::VulkanMemoryAllocator-Hpp)

# MMIO
find_package(mmio CONFIG REQUIRED)
target_link_libraries(dat-engine PRIVATE mmio::mmio)

# SPDLog
find_package(fmt CONFIG REQUIRED)
target_link_libraries(dat-engine PUBLIC fmt::fmt)

# SPDLog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(dat-engine PUBLIC spdlog::spdlog)

# No third party git submodules yet