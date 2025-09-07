cmake_minimum_required(VERSION 3.22)

project(dat-asset-io)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

add_library(dat-asset-io STATIC "include/AssetIoResult.h"
        "include/dat-mesh/Meta.h" "source/dat-mesh/Meta.cpp"
        "include/dat-mesh/Reader.h" "source/dat-mesh/Reader.cpp"
        "include/dat-mesh/Writer.h" "source/dat-mesh/Writer.cpp")

target_include_directories(dat-asset-io PUBLIC include)