#include "VulkanGpu.h"

#include <SDL3/SDL_vulkan.h>

#include "VkStub.h"
#include <vulkan/vulkan_to_string.hpp>


#include <gpu/exception/GpuInitException.h>
#include <util/Logger.h>

#include "DatEngine.h"
#include "VkShortcuts.h"
#include "util/CVar.h"

VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

extern DatEngine::CVarInt bufferedFramesCVar;

using namespace DatEngine::DatGpu::DatVk;

/* -------------------------------------------- */
/* Initialisation                               */
/* -------------------------------------------- */

void VulkanGPU::initialise() {
    CORE_TRACE("Initialising Vulkan Renderer");
    initialiseInstance();

#ifdef _DEBUG
    setupDebugMessenger();
#endif

    initialisePhysicalDevice();

    initialiseDevice();
    initialiseVma();
    initialiseSurface();
    initialiseSwapchain();
    initialiseSwapchainImages();
    initialiseFrameData();
    initialiseGBuffers();

    CORE_INFO("Vulkan Renderer Initialised");
}

/* -------------------------------------------- */

void VulkanGPU::initialiseInstance() {
    CORE_TRACE("Creating VK Instance");

    constexpr vk::ApplicationInfo applicationInfo(
            "Test-App", // TODO: Allow custom names
            vk::makeApiVersion(0, 1, 0, 0),
            "Dat Engine",
            vk::makeApiVersion(0, 1, 0, 0),
            vk::ApiVersion13
    );

    SDL_Vulkan_LoadLibrary(nullptr);
    VULKAN_HPP_DEFAULT_DISPATCHER.init();

    uint32_t sdlInstanceExtensionsCount;
    const char* const* sdlInstanceExtensions = SDL_Vulkan_GetInstanceExtensions(&sdlInstanceExtensionsCount);

    if (sdlInstanceExtensions == nullptr) {
        throw GpuInitException("Failed to get required instance extensions.");
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

    this->instance = vk::createInstance(instanceInfo);

    VULKAN_HPP_DEFAULT_DISPATCHER.init(instance);
}

/* -------------------------------------------- */

void VulkanGPU::setupDebugMessenger() {
    debugMessenger = instance.createDebugUtilsMessengerEXT(
            vk::DebugUtilsMessengerCreateInfoEXT(
                    {},
                    vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
                            | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
                            | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
                    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
                            | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
                    debugCallback
            )
    );
}

/* -------------------------------------------- */

void VulkanGPU::initialisePhysicalDevice() {
    CORE_TRACE("Creating VK Physical Device");

    const std::vector<vk::PhysicalDevice> physicalDevices = instance.enumeratePhysicalDevices();

    if (physicalDevices.empty()) {
        throw GpuInitException("Vulkan failed to find any GPUs");
    }

    // TODO: Some selection process
    this->physicalDevice = physicalDevices[0];
}

/* -------------------------------------------- */

void VulkanGPU::initialiseDevice() {
    CORE_TRACE("Creating VK Logical Device");

    std::unordered_map<uint32_t, uint32_t> queues = selectQueues();

    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    queueCreateInfos.reserve(queues.size());

    // The max this array can be is 3 elements if all the queues are the same queue family (Graphics, Compute, Transfer)
    // All queues will use the same array as we don't care about priority, but it's a required parameter
    float queuePriorities[3] = {1.f, 1.f, 1.f};

    for (auto [fst, snd]: queues) {
        queueCreateInfos.push_back(vk::DeviceQueueCreateInfo({}, fst, snd, queuePriorities));
    }

#ifdef _DEBUG
    if (!checkValidationLayerSupport()) {
        throw GpuInitException("Vulkan is missing required validation layers.");
    }
#endif

    std::vector deviceExtensions{vk::KHRSwapchainExtensionName};

    vk::PhysicalDeviceShaderDrawParametersFeatures shaderDrawParameters(true);

    vk::PhysicalDeviceVulkan12Features features2;
    features2.setBufferDeviceAddress(true).setDescriptorIndexing(true).setPNext(&shaderDrawParameters);

    vk::PhysicalDeviceVulkan13Features features3;
    features3.setDynamicRendering(true).setSynchronization2(true).setPNext(&features2);

    this->device = physicalDevice.createDevice(
            vk::DeviceCreateInfo({}, queueCreateInfos, nullptr, deviceExtensions, nullptr, &features3)
    );

    // Get queues
    if (!unifiedTransferQueue)
        device.getQueue(transferQueueIndex, --queues[transferQueueIndex], &transferQueue);

    device.getQueue(graphicsQueueIndex, --queues[graphicsQueueIndex], &graphicsQueue);

    if (unifiedTransferQueue)
        transferQueue = graphicsQueue;
}

/* -------------------------------------------- */

void VulkanGPU::initialiseVma() {
    CORE_TRACE("Initialising VMA");

    vma::VulkanFunctions vulkanFunctions;
    vulkanFunctions.vkGetInstanceProcAddr = VULKAN_HPP_DEFAULT_DISPATCHER.vkGetInstanceProcAddr;
    vulkanFunctions.vkGetDeviceProcAddr = VULKAN_HPP_DEFAULT_DISPATCHER.vkGetDeviceProcAddr;

    allocator = createAllocator(
            vma::AllocatorCreateInfo({}, physicalDevice, device)
                    .setInstance(instance)
                    .setVulkanApiVersion(vk::ApiVersion13)
                    .setPVulkanFunctions(&vulkanFunctions)
    );
}

/* -------------------------------------------- */

void VulkanGPU::initialiseSurface() {
    CORE_TRACE("Creating Surface");
    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(Engine::getInstance()->getWindow(), instance, nullptr, &surface)) {
        throw GpuInitException("Failed to create surface with SDL.");
    };

    this->surface = surface;
}

/* -------------------------------------------- */

void VulkanGPU::initialiseSwapchain() {
    CORE_TRACE("Initialising Swapchain");
    bufferedFrames = bufferedFramesCVar.get();

    const vk::SurfaceCapabilitiesKHR surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);

    const vk::SurfaceFormatKHR format = getBestSwapchainFormat();

    swapchainExtent = getWindowExtent(surfaceCapabilities);
    swapchainFormat = format.format;

    const uint32_t bufferedImages = DatMaths::clamp<uint32_t>(
            bufferedFrames,
            surfaceCapabilities.minImageCount,
            surfaceCapabilities.maxImageCount == 0 ? INT_MAX : surfaceCapabilities.maxImageCount
    );

    const vk::SwapchainCreateInfoKHR swapchainInfo =
            vk::SwapchainCreateInfoKHR()
                    .setSurface(surface)
                    .setMinImageCount(bufferedImages)
                    .setImageFormat(swapchainFormat)
                    .setImageColorSpace(format.colorSpace)
                    .setImageExtent(swapchainExtent)
                    .setImageArrayLayers(1)
                    .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eTransferDst)
                    .setPresentMode(getIdealPresentMode());

    swapchain = device.createSwapchainKHR(swapchainInfo);
}

/* -------------------------------------------- */

void VulkanGPU::initialiseSwapchainImages() {
    CORE_TRACE("Initialising Swapchain Images");
    const std::vector<vk::Image> swapchainImages = device.getSwapchainImagesKHR(swapchain);

    swapchainImageCount = swapchainImages.size();
    swapchainData = new SwapchainData[swapchainImageCount];

    for (int i = 0; i < swapchainImageCount; i++) {
        auto& [image, imageView, swapchainImage] = swapchainData[i];

        image = swapchainImages[i];

        vk::ImageViewCreateInfo swapchainImageViewCreateInfo =
                vk::ImageViewCreateInfo()
                        .setImage(image)
                        .setViewType(vk::ImageViewType::e2D)
                        .setFormat(swapchainFormat)
                        .setComponents({})
                        .setSubresourceRange({vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1});

        imageView = device.createImageView(swapchainImageViewCreateInfo);

        swapchainImage = device.createSemaphore({});
    }
}

/* -------------------------------------------- */

void VulkanGPU::initialiseFrameData() {
    CORE_TRACE("Initialising Frame Data");

    frameData = new FrameData[bufferedFrames];
    for (int i = 0; i < bufferedFrames; i++) {
        initialiseFrameCommandStructure(frameData[i]);
        initialiseFrameSyncStructure(frameData[i]);
    }
}

/* -------------------------------------------- */

void VulkanGPU::initialiseFrameCommandStructure(FrameData& frameData) const {
    const vk::CommandPoolCreateInfo commandPoolCreateInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
                                                          graphicsQueueIndex);
    frameData.commandPool = device.createCommandPool(commandPoolCreateInfo);

    const vk::CommandBufferAllocateInfo commandAllocCreateInfo(frameData.commandPool, vk::CommandBufferLevel::ePrimary,
                                                               1);
    const std::vector<vk::CommandBuffer> bufferList = device.allocateCommandBuffers(commandAllocCreateInfo);
    frameData.commandBuffer = bufferList[0];
}

/* -------------------------------------------- */

void VulkanGPU::initialiseFrameSyncStructure(FrameData& frameData) const {
    frameData.renderFence = device.createFence(vk::FenceCreateInfo(vk::FenceCreateFlagBits::eSignaled));
    frameData.swapchainSemaphore = device.createSemaphore({});
}

/* -------------------------------------------- */

void VulkanGPU::initialiseGBuffers() {
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

    vma::AllocationCreateInfo vmaAllocationCreateInfo{
            {},
            vma::MemoryUsage::eGpuOnly,
            vk::MemoryPropertyFlagBits::eDeviceLocal
    };
    std::pair<vk::Image, vma::Allocation> result;
    result = allocator.createImage(drawImageCreateInfo, vmaAllocationCreateInfo);

    drawImage.image = result.first;
    drawImage.allocation = result.second;

    drawImage.view = device.createImageView(
            Shortcuts::getImageViewCreateInfo(drawImage.format, drawImage.image, vk::ImageAspectFlagBits::eColor)
    );
}

/* -------------------------------------------- */
/* Draw                                         */
/* -------------------------------------------- */

void VulkanGPU::draw() {
    auto& [commandPool, commandBuffer, renderFence, swapchainSemaphore] = getCurrentFrame();

    VK_QUICK_FAIL(device.waitForFences(1, &renderFence, true, 1000000000));
    VK_QUICK_FAIL(device.resetFences(1, &renderFence));

    uint32_t swapchainImageIndex;
    VK_QUICK_FAIL(device.acquireNextImageKHR(swapchain, 1000000000, swapchainSemaphore, nullptr, &swapchainImageIndex));

    auto& [swapchainImage, swapchainImageView, renderSemaphore] = swapchainData[swapchainImageIndex];

    commandBuffer.reset();

    commandBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit));

    Shortcuts::transitionImage(commandBuffer, drawImage.image,
                               vk::ImageLayout::eUndefined, vk::ImageLayout::eGeneral,
                               vk::PipelineStageFlagBits2::eTopOfPipe,vk::PipelineStageFlagBits2::eTopOfPipe,
                               vk::AccessFlagBits2::eNone, vk::AccessFlagBits2::eMemoryWrite);

    drawBackground(commandBuffer);

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

    commandBuffer.end();

    vk::SemaphoreSubmitInfo semaphoreWaitInfo(swapchainSemaphore, 1, vk::PipelineStageFlagBits2::eColorAttachmentOutput);
    vk::SemaphoreSubmitInfo semaphoreSignalInfo(renderSemaphore, 1, vk::PipelineStageFlagBits2::eAllGraphics);

    vk::CommandBufferSubmitInfo commandBufferSubmitInfo(commandBuffer);

    vk::SubmitInfo2 submitInfo({}, 1, &semaphoreWaitInfo, 1, &commandBufferSubmitInfo, 1, &semaphoreSignalInfo);
    VK_QUICK_FAIL(graphicsQueue.submit2(1, &submitInfo, renderFence));

    VK_QUICK_FAIL(graphicsQueue.presentKHR(vk::PresentInfoKHR(1, &renderSemaphore, 1, &swapchain, &swapchainImageIndex)));

    ++frameNumber;
}

/* -------------------------------------------- */

void VulkanGPU::drawBackground(vk::CommandBuffer cmd) {
    cmd.clearColorImage(drawImage.image, vk::ImageLayout::eGeneral,
                                      {0.f, 0.f, std::abs(DatMaths::sin(frameNumber / 120.f)), 0.f},
                                      vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor,
                                          0, vk::RemainingMipLevels,
                                          0, vk::RemainingArrayLayers));
}

/* -------------------------------------------- */
/* Cleanup                                      */
/* -------------------------------------------- */

void VulkanGPU::cleanup() {
    CORE_TRACE("Cleaning up the Vulkan Renderer");

    device.waitIdle();

    destroyGpuMemory();

    device.destroyImageView(drawImage.view);
    allocator.destroyImage(drawImage.image, drawImage.allocation);

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

/* -------------------------------------------- */

void VulkanGPU::destroyDebugMessenger() {
    instance.destroyDebugUtilsMessengerEXT(debugMessenger);
    debugMessenger = nullptr;
}

/* -------------------------------------------- */

void VulkanGPU::destroySwapchain() {
    CORE_TRACE("Destroying the Swapchain");
    device.destroySwapchainKHR(swapchain);

    for (int i = 0; i < swapchainImageCount; i++) {
        device.destroyImageView(swapchainData[i].imageView);
        device.destroySemaphore(swapchainData[i].renderSemaphore);
    }
    delete[] swapchainData;

    for (int i = 0; i < bufferedFrames; i++) {
        auto& [commandPool, _, renderFence, swapchainSemaphore] = frameData[i];
        device.destroyCommandPool(commandPool);

        device.destroySemaphore(swapchainSemaphore);
        device.destroyFence(renderFence);
    }
    delete[] frameData;

    swapchainData = nullptr;
    swapchainImageCount = 0;
}

/* -------------------------------------------- */

void VulkanGPU::destroyGpuMemory() {}

/* -------------------------------------------- */
/* Util                                         */
/* -------------------------------------------- */

VkBool32 VulkanGPU::debugCallback(
        const vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        const vk::DebugUtilsMessageTypeFlagsEXT messageType,
        const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
) {
    std::string type;

    if (messageType == vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral) {
        type = "General";
    } else if (messageType == vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation) {
        type = "Validation";
    } else if (messageType == vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance) {
        type = "Performance";
    }

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

    return false;
}

/* -------------------------------------------- */

std::unordered_map<uint32_t, uint32_t> VulkanGPU::selectQueues() {
    std::unordered_map<uint32_t, uint32_t> queues;
    std::vector<uint32_t> usedQueues;

    // Select graphics queue
    graphicsQueueIndex = getBestQueue(vk::QueueFlagBits::eGraphics, usedQueues);
    usedQueues.push_back(graphicsQueueIndex);
    queues[graphicsQueueIndex] = 1;

    // Check to see if we've anything like a dedicated transfer queue
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

/* -------------------------------------------- */

int32_t VulkanGPU::getBestQueue(vk::Flags<vk::QueueFlagBits> requiredFlags, std::vector<uint32_t>& usedQueues) const {
    auto queueFamilies = physicalDevice.getQueueFamilyProperties();
    std::vector<uint32_t> queueOptions;

    for (uint32_t i = 0; i < queueFamilies.size(); i++) {
        const vk::QueueFamilyProperties& queueFamily = queueFamilies[i];
        const int usages = std::ranges::count_if(usedQueues, [i](const uint32_t queue) { return queue == i; });

        if (requiredFlags & queueFamily.queueFlags && usages < queueFamily.queueCount) {
            queueOptions.push_back(i);
        }
    }

    if (queueOptions.empty())
        return -1;

    // Sort by least flags to get the most specific queue
    std::ranges::sort(queueOptions, std::ranges::less(), [&queueFamilies](const uint32_t queue) {
        return std::popcount(static_cast<uint32_t>(queueFamilies[queue].queueFlags));
    });

    const uint32_t selectedQueue = queueOptions.front();
    return selectedQueue;
}

/* -------------------------------------------- */

bool VulkanGPU::checkValidationLayerSupport() const {
    std::vector<vk::LayerProperties> layerProperties = vk::enumerateInstanceLayerProperties();

    bool layerMissed = false;
    for (auto validationLayer: validationLayers) {
        if (std::ranges::find_if(
                    layerProperties,
                    [&validationLayer](const vk::LayerProperties& layer) {
                        return strcmp(layer.layerName, validationLayer);
                    }
            )
            == layerProperties.end()) {
            CORE_CRITICAL("Failed to find validation layer: {}", validationLayer);
            layerMissed = true;
        }
    }

    return !layerMissed;
}

/* -------------------------------------------- */

vk::SurfaceFormatKHR VulkanGPU::getBestSwapchainFormat() const {
    const auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);

    for (const auto surfaceFormat: surfaceFormats) {
        if (surfaceFormat.format == vk::Format::eB8G8R8Srgb
            && surfaceFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return surfaceFormat;
        }
    }

    return surfaceFormats[0];
}

/* -------------------------------------------- */

vk::Extent2D VulkanGPU::getWindowExtent(const vk::SurfaceCapabilitiesKHR& surfaceCapabilities) {
    if (surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return surfaceCapabilities.currentExtent;
    }

    // If the current extent has the special value (0xFFFFFFFF, 0xFFFFFFFF), the surface size will be determined by the
    // extent of a swapchain targeting the surface so we gotta check that instead
    int width, height;
    SDL_GetWindowSize(Engine::getInstance()->getWindow(), &width, &height);

    return {DatMaths::clamp<uint32_t>(
                    width,
                    surfaceCapabilities.minImageExtent.width,
                    surfaceCapabilities.maxImageExtent.width
            ),
            DatMaths::clamp<uint32_t>(
                    height,
                    surfaceCapabilities.minImageExtent.height,
                    surfaceCapabilities.maxImageExtent.height
            )};
}

/* -------------------------------------------- */

vk::PresentModeKHR VulkanGPU::getIdealPresentMode() const {
    const bool enableVsync = CVarSystem::get()->getBoolCVar("BEnableVsync");
    const auto availablePresentModes = physicalDevice.getSurfacePresentModesKHR(surface);

    for (const auto presentMode: availablePresentModes) {
        if (enableVsync ? presentMode == vk::PresentModeKHR::eFifoRelaxed
                        : presentMode == vk::PresentModeKHR::eImmediate)
            return presentMode;
    }

    return vk::PresentModeKHR::eFifo;
}

/* -------------------------------------------- */

FrameData& VulkanGPU::getCurrentFrame() const {
    return frameData[frameNumber % bufferedFrames];
}

/* -------------------------------------------- */

int VulkanGPU::getWindowFlags() {
    return SDL_WINDOW_VULKAN;
}

/* -------------------------------------------- */

void VulkanGPU::addValidationLayer(const char* layer) {
#ifdef _DEBUG
    CORE_TRACE("Adding validation layer: {}", layer);
    validationLayers.push_back(layer);
#endif
}
