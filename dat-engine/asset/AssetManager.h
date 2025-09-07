#pragma once

#include <unordered_map>
#include <typeinfo>
#include <functional>

#include <util/TypeTraits.h>

#include <dat-vfs.h>

#include "Asset.h"
#include "AssetRef.h"
#include "AssetFactory.h"

using TypeInfoRef = std::reference_wrapper<const std::type_info>;

namespace DatEngine::Assets {
    struct TypeInfoHasher {
        std::size_t operator()(TypeInfoRef code) const
        {
            return code.get().hash_code();
        }
    };

    struct TypeInfoEqualTo {
        bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
        {
            return lhs.get() == rhs.get();
        }
    };

    class AssetManager {
        /** Cache for engine-assets already in use */
        std::unordered_map<DVFS::DatPath, AssetRef<Asset>> assetCache;

        /** Factories for loading engine-assets from the disk */
        std::unordered_map<TypeInfoRef, AssetFactory*, TypeInfoHasher, TypeInfoEqualTo> assetFactories;

        template<CSubClass<Asset> TAssetType>
        AssetRef<TAssetType>* getAsset(const DVFS::DatPath& path, const bool ensureLoaded = false) {
            // Check cache
            if (assetCache.contains(path)) {
                return assetCache.at(path).clone<TAssetType>();
            }

            // Create new asset ref
            TAssetType* asset = new TAssetType(this, path);
            assetCache.emplace(path, asset);

            if (ensureLoaded) {
                // TODO: add to load queue
            }

            return AssetRef<TAssetType>::createAssetRef(asset);
        }

        // Garbage collection
        // Load Asset
    };
}