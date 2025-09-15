#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>

#include "DatPath.h"

namespace DatEngine::Assets {
    // Predefines
    class AssetManager;

    enum class AssetState : uint32_t {
        UNLOADED,
        LOADING,
        LOADED,
        UNLOADING
    };

    class Asset {
    protected:
        AssetManager* owningAssMan;

        AssetState state = AssetState::UNLOADED;
        unsigned int cpuLock = 0;

        Dvfs::DatPath assetPath;
    public:
        Asset(AssetManager* owningAssMan, Dvfs::DatPath assetPath) : owningAssMan(owningAssMan),
                                                                            assetPath(std::move(assetPath)) {};

        // Deconstructor must be dealt with to clear asset from memory
        virtual ~Asset() = 0;

        // Lock and unlock
        void lock() {
            ++cpuLock;
        }

        void unlock() {
            assert(cpuLock != 0);
            --cpuLock;
        }

        // Load and unload (virtual)
        void load() {
            switch (state) {
                case AssetState::UNLOADED:
                    // Start load
                    break;
                case AssetState::UNLOADING:
                    // Cancel unload
                    break;
                default:
                    // Do nothing
                    break;
            }
        }
    };
}