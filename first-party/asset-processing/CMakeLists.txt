cmake_minimum_required(VERSION 3.22)

include(cmake/CPM.cmake)

project(dat-asset-processor
        VERSION 1.0.0
        DESCRIPTION "Library for handling asset processing"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

#################################################
# Static Library                                #
#################################################

add_library(dat-asset-processor STATIC)
target_link_libraries(dat-asset-processor PRIVATE dat-asset-io)

#CPMAddPackage("gh:KhronosGroup/glslang#15.4.0")
#CPMAddPackage(gh:KhronosGroup/SPIRV-Tools@2024.4)
#target_link_libraries(lib-dat-asset-processor PRIVATE glslang::glslang glslang::glslang-default-resource-limits glslang::SPIRV glslang::SPVRemapper)

find_package(glslang CONFIG REQUIRED)
target_link_libraries(dat-asset-processor PRIVATE glslang::glslang glslang::glslang-default-resource-limits glslang::SPIRV glslang::SPVRemapper)

CPMAddPackage(gh:assimp/assimp@6.0.2)
target_link_libraries(dat-asset-processor PRIVATE assimp::assimp)

target_include_directories(dat-asset-processor PUBLIC include)

target_sources(dat-asset-processor PRIVATE
        include/AssetProcessException.h
        include/BaseAssetProcessor.h source/BaseAssetProcessor.cpp
        include/ShaderProcessor.h source/ShaderProcessor.cpp
)

#################################################
# Application                                   #
#################################################

add_executable(dat-asset-processor-application
        source/application/AssetProcessorApplication.cpp
)

add_dependencies(dat-asset-processor-application dat-asset-processor)
target_link_libraries(dat-asset-processor-application PRIVATE dat-asset-processor)


CPMAddPackage(gh:CLIUtils/CLI11@2.5.0)
find_package(CLI11 CONFIG REQUIRED)
target_link_libraries(dat-asset-processor-application PRIVATE CLI11::CLI11)

# FMT
CPMAddPackage("gh:fmtlib/fmt#11.2.0")
target_link_libraries(dat-asset-processor-application PUBLIC fmt::fmt)

# SPDLog
CPMAddPackage(gh:gabime/spdlog@1.15.3)
target_link_libraries(dat-asset-processor-application PUBLIC spdlog::spdlog)