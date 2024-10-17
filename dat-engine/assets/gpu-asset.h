#pragma once

#include "asset.h"

class GpuAsset : public Asset {
    AssetState gpuState = AssetState::UNLOADED;
    unsigned int gpuLock = 0;

public:
    // GPU Lock and unlock
};