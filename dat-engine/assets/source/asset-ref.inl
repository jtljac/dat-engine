template<subClass<Asset> assetType>
template<baseClass<Asset> otherAssetType>
requires(exactClass<otherAssetType, assetType> || baseClass<otherAssetType, assetType> ||
         subClass<otherAssetType, assetType>)
AssetRef<assetType>::AssetRef(const AssetRef& otherAssetRef) : asset(static_cast<assetType>(otherAssetRef.asset)), refCount(otherAssetRef.refCount) {
    ++(*refCount);
}

template<subClass<Asset> assetType>
AssetRef<assetType>::~AssetRef() {
    --(*refCount);
}

template<subClass<Asset> assetType>
AssetRef<assetType> AssetRef<assetType>::createAssetRef(assetType* asset) {
    return {asset};
}

template<subClass<Asset> assetType>
Asset AssetRef<assetType>::operator*() {
    return *asset;
}

template<subClass<Asset> assetType>
Asset* AssetRef<assetType>::operator->() {
    return asset;
}

template<subClass<Asset> assetType>
unsigned int AssetRef<assetType>::getRefCount() {
    return *refCount;
}

template<subClass<Asset> assetType>
template<baseClass<Asset> newAssetType>
requires(exactClass<newAssetType, assetType> || baseClass<newAssetType, assetType> || subClass<newAssetType, assetType>)
AssetRef<newAssetType> AssetRef<assetType>::clone() {
    return AssetRef<newAssetType>(*this);
}