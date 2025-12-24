#ifndef ASSETREF_INL
#define ASSETREF_INL

template<TypeTraits::CSubClass<Asset> TAssetType>
template<TypeTraits::CBaseClass<Asset> TOtherAssetType>
requires(TypeTraits::CConvertsTo<TAssetType, TOtherAssetType>)
AssetRef<TAssetType>::AssetRef(const AssetRef& otherAssetRef) : asset(static_cast<TAssetType>(otherAssetRef.asset)), refCount(otherAssetRef.refCount) {
    ++(*refCount);
}

template<TypeTraits::CSubClass<Asset> TAssetType>
AssetRef<TAssetType>::~AssetRef() {
    if (refCount != nullptr) --(*refCount);
}

template<TypeTraits::CSubClass<Asset> TAssetType>
AssetRef<TAssetType> AssetRef<TAssetType>::createAssetRef(TAssetType* asset) {
    return {asset};
}

template<TypeTraits::CSubClass<Asset> TAssetType>
TAssetType& AssetRef<TAssetType>::operator*() {
    return *asset;
}

template<TypeTraits::CSubClass<Asset> TAssetType>
TAssetType& AssetRef<TAssetType>::operator->() {
    return *asset;
}

template<TypeTraits::CSubClass<Asset> TAssetType>
unsigned int AssetRef<TAssetType>::getRefCount() {
    return *refCount;
}

template<TypeTraits::CSubClass<Asset> TAssetType>
template<TypeTraits::CBaseClass<Asset> newTAssetType>
    requires(TypeTraits::CExactClass<newTAssetType, TAssetType> || TypeTraits::CBaseClass<newTAssetType, TAssetType> ||
             TypeTraits::CSubClass<newTAssetType, TAssetType>)
AssetRef<newTAssetType> AssetRef<TAssetType>::clone() {
    return AssetRef<newTAssetType>(*this);
}
#endif // ASSETREF_INL