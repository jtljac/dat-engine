#include "../vk-shortcuts.h"

#include <util/logger.h>
#include <vulkan/vulkan_to_string.hpp>
#include <vk_mem_alloc.h>

vk::ImageCreateInfo DatEngine::DatGPU::DatVk::Shortcuts::getImageCreateInfo(
        const vk::Format format,
        const vk::ImageUsageFlags usageFlags,
        const vk::Extent3D extent,
        const vk::ImageTiling tiling
) {
    return vk::ImageCreateInfo {
            {},
            vk::ImageType::e2D,
            format,
            extent,
            1,
            1,
            vk::SampleCountFlagBits::e1,
            tiling,
            usageFlags
    };
}
vk::ImageViewCreateInfo DatEngine::DatGPU::DatVk::Shortcuts::getImageViewCreateInfo(
        const vk::Format format,
        const vk::Image image,
        const vk::ImageAspectFlags aspectFlags
) {
    return {
        {},
        image,
        vk::ImageViewType::e2D,
        format,
        {},
        {
            aspectFlags,
            0,
            1,
            0,
            1
        }
    };
}

void DatEngine::DatGPU::DatVk::Shortcuts::transitionImage(
        const vk::CommandBuffer cmd,
        const vk::Image image,
        const vk::ImageLayout currentLayout,
        const vk::ImageLayout newLayout,
        const vk::PipelineStageFlags2 srcStage,
        const vk::PipelineStageFlags2 dstStage,
        const vk::AccessFlags2 srcAccessMask,
        const vk::AccessFlags2 dstAccessMask
) {
    vk::ImageMemoryBarrier2 imageBarrier(
            srcStage,
            srcAccessMask,
            dstStage,
            dstAccessMask,
            currentLayout,
            newLayout,
            {},
            {},
            image,
            vk::ImageSubresourceRange(
                    newLayout == vk::ImageLayout::eDepthAttachmentOptimal ? vk::ImageAspectFlagBits::eDepth
                                                                          : vk::ImageAspectFlagBits::eColor,
                    0,
                    vk::RemainingMipLevels,
                    0,
                    vk::RemainingArrayLayers
            )
    );

    cmd.pipelineBarrier2(vk::DependencyInfo().setImageMemoryBarrierCount(1).setImageMemoryBarriers(imageBarrier));
}

void DatEngine::DatGPU::DatVk::Shortcuts::copyImageToImage(
        const vk::CommandBuffer cmd,
        const vk::Image srcImage,
        const vk::Image dstImage,
        const vk::Extent2D srcSize,
        const vk::Extent2D dstSize,
        const vk::ImageAspectFlags aspectMask,
        const vk::ImageLayout srcLayout,
        const vk::ImageLayout dstLayout
) {
    const vk::ImageBlit2 blit(
            vk::ImageSubresourceLayers(aspectMask, 0, 0, 1),
            {{{}, {static_cast<int32_t>(srcSize.width), static_cast<int32_t>(srcSize.height), 1}}},
            vk::ImageSubresourceLayers(aspectMask, 0, 0, 1),
            {{{}, {static_cast<int32_t>(dstSize.width), static_cast<int32_t>(dstSize.height), 1}}}
    );

    const vk::BlitImageInfo2 blitInfo(srcImage, srcLayout, dstImage, dstLayout, 1, &blit, vk::Filter::eLinear);

    cmd.blitImage2(blitInfo);
}

/* -------------------------------------------- */
/* DescriptorLayoutBuilder                      */
/* -------------------------------------------- */

void DatEngine::DatGPU::DatVk::Shortcuts::DescriptorLayoutBuilder::addBinding(
        uint32_t binding, vk::DescriptorType type
) {
    bindings.push_back({binding, type, 1});
}

void DatEngine::DatGPU::DatVk::Shortcuts::DescriptorLayoutBuilder::clear() { bindings.clear(); }

vk::DescriptorSetLayout DatEngine::DatGPU::DatVk::Shortcuts::DescriptorLayoutBuilder::build(
        const vk::Device device, const vk::ShaderStageFlagBits stage, const void* pNext, const vk::DescriptorSetLayoutCreateFlagBits flags) {
    for (auto& binding : bindings) {
        binding.stageFlags |= stage;
    }

    return device.createDescriptorSetLayout({
        flags,
        bindings,
        pNext
    });
}


