#pragma once


#include "Asset.h"
namespace DatEngine::Assets {
    template<CSubClass<Asset> TAssetType = Asset>
    class AssetRef {
        /** The asset this references */
        TAssetType* asset;

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
        template<CBaseClass<Asset> otherAssetType>
        requires(CExactClass<otherAssetType, TAssetType> || CBaseClass<otherAssetType, TAssetType> || CSubClass<otherAssetType, TAssetType>)
        AssetRef(const AssetRef& otherAssetRef);

        /**
         * Create an AssetRef with from given asset
         * @param asset The asset to be held by the AssetRef
         * @return The newly created AssetRef
         */
        static AssetRef createAssetRef(TAssetType* asset);

        ~AssetRef();

        TAssetType& operator*();

        TAssetType& operator->();

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
        template<CBaseClass<Asset> newAssetType = TAssetType>
        requires(CExactClass<newAssetType, TAssetType> || CBaseClass<newAssetType, TAssetType> || CSubClass<newAssetType, TAssetType>)
        AssetRef<newAssetType> clone();
    };

#include "AssetRef.inl"
}