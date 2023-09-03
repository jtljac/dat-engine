cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
    "asset.h" "gpu-asset.h"
    "asset-ref.h"
    "asset-factory.h"
    "asset-manager.h" "source/asset-manager.cpp"
)