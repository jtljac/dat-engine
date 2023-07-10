//
// Created by jacob on 10/07/23.
//

#pragma once


#include "rendering/irenderer.h"

#define VULKAN_HPP_NO_EXCEPTIONS = 1
#include <vulkan/vulkan.hpp>

class VulkanRenderer : public IRenderer {
protected:
public:
    bool initialise() override;

    void cleanup() override;
};
