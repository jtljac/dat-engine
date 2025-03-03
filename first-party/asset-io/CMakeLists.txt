cmake_minimum_required(VERSION 3.22)

project(lib-dat-asset-io)

add_library(lib-dat-asset-io INTERFACE)

target_include_directories(lib-dat-asset-io INTERFACE include)

target_sources(lib-dat-asset-io PRIVATE
        "include/asset-io-result.h"
        "include/dat-mesh/meta.h" "include/dat-mesh/reader.h" "include/dat-mesh/writer.h"
        "source/dat-mesh/reader.cpp" "source/dat-mesh/writer.cpp"
)