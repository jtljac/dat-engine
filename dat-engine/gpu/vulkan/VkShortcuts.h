#pragma once

#include <filesystem>
#include <vector>

#include "VkStub.h"

#include <util/Macros.h>

/**
 * Checks the result of a vulkan method that returns a vk::ResultValueType, setting @code varDecl@endcode to the value
 * on success and throwing DatGpuInitException on failure
 *
 * @param varDecl The variable declaration to store the default in, this can be defining a new variable
 *                (@code const auto surfaceVar@endcode) or storing in an existing one.
 * @param x The vulkan method that returns a vk::ResultValueType
 */
#define VK_INIT_CHECK(varDecl, x)                                                                                      \
    const auto CAT(wrappedResult, __LINE__) = x;                                                                       \
    if (CAT(wrappedResult, __LINE__).result != vk::Result::eSuccess) {                                                 \
        throw GpuInitException(                                                                                        \
                "Vulkan error occured on line \"" STRINGIFY(__LINE__) "\": {}",                                        \
                vk::to_string(CAT(wrappedResult, __LINE__).result)                                                     \
        );                                                                                                             \
    }                                                                                                                  \
    varDecl = CAT(wrappedResult, __LINE__).value;

/**
 * Checks the result of a vulkan method that returns a vk::ResultValueType, setting @code varDecl@endcode to the value
 * on success and quitting the program on fail
 *
 * This macro specifically requires that the function it is contained within returns a @code bool@endcode
 *
 * @param varDecl The variable declaration to store the default in, this can be defining a new variable
 *                (@code const auto surfaceVar@endcode) or storing in an existing one.
 * @param x The vulkan method that returns a vk::ResultValueType
 */
#define VK_QUICK_FAIL(x)                                                                                               \
    const auto CAT(result, __LINE__) = x;                                                                              \
    if (CAT(result, __LINE__) != vk::Result::eSuccess) {                                                               \
        CORE_CRITICAL(                                                                                                 \
                "Vulkan error occured on line \"" STRINGIFY(__LINE__) "\": {}",                                        \
                vk::to_string(CAT(result, __LINE__))                                                                   \
        );                                                                                                             \
        abort();                                                                                                       \
    }

namespace DatEngine::DatGpu::DatVk::Shortcuts {

    /* -------------------------------------------- */
    /* Image                                        */
    /* -------------------------------------------- */

    /**
     * Get a template pre-configured vk::ImageCreateInfo
     *
     * @param format The format of the image
     * @param usageFlags The usage flags for the image
     * @param extent The extent of the Image
     * @param tiling The tiling mode for the image on the GPU
     * @return A pre-configured vk::ImageCreateInfo
     */
    vk::ImageCreateInfo getImageCreateInfo(
            vk::Format format,
            vk::ImageUsageFlags usageFlags,
            vk::Extent3D extent,
            vk::ImageTiling tiling = vk::ImageTiling::eOptimal
    );

    /**
     * Get a template pre-configured vk::ImageViewCreateInfo
     *
     * @param format The format of the image
     * @param image The image the ImageView belongs to
     * @param aspectFlags A Bitmask specifying which aspects are included in the ImageView
     * @return A pre-configured vk::ImageViewCreateInfo
     */
    vk::ImageViewCreateInfo
    getImageViewCreateInfo(vk::Format format, vk::Image image, vk::ImageAspectFlags aspectFlags);

    /**
     * Transition an image from the @code currentLayout@endcode to the @code newLayout@endcode
     *
     * @param cmd The command buffer the transition will execute on
     * @param image The image that will be transitioned
     * @param currentLayout The current layout of the image
     * @param newLayout The layout to transition the image to
     * @param srcStage The stage the image should wait for
     * @param dstStage The stage the image should transition on
     * @param srcAccessMask The access mask for memory before the transition
     * @param dstAccessMask The access mask for memory during the transition
     */
    void transitionImage(
            vk::CommandBuffer cmd,
            vk::Image image,
            vk::ImageLayout currentLayout,
            vk::ImageLayout newLayout,
            vk::PipelineStageFlags2 srcStage = vk::PipelineStageFlagBits2::eAllCommands,
            vk::PipelineStageFlags2 dstStage = vk::PipelineStageFlagBits2::eAllCommands,
            vk::AccessFlags2 srcAccessMask = vk::AccessFlagBits2::eMemoryWrite,
            vk::AccessFlags2 dstAccessMask = vk::AccessFlagBits2::eMemoryWrite | vk::AccessFlagBits2::eMemoryRead
    );

    /**
     * Copy the contents of an image onto another, performing a rescale if necessary
     *
     * @param cmd The command buffer the copy will execute on
     * @param srcImage The image to copy from
     * @param dstImage The image to copy to
     * @param srcSize The size of the image to copy from
     * @param dstSize The size of the image to copy to
     * @param aspectMask The image aspect to copy, defaults to vk::ImageAspectFlagBits::eColor
     * @param srcLayout The current layout of the src image, defaults to vk::ImageLayout::eTransferSrcOptimal
     * @param dstLayout The current layout of the dest image, defaults to vk::ImageLayout::eTransferDstOptimal
     */
    void copyImageToImage(
            vk::CommandBuffer cmd,
            vk::Image srcImage,
            vk::Image dstImage,
            vk::Extent2D srcSize,
            vk::Extent2D dstSize,
            vk::ImageAspectFlags aspectMask = vk::ImageAspectFlagBits::eColor,
            vk::ImageLayout srcLayout = vk::ImageLayout::eTransferSrcOptimal,
            vk::ImageLayout dstLayout = vk::ImageLayout::eTransferDstOptimal
    );

    /* -------------------------------------------- */
    /* Descriptor Sets                              */
    /* -------------------------------------------- */

    /**
     * A builder for creating Descriptor Sets
     */
    struct DescriptorLayoutBuilder {
        /** A list of Descriptor Set Bindings to include in the build */
        std::vector<vk::DescriptorSetLayoutBinding> bindings;

        /**
         * Add a new binding to the descriptor set
         *
         * @param binding The binding in the descriptor set for the binding
         * @param type The type of the binding
         * @return The DescriptorLayoutBuilder for chaining
         */
        DescriptorLayoutBuilder& addBinding(uint32_t binding, vk::DescriptorType type);

        /**
         * Empty the descriptor set Builder
         * @return The DescriptorLayoutBuilder for chaining
         */
        DescriptorLayoutBuilder& clear();

        /**
         * Build the added bindings into a new DescriptorSetLayout
         *
         * @param device The device to own the descriptor set
         * @param stage The stage the descriptor set will be bound to
         * @param pNext nullptr or a pointer to a structure extending the resulting DescriptorSetLayout
         * @param flags Flags for the properties of the DescriptorSetLayout
         * @return A new DescriptorSetLayout built using the added bindings
         */

        vk::DescriptorSetLayout
        build(vk::Device device,
              vk::ShaderStageFlagBits stage,
              const void* pNext = nullptr,
              vk::DescriptorSetLayoutCreateFlagBits flags = static_cast<vk::DescriptorSetLayoutCreateFlagBits>(0));
    };

    /* -------------------------------------------- */
    /* Shader                                       */
    /* -------------------------------------------- */

    /**
     * Create a shader module from spir-v on the filesystem
     *
     * @param device The device to own the shader module
     * @param filePath The path to the shader spirv
     * @return a result that contains the shader module
     */
    std::optional<vk::ShaderModule> loadShaderModule(vk::Device device, std::filesystem::path filePath);

} // namespace DatEngine::DatGpu::DatVk::Shortcuts
