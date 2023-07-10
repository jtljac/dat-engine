//
// Created by jacob on 10/07/23.
//

#include "rendering/vulkan/vulkan-renderer.h"

#include <SDL_vulkan.h>
#include <iostream>

bool VulkanRenderer::initialise() {
    // VK Instance
    vk::ApplicationInfo applicationInfo(
            "Test-App",   // TODO: Allow custom names
            VK_MAKE_VERSION(1, 0, 0),
            "Dat Engine",
            VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_3
    );
    SDL_Vulkan_LoadLibrary(nullptr);

    unsigned int count;
    SDL_Vulkan_GetInstanceExtensions(nullptr, &count, nullptr);
    std::vector<const char*> extensions(count);
    if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, extensions.data()))

    std::cout << "test";

    // VK Device

    return false;
}

void VulkanRenderer::cleanup() {

}
