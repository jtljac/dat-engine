#pragma once

namespace vk {
    class Image;
    class ImageView;
}

namespace DatEngine::DatGPU::DatVk {
    struct SwapchainData {
        vk::Image image;
        vk::ImageView imageView;
    };
}