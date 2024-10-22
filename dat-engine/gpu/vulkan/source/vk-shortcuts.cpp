#include "../vk-shortcuts.h"

void DatEngine::DatGPU::DatVk::Shortcuts::transitionImage(const vk::CommandBuffer cmd, const vk::Image image, const vk::ImageLayout currentLayout,
                     const vk::ImageLayout newLayout, const vk::PipelineStageFlags2 srcStage,
                     const vk::PipelineStageFlags2 dstStage, const vk::AccessFlags2 srcAccessMask,
                     const vk::AccessFlags2 dstAccessMask) {
    vk::ImageMemoryBarrier2 imageBarrier(
            srcStage, srcAccessMask, dstStage, dstAccessMask, currentLayout, newLayout, {}, {}, image,
            vk::ImageSubresourceRange(newLayout == vk::ImageLayout::eDepthAttachmentOptimal
                                              ? vk::ImageAspectFlagBits::eDepth
                                              : vk::ImageAspectFlagBits::eColor,
                                      0, vk::RemainingMipLevels, 0, vk::RemainingArrayLayers));

    cmd.pipelineBarrier2(vk::DependencyInfo().setImageMemoryBarrierCount(1).setImageMemoryBarriers(imageBarrier));
}
