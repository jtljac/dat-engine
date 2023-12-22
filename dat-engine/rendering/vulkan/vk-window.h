//
// Created by jacob on 14/07/23.
//

#pragma once

#include "../iwindow.h"
#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan.hpp>

/**
 * A window implementation for Vulkan
 */
class VkWindow : public IWindow {
    vk::SurfaceKHR surface;
    // Swapchain
    // 
};