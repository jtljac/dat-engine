#pragma once

#include <vulkan/vulkan.hpp>

namespace DatEngine::DatGPU::DatVk::Shortcuts {

/* -------------------------------------------- */
/* Image                                        */
/* -------------------------------------------- */

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
void transitionImage(vk::CommandBuffer cmd,
                         vk::Image image,
                         vk::ImageLayout currentLayout,
                         vk::ImageLayout newLayout,
                         vk::PipelineStageFlags2 srcStage = vk::PipelineStageFlagBits2::eAllCommands,
                         vk::PipelineStageFlags2 dstStage = vk::PipelineStageFlagBits2::eAllCommands,
                         vk::AccessFlags2 srcAccessMask = vk::AccessFlagBits2::eMemoryWrite,
                         vk::AccessFlags2 dstAccessMask = vk::AccessFlagBits2::eMemoryWrite | vk::AccessFlagBits2::eMemoryRead);

}