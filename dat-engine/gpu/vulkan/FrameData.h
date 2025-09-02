#pragma once

#include "VkStub.h"

namespace vk {
    class Image;
    class ImageView;
}

namespace DatEngine::DatGpu::DatVk {
    /**
     * Data for a frame in the swapchain
     */
    struct SwapchainData {
        /** An image in the swapchain */
        vk::Image image;
        /** The ImageView for the swapchain image */
        vk::ImageView imageView;

        /** A Semaphore tracking once rendering has finished and ready to present */
        vk::Semaphore renderSemaphore;
    };

    /**
     * Group of data used by a single frame for rendering
     */
    struct FrameData {
        /** The command pool for the frame */
        vk::CommandPool commandPool;
        /** The command buffer from the command pool for the frame */
        vk::CommandBuffer commandBuffer;

        /** A Fence for tracking when the GPU has finished drawing a frame */
        vk::Fence renderFence;
        /** A Semaphore tracking retrieving a swapchain image */
        vk::Semaphore swapchainSemaphore;
    };
}