#pragma once

#include <vk_mem_alloc.h>
#include <vulkan-memory-allocator-hpp/vk_mem_alloc.hpp>

namespace DatEngine::DatGPU::DatVk {
    struct AllocatedImage {
        vk::Image image = VK_NULL_HANDLE;
        vk::ImageView view = VK_NULL_HANDLE;
        vma::Allocation allocation = VK_NULL_HANDLE;
        vk::Extent3D extent = {};
        vk::Format format = {};
    };

    /**
     *
     */
    struct DescriptorAllocator {
        /**
         * A helper struct for initialising the pool, representing the ratio of a particular descriptor set type to the
         * maximum number of sets
         */
        struct PoolSizeRatio {
            /** The type of this ratio */
            vk::DescriptorType type;
            /** The ratio (compared to the maximum number of sets) of this type to contain in the pool */
            float ratio;
        };

        /** The device that will own the descriptor pool */
        vk::Device device;

        /** The pool represented by this allocator */
        vk::DescriptorPool pool;

        /**
         * Initialise the Descriptor Pool
         *
         * @param device The device that will own the Descriptor Pool
         * @param maxSets The maximum number of sets to have in this pool
         * @param ratios The ratios of each descriptor type to have in this pool
         */
        void initPool(vk::Device device, uint32_t maxSets, std::span<const PoolSizeRatio> ratios);

        /**
         * Destroy all the descriptors created from this pool
         */
        void clearDescriptors() const;

        /**
         * Destroy this pool
         */
        void destroyPool() const;

        /**
         * Generate a descriptor set with the given layout from the pool
         *
         * @param layout The layout of the set to allocate
         * @return An allocated descriptor set
         */
        VkDescriptorSet allocate(vk::DescriptorSetLayout layout) const;
    };
} // namespace DatEngine::DatGPU::DatVk
