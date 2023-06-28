cmake_minimum_required(VERSION 3.22)

add_subdirectory(util)
add_subdirectory(platform)
add_subdirectory(rendering)

target_include_directories(dat-engine PUBLIC ./)

target_sources(dat-engine PRIVATE "source/dat-engine.cpp")

#add_custom_target(assetProcessor
#        COMMAND asset-processor "${CMAKE_CURRENT_LIST_DIR}/Assets" "${projectAssetDir}" "${assetDest}" "${CMAKE_CURRENT_LIST_DIR}/ShaderLibrary"
#        COMMENT "Running Asset Processor"
#        )
#add_dependencies(dat-engine assetProcessor)