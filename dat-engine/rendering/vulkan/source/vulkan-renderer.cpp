//
// Created by jacob on 10/07/23.
//

#include "rendering/vulkan/vulkan-renderer.h"

#include <iostream>
#include <SDL_vulkan.h>

#include <util/logger.h>

bool VulkanRenderer::initialise() {
    CORE_TRACE("Initialising Vulkan Renderer");

    // VK Instance
    CORE_TRACE("Creating VK Instance");
    {
        vk::ApplicationInfo applicationInfo(
                "Test-App",   // TODO: Allow custom names
                VK_MAKE_VERSION(1, 0, 0),
                "Dat Engine",
                VK_MAKE_VERSION(1, 0, 0),
                VK_API_VERSION_1_3
        );
        SDL_Vulkan_LoadLibrary(nullptr);

        uint32_t count;
        SDL_Vulkan_GetInstanceExtensions(nullptr, &count, nullptr);
        std::vector<const char*> extensions(count);
        if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, extensions.data())) {
            CORE_CRITICAL("Failed to get required instance extensions.");
            return false;
        }

        CORE_DEBUG("SDL Instance Extensions:");
        for (const char* item: extensions) {
            CORE_DEBUG("- %s", item);
        }

        std::vector<const char*> layers;

        vk::InstanceCreateInfo instanceInfo({}, &applicationInfo, layers, extensions);
        vk::ResultValue<vk::Instance> instanceResult = vk::createInstance(instanceInfo);

        if (instanceResult.result != vk::Result::eSuccess) {
            CORE_CRITICAL("Failed to create vulkan instance");
            return false;
        }
        this->instance = instanceResult.value;
    }

    // Physical Device
    {
        CORE_TRACE("Creating VK Physical Device");
        vk::ResultValue<std::vector<vk::PhysicalDevice>> devicesResult = instance.enumeratePhysicalDevices();
        if (devicesResult.result != vk::Result::eSuccess) {
            CORE_CRITICAL("Failed to get the available GPUs");
            return false;
        } else if (devicesResult.value.empty()) {
            CORE_CRITICAL("Failed to find any GPUs");
            return false;
        }

        // TODO: Some selection process
        this->physicalDevice = devicesResult.value[0];
    }

    // Logical Device
    {
        CORE_TRACE("Creating VK Logical Device");
        vk::DeviceCreateInfo deviceInfo(

        )
    }
    CORE_INFO("Vulkan Renderer Initialised");
    return true;
}

void VulkanRenderer::cleanup() {

}
