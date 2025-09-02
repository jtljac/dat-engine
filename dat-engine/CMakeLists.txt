cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
        "DatEngine.h" "DatEngine.cpp"
)

add_subdirectory(util)
add_subdirectory(container)
add_subdirectory(maths)
add_subdirectory(platform)
add_subdirectory(gpu)

target_include_directories(dat-engine PUBLIC ./)
target_include_directories(dat-engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

#add_custom_target(asset-processor
#        COMMAND dat-asset-processor-application -i "${CMAKE_CURRENT_LIST_DIR}/engine-assets" -i "${projectAssetDir}" "${assetDest}" #[["${CMAKE_CURRENT_LIST_DIR}/ShaderLibrary"]]
#        COMMENT "Running Asset Processor"
#)
#add_dependencies(dat-engine asset-processor)