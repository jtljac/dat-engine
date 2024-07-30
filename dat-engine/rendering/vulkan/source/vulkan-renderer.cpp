//
// Created by jacob on 10/07/23.
//

#include "rendering/vulkan/vulkan-renderer.h"

#include <iostream>
#include <SDL_vulkan.h>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include <util/logger.h>

using namespace DatEngine;

bool VulkanRenderer::initialise() {
    CORE_TRACE("Initialising Vulkan Renderer");
    if (!initialiseInstance()) return false;
    if (!initialisePhysicalDevice()) return false;
    if (!initialiseDevice()) return false;
    if (!initialiseVma()) return false;

    CORE_INFO("Vulkan Renderer Initialised");
    return true;
}

bool VulkanRenderer::initialiseInstance() {
    CORE_TRACE("Creating VK Instance");

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
        CORE_DEBUG("- {}", item);
    }

    std::vector<const char*> layers;

    vk::InstanceCreateInfo instanceInfo({}, &applicationInfo, layers, extensions);
    vk::ResultValue<vk::Instance> instanceResult = vk::createInstance(instanceInfo);

    switch (instanceResult.result) {
        case vk::Result::eSuccess:
            this->instance = instanceResult.value;
            return true;
        case vk::Result::eErrorExtensionNotPresent:
            CORE_CRITICAL("Failed to create vulkan instance due to required extensions not being present.");
            return false;
        default:
            CORE_CRITICAL("Failed to create vulkan instance.");
            return false;
    }
}

bool VulkanRenderer::initialisePhysicalDevice() {
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

    return true;
}

bool VulkanRenderer::initialiseDevice() {
    CORE_TRACE("Creating VK Logical Device");

    // TODO: Figure out some queues
    std::vector<vk::DeviceQueueCreateInfo> queues;

    // TODO: Make Configurable
    std::vector<const char*> validationLayers {

    };

    // TODO: Make Configurable
    std::vector<const char*> deviceExtensions {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME
    };

    auto test = physicalDevice.enumerateDeviceExtensionProperties(nullptr);

    for (const auto& item: test.value) {
        CORE_INFO("{}", item.extensionName.data());
    }

    vk::PhysicalDeviceFeatures deviceFeatures;
    deviceFeatures.setFillModeNonSolid(VK_TRUE);

    vk::PhysicalDeviceShaderDrawParametersFeatures shaderDrawParameters(VK_TRUE);

    vk::DeviceCreateInfo deviceInfo(
            {},
            queues,
            validationLayers,
            deviceExtensions,
            &deviceFeatures,
            &shaderDrawParameters
    );

    vk::ResultValue<vk::Device> deviceResult = physicalDevice.createDevice(deviceInfo);

    switch(deviceResult.result) {
        case vk::Result::eSuccess:
            this->device = deviceResult.value;
            return true;
        case vk::Result::eErrorExtensionNotPresent:
            CORE_CRITICAL("Failed to setup device due to required extensions not being present.");
            return false;
        case vk::Result::eErrorFeatureNotPresent:
            CORE_CRITICAL("Failed to setup device due to required features not being present.");
            return false;
        default:
            CORE_CRITICAL("Failed to setup device");
            return false;
    }
}

bool VulkanRenderer::initialiseVma() {
    VmaAllocatorCreateInfo allocatorInfo{
        .physicalDevice = physicalDevice,
        .device = device,
        .instance = instance,
        .vulkanApiVersion = VK_API_VERSION_1_3
    };

    if (vmaCreateAllocator(&allocatorInfo, &this->allocator) != VK_SUCCESS) {
        CORE_CRITICAL("Failed to setup Vulkan Memory Allocator");
        return false;
    }

    return true;
}

void VulkanRenderer::cleanup() {

    vmaDestroyAllocator(allocator);

    device.destroy();
    instance.destroy();

    IRenderer::cleanup();
}
