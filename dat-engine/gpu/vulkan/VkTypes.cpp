#include "VkTypes.h"

#include "VkStub.h"

#include <vector>

#include <util/Logger.h>
#include "VkShortcuts.h"

using namespace DatEngine::DatGpu::DatVk;

/* -------------------------------------------- */
/* DescriptorAllocator                          */
/* -------------------------------------------- */

void DescriptorAllocator::initPool(const vk::Device device, const uint32_t maxSets, std::span<const PoolSizeRatio> ratios) {
    this->device = device;
    std::vector<vk::DescriptorPoolSize> poolSizes;

    for (auto [type, ratio] : ratios) {
        poolSizes.emplace_back(type, static_cast<uint32_t>(ratio * maxSets));
    }

    pool = device.createDescriptorPool({(vk::DescriptorPoolCreateFlagBits) 0, maxSets, poolSizes});
}

void DescriptorAllocator::clearDescriptors() const {
    device.resetDescriptorPool(pool);
}

void DescriptorAllocator::destroyPool() const {
    device.destroyDescriptorPool(pool);
}

VkDescriptorSet DescriptorAllocator::allocate(vk::DescriptorSetLayout layout) const {
    vk::DescriptorSetAllocateInfo allocInfo = {
        pool,
        1,
        &layout
    };
    vk::DescriptorSet set;
    VK_QUICK_FAIL(device.allocateDescriptorSets(&allocInfo, &set));

    return set;
}