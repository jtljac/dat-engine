//
// Created by jacob on 10/07/23.
//

#include "rendering/vulkan/vulkan-renderer.h"


#include <algorithm>
#include <iostream>
#include <SDL_vulkan.h>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include <util/logger.h>

#include "maths/vector/vec1.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

using namespace DatEngine;

bool VulkanRenderer::initialise() {
    CORE_TRACE("Initialising Vulkan Renderer");
    if (!initialiseInstance()) return false;
#ifdef _DEBUG
    if (!setupDebugMessenger()) return false;
#endif
    if (!initialisePhysicalDevice()) return false;
    if (!initialiseDevice()) return false;
    if (!initialiseVma()) return false;

    CORE_INFO("Vulkan Renderer Initialised");
    return true;
}

bool VulkanRenderer::initialiseInstance() {
    CORE_TRACE("Creating VK Instance");

    constexpr vk::ApplicationInfo applicationInfo("Test-App", // TODO: Allow custom names
                                                  vk::makeApiVersion(0, 1, 0, 0), "Dat Engine",
                                                  vk::makeApiVersion(0, 1, 0, 0), vk::ApiVersion13);

    SDL_Vulkan_LoadLibrary(nullptr);
    VULKAN_HPP_DEFAULT_DISPATCHER.init();

    uint32_t count;
    SDL_Vulkan_GetInstanceExtensions(nullptr, &count, nullptr);
    std::vector<const char*> extensions(count);
    if (!SDL_Vulkan_GetInstanceExtensions(nullptr, &count, extensions.data())) {
        CORE_CRITICAL("Failed to get required instance extensions.");
        return false;
    }

#ifdef _DEBUG
    extensions.push_back(vk::EXTDebugUtilsExtensionName);
#endif

    CORE_DEBUG("SDL Instance Extensions:");
    for (const char* item: extensions) {
        CORE_DEBUG("- {}", item);
    }


#ifdef _DEBUG
     std::vector<const char*>& layers = this->validationLayers;
#else
    std::vector<const char*> layers;
#endif

    const vk::InstanceCreateInfo instanceInfo({}, &applicationInfo, layers, extensions);

    const vk::ResultValue<vk::Instance> instanceResult = createInstance(instanceInfo);

    switch (instanceResult.result) {
        case vk::Result::eSuccess:
            this->instance = instanceResult.value;
            VULKAN_HPP_DEFAULT_DISPATCHER.init(instance);
            return true;
        case vk::Result::eErrorExtensionNotPresent:
            CORE_CRITICAL("Failed to create vulkan instance due to required extensions not being present.");
            return false;
        default:
            CORE_CRITICAL("Failed to create vulkan instance.");
            return false;
    }
}

bool VulkanRenderer::setupDebugMessenger() {
    const auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
    if (func == nullptr) {
        CORE_CRITICAL("Failed to find debug messenger address.");
        return false;
    }

    const auto messengerResult = instance.createDebugUtilsMessengerEXT(vk::DebugUtilsMessengerCreateInfoEXT(
        {},
        vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
        | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
        | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
        debugCallback, nullptr));

    if (messengerResult.result != vk::Result::eSuccess) {
        CORE_CRITICAL("Failed to create debug messenger.");
        return false;
    }

    debugMessenger = messengerResult.value;
    return true;
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

#ifdef _DEBUG
    if (!checkValidationLayersSupport()) {
        return false;
    }
#endif

    // TODO: Make Configurable
    std::vector deviceExtensions {
        vk::KHRSwapchainExtensionName
    };

    auto test = physicalDevice.enumerateDeviceExtensionProperties(nullptr);

    for (const auto& item: test.value) {
        CORE_DEBUG("{}", item.extensionName.data());
    }

    vk::PhysicalDeviceShaderDrawParametersFeatures shaderDrawParameters(true);

    vk::PhysicalDeviceVulkan12Features features2;
    features2.setBufferDeviceAddress(true)
            .setDescriptorIndexing(true)
            .setPNext(&shaderDrawParameters);

    vk::PhysicalDeviceVulkan13Features features3;
    features3.setDynamicRendering(true)
            .setSynchronization2(true)
            .setPNext(&features2);


    vk::DeviceCreateInfo deviceInfo(
            {},
            queues,
            nullptr,
            deviceExtensions,
            nullptr,
            &features3
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
    const VmaAllocatorCreateInfo allocatorInfo{.physicalDevice = physicalDevice,
                                               .device = device,
                                               .instance = instance,
                                               .vulkanApiVersion = vk::ApiVersion13};

    if (vmaCreateAllocator(&allocatorInfo, &this->allocator) != VK_SUCCESS) {
        CORE_CRITICAL("Failed to setup Vulkan Memory Allocator");
        return false;
    }

    return true;
}
void VulkanRenderer::destroyDebugMessenger() {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT");
    if (func == nullptr) return;

    instance.destroyDebugUtilsMessengerEXT(debugMessenger);
}

bool VulkanRenderer::checkValidationLayersSupport() const {
    auto layerProperties = vk::enumerateInstanceLayerProperties();
    if (layerProperties.result != vk::Result::eSuccess) {
        CORE_CRITICAL("Failed to get validation layer properties");
        return false;
    }

    bool layerMissed = false;
    for (auto validationLayer: validationLayers) {
        if (std::ranges::find_if(layerProperties.value,
            [&validationLayer](const vk::LayerProperties& layer) {return strcmp(layer.layerName, validationLayer);})
            == layerProperties.value.end()) {
            CORE_CRITICAL("Failed to find validation layer: {}", validationLayer);
            layerMissed = true;
        }
    }

    return !layerMissed;
}
VkBool32 VulkanRenderer::debugCallback(const VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                       const VkDebugUtilsMessageTypeFlagsEXT messageType,
                                       const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::string type;
    switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            type = "General";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            type = "Validation";
            break;
        case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
            type = "Performance";
            break;
        default:;
    }

    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            CORE_DEBUG("[Vulkan Validation][{}]: {}", type, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            CORE_INFO("[Vulkan Validation][{}]: {}", type, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            CORE_WARN("[Vulkan Validation][{}]: {}", type, pCallbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            CORE_ERROR("[Vulkan Validation][{}]: {}", type, pCallbackData->pMessage);
            break;
        default:;
    }

    return VK_FALSE;
}

int VulkanRenderer::getWindowFlags() {
    return SDL_WINDOW_VULKAN;
}

void VulkanRenderer::cleanup() {

    vmaDestroyAllocator(allocator);

    device.destroy();
#ifdef _DEBUG
    destroyDebugMessenger();
#endif
    instance.destroy();
}

void VulkanRenderer::addValidationLayer(const char* layer) {
#ifdef _DEBUG
    validationLayers.push_back(layer);
#endif
}
