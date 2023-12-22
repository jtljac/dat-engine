//
// Created by jacob on 10/07/23.
//

#pragma once


#include "rendering/irenderer.h"
#include "vk-window.h"

#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan.hpp>
#include <vk_mem_alloc.h>


/**
 * A renderer implementation for the Vulkan Graphics API
 */
class VulkanRenderer : public IRenderer<VkWindow> {
protected:
    // Vulkan Instance
    vk::Instance instance;
    vk::PhysicalDevice physicalDevice;
    vk::Device device;

    // Memory Management
    VmaAllocator allocator = VK_NULL_HANDLE;

    /**
     * Setup the Vulkan Instance
     * @return true if successful
     */
    bool initialiseInstance();

    /**
     * Select a physical device for vulkan to use
     * @return true if successful
     */
    bool initialisePhysicalDevice();

    /**
     * Create a logical device
     * @return true if successful
     */
    bool initialiseDevice();

    /**
     * Setup Vulkan Memory Manager
     * @return true if successful
     */
    bool initialiseVma();
public:
    bool initialise() override;

    void cleanup() override;
};
