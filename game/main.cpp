#include <iostream>

#include <DatEngine.h>

#include <gpu/vulkan/VulkanGpu.h>

using namespace DatEngine;

int main() {
    Engine::preInit();

    const auto renderer = new DatGpu::DatVk::VulkanGPU();
    // renderer->addValidationLayer("VK_LAYER_LUNARG_monitor");

    Engine::init(renderer);

    Engine::getInstance()->startLoop();
}
