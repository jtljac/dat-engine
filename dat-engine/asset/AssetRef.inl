#ifndef ASSETREF_INL
#define ASSETREF_INL
template<CSubClass<Asset> TAssetType>
template<CBaseClass<Asset> TOtherAssetType>
requires(CExactClass<TOtherAssetType, TAssetType> || CBaseClass<TOtherAssetType, TAssetType> ||
         CSubClass<TOtherAssetType, TAssetType>)
AssetRef<TAssetType>::AssetRef(const AssetRef& otherAssetRef) : asset(static_cast<TAssetType>(otherAssetRef.asset)), refCount(otherAssetRef.refCount) {
    ++(*refCount);
}

template<CSubClass<Asset> TAssetType>
AssetRef<TAssetType>::~AssetRef() {
    --(*refCount);
}

template<CSubClass<Asset> TAssetType>
AssetRef<TAssetType> AssetRef<TAssetType>::createAssetRef(TAssetType* asset) {
    return {asset};
}

template<CSubClass<Asset> TAssetType>
TAssetType& AssetRef<TAssetType>::operator*() {
    return *asset;
}

template<CSubClass<Asset> TAssetType>
TAssetType& AssetRef<TAssetType>::operator->() {
    return asset;
}

template<CSubClass<Asset> TAssetType>
unsigned int AssetRef<TAssetType>::getRefCount() {
    return *refCount;
}

template<CSubClass<Asset> TAssetType>
template<CBaseClass<Asset> newTAssetType>
    requires(CExactClass<newTAssetType, TAssetType> || CBaseClass<newTAssetType, TAssetType> ||
             CSubClass<newTAssetType, TAssetType>)
AssetRef<newTAssetType> AssetRef<TAssetType>::clone() {
    return AssetRef<newTAssetType>(*this);
}
#endif // ASSETREF_INL