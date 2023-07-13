//
// Created by jacob on 10/07/23.
//

#pragma once


#include "rendering/irenderer.h"

#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan.hpp>

class VulkanRenderer : public IRenderer {
protected:
    vk::Instance instance;
    vk::PhysicalDevice physicalDevice;
    vk::Device device;
public:
    bool initialise() override;

    void cleanup() override;
};
