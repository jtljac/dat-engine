#define VMA_IMPLEMENTATION
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include "../vulkan-gpu.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

#include <SDL_vulkan.h>
#include <vulkan/vulkan_to_string.hpp>

#include <dat-engine.h>
#include <maths/common-maths.h>
#include <util/cvar.h>
#include <util/logger.h>

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

/**
 * Handle simple checking and unwrapping for methods that returns a vk::ResultValueType. Whenever the vk::Result isn't
 * vk::Result::eSuccess, it will log to critical and call @code return false@endcode
 *
 * This macro specifically requires that the function it is contained within returns a @code bool@endcode
 *
 * @param varDecl The variable declaration for the result. Can be auto, the correct type for the wrapped method, or an
 *                existing variable.
 * @param x The method that returns a vk::ResultValueType
 */

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

#define VK_CHECK(varDecl, x) \
    const auto wrappedResult = x;\
    if (wrappedResult.result != vk::Result::eSuccess) { \
        CORE_CRITICAL("Vulkan error occured during \"" #x "\": {}", vk::to_string(wrappedResult.result)); \
        return false; \
    } \
    varDecl = wrappedResult.value;

using namespace DatEngine::DatGPU::DatVk;

/* -------------------------------------------- */
/* Initialisation                               */
/* -------------------------------------------- */

bool VulkanGPU::initialise() {
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
    if (!initialiseFrameData()) return false;
    // if (!initialiseSyncStructures()) return false;

    CORE_INFO("Vulkan Renderer Initialised");
    return true;
}

bool VulkanGPU::initialiseInstance() {
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

bool VulkanGPU::setupDebugMessenger() {
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

bool VulkanGPU::initialisePhysicalDevice() {
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

bool VulkanGPU::initialiseDevice() {
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

bool VulkanGPU::initialiseSurface() {
    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(Engine::getInstance()->getWindow(), instance, &surface)) {
        CORE_CRITICAL("Failed to create surface with SDL.");
        return false;
    };

    this->surface = surface;
    return true;
}

bool VulkanGPU::initialiseVma() {
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
vk::Extent2D VulkanGPU::getWindowExtent(const vk::SurfaceCapabilitiesKHR surfaceCapabilities) {
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

bool VulkanGPU::initialiseSwapchain() {
    CORE_TRACE("Initialising Swapchain");
    const int32_t* bufferedFrames = CVarSystem::get()->getIntCVar("IBufferedFrames");

    VK_CHECK(const vk::SurfaceCapabilitiesKHR surfaceCapabilities, physicalDevice.getSurfaceCapabilitiesKHR(surface))

    const vk::SurfaceFormatKHR format = getBestSwapchainFormat();

    swapchainExtent = getWindowExtent(surfaceCapabilities);
    swapchainFormat = format.format;

    const uint32_t bufferedImages = DatMaths::clamp<uint32_t>(
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
bool VulkanGPU::initialiseSwapchainImages() {
    CORE_TRACE("Initialising Swapchain Images");
    VK_CHECK(const std::vector<vk::Image> swapchainImages, device.getSwapchainImagesKHR(swapchain))

    swapchainImageCount = swapchainImages.size();
    swapchainData = new SwapchainData[swapchainImageCount];

    for (int i = 0; i < swapchainImageCount; i++) {
        SwapchainData swapchainData& = swapchainData[i];
        image = swapchainImages[i];

        vk::ImageViewCreateInfo swapchainImageViewCreateInfo =
                vk::ImageViewCreateInfo()
                        .setImage(image)
                        .setViewType(vk::ImageViewType::e2D)
                        .setFormat(swapchainFormat)
                        .setComponents({})
                        .setSubresourceRange({vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

        VK_CHECK(swapchainData[i].imageView, device.createImageView(swapchainImageViewCreateInfo))
    }

    return true;
}

/* -------------------------------------------- */
/* Cleanup                                      */
/* -------------------------------------------- */

void VulkanGPU::destroyDebugMessenger() {
    // Cheeky load to make sure the function is loaded
    const auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
    if (func == nullptr)
        return;

    instance.destroyDebugUtilsMessengerEXT(debugMessenger);
    debugMessenger = nullptr;
}

void VulkanGPU::destroySwapchain() {
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

bool VulkanGPU::checkValidationLayersSupport() const {
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
VkBool32 VulkanGPU::debugCallback(const VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
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

std::unordered_map<uint32_t, uint32_t> VulkanGPU::selectQueues() {
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

int32_t VulkanGPU::getBestQueue(const vk::Flags<vk::QueueFlagBits> requiredFlags, std::vector<uint32_t>& usedQueues) const {
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

vk::SurfaceFormatKHR VulkanGPU::getBestSwapchainFormat() const {
    const auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface).value;

    for (auto surfaceFormat: surfaceFormats) {
        if (surfaceFormat.format == vk::Format::eB8G8R8Srgb &&
            surfaceFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return surfaceFormat;
        }
    }

    return surfaceFormats[0];
}
vk::PresentModeKHR VulkanGPU::getIdealPresentMode() const {
    const bool enableVsync = CVarSystem::get()->getBoolCVar("BEnableVsync");
    const auto availablePresentModes = physicalDevice.getSurfacePresentModesKHR(surface).value;

    for (const auto presentMode : availablePresentModes) {
        if (enableVsync
            ? presentMode == vk::PresentModeKHR::eFifoRelaxed
            : presentMode == vk::PresentModeKHR::eImmediate) return presentMode;
    }

    return vk::PresentModeKHR::eFifo;
}

void VulkanGPU::addValidationLayer(const char* layer) {
#ifdef _DEBUG
    validationLayers.push_back(layer);
#endif
}

/* -------------------------------------------- */
/* Override                                     */
/* -------------------------------------------- */

int VulkanGPU::getWindowFlags() {
    return SDL_WINDOW_VULKAN;
}

void VulkanGPU::cleanup() {
    destroySwapchain();

    vmaDestroyAllocator(allocator);

    device.destroy();
#ifdef _DEBUG
    destroyDebugMessenger();
#endif
    instance.destroy();
}
