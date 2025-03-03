#pragma once

#include <vk_mem_alloc.h>
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>

namespace DatEngine::DatGPU::DatVk {
    struct AllocatedImage {
        vk::Image image = VK_NULL_HANDLE;
        vk::ImageView view = VK_NULL_HANDLE;
        VmaAllocation allocation = VK_NULL_HANDLE;
        vk::Extent3D extent = {};
        vk::Format format = {};
    };
} // namespace DatEngine::DatGPU::DatVk
