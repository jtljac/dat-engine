#include <iostream>

#include <dat-engine.h>

#include <gpu/vulkan/vulkan-gpu.h>

using namespace DatEngine;

int main() {
    Engine::preInit();

    const auto renderer = new DatGPU::DatVk::VulkanGPU();
    renderer->addValidationLayer("VK_LAYER_LUNARG_monitor");

    Engine::init(renderer);

    Engine::getInstance()->startLoop();


}