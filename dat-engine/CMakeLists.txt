cmake_minimum_required(VERSION 3.22)

target_sources(dat-engine PRIVATE
        "dat-engine.h" "source/dat-engine.cpp"
)

add_subdirectory(container)
add_subdirectory(maths)
add_subdirectory(platform)
add_subdirectory(rendering)
add_subdirectory(util)

target_include_directories(dat-engine PUBLIC ./)
target_include_directories(dat-engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

#add_custom_target(assetProcessor
#        COMMAND asset-processor "${CMAKE_CURRENT_LIST_DIR}/Assets" "${projectAssetDir}" "${assetDest}" "${CMAKE_CURRENT_LIST_DIR}/ShaderLibrary"
#        COMMENT "Running Asset Processor"
#        )
#add_dependencies(dat-engine assetProcessor)