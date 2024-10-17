#define VMA_IMPLEMENTATION
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include "rendering/vulkan/vulkan-renderer.h"

#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <queue>

#include <SDL_vulkan.h>

#include <dat-engine.h>
#include <maths/common-maths.h>
#include <util/cvar.h>
#include <util/logger.h>


VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

using namespace DatEngine::DatRendering::DatVk;

/* -------------------------------------------- */
/* Initialisation                               */
/* -------------------------------------------- */

bool VulkanRenderer::initialise() {
    CORE_TRACE("Initialising Vulkan Renderer");
    if (!initialiseInstance()) return false;
#ifdef _DEBUG
    if (!setupDebugMessenger()) return false;
#endif
    if (!initialisePhysicalDevice()) return false;
    if (!initialiseDevice()) return false;
    if (!initialiseVma()) return false;

    if (!initialiseSurface()) return false;
    if (!initialiseSwapchain()) return false;
    if (!initialiseSwapchainImages()) return false;
    // if (!initialiseCommands()) return false;
    // if (!initialiseSyncStructures()) return false;

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
    std::unordered_map<uint32_t, uint32_t> queues = selectQueues();

    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    queueCreateInfos.reserve(queues.size());

    // Required, size 3 as this is the largest it can be if all queues are the same queue family (Graphics, Compute,
    // Transfer)
    float queuePriorities[3] = {1.f, 1.f, 1.f};

    for (auto [fst, snd]: queues) {
        queueCreateInfos.push_back(vk::DeviceQueueCreateInfo({}, fst, snd, queuePriorities));
    }

#ifdef _DEBUG
    if (!checkValidationLayersSupport()) {
        return false;
    }
#endif

    // TODO: Make Configurable
    std::vector deviceExtensions{vk::KHRSwapchainExtensionName};

    vk::PhysicalDeviceShaderDrawParametersFeatures shaderDrawParameters(true);

    vk::PhysicalDeviceVulkan12Features features2;
    features2.setBufferDeviceAddress(true).setDescriptorIndexing(true).setPNext(&shaderDrawParameters);

    vk::PhysicalDeviceVulkan13Features features3;
    features3.setDynamicRendering(true).setSynchronization2(true).setPNext(&features2);

    vk::DeviceCreateInfo deviceInfo({}, queueCreateInfos, nullptr, deviceExtensions, nullptr, &features3);

    vk::ResultValue<vk::Device> deviceResult = physicalDevice.createDevice(deviceInfo);

    switch (deviceResult.result) {
        case vk::Result::eSuccess:
            this->device = deviceResult.value;
            break;
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

    // Get queues
    if (!unifiedTransferQueue)
        device.getQueue(transferQueueIndex, --queues[transferQueueIndex], &transferQueue);

    device.getQueue(graphicsQueueIndex, --queues[graphicsQueueIndex], &graphicsQueue);

    if (unifiedTransferQueue)
        transferQueue = graphicsQueue;
    return true;
}

bool VulkanRenderer::initialiseSurface() {
    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(Engine::getInstance()->getWindow(), instance, &surface)) {
        CORE_CRITICAL("Failed to create surface with SDL.");
        return false;
    };

    this->surface = surface;
    return true;
}

bool VulkanRenderer::initialiseVma() {
    CORE_TRACE("Initialising VMA");
    // const vma::AllocatorCreateInfo allocatorCreateInfo = vma::AllocatorCreateInfo({}, physicalDevice, device)
    //                                                              .setInstance(instance)
    //                                                              .setVulkanApiVersion(vk::ApiVersion13);
    //
    // const vk::ResultValue<vma::Allocator> allocatorResult = createAllocator(allocatorCreateInfo);
    //
    // if (allocatorResult.result != vk::Result::eSuccess) {
    //     CORE_CRITICAL("Failed to setup Vulkan Memory Allocator");
    //     return false;
    // }
    //
    // allocator = allocatorResult.value;

    const VmaAllocatorCreateInfo allocatorInfo{.physicalDevice = physicalDevice,
                                              .device = device,
                                              .instance = instance,
                                              .vulkanApiVersion = vk::ApiVersion13};

    if (vmaCreateAllocator(&allocatorInfo, &this->allocator) != VK_SUCCESS) {
        CORE_CRITICAL("Failed to create VMA allocator.");
        return false;
    }

    return true;
}
vk::Extent2D VulkanRenderer::getWindowExtent(const vk::SurfaceCapabilitiesKHR surfaceCapabilities) {
    if (surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return surfaceCapabilities.currentExtent;
    }

    int width, height;
    SDL_GetWindowSize(Engine::getInstance()->getWindow(), &width, &height);

    return {
        DatMaths::clamp<uint32_t>(width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width),
        DatMaths::clamp<uint32_t>(height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height)
    };
}

bool VulkanRenderer::initialiseSwapchain() {
    CORE_TRACE("Initialising Swapchain");
    const int32_t* bufferedFrames = CVarSystem::get()->getIntCVar("IBufferedFrames");

    const vk::ResultValue<vk::SurfaceCapabilitiesKHR> surfaceCapabilitiesResult = physicalDevice.getSurfaceCapabilitiesKHR(surface);

    if (surfaceCapabilitiesResult.result != vk::Result::eSuccess) {
        CORE_CRITICAL("Failed to get surface capabilities");
        return false;
    }

    const vk::SurfaceCapabilitiesKHR surfaceCapabilities = surfaceCapabilitiesResult.value;
    const vk::SurfaceFormatKHR format = getBestSwapchainFormat();

    swapchainExtent = getWindowExtent(surfaceCapabilities);
    swapchainFormat = format.format;

    bool bufferedImages = DatMaths::clamp<uint32_t>(
            *bufferedFrames, surfaceCapabilities.minImageCount,
            surfaceCapabilities.maxImageCount == 0 ? INT_MAX : surfaceCapabilities.maxImageCount);

    const vk::SwapchainCreateInfoKHR swapchainInfo = vk::SwapchainCreateInfoKHR()
            .setSurface(surface)
            .setMinImageCount(bufferedImages)
            .setImageFormat(swapchainFormat)
            .setImageColorSpace(format.colorSpace)
            .setImageExtent(swapchainExtent)
            .setImageArrayLayers(1)
            .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst)
            .setPresentMode(getIdealPresentMode());
    const vk::ResultValue<vk::SwapchainKHR> swapchainResult = device.createSwapchainKHR(swapchainInfo);

    if (swapchainResult.result != vk::Result::eSuccess) {
        CORE_CRITICAL("Failed to setup Swapchain");
        return false;
    }

    swapchain = swapchainResult.value;

    return true;
}
bool VulkanRenderer::initialiseSwapchainImages() {
    CORE_TRACE("Initialising Swapchain Images");
    const vk::ResultValue<std::vector<vk::Image>> swapchainImagesResult = device.getSwapchainImagesKHR(swapchain);

    if (swapchainImagesResult.result != vk::Result::eSuccess) {
        CORE_CRITICAL("Failed to get Swapchain images");
        return false;
    }

    swapchainImageCount = swapchainImagesResult.value.size();
    swapchainData = new SwapchainData[swapchainImageCount];

    for (int i = 0; i < swapchainImageCount; i++) {
        SwapchainData swapchainImage = swapchainData[i];
        swapchainImage.image = swapchainImagesResult.value[i];

        vk::ImageViewCreateInfo swapchainImageViewCreateInfo =
                vk::ImageViewCreateInfo()
                        .setImage(swapchainImage.image)
                        .setViewType(vk::ImageViewType::e2D)
                        .setFormat(swapchainFormat)
                        .setComponents({})
                        .setSubresourceRange({vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

        vk::ResultValue<vk::ImageView> imageViewResult = device.createImageView(swapchainImageViewCreateInfo);

        if (imageViewResult.result != vk::Result::eSuccess) {
            CORE_CRITICAL("Failed to create swapchain image view");
            return false;
        }

        swapchainImage.imageView = imageViewResult.value;
    }

    return true;
}

/* -------------------------------------------- */
/* Cleanup                                      */
/* -------------------------------------------- */

void VulkanRenderer::destroyDebugMessenger() {
    // Cheeky load to make sure the function is loaded
    const auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
    if (func == nullptr)
        return;

    instance.destroyDebugUtilsMessengerEXT(debugMessenger);
    debugMessenger = nullptr;
}

void VulkanRenderer::destroySwapchain() {
    device.destroySwapchainKHR(swapchain);

    for (int i = 0; i < swapchainImageCount; i++) {
        device.destroyImageView(swapchainData[i].imageView);
    }

    delete[] swapchainData;
    swapchainData = nullptr;
    swapchainImageCount = 0;
}
/* -------------------------------------------- */
/* Utils                                        */
/* -------------------------------------------- */

bool VulkanRenderer::checkValidationLayersSupport() const {
    auto layerProperties = vk::enumerateInstanceLayerProperties();
    if (layerProperties.result != vk::Result::eSuccess) {
        CORE_CRITICAL("Failed to get validation layer properties");
        return false;
    }

    bool layerMissed = false;
    for (auto validationLayer: validationLayers) {
        if (std::ranges::find_if(layerProperties.value, [&validationLayer](const vk::LayerProperties& layer) {
            return strcmp(layer.layerName, validationLayer);
        }) == layerProperties.value.end()) {
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

std::unordered_map<uint32_t, uint32_t> VulkanRenderer::selectQueues() {
    std::unordered_map<uint32_t, uint32_t> queues;
    std::vector<uint32_t> usedQueues;

    // Select graphics queue
    graphicsQueueIndex = getBestQueue(vk::QueueFlagBits::eGraphics, usedQueues);
    usedQueues.push_back(graphicsQueueIndex);
    queues[graphicsQueueIndex] = 1;

    const int32_t tempTransferQueueIndex = getBestQueue(vk::QueueFlagBits::eTransfer, usedQueues);
    if (tempTransferQueueIndex == -1) {
        transferQueueIndex = graphicsQueueIndex;
        unifiedTransferQueue = true;
    } else {
        transferQueueIndex = tempTransferQueueIndex;
        usedQueues.push_back(transferQueueIndex);
        queues[transferQueueIndex]++;
    }

    return queues;
}

int32_t VulkanRenderer::getBestQueue(const vk::Flags<vk::QueueFlagBits> requiredFlags, std::vector<uint32_t>& usedQueues) const {
    auto queueFamilies = physicalDevice.getQueueFamilyProperties();
    std::vector<uint32_t> queueOptions;

    for (uint32_t i = 0; i < queueFamilies.size(); i++) {
        const vk::QueueFamilyProperties& queueFamily = queueFamilies[i];
        const int usages = std::ranges::count_if(usedQueues, [i](const uint32_t queue) { return queue == i; });

        if (requiredFlags & queueFamily.queueFlags && usages < queueFamily.queueCount) {
            queueOptions.push_back(i);
        }
    }

    if (queueOptions.empty()) return -1;
    std::ranges::sort(queueOptions, std::ranges::less(), [&queueFamilies](const uint32_t queue) {
        return std::popcount(static_cast<uint32_t>(queueFamilies[queue].queueFlags));
    });

    const uint32_t selectedQueue = queueOptions.front();
    return selectedQueue;
}

vk::SurfaceFormatKHR VulkanRenderer::getBestSwapchainFormat() const {
    const auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface).value;

    for (auto surfaceFormat: surfaceFormats) {
        if (surfaceFormat.format == vk::Format::eB8G8R8Srgb &&
            surfaceFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return surfaceFormat;
        }
    }

    return surfaceFormats[0];
}
vk::PresentModeKHR VulkanRenderer::getIdealPresentMode() const {
    const bool enableVsync = CVarSystem::get()->getBoolCVar("BEnableVsync");
    const auto availablePresentModes = physicalDevice.getSurfacePresentModesKHR(surface).value;

    for (const auto presentMode : availablePresentModes) {
        if (enableVsync
            ? presentMode == vk::PresentModeKHR::eFifoRelaxed
            : presentMode == vk::PresentModeKHR::eImmediate) return presentMode;
    }

    return vk::PresentModeKHR::eFifo;
}

void VulkanRenderer::addValidationLayer(const char* layer) {
#ifdef _DEBUG
    validationLayers.push_back(layer);
#endif
}

/* -------------------------------------------- */
/* Override                                     */
/* -------------------------------------------- */

int VulkanRenderer::getWindowFlags() {
    return SDL_WINDOW_VULKAN;
}

void VulkanRenderer::cleanup() {
    destroySwapchain();

    vmaDestroyAllocator(allocator);

    device.destroy();
#ifdef _DEBUG
    destroyDebugMessenger();
#endif
    instance.destroy();
}
