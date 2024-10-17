#include <iostream>

#include <dat-engine.h>

#include "rendering/vulkan/vulkan-gpu.h"

using namespace DatEngine;

int main() {
    const auto renderer = new DatGPU::DatVk::VulkanGPU();
    renderer->addValidationLayer("VK_LAYER_LUNARG_monitor");

    Engine::getInstance()->init(renderer);

    Engine::getInstance()->startLoop();
}