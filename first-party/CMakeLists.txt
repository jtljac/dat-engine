cmake_minimum_required(VERSION 3.22)
add_subdirectory(dat-archive)
target_link_libraries(dat-engine PUBLIC dat-archive)

add_subdirectory(dat-vfs)
target_link_libraries(dat-engine PUBLIC dat-vfs)

add_subdirectory(asset-io)
target_link_libraries(dat-engine PUBLIC lib-dat-asset-io)
add_subdirectory(asset-processing)