#pragma once

#include <unordered_map>
#include <typeinfo>
#include <functional>

#include <util/TypeTraits.h>

#include <DatVfs.h>

#include "Asset.h"
#include "AssetRef.h"
#include "service/EngineService.h"

using TypeInfoRef = std::reference_wrapper<const std::type_info>;

namespace DatEngine::Assets {
    class AssetManager : public Service::EngineService {
        /** Cache for engine-assets already in use */
        std::unordered_map<Dvfs::DatPath, AssetRef<>> assetCache;

        Dvfs::DatVFS vfs;

        template<TypeTraits::CSubClass<Asset> TAssetType>
        AssetRef<TAssetType> getAsset(const Dvfs::DatPath& path, const bool ensureLoaded = false) {
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