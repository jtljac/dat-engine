#define VMA_IMPLEMENTATION
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1
#include "../vulkan-gpu.h"
#include "../vk-shortcuts.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_to_string.hpp>
#include <vk_mem_alloc.h>

#include <dat-engine.h>
#include <maths/common-maths.h>
#include <util/cvar.h>
#include <util/logger.h>

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

using namespace DatEngine::DatGPU::DatVk;

/* -------------------------------------------- */
/* Initialisation                               */
/* -------------------------------------------- */

bool VulkanGPU::initialise() {
    CORE_TRACE("Initialising Vulkan Renderer");
    if (!initialiseInstance())
        return false;
#ifdef _DEBUG
    if (!setupDebugMessenger())
        return false;
#endif
    if (!initialisePhysicalDevice())
        return false;
    if (!initialiseDevice())
        return false;
    if (!initialiseVma())
        return false;

    if (!initialiseSurface())
        return false;
    if (!initialiseSwapchain())
        return false;
    if (!initialiseSwapchainImages())
        return false;
    if (!initialiseFrameData())
        return false;
    if (!initialiseGBuffers())
        return false;
    if (!initialiseDescriptors())
        return false;
    if (!initialisePipelines())
        return false;

    CORE_INFO("Vulkan Renderer Initialised");
    return true;
}

void VulkanGPU::draw() {
    auto& [commandPool, commandBuffer, renderFence, renderSemaphore, swapchainSemaphore] = getCurrentFrame();

    // Wait for the last usage of this swapchain image to finish
    VK_QUICK_FAIL(device.waitForFences(1, &renderFence, true, 1000000000));
    VK_QUICK_FAIL(device.resetFences(1, &renderFence));

    uint32_t swapchainImageIndex;
    VK_QUICK_FAIL(device.acquireNextImageKHR(swapchain, 1000000000, swapchainSemaphore, nullptr, &swapchainImageIndex));
    auto& [swapchainImage, swapchainImageView] = swapchainData[swapchainImageIndex];

    VK_QUICK_FAIL(commandBuffer.reset());
    VK_QUICK_FAIL(commandBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit)));

    Shortcuts::transitionImage(commandBuffer, drawImage.image,
                               vk::ImageLayout::eUndefined, vk::ImageLayout::eGeneral,
                               vk::PipelineStageFlagBits2::eTopOfPipe,vk::PipelineStageFlagBits2::eTopOfPipe,
                               vk::AccessFlagBits2::eNone, vk::AccessFlagBits2::eMemoryWrite);

    drawBackground(commandBuffer);

    // Copy draw image to swapchain image
    Shortcuts::transitionImage(commandBuffer, drawImage.image,
                               vk::ImageLayout::eGeneral, vk::ImageLayout::eTransferSrcOptimal,
                               vk::PipelineStageFlagBits2::eTopOfPipe,vk::PipelineStageFlagBits2::eComputeShader,
                               vk::AccessFlagBits2::eMemoryWrite, vk::AccessFlagBits2::eMemoryRead);
    Shortcuts::transitionImage(commandBuffer, swapchainImage,
                               vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal,
                               vk::PipelineStageFlagBits2::eTopOfPipe,vk::PipelineStageFlagBits2::eComputeShader,
                               vk::AccessFlagBits2::eNone, vk::AccessFlagBits2::eMemoryWrite);
    Shortcuts::copyImageToImage(commandBuffer, drawImage.image, swapchainImage, drawImageExtent, swapchainExtent);
    Shortcuts::transitionImage(commandBuffer, swapchainImage,
                               vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::ePresentSrcKHR,
                               vk::PipelineStageFlagBits2::eComputeShader,vk::PipelineStageFlagBits2::eComputeShader,
                               vk::AccessFlagBits2::eMemoryWrite, vk::AccessFlagBits2::eMemoryRead);

    VK_QUICK_FAIL(commandBuffer.end());

    vk::SemaphoreSubmitInfo semaphoreWaitInfo(swapchainSemaphore, 1, vk::PipelineStageFlagBits2::eColorAttachmentOutput);
    vk::SemaphoreSubmitInfo semaphoreSignalInfo(renderSemaphore, 1, vk::PipelineStageFlagBits2::eAllGraphics);

    vk::CommandBufferSubmitInfo commandBufferSubmitInfo(commandBuffer);

    vk::SubmitInfo2 submitInfo({}, 1, &semaphoreWaitInfo, 1, &commandBufferSubmitInfo, 1, &semaphoreSignalInfo);
    VK_QUICK_FAIL(graphicsQueue.submit2(1, &submitInfo, renderFence));

    VK_QUICK_FAIL(graphicsQueue.presentKHR(vk::PresentInfoKHR(1, &renderSemaphore, 1, &swapchain, &swapchainImageIndex)));

    ++frameNumber;
}

void VulkanGPU::drawBackground(const vk::CommandBuffer cmd) {
    cmd.clearColorImage(drawImage.image, vk::ImageLayout::eGeneral,
                                  {0.f, 0.f, std::abs(DatMaths::sin(frameNumber / 120.f)), 0.f},
                                  vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor,
                                      0, vk::RemainingMipLevels,
                                      0, vk::RemainingArrayLayers));
}



bool VulkanGPU::initialiseInstance() {
    CORE_TRACE("Creating VK Instance");

    constexpr vk::ApplicationInfo applicationInfo("Test-App", // TODO: Allow custom names
                                                  vk::makeApiVersion(0, 1, 0, 0), "Dat Engine",
                                                  vk::makeApiVersion(0, 1, 0, 0), vk::ApiVersion13);

    SDL_Vulkan_LoadLibrary(nullptr);
    VULKAN_HPP_DEFAULT_DISPATCHER.init();

    uint32_t sdlInstanceExtensionsCount;
    const char* const* sdlInstanceExtensions = SDL_Vulkan_GetInstanceExtensions(&sdlInstanceExtensionsCount);

    if (sdlInstanceExtensions == nullptr) {
        CORE_CRITICAL("Failed to get required instance extensions.");
        return false;
    }

    std::vector<const char*> extensions(sdlInstanceExtensionsCount);
    std::memcpy(extensions.data(), sdlInstanceExtensions, sdlInstanceExtensionsCount * sizeof(char*));

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

    VK_CHECK(this->instance, vk::createInstance(instanceInfo));

    vk::detail::defaultDispatchLoaderDynamic.init(instance);

    return true;
}

bool VulkanGPU::setupDebugMessenger() {
    const auto func = reinterpret_cast<vk::PFN_DebugUtilsMessengerCallbackEXT>(
            instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
    if (func == nullptr) {
        CORE_CRITICAL("Failed to find debug messenger address.");
        return false;
    }

    VK_CHECK(debugMessenger, instance.createDebugUtilsMessengerEXT(
                    vk::DebugUtilsMessengerCreateInfoEXT(
                            {},
                            vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo
                                    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                                    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
                                    | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
                            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                                    | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
                                    | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
                            debugCallback,
                            nullptr
                    )
            )
    );
    return true;
}

bool VulkanGPU::initialisePhysicalDevice() {
    CORE_TRACE("Creating VK Physical Device");

    VK_CHECK(const std::vector<vk::PhysicalDevice> physicalDevices, instance.enumeratePhysicalDevices())

    if (physicalDevices.empty()) {
        CORE_CRITICAL("Failed to find any GPUs");
        return false;
    }

    // TODO: Some selection process
    this->physicalDevice = physicalDevices[0];

    return true;
}

bool VulkanGPU::initialiseDevice() {
    CORE_TRACE("Creating VK Logical Device");

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

    std::vector deviceExtensions{vk::KHRSwapchainExtensionName};

    vk::PhysicalDeviceShaderDrawParametersFeatures shaderDrawParameters(true);

    vk::PhysicalDeviceVulkan12Features features2;
    features2.setBufferDeviceAddress(true).setDescriptorIndexing(true).setPNext(&shaderDrawParameters);

    vk::PhysicalDeviceVulkan13Features features3;
    features3.setDynamicRendering(true).setSynchronization2(true).setPNext(&features2);

    vk::DeviceCreateInfo deviceInfo({}, queueCreateInfos, nullptr, deviceExtensions, nullptr, &features3);

    VK_CHECK(this->device, physicalDevice.createDevice(deviceInfo));

    // Get queues
    if (!unifiedTransferQueue)
        device.getQueue(transferQueueIndex, --queues[transferQueueIndex], &transferQueue);

    device.getQueue(graphicsQueueIndex, --queues[graphicsQueueIndex], &graphicsQueue);

    if (unifiedTransferQueue)
        transferQueue = graphicsQueue;
    return true;
}

bool VulkanGPU::initialiseVma() {
    CORE_TRACE("Initialising VMA");
    const vma::AllocatorCreateInfo allocatorCreateInfo = vma::AllocatorCreateInfo({}, physicalDevice, device)
                                                                 .setInstance(instance)
                                                                 .setVulkanApiVersion(vk::ApiVersion13);

    VK_CHECK(allocator, createAllocator(allocatorCreateInfo));

    return true;
}

bool VulkanGPU::initialiseSurface() {
    CORE_TRACE("Creating Surface");
    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(Engine::getInstance()->getWindow(), instance, nullptr, &surface)) {
        CORE_CRITICAL("Failed to create surface with SDL.");
        return false;
    };

    this->surface = surface;
    return true;
}

bool VulkanGPU::initialiseSwapchain() {
    CORE_TRACE("Initialising Swapchain");
    bufferedFrames = *CVarSystem::get()->getIntCVar("IBufferedFrames");

    VK_CHECK(const vk::SurfaceCapabilitiesKHR surfaceCapabilities, physicalDevice.getSurfaceCapabilitiesKHR(surface))

    const vk::SurfaceFormatKHR format = getBestSwapchainFormat();

    swapchainExtent = getWindowExtent(surfaceCapabilities);
    swapchainFormat = format.format;

    const uint32_t bufferedImages = DatMaths::clamp<uint32_t>(
            bufferedFrames, surfaceCapabilities.minImageCount,
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

    VK_CHECK(swapchain, device.createSwapchainKHR(swapchainInfo));

    return true;
}
bool VulkanGPU::initialiseSwapchainImages() {
    CORE_TRACE("Initialising Swapchain Images");
    VK_CHECK(const std::vector<vk::Image> swapchainImages, device.getSwapchainImagesKHR(swapchain))

    swapchainImageCount = swapchainImages.size();
    swapchainData = new SwapchainData[swapchainImageCount];

    for (int i = 0; i < swapchainImageCount; i++) {
        auto& [image, imageView] = swapchainData[i];

        image = swapchainImages[i];

        vk::ImageViewCreateInfo swapchainImageViewCreateInfo =
                vk::ImageViewCreateInfo()
                        .setImage(image)
                        .setViewType(vk::ImageViewType::e2D)
                        .setFormat(swapchainFormat)
                        .setComponents({})
                        .setSubresourceRange({vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

        VK_CHECK(imageView, device.createImageView(swapchainImageViewCreateInfo))
    }

    return true;
}

bool VulkanGPU::initialiseFrameData() {
    CORE_TRACE("Initialising Frame Data");

    frameData = new FrameData[bufferedFrames];
    for (int i = 0; i < bufferedFrames; i++) {
        if (!initialiseFrameCommandStructure(frameData[i])) return false;
        if (!initialiseFrameSyncStructure(frameData[i])) return false;
    }

    return true;
}

bool VulkanGPU::initialiseFrameCommandStructure(FrameData& frameData) const {
    const vk::CommandPoolCreateInfo commandPoolCreateInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer, graphicsQueueIndex);
    VK_CHECK(frameData.commandPool, device.createCommandPool(commandPoolCreateInfo));

    const vk::CommandBufferAllocateInfo commandAllocCreateInfo(frameData.commandPool, vk::CommandBufferLevel::ePrimary,1);
    VK_CHECK(const std::vector<vk::CommandBuffer> bufferList, device.allocateCommandBuffers(commandAllocCreateInfo));
    frameData.commandBuffer = bufferList[0];

    return true;
}

bool VulkanGPU::initialiseFrameSyncStructure(FrameData& frameData) const {
    VK_CHECK(frameData.renderFence, device.createFence(vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled)));

    VK_CHECK(frameData.renderSemaphore, device.createSemaphore({}));
    VK_CHECK(frameData.swapchainSemaphore, device.createSemaphore({}));

    return true;
}

bool VulkanGPU::initialiseGBuffers() {
    CORE_TRACE("Initialising G-Buffers");
    drawImageExtent = swapchainExtent;

    drawImage.format = vk::Format::eR16G16B16A16Sfloat;
    drawImage.extent = vk::Extent3D{drawImageExtent.width, drawImageExtent.height, 1};

    const vk::ImageCreateInfo drawImageCreateInfo = Shortcuts::getImageCreateInfo(
            drawImage.format,
            vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst
                    | vk::ImageUsageFlagBits::eStorage | vk::ImageUsageFlagBits::eColorAttachment,
            drawImage.extent
    );

    std::pair<vk::Image, vma::Allocation> result;
    VK_CHECK(result, allocator.createImage(drawImageCreateInfo, {
            {},
            vma::MemoryUsage::eGpuOnly,
            vk::MemoryPropertyFlagBits::eDeviceLocal
    }));

    drawImage.image = result.first;
    drawImage.allocation = result.second;

    VK_CHECK(drawImage.view,
        device.createImageView(Shortcuts::getImageViewCreateInfo(drawImage.format, drawImage.image, vk::ImageAspectFlagBits::eColor)));

    return true;
}

bool VulkanGPU::initialiseDescriptors() {
    globalDescriptorAllocator.initPool(device, 10, {{{vk::DescriptorType::eStorageImage, 1}}});

    drawImageDescriptorSetLayout = Shortcuts::DescriptorLayoutBuilder()
                                           .addBinding(0, vk::DescriptorType::eStorageImage)
                                           .build(device, vk::ShaderStageFlagBits::eCompute);

    drawImageDescriptorSet = globalDescriptorAllocator.allocate(drawImageDescriptorSetLayout);

    vk::DescriptorImageInfo imagInfo = {{}, drawImage.view, vk::ImageLayout::eGeneral};

    vk::WriteDescriptorSet
            writeDescriptorSet{drawImageDescriptorSet, 0, {}, 1, vk::DescriptorType::eStorageImage, &imagInfo};

    device.updateDescriptorSets(1, &writeDescriptorSet, 0, nullptr);

    return true;
}

bool VulkanGPU::initialisePipelines() {

}

/* -------------------------------------------- */
/* Cleanup                                      */
/* -------------------------------------------- */

void VulkanGPU::destroyDebugMessenger() {
    CORE_TRACE("Destroying Debug Messenger");
    // Cheeky load to make sure the function is loaded
    const auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
    if (func == nullptr)
        return;

    instance.destroyDebugUtilsMessengerEXT(debugMessenger);
    debugMessenger = nullptr;
}

void VulkanGPU::destroySwapchain() {
    CORE_TRACE("Destroying the Swapchain");
    device.destroySwapchainKHR(swapchain);

    for (int i = 0; i < swapchainImageCount; i++) {
        device.destroyImageView(swapchainData[i].imageView);
    }
    delete[] swapchainData;

    for (int i = 0; i < bufferedFrames; i++) {
        auto& [commandPool, _, renderFence, renderSemaphore, swapchainSemaphore] = frameData[i];
        device.destroyCommandPool(commandPool);

        device.destroySemaphore(renderSemaphore);
        device.destroySemaphore(swapchainSemaphore);
        device.destroyFence(renderFence);
    }
    delete[] frameData;

    swapchainData = nullptr;
    swapchainImageCount = 0;
}

void VulkanGPU::destroyGpuMemory() {
}

/* -------------------------------------------- */
/* Utils                                        */
/* -------------------------------------------- */

bool VulkanGPU::checkValidationLayersSupport() const {
    VK_CHECK(std::vector<vk::LayerProperties> layerProperties, vk::enumerateInstanceLayerProperties())

    bool layerMissed = false;
    for (auto validationLayer: validationLayers) {
        if (std::ranges::find_if(layerProperties, [&validationLayer](const vk::LayerProperties& layer) {
            return strcmp(layer.layerName, validationLayer);
        }) == layerProperties.end()) {
            CORE_CRITICAL("Failed to find validation layer: {}", validationLayer);
            layerMissed = true;
        }
    }

    return !layerMissed;
}
VkBool32 VulkanGPU::debugCallback(const vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                       const vk::DebugUtilsMessageTypeFlagsEXT messageType,
                                       const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::string type = vk::to_string(messageType);

    switch (messageSeverity) {
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
            CORE_DEBUG("[Vulkan Validation][{}]: {}", type, pCallbackData->pMessage);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
            CORE_INFO("[Vulkan Validation][{}]: {}", type, pCallbackData->pMessage);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
            CORE_WARN("[Vulkan Validation][{}]: {}", type, pCallbackData->pMessage);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
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

vk::Extent2D VulkanGPU::getWindowExtent(const vk::SurfaceCapabilitiesKHR& surfaceCapabilities) {
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

vk::PresentModeKHR VulkanGPU::getIdealPresentMode() const {
    const bool enableVsync = CVarSystem::get()->getBoolCVar("BEnableVsync");
    const auto availablePresentModes = physicalDevice.getSurfacePresentModesKHR(surface).value;

    for (const auto presentMode: availablePresentModes) {
        if (enableVsync ? presentMode == vk::PresentModeKHR::eFifoRelaxed
                        : presentMode == vk::PresentModeKHR::eImmediate)
            return presentMode;
    }

    return vk::PresentModeKHR::eFifo;
}

FrameData& VulkanGPU::getCurrentFrame() const {
    return frameData[frameNumber % bufferedFrames];
}

void VulkanGPU::addValidationLayer(const char* layer) {
#ifdef _DEBUG
    CORE_TRACE("Adding validation layer: {}", layer);
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
    CORE_TRACE("Cleaning up the Vulkan Renderer");

    destroyGpuMemory();

    device.destroyDescriptorSetLayout(drawImageDescriptorSetLayout);
    globalDescriptorAllocator.destroyPool();

    device.destroyImageView(drawImage.view);
    vmaDestroyImage(allocator, drawImage.image, drawImage.allocation);

    destroySwapchain();

    instance.destroySurfaceKHR(surface);

    allocator.destroy();

    device.destroy();

#ifdef _DEBUG
    destroyDebugMessenger();
#endif

    instance.destroy();

    SDL_Vulkan_UnloadLibrary();
}
