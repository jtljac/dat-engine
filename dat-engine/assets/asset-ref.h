#pragma once

#include <util/type-traits.h>

#include "asset.h"

template<DatEngine::subClass<Asset> assetType = Asset>
class AssetRef {
    /** The asset this references */
    assetType* asset;

    /** The number of asset references to this asset */
    unsigned int* const refCount;

    AssetRef(Asset* asset) : asset(asset),
                             refCount(new unsigned int(0)) {}
    AssetRef(Asset* asset, unsigned int refCount) : asset(asset),
                                                    refCount(new unsigned int(refCount)) {}
public:
    /**
     * Copy constructor/automatic static cast
     * <br>
     * This handles the smart pointer part of this data structure, incrementing the count of references
     * <br>
     * This also automatically converts between parent and child classes
     * @tparam otherAssetType The type to convert the reference to
     * @param otherAssetRef The asset reference to generate this one off of
     */
    template<baseClass<Asset> otherAssetType>
    requires(exactClass<otherAssetType, assetType> || baseClass<otherAssetType, assetType> || subClass<otherAssetType, assetType>)
    AssetRef(const AssetRef& otherAssetRef);

    /**
     * Create an AssetRef with from given asset
     * @param asset The asset to be held by the AssetRef
     * @return The newly created AssetRef
     */
    static AssetRef createAssetRef(assetType* asset);

    ~AssetRef();

    Asset operator*();

    Asset* operator->();

    /**
     * Get the number of references to this asset currently in memory
     * @return The number of current references to this file
     */
    unsigned int getRefCount();

    /**
     * Create a copy of this AssetRef, incrementing the number of references
     * <br>
     * This also handles static casting between child and parent classes
     * @tparam otherAssetType The type to convert the reference to
     * @param otherAssetRef The asset reference to generate this one off of
     * @return a new AssetRef to the asset
     */
    template<baseClass<Asset> newAssetType = assetType>
    requires(exactClass<newAssetType, assetType> || baseClass<newAssetType, assetType> || subClass<newAssetType, assetType>)
    AssetRef<newAssetType> clone();
};

#include "source/asset-ref.inl"