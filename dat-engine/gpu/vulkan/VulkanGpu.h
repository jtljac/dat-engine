#pragma once


#include "VkStub.h"

#include "../IGpu.h"

#include "FrameData.h"
#include "VkTypes.h"

#include <unordered_map>

namespace DatEngine::DatGpu::DatVk {
    class VulkanGPU : public IGpu {
    protected:
        /** Handle for Vulkan Instance */
        vk::Instance instance = VK_NULL_HANDLE;
        /** Handle for Physical GPU Device */
        vk::PhysicalDevice physicalDevice = VK_NULL_HANDLE;
        /** Handle for Logical GPU Device */
        vk::Device device = VK_NULL_HANDLE;
        /** Handle for Debug Messenger */
        vk::DebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

        // Queues
        /** Index of queue used for graphics operations */
        uint32_t graphicsQueueIndex = UINT32_MAX;
        /** Queue used for graphics operations */
        vk::Queue graphicsQueue;

        /** Whether the transfer queue is unified with the graphics queue */
        bool unifiedTransferQueue = false;
        /** Index for queue used for transfer operations */
        uint32_t transferQueueIndex = UINT32_MAX;
        /** Queue used for transfer operations */
        vk::Queue transferQueue;

        // Memory Management
        /** Handle for vulkan memory allocator */
        vma::Allocator allocator;

        // Surface
        /** Handle to Surface used for rendering */
        vk::SurfaceKHR surface = VK_NULL_HANDLE;

        // Swapchain
        /** Handle for swapchain used for rendering */
        vk::SwapchainKHR swapchain = VK_NULL_HANDLE;
        /** Format of the swapchain images */
        vk::Format swapchainFormat = vk::Format::eUndefined;
        /** Size of the swapchain images (Might not match user set window size) */
        vk::Extent2D swapchainExtent;

        // Frame
        /** Number of frames to buffer */
        int bufferedFrames = 0;
        /** The current frame the renderer is on */
        int frameNumber = 0;
        /** Number of images in the swapchain (Might not match user set buffered frames) */
        size_t swapchainImageCount = 0;

        /** Array of swapchain images and image views */
        SwapchainData* swapchainData = nullptr;
        /** Array of per frame data */
        FrameData* frameData = nullptr;

        // G-Buffers
        AllocatedImage drawImage;
        vk::Extent2D drawImageExtent = {};

        DescriptorAllocator globalDescriptorAllocator;

        vk::DescriptorSet drawImageDescriptorSet;
        vk::DescriptorSetLayout drawImageDescriptorSetLayout;

        // Pipelines
        vk::Pipeline gradientPipeline;
        vk::PipelineLayout gradientPipelineLayout;

        // Validation Layers
#ifdef _DEBUG
        /**
         * Vector of validation layers to load
         */
        std::vector<const char*> validationLayers{"VK_LAYER_KHRONOS_validation"};
#endif

        /* -------------------------------------------- */
        /* Initialisation                               */
        /* -------------------------------------------- */

        /**
         * Set up the Vulkan Instance wit the requested instance extensions and validation layers, and configures the
         * dynamic dispatcher
         */
        void initialiseInstance();

        /**
         * Set up the debug messenger and register it with the logger
         */
        void setupDebugMessenger();

        /**
         * Select and initialise a physical device for vulkan to use
         */
        void initialisePhysicalDevice();

        /**
         * Create a logical device with the required device extensions, and selects and initialises queues
         */
        void initialiseDevice();

        /**
         * Set up Vulkan Memory Manager
         */
        void initialiseVma();

        /**
         * Set up the surface used for rendering to
         *
         * Gets the surface from SDL
         */
        void initialiseSurface();

        /**
         * Fetches a swapchain from the driver, selecting the best surface format available from the device, and
         * fetching atleast as many swapchain images as there are buffered frames (The driver may return more).
         */
        void initialiseSwapchain();

        /**
         * Sets up the swapchain images and image views for rendering to
         */
        void initialiseSwapchainData();

        /**
         * Set up the structures required by each buffered frame
         */
        void initialiseFrameData();
        /**
         * Sets up the command pools and command buffers for the given FrameData
         *
         * @param frameData The frame data to populate
         */
        void initialiseFrameCommandStructure(FrameData& frameData) const;

        /**
         * Sets up the semaphores and fences for the given FrameData
         *
         * @param frameData The frame data to populate
         */
        void initialiseFrameSyncStructure(FrameData& frameData) const;

        /**
         * Initialise the supporting frame buffers for each frame
         *
         * Allocates each GBuffer image and image view,
         *
         */
        void initialiseGBuffers();

        /**
         * Initialised the global descriptors
         */
        void initialiseDescriptors();

        /**
         * Initialise the global pipelines
         */
        void initialisePipelines();

        /**
         * Set up the pipeline used for drawing the background
         */
        void initialiseBackgroundPipelines();

        /* -------------------------------------------- */
        /* Draw                                         */
        /* -------------------------------------------- */

        void drawBackground(vk::CommandBuffer cmd);

        /* -------------------------------------------- */
        /* Cleanup                                      */
        /* -------------------------------------------- */

        /**
         * Destroy the vulkan object handling the Debug Messenger
         */
        void destroyDebugMessenger();

        /**
         * Destroy the swapchain and it's images
         */
        void destroySwapchain();

        /**
         * Destroy all the memory currently used by the GPU
         */
        void destroyGpuMemory();


        /* -------------------------------------------- */
        /* Utils                                        */
        /* -------------------------------------------- */

        /**
         * Validation layer message callback method
         *
         * @param messageSeverity The severity tag attached to the message
         * @param messageType The type tag attached to the message
         * @param pCallbackData Data for the message
         * @param pUserData A pointer of user data for misc usage (Unused)
         *
         * @return Indicates if the vulkan call should be aborted (Always @code false@endcode)
         */
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                vk::DebugUtilsMessageTypeFlagsEXT messageType,
                const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData
        );

        /**
         * Select queues to be used by the GPU
         *
         * @return A map of queue family indices to number of queues to reserve
         */
        [[nodiscard]] std::unordered_map<uint32_t, uint32_t> selectQueues();

        /**
         * Get the best queue available for the given required queue flags.
         *
         * This tries to select the queue that has all the required flags, and the least number of flags, I.e the most
         * specific queue.
         *
         * @param requiredFlags The flags required for the queue
         * @param usedQueues Queues families that have already been selected (Multiples of a queue family index
         *                   represent multiple usages of that queue family and shouldn't exceed the queue family's
         *                   queue count).
         * @return The best available queue index for the requirements, or @code -1@endcode if no available queues fit
         *         the requirements
         */
        [[nodiscard]]
        int32_t getBestQueue(vk::Flags<vk::QueueFlagBits> requiredFlags, std::vector<uint32_t>& usedQueues) const;

        /**
         * Check if the selected validation layers are supported by the system
         *
         * @return @code true@endcode if the chosen validation layers are supported
         */
        [[nodiscard]] bool checkValidationLayerSupport() const;


        /**
         * Get the best available swapchain format for the device
         *
         * @return The best available swapchain format
         */
        [[nodiscard]] vk::SurfaceFormatKHR getBestSwapchainFormat() const;

        /**
         * Get the window extent for the current surface
         *
         * This will usually be the size of the window, the value is constrained
         *
         * @param surfaceCapabilities The capabilities of the surface
         * @return The window extent for the application window
         */
        [[nodiscard]] static vk::Extent2D getWindowExtent(const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);

        /**
         * Get the best present mode available on the device/surface that conforms to the user's selected VSync
         options
         *
         * VSync is controlled using the CVar @code BEnableVsync@endcode
         *
         * Will typically return vk::PresentModeKHR::eFifoRelaxed for vsync on and vk::PresentModeKHR::eImmediate
         when
         * vsync is off. Falling back to vk::PresentModeKHR::eFifo if the preferred option is unavailable (Fifo is
         * guaranteed).
         *
         * @return The best present mode available
         */
        [[nodiscard]] vk::PresentModeKHR getIdealPresentMode() const;

        /**
         * Get the current framedata being used for rendering
         *
         * @return The current framedata being used for rendering
         */
        [[nodiscard]] FrameData& getCurrentFrame() const;

    public:
        int getWindowFlags() override;
        void initialise() override;
        void draw() override;
        void cleanup() override;

        // Utils
        /**
         * When compiled in debug mode, add a validation layer to load when initialising vulkan
         *
         * @param layer The validation layer to enable
         */
        void addValidationLayer(const char* layer);
    };
} // namespace DatEngine::DatGpu::DatVk
