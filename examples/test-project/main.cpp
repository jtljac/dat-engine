#include <iostream>

#include <dat-engine.h>

#include "rendering/vulkan/vulkan-renderer.h"

using namespace DatEngine;

int main() {
    auto renderer = new DatRendering::DatVk::VulkanRenderer();
    renderer->addValidationLayer("VK_LAYER_LUNARG_monitor");

    Engine::getInstance()->init(renderer);

    Engine::getInstance()->startLoop();
}