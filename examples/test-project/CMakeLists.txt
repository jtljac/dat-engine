cmake_minimum_required(VERSION 3.22)

add_executable(dat-game main.cpp)

target_link_libraries(dat-game dat-engine)

#target_sources(dat-game PRIVATE
#        )

set(assetDest "${CMAKE_CURRENT_BINARY_DIR}/assets"  CACHE INTERNAL "")
#set(projectAssetDir "${CMAKE_CURRENT_LIST_DIR}/project-assets"  CACHE INTERNAL "")


add_dependencies(dat-game asset-processor)