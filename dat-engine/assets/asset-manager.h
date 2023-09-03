//
// Created by jacob on 11/08/23.
//

#pragma once

#include <unordered_map>
#include <typeinfo>
#include <functional>

#include <util/type-traits.h>

#include <dat-vfs.h>

#include "asset.h"
#include "asset-ref.h"
#include "asset-factory.h"

using TypeInfoRef = std::reference_wrapper<const std::type_info>;

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
    /** Cache for assets already in use */
    std::unordered_map<DVFS::DatPath, AssetRef<Asset>> assetCache;

    /** Factories for loading assets from the disk */
    std::unordered_map<TypeInfoRef, AssetFactory*, TypeInfoHasher, TypeInfoEqualTo> assetFactories;

    template<subClass<Asset> assetType>
    AssetRef<assetType>* getAsset(const DVFS::DatPath& path, const bool ensureLoaded = false) {
        // Check cache
        if (assetCache.contains(path)) {
            return assetCache.at(path).clone<assetType>();
        }

        // Create new asset ref
        assetType* asset = new assetType(this, path);
        assetCache.emplace(path, asset);

        if (ensureLoaded) {
            // TODO: add to load queue
        }

        return AssetRef<assetType>::createAssetRef(asset);
    }

    // Garbage collection
    // Load Asset
};