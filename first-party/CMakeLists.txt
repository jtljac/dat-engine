cmake_minimum_required(VERSION 3.22)

# Dat Archive
CPMAddPackage("gh:jtljac/dat-archive#master")
target_link_libraries(dat-engine PUBLIC dat-archive)

# Dat VFS
CPMAddPackage("gh:jtljac/dat-vfs#master")
target_link_libraries(dat-engine PUBLIC dat-vfs)

# Asset IO
add_subdirectory(asset-io)
target_link_libraries(dat-engine PUBLIC dat-asset-io)

# Asset Processing
add_subdirectory(asset-processing)