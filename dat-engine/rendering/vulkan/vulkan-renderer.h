//
// Created by jacob on 10/07/23.
//

#pragma once


#include "rendering/irenderer.h"

#define VULKAN_HPP_NO_EXCEPTIONS
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include <vk_mem_alloc.h>
#include <vulkan/vulkan.hpp>

#include "util/logger.h"

namespace DatEngine {
    class VulkanRenderer : public IRenderer {
    protected:
        // Vulkan Instance
        vk::Instance instance;
        vk::PhysicalDevice physicalDevice;
        vk::Device device;
        vk::DebugUtilsMessengerEXT debugMessenger;

        // Memory Management
        VmaAllocator allocator = VK_NULL_HANDLE;

        // Surface
        vk::SurfaceKHR surface;

        // Swapchain
        VkSwapchainKHR swapchain;
        VkFormat swapchainFormat;

        std::vector<VkImage> swapchainImages;
        std::vector<VkImageView> swapchainImageViews;
        VkExtent2D swapchainExtent;

        // Validation Layers
#ifdef _DEBUG
        std::vector<const char*> validationLayers {
            "VK_LAYER_KHRONOS_validation"
        };
#endif

        /**
         * Set up the Vulkan Instance
         * @return true if successful
         */
        bool initialiseInstance();

        bool setupDebugMessenger();

        /**
         * Select a physical device for vulkan to use
         * @return true if successful
         */
        bool initialisePhysicalDevice();

        /**
         * Create a logical device
         * @return true if successful
         */
        bool initialiseDevice();

        /**
         * Setup Vulkan Memory Manager
         * @return true if successful
         */
        bool initialiseVma();

        // Surface
        // Swapchain
        // Swapchain Images
        // Framedata
        //

        // Cleanup
        void destroyDebugMessenger();

        // Utils
        bool checkValidationLayersSupport() const;
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                            VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                            void* pUserData);

    public:
        int getWindowFlags() override;
        bool initialise() override;
        void cleanup() override;

        void addValidationLayer(const char* layer);
    };
}