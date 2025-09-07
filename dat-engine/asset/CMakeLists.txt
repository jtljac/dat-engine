cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
    "Asset.h" "GpuAsset.h"
    "AssetRef.h"
    "AssetFactory.h"
    "AssetManager.h" "AssetManager.cpp"
)