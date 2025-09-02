#pragma once

#include "VkStub.h"

namespace DatEngine::DatGpu::DatVk {
    struct AllocatedImage {
        vk::Image image = VK_NULL_HANDLE;
        vk::ImageView view = VK_NULL_HANDLE;
        vma::Allocation allocation = VK_NULL_HANDLE;
        vk::Extent3D extent = {};
        vk::Format format = {};
    };
} // namespace DatEngine::DatGPU::DatVk