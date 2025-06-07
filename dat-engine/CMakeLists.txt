cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
        "dat-engine.h" "source/dat-engine.cpp"
)

#add_subdirectory(assets)
add_subdirectory(container)
add_subdirectory(maths)
add_subdirectory(platform)
add_subdirectory(gpu)
add_subdirectory(util)

target_include_directories(dat-engine PUBLIC ./)
target_include_directories(dat-engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_custom_target(asset-processor
        COMMAND dat-asset-processor-application -i "${CMAKE_CURRENT_LIST_DIR}/engine-assets" -i "${projectAssetDir}" "${assetDest}" #[["${CMAKE_CURRENT_LIST_DIR}/ShaderLibrary"]]
        COMMENT "Running Asset Processor"
        )
add_dependencies(dat-engine asset-processor)