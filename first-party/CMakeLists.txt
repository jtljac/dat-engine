cmake_minimum_required(VERSION 3.22)
add_subdirectory(dat-archive)
target_link_libraries(dat-engine dat-archive)

add_subdirectory(dat-vfs)
target_link_libraries(dat-engine dat-vfs)